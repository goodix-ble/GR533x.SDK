/**
 *****************************************************************************************
 *
 * @file harmony_mesh_server.h
 *
 * @brief Harmony mesh vendor  Server API.
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
#ifndef __HARMONY_MESH_SERVER_H__
#define __HARMONY_MESH_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "harmony_mesh_common.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/** Harmony mesh vendor Server model ID */
#define HARMONY_MESH_SERVER_MODEL_ID (0x0002)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/* Forward declaration */
typedef struct __harmony_mesh_server_t  harmony_mesh_server_t;

/**
 * Callback type for Harmony mesh vendor  Set/Set Unacknowledged message.
 *
 * @param[in]       model_instance_index      Model instance index.
 * @param[in]       attri_type                          harmony mesh attribute type to be used by the application.
 * @param[in]       attri_value                        harmony mesh attribute value to be used by the application.
 * @param[in]       value_len                          harmony mesh attribute value length to be used by the application.
 * @param[out]     p_out                               harmony mesh attribute value response to harmony gateway.
 * @param[out]     p_out_len                         harmony mesh attribute value length response to harmony gateway.
 */
typedef void (*harmony_mesh_state_set_cb_t)(uint8_t model_instance_index, uint16_t attri_type, uint8_t *attri_value, uint16_t value_len, uint8_t *p_out, uint16_t *p_out_len);

/**
 * Callback type for Harmony mesh vendor  Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]       attri_type                       harmony mesh attribute type to be used by the application.
 * @param[out]     p_out                             harmony mesh attribute value response to harmony gateway.
 * @param[out]     p_out_len                      harmony mesh attribute value length response to harmony gateway.
 */
typedef void (*harmony_mesh_state_get_cb_t)(uint8_t model_instance_index, uint16_t attri_type, uint8_t *p_out, uint16_t *p_out_len);

/**
 * Callback type for Harmony mesh vendor notify status message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     attri_type                         notify attribute type to be used by the application.
 */
typedef void (*harmony_mesh_state_change_notify_cb_t)(uint8_t model_instance_index, uint16_t attri_type);

/**
 * Transaction callbacks for the Harmony mesh state.
 */
typedef struct
{
    harmony_mesh_state_get_cb_t get_cb;                 /**< Callback for Harmony mesh vendor  Get message. */
    harmony_mesh_state_set_cb_t set_cb;                 /**< Callback for Harmony mesh vendor  Set/Set Unacknowledged message. */
    //harmony_mesh_state_set_cb_t set_unack_cb;     /**< Callback for Harmony mesh vendor  Set/Set Unacknowledged message. */
    //harmony_mesh_state_get_cb_t set_status_cb;     /**< Callback for Harmony mesh vendor  Get message. */
    //harmony_mesh_state_set_cb_t get_status_cb;     /**< Callback for Harmony mesh vendor  Set/Set Unacknowledged message. */
} harmony_mesh_server_state_cbs_t;

/**
 * Transaction callbacks for the Harmony mesh state.
 */
typedef struct
{
    //harmony_mesh_state_change_notify_cb_t change_notify_cb;                             /**< Callback for Harmony mesh vendor  Set/Set Unacknowledged message. */
    //harmony_mesh_state_change_notify_cb_t change_notify_unack_cb;                 /**< Callback for Harmony mesh vendor  Set/Set Unacknowledged message. */
    harmony_mesh_state_change_notify_cb_t change_notify_status_cb;                  /**< Callback for Harmony mesh vendor  notify status message. */
} harmony_mesh_server_state_change_cbs_t;

/**
 * Harmony mesh vendor  Server callback list.
 */
typedef struct
{
    harmony_mesh_server_state_cbs_t state_cbs;  /**< Callback list for Harmony mesh Server. */
    harmony_mesh_server_state_change_cbs_t state_change_cbs;  /**< Callback list for Harmony mesh Server. */
} harmony_mesh_server_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    const harmony_mesh_server_callbacks_t *p_callbacks;     /**< User provided callback for this model. */
} harmony_mesh_server_settings_t;

/** Structure for tracking TID expiry for the models */
typedef struct
{
    uint16_t src;               /**< Source address */
    uint8_t old_tid;            /**< Previously received TID */
    bool new_transaction;       /**< New transaction indicator flag */
} tid_filter_t;

/**
 * Harmony mesh vendor  Server model information.
 */
struct __harmony_mesh_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    tid_filter_t tid_filter;                    /**< Tid tracker. */
    mesh_timer_t harmony_mesh_timer;            /**< mesh timer instance. */
    void *timer_msg;
    harmony_mesh_server_settings_t settings;    /**< Settings for this model instance. */
    uint16_t client_address;                    /**< The address message received. */
    uint8_t model_instance_index;               /**< Model instance index. */
};

/**
 * Initializes Harmony mesh vendor  Server model.
 *
 * @param[in]     p_server                     harmony mesh server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command is disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t harmony_mesh_server_init(harmony_mesh_server_t *p_server, uint8_t element_offset);

/**
 * Harmony mesh vendor  Server publishes unsolicited Status message without ack.
 *
 * @param[in]     p_server                  harmony mesh server information pointer.
 * @param[in]     tid                       Transaction Identifier.
 * @param[in]     attri_type                harmony mesh attribute type to be used by the application.
 * @param[in]     p_out                     harmony mesh attribute value to harmony gateway.
 * @param[in]     p_out_len                 harmony mesh attribute value length .
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
uint16_t harmony_mesh_server_status_notify_without_ack(harmony_mesh_server_t * p_server, const uint8_t tid, const uint16_t attri_type, uint8_t *p_out, uint16_t p_out_len);


/**
 * Harmony mesh vendor  Server publishes unsolicited Status message with ack.
 *
 * @param[in]     p_server                  harmony mesh server information pointer.
 * @param[in]     tid                       Transaction Identifier.
 * @param[in]     attri_type                harmony mesh attribute type to be used by the application.
 * @param[in]     p_out                     harmony mesh attribute value to harmony gateway.
 * @param[in]     p_out_len                 harmony mesh attribute value length .
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
uint16_t harmony_mesh_server_status_notify_with_ack(harmony_mesh_server_t * p_server, const uint8_t tid, const uint16_t attri_type, uint8_t *p_out, uint16_t p_out_len);


#endif /* __HARMONY_MESH_SERVER_H__ */

/** @} */

