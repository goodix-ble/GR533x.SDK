/**
 *****************************************************************************************
 *
 * @file app_light_ctl_setup_server.c
 *
 * @brief APP Light CTL Setup API Implementation.
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
#include "app_light_ctl_setup_server.h"
#include "light_ctl_setup_server.h"
#include "app_log.h"
#include "user_app.h"
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

static void light_ctl_default_state_set_cb(light_ctl_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                                                            const void * p_in, void * p_out);

static void light_ctl_range_state_set_cb(light_ctl_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                                                            const void * p_in, void * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const light_ctl_server_callbacks_t light_ctl_setup_srv_cbs =
{
    .light_ctl_dft_cbs.set_cb = light_ctl_default_state_set_cb,
    .light_ctl_temp_range_cbs.set_cb = light_ctl_range_state_set_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void light_ctl_default_state_set_cb(light_ctl_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                                                            const void * p_in, void * p_out)
{
    app_light_ctl_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_light_ctl_setup_server_t, server, p_self);
    light_ctl_dft_set_params_t *p_in_set = (light_ctl_dft_set_params_t *)p_in;
    light_ctl_dft_status_params_t * p_out_set = (light_ctl_dft_status_params_t *)p_out;

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: %04X", __func__, p_self->model_instance_index, p_in_set->ln);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of ctl value, process timing */
    FORMAT_VALUE_RANGE(p_in_set->temp, LIGHT_CTL_TEMPERATURE_MAX, LIGHT_CTL_TEMPERATURE_MIN);
    p_server->state->dft_state.default_ln= p_in_set->ln;
    p_server->state->dft_state.default_temp = p_in_set->temp;
    p_server->state->dft_state.default_dlt_uv = p_in_set->dlt_uv;

    store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_Lightness_State, 0, p_server->state->dft_state.default_ln == 0 ? p_server->state->target_state.target_ctl_ln: p_server->state->dft_state.default_ln, p_server->state->target_state.target_ctl_ln);
    store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_CTL_Temp_State, p_server->state->dft_state.default_temp, p_server->state->dft_state.default_temp, p_server->state->target_state.target_ctl_temp);
    store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_CTL_DLT_State, p_server->state->dft_state.default_dlt_uv, p_server->state->dft_state.default_dlt_uv, p_server->state->target_state.target_ctl_dlt_uv);

    p_server->light_ctl_setup_set_cb(p_server->server.model_instance_index, NULL, &p_server->state->dft_state, NULL);

    /* Prepare response */
    if (p_out_set != NULL)
    {
        p_out_set->ln = p_server->state->dft_state.default_ln;
        p_out_set->temp = p_server->state->dft_state.default_temp;
        p_out_set->dlt_uv = p_server->state->dft_state.default_dlt_uv;
    }
}

static void light_ctl_range_state_set_cb(light_ctl_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                                                            const void * p_in, void * p_out)
{
    app_light_ctl_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_light_ctl_setup_server_t, server, p_self);
    light_ctl_set_range_params_t *p_in_set = (light_ctl_set_range_params_t *)p_in;
    light_ctl_range_status_params_t * p_out_set = (light_ctl_range_status_params_t *)p_out;
    uint8_t status_code;

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET range: %04X ~ %04X", __func__, p_self->model_instance_index, p_in_set->range_min, p_in_set->range_max);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of ctl value, process timing */
    if ( LIGHT_CTL_TEMPERATURE_MIN > p_in_set->range_min)
    {
        status_code = STATUS_CODES_ERR_MIN;
    }
    else if ((LIGHT_CTL_TEMPERATURE_MAX < p_in_set->range_max) || (p_in_set->range_min > p_in_set->range_max))
    {
        status_code = STATUS_CODES_ERR_MAX;
    }
    else
    {
        status_code = STATUS_CODES_SUCCESS;
        p_server->state->temp_range.range_min= p_in_set->range_min;
        p_server->state->temp_range.range_max = p_in_set->range_max;

        //FORMAT_VALUE_RANGE(p_server->state->present_state.present_ctl_temp, p_server->state->temp_range.range_max, p_server->state->temp_range.range_min);
        //FORMAT_VALUE_RANGE(p_server->state->target_state.target_ctl_temp, p_server->state->temp_range.range_max, p_server->state->temp_range.range_min);

        store_status_before_power_down(p_server->server.model_instance_index, OnPowerUp_Bind_CTL_Temp_State, p_server->state->dft_state.default_temp, p_server->state->dft_state.default_temp, p_server->state->target_state.target_ctl_temp);
        p_server->light_ctl_setup_set_cb(p_server->server.model_instance_index, /*&(p_server->state->present_state)*/ NULL, NULL, &(p_server->state->temp_range));
    }

    /* Prepare response */
    if (p_out_set != NULL)
    {
        p_out_set->status_code = status_code;
        p_out_set->range_max = p_server->state->temp_range.range_max;
        p_out_set->range_min = p_server->state->temp_range.range_min;
    }

}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_light_ctl_setup_server_init(app_light_ctl_setup_server_t *p_server, uint8_t element_offset, app_light_ctl_set_cb_t set_cb)
{
    if(( p_server == NULL)
        || (LIGHT_CTL_INSTANCE_COUNT <= element_offset)
        ||(p_server->server.ctl_server == NULL)
        || (p_server->state == NULL))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->light_ctl_setup_set_cb = set_cb;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->server.settings.p_callbacks = &light_ctl_setup_srv_cbs;

    return light_ctl_setup_server_init(&p_server->server, element_offset);
}

