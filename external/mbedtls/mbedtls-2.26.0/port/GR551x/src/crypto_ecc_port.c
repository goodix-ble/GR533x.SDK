#include "crypto_ecc_port.h"
#include "crypto_pkc.h"
#include "crypto_pkc_port.h"

uint32_t hw_ecc_rng32(void)
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

void hw_ecc_point_mul(algo_ecc_config_t *ecc_calc_options,
                      uint32_t k[ECC_U32_LENGTH],
                      algo_ecc_point_t *Q,
                      algo_ecc_point_t *result)
{
    ecc_curve_init_t *ecc_curve = (ecc_curve_init_t *)ecc_calc_options->curve;
    hal_set_curve(ecc_curve);
    hal_pkc_ecc_point_multi_handle(k, (ecc_point_t *)Q, (ecc_point_t *)result);
}

void hw_ecc_sha(const uint8_t *message, uint32_t message_byte_length, uint8_t output[32])
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

void hw_ecc_modular_compare(algo_ecc_config_t *ecc_calc_options,
                            uint32_t in_a[],
                            uint32_t in_prime[],
                            uint32_t result[])
{
    hal_pkc_modular_compare_handle(256, in_a, in_prime, result);
}

// modular inverse
// output is a^(-1)
void ecc_modular_inverse(
    algo_ecc_config_t *ecc_config, uint32_t in_a[], uint32_t in_prime[], uint32_t r_square[], uint32_t constq, uint32_t out_a_inverse[])
{
    // check if input a = 0
    if (pkc_number_compare_to_const(in_a, 0, 256) == 0)
    {
        return;
    }

    if ((in_prime[0] & 1) == 0)
    {
        return;
    }

    hw_ecc_montgomery_inverse(ecc_config, in_a, in_prime, constq, out_a_inverse);
}

void hw_ecc_montgomery_inverse(
    algo_ecc_config_t *ecc_calc_options, uint32_t in_a[], uint32_t in_prime[], uint32_t constp, uint32_t out_x[])
{
    hal_pkc_montgomery_inversion_handle(256, in_a, in_prime, constp, out_x);
}

void hw_ecc_modular_sub(
    algo_ecc_config_t *ecc_calc_options, uint32_t in_a[], uint32_t in_b[], uint32_t in_prime[], uint32_t result[])
{
    hal_pkc_modular_sub_handle(256, in_a, in_b, in_prime, result);
}

void hw_ecc_montgomery_mul(algo_ecc_config_t *ecc_calc_options,
                           uint32_t in_a[],
                           uint32_t in_b[],
                           uint32_t in_prime[],
                           uint32_t constp,
                           uint32_t result[])
{
    hal_pkc_montgomery_multi_handle(256, in_a, in_b, in_prime, constp, result);
}

void hw_ecc_modular_add(
    algo_ecc_config_t *ecc_calc_options, uint32_t in_a[], uint32_t in_b[], uint32_t in_prime[], uint32_t result[])
{
    hal_pkc_modular_add_handle(256, in_a, in_b, in_prime, result);
}

// c = a * b mod prime
void ecc_modular_multiply(algo_ecc_config_t *ecc_config,
                          uint32_t in_a[],
                          uint32_t in_b[],
                          uint32_t in_prime[],
                          uint32_t r_square[],
                          uint32_t constq,
                          uint32_t out_result[])
{
    uint32_t tmp[64] = { 0 };

    hw_ecc_montgomery_mul(ecc_config, in_a, in_b, in_prime, constq, tmp);
    hw_ecc_montgomery_mul(ecc_config, tmp, r_square, in_prime, constq, out_result);
}

/**
 *  \brief check if point is an infinite point
 *
 *  \param[in] point  input point.
 *
 *  \return
 *      \li 0  Not inifinte point
 *      \li 1  is infinite point
 */
uint32_t ecc_is_infinite_point(algo_ecc_point_t *point)
{

    uint32_t i = 0;

    if (NULL == point)
    {
        return (uint32_t)ECC_ERROR_PARAMETER;
    }

    for (i = 0; i < ECC_U32_LENGTH; i++)
    {

        if (point->x[i] != 0 || point->y[i] != 0)
        {
            return 0;
        }
    }

    return 1;
}
