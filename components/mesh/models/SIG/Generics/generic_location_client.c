/**
 *****************************************************************************************
 *
 * @file generic_location_client.c
 *
 * @brief Generic Location Client API Implementation.
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
#include "generic_location_message.h"
#include "generic_location_client.h"
#include "common_utils.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void global_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void local_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void generic_location_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void generic_location_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
static const uint16_t generic_location_client_opcode_list[] =
{
    GENERIC_LOCATION_GLOBAL_OPCODE_STATUS,
    GENERIC_LOCATION_LOCAL_OPCODE_STATUS
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {GENERIC_LOCATION_GLOBAL_OPCODE_STATUS, global_status_handle},
    {GENERIC_LOCATION_LOCAL_OPCODE_STATUS, local_status_handle},
};

static const mesh_model_cb_t generic_location_client_msg_cb = {
    .cb_rx             = generic_location_client_rx_cb,
    .cb_sent           = generic_location_client_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t generic_location_client_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_GENC_LOC),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)generic_location_client_opcode_list,
    .num_opcodes = sizeof(generic_location_client_opcode_list) / sizeof(uint16_t),
    .p_cb = &generic_location_client_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static void global_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    generic_location_client_t * p_client = (generic_location_client_t *) p_args;
    location_global_status_params_t in_data = {0};

    APP_LOG_INFO("[%s] enter , source address: 0x%04X", __func__, p_rx_msg->src);
    if (p_rx_msg->msg_len == GENERIC_LOCATION_GLOBAL_STATUS_MAXLEN)
    {
        generic_location_global_status_msg_pkt_t * p_msg_params_packed = (generic_location_global_status_msg_pkt_t *) p_rx_msg->msg;

        in_data.global_latitude = gx_read32p((const void *)&p_msg_params_packed->global_latitude);
        in_data.global_longitude = gx_read32p((const void *)&p_msg_params_packed->global_longitude);
        in_data.global_altitude = gx_read16p((const void *)&p_msg_params_packed->global_altitude);

        p_client->settings.p_callbacks->location_status_cb(p_client, p_rx_msg, &in_data, NULL);
    }
    else
    {
        APP_LOG_ERROR("[ERROR] message length is %d ", p_rx_msg->msg_len);
    }
}

static void local_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    generic_location_client_t * p_client = (generic_location_client_t *) p_args;
    location_local_status_params_t in_data = {0};

    APP_LOG_INFO("[%s] enter , source address 0x%04X", __func__, p_rx_msg->src);
    if (p_rx_msg->msg_len == GENERIC_LOCATION_LOCAL_STATUS_MAXLEN)
    {
        generic_location_local_status_msg_pkt_t * p_msg_params_packed = (generic_location_local_status_msg_pkt_t *) p_rx_msg->msg;

        in_data.local_north = gx_read16p((const void *)&p_msg_params_packed->local_north);
        in_data.local_east = gx_read16p((const void *)&p_msg_params_packed->local_east);
        in_data.local_altitude = gx_read16p((const void *)&p_msg_params_packed->local_altitude);
        in_data.floor_number = p_msg_params_packed->floor_number;
        in_data.uncertainty = gx_read16p((const void *)&p_msg_params_packed->uncertainty);

        p_client->settings.p_callbacks->location_status_cb(p_client, p_rx_msg, NULL, &in_data);
    }
    else
    {
        APP_LOG_ERROR("[ERROR] message length is %d ", p_rx_msg->msg_len);
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

static uint16_t model_send_unicast_dev(generic_location_client_t *p_client, uint16_t opcode, uint8_t tx_hdl, uint8_t *p_buffer, uint16_t length)
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

static void generic_location_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;

    APP_LOG_INFO("[%s] enter", __func__);
    for(uint8_t i = 0; i<generic_location_client_register_info.num_opcodes; i++)
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

static void generic_location_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    generic_location_client_t * p_client = (generic_location_client_t *) p_args;

    switch(p_sent->tx_hdl - p_client->model_instance_index * GENERIC_LOCATION_CLIENT_TX_HDL_TOTAL)
    {
        case GENERIC_LOCATION_CLIENT_GET_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent get message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send get message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case GENERIC_LOCATION_CLIENT_SET_LOC_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent set local message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send set local message = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case GENERIC_ONOFF_CLIENT_SET_LOC_UNRELIABLE_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent set local unack message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send set local unackmessage = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case GENERIC_LOCATION_CLIENT_SET_GLO_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent set global message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send set global message = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case GENERIC_ONOFF_CLIENT_SET_GLO_UNRELIABLE_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent set global unack message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send set global unack message = %x!!!", p_client->model_instance_index, p_sent->status);
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

uint16_t generic_location_client_init(generic_location_client_t *p_client, uint8_t element_offset)
{
    if (NULL == p_client
        || NULL == p_client->settings.p_callbacks
        || NULL == p_client->settings.p_callbacks->location_status_cb
        || NULL == p_client->settings.p_callbacks->ack_transaction_status_cb
        || GENERIC_LOCATION_CLIENT_INSTANCE_COUNT_MAX <= p_client->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    generic_location_client_register_info.p_args         = p_client;
    generic_location_client_register_info.element_offset = element_offset;
    
    return mesh_model_register(&generic_location_client_register_info, &p_client->model_lid);
}

uint16_t generic_location_local_set(generic_location_client_t * p_client, const location_local_status_params_t * p_params, bool ack_flg)
{
    generic_location_local_status_msg_pkt_t set;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = ack_flg ? (GENERIC_LOCATION_CLIENT_SET_LOC_SEND_TX_HDL + p_client->model_instance_index * GENERIC_LOCATION_CLIENT_TX_HDL_TOTAL)
                                            :(GENERIC_ONOFF_CLIENT_SET_LOC_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * GENERIC_LOCATION_CLIENT_TX_HDL_TOTAL);
    uint16_t opcode = ack_flg ? GENERIC_LOCATION_LOCAL_OPCODE_SET:GENERIC_LOCATION_LOCAL_OPCODE_SET_UNACK;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(GENERIC_LOCATION_LOCAL_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if ((!ack_flg) || (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state)))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            gx_write16p((void const *)&set.local_north, p_params->local_north);
            gx_write16p((void const *)&set.local_east, p_params->local_east);
            gx_write16p((void const *)&set.local_altitude, p_params->local_altitude);
            set.floor_number = p_params->floor_number;
            gx_write16p((void const *)&set.uncertainty, p_params->uncertainty);

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, opcode, tx_hdl, (uint8_t *)&set, GENERIC_LOCATION_LOCAL_STATUS_MAXLEN);
#else
            message_create(&model_msg_send, p_client->model_lid, opcode, tx_hdl, (uint8_t *)&set, GENERIC_LOCATION_LOCAL_STATUS_MAXLEN);
            return mesh_model_publish(&model_msg_send, ack_flg?(&reliable_info):NULL);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t generic_location_global_set(generic_location_client_t * p_client, const location_global_status_params_t * p_params, bool ack_flg)
{
    generic_location_global_status_msg_pkt_t set;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = ack_flg ? (GENERIC_LOCATION_CLIENT_SET_GLO_SEND_TX_HDL + p_client->model_instance_index * GENERIC_LOCATION_CLIENT_TX_HDL_TOTAL)
                                            :(GENERIC_ONOFF_CLIENT_SET_GLO_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * GENERIC_LOCATION_CLIENT_TX_HDL_TOTAL);
    uint16_t opcode = ack_flg ? GENERIC_LOCATION_GLOBAL_OPCODE_SET:GENERIC_LOCATION_GLOBAL_OPCODE_SET_UNACK;

#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(GENERIC_LOCATION_GLOBAL_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif
    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if ((!ack_flg) || (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state)))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            gx_write32p((void const *)&set.global_latitude, p_params->global_latitude);
            gx_write32p((void const *)&set.global_longitude, p_params->global_longitude);
            gx_write16p((void const *)&set.global_altitude, p_params->global_altitude);

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, opcode, tx_hdl, (uint8_t *)&set, GENERIC_LOCATION_GLOBAL_STATUS_MAXLEN);
#else
            message_create(&model_msg_send, p_client->model_lid, opcode, tx_hdl, (uint8_t *)&set, GENERIC_LOCATION_GLOBAL_STATUS_MAXLEN);
            return mesh_model_publish(&model_msg_send, ack_flg?(&reliable_info):NULL);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}
uint16_t generic_location_client_get(generic_location_client_t * p_client, const cmd_type_t cmd_type)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = GENERIC_LOCATION_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * GENERIC_LOCATION_CLIENT_TX_HDL_TOTAL;
    uint16_t opcode = (cmd_type == LOCAL)?GENERIC_LOCATION_LOCAL_OPCODE_GET : GENERIC_LOCATION_GLOBAL_OPCODE_GET;
#ifndef MESH_MODEL_BQB_TEST
    uint16_t reply_opcode = (cmd_type == LOCAL)?GENERIC_LOCATION_LOCAL_OPCODE_STATUS:GENERIC_LOCATION_GLOBAL_OPCODE_STATUS;
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(reply_opcode),
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
            return model_send_unicast_dev(p_client, opcode, tx_hdl, NULL, 0);
#else
            message_create(&model_msg_send, p_client->model_lid, opcode, tx_hdl, NULL, 0);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

