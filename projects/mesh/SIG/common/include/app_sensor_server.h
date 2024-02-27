/**
 *****************************************************************************************
 *
 * @file app_sensor_server.h
 *
 * @brief App Sensor API.
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
#ifndef __APP_SENSOR_SERVER_H__
#define __APP_SENSOR_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "sensor_server.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

#define MESH_SENSOR_SERVER_INSTANCE_COUNT (1)    // should no more than MESH_SENSOR_SERVER_INSTANCE_COUNT_MAX

#define SENSOR_PUB_ON 0x01
#define SENSOR_PUB_OFF 0x00
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef struct
{
    uint16_t candece_number;
    uint32_t delay_ms_in_period;
    sensor_cadence_status_params_t *p_candece;
}app_sensor_cadence_t;

typedef struct
{
    uint16_t sensor_state_number;
    uint16_t sensor_pub_number;
    uint8_t *sensor_pub_map;
    sensor_status_params_t *p_sensor;
}app_sensor_status_t;

/**
 * Application Generic Sensor Server model information.
 */
 typedef struct
 {
    sensor_server_t server;      /**< Generic Sensor Server model information. */

    mesh_timer_t pub_timer;             /**< publish period timer instance. */
    uint32_t publish_period_ms;
    uint16_t client_address;            /**< The address message received. */
} app_sensor_server_t;

typedef struct
{
    app_sensor_server_t *p_server;
    uint16_t trigger_id;                                /**< property id. */
    int32_t trigger_delta_value;                 /**< property id value. */
    bool trigger_flag;                                  /**< true, publish immediate;     false, publish later*/
    uint8_t trigger_min_period;
}app_sensor_min_period_ctrl_t;

/**
 * Initializes Application Mesh Sensor Server model.
 *
 * @param[in]     p_server                 Application Mesh Sensor server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     set_cb                   Application Mesh Sensor server setting callback.
 * @param[in]     get_cb                   Application Mesh Sensor server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_sensor_server_init(app_sensor_server_t *p_server, uint8_t element_offset);

/**
 * Application Mesh Sensor Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Mesh Sensor server information pointer.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is Success.
 * @retval ::MESH_ERROR_INVALID_PARAM             Invalid Parameter.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES    Insufficient Resources.
 * @retval ::MESH_ERROR_INVALID_MODEL             Invalid Model.
 * @retval ::MESH_ERROR_INVALID_PUBLISH_PARAMS    Invalid Publish Parameters.
 * @retval ::MESH_ERROR_INVALID_BINDING           Invalid Binding.
 * @retval ::MESH_ERROR_INVALID_APPKEY_ID         Invalid AppKey Index.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED        Command Disallowed.
 * @retval ::MESH_ERROR_NOT_FOUND                 Resource requested not found.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_ON     Reliable message transfer procedure is on.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 */
void app_sensor_status_publish(app_sensor_server_t * p_server);

void app_sensor_desc_status_register(sensor_descriptor_status_params__t * reg, uint16_t reg_length);

void app_sensor_cadence_status_register(sensor_cadence_status_params_t * reg, uint16_t reg_length);

void app_sensor_settings_status_register(sensor_settings_status_params_t * reg);

void app_sensor_setting_status_register(sensor_setting_status_params_t * reg);

void app_sensor_state_status_register(sensor_status_params_t * reg, uint8_t *pub_map, uint16_t reg_length);

void app_sensor_column_status_register(sensor_column_status_params_t * reg);

void app_sensor_series_status_register(sensor_series_status_params_t * reg);

void app_sensor_status_update(app_sensor_server_t * p_server, uint16_t property_id, uint8_t *delta_value, uint16_t value_length, bool decrese_flag);

#endif /* __APP_SENSOR_SERVER_H__ */

/** @} */

