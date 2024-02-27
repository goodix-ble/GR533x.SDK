/**
 *****************************************************************************************
 *
 * @file app_light_lightness_server.c
 *
 * @brief APP LIGHT LIGHTNESS API Implementation.
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
#include "app_light_lightness_server.h"
#include "light_lightness_server.h"
#include "app_log.h"
#include "user_app.h"
#include "mesh_bind.h"
#include "mesh_scenes_common.h"
#include "generic_power_onoff_behavior.h"

/*
 * DEFINES
 ****************************************************************************************
 */
/// Convert Light Lightness Linear value into Light Lightness Actual value
/// LA = 65535 * sqrt(LL / 65535)
///    = sqrt(65535 * 65535) * sqrt(LL / 65535)
///    = sqrt(65535 * LL)
///    = sqrt(65536 * LL - LL)
///    = sqrt(2^16 * LL - LL)
#define CV_LIGHTS_LN_ACTUAL(linear)                     \
        (gx_lights_isqrt(((uint32_t)linear << 16) - linear))

/// Convert Light Lightness Actual value into Light Lightness Linear value
/// LL = Ceil(65535 * (LA / 65535)^2)
///    = Ceil(LA^2 / 65535)
///    = Floor((LA^2 + 65534) + 65535)
#define CV_LIGHTS_LN_LINEAR(actual)                     \
        ((((uint32_t)actual * actual) + 65534) / 65535)

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void light_ln_state_set_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_ln_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               light_ln_status_params_u * p_out);

static void light_ln_state_get_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_status_params_u * p_out);

static void light_ln_linear_state_set_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_ln_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               light_ln_status_params_u * p_out);

static void light_ln_linear_state_get_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_status_params_u * p_out);

static void light_ln_last_state_get_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_status_params_u * p_out);

static void light_ln_default_state_get_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_status_params_u * p_out);

static void light_ln_range_state_get_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_status_params_u * p_out);

static void app_light_ln_bind_check(app_light_lightness_server_t *p_server, uint32_t trigger_model, bool is_boot);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

typedef struct
{
    app_light_lightness_server_t *p_server;
    uint8_t model_instance_index;
}ln_server_t;


const light_ln_server_callbacks_t light_ln_srv_cbs =
{
    .light_ln_cbs.set_cb = light_ln_state_set_cb,
    .light_ln_cbs.get_cb = light_ln_state_get_cb,

    .light_ln_linear_cbs.set_cb = light_ln_linear_state_set_cb,
    .light_ln_linear_cbs.get_cb = light_ln_linear_state_get_cb,

    .light_ln_last_cbs.get_cb = light_ln_last_state_get_cb,

    .light_ln_dft_cbs.get_cb = light_ln_default_state_get_cb,

    .light_ln_range_cbs.get_cb = light_ln_range_state_get_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static inline void lightness_state_range_format(light_ln_state_t *p_state)
{
    if (p_state->target_ln != 0)
    {
        if (p_state->target_ln > p_state->max_ln)
        {
            p_state->target_ln = p_state->max_ln;
        }
        else if (p_state->target_ln < p_state->min_ln)
        {
            p_state->target_ln = p_state->min_ln;
        }
    }

    if (p_state->present_ln != 0)
    {
        if (p_state->present_ln > p_state->max_ln)
        {
            p_state->present_ln = p_state->max_ln;
        }
        else if (p_state->present_ln < p_state->min_ln)
        {
            p_state->present_ln = p_state->min_ln;
        }
    }
}

static void lightness_state_process_timing(app_light_lightness_server_t * p_server, bool linear)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    uint16_t status = MESH_ERROR_NO_ERROR;
    if (linear)
    {
        mesh_timer_t *p_timer = &(p_server->linear_state_timer);
        mesh_timer_clear(&p_timer->timer_id);
        if (p_server->state.linear_delay_ms != 0)
        {
            p_timer->delay_ms = p_server->state.linear_delay_ms;
            status = mesh_timer_set(p_timer);
        }
        else if (p_server->state.linear_remaining_time_ms != 0)
        {
            p_timer->delay_ms = p_server->state.linear_remaining_time_ms;
            status = mesh_timer_set(p_timer);
            mesh_run_time_get(&p_server->linear_last_time_clock_ms, &p_server->linear_last_time_nb_wrap);
        }
        
    }
    else
    {
        mesh_timer_t *p_timer = &(p_server->actual_state_timer);
        mesh_timer_clear(&p_timer->timer_id);
        if (p_server->state.actual_delay_ms != 0)
        {
            p_timer->delay_ms = p_server->state.actual_delay_ms;
            status = mesh_timer_set(p_timer);
        }
        else if (p_server->state.actual_remaining_time_ms != 0)
        {
            p_timer->delay_ms = p_server->state.actual_remaining_time_ms;
            status = mesh_timer_set(p_timer);
            mesh_run_time_get(&p_server->actual_last_time_clock_ms, &p_server->actual_last_time_nb_wrap);
        }
    }

    if (status != MESH_ERROR_NO_ERROR)
    {
       APP_LOG_ERROR("State transition timer error");
    }
}



static void lightness_state_value_update(app_light_lightness_server_t * p_server, bool immed, bool linear)
{
    APP_LOG_INFO("[%s] enter.", __func__);
   
    if (!immed)
    {
        uint32_t remainint_time_ms = 0;
        uint32_t delay_time_ms = 0;
        if (linear)
        {
            remainint_time_ms = p_server->state.linear_remaining_time_ms;
            delay_time_ms = p_server->state.linear_delay_ms;
        }
        else
        {
            remainint_time_ms = p_server->state.actual_remaining_time_ms;
            delay_time_ms = p_server->state.actual_delay_ms;
        }
        /* Requirement: If delay and transition time is zero, current state changes to the target state. */
        if (delay_time_ms == 0 && remainint_time_ms == 0)
        {
            p_server->state.state.present_ln = p_server->state.state.target_ln;
            p_server->state.state.present_ln_linear = p_server->state.state.target_ln_linear;
            p_server->state.state.last_ln = (p_server->state.state.present_ln == 0) ? p_server->state.state.last_ln:p_server->state.state.present_ln;

            light_ln_status_params_t status_params;
            status_params.present_ln = p_server->state.state.present_ln;
            status_params.remaining_time_ms = p_server->state.actual_remaining_time_ms;
            light_ln_server_status_publish(&p_server->server, &status_params);

            if (!p_server->value_updated)
            {
                app_light_ln_bind_check(p_server,MODEL_ID_LIGHTS_LN, false);
                p_server->light_ln_set_cb(p_server->server.model_instance_index, &(p_server->state.state));
                p_server->value_updated = true;
            }
        }
        
        store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_Lightness_State, 0, 
                                p_server->state.state.default_ln == 0 ? p_server->state.state.last_ln : p_server->state.state.default_ln,
                                p_server->state.state.target_ln);
    }
    else
    {
        p_server->state.state.last_ln = (p_server->state.state.present_ln == 0) ? p_server->state.state.last_ln:p_server->state.state.present_ln;
        p_server->light_ln_set_cb(p_server->server.model_instance_index, &(p_server->state.state));
    

        store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_Lightness_State, 0, 
                                    p_server->state.state.default_ln == 0 ? p_server->state.state.last_ln : p_server->state.state.default_ln,
                                    p_server->state.state.last_ln);
    }
}

static void light_actual_state_timer_cb(void * p_context)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    app_light_lightness_server_t * p_server = (app_light_lightness_server_t *) p_context;

    /* Requirement: Process timing. Process the delay first (Non-zero delay will delay the required
     * state transition by the specified amount) and then the transition time.
     */
    if (p_server->state.actual_delay_ms != 0)
    {
        p_server->state.actual_delay_ms = 0;
        lightness_state_value_update(p_server, false, false);
    }
    else if (p_server->state.actual_remaining_time_ms != 0)
    {
        p_server->state.actual_remaining_time_ms = 0;
        lightness_state_value_update(p_server, false, false);
    }
    lightness_state_process_timing(p_server, false);
}

static void light_linear_state_timer_cb(void * p_context)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    app_light_lightness_server_t * p_server = (app_light_lightness_server_t *) p_context;

    /* Requirement: Process timing. Process the delay first (Non-zero delay will delay the required
     * state transition by the specified amount) and then the transition time.
     */
    if (p_server->state.linear_delay_ms != 0)
    {
        p_server->state.linear_delay_ms = 0;
        lightness_state_value_update(p_server, false, true);
    }
    else if (p_server->state.linear_remaining_time_ms != 0)
    {
        p_server->state.linear_remaining_time_ms = 0;
        lightness_state_value_update(p_server, false, true);
    }
    lightness_state_process_timing(p_server, true);
}

static uint32_t get_actual_remaining_time_ms(app_light_lightness_server_t *p_server)
{
    /* Requirement: Always report remaining time */
    if (p_server->state.actual_remaining_time_ms > 0 && p_server->state.actual_delay_ms == 0)
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
        
        if (p_server->state.actual_remaining_time_ms >= delta && delta > 0)
        {
            return (p_server->state.actual_remaining_time_ms - delta);
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return p_server->state.actual_remaining_time_ms;
    }
}

static void light_ln_state_get_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_light_lightness_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lightness_server_t, server, p_self);
    light_ln_state_t usr_state;

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the lightness state */
    p_server->light_ln_get_cb(p_server->server.model_instance_index, &usr_state);
    p_out->ln.present_ln = usr_state.present_ln;
    p_out->ln.target_ln = p_server->state.state.target_ln;
    p_out->ln.remaining_time_ms = get_actual_remaining_time_ms(p_server);
}

static void light_ln_state_set_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_ln_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               light_ln_status_params_u * p_out)
{
    app_light_lightness_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lightness_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: 0x%04X", __func__, p_self->model_instance_index, p_in->ln);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of lightness value, process timing */
    p_server->value_updated = false;
    p_server->state.state.target_ln = p_in->ln;

    /* Ensure that Light Lightness Actual state value is between Light Lightness Range Min and Max values */
    if (p_server->state.state.target_ln != 0)
    {
        lightness_state_range_format(&p_server->state.state);
    }
    p_server->state.state.target_ln_linear = CV_LIGHTS_LN_LINEAR(p_server->state.state.target_ln);

    if (p_in_transition == NULL)
    {
        p_server->state.actual_delay_ms = 0;
        p_server->state.actual_remaining_time_ms = 0;
    }
    else
    {
        p_server->state.actual_delay_ms = p_in_transition->delay_ms;
        p_server->state.actual_remaining_time_ms = p_in_transition->transition_time_ms;
    }

    lightness_state_value_update(p_server, false, false);
    lightness_state_process_timing(p_server, false);

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->ln.present_ln = p_server->state.state.present_ln;
        p_out->ln.target_ln= p_server->state.state.target_ln;
        p_out->ln.remaining_time_ms= p_server->state.actual_remaining_time_ms;
    }

}

static void light_ln_linear_state_get_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_light_lightness_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lightness_server_t, server, p_self);
    light_ln_state_t usr_state;

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the lightness linear state */
    p_server->light_ln_get_cb(p_server->server.model_instance_index, &usr_state);
    p_out->ln.present_ln = usr_state.present_ln_linear;
    p_out->ln.target_ln = p_server->state.state.target_ln_linear;

    /* Requirement: Always report remaining time */
    if (p_server->state.linear_remaining_time_ms > 0 && p_server->state.linear_delay_ms == 0)
    {
        uint32_t current_time_clock_ms;
        uint16_t current_time_nb_wrap;
        uint32_t delta;

        mesh_run_time_get(&current_time_clock_ms, &current_time_nb_wrap);

        // only two conditions:
        // current_time_nb_wrap == last_time_nb_wrap
        if (current_time_nb_wrap == p_server->linear_last_time_nb_wrap)
        {
            delta = current_time_clock_ms - p_server->linear_last_time_clock_ms;
        }
        // current_time_nb_wrap == last_time_nb_wrap + 1
        else
        {
            delta = current_time_clock_ms + (0xFFFFFFFF - p_server->linear_last_time_clock_ms) + 1;
        }
        
        if (p_server->state.linear_remaining_time_ms >= delta && delta > 0)
        {
            p_out->ln.remaining_time_ms = p_server->state.linear_remaining_time_ms - delta;
        }
        else
        {
            p_out->ln.remaining_time_ms = 0;
        }
    }
    else
    {
        p_out->ln.remaining_time_ms = p_server->state.linear_remaining_time_ms;
    }
}

static void light_ln_linear_state_set_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_ln_set_params_t * p_in, const model_transition_t * p_in_transition,
                                               light_ln_status_params_u * p_out)
{
    app_light_lightness_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lightness_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: %04X", __func__, p_self->model_instance_index, p_in->ln);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of lightness value, process timing */
    p_server->value_updated = false;
    p_server->state.state.target_ln_linear= p_in->ln;
    p_server->state.state.target_ln = CV_LIGHTS_LN_ACTUAL(p_server->state.state.target_ln_linear);

    /* Ensure that Light Lightness Actual state value is between Light Lightness Range Min and Max values */
    if (p_server->state.state.target_ln_linear!= 0)
    {
        lightness_state_range_format(&p_server->state.state);
    }
    p_server->state.state.target_ln_linear = CV_LIGHTS_LN_LINEAR(p_server->state.state.target_ln);

    if (p_in_transition == NULL)
    {
        p_server->state.linear_delay_ms = 0;
        p_server->state.linear_remaining_time_ms = 0;
    }
    else
    {
        p_server->state.linear_delay_ms = p_in_transition->delay_ms;
        p_server->state.linear_remaining_time_ms = p_in_transition->transition_time_ms;
    }

    lightness_state_value_update(p_server, false, true);
    lightness_state_process_timing(p_server, true);

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->ln.present_ln = p_server->state.state.present_ln_linear;
        p_out->ln.target_ln= p_server->state.state.target_ln_linear;
        p_out->ln.remaining_time_ms= p_server->state.linear_remaining_time_ms;
    }

}

static void light_ln_last_state_get_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_light_lightness_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lightness_server_t, server, p_self);
    
    light_ln_state_t usr_state;
    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the lightness last state */
    p_server->light_ln_get_cb(p_server->server.model_instance_index, &usr_state);
    p_out->ln_last.ln= usr_state.last_ln;
}

static void light_ln_default_state_get_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_light_lightness_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lightness_server_t, server, p_self);
    light_ln_state_t usr_state;

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the lightness default state */
    p_server->light_ln_get_cb(p_server->server.model_instance_index, &usr_state);
    p_out->ln_dft.ln= usr_state.default_ln;

}

static void light_ln_range_state_get_cb(light_ln_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_status_params_u * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_light_lightness_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lightness_server_t, server, p_self);
    
    light_ln_state_t usr_state;
    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the lightness range state */
    p_server->light_ln_get_cb(p_server->server.model_instance_index, &usr_state);
    p_out->ln_range.status_code= usr_state.status_code;
    p_out->ln_range.min_ln= usr_state.min_ln;
    p_out->ln_range.max_ln= usr_state.max_ln;
}

static void app_light_ln_scene_recall_cb(void *p_server, uint8_t *stored_state, uint16_t state_length)
{
    app_light_lightness_server_t *recal_server = (app_light_lightness_server_t *)p_server;

    APP_LOG_INFO("[%s] enter ", __func__);
    APP_LOG_INFO("server lightness recall state: value %d, length %d", *stored_state, state_length);

    if (NULL == p_server)
    {
        APP_LOG_INFO(" [%s] exit : Unknow server state to recall !!!", __func__);
        return ;
    }

    if (state_length != sizeof(recal_server->state.state.present_ln))
    {
        APP_LOG_INFO(" [%s] exit : invalid recall param!!!", __func__);
        return ;
    }

    APP_LOG_INFO(" 0x%04x, 0x%04x, 0x%04x!!!", *(uint16_t *)stored_state, recal_server->state.state.present_ln, recal_server->state.state.present_ln_linear);
    //value has been recalled in scenes model

    if (*(uint16_t *)stored_state == recal_server->state.state.present_ln)
    {
        light_ln_status_params_t status =
        {
            .present_ln = recal_server->state.state.present_ln,
            .target_ln = recal_server->state.state.target_ln,
            .remaining_time_ms = recal_server->state.actual_remaining_time_ms
        };
        (void )light_ln_server_status_publish(&recal_server->server, &status);
    }

    recal_server->light_ln_set_cb(recal_server->server.model_instance_index, &(recal_server->state.state));
}

static void app_light_ln_bind_check(app_light_lightness_server_t *p_server, uint32_t trigger_model, bool is_boot)
{
    static uint16_t repeat_bind_ln_st[LIGHT_LIGHTNESS_INSTANCE_COUNT] = {0,};
    uint16_t *repeat_bind_ln = &repeat_bind_ln_st[p_server->server.model_instance_index];

    APP_LOG_INFO(" [%s] enter, model_instance_index %d, repeat value %d, bind value %d", __func__, p_server->server.model_instance_index, *repeat_bind_ln, p_server->state.state.present_ln);

    if (*repeat_bind_ln != p_server->state.state.present_ln|| is_boot)
    {
        if (trigger_model != MODEL_ID_GENS_LVL)
        {
            /* check bind generic level state */
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_GENS_LVL, MODEL_ID_LIGHTS_LN, &p_server->state.state.present_ln, sizeof(p_server->state.state.present_ln));
        }

        if (trigger_model != MODEL_ID_GENS_OO)
        {
            /* check bind generic onoff state */
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_GENS_OO, MODEL_ID_LIGHTS_LN, &p_server->state.state.present_ln, sizeof(p_server->state.state.present_ln));
        }

        if (trigger_model != MODEL_ID_LIGHTS_CTL)
        {
            /* check bind light ctl state */
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_CTL, MODEL_ID_LIGHTS_LN, &p_server->state.state.present_ln, sizeof(p_server->state.state.present_ln));
        }
        
        if (trigger_model != MODEL_ID_LIGHTS_HSL)
        {
            /* check bind light HSL state */
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_HSL, MODEL_ID_LIGHTS_LN, &p_server->state.state.present_ln, sizeof(p_server->state.state.present_ln));
        }

        if (trigger_model != MODEL_ID_LIGHTS_XYL)
        {
            /* check bind light xyl state */
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_XYL, MODEL_ID_LIGHTS_LN, &p_server->state.state.present_ln, sizeof(p_server->state.state.present_ln));
        }
        /*
        if (trigger_model != MODEL_ID_LIGHTS_LC)
        {
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_LC, MODEL_ID_LIGHTS_LN, &p_server->state.state.present_ln, sizeof(p_server->state.state.present_ln));
        }*/

        *repeat_bind_ln = p_server->state.state.present_ln;
    }
    return ;
}

static bool app_light_ln_bind_cb(void *p_server, uint32_t src_model_id, void *p_data, uint16_t data_len)
{
    app_light_lightness_server_t * pl_server = (app_light_lightness_server_t *)p_server;
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

                    if(pl_server->state.state.present_ln != present_lvl + 32768)
                    {
                        pl_server->state.state.present_ln = present_lvl + 32768;
                        if (pl_server->state.state.present_ln != 0)
                        {
                            lightness_state_range_format(&pl_server->state.state);
                        }
                        pl_server->state.state.present_ln_linear = CV_LIGHTS_LN_LINEAR(pl_server->state.state.present_ln);
                        lightness_state_value_update(pl_server, true, false);
                        if (pl_server->state.state.present_ln != present_lvl + 32768 && p_data != NULL)
                        {
                            *(int16_t *)p_data = pl_server->state.state.present_ln -  32768;
                        }

                        ret = true;
                    }
                    APP_LOG_INFO("Model generic level bind message length %d, value %d, lightness actual %d", data_len, present_lvl, pl_server->state.state.present_ln);
                }
                break;
            }
            case MODEL_ID_GENS_OO:
            {
                if (data_len == 1)
                {
                    uint8_t onoff = *(uint8_t *)p_data;

                    if ((onoff == 0x00) && (pl_server->state.state.present_ln != 0))//onoff :off
                    {
                        pl_server->state.state.present_ln = 0x00;
                        pl_server->state.state.present_ln_linear = 0x00;
                        lightness_state_value_update(pl_server, true, false);

                        ret = true;
                    }
                    else if ((onoff == 0x01) && (pl_server->state.state.present_ln == 0))//onoff :on
                    {
                        // Update default lightness, CTL HSL XYL may modify it. 
                        pl_server->light_ln_get_cb(pl_server->server.model_instance_index, &pl_server->state.state);
                        if(pl_server->state.state.default_ln == 0x0000)
                        {
                            pl_server->state.state.present_ln = pl_server->state.state.last_ln;
                        }
                        else
                        {
                            pl_server->state.state.present_ln = pl_server->state.state.default_ln;
                        }
                        pl_server->state.state.present_ln_linear = CV_LIGHTS_LN_LINEAR(pl_server->state.state.present_ln);
                        lightness_state_value_update(pl_server, true, false);

                        ret = true;
                    }
                    APP_LOG_INFO("Model generic onoff bind message length %d, value %d, lightness actual %d", data_len, onoff, pl_server->state.state.present_ln);
                }
                break;
            }
            case MODEL_ID_LIGHTS_CTL:
            case MODEL_ID_LIGHTS_HSL:
            case MODEL_ID_LIGHTS_XYL:
            case MODEL_ID_LIGHTS_LC:
            {
                if (data_len == 2)
                {
                    uint16_t present_ln = *(uint16_t *)p_data;
                    /*if (MODEL_ID_LIGHTS_LC == src_model_id)
                    {
                        uint32_t present_ln_tmp = CV_LIGHTS_LN_ACTUAL(present_ln);
                        while(present_ln*65535 > present_ln_tmp * present_ln_tmp)//present_ln = present_ln_tmp * present_ln_tmp / 65535
                        {
                            present_ln_tmp++;
                            APP_LOG_INFO("Model light lightness adjust binding present lightness to %d", present_ln_tmp);
                        }
                        present_ln = present_ln_tmp;
                    }*/
                    if( pl_server->state.state.present_ln  != present_ln)
                    {
                        pl_server->state.state.present_ln = present_ln;
                        if (pl_server->state.state.present_ln != 0)
                        {
                            lightness_state_range_format(&pl_server->state.state);
                        }
                        pl_server->state.state.present_ln_linear = CV_LIGHTS_LN_LINEAR(pl_server->state.state.present_ln);

                        if (pl_server->state.state.present_ln != present_ln && p_data != NULL)
                        {
                            *(uint16_t *)p_data = pl_server->state.state.present_ln;
                        }
                        lightness_state_value_update(pl_server, true, false);
                        ret = true;
                    }
                }
                break;
            }
            default:
                break;
        }

        if(ret)
        {
            app_light_ln_status_publish(pl_server);
            app_light_ln_bind_check(pl_server, src_model_id, false);
        }
    }

    return ret;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_light_ln_status_publish(app_light_lightness_server_t * p_server)
{
    light_ln_state_t usr_state;

    p_server->light_ln_get_cb(p_server->server.model_instance_index, &usr_state);

    // if the timer isn't in list, no error occurs.
    //mesh_timer_clear(&p_server->app_timer.timer_id);

    light_ln_status_params_t status =
    {
        .present_ln = usr_state.present_ln,
        .target_ln = p_server->state.state.target_ln,
        .remaining_time_ms = get_actual_remaining_time_ms(p_server)
    };
    return light_ln_server_status_publish(&p_server->server, &status);
}

uint16_t app_light_ln_server_init(app_light_lightness_server_t *p_server, uint8_t element_offset, app_light_ln_set_cb_t set_cb, app_light_ln_get_cb_t get_cb)
{
    if(( p_server == NULL) || (LIGHT_LIGHTNESS_INSTANCE_COUNT <= element_offset))
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

    p_server->light_ln_set_cb = set_cb;
    p_server->light_ln_get_cb = get_cb;

    //p_server->state.state.present_ln = 0;
    power_up_sequence_behavior(element_offset, element_offset, OnPowerUp_Bind_Lightness_State, &p_server->state.state.present_ln);
    p_server->state.state.target_ln = 0;
    p_server->state.state.present_ln_linear= 0;
    p_server->state.state.target_ln_linear= 0;
    p_server->state.state.last_ln = 0xFFFF;
    p_server->state.actual_remaining_time_ms = 0;
    p_server->state.actual_delay_ms = 0;
    p_server->state.linear_remaining_time_ms = 0;
    p_server->state.linear_delay_ms = 0;
    p_server->state.state.default_ln= 0;
    p_server->state.state.status_code = STATUS_CODES_SUCCESS;
    p_server->state.state.min_ln= 0x0001;
    p_server->state.state.max_ln= 0xFFFF;

    p_server->actual_last_time_clock_ms = 0;
    p_server->actual_last_time_nb_wrap = 0;
    p_server->linear_last_time_clock_ms = 0;
    p_server->linear_last_time_nb_wrap = 0;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->value_updated = false;

    p_server->server.settings.p_callbacks = &light_ln_srv_cbs,
        
    p_server->actual_state_timer.callback = light_actual_state_timer_cb;
    p_server->actual_state_timer.p_args = p_server;
    p_server->actual_state_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->actual_state_timer.reload = false;

    p_server->linear_state_timer.callback = light_linear_state_timer_cb;
    p_server->linear_state_timer.p_args = p_server;
    p_server->linear_state_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->linear_state_timer.reload = false;

    mesh_model_bind_list_add(MODEL_ID_LIGHTS_LN, element_offset, (void *)p_server, app_light_ln_bind_cb);
    mesh_scenes_state_store_with_scene(element_offset, app_light_ln_scene_recall_cb, (void *)p_server, (uint8_t *)&p_server->state.state.present_ln, sizeof(p_server->state.state.present_ln));
    mesh_scenes_state_store_with_scene(element_offset, app_light_ln_scene_recall_cb, (void *)p_server, (uint8_t *)&p_server->state.state.present_ln_linear, sizeof(p_server->state.state.present_ln_linear));

    //check hue element binding level
    app_light_ln_bind_check(p_server, element_offset, true);

    return light_ln_server_init(&p_server->server, element_offset);
}

uint32_t gx_lights_isqrt(uint32_t n)
{
    uint64_t isqrt;
    uint64_t min = 0;
    uint64_t max = ((uint64_t)1) << 32;

    while (1)
    {
        uint64_t sq;

        if (max <= (1 + min))
        {
            isqrt = min;
            break;
        }

        isqrt = min + ((max - min) >> 1);
        sq = isqrt * isqrt;

        if (sq == n)
        {
            break;
        }

        if (sq > n)
        {
            max = isqrt;
        }
        else
        {
            min = isqrt;
        }
    }

    return (isqrt);
}

