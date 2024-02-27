/**
 *****************************************************************************************
 *
 * @file scheduler_setup_server.c
 *
 * @brief mesh scheduler setup Server API Implementation.
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
#include "app_log.h"
#include "scheduler_message.h"
#include "scheduler_server.h"
#include "scheduler_setup_server.h"
#include "common_utils.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_scheduler_action_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void mesh_scheduler_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t mesh_scheduler_setup_server_opcode_list[] =
{
    TSCNS_SCHEDULER_OPCODE_ACTION_SET,
    TSCNS_SCHEDULER_OPCODE_ACTION_SET_UNACKNOWLEDGED,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {TSCNS_SCHEDULER_OPCODE_ACTION_SET, handle_scheduler_action_set_cb},
    {TSCNS_SCHEDULER_OPCODE_ACTION_SET_UNACKNOWLEDGED, handle_scheduler_action_set_cb},
};

static const mesh_model_cb_t mesh_scheduler_setup_server_msg_cb = {
    .cb_rx             = mesh_scheduler_setup_server_rx_cb,
    .cb_sent           = NULL,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t mesh_scheduler_setup_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_TSCNS_SCHS),
    .element_offset = 0,
    .publish = false,
    .p_opcodes = (uint16_t *)mesh_scheduler_setup_server_opcode_list,
    .num_opcodes = sizeof(mesh_scheduler_setup_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &mesh_scheduler_setup_server_msg_cb,
    .p_args = NULL,
};

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */


/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static void handle_scheduler_action_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_scheduler_setup_server_t  * p_server = (mesh_scheduler_setup_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);

    mesh_scheduler_action_set_params_t in_data = {0};    
    mesh_scheduler_action_status_params_t out_data = {0, MESH_SCHEDULER_INVALID_YEAR, };
    mesh_scheduler_action_set_msg_pkt_t * p_msg_params_packed = (mesh_scheduler_action_set_msg_pkt_t *) p_rx_msg->msg;

    if (p_rx_msg->msg_len == TSCNS_SCHEDULER_ACTION_SET_MINLEN)
    {
        scheduler_unpack_action_status(&in_data, p_msg_params_packed);

        p_server->settings.p_callbacks->scheduler_cbs.action_set_cb(p_server,
                                                                     p_rx_msg,
                                                                     &in_data,
                                                                     (p_rx_msg->opcode.company_opcode == TSCNS_SCHEDULER_OPCODE_ACTION_SET) ? &out_data : NULL);

        if ((p_rx_msg->opcode.company_opcode == TSCNS_SCHEDULER_OPCODE_ACTION_SET) && (out_data.year != MESH_SCHEDULER_INVALID_YEAR))
        {
            (void) scheduler_action_status_send(p_server->scheduler_server, p_rx_msg, &out_data);
        }
    }

}

static void mesh_scheduler_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<mesh_scheduler_setup_server_register_info.num_opcodes; i++)
    {
        if(company_opcode == m_opcode_handlers[i].opcode)
        {
            handler = m_opcode_handlers[i].handler;
            break;
        }
    }

    if (NULL != handler)
    {
        handler(p_model_msg, p_args);
    }
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t mesh_scheduler_setup_server_init(mesh_scheduler_setup_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->scheduler_cbs.action_set_cb
        || TSCNS_SCHEDULER_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)        
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    mesh_scheduler_setup_server_register_info.p_args = p_server;
    mesh_scheduler_setup_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&mesh_scheduler_setup_server_register_info, &p_server->model_lid);
}

