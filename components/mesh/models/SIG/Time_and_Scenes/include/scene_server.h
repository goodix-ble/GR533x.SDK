/**
 *****************************************************************************************
 *
 * @file scene_server.h
 *
 * @brief Mesh Scene Server API.
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
#ifndef __TSCNS_SCENE_SERVER_H__
#define __TSCNS_SCENE_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "model_common.h"
#include "mesh_scenes_common.h"
#include "scene_common.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/* Forward declaration */
typedef struct __mesh_scene_server_t  mesh_scene_server_t;

typedef struct __mesh_scene_setup_server_t  mesh_scene_setup_server_t;

/**
 * Callback type for Mesh Scene Store/Store Unacknowledged message.
 *
 * @param[in]      p_self                   Pointer to the mesh Scene Setup server model structure.
 * @param[in]      p_rx_msg             Pointer to the the received message info.
 * @param[in]      p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[out]    p_out                   Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*mesh_scene_state_store_cb_t)(mesh_scene_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const mesh_scene_store_params_t * p_in,
                                                    mesh_scene_register_status_params_t * p_out);

/**
 * Callback type for mesh Scene Recal/Recall Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the mesh Scene server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[in]     p_in_transition      Pointer to optional transition parameters, if present in the incoming message.
 *                                         Otherwise, set to NULL.
 * @param[out]    p_out                  Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*mesh_scene_state_recall_cb_t)(mesh_scene_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const mesh_scene_recall_params_t * p_in,
                                                    const model_transition_t * p_in_transition,
                                                    mesh_scene_status_params_t * p_out);


/**
 * Callback type for mesh Scene Get message.
 *
 * @param[in]     p_self                   Pointer to the mesh Scene server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[out]    p_out                  Pointer to store the output parameters from the user application.
 */
typedef void (*mesh_scene_state_get_cb_t)(mesh_scene_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    mesh_scene_status_params_t * p_out);

/**
 * Callback type for mesh Scene Register Get message.
 *
 * @param[in]     p_self                   Pointer to the mesh Scene server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[out]    p_out                  Pointer to store the output parameters from the user application.
 */
typedef void (*mesh_scene_state_register_get_cb_t)(mesh_scene_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    mesh_scene_register_status_params_t * p_out);

/**
 * Callback type for mesh Scene Delete/Delete Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the mesh Scene Setup server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[out]    p_out                  Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*mesh_scene_state_delete_cb_t)(mesh_scene_setup_server_t *p_self,
                                                   const mesh_model_msg_ind_t *p_rx_msg,
                                                   const mesh_scene_delete_params_t * p_in,
                                                   mesh_scene_register_status_params_t * p_out);
/**
 * Transaction callbacks for the   mesh Scene state.
 */
typedef struct
{
    mesh_scene_state_store_cb_t store_cb;                            /**< Callback for   mesh Scene Set/Set Unacknowledged message. */
    mesh_scene_state_recall_cb_t recall_cb;                           /**< Callback for   mesh Scene Get message. */
    mesh_scene_state_get_cb_t get_cb;                            /**< Callback for   mesh Scene Set/Set Unacknowledged message. */
    mesh_scene_state_register_get_cb_t register_get_cb;                   /**< Callback for   mesh Scene Set/Set Unacknowledged message. */
    mesh_scene_state_delete_cb_t delete_cb;                  /**< Callback for   mesh Scene Get message. */
} mesh_scene_server_state_cbs_t;

/**
 *   mesh Scene Server callback list.
 */
typedef struct
{
    mesh_scene_server_state_cbs_t scenes_cbs;     /**< Callback list for mesh Scene Server. */
} mesh_scene_server_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    const mesh_scene_server_callbacks_t *p_callbacks;    /**< User provided callback for this model. */
} mesh_scene_server_settings_t;

/**
 *   mesh Scene Server model information.
 */
struct __mesh_scene_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    tid_tracker_t tid_tracker;                  /**< Tid tracker. */
    mesh_scene_server_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */

    uint8_t * p_dtt_ms;        /**< point to the default transition time*/
};

struct __mesh_scene_setup_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    mesh_scene_server_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */

    mesh_scene_server_t *scene_server;
};

/**
 * Initializes   mesh Scene Server model.
 *
 * @param[in]     p_server                   Time server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t mesh_scene_server_init(mesh_scene_server_t *p_server, uint8_t element_offset);

/**
 *   mesh Scene Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                   Time server information pointer.
 * @param[in]     p_params                 Status Message parameters.
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
uint16_t mesh_scene_server_status_publish(mesh_scene_server_t * p_server, 
                                             const mesh_scene_status_params_t * p_params);
                                             
uint16_t mesh_scene_server_register_status_publish(mesh_scene_server_t * p_server,
                                                            const mesh_scene_register_status_params_t * p_params);

/**
 *   mesh Scene Server send Scene Register Status message.
 *
 * @param[in]     p_server                   Scene server information pointer.
 * @param[in]     p_rx_msg                 Revice Message parameters.
 * @param[in]     p_params                 Status Message parameters.
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
 uint32_t scene_regester_status_send(mesh_scene_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const mesh_scene_register_status_params_t * p_params);
#endif /* __TSCNS_SCENE_SERVER_H__ */

/** @} */

