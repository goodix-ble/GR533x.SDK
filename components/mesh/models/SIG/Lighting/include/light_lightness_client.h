/**
 *****************************************************************************************
 *
 * @file light_lightness_client.h
 *
 * @brief Light Lightness Client API.
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
#ifndef __LIGHT_LIGHTNESS_CLIENT_H__
#define __LIGHT_LIGHTNESS_CLIENT_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "model_common.h"
#include "light_lightness_common.h"

/*
 * DEFINES
 ****************************************************************************************
 */
//#define MESH_MODEL_BQB_TEST

/*
 * ENUMERATIONS
 ****************************************************************************************
 */
 
/*idenfify the cmd type of send to server*/
typedef enum
{
    ACTURL,
    LINEAR,
}cmd_type_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/* Forward declaration */
typedef struct __light_ln_client_t  light_ln_client_t;

/**
 * Callback type for Light Lightness Actual or Linear state related transactions
 *
 * @param[in]     p_self                   Pointer to the light lightness client model structure
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the Lightness Actual or Linear Status message info.
 */
typedef void (*light_ln_state_status_cb_t)(const light_ln_client_t * p_self,
                                           const mesh_model_msg_ind_t * p_rx_msg,
                                           light_ln_status_params_t * p_in);
                                                  
/**
 * Callback type for Light Lightness Last state related transactions
 *
 * @param[in]     p_self                   Pointer to the light lightness client model structure
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the Lightness Last Status message info.
 */
typedef void (*light_ln_last_state_status_cb_t)(const light_ln_client_t * p_self,
                                                const mesh_model_msg_ind_t * p_rx_msg,
                                                light_ln_last_status_params_t * p_in);
                                                       
/**
 * Callback type for Light Lightness Default state related transactions
 *
 * @param[in]     p_self                   Pointer to the light lightness client model structure
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the Lightness Default Status message info.
 */
typedef void (*light_ln_dft_state_status_cb_t)(const light_ln_client_t * p_self,
                                               const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_dft_status_params_t * p_in);

/**
 * Callback type for Light Lightness Range state related transactions
 *
 * @param[in]     p_self                   Pointer to the light lightness client model structure
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the Lightness Range Status message info.
 */
typedef void (*light_ln_range_state_status_cb_t)(const light_ln_client_t * p_self,
                                               const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_range_status_params_t * p_in);

/**
 * Light Lightness Client callback list.
 */
typedef struct
{
    light_ln_state_status_cb_t        ln_actual_status_cb;         /**< Callback for Light Lightness Actual  Status message. */
    light_ln_state_status_cb_t        ln_linear_status_cb;         /**< Callback for Light Lightness Linear  Status message. */
    light_ln_last_state_status_cb_t   ln_last_status_cb;           /**< Callback for Light Lightness Last Status message. */
    light_ln_dft_state_status_cb_t    ln_dft_status_cb;            /**< Callback for Light Lightness Default Status message. */
    light_ln_range_state_status_cb_t  ln_range_status_cb;          /**< Callback for Light Lightness Range Status message. */
    mesh_model_reliable_trans_cb_t    ack_transaction_status_cb;   /**< Callback for reliable message timeout. */
} light_ln_client_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    uint32_t timeout_ms;                                      /**< Reliable message timeout time. */
    const light_ln_client_callbacks_t *p_callbacks;    /**< User provided callback for this model. */
} light_ln_client_settings_t;

/**
 * Light Lightness Client model information.
 */
struct __light_ln_client_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    light_ln_client_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */
};

/**
 * Initializes Light Lightness Client model.
 *
 * @param[in]     p_client                 Light Lightness Client client information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t light_ln_client_init(light_ln_client_t *p_client, uint8_t element_offset);

/**
 * Sends a Lightness Actual or Linear Set message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 Message parameters.
 * @param[in]     p_transition             Optional transition parameters
 * @param[in]     cmd_type                 Identify the cmd is Actual or Linear
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
uint16_t light_ln_client_set(light_ln_client_t * p_client, const light_ln_set_params_t * p_params,
                                  const model_transition_t * p_transition, const cmd_type_t cmd_type);

/**
 * Sends a Lightness Actual or Linear Set Unacknowledged message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 Message parameters.
 * @param[in]     p_transition             Optional transition parameters
 * @param[in]     cmd_type                 Identify the cmd is Actual or Linear
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
uint16_t light_ln_client_set_unack(light_ln_client_t * p_client, const light_ln_set_params_t * p_params,
                                        const model_transition_t * p_transition,const cmd_type_t cmd_type);

/**
 * Sends a Lightness Actual or Linear Get message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     cmd_type                 Identify the cmd is Actual or Linear
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
uint16_t light_ln_client_get(light_ln_client_t * p_client, const cmd_type_t cmd_type);


/**
 * Sends a Lightness Last Get message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
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
uint16_t light_ln_last_client_get(light_ln_client_t * p_client);


/**
 * Sends a Lightness Default Set message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 Message parameters.
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
uint16_t light_ln_dft_client_set(light_ln_client_t * p_client, const light_ln_set_dft_params_t * p_params);

/**
 * Sends a Lightness Default Set Unacknowledged message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 Message parameters.
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
uint16_t light_ln_dft_client_set_unack(light_ln_client_t * p_client, const light_ln_set_dft_params_t * p_params);

/**
 * Sends a Lightness Default Get message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
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
uint16_t light_ln_dft_client_get(light_ln_client_t * p_client);


/**
 * Sends a Lightness Range Set message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 Message parameters.
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
uint16_t light_ln_range_client_set(light_ln_client_t * p_client, const light_ln_set_range_params_t * p_params);

/**
 * Sends a Lightness Range Set Unacknowledged message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 Message parameters.
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
uint16_t light_ln_range_client_set_unack(light_ln_client_t * p_client, const light_ln_set_range_params_t * p_params);

/**
 * Sends a Lightness Range Get message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
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
uint16_t light_ln_range_client_get(light_ln_client_t * p_client);

#endif /* __LIGHT_LIGHTNESS_CLIENT_H__ */

/** @} */

