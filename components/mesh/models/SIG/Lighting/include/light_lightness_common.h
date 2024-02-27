/**
 *****************************************************************************************
 *
 * @file light_lightness_common.h
 *
 * @brief Light Lightness Common Define.
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
#ifndef __LIGHT_LIGHTNESS_COMMON_H__
#define __LIGHT_LIGHTNESS_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** Light Lightness Server model max number */
#define LIGHT_LIGHTNESS_SERVER_INSTANCE_COUNT_MAX              (16)
/** Light Lightness Client model max number */
#define LIGHT_LIGHTNESS_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for Light Lightness Server */
#define LIGHT_LIGHTNESS_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for Light Lightness Server publish Status message */
#define LIGHT_LIGHTNESS_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for Light Lightness Server response Status message */
#define LIGHT_LIGHTNESS_SERVER_RSP_SEND_TX_HDL                 (0x01)

/** The total number of transmit handle for Light Lightness Client */
#define LIGHT_LIGHTNESS_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for Light Lightness Client Get message */
#define LIGHT_LIGHTNESS_CLIENT_GET_SEND_TX_HDL                 (LIGHT_LIGHTNESS_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + LIGHT_LIGHTNESS_SERVER_TX_HDL_TOTAL * LIGHT_LIGHTNESS_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Light Lightness Client Set message */
#define LIGHT_LIGHTNESS_CLIENT_SET_SEND_TX_HDL                 (LIGHT_LIGHTNESS_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for Light Lightness Client Set Unacknowledged message */
#define LIGHT_LIGHTNESS_CLIENT_SET_UNRELIABLE_SEND_TX_HDL      (LIGHT_LIGHTNESS_CLIENT_SET_SEND_TX_HDL + 1)

/** The reliable message timeout time */
#define LIGHT_LIGHTNESS_RELIABLE_MSG_TIMEOUT_MS                (30000)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Permanet parameters for the Light Lightness Set message. */
typedef struct
{
    uint16_t ln;                                            /**< State to set */
    uint8_t tid;                                            /**< Transaction ID */
} light_ln_set_params_t;

/** Permanet parameters for the Light Lightness Default Set message. */
typedef struct
{
    uint16_t ln;                                            /**< State to set */
} light_ln_set_dft_params_t;

/** Permanet parameters for the Light Lightness Range Set message. */
typedef struct
{
    uint16_t ln_min;                                            /**< State to set */
    uint16_t ln_max;                                            /**< State to set */
} light_ln_set_range_params_t;

typedef union
{
    struct {
        uint16_t ln_min;                                            /**< State to set */
        uint16_t ln_max;                                            /**< State to set */
    }u;
    uint16_t ln;                                            /**< State to set */
} light_ln_setup_params_t;

/** Parameters for the Light Lightness Status message. */
typedef struct
{
    uint16_t present_ln;                                 /**< The present value of the Light Lightness state */
    uint16_t target_ln;                                  /**< The target value of the Light Lightness state (optional) */
    uint32_t remaining_time_ms;                             /**< Remaining time value in milliseconds */
} light_ln_status_params_t;

typedef struct
{
    uint16_t ln;                                 /**< The present value of the Light Lightness state */
} light_ln_dft_status_params_t;

typedef struct
{
    uint16_t ln;                                 /**< The present value of the Light Lightness state */
} light_ln_last_status_params_t;

typedef struct
{
    uint8_t status_code;
    uint16_t min_ln;                                 /**< The min value of the Light Lightness state */
    uint16_t max_ln;                                /**< The max value of the Light Lightness state */
} light_ln_range_status_params_t;

typedef union
{
    light_ln_status_params_t ln;
    light_ln_dft_status_params_t ln_dft;
    light_ln_last_status_params_t ln_last;
    light_ln_range_status_params_t ln_range;
}light_ln_status_params_u;

#endif /* __LIGHT_LIGHTNESS_COMMON_H__ */

/** @} */

