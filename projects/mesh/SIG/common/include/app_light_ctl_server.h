/**
 *****************************************************************************************
 *
 * @file app_light_ctl_server.h
 *
 * @brief App Light CTL API.
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
#ifndef __APP_LIGHT_CTL_SERVER_H__
#define __APP_LIGHT_CTL_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "light_ctl_server.h"


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */
//#define MESH_MODEL_BQB_TEST

#define LIGHT_CTL_INSTANCE_COUNT (4)    // should no more than LIGHT_CTL_SERVER_INSTANCE_COUNT_MAX

/// Convert Generic Level value into Light CTL temperature value
/// Light CTL Temperature = T_MIN + (Generic Level + 32768) * (T_MAX - T_MIN) / 65535
#define CV_LIGHTS_CTL_TEMP(T_MIN, T_MAX, level)                     \
        (T_MIN + (level+32768)*(T_MAX-T_MIN)/65535)

/// Convert Light CTL temperature value into Generic Level value
/// Generic Level = (Light CTL Temperature - T _MIN) * 65535 / (T_MAX - T_MIN) - 32768
#define CV_GENS_LVL(T_MIN, T_MAX, temperature)                     \
        ((temperature-T_MIN)*65535/(T_MAX-T_MIN) - 32768)


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef struct
{
    uint16_t present_ctl_ln;                    /**< Present value of the Light CTL lightness  state. */
    uint16_t present_ctl_temp;               /**< Present value of the Light CTL temperature  state. */
    int16_t present_ctl_dlt_uv;           /**< Present value of the Light CTL Delta UV  state. */
}light_ctl_present_state_t;

typedef struct
{
    uint16_t target_ctl_ln;                     /**< Target value of the Light CTL lightness state, as received from the model interface. */
    uint16_t target_ctl_temp;                 /**< Target value of the Light CTL temperature state, as received from the model interface. */
    int16_t target_ctl_dlt_uv;             /**< Target value of the Light CTL Delta UV  state. */
}light_ctl_target_state_t;

typedef struct
{
    uint16_t default_ln;                         /**< Value of the Light CTL Default state. */
    uint16_t default_temp;                    /**< The value of the Light CTL Temperature Default state. */
    int16_t default_dlt_uv;                  /**< The value of the Light CTL Delta UV Default state. */
}light_ctl_dft_state_t;

typedef struct
{
//    uint8_t status_ccode;                      /**< Status Code for the requesting message. */
    uint16_t range_min;                        /**< Value of the Light CTL temperature Range Min state. */
    uint16_t range_max;                        /**< Value of the Light CTL temperature Range Max state. */
}light_ctl_temp_range_state_t;

/** Internal structure to hold state and timing information. */
typedef struct
{
        /// Delta value in case of move transition
    //int16_t move_delta;
    light_ctl_present_state_t present_state;
    light_ctl_target_state_t target_state;
    light_ctl_dft_state_t dft_state;
    light_ctl_temp_range_state_t temp_range;

    uint32_t ctl_remaining_time_ms;      /**< Remaining time to reach `target ctl`. */
    uint32_t ctl_delay_ms;                       /**< Time to delay the processing of received SET message. */
    uint32_t temp_remaining_time_ms;      /**< Remaining time to reach `target temperature`. */
    uint32_t temp_delay_ms;                       /**< Time to delay the processing of received SET message. */
} app_light_ctl_state_t;

/**
 * Application callback type for Light CTL Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     ctl_state                          ctl state to be used by the application.
 * @param[in]     dft_state                          ctl default state to be used by the application.
 * @param[in]     temp_state                      ctl temperature state to be used by the application.
 */
typedef void (*app_light_ctl_set_cb_t)(uint8_t model_instance_index, light_ctl_present_state_t *ctl_state, light_ctl_dft_state_t *dft_state, light_ctl_temp_range_state_t *temp_state);

/**
 * Application callback type for Light CTL Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     ctl_state                          ctl state to be used by the application.
 * @param[in]     dft_state                          ctl default state to be used by the application.
 * @param[in]     temp_state                      ctl temperature state to be used by the application.
 */
typedef void (*app_light_ctl_get_cb_t)(uint8_t model_instance_index, light_ctl_present_state_t *ctl_state, light_ctl_dft_state_t *dft_state, light_ctl_temp_range_state_t *temp_state);

/**
 * Application Light CTL Server model information.
 */
 typedef struct
 {
    light_ctl_server_t server;                           /**< Light CTL Server model information. */
    mesh_timer_t ctl_state_timer;                 /**< CTL state timer instance. */
    app_light_ctl_set_cb_t light_ctl_set_cb;     /**< Callback to be called for informing the user application to update the value*/
    app_light_ctl_get_cb_t light_ctl_get_cb;    /**< Callback to be called for requesting current value from the user application */

    app_light_ctl_state_t state;             /**< Internal variableto to hold state and timing information */

    uint32_t ctl_last_time_clock_ms;                /**< Internal variable. It is used for acquiring last time value. For CTL state*/
    uint16_t ctl_last_time_nb_wrap;                 /**< Internal variable. It is used for acquiring last time value. For CTL state*/

    uint16_t client_address;                        /**< The address message received. */

    bool value_updated;                             /**< Internal variable. To flag if the received message has been processed to update the ctl value */
 } app_light_ctl_server_t;

/**
 * Initializes Application Light CTL Server model.
 *
 * @param[in]     p_server                 Application Light CTL server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     set_cb                   Application Light CTL server setting callback.
 * @param[in]     get_cb                   Application Light CTL server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_light_ctl_server_init(app_light_ctl_server_t *p_server, uint8_t element_offset, app_light_ctl_set_cb_t set_cb, app_light_ctl_get_cb_t get_cb);

/**
 * Application Light CTL Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Light CTL server information pointer.
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
uint16_t app_light_ctl_status_publish(app_light_ctl_server_t * p_server);

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

#endif /* __APP_LIGHT_CTL_SERVER_H__ */

/** @} */

