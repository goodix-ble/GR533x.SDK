/**
 *****************************************************************************************
 *
 * @file app_light_HSL_Saturation_server.c
 *
 * @brief APP LIGHT HSL Saturation Server API Implementation.
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
#include "app_light_HSL_server.h"
#include "app_light_HSL_saturation_server.h"
#include "light_HSL_saturation_server.h"
#include "app_log.h"
#include "user_app.h"
#include "mesh_bind.h"
#include "generic_power_onoff_behavior.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void light_HSL_stt_state_set_cb(light_HSL_stt_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                   const light_HSL_stt_set_params_t * p_in, const model_transition_t * p_in_transition,
                                   light_HSL_status_params_u * p_out);

static void light_HSL_stt_state_get_cb(light_HSL_stt_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_HSL_status_params_u * p_out);


static void app_light_HSL_stt_bind_check(app_light_HSL_stt_server_t *p_server, uint32_t trigger_model, bool is_boot);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

typedef struct
{
    app_light_HSL_server_t *p_server;
    uint8_t model_instance_index;
}HSL_server_t;


const light_HSL_server_callbacks_t light_HSL_stt_srv_cbs =
{
    .light_HSL_stt_cbs.set_cb = light_HSL_stt_state_set_cb,
    .light_HSL_stt_cbs.get_cb = light_HSL_stt_state_get_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */


static void stt_state_process_timing(app_light_HSL_stt_server_t * p_server, bool linear)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    uint32_t status = MESH_ERROR_NO_ERROR;
    mesh_timer_t *p_timer = &(p_server->stt_state_timer);
    //APP_LOG_INFO("SERVER[%d] -- before -- mesh app timer clear, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
    
    // if the timer isn't in list, no error occurs.
    mesh_timer_clear(&p_timer->timer_id);

    //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer clear, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);

    /* Process timing requirements */
    if (p_server->state->stt_time.delay_ms != 0)
    {
        p_timer->delay_ms = p_server->state->stt_time.delay_ms;
        status = mesh_timer_set(p_timer);
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
    }
    else if (p_server->state->stt_time.remaining_time_ms != 0)
    {
        p_timer->delay_ms = p_server->state->stt_time.remaining_time_ms;
        status = mesh_timer_set(p_timer);
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
        mesh_run_time_get(&p_server->stt_last_time_clock_ms, &p_server->stt_last_time_nb_wrap);
    }

    if (status != MESH_ERROR_NO_ERROR)
    {
       // APP_LOG_INFO("State transition timer error");
    }
}

static void stt_state_value_update(app_light_HSL_stt_server_t * p_server, bool immed)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    if (!immed)
    {
        /* Requirement: If delay and transition time is zero, current state changes to the target state. */
        if ((p_server->state->stt_time.delay_ms == 0 && p_server->state->stt_time.remaining_time_ms == 0) )
        {
            p_server->state->present_state.present_stt = p_server->state->target_state.target_stt;

            light_HSL_stt_status_params_t status_params;
            status_params.present_stt = p_server->state->present_state.present_stt;
            status_params.target_stt = p_server->state->target_state.target_stt;
            status_params.remaining_time_ms = p_server->state->stt_time.remaining_time_ms;
            (void) light_HSL_stt_server_status_publish(&p_server->server, &status_params);

            if (!p_server->value_updated)
            {
                p_server->light_HSL_stt_set_cb(p_server->server.model_instance_index, &(p_server->state->present_state), NULL, NULL);
                p_server->value_updated = true;
                app_light_HSL_stt_bind_check(p_server, MODEL_ID_LIGHTS_HSLSAT, false);
            }
        }
    }
    else
    {
        p_server->light_HSL_stt_set_cb(p_server->server.model_instance_index, &(p_server->state->present_state), NULL, NULL);
    }

    store_status_before_power_down(p_server->server.HSL_server->model_instance_index, OnPowerUp_Bind_HSL_Hue_State, p_server->state->dft_state.dft_hue, p_server->state->dft_state.dft_hue, p_server->state->target_state.target_hue);
    store_status_before_power_down(p_server->server.HSL_server->model_instance_index, OnPowerUp_Bind_HSL_Saturation_State, p_server->state->dft_state.dft_stt, p_server->state->dft_state.dft_stt, p_server->state->target_state.target_stt);
}

static void stt_state_timer_cb(void * p_context)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    app_light_HSL_stt_server_t * p_server = (app_light_HSL_stt_server_t *) p_context;

    /* Requirement: Process timing. Process the delay first (Non-zero delay will delay the required
     * state transition by the specified amount) and then the transition time.
     */
    if (p_server->state->stt_time.delay_ms != 0)
    {
        p_server->state->stt_time.delay_ms = 0;
        stt_state_value_update(p_server, false);
    }
    else if (p_server->state->stt_time.remaining_time_ms != 0)
    {
        p_server->state->stt_time.remaining_time_ms = 0;
        stt_state_value_update(p_server, false);
    }
    stt_state_process_timing(p_server, false);
}

static uint32_t get_remaining_time_ms(app_light_HSL_stt_server_t *p_server)
{
    if (p_server->state->stt_time.remaining_time_ms > 0 && p_server->state->stt_time.delay_ms == 0)
    {
        uint32_t current_time_clock_ms;
        uint16_t current_time_nb_wrap;
        uint32_t delta;

        mesh_run_time_get(&current_time_clock_ms, &current_time_nb_wrap);

        // only two conditions:
        // current_time_nb_wrap == last_time_nb_wrap
        if (current_time_nb_wrap == p_server->stt_last_time_nb_wrap)
        {
            delta = current_time_clock_ms - p_server->stt_last_time_clock_ms;
        }
        // current_time_nb_wrap == last_time_nb_wrap + 1
        else
        {
            delta = current_time_clock_ms + (0xFFFFFFFF - p_server->stt_last_time_clock_ms) + 1;
        }
        
        if (p_server->state->stt_time.remaining_time_ms >= delta && delta > 0)
        {
            return p_server->state->stt_time.remaining_time_ms - delta;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return p_server->state->stt_time.remaining_time_ms;
    }
}

static void light_HSL_stt_state_get_cb(light_HSL_stt_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_HSL_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_light_HSL_stt_server_t *p_server = PARENT_BY_FIELD_GET(app_light_HSL_stt_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the HSL state */
    p_server->light_HSL_stt_get_cb(p_server->server.model_instance_index, &(p_server->state->present_state), NULL, NULL);
    p_out->HSL_stt.present_stt = p_server->state->present_state.present_stt;
    p_out->HSL_stt.target_stt = p_server->state->target_state.target_stt;

    /* Requirement: Always report remaining time */
    p_out->HSL_stt.remaining_time_ms = get_remaining_time_ms(p_server);

}

static void light_HSL_stt_state_set_cb(light_HSL_stt_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_HSL_stt_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               light_HSL_status_params_u * p_out)
{
    app_light_HSL_stt_server_t *p_server = PARENT_BY_FIELD_GET(app_light_HSL_stt_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: %04X", __func__, p_self->model_instance_index, p_in->stt);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of HSL Hue value, process timing */
    p_server->value_updated = false;
    p_server->state->target_state.target_stt = p_in->stt;

    /* Ensure that Light HSL Actual state value is between Light HSL Range Min and Max values */
    if (p_server->state->target_state.target_stt != 0)
    {
        FORMAT_VALUE_RANGE(p_server->state->target_state.target_stt,
                        p_server->state->range_state.max_stt,
                        p_server->state->range_state.min_stt);
    }
    

    if (p_in_transition == NULL)
    {
        p_server->state->stt_time.delay_ms = 0;
        p_server->state->stt_time.remaining_time_ms = 0;
    }
    else
    {
        p_server->state->stt_time.delay_ms = p_in_transition->delay_ms;
        p_server->state->stt_time.remaining_time_ms = p_in_transition->transition_time_ms;
    }

    stt_state_value_update(p_server, false);
    stt_state_process_timing(p_server, false);

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->HSL_stt.present_stt = p_server->state->present_state.present_stt;
        p_out->HSL_stt.target_stt = p_server->state->target_state.target_stt;
        p_out->HSL_stt.remaining_time_ms= p_server->state->stt_time.remaining_time_ms;
    }

}



static void app_light_HSL_stt_bind_check(app_light_HSL_stt_server_t *p_server, uint32_t trigger_model, bool is_boot)
{
    static uint16_t repeat_bind_stt_st[LIGHT_HSL_INSTANCE_COUNT] = {0,};
    uint16_t *repeat_bind_stt = &repeat_bind_stt_st[p_server->server.model_instance_index];
    APP_LOG_INFO(" %s enter, repeat value %d, bind value %d", __func__, *repeat_bind_stt, p_server->state->present_state.present_stt);
    if ((*repeat_bind_stt != p_server->state->present_state.present_stt) || is_boot)
    {
        if(trigger_model != MODEL_ID_GENS_LVL)
        {
            /* check bind generic level state */
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_GENS_LVL, MODEL_ID_LIGHTS_HSLSAT,
                              &p_server->state->present_state.present_stt, sizeof(p_server->state->present_state.present_stt));
        }
        *repeat_bind_stt = p_server->state->present_state.present_stt;
    }
    return ;
}



static bool app_light_HSL_stt_bind_cb(void *p_server, uint32_t src_model_id, void *p_data, uint16_t data_len)
{
    app_light_HSL_stt_server_t * pl_server = (app_light_HSL_stt_server_t *)p_server;
    bool ret = false;

    APP_LOG_INFO("[%s] enter, SERVER[%d], src model %04X data length %d", __func__, pl_server->server.model_instance_index, src_model_id, data_len);

    if (pl_server != NULL)
    {
        switch(src_model_id)
        {
            case MODEL_ID_GENS_LVL:
            {
                if (data_len == 2)
                {
                    int16_t present_lvl = *(int16_t *)p_data;

                    if(pl_server->state->present_state.present_stt != present_lvl + 32768)
                    {
                        pl_server->state->present_state.present_stt = present_lvl + 32768;
                        if (pl_server->state->present_state.present_stt != 0)
                        {
                            FORMAT_VALUE_RANGE(pl_server->state->present_state.present_stt,
                                               pl_server->state->range_state.max_stt,
                                               pl_server->state->range_state.min_stt);
                        }
                        stt_state_value_update(pl_server, true);
                        ret = true;
                        if (pl_server->state->present_state.present_stt != (present_lvl + 32768) && p_data != NULL)
                        {
                            *(int16_t *)p_data = pl_server->state->present_state.present_stt - 32768;
                        }
                    }
                    APP_LOG_INFO("model gen level bind message length %d, value %d, HSL Saturation %d", data_len, present_lvl, pl_server->state->present_state.present_stt);
                }
                break;
            }
            case MODEL_ID_LIGHTS_HSL:
            {
                /* HSL server notice HSL Saturation server Saturation status has been changed */
                if (data_len == 2)
                {
                    uint16_t present_HSL_stt = *(int16_t *)p_data;
                    APP_LOG_INFO("model HSL server bind message length %d, value %d, HSL Saturation %d", data_len, present_HSL_stt, pl_server->state->present_state.present_stt);
                    ret = true;
                }
                break;
            }

            default:
                break;
        }

        if(ret)
        {
            app_light_HSL_stt_status_publish(pl_server);
            app_light_HSL_stt_bind_check(pl_server, src_model_id, false);
        }
    }

    return ret;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_light_HSL_stt_status_publish(app_light_HSL_stt_server_t * p_server)
{
    p_server->light_HSL_stt_get_cb(p_server->server.model_instance_index, &p_server->state->present_state, NULL, NULL);

    // if the timer isn't in list, no error occurs.
    //mesh_timer_clear(&p_server->app_timer.timer_id);

    light_HSL_stt_status_params_t status =
    {
        .present_stt = p_server->state->present_state.present_stt,
        .target_stt = p_server->state->target_state.target_stt,
        .remaining_time_ms = get_remaining_time_ms(p_server)
    };
    return light_HSL_stt_server_status_publish(&p_server->server, &status);
}

uint16_t app_light_HSL_stt_server_init(app_light_HSL_stt_server_t *p_server, uint8_t element_offset, app_light_HSL_set_cb_t set_cb, app_light_HSL_get_cb_t get_cb)
{
    if(( p_server == NULL) || (LIGHT_HSL_INSTANCE_COUNT <= element_offset))
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

    p_server->light_HSL_stt_set_cb = set_cb;
    p_server->light_HSL_stt_get_cb = get_cb;

    //p_server->state->present_state.present_stt = 0;
    p_server->state->target_state.target_stt = 0;

    p_server->state->stt_time.remaining_time_ms = 0;
    p_server->state->stt_time.delay_ms = 0;
    
    p_server->state->range_state.max_hue = UINT16_MAX;
    p_server->state->range_state.min_hue = 0;
    
    p_server->state->range_state.max_stt = UINT16_MAX;
    p_server->state->range_state.min_stt = 0;
    

    
    p_server->stt_last_time_clock_ms = 0;
    p_server->stt_last_time_nb_wrap = 0;


    p_server->client_address = MESH_INVALID_ADDR;

    p_server->value_updated = false;

    p_server->server.settings.p_callbacks = &light_HSL_stt_srv_cbs,
        
    p_server->stt_state_timer.callback = stt_state_timer_cb;
    p_server->stt_state_timer.p_args = p_server;
    p_server->stt_state_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->stt_state_timer.reload = false;

    mesh_model_bind_list_add(MODEL_ID_LIGHTS_HSLSAT, element_offset, (void *)p_server, app_light_HSL_stt_bind_cb);

    //check saturation element binding level
    app_light_HSL_stt_bind_check(p_server, element_offset, true);

    return light_HSL_stt_server_init(&p_server->server, element_offset);
}

