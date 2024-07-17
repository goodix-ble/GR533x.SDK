/*
 *  Elliptic curve DSA
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
 * References:
 *
 * SEC1 http://www.secg.org/index.php?action=secg,docs_secg
 */

#include "common.h"

#if defined(MBEDTLS_ECDSA_C)

#include "mbedtls/ecdsa.h"
#include "mbedtls/asn1write.h"

#include <string.h>

#if defined(MBEDTLS_ECDSA_DETERMINISTIC)
#include "mbedtls/hmac_drbg.h"
#endif

#if defined(MBEDTLS_PLATFORM_C)
#include "mbedtls/platform.h"
#else
#include <stdlib.h>
#define mbedtls_calloc    calloc
#define mbedtls_free       free
#endif

#include "mbedtls/platform_util.h"
#include "mbedtls/error.h"

/* Parameter validation macros based on platform_util.h */
#define ECDSA_VALIDATE_RET( cond )    \
    MBEDTLS_INTERNAL_VALIDATE_RET( cond, MBEDTLS_ERR_ECP_BAD_INPUT_DATA )
#define ECDSA_VALIDATE( cond )        \
    MBEDTLS_INTERNAL_VALIDATE( cond )

#if defined(MBEDTLS_ECP_RESTARTABLE)

/*
 * Sub-context for ecdsa_verify()
 */
struct mbedtls_ecdsa_restart_ver
{
    mbedtls_mpi u1, u2;     /* intermediate values  */
    enum {                  /* what to do next?     */
        ecdsa_ver_init = 0, /* getting started      */
        ecdsa_ver_muladd,   /* muladd step          */
    } state;
};

/*
 * Init verify restart sub-context
 */
static void ecdsa_restart_ver_init( mbedtls_ecdsa_restart_ver_ctx *ctx )
{
    mbedtls_mpi_init( &ctx->u1 );
    mbedtls_mpi_init( &ctx->u2 );
    ctx->state = ecdsa_ver_init;
}

/*
 * Free the components of a verify restart sub-context
 */
static void ecdsa_restart_ver_free( mbedtls_ecdsa_restart_ver_ctx *ctx )
{
    if( ctx == NULL )
        return;

    mbedtls_mpi_free( &ctx->u1 );
    mbedtls_mpi_free( &ctx->u2 );

    ecdsa_restart_ver_init( ctx );
}

/*
 * Sub-context for ecdsa_sign()
 */
struct mbedtls_ecdsa_restart_sig
{
    int sign_tries;
    int key_tries;
    mbedtls_mpi k;          /* per-signature random */
    mbedtls_mpi r;          /* r value              */
    enum {                  /* what to do next?     */
        ecdsa_sig_init = 0, /* getting started      */
        ecdsa_sig_mul,      /* doing ecp_mul()      */
        ecdsa_sig_modn,     /* mod N computations   */
    } state;
};

/*
 * Init verify sign sub-context
 */
static void ecdsa_restart_sig_init( mbedtls_ecdsa_restart_sig_ctx *ctx )
{
    ctx->sign_tries = 0;
    ctx->key_tries = 0;
    mbedtls_mpi_init( &ctx->k );
    mbedtls_mpi_init( &ctx->r );
    ctx->state = ecdsa_sig_init;
}

/*
 * Free the components of a sign restart sub-context
 */
static void ecdsa_restart_sig_free( mbedtls_ecdsa_restart_sig_ctx *ctx )
{
    if( ctx == NULL )
        return;

    mbedtls_mpi_free( &ctx->k );
    mbedtls_mpi_free( &ctx->r );
}

#if defined(MBEDTLS_ECDSA_DETERMINISTIC)
/*
 * Sub-context for ecdsa_sign_det()
 */
struct mbedtls_ecdsa_restart_det
{
    mbedtls_hmac_drbg_context rng_ctx;  /* DRBG state   */
    enum {                      /* what to do next?     */
        ecdsa_det_init = 0,     /* getting started      */
        ecdsa_det_sign,         /* make signature       */
    } state;
};

/*
 * Init verify sign_det sub-context
 */
static void ecdsa_restart_det_init( mbedtls_ecdsa_restart_det_ctx *ctx )
{
    mbedtls_hmac_drbg_init( &ctx->rng_ctx );
    ctx->state = ecdsa_det_init;
}

/*
 * Free the components of a sign_det restart sub-context
 */
static void ecdsa_restart_det_free( mbedtls_ecdsa_restart_det_ctx *ctx )
{
    if( ctx == NULL )
        return;

    mbedtls_hmac_drbg_free( &ctx->rng_ctx );

    ecdsa_restart_det_init( ctx );
}
#endif /* MBEDTLS_ECDSA_DETERMINISTIC */

#define ECDSA_RS_ECP    ( rs_ctx == NULL ? NULL : &rs_ctx->ecp )

/* Utility macro for checking and updating ops budget */
#define ECDSA_BUDGET( ops )   \
    MBEDTLS_MPI_CHK( mbedtls_ecp_check_budget( grp, ECDSA_RS_ECP, ops ) );

/* Call this when entering a function that needs its own sub-context */
#define ECDSA_RS_ENTER( SUB )   do {                                 \
    /* reset ops count for this call if top-level */                 \
    if( rs_ctx != NULL && rs_ctx->ecp.depth++ == 0 )                 \
        rs_ctx->ecp.ops_done = 0;                                    \
                                                                     \
    /* set up our own sub-context if needed */                       \
    if( mbedtls_ecp_restart_is_enabled() &&                          \
        rs_ctx != NULL && rs_ctx->SUB == NULL )                      \
    {                                                                \
        rs_ctx->SUB = mbedtls_calloc( 1, sizeof( *rs_ctx->SUB ) );   \
        if( rs_ctx->SUB == NULL )                                    \
            return( MBEDTLS_ERR_ECP_ALLOC_FAILED );                  \
                                                                     \
        ecdsa_restart_## SUB ##_init( rs_ctx->SUB );                 \
    }                                                                \
} while( 0 )

/* Call this when leaving a function that needs its own sub-context */
#define ECDSA_RS_LEAVE( SUB )   do {                                 \
    /* clear our sub-context when not in progress (done or error) */ \
    if( rs_ctx != NULL && rs_ctx->SUB != NULL &&                     \
        ret != MBEDTLS_ERR_ECP_IN_PROGRESS )                         \
    {                                                                \
        ecdsa_restart_## SUB ##_free( rs_ctx->SUB );                 \
        mbedtls_free( rs_ctx->SUB );                                 \
        rs_ctx->SUB = NULL;                                          \
    }                                                                \
                                                                     \
    if( rs_ctx != NULL )                                             \
        rs_ctx->ecp.depth--;                                         \
} while( 0 )

#else /* MBEDTLS_ECP_RESTARTABLE */

#define ECDSA_RS_ECP    NULL

#define ECDSA_BUDGET( ops )   /* no-op; for compatibility */

#define ECDSA_RS_ENTER( SUB )   (void) rs_ctx
#define ECDSA_RS_LEAVE( SUB )   (void) rs_ctx

#endif /* MBEDTLS_ECP_RESTARTABLE */

#if defined(MBEDTLS_ECC_ALT)
#include "crypto_ecc.h"

#define SWAP_ENDIAN_32_ARRAY(arr, size) \
do { \
    for(uint32_t i = 0; i < (size); i++) { \
        (arr)[i] = ( ((arr)[i] >> 24) | (((arr)[i] & 0x00FF0000) >> 8) | (((arr)[i] & 0x0000FF00) << 8) | ((arr)[i] << 24) ); \
    } \
} while(0)

/*
 * Derive a suitable integer for group grp from a buffer of length len
 * SEC1 4.1.3 step 5 aka SEC1 4.1.4 step 3
 */
static int derive_mpi( const mbedtls_ecp_group *grp, mbedtls_mpi *x,
                       const unsigned char *buf, size_t blen )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    size_t n_size = ( grp->nbits + 7 ) / 8;
    size_t use_size = blen > n_size ? n_size : blen;

    MBEDTLS_MPI_CHK( mbedtls_mpi_read_binary( x, buf, use_size ) );
    if( use_size * 8 > grp->nbits )
        MBEDTLS_MPI_CHK( mbedtls_mpi_shift_r( x, use_size * 8 - grp->nbits ) );

    /* While at it, reduce modulo N */
    if( mbedtls_mpi_cmp_mpi( x, &grp->N ) >= 0 )
        MBEDTLS_MPI_CHK( mbedtls_mpi_sub_mpi( x, x, &grp->N ) );

cleanup:
    return( ret );
}

#if defined(MBEDTLS_ECDSA_SIGN_ALT)
static int hw_ecdsa_sign( mbedtls_ecp_group *grp, mbedtls_mpi *r, mbedtls_mpi *s,
                          const mbedtls_mpi *d, const unsigned char *buf, size_t blen )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    uint32_t in_signiture_r[8] = {0};
    uint32_t in_signiture_s[8] = {0};
    uint8_t private_key[32] = {0};
    algo_ecc_ecdsa_config_t ecc_ecdsa_ctx = {0};

    switch (grp->id)
    {
        case MBEDTLS_ECP_DP_SECP256R1:
            crypto_ecc_ecdsa_init(&ecc_ecdsa_ctx, ECC_CURVE_SECP256R1);
            break;
        case MBEDTLS_ECP_DP_SECP256K1:
            crypto_ecc_ecdsa_init(&ecc_ecdsa_ctx, ECC_CURVE_SECP256K1);
            break;
        default:
            ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
            goto cleanup;
    }

    mbedtls_mpi_write_binary(d, private_key, 32);
    SWAP_ENDIAN_32_ARRAY((uint32_t *)private_key, 8);
    memcpy(ecc_ecdsa_ctx.our_secret_value, private_key, 32);

    if ( (ret = crypto_ecc_ecdsa_sign(&ecc_ecdsa_ctx, ECC_HASH_NONE, (uint8_t *)buf, blen, in_signiture_r, in_signiture_s)) != 0)
    {
        goto cleanup;
    }

    SWAP_ENDIAN_32_ARRAY((uint32_t *)in_signiture_r, 8);
    SWAP_ENDIAN_32_ARRAY((uint32_t *)in_signiture_s, 8);
    mbedtls_mpi_read_binary(r, (const unsigned char *)in_signiture_r, 32);
    mbedtls_mpi_read_binary(s, (const unsigned char *)in_signiture_s, 32);

cleanup:
    return( ret );
}

/*
 * Compute ECDSA signature of a hashed message (SEC1 4.1.3)
 * Obviously, compared to SEC1 4.1.3, we skip step 4 (hash message)
 */
static int ecdsa_sign_restartable( mbedtls_ecp_group *grp,
                mbedtls_mpi *r, mbedtls_mpi *s,
                const mbedtls_mpi *d, const unsigned char *buf, size_t blen,
                int (*f_rng)(void *, unsigned char *, size_t), void *p_rng,
                int (*f_rng_blind)(void *, unsigned char *, size_t),
                void *p_rng_blind,
                mbedtls_ecdsa_restart_ctx *rs_ctx )
{
    int ret, key_tries, sign_tries;
    int *p_sign_tries = &sign_tries, *p_key_tries = &key_tries;
    mbedtls_ecp_point R;
    mbedtls_mpi k, e, t;
    mbedtls_mpi *pk = &k, *pr = r;

    /* Fail cleanly on curves such as Curve25519 that can't be used for ECDSA */
    if( ! mbedtls_ecdsa_can_do( grp->id ) || grp->N.p == NULL )
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );

    /* Make sure d is in range 1..n-1 */
    if( mbedtls_mpi_cmp_int( d, 1 ) < 0 || mbedtls_mpi_cmp_mpi( d, &grp->N ) >= 0 )
        return( MBEDTLS_ERR_ECP_INVALID_KEY );

    mbedtls_ecp_point_init( &R );
    mbedtls_mpi_init( &k ); mbedtls_mpi_init( &e ); mbedtls_mpi_init( &t );

    ECDSA_RS_ENTER( sig );

    switch (grp->id)
    {
        case MBEDTLS_ECP_DP_SECP256R1:
        case MBEDTLS_ECP_DP_SECP256K1:
            MBEDTLS_MPI_CHK( hw_ecdsa_sign( grp, r, s, d, buf, blen ) );
            break;
        default:
#if defined(MBEDTLS_ECP_RESTARTABLE)
            if( rs_ctx != NULL && rs_ctx->sig != NULL )
            {
                /* redirect to our context */
                p_sign_tries = &rs_ctx->sig->sign_tries;
                p_key_tries = &rs_ctx->sig->key_tries;
                pk = &rs_ctx->sig->k;
                pr = &rs_ctx->sig->r;

                /* jump to current step */
                if( rs_ctx->sig->state == ecdsa_sig_mul )
                    goto mul;
                if( rs_ctx->sig->state == ecdsa_sig_modn )
                    goto modn;
            }
#endif /* MBEDTLS_ECP_RESTARTABLE */

            *p_sign_tries = 0;
            do
            {
                if( (*p_sign_tries)++ > 10 )
                {
                    ret = MBEDTLS_ERR_ECP_RANDOM_FAILED;
                    goto cleanup;
                }

                /*
                * Steps 1-3: generate a suitable ephemeral keypair
                * and set r = xR mod n
                */
                *p_key_tries = 0;
                do
                {
                    if( (*p_key_tries)++ > 10 )
                    {
                        ret = MBEDTLS_ERR_ECP_RANDOM_FAILED;
                        goto cleanup;
                    }

                    MBEDTLS_MPI_CHK( mbedtls_ecp_gen_privkey( grp, pk, f_rng, p_rng ) );

#if defined(MBEDTLS_ECP_RESTARTABLE)
                    if( rs_ctx != NULL && rs_ctx->sig != NULL )
                        rs_ctx->sig->state = ecdsa_sig_mul;

mul:
#endif
                    MBEDTLS_MPI_CHK( mbedtls_ecp_mul_restartable( grp, &R, pk, &grp->G,
                                                                f_rng_blind,
                                                                p_rng_blind,
                                                                ECDSA_RS_ECP ) );
                    MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( pr, &R.X, &grp->N ) );
                }
                while( mbedtls_mpi_cmp_int( pr, 0 ) == 0 );

#if defined(MBEDTLS_ECP_RESTARTABLE)
                if( rs_ctx != NULL && rs_ctx->sig != NULL )
                    rs_ctx->sig->state = ecdsa_sig_modn;

modn:
#endif
                /*
                * Accounting for everything up to the end of the loop
                * (step 6, but checking now avoids saving e and t)
                */
                ECDSA_BUDGET( MBEDTLS_ECP_OPS_INV + 4 );

                /*
                * Step 5: derive MPI from hashed message
                */
                MBEDTLS_MPI_CHK( derive_mpi( grp, &e, buf, blen ) );

                /*
                * Generate a random value to blind inv_mod in next step,
                * avoiding a potential timing leak.
                */
                MBEDTLS_MPI_CHK( mbedtls_ecp_gen_privkey( grp, &t, f_rng_blind,
                                                        p_rng_blind ) );

                /*
                * Step 6: compute s = (e + r * d) / k = t (e + rd) / (kt) mod n
                */
                MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( s, pr, d ) );
                MBEDTLS_MPI_CHK( mbedtls_mpi_add_mpi( &e, &e, s ) );
                MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( &e, &e, &t ) );
                MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( pk, pk, &t ) );
                MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( pk, pk, &grp->N ) );
                MBEDTLS_MPI_CHK( mbedtls_mpi_inv_mod( s, pk, &grp->N ) );
                MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( s, s, &e ) );
                MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( s, s, &grp->N ) );
            }
            while( mbedtls_mpi_cmp_int( s, 0 ) == 0 );

#if defined(MBEDTLS_ECP_RESTARTABLE)
            if( rs_ctx != NULL && rs_ctx->sig != NULL )
                mbedtls_mpi_copy( r, pr );
#endif
            break;
    }

cleanup:
    mbedtls_ecp_point_free( &R );
    mbedtls_mpi_free( &k ); mbedtls_mpi_free( &e ); mbedtls_mpi_free( &t );

    ECDSA_RS_LEAVE( sig );

    return( ret );
}

int mbedtls_ecdsa_can_do( mbedtls_ecp_group_id gid )
{
    switch( gid )
    {
#ifdef MBEDTLS_ECP_DP_CURVE25519_ENABLED
        case MBEDTLS_ECP_DP_CURVE25519: return 0;
#endif
#ifdef MBEDTLS_ECP_DP_CURVE448_ENABLED
        case MBEDTLS_ECP_DP_CURVE448: return 0;
#endif
    default: return 1;
    }
}

/*
 * Compute ECDSA signature of a hashed message
 */
int mbedtls_ecdsa_sign( mbedtls_ecp_group *grp, mbedtls_mpi *r, mbedtls_mpi *s,
                const mbedtls_mpi *d, const unsigned char *buf, size_t blen,
                int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    ECDSA_VALIDATE_RET( grp   != NULL );
    ECDSA_VALIDATE_RET( r     != NULL );
    ECDSA_VALIDATE_RET( s     != NULL );
    ECDSA_VALIDATE_RET( d     != NULL );
    ECDSA_VALIDATE_RET( f_rng != NULL );
    ECDSA_VALIDATE_RET( buf   != NULL || blen == 0 );

    /* Use the same RNG for both blinding and ephemeral key generation */
    return( ecdsa_sign_restartable( grp, r, s, d, buf, blen,
                                    f_rng, p_rng, f_rng, p_rng, NULL ) );
}
#endif /* MBEDTLS_ECDSA_SIGN_ALT */

#if defined(MBEDTLS_ECDSA_VERIFY_ALT)
static int hw_ecdsa_verify( mbedtls_ecp_group *grp,
                            const unsigned char *buf, size_t blen,
                            const mbedtls_ecp_point *Q,
                            const mbedtls_mpi *r, const mbedtls_mpi *s )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    uint32_t in_signiture_r[8] = {0};
    uint32_t in_signiture_s[8] = {0};
    uint8_t temp_buf[65] = {0};
    uint8_t public_key[64] = {0};
    uint32_t olen;
    algo_ecc_ecdsa_config_t ecc_ecdsa_ctx = {0};

    switch (grp->id)
    {
        case MBEDTLS_ECP_DP_SECP256R1:
            crypto_ecc_ecdsa_init(&ecc_ecdsa_ctx, ECC_CURVE_SECP256R1);
            break;
        case MBEDTLS_ECP_DP_SECP256K1:
            crypto_ecc_ecdsa_init(&ecc_ecdsa_ctx, ECC_CURVE_SECP256K1);
            break;
        default:
            ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
            goto cleanup;
    }

    mbedtls_ecp_point_write_binary( grp, Q, MBEDTLS_ECP_PF_UNCOMPRESSED, &olen, temp_buf, sizeof(temp_buf) );
    memcpy(public_key, temp_buf + 1, 64);
    SWAP_ENDIAN_32_ARRAY((uint32_t *)public_key, 16);
    memcpy(&(ecc_ecdsa_ctx.our_public_point), public_key, 64);

    mbedtls_mpi_write_binary(r, (uint8_t *)in_signiture_r, 32);
    mbedtls_mpi_write_binary(s, (uint8_t *)in_signiture_s, 32);
    SWAP_ENDIAN_32_ARRAY((uint32_t *)in_signiture_r, 8);
    SWAP_ENDIAN_32_ARRAY((uint32_t *)in_signiture_s, 8);

    ret = crypto_ecc_ecdsa_verify(&ecc_ecdsa_ctx, ECC_HASH_NONE, (uint8_t *)buf, blen, in_signiture_r, in_signiture_s);

cleanup:
    return( ret );
}

/*
 * Verify ECDSA signature of hashed message (SEC1 4.1.4)
 * Obviously, compared to SEC1 4.1.3, we skip step 2 (hash message)
 */
static int ecdsa_verify_restartable( mbedtls_ecp_group *grp,
                                     const unsigned char *buf, size_t blen,
                                     const mbedtls_ecp_point *Q,
                                     const mbedtls_mpi *r, const mbedtls_mpi *s,
                                     mbedtls_ecdsa_restart_ctx *rs_ctx )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    mbedtls_mpi e, s_inv, u1, u2;
    mbedtls_ecp_point R;
    mbedtls_mpi *pu1 = &u1, *pu2 = &u2;

    mbedtls_ecp_point_init( &R );
    mbedtls_mpi_init( &e ); mbedtls_mpi_init( &s_inv );
    mbedtls_mpi_init( &u1 ); mbedtls_mpi_init( &u2 );

    /* Fail cleanly on curves such as Curve25519 that can't be used for ECDSA */
    if( ! mbedtls_ecdsa_can_do( grp->id ) || grp->N.p == NULL )
        return( MBEDTLS_ERR_ECP_BAD_INPUT_DATA );

    ECDSA_RS_ENTER( ver );

    switch (grp->id)
    {
        case MBEDTLS_ECP_DP_SECP256R1:
        case MBEDTLS_ECP_DP_SECP256K1:
            MBEDTLS_MPI_CHK( hw_ecdsa_verify( grp, buf, blen, Q, r, s ) );
            break;
        default:
#if defined(MBEDTLS_ECP_RESTARTABLE)
            if( rs_ctx != NULL && rs_ctx->ver != NULL )
            {
                /* redirect to our context */
                pu1 = &rs_ctx->ver->u1;
                pu2 = &rs_ctx->ver->u2;

                /* jump to current step */
                if( rs_ctx->ver->state == ecdsa_ver_muladd )
                    goto muladd;
            }
#endif /* MBEDTLS_ECP_RESTARTABLE */

            /*
            * Step 1: make sure r and s are in range 1..n-1
            */
            if( mbedtls_mpi_cmp_int( r, 1 ) < 0 || mbedtls_mpi_cmp_mpi( r, &grp->N ) >= 0 ||
                mbedtls_mpi_cmp_int( s, 1 ) < 0 || mbedtls_mpi_cmp_mpi( s, &grp->N ) >= 0 )
            {
                ret = MBEDTLS_ERR_ECP_VERIFY_FAILED;
                goto cleanup;
            }

            /*
            * Step 3: derive MPI from hashed message
            */
            MBEDTLS_MPI_CHK( derive_mpi( grp, &e, buf, blen ) );

            /*
            * Step 4: u1 = e / s mod n, u2 = r / s mod n
            */
            ECDSA_BUDGET( MBEDTLS_ECP_OPS_CHK + MBEDTLS_ECP_OPS_INV + 2 );

            MBEDTLS_MPI_CHK( mbedtls_mpi_inv_mod( &s_inv, s, &grp->N ) );

            MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( pu1, &e, &s_inv ) );
            MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( pu1, pu1, &grp->N ) );

            MBEDTLS_MPI_CHK( mbedtls_mpi_mul_mpi( pu2, r, &s_inv ) );
            MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( pu2, pu2, &grp->N ) );

#if defined(MBEDTLS_ECP_RESTARTABLE)
            if( rs_ctx != NULL && rs_ctx->ver != NULL )
                rs_ctx->ver->state = ecdsa_ver_muladd;

muladd:
#endif
            /*
            * Step 5: R = u1 G + u2 Q
            */
            MBEDTLS_MPI_CHK( mbedtls_ecp_muladd_restartable( grp,
                            &R, pu1, &grp->G, pu2, Q, ECDSA_RS_ECP ) );

            if( mbedtls_ecp_is_zero( &R ) )
            {
                ret = MBEDTLS_ERR_ECP_VERIFY_FAILED;
                goto cleanup;
            }

            /*
            * Step 6: convert xR to an integer (no-op)
            * Step 7: reduce xR mod n (gives v)
            */
            MBEDTLS_MPI_CHK( mbedtls_mpi_mod_mpi( &R.X, &R.X, &grp->N ) );

            /*
            * Step 8: check if v (that is, R.X) is equal to r
            */
            if( mbedtls_mpi_cmp_mpi( &R.X, r ) != 0 )
            {
                ret = MBEDTLS_ERR_ECP_VERIFY_FAILED;
                goto cleanup;
            }
            break;
    }

cleanup:
    mbedtls_ecp_point_free( &R );
    mbedtls_mpi_free( &e ); mbedtls_mpi_free( &s_inv );
    mbedtls_mpi_free( &u1 ); mbedtls_mpi_free( &u2 );

    ECDSA_RS_LEAVE( ver );

    return( ret );
}

/*
 * Verify ECDSA signature of hashed message
 */
int mbedtls_ecdsa_verify( mbedtls_ecp_group *grp,
                          const unsigned char *buf, size_t blen,
                          const mbedtls_ecp_point *Q,
                          const mbedtls_mpi *r,
                          const mbedtls_mpi *s)
{
    ECDSA_VALIDATE_RET( grp != NULL );
    ECDSA_VALIDATE_RET( Q   != NULL );
    ECDSA_VALIDATE_RET( r   != NULL );
    ECDSA_VALIDATE_RET( s   != NULL );
    ECDSA_VALIDATE_RET( buf != NULL || blen == 0 );

    return( ecdsa_verify_restartable( grp, buf, blen, Q, r, s, NULL ) );
}
#endif /* MBEDTLS_ECDSA_VERIFY_ALT */

#if defined(MBEDTLS_ECDSA_GENKEY_ALT)
static int hw_ecdsa_gen_secret_and_public(mbedtls_ecp_group *grp, mbedtls_mpi *d, mbedtls_ecp_point *Q)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    uint8_t private_key[32] = {0};
    uint8_t public_key[65] = {0};
    uint8_t temp_buf[64] = {0};
    algo_ecc_ecdsa_config_t ecc_ecdsa_ctx = {0};

    switch (grp->id)
    {
        case MBEDTLS_ECP_DP_SECP256R1:
            crypto_ecc_ecdsa_init(&ecc_ecdsa_ctx, ECC_CURVE_SECP256R1);
            break;
        case MBEDTLS_ECP_DP_SECP256K1:
            crypto_ecc_ecdsa_init(&ecc_ecdsa_ctx, ECC_CURVE_SECP256K1);
            break;
        default:
            ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
            goto cleanup;
    }

    ret = crypto_ecc_ecdsa_gen_secret_and_public(&ecc_ecdsa_ctx);
    if (ret != 0)
    {
        goto cleanup;
    }

    memcpy(private_key, (uint8_t *)(ecc_ecdsa_ctx.our_secret_value), 32);
    SWAP_ENDIAN_32_ARRAY((uint32_t *)private_key, 8);
    mbedtls_mpi_read_binary(d, private_key, sizeof(private_key));

    memcpy(temp_buf, (uint8_t *)&(ecc_ecdsa_ctx.our_public_point), 64);
    SWAP_ENDIAN_32_ARRAY((uint32_t *)temp_buf, 16);
    public_key[0] = 0x04;
    memcpy(public_key + 1, temp_buf, 64);
    mbedtls_ecp_point_read_binary(grp, Q, public_key, sizeof(public_key));

cleanup:
    return( ret );
}

/*
 * Generate key pair
 */
int mbedtls_ecdsa_genkey( mbedtls_ecdsa_context *ctx, mbedtls_ecp_group_id gid,
                  int (*f_rng)(void *, unsigned char *, size_t), void *p_rng )
{
    int ret = 0;
    ECDSA_VALIDATE_RET( ctx   != NULL );
    ECDSA_VALIDATE_RET( f_rng != NULL );

    ret = mbedtls_ecp_group_load( &ctx->grp, gid );
    if( ret != 0 )
        return( ret );

    switch (gid)
    {
        case MBEDTLS_ECP_DP_SECP256R1:
        case MBEDTLS_ECP_DP_SECP256K1:
            MBEDTLS_MPI_CHK( hw_ecdsa_gen_secret_and_public( &ctx->grp, &ctx->d, &ctx->Q ) );
            break;
        default:
            MBEDTLS_MPI_CHK( mbedtls_ecp_gen_keypair( &ctx->grp, &ctx->d, &ctx->Q, f_rng, p_rng ) );
            break;
    }

cleanup:
    return( ret );
}
#endif /* MBEDTLS_ECDSA_GENKEY_ALT */

#endif /* MBEDTLS_ECC_ALT */

#endif /* MBEDTLS_ECDSA_C */
