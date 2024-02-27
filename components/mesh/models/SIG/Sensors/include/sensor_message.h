/**
 *****************************************************************************************
 *
 * @file sensor_message.h
 *
 * @brief Mesh Sensor Message Define.
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
#ifndef __MESH_SENSOR_MESSAGE_H__
#define __MESH_SENSOR_MESSAGE_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */
#define MESH_SENSOR_DESC_GET_MINLEN 0
#define MESH_SENSOR_DESC_GET_MAXLEN 2

#define MESH_SENSOR_DESC_STATUS_MINLEN 2

#define MESH_SENSOR_CADENCE_GET_MINLEN 2

#define MESH_SENSOR_SETTINGS_GET_MINLEN 2

#define MESH_SENSOR_SETTING_GET_MINLEN 4

#define MESH_SENSOR_SETTINGS_STATUS_MINLEN 2
#define MESH_SENSOR_SETTING_STATUS_MINLEN 4

#define MESH_SENSOR_GET_MINLEN 2


/** The allowed shortest length for the cadence Set message. */
#define MESH_SENSOR_CADENCE_SET_MINLEN 4
/** The allowed shortest length for the Set message. */
#define MESH_SENSOR_SETTING_SET_MINLEN 4

/** The allowed shortest length for the Status message. */
#define MESH_SENSOR_STATUS_MINLEN 1
/** The allowed longest length for the Status message. */
#define MESH_SENSOR_STATUS_MAXLEN 3

#define MESH_SENSOR_STATUS_FORMAT_A 0x0
#define MESH_SENSOR_STATUS_FORMAT_B 0x1

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Mesh Sensor model message opcodes. */
typedef enum
{
    MESH_SENSOR_DESCRIPTOR_OPCODE_GET = 0x8230,                  /** Message opcode for the Mesh Sensor Descriptor Get message. */
    MESH_SENSOR_DESCRIPTOR_OPCODE_STATUS = 0x51,               /** Message opcode for the Mesh Sensor Descriptor Status message. */
    MESH_SENSOR_OPCODE_GET = 0x8231,                                        /** Message opcode for the Mesh Sensor Get message. */
    MESH_SENSOR_OPCODE_STATUS = 0x52,                                     /** Message opcode for the Mesh Sensor Status message. */
    MESH_SENSOR_COLUMN_OPCODE_GET = 0x8232,                         /** Message opcode for the Mesh Sensor Column Get message. */
    MESH_SENSOR_COLUMN_OPCODE_STATUS = 0x53,                      /** Message opcode for the Mesh Sensor Column Status message. */
    MESH_SENSOR_SERIES_OPCODE_GET = 0x8233,                          /** Message opcode for the Mesh Sensor Series Get message. */
    MESH_SENSOR_SERIES_OPCODE_STATUS = 0x54,                        /** Message opcode for the Mesh Sensor Series Status message. */
} sensor_opcode_t;

typedef enum
{
    MESH_SENSOR_CADENCE_OPCODE_GET = 0x8234,                                /** Message opcode for the Mesh Sensor Cadence Get message. */
    MESH_SENSOR_CADENCE_OPCODE_SET = 0x55,                                    /** Message opcode for the Mesh Sensor Cadence Set message. */
    MESH_SENSOR_CADENCE_OPCODE_SET_UNACKNOWLEDGED = 0x56,   /** Message opcode for the Mesh Sensor Cadence Set Unacknowledge message. */
    MESH_SENSOR_CADENCE_OPCODE_STATUS  = 0x57,                            /** Message opcode for the Mesh Sensor Cadence Status message. */
    MESH_SENSOR_SETTINGS_OPCODE_GET = 0x8235,                               /** Message opcode for the Mesh Sensor Settings Get message. */
    MESH_SENSOR_SETTINGS_OPCODE_STATUS = 0x58,                            /** Message opcode for the Mesh Sensor Settings Status message. */
    MESH_SENSOR_SETTING_OPCODE_GET = 0x8236,                                 /** Message opcode for the Mesh Sensor Setting Get message. */
    MESH_SENSOR_SETTING_OPCODE_SET = 0x59,                                     /** Message opcode for the Mesh Sensor Setting Set message. */
    MESH_SENSOR_SETTING_OPCODE_SET_UNACKNOWLEDGED = 0x5A,    /** Message opcode for the Mesh Sensor Setting Set Unacknowledge  message. */
    MESH_SENSOR_SETTING_OPCODE_STATUS = 0x5B                               /** Message opcode for the Mesh Sensor Setting Status message. */
} sensor_setup_opcode_t;
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Mesh Sensor Descriptor Get message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                         /**< Property ID for the sensor (Optional) */
} sensor_descriptor_get_msg_pkt_t;

/** Message format for the Mesh Sensor Descriptor Status message. */
typedef struct __attribute((packed))
{
    uint16_t sensor_property_id;                        /**< Property ID for the sensor */
    uint16_t sensor_positive_tolerance;             /**< The Sensor Positive Tolerance field*/
    uint16_t sensor_negative_tolerance;            /**< The Sensor Negative Tolerance field*/
    uint8_t sensor_sampling_function;               /**< The Sensor Sampling Function field*/
    uint8_t sensor_measurement_period;          /**< The Sensor Measurement Period field*/
    uint8_t sensor_update_interval;                   /**< The Sensor Update Interval field */
} sensor_descriptor_status_pkt__t;

typedef struct __attribute((packed))
{
    uint64_t sensor_descriptor;                                 /**< The Sensor Descriptor state represents the attributes describing the sensor data */
} sensor_descriptor_status_msg_pkt_t;

/** Message format for the Mesh Cadence Get message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
} sensor_cadence_get_msg_pkt_t;

/** Message format for the Mesh Cadence Set message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint8_t sensor_cadence[];                                 /**< The Sensor Cadence state*/
} sensor_cadence_set_msg_pkt_t;

/** Message format for the Mesh Cadence Status message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint8_t sensor_cadence[];                                 /**< The Sensor Cadence state*/
} sensor_cadence_status_msg_pkt_t;

/** Message format for the Mesh Settings Get message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
} sensor_settings_get_msg_pkt_t;

/** Message format for the Mesh Settings Status message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint8_t setting_property_id[];                         /**< a sequence of all Sensor Setting Property ID states of a sensor  */
} sensor_settings_status_msg_pkt_t;

/** Message format for the Mesh Setting Get message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint16_t setting_property_id;                            /**< Setting Property ID identifying a setting within a sensor*/
} sensor_setting_get_msg_pkt_t;

/** Message format for the Mesh Setting Set message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint16_t setting_property_id;                            /**< Setting Property ID identifying a setting within a sensor*/
    uint8_t setting_raw[];                                         /**< Raw value for the setting */
} sensor_setting_set_msg_pkt_t;

/** Message format for the Mesh Setting Status message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint16_t setting_property_id;                            /**< Setting Property ID identifying a setting within a sensor*/
    uint8_t setting_access;                                      /**< Read / Write access rights for the setting.  */
    uint8_t setting_raw[];                                        /**< Raw value for the setting */
} sensor_setting_status_msg_pkt_t;

/** Message format for the Mesh Sensor Get message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                         /**< Property ID for the sensor (Optional) */
} sensor_get_msg_pkt_t;

/** Message format for the Mesh Sensor Status message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;
    uint8_t sensor_data[];                                 /**< The Sensor Data state */
} sensor_status_msg_pkt_t;

/** Message format for the Mesh Column Get message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint8_t raw_x[];                                                 /**< Raw value identifying a column */
} sensor_column_get_msg_pkt_t;

/** Message format for the Mesh Sensor Column Status message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint8_t column_data[];                                       /**< Column Status raw data */
} sensor_column_status_msg_pkt_t;

/** Message format for the Mesh Series Get message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                         /**< Property ID for the sensor (Optional) */
    uint8_t series_x[];                                              /**<  Series Column states raw data*/
} sensor_series_get_msg_pkt_t;

/** Message format for the Mesh Series Status message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                          /**< The present value of the Mesh Sensor state */
    uint8_t series_data[];                                         /**<  a sequence of  the Series Column states raw data*/
} sensor_series_status_msg_pkt_t;

#endif /* __MESH_SENSOR_MESSAGE_H__ */

/** @} */

