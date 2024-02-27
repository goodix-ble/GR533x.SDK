/**
 *****************************************************************************************
 *
 * @file generic_location_server.h
 *
 * @brief Generic Location Server API.
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
#ifndef __GENERIC_LOCATION_SERVER_H__
#define __GENERIC_LOCATION_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "model_common.h"
#include "generic_location_common.h"

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
typedef struct __generic_location_server_t  generic_location_server_t;

typedef struct __generic_location_setup_server_t  generic_location_setup_server_t;

/**
 * Callback type for Generic Location Get message.
 *
 * @param[in]     p_self                   Pointer to the generic Location server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 */
typedef void (*generic_location_state_get_cb_t)(generic_location_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    void * p_out);

/**
 * Callback type for Light Lightness Setup Set/Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the light lightness server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[in]     p_in_transition          Pointer to optional transition parameters, if present in the incoming message.
 *                                         Otherwise, set to NULL.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*generic_location_state_setup_cb_t)(generic_location_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const void * p_in,
                                                    void * p_out);

/**
 * Transaction callbacks for the Generic Location state.
 */
typedef struct
{
    generic_location_state_get_cb_t get_cb;        /**< Callback for Generic Location Get message. */
    generic_location_state_setup_cb_t set_global_cb;
    generic_location_state_setup_cb_t set_local_cb;
} generic_location_server_state_cbs_t;

/**
 * Generic Location Server callback list.
 */
typedef struct
{
    generic_location_server_state_cbs_t location_cbs;     /**< Callback list for Generic Location Setup Server. */
} generic_location_server_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    const generic_location_server_callbacks_t *p_callbacks;    /**< User provided callback for this model. */
} generic_location_server_settings_t;

/**
 * Generic Location Server model information.
 */
struct __generic_location_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    generic_location_server_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */
};

struct __generic_location_setup_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    generic_location_server_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */
    generic_location_server_t *location_server;
};

/**
 * Initializes Generic Location Server model.
 *
 * @param[in]     p_server                 Generic location server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t generic_location_server_init(generic_location_server_t *p_server, uint8_t element_offset);

/**
 * Generic Location Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Generic location server information pointer.
 * @param[in]     p_params               Status Message parameters.
 * @param[in]     global_flag              true : publish global status ; false : publish local status.
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
uint16_t generic_location_server_status_publish(generic_location_server_t * p_server, bool global_flag, const void * p_params);

/**
 * Initializes Generic Location Setup Server model.
 *
 * @param[in]     p_server                 Generic location server setup information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t generic_location_setup_server_init(generic_location_setup_server_t *p_server, uint8_t element_offset);
#endif /* __GENERIC_LOCATION_SERVER_H__ */

/** @} */

