/**
 *****************************************************************************************
 *
 * @file generic_power_onoff_setup_server.h
 *
 * @brief Generic Power OnOff Setup Server API.
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
#ifndef __GENERIC_POWER_ONOFF_SETUP_SERVER_H__
#define __GENERIC_POWER_ONOFF_SETUP_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "model_common.h"
#include "generic_power_onoff_common.h"
#include "generic_power_onoff_server.h"
#include "generic_dtt_server.h"
#include "generic_power_onoff_setup_server.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/** Generic Power OnOff Setup Server model ID */
#define MODEL_ID_GENS_POOS (0x1007)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/* Forward declaration */
typedef struct __generic_power_onoff_setup_server_t  generic_power_onoff_setup_server_t;

/**
 * Callback type for Generic Power OnOff Setup Set/Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the generic power onoff setup server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*generic_power_onoff_state_set_cb_t)(generic_power_onoff_setup_server_t  * p_self,
                                                   const mesh_model_msg_ind_t *p_rx_msg,
                                                   const generic_power_onoff_set_params_t * p_in,                                                  
                                                   generic_power_onoff_status_params_t * p_out);


/**
 * Transaction callbacks for the Generic On Off state.
 */
typedef struct
{
    /**< Callback for Generic Power OnOff Setup Set/Set Unacknowledged message. */  
    generic_power_onoff_state_set_cb_t set_cb;        
} generic_power_onoff_setup_server_state_cbs_t;

/**
 * Generic On Off Server callback list.
 */
typedef struct
{
    generic_power_onoff_setup_server_state_cbs_t power_onoff_cbs;     /**< Callback list for Generic Power OnOff Setup Server. */
} generic_power_onoff_setup_server_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    const generic_power_onoff_setup_server_callbacks_t *p_callbacks;    /**< User provided callback for this model. */
} generic_power_onoff_setup_server_settings_t;

/**
 * Generic Power OnOff Setup Server model information.
 */
struct __generic_power_onoff_setup_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    generic_power_onoff_setup_server_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */
    generic_power_onoff_server_t *power_server;
};

/**
 * Initializes Generic Power OnOff Setup Server model.
 *
 * @param[in]     p_server                 Generic Power OnOff Setup server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t generic_power_onoff_setup_server_init(generic_power_onoff_setup_server_t *p_server, uint8_t element_offset);


/**
 * Generic Power OnOff Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Generic Power OnOff Setup server information pointer.
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
uint16_t generic_power_onoff_setup_server_status_publish(generic_power_onoff_setup_server_t * p_server, 
                                                         const generic_power_onoff_status_params_t * p_params);

#endif /* __GENERIC_POWER_ONOFF_SETUP_SERVER_H__ */

/** @} */

