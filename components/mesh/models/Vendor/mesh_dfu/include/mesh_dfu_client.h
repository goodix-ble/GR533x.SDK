/**
 *****************************************************************************************
 *
 * @file mesh_dfu_client.h
 *
 * @brief Mesh DFU Client API.
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
#ifndef __MESH_DFU_CLIENT_H__
#define __MESH_DFU_CLIENT_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "mesh_dfu_common.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/** Mesh DFU Client model ID */
#define MESH_DFU_CLIENT_MODEL_ID (0x0011)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */




/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/* Forward declaration */
typedef struct __mesh_dfu_client_t  mesh_dfu_client_t;

/**
 * Callback type for Mesh DFU Current Version Status
 *
 * @param[in]     p_self                   Pointer to the Mesh DFU client model structure
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the Status message info.
 */
typedef void (*mesh_dfu_current_version_status_cb_t)(const mesh_dfu_client_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg, mesh_dfu_current_version_status_msg_pkt_t *p_in);
/**
 * Callback type for Mesh DFU New Version Status
 *
 * @param[in]     p_self                   Pointer to the Mesh DFU client model structure
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the Status message info.
 */
typedef void (*mesh_dfu_new_version_status_cb_t)(const mesh_dfu_client_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg, mesh_dfu_new_version_status_msg_pkt_t *p_in);
/**
 * Mesh DFU Client callback list.
 */
typedef struct
{
    mesh_dfu_current_version_status_cb_t dfu_current_version_status_cb;     /**< Callback for Mesh DFU Current Version Status message. */
    mesh_dfu_new_version_status_cb_t dfu_new_version_status_cb;             /**< Callback for Mesh DFU New Version Status message. */
    mesh_model_reliable_trans_cb_t ack_transaction_status_cb;               /**< Callback for reliable message timeout. */
} mesh_dfu_client_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    uint32_t timeout_ms;                                /**< Reliable message timeout time. */
    const mesh_dfu_client_callbacks_t *p_callbacks;     /**< User provided callback for this model. */
} mesh_dfu_client_settings_t;

/**
 * Mesh DFU Client model information.
 */
struct __mesh_dfu_client_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    mesh_dfu_client_settings_t settings;        /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */
};

/**
 * Initializes Mesh DFU Client model.
 *
 * @param[in]     p_client                 Mesh DFU client information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is successful.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command is disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t mesh_dfu_client_init(mesh_dfu_client_t *p_client, uint8_t element_offset);

/**
 * Sends a New Version Set message to the server.
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
uint16_t mesh_dfu_client_new_version_set(mesh_dfu_client_t * p_client, const mesh_dfu_new_version_set_msg_pkt_t * p_params);

/**
 * Sends a New Version Set Unacknowledged message to the server.
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
uint16_t mesh_dfu_client_new_version_set_unack(mesh_dfu_client_t * p_client, const mesh_dfu_new_version_set_msg_pkt_t * p_params);

/**
 * Sends a Current Version Get message to the server.
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
uint16_t mesh_dfu_client_current_version_get(mesh_dfu_client_t * p_client);

/**
 * Cancel the sending Set/Get message to the server.
 *
 * @param[in]     p_client                 Client model information pointer.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is successful.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_OFF    Reliable message transfer procedure is off.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 */
uint16_t mesh_dfu_client_setget_cancel(mesh_dfu_client_t * p_client);

#endif /* __MESH_DFU_CLIENT_H__ */

/** @} */
