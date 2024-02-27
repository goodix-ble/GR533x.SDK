/**
 *****************************************************************************************
 *
 * @file scheduler_server.c
 *
 * @brief Mesh Time Server API Implementation.
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
#include "common_utils.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_scheduler_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_scheduler_action_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void mesh_scheduler_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void mesh_scheduler_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);



/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t mesh_scheduler_server_opcode_list[] =
{
    TSCNS_SCHEDULER_OPCODE_ACTION_GET,
    TSCNS_SCHEDULER_OPCODE_GET,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {TSCNS_SCHEDULER_OPCODE_ACTION_GET, handle_scheduler_action_get_cb},
    {TSCNS_SCHEDULER_OPCODE_GET, handle_scheduler_get_cb},
};

static const mesh_model_cb_t mesh_scheduler_server_msg_cb = {
    .cb_rx             = mesh_scheduler_server_rx_cb,
    .cb_sent           = mesh_scheduler_server_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t mesh_scheduler_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_TSCNS_SCH),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)mesh_scheduler_server_opcode_list,
    .num_opcodes = sizeof(mesh_scheduler_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &mesh_scheduler_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static mesh_error_t scheduler_message_send(mesh_scheduler_server_t * p_server,
                                                                const mesh_model_msg_ind_t *p_rx_msg,
                                                                uint16_t send_op,
                                                                uint8_t tx_hdl,
                                                                uint8_t *p_data_send,
                                                                uint16_t data_send_len)
{
    mesh_error_t status = MESH_ERROR_NO_ERROR;
    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(send_op),
        .tx_hdl = tx_hdl,
        .p_data_send = p_data_send,
        .data_send_len = data_send_len,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };


    if (NULL == p_rx_msg)
    {
        APP_LOG_INFO("SERVER[%d] -- to publish : send opcode = %04X, data_send_len = %d.",
                p_server->model_instance_index, send_op, data_send_len);
        status = mesh_model_publish(&msg_send, NULL);
    }
    else
    {
        APP_LOG_INFO("SERVER[%d] -- to response , recv opcode:%04X, response opcode:%04X, data length:%d.",
                p_server->model_instance_index, p_rx_msg->opcode.company_opcode, send_op, data_send_len);
        status = mesh_model_rsp_send(&msg_send);
    }

    return status;
}

static void handle_scheduler_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_scheduler_server_t * p_server = (mesh_scheduler_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   

    uint16_t out_data = 0;

    if (p_rx_msg->msg_len == 0)
    {
        p_server->settings.p_callbacks->scheduler_cbs.get_cb(p_server, p_rx_msg, &out_data);
        (void) scheduler_status_send(p_server, p_rx_msg, &out_data);
    }
}

static void handle_scheduler_action_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_scheduler_server_t * p_server = (mesh_scheduler_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   

    mesh_scheduler_action_status_params_t out_data = {0, MESH_SCHEDULER_INVALID_YEAR};

    if (p_rx_msg->msg_len == TSCNS_SCHEDULER_ACTION_GET_MINLEN)
    {
        p_server->settings.p_callbacks->scheduler_cbs.action_get_cb(p_server, p_rx_msg, p_rx_msg->msg[0], &out_data);
        if (out_data.year != MESH_SCHEDULER_INVALID_YEAR)
        {
            (void) scheduler_action_status_send(p_server, p_rx_msg, &out_data);
        }
    }
}

static void mesh_scheduler_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<mesh_scheduler_server_register_info.num_opcodes; i++)
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

static void mesh_scheduler_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    mesh_scheduler_server_t * p_server = (mesh_scheduler_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * TSCNS_SCHEDULER_SERVER_TX_HDL_TOTAL)
    {
        case TSCNS_SCHEDULER_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case TSCNS_SCHEDULER_SERVER_PUBLISH_SEND_TX_HDL:
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
uint32_t scheduler_status_send(mesh_scheduler_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const uint16_t * p_params)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    uint16_t send_param;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? TSCNS_SCHEDULER_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * TSCNS_SCHEDULER_SERVER_TX_HDL_TOTAL
                                        : TSCNS_SCHEDULER_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * TSCNS_SCHEDULER_SERVER_TX_HDL_TOTAL;

    gx_write16p(&send_param, *p_params);

    return scheduler_message_send(p_server, p_rx_msg, TSCNS_SCHEDULER_OPCODE_STATUS, tx_hdl, (uint8_t *)&send_param, TSCNS_SCHEDULER_STATUS_MINLEN);
}

uint32_t scheduler_action_status_send(mesh_scheduler_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const mesh_scheduler_action_status_params_t * p_params)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    mesh_scheduler_action_status_msg_pkt_t msg_pkt;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? TSCNS_SCHEDULER_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * TSCNS_SCHEDULER_SERVER_TX_HDL_TOTAL
                                        : TSCNS_SCHEDULER_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * TSCNS_SCHEDULER_SERVER_TX_HDL_TOTAL;

    scheduler_pack_action_status(&msg_pkt, p_params);

    return scheduler_message_send(p_server, p_rx_msg, TSCNS_SCHEDULER_OPCODE_ACTION_STATUS, tx_hdl, (uint8_t *)&msg_pkt, TSCNS_SCHEDULER_ACTION_STATUS_MINLEN);
}

uint16_t mesh_scheduler_server_init(mesh_scheduler_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->scheduler_cbs.get_cb
        || NULL == p_server->settings.p_callbacks->scheduler_cbs.action_get_cb
        || TSCNS_SCHEDULER_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)        
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    mesh_scheduler_server_register_info.p_args = p_server;
    mesh_scheduler_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&mesh_scheduler_server_register_info, &p_server->model_lid);
}

uint16_t mesh_scheduler_server_status_publish(mesh_scheduler_server_t * p_server, 
                                                            const uint16_t *p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return scheduler_status_send(p_server, NULL, p_params);
}

uint16_t mesh_scheduler_server_action_status_publish(mesh_scheduler_server_t * p_server, 
                                                            const mesh_scheduler_action_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return scheduler_action_status_send(p_server, NULL, p_params);
}

