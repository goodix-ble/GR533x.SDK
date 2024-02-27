/**
 *****************************************************************************************
 *
 * @file app_scene_server.c
 *
 * @brief APP Mesh Scene API Implementation.
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
#include "app_scene_server.h"
#include "scene_server.h"
#include "app_log.h"
#include "user_app.h"
#include "mesh_bind.h"
#include "mesh_scenes_common.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void app_mesh_scene_state_get_cb(mesh_scene_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               mesh_scene_status_params_t * p_out);

static void app_mesh_scene_register_state_get_cb(mesh_scene_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               mesh_scene_register_status_params_t * p_out);

static void app_mesh_scene_state_recall_cb(mesh_scene_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const mesh_scene_recall_params_t * p_in, const model_transition_t * p_in_transition,
                                               mesh_scene_status_params_t * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const mesh_scene_server_callbacks_t scene_srv_cbs =
{
    .scenes_cbs.recall_cb = app_mesh_scene_state_recall_cb,
    .scenes_cbs.get_cb = app_mesh_scene_state_get_cb,
    .scenes_cbs.register_get_cb = app_mesh_scene_register_state_get_cb,
};


/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
 static void scene_update_ramaining_time(app_scene_server_t *p_server, uint32_t *remaining_ms)
{
    if (p_server->state.remaining_time_ms > 0 && p_server->state.delay_ms == 0)
    {
        uint32_t current_time_clock_ms;
        uint16_t current_time_nb_wrap;
        uint32_t delta;

        mesh_run_time_get(&current_time_clock_ms, &current_time_nb_wrap);

        // only two conditions:
        if (current_time_nb_wrap == p_server->scene_last_time_nb_wrap)
        {
            delta = current_time_clock_ms - p_server->scene_last_time_clock_ms;
        }
        else
        {
            delta = current_time_clock_ms + (0xFFFFFFFF - p_server->scene_last_time_clock_ms) + 1;
        }
        
        if (p_server->state.remaining_time_ms >= delta && delta > 0)
        {
            *remaining_ms = p_server->state.remaining_time_ms- delta;
        }
        else
        {
            *remaining_ms = 0;
        }
    }
    else
    {
        *remaining_ms = p_server->state.remaining_time_ms;
    }
}

static void scene_state_process_timing(app_scene_server_t * p_server)
{
    uint32_t status = MESH_ERROR_NO_ERROR;

    APP_LOG_INFO("[%s] enter.", __func__);

    // if the timer isn't in list, no error occurs.
    mesh_timer_clear(&p_server->scene_state_timer.timer_id);

    //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer clear, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);

    /* Process timing requirements */
    if (p_server->state.delay_ms!= 0)
    {
        p_server->scene_state_timer.delay_ms = p_server->state.delay_ms;
        status = mesh_timer_set(&(p_server->scene_state_timer));
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
    }
    else if (p_server->state.remaining_time_ms != 0)
    {
        p_server->scene_state_timer.delay_ms = p_server->state.remaining_time_ms;
        status = mesh_timer_set(&(p_server->scene_state_timer));
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);

        mesh_run_time_get(&p_server->scene_last_time_clock_ms, &p_server->scene_last_time_nb_wrap);
    }

    if (status != MESH_ERROR_NO_ERROR)
    {
       // APP_LOG_INFO("State transition timer error");
    }
}

static void scene_state_value_update(app_scene_server_t * p_server)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    /* Requirement: If delay and transition time is zero, current state changes to the target state. */
    if ((p_server->state.delay_ms == 0 && p_server->state.remaining_time_ms == 0) )
    {
        model_scenes_state_t scene_err_code = mesh_scenes_scene_recall(p_server->server.model_instance_index, p_server->state.target_scene);

        p_server->state.status_code = MESH_SCENE_STATUS_CODE_DECODE(scene_err_code);

        if (MODEL_SCENES_SUCCESS == scene_err_code)
        {
            p_server->state.current_scene = p_server->state.target_scene;
            p_server->state.target_scene = MESH_SCENES_SCENE_VALUE_PROHIBITED;
        }

        mesh_scene_status_params_t status_params;
        status_params.status_code = p_server->state.status_code;
        status_params.current_scene = p_server->state.current_scene;
        status_params.remaining_time_ms = p_server->state.remaining_time_ms;
        (void) mesh_scene_server_status_publish(&p_server->server, &status_params);

        if (!p_server->value_updated)
        {
            p_server->scene_set_cb(p_server->server.model_instance_index, p_server->state.current_scene);
            p_server->value_updated = true;
        }
    }
}

static void mesh_scene_state_timer_cb(void * p_context)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    app_scene_server_t * p_server = (app_scene_server_t *) p_context;

    /* Requirement: Process timing. Process the delay first (Non-zero delay will delay the required
     * state transition by the specified amount) and then the transition time.
     */
    if (p_server->state.delay_ms!= 0)
    {
        p_server->state.delay_ms = 0;
        scene_state_value_update(p_server);
    }
    else if (p_server->state.remaining_time_ms!= 0)
    {
        p_server->state.remaining_time_ms = 0;
        scene_state_value_update(p_server);
    }
    scene_state_process_timing(p_server);
}

static void app_mesh_scene_state_get_cb(mesh_scene_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               mesh_scene_status_params_t * p_out)
{
    app_scene_server_t *p_server = PARENT_BY_FIELD_GET(app_scene_server_t, server, p_self);
    model_scenes_state_t scenes_state = MODEL_SCENES_SUCCESS;

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the Time state */
    p_server->scene_get_cb(p_server->server.model_instance_index, &p_server->state.current_scene);

    //When a scene transition is in progress, the value of the Current Scene state shall be set to 0x0000.
    if (p_server->state.remaining_time_ms > 0)
    {
        p_server->state.current_scene = MESH_SCENES_SCENE_VALUE_PROHIBITED;
    }
//    else if (MODEL_SCENES_SUCCESS != (scenes_state = mesh_scenes_current_scene_verify(p_server->server.model_instance_index, p_server->state.current_scene)))
//    {
//        p_server->state.current_scene = mesh_scenes_current_scene_get(p_server->server.model_instance_index);
//        p_server->scene_set_cb(p_server->server.model_instance_index, p_server->state.current_scene);
//    }

    p_server->state.status_code = MESH_SCENE_STATUS_CODE_DECODE(scenes_state);
    p_out->status_code = p_server->state.status_code;
    APP_LOG_INFO("[%s] scene 0x%04x,  %d", __func__, scenes_state, p_server->state.status_code);
    p_out->current_scene = p_server->state.current_scene;
    p_out->target_scene = p_server->state.target_scene;
    scene_update_ramaining_time(p_server, &p_out->remaining_time_ms);

}

static void app_mesh_scene_register_state_get_cb(mesh_scene_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               mesh_scene_register_status_params_t * p_out)
{
    app_scene_server_t *p_server = PARENT_BY_FIELD_GET(app_scene_server_t, server, p_self);
    model_scenes_state_t scenes_state = MODEL_SCENES_SUCCESS;

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the Time state */
    p_server->scene_get_cb(p_server->server.model_instance_index, &p_server->state.current_scene);

    if (p_server->state.remaining_time_ms > 0)
    {
        p_server->state.current_scene = MESH_SCENES_SCENE_VALUE_PROHIBITED;
    }
    else if (MODEL_SCENES_SUCCESS != (scenes_state = mesh_scenes_current_scene_verify(p_server->server.model_instance_index, p_server->state.current_scene)))
    {
        p_server->state.current_scene = mesh_scenes_current_scene_get(p_server->server.model_instance_index);
        p_server->scene_set_cb(p_server->server.model_instance_index, p_server->state.current_scene);
    }

    p_out->current_scene = p_server->state.current_scene;

    p_out->scene_cnt = mesh_scenes_scene_register_get(p_server->server.model_instance_index, sizeof(p_out->scene), p_out->scene);
    //if (p_out->scene_cnt == 0)
    //{
        //p_server->state.status_code = MESH_SCENE_STATUS_CODE_DECODE(MODEL_SCENES_ERR_NOT_FOUND);
    //}
    //else
    {
        p_server->state.status_code = MESH_SCENE_STATUS_CODE_DECODE(MODEL_SCENES_SUCCESS);
    }
    p_out->status_code = p_server->state.status_code;
    APP_LOG_INFO("[%s] scene 0x%04x,  %d", __func__, scenes_state, p_server->state.status_code);
}

static void app_mesh_scene_state_recall_cb(mesh_scene_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const mesh_scene_recall_params_t * p_in, const model_transition_t * p_in_transition,
                                               mesh_scene_status_params_t * p_out)
{
    app_scene_server_t *p_server = PARENT_BY_FIELD_GET(app_scene_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: Recall: 0x%04X", __func__, p_self->model_instance_index, p_in->scene_number);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    if (MESH_SCENES_SCENE_VALUE_PROHIBITED != p_in->scene_number)
    {
        /* Update internal representation of ctl value, process timing */
        p_server->value_updated = false;
        p_server->state.target_scene = p_in->scene_number;

        if (p_in_transition == NULL)
        {
            p_server->state.delay_ms = 0;
            p_server->state.remaining_time_ms = 0;
        }
        else
        {
            p_server->state.delay_ms = p_in_transition->delay_ms;
            p_server->state.remaining_time_ms = p_in_transition->transition_time_ms;

            p_server->state.status_code = MESH_SCENE_STATUS_CODE_DECODE(MODEL_SCENES_SUCCESS);

            //When a scene transition is in progress, the value of the Current Scene state shall be set to 0x0000
            p_server->state.current_scene = MESH_SCENES_SCENE_VALUE_PROHIBITED;
            p_server->scene_set_cb(p_server->server.model_instance_index, p_server->state.current_scene);
        }

        scene_state_value_update(p_server);
        scene_state_process_timing(p_server);
    }
    else
    {
        p_server->state.status_code = MESH_SCENE_STATUS_CODE_DECODE(MODEL_SCENES_ERR_NOT_FOUND);
        scene_update_ramaining_time(p_server, &(p_server->state.remaining_time_ms));
    }

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->status_code = p_server->state.status_code;
        p_out->current_scene = p_server->state.current_scene;
        p_out->target_scene = p_server->state.target_scene;
        p_out->remaining_time_ms = p_server->state.remaining_time_ms;
    }
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_scene_status_publish(app_scene_server_t * p_server)
{
    p_server->scene_get_cb(p_server->server.model_instance_index, &p_server->state.current_scene);

    mesh_scene_status_params_t status =
    {
        .status_code = p_server->state.status_code,
        .current_scene = p_server->state.current_scene,
        .target_scene = p_server->state.target_scene,
    };
    scene_update_ramaining_time(p_server, &(status.remaining_time_ms));

    return mesh_scene_server_status_publish(&p_server->server, &status);
}

uint16_t app_scene_register_status_publish(app_scene_server_t * p_server)
{
    mesh_scene_register_status_params_t status;
    status.status_code = MESH_SCENE_STATUS_CODE_DECODE(MODEL_SCENES_SUCCESS),
    status.current_scene = p_server->state.current_scene,
    status.scene_cnt = mesh_scenes_scene_register_get(p_server->server.model_instance_index, sizeof(status.scene), status.scene);
    return mesh_scene_server_register_status_publish(&p_server->server, &status);
}

uint16_t app_scene_server_init(app_scene_server_t *p_server, uint8_t element_offset, app_scene_get_cb_t get_cb, app_scene_set_cb_t set_cb)
{
    if(( p_server == NULL) || (TSCNS_SCENE_SERVER_INSTANCE_COUNT <= element_offset))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.tid_tracker.tid_expiry_timer.callback = NULL;
    p_server->server.tid_tracker.tid_expiry_timer.p_args = NULL;
    p_server->server.tid_tracker.tid_expiry_timer.delay_ms = 0;
    p_server->server.tid_tracker.tid_expiry_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->server.tid_tracker.tid_expiry_timer.reload = false;
    p_server->server.model_instance_index = element_offset;
    p_server->server.p_dtt_ms = NULL;

    p_server->scene_get_cb = get_cb;
    p_server->scene_set_cb = set_cb;

    p_server->state.status_code = MESH_SCENE_STATUS_CODE_DECODE(MODEL_SCENES_ERR_NOT_FOUND);
    p_server->state.current_scene = MESH_SCENES_SCENE_VALUE_PROHIBITED;
    p_server->state.target_scene = MESH_SCENES_SCENE_VALUE_PROHIBITED;
    p_server->state.remaining_time_ms = 0;
    p_server->state.delay_ms = 0;

    p_server->scene_last_time_clock_ms = 0;
    p_server->scene_last_time_nb_wrap = 0;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->value_updated = false;

    p_server->server.settings.p_callbacks = &scene_srv_cbs;

    p_server->scene_state_timer.callback = mesh_scene_state_timer_cb;
    p_server->scene_state_timer.p_args = p_server;
    p_server->scene_state_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->scene_state_timer.reload = false;

    return mesh_scene_server_init(&p_server->server, element_offset);
}


