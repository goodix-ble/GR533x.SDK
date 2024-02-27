/**
 *****************************************************************************************
 *
 * @file generic_power_level_common.h
 *
 * @brief Generic Power Level Common Define.
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
#ifndef __GENERIC_POWER_LEVEL_COMMON_H__
#define __GENERIC_POWER_LEVEL_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** Generic Power Level Server model max number */
#define GENERIC_POWER_LEVEL_SERVER_INSTANCE_COUNT_MAX              (16)
/** Generic Power Level Client model max number */
#define GENERIC_POWER_LEVEL_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for Generic Power Level Server */
#define GENERIC_POWER_LEVEL_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for Generic Power Level Server publish Status message */
#define GENERIC_POWER_LEVEL_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for Generic Power Level Server response Status message */
#define GENERIC_POWER_LEVEL_SERVER_RSP_SEND_TX_HDL                 (0x01)

/** The total number of transmit handle for Generic Power Level Client */
#define GENERIC_POWER_LEVEL_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for Generic Power Level Client Get message */
#define GENERIC_POWER_LEVEL_CLIENT_GET_SEND_TX_HDL                 (GENERIC_POWER_LEVEL_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + GENERIC_POWER_LEVEL_SERVER_TX_HDL_TOTAL * GENERIC_POWER_LEVEL_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Generic Power Level Client Set message */
#define GENERIC_POWER_LEVEL_CLIENT_SET_SEND_TX_HDL                 (GENERIC_POWER_LEVEL_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for Generic Power Level Client Set Unacknowledged message */
#define GENERIC_POWER_LEVEL_CLIENT_SET_UNRELIABLE_SEND_TX_HDL      (GENERIC_POWER_LEVEL_CLIENT_SET_SEND_TX_HDL + 1)

/** The reliable message timeout time */
#define GENERIC_POWER_LEVEL_RELIABLE_MSG_TIMEOUT_MS                (30000)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Permanet parameters for the Generic Power Level Set message. */
typedef struct
{
    uint16_t power;                                            /**< State to set */
    uint8_t tid;                                            /**< Transaction ID */
} generic_power_level_set_params_t;

/** Permanet parameters for the Generic Power Level Default Set message. */
typedef struct
{
    uint16_t power;                                            /**< State to set */
} generic_power_level_set_dft_params_t;

/** Permanet parameters for the Generic Power Level Range Set message. */
typedef struct
{
    uint16_t power_min;                                            /**< State to set */
    uint16_t power_max;                                            /**< State to set */
} generic_power_level_set_range_params_t;

typedef union
{
    struct {
        uint16_t power_min;                                            /**< State to set */
        uint16_t power_max;                                            /**< State to set */
    }u;
    uint16_t power;                                            /**< State to set */
} generic_power_level_setup_params_t;

/** Parameters for the Generic Power Level Status message. */
typedef struct
{
    uint16_t present_power;                                 /**< The present value of the Generic Power Level state */
    uint16_t target_power;                                  /**< The target value of the Generic Power Level state (optional) */
    uint32_t remaining_time_ms;                             /**< Remaining time value in milliseconds */
} generic_power_level_status_params_t;

typedef struct
{
    uint16_t power;                                 /**< The present value of the Generic Power Level state */
} generic_power_level_dft_status_params_t;

typedef struct
{
    uint16_t power;                                 /**< The present value of the Generic Power Level state */
} generic_power_level_last_status_params_t;

typedef struct
{
    uint8_t status_code;
    uint16_t min_power;                                 /**< The min value of the Generic Power Level state */
    uint16_t max_power;                                /**< The max value of the Generic Power Level state */
} generic_power_level_range_status_params_t;

typedef union
{
    generic_power_level_status_params_t power;
    generic_power_level_dft_status_params_t power_dft;
    generic_power_level_last_status_params_t power_last;
    generic_power_level_range_status_params_t power_range;
}generic_power_level_status_params_u;

#endif /* __GENERIC_POWER_LEVEL_COMMON_H__ */

/** @} */

