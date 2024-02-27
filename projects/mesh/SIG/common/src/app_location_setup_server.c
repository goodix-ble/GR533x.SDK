/**
 *****************************************************************************************
 *
 * @file app_location_server.c
 *
 * @brief APP Location API Implementation.
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
#include "app_location_setup_server.h"
#include "app_location_server.h"
#include "generic_location_server.h"
#include "app_log.h"
#include "user_app.h"
#include "mesh_bind.h"
#include "common_utils.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void generic_location_state_set_cb(generic_location_setup_server_t  * p_self,
                                                                            const mesh_model_msg_ind_t *p_rx_msg,
                                                                            const void * p_in,
                                                                            void * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const generic_location_server_callbacks_t location_setup_srv_cbs =
{
    .location_cbs.set_global_cb = generic_location_state_set_cb,
    .location_cbs.set_local_cb = generic_location_state_set_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void generic_location_state_set_cb(generic_location_setup_server_t  * p_self,
                                                                            const mesh_model_msg_ind_t *p_rx_msg,
                                                                            const void * p_in,
                                                                            void * p_out)
{
    app_location_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_location_setup_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET", __func__, p_self->model_instance_index);

    switch (p_rx_msg->opcode.company_opcode)
    {
        case GENERIC_LOCATION_GLOBAL_OPCODE_SET:
        case GENERIC_LOCATION_GLOBAL_OPCODE_SET_UNACK:
        {
            generic_location_state_update(p_server->state, (location_global_status_params_t *)p_in, NULL);
            *p_server->global_state = *(location_global_status_params_t *)p_in;
            /* Prepare response */
            if (p_out != NULL)
            {
                *(location_global_status_params_t *)p_out = *(location_global_status_params_t *)p_in;
            }
            break;
        }

        case GENERIC_LOCATION_LOCAL_OPCODE_SET:
        case GENERIC_LOCATION_LOCAL_OPCODE_SET_UNACK:
        {
            generic_location_state_update(p_server->state, NULL, (location_local_status_params_t *)p_in);
            *p_server->local_state = *(location_local_status_params_t *)p_in;
            /* Prepare response */
            if (p_out != NULL)
            {
                *(location_local_status_params_t *)p_out = *(location_local_status_params_t *)p_in;
            }
            break;
        }
        default:
            break;
    }

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of lightness value, process timing */

    p_server->location_set_cb(p_server->server.model_instance_index, p_server->state);
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_generic_location_setup_server_init(app_location_setup_server_t *p_server, uint8_t element_offset, app_generic_location_set_cb_t set_cb)
{
    if(( p_server == NULL) 
        || (GENERIC_LOCATION_SERVER_INSTANCE_COUNT <= element_offset) 
        ||(p_server->server.location_server == NULL)
        || (p_server->state == NULL))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->location_set_cb = set_cb;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->server.settings.p_callbacks = &location_setup_srv_cbs;

    return generic_location_setup_server_init(&p_server->server, element_offset);
}
