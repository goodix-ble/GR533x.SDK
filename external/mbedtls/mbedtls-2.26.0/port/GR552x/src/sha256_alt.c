/*
 *  FIPS-180-2 compliant SHA-256 implementation
 *
 *  Copyright The Mbed TLS Contributors
 *  SPDX-License-Identifier: Apache-2.0
 *
 *  Licensed under the Apache License, Version 2.0 (the "License"); you may
 *  not use this file except in compliance with the License.
 *  You may obtain a copy of the License at
 *
 *  http://www.apache.org/licenses/LICENSE-2.0
 *
 *  Unless required by applicable law or agreed to in writing, software
 *  distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 *  WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 *  See the License for the specific language governing permissions and
 *  limitations under the License.
 */
/*
 *  The SHA-256 Secure Hash Standard was published by NIST in 2002.
 *
 *  http://csrc.nist.gov/publications/fips/fips180-2/fips180-2.pdf
 */

#include "common.h"

#if defined(MBEDTLS_SHA256_C)

#include "sha256.h"
#include "platform_util.h"
#include "error.h"

#include <string.h>

#if defined(MBEDTLS_SELF_TEST)
#if defined(MBEDTLS_PLATFORM_C)
#include "platform.h"
#else
#include <stdio.h>
#include <stdlib.h>
#define mbedtls_printf printf
#define mbedtls_calloc    calloc
#define mbedtls_free       free
#endif /* MBEDTLS_PLATFORM_C */
#endif /* MBEDTLS_SELF_TEST */

#define SHA256_VALIDATE_RET(cond)                           \
    MBEDTLS_INTERNAL_VALIDATE_RET( cond, MBEDTLS_ERR_SHA256_BAD_INPUT_DATA )
#define SHA256_VALIDATE(cond)  MBEDTLS_INTERNAL_VALIDATE( cond )

#if defined(MBEDTLS_SHA256_ALT)
#include "grx_hal.h"

/*
 * 32-bit integer manipulation macros (big endian)
 */
#ifndef GET_UINT32_BE
#define GET_UINT32_BE(n,b,i)                            \
do {                                                    \
    (n) = ( (uint32_t) (b)[(i)    ] << 24 )             \
        | ( (uint32_t) (b)[(i) + 1] << 16 )             \
        | ( (uint32_t) (b)[(i) + 2] <<  8 )             \
        | ( (uint32_t) (b)[(i) + 3]       );            \
} while( 0 )
#endif

#ifndef PUT_UINT32_BE
#define PUT_UINT32_BE(n,b,i)                            \
do {                                                    \
    (b)[(i)    ] = (unsigned char) ( (n) >> 24 );       \
    (b)[(i) + 1] = (unsigned char) ( (n) >> 16 );       \
    (b)[(i) + 2] = (unsigned char) ( (n) >>  8 );       \
    (b)[(i) + 3] = (unsigned char) ( (n)       );       \
} while( 0 )
#endif

static void hmac_clock_enable(void)
{
    ll_cgc_disable_force_off_secu_hclk();
    ll_cgc_disable_wfi_off_secu_hclk();
    ll_cgc_disable_force_off_hmac_hclk();
    ll_cgc_disable_force_off_secu_div4_pclk();
    ll_cgc_disable_wfi_off_hmac_hclk();
    ll_cgc_disable_wfi_off_secu_div4_hclk();
}

static void hmac_clock_disable(void)
{
    ll_cgc_enable_force_off_hmac_hclk();
    ll_cgc_enable_wfi_off_hmac_hclk();

    if (ll_cgc_get_force_off_secu() == LL_CGC_MCU_SECU_FRC_OFF_HCLK)
    {
        ll_cgc_enable_force_off_secu_hclk();
        ll_cgc_enable_force_off_secu_div4_pclk();
    }

    if (ll_cgc_get_slp_off_secu() == LL_CGC_MCU_SECU_FRC_OFF_WFI_HCLK)
    {
        ll_cgc_enable_wfi_off_secu_hclk();
        ll_cgc_enable_wfi_off_secu_div4_hclk();
    }
}

void mbedtls_sha256_init( mbedtls_sha256_context *ctx )
{
    SHA256_VALIDATE( ctx != NULL );

    memset( ctx, 0, sizeof( mbedtls_sha256_context ) );
}

void mbedtls_sha256_free( mbedtls_sha256_context *ctx )
{
    if( ctx == NULL )
        return;

    mbedtls_platform_zeroize( ctx, sizeof( mbedtls_sha256_context ) );
}

void mbedtls_sha256_clone( mbedtls_sha256_context *dst,
                           const mbedtls_sha256_context *src )
{
    SHA256_VALIDATE( dst != NULL );
    SHA256_VALIDATE( src != NULL );

    *dst = *src;
}

/*
 * SHA-256 context setup
 */
int mbedtls_sha256_starts_ret( mbedtls_sha256_context *ctx, int is224 )
{
    SHA256_VALIDATE_RET( ctx != NULL );
    SHA256_VALIDATE_RET( is224 == 0 || is224 == 1 );

    ctx->total[0] = 0;
    ctx->total[1] = 0;

    if( is224 == 0 )
    {
        /* SHA-256 */
        ctx->state[0] = 0x6A09E667;
        ctx->state[1] = 0xBB67AE85;
        ctx->state[2] = 0x3C6EF372;
        ctx->state[3] = 0xA54FF53A;
        ctx->state[4] = 0x510E527F;
        ctx->state[5] = 0x9B05688C;
        ctx->state[6] = 0x1F83D9AB;
        ctx->state[7] = 0x5BE0CD19;
    }
    else
    {
        /* SHA-224 */
        ctx->state[0] = 0xC1059ED8;
        ctx->state[1] = 0x367CD507;
        ctx->state[2] = 0x3070DD17;
        ctx->state[3] = 0xF70E5939;
        ctx->state[4] = 0xFFC00B31;
        ctx->state[5] = 0x68581511;
        ctx->state[6] = 0x64F98FA7;
        ctx->state[7] = 0xBEFA4FA4;
    }

    ctx->is224 = is224;

    return( 0 );
}

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_sha256_starts( mbedtls_sha256_context *ctx,
                            int is224 )
{
    mbedtls_sha256_starts_ret( ctx, is224 );
}
#endif

#define SWAP_ENDIAN_32_ARRAY(arr, size) \
do { \
    for(uint32_t i = 0; i < (size); i++) { \
        (arr)[i] = ( ((arr)[i] >> 24) | (((arr)[i] & 0x00FF0000) >> 8) | (((arr)[i] & 0x0000FF00) << 8) | ((arr)[i] << 24) ); \
    } \
} while(0)

static void hmac_read_data(uint32_t *p_data)
{
    for (uint32_t i = 0U; i < HMAC_DIGESTSIZE_WORDS; i++)
    {
        p_data[i] = HMAC->DATA_OUT;
    }
}

static void hmac_write_data(uint32_t *p_data)
{
    for (uint32_t i = 0U; i < HMAC_BLOCKSIZE_WORDS; i++)
    {
        HMAC->DATA_IN = p_data[i];
    }
}

int mbedtls_internal_sha256_process( mbedtls_sha256_context *ctx,
                                const unsigned char data[64] )
{
    SHA256_VALIDATE_RET( ctx != NULL );
    SHA256_VALIDATE_RET( (const unsigned char *)data != NULL );

    /* HMAC clock enable */
    hmac_clock_enable();

    /* Set SHA mode */
    ll_hmac_enable_sha(HMAC);

    /* Set initial HASH in user HASH mode */
    ll_hmac_enable_user_hash(HMAC);
    SWAP_ENDIAN_32_ARRAY(ctx->state, 8);
    ll_hmac_set_user_hash_255_224(HMAC, ctx->state[0]);
    ll_hmac_set_user_hash_223_192(HMAC, ctx->state[1]);
    ll_hmac_set_user_hash_191_160(HMAC, ctx->state[2]);
    ll_hmac_set_user_hash_159_128(HMAC, ctx->state[3]);
    ll_hmac_set_user_hash_127_96 (HMAC, ctx->state[4]);
    ll_hmac_set_user_hash_95_64  (HMAC, ctx->state[5]);
    ll_hmac_set_user_hash_63_32  (HMAC, ctx->state[6]);
    ll_hmac_set_user_hash_31_0   (HMAC, ctx->state[7]);

    /* Disable DPA Resistence */
    ll_hmac_disable_private(HMAC);

    /* Set big endian */
    ll_hmac_disable_little_endian(HMAC);

    /* Disable interrupt and clear flag */
    HMAC->INT = 1U;

    /* HMAC enable */
    ll_hmac_enable(HMAC);

    /* MCU write HMAC input */
    hmac_write_data((uint32_t *)data);

    /* HMAC wait for completion */
    while(READ_BITS(HMAC->STAT, LL_HMAC_FLAG_DATAREADY_SHA) == 0U);

    /* MCU read HMAC output */
    hmac_read_data(ctx->state);
    SWAP_ENDIAN_32_ARRAY(ctx->state, 8);

    /* HMAC disable */
    ll_hmac_disable(HMAC);

    /* HMAC clock disable */
    hmac_clock_disable();

    return( 0 );
}

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_sha256_process( mbedtls_sha256_context *ctx,
                             const unsigned char data[64] )
{
    mbedtls_internal_sha256_process( ctx, data );
}
#endif

/*
 * SHA-256 process buffer
 */
int mbedtls_sha256_update_ret( mbedtls_sha256_context *ctx,
                               const unsigned char *input,
                               size_t ilen )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    size_t fill;
    uint32_t left;

    SHA256_VALIDATE_RET( ctx != NULL );
    SHA256_VALIDATE_RET( ilen == 0 || input != NULL );

    if( ilen == 0 )
        return( 0 );

    left = ctx->total[0] & 0x3F;
    fill = 64 - left;

    ctx->total[0] += (uint32_t) ilen;
    ctx->total[0] &= 0xFFFFFFFF;

    if( ctx->total[0] < (uint32_t) ilen )
        ctx->total[1]++;

    if( left && ilen >= fill )
    {
        memcpy( (void *) (ctx->buffer + left), input, fill );

        if( ( ret = mbedtls_internal_sha256_process( ctx, ctx->buffer ) ) != 0 )
            return( ret );

        input += fill;
        ilen  -= fill;
        left = 0;
    }

    while( ilen >= 64 )
    {
        if( ( ret = mbedtls_internal_sha256_process( ctx, input ) ) != 0 )
            return( ret );

        input += 64;
        ilen  -= 64;
    }

    if( ilen > 0 )
        memcpy( (void *) (ctx->buffer + left), input, ilen );

    return( 0 );
}

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_sha256_update( mbedtls_sha256_context *ctx,
                            const unsigned char *input,
                            size_t ilen )
{
    mbedtls_sha256_update_ret( ctx, input, ilen );
}
#endif

/*
 * SHA-256 final digest
 */
int mbedtls_sha256_finish_ret( mbedtls_sha256_context *ctx,
                               unsigned char output[32] )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    uint32_t used;
    uint32_t high, low;

    SHA256_VALIDATE_RET( ctx != NULL );
    SHA256_VALIDATE_RET( (unsigned char *)output != NULL );

    /*
     * Add padding: 0x80 then 0x00 until 8 bytes remain for the length
     */
    used = ctx->total[0] & 0x3F;

    ctx->buffer[used++] = 0x80;

    if( used <= 56 )
    {
        /* Enough room for padding + length in current block */
        memset( ctx->buffer + used, 0, 56 - used );
    }
    else
    {
        /* We'll need an extra block */
        memset( ctx->buffer + used, 0, 64 - used );

        if( ( ret = mbedtls_internal_sha256_process( ctx, ctx->buffer ) ) != 0 )
            return( ret );

        memset( ctx->buffer, 0, 56 );
    }

    /*
     * Add message length
     */
    high = ( ctx->total[0] >> 29 )
         | ( ctx->total[1] <<  3 );
    low  = ( ctx->total[0] <<  3 );

    PUT_UINT32_BE( high, ctx->buffer, 56 );
    PUT_UINT32_BE( low,  ctx->buffer, 60 );

    if( ( ret = mbedtls_internal_sha256_process( ctx, ctx->buffer ) ) != 0 )
        return( ret );

    /*
     * Output final state
     */
    PUT_UINT32_BE( ctx->state[0], output,  0 );
    PUT_UINT32_BE( ctx->state[1], output,  4 );
    PUT_UINT32_BE( ctx->state[2], output,  8 );
    PUT_UINT32_BE( ctx->state[3], output, 12 );
    PUT_UINT32_BE( ctx->state[4], output, 16 );
    PUT_UINT32_BE( ctx->state[5], output, 20 );
    PUT_UINT32_BE( ctx->state[6], output, 24 );

    if( ctx->is224 == 0 )
        PUT_UINT32_BE( ctx->state[7], output, 28 );

    return( 0 );
}

#if !defined(MBEDTLS_DEPRECATED_REMOVED)
void mbedtls_sha256_finish( mbedtls_sha256_context *ctx,
                            unsigned char output[32] )
{
    mbedtls_sha256_finish_ret( ctx, output );
}
#endif

#endif /* !MBEDTLS_SHA256_ALT */

#endif /* MBEDTLS_SHA256_C */
