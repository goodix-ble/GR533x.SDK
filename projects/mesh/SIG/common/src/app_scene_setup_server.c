/**
 *****************************************************************************************
 *
 * @file app_scene_setup_server.c
 *
 * @brief APP mesh scene API Implementation.
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "app_scene_setup_server.h"
#include "scene_setup_server.h"
#include "app_log.h"
#include "user_app.h"
#include "mesh_bind.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void app_mesh_scene_register_state_store_cb(mesh_scene_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const mesh_scene_store_params_t * p_in,
                                                    mesh_scene_register_status_params_t * p_out);

static void app_mesh_scene_register_state_delete_cb(mesh_scene_setup_server_t *p_self,
                                                   const mesh_model_msg_ind_t *p_rx_msg,
                                                   const mesh_scene_delete_params_t * p_in,
                                                   mesh_scene_register_status_params_t * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const mesh_scene_server_callbacks_t scene_setup_srv_cbs =
{
    .scenes_cbs.store_cb = app_mesh_scene_register_state_store_cb,
    .scenes_cbs.delete_cb = app_mesh_scene_register_state_delete_cb,
};
/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static void app_mesh_scene_register_state_store_cb(mesh_scene_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const mesh_scene_store_params_t * p_in,
                                                    mesh_scene_register_status_params_t * p_out)
{
    app_scene_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_scene_setup_server_t, server, p_self);
    model_scenes_state_t scene_err_code = MODEL_SCENES_SUCCESS;

    //the scene transition is in progress
    if (0 != p_server->state->remaining_time_ms)
    {
        scene_err_code = mesh_scenes_scene_store(p_server->server.model_instance_index, p_in->scene_number, p_server->state->target_scene);
    }
    else
    {
        scene_err_code = mesh_scenes_scene_store(p_server->server.model_instance_index, p_in->scene_number, MESH_SCENES_SCENE_VALUE_PROHIBITED);
    }

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: Store: 0x%04x", __func__, p_self->model_instance_index, p_in->scene_number);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    p_server->state->status_code = MESH_SCENE_STATUS_CODE_DECODE(scene_err_code);

    if (MODEL_SCENES_SUCCESS == scene_err_code)
    {
        //the scene transition is in progress
        if (0 != p_server->state->remaining_time_ms)
        {
            p_server->state->current_scene = MESH_SCENES_SCENE_VALUE_PROHIBITED;
        }
        else
        {
            p_server->state->current_scene = p_in->scene_number;
        }
    }
    else
    {
        if (MODEL_SCENES_SUCCESS != mesh_scenes_current_scene_verify(p_server->server.model_instance_index, p_server->state->current_scene))
        {
            p_server->state->current_scene = mesh_scenes_current_scene_get(p_server->server.model_instance_index);
            p_server->state->current_scene = MESH_SCENES_SCENE_VALUE_PROHIBITED;
        }
    }
    p_server->store_cb(p_server->server.model_instance_index, p_server->state->current_scene);

    /* Prepare response */
    p_out->status_code = p_server->state->status_code;
    p_out->current_scene = p_server->state->current_scene;
    p_out->scene_cnt = mesh_scenes_scene_register_get(p_server->server.model_instance_index, sizeof(p_out->scene), p_out->scene);
}

static void app_mesh_scene_register_state_delete_cb(mesh_scene_setup_server_t *p_self,
                                                   const mesh_model_msg_ind_t *p_rx_msg,
                                                   const mesh_scene_delete_params_t * p_in,
                                                   mesh_scene_register_status_params_t * p_out)
{
    app_scene_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_scene_setup_server_t, server, p_self);
    model_scenes_state_t scene_err_code =  mesh_scenes_scene_delete(p_server->server.model_instance_index, p_in->scene_number);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: Delete: 0x%04x", __func__, p_self->model_instance_index, p_in->scene_number);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    p_server->state->status_code = MESH_SCENE_STATUS_CODE_DECODE(scene_err_code);
    if ((MODEL_SCENES_SUCCESS == scene_err_code)
        &&(p_server->state->current_scene == p_in->scene_number))
    {
        p_server->state->current_scene = MESH_SCENES_SCENE_VALUE_PROHIBITED;
    }
    else if (MODEL_SCENES_SUCCESS != mesh_scenes_current_scene_verify(p_server->server.model_instance_index, p_server->state->current_scene))
    {
        p_server->state->current_scene = MESH_SCENES_SCENE_VALUE_PROHIBITED;
    }

    p_server->delete_cb(p_server->server.model_instance_index, p_server->state->current_scene, p_in->scene_number, scene_err_code);

    /* Prepare response */
    p_out->status_code = p_server->state->status_code;
    p_out->current_scene = p_server->state->current_scene;
    p_out->scene_cnt = mesh_scenes_scene_register_get(p_server->server.model_instance_index, sizeof(p_out->scene), p_out->scene);
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
*/
uint16_t app_scene_setup_server_init(app_scene_setup_server_t *p_server, uint8_t element_offset, app_scene_setup_store_cb_t store_cb, app_scene_setup_delete_cb_t delete_cb)
{
    if(( p_server == NULL)
        || (TSCNS_SCENE_SERVER_INSTANCE_COUNT <= element_offset)
        || (p_server->server.scene_server == NULL)
        || (p_server->state == NULL))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->store_cb = store_cb;
    p_server->delete_cb = delete_cb;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->server.settings.p_callbacks = &scene_setup_srv_cbs;

    return mesh_scene_setup_server_init(&p_server->server, element_offset);
}

