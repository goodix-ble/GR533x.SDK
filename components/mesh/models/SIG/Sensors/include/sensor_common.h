/**
 *****************************************************************************************
 *
 * @file sensor_common.h
 *
 * @brief Mesh Sensor Common Define.
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
#ifndef __MESH_SENSOR_COMMON_H__
#define __MESH_SENSOR_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** Mesh Sensor Server model max number */
#define MESH_SENSOR_SERVER_INSTANCE_COUNT_MAX              (16)
/** Mesh Sensor Client model max number */
#define MESH_SENSOR_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for Mesh Sensor Server */
#define MESH_SENSOR_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for Mesh Sensor Server publish Status message */
#define MESH_SENSOR_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for Mesh Sensor Server response Status message */
#define MESH_SENSOR_SERVER_RSP_SEND_TX_HDL                 (0x01)

/** The total number of transmit handle for Mesh Sensor Client */
#define MESH_SENSOR_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for Mesh Sensor Client Get message */
#define MESH_SENSOR_CLIENT_GET_SEND_TX_HDL                 (MESH_SENSOR_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + MESH_SENSOR_SERVER_TX_HDL_TOTAL * MESH_SENSOR_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Mesh Sensor Client Set message */
#define MESH_SENSOR_CLIENT_SET_SEND_TX_HDL                 (MESH_SENSOR_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for Mesh Sensor Client Set Unacknowledged message */
#define MESH_SENSOR_CLIENT_SET_UNRELIABLE_SEND_TX_HDL      (MESH_SENSOR_CLIENT_SET_SEND_TX_HDL + 1)

/** The reliable message timeout time */
#define MESH_SENSOR_RELIABLE_MSG_TIMEOUT_MS                (30000)

#define MESH_SENSOR_SETTING_ACCESS_RD      0x01
#define MESH_SENSOR_SETTING_ACCESS_RW      0x03

#define MESH_SENSOR_CADENCE_TRIGGER_VALUE 0x00
#define MESH_SENSOR_CADENCE_TRIGGER_PERCENT 0x01

#define MESH_SENSOR_STATUS_CADENCE_DIV_MAX 15

#define MESH_SENSOR_STATUS_MIN_INTERVAL_MAX 26
/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Permanet parameters for the Mesh sensor Descriptor Get message. */
typedef struct
{
    uint16_t property_id;                                         /**< Property ID for the sensor (Optional) */
} sensor_descriptor_get_params_t;

/** Parameters for the Mesh sensor Descriptor Status message. */
typedef struct
{
    uint16_t sensor_property_id;                        /**< Property ID for the sensor */
    uint16_t sensor_positive_tolerance;             /**< The Sensor Positive Tolerance field*/
    uint16_t sensor_negative_tolerance;            /**< The Sensor Negative Tolerance field*/
    uint8_t sensor_sampling_function;               /**< The Sensor Sampling Function field*/
    uint8_t sensor_measurement_period;          /**< The Sensor Measurement Period field*/
    uint8_t sensor_update_interval;                   /**< The Sensor Update Interval field */
} sensor_descriptor_status_params__t;

typedef struct
{
    uint16_t desc_length;
    uint16_t sensor_property_id;
    sensor_descriptor_status_params__t *p_desc;
}sensor_descriptor_status_params_t;

/** Permanet parameters for the Mesh sensor Cadence Get message. */
typedef struct
{
    uint16_t property_id;                                     /**< Property ID for the sensor . */
} sensor_cadence_get_params_t;

/** Parameters for the Mesh sensor Cadence Set message. */
typedef struct
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint8_t fast_cadence_period_div;
    uint8_t trigger_type;
    uint16_t property_value_length;
    uint8_t *trigger_dlt_down;
    uint8_t *trigger_dlt_up;
    uint8_t min_interval;
    uint8_t * fast_cadence_low;
    uint8_t * fast_cadence_high;
} sensor_cadence_set_params_t;

/** Parameters for the Mesh sensor Cadence Status message. */
typedef struct
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint8_t fast_cadence_period_div;
    uint8_t trigger_type;
    uint16_t property_value_length;
    uint8_t *trigger_dlt_down;
    uint8_t *trigger_dlt_up;
    uint8_t min_interval;
    uint8_t * fast_cadence_low;
    uint8_t * fast_cadence_high;
} sensor_cadence_status_params_t;

/** Permanet parameters for the Mesh sensor Settings Get message. */
typedef struct
{
    uint16_t property_id;                                     /**< Property ID for the sensor . */
} sensor_settings_get_params_t;

/** Parameters for the Mesh sensor Settings Status message. */
typedef struct
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint16_t setting_id_number;
    uint8_t *setting_property_id;                         /**< a sequence of all Sensor Setting Property ID states of a sensor  */
} sensor_settings_status_params_t;

/** Permanet parameters for the Mesh sensor Setting Get message. */
typedef struct
{
    uint16_t property_id;                                        /**< Property ID for the sensor . */
    uint16_t setting_property_id;                           /**< Setting Property ID identifying a setting within a sensor*/
} sensor_setting_get_params_t;

/** Parameters for the Mesh sensor Setting Set message. */
typedef struct
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint16_t setting_property_id;                            /**< Setting Property ID identifying a setting within a sensor*/
    uint16_t setting_raw_length;
    uint8_t *setting_raw;                                         /**< Raw value for the setting */
} sensor_setting_set_params_t;

/** Parameters for the Mesh sensor Setting Status message. */
typedef struct
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint16_t setting_property_id;                            /**< Setting Property ID identifying a setting within a sensor*/
    uint8_t setting_access;
    uint16_t setting_raw_length;
    uint8_t *setting_raw;                                         /**< Raw value for the setting */
} sensor_setting_status_params_t;

/** Permanet parameters for the Mesh Sensor Get message. */
typedef struct
{
    uint16_t property_id;                                     /**< Property ID for the sensor (Optional). */
} sensor_get_params_t;

/** Parameters for the Mesh Sensor Status message. */
//typedef struct
//{
    //uint16_t property_id;
    //uint16_t raw_value_length;
    //uint8_t *raw_value;                                 /**< The Sensor Data state */
//} sensor_status_params__t;

typedef struct
{
    //uint16_t sensor_data_number;
    uint8_t format;
    uint16_t property_id;
    uint16_t sensor_data_length;
    uint8_t *p_sensor_data;
    //sensor_status_params__t *p_sensor_data;                                 /**< The Sensor Data state */
} sensor_status_params_t;

/** Permanet parameters for the Mesh Sensor Column Get message. */
typedef struct
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint16_t raw_x_length;
    uint8_t *raw_x;                                                 /**< Raw value identifying a column */
} sensor_column_get_params_t;

/** Parameters for the Mesh Sensor Column Status message. */
typedef struct
{
    uint16_t property_id;                                         /**< Property ID for the sensor  */
    uint16_t raw_x_length;
    uint8_t *raw_x;                                                  /**< Raw value representing the left corner of the column on the X axis. */
    uint16_t width_length;
    uint8_t *width;                                                   /**< Raw value representing the width of the column.  */
    uint16_t raw_y_length;
    uint8_t *raw_y;                                                  /**< Raw value representing the height of the column on the Y axis */
} sensor_column_status_params_t;

/** Permanet parameters for the Mesh Sensor Series Get message. */
typedef struct
{
    uint16_t property_id;                                     /**< Property ID for the sensor . */
    uint16_t series_x_length;
    uint8_t *series_x1;                                              /**<  Series Column states raw data*/
    uint8_t *series_x2;                                              /**<  Series Column states raw data*/
} sensor_series_get_params_t;

/** Parameters for the Mesh Sensor Series Status message. */
typedef struct
{
    uint16_t raw_x_length;
    uint8_t *raw_x;                                                  /**< Raw value representing the left corner of the column on the X axis. */
    uint16_t width_length;
    uint8_t *width;                                                   /**< Raw value representing the width of the column.  */
    uint16_t raw_y_length;
    uint8_t *raw_y;                                                  /**< Raw value representing the height of the column on the Y axis */
} sensor_series_status_params__t;

typedef struct
{
    uint16_t property_id;                                          /**< Property ID for the sensor . */
    uint16_t series_data_num;
    sensor_series_status_params__t *series_data;     /**<  a sequence of  the Series Column states raw data*/
} sensor_series_status_params_t;
#endif /* __MESH_SENSOR_COMMON_H__ */

/** @} */

