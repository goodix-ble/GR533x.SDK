/**
 *****************************************************************************************
 *
 * @file app_power_onoff_server.h
 *
 * @brief APP Power OnOff API.
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
#ifndef __APP_POWER_ONOFF_SERVER_H__
#define __APP_POWER_ONOFF_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "generic_power_onoff_server.h"


#define GENERIC_POWER_ONOFF_SERVER_INSTANCE_COUNT (2)    // should no more than GENERIC_POWER_ONOFF_SERVER_INSTANCE_COUNT_MAX

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Internal structure to hold state information. */
typedef struct
{
    uint8_t on_power_up;             /**< Present value of the On Power Up state. */
} app_power_onoff_state_t;


/**
 * Application callback type for Generic Power OnOff Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[out]    p_on_power_up             Application fills this value with the value retrived from the hardware interface.
 */
typedef void (*app_generic_power_onoff_get_cb_t)(uint8_t model_instance_index, uint8_t * p_on_power_up);

/**
 * Application Generic Power OnOff Setup Server model information.
 */
 typedef struct
 {
    generic_power_onoff_server_t server;                    /**< Generic Power OnOff Server model information. */
    app_generic_power_onoff_get_cb_t power_onoff_get_cb;    /**< Callback to be called for requesting current value from the user application */
    app_power_onoff_state_t state;                          /**< Internal variableto to hold state */
    uint16_t client_address;                                /**< The address message received. */
    bool value_updated;                                     /**< Internal variable. To flag if the received message has been processed to update the On Power Up value */
 } app_power_onoff_server_t;

/**
 * Initializes Application Generic Power OnOff Setup Server model.
 *
 * @param[in]     p_server                 Application Generic Power OnOff Setup server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     get_cb                   Application Generic Power OnOff server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_generic_power_onoff_server_init(app_power_onoff_server_t *p_server,
                                             uint8_t element_offset, 
                                             app_generic_power_onoff_get_cb_t get_cb);

/**
 * Application Generic Power OnOff Setup Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Generic Power OnOff server information pointer.
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
uint16_t app_generic_power_onoff_status_publish(app_power_onoff_server_t * p_server);

#endif /* __APP_POWER_ONOFF_SERVER_H__ */

/** @} */

