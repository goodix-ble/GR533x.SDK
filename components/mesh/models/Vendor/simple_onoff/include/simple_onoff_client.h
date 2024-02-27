/**
 *****************************************************************************************
 *
 * @file simple_onoff_client.h
 *
 * @brief Simple On Off Client API.
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
#ifndef __SIMPLE_ONOFF_CLIENT_H__
#define __SIMPLE_ONOFF_CLIENT_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "simple_onoff_common.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/** Simple On Off Client model ID */
#define SIMPLE_ON_OFF_CLIENT_MODEL_ID (0x1001)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */




/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/* Forward declaration */
typedef struct __simple_onoff_client_t  simple_onoff_client_t;

/**
 * Callback type for On Off state related transactions
 *
 * @param[in]     p_self                   Pointer to the Simple on off client model structure
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the Status message info.
 */
typedef void (*simple_onoff_state_status_cb_t)(const simple_onoff_client_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg, simple_onoff_status_msg_pkt_t * p_in);

/**
 * Simple On Off Client callback list.
 */
typedef struct
{
    simple_onoff_state_status_cb_t onoff_status_cb;             /**< Callback for Simple On Off Status message. */
    mesh_model_reliable_trans_cb_t ack_transaction_status_cb;   /**< Callback for reliable message timeout. */
} simple_onoff_client_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    uint32_t timeout_ms;                                    /**< Reliable message timeout time. */
    const simple_onoff_client_callbacks_t *p_callbacks;     /**< User provided callback for this model. */
} simple_onoff_client_settings_t;

/**
 * Simple On Off Client model information.
 */
struct __simple_onoff_client_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    simple_onoff_client_settings_t settings;    /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */
};

/**
 * Initializes Simple On Off Client model.
 *
 * @param[in]     p_client                 Simple OnOff client information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is successful.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command is disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t simple_onoff_client_init(simple_onoff_client_t *p_client, uint8_t element_offset);

/**
 * Sends a Set message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 Message parameters.
 * @param[in]     p_transition             Optional transition parameters
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is successful.
 * @retval ::MESH_ERROR_INVALID_PARAM             Invalid parameter.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES    Insufficient resources.
 * @retval ::MESH_ERROR_INVALID_MODEL             Invalid model.
 * @retval ::MESH_ERROR_INVALID_PUBLISH_PARAMS    Invalid publish parameters.
 * @retval ::MESH_ERROR_INVALID_BINDING           Invalid binding.
 * @retval ::MESH_ERROR_INVALID_APPKEY_ID         Invalid application key index.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED        Command is disallowed.
 * @retval ::MESH_ERROR_NOT_FOUND                 Requested resource not found.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_ON     Reliable message transfer procedure is on.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 */
uint16_t simple_onoff_client_set(simple_onoff_client_t * p_client, const simple_onoff_set_msg_pkt_t * p_params);

/**
 * Sends a Set Unacknowledged message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 * @param[in]     p_params                 Message parameters.
 * @param[in]     p_transition             Optional transition parameters
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is successful.
 * @retval ::MESH_ERROR_INVALID_PARAM             Invalid parameter.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES    Insufficient resources.
 * @retval ::MESH_ERROR_INVALID_MODEL             Invalid model.
 * @retval ::MESH_ERROR_INVALID_PUBLISH_PARAMS    Invalid publish parameters.
 * @retval ::MESH_ERROR_INVALID_BINDING           Invalid binding.
 * @retval ::MESH_ERROR_INVALID_APPKEY_ID         Invalid application key index.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED        Command is disallowed.
 * @retval ::MESH_ERROR_NOT_FOUND                 Requested resource not found.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_ON     Reliable message transfer procedure is on.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 */
uint16_t simple_onoff_client_set_unack(simple_onoff_client_t * p_client, const simple_onoff_set_msg_pkt_t * p_params);

/**
 * Sends a Get message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is successful.
 * @retval ::MESH_ERROR_INVALID_PARAM             Invalid parameter.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES    Insufficient resources.
 * @retval ::MESH_ERROR_INVALID_MODEL             Invalid model.
 * @retval ::MESH_ERROR_INVALID_PUBLISH_PARAMS    Invalid publish parameters.
 * @retval ::MESH_ERROR_INVALID_BINDING           Invalid binding.
 * @retval ::MESH_ERROR_INVALID_APPKEY_ID         Invalid application key index.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED        Command is disallowed.
 * @retval ::MESH_ERROR_NOT_FOUND                 Requested resource not found.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_ON     Reliable message transfer procedure is on.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 */
uint16_t simple_onoff_client_get(simple_onoff_client_t * p_client);

/**
 * Cancel the sending Set/Get message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is successful.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_OFF    Reliable message transfer procedure is off.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 */
uint16_t simple_onoff_client_setget_cancel(simple_onoff_client_t * p_client);

#endif /* __SIMPLE_ONOFF_CLIENT_H__ */

/** @} */
