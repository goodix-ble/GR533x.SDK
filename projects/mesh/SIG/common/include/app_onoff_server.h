/**
 *****************************************************************************************
 *
 * @file app_onoff_server.h
 *
 * @brief App On Off API.
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
#ifndef __APP_ONOFF_SERVER_H__
#define __APP_ONOFF_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "generic_onoff_server.h"
#include "generic_power_onoff_behavior.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

#define GENERIC_ONOFF_SERVER_INSTANCE_COUNT (2)    // should no more than GENERIC_ONOFF_SERVER_INSTANCE_COUNT_MAX

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Internal structure to hold state and timing information. */
typedef struct
{
    bool present_onoff;             /**< Present value of the OnOff state. */
    bool target_onoff;              /**< Target value of the OnOff state, as received from the model interface. */
    uint32_t remaining_time_ms;     /**< Remaining time to reach `target_onoff`. */
    uint32_t delay_ms;              /**< Time to delay the processing of received SET message. */
} app_onoff_state_t;

/**
 * Application callback type for Generic On Off Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     onoff                     On Off state to be used by the application.
 */
typedef void (*app_generic_onoff_set_cb_t)(uint8_t model_instance_index, bool onoff);

/**
 * Application callback type for Generic On Off Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[out]     p_present_onoff           Application fills this value with the value retrived from the hardware interface.
 */
typedef void (*app_generic_onoff_get_cb_t)(uint8_t model_instance_index, bool * p_present_onoff);

/**
 * Store the bind state value callback.
 *
 * @param[in]     bind_instance_index     Bind state instance. Range in [0x00~0x0E]
 * @param[in]     state_enum              Bind state sequence number of an element. Range in [0x00~0x0E]
 * @param[in]     off_value               Bind state will be set to this value when power onoff equal to 0.
 * @param[in]     on_value                Bind state will be set to this value when power onoff equal to 1.
 * @param[in]     restore_value           Bind state will be set to this value when power onoff equal to 2.
 *
 * @retval ::NVDS_SUCCESS                            Operation is Success.
 * @retval ::NVDS_LENGTH_OUT_OF_RANGE      Store the bind state to flash faild, the bind_instance_index more than store support.
 * @retval ::NVDS_INVALID_PARA                    NVDS invalid params.
 */
typedef uint8_t (*store_power_status_cb_t)(uint16_t bind_instance_index, OnPowerUp_Bind_State_t state_enum, uint16_t off_value, uint16_t on_value, uint16_t restore_value);

/**
 * Application Generic On Off Server model information.
 */
 typedef struct
 {
    generic_onoff_server_t server;      /**< Generic On Off Server model information. */
    mesh_timer_t app_timer;             /**< APP timer instance. */
    app_generic_onoff_set_cb_t onoff_set_cb;    /**< Callback to be called for informing the user application to update the value*/
    app_generic_onoff_get_cb_t onoff_get_cb;    /**< Callback to be called for requesting current value from the user application */

    app_onoff_state_t state;            /**< Internal variableto to hold state and timing information */

    uint32_t last_time_clock_ms;        /**< Internal variable. It is used for acquiring last time value. */
    uint16_t last_time_nb_wrap;         /**< Internal variable. It is used for acquiring last time value. */

    uint16_t client_address;            /**< The address message received. */

    bool value_updated;                 /**< Internal variable. To flag if the received message has been processed to update the present OnOff value */
 } app_onoff_server_t;

/**
 * Initializes Application Generic On Off Server model.
 *
 * @param[in]     p_server                 Application Generic OnOff server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     set_cb                   Application Generic OnOff server setting callback.
 * @param[in]     get_cb                   Application Generic OnOff server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_generic_onoff_server_init(app_onoff_server_t *p_server, uint8_t element_offset, app_generic_onoff_set_cb_t set_cb, app_generic_onoff_get_cb_t get_cb);

/**
 * Application Generic On Off Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Generic OnOff server information pointer.
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
uint16_t app_generic_onoff_status_publish(app_onoff_server_t * p_server);

/**
 * Application Generic On Off Server register power onoff callback.
 *
 * @param[in]     cb                 Application Generic OnOff server power onoff callback.
 *
 */
void app_generic_onoff_store_power_cb_register(store_power_status_cb_t cb);

#endif /* __APP_ONOFF_SERVER_H__ */

/** @} */

