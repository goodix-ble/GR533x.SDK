/**
 *****************************************************************************************
 *
 * @file app_light_lc_server.c
 *
 * @brief APP LIGHT LC API Implementation.
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
#include "app_light_lc_server.h"
#include "light_lc_server.h"
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

extern uint8_t pin_on_power_up[];
uint8_t event_flag;
/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void light_lc_mode_state_set_cb(light_lc_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_mode_set_params_t * p_in,
                                                    light_lc_mode_status_params_t * p_out);

static void light_lc_mode_state_get_cb(light_lc_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    light_lc_mode_status_params_t * p_out);

static void light_lc_om_state_set_cb(light_lc_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_om_set_params_t * p_in,
                                                    light_lc_om_status_params_t * p_out);

static void light_lc_om_state_get_cb(light_lc_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    light_lc_om_status_params_t * p_out);

static void light_lc_loo_state_set_cb(light_lc_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_loo_set_params_t * p_in,
                                                    const model_transition_t * p_in_transition,
                                                    light_lc_loo_status_params_t * p_out);

static void light_lc_loo_state_get_cb(light_lc_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    light_lc_loo_status_params_t * p_out);

static void light_lc_sensor_status_cb(light_lc_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    uint8_t lc_senser_mask,
                                                    uint8_t lc_occupancy,
                                                    uint32_t lc_amb_luxlvl);

static void app_light_lc_bind_check(app_light_lc_server_t *p_server, uint32_t trigger_model);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const light_lc_server_callbacks_t light_lc_srv_cbs =
{
    .light_lc_mode_set_cbs = light_lc_mode_state_set_cb,
    .light_lc_mode_get_cbs = light_lc_mode_state_get_cb,
    .light_lc_om_set_cbs = light_lc_om_state_set_cb,
    .light_lc_om_get_cbs = light_lc_om_state_get_cb,
    .light_lc_loo_set_cbs = light_lc_loo_state_set_cb,
    .light_lc_loo_get_cbs = light_lc_loo_state_get_cb,
    .light_lc_sensor_state_cbs = light_lc_sensor_status_cb,
};

const char *app_light_machine_event_string[LIGHT_LC_STATE_MECHINE_EVENTS_MAX] = {"mode on", "mode off", "occupancy on", "light on", "light off", "timer off"};
const char *app_light_machine_state_string[LIGHT_LC_STATE_MECHINE_STATES_MAX] = {"off", "standby", "fade on", "run", "fade", "prolong", "fade standby auto", "fade standby manual"};
const char *app_light_machine_timer_string[LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_MAX] = {"abort timer", "T1", "T2", "T3", "T4", "T5", "T6", " Transition Time",};
const char *app_light_machine_action_string[6] = {"no action", "light on", "light off", "occpancy on", "occpancy off", "Timer to"};

const app_light_lc_machine_transtion_action_t machine_actions_task[] = 
{
    // light lc state machine off state
    {LIGHT_LC_STATE_MECHINE_STATES_OFF, LIGHT_LC_STATE_MECHINE_EVENTS_MODE_ON, 
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_NO_ACTION,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_ANY, LIGHT_LC_STATE_MECHINE_STATES_STANDBY},

    // light lc state machine standby state
    {LIGHT_LC_STATE_MECHINE_STATES_STANDBY, LIGHT_LC_STATE_MECHINE_EVENTS_MODE_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_ANY, LIGHT_LC_STATE_MECHINE_STATES_OFF},

    {LIGHT_LC_STATE_MECHINE_STATES_STANDBY, LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_ON,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_ON | LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_TRANSITION, LIGHT_LC_STATE_MECHINE_STATES_FADE_ON},

    {LIGHT_LC_STATE_MECHINE_STATES_STANDBY, LIGHT_LC_STATE_MECHINE_EVENTS_OCC_ON,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY/*LIGHT_LC_STATE_MECHINE_CONDITIONS_AUTO_OCC*/, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_ON | LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T1, LIGHT_LC_STATE_MECHINE_STATES_FADE_ON},

    // light lc state machine fade on state
    {LIGHT_LC_STATE_MECHINE_STATES_FADE_ON, LIGHT_LC_STATE_MECHINE_EVENTS_MODE_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_ANY, LIGHT_LC_STATE_MECHINE_STATES_OFF},

    {LIGHT_LC_STATE_MECHINE_STATES_FADE_ON, LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF | LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_TRANSITION, LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL},

    {LIGHT_LC_STATE_MECHINE_STATES_FADE_ON, LIGHT_LC_STATE_MECHINE_EVENTS_TIMER_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T2, LIGHT_LC_STATE_MECHINE_STATES_RUN},

    // light lc state machine run state
    {LIGHT_LC_STATE_MECHINE_STATES_RUN, LIGHT_LC_STATE_MECHINE_EVENTS_MODE_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_ANY, LIGHT_LC_STATE_MECHINE_STATES_OFF},

    {LIGHT_LC_STATE_MECHINE_STATES_RUN, LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF|LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_TRANSITION, LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL},

    {LIGHT_LC_STATE_MECHINE_STATES_RUN, LIGHT_LC_STATE_MECHINE_EVENTS_OCC_ON,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OCC_OFF | LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T2, LIGHT_LC_STATE_MECHINE_STATES_RUN},

    {LIGHT_LC_STATE_MECHINE_STATES_RUN, LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_ON,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T2, LIGHT_LC_STATE_MECHINE_STATES_RUN},

    {LIGHT_LC_STATE_MECHINE_STATES_RUN, LIGHT_LC_STATE_MECHINE_EVENTS_TIMER_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T3, LIGHT_LC_STATE_MECHINE_STATES_FADE},

    // light lc state machine fade state
    {LIGHT_LC_STATE_MECHINE_STATES_FADE, LIGHT_LC_STATE_MECHINE_EVENTS_MODE_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_ANY, LIGHT_LC_STATE_MECHINE_STATES_OFF},

    {LIGHT_LC_STATE_MECHINE_STATES_FADE, LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF|LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_TRANSITION, LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL},

    {LIGHT_LC_STATE_MECHINE_STATES_FADE, LIGHT_LC_STATE_MECHINE_EVENTS_OCC_ON,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OCC_OFF | LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_TRANSITION, LIGHT_LC_STATE_MECHINE_STATES_FADE_ON},

    {LIGHT_LC_STATE_MECHINE_STATES_FADE, LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_ON,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T1, LIGHT_LC_STATE_MECHINE_STATES_FADE_ON},

    {LIGHT_LC_STATE_MECHINE_STATES_FADE, LIGHT_LC_STATE_MECHINE_EVENTS_TIMER_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T4, LIGHT_LC_STATE_MECHINE_STATES_PROLONG},

    // light lc state machine prolong state
    {LIGHT_LC_STATE_MECHINE_STATES_PROLONG, LIGHT_LC_STATE_MECHINE_EVENTS_MODE_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_ANY, LIGHT_LC_STATE_MECHINE_STATES_OFF},

    {LIGHT_LC_STATE_MECHINE_STATES_PROLONG, LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF|LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_TRANSITION, LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL},

    {LIGHT_LC_STATE_MECHINE_STATES_PROLONG, LIGHT_LC_STATE_MECHINE_EVENTS_OCC_ON,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OCC_OFF | LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T1, LIGHT_LC_STATE_MECHINE_STATES_FADE_ON},

    {LIGHT_LC_STATE_MECHINE_STATES_PROLONG, LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_ON,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_TRANSITION, LIGHT_LC_STATE_MECHINE_STATES_FADE_ON},

    {LIGHT_LC_STATE_MECHINE_STATES_PROLONG, LIGHT_LC_STATE_MECHINE_EVENTS_TIMER_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF|LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T5, LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_AUTO},

    // light lc state machine fade standby auto state
    {LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_AUTO, LIGHT_LC_STATE_MECHINE_EVENTS_MODE_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_ANY, LIGHT_LC_STATE_MECHINE_STATES_OFF},

    {LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_AUTO, LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF|LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_TRANSITION, LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL},

    {LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_AUTO, LIGHT_LC_STATE_MECHINE_EVENTS_OCC_ON,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OCC_OFF | LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T1, LIGHT_LC_STATE_MECHINE_STATES_FADE_ON},

    {LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_AUTO, LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_ON,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_TRANSITION, LIGHT_LC_STATE_MECHINE_STATES_FADE_ON},

    {LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_AUTO, LIGHT_LC_STATE_MECHINE_EVENTS_TIMER_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_NO_ACTION,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T5, LIGHT_LC_STATE_MECHINE_STATES_STANDBY},

    // light lc state machine fade standby manual state
    {LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL, LIGHT_LC_STATE_MECHINE_EVENTS_MODE_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_ANY, LIGHT_LC_STATE_MECHINE_STATES_OFF},

    {LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL, LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_ON,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_TRANSITION, LIGHT_LC_STATE_MECHINE_STATES_FADE_ON},

    {LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL, LIGHT_LC_STATE_MECHINE_EVENTS_TIMER_OFF,
        LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY, LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF,
        LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_ANY, LIGHT_LC_STATE_MECHINE_STATES_STANDBY}
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static Light_lc_state_mechine_conditions_t light_lc_get_mechine_condition(app_light_lc_state_t *lc_mode)
{
    if ((lc_mode->lc_om.mode == LIGHT_LC_OCC_MODE_STATE_OCC)
        && (lc_mode->lc_LuxLVL.value < lc_mode->lc_property.LuxLvl_on))
    {
        return LIGHT_LC_STATE_MECHINE_CONDITIONS_AUTO_OCC;
    }
    else if ((lc_mode->lc_om.mode == LIGHT_LC_OCC_MODE_STATE_NO_OCC)
        && (lc_mode->lc_LuxLVL.value >= lc_mode->lc_property.LuxLvl_on))
    {
        return LIGHT_LC_STATE_MECHINE_CONDITIONS_NO_AUTO_OCC;
    }

    if (lc_mode->lc_occ_value.value == LIGHT_LC_OCC_REPORT_BEEN_OCC)
    {
        return LIGHT_LC_STATE_MECHINE_CONDITIONS_OCC_ON;
    }
    else
    {
        return LIGHT_LC_STATE_MECHINE_CONDITIONS_OCC_OFF;
    }
}

#if 0
static Light_lc_state_mechine_states_t light_lc_state_machine_states_get(app_light_lc_state_t *lc_mode)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    if (lc_mode == NULL)
    {
        return LIGHT_LC_STATE_MECHINE_STATES_MAX;
    }

    lc_mode->machine_state
}
#endif

static void lc_state_process_timing(app_light_lc_server_t * p_server)
{
    APP_LOG_INFO("[%s] enter delay_ms: %d, remaining_time_ms: %d.", __func__, p_server->state.lc_loo.delay_ms, p_server->state.lc_loo.remaining_time_ms);
    
    uint32_t status = MESH_ERROR_NO_ERROR;
    mesh_timer_t *p_timer = &(p_server->loo_state_timer);
    
    // if the timer isn't in list, no error occurs.
    mesh_timer_clear(&p_timer->timer_id);

    /* Process timing requirements */
    if (p_server->state.lc_loo.delay_ms != 0)
    {
        p_timer->delay_ms = p_server->state.lc_loo.delay_ms;
        status = mesh_timer_set(p_timer);
    }
    else
    {
        if (p_server->state.lc_loo.target_loo == LIGHT_LC_LOO_MODE_STATE_ON)
        {
            p_server->state.lc_loo.present_loo = p_server->state.lc_loo.target_loo;
            //upload to grmesh PC.
            //p_server->light_lc_set_cb(p_server->server.model_instance_index, &(p_server->state.lc_loo.present_loo), &(p_server->state.lc_linear.value));
            light_lc_state_machine(p_server, &p_server->state, LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_ON);
        }
        else if (p_server->state.lc_loo.target_loo == LIGHT_LC_LOO_MODE_STATE_OFF)
        {
            light_lc_state_machine(p_server, &p_server->state, LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_OFF);
        }
        mesh_run_time_get(&p_server->loo_last_time_clock_ms, &p_server->loo_last_time_nb_wrap);
    }

    if (status != MESH_ERROR_NO_ERROR)
    {
       APP_LOG_INFO("State transition timer error");
    }
}

static void lc_state_value_update(app_light_lc_server_t * p_server)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    /* Requirement: If delay and transition time is zero, current state changes to the target state. */
    if ((p_server->state.lc_loo.delay_ms == 0 && p_server->state.lc_loo.remaining_time_ms == 0)
        || (p_server->state.lc_loo.delay_ms == 0 && p_server->state.lc_loo.target_loo == 1))
    {
        p_server->state.lc_loo.present_loo = p_server->state.lc_loo.target_loo;

        light_lc_loo_status_params_t status_params;
        status_params.present_loo = p_server->state.lc_loo.present_loo;
        status_params.target_loo = p_server->state.lc_loo.target_loo;
        status_params.remaining_time_ms = p_server->state.lc_loo.remaining_time_ms;

        if((p_server->state.machine_state == LIGHT_LC_STATE_MECHINE_STATES_STANDBY) && (event_flag == LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_OFF))
        {
            status_params.remaining_time_ms = 200;
        }
        (void) light_lc_server_loo_status_publish(&p_server->server, &status_params);

        //if (!p_server->value_updated)
        {
            p_server->light_lc_set_cb(p_server->server.model_instance_index, &(p_server->state.lc_loo.present_loo), &(p_server->state.lc_linear.value));
            //p_server->value_updated = true;
            app_light_lc_bind_check(p_server,MODEL_ID_LIGHTS_LC);
        }
        store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_LC_loo_State, 0, 0, p_server->state.lc_loo.target_loo);
    }
}

static void light_lc_loo_state_timer_cb(void * p_context)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    app_light_lc_server_t * p_server = (app_light_lc_server_t *) p_context;

    /* Requirement: Process timing. Process the delay first (Non-zero delay will delay the required
     * state transition by the specified amount) and then the transition time.
     */
    if (p_server->state.lc_loo.delay_ms != 0)
    {
        p_server->state.lc_loo.delay_ms = 0;
        lc_state_process_timing(p_server);
        lc_state_value_update(p_server);
    }
}

static void light_lc_PI_feedback_regulator_calc(app_light_lc_state_t *lc_mode)
{
    int32_t PI_E = lc_mode->output_state.luxlvl_output - lc_mode->lc_LuxLVL.value;
    uint32_t PI_D = lc_mode->lc_property.Regulator_Accuracy * lc_mode->output_state.luxlvl_output / 2;
    int32_t PI_U = 0;
    // TODO: sunmation interval ???
    uint32_t PI_T = 100; //ms, modify after
    static uint32_t ln_n = 0;

    if (PI_E > PI_D)
    {
        PI_U = PI_E - PI_D;
    }
    else if (PI_E < -PI_D)//(PI_E + PI_D < 0) // PI_E < -PI_D
    {
        PI_U = PI_E + PI_D;
    }
    else
    {
        PI_U = 0;
    }

    if (PI_U >= 0)
    {
        ln_n = ln_n + PI_U * PI_T * lc_mode->lc_property.Regulator_kiu/1000;
        lc_mode->output_state.regulator_output = ln_n + PI_U * lc_mode->lc_property.Regulator_kpu;
    }
    else
    {
        ln_n = ln_n + PI_U * PI_T * lc_mode->lc_property.Regulator_kid/1000;
        lc_mode->output_state.regulator_output = ln_n + PI_U * lc_mode->lc_property.Regulator_kpd;
    }
}

static void light_lc_machine_output_calc(app_light_lc_state_t *lc_mode)
{
    APP_LOG_INFO("[%s], machine_state:0x%x,%d", __func__, lc_mode->machine_state, __LINE__);
    APP_LOG_INFO("[%s],Lightness_standby:%d,Lightness_on:%d,lightness_output:%d,Lightness_prolong:%d", __func__,\
    lc_mode->lc_property.Lightness_standby, lc_mode->lc_property.Lightness_on, lc_mode->output_state.lightness_output, \
    lc_mode->lc_property.Lightness_prolong);
    
    APP_LOG_INFO("[%s],remaining_time_ms:%d,Time_fade_on:%d,Time_prolong:%d,Time_fade_standby_auto:%d, Time_fade_standby_manual:%d", __func__,\
    lc_mode->lc_loo.remaining_time_ms, lc_mode->lc_property.Time_fade_on, lc_mode->lc_property.Time_prolong, \
    lc_mode->lc_property.Time_fade_standby_auto, lc_mode->lc_property.Time_fade_standby_manual);

    if(lc_mode->lc_property.Time_fade_standby_auto == 0x4E20)
    {
        uint8_t present_loo = 0;
        uint8_t status = nvds_put(NV_TAG_APP(BIND_PARAM_TAG(0, OnPowerUp_Bind_Property_Auto_LC_loo_State)),1 ,&present_loo);
    }
    if(lc_mode->lc_property.Time_fade_standby_manual == 0x4E20)
    {
        uint8_t present_loo = 1;
        uint8_t status = nvds_put(NV_TAG_APP(BIND_PARAM_TAG(0, OnPowerUp_Bind_Property_Manual_LC_loo_State)),1 ,&present_loo);
    }

    switch(lc_mode->machine_state)
    {
        case LIGHT_LC_STATE_MECHINE_STATES_OFF:
            lc_mode->output_state.lightness_output = 0;
            lc_mode->output_state.luxlvl_output= 0;
            break;
        case LIGHT_LC_STATE_MECHINE_STATES_STANDBY:
            lc_mode->output_state.lightness_output = lc_mode->lc_property.Lightness_standby;
            lc_mode->output_state.luxlvl_output= lc_mode->lc_property.LuxLvl_standby;
            break;
        case LIGHT_LC_STATE_MECHINE_STATES_FADE_ON:
            lc_mode->output_state.lightness_output = lc_mode->lc_property.Lightness_on \
                - lc_mode->lc_loo.remaining_time_ms/lc_mode->lc_property.Time_fade_on * (lc_mode->lc_property.Lightness_on - lc_mode->output_state.lightness_output);
            lc_mode->output_state.luxlvl_output= lc_mode->lc_property.LuxLvl_on\
                - lc_mode->lc_loo.remaining_time_ms/lc_mode->lc_property.Time_fade_on * (lc_mode->lc_property.LuxLvl_on - lc_mode->output_state.luxlvl_output);
            break;
        case LIGHT_LC_STATE_MECHINE_STATES_RUN:
            lc_mode->output_state.lightness_output = lc_mode->lc_property.Lightness_on;
            lc_mode->output_state.luxlvl_output= lc_mode->lc_property.LuxLvl_on;
            break;
        case LIGHT_LC_STATE_MECHINE_STATES_FADE:
            lc_mode->output_state.lightness_output = lc_mode->lc_property.Lightness_prolong \
                - lc_mode->lc_loo.remaining_time_ms/lc_mode->lc_property.Time_prolong * (lc_mode->lc_property.Lightness_prolong - lc_mode->output_state.lightness_output);
            lc_mode->output_state.luxlvl_output= lc_mode->lc_property.LuxLvl_prolong \
                - lc_mode->lc_loo.remaining_time_ms/lc_mode->lc_property.Time_prolong * (lc_mode->lc_property.LuxLvl_prolong - lc_mode->output_state.luxlvl_output);
            break;
        case LIGHT_LC_STATE_MECHINE_STATES_PROLONG:
            lc_mode->output_state.lightness_output = lc_mode->lc_property.Lightness_prolong;
            lc_mode->output_state.luxlvl_output= lc_mode->lc_property.LuxLvl_prolong;
            break;
        case LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_AUTO:
            lc_mode->output_state.lightness_output = lc_mode->lc_property.Lightness_standby \
                - lc_mode->lc_loo.remaining_time_ms/lc_mode->lc_property.Time_fade_standby_auto* (lc_mode->lc_property.Lightness_standby - lc_mode->output_state.lightness_output);
            lc_mode->output_state.luxlvl_output= lc_mode->lc_property.LuxLvl_standby \
                - lc_mode->lc_loo.remaining_time_ms/lc_mode->lc_property.Time_fade_standby_auto * (lc_mode->lc_property.LuxLvl_standby - lc_mode->output_state.luxlvl_output);
            break;
        case LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL:
            lc_mode->output_state.lightness_output = lc_mode->lc_property.Lightness_standby \
                - lc_mode->lc_loo.remaining_time_ms/lc_mode->lc_property.Time_fade_standby_manual* (lc_mode->lc_property.Lightness_standby - lc_mode->output_state.lightness_output);
            lc_mode->output_state.luxlvl_output= lc_mode->lc_property.LuxLvl_standby \
                - lc_mode->lc_loo.remaining_time_ms/lc_mode->lc_property.Time_fade_standby_manual * (lc_mode->lc_property.LuxLvl_standby - lc_mode->output_state.luxlvl_output);
            break;
        default:
            break;
    }

    APP_LOG_INFO("[%s] : lightness output 0x%x, luxlevel 0x%x", __func__, lc_mode->output_state.lightness_output, lc_mode->output_state.luxlvl_output);
}

static void light_lc_machine_timer_cb(void * p_context)
{    
    app_light_lc_server_t * p_server = (app_light_lc_server_t *) p_context;
    APP_LOG_INFO("[%s] enter.", __func__);

    if ((p_server->state.machine_state == LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_AUTO)
        || (p_server->state.machine_state == LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL))
    {
        p_server->state.machine_state = LIGHT_LC_STATE_MECHINE_STATES_STANDBY;
    }
    else
    {
        p_server->state.machine_state = p_server->state.next_machine_state;
    }

    light_lc_machine_output_calc(&(p_server->state));
    light_lc_PI_feedback_regulator_calc(&(p_server->state));
    p_server->state.lc_linear.value = p_server->state.output_state.lightness_output;//p_server->state.output_state.lightness_output * p_server->state.output_state.lightness_output /65535;
    p_server->state.lc_linear.value = p_server->state.lc_linear.value > p_server->state.output_state.regulator_output ? p_server->state.lc_linear.value : p_server->state.output_state.regulator_output;

    //if (p_server->state.lc_loo.remaining_time_ms != 0)
    {
        p_server->state.lc_loo.remaining_time_ms = 0;
        p_server->state.lc_loo.present_loo = p_server->state.lc_loo.target_loo;
        lc_state_value_update(p_server);
    }

    if (p_server->state.lc_loo.present_loo == LIGHT_LC_LOO_MODE_STATE_ON)
    {
        APP_LOG_INFO("[%s]  output lightness linear value 0x%x ", __func__, p_server->state.lc_linear.value);
    }
    //app_light_lc_bind_check(p_server,MODEL_ID_LIGHTS_LC);
    light_lc_state_machine(p_server, &p_server->state, LIGHT_LC_STATE_MECHINE_EVENTS_TIMER_OFF);
}

static void light_lc_mode_state_set_cb(light_lc_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_mode_set_params_t * p_in,
                                                    light_lc_mode_status_params_t * p_out)
{
    app_light_lc_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lc_server_t, server, p_self);
    light_lc_mode_status_params_t pub_out = {p_in->mode};
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: 0x%04X", __func__, p_self->model_instance_index, p_in->mode);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* mode =0, The controller is turned off. The binding with the Light Lightness state is disabled.*/
    if ((p_server->state.lc_mode.mode == LIGHT_LC_MODE_STATE_OFF) && (p_in->mode == LIGHT_LC_MODE_STATE_ON))
    {
        light_lc_state_machine(p_server, &p_server->state, LIGHT_LC_STATE_MECHINE_EVENTS_MODE_ON);
    }
    else if ((p_server->state.lc_mode.mode == LIGHT_LC_MODE_STATE_ON) && (p_in->mode == LIGHT_LC_MODE_STATE_OFF))
    {
        light_lc_state_machine(p_server, &p_server->state, LIGHT_LC_STATE_MECHINE_EVENTS_MODE_OFF);
    }
    p_server->state.lc_mode.mode = p_in->mode;

    store_status_before_power_down(p_self->model_instance_index, OnPowerUp_Bind_LC_mode_State, 0, 0, p_in->mode);

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->mode = p_server->state.lc_mode.mode;
    }

    light_lc_server_mode_status_publish(p_self, &pub_out);
}

static void light_lc_mode_state_get_cb(light_lc_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    light_lc_mode_status_params_t * p_out)
{
    app_light_lc_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lc_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* mode =0, The controller is turned off. The binding with the Light Lightness state is disabled.*/
    //light_lc_state_machine(&p_server->state);

    /* Prepare response */
    p_out->mode = p_server->state.lc_mode.mode;
}

static void light_lc_om_state_set_cb(light_lc_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_om_set_params_t * p_in,
                                                    light_lc_om_status_params_t * p_out)
{
    app_light_lc_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lc_server_t, server, p_self);
    light_lc_om_status_params_t pub_out = {p_in->mode};

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: 0x%04X", __func__, p_self->model_instance_index, p_in->mode);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* mode =0, The controller does not transition from a standby state when occupancy is reported.*/
    p_server->state.lc_om.mode = p_in->mode;

    store_status_before_power_down(p_self->model_instance_index, OnPowerUp_Bind_LC_om_State, p_in->mode, p_in->mode, p_in->mode);

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->mode = p_server->state.lc_om.mode;
    }

    //if (pub_out.mode == LIGHT_LC_OCC_MODE_STATE_OCC)
    {
        light_lc_server_occ_mode_status_publish(p_self, &pub_out);
    }

    // for pts test, occupancy state setting
#ifdef MESH_MODEL_BQB_TEST
    p_server->state.lc_occ_value.value = LIGHT_LC_OCC_REPORT_BEEN_OCC;
#endif

    if ((p_server->state.lc_om.mode == LIGHT_LC_OCC_MODE_STATE_OCC)
                && (p_server->state.lc_occ_value.value == LIGHT_LC_OCC_REPORT_BEEN_OCC))
    {
        light_lc_state_machine(p_server, &p_server->state, LIGHT_LC_STATE_MECHINE_EVENTS_OCC_ON);
    }

}

static void light_lc_om_state_get_cb(light_lc_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    light_lc_om_status_params_t * p_out)
{
    app_light_lc_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lc_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* mode =0, The controller is turned off. The binding with the Light Lightness state is disabled.*/
    //light_lc_state_machine(&p_server->state);

    /* Prepare response */
    p_out->mode = p_server->state.lc_om.mode;
}

static void light_lc_loo_state_set_cb(light_lc_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_loo_set_params_t * p_in,
                                                    const model_transition_t * p_in_transition,
                                                    light_lc_loo_status_params_t * p_out)
{
    app_light_lc_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lc_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: %d", __func__, p_self->model_instance_index, p_in->loo);
    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of OnOff value, process timing */
    p_server->value_updated = false;
    p_server->state.lc_loo.target_loo = p_in->loo;
    if (p_in_transition == NULL)
    {
        p_server->state.lc_loo.delay_ms = 0;
        p_server->state.lc_loo.remaining_time_ms = 0;
    }
    else
    {
        p_server->state.lc_loo.delay_ms = p_in_transition->delay_ms;
        p_server->state.lc_loo.remaining_time_ms = p_in_transition->transition_time_ms;
    }

    lc_state_process_timing(p_server);
    lc_state_value_update(p_server);

    /* Prepare response */
    if (p_out != NULL)
    {
        if(0x02 == pin_on_power_up[p_self->model_instance_index])
        {
            uint16_t store_len = 1;
            uint8_t present_loo = 0;
            uint8_t status = nvds_get(NV_TAG_APP(BIND_PARAM_TAG(p_self->model_instance_index, OnPowerUp_Bind_Property_Manual_LC_loo_State)), &store_len, &present_loo);
            if(status == NVDS_SUCCESS)
            {
                p_server->state.lc_loo.present_loo = present_loo;
            }
        }
        p_out->present_loo = p_server->state.lc_loo.present_loo;
        p_out->target_loo = p_server->state.lc_loo.target_loo;
        p_out->remaining_time_ms = p_server->state.lc_loo.remaining_time_ms;
    }
}

static uint32_t get_remaining_time_ms(app_light_lc_server_t* p_server)
{
    /* Requirement: Always report remaining time */
    if (p_server->state.lc_loo.remaining_time_ms > 0 && p_server->state.lc_loo.delay_ms == 0)
    {
        uint32_t current_time_clock_ms;
        uint16_t current_time_nb_wrap;
        uint32_t delta;

        mesh_run_time_get(&current_time_clock_ms, &current_time_nb_wrap);

        if (current_time_nb_wrap == p_server->loo_last_time_nb_wrap)
        {
            delta = current_time_clock_ms - p_server->loo_last_time_clock_ms;
        }
        else
        {
            delta = current_time_clock_ms + (0xFFFFFFFF - p_server->loo_last_time_clock_ms) + 1;
        }
        
        if (p_server->state.lc_loo.remaining_time_ms >= delta && delta > 0)
        {
            return p_server->state.lc_loo.remaining_time_ms - delta;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        return p_server->state.lc_loo.remaining_time_ms;
    }
}

static void light_lc_loo_state_get_cb(light_lc_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    light_lc_loo_status_params_t * p_out)
{
    app_light_lc_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lc_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);
    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the OnOff state */
    // TODO: update onoff state
    //p_server->onoff_get_cb(p_server->server.model_instance_index, &p_server->state.present_onoff);
    if((0x02 == pin_on_power_up[p_self->model_instance_index]) && (0x01 == p_server->state.lc_loo.present_loo))
    {
        static uint8_t flag = 0;
        if(!flag)
        {
            uint16_t store_len = 1;
            uint8_t present_loo;
            uint8_t status = nvds_get(NV_TAG_APP(BIND_PARAM_TAG(p_self->model_instance_index, OnPowerUp_Bind_Property_Auto_LC_loo_State)), &store_len, &present_loo);
            if(status == NVDS_SUCCESS)
            {
                p_server->state.lc_loo.present_loo = present_loo;
            }
            p_out->present_loo = p_server->state.lc_loo.present_loo;
            flag++;
        }
        else
        {
            p_out->present_loo = 0;
        }
    }
    else
    {
        p_out->present_loo = p_server->state.lc_loo.present_loo;
    }
    //p_out->present_loo = p_server->state.lc_loo.present_loo;
    p_out->target_loo = p_server->state.lc_loo.target_loo;
    p_out->remaining_time_ms = get_remaining_time_ms(p_server);
}

static void light_lc_sensor_status_cb(light_lc_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    uint8_t lc_senser_mask,
                                                    uint8_t lc_occupancy,
                                                    uint32_t lc_amb_luxlvl)
{
    app_light_lc_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lc_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: sensor status", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of lightness value, process timing */
    if (LC_OCCUPANCY_BIT & lc_senser_mask)
    {
        p_server->state.lc_occ_value.value = lc_occupancy;
    }

    if (LC_AMB_LUXLVL_BIT & lc_senser_mask)
    {
        p_server->state.lc_LuxLVL.value = lc_amb_luxlvl;
    }

    /* mode =0, The controller does not transition from a standby state when occupancy is reported.*/
    if (p_server->state.lc_om.mode == LIGHT_LC_OCC_MODE_STATE_OCC)
    {
        light_lc_state_machine(p_server, &p_server->state, LIGHT_LC_STATE_MECHINE_EVENTS_OCC_ON);
    }
}

static void app_light_lc_scene_recall_cb(void *p_server, uint8_t *stored_state, uint16_t state_length)
{
    app_light_lc_server_t *recal_server = (app_light_lc_server_t *)p_server;

    APP_LOG_INFO(" [%s] enter ", __func__);
    APP_LOG_INFO("server light lc recall state: value %d, length %d", *stored_state, state_length);

    if (NULL == p_server)
    {
        APP_LOG_INFO(" [%s] exit : Unknow server state to recall !!!", __func__);
        return ;
    }

    if (state_length != sizeof(recal_server->state.lc_loo.present_loo))
    {
        APP_LOG_INFO(" [%s] exit : invalid recall param!!!", __func__);
        return ;
    }

    APP_LOG_INFO(" recall %d, onoff %d, om mode %d, mode %d!!!", *(uint16_t *)stored_state, recal_server->state.lc_loo.present_loo, recal_server->state.lc_om.mode,recal_server->state.lc_mode.mode);
    //value has been recalled in scenes model

    if (stored_state == (uint8_t *)&recal_server->state.lc_loo.present_loo)
    {
        recal_server->state.lc_loo.target_loo = recal_server->state.lc_loo.present_loo;
        lc_state_process_timing(recal_server);
        lc_state_value_update(recal_server);
        if((recal_server->state.lc_property.Time_fade_standby_auto == 0x4e20)
                || (recal_server->state.lc_property.Time_fade_standby_manual == 0x4e20))
        {
            recal_server->state.lc_loo.present_loo = LIGHT_LC_LOO_MODE_STATE_OFF;
        }
    }

    if (stored_state == &recal_server->state.lc_om.mode)
    {
        light_lc_mode_status_params_t pub_out = {recal_server->state.lc_om.mode};
        light_lc_server_mode_status_publish(&recal_server->server, &pub_out);
    }
    recal_server->light_lc_set_cb(recal_server->server.model_instance_index, &(recal_server->state.lc_loo.present_loo), &(recal_server->state.lc_linear.value));
}

static void app_light_lc_bind_check(app_light_lc_server_t *p_server, uint32_t trigger_model)
{
    static uint8_t repeat_bind_lc_onoff_st[LIGHT_LC_INSTANCE_COUNT] = {0,};
    static uint16_t repeat_bind_lc_linear_st[LIGHT_LC_INSTANCE_COUNT] = {0,};
    
    uint8_t* repeat_bind_lc_onoff = &repeat_bind_lc_onoff_st[p_server->server.model_instance_index];
    uint16_t* repeat_bind_lc_linear = &repeat_bind_lc_linear_st[p_server->server.model_instance_index];

    APP_LOG_INFO(" %s enter, trigger model 0x%x, loo %d, linear %d", __func__, trigger_model, p_server->state.lc_loo.present_loo, p_server->state.lc_linear.value);
    if (*repeat_bind_lc_onoff != p_server->state.lc_loo.present_loo)
    {
        if (trigger_model != MODEL_ID_GENS_OO)
        {
            /* check bind generic onoff state */
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_GENS_OO, MODEL_ID_LIGHTS_LC, &p_server->state.lc_loo.present_loo, sizeof(p_server->state.lc_loo.present_loo));
        }
        *repeat_bind_lc_onoff = p_server->state.lc_loo.present_loo;
    }

    APP_LOG_INFO("trigger mode 0x%x, lc mode %d", trigger_model, p_server->state.lc_mode.mode);
    
    if (*repeat_bind_lc_linear != p_server->state.lc_linear.value)
    {
        if (trigger_model != MODEL_ID_LIGHTS_LN)
        {
            /* check bind light Lightness state */
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_LN, MODEL_ID_LIGHTS_LC, &p_server->state.output_state.lightness_output, sizeof(p_server->state.output_state.lightness_output));
//            if (p_server->state.lc_mode.mode == LIGHT_LC_MODE_STATE_ON)
//            {
//                mesh_model_bind_check(p_server->server.model_instance_index-1, MODEL_ID_LIGHTS_LN, MODEL_ID_LIGHTS_LC, &p_server->state.output_state.lightness_output, sizeof(p_server->state.output_state.lightness_output));
//            }
        }
        *repeat_bind_lc_linear = p_server->state.lc_linear.value;
    }
    return ;
}

static bool app_light_lc_bind_cb(void *p_server, uint32_t src_model_id, void *p_data, uint16_t data_len)
{
    app_light_lc_server_t * pl_server = (app_light_lc_server_t *)p_server;
    bool ret = false;

    APP_LOG_INFO("[%s] enter, SERVER[%d], src model %04X data length %d", __func__, pl_server->server.model_instance_index, src_model_id, data_len);

    if (pl_server != NULL)
    {
        switch(src_model_id)
        {
            /*case MODEL_ID_LIGHTS_LN:
            {
                if (data_len == 2)
                {
                    uint16_t present_ln = *(int16_t *)p_data;
                    uint16_t present_ln_linear = CV_LIGHTS_LN_LINEAR(present_ln);
                    if( pl_server->state.lc_linear.value != present_ln_linear)
                    {
                        pl_server->state.lc_mode.mode = LIGHT_LC_MODE_STATE_OFF;

                        ret = false;
                    }
                    APP_LOG_INFO("model lightness linear bind message length %d, value %d, lc mode %d", data_len, present_ln_linear, pl_server->state.lc_mode.mode);
                }
                break;
            }*/
            case MODEL_ID_GENS_OO:
            {
                if (data_len == 1)
                {
                    uint8_t onoff = *(uint8_t *)p_data;

                    if (onoff == 0x00)//onoff :off
                    {
                        pl_server->state.lc_loo.target_loo = 0;

                        lc_state_process_timing(pl_server);
                        lc_state_value_update(pl_server);

                        ret = true;
                    }
                    else if (onoff == 0x01)//onoff :on
                    {
                        pl_server->state.lc_loo.target_loo = 1;

                        lc_state_process_timing(pl_server);
                        lc_state_value_update(pl_server);

                        ret = true;
                    }
                    APP_LOG_INFO("model gen onoff bind message length %d, value %d, ligh lc onoff %d", data_len, onoff, pl_server->state.lc_loo.present_loo);
                }
                break;
            }
            default:
                break;
        }

        if(ret)
        {
            //app_light_lc_status_publish(pl_server);
            //app_light_lc_bind_check(pl_server, src_model_id);
        }
    }

    return ret;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */
void light_lc_set_machine_timer(app_light_lc_state_t *lc_mode, uint32_t transition_time_ms)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    uint32_t status = MESH_ERROR_NO_ERROR;
    mesh_timer_t *p_timer = &(lc_mode->machine_timer);
    
    // if the timer isn't in list, no error occurs.
    mesh_timer_clear(&p_timer->timer_id);

    /* Process timing requirements */
    p_timer->delay_ms = transition_time_ms;
    status = mesh_timer_set(p_timer);

    if (status != MESH_ERROR_NO_ERROR)
    {
       APP_LOG_INFO("State transition timer error");
    }
}

static void light_lc_do_action(app_light_lc_state_t *lc_mode, uint8_t action, Light_lc_state_mechine_actions_timer_t Transition_time, Light_lc_state_mechine_states_t next_state)
{
    char *action_string = NULL;
    uint32_t transition_time_ms = 0;

    action_string = (char *)(action&LIGHT_LC_STATE_MECHINE_ACTIONS_SET_ON ? app_light_machine_action_string[1]
                                                       : (action&LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF ? app_light_machine_action_string[2]
                                                       : (action&LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OCC_OFF ? app_light_machine_action_string[4]
                                                       : (action & LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER ? app_light_machine_action_string[5] : app_light_machine_action_string[0]))));
    APP_LOG_INFO("Light LC state Machine next states is %s,  Set %s, %s %s",
                                                        app_light_machine_state_string[next_state],
                                                        action_string,
                                                        action & LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER ? app_light_machine_action_string[5]:"Abort Timer",
                                                        app_light_machine_timer_string[Transition_time]);

    if (action & LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF)
    {
        switch(next_state)
        {
            case LIGHT_LC_STATE_MECHINE_STATES_FADE_ON:
            case LIGHT_LC_STATE_MECHINE_STATES_FADE:
            case LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_AUTO:
            case LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL:
                lc_mode->lc_loo.target_loo = LIGHT_LC_LOO_MODE_STATE_OFF;
                break;
            default:
                lc_mode->lc_loo.present_loo = LIGHT_LC_LOO_MODE_STATE_OFF;
                break;
        }
    }
    else if (action & LIGHT_LC_STATE_MECHINE_ACTIONS_SET_ON)
    {
        switch(next_state)
        {
            case LIGHT_LC_STATE_MECHINE_STATES_FADE_ON:
            case LIGHT_LC_STATE_MECHINE_STATES_FADE:
            case LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_AUTO:
            case LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL:
                lc_mode->lc_loo.present_loo = LIGHT_LC_LOO_MODE_STATE_ON;
                lc_mode->lc_loo.target_loo = LIGHT_LC_LOO_MODE_STATE_ON;
                break;
            default:
                lc_mode->lc_loo.present_loo = LIGHT_LC_LOO_MODE_STATE_ON;
                break;
        }
    }
    else if (action & LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OCC_OFF)
    {
        lc_mode->lc_occ_value.value = LIGHT_LC_OCC_MODE_STATE_NO_OCC;
    }

    if (action & LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER)
    {
        switch(Transition_time)
        {
            case LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T1:
                transition_time_ms = lc_mode->lc_property.Light_lc_set_timer_t1;
                break;
            case LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T2:
                transition_time_ms = lc_mode->lc_property.Light_lc_set_timer_t2;
                break;
            case LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T3:
                transition_time_ms = lc_mode->lc_property.Light_lc_set_timer_t3;
                break;
            case LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T4:
                transition_time_ms = lc_mode->lc_property.Light_lc_set_timer_t4;
                break;
            case LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T5:
                transition_time_ms = lc_mode->lc_property.Light_lc_set_timer_t5;
                break;
            case LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T6:
                transition_time_ms = lc_mode->lc_property.Light_lc_set_timer_t6;
                break;
            case LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_TRANSITION:
                if (lc_mode->lc_loo.remaining_time_ms > 0)
                {
                    transition_time_ms = lc_mode->lc_loo.remaining_time_ms;
                }
                else
                {
                    if (next_state == LIGHT_LC_STATE_MECHINE_STATES_FADE_ON)
                    {
                        transition_time_ms = lc_mode->lc_property.Time_fade_on;
                    }
                    else if (next_state == LIGHT_LC_STATE_MECHINE_STATES_FADE)
                    {
                        transition_time_ms = lc_mode->lc_property.Time_fade;
                    }
                    else if (next_state == LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_AUTO)
                    {
                        transition_time_ms = lc_mode->lc_property.Time_fade_standby_auto;
                    }
                    else if (next_state == LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL)
                    {
                        transition_time_ms = lc_mode->lc_property.Time_fade_standby_manual;
                    }

                    lc_mode->lc_loo.remaining_time_ms = transition_time_ms;
                }
                break;
            default:
                APP_LOG_INFO("no transition time found");
                break;
        }
    }
/*
    lc_mode->machine_state = next_state;//state changes immediate
    if (lc_mode->lc_loo.present_loo == LIGHT_LC_LOO_MODE_STATE_ON)
    {
        light_lc_machine_output_calc(lc_mode);
        light_lc_PI_feedback_regulator_calc(lc_mode);

        lc_mode->lc_linear.value = lc_mode->output_state.lightness_output;//lc_mode->output_state.lightness_output * lc_mode->output_state.lightness_output /65535;
        lc_mode->lc_linear.value = lc_mode->lc_linear.value > lc_mode->output_state.regulator_output ? lc_mode->lc_linear.value : lc_mode->output_state.regulator_output;

        APP_LOG_INFO("[%s]  output lightness linear value 0x%x ", __func__, lc_mode->lc_linear.value);
    }
*/
    if (transition_time_ms != 0)
    {
        lc_mode->next_machine_state = next_state;
        if (transition_time_ms == LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T5 || transition_time_ms == LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T6)
        {
            lc_mode->lc_loo.target_loo = LIGHT_LC_LOO_MODE_STATE_OFF;
        }
        if ((next_state == LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL) && (transition_time_ms == 0x012c))
        {
            lc_mode->lc_loo.present_loo = LIGHT_LC_LOO_MODE_STATE_OFF;
        }
        light_lc_set_machine_timer(lc_mode, transition_time_ms);
    }
    else
    {
        lc_mode->machine_state = lc_mode->next_machine_state = next_state;
        light_lc_machine_output_calc(lc_mode);
        light_lc_PI_feedback_regulator_calc(lc_mode);
        APP_LOG_INFO("lc_mode->machine_state =  0x%x ", lc_mode->machine_state);
        lc_mode->lc_linear.value = lc_mode->output_state.lightness_output * lc_mode->output_state.lightness_output /65535;
        lc_mode->lc_linear.value = lc_mode->lc_linear.value > lc_mode->output_state.regulator_output ? lc_mode->lc_linear.value : lc_mode->output_state.regulator_output;
        if (lc_mode->lc_loo.present_loo == LIGHT_LC_LOO_MODE_STATE_ON)
        {
            APP_LOG_INFO("[%s]  output lightness linear value 0x%x ", __func__, lc_mode->lc_linear.value);
        }
        //lc_mode->machine_state = lc_mode->next_machine_state = next_state;
    }
}
inline static void clear_timer_when_receive_event(app_light_lc_state_t *lc_mode)
{
    mesh_timer_t *p_timer = &(lc_mode->machine_timer);
    // if the timer isn't in list, no error occurs.
    mesh_timer_clear(&p_timer->timer_id);
    lc_mode->lc_loo.target_loo = lc_mode->lc_loo.present_loo;
}

void light_lc_state_machine(app_light_lc_server_t * p_server, app_light_lc_state_t *lc_mode, Light_lc_state_mechine_events_t event)
{
    int8_t arr_length = sizeof(machine_actions_task)/sizeof(app_light_lc_machine_transtion_action_t);

    APP_LOG_INFO("Light LC state Machine current states is[%d] [%s], trigger event [%s]",lc_mode->machine_state, app_light_machine_state_string[lc_mode->machine_state], app_light_machine_event_string[event]);
    for (int8_t i = 0; i<arr_length; i++ )
    {
        if ((machine_actions_task[i].current_state == lc_mode->machine_state)
            &&(machine_actions_task[i].events == event))
        {
            if ((machine_actions_task[i].conditon == LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY)
                ||(machine_actions_task[i].conditon == light_lc_get_mechine_condition(lc_mode)))
            {
                clear_timer_when_receive_event(lc_mode);
                light_lc_do_action(lc_mode, machine_actions_task[i].action, machine_actions_task[i].Transition_time, machine_actions_task[i].next_state);
                break;
            }
        }
    }
    app_light_lc_bind_check(p_server,MODEL_ID_LIGHTS_LC);
//    if ((lc_mode->lc_loo.present_loo == LIGHT_LC_LOO_MODE_STATE_ON) || (lc_mode->lc_mode.mode == LIGHT_LC_MODE_STATE_OFF))
//    {
//        //lc_state_value_update(p_server);
//        app_light_lc_bind_check(p_server,MODEL_ID_LIGHTS_LC);
//    }
    event_flag = event;
}


uint16_t app_light_lc_mode_status_publish(app_light_lc_server_t * p_server)
{
    light_lc_mode_status_params_t params = 
    {
        .mode = p_server->state.lc_mode.mode,
    };
    return light_lc_server_mode_status_publish(&p_server->server, &params);
}

uint16_t app_light_lc_om_status_publish(app_light_lc_server_t * p_server)
{
    light_lc_om_status_params_t params = 
    {
        .mode = p_server->state.lc_om.mode
    };
    return light_lc_server_occ_mode_status_publish(&p_server->server, &params);
}

uint16_t app_light_lc_loo_status_publish(app_light_lc_server_t * p_server)
{
    light_lc_loo_status_params_t params = 
    {
        .present_loo = p_server->state.lc_loo.present_loo,
        .target_loo = p_server->state.lc_loo.target_loo,
        .remaining_time_ms = get_remaining_time_ms(p_server),
    };
    return light_lc_server_loo_status_publish(&p_server->server, &params);
}


uint16_t app_light_lc_server_init(app_light_lc_server_t *p_server, uint8_t element_offset, app_light_lc_set_cb_t set_cb, app_light_lc_get_cb_t get_cb)
{
    if(( p_server == NULL) || (LIGHT_LC_INSTANCE_COUNT <= element_offset))
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

    p_server->light_lc_set_cb = set_cb;
    p_server->light_lc_get_cb = get_cb;
    p_server->state.machine_state = LIGHT_LC_STATE_MECHINE_STATES_OFF;
    p_server->state.lc_loo.present_loo = 0;
    p_server->state.lc_loo.target_loo = 0;
    p_server->state.lc_loo.remaining_time_ms = 0;
    p_server->state.lc_loo.delay_ms = 0;

    p_server->state.lc_mode.mode = LIGHT_LC_MODE_STATE_OFF;
    p_server->state.lc_om.mode = LIGHT_LC_OCC_MODE_STATE_OCC;
    power_up_sequence_behavior(element_offset, element_offset, OnPowerUp_Bind_LC_mode_State, (uint16_t *)&p_server->state.lc_mode.mode);
    power_up_sequence_behavior(element_offset, element_offset, OnPowerUp_Bind_LC_om_State, (uint16_t *)&p_server->state.lc_om.mode);
    power_up_sequence_behavior(element_offset, element_offset, OnPowerUp_Bind_LC_loo_State, (uint16_t *)&p_server->state.lc_loo.present_loo);

    p_server->state.lc_occ_value.value = LIGHT_LC_OCC_REPORT_NO_OCC;
    p_server->state.lc_LuxLVL.value = 0;
    p_server->state.lc_linear.value = 0;
    memset(&(p_server->state.lc_property), 0, sizeof(app_light_lc_property_state_t));
    p_server->state.lc_property.Regulator_kid = 0.000000f;
    p_server->state.lc_property.Regulator_kiu= 0.000000f;
    p_server->state.lc_property.Regulator_kpd= 0.000000f;
    p_server->state.lc_property.Regulator_kpu= 0.000000f;
    p_server->state.lc_property.Light_lc_set_timer_t1 = 4000;//ms
    p_server->state.lc_property.Light_lc_set_timer_t2 = 4000;//ms
    p_server->state.lc_property.Light_lc_set_timer_t3 = 4000;//ms
    p_server->state.lc_property.Light_lc_set_timer_t4 = 4000;//ms
    p_server->state.lc_property.Light_lc_set_timer_t5 = 4000;//ms
    p_server->state.lc_property.Light_lc_set_timer_t6 = 4000;//ms
    memset(&(p_server->state.output_state), 0, sizeof(app_light_lc_output_state_t));

    p_server->loo_last_time_clock_ms = 0;
    p_server->loo_last_time_nb_wrap = 0;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->value_updated = false;

    p_server->server.settings.p_callbacks = &light_lc_srv_cbs,
        
    p_server->loo_state_timer.callback = light_lc_loo_state_timer_cb;
    p_server->loo_state_timer.p_args = p_server;
    p_server->loo_state_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->loo_state_timer.reload = false;

    p_server->state.machine_timer.callback = light_lc_machine_timer_cb;
    p_server->state.machine_timer.p_args = p_server;
    p_server->state.machine_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->state.machine_timer.reload = false;

    mesh_model_bind_list_add(MODEL_ID_LIGHTS_LC, element_offset, (void *)p_server, app_light_lc_bind_cb);
    mesh_scenes_state_store_with_scene(element_offset, app_light_lc_scene_recall_cb, (void *)p_server, (uint8_t *)&p_server->state.lc_loo.present_loo, sizeof(p_server->state.lc_loo.present_loo));
    mesh_scenes_state_store_with_scene(element_offset, app_light_lc_scene_recall_cb, (void *)p_server, (uint8_t *)&p_server->state.lc_mode.mode, sizeof(p_server->state.lc_mode.mode));
    mesh_scenes_state_store_with_scene(element_offset, app_light_lc_scene_recall_cb, (void *)p_server, (uint8_t *)&p_server->state.lc_om.mode, sizeof(p_server->state.lc_om.mode));

    return light_lc_server_init(&p_server->server, element_offset);
}

