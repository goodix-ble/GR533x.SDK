/**
 *****************************************************************************************
 *
 * @file scheduler_client.c
 *
 * @brief Mesh Scheduler Client API Implementation.
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
#include "scheduler_client.h"
#include "common_utils.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
 
static void scheduler_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void scheduler_action_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void mesh_scheduler_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void mesh_scheduler_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t mesh_scheduler_client_opcode_list[] =
{
    TSCNS_SCHEDULER_OPCODE_ACTION_STATUS,
    TSCNS_SCHEDULER_OPCODE_STATUS,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {TSCNS_SCHEDULER_OPCODE_ACTION_STATUS, scheduler_action_status_handle},
    {TSCNS_SCHEDULER_OPCODE_STATUS, scheduler_status_handle},
};

static const mesh_model_cb_t mesh_scheduler_client_msg_cb = {
    .cb_rx             = mesh_scheduler_client_rx_cb,
    .cb_sent           = mesh_scheduler_client_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t mesh_scheduler_client_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_TSCNC_SCH),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)mesh_scheduler_client_opcode_list,
    .num_opcodes = sizeof(mesh_scheduler_client_opcode_list) / sizeof(uint16_t),
    .p_cb = &mesh_scheduler_client_msg_cb,
    .p_args = NULL,
};



/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void scheduler_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_scheduler_client_t * p_client = (mesh_scheduler_client_t *) p_args;

    if (p_rx_msg->msg_len ==  TSCNS_SCHEDULER_STATUS_MINLEN)
    {
        uint16_t in_data = gx_read16p((void const *)p_rx_msg->msg);

        APP_LOG_INFO("scheduler status %02x", in_data);
        p_client->settings.p_callbacks->scheduler_status_cb(p_client, p_rx_msg, &in_data);
    }
}

static void scheduler_action_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_scheduler_client_t * p_client = (mesh_scheduler_client_t *) p_args;

    if (p_rx_msg->msg_len == TSCNS_SCHEDULER_ACTION_STATUS_MINLEN)
    {
        mesh_scheduler_action_status_msg_pkt_t * p_msg_params_packed = (mesh_scheduler_action_status_msg_pkt_t *) p_rx_msg->msg;
        mesh_scheduler_action_status_params_t in_data = {0}; 

        scheduler_unpack_action_status((mesh_scheduler_action_set_params_t *)&in_data, (mesh_scheduler_action_set_msg_pkt_t *)p_msg_params_packed);
        p_client->settings.p_callbacks->scheduler_action_status_cb(p_client, p_rx_msg, &in_data);
    }
}

#ifdef MESH_MODEL_BQB_TEST
static void message_send_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, uint8_t * p_buffer, uint16_t length)
{
    mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_SIG(company_opcode);

    // fill publish data by tx_hdl
    p_msg_tx->model_lid        = model_lid;
    p_msg_tx->opcode           = opcode;
    p_msg_tx->tx_hdl           = tx_hdl;
    p_msg_tx->p_data_send      = p_buffer;
    p_msg_tx->data_send_len    = length;
    p_msg_tx->dst              = 0x01;
    p_msg_tx->appkey_index     = 0x00;
}

static uint16_t model_send_unicast_dev(mesh_scheduler_client_t *p_client, uint16_t opcode, uint8_t tx_hdl, uint8_t *p_buffer, uint16_t length)
{
    mesh_model_send_info_t model_msg_send;
    message_send_create(&model_msg_send, p_client->model_lid, opcode, tx_hdl, p_buffer, length);

    return mesh_model_pdu_send(&model_msg_send);
}
#else
static void message_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, uint8_t * p_buffer, uint16_t length)
{
    mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_SIG(company_opcode);

    // fill publish data by tx_hdl
    p_msg_tx->model_lid        = model_lid;
    p_msg_tx->opcode           = opcode;
    p_msg_tx->tx_hdl           = tx_hdl;
    p_msg_tx->p_data_send      = p_buffer;
    p_msg_tx->data_send_len    = length;
    p_msg_tx->dst              = MESH_INVALID_ADDR;
    p_msg_tx->appkey_index     = MESH_INVALID_KEY_INDEX;
}
#endif

static void mesh_scheduler_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;
    uint8_t index = 0;
    switch(company_opcode)
    {
        case TSCNS_SCHEDULER_OPCODE_ACTION_STATUS:
            index = 0;
            break;
        case TSCNS_SCHEDULER_OPCODE_STATUS:
            index = 1;
            break;
        default:
            APP_LOG_INFO("[%s] enter -- Failed to find status callback = %x!!!", __func__, company_opcode);
            return ;
    }

    APP_LOG_INFO("[%s] enter -- callback = %d!!!", __func__, index);

    mesh_opcode_handler_cb_t handler = m_opcode_handlers[index].handler;

    if (NULL != handler)
    {
        handler(p_model_msg, p_args);
    }
}

static void mesh_scheduler_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args)
{
    mesh_scheduler_client_t * p_client = (mesh_scheduler_client_t *) p_args;
    
    switch(p_sent->tx_hdl - p_client->model_instance_index * TSCNS_SCHEDULER_SERVER_TX_HDL_TOTAL)
    {
        case TSCNS_SCHEDULER_CLIENT_GET_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent get message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send get message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case TSCNS_SCHEDULER_CLIENT_SET_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent set message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send set message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case TSCNS_SCHEDULER_CLIENT_SET_UNRELIABLE_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent set(unreliable) message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send set(unreliable) message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
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

uint16_t mesh_scheduler_client_init(mesh_scheduler_client_t *p_client, uint8_t element_offset)
{
    if (NULL == p_client
        || NULL == p_client->settings.p_callbacks
        || NULL == p_client->settings.p_callbacks->scheduler_status_cb
        || NULL == p_client->settings.p_callbacks->scheduler_action_status_cb
        || NULL == p_client->settings.p_callbacks->ack_transaction_status_cb
        || TSCNS_SCHEDULER_CLIENT_INSTANCE_COUNT_MAX <= p_client->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    mesh_scheduler_client_register_info.p_args         = p_client;
    mesh_scheduler_client_register_info.element_offset = element_offset;
    
    return mesh_model_register(&mesh_scheduler_client_register_info, &p_client->model_lid);
}

uint16_t mesh_scheduler_client_action_set(mesh_scheduler_client_t * p_client, const mesh_scheduler_action_set_params_t * p_params)
{
    mesh_scheduler_action_set_msg_pkt_t set;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = TSCNS_SCHEDULER_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * TSCNS_SCHEDULER_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(TSCNS_SCHEDULER_OPCODE_ACTION_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

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

            scheduler_pack_action_status((mesh_scheduler_action_status_msg_pkt_t *)&set, (mesh_scheduler_action_status_params_t *)p_params);

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, TSCNS_SCHEDULER_OPCODE_ACTION_SET, tx_hdl, (uint8_t *)&set, TSCNS_SCHEDULER_ACTION_SET_MINLEN);
#else
            message_create(&model_msg_send, p_client->model_lid, TSCNS_SCHEDULER_OPCODE_ACTION_SET, tx_hdl, (uint8_t *)&set, TSCNS_SCHEDULER_ACTION_SET_MINLEN);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t mesh_scheduler_client_action_set_unack(mesh_scheduler_client_t * p_client, const mesh_scheduler_action_set_params_t * p_params)
{
    mesh_scheduler_action_set_msg_pkt_t set_un;
    uint8_t tx_hdl = TSCNS_SCHEDULER_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * TSCNS_SCHEDULER_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    scheduler_pack_action_status((mesh_scheduler_action_status_msg_pkt_t *)&set_un, (mesh_scheduler_action_status_params_t *)p_params);

#ifdef MESH_MODEL_BQB_TEST
    return model_send_unicast_dev(p_client, TSCNS_SCHEDULER_OPCODE_ACTION_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, TSCNS_SCHEDULER_ACTION_SET_MINLEN);
#else
    message_create(&model_msg_send, p_client->model_lid, TSCNS_SCHEDULER_OPCODE_ACTION_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, TSCNS_SCHEDULER_ACTION_SET_MINLEN);
    return mesh_model_publish(&model_msg_send, NULL);
#endif
}

uint16_t mesh_scheduler_client_get(mesh_scheduler_client_t * p_client)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = TSCNS_SCHEDULER_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * TSCNS_SCHEDULER_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(TSCNS_SCHEDULER_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif    

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
#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, TSCNS_SCHEDULER_OPCODE_GET, tx_hdl, NULL, 0);
#else
            message_create(&model_msg_send, p_client->model_lid, TSCNS_SCHEDULER_OPCODE_GET, tx_hdl, NULL, 0);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t mesh_scheduler_client_action_get(mesh_scheduler_client_t * p_client, uint8_t action_index)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = TSCNS_SCHEDULER_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * TSCNS_SCHEDULER_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(TSCNS_SCHEDULER_OPCODE_ACTION_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif    

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
#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, TSCNS_SCHEDULER_OPCODE_ACTION_GET, tx_hdl, &action_index, TSCNS_SCHEDULER_ACTION_GET_MINLEN);
#else
            message_create(&model_msg_send, p_client->model_lid, TSCNS_SCHEDULER_OPCODE_ACTION_GET, tx_hdl, &action_index, TSCNS_SCHEDULER_ACTION_GET_MINLEN);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t mesh_scheduler_client_setget_cancel(mesh_scheduler_client_t * p_client)
{
    if (p_client == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    
    return mesh_model_reliable_trans_cancel(p_client->model_lid);
}

