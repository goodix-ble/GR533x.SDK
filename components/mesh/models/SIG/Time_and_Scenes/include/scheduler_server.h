/**
 *****************************************************************************************
 *
 * @file scheduler_server.h
 *
 * @brief Mesh Time Server API.
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
#ifndef __TSCNS_SCHEDULER_SERVER_H__
#define __TSCNS_SCHEDULER_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "model_common.h"
#include "scheduler_common.h"

/*
 * DEFINES
 ****************************************************************************************
 */
#define MESH_SCHEDULER_INVALID_YEAR (0x7F)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/* Forward declaration */
typedef struct __mesh_scheduler_server_t  mesh_scheduler_server_t;

typedef struct __mesh_scheduler_setup_server_t  mesh_scheduler_setup_server_t;

/**
 * Callback type for mesh scheduler Get message.
 *
 * @param[in]      p_self                     Pointer to the mesh scheduler server model structure.
 * @param[in]      p_rx_msg               Pointer to the the received message info.
 * @param[out]    p_out                     Pointer to store the output parameters from the user application.
 */
typedef void (*mesh_scheduler_get_cb_t)(mesh_scheduler_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    uint16_t * p_out);

/**
 * Callback type for mesh scheduler action Get message.
 *
 * @param[in]      p_self                   Pointer to the mesh scheduler server model structure.
 * @param[in]      p_rx_msg             Pointer to the the received message info.
 * @param[out]    p_out                   Pointer to store the output parameters from the user application.
 */
typedef void (*mesh_scheduler_action_get_cb_t)(mesh_scheduler_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    const uint8_t p_in,
                                                    mesh_scheduler_action_status_params_t * p_out);

/**
 * Callback type for mesh scheduler action Set message.
 *
 * @param[in]     p_self                   Pointer to the mesh scheduler server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[in]     p_in                      Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[out]    p_out                  Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*mesh_scheduler_action_set_cb_t)(mesh_scheduler_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const mesh_scheduler_action_set_params_t *p_in,
                                                    mesh_scheduler_action_status_params_t * p_out);

/**
 * Transaction callbacks for the Mesh Scheduler state.
 */
typedef struct
{
    mesh_scheduler_get_cb_t get_cb;                                       /**< Callback for Mesh Scheduler Get message. */
    mesh_scheduler_action_get_cb_t action_get_cb;                   /**< Callback for Mesh Scheduler Get message. */
    mesh_scheduler_action_set_cb_t action_set_cb;                   /**< Callback for Mesh Scheduler Set/Set Unacknowledged message. */
} mesh_scheduler_server_state_cbs_t;

/**
 *   mesh scheduler Server callback list.
 */
typedef struct
{
    mesh_scheduler_server_state_cbs_t scheduler_cbs;     /**< Callback list for mesh scheduler Server. */
} mesh_scheduler_server_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    const mesh_scheduler_server_callbacks_t *p_callbacks;    /**< User provided callback for this model. */
} mesh_scheduler_server_settings_t;

/**
 *   mesh scheduler Server model information.
 */
struct __mesh_scheduler_server_t
{
    mesh_lid_t model_lid;                                   /**< Model local identifier. */
    mesh_scheduler_server_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;                    /**< Model instance index. */
};

struct __mesh_scheduler_setup_server_t
{
    mesh_lid_t model_lid;                                    /**< Model local identifier. */
    mesh_scheduler_server_settings_t settings;     /**< Settings for this model instance. */
    uint8_t model_instance_index;                     /**< Model instance index. */

    mesh_scheduler_server_t *scheduler_server;
};

/**
 * Initializes   mesh scheduler Server model.
 *
 * @param[in]     p_server                   Time server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t mesh_scheduler_server_init(mesh_scheduler_server_t *p_server, uint8_t element_offset);

/**
 *   mesh scheduler Server publishes unsolicited Status message.
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
uint16_t mesh_scheduler_server_status_publish(mesh_scheduler_server_t * p_server, 
                                                            const uint16_t *p_params);
                                                            
uint16_t mesh_scheduler_server_action_status_publish(mesh_scheduler_server_t * p_server, 
                                                            const mesh_scheduler_action_status_params_t * p_params);

/**
 *   mesh scheduler Server send Time Status message.
 *
 * @param[in]     p_server                   Time server information pointer.
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
uint32_t scheduler_status_send(mesh_scheduler_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const uint16_t * p_params);


/**
 *   mesh scheduler Server send action Status message.
 *
 * @param[in]     p_server                   Time server information pointer.
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
 uint32_t scheduler_action_status_send(mesh_scheduler_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const mesh_scheduler_action_status_params_t * p_params);

#endif /* __TSCNS_SCHEDULER_SERVER_H__ */

/** @} */

