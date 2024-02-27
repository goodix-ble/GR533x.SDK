/**
 *****************************************************************************************
 *
 * @file simple_onoff_server.h
 *
 * @brief Simple On Off Server API.
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
#ifndef __SIMPLE_ONOFF_SERVER_H__
#define __SIMPLE_ONOFF_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "simple_onoff_common.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/** Simple On Off Server model ID */
#define SIMPLE_ON_OFF_SERVER_MODEL_ID (0x1000)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/* Forward declaration */
typedef struct __simple_onoff_server_t  simple_onoff_server_t;

/**
 * Callback type for Simple On Off Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     onoff                     On Off state to be used by the application.
 */
typedef void (*simple_onoff_state_set_cb_t)(uint8_t model_instance_index, uint8_t onoff);

/**
 * Callback type for Simple On Off Get Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     p_present_onoff           Application fills this value with the value retrived from the hardware interface.
 */
typedef void (*simple_onoff_state_get_cb_t)(uint8_t model_instance_index, uint8_t * p_present_onoff);

typedef void (*simple_onoff_light_demo_set_cb_t)(uint8_t model_instance_index, light_demo_set_params_t *set_param);
/**
 * Transaction callbacks for the Generic On Off state.
 */
typedef struct
{
    simple_onoff_state_set_cb_t set_cb;     /**< Callback for Simple On Off Set/Set Unacknowledged message. */
    simple_onoff_state_get_cb_t get_cb;     /**< Callback for Simple On Off Get message. */
    simple_onoff_light_demo_set_cb_t light_demo_cb;
} simple_onoff_server_state_cbs_t;

/**
 * Simple On Off Server callback list.
 */
typedef struct
{
    simple_onoff_server_state_cbs_t onoff_cbs;  /**< Callback list for Generic On Off Server. */
} simple_onoff_server_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    const simple_onoff_server_callbacks_t *p_callbacks;     /**< User provided callback for this model. */
} simple_onoff_server_settings_t;

/** Structure for tracking TID expiry for the models */
typedef struct
{
    uint16_t src;               /**< Source address */
    uint8_t old_tid;            /**< Previously received TID */
    bool new_transaction;       /**< New transaction indicator flag */
} tid_filter_t;

/**
 * Simple On Off Server model information.
 */
struct __simple_onoff_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    tid_filter_t tid_filter;                    /**< Tid tracker. */
    simple_onoff_server_settings_t settings;    /**< Settings for this model instance. */
    uint16_t client_address;                    /**< The address message received. */
    uint8_t model_instance_index;               /**< Model instance index. */
    mesh_timer_t light_demo_timer;                 /**< Light demo timer instance. */
};

/**
 * Initializes Simple On Off Server model.
 *
 * @param[in]     p_server                 Simple OnOff server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command is disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t simple_onoff_server_init(simple_onoff_server_t *p_server, uint8_t element_offset);

/**
 * Simple On Off Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Simple OnOff server information pointer.
 * @param[in]     p_params                 Status Message parameters.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is Success.
 * @retval ::MESH_ERROR_INVALID_PARAM             Invalid parameter.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES    Insufficient resources.
 * @retval ::MESH_ERROR_INVALID_MODEL             Invalid model.
 * @retval ::MESH_ERROR_INVALID_PUBLISH_PARAMS    Invalid publish parameters.
 * @retval ::MESH_ERROR_INVALID_BINDING           Invalid binding.
 * @retval ::MESH_ERROR_INVALID_APPKEY_ID         Invalid application key index.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED        Command is disallowed.
 * @retval ::MESH_ERROR_NOT_FOUND                 Requested resource not found.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_ON     Reliable message transfer procedure is on.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 */
uint16_t simple_onoff_server_status_publish(simple_onoff_server_t * p_server, const simple_onoff_status_msg_pkt_t * p_params);

uint16_t light_demo_server_status_publish(simple_onoff_server_t * p_server, const light_demo_set_msg_pkt_t * p_params);

#endif /* __SIMPLE_ONOFF_SERVER_H__ */

/** @} */

