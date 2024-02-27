/**
 *****************************************************************************************
 *
 * @file app_light_HSL_server.c
 *
 * @brief APP LIGHT HSL Server API Implementation.
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
#include "app_light_HSL_setup_server.h"
#include "light_HSL_server.h"
#include "app_log.h"
#include "user_app.h"
#include "mesh_bind.h"
#include "mesh_scenes_common.h"
#include "generic_power_onoff_behavior.h"

/*
 * DEFINES
 ****************************************************************************************
 */


/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void light_HSL_state_set_cb(light_HSL_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_HSL_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               light_HSL_status_params_u * p_out);

static void light_HSL_state_get_cb(light_HSL_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_HSL_status_params_u * p_out);

static void light_HSL_target_state_get_cb(light_HSL_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_HSL_status_params_u * p_out);

static void light_HSL_default_state_get_cb(light_HSL_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_HSL_status_params_u * p_out);

static void light_HSL_range_state_get_cb(light_HSL_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_HSL_status_params_u * p_out);

static void app_light_HSL_bind_check(app_light_HSL_server_t *p_server, uint32_t trigger_model);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

typedef struct
{
    app_light_HSL_server_t *p_server;
    uint8_t model_instance_index;
}HSL_server_t;


const light_HSL_server_callbacks_t light_HSL_srv_cbs =
{
    .light_HSL_cbs.set_cb = light_HSL_state_set_cb,
    .light_HSL_cbs.get_cb = light_HSL_state_get_cb,
    .light_HSL_cbs.target_get_cb = light_HSL_target_state_get_cb,

    //.light_HSL_dft_cbs.set_cb = light_HSL_default_state_set_cb,
    .light_HSL_dft_cbs.get_cb = light_HSL_default_state_get_cb,

    //.light_HSL_range_cbs.set_cb = light_HSL_range_state_set_cb,
    .light_HSL_range_cbs.get_cb = light_HSL_range_state_get_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */


static void HSL_state_process_timing(app_light_HSL_server_t * p_server, bool linear)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    uint32_t status = MESH_ERROR_NO_ERROR;
    mesh_timer_t *p_timer = &(p_server->HSL_state_timer);
    //APP_LOG_INFO("SERVER[%d] -- before -- mesh app timer clear, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
    
    // if the timer isn't in list, no error occurs.
    mesh_timer_clear(&p_timer->timer_id);

    //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer clear, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);

    /* Process timing requirements */
    if (p_server->state.HSL_time.delay_ms != 0)
    {
        p_timer->delay_ms = p_server->state.HSL_time.delay_ms;
        status = mesh_timer_set(p_timer);
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
    }
    else if (p_server->state.HSL_time.remaining_time_ms != 0)
    {
        p_timer->delay_ms = p_server->state.HSL_time.remaining_time_ms;
        status = mesh_timer_set(p_timer);
        //APP_LOG_INFO("SERVER[%d] -- after -- mesh app timer set, timer_id = %ld.", p_server->server.model_instance_index, p_server->app_timer.timer_id);
        mesh_run_time_get(&p_server->HSL_last_time_clock_ms, &p_server->HSL_last_time_nb_wrap);
    }

    if (status != MESH_ERROR_NO_ERROR)
    {
       // APP_LOG_INFO("State transition timer error");
    }
}

static void HSL_state_value_update(app_light_HSL_server_t * p_server, bool immed)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    if (!immed)
    {
        /* Requirement: If delay and transition time is zero, current state changes to the target state. */
        if ((p_server->state.HSL_time.delay_ms == 0 && p_server->state.HSL_time.remaining_time_ms == 0) )
        {
            p_server->state.present_state.present_hue = p_server->state.target_state.target_hue;
            p_server->state.present_state.present_stt = p_server->state.target_state.target_stt;
            p_server->state.present_state.present_ln = p_server->state.target_state.target_ln;
            
            light_HSL_status_params_t status_params;
            status_params.HSL_hue = p_server->state.present_state.present_hue,
            status_params.HSL_stt = p_server->state.present_state.present_stt,
            status_params.HSL_ln = p_server->state.present_state.present_ln,
            status_params.remaining_time_ms = p_server->state.HSL_time.remaining_time_ms,
            
            (void) light_HSL_server_status_publish(&p_server->server, &status_params);

            if (!p_server->value_updated)
            {
                p_server->light_HSL_set_cb(p_server->server.model_instance_index, &(p_server->state.present_state), NULL, NULL);
                app_light_HSL_bind_check(p_server, MODEL_ID_LIGHTS_HSL);
                // TODO: enhance logical judgement here
                p_server->light_HSL_set_cb(p_server->server.model_instance_index, &(p_server->state.present_state), NULL, NULL);
                p_server->value_updated = true;
                
            }
        }
    }
    else
    {
        p_server->light_HSL_set_cb(p_server->server.model_instance_index, &(p_server->state.present_state), NULL, NULL);
    }
    p_server->light_HSL_get_cb(p_server->server.model_instance_index, NULL, &(p_server->state.dft_state), NULL);//default lightness maybe changed by lightness model.
    store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_Lightness_State, 0, p_server->state.dft_state.dft_ln== 0 ? p_server->state.target_state.target_ln: p_server->state.dft_state.dft_ln, p_server->state.target_state.target_ln);
    store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_HSL_Hue_State, p_server->state.dft_state.dft_hue, p_server->state.dft_state.dft_hue, p_server->state.target_state.target_hue);
    store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_HSL_Saturation_State, p_server->state.dft_state.dft_stt, p_server->state.dft_state.dft_stt, p_server->state.target_state.target_stt);
}

static void HSL_state_timer_cb(void * p_context)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    app_light_HSL_server_t * p_server = (app_light_HSL_server_t *) p_context;

    /* Requirement: Process timing. Process the delay first (Non-zero delay will delay the required
     * state transition by the specified amount) and then the transition time.
     */
    if (p_server->state.HSL_time.delay_ms != 0)
    {
        p_server->state.HSL_time.delay_ms = 0;
        HSL_state_value_update(p_server, false);
    }
    else if (p_server->state.HSL_time.remaining_time_ms != 0)
    {
        p_server->state.HSL_time.remaining_time_ms = 0;
        HSL_state_value_update(p_server, false);
    }
    HSL_state_process_timing(p_server, false);
}



static uint32_t get_remaining_time(app_light_HSL_server_t* p_server)
{
    if (p_server->state.HSL_time.remaining_time_ms > 0 && p_server->state.HSL_time.delay_ms == 0)
    {
        uint32_t current_time_clock_ms;
        uint16_t current_time_nb_wrap;
        uint32_t delta;

        mesh_run_time_get(&current_time_clock_ms, &current_time_nb_wrap);

        // only two conditions:
        // current_time_nb_wrap == last_time_nb_wrap
        if (current_time_nb_wrap == p_server->HSL_last_time_nb_wrap)
        {
            delta = current_time_clock_ms - p_server->HSL_last_time_clock_ms;
        }
        // current_time_nb_wrap == last_time_nb_wrap + 1
        else
        {
            delta = current_time_clock_ms + (0xFFFFFFFF - p_server->HSL_last_time_clock_ms) + 1;
        }
        
        if (p_server->state.HSL_time.remaining_time_ms >= delta && delta > 0)
        {
            return (p_server->state.HSL_time.remaining_time_ms - delta);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return p_server->state.HSL_time.remaining_time_ms;
    }
}

static void light_HSL_state_get_cb(light_HSL_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_HSL_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_light_HSL_server_t *p_server = PARENT_BY_FIELD_GET(app_light_HSL_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the HSL state */
    p_server->light_HSL_get_cb(p_server->server.model_instance_index, &p_server->state.present_state, NULL, NULL);
    
    p_out->HSL.HSL_hue = p_server->state.present_state.present_hue;
    p_out->HSL.HSL_stt = p_server->state.present_state.present_stt;
    p_out->HSL.HSL_ln = p_server->state.present_state.present_ln;
    p_out->HSL.remaining_time_ms = get_remaining_time(p_server);
    
}

static void light_HSL_state_set_cb(light_HSL_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_HSL_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               light_HSL_status_params_u * p_out)
{
    app_light_HSL_server_t *p_server = PARENT_BY_FIELD_GET(app_light_HSL_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET HSL Hue Saturation HSL TO %d, %d, %d", 
                  __func__, p_self->model_instance_index, p_in->HSL_hue, p_in->HSL_stt, p_in->HSL_ln);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of HSL value, process timing */
    p_server->value_updated = false;
    p_server->state.target_state.target_hue = p_in->HSL_hue;
    p_server->state.target_state.target_stt = p_in->HSL_stt;
    p_server->state.target_state.target_ln = p_in->HSL_ln;

    /* Ensure that Light HSL state value is between Light HSL Range Min and Max values */
    if (p_server->state.target_state.target_hue != 0)
    {
        FORMAT_VALUE_RANGE(p_server->state.target_state.target_hue,
                       p_server->state.range_state.max_hue,
                       p_server->state.range_state.min_hue);
    }
    
    if (p_server->state.target_state.target_stt != 0)
    {
        FORMAT_VALUE_RANGE(p_server->state.target_state.target_stt,
                       p_server->state.range_state.max_stt,
                       p_server->state.range_state.min_stt);
    }
    
    if (p_in_transition == NULL)
    {
        p_server->state.HSL_time.delay_ms = 0;
        p_server->state.HSL_time.remaining_time_ms = 0;
    }
    else
    {
        p_server->state.HSL_time.delay_ms = p_in_transition->delay_ms;
        p_server->state.HSL_time.remaining_time_ms = p_in_transition->transition_time_ms;
    }

    HSL_state_value_update(p_server, false);
    HSL_state_process_timing(p_server, false);

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->HSL.HSL_hue = p_server->state.present_state.present_hue;
        p_out->HSL.HSL_stt = p_server->state.present_state.present_stt;
        p_out->HSL.HSL_ln = p_server->state.present_state.present_ln;
        p_out->HSL.remaining_time_ms= p_server->state.HSL_time.remaining_time_ms;
    }

}



static void light_HSL_target_state_get_cb(light_HSL_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_HSL_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_light_HSL_server_t *p_server = PARENT_BY_FIELD_GET(app_light_HSL_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    p_out->HSL.HSL_hue = p_server->state.target_state.target_hue;
    p_out->HSL.HSL_stt = p_server->state.target_state.target_stt;
    p_out->HSL.HSL_ln = p_server->state.target_state.target_ln;
    p_out->HSL.remaining_time_ms = get_remaining_time(p_server);
}

static void light_HSL_default_state_get_cb(light_HSL_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_HSL_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_light_HSL_server_t *p_server = PARENT_BY_FIELD_GET(app_light_HSL_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;
    
    /* Requirement: Provide the current value of the HSL Default state */
    p_server->light_HSL_get_cb(p_server->server.model_instance_index, NULL, &p_server->state.dft_state, NULL);
    p_out->HSL_dft.hue = p_server->state.dft_state.dft_hue;
    p_out->HSL_dft.stt = p_server->state.dft_state.dft_stt;
    p_out->HSL_dft.ln = p_server->state.dft_state.dft_ln;
}

static void light_HSL_range_state_get_cb(light_HSL_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_HSL_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_light_HSL_server_t *p_server = PARENT_BY_FIELD_GET(app_light_HSL_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the HSL Range state */
    p_server->light_HSL_get_cb(p_server->server.model_instance_index, NULL, NULL, &p_server->state.range_state);
    p_out->HSL_range.status_code = STATUS_CODES_SUCCESS;
    p_out->HSL_range.min_hue= p_server->state.range_state.min_hue;
    p_out->HSL_range.max_hue= p_server->state.range_state.max_hue;
    p_out->HSL_range.min_stt= p_server->state.range_state.min_stt;
    p_out->HSL_range.max_stt= p_server->state.range_state.max_stt;
}

static void app_light_HSL_scene_recall_cb(void *p_server, uint8_t *stored_state, uint16_t state_length)
{
    app_light_HSL_server_t *recal_server = (app_light_HSL_server_t *)p_server;
    light_HSL_present_state_t * recall_state_ptr = (light_HSL_present_state_t *)stored_state;

    APP_LOG_INFO(" [%s] enter ", __func__);
    APP_LOG_INFO("server hsl recall state: value %d, length %d", *stored_state, state_length);

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

    APP_LOG_INFO(" 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x, 0x%04x!!!", recall_state_ptr->present_hue, recall_state_ptr->present_stt, recall_state_ptr->present_ln,
                                                                                                                    recal_server->state.present_state.present_hue, recal_server->state.present_state.present_stt, recal_server->state.present_state.present_ln);
    //value has been recalled in scenes model

    light_HSL_status_params_t status =
    {
        .HSL_hue = recal_server->state.present_state.present_hue,
        .HSL_stt = recal_server->state.present_state.present_stt,
        .HSL_ln = recal_server->state.present_state.present_ln,
        .remaining_time_ms = recal_server->state.HSL_time.remaining_time_ms,
    };
    light_HSL_server_status_publish(&recal_server->server, &status);

    recal_server->light_HSL_set_cb(recal_server->server.model_instance_index, &(recal_server->state.present_state), NULL, NULL);
}

static void app_light_HSL_bind_check(app_light_HSL_server_t *p_server, uint32_t trigger_model)
{
    static uint16_t repeat_bind_HSL_ln_st[LIGHT_HSL_INSTANCE_COUNT] = {0,};
    static uint16_t repeat_bind_HSL_stt_st[LIGHT_HSL_INSTANCE_COUNT] = {0,};
    static uint16_t repeat_bind_HSL_hue_st[LIGHT_HSL_INSTANCE_COUNT] = {0,};
    
    uint16_t *repeat_bind_HSL_ln = &repeat_bind_HSL_ln_st[p_server->server.model_instance_index];
    uint16_t *repeat_bind_HSL_stt = &repeat_bind_HSL_stt_st[p_server->server.model_instance_index];
    uint16_t *repeat_bind_HSL_hue = &repeat_bind_HSL_hue_st[p_server->server.model_instance_index];

    APP_LOG_INFO(" %s enter, repeat value ln: %d, stt: %d, hue: %d, bind value ln: %d, stt: %d, hue: %d", __func__, 
                    *repeat_bind_HSL_ln, *repeat_bind_HSL_stt, *repeat_bind_HSL_hue,
                    p_server->state.present_state.present_ln, p_server->state.present_state.present_stt, p_server->state.present_state.present_hue);

    if (*repeat_bind_HSL_ln != p_server->state.present_state.present_ln)
    {
    /* check bind light lightness state */
        if (trigger_model != MODEL_ID_LIGHTS_LN)
        {
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_LN, MODEL_ID_LIGHTS_HSL,
                                &p_server->state.present_state.present_ln, sizeof(p_server->state.present_state.present_ln));
        }
        *repeat_bind_HSL_ln = p_server->state.present_state.present_ln;
    }
    if (*repeat_bind_HSL_stt != p_server->state.present_state.present_stt)
    {
    /* HSL server notice HSL Saturation server Saturation status has been changed */
        if (trigger_model != MODEL_ID_LIGHTS_HSLSAT)
        {
            /* hsl state binding to hsl saturation state in saturation element*/
            mesh_model_bind_check(p_server->server.model_instance_index + 2, MODEL_ID_LIGHTS_HSLSAT, MODEL_ID_LIGHTS_HSL,
                                &p_server->state.present_state.present_stt, sizeof(p_server->state.present_state.present_stt));
        }
        *repeat_bind_HSL_stt = p_server->state.present_state.present_stt;
    }
    if (*repeat_bind_HSL_hue != p_server->state.present_state.present_hue)
    {
    /* HSL server notice HSL Hue server Hue status has been changed */
        if (trigger_model != MODEL_ID_LIGHTS_HSLH)
        {
            /* hsl state binding to hsl hue state in hue element*/
            mesh_model_bind_check(p_server->server.model_instance_index + 1, MODEL_ID_LIGHTS_HSLH, MODEL_ID_LIGHTS_HSL,
                                &p_server->state.present_state.present_hue, sizeof(p_server->state.present_state.present_hue));
        }
        *repeat_bind_HSL_hue = p_server->state.present_state.present_hue;
    }
    return;
}


static bool app_light_HSL_ln_bind_cb(void *p_server, uint32_t src_model_id, void *p_data, uint16_t data_len)
{
    app_light_HSL_server_t * pl_server = (app_light_HSL_server_t *)p_server;
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
                    int16_t present_ln = *(int16_t *)p_data;

                    if( pl_server->state.present_state.present_ln != present_ln)
                    {
                        pl_server->state.present_state.present_ln = present_ln;

                        HSL_state_value_update(pl_server, true);

                        ret = true;
                    }
                    APP_LOG_INFO("model Light Lightness bind message length %d, value %d, HSL Lightness %d",
                                  data_len, present_ln, pl_server->state.present_state.present_ln);
                }
                break;
            }
            
            default:
                break;
        }

        if(ret)
        {
            app_light_HSL_status_publish(pl_server);
            app_light_HSL_bind_check(pl_server, src_model_id);
        }
    }

    return ret;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_light_HSL_status_publish(app_light_HSL_server_t * p_server)
{
    p_server->light_HSL_get_cb(p_server->server.model_instance_index, &p_server->state.present_state, NULL, NULL);

    // if the timer isn't in list, no error occurs.
    //mesh_timer_clear(&p_server->app_timer.timer_id);

    light_HSL_status_params_t status =
    {
        .HSL_hue = p_server->state.present_state.present_hue,
        .HSL_stt = p_server->state.present_state.present_stt,
        .HSL_ln = p_server->state.present_state.present_ln,
        .remaining_time_ms = get_remaining_time(p_server),
        //.remaining_time_ms = p_server->state.HSL_time.remaining_time_ms,
    };
    return light_HSL_server_status_publish(&p_server->server, &status);
}

uint16_t app_light_HSL_server_init(app_light_HSL_server_t *p_server, uint8_t element_offset, app_light_HSL_set_cb_t set_cb, app_light_HSL_get_cb_t get_cb)
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

    p_server->light_HSL_set_cb = set_cb;
    p_server->light_HSL_get_cb = get_cb;

    p_server->state.present_state.present_hue = 0;
    p_server->state.present_state.present_stt = 0;
    p_server->state.present_state.present_ln = 0;
    power_up_sequence_behavior(element_offset, element_offset, OnPowerUp_Bind_Lightness_State, (uint16_t *)&p_server->state.present_state.present_ln);
    power_up_sequence_behavior(element_offset, element_offset, OnPowerUp_Bind_HSL_Hue_State, (uint16_t *)&p_server->state.present_state.present_hue);
    power_up_sequence_behavior(element_offset, element_offset, OnPowerUp_Bind_HSL_Saturation_State, (uint16_t *)&p_server->state.present_state.present_stt);

    APP_LOG_INFO("present hue 0x%x, saturation 0x%x", p_server->state.present_state.present_hue, p_server->state.present_state.present_stt);
    p_server->state.target_state.target_hue = 0;
    p_server->state.target_state.target_stt = 0;
    p_server->state.target_state.target_ln = 0;
    
    p_server->state.dft_state.dft_hue = 0;
    p_server->state.dft_state.dft_stt = 0;
    p_server->state.dft_state.dft_ln = 0;
    
    p_server->state.range_state.max_hue = UINT16_MAX;
    p_server->state.range_state.min_hue = 0;
    
    p_server->state.range_state.max_stt = UINT16_MAX;
    p_server->state.range_state.min_stt = 0;

    p_server->state.HSL_time.delay_ms = 0;
    p_server->state.HSL_time.remaining_time_ms = 0;

    
    p_server->HSL_last_time_clock_ms = 0;
    p_server->HSL_last_time_nb_wrap = 0;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->value_updated = false;

    p_server->server.settings.p_callbacks = &light_HSL_srv_cbs,
        
    p_server->HSL_state_timer.callback = HSL_state_timer_cb;
    p_server->HSL_state_timer.p_args = p_server;
    p_server->HSL_state_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->HSL_state_timer.reload = false;

    mesh_model_bind_list_add(MODEL_ID_LIGHTS_HSL, element_offset, (void *)p_server, app_light_HSL_ln_bind_cb);
    mesh_scenes_state_store_with_scene(element_offset, app_light_HSL_scene_recall_cb, (void *)p_server, (uint8_t *)&p_server->state.present_state, sizeof(p_server->state.present_state));

    return light_HSL_server_init(&p_server->server, element_offset);
}



