/**
 *****************************************************************************************
 *
 * @file light_lc_common.h
 *
 * @brief Light LC Common Define.
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
#ifndef __LIGHT_LC_COMMON_H__
#define __LIGHT_LC_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** Light LC Server model max number */
#define LIGHT_LC_SERVER_INSTANCE_COUNT_MAX              (16)
/** Light LC Client model max number */
#define LIGHT_LC_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for Light LC Server */
#define LIGHT_LC_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for Light LC Server publish Status message */
#define LIGHT_LC_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for Light LC Server response Status message */
#define LIGHT_LC_SERVER_RSP_SEND_TX_HDL                 (0x01)

/** The total number of transmit handle for Light LC Client */
#define LIGHT_LC_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for Light LC Client Get message */
#define LIGHT_LC_CLIENT_GET_SEND_TX_HDL                 (LIGHT_LC_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + LIGHT_LC_SERVER_TX_HDL_TOTAL * LIGHT_LC_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Light LC Client Set message */
#define LIGHT_LC_CLIENT_SET_SEND_TX_HDL                 (LIGHT_LC_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for Light LC Client Set Unacknowledged message */
#define LIGHT_LC_CLIENT_SET_UNRELIABLE_SEND_TX_HDL      (LIGHT_LC_CLIENT_SET_SEND_TX_HDL + 1)

/** The reliable message timeout time */
#define LIGHT_LC_RELIABLE_MSG_TIMEOUT_MS                (30000)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Permanet parameters for the Light LC Mode Set message. */
typedef struct
{
    uint8_t mode;                                            /**< The target value of the Light LC Mode state*/
} light_lc_mode_set_params_t;

/** Permanet parameters for the Light LC Occupancy Mode Set message. */
typedef struct
{
    uint8_t mode;                                            /**< The target value of the Light LC Occupancy Mode state*/
} light_lc_om_set_params_t;

/** Permanet parameters for the Light LC Light OnOff Set message. */
typedef struct
{
    uint8_t loo;                                            /**< The target value of the Light LC Light OnOff state */
    uint8_t tid;                                             /**< Transaction number for application */
} light_lc_loo_set_params_t;

/** Permanet parameters for the Light LC Property Get message. */
typedef struct
{
    uint16_t property_id;                                            /**< Property ID identifying a Light LC Property.*/
} light_lc_property_get_params_t;

/** Permanet parameters for the Light LC Property Set message. */
typedef struct
{
    uint16_t property_id;                                            /**< Property ID identifying a Light LC Property.*/
    uint16_t value_length;
    uint8_t *property_value;                                           /**< Raw value for the Light LC Property.*/
} light_lc_property_set_params_t;

/** Parameters for the Light LC Mode Status message. */
typedef struct
{
    uint8_t mode;                                            /**< The present value of the Light LC Mode state*/
} light_lc_mode_status_params_t;

/** Parameters for the Light LC Occupancy Mode Status message. */
typedef struct
{
    uint8_t mode;                                            /**< The present value of the Light LC Occupancy Mode state*/
} light_lc_om_status_params_t;

/** Parameters for the Light LC Light OnOff Status message. */
typedef struct
{
    uint8_t present_loo;                                 /**< The present value of the Light LC Light OnOff state */
    uint8_t target_loo;                                   /**< The target value of the Light LC Light OnOff state (optional) */
    uint32_t remaining_time_ms;                  /**< Remaining time value in milliseconds */
} light_lc_loo_status_params_t;

/** Parameters for the Light LC Property Status message. */
typedef struct
{
    uint16_t property_id;                                            /**< Property ID identifying a Light LC Property.*/
    uint16_t value_length;
    uint8_t *property_value;                                           /**< Raw value for the Light LC Property.*/
} light_lc_property_status_params_t;

/** Parameters for the Mesh Sensor Status message. */
typedef struct
{
    uint16_t property_id;
    uint16_t raw_value_length;
    uint8_t *raw_value;                                 /**< The Sensor Data state */
} sensor_status_params__t;

#endif /* __LIGHT_LC_COMMON_H__ */

/** @} */

