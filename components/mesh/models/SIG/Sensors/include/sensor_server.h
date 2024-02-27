/**
 *****************************************************************************************
 *
 * @file sensor_server.h
 *
 * @brief Mesh Sensor Server API.
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
#ifndef __MESH_SENSOR_SERVER_H__
#define __MESH_SENSOR_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "model_common.h"
#include "sensor_common.h"
#include "grx_sys.h"
#include "mesh_property.h"

/*
 * DEFINES
 ****************************************************************************************
 */

#define SENSOR_TOLERANCE_MASK (0xFFF)
#define SENSOR_PROPERTY_ID_LENGTH (2)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/* Forward declaration */
typedef struct __sensor_server_t  sensor_server_t;

typedef struct __sensor_setup_server_t  sensor_setup_server_t;

/**
 * Callback type for Mesh Sensor Descriptor Get message.
 *
 * @param[in]     p_self                   Pointer to the mesh sensor server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[out]    p_out                  Pointer to store the output parameters from the user application.
 */
typedef void (*sensor_descriptor_state_get_cb_t)(sensor_server_t * p_self,
                                                                                            const mesh_model_msg_ind_t * p_rx_msg,
                                                                                            sensor_descriptor_get_params_t * p_in,
                                                                                            sensor_descriptor_status_params_t* p_out);

/**
 * Callback type for Mesh Sensor Get message.
 *
 * @param[in]     p_self                   Pointer to the mesh sensor server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanent parameters of get message.
 * @param[out]    p_out                  Pointer to the output parameters address from the user application.
 * @param[out]    p_out_length        the length of output parameters from the user application.
 */
typedef void (*sensor_state_get_cb_t)(sensor_server_t * p_self,
                                                                            const mesh_model_msg_ind_t * p_rx_msg,
                                                                            const sensor_get_params_t * p_in,
                                                                            sensor_status_params_t ** p_out,
                                                                            uint16_t *p_out_length,
                                                                            bool map_pub);
/**
 * Callback type for Mesh Sensor Column Get message.
 *
 * @param[in]     p_self                   Pointer to the mesh sensor server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[out]    p_out                  Pointer to store the output parameters from the user application.
 */
typedef void (*sensor_column_state_get_cb_t)(sensor_server_t * p_self,
                                                                                            const mesh_model_msg_ind_t * p_rx_msg,
                                                                                            const sensor_column_get_params_t * p_in,
                                                                                            sensor_column_status_params_t * p_out);
/**
 * Callback type for Mesh Sensor Series Get message.
 *
 * @param[in]     p_self                   Pointer to the mesh sensor server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[out]    p_out                  Pointer to store the output parameters from the user application.
 */
typedef void (*sensor_series_state_get_cb_t)(sensor_server_t * p_self,
                                                                                            const mesh_model_msg_ind_t * p_rx_msg,
                                                                                            const sensor_series_get_params_t *p_in,
                                                                                            sensor_series_status_params_t * p_out);

typedef void (*sensor_publish_period_cb_t)(sensor_server_t * p_self,
                                                                                            const mesh_model_publish_period_ind_t * p_rx_msg);

/**************************************setup server callback*****************************************/

/**
 * Callback type for Mesh Sensor Cadence Get message.
 *
 * @param[in]     p_self                   Pointer to the mesh sensor setup server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanent parameters of get message.
 * @param[out]    p_out                  Pointer to store the output parameters from the user application.
 */
typedef void (*sensor_cadence_state_get_cb_t)(sensor_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const sensor_cadence_get_params_t * p_in,
                                                    sensor_cadence_status_params_t * p_out);

/**
 * Callback type for Mesh Sensor Cadence Set/Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the mesh sensor setup server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanent parameters of set/set unacknowledged message.
 * @param[out]    p_out                  Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*sensor_cadence_state_set_cb_t)(sensor_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const sensor_cadence_set_params_t * p_in,
                                                    sensor_cadence_status_params_t * p_out);

/**
 * Callback type for Mesh Sensor Settings Get message.
 *
 * @param[in]     p_self                   Pointer to the mesh sensor setup server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanent parameters of get message.
 * @param[out]    p_out                  Pointer to store the output parameters from the user application.
 */
typedef void (*sensor_settings_state_get_cb_t)(sensor_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const sensor_settings_get_params_t * p_in,
                                                    sensor_settings_status_params_t * p_out);

/**
 * Callback type for Mesh Sensor Setting Get message.
 *
 * @param[in]     p_self                   Pointer to the mesh sensor setup server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanent parameters of get message.
 * @param[out]    p_out                  Pointer to store the output parameters from the user application.
 */
typedef void (*sensor_setting_state_get_cb_t)(sensor_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const sensor_setting_get_params_t * p_in,
                                                    sensor_setting_status_params_t * p_out);

/**
 * Callback type for Mesh Sensor Setting Set/Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the mesh sensor setup server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanent parameters of set/set unacknowledged message.
 * @param[out]    p_out                  Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*sensor_setting_state_set_cb_t)(sensor_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const sensor_setting_set_params_t * p_in,
                                                    sensor_setting_status_params_t * p_out);


/**
 * Transaction callbacks for the Mesh Sensor state.
 */
typedef struct
{
    sensor_descriptor_state_get_cb_t descrip_get_cb; /**< Callback for Mesh Sensor Descriptor Get message. */
    sensor_state_get_cb_t get_cb;                               /**< Callback for Mesh Sensor Get message. */
    sensor_column_state_get_cb_t column_get_cb;     /**< Callback for Mesh Sensor Column Get message. */
    sensor_series_state_get_cb_t series_get_cb;        /**< Callback for Mesh Sensor Series Get message. */
    sensor_publish_period_cb_t publish_period_cb;
} sensor_server_state_cbs_t;

typedef struct
{
    sensor_cadence_state_get_cb_t cadence_get_cb;   /**< Callback for Mesh Sensor Cadence Get message. */
    sensor_cadence_state_set_cb_t cadence_set_cb;   /**< Callback for Mesh Sensor Cadence Set/Set Unacknowledged message. */
    sensor_settings_state_get_cb_t settings_get_cb;    /**< Callback for Mesh Sensor Settings Get message. */
    sensor_setting_state_get_cb_t setting_get_cb;        /**< Callback for Mesh Sensor Setting Get message. */
    sensor_setting_state_set_cb_t setting_set_cb;        /**< Callback for Mesh Sensor Setting Set/Set Unacknowledged message. */
} sensor_setup_server_state_cbs_t;

/**
 * Mesh Sensor Server callback list.
 */
typedef struct
{
    sensor_server_state_cbs_t sensor_cbs;                       /**< Callback list for Mesh Sensor Server. */
} sensor_server_callbacks_t;

/**
 * Mesh Sensor Setup Server callback list.
 */
typedef struct
{
    sensor_setup_server_state_cbs_t sensor_setup_cbs;  /**< Callback list for Mesh Sensor Setup Server. */
} sensor_setup_server_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    const sensor_server_callbacks_t *p_callbacks;    /**< User provided callback for this model. */
} sensor_server_settings_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    const sensor_setup_server_callbacks_t *p_callbacks;    /**< User provided callback for this model. */
} sensor_setup_server_settings_t;

/**
 * Mesh Sensor Server model information.
 */
struct __sensor_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    sensor_server_settings_t settings;      /**< Settings for this model instance. */
    uint8_t model_instance_index;        /**< Model instance index. */
};

/**
 * Mesh Sensor Server model information.
 */
struct __sensor_setup_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    sensor_setup_server_settings_t settings;      /**< Settings for this model instance. */
    uint8_t model_instance_index;        /**< Model instance index. */
};

/**
 * Initializes Mesh Sensor Server model.
 *
 * @param[in]     p_server                 Mesh Sensor server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t sensor_server_init(sensor_server_t *p_server, uint8_t element_offset);

/**
 * Mesh Sensor Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Mesh Sensor server information pointer.
 * @param[in]     p_params                Status Message parameters.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is Success.
 * @retval ::MESH_ERROR_INVALID_PARAM             Invalid Parameter.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES    Insufficient Resources.
 * @retval ::MESH_ERROR_INVALID_MODEL             Invalid Model.
 * @retval ::MESH_ERROR_INVALID_PUBLISH_PARAMS    Invalid Publish Parameters.
 * @retval ::MESH_ERROR_INVALID_BINDING           Invalid Binding.
 * @retval ::MESH_ERROR_INVALID_APPKEY_ID         Invalid AppKey Index.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED        Command Disallowed.
 * @retval ::MESH_ERROR_NOT_FOUND                 Requested resource not found.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_ON     Reliable message transfer procedure is on.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 */
uint16_t sensor_server_desc_status_publish(sensor_server_t * p_server, 
                                                            const sensor_descriptor_status_params_t * p_params);

/**
 * Mesh Sensor Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Mesh Sensor server information pointer.
 * @param[in]     p_params                Status Message parameters.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is Success.
 * @retval ::MESH_ERROR_INVALID_PARAM             Invalid Parameter.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES    Insufficient Resources.
 * @retval ::MESH_ERROR_INVALID_MODEL             Invalid Model.
 * @retval ::MESH_ERROR_INVALID_PUBLISH_PARAMS    Invalid Publish Parameters.
 * @retval ::MESH_ERROR_INVALID_BINDING           Invalid Binding.
 * @retval ::MESH_ERROR_INVALID_APPKEY_ID         Invalid AppKey Index.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED        Command Disallowed.
 * @retval ::MESH_ERROR_NOT_FOUND                 Requested resource not found.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_ON     Reliable message transfer procedure is on.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 */
uint16_t sensor_server_status_publish(sensor_server_t * p_server, bool pub_map);

#endif /* __MESH_SENSOR_SERVER_H__ */

/** @} */

