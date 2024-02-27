/**
 *****************************************************************************************
 *
 * @file sensor_client.h
 *
 * @brief Mesh Sensor Client API.
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
#ifndef __MESH_SENSOR_CLIENT_H__
#define __MESH_SENSOR_CLIENT_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "model_common.h"
#include "sensor_common.h"
#include "mesh_property.h"

/*
 * DEFINES
 ****************************************************************************************
 */
//#define MESH_MODEL_BQB_TEST

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/* Forward declaration */
typedef struct __sensor_client_t  sensor_client_t;

typedef void (*descriptor_state_status_cb_t)(const sensor_client_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    sensor_descriptor_status_params_t * p_in);

typedef void (*cadence_state_status_cb_t)(const sensor_client_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    sensor_cadence_status_params_t * p_in);

typedef void (*settings_state_status_cb_t)(const sensor_client_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    sensor_settings_status_params_t * p_in);

typedef void (*setting_state_status_cb_t)(const sensor_client_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    sensor_setting_status_params_t * p_in);

/**
 * Callback type for sensor state related transactions
 *
 * @param[in]     p_self                   Pointer to the mesh sensor client model structure
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the Status message info.
 */
typedef void (*sensor_state_status_cb_t)(const sensor_client_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    sensor_status_params_t * p_in);

typedef void (*column_state_status_cb_t)(const sensor_client_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    sensor_column_status_params_t * p_in);

typedef void (*series_state_status_cb_t)(const sensor_client_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    sensor_series_status_params_t * p_in);

/**
 * Mesh Sensor Client callback list.
 */
typedef struct
{
    descriptor_state_status_cb_t desc_status_cb;
    cadence_state_status_cb_t cadence_status_cb;
    settings_state_status_cb_t settings_status_cb;
    setting_state_status_cb_t setting_status_cb;
    sensor_state_status_cb_t sensor_status_cb;            /**< Callback for Mesh Sensor Status message. */
    column_state_status_cb_t column_status_cb;
    series_state_status_cb_t series_status_cb;
    mesh_model_reliable_trans_cb_t ack_transaction_status_cb;   /**< Callback for reliable message timeout. */
} sensor_client_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    uint32_t timeout_ms;                                    /**< Reliable message timeout time. */
    const sensor_client_callbacks_t *p_callbacks;    /**< User provided callback for this model. */
} sensor_client_settings_t;

/**
 * Mesh Sensor Client model information.
 */
struct __sensor_client_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    sensor_client_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */
};

/**
 * Initializes Mesh Sensor Client model.
 *
 * @param[in]     p_client                     Mesh Sensor client information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                        Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED    Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid parameter.
 */
uint16_t sensor_client_init(sensor_client_t *p_client, uint8_t element_offset);

uint16_t sensor_descriptor_client_get(sensor_client_t * p_client, const sensor_descriptor_get_params_t * p_params);

uint16_t sensor_cadence_client_get(sensor_client_t * p_client, const sensor_cadence_get_params_t * p_params);

uint16_t sensor_cadence_client_set(sensor_client_t * p_client, const sensor_cadence_set_params_t * p_params);

uint16_t sensor_cadence_client_set_unack(sensor_client_t * p_client, const sensor_cadence_set_params_t * p_params);

uint16_t sensor_settings_client_get(sensor_client_t * p_client, const sensor_settings_get_params_t * p_params);

uint16_t sensor_setting_client_get(sensor_client_t * p_client, const sensor_setting_get_params_t * p_params);

uint16_t sensor_setting_client_set(sensor_client_t * p_client, const sensor_setting_set_params_t * p_params);

uint16_t sensor_setting_client_set_unack(sensor_client_t * p_client, const sensor_setting_set_params_t * p_params);

uint16_t sensor_client_get(sensor_client_t * p_client, const sensor_get_params_t * p_params);

uint16_t sensor_column_client_get(sensor_client_t * p_client, const sensor_column_get_params_t * p_params);

uint16_t sensor_series_client_get(sensor_client_t * p_client, const sensor_series_get_params_t * p_params);

uint16_t sensor_client_setget_cancel(sensor_client_t * p_client);

#endif /* __MESH_SENSOR_CLIENT_H__ */

/** @} */

