/**
 ****************************************************************************************
 *
 * @file app_client_property_server.c
 *
 * @brief APP Client Property Server API Implementation.
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
#include "app_client_property_server.h"
#include "generic_client_property_server.h"
#include "model_common.h"
#include "user_app.h"
#include "mesh_bind.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
                                                  
void generic_client_properties_state_get_cb(const generic_client_property_server_t * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const generic_properties_client_get_params_t * p_in,
                                                    generic_properties_uamc_status_params_t * p_out);
/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
const generic_client_property_server_callbacks_t client_property_srv_cbs =
{
    .property_cbs.client_properties_get_cb = generic_client_properties_state_get_cb,
};


/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */


/***** Generic client property model interface callbacks *****/

void generic_client_properties_state_get_cb(const generic_client_property_server_t * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const generic_properties_client_get_params_t * p_in,
                                                    generic_properties_uamc_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    APP_LOG_INFO("SERVER[%d] -- msg: Client Properties GET.", p_self->model_instance_index);

    app_client_property_server_t *p_server = PARENT_BY_FIELD_GET(app_client_property_server_t, server, p_self);
    
    //p_server->client_properties_state.smallest_property_id = p_in->property_id;
    /* Requirement: Provide the current value of the client properties state */
    p_server->client_properties_get_cb(p_server->server.model_instance_index, &p_server->client_properties_state);
    for(int i = 0; i < p_server->client_properties_state.id_number; i++)
    {
        if(p_server->client_properties_state.property_id[i] >= p_in->property_id)
        {
            p_server->client_properties_state.smallest_property_id = p_server->client_properties_state.property_id[i];
            p_out->id_number = p_server->client_properties_state.id_number - i;
            p_out->property_id = p_server->client_properties_state.property_id + i;
            break;
        }
    }
    if (0 == p_out->id_number)
    {
        p_out->property_id = NULL;
    }
}
    

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */
uint16_t app_generic_client_property_status_publish(app_client_property_server_t * p_server, uint16_t property_id)
{
    generic_properties_uamc_status_params_t p_properties_status;
    
    p_server->client_properties_get_cb(p_server->server.model_instance_index, &p_server->client_properties_state);
    
    for(int i = 0; i < p_server->client_properties_state.id_number; i++)
    {
        if(p_server->client_properties_state.property_id[i] >= property_id)
        {
            p_server->client_properties_state.smallest_property_id = p_server->client_properties_state.property_id[i];
            p_properties_status.id_number = p_server->client_properties_state.id_number - i;
            p_properties_status.property_id = p_server->client_properties_state.property_id + i;
            break;
        }
    }

    if (p_properties_status.id_number == 0)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    return generic_client_properties_server_status_publish(&p_server->server, &p_properties_status);
}

uint16_t app_generic_client_property_server_init(app_client_property_server_t *p_server, uint8_t element_offset,
                                               app_generic_client_properties_get_cb_t client_properties_get_cb)
{
    if(( p_server != NULL) && (GENERIC_CLIENT_PROPERTY_SERVER_INSTANCE_COUNT <= element_offset))
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


    p_server->client_properties_get_cb = client_properties_get_cb;
    
    p_server->client_properties_state.id_number = 0;
    p_server->client_properties_state.property_id = NULL;

    p_server->value_updated = false;
    
    p_server->server.settings.p_callbacks = &client_property_srv_cbs;
    APP_LOG_INFO("init client property server ");            
    uint16_t init_status = generic_client_property_server_init(&p_server->server, element_offset);
    return  init_status;
}
