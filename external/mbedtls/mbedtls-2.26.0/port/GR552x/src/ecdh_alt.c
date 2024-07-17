/*
 *  Elliptic curve Diffie-Hellman
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
 * RFC 4492
 */

#include "common.h"

#if defined(MBEDTLS_ECDH_C)

#include "mbedtls/ecdh.h"
#include "mbedtls/platform_util.h"
#include "mbedtls/error.h"

#include <string.h>

/* Parameter validation macros based on platform_util.h */
#define ECDH_VALIDATE_RET( cond )    \
    MBEDTLS_INTERNAL_VALIDATE_RET( cond, MBEDTLS_ERR_ECP_BAD_INPUT_DATA )
#define ECDH_VALIDATE( cond )        \
    MBEDTLS_INTERNAL_VALIDATE( cond )

#if defined(MBEDTLS_ECC_ALT)
#include "crypto_ecc.h"

#define SWAP_ENDIAN_32_ARRAY(arr, size) \
do { \
    for(uint32_t i = 0; i < (size); i++) { \
        (arr)[i] = ( ((arr)[i] >> 24) | (((arr)[i] & 0x00FF0000) >> 8) | (((arr)[i] & 0x0000FF00) << 8) | ((arr)[i] << 24) ); \
    } \
} while(0)

#if defined(MBEDTLS_ECDH_GEN_PUBLIC_ALT)
static int hw_ecdh_gen_secret_and_public(mbedtls_ecp_group *grp, mbedtls_mpi *d, mbedtls_ecp_point *Q)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    uint8_t private_key[32] = {0};
    uint8_t public_key[65] = {0};
    uint8_t temp_buf[64] = {0};
    algo_ecc_ecdh_config_t ecdh_data = {0};

    switch (grp->id)
    {
        case MBEDTLS_ECP_DP_SECP256R1:
            crypto_ecc_ecdh_init(&ecdh_data, ECC_CURVE_SECP256R1);
            break;
        case MBEDTLS_ECP_DP_SECP256K1:
            crypto_ecc_ecdh_init(&ecdh_data, ECC_CURVE_SECP256K1);
            break;
        default:
            ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
            goto cleanup;
    }

    ret = crypto_ecc_ecdh_gen_secret_and_public(&ecdh_data);
    if (ret != 0)
    {
        goto cleanup;
    }

    memcpy(private_key, (uint8_t *)(ecdh_data.our_secret_value), 32);
    SWAP_ENDIAN_32_ARRAY((uint32_t *)private_key, 8);
    mbedtls_mpi_read_binary(d, private_key, sizeof(private_key));

    memcpy(temp_buf, (uint8_t *)&(ecdh_data.our_public_point), 64);
    SWAP_ENDIAN_32_ARRAY((uint32_t *)temp_buf, 16);
    public_key[0] = 0x04;
    memcpy(public_key + 1, temp_buf, 64);
    mbedtls_ecp_point_read_binary( grp, Q, public_key, sizeof(public_key) );

cleanup:
    return( ret );
}

/*
 * Generate public key (restartable version)
 *
 * Note: this internal function relies on its caller preserving the value of
 * the output parameter 'd' across continuation calls. This would not be
 * acceptable for a public function but is OK here as we control call sites.
 */
static int ecdh_gen_public_restartable( mbedtls_ecp_group *grp,
                    mbedtls_mpi *d, mbedtls_ecp_point *Q,
                    int (*f_rng)(void *, unsigned char *, size_t),
                    void *p_rng,
                    mbedtls_ecp_restart_ctx *rs_ctx )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;

    /* If multiplication is in progress, we already generated a privkey */
#if defined(MBEDTLS_ECP_RESTARTABLE)
    if( rs_ctx == NULL || rs_ctx->rsm == NULL )
#endif

    switch (grp->id)
    {
        case MBEDTLS_ECP_DP_SECP256R1:
        case MBEDTLS_ECP_DP_SECP256K1:
            MBEDTLS_MPI_CHK( hw_ecdh_gen_secret_and_public( grp, d, Q ) );
            break;
        default:
            MBEDTLS_MPI_CHK( mbedtls_ecp_gen_privkey( grp, d, f_rng, p_rng ) );
            MBEDTLS_MPI_CHK( mbedtls_ecp_mul_restartable( grp, Q, d, &grp->G,
                                                        f_rng, p_rng, rs_ctx ) );
            break;
    }

cleanup:
    return( ret );
}

/*
 * Generate public key
 */
int mbedtls_ecdh_gen_public( mbedtls_ecp_group *grp, mbedtls_mpi *d, mbedtls_ecp_point *Q,
                     int (*f_rng)(void *, unsigned char *, size_t),
                     void *p_rng )
{
    ECDH_VALIDATE_RET( grp != NULL );
    ECDH_VALIDATE_RET( d != NULL );
    ECDH_VALIDATE_RET( Q != NULL );
    ECDH_VALIDATE_RET( f_rng != NULL );
    return( ecdh_gen_public_restartable( grp, d, Q, f_rng, p_rng, NULL ) );
}
#endif /* MBEDTLS_ECDH_GEN_PUBLIC_ALT */

#if defined(MBEDTLS_ECDH_COMPUTE_SHARED_ALT)
static int hw_ecdh_compute_shared(mbedtls_ecp_group *grp, const mbedtls_mpi *d, const mbedtls_ecp_point *Q, mbedtls_mpi *z)
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    uint8_t private_key[32] = {0};
    uint8_t public_key[64] = {0};
    uint8_t share_key[32] = {0};
    uint8_t temp_buf[65] = {0};
    algo_ecc_ecdh_config_t ecdh_data = {0};
    uint32_t olen;

    switch (grp->id)
    {
        case MBEDTLS_ECP_DP_SECP256R1:
            crypto_ecc_ecdh_init(&ecdh_data, ECC_CURVE_SECP256R1);
            break;
        case MBEDTLS_ECP_DP_SECP256K1:
            crypto_ecc_ecdh_init(&ecdh_data, ECC_CURVE_SECP256K1);
            break;
        default:
            ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
            goto cleanup;
    }

    mbedtls_mpi_write_binary( d, private_key, 32 );
    mbedtls_ecp_point_write_binary( grp, Q, MBEDTLS_ECP_PF_UNCOMPRESSED, &olen, temp_buf, sizeof(temp_buf));
    memcpy(public_key, temp_buf + 1, 64);
    SWAP_ENDIAN_32_ARRAY((uint32_t *)private_key, 8);
    SWAP_ENDIAN_32_ARRAY((uint32_t *)public_key, 16);
    memcpy(ecdh_data.our_secret_value, private_key, 32);

    ret = crypto_ecc_ecdh_compute_shared(&ecdh_data, (algo_ecc_point_t *)public_key);
    if (ret != 0)
    {
        goto cleanup;
    }

    memcpy(share_key, (uint8_t *)(ecdh_data.shared_point.x), 32);
    SWAP_ENDIAN_32_ARRAY((uint32_t *)share_key, 8);
    mbedtls_mpi_read_binary(z, share_key, sizeof(share_key));

cleanup:
    return( ret );
}

/*
 * Compute shared secret (SEC1 3.3.1)
 */
static int ecdh_compute_shared_restartable( mbedtls_ecp_group *grp,
                         mbedtls_mpi *z,
                         const mbedtls_ecp_point *Q, const mbedtls_mpi *d,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng,
                         mbedtls_ecp_restart_ctx *rs_ctx )
{
    int ret = MBEDTLS_ERR_ERROR_CORRUPTION_DETECTED;
    mbedtls_ecp_point P;

    mbedtls_ecp_point_init( &P );

    switch (grp->id)
    {
        case MBEDTLS_ECP_DP_SECP256R1:
        case MBEDTLS_ECP_DP_SECP256K1:
            MBEDTLS_MPI_CHK( hw_ecdh_compute_shared( grp, d, Q, z ) );
            break;
        default:
            MBEDTLS_MPI_CHK( mbedtls_ecp_mul_restartable( grp, &P, d, Q,
                                                        f_rng, p_rng, rs_ctx ) );
            if( mbedtls_ecp_is_zero( &P ) )
            {
                ret = MBEDTLS_ERR_ECP_BAD_INPUT_DATA;
                goto cleanup;
            }
            MBEDTLS_MPI_CHK( mbedtls_mpi_copy( z, &P.X ) );
            break;
    }

cleanup:
    mbedtls_ecp_point_free( &P );

    return( ret );
}

/*
 * Compute shared secret (SEC1 3.3.1)
 */
int mbedtls_ecdh_compute_shared( mbedtls_ecp_group *grp, mbedtls_mpi *z,
                         const mbedtls_ecp_point *Q, const mbedtls_mpi *d,
                         int (*f_rng)(void *, unsigned char *, size_t),
                         void *p_rng )
{
    ECDH_VALIDATE_RET( grp != NULL );
    ECDH_VALIDATE_RET( Q != NULL );
    ECDH_VALIDATE_RET( d != NULL );
    ECDH_VALIDATE_RET( z != NULL );
    return( ecdh_compute_shared_restartable( grp, z, Q, d,
                                             f_rng, p_rng, NULL ) );
}
#endif /* MBEDTLS_ECDH_COMPUTE_SHARED_ALT */

#endif /* MBEDTLS_ECC_ALT */

#endif /* MBEDTLS_ECDH_C */
