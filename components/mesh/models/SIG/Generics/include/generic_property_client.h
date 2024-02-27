/**
 ****************************************************************************************
 *
 * @file generic_property_client.h
 *
 * @brief @brief Generic Property Client API.
 *
 ****************************************************************************************
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
#ifndef __GENERIC_PROPERTY_CLIENT_H__
#define __GENERIC_PROPERTY_CLIENT_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "model_common.h"
#include "generic_property_common.h"

/*
 * DEFINES
 ****************************************************************************************
 */
//#define MESH_MODEL_BQB_TEST
/*
 * ENUMERATIONS
 ****************************************************************************************
 */
typedef enum
{
    USER,
    ADMIN,
    MFR,
}property_cmd_type_t;


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef struct __generic_property_client_t  generic_property_client_t;

/**
 * Callback type for Property state related transactions
 *
 * @param[in]     p_self                   Pointer to the model structure
 * @param[in]     p_rx_msg                 Pointer to the mesh model received message
 * @param[in]     p_in                     Pointer to the input event parameters for the user application
 */
typedef void (*generic_property_user_state_status_cb_t)(const generic_property_client_t * p_self,
                                                        const mesh_model_msg_ind_t * p_rx_msg,
                                                        const generic_property_uam_status_params_t * p_in);
                                                        
typedef void (*generic_properties_user_state_status_cb_t)(const generic_property_client_t * p_self,
                                                        const mesh_model_msg_ind_t * p_rx_msg,
                                                        const generic_properties_uamc_status_params_t * p_in);
                                                        
typedef void (*generic_property_admin_state_status_cb_t)(const generic_property_client_t * p_self,
                                                        const mesh_model_msg_ind_t * p_rx_msg,
                                                        const generic_property_uam_status_params_t * p_in);
                                                        
typedef void (*generic_properties_admin_state_status_cb_t)(const generic_property_client_t * p_self,
                                                        const mesh_model_msg_ind_t * p_rx_msg,
                                                        const generic_properties_uamc_status_params_t * p_in);
                                                        
typedef void (*generic_property_mfr_state_status_cb_t)(const generic_property_client_t * p_self,
                                                        const mesh_model_msg_ind_t * p_rx_msg,
                                                        const generic_property_uam_status_params_t * p_in);
                                                        
typedef void (*generic_properties_mfr_state_status_cb_t)(const generic_property_client_t * p_self,
                                                        const mesh_model_msg_ind_t * p_rx_msg,
                                                        const generic_properties_uamc_status_params_t * p_in);
                                                        
typedef void (*generic_properties_client_state_status_cb_t)(const generic_property_client_t * p_self,
                                                        const mesh_model_msg_ind_t * p_rx_msg,
                                                        const generic_properties_uamc_status_params_t * p_in);


/**
 * Generic Property Client callback list.
 */
typedef struct
{
    generic_property_user_state_status_cb_t    property_user_status_cb;            /**< Client model User Property response message callback. */    
    generic_properties_user_state_status_cb_t  properties_user_status_cb;           /**< Client model User Properties response message callback. */
    generic_property_admin_state_status_cb_t    property_admin_status_cb;            /**< Client model Admin Property response message callback. */    
    generic_properties_admin_state_status_cb_t  properties_admin_status_cb;           /**< Client model Admin Properties response message callback. */
    generic_property_mfr_state_status_cb_t    property_mfr_status_cb;            /**< Client model Manufacturer Property response message callback. */    
    generic_properties_mfr_state_status_cb_t  properties_mfr_status_cb;           /**< Client model Manufacturer Properties response message callback. */
    generic_properties_client_state_status_cb_t properties_client_status_cb;       /**< Client model Client Properties response message callback. */
    
    mesh_model_reliable_trans_cb_t ack_transaction_status_cb;           /**< Callback to call after the acknowledged transaction has ended. */
} generic_property_client_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    uint32_t timeout_ms;                                        /**< Reliable message timeout time. */
    const generic_property_client_callbacks_t *p_callbacks;        /**< User provided callback for this model. */
} generic_property_client_settings_t;

/**
 * Generic Property Client model information.
 */
struct __generic_property_client_t
{
    mesh_lid_t model_lid;                                       /**< Model local identifier. */
    generic_property_client_settings_t settings;                   /**< Settings for this model instance. */
    uint8_t model_instance_index;                               /**< Model instance index. */
};

/**
 * Initializes Generic Property Client model.
 *
 * @param[in]     p_client                 Generic Property client information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t generic_property_client_init(generic_property_client_t *p_client, uint8_t element_offset);

/**
 * Sends a Set message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 User Set Message parameters.
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
uint16_t generic_property_client_user_set(generic_property_client_t * p_client, const generic_property_user_set_params_t * p_params);

/**
 * Sends a Set Unacknowledged message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 User Set Message parameters.
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
uint16_t generic_property_client_user_set_unack(generic_property_client_t * p_client, const generic_property_user_set_params_t * p_params);



/**
 * Sends a Admin Set message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 Admin Set Message parameters.
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
uint16_t generic_property_client_admin_set(generic_property_client_t * p_client, const generic_property_admin_set_params_t * p_params);


/**
 * Sends a Delta Set Unacknowledged message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 Admin Set Message parameters.
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
uint16_t generic_property_client_admin_set_unack(generic_property_client_t * p_client, const generic_property_admin_set_params_t * p_params);


/**
 * Sends a Manufacturer Set message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 Manufacture Set Message parameters.
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
uint16_t generic_property_client_mfr_set(generic_property_client_t * p_client, const generic_property_mfr_set_params_t * p_params);

/**
 * Sends a Move Set Unacknowledged message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 Manufacture Set Message parameters.
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
uint16_t generic_property_client_mfr_set_unack(generic_property_client_t * p_client, const generic_property_mfr_set_params_t * p_params);

/**
 * Sends a Get message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 User/Admin/Manufacturer Get Message parameters.
 * @param[in]     cmd_type                 Identify the Get Message command type is User or Admin or Manufacturer.
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
uint16_t generic_property_client_uam_get(generic_property_client_t * p_client, 
                                          const generic_property_uam_get_params_t * p_params,
                                          property_cmd_type_t cmd_type);

/**
 * Sends a Get message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     cmd_type                 Identify the Get Message command type is User or Admin or Manufacturer.
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
uint16_t generic_properties_client_uam_get(generic_property_client_t * p_client, property_cmd_type_t cmd_type);


/**
 * Sends a Get message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 Client Get Message parameters.
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
uint16_t generic_properties_client_get(generic_property_client_t * p_client, const generic_properties_client_get_params_t * p_params);

#endif /* __GENERIC_property_CLIENT_H__ */

/** @} */
