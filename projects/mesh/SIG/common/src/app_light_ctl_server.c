/**
 *****************************************************************************************
 *
 * @file app_light_ctl_server.c
 *
 * @brief APP Light CTL Server API Implementation.
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
#include "app_light_ctl_server.h"
#include "light_ctl_server.h"
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
static void light_ctl_state_set_cb(light_ctl_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_ctl_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               void * p_out);

static void light_ctl_state_get_cb(light_ctl_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out);

static void light_ctl_range_state_get_cb(light_ctl_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out);

static void light_ctl_dft_state_get_cb(light_ctl_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out);

static void app_light_ctl_bind_check(app_light_ctl_server_t *p_server, uint32_t trigger_model);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

typedef struct
{
    app_light_ctl_server_t *p_server;
    uint8_t model_instance_index;
}ln_server_t;


const light_ctl_server_callbacks_t light_ctl_srv_cbs =
{
    .light_ctl_cbs.set_cb = light_ctl_state_set_cb,
    .light_ctl_cbs.get_cb = light_ctl_state_get_cb,

    .light_ctl_temp_range_cbs.get_cb = light_ctl_range_state_get_cb,
    .light_ctl_dft_cbs.get_cb = light_ctl_dft_state_get_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void ctl_update_ramaining_time(app_light_ctl_server_t *p_server, uint32_t *remaining_ms)
{
    if (p_server->state.ctl_remaining_time_ms > 0 && p_server->state.ctl_delay_ms == 0)
    {
        uint32_t current_time_clock_ms;
        uint16_t current_time_nb_wrap;
        uint32_t delta;

        mesh_run_time_get(&current_time_clock_ms, &current_time_nb_wrap);

        // only two conditions:
        if (current_time_nb_wrap == p_server->ctl_last_time_nb_wrap)
        {
            delta = current_time_clock_ms - p_server->ctl_last_time_clock_ms;
        }
        else
        {
            delta = current_time_clock_ms + (0xFFFFFFFF - p_server->ctl_last_time_clock_ms) + 1;
        }
        
        if (p_server->state.ctl_remaining_time_ms >= delta && delta > 0)
        {
            *remaining_ms = p_server->state.ctl_remaining_time_ms- delta;
        }
        else
        {
            *remaining_ms = 0;
        }
    }
    else
    {
        *remaining_ms = p_server->state.ctl_remaining_time_ms;
    }
}

static void ctl_state_process_timing(app_light_ctl_server_t * p_server)
{
    uint32_t status = MESH_ERROR_NO_ERROR;

    APP_LOG_INFO("[%s] enter.", __func__);

    // if the timer isn't in list, no error occurs.
    mesh_timer_clear(&p_server->ctl_state_timer.timer_id);

    //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer clear, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);

    /* Process timing requirements */
    if (p_server->state.ctl_delay_ms != 0)
    {
        p_server->ctl_state_timer.delay_ms = p_server->state.ctl_delay_ms;
        status = mesh_timer_set(&(p_server->ctl_state_timer));
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
    }
    else if (p_server->state.ctl_remaining_time_ms != 0)
    {
        p_server->ctl_state_timer.delay_ms = p_server->state.ctl_remaining_time_ms;
        status = mesh_timer_set(&(p_server->ctl_state_timer));
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);

        mesh_run_time_get(&p_server->ctl_last_time_clock_ms, &p_server->ctl_last_time_nb_wrap);
    }

    if (status != MESH_ERROR_NO_ERROR)
    {
       // APP_LOG_INFO("State transition timer error");
    }
}

static void ctl_state_value_update(app_light_ctl_server_t * p_server, bool immed)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    if (!immed)
    {
        /* Requirement: If delay and transition time is zero, current state changes to the target state. */
        if ((p_server->state.ctl_delay_ms == 0 && p_server->state.ctl_remaining_time_ms == 0) )
        {
            p_server->state.present_state.present_ctl_ln = p_server->state.target_state.target_ctl_ln;
            p_server->state.present_state.present_ctl_temp = p_server->state.target_state.target_ctl_temp;
            p_server->state.present_state.present_ctl_dlt_uv = p_server->state.target_state.target_ctl_dlt_uv;

            light_ctl_status_params_t status_params;
            status_params.present_ctl_ln = p_server->state.present_state.present_ctl_ln;
            status_params.present_ctl_temp = p_server->state.present_state.present_ctl_temp;
            status_params.remaining_time_ms = p_server->state.ctl_remaining_time_ms;
            light_ctl_server_status_publish(&p_server->server, &status_params);

            if (!p_server->value_updated)
            {
                p_server->light_ctl_set_cb(p_server->server.model_instance_index, &(p_server->state.present_state), NULL, NULL);
                app_light_ctl_bind_check(p_server, MODEL_ID_LIGHTS_CTL);
                // TODO: enhance logical judgement here
                p_server->light_ctl_set_cb(p_server->server.model_instance_index, &(p_server->state.present_state), NULL, NULL);
                p_server->value_updated = true;
            }
        }
    }
    else
    {
        p_server->light_ctl_set_cb(p_server->server.model_instance_index, &(p_server->state.present_state), NULL, NULL);
    }
    
    p_server->light_ctl_get_cb(p_server->server.model_instance_index, NULL, &(p_server->state.dft_state), NULL);//default lightness maybe changed by lightness model.
    store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_Lightness_State, 0, p_server->state.dft_state.default_ln== 0 ? p_server->state.target_state.target_ctl_ln: p_server->state.dft_state.default_ln, p_server->state.target_state.target_ctl_ln);
    store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_CTL_Temp_State, p_server->state.dft_state.default_temp, p_server->state.dft_state.default_temp, p_server->state.target_state.target_ctl_temp);
    store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_CTL_DLT_State, p_server->state.dft_state.default_dlt_uv, p_server->state.dft_state.default_dlt_uv, p_server->state.target_state.target_ctl_dlt_uv);
}

static void light_ctl_state_timer_cb(void * p_context)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    app_light_ctl_server_t * p_server = (app_light_ctl_server_t *) p_context;

    /* Requirement: Process timing. Process the delay first (Non-zero delay will delay the required
     * state transition by the specified amount) and then the transition time.
     */
    if (p_server->state.ctl_delay_ms != 0)
    {
        p_server->state.ctl_delay_ms = 0;
        ctl_state_value_update(p_server, false);
    }
    else if (p_server->state.ctl_remaining_time_ms != 0)
    {
        p_server->state.ctl_remaining_time_ms = 0;
        ctl_state_value_update(p_server, false);
    }
    ctl_state_process_timing(p_server);
}

static void light_ctl_state_get_cb(light_ctl_server_t * p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_light_ctl_server_t *p_server = PARENT_BY_FIELD_GET(app_light_ctl_server_t, server, p_self);
    light_ctl_status_params_t *p_out_set = (light_ctl_status_params_t *)p_out;

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the ctl state */
    p_server->light_ctl_get_cb(p_server->server.model_instance_index, &p_server->state.present_state, NULL, NULL);

    p_out_set->present_ctl_ln = p_server->state.present_state.present_ctl_ln;
    p_out_set->present_ctl_temp = p_server->state.present_state.present_ctl_temp;
    p_out_set->target_ctl_ln = p_server->state.target_state.target_ctl_ln;
    p_out_set->target_ctl_temp= p_server->state.target_state.target_ctl_temp;

    /* Requirement: Always report remaining time */
    ctl_update_ramaining_time(p_server, &p_out_set->remaining_time_ms);
}

static void light_ctl_state_set_cb(light_ctl_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_ctl_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               void * p_out)
{
    app_light_ctl_server_t *p_server = PARENT_BY_FIELD_GET(app_light_ctl_server_t, server, p_self);
    light_ctl_status_params_t *p_out_set = (light_ctl_status_params_t *)p_out;

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: %04X", __func__, p_self->model_instance_index, p_in->ctl_ln);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of ctl value, process timing */
    p_server->value_updated = false;
    p_server->state.target_state.target_ctl_ln = p_in->ctl_ln;
    p_server->state.target_state.target_ctl_temp = p_in->ctl_temp;
    p_server->state.target_state.target_ctl_dlt_uv = p_in->ctl_dlt_uv;

    /* Ensure that Light CTL lightness state value is between Light CTL Range Min and Max values */
    FORMAT_VALUE_RANGE(p_server->state.target_state.target_ctl_temp, p_server->state.temp_range.range_max, p_server->state.temp_range.range_min);

    if (p_in_transition == NULL)
    {
        p_server->state.ctl_delay_ms = 0;
        p_server->state.ctl_remaining_time_ms = 0;
    }
    else
    {
        p_server->state.ctl_delay_ms = p_in_transition->delay_ms;
        p_server->state.ctl_remaining_time_ms = p_in_transition->transition_time_ms;
    }

    ctl_state_value_update(p_server, false);
    ctl_state_process_timing(p_server);

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out_set->present_ctl_ln = p_server->state.present_state.present_ctl_ln;
        p_out_set->present_ctl_temp = p_server->state.present_state.present_ctl_temp;
        p_out_set->target_ctl_ln = p_server->state.target_state.target_ctl_ln;
        p_out_set->target_ctl_temp = p_server->state.target_state.target_ctl_temp;
        p_out_set->remaining_time_ms = p_server->state.ctl_remaining_time_ms;
    }

}

static void light_ctl_range_state_get_cb(light_ctl_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out)
{
    app_light_ctl_server_t *p_server = PARENT_BY_FIELD_GET(app_light_ctl_server_t, server, p_self);
    light_ctl_range_status_params_t *p_out_set = (light_ctl_range_status_params_t *)p_out;

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the ctl linear state */
    p_server->light_ctl_get_cb(p_server->server.model_instance_index, NULL, NULL, &p_server->state.temp_range);
    p_out_set->status_code = STATUS_CODES_SUCCESS;
    p_out_set->range_max = p_server->state.temp_range.range_max;
    p_out_set->range_min = p_server->state.temp_range.range_min;
}

static void light_ctl_dft_state_get_cb(light_ctl_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out)
{
    app_light_ctl_server_t *p_server = PARENT_BY_FIELD_GET(app_light_ctl_server_t, server, p_self);
    light_ctl_dft_status_params_t *p_out_set = (light_ctl_dft_status_params_t *)p_out;

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the ctl linear state */
    p_server->light_ctl_get_cb(p_server->server.model_instance_index, NULL, &p_server->state.dft_state, NULL);

    p_out_set->ln = p_server->state.dft_state.default_ln;
    p_out_set->temp = p_server->state.dft_state.default_temp;
    p_out_set->dlt_uv = p_server->state.dft_state.default_dlt_uv;
}

static void app_light_ctl_scene_recall_cb(void *p_server, uint8_t *stored_state, uint16_t state_length)
{
    app_light_ctl_server_t *recal_server = (app_light_ctl_server_t *)p_server;
    light_ctl_present_state_t * recall_state_ptr = (light_ctl_present_state_t *)stored_state;

    APP_LOG_INFO(" [%s] enter ", __func__);
    APP_LOG_INFO("server ctl recall state: value %d, length %d", *stored_state, state_length);

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

    APP_LOG_INFO(" 0x%04x, 0x%04x, 0x%04x, 0x%04x!!!", recall_state_ptr->present_ctl_ln, recall_state_ptr->present_ctl_dlt_uv, recal_server->state.present_state.present_ctl_ln, recal_server->state.present_state.present_ctl_dlt_uv);
    //value has been recalled in scenes model

    light_ctl_status_params_t status =
    {
        .present_ctl_ln = recal_server->state.present_state.present_ctl_ln,
        .present_ctl_temp = recal_server->state.present_state.present_ctl_temp,
        .target_ctl_ln = recal_server->state.target_state.target_ctl_ln,
        .target_ctl_temp = recal_server->state.target_state.target_ctl_temp,
    };
    ctl_update_ramaining_time(recal_server, &(status.remaining_time_ms));

    light_ctl_server_status_publish(&recal_server->server, &status);

    recal_server->light_ctl_set_cb(recal_server->server.model_instance_index, &(recal_server->state.present_state), NULL, NULL);
}

static void app_light_ctl_bind_check(app_light_ctl_server_t *p_server, uint32_t trigger_model)
{
    static uint16_t repeat_bind_ln_st[LIGHT_CTL_INSTANCE_COUNT] = {0,};
    static uint16_t repeat_bind_temp_st[LIGHT_CTL_INSTANCE_COUNT] = {LIGHT_CTL_TEMPERATURE_MIN,LIGHT_CTL_TEMPERATURE_MIN,
                                                                        LIGHT_CTL_TEMPERATURE_MIN, LIGHT_CTL_TEMPERATURE_MIN};
    uint16_t *repeat_bind_temp = &repeat_bind_temp_st[p_server->server.model_instance_index];
    uint16_t *repeat_bind_ln = &repeat_bind_ln_st[p_server->server.model_instance_index];

    APP_LOG_INFO(" [%s] enter,model_instance_index %d, repeat value %d %d, bind value %d %d", __func__, p_server->server.model_instance_index, *repeat_bind_temp, *repeat_bind_ln, p_server->state.present_state.present_ctl_temp, p_server->state.present_state.present_ctl_ln);

    if (*repeat_bind_temp != p_server->state.present_state.present_ctl_temp)
    {
        if (MODEL_ID_LIGHTS_CTLT != trigger_model)
        {
            /* ctl check bind light ctl temperature state */
            /* ctl state binding to ctl temperature state in temperature element*/
            mesh_model_bind_check(p_server->server.model_instance_index + 1, MODEL_ID_LIGHTS_CTLT, MODEL_ID_LIGHTS_CTL, &p_server->state.present_state.present_ctl_temp, sizeof(p_server->state.present_state.present_ctl_temp));
        }
        *repeat_bind_temp = p_server->state.present_state.present_ctl_temp;
    }

    if (*repeat_bind_ln != p_server->state.present_state.present_ctl_ln)
    {

        if (MODEL_ID_LIGHTS_LN != trigger_model)
        {
            /* check bind light lightness actual state */
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_LN, MODEL_ID_LIGHTS_CTL, &p_server->state.present_state.present_ctl_ln, sizeof(p_server->state.present_state.present_ctl_ln));
        }
        *repeat_bind_ln = p_server->state.present_state.present_ctl_ln;
    }

    return ;
}

static bool app_light_ctl_bind_cb(void *p_server, uint32_t src_model_id, void *p_data, uint16_t data_len)
{
    app_light_ctl_server_t * pl_server = (app_light_ctl_server_t *)p_server;
    bool ret = false;

    APP_LOG_INFO("[%s] enter, SERVER[%d], src model %04X data length %d", __func__, pl_server->server.model_instance_index, src_model_id, data_len);

    if (pl_server != NULL)
    {
        switch(src_model_id)
        {
            case MODEL_ID_LIGHTS_LN:
            {
                if (data_len == 2)
                {
                    uint16_t present_ln = *(uint16_t *)p_data;

                    if( pl_server->state.present_state.present_ctl_ln != present_ln)
                    {
                        pl_server->state.present_state.present_ctl_ln = present_ln;
                        ctl_state_value_update(pl_server, true);
                        ret = true;
                    }
                    APP_LOG_INFO("model light lightness bind message length %d, value %d, ctl   %d", data_len, present_ln, pl_server->state.present_state.present_ctl_ln);
                }
                break;
            }
            default:
                break;
        }

        if(ret)
        {
            app_light_ctl_status_publish(pl_server);
            app_light_ctl_bind_check(pl_server, src_model_id);
        }
    }

    return ret;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_light_ctl_status_publish(app_light_ctl_server_t * p_server)
{
    p_server->light_ctl_get_cb(p_server->server.model_instance_index, &p_server->state.present_state, NULL, NULL);
    // if the timer isn't in list, no error occurs.
    //mesh_timer_clear(&p_server->app_timer.timer_id);

    light_ctl_status_params_t status =
    {
        .present_ctl_ln = p_server->state.present_state.present_ctl_ln,
        .present_ctl_temp = p_server->state.present_state.present_ctl_temp,
        .target_ctl_ln = p_server->state.target_state.target_ctl_ln,
        .target_ctl_temp = p_server->state.target_state.target_ctl_temp,
    };
    ctl_update_ramaining_time(p_server, &(status.remaining_time_ms));

    return light_ctl_server_status_publish(&p_server->server, &status);
}

uint16_t app_light_ctl_server_init(app_light_ctl_server_t *p_server, uint8_t element_offset, app_light_ctl_set_cb_t set_cb, app_light_ctl_get_cb_t get_cb)
{
    if(( p_server == NULL) || (LIGHT_CTL_INSTANCE_COUNT <= element_offset))
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

    p_server->light_ctl_set_cb = set_cb;
    p_server->light_ctl_get_cb = get_cb;

    p_server->state.present_state.present_ctl_ln = LIGHT_CTL_LIGHTNESS_NO_EMIT;
    p_server->state.present_state.present_ctl_temp = LIGHT_CTL_TEMPERATURE_MIN;
    p_server->state.present_state.present_ctl_dlt_uv = LIGHT_CTL_DELTA_UV_ZERO;
    power_up_sequence_behavior(element_offset, element_offset, OnPowerUp_Bind_CTL_Temp_State, (uint16_t *)&p_server->state.present_state.present_ctl_temp);
    power_up_sequence_behavior(element_offset, element_offset, OnPowerUp_Bind_CTL_DLT_State, (uint16_t *)&p_server->state.present_state.present_ctl_dlt_uv);

    p_server->state.target_state.target_ctl_ln = LIGHT_CTL_LIGHTNESS_NO_EMIT;
    p_server->state.target_state.target_ctl_temp = LIGHT_CTL_TEMPERATURE_MIN;
    p_server->state.target_state.target_ctl_dlt_uv = LIGHT_CTL_DELTA_UV_ZERO;
    
    p_server->state.dft_state.default_ln = LIGHT_CTL_LIGHTNESS_NO_EMIT;
    p_server->state.dft_state.default_temp = LIGHT_CTL_TEMPERATURE_MIN;
    p_server->state.dft_state.default_dlt_uv = LIGHT_CTL_DELTA_UV_ZERO;
    p_server->state.temp_range.range_min = LIGHT_CTL_TEMPERATURE_MIN;
    p_server->state.temp_range.range_max = LIGHT_CTL_TEMPERATURE_MAX;

    p_server->state.ctl_remaining_time_ms = 0;
    p_server->state.ctl_delay_ms = 0;

    p_server->ctl_last_time_clock_ms = 0;
    p_server->ctl_last_time_nb_wrap = 0;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->value_updated = false;

    p_server->server.settings.p_callbacks = &light_ctl_srv_cbs,
        
    p_server->ctl_state_timer.callback = light_ctl_state_timer_cb;
    p_server->ctl_state_timer.p_args = p_server;
    p_server->ctl_state_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->ctl_state_timer.reload = false;

    mesh_model_bind_list_add(MODEL_ID_LIGHTS_CTL, element_offset, (void *)p_server, app_light_ctl_bind_cb);
    mesh_scenes_state_store_with_scene(element_offset, app_light_ctl_scene_recall_cb, (void *)p_server, (uint8_t *)&p_server->state.present_state, sizeof(p_server->state.present_state));

    return light_ctl_server_init(&p_server->server, element_offset);
}

