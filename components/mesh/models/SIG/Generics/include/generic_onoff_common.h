/**
 *****************************************************************************************
 *
 * @file generic_onoff_common.h
 *
 * @brief Generic On Off Common Define.
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
#ifndef __GENERIC_ONOFF_COMMON_H__
#define __GENERIC_ONOFF_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** Generic On Off Server model max number */
#define GENERIC_ONOFF_SERVER_INSTANCE_COUNT_MAX              (16)
/** Generic On Off Client model max number */
#define GENERIC_ONOFF_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for Generic On Off Server */
#define GENERIC_ONOFF_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for Generic On Off Server publish Status message */
#define GENERIC_ONOFF_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for Generic On Off Server response Status message */
#define GENERIC_ONOFF_SERVER_RSP_SEND_TX_HDL                 (0x01)

/** The total number of transmit handle for Generic On Off Client */
#define GENERIC_ONOFF_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for Generic On Off Client Get message */
#define GENERIC_ONOFF_CLIENT_GET_SEND_TX_HDL                 (GENERIC_ONOFF_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + GENERIC_ONOFF_SERVER_TX_HDL_TOTAL * GENERIC_ONOFF_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Generic On Off Client Set message */
#define GENERIC_ONOFF_CLIENT_SET_SEND_TX_HDL                 (GENERIC_ONOFF_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for Generic On Off Client Set Unacknowledged message */
#define GENERIC_ONOFF_CLIENT_SET_UNRELIABLE_SEND_TX_HDL      (GENERIC_ONOFF_CLIENT_SET_SEND_TX_HDL + 1)

/** The reliable message timeout time */
#define GENERIC_ONOFF_RELIABLE_MSG_TIMEOUT_MS                (30000)

/** Maximum value of the onoff state, as defined in the Mesh Model Specification v1.0 */
#define GENERIC_ONOFF_MAX        (0x01)


/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Permanet parameters for the Generic On Off Set message. */
typedef struct
{
    bool on_off;                                            /**< State to set */
    uint8_t tid;                                            /**< Transaction ID */
} generic_onoff_set_params_t;

/** Parameters for the Generic OnOff Status message. */
typedef struct
{
    uint8_t present_on_off;                                 /**< The present value of the Generic OnOff state */
    uint8_t target_on_off;                                  /**< The target value of the Generic OnOff state (optional) */
    uint32_t remaining_time_ms;                             /**< Remaining time value in milliseconds */
} generic_onoff_status_params_t;

#endif /* __GENERIC_ONOFF_COMMON_H__ */

/** @} */

