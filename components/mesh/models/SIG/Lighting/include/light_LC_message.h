/**
 *****************************************************************************************
 *
 * @file light_lc_message.h
 *
 * @brief Light LC Define.
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
#ifndef __LIGHT_LC_MESSAGE_H__
#define __LIGHT_LC_MESSAGE_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** The allowed shortest length for the LC Mode Set message. */
#define LIGHT_LC_MODE_SET_MINLEN 1
/** The allowed shortest length for the LC Mode  Get message. */
#define LIGHT_LC_MODE_GET_MINLEN 0
/** The allowed shortest length for the LC Mode  Status message. */
#define LIGHT_LC_MODE_STATUS_MINLEN 1
/** The allowed shortest length for the LC Occupancy Mode Set message. */
#define LIGHT_LC_OM_SET_MINLEN 1
/** The allowed shortest length for the LC Occupancy Mode  Get message. */
#define LIGHT_LC_OM_GET_MINLEN 0
/** The allowed shortest length for the LC Occupancy Mode Status message. */
#define LIGHT_LC_OM_STATUS_MINLEN 1
/** The allowed shortest length for the LC Light Onoff Set message. */
#define LIGHT_LC_LOO_SET_MINLEN 2
/** The allowed longest length for the LC Light Onoff Set message. */
#define LIGHT_LC_LOO_SET_MAXLEN 4
/** The allowed shortest length for the LC Light Onoff Get message. */
#define LIGHT_LC_LOO_GET_MINLEN 0
/** The allowed shortest length for the LC Light Onoff STATUS message. */
#define LIGHT_LC_LOO_STATUS_MINLEN 1
/** The allowed longest length for the LC Light Onoff STATUS message. */
#define LIGHT_LC_LOO_STATUS_MAXLEN 3

#define LIGHT_LC_PROPERTY_GET_MINLEN 2


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Light Lightness  model message opcodes. */
typedef enum
{
    LIGHT_LC_MODE_OPCODE_GET = 0x8291,                                                        /** Message opcode for the Light LC Model Get message. */
    LIGHT_LC_MODE_OPCODE_SET = 0x8292,                                                        /** Message opcode for the Light LC Model  Set message. */
    LIGHT_LC_MODE_OPCODE_SET_UNACKNOWLEDGED = 0x8293,                       /** Message opcode for the Light LC Model  Set Unacknowledged message. */
    LIGHT_LC_MODE_OPCODE_STATUS = 0x8294,                                                 /** Message opcode for the Light LC Model  Status message. */
    LIGHT_LC_OM_OPCODE_GET = 0x8295,                                         /** Message opcode for the Light  LC Occupancy Mode Get message. */
    LIGHT_LC_OM_OPCODE_SET = 0x8296,                                         /** Message opcode for the Light  LC Occupancy Mode Set message. */
    LIGHT_LC_OM_OPCODE_SET_UNACKNOWLEDGED = 0x8297,        /** Message opcode for the Light  LC Occupancy Mode Set Unacknowledged message. */
    LIGHT_LC_OM_OPCODE_STATUS = 0x8298,                                  /** Message opcode for the Light  LC Occupancy Mode Status message. */
    LIGHT_LC_LOO_OPCODE_GET = 0x8299,                                         /** Message opcode for the Light LC Light OnOff Get message. */
    LIGHT_LC_LOO_OPCODE_SET = 0x829A,                                         /** Message opcode for the Light LC Light OnOff Set message. */
    LIGHT_LC_LOO_OPCODE_SET_UNACKNOWLEDGED = 0x829B,        /** Message opcode for the Light LC Light OnOff Set Unacknowledged message. */
    LIGHT_LC_LOO_OPCODE_STATUS = 0x829C,                                  /** Message opcode for the Light LC Light OnOff Status message. */
    LIGHT_LC_SENSOR_OPCODE_STATUS = 0x52
} light_LC_opcode_t;

/** Light Lightness  model message opcodes. */
typedef enum
{
    LIGHT_LC_PROPERTY_OPCODE_GET = 0x829D,                                     /** Message opcode for the Light Lightness  Linear Get message. */
    LIGHT_LC_PROPERTY_OPCODE_SET = 0x62,                                         /** Message opcode for the Light Lightness  Linear Set message. */
    LIGHT_LC_PROPERTY_OPCODE_SET_UNACKNOWLEDGED = 0x63,        /** Message opcode for the Light Lightness  Linear Set Unacknowledged message. */
    LIGHT_LC_PROPERTY_OPCODE_STATUS = 0x64,                                  /** Message opcode for the Light Lightness  Linear Status message. */
} light_LC_setup_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Light LC Mode Set message. */
typedef struct __attribute((packed))
{
    uint8_t mode;                                            /**< The target value of the Light LC Mode state*/
} light_lc_mode_set_msg_pkt_t;

/** Message format for the Light LC Mode state message. */
typedef struct __attribute((packed))
{
    uint8_t mode;                                            /**< The present value of the Light LC Mode state*/
} light_lc_mode_status_msg_pkt_t;

/** Message format for the Light LC OM Set message. */
typedef struct __attribute((packed))
{
    uint8_t mode;                                            /**< The target value of the Light LC Occupancy Mode state*/
} light_lc_om_set_msg_pkt_t;

/** Message format for the Light LC Occupancy Mode state message. */
typedef struct __attribute((packed))
{
    uint8_t mode;                                            /**< The present value of the Light LC Occupancy Mode state*/
} light_lc_om_status_msg_pkt_t;

/** Message format for the Light LC Light OnOff Set message. */
typedef struct __attribute((packed))
{
    uint8_t loo;                                            /**< The target value of the Light LC Light OnOff state */
    uint8_t tid;                                             /**< Transaction number for application */
    uint8_t transition_time;                        /**< Encoded transition time value */
    uint8_t delay;                                        /**< Encoded message execution delay in 5 millisecond steps */
} light_lc_loo_set_msg_pkt_t;

/** Message format for the Light LC Light OnOff Status message. */
typedef struct __attribute((packed))
{
    uint8_t present_loo;                                 /**< The present value of the Light LC Light OnOff state */
    uint8_t target_loo;                                    /**< The target value of the Light LC Light OnOff state (optional) */
    uint8_t remaining_time;                           /**< Encoded remaining time */
} light_lc_loo_status_msg_pkt_t;

/** Message format for the Light LC Property Get message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                            /**< Property ID identifying a Light LC Property.*/
} light_lc_property_get_msg_pkt_t;

/** Message format for the Light LC Property Set message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                            /**< Property ID identifying a Light LC Property.*/
    uint8_t property_value[];                                      /**< Raw value for the Light LC Property.*/
} light_lc_property_set_msg_pkt_t;

/** Message format for the Light LC Property state message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                            /**< Property ID identifying a Light LC Property.*/
    uint8_t property_value[];                                      /**< Raw value for the Light LC Property.*/
} light_lc_property_status_msg_pkt_t;

/** Message format for the Mesh Sensor Status message. */
//typedef struct __attribute((packed))
//{
    //uint8_t sensor_data[];                                 /**< The Sensor Data state */
//} sensor_status_msg_pkt_t;

#endif /* __LIGHT_LC_MESSAGE_H__ */

/** @} */

