/**
 *****************************************************************************************
 *
 * @file app_power_level_server.c
 *
 * @brief APP Power Level Server API Implementation.
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
#include "app_power_level_server.h"
#include "app_power_level_setup_server.h"
#include "generic_power_level_server.h"
#include "app_log.h"
#include "user_app.h"
#include "mesh_bind.h"
#include "generic_power_onoff_behavior.h"
#include "mesh_scenes_common.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void generic_power_level_state_set_cb(generic_power_level_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const generic_power_level_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               generic_power_level_status_params_u * p_out);

static void generic_power_level_state_get_cb(generic_power_level_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_power_level_status_params_u * p_out);

static void generic_power_level_last_state_get_cb(generic_power_level_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_power_level_status_params_u * p_out);

static void generic_power_level_default_state_get_cb(generic_power_level_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_power_level_status_params_u * p_out);

static void generic_power_level_range_state_get_cb(generic_power_level_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_power_level_status_params_u * p_out);

static void app_generic_power_level_bind_check(app_generic_power_level_server_t *p_server, uint32_t trigger_model);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

typedef struct
{
    app_generic_power_level_server_t *p_server;
    uint8_t model_instance_index;
}power_server_t;

app_generic_power_level_server_t *power_server_ins[GENERIC_POWER_LEVEL_SERVER_INSTANCE_COUNT];

const generic_power_level_server_callbacks_t generic_power_level_srv_cbs =
{
    .generic_power_level_cbs.set_cb = generic_power_level_state_set_cb,
    .generic_power_level_cbs.get_cb = generic_power_level_state_get_cb,

    .generic_power_level_last_cbs.get_cb = generic_power_level_last_state_get_cb,

    //.generic_power_level_dft_cbs.set_cb = generic_power_level_default_state_set_cb,
    .generic_power_level_dft_cbs.get_cb = generic_power_level_default_state_get_cb,

    //.generic_power_level_range_cbs.set_cb = generic_power_level_range_state_set_cb,
    .generic_power_level_range_cbs.get_cb = generic_power_level_range_state_get_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void power_state_process_timing(app_generic_power_level_server_t * p_server)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    uint32_t status = MESH_ERROR_NO_ERROR;
    mesh_timer_t *p_timer = &p_server->actual_state_timer;
    //APP_LOG_INFO("SERVER[%d] -- before -- mesh app timer clear, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
    
    // if the timer isn't in list, no error occurs.
    mesh_timer_clear(&p_timer->timer_id);

    //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer clear, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);

    /* Process timing requirements */
    if (p_server->app_state.delay_ms != 0)
    {
        p_timer->delay_ms = p_server->app_state.delay_ms;
        status = mesh_timer_set(p_timer);
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
    }
    else if (p_server->app_state.remaining_time_ms != 0)
    {
        p_timer->delay_ms = p_server->app_state.remaining_time_ms;
        status = mesh_timer_set(p_timer);
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
        mesh_run_time_get(&p_server->actual_last_time_clock_ms, &p_server->actual_last_time_nb_wrap);
    }

    if (status != MESH_ERROR_NO_ERROR)
    {
       APP_LOG_INFO("State transition timer error");
    }
}

static void power_state_value_update(app_generic_power_level_server_t * p_server, bool immed)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    if (!immed)
    {
        /* Requirement: If delay and transition time is zero, current state changes to the target state. */
        if ((p_server->app_state.delay_ms == 0 && p_server->app_state.remaining_time_ms == 0) )
        {
            p_server->app_state.state.present_power = p_server->app_state.state.target_power;
            /* Requirement: The Last Power should be an non-zero value. */
            if (0 != p_server->app_state.state.present_power)
            {
                p_server->app_state.state.last_power = p_server->app_state.state.present_power;
            }
            generic_power_level_status_params_t status_params;
            status_params.present_power = p_server->app_state.state.present_power;
            status_params.target_power = p_server->app_state.state.target_power;
            status_params.remaining_time_ms = p_server->app_state.remaining_time_ms;
            generic_power_level_server_status_publish(&p_server->server, &status_params);

            if (!p_server->value_updated)
            {
                p_server->generic_power_level_set_cb(p_server->server.model_instance_index, &(p_server->app_state.state));
                p_server->value_updated = true;
                app_generic_power_level_bind_check(p_server, MODEL_ID_GENS_PLVL);
            }
        }
    }
    else
    {
        if (0 != p_server->app_state.state.present_power)
        {
            p_server->app_state.state.last_power = p_server->app_state.state.present_power;
        }
        p_server->generic_power_level_set_cb(p_server->server.model_instance_index, &(p_server->app_state.state));
    }
    store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_Power_Level_State, 0, 
                                   p_server->app_state.state.default_power == 0 ? p_server->app_state.state.last_power : p_server->app_state.state.default_power, 
                                   p_server->app_state.state.target_power);
}

static void power_state_timer_cb(void * p_context)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    app_generic_power_level_server_t * p_server = (app_generic_power_level_server_t *) p_context;

    /* Requirement: Process timing. Process the delay first (Non-zero delay will delay the required
     * state transition by the specified amount) and then the transition time.
     */
    if (p_server->app_state.delay_ms != 0)
    {
        p_server->app_state.delay_ms = 0;
        power_state_value_update(p_server, false);
    }
    else if (p_server->app_state.remaining_time_ms != 0)
    {
        p_server->app_state.remaining_time_ms = 0;
        power_state_value_update(p_server, false);
    }
    power_state_process_timing(p_server);
}

static uint32_t get_remaining_time_ms(app_generic_power_level_server_t *p_server)
{
    if (p_server->app_state.remaining_time_ms > 0 && p_server->app_state.delay_ms == 0)
    {
        uint32_t current_time_clock_ms;
        uint16_t current_time_nb_wrap;
        uint32_t delta;

        mesh_run_time_get(&current_time_clock_ms, &current_time_nb_wrap);

        // only two conditions:
        // current_time_nb_wrap == last_time_nb_wrap
        if (current_time_nb_wrap == p_server->actual_last_time_nb_wrap)
        {
            delta = current_time_clock_ms - p_server->actual_last_time_clock_ms;
        }
        // current_time_nb_wrap == last_time_nb_wrap + 1
        else
        {
            delta = current_time_clock_ms + (0xFFFFFFFF - p_server->actual_last_time_clock_ms) + 1;
        }
        
        if (p_server->app_state.remaining_time_ms >= delta && delta > 0)
        {
            return p_server->app_state.remaining_time_ms - delta;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return p_server->app_state.remaining_time_ms;
    }
}

static void generic_power_level_state_get_cb(generic_power_level_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_power_level_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_generic_power_level_server_t *p_server = PARENT_BY_FIELD_GET(app_generic_power_level_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the power state */
    p_server->generic_power_level_get_cb(p_server->server.model_instance_index, &p_server->app_state.state);
    p_out->power.present_power = p_server->app_state.state.present_power;
    p_out->power.target_power = p_server->app_state.state.target_power;

    /* Requirement: Always report remaining time */
    p_out->power.remaining_time_ms = get_remaining_time_ms(p_server);
}


static void generic_power_level_state_set_cb(generic_power_level_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const generic_power_level_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               generic_power_level_status_params_u * p_out)
{
    app_generic_power_level_server_t *p_server = PARENT_BY_FIELD_GET(app_generic_power_level_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: %d.", __func__, p_self->model_instance_index, p_in->power);
    
    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of Power value, process timing */
    p_server->value_updated = false;
    p_server->app_state.state.target_power = p_in->power;

    /* Ensure that Power Actual state value is between Power Range Min and Max values */
    if (p_server->app_state.state.target_power != 0)
    {
        if (p_server->app_state.state.target_power > p_server->app_state.state.max_power)
        {
            p_server->app_state.state.target_power = p_server->app_state.state.max_power;
        }
        else if (p_server->app_state.state.target_power < p_server->app_state.state.min_power)
        {
            p_server->app_state.state.target_power = p_server->app_state.state.min_power;
        }
    }

    if (p_in_transition == NULL)
    {
        p_server->app_state.delay_ms = 0;
        p_server->app_state.remaining_time_ms = 0;
    }
    else
    {
        p_server->app_state.delay_ms = p_in_transition->delay_ms;
        p_server->app_state.remaining_time_ms = p_in_transition->transition_time_ms;
    }
    
    power_state_value_update(p_server, false);
    power_state_process_timing(p_server);

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->power.present_power = p_server->app_state.state.present_power;
        p_out->power.target_power= p_server->app_state.state.target_power;
        p_out->power.remaining_time_ms= p_server->app_state.remaining_time_ms;
    }
}




static void generic_power_level_last_state_get_cb(generic_power_level_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_power_level_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_generic_power_level_server_t *p_server = PARENT_BY_FIELD_GET(app_generic_power_level_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the Power Level state */
    p_server->generic_power_level_get_cb(p_server->server.model_instance_index, &p_server->app_state.state);
    p_out->power_last.power= p_server->app_state.state.last_power;
}

static void generic_power_level_default_state_get_cb(generic_power_level_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_power_level_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_generic_power_level_server_t *p_server = PARENT_BY_FIELD_GET(app_generic_power_level_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the Power Level state */
    p_server->generic_power_level_get_cb(p_server->server.model_instance_index, &p_server->app_state.state);
    p_out->power_dft.power= p_server->app_state.state.default_power;
}



static void generic_power_level_range_state_get_cb(generic_power_level_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_power_level_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_generic_power_level_server_t *p_server = PARENT_BY_FIELD_GET(app_generic_power_level_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the Power Level state */
    p_server->generic_power_level_get_cb(p_server->server.model_instance_index, &p_server->app_state.state);
    p_out->power_range.status_code= p_server->app_state.state.status_code;
    p_out->power_range.min_power= p_server->app_state.state.min_power;
    p_out->power_range.max_power= p_server->app_state.state.max_power;
}

static void app_generic_power_level_bind_check(app_generic_power_level_server_t *p_server, uint32_t trigger_model)
{
    static uint16_t repeat_bind_power_st[GENERIC_POWER_LEVEL_SERVER_INSTANCE_COUNT] = {0,};
    uint16_t *repeat_bind_power = &repeat_bind_power_st[p_server->server.model_instance_index];

    APP_LOG_INFO(" %s enter, repeat value %d, bind value %d", __func__, *repeat_bind_power, p_server->app_state.state.present_power);

    if (*repeat_bind_power != p_server->app_state.state.present_power)
    {
        if (trigger_model != MODEL_ID_GENS_LVL)
        {
            /* check bind generic level state */
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_GENS_LVL, MODEL_ID_GENS_PLVL,
                              &p_server->app_state.state.present_power, sizeof(p_server->app_state.state.present_power));
        }

        if (trigger_model != MODEL_ID_GENS_OO)
        {
            /* check bind generic onoff state */
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_GENS_OO, MODEL_ID_GENS_PLVL, 
                              &p_server->app_state.state.present_power, sizeof(p_server->app_state.state.present_power));
        }
        *repeat_bind_power = p_server->app_state.state.present_power;
    }
    return ;
}

static bool app_generic_power_level_bind_cb(void *p_server, uint32_t src_model_id, void *p_data, uint16_t data_len)
{
    app_generic_power_level_server_t * pl_server = (app_generic_power_level_server_t *)p_server;
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

                    if(pl_server->app_state.state.present_power != present_lvl + 32768)
                    {
                        pl_server->app_state.state.present_power = present_lvl + 32768;
                        if (pl_server->app_state.state.present_power != 0)
                        {
                            if (pl_server->app_state.state.present_power > pl_server->app_state.state.max_power)
                            {
                                pl_server->app_state.state.present_power = pl_server->app_state.state.max_power;
                            }
                            else if (pl_server->app_state.state.present_power < pl_server->app_state.state.min_power)
                            {
                                pl_server->app_state.state.present_power = pl_server->app_state.state.min_power;
                            }
                        }
                        power_state_value_update(pl_server, true);
                        ret = true;
                        if (pl_server->app_state.state.present_power != present_lvl + 32768 && p_data != NULL)
                        {
                            *(int16_t *)p_data = pl_server->app_state.state.present_power - 32768;
                        }
                    }
                    APP_LOG_INFO("model gen level bind message length %d, value %d, power actual %d", 
                                   data_len, present_lvl, pl_server->app_state.state.present_power);
                }
                break;
            }
            case MODEL_ID_GENS_OO:
            {
                if (data_len == 1)
                {
                    uint8_t onoff = *(uint8_t *)p_data;

                    if ((onoff == 0x00) && (pl_server->app_state.state.present_power != 0))//onoff :off
                    {
                        pl_server->app_state.state.present_power = 0x00;
                        power_state_value_update(pl_server, true);
                        ret = true;
                    }
                    else if ((onoff == 0x01) && (pl_server->app_state.state.present_power == 0))//onoff :on
                    {
                        if(pl_server->app_state.state.default_power == 0x0000)
                        {
                            pl_server->app_state.state.present_power = pl_server->app_state.state.last_power;
                        }
                        else
                        {
                            pl_server->app_state.state.present_power = pl_server->app_state.state.default_power;
                        }
                        power_state_value_update(pl_server, true);

                        ret = true;
                    }
                    APP_LOG_INFO("model gen onoff bind message length %d, value %d, power actual %d", data_len, onoff, pl_server->app_state.state.present_power);
                }
                break;
            }
            default:
                break;
        }

        if(ret)
        {
            app_generic_power_level_status_publish(pl_server);
            app_generic_power_level_bind_check(pl_server, src_model_id);
        }
    }

    return ret;
}

static void app_generic_power_level_scene_recall_cb(void *p_server, uint8_t *stored_state, uint16_t state_length)
{
    app_generic_power_level_server_t *recal_server = (app_generic_power_level_server_t *)p_server;

    APP_LOG_INFO(" [%s] enter ", __func__);
    APP_LOG_INFO("server power level recall state: value %d, length %d", *(int16_t *)stored_state, state_length);

    if (NULL == p_server)
    {
        APP_LOG_INFO(" [%s] exit : Unknow server state to recall !!!", __func__);
        return ;
    }

    if (state_length != sizeof(recal_server->app_state.state.present_power))
    {
        APP_LOG_INFO(" [%s] exit : invalid recall param!!!", __func__);
        return ;
    }
    recal_server->app_state.state.present_power = *(int16_t *)stored_state;

    generic_power_level_status_params_t status =
    {
        .present_power = recal_server->app_state.state.present_power,
        .target_power = recal_server->app_state.state.target_power,
        .remaining_time_ms = recal_server->app_state.remaining_time_ms
    };
    APP_LOG_INFO("debug publish status: 0x%04X 0x%04X 0x%04X", status.present_power, status.target_power, status.remaining_time_ms);
    generic_power_level_server_status_publish(&recal_server->server, &status);

    recal_server->generic_power_level_set_cb(recal_server->server.model_instance_index, &(recal_server->app_state.state));
}
/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_generic_power_level_status_publish(app_generic_power_level_server_t * p_server)
{
    p_server->generic_power_level_get_cb(p_server->server.model_instance_index, &p_server->app_state.state);

    // if the timer isn't in list, no error occurs.
    //mesh_timer_clear(&p_server->app_timer.timer_id);

    generic_power_level_status_params_t status =
    {
        .present_power = p_server->app_state.state.present_power,
        .target_power = p_server->app_state.state.target_power,
        .remaining_time_ms = get_remaining_time_ms(p_server),
    };
    APP_LOG_INFO("debug publish status: 0x%04X 0x%04X 0x%04X", status.present_power, status.target_power, status.remaining_time_ms);
    return generic_power_level_server_status_publish(&p_server->server, &status);
}

uint16_t app_generic_power_level_server_init(app_generic_power_level_server_t *p_server, uint8_t element_offset, 
                                             app_generic_power_level_set_cb_t set_cb, app_generic_power_level_get_cb_t get_cb)
{
    if(( p_server == NULL) || (GENERIC_POWER_LEVEL_SERVER_INSTANCE_COUNT <= element_offset))
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

    p_server->generic_power_level_set_cb = set_cb;
    p_server->generic_power_level_get_cb = get_cb;

    //p_server->app_state.state.present_power = 0;
    power_up_sequence_behavior(element_offset, element_offset,
                               OnPowerUp_Bind_Power_Level_State,&p_server->app_state.state.present_power);
    p_server->app_state.state.target_power = 0;
    p_server->app_state.state.last_power = 0xFFFF;
    p_server->app_state.remaining_time_ms = 0;
    p_server->app_state.delay_ms = 0,
    
    p_server->app_state.state.default_power= 0;
    p_server->app_state.state.status_code = STATUS_CODES_SUCCESS;
    p_server->app_state.state.min_power= 0x0001;
    p_server->app_state.state.max_power= 0xFFFF;

    p_server->actual_last_time_clock_ms = 0;
    p_server->actual_last_time_nb_wrap = 0;
    
    p_server->client_address = MESH_INVALID_ADDR;

    p_server->value_updated = false,

    p_server->server.settings.p_callbacks = &generic_power_level_srv_cbs;
        
    p_server->actual_state_timer.callback = power_state_timer_cb;
    p_server->actual_state_timer.p_args = p_server;
    p_server->actual_state_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->actual_state_timer.reload = false;

    power_server_ins[element_offset] = p_server;
    
    mesh_model_bind_list_add(MODEL_ID_GENS_PLVL, element_offset, (void *)p_server, app_generic_power_level_bind_cb);
    mesh_scenes_state_store_with_scene(element_offset, app_generic_power_level_scene_recall_cb, (void *)p_server, (uint8_t *)&p_server->app_state.state.present_power, sizeof(p_server->app_state.state.present_power));

    return generic_power_level_server_init(&p_server->server, element_offset);
}


