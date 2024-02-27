/**
 *****************************************************************************************
 *
 * @file app_light_HSL_server.h
 *
 * @brief App Light HSL Server API.
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
#ifndef __APP_LIGHT_HSL_SERVER_H__
#define __APP_LIGHT_HSL_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "light_HSL_server.h"


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */
//#define MESH_MODEL_BQB_TEST

#define FORMAT_VALUE_RANGE(value, max, min) ((value) = ((value) > (max)) ? (max) : (((value) < (min)) ? (min):(value)))
/*The HSL model need at least three element*/
#define LIGHT_HSL_INSTANCE_COUNT (3)    // should no more than LIGHT_HSL_SERVER_INSTANCE_COUNT_MAX

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef struct
{
    uint16_t present_hue;                    /**< Present value of the Light HSL Hue state. */
    uint16_t present_stt;                    /**< Present value of the Light HSL Saturation state. */
    uint16_t present_ln;                     /**< Present value of the Light HSL Lightness state. */
}light_HSL_present_state_t;

typedef struct
{
    uint16_t target_hue;                    /**< Target value of the Light HSL Hue state. */
    uint16_t target_stt;                    /**< Target value of the Light HSL Saturation state. */
    uint16_t target_ln;                     /**< Target value of the Light HSL Lightness state. */
}light_HSL_target_state_t;


typedef struct
{
    uint16_t dft_hue;                     /**< Value of the Light HSL Default Hue state. */
    uint16_t dft_stt;                     /**< Value of the Light HSL Default Saturation state. */
    uint16_t dft_ln;                     /**< Value of the Light HSL Default Lightness state. */
}light_HSL_dft_state_t;

typedef struct
{
    //uint8_t status_code;
    uint16_t min_hue;                           /**< Value of the Light HSL Hue Range Min state. */
    uint16_t max_hue;                           /**< Value of the Light HSL Hue Range Max state. */
    uint16_t min_stt;                           /**< Value of the Light HSL Saturation Range Min state. */
    uint16_t max_stt;                           /**< Value of the Light HSL Saturation Range Max state. */
}light_HSL_range_state_t;

typedef struct
{
    uint32_t delay_ms;
    uint32_t remaining_time_ms;
}light_HSL_time_state_t;


/** Internal structure to hold state and timing information. */
typedef struct
{
    light_HSL_present_state_t present_state;
    light_HSL_target_state_t  target_state;
    light_HSL_dft_state_t     dft_state;
    light_HSL_range_state_t   range_state;
    light_HSL_time_state_t HSL_time; /**< Transition time info of HSL Set*/
    light_HSL_time_state_t hue_time; /**< Transition time info of Hue Set*/
    light_HSL_time_state_t stt_time; /**< Transition time info of Saturation Set*/

} app_light_HSL_state_t;

/**
 * Application callback type for Light HSL Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     HSL_state                          HSL state to be used by the application.
 */
typedef void (*app_light_HSL_set_cb_t)(uint8_t model_instance_index, 
                                       light_HSL_present_state_t* HSL_state,
                                       light_HSL_dft_state_t* dft_state,
                                       light_HSL_range_state_t* range_state);

/**
 * Application callback type for Light HSL Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[out]   HSL_state                          HSL state.
 */
typedef void (*app_light_HSL_get_cb_t)(uint8_t model_instance_index, 
                                       light_HSL_present_state_t* HSL_state,
                                       light_HSL_dft_state_t* dft_state,
                                       light_HSL_range_state_t* range_state);

/**
 * Application Light HSL Server model information.
 */
 typedef struct
 {
    light_HSL_server_t server;                  /**< Light HSL Server model information. */
    mesh_timer_t HSL_state_timer;            /**< actual state timer instance. */
     
    app_light_HSL_set_cb_t light_HSL_set_cb;     /**< Callback to be called for informing the user application to update the value*/
    app_light_HSL_get_cb_t light_HSL_get_cb;     /**< Callback to be called for requesting current value from the user application */

    app_light_HSL_state_t state;             /**< Internal variableto to hold state and timing information */

    uint32_t HSL_last_time_clock_ms;           /**< Internal variable. It is used for acquiring last time value. */
    uint16_t HSL_last_time_nb_wrap;                 /**< Internal variable. It is used for acquiring last time value. */

    uint16_t client_address;                        /**< The address message received. */

    bool value_updated;                             /**< Internal variable. To flag if the received message has been processed to update the HSL value */
 } app_light_HSL_server_t;

/**
 * Initializes Application Light HSL Server model.
 *
 * @param[in]     p_server                 Application Light HSL server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     set_cb                   Application Light HSL server setting callback.
 * @param[in]     get_cb                   Application Light HSL server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_light_HSL_server_init(app_light_HSL_server_t *p_server, uint8_t element_offset, app_light_HSL_set_cb_t set_cb, app_light_HSL_get_cb_t get_cb);

/**
 * Application Light HSL Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Light HSL server information pointer.
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
uint16_t app_light_HSL_status_publish(app_light_HSL_server_t * p_server);

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

#endif /* __APP_LIGHT_HSL_SERVER_H__ */

/** @} */

