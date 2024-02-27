/**
 *****************************************************************************************
 *
 * @file mesh_dfu_client.c
 *
 * @brief Mesh DFU Client API Implementation.
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
#include "mesh_dfu_client.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void current_version_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void new_version_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void mesh_dfu_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void mesh_dfu_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t mesh_dfu_client_opcode_list[] =
{
    MESH_DFU_OPCODE_CURRENT_VERSION_STATUS,
    MESH_DFU_OPCODE_NEW_VERSION_STATUS,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {MESH_DFU_OPCODE_CURRENT_VERSION_STATUS, current_version_status_handle},
    {MESH_DFU_OPCODE_NEW_VERSION_STATUS, new_version_status_handle},
};

static const mesh_model_cb_t mesh_dfu_client_msg_cb = {
    .cb_rx             = mesh_dfu_client_rx_cb,
    .cb_sent           = mesh_dfu_client_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t mesh_dfu_client_register_info = 
{
    .model_id = MESH_MODEL_VENDOR(MESH_DFU_CLIENT_MODEL_ID, MESH_DFU_COMPANY_ID),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)mesh_dfu_client_opcode_list,
    .num_opcodes = sizeof(mesh_dfu_client_opcode_list) / sizeof(uint16_t),
    .p_cb = &mesh_dfu_client_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static void current_version_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_dfu_client_t * p_client = (mesh_dfu_client_t *) p_args;

    if (p_rx_msg->msg_len == sizeof(mesh_dfu_current_version_status_msg_pkt_t))
    {
        p_client->settings.p_callbacks->dfu_current_version_status_cb(p_client, p_rx_msg, (mesh_dfu_current_version_status_msg_pkt_t *)p_rx_msg->msg);
    }
}

static void new_version_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_dfu_client_t * p_client = (mesh_dfu_client_t *) p_args;

    if (p_rx_msg->msg_len == sizeof(mesh_dfu_new_version_status_msg_pkt_t))
    {
        p_client->settings.p_callbacks->dfu_new_version_status_cb(p_client, p_rx_msg, (mesh_dfu_new_version_status_msg_pkt_t *)p_rx_msg->msg);
    }
}

static void message_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, uint8_t * p_buffer, uint16_t length)
{
    mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_VENDOR(company_opcode, MESH_DFU_COMPANY_ID);

    // fill publish data by tx_hdl
    p_msg_tx->model_lid        = model_lid;
    p_msg_tx->opcode           = opcode;
    p_msg_tx->tx_hdl           = tx_hdl;
    p_msg_tx->p_data_send      = p_buffer;
    p_msg_tx->data_send_len    = length;
    p_msg_tx->dst              = MESH_INVALID_ADDR;
    p_msg_tx->appkey_index     = MESH_INVALID_KEY_INDEX;
}

static void mesh_dfu_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;
    mesh_opcode_handler_cb_t handler = NULL;
    
    for (uint8_t i = 0; i < sizeof(m_opcode_handlers) / sizeof(m_opcode_handlers[0]); i++)
    {
        if (company_opcode == m_opcode_handlers[i].opcode)
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

static void mesh_dfu_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args)
{
    mesh_dfu_client_t * p_client = (mesh_dfu_client_t *) p_args;
    
    switch(p_sent->tx_hdl - p_client->model_instance_index * MESH_DFU_CLIENT_TX_HDL_TOTAL)
    {
        case MESH_DFU_CLIENT_CURRENT_VERSION_GET_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("DFUCLIENT[%d] -- Sent get message!!!", p_client->model_instance_index)
                  : APP_LOG_INFO("DFUCLIENT[%d] -- Failed to send get message, status = %x!!!", p_client->model_instance_index, p_sent->status);

            break;
        case MESH_DFU_CLIENT_NEW_VERSION_SET_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("DFUCLIENT[%d] -- Sent set message!!!", p_client->model_instance_index)
                  : APP_LOG_INFO("DFUCLIENT[%d] -- Failed to send set message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            break;
        case MESH_DFU_CLIENT_NEW_VERSION_SET_UNRELIABLE_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("DFUCLIENT[%d] -- Sent set(unreliable) message!!!", p_client->model_instance_index)
                  : APP_LOG_INFO("DFUCLIENT[%d] -- Failed to send set(unreliable) message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            break;
        default:
            APP_LOG_INFO("msg has been sent!!!");
            break;
    }   
}


/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t mesh_dfu_client_init(mesh_dfu_client_t *p_client, uint8_t element_offset)
{
    if (NULL == p_client
        || NULL == p_client->settings.p_callbacks
        || NULL == p_client->settings.p_callbacks->dfu_current_version_status_cb
        || NULL == p_client->settings.p_callbacks->dfu_new_version_status_cb
        || NULL == p_client->settings.p_callbacks->ack_transaction_status_cb
        || MESH_DFU_CLIENT_INSTANCE_COUNT_MAX <= p_client->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    mesh_dfu_client_register_info.p_args         = p_client;
    mesh_dfu_client_register_info.element_offset = element_offset;
    
    return mesh_model_register(&mesh_dfu_client_register_info, &p_client->model_lid);
}

uint16_t mesh_dfu_client_new_version_set(mesh_dfu_client_t * p_client, const mesh_dfu_new_version_set_msg_pkt_t * p_params)
{
    mesh_model_send_info_t model_msg_send;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = MESH_DFU_CLIENT_NEW_VERSION_SET_SEND_TX_HDL + p_client->model_instance_index * MESH_DFU_CLIENT_TX_HDL_TOTAL;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_VENDOR(MESH_DFU_OPCODE_NEW_VERSION_STATUS, MESH_DFU_COMPANY_ID),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
    
    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            message_create(&model_msg_send, p_client->model_lid, MESH_DFU_OPCODE_NEW_VERSION_SET,
                            tx_hdl, (uint8_t *)p_params, sizeof(mesh_dfu_new_version_set_msg_pkt_t));
            
            return mesh_model_publish(&model_msg_send, &reliable_info);
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t mesh_dfu_client_new_version_set_unack(mesh_dfu_client_t * p_client, const mesh_dfu_new_version_set_msg_pkt_t * p_params)
{
    mesh_model_send_info_t model_msg_send;
    uint8_t tx_hdl = MESH_DFU_CLIENT_NEW_VERSION_SET_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * MESH_DFU_CLIENT_TX_HDL_TOTAL;

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    message_create(&model_msg_send, p_client->model_lid, MESH_DFU_OPCODE_NEW_VERSION_SET_UNACKNOWLEDGED,
                    tx_hdl, (uint8_t *)p_params, sizeof(mesh_dfu_new_version_set_msg_pkt_t));

    return mesh_model_publish(&model_msg_send, NULL);
}

uint16_t mesh_dfu_client_current_version_get(mesh_dfu_client_t * p_client)
{
    mesh_model_send_info_t model_msg_send;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = MESH_DFU_CLIENT_CURRENT_VERSION_GET_SEND_TX_HDL + p_client->model_instance_index * MESH_DFU_CLIENT_TX_HDL_TOTAL;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_VENDOR(MESH_DFU_OPCODE_CURRENT_VERSION_STATUS, MESH_DFU_COMPANY_ID),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
    
    if (p_client == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            message_create(&model_msg_send, p_client->model_lid, MESH_DFU_OPCODE_CURRENT_VERSION_GET, tx_hdl, NULL, 0);
            
            return mesh_model_publish(&model_msg_send, &reliable_info);
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t mesh_dfu_client_setget_cancel(mesh_dfu_client_t * p_client)
{
    if (p_client == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return mesh_model_reliable_trans_cancel(p_client->model_lid);
}

