#include "crypto_rsa_port.h"
#include "crypto_rsa.h"
#include "crypto_pkc.h"
#include "crypto_pkc_port.h"

uint32_t hw_rsa_rng32(void)
{
    uint32_t rng32;
    rng_handle_t g_rng_handle = {0};

    g_rng_handle.p_instance = RNG;
    g_rng_handle.init.seed_mode  = RNG_SEED_FR0_S0;
    g_rng_handle.init.lfsr_mode  = RNG_LFSR_MODE_59BIT;
    g_rng_handle.init.out_mode   = RNG_OUTPUT_FR0_S0;
    g_rng_handle.init.post_mode  = RNG_POST_PRO_NEUMANN;

    hal_rng_init(&g_rng_handle);
    hal_rng_generate_random_number(&g_rng_handle, NULL, &rng32);
    hal_rng_deinit(&g_rng_handle);

    return rng32;
}

void hw_rsa_sha(const uint8_t *message, uint32_t message_byte_length, uint8_t output[32])
{
    uint8_t buf[32] = {0};
    hmac_handle_t g_hmac_handle = {0};
    g_hmac_handle.p_instance       = HMAC;
    g_hmac_handle.init.mode        = HMAC_MODE_SHA;
    g_hmac_handle.init.p_user_hash = NULL;
    g_hmac_handle.init.dpa_mode    = DISABLE;

    hal_hmac_init(&g_hmac_handle);
    hal_hmac_sha256_digest(&g_hmac_handle, (uint32_t *)message, message_byte_length, (uint32_t *)buf, 1000);
    hal_hmac_deinit(&g_hmac_handle);

    memcpy(output, buf, 32);
}

void hw_rsa_modular_left_shift(algo_rsa_config_t *rsa_calc_options,
                               uint32_t bits_len,
                               uint32_t in_a[],
                               uint32_t in_prime[],
                               uint32_t shift_bits,
                               uint32_t result[])
{
    hal_pkc_modular_left_shift_handle(bits_len, in_a, in_prime, shift_bits, result);
}

void hw_rsa_modular_compare(algo_rsa_config_t *rsa_calc_options,
                            uint32_t bits_len,
                            uint32_t in_a[],
                            uint32_t in_prime[],
                            uint32_t result[])
{
    hal_pkc_modular_compare_handle(bits_len, in_a, in_prime, result);
}

void hw_rsa_montgomery_inverse(algo_rsa_config_t *rsa_calc_options,
                               uint32_t bits_len,
                               uint32_t in_a[],
                               uint32_t in_prime[],
                               uint32_t constp,
                               uint32_t out_x[])
{
    hal_pkc_montgomery_inversion_handle(bits_len, in_a, in_prime, constp, out_x);
}

void rsa_modular_inverse(algo_rsa_config_t *ecc_config,
                         uint32_t bits_len,
                         uint32_t in_a[],
                         uint32_t in_prime[],
                         uint32_t r_square[],
                         uint32_t constq,
                         uint32_t out_a_inverse[])
{
    // check if input a = 0
    if (pkc_number_compare_to_const(in_a, 0, bits_len) == 0)
    {
        return;
    }

    hw_rsa_montgomery_inverse(ecc_config, bits_len, in_a, in_prime, constq, out_a_inverse);
}

void hw_rsa_modular_exponent(algo_rsa_config_t *rsa_calc_options,
                             uint32_t bits_len,
                             uint32_t in_a[],
                             uint32_t in_b[],
                             uint32_t in_prime[],
                             uint32_t r_square[],
                             uint32_t constq,
                             uint32_t result[])
{
    hal_pkc_rsa_modular_exponent_handle(bits_len, in_a, in_b, in_prime, r_square, constq, result);
}

//out_result in_a ^(in_b) mod in_prime
void rsa_modular_exponent(algo_rsa_config_t *rsa_config,
                          uint32_t bits_len,
                          uint32_t in_a[],
                          uint32_t in_d[],
                          uint32_t in_prime[],
                          uint32_t r_square[],
                          uint32_t constp,
                          uint32_t out_result[])
{
    hw_rsa_modular_exponent(rsa_config, bits_len, in_a, in_d, in_prime, r_square, constp, out_result);
}

void hw_rsa_montgomery_mul(algo_rsa_config_t *rsa_calc_options,
                           uint32_t bits_len,
                           uint32_t in_a[],
                           uint32_t in_b[],
                           uint32_t in_prime[],
                           uint32_t constp,
                           uint32_t result[])
{
    hal_pkc_montgomery_multi_handle(bits_len, in_a, in_b, in_prime, constp, result);
}

int rsa_safer_memcmp( const void *a, const void *b, size_t n )
{
    size_t i;
    const unsigned char *A = (const unsigned char *) a;
    const unsigned char *B = (const unsigned char *) b;
    unsigned char diff = 0;

    for( i = 0; i < n; i++ )
        diff |= A[i] ^ B[i];

    return( diff );
}
