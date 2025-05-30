/**
 ****************************************************************************************
 *
 * @file generic_level_server.h
 *
 * @brief  Generic Level Server API.
 *
 *
 ****************************************************************************************
 @attention
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
#ifndef __GENERIC_LEVEL_SERVER_H__
#define __GENERIC_LEVEL_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "model_common.h"
#include "generic_level_common.h" 

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
typedef struct __generic_level_server_t generic_level_server_t;

/**
 * Callback type for Generic Level Set/Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the model structure.
 * @param[in]     p_rx_msg                 Pointer to the mesh model received message.
 * @param[in]     p_in                     Pointer to the input parameters for the user application.
 * @param[in]     p_in_transition          Pointer to transition parameters, if present in the incoming message,
 *                                         otherwise set to null.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 *                                         If null, indicates that it is UNACKNOWLEDGED message and no
 *                                         output params are required.
 */
typedef void (*generic_level_state_set_cb_t)(const generic_level_server_t * p_self,
                                             const mesh_model_msg_ind_t *p_rx_msg,
                                             const generic_level_set_params_t * p_in,
                                             const model_transition_t * p_in_transition,
                                             generic_level_status_params_t * p_out);


/**
 * Callback type for Generic Level Get message.
 *
 * @param[in]     p_self                   Pointer to the model structure.
 * @param[in]     p_rx_msg                 Pointer to the mesh model received message.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 */
typedef void (*generic_level_state_get_cb_t)(const generic_level_server_t * p_self,
                                             const mesh_model_msg_ind_t *p_rx_msg,
                                             generic_level_status_params_t * p_out);


/**
 * Callback type for Generic Level Delta Set/Delta Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the model structure.
 * @param[in]     p_rx_msg                 Pointer to the mesh model received message.
 * @param[in]     p_in                     Pointer to the input parameters for the user application.
 * @param[in]     p_in_transition          Pointer to transition parameters, if present in the incoming message,
 *                                         otherwise set to null.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 *                                         If null, indicates that it is UNACKNOWLEDGED message and no
 *                                         output params are required.
 */
typedef void (*generic_level_state_delta_set_cb_t)(const generic_level_server_t * p_self,
                                                   const mesh_model_msg_ind_t *p_rx_msg,
                                                   const generic_level_delta_set_params_t * p_in,
                                                   const model_transition_t * p_in_transition,
                                                   generic_level_status_params_t * p_out);


/**
 * Callback type for Generic Level Move Set/Move Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the model structure.
 * @param[in]     p_rx_msg                 Pointer to the mesh model received message.
 * @param[in]     p_in                     Pointer to the input parameters for the user application.
 * @param[in]     p_in_transition          Pointer to transition parameters, if present in the incoming message,
 *                                         otherwise set to null.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 *                                         If null, indicates that it is UNACKNOWLEDGED message and no
 *                                         output params are required.
 */
typedef void (*generic_level_state_move_set_cb_t)(const generic_level_server_t * p_self,
                                                  const mesh_model_msg_ind_t *p_rx_msg,
                                                  const generic_level_move_set_params_t * p_in,
                                                  const model_transition_t * p_in_transition,
                                                  generic_level_status_params_t * p_out);


/**
 * Transaction callbacks for the Generic Level state.
 */
typedef struct
{
    generic_level_state_get_cb_t        get_cb;         /**< Callback for Generic Level Get message. */
    generic_level_state_set_cb_t        set_cb;         /**< Callback for Generic Level Set/Set Unacknowledged message. */
    generic_level_state_delta_set_cb_t  delta_set_cb;   /**< Callback for Generic Level Delta Set/Set Unacknowledged message. */
    generic_level_state_move_set_cb_t   move_set_cb;    /**< Callback for Generic Level Move Set/Set Unacknowledged message. */
} generic_level_server_state_cbs_t;


/**
 * Generic Level server callback list.
 */
typedef struct
{    
    generic_level_server_state_cbs_t level_cbs;           /** Callbacks for the level state. */
} generic_level_server_callbacks_t;


/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{    
    const generic_level_server_callbacks_t * p_callbacks;  /**< User provided callback for this model. */
} generic_level_server_settings_t;

/**
 * Generic Level Server model information.
 */
struct __generic_level_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */    
    tid_tracker_t tid_tracker;                  /** Tid tracker structure. */   
    generic_level_server_settings_t settings;   /** Model settings and callbacks for this instance. */
    uint8_t model_instance_index;               /**< Model instance index. */
	  uint8_t * p_dtt_ms;        /**< point to the default transition time*/
};


/**
 * Initializes Generic Level server.
 *
 * @note The server handles the model allocation and adding.
 *
 * @param[in]     p_server                 Generic Level server context pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t generic_level_server_init(generic_level_server_t * p_server, uint8_t element_offset);

/**
 * Publishes unsolicited Status message.
 *
 *
 * @param[in]     p_server                 Status server context pointer.
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
uint16_t generic_level_server_status_publish(generic_level_server_t * p_server, const generic_level_status_params_t * p_params);

                                             
 #endif /* __GENERIC_LEVEL_SERVER_H__ */

/** @} */
