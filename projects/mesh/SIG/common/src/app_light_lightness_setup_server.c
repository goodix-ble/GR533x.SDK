/**
 *****************************************************************************************
 *
 * @file app_light_lightness_setup_server.c
 *
 * @brief APP Light Lightness Setup API Implementation.
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
#include "app_light_lightness_setup_server.h"
#include "light_lightness_setup_server.h"
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

static void light_ln_default_state_set_cb(light_ln_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_ln_setup_params_t * p_in, const model_transition_t * p_in_transition,
                                               light_ln_status_params_u * p_out);

static void light_ln_range_state_set_cb(light_ln_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_ln_setup_params_t * p_in, const model_transition_t * p_in_transition,
                                               light_ln_status_params_u * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const light_ln_server_callbacks_t light_ln_setup_srv_cbs =
{
    .light_ln_dft_cbs.set_cb = light_ln_default_state_set_cb,

    .light_ln_range_cbs.set_cb = light_ln_range_state_set_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void light_ln_default_state_set_cb(light_ln_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_ln_setup_params_t * p_in, const model_transition_t * p_in_transition,
                                               light_ln_status_params_u * p_out)
{
    app_light_lightness_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lightness_setup_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: %04X", __func__, p_self->model_instance_index, p_in->ln);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of lightness value, process timing */
    p_server->state->state.default_ln= p_in->ln;

    p_server->light_ln_setup_set_cb(p_server->server.model_instance_index, &(p_server->state->state));

    store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_Lightness_State, 0, p_server->state->state.default_ln == 0 ? p_server->state->state.last_ln : p_server->state->state.default_ln, p_server->state->state.target_ln);
    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->ln_dft.ln= p_server->state->state.default_ln;
    }
}

static void light_ln_range_state_set_cb(light_ln_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_ln_setup_params_t * p_in, const model_transition_t * p_in_transition,
                                               light_ln_status_params_u * p_out)
{
    app_light_lightness_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lightness_setup_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET range: %04X ~ %04X", __func__, p_self->model_instance_index, p_in->u.ln_min, p_in->u.ln_max);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of lightness value, process timing */
    if ( 0 == p_in->u.ln_min)
    {
        p_server->state->state.status_code = STATUS_CODES_ERR_MIN;
    }
    else if (p_in->u.ln_min > p_in->u.ln_max)
    {
        p_server->state->state.status_code = STATUS_CODES_ERR_MAX;//STATUS_CODES_ERR_MAX
    }
    else
    {
        p_server->state->state.status_code = STATUS_CODES_SUCCESS;
        p_server->state->state.min_ln = p_in->u.ln_min;
        p_server->state->state.max_ln = p_in->u.ln_max;
    }

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->ln_range.status_code= p_server->state->state.status_code;
        p_out->ln_range.max_ln= p_server->state->state.max_ln;
        p_out->ln_range.min_ln= p_server->state->state.min_ln;
        //p_out->ln_range.max_ln= p_in->u.ln_max;
        //p_out->ln_range.min_ln= p_in->u.ln_min;
    }

    p_server->state->state.status_code = STATUS_CODES_SUCCESS;
    p_server->light_ln_setup_set_cb(p_server->server.model_instance_index, &(p_server->state->state));
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_light_ln_setup_server_init(app_light_lightness_setup_server_t *p_server, uint8_t element_offset, app_light_ln_set_cb_t set_cb)
{
    if(( p_server == NULL)
        || (LIGHT_LIGHTNESS_INSTANCE_COUNT <= element_offset)
        ||(p_server->server.ln_server == NULL)
        || (p_server->state == NULL))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->light_ln_setup_set_cb = set_cb;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->server.settings.p_callbacks = &light_ln_setup_srv_cbs;

    return light_ln_setup_server_init(&p_server->server, element_offset);
}

