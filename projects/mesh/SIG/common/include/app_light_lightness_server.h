/**
 *****************************************************************************************
 *
 * @file app_light_lightness_server.h
 *
 * @brief App Light Lightness API.
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
#ifndef __APP_LIGHT_LIGHTNESS_SERVER_H__
#define __APP_LIGHT_LIGHTNESS_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "light_lightness_server.h"


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */
//#define MESH_MODEL_BQB_TEST
#define LIGHT_LIGHTNESS_INSTANCE_COUNT (1)    // should no more than LIGHT_LIGHTNESS_SERVER_INSTANCE_COUNT_MAX

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef struct
{
    uint16_t present_ln;                    /**< Present value of the Light Lightness Actual state. */
    uint16_t present_ln_linear;         /**< Present value of the Light Lightness Linear state. */
    uint16_t target_ln;                       /**< Target value of the Light Lightness Actual state, as received from the model interface. */
    uint16_t target_ln_linear;          /**< Target value of the Light Lightness Linear state, as received from the model interface. */
    uint16_t last_ln;                           /**< Value of the Light Lightness Last state. */
    uint16_t default_ln;                     /**< Value of the Light Lightness Default state. */
    uint8_t status_code;
    uint16_t min_ln;                           /**< Value of the Light Lightness Range Min state. */
    uint16_t max_ln;                          /**< Value of the Light Lightness Range Max state. */
}light_ln_state_t;

/** Internal structure to hold state and timing information. */
typedef struct
{
        /// Delta value in case of move transition
    //int16_t move_delta;
    light_ln_state_t state;

    uint32_t actual_remaining_time_ms;      /**< Remaining time to reach `target lightness actual`. */
    uint32_t actual_delay_ms;               /**< Time to delay the processing of received lightness actual SET message. */
    uint32_t linear_remaining_time_ms;      /**< Remaining time to reach `target lightness linear`. */
    uint32_t linear_delay_ms;               /**< Time to delay the processing of received lightness linear SET message. */
} app_light_lightness_state_t;

/**
 * Application callback type for Light Lightness Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     ln_state                          lightness state to be used by the application.
 */
typedef void (*app_light_ln_set_cb_t)(uint8_t model_instance_index, light_ln_state_t *ln_state);

/**
 * Application callback type for Light Lightness Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[out]   ln_state                          lightness state.
 */
typedef void (*app_light_ln_get_cb_t)(uint8_t model_instance_index, light_ln_state_t *ln_state);

/**
 * Application Light Lightness Server model information.
 */
 typedef struct
 {
    light_ln_server_t server;                           /**< Light Lightness Server model information. */
    mesh_timer_t actual_state_timer;           /**< actual state timer instance. */
    mesh_timer_t linear_state_timer;            /**< linear state timer instance. */
    app_light_ln_set_cb_t light_ln_set_cb;     /**< Callback to be called for informing the user application to update the value*/
    app_light_ln_get_cb_t light_ln_get_cb;    /**< Callback to be called for requesting current value from the user application */

    app_light_lightness_state_t state;             /**< Internal variableto to hold state and timing information */

    uint32_t actual_last_time_clock_ms;                /**< Internal variable. It is used for acquiring last time value. */
    uint16_t actual_last_time_nb_wrap;                 /**< Internal variable. It is used for acquiring last time value. */
    uint32_t linear_last_time_clock_ms;                /**< Internal variable. It is used for acquiring last time value. */
    uint16_t linear_last_time_nb_wrap;                 /**< Internal variable. It is used for acquiring last time value. */

    uint16_t client_address;                        /**< The address message received. */

    bool value_updated;                             /**< Internal variable. To flag if the received message has been processed to update the lightness value */
 } app_light_lightness_server_t;

/**
 * Initializes Application Light Lightness Server model.
 *
 * @param[in]     p_server                 Application Light Lightness server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     set_cb                   Application Light Lightness server setting callback.
 * @param[in]     get_cb                   Application Light Lightness server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_light_ln_server_init(app_light_lightness_server_t *p_server, uint8_t element_offset, app_light_ln_set_cb_t set_cb, app_light_ln_get_cb_t get_cb);

/**
 * Application Light Lightness Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Light Lightness server information pointer.
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
uint16_t app_light_ln_status_publish(app_light_lightness_server_t * p_server);

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

#endif /* __APP_LIGHT_LIGHTNESS_SERVER_H__ */

/** @} */

