/**
 *****************************************************************************************
 *
 * @file app_light_xyl_setup_server.c
 *
 * @brief APP Light xyL Setup API Implementation.
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
#include "app_light_xyl_setup_server.h"
#include "light_xyl_setup_server.h"
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

static void light_xyl_default_state_set_cb(light_xyl_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                                                            const void * p_in, void * p_out);

static void light_xyl_range_state_set_cb(light_xyl_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                                                            const void * p_in, void * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const light_xyl_server_callbacks_t light_xyl_setup_srv_cbs =
{
    .light_xyl_dft_cbs.set_cb = light_xyl_default_state_set_cb,
    .light_xyl_range_cbs.set_cb = light_xyl_range_state_set_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void light_xyl_default_state_set_cb(light_xyl_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                                                            const void * p_in, void * p_out)
{
    app_light_xyl_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_light_xyl_setup_server_t, server, p_self);
    light_xyl_dft_set_params_t *p_in_set = (light_xyl_dft_set_params_t *)p_in;
    light_xyl_dft_status_params_t * p_out_set = (light_xyl_dft_status_params_t *)p_out;

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: %04X", __func__, p_self->model_instance_index, p_in_set->ln);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of xyL value, process timing */
    p_server->state->dft_state.default_ln= p_in_set->ln;
    p_server->state->dft_state.default_x= p_in_set->x;
    p_server->state->dft_state.default_y= p_in_set->y;

    store_status_before_power_down(p_server->server.model_instance_index,
                                                            OnPowerUp_Bind_Lightness_State,
                                                            0,
                                                            p_server->state->dft_state.default_ln== 0 ? p_server->state->target_state.target_xyl_ln: p_server->state->dft_state.default_ln,
                                                            p_server->state->target_state.target_xyl_ln);
    store_status_before_power_down(p_server->server.model_instance_index,
                                                            OnPowerUp_Bind_xyL_X_State,
                                                            p_server->state->dft_state.default_x,
                                                            p_server->state->dft_state.default_x,
                                                            p_server->state->target_state.target_xyl_x);
    store_status_before_power_down(p_server->server.model_instance_index,
                                                            OnPowerUp_Bind_xyL_Y_State,
                                                            p_server->state->dft_state.default_y,
                                                            p_server->state->dft_state.default_y,
                                                            p_server->state->target_state.target_xyl_y);

    p_server->light_xyl_setup_set_cb(p_server->server.model_instance_index, NULL, &p_server->state->dft_state, NULL);

    /* Prepare response */
    if (p_out_set != NULL)
    {
        p_out_set->ln = p_server->state->dft_state.default_ln;
        p_out_set->x = p_server->state->dft_state.default_x;
        p_out_set->y = p_server->state->dft_state.default_y;
    }
}

static void light_xyl_range_state_set_cb(light_xyl_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                                                            const void * p_in, void * p_out)
{
    app_light_xyl_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_light_xyl_setup_server_t, server, p_self);
    light_xyl_set_range_params_t *p_in_set = (light_xyl_set_range_params_t *)p_in;
    light_xyl_range_status_params_t * p_out_set = (light_xyl_range_status_params_t *)p_out;
    uint8_t status_code;

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET x range: %04X ~ %04X, y range: %04X ~ %04X", 
        __func__, p_self->model_instance_index, p_in_set->range_min_x, p_in_set->range_max_x, p_in_set->range_min_y, p_in_set->range_max_y);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of xyL value, process timing */
    if ((p_in_set->range_min_x > p_in_set->range_max_x) ||(p_in_set->range_min_y > p_in_set->range_max_y))
    {
        status_code = STATUS_CODES_ERR_MAX;
    }
    else
    {
        status_code = STATUS_CODES_SUCCESS;
        p_server->state->xyl_range.range_min_x= p_in_set->range_min_x;
        p_server->state->xyl_range.range_max_x= p_in_set->range_max_x;
        p_server->state->xyl_range.range_min_y= p_in_set->range_min_y;
        p_server->state->xyl_range.range_max_y= p_in_set->range_max_y;

        //FORMAT_VALUE_RANGE(p_server->state->present_state.present_xyl_x, p_server->state->xyl_range.range_max_x, p_server->state->xyl_range.range_min_x);
        //FORMAT_VALUE_RANGE(p_server->state->target_state.target_xyl_x, p_server->state->xyl_range.range_max_x, p_server->state->xyl_range.range_min_x);
        //FORMAT_VALUE_RANGE(p_server->state->present_state.present_xyl_y, p_server->state->xyl_range.range_max_y, p_server->state->xyl_range.range_min_y);
        //FORMAT_VALUE_RANGE(p_server->state->target_state.target_xyl_y, p_server->state->xyl_range.range_max_y, p_server->state->xyl_range.range_min_y);

        store_status_before_power_down(p_server->server.model_instance_index,
                                                                OnPowerUp_Bind_Lightness_State,
                                                                0,
                                                                p_server->state->dft_state.default_ln== 0 ? p_server->state->target_state.target_xyl_ln: p_server->state->dft_state.default_ln,
                                                                p_server->state->target_state.target_xyl_ln);
        store_status_before_power_down(p_server->server.model_instance_index,
                                                                OnPowerUp_Bind_xyL_X_State,
                                                                p_server->state->dft_state.default_x,
                                                                p_server->state->dft_state.default_x,
                                                                p_server->state->target_state.target_xyl_x);
        store_status_before_power_down(p_server->server.model_instance_index,
                                                                OnPowerUp_Bind_xyL_Y_State,
                                                                p_server->state->dft_state.default_y,
                                                                p_server->state->dft_state.default_y,
                                                                p_server->state->target_state.target_xyl_y);

        p_server->light_xyl_setup_set_cb(p_server->server.model_instance_index, /*&(p_server->state->present_state)*/ NULL, NULL, &(p_server->state->xyl_range));
    }


    /* Prepare response */
    if (p_out_set != NULL)
    {
        p_out_set->status_code = status_code;
        p_out_set->range_max_x = p_server->state->xyl_range.range_max_x;
        p_out_set->range_min_x = p_server->state->xyl_range.range_min_x;
        p_out_set->range_max_y = p_server->state->xyl_range.range_max_y;
        p_out_set->range_min_y = p_server->state->xyl_range.range_min_y;
    }
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_light_xyl_setup_server_init(app_light_xyl_setup_server_t *p_server, uint8_t element_offset, app_light_xyl_set_cb_t set_cb)
{
    if(( p_server == NULL)
        || (LIGHT_XYL_INSTANCE_COUNT <= element_offset)
        ||(p_server->server.xyl_server == NULL)
        || (p_server->state == NULL))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->light_xyl_setup_set_cb = set_cb;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->server.settings.p_callbacks = &light_xyl_setup_srv_cbs;

    return light_xyl_setup_server_init(&p_server->server, element_offset);
}

