/**
 *****************************************************************************************
 *
 * @file light_ctl_common.h
 *
 * @brief Light CTL Common Define.
 *
 *****************************************************************************************
 * @attention
  #####Copyright (c) 2019 GOODIX
  All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of GOODIX nor the names of its contributors may be used
    to endorse or promote products derived from this software without
    specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************************
 */

 /**
 * @addtogroup MESH
 * @{
 */
#ifndef __LIGHT_CTL_COMMON_H__
#define __LIGHT_CTL_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** Light CTL Server model max number */
#define LIGHT_CTL_SERVER_INSTANCE_COUNT_MAX              (16)
/** Light CTL Client model max number */
#define LIGHT_CTL_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for Light CTL Server */
#define LIGHT_CTL_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for Light CTL Server publish Status message */
#define LIGHT_CTL_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for Light CTL Server response Status message */
#define LIGHT_CTL_SERVER_RSP_SEND_TX_HDL                 (0x01)

/** The total number of transmit handle for Light CTL Client */
#define LIGHT_CTL_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for Light CTL Client Get message */
#define LIGHT_CTL_CLIENT_GET_SEND_TX_HDL                 (LIGHT_CTL_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + LIGHT_CTL_SERVER_TX_HDL_TOTAL * LIGHT_CTL_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Light CTL Client Set message */
#define LIGHT_CTL_CLIENT_SET_SEND_TX_HDL                 (LIGHT_CTL_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for Light CTL Client Set Unacknowledged message */
#define LIGHT_CTL_CLIENT_SET_UNRELIABLE_SEND_TX_HDL      (LIGHT_CTL_CLIENT_SET_SEND_TX_HDL + 1)

/** The reliable message timeout time */
#define LIGHT_CTL_RELIABLE_MSG_TIMEOUT_MS                (30000)

#define LIGHT_CTL_TEMPERATURE_MIN (0x0320)                /**< The color temperature of white light in Kelvin, 800 Kelvin ~20000 Kelvin*/
#define LIGHT_CTL_TEMPERATURE_MAX (0x4e20)               /**< The color temperature of white light in Kelvin, 800 Kelvin ~20000 Kelvin*/
#define LIGHT_CTL_TEMPERATURE_UNKNOW (0xFFFF)        /**< The color temperature of white light is unknown*/
#define LIGHT_CTL_DELTA_UV_ZERO (0x0000)                    /**< A value of 0x0000 represents the Delta UV = 0 of a tunable white light*/
#define LIGHT_CTL_LIGHTNESS_NO_EMIT (0x0000)            /**< Light is not emitted by the element*/
#define LIGHT_CTL_LIGHTNESS_HIGHEST_EMIT (0xFFFF)  /**< The highest perceived lightness of a light emitted by the element*/

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Permanet parameters for the Light CTL Set message. */
typedef struct
{
    uint16_t ctl_ln;                                         /**< The target value of the Light CTL Lightness state */
    uint16_t ctl_temp;                                    /**< The target value of the Light CTL Temperature state */
    int16_t ctl_dlt_uv;                                 /**< The target value of the Light CTL Delta UV state */
    uint8_t tid;                                               /**< Transaction number for application */
} light_ctl_set_params_t;

typedef struct
{
    uint16_t ctl_temp;                                    /**< The target value of the Light CTL Temperature state */
    int16_t ctl_dlt_uv;                                 /**< The target value of the Light CTL Delta UV state */
    uint8_t tid;                                               /**< Transaction number for application */
} light_ctl_temp_set_params_t;

typedef struct
{
    uint16_t ln;                                         /**< The value of the Light Lightness Default state */
    uint16_t temp;                                   /**< The value of the Light CTL Temperature Default state */
    int16_t dlt_uv;                                 /**< The value of the Light CTL Delta UV Default state */
} light_ctl_dft_set_params_t;

typedef struct
{
    uint16_t range_min;                                         /**< The value of the Temperature Range Min field of the Light CTL Temperature Range state */
    uint16_t range_max;                                         /**< The value of the Temperature Range Max field of the Light CTL Temperature Range state */
} light_ctl_set_range_params_t;

/** Message format for the Light CTL Status message. */
typedef struct
{
    uint16_t present_ctl_ln;                                 /**< The present value of the Light CTL Lightness state */
    uint16_t present_ctl_temp;                           /**< The present value of the Light CTL Temperature state */
    uint16_t target_ctl_ln;                                  /**< The target value of the Light CTL Lightness state (optional) */
    uint16_t target_ctl_temp;                             /**< The target value of the Light CTL Temperature state (optional) */
    uint32_t remaining_time_ms;                               /**< Remaining time value in milliseconds */
} light_ctl_status_params_t;

typedef struct
{
    uint16_t present_ctl_temp;                           /**< The present value of the Light CTL Temperature state */
    int16_t present_ctl_dlt_uv;                                 /**< The present value of the Light CTL Lightness state */
    uint16_t target_ctl_temp;                             /**< The target value of the Light CTL Temperature state (optional) */
    int16_t target_ctl_dlt_uv;                                  /**< The target value of the Light CTL Lightness state (optional) */
    uint32_t remaining_time_ms;                               /**< Remaining time value in milliseconds */
} light_ctl_temp_status_params_t;

typedef struct
{
    uint16_t ln;                                         /**< The value of the Light Lightness Default state */
    uint16_t temp;                                   /**< The value of the Light CTL Temperature Default state */
    int16_t dlt_uv;                                 /**< The value of the Light CTL Delta UV Default state */
} light_ctl_dft_status_params_t;

typedef struct
{
    uint8_t status_code;                                            /**<Status Code for the requesting message */
    uint16_t range_min;                                         /**< The value of the Temperature Range Min field of the Light CTL Temperature Range state */
    uint16_t range_max;                                         /**< The value of the Temperature Range Max field of the Light CTL Temperature Range state */
} light_ctl_range_status_params_t;

/*
typedef union
{
    light_ctl_status_params_t ln;
    light_ctl_dft_status_params_t ln_dft;
    light_ctl_last_status_params_t ln_last;
    light_ctl_range_status_params_t ln_range;
}light_ctl_status_params_u;
*/
#endif /* __LIGHT_CTL_COMMON_H__ */

/** @} */

