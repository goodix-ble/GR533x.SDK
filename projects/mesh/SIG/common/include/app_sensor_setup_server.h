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
#ifndef __APP_MESH_SENSOR_SETUP_SERVER_H__
#define __APP_MESH_SENSOR_SETUP_SERVER_H__

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

//#define MESH_SENSOR_SERVER_INSTANCE_COUNT (1)    // should no more than MESH_SENSOR_SERVER_INSTANCE_COUNT_MAX

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/**
 * Application callback type for Generic Sensor Cadence Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     status                     Sensor state to be used by the application.
 */
typedef void (*app_sensor_cadence_set_cb_t)(uint8_t model_instance_index, sensor_cadence_status_params_t *status);

/**
 * Application callback type for Generic Sensor Setting Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[out]     status           Application fills this value with the value retrived from the hardware interface.
 */
typedef void (*app_sensor_setting_set_cb_t)(uint8_t model_instance_index, sensor_setting_status_params_t *status);

/**
 * Application Generic Sensor Server model information.
 */
 typedef struct
 {
    sensor_setup_server_t server;      /**< Generic Sensor Server model information. */
    app_sensor_cadence_set_cb_t cadence_set_cb;    /**< Callback to be called for informing the user application to update the cadence*/
    app_sensor_setting_set_cb_t setting_get_cb;    /**< Callback to be called for informing the user application to update the setting*/

    uint16_t client_address;            /**< The address message received. */
 } app_sensor_setup_server_t;

/**
 * Initializes Application Generic Sensor Server model.
 *
 * @param[in]     p_server                 Application Generic OnOff server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     set_cb                   Application Generic OnOff server setting callback.
 * @param[in]     get_cb                   Application Generic OnOff server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_sensor_setup_server_init(app_sensor_setup_server_t *p_server, uint8_t element_offset, app_sensor_cadence_set_cb_t cadence_set_cb, app_sensor_setting_set_cb_t setting_set_cb);

/**
 * Application Generic Sensor Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Generic OnOff server information pointer.
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
//void app_sensor_status_publish(app_sensor_server_t * p_server);

#endif /* __APP_MESH_SENSOR_SETUP_SERVER_H__ */

/** @} */

