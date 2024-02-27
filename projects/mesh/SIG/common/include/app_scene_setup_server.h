/**
 *****************************************************************************************
 *
 * @file app_scene_setup_server.h
 *
 * @brief App scene setup API.
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
#ifndef __APP_MESH_SCENE_SETUP_SERVER_H__
#define __APP_MESH_SCENE_SETUP_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "app_scene_server.h"
#include "scene_server.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/**
 * Application mesh scene Server model information.
 */

typedef struct
{
    mesh_scene_setup_server_t server;                                      /**<   mesh scene Server model information. */
    app_scene_setup_store_cb_t store_cb;                                 /**< Callback to be called for informing the user application to store the value*/
    app_scene_setup_delete_cb_t delete_cb;                              /**< Callback to be called for informing  the user application to delete the value */

    app_scene_state_t *state;                                                    /**< Internal variableto to hold state and timing information */

    uint16_t client_address;                                                    /**< The address message received. */
} app_scene_setup_server_t;


/**
 * Initializes Application   mesh scene setup Server model.
 *
 * @param[in]     p_server                 Application   Mesh Time setup server information pointer.
 * @param[in]     element_offset        Element address offset from primary element address.
 * @param[in]     store_cb                 Application   Mesh Time server Store callback.
 * @param[in]     delete_cb                Application   Mesh Time server Delete callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_scene_setup_server_init(app_scene_setup_server_t *p_server, uint8_t element_offset, app_scene_setup_store_cb_t store_cb, app_scene_setup_delete_cb_t delete_cb);

#endif /* __APP_MESH_SCENE_SETUP_SERVER_H__ */

/** @} */

