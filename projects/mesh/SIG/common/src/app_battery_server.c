/**
 *****************************************************************************************
 *
 * @file app_battery_server.c
 *
 * @brief APP Battery API Implementation.
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
#include "app_battery_server.h"
#include "generic_battery_server.h"
#include "app_log.h"
#include "user_app.h"
#include "mesh_bind.h"


/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void generic_battery_state_get_cb(generic_battery_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_battery_status_params_t * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const generic_battery_server_callbacks_t battery_srv_cbs =
{
    .battery_cbs.get_cb = generic_battery_state_get_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void generic_battery_state_get_cb(generic_battery_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               generic_battery_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_battery_server_t *p_server = PARENT_BY_FIELD_GET(app_battery_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the battery state */
    p_server->battery_get_cb(p_server->server.model_instance_index, &p_server->state);
    *p_out = *(generic_battery_status_params_t *)&(p_server->state);
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_generic_battery_status_publish(app_battery_server_t * p_server)
{
    p_server->battery_get_cb(p_server->server.model_instance_index, &p_server->state);

    generic_battery_status_params_t status = *(generic_battery_status_params_t *)&p_server->state;
    return generic_battery_server_status_publish(&p_server->server, &status);
}



uint16_t app_generic_battery_server_init(app_battery_server_t *p_server, uint8_t element_offset, app_generic_battery_get_cb_t get_cb)
{
    if(( p_server == NULL) || (GENERIC_BATTERY_SERVER_INSTANCE_COUNT <= element_offset))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->battery_get_cb = get_cb;

    p_server->state.battery_level = 0xFF;
    p_server->state.time_to_charge = GENERIC_BATTERY_TIME_CHARGE_UNKNOW;
    p_server->state.time_to_discharge= GENERIC_BATTERY_TIME_DISCHARGE_UNKNOW;
    p_server->state.flags_presence = APP_BATTERY_PRESENT_UNKNOW;
    p_server->state.flags_indicator = APP_BATTERY_CHARGE_PRESENT_UNKNOW;
    p_server->state.flags_charging= APP_BATTERY_CHARGEING_UNKNOW;
    p_server->state.flags_serviceability= APP_BATTERY_SERVICEABILITY_UNKNOW;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->server.settings.p_callbacks = &battery_srv_cbs;
        
    return generic_battery_server_init(&p_server->server, element_offset);
}
