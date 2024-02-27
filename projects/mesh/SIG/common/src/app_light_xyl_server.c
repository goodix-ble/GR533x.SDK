/**
 *****************************************************************************************
 *
 * @file app_light_xyl_server.c
 *
 * @brief APP Light xyL Server API Implementation.
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
#include "app_light_xyl_server.h"
#include "light_xyl_server.h"
#include "app_log.h"
#include "user_app.h"
#include "mesh_bind.h"
#include "mesh_scenes_common.h"
#include "generic_power_onoff_behavior.h"

/*
 * DEFINES
 ****************************************************************************************
 */
#define FORMAT_VALUE_RANGE(value, max, min) ((value) = ((value) > (max)) ? (max) : (((value) < (min)) ? (min):(value)))

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void light_xyl_state_set_cb(light_xyl_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_xyl_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               void * p_out);

static void light_xyl_state_get_cb(light_xyl_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out);

static void light_xyl_targe_state_get_cb(light_xyl_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out);

static void light_xyl_range_state_get_cb(light_xyl_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out);

static void light_xyl_dft_state_get_cb(light_xyl_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out);

static void app_light_xyl_bind_check(app_light_xyl_server_t *p_server, uint32_t trigger_model);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

typedef struct
{
    app_light_xyl_server_t *p_server;
    uint8_t model_instance_index;
}ln_server_t;


const light_xyl_server_callbacks_t light_xyl_srv_cbs =
{
    .light_xyl_cbs.set_cb = light_xyl_state_set_cb,
    .light_xyl_cbs.get_cb = light_xyl_state_get_cb,

    .light_xyl_target_cbs.get_cb = light_xyl_targe_state_get_cb,
    .light_xyl_range_cbs.get_cb = light_xyl_range_state_get_cb,
    .light_xyl_dft_cbs.get_cb = light_xyl_dft_state_get_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void xyl_update_ramaining_time(app_light_xyl_server_t *p_server, uint32_t *remaining_ms)
{
    if (p_server->state.xyl_remaining_time_ms > 0 && p_server->state.xyl_delay_ms == 0)
    {
        uint32_t current_time_clock_ms;
        uint16_t current_time_nb_wrap;
        uint32_t delta;

        mesh_run_time_get(&current_time_clock_ms, &current_time_nb_wrap);

        // only two conditions:
        if (current_time_nb_wrap == p_server->xyl_last_time_nb_wrap)
        {
            delta = current_time_clock_ms - p_server->xyl_last_time_clock_ms;
        }
        else
        {
            delta = current_time_clock_ms + (0xFFFFFFFF - p_server->xyl_last_time_clock_ms) + 1;
        }
        
        if (p_server->state.xyl_remaining_time_ms >= delta && delta > 0)
        {
            *remaining_ms = p_server->state.xyl_remaining_time_ms- delta;
        }
        else
        {
            *remaining_ms = 0;
        }
    }
    else
    {
        *remaining_ms = p_server->state.xyl_remaining_time_ms;
    }
}

static void xyl_state_process_timing(app_light_xyl_server_t * p_server)
{
    uint32_t status = MESH_ERROR_NO_ERROR;

    APP_LOG_INFO("[%s] enter.", __func__);

    // if the timer isn't in list, no error occurs.
    mesh_timer_clear(&p_server->xyl_state_timer.timer_id);

    //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer clear, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);

    /* Process timing requirements */
    if (p_server->state.xyl_delay_ms != 0)
    {
        p_server->xyl_state_timer.delay_ms = p_server->state.xyl_delay_ms;
        status = mesh_timer_set(&(p_server->xyl_state_timer));
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
    }
    else if (p_server->state.xyl_remaining_time_ms != 0)
    {
        p_server->xyl_state_timer.delay_ms = p_server->state.xyl_remaining_time_ms;
        status = mesh_timer_set(&(p_server->xyl_state_timer));
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);

        mesh_run_time_get(&p_server->xyl_last_time_clock_ms, &p_server->xyl_last_time_nb_wrap);
    }

    if (status != MESH_ERROR_NO_ERROR)
    {
       // APP_LOG_INFO("State transition timer error");
    }
}

static void xyl_state_value_update(app_light_xyl_server_t * p_server, bool immed)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    if (!immed)
    {
        /* Requirement: If delay and transition time is zero, current state changes to the target state. */
        if ((p_server->state.xyl_delay_ms == 0 && p_server->state.xyl_remaining_time_ms == 0) )
        {
            p_server->state.present_state.present_xyl_ln = p_server->state.target_state.target_xyl_ln;
            p_server->state.present_state.present_xyl_x = p_server->state.target_state.target_xyl_x;
            p_server->state.present_state.present_xyl_y = p_server->state.target_state.target_xyl_y;

            light_xyl_status_params_t status_params;
            status_params.present_xyl_ln = p_server->state.present_state.present_xyl_ln;
            status_params.present_xyl_x = p_server->state.present_state.present_xyl_x;
            status_params.present_xyl_y = p_server->state.present_state.present_xyl_y;
            status_params.remaining_time_ms = p_server->state.xyl_remaining_time_ms;
            light_xyl_server_status_publish(&p_server->server, &status_params);

            if (!p_server->value_updated)
            {
                p_server->light_xyl_set_cb(p_server->server.model_instance_index, &(p_server->state.present_state), NULL, NULL);
                app_light_xyl_bind_check(p_server, MODEL_ID_LIGHTS_XYL);
                // TODO: enhance logical judgement here
                p_server->light_xyl_set_cb(p_server->server.model_instance_index, &(p_server->state.present_state), NULL, NULL);
                p_server->value_updated = true;
                
            }
        }
    }
    else
    {
        p_server->light_xyl_set_cb(p_server->server.model_instance_index, &(p_server->state.present_state), NULL, NULL);
    }
    
    p_server->light_xyl_get_cb(p_server->server.model_instance_index, NULL, &(p_server->state.dft_state), NULL);//default lightness maybe changed by lightness model.
    
    store_status_before_power_down(p_server->server.model_instance_index,
                                                            OnPowerUp_Bind_Lightness_State,
                                                            0,
                                                            p_server->state.dft_state.default_ln== 0 ? p_server->state.target_state.target_xyl_ln: p_server->state.dft_state.default_ln,
                                                            p_server->state.target_state.target_xyl_ln);
    store_status_before_power_down(p_server->server.model_instance_index,
                                                            OnPowerUp_Bind_xyL_X_State,
                                                            p_server->state.dft_state.default_x,
                                                            p_server->state.dft_state.default_x,
                                                            p_server->state.target_state.target_xyl_x);
    store_status_before_power_down(p_server->server.model_instance_index,
                                                            OnPowerUp_Bind_xyL_Y_State,
                                                            p_server->state.dft_state.default_y,
                                                            p_server->state.dft_state.default_y,
                                                            p_server->state.target_state.target_xyl_y);
}

static void light_xyl_state_timer_cb(void * p_context)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    app_light_xyl_server_t * p_server = (app_light_xyl_server_t *) p_context;

    /* Requirement: Process timing. Process the delay first (Non-zero delay will delay the required
     * state transition by the specified amount) and then the transition time.
     */
    if (p_server->state.xyl_delay_ms != 0)
    {
        p_server->state.xyl_delay_ms = 0;
        xyl_state_value_update(p_server, false);
    }
    else if (p_server->state.xyl_remaining_time_ms != 0)
    {
        p_server->state.xyl_remaining_time_ms = 0;
        xyl_state_value_update(p_server, false);
    }
    xyl_state_process_timing(p_server);
}

static void light_xyl_state_get_cb(light_xyl_server_t * p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_light_xyl_server_t *p_server = PARENT_BY_FIELD_GET(app_light_xyl_server_t, server, p_self);
    light_xyl_status_params_t *p_out_set = (light_xyl_status_params_t *)p_out;

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the xyL state */
    p_server->light_xyl_get_cb(p_server->server.model_instance_index, &p_server->state.present_state, NULL, NULL);

    p_out_set->present_xyl_ln = p_server->state.present_state.present_xyl_ln;
    p_out_set->present_xyl_x = p_server->state.present_state.present_xyl_x;
    p_out_set->present_xyl_y = p_server->state.present_state.present_xyl_y;

    /* Requirement: Always report remaining time */
    xyl_update_ramaining_time(p_server, &p_out_set->remaining_time_ms);
}

static void light_xyl_state_set_cb(light_xyl_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_xyl_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               void * p_out)
{
    app_light_xyl_server_t *p_server = PARENT_BY_FIELD_GET(app_light_xyl_server_t, server, p_self);
    light_xyl_status_params_t *p_out_set = (light_xyl_status_params_t *)p_out;

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: %04X", __func__, p_self->model_instance_index, p_in->xyl_ln);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of xyL value, process timing */
    p_server->value_updated = false;
    p_server->state.target_state.target_xyl_ln = p_in->xyl_ln;
    p_server->state.target_state.target_xyl_x = p_in->xyl_x;
    p_server->state.target_state.target_xyl_y = p_in->xyl_y;

    /* Ensure that Light xyL lightness state value is between Light xyL Range Min and Max values */
    FORMAT_VALUE_RANGE(p_server->state.target_state.target_xyl_x, p_server->state.xyl_range.range_max_x, p_server->state.xyl_range.range_min_x);
    FORMAT_VALUE_RANGE(p_server->state.target_state.target_xyl_y, p_server->state.xyl_range.range_max_y, p_server->state.xyl_range.range_min_y);

    if (p_in_transition == NULL)
    {
        p_server->state.xyl_delay_ms = 0;
        p_server->state.xyl_remaining_time_ms = 0;
    }
    else
    {
        p_server->state.xyl_delay_ms = p_in_transition->delay_ms;
        p_server->state.xyl_remaining_time_ms = p_in_transition->transition_time_ms;
    }

    xyl_state_value_update(p_server, false);
    xyl_state_process_timing(p_server);

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out_set->present_xyl_ln = p_server->state.present_state.present_xyl_ln;
        p_out_set->present_xyl_x = p_server->state.present_state.present_xyl_x;
        p_out_set->present_xyl_y = p_server->state.present_state.present_xyl_y;
        p_out_set->remaining_time_ms = p_server->state.xyl_remaining_time_ms;
    }

}

static void light_xyl_targe_state_get_cb(light_xyl_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_light_xyl_server_t *p_server = PARENT_BY_FIELD_GET(app_light_xyl_server_t, server, p_self);
    light_xyl_target_status_params_t *p_out_set = (light_xyl_target_status_params_t *)p_out;

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the xyL target state */
    p_server->light_xyl_get_cb(p_server->server.model_instance_index, &p_server->state.present_state, NULL, NULL);

    p_out_set->target_xyl_ln= p_server->state.target_state.target_xyl_ln;
    p_out_set->target_xyl_x= p_server->state.target_state.target_xyl_x;
    p_out_set->target_xyl_y= p_server->state.target_state.target_xyl_y;

    /* Requirement: Always report remaining time */
    xyl_update_ramaining_time(p_server, &p_out_set->remaining_time_ms);
}

static void light_xyl_range_state_get_cb(light_xyl_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out)
{
    app_light_xyl_server_t *p_server = PARENT_BY_FIELD_GET(app_light_xyl_server_t, server, p_self);
    light_xyl_range_status_params_t *p_out_set = (light_xyl_range_status_params_t *)p_out;

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the xyL range state */
    p_server->light_xyl_get_cb(p_server->server.model_instance_index, NULL, NULL, &p_server->state.xyl_range);
    p_out_set->status_code = STATUS_CODES_SUCCESS;
    p_out_set->range_max_x= p_server->state.xyl_range.range_max_x;
    p_out_set->range_min_x= p_server->state.xyl_range.range_min_x;
    p_out_set->range_max_y= p_server->state.xyl_range.range_max_y;
    p_out_set->range_min_y= p_server->state.xyl_range.range_min_y;
}

static void light_xyl_dft_state_get_cb(light_xyl_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out)
{
    app_light_xyl_server_t *p_server = PARENT_BY_FIELD_GET(app_light_xyl_server_t, server, p_self);
    light_xyl_dft_status_params_t *p_out_set = (light_xyl_dft_status_params_t *)p_out;

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the xyL default state */
    p_server->light_xyl_get_cb(p_server->server.model_instance_index, NULL, &p_server->state.dft_state, NULL);

    p_out_set->ln = p_server->state.dft_state.default_ln;
    p_out_set->x = p_server->state.dft_state.default_x;
    p_out_set->y = p_server->state.dft_state.default_y;
}

static void app_light_xyL_scene_recall_cb(void *p_server, uint8_t *stored_state, uint16_t state_length)
{
    app_light_xyl_server_t *recal_server = (app_light_xyl_server_t *)p_server;
    light_xyl_present_state_t * recall_state_ptr = (light_xyl_present_state_t *)stored_state;

    APP_LOG_INFO(" [%s] enter ", __func__);
    APP_LOG_INFO("server ctl recall state: L=0x%04x, x=0x%04x, y=0x%04x, length %d", recall_state_ptr->present_xyl_ln, recall_state_ptr->present_xyl_x, recall_state_ptr->present_xyl_y, state_length);

    if (NULL == p_server)
    {
        APP_LOG_INFO(" [%s] exit : Unknow server state to recall !!!", __func__);
        return ;
    }

    if (state_length != sizeof(recal_server->state.present_state))
    {
        APP_LOG_INFO(" [%s] exit : invalid recall param!!!", __func__);
        return ;
    }

    //value has been recalled in scenes model
    light_xyl_status_params_t status =
    {
        .present_xyl_ln = recal_server->state.present_state.present_xyl_ln,
        .present_xyl_x = recal_server->state.present_state.present_xyl_x,
        .present_xyl_y = recal_server->state.present_state.present_xyl_y,
    };
    xyl_update_ramaining_time(recal_server, &(status.remaining_time_ms));

    light_xyl_server_status_publish(&recal_server->server, &status);

    recal_server->light_xyl_set_cb(recal_server->server.model_instance_index, &(recal_server->state.present_state), NULL, NULL);
}

static void app_light_xyl_bind_check(app_light_xyl_server_t *p_server, uint32_t trigger_model)
{
    static uint16_t repeat_bind_xyl_st[LIGHT_XYL_INSTANCE_COUNT] = {0,};
    uint16_t *repeat_bind_ln = &repeat_bind_xyl_st[p_server->server.model_instance_index];

    APP_LOG_INFO(" %s enter, repeat value %d, bind value %d", __func__, *repeat_bind_ln, p_server->state.present_state.present_xyl_ln);

    // TODO: xyL bind HSL model
    if (*repeat_bind_ln != p_server->state.present_state.present_xyl_ln)
    {
        if (MODEL_ID_LIGHTS_LN!= trigger_model)
        {
            /* xyL check bind light lightness state */
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_LN, MODEL_ID_LIGHTS_XYL, &p_server->state.present_state.present_xyl_ln, sizeof(p_server->state.present_state.present_xyl_ln));
            *repeat_bind_ln = p_server->state.present_state.present_xyl_ln;
        }
    }

    return ;
}

static bool app_light_xyl_bind_cb(void *p_server, uint32_t src_model_id, void *p_data, uint16_t data_len)
{
    app_light_xyl_server_t * pl_server = (app_light_xyl_server_t *)p_server;
    bool ret = false;

    APP_LOG_INFO("[%s] enter, SERVER[%d], src model %04X data length %d", __func__, pl_server->server.model_instance_index, src_model_id, data_len);

    // TODO: xyL bind HSL model

    if (pl_server != NULL)
    {
        switch(src_model_id)
        {
            case MODEL_ID_LIGHTS_LN:
            {
                if (data_len == 2)
                {
                    uint16_t present_ln = *(uint16_t *)p_data;

                    if( pl_server->state.present_state.present_xyl_ln != present_ln)
                    {
                        pl_server->state.present_state.present_xyl_ln = present_ln;
                        xyl_state_value_update(pl_server, true);
                        ret = true;
                    }
                    APP_LOG_INFO("model light lightness bind message length %d, value %d, ln %d", data_len, present_ln, pl_server->state.present_state.present_xyl_ln);
                }
                break;
            }
            default:
                break;
        }

        if(ret)
        {
            app_light_xyl_status_publish(pl_server);
            app_light_xyl_bind_check(pl_server, src_model_id);
        }
    }

    return ret;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_light_xyl_status_publish(app_light_xyl_server_t * p_server)
{
    p_server->light_xyl_get_cb(p_server->server.model_instance_index, &p_server->state.present_state, NULL, NULL);
    // if the timer isn't in list, no error occurs.
    //mesh_timer_clear(&p_server->app_timer.timer_id);

    light_xyl_status_params_t status =
    {
        .present_xyl_ln = p_server->state.present_state.present_xyl_ln,
        .present_xyl_x = p_server->state.present_state.present_xyl_x,
        .present_xyl_y = p_server->state.present_state.present_xyl_y,
    };
    xyl_update_ramaining_time(p_server, &(status.remaining_time_ms));

    return  light_xyl_server_status_publish(&p_server->server, &status);
}

uint16_t app_light_xyl_server_init(app_light_xyl_server_t *p_server, uint8_t element_offset, app_light_xyl_set_cb_t set_cb, app_light_xyl_get_cb_t get_cb)
{
    if(( p_server == NULL) || (LIGHT_XYL_INSTANCE_COUNT <= element_offset))
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

    p_server->light_xyl_set_cb = set_cb;
    p_server->light_xyl_get_cb = get_cb;

    p_server->state.present_state.present_xyl_ln = 0;
    p_server->state.present_state.present_xyl_x = 0;
    p_server->state.present_state.present_xyl_y = 0;
    power_up_sequence_behavior(element_offset, element_offset, OnPowerUp_Bind_Lightness_State, (uint16_t *)&p_server->state.present_state.present_xyl_ln);
    power_up_sequence_behavior(element_offset, element_offset, OnPowerUp_Bind_xyL_X_State, (uint16_t *)&p_server->state.present_state.present_xyl_x);
    power_up_sequence_behavior(element_offset, element_offset, OnPowerUp_Bind_xyL_Y_State, (uint16_t *)&p_server->state.present_state.present_xyl_y);

    p_server->state.target_state.target_xyl_ln = 0;
    p_server->state.target_state.target_xyl_x = 0;
    p_server->state.target_state.target_xyl_y = 0;

    p_server->state.dft_state.default_ln = 0;
    p_server->state.dft_state.default_x = 0;
    p_server->state.dft_state.default_y = 0;
    p_server->state.xyl_range.range_max_x = 0xFFFF;
    p_server->state.xyl_range.range_min_x = 0;
    p_server->state.xyl_range.range_max_y = 0xFFFF;
    p_server->state.xyl_range.range_min_y = 0;

    p_server->state.xyl_remaining_time_ms = 0;
    p_server->state.xyl_delay_ms = 0;

    p_server->xyl_last_time_clock_ms = 0;
    p_server->xyl_last_time_nb_wrap = 0;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->value_updated = false;

    p_server->server.settings.p_callbacks = &light_xyl_srv_cbs,
        
    p_server->xyl_state_timer.callback = light_xyl_state_timer_cb;
    p_server->xyl_state_timer.p_args = p_server;
    p_server->xyl_state_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->xyl_state_timer.reload = false;

    mesh_model_bind_list_add(MODEL_ID_LIGHTS_XYL, element_offset, (void *)p_server, app_light_xyl_bind_cb);
    mesh_scenes_state_store_with_scene(element_offset, app_light_xyL_scene_recall_cb, (void *)p_server, (uint8_t *)&p_server->state.present_state, sizeof(p_server->state.present_state));

    return light_xyl_server_init(&p_server->server, element_offset);
}

