/**
 *****************************************************************************************
 *
 * @file app_power_onoff_server.c
 *
 * @brief APP Power OnOff API Implementation.
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
#include "app_power_onoff_server.h"
#include "app_onoff_server.h"
#include "generic_power_onoff_server.h"
#include "app_log.h"
#include "user_app.h"


/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void generic_power_onoff_state_get_cb(generic_power_onoff_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_power_onoff_status_params_t * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
const generic_power_onoff_server_callbacks_t power_onoff_srv_cbs =
{
    .power_onoff_cbs.get_cb = generic_power_onoff_state_get_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */


static void generic_power_onoff_state_get_cb(generic_power_onoff_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_power_onoff_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_power_onoff_server_t *p_server = PARENT_BY_FIELD_GET(app_power_onoff_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the Power OnOff state */
    p_server->power_onoff_get_cb(p_server->server.model_instance_index, &p_server->state.on_power_up);
    p_out->on_power_up = p_server->state.on_power_up;
}


/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_generic_power_onoff_status_publish(app_power_onoff_server_t * p_server)
{
    p_server->power_onoff_get_cb(p_server->server.model_instance_index, &p_server->state.on_power_up);

    generic_power_onoff_status_params_t status =
    {
        .on_power_up = p_server->state.on_power_up,
    };
    return generic_power_onoff_server_status_publish(&p_server->server, &status);
}


uint16_t app_generic_power_onoff_server_init(app_power_onoff_server_t *p_server,
                                                   uint8_t element_offset, 
                                                   app_generic_power_onoff_get_cb_t get_cb)
{
    if(( p_server == NULL) 
        ||(GENERIC_POWER_ONOFF_SERVER_INSTANCE_COUNT <= element_offset))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->power_onoff_get_cb = get_cb;
    p_server->state.on_power_up = 0x01;/*Default*/;
    p_server->client_address = MESH_INVALID_ADDR;
    p_server->value_updated = false;
    p_server->server.settings.p_callbacks = &power_onoff_srv_cbs;

    app_generic_onoff_store_power_cb_register(store_status_before_power_down);

    return generic_power_onoff_server_init(&p_server->server, element_offset);
}
