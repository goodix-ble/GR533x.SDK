/**
 *****************************************************************************************
 *
 * @file generic_battery_common.h
 *
 * @brief Generic Battery Common Define.
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
#ifndef __GENERIC_BATTERY_COMMON_H__
#define __GENERIC_BATTERY_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** Generic Battery Server model max number */
#define GENERIC_BATTERY_SERVER_INSTANCE_COUNT_MAX              (16)
/** Generic Battery Client model max number */
#define GENERIC_BATTERY_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for Generic Battery Server */
#define GENERIC_BATTERY_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for Generic Battery Server publish Status message */
#define GENERIC_BATTERY_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for Generic Battery Server response Status message */
#define GENERIC_BATTERY_SERVER_RSP_SEND_TX_HDL                 (0x01)

/** The total number of transmit handle for Generic Battery Client */
#define GENERIC_BATTERY_CLIENT_TX_HDL_TOTAL                    (1)
/** The transmit handle for Generic Battery Client Get message */
#define GENERIC_BATTERY_CLIENT_GET_SEND_TX_HDL                 (GENERIC_BATTERY_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + GENERIC_BATTERY_SERVER_TX_HDL_TOTAL * GENERIC_BATTERY_SERVER_INSTANCE_COUNT_MAX)

/** The reliable message timeout time */
#define GENERIC_BATTERY_RELIABLE_MSG_TIMEOUT_MS                (30000)


/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Parameters for the Generic battery Status message. */
typedef struct
{
    uint8_t battery_level;                         /**< Present level of the battery state.  from 0 percent through 100 percent.*/
    uint32_t time_to_discharge;              /**< The value of the Generic Battery Time to Discharge state. */
    uint32_t time_to_charge;                   /**<The value of the Generic Battery Time to Charge state. */
    uint8_t flags_presence;                     /**<Generic Battery Flags Presence.*/
    uint8_t flags_indicator;                     /**<Generic Battery Flags Indicator.*/
    uint8_t flags_charging;                     /**<Generic Battery Flags Charging.*/
    uint8_t flags_serviceability;             /**<Generic Battery Flags Serviceability.*/
} generic_battery_status_params_t;

#endif /* __GENERIC_BATTERY_COMMON_H__ */

/** @} */

