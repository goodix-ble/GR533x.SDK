/**
 ****************************************************************************************
 *
 * @file app_level.c
 *
 * @brief APP Level API Implementation.
 *
 ****************************************************************************************
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
#include "app_log.h"
#include "model_common.h"
#include "app_level_server.h"
#include "generic_level_server.h"
#include "model_common.h"
#include "user_app.h"
#include "mesh_bind.h"
#include "mesh_scenes_common.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void generic_level_state_set_cb(const generic_level_server_t *p_self,
                                       const mesh_model_msg_ind_t *p_rx_msg,
                                       const generic_level_set_params_t * p_in,
                                       const model_transition_t * p_in_transition,
                                       generic_level_status_params_t * p_out);
                                       
static void generic_level_state_get_cb(const generic_level_server_t *p_self,
                                       const mesh_model_msg_ind_t * p_rx_msg,
                                       generic_level_status_params_t * p_out);
                                       
static void generic_level_state_delta_set_cb(const generic_level_server_t * p_self,
                                             const mesh_model_msg_ind_t *p_rx_msg,
                                             const generic_level_delta_set_params_t * p_in,
                                             const model_transition_t * p_in_transition,
                                             generic_level_status_params_t * p_out);

static void generic_level_state_move_set_cb(const generic_level_server_t * p_self,
                                            const mesh_model_msg_ind_t *p_rx_msg,
                                            const generic_level_move_set_params_t * p_in,
                                            const model_transition_t * p_in_transition,
                                            generic_level_status_params_t * p_out);                                                

static void app_level_bind_check(app_level_server_t *p_server, uint32_t trigger_model);

static void level_state_timer_cb(void * p_context);
/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
const generic_level_server_callbacks_t level_srv_cbs =
{
    .level_cbs.set_cb = generic_level_state_set_cb,
    .level_cbs.get_cb = generic_level_state_get_cb,
    .level_cbs.delta_set_cb = generic_level_state_delta_set_cb,
    .level_cbs.move_set_cb = generic_level_state_move_set_cb,
};


/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static void compute_move_info(app_level_server_t * p_server)
{
    if(p_server->state.transition_time_ms != 0)
    {
        uint8_t enc_time = TRANSITION_TIME_UNKNOWN;
        enc_time = model_transition_time_encode(p_server->state.transition_time_ms);
        p_server->state.params.move.number_steps = (enc_time & ~TRANSITION_TIME_STEP_MASK);
        
        switch(enc_time & TRANSITION_TIME_STEP_MASK)
        {
            case TRANSITION_TIME_STEP_RESOLUTION_100MS:
            p_server->state.params.move.resolution_time = TRANSITION_TIME_STEP_100MS_FACTOR;
            break;

            case TRANSITION_TIME_STEP_RESOLUTION_1S:
            p_server->state.params.move.resolution_time = TRANSITION_TIME_STEP_1S_FACTOR;
            break;

            case TRANSITION_TIME_STEP_RESOLUTION_10S:
            p_server->state.params.move.resolution_time = TRANSITION_TIME_STEP_10S_FACTOR;              
            break;

            case TRANSITION_TIME_STEP_RESOLUTION_10M:
            p_server->state.params.move.resolution_time = TRANSITION_TIME_STEP_10M_FACTOR;              
            break;

            default:
                break;
        }
        p_server->state.params.move.step_length = p_server->state.params.move.required_move / p_server->state.params.move.number_steps;
        p_server->state.params.move.remain_length = p_server->state.params.move.required_move % p_server->state.params.move.number_steps;
    }
    
}


static void set_or_delta_set_state_update(app_level_server_t * p_server)
{
    APP_LOG_INFO("[%s] enter : delay: %d, transition: %d.", __func__,p_server->state.delay_ms, p_server->state.transition_time_ms);
    
    /* Requirement: If delay and transition time is zero, current state changes to the target state. */
    if (p_server->state.delay_ms == 0 && p_server->state.transition_time_ms == 0)
    {       
        p_server->state.present_level = p_server->state.target_level;
       
        generic_level_status_params_t status_params;
        status_params.present_level = p_server->state.present_level;
        status_params.target_level = p_server->state.target_level;
        status_params.remaining_time_ms = p_server->state.transition_time_ms;
        generic_level_server_status_publish(&p_server->server, &status_params);

        if (!p_server->value_updated)
        {
            p_server->level_set_cb(p_server->server.model_instance_index, p_server->state.present_level);
            app_level_bind_check(p_server,MODEL_ID_GENS_LVL);
            // TODO: enhance logical judgement here
            p_server->level_set_cb(p_server->server.model_instance_index, p_server->state.present_level);
            p_server->value_updated = true;
        }
    }   
}



static void level_state_process_timing(app_level_server_t * p_server)
{
    APP_LOG_INFO("[%s] enter.", __func__);
        
    uint32_t status = MESH_ERROR_SDK_INVALID_PARAM;
    // if the timer isn't in list, no error occurs.
    mesh_timer_clear(&p_server->app_timer.timer_id);   

    /* Process timing requirements */
    if (p_server->state.delay_ms != 0)
    {
        p_server->app_timer.delay_ms = p_server->state.delay_ms;
        status = mesh_timer_set(&p_server->app_timer);
        if(MESH_ERROR_NO_ERROR == status)
        {
            APP_LOG_INFO("[%s] : timer set for delay.", __func__);
        }
        
    }
    else if (p_server->state.transition_time_ms != 0)
    {
        if (p_server->state.transition_type !=  TRANSITION_MOVE_SET)
        {
            p_server->app_timer.delay_ms = p_server->state.transition_time_ms;
            status = mesh_timer_set(&p_server->app_timer);
            if(MESH_ERROR_NO_ERROR == status)
            {
                APP_LOG_INFO("[%s] : timer set for transition.", __func__);
            }
            mesh_run_time_get(&p_server->last_time_clock_ms, &p_server->last_time_nb_wrap);
        }
        else
        {
            level_state_timer_cb(p_server);
        }
    }
}

static void level_state_timer_cb(void * p_context)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    app_level_server_t * p_server = (app_level_server_t *) p_context;
    
    if (p_server->state.transition_type !=  TRANSITION_MOVE_SET)
    {
        /* Requirement: Process timing, Process the delay first and then the transition time.*/     
        if (p_server->state.delay_ms != 0)
        {
            p_server->state.delay_ms = 0;
            set_or_delta_set_state_update(p_server);
            APP_LOG_INFO("[%s] : delay timeout ", __func__);
        }
        else if (p_server->state.transition_time_ms != 0)
        {
            p_server->state.transition_time_ms = 0;
            set_or_delta_set_state_update(p_server);
            APP_LOG_INFO("[%s] : transition timeout ", __func__);
        }
        level_state_process_timing(p_server);
    }
    else
    {
        if (p_server->state.delay_ms != 0)
        {
            p_server->state.delay_ms = 0;       
        }
        else if(p_server->state.transition_time_ms != 0 && p_server->state.params.move.number_steps != 0)
        {
            p_server->state.transition_time_ms -= p_server->state.params.move.resolution_time;
            p_server->state.params.move.number_steps--;
            p_server->state.present_level += p_server->state.params.move.step_length;
            p_server->level_set_cb(p_server->server.model_instance_index, p_server->state.present_level);
        }
        
        if(p_server->state.transition_time_ms != 0 && p_server->state.params.move.number_steps != 0)
        {
            p_server->app_timer.delay_ms = p_server->state.params.move.resolution_time;
            mesh_timer_set(&p_server->app_timer);
        }
        else
        {
            if(p_server->state.params.move.remain_length != 0)
            {
                p_server->state.present_level += p_server->state.params.move.remain_length;
                p_server->state.params.move.remain_length = 0;
            }
            p_server->level_set_cb(p_server->server.model_instance_index, p_server->state.present_level);
            app_level_bind_check(p_server, MODEL_ID_GENS_LVL);
            // TODO: enhance logical judgement here
            p_server->level_set_cb(p_server->server.model_instance_index, p_server->state.present_level);
        }

    }
        
}


static uint32_t get_remaining_time_ms(app_level_server_t *p_server)
{
    if (p_server->state.transition_type == TRANSITION_MOVE_SET)
    {
        return 0xFFFFFFFF;
    }
    else
    {
        uint32_t current_time_clock_ms;
        uint16_t current_time_nb_wrap;
        uint32_t elapsed_time;

        mesh_run_time_get(&current_time_clock_ms, &current_time_nb_wrap);

        // only two conditions:
        // current_time_nb_wrap == last_time_nb_wrap
        if (current_time_nb_wrap == p_server->last_time_nb_wrap)
        {
            elapsed_time = current_time_clock_ms - p_server->last_time_clock_ms;
        }
        // current_time_nb_wrap == last_time_nb_wrap + 1
        else
        {
            elapsed_time = current_time_clock_ms + (0xFFFFFFFF - p_server->last_time_clock_ms) + 1;
        }
        
        if(elapsed_time >= p_server->state.transition_time_ms)
        {
            return 0;
        }
        else
        {
            return(p_server->state.transition_time_ms - elapsed_time);
        }
        
    }
}

/***** Generic level model interface callbacks *****/
static void generic_level_state_get_cb(const generic_level_server_t *p_self,
                                       const mesh_model_msg_ind_t * p_rx_msg,
                                       generic_level_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    APP_LOG_INFO("SERVER[%d] -- msg: GET ", p_self->model_instance_index);

    app_level_server_t *p_server = PARENT_BY_FIELD_GET(app_level_server_t, server, p_self);
    

    /* Requirement: Provide the current value of the Level state */
    p_server->level_get_cb(p_server->server.model_instance_index, &p_server->state.present_level);
    p_out->present_level = p_server->state.present_level;
    p_out->target_level = p_server->state.target_level;
    p_out->remaining_time_ms = get_remaining_time_ms(p_server);
}
    


static void generic_level_state_set_cb(const generic_level_server_t *p_self,
                                       const mesh_model_msg_ind_t *p_rx_msg,
                                       const generic_level_set_params_t * p_in,
                                       const model_transition_t * p_in_transition,
                                       generic_level_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    

    app_level_server_t *p_server = PARENT_BY_FIELD_GET(app_level_server_t, server, p_self);
    
    /* Requirement: If transition time parameters are unavailable and default transition time state
    is not available, transition shall be instantaneous. */   
    if (p_in_transition == NULL)
    {
        p_server->state.delay_ms = 0;
        if (p_server->p_dtt_ms == NULL)
        {
            p_server->state.transition_time_ms = 0;
        }
        else
        {
            p_server->state.transition_time_ms = *p_server->p_dtt_ms;
        }
    }
    else
    {
        p_server->state.delay_ms = p_in_transition->delay_ms;
        p_server->state.transition_time_ms = p_in_transition->transition_time_ms;
    }
    
    /* Update internal representation of Level value, process timing. */    
    p_server->value_updated = false;
    p_server->state.target_level = p_in->level;
    p_server->state.transition_type = TRANSITION_SET;
    p_server->state.params.set.initial_present_level = p_server->state.present_level;
    p_server->state.params.set.required_delta = p_server->state.target_level - p_server->state.present_level;
    
    APP_LOG_INFO("SERVER[%d] -- msg: SET: Level: %d  delay: %d  tt: %d  req-delta: %d ", 
    p_self->model_instance_index, p_server->state.target_level,  p_server->state.delay_ms, 
    p_server->state.transition_time_ms,p_server->state.params.set.required_delta);
    
    set_or_delta_set_state_update(p_server);
    level_state_process_timing(p_server);
                
    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->present_level = p_server->state.present_level;
        p_out->target_level = p_server->state.target_level;
        p_out->remaining_time_ms = p_server->state.transition_time_ms;
    }
        
}

static void generic_level_state_delta_set_cb(const generic_level_server_t * p_self,
                                             const mesh_model_msg_ind_t *p_rx_msg,
                                             const generic_level_delta_set_params_t * p_in,
                                             const model_transition_t * p_in_transition,
                                             generic_level_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter.", __func__);   
    
    app_level_server_t   * p_server = PARENT_BY_FIELD_GET(app_level_server_t, server, p_self);
    /* Requirement: If transition time parameters are unavailable and default transition time state
    is not available, transition shall be instantaneous. */
    if (p_in_transition == NULL)
    {
        p_server->state.delay_ms = 0;
        if (p_server->p_dtt_ms == NULL)
        {
            p_server->state.transition_time_ms = 0;
        }
        else
        {
            p_server->state.transition_time_ms = *p_server->p_dtt_ms;
        }
    }
    else
    {
        p_server->state.delay_ms = p_in_transition->delay_ms;
        p_server->state.transition_time_ms = p_in_transition->transition_time_ms;
    }
    p_server->value_updated = false;
    p_server->state.transition_type = TRANSITION_DELTA_SET; 
    /* Update internal representation of Level value, process timing. */
    /* Requirement: If TID is same as previous TID for the same message, delta value is cumulative. */
    int32_t delta = p_in->delta_level;
    delta = p_in->delta_level % UINT16_MAX;

    if (!model_transaction_is_new(&p_server->server.tid_tracker))
    {
        APP_LOG_INFO("SERVER[%d] -- tid: %d Same TID, assuming cumulative delta set.", p_self->model_instance_index, p_in->tid);        
    }
    else
    {
        p_server->state.params.set.initial_present_level = p_server->state.present_level;       
    }   
    
    p_server->state.target_level = p_server->state.params.set.initial_present_level + delta;
    //p_server->state.target_level = p_server->state.present_level + delta;
    p_server->state.params.set.required_delta = delta;
    
    APP_LOG_INFO("SERVER[%d] -- msg: Delta SET: delta: %d  delay: %d  tt: %d", 
    p_self->model_instance_index, delta, p_server->state.delay_ms, p_server->state.transition_time_ms);
    
    APP_LOG_INFO("SERVER[%d] -- msg: Delta SET: initial-level: %d  present-level: %d  target-level: %d", 
    p_self->model_instance_index, p_server->state.params.set.initial_present_level,
    p_server->state.present_level, p_server->state.target_level);
    
    set_or_delta_set_state_update(p_server);
    level_state_process_timing(p_server);
            
    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->present_level = p_server->state.present_level;
        p_out->target_level = p_server->state.target_level;
        p_out->remaining_time_ms = p_server->state.transition_time_ms;
    }
}

static void generic_level_state_move_set_cb(const generic_level_server_t * p_self,
                                            const mesh_model_msg_ind_t *p_rx_msg,
                                            const generic_level_move_set_params_t * p_in,
                                            const model_transition_t * p_in_transition,
                                            generic_level_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    app_level_server_t   * p_server = PARENT_BY_FIELD_GET(app_level_server_t, server, p_self);
    
    if (p_in_transition == NULL)
    {
        //If the resulting Transition Time is equal to 0, the Generic Move Set command will not initiate any Generic Level state change
        return ;
        //p_server->state.delay_ms = 0;
        //p_server->state.transition_time_ms = 0;
        //p_server->state.target_level = p_server->state.present_level;
    }
    else
    {
        p_server->state.delay_ms = p_in_transition->delay_ms;
        p_server->state.transition_time_ms = p_in_transition->transition_time_ms;
    }
    /* Requirement: For the status message: The target Generic Level state is the upper limit of
       the Generic Level state when the transition speed is positive, or the lower limit of the
       Generic Level state when the transition speed is negative. */
    if (p_in->move_level > 0)
    {
        p_server->state.target_level = INT16_MAX;
    }
    else
    {
        p_server->state.target_level = INT16_MIN;
    }
    p_server->state.params.move.required_move = p_in->move_level;
    p_server->state.params.move.initial_present_level = p_server->state.present_level;
    p_server->state.transition_type = TRANSITION_MOVE_SET;
    
    compute_move_info(p_server);
    
    APP_LOG_INFO("SERVER[%d] -- msg: MOVE SET: move-level: %d  delay: %d  tt: %d ", 
    p_self->model_instance_index, p_in->move_level, p_server->state.delay_ms, p_server->state.transition_time_ms);
    
    APP_LOG_INFO("SERVER[%d] -- msg: MOVE SET: resolution_time: %d  number_steps: %d ", 
    p_self->model_instance_index, p_server->state.params.move.resolution_time, p_server->state.params.move.number_steps);
    
    if (p_in->move_level == 0 || p_server->state.transition_time_ms == 0)
    {
        APP_LOG_INFO("SERVER[%d] -- msg: MOVE SET: if the move-level or the transition-time equal to 0, it shall stop changing the Generic Level state");
    }

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->present_level = p_server->state.present_level;
        p_out->target_level = p_server->state.target_level;
        p_out->remaining_time_ms = 0xFFFFFFFF;//p_server->state.transition_time_ms;
    }
    level_state_process_timing(p_server);
}

static void app_level_scene_recall_cb(void *p_server, uint8_t *stored_state, uint16_t state_length)
{
    app_level_server_t *recal_server = (app_level_server_t *)p_server;

    APP_LOG_INFO("[%s] Server level recall state: value %d, length %d", __func__, *(int16_t *)stored_state, state_length);

    if (NULL == p_server)
    {
        APP_LOG_INFO(" [%s] exit : Unknow server state to recall !!!", __func__);
        return ;
    }

    if (state_length != sizeof(recal_server->state.present_level))
    {
        APP_LOG_INFO(" [%s] exit : invalid recall param!!!", __func__);
        return ;
    }
    recal_server->state.present_level= *(int16_t *)stored_state;

    generic_level_status_params_t status =
    {
        .present_level = recal_server->state.present_level,
        .target_level = recal_server->state.target_level,
        .remaining_time_ms = recal_server->state.transition_time_ms
    };

    generic_level_server_status_publish(&recal_server->server, &status);

    recal_server->level_set_cb(recal_server->server.model_instance_index, recal_server->state.present_level);
}

static void app_level_bind_check(app_level_server_t *p_server, uint32_t trigger_model)
{
    static int16_t repeat_bind_level_st[GENERIC_LEVEL_SERVER_INSTANCE_COUNT] = {0,};
    int16_t *repeat_bind_level = &repeat_bind_level_st[p_server->server.model_instance_index];

    APP_LOG_INFO(" [%s] enter, repeat value %d, bind value %d", __func__, *repeat_bind_level, p_server->state.present_level);
    if (*repeat_bind_level != p_server->state.present_level)
    {
        if (trigger_model != MODEL_ID_LIGHTS_LN)
        {
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_LN, MODEL_ID_GENS_LVL,
                                  &p_server->state.present_level, sizeof(p_server->state.present_level));
        }

        if (trigger_model != MODEL_ID_LIGHTS_CTLT)
        {
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_CTLT, MODEL_ID_GENS_LVL,
                                  &p_server->state.present_level, sizeof(p_server->state.present_level));
        }

        if (trigger_model != MODEL_ID_GENS_PLVL)
        {
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_GENS_PLVL, MODEL_ID_GENS_LVL,
                                  &p_server->state.present_level, sizeof(p_server->state.present_level));
        }
        if (trigger_model != MODEL_ID_LIGHTS_HSLH)
        {
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_HSLH, MODEL_ID_GENS_LVL,
                                  &p_server->state.present_level, sizeof(p_server->state.present_level));
        }
        if (trigger_model != MODEL_ID_LIGHTS_HSLSAT)
        {
            mesh_model_bind_check(p_server->server.model_instance_index, MODEL_ID_LIGHTS_HSLSAT, MODEL_ID_GENS_LVL,
                                  &p_server->state.present_level, sizeof(p_server->state.present_level));
        }
        *repeat_bind_level = p_server->state.present_level;
    }
}

static bool app_level_bind_cb(void *p_server, uint32_t src_model_id, void *p_data, uint16_t data_len)
{
    app_level_server_t * pl_server = (app_level_server_t *)p_server;
    bool ret = false;

    APP_LOG_INFO("[%s] : src model id 0x%04x,  length = %d, data %d ", __func__, src_model_id, data_len, *(uint16_t *)p_data);

    if (pl_server != NULL)
    {
        switch(src_model_id)
        {
            case MODEL_ID_LIGHTS_LN:
            {
                if (data_len == 2)
                {
                    uint16_t present_ln = *(uint16_t *)p_data;

                    if ( pl_server->state.present_level != present_ln - 32768)
                    {
                        pl_server->state.present_level = present_ln - 32768;
                        pl_server->level_set_cb(pl_server->server.model_instance_index, pl_server->state.present_level);

                        ret = true;
                    }
                }
                break;
            }
            
            case MODEL_ID_GENS_PLVL:
            {
                if (data_len == 2)
                {
                    uint16_t present_power = *(uint16_t *)p_data;

                    if ( pl_server->state.present_level != present_power - 32768)
                    {
                        pl_server->state.present_level = present_power - 32768;
                        pl_server->level_set_cb(pl_server->server.model_instance_index, pl_server->state.present_level);

                        ret = true;
                    }
                }
                break;
            }
            case MODEL_ID_LIGHTS_CTLT:
            //case MODEL_ID_LIGHTS_CTL:
            {
                if (data_len == 2)
                {
                    uint16_t present_level = *(uint16_t *)p_data;
                    if ( pl_server->state.present_level != present_level)
                    {
                        pl_server->state.present_level = present_level;
                        pl_server->level_set_cb(pl_server->server.model_instance_index, pl_server->state.present_level);
                        ret = true;
                    }
                }
                break;
            }
            case MODEL_ID_LIGHTS_HSLH:
            case MODEL_ID_LIGHTS_HSLSAT:
            {
                if (data_len == 2)
                {
                    uint16_t present_SL = *(uint16_t *)p_data;
                    if ( pl_server->state.present_level != present_SL - 32768)
                    {
                        pl_server->state.present_level = present_SL - 32768;
                        pl_server->level_set_cb(pl_server->server.model_instance_index, pl_server->state.present_level);
                        ret = true;
                    }
                }
                break;
            }
            default:
                break;
        }

        if (ret)
        {
            app_level_status_publish(pl_server);
            app_level_bind_check(pl_server, src_model_id);
        }
    }

    return ret;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */
uint16_t app_level_status_publish(app_level_server_t * p_server)
{
    p_server->level_get_cb(p_server->server.model_instance_index, &p_server->state.present_level);
    // if the timer isn't in list, no error occurs. [Nordic codes].
    /*mesh_timer_clear(&p_server->app_timer.timer_id);
    
    p_server->state.target_level = p_server->state.present_level;
    p_server->state.delay_ms = 0;
    p_server->state.transition_time_ms = 0;*/

    generic_level_status_params_t status = {
                .present_level = p_server->state.present_level,
                .target_level = p_server->state.target_level,
                .remaining_time_ms = get_remaining_time_ms(p_server)
            };
    return generic_level_server_status_publish(&p_server->server, &status);
}

uint16_t app_generic_level_server_init(app_level_server_t *p_server, uint8_t element_offset,
                                       app_generic_level_set_cb_t set_cb, app_generic_level_get_cb_t get_cb)
{
    if(( p_server == NULL) || (GENERIC_LEVEL_SERVER_INSTANCE_COUNT <= element_offset))
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

    p_server->level_set_cb = set_cb;
    p_server->level_get_cb = get_cb;

    p_server->state.present_level = 0;
    p_server->state.target_level = 0;
    p_server->state.transition_time_ms = 0;
    p_server->state.delay_ms = 0;

    p_server->last_time_clock_ms = 0;
    p_server->last_time_nb_wrap = 0;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->value_updated = false;
    
    p_server->server.settings.p_callbacks = &level_srv_cbs;
    uint16_t init_status = generic_level_server_init(&p_server->server, element_offset);
    if(init_status == MESH_ERROR_NO_ERROR)
    {
        p_server->app_timer.callback = level_state_timer_cb;
        p_server->app_timer.p_args = p_server;
        p_server->app_timer.timer_id = 0xFFFFFFFF;
        p_server->app_timer.reload = false;
        mesh_model_bind_list_add(MODEL_ID_GENS_LVL, element_offset, (void *)p_server, app_level_bind_cb);
        mesh_scenes_state_store_with_scene(element_offset, app_level_scene_recall_cb, (void *)p_server, (uint8_t *)&p_server->state.present_level, sizeof(p_server->state.present_level));
    }
    return  init_status;
}
