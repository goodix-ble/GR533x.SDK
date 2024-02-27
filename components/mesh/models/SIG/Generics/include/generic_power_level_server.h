/**
 *****************************************************************************************
 *
 * @file generic_power_level_server.h
 *
 * @brief Generic Power Level Server API.
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
#ifndef __GENERIC_POWER_LEVEL_SERVER_H__
#define __GENERIC_POWER_LEVEL_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "model_common.h"
#include "generic_power_level_common.h"
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
typedef struct __generic_power_level_server_t  generic_power_level_server_t;

/* Forward declaration */
typedef struct __generic_power_level_setup_server_t  generic_power_level_setup_server_t;

/**
 * Callback type for Generic Power Level Set/Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the Power Level server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[in]     p_in_transition          Pointer to optional transition parameters, if present in the incoming message.
 *                                         Otherwise, set to NULL.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*generic_power_level_state_set_cb_t)(generic_power_level_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const generic_power_level_set_params_t * p_in,
                                                    const model_transition_t * p_in_transition,
                                                    generic_power_level_status_params_u * p_out);


/**
 * Callback type for Generic Power Level Get message.
 *
 * @param[in]     p_self                   Pointer to the Power Level server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 */
typedef void (*generic_power_level_state_get_cb_t)(generic_power_level_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    generic_power_level_status_params_u * p_out);

/**
 * Callback type for Generic Power Level Setup Set/Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the Power Level server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[in]     p_in_transition          Pointer to optional transition parameters, if present in the incoming message.
 *                                         Otherwise, set to NULL.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*generic_power_level_state_setup_cb_t)(generic_power_level_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const generic_power_level_setup_params_t * p_in,
                                                    const model_transition_t * p_in_transition,
                                                    generic_power_level_status_params_u * p_out);

/**
 * Transaction callbacks for the Generic Power Level state.
 */
typedef struct
{
    generic_power_level_state_set_cb_t set_cb;        /**< Callback for Generic Power Level Set/Set Unacknowledged message. */
    generic_power_level_state_get_cb_t get_cb;        /**< Callback for Generic Power Level Get message. */
} generic_power_level_state_cbs_t;


typedef struct
{
    generic_power_level_state_get_cb_t get_cb;        /**< Callback for Generic Power Level Last Get message. */
} generic_power_level_last_state_cbs_t;

typedef struct
{
    generic_power_level_state_setup_cb_t set_cb;        /**< Callback for Generic Power Level Default Set/Set Unacknowledged message. */
    generic_power_level_state_get_cb_t get_cb;        /**< Callback for Generic Power Level Default Get message. */
} generic_power_level_dft_state_cbs_t;

typedef struct
{
    generic_power_level_state_setup_cb_t set_cb;        /**< Callback for Generic Power Level Range Set/Set Unacknowledged message. */
    generic_power_level_state_get_cb_t get_cb;        /**< Callback for Generic Power Level Range Get message. */
} generic_power_level_range_state_cbs_t;

/**
 * Generic Power Level Server callback list.
 */
typedef struct
{
    generic_power_level_state_cbs_t generic_power_level_cbs;                                      /**< Callback list for Generic Power Level state. */
    generic_power_level_last_state_cbs_t generic_power_level_last_cbs;                      /**< Callback list for Generic Power Level Last state. */
    generic_power_level_dft_state_cbs_t generic_power_level_dft_cbs;                         /**< Callback list for Generic Power Level Default state. */
    generic_power_level_range_state_cbs_t generic_power_level_range_cbs;                /**< Callback list for Generic Power Level Range state. */
} generic_power_level_server_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    const generic_power_level_server_callbacks_t *p_callbacks;    /**< User provided callback for this model. */
} generic_power_level_server_settings_t;

/**
 * Generic Power Level Server model information.
 */
struct __generic_power_level_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    tid_tracker_t tid_tracker;                  /**< Tid tracker. */
    generic_power_level_server_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */

    uint8_t * p_dtt_ms;        /**< point to the default transition time*/
};

/**
 * Generic Power Level Setup Server model information.
 */
struct __generic_power_level_setup_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    generic_power_level_server_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */
    generic_power_level_server_t *lvl_server;
};

/**
 * Initializes Generic Power Level Server model.
 *
 * @param[in]     p_server                 Generic Power Level server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t generic_power_level_server_init(generic_power_level_server_t *p_server, uint8_t element_offset);

/**
 * Generic Power Level Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Generic Power Level server information pointer.
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
 * @retval ::MESH_ERROR_NOT_FOUND                 Resource requested not found.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_ON     Reliable message transfer procedure is on.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 */
uint16_t generic_power_level_server_status_publish(generic_power_level_server_t * p_server, 
                                             const generic_power_level_status_params_t * p_params);

#endif /* __GENERIC_POWER_LEVEL_SERVER_H__ */

/** @} */

