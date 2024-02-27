/**
 *****************************************************************************************
 *
 * @file app_default_transition_time_server.c
 *
 * @brief APP Generic Default Transition Time API Implementation.
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
#include "app_dtt_server.h"
#include "app_log.h"
#include "user_app.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void generic_default_transition_time_state_set_cb(generic_default_transition_time_server_t *p_self,
                                       const mesh_model_msg_ind_t *p_rx_msg,
                                       const generic_default_transition_time_set_params_t * p_in,
                                       generic_default_transition_time_status_params_t * p_out);

static void generic_default_transition_time_state_get_cb(generic_default_transition_time_server_t *p_self,
                                       const mesh_model_msg_ind_t * p_rx_msg,
                                       generic_default_transition_time_status_params_t * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
const generic_default_transition_time_server_callbacks_t default_transition_time_srv_cbs =
{
    .default_transition_time_cbs.set_cb = generic_default_transition_time_state_set_cb,
    .default_transition_time_cbs.get_cb = generic_default_transition_time_state_get_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static void default_transition_time_state_value_update(app_default_transition_time_server_t * p_server)
{
    generic_default_transition_time_status_params_t status_params;

    APP_LOG_INFO("[%s] enter.", __func__);
    
    p_server->state.present_default_transition_time = p_server->state.present_default_transition_time;

    status_params.present_default_transition_time= p_server->state.present_default_transition_time;
    generic_default_transition_time_server_status_publish(&p_server->server, &status_params);

    if (!p_server->value_updated)
    {
        p_server->default_transition_time_set_cb(p_server->server.model_instance_index, p_server->state.present_default_transition_time);
        p_server->value_updated = true;
    }

}

static void generic_default_transition_time_state_get_cb(generic_default_transition_time_server_t *p_self,
                                       const mesh_model_msg_ind_t * p_rx_msg,
                                       generic_default_transition_time_status_params_t * p_out)
{
    APP_LOG_INFO("SERVER[%d] -- msg: GET Default Transition Time", p_self->model_instance_index);

    app_default_transition_time_server_t *p_server = PARENT_BY_FIELD_GET(app_default_transition_time_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the dtt state */
    p_server->default_transition_time_get_cb(p_server->server.model_instance_index, &p_server->state.present_default_transition_time);
    p_out->present_default_transition_time = p_server->state.present_default_transition_time;
}

static void generic_default_transition_time_state_set_cb(generic_default_transition_time_server_t *p_self,
                                       const mesh_model_msg_ind_t *p_rx_msg,
                                       const generic_default_transition_time_set_params_t * p_in,
                                       generic_default_transition_time_status_params_t * p_out)
{
    APP_LOG_INFO("SERVER[%d] -- msg: SET Default Transition Time: %d", p_self->model_instance_index, p_in->default_transition_time);

    app_default_transition_time_server_t *p_server = PARENT_BY_FIELD_GET(app_default_transition_time_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of dtt value, process timing */
    p_server->value_updated = false;
    p_server->state.present_default_transition_time = p_in->default_transition_time;

    default_transition_time_state_value_update(p_server);
    /* Prepare response */
    if (p_out != NULL)
    {
        p_out->present_default_transition_time = p_server->state.present_default_transition_time;
    }
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */
uint16_t app_default_transition_time_status_publish(app_default_transition_time_server_t * p_server)
{
    p_server->default_transition_time_get_cb(p_server->server.model_instance_index, &p_server->state.present_default_transition_time);

    p_server->state.present_default_transition_time= p_server->state.present_default_transition_time;

    generic_default_transition_time_status_params_t status =
    {
        .present_default_transition_time = p_server->state.present_default_transition_time,
    };
    return generic_default_transition_time_server_status_publish(&p_server->server, &status);
}

uint16_t app_generic_default_transition_time_server_init(app_default_transition_time_server_t *p_server, uint8_t element_offset, app_default_transition_time_set_cb_t set_cb, app_default_transition_time_get_cb_t get_cb)
{
    if ((p_server == NULL) || (GENERIC_DTT_SERVER_INSTANCE_COUNT <= element_offset))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->default_transition_time_set_cb = set_cb;
    p_server->default_transition_time_get_cb = get_cb;
    
    p_server->state.present_default_transition_time = 0;
            
    p_server->client_address = MESH_INVALID_ADDR;
    
    p_server->value_updated = false;

    p_server->server.settings.p_callbacks = &default_transition_time_srv_cbs;

    model_register_dtt_ptr(element_offset, &p_server->state.present_default_transition_time);

    return generic_default_transition_time_server_init(&p_server->server, element_offset);
}
