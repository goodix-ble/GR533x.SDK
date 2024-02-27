/**
 *****************************************************************************************
 *
 * @file scene_setup_server.c
 *
 * @brief mesh time setup Server API Implementation.
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
#include "scene_message.h"
#include "scene_server.h"
#include "scene_setup_server.h"
#include "common_utils.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_scene_store_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_scene_delete_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void mesh_scene_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void mesh_scene_setup_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t mesh_scene_setup_server_opcode_list[] =
{
    TSCNS_SCENE_OPCODE_STORE,
    TSCNS_SCENE_OPCODE_STORE_UNACKNOWLEDGED,
    TSCNS_SCENE_OPCODE_DELETE,
    TSCNS_SCENE_OPCODE_DELETE_UNACKNOWLEDGED,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {TSCNS_SCENE_OPCODE_STORE, handle_scene_store_cb},
    {TSCNS_SCENE_OPCODE_STORE_UNACKNOWLEDGED, handle_scene_store_cb},
    {TSCNS_SCENE_OPCODE_DELETE, handle_scene_delete_cb},
    {TSCNS_SCENE_OPCODE_DELETE_UNACKNOWLEDGED, handle_scene_delete_cb},
};

static const mesh_model_cb_t mesh_scene_setup_server_msg_cb = {
    .cb_rx             = mesh_scene_setup_server_rx_cb,
    .cb_sent           = mesh_scene_setup_server_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t mesh_scene_setup_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_TSCNS_SCNS),
    .element_offset = 0,
    .publish = false,
    .p_opcodes = (uint16_t *)mesh_scene_setup_server_opcode_list,
    .num_opcodes = sizeof(mesh_scene_setup_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &mesh_scene_setup_server_msg_cb,
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
static void handle_scene_store_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_scene_setup_server_t  * p_server = (mesh_scene_setup_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);

    mesh_scene_store_params_t in_data = {0};
    mesh_scene_register_status_params_t out_data = {0};
    mesh_scene_store_msg_pkt_t * p_msg_params_packed = (mesh_scene_store_msg_pkt_t *) p_rx_msg->msg;

    if (p_rx_msg->msg_len == TSCNS_SCENE_STORE_MINLEN)
    {
        in_data.scene_number = gx_read16p((const void *)&p_msg_params_packed->scene_number);

        p_server->settings.p_callbacks->scenes_cbs.store_cb(p_server,
                                                                                 p_rx_msg,
                                                                                 &in_data,
                                                                                 (p_rx_msg->opcode.company_opcode == TSCNS_SCENE_OPCODE_STORE) ? ((void *)&out_data) : NULL);

        if (p_rx_msg->opcode.company_opcode == TSCNS_SCENE_OPCODE_STORE)
        {
            (void) scene_regester_status_send(p_server->scene_server, p_rx_msg, &out_data);
        }        
    }
}

static void handle_scene_delete_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_scene_setup_server_t  * p_server = (mesh_scene_setup_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);

    mesh_scene_delete_params_t in_data = {0};
    mesh_scene_register_status_params_t out_data = {0};
    mesh_scene_delete_msg_pkt_t * p_msg_params_packed = (mesh_scene_delete_msg_pkt_t *) p_rx_msg->msg;

    if (p_rx_msg->msg_len == TSCNS_SCENE_DELETE_MINLEN)
    {
        in_data.scene_number = gx_read16p((const void *)&p_msg_params_packed->scene_number);

        p_server->settings.p_callbacks->scenes_cbs.delete_cb(p_server,
                                                                                     p_rx_msg,
                                                                                     &in_data,
                                                                                     (p_rx_msg->opcode.company_opcode == TSCNS_SCENE_OPCODE_DELETE) ? ((void *)&out_data) : NULL);

        if (p_rx_msg->opcode.company_opcode == TSCNS_SCENE_OPCODE_DELETE)
        {
            (void) scene_regester_status_send(p_server->scene_server, p_rx_msg, &out_data);
        }
    }
}

static void mesh_scene_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<mesh_scene_setup_server_register_info.num_opcodes; i++)
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

static void mesh_scene_setup_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    mesh_scene_setup_server_t * p_server = (mesh_scene_setup_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * TSCNS_SCENE_SERVER_TX_HDL_TOTAL)
    {
        case TSCNS_SCENE_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case TSCNS_SCENE_SERVER_PUBLISH_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Published message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to published message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        default:
            APP_LOG_INFO("Never here!!!");
            break;
    }
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t mesh_scene_setup_server_init(mesh_scene_setup_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->scenes_cbs.store_cb
        || NULL == p_server->settings.p_callbacks->scenes_cbs.delete_cb
        || TSCNS_SCENE_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)        
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    mesh_scene_setup_server_register_info.p_args = p_server;
    mesh_scene_setup_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&mesh_scene_setup_server_register_info, &p_server->model_lid);
}

