/**
 *****************************************************************************************
 *
 * @file app_onoff_server.c
 *
 * @brief APP On Off API Implementation.
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
#include "app_onoff_server.h"
#include "generic_onoff_server.h"
#include "app_log.h"
#include "user_app.h"
#include "mesh_bind.h"
#include "mesh_scenes_common.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void generic_onoff_state_set_cb(generic_onoff_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const generic_onoff_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               generic_onoff_status_params_t * p_out);

static void generic_onoff_state_get_cb(generic_onoff_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_onoff_status_params_t * p_out);

static void app_onoff_bind_check(app_onoff_server_t *p_server, uint32_t trigger_model);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const generic_onoff_server_callbacks_t onoff_srv_cbs =
{
    .onoff_cbs.set_cb = generic_onoff_state_set_cb,
    .onoff_cbs.get_cb = generic_onoff_state_get_cb,
};

static store_power_status_cb_t store_power_status_cb = NULL;

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void onoff_state_process_timing(app_onoff_server_t * p_server)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    uint32_t status = MESH_ERROR_NO_ERROR;

    //APP_LOG_INFO("SERVER[%d] -- before -- mesh app timer clear, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
    
    // if the timer isn't in list, no error occurs.
    mesh_timer_clear(&p_server->app_timer.timer_id);

    //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer clear, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);

    /* Process timing requirements */
    if (p_server->state.delay_ms != 0)
    {
        p_server->app_timer.delay_ms = p_server->state.delay_ms;
        status = mesh_timer_set(&p_server->app_timer);
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
    }
    else if (p_server->state.remaining_time_ms != 0)
    {
        p_server->app_timer.delay_ms = p_server->state.remaining_time_ms;
        status = mesh_timer_set(&p_server->app_timer);
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
   
        mesh_run_time_get(&p_server->last_time_clock_ms, &p_server->last_time_nb_wrap);
    }

    if (status != MESH_ERROR_NO_ERROR)
    {
       // APP_LOG_INFO("State transition timer error");
    }
}

static void onoff_state_value_update(app_onoff_server_t * p_server)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    /* Requirement: If delay and transition time is zero, current state changes to the target state. */
    if ((p_server->state.delay_ms == 0 && p_server->state.remaining_time_ms == 0) ||
    /* Requirement: If current state is 0 (checked earlier) and target state is 1, current state value changes
     * to the target state value immediately after the delay.
     */
        (p_server->state.delay_ms == 0 && p_server->state.target_onoff == 1))
    {
        p_server->state.present_onoff = p_server->state.target_onoff;

        generic_onoff_status_params_t status_params;
        status_params.present_on_off = p_server->state.present_onoff;
        status_params.target_on_off = p_server->state.target_onoff;
        status_params.remaining_time_ms = p_server->state.remaining_time_ms;
        generic_onoff_server_status_publish(&p_server->server, &status_params);

        if (!p_server->value_updated)
        {
            p_server->onoff_set_cb(p_server->server.model_instance_index, p_server->state.present_onoff);
            p_server->value_updated = true;
        }

        app_onoff_bind_check(p_server, MODEL_ID_GENS_OO);
    }
}

static void onoff_state_timer_cb(void * p_context)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    app_onoff_server_t * p_server = (app_onoff_server_t *) p_context;

    /* Requirement: Process timing. Process the delay first (Non-zero delay will delay the required
     * state transition by the specified amount) and then the transition time.
     */
    if (p_server->state.delay_ms != 0)
    {
        p_server->state.delay_ms = 0;
        onoff_state_value_update(p_server);
    }
    else if (p_server->state.remaining_time_ms != 0)
    {
        p_server->state.remaining_time_ms = 0;
        onoff_state_value_update(p_server);
    }
    onoff_state_process_timing(p_server);
}

static uint32_t get_remaining_time_ms(app_onoff_server_t *p_server)
{
    /* Requirement: Always report remaining time */
    if (p_server->state.remaining_time_ms > 0 && p_server->state.delay_ms == 0)
    {
        uint32_t current_time_clock_ms;
        uint16_t current_time_nb_wrap;
        uint32_t delta;

        mesh_run_time_get(&current_time_clock_ms, &current_time_nb_wrap);

        // only two conditions:
        // current_time_nb_wrap == last_time_nb_wrap
        if (current_time_nb_wrap == p_server->last_time_nb_wrap)
        {
            delta = current_time_clock_ms - p_server->last_time_clock_ms;
        }
        // current_time_nb_wrap == last_time_nb_wrap + 1
        else
        {
            delta = current_time_clock_ms + (0xFFFFFFFF - p_server->last_time_clock_ms) + 1;
        }
        
        if (p_server->state.remaining_time_ms >= delta && delta > 0)
        {
            return (p_server->state.remaining_time_ms - delta);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return p_server->state.remaining_time_ms;
    }
}

static void generic_onoff_state_get_cb(generic_onoff_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_onoff_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_onoff_server_t *p_server = PARENT_BY_FIELD_GET(app_onoff_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the OnOff state */
    p_server->onoff_get_cb(p_server->server.model_instance_index, &p_server->state.present_onoff);
    p_out->present_on_off = p_server->state.present_onoff;
    p_out->target_on_off = p_server->state.target_onoff;
    p_out->remaining_time_ms = get_remaining_time_ms(p_server);
}

static void generic_onoff_state_set_cb(generic_onoff_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const generic_onoff_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               generic_onoff_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: %d", __func__, p_self->model_instance_index, p_in->on_off);

    app_onoff_server_t *p_server = PARENT_BY_FIELD_GET(app_onoff_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of OnOff value, process timing */
    p_server->value_updated = false;
    p_server->state.target_onoff = p_in->on_off;
    if (p_in_transition == NULL)
    {
        p_server->state.delay_ms = 0;
        p_server->state.remaining_time_ms = 0;
    }
    else
    {
        p_server->state.delay_ms = p_in_transition->delay_ms;
        p_server->state.remaining_time_ms = p_in_transition->transition_time_ms;
    }

    if (store_power_status_cb != NULL)
    {
        store_power_status_cb(p_server->server.model_instance_index, OnPowerUp_Bind_OnOff_State, 0, 1, p_server->state.target_onoff);
    }

    onoff_state_value_update(p_server);
    onoff_state_process_timing(p_server);

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->present_on_off = p_server->state.present_onoff;
        p_out->target_on_off = p_server->state.target_onoff;
        p_out->remaining_time_ms = p_server->state.remaining_time_ms;
    }
}

static void app_onoff_scene_recall_cb(void *p_server, uint8_t *stored_state, uint16_t state_length)
{
    app_onoff_server_t *recal_server = (app_onoff_server_t *)p_server;

    APP_LOG_INFO(" [%s] enter ", __func__);
    APP_LOG_INFO("server onoff recall state: value %d, length %d", *stored_state, state_length);

    if (NULL == p_server)
    {
        APP_LOG_INFO(" [%s] exit : Unknow server state to recall !!!", __func__);
        return ;
    }

    if (state_length != sizeof(recal_server->state.present_onoff))
    {
        APP_LOG_INFO(" [%s] exit : invalid recall param!!!", __func__);
        return ;
    }
    recal_server->state.present_onoff = *(bool *)stored_state;

    generic_onoff_status_params_t status =
    {
        .present_on_off = recal_server->state.present_onoff,
        .target_on_off = recal_server->state.target_onoff,
        .remaining_time_ms = recal_server->state.remaining_time_ms
    };

    generic_onoff_server_status_publish(&recal_server->server, &status);

    recal_server->onoff_set_cb(recal_server->server.model_instance_index, recal_server->state.present_onoff);
}

static void app_onoff_bind_check(app_onoff_server_t *p_server, uint32_t trigger_model)
{
    static bool repeat_bind_onoff_st[GENERIC_ONOFF_SERVER_INSTANCE_COUNT] = {0,};
    bool *repeat_bind_onoff = &repeat_bind_onoff_st[p_server->server.model_instance_index];

    APP_LOG_INFO(" [%s] enter, repeat value %d, bind value %d", __func__, *repeat_bind_onoff, p_server->state.present_onoff);

    if (*repeat_bind_onoff != p_server->state.present_onoff)
    {
        if (trigger_model != MODEL_ID_LIGHTS_LN)
        {
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_LN, MODEL_ID_GENS_OO, 
                              &p_server->state.present_onoff, sizeof(p_server->state.present_onoff));
        }

        if (trigger_model != MODEL_ID_GENS_PLVL)
        {
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_GENS_PLVL, MODEL_ID_GENS_OO, 
                              &p_server->state.present_onoff, sizeof(p_server->state.present_onoff));
        }

        if (trigger_model != MODEL_ID_LIGHTS_LC)
        {
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_LC, MODEL_ID_GENS_OO, 
                              &p_server->state.present_onoff, sizeof(p_server->state.present_onoff));
        }

        *repeat_bind_onoff = p_server->state.present_onoff;
    }
}

static bool app_onoff_bind_cb(void *p_server, uint32_t src_model_id, void *p_data, uint16_t data_len)
{
    app_onoff_server_t * pl_server = (app_onoff_server_t *)p_server;
    bool ret = false;

    APP_LOG_INFO("[%s] enter, SERVER[%d], src model %04X", __func__, pl_server->server.model_instance_index, src_model_id);

    if (NULL != pl_server)
    {
        switch(src_model_id)
        {
            case MODEL_ID_LIGHTS_LN:
            {
                if (data_len == 2)
                {
                    uint16_t present_ln = *(uint16_t *)p_data;

                    if (pl_server->state.present_onoff != (present_ln? 1 : 0))
                    {
                        pl_server->state.present_onoff = present_ln? 1 : 0;
                        pl_server->onoff_set_cb(pl_server->server.model_instance_index, pl_server->state.present_onoff);

                        ret = true;
                    }
                    APP_LOG_INFO("Model light lightness bind message length %d, value %d, onoff %d", data_len, present_ln, pl_server->state.present_onoff);
                }
                break;
            }
            case MODEL_ID_GENS_PLVL:
            {
                if (data_len == 2)
                {
                    uint16_t present_power = *(uint16_t *)p_data;

                    if (pl_server->state.present_onoff != (present_power? 1 : 0))
                    {
                        pl_server->state.present_onoff = present_power? 1 : 0;
                        pl_server->onoff_set_cb(pl_server->server.model_instance_index, pl_server->state.present_onoff);

                        ret = true;
                    }
                    APP_LOG_INFO("Model generic power level bind message length %d, value %d, onoff %d", data_len, present_power, pl_server->state.present_onoff);
                }
            }
            case MODEL_ID_LIGHTS_LC:
            {
                if (data_len == 1)
                {
                    uint8_t present_onoff = *(uint8_t *)p_data;

                    if (pl_server->state.present_onoff != present_onoff)
                    {
                        pl_server->state.present_onoff = present_onoff;
                        pl_server->onoff_set_cb(pl_server->server.model_instance_index, pl_server->state.present_onoff);
                        ret = true;
                    }
                    APP_LOG_INFO("Model light lc onoff bind message length %d, value %d, onoff %d", data_len, present_onoff, pl_server->state.present_onoff);
                }
            }
            default:
                break;
        }

        //if(ret)
        {
            app_generic_onoff_status_publish(pl_server);
            app_onoff_bind_check(pl_server, src_model_id);
        }
    }

    return ret;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */
void app_generic_onoff_store_power_cb_register(store_power_status_cb_t cb)
{
    store_power_status_cb = cb;
}

uint16_t app_generic_onoff_status_publish(app_onoff_server_t * p_server)
{
    p_server->onoff_get_cb(p_server->server.model_instance_index, &p_server->state.present_onoff);

    /*p_server->state.target_onoff = p_server->state.present_onoff;[Nordic codes]
    p_server->state.delay_ms = 0;
    p_server->state.remaining_time_ms = 0;

    // if the timer isn't in list, no error occurs.
    mesh_timer_clear(&p_server->app_timer.timer_id);*/

    generic_onoff_status_params_t status =
    {
        .present_on_off = p_server->state.present_onoff,
        .target_on_off = p_server->state.target_onoff,
        .remaining_time_ms = get_remaining_time_ms(p_server)
    };
    return generic_onoff_server_status_publish(&p_server->server, &status);
}

uint16_t app_generic_onoff_server_init(app_onoff_server_t *p_server, uint8_t element_offset, app_generic_onoff_set_cb_t set_cb, app_generic_onoff_get_cb_t get_cb)
{
    if(( p_server == NULL) || (GENERIC_ONOFF_SERVER_INSTANCE_COUNT <= element_offset))
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

    p_server->onoff_set_cb = set_cb;
    p_server->onoff_get_cb = get_cb;

    p_server->state.present_onoff = 0;
    p_server->state.target_onoff = 0;
    p_server->state.remaining_time_ms = 0;
    p_server->state.delay_ms = 0;

    p_server->last_time_clock_ms = 0;
    p_server->last_time_nb_wrap = 0;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->value_updated = false;

    p_server->server.settings.p_callbacks = &onoff_srv_cbs;
        
    p_server->app_timer.callback = onoff_state_timer_cb;
    p_server->app_timer.p_args = p_server;
    p_server->app_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->app_timer.reload = false;

    mesh_model_bind_list_add(MODEL_ID_GENS_OO, element_offset, (void *)p_server, app_onoff_bind_cb);
    mesh_scenes_state_store_with_scene(element_offset, app_onoff_scene_recall_cb, (void *)p_server, (uint8_t *)&p_server->state.present_onoff, sizeof(p_server->state.present_onoff));

    return generic_onoff_server_init(&p_server->server, element_offset);
}
