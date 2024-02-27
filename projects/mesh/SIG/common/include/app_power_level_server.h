/**
 *****************************************************************************************
 *
 * @file app_power_level_server.h
 *
 * @brief App Power Level Server API.
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
#ifndef __APP_POWER_LEVEL_SERVER_H__
#define __APP_POWER_LEVEL_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "generic_power_level_server.h"


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

#define GENERIC_POWER_LEVEL_SERVER_INSTANCE_COUNT (1)    // should no more than GENERIC_POWER_LEVEL_SERVER_INSTANCE_COUNT_MAX

//#define MESH_MODEL_BQB_TEST
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef struct
{
    uint16_t present_power;                    /**< Present value of the Generic Power Level Actual state. */
    uint16_t target_power;                       /**< Target value of the Generic Power Level Actual state, as received from the model interface. */
    uint16_t last_power;                           /**< Value of the Generic Power Level Last state. */
    uint16_t default_power;                     /**< Value of the Generic Power Level Default state. */
    uint8_t status_code;
    uint16_t min_power;                           /**< Value of the Generic Power Level Range Min state. */
    uint16_t max_power;                          /**< Value of the Generic Power Level Range Max state. */
}generic_power_level_state_t;

/** Internal structure to hold state and timing information. */
typedef struct
{
    generic_power_level_state_t state;
    uint32_t remaining_time_ms;      /**< Remaining time to reach `target power`. */
    uint32_t delay_ms;                       /**< Time to delay the processing of received SET message. */
} app_generic_power_level_state_t;

/**
 * Application callback type for Generic Power Level Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     power_state               power state to be used by the application.
 */
typedef void (*app_generic_power_level_set_cb_t)(uint8_t model_instance_index, generic_power_level_state_t *power_state);

/**
 * Application callback type for Generic Power Level Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[out]    power_state           Application fills this value with the value retrived from the hardware interface.
 */
typedef void (*app_generic_power_level_get_cb_t)(uint8_t model_instance_index, generic_power_level_state_t *power_state);

/**
 * Application Generic Power Level Server model information.
 */
 typedef struct
 {
    generic_power_level_server_t server;                           /**< Generic Power Level Server model information. */
    mesh_timer_t actual_state_timer;           /**< actual state timer instance. */
    app_generic_power_level_set_cb_t generic_power_level_set_cb;     /**< Callback to be called for informing the user application to update the value*/
    app_generic_power_level_get_cb_t generic_power_level_get_cb;    /**< Callback to be called for requesting current value from the user application */

    app_generic_power_level_state_t app_state;             /**< Internal variableto to hold state and timing information */

    uint32_t actual_last_time_clock_ms;                /**< Internal variable. It is used for acquiring last time value. */
    uint16_t actual_last_time_nb_wrap;                 /**< Internal variable. It is used for acquiring last time value. */
     
    uint16_t client_address;                        /**< The address message received. */

    bool value_updated;                             /**< Internal variable. To flag if the received message has been processed to update the present OnOff value */
 } app_generic_power_level_server_t;

/**
 * Initializes Application Generic Power Level Server model.
 *
 * @param[in]     p_server                 Application Generic Power Level server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     set_cb                   Application Generic Power Level server setting callback.
 * @param[in]     get_cb                   Application Generic Power Level server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_generic_power_level_server_init(app_generic_power_level_server_t *p_server, uint8_t element_offset, 
                                             app_generic_power_level_set_cb_t set_cb, app_generic_power_level_get_cb_t get_cb);

/**
 * Application Generic Power Level Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Generic Power Level server information pointer.
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
uint16_t app_generic_power_level_status_publish(app_generic_power_level_server_t * p_server);

/**
 ****************************************************************************************
 * @brief Compure integer square root
 *
 * @param[in] n     Value
 *
 * @return Integer square root of n
 ****************************************************************************************
 */
uint32_t gx_lights_isqrt(uint32_t n);


#endif /* __APP_POWER_LEVEL_SERVER_H__ */

/** @} */

