/**
 *****************************************************************************************
 *
 * @file app_power_onoff_setup_server.h
 *
 * @brief APP Power OnOff Setup API.
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
#ifndef __APP_POWER_ONOFF_SETUP_SERVER_H__
#define __APP_POWER_ONOFF_SETUP_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "app_power_onoff_server.h"
#include "generic_power_onoff_setup_server.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */


/**
 * Application callback type for Generic Power OnOff Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     onoff                     On Off state to be used by the application.
 */
typedef void (*app_generic_power_onoff_set_cb_t)(uint8_t model_instance_index, uint8_t on_power_up);



/**
 * Application Generic Power OnOff Setup Server model information.
 */
typedef struct
{
    /**< Generic Power OnOff Setup Server model information. */
    generic_power_onoff_setup_server_t server;
    
    /**< Callback to be called for informing the user application to update the value*/
    app_generic_power_onoff_set_cb_t power_onoff_set_cb_t;
    
    app_power_onoff_state_t *state;                  /**< Internal variableto to hold state */
    uint16_t client_address;                        /**< The address message received. */
    
    /**< Internal variable. To flag if the received message has been processed to update the On Power Up value */
    bool value_updated;                             
} app_power_onoff_setup_server_t;

/**
 * Initializes Application Generic Power OnOff Setup Server model.
 *
 * @param[in]     p_server                 Application Generic Power OnOff Setup server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     set_cb                   Application Generic Power OnOff Setup server setting callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_generic_power_onoff_setup_server_init(app_power_onoff_setup_server_t *p_server,
                                                   uint8_t element_offset, 
                                                   app_generic_power_onoff_set_cb_t set_cb);

#endif /* __APP_POWER_ONOFF_SERVER_H__ */

/** @} */

