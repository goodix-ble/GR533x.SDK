/**
 *****************************************************************************************
 *
 * @file app_scene_server.h
 *
 * @brief App Scene API.
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
#ifndef __APP_MESH_SCENE_SERVER_H__
#define __APP_MESH_SCENE_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "scene_server.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

#define TSCNS_SCENE_SERVER_INSTANCE_COUNT (3)    // should no more than TSCNS_SCENE_SERVER_INSTANCE_COUNT_MAX

#define APP_SCENE_ZONE_OFFSET_MIN          (-64)
#define APP_SCENE_ZONE_OFFSET_MAX          (191)

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Internal structure to hold state and timing information. */
typedef struct
{
    uint8_t status_code;                                 /**<The Status Code field identifies the status code for the last operation */
    uint16_t current_scene;                           /**< Scene Number of a current scene. */
    uint16_t target_scene;                             /**< Scene Number of a target scene.  */
    uint32_t remaining_time_ms;                  /**< Remaining time to reach `target_onoff`. */
    uint32_t delay_ms;                                  /**< Time to delay the processing of received SET message. */

    //uint16_t scene_cnt;                                 /**< Scene Number count of scenes list . */
    //uint16_t scene[];                                     /**< A list of scenes stored within an element. */
} app_scene_state_t;

/**
 * Application callback type for mesh scene state Get message.
 *
 * @param[in]       model_instance_index      Model instance index.
 * @param[out]     current_scene                 Returen the current scene number of an element if not NULL.
 */
typedef void (*app_scene_get_cb_t)(uint8_t model_instance_index, uint16_t *current_scene);

/**
 * Application callback type for mesh scene change event.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     current_scene                 the Scene Number of the currently active scene.
 */
typedef void (*app_scene_set_cb_t)(uint8_t model_instance_index, uint16_t current_scene);

/**
 * Application callback type for mesh scene Store/Store Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     current_scene                 the Scene Number of the currently active scene.
 */
typedef void (*app_scene_setup_store_cb_t)(uint8_t model_instance_index, uint16_t current_scene);

/**
 * Application callback type for   mesh scene Delete message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     current_scene                  the Scene Number of the currently active scene.
 * @param[in]     delete_scene                   the Scene Number of to be deleted.
 * @param[in]     delete_result                  the result of delete the scene.
 */
typedef void (*app_scene_setup_delete_cb_t)(uint8_t model_instance_index, uint16_t current_scene, uint16_t delete_scene, uint16_t delete_result);

/**
 * Application   mesh scene Server model information.
 */
 typedef struct
 {
    mesh_scene_server_t server;                                      /**<   mesh scene Server model information. */
    mesh_timer_t scene_state_timer;                 /**< Scene state timer instance. */
    app_scene_get_cb_t scene_get_cb;                               /**< Callback to be called for informing the user application to update the value*/
    app_scene_set_cb_t scene_set_cb;                              /**< Callback to be called for requesting current value from the user application */

    app_scene_state_t state;                                             /**< Internal variableto to hold state and timing information */

    uint32_t scene_last_time_clock_ms;                /**< Internal variable. It is used for acquiring last time value. For scene state*/
    uint16_t scene_last_time_nb_wrap;                 /**< Internal variable. It is used for acquiring last time value. For scene state*/

    uint16_t client_address;            /**< The address message received. */

    bool value_updated;                             /**< Internal variable. To flag if the received message has been processed to update the scene value */
} app_scene_server_t;

/**
 * Initializes Application   mesh scene Server model.
 *
 * @param[in]     p_server                    Application   Mesh Scene server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     get_cb                       Application   Mesh Scene server get callback.
 * @param[in]     recall_cb                    Application   Mesh Scene server recall callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_scene_server_init(app_scene_server_t *p_server, uint8_t element_offset, app_scene_get_cb_t get_cb, app_scene_set_cb_t recall_cb);

/**
 * Application   mesh scene Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application  Mesh Scene server information pointer.
 *
 */
uint16_t app_scene_status_publish(app_scene_server_t * p_server);
uint16_t app_scene_register_status_publish(app_scene_server_t * p_server);

#endif /* __APP_MESH_SCENE_SERVER_H__ */

/** @} */

