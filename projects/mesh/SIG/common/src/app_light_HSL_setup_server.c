/**
 *****************************************************************************************
 *
 * @file app_light_HSL_setup_server.c
 *
 * @brief APP Light HSL Setup API Implementation.
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
#include "app_light_HSL_setup_server.h"
#include "light_HSL_setup_server.h"
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

static void light_HSL_default_state_set_cb(light_HSL_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_HSL_setup_params_t * p_in,
                                               light_HSL_status_params_u * p_out);

static void light_HSL_range_state_set_cb(light_HSL_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_HSL_setup_params_t * p_in,
                                               light_HSL_status_params_u * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const light_HSL_server_callbacks_t light_HSL_setup_srv_cbs =
{
    .light_HSL_dft_cbs.set_cb = light_HSL_default_state_set_cb,

    .light_HSL_range_cbs.set_cb = light_HSL_range_state_set_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void light_HSL_default_state_set_cb(light_HSL_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_HSL_setup_params_t * p_in, light_HSL_status_params_u * p_out)
{
    app_light_HSL_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_light_HSL_setup_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- SET HSL DFT  Hue: %d, Saturation:%d, Lightness:%d. ",
                  __func__, p_self->model_instance_index, p_in->dft.hue, p_in->dft.stt, p_in->dft.ln);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of HSL value, process timing */
    p_server->state->dft_state.dft_hue= p_in->dft.hue;
    p_server->state->dft_state.dft_stt= p_in->dft.stt;
    p_server->state->dft_state.dft_ln= p_in->dft.ln;

    p_server->light_HSL_setup_set_cb(p_server->server.model_instance_index, NULL, &(p_server->state->dft_state), NULL);

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->HSL_dft.hue = p_server->state->dft_state.dft_hue;
        p_out->HSL_dft.stt = p_server->state->dft_state.dft_stt;
        p_out->HSL_dft.ln = p_server->state->dft_state.dft_ln;
    }

    store_status_before_power_down(p_server->server.HSL_server->model_instance_index, OnPowerUp_Bind_Lightness_State, 0, p_server->state->dft_state.dft_ln== 0 ? p_server->state->target_state.target_ln: p_server->state->dft_state.dft_ln, p_server->state->target_state.target_ln);
    store_status_before_power_down(p_server->server.HSL_server->model_instance_index, OnPowerUp_Bind_HSL_Hue_State, p_server->state->dft_state.dft_hue, p_server->state->dft_state.dft_hue, p_server->state->target_state.target_hue);
    store_status_before_power_down(p_server->server.HSL_server->model_instance_index, OnPowerUp_Bind_HSL_Saturation_State, p_server->state->dft_state.dft_stt, p_server->state->dft_state.dft_stt, p_server->state->target_state.target_stt);
}

static void light_HSL_range_state_set_cb(light_HSL_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const light_HSL_setup_params_t * p_in, light_HSL_status_params_u * p_out)
{
    app_light_HSL_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_light_HSL_setup_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET HSL RANGE  Hue_Min: %d, Hue_Max: %d, Saturation_Min: %d, Saturation_Max: %d.", 
                      __func__, p_self->model_instance_index, p_in->range.min_hue, p_in->range.max_hue, p_in->range.min_stt, p_in->range.max_stt);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of HSL value, process timing */

    if ((p_in->range.min_hue > p_in->range.max_hue) || (p_in->range.min_stt > p_in->range.max_stt))
    {
        p_out->HSL_range.status_code = STATUS_CODES_ERR_MAX;
    }
    else
    {
        p_out->HSL_range.status_code = STATUS_CODES_SUCCESS;
        p_server->state->range_state.min_hue = p_in->range.min_hue;
        p_server->state->range_state.max_hue = p_in->range.max_hue;
        p_server->state->range_state.min_stt = p_in->range.min_stt;
        p_server->state->range_state.max_stt = p_in->range.max_stt;
    }
    p_server->light_HSL_setup_set_cb(p_server->server.model_instance_index, NULL, NULL,&(p_server->state->range_state));

    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->HSL_range.max_hue= p_server->state->range_state.max_hue;
        p_out->HSL_range.min_hue= p_server->state->range_state.min_hue;
        p_out->HSL_range.max_stt= p_server->state->range_state.max_stt;
        p_out->HSL_range.min_stt= p_server->state->range_state.min_stt;
    }
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_light_HSL_setup_server_init(app_light_HSL_setup_server_t *p_server, uint8_t element_offset, app_light_HSL_set_cb_t set_cb)
{
    if(( p_server == NULL)
        ||(LIGHT_HSL_INSTANCE_COUNT <= element_offset)
        ||(p_server->server.HSL_server == NULL)
        ||(p_server->state == NULL))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->light_HSL_setup_set_cb = set_cb;

    p_server->client_address = MESH_INVALID_ADDR;
    p_server->server.settings.p_callbacks = &light_HSL_setup_srv_cbs;

    return light_HSL_setup_server_init(&p_server->server, element_offset);
}

