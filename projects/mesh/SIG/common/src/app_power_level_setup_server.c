/**
 *****************************************************************************************
 *
 * @file app_power_level_setup_server.c
 *
 * @brief APP Power Level Setup API Implementation.
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
#include "app_power_level_setup_server.h"
#include "generic_power_level_setup_server.h"
#include "app_log.h"
#include "user_app.h"
#include "generic_power_onoff_behavior.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void generic_power_level_default_state_set_cb(generic_power_level_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const generic_power_level_setup_params_t * p_in, const model_transition_t * p_in_transition,
                                               generic_power_level_status_params_u * p_out);

static void generic_power_level_range_state_set_cb(generic_power_level_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const generic_power_level_setup_params_t * p_in, const model_transition_t * p_in_transition,
                                               generic_power_level_status_params_u * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const generic_power_level_server_callbacks_t generic_power_level_setup_srv_cbs =
{
    .generic_power_level_dft_cbs.set_cb = generic_power_level_default_state_set_cb,

    .generic_power_level_range_cbs.set_cb = generic_power_level_range_state_set_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void generic_power_level_default_state_set_cb(generic_power_level_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const generic_power_level_setup_params_t * p_in, const model_transition_t * p_in_transition,
                                               generic_power_level_status_params_u * p_out)
{
    app_generic_power_level_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_generic_power_level_setup_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: %04X", __func__, p_self->model_instance_index, p_in->power);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of Power Default value, process timing */
    p_server->app_state->state.default_power= p_in->power;

    p_server->generic_power_level_setup_set_cb(p_server->server.model_instance_index, &(p_server->app_state->state));
    
    store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_Power_Level_State, 0, 
                                   p_server->app_state->state.default_power == 0 ? p_server->app_state->state.last_power : p_server->app_state->state.default_power, 
                                   p_server->app_state->state.target_power);
    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->power_dft.power= p_server->app_state->state.default_power;
    }
}

static void generic_power_level_range_state_set_cb(generic_power_level_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const generic_power_level_setup_params_t * p_in, const model_transition_t * p_in_transition,
                                               generic_power_level_status_params_u * p_out)
{
    app_generic_power_level_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_generic_power_level_setup_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET range: %04X ~ %04X", __func__, p_self->model_instance_index, p_in->u.power_min, p_in->u.power_max);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;
    if ((0 == p_in->u.power_min) || (0 == p_in->u.power_max) || (p_in->u.power_min > p_in->u.power_max))
    {
        APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: the set Power Range value is invalid.  ", __func__, p_self->model_instance_index);
    }

    /* Update internal representation of Power Range value, process timing */
    if ( 0 == p_in->u.power_min)
    {
        p_server->app_state->state.status_code = STATUS_CODES_ERR_MIN;
    }
    else if (p_in->u.power_min > p_in->u.power_max)
    {
        p_server->app_state->state.status_code = STATUS_CODES_ERR_MAX;
    }
    else
    {
        p_server->app_state->state.status_code = STATUS_CODES_SUCCESS;
        p_server->app_state->state.min_power = p_in->u.power_min;
        p_server->app_state->state.max_power = p_in->u.power_max;
        p_server->generic_power_level_setup_set_cb(p_server->server.model_instance_index, &(p_server->app_state->state));
    }

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->power_range.status_code= p_server->app_state->state.status_code;
        p_out->power_range.max_power= p_server->app_state->state.max_power;
        p_out->power_range.min_power= p_server->app_state->state.min_power;
    }
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_generic_power_level_setup_server_init(app_generic_power_level_setup_server_t *p_server, uint8_t element_offset, app_generic_power_level_set_cb_t set_cb)
{
    if(( p_server == NULL)
        || (p_server->app_state == NULL)
        || (GENERIC_POWER_LEVEL_SERVER_INSTANCE_COUNT <= element_offset)
        || (p_server->server.lvl_server == NULL))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->generic_power_level_setup_set_cb = set_cb;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->server.settings.p_callbacks = &generic_power_level_setup_srv_cbs;

    return generic_power_level_setup_server_init(&p_server->server, element_offset);
}

