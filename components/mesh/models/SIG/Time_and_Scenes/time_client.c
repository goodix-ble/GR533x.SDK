/**
 *****************************************************************************************
 *
 * @file time_client.c
 *
 * @brief Mesh Time Client API Implementation.
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
#include "time_message.h"
#include "time_client.h"
#include "common_utils.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void time_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void role_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void zone_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void dlt_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void mesh_time_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void mesh_time_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t mesh_time_client_opcode_list[] =
{
    TSCNS_TIME_OPCODE_STATUS,
    TSCNS_TIME_ROLE_OPCODE_STATUS,
    TSCNS_TIME_ZONE_OPCODE_STATUS,
    TSCNS_TIME_TAI2UTC_DLT_OPCODE_STATUS,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {TSCNS_TIME_OPCODE_STATUS, time_status_handle},
    {TSCNS_TIME_ROLE_OPCODE_STATUS, role_status_handle},
    {TSCNS_TIME_ZONE_OPCODE_STATUS, zone_status_handle},
    {TSCNS_TIME_TAI2UTC_DLT_OPCODE_STATUS, dlt_status_handle}
};

static const mesh_model_cb_t mesh_time_client_msg_cb = {
    .cb_rx             = mesh_time_client_rx_cb,
    .cb_sent           = mesh_time_client_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t mesh_time_client_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_TSCNC_TIM),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)mesh_time_client_opcode_list,
    .num_opcodes = sizeof(mesh_time_client_opcode_list) / sizeof(uint16_t),
    .p_cb = &mesh_time_client_msg_cb,
    .p_args = NULL,
};

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

extern bool is_little_endian;

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static bool endian_judge(void)
{
    uint16_t i= 0x01;
    uint8_t *p = (uint8_t *)&i;

    return (is_little_endian = (*p == 0x01)?true:false);
}

static void time_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_time_client_t * p_client = (mesh_time_client_t *) p_args;
    mesh_time_status_params_t in_data = {0};

    if (p_rx_msg->msg_len == TSCNS_TIME_STATUS_MINLEN)
    {
        mesh_time_status_msg_pkt_t * p_msg_params_packed = (mesh_time_status_msg_pkt_t *) p_rx_msg->msg;

        in_data.TAI_seconds = p_msg_params_packed->TAI_seconds;
        in_data.TAI_seconds = gx_read40p(&in_data.TAI_seconds);

        in_data.subsecond = p_msg_params_packed->subsecond;
        in_data.uncertainty = p_msg_params_packed->uncertainty;;
        in_data.time_authority = p_msg_params_packed->time_authority;

        in_data.TAI2UTC_dlt = p_msg_params_packed->TAI2UTC_dlt;
        if (!is_little_endian)
        {
            in_data.TAI2UTC_dlt = in_data.TAI2UTC_dlt<<1;
        }
        in_data.TAI2UTC_dlt = gx_read16p(&in_data.TAI2UTC_dlt);

        in_data.time_zone_offset = p_msg_params_packed->time_zone_offset;

    APP_LOG_INFO("get time is %lld s, %d ms, uncertainty %d, time_authority %d, TAI to UTC dlt %d, offset %d!", 
        in_data.TAI_seconds, in_data.subsecond*1000/256, in_data.uncertainty, in_data.time_authority, in_data.TAI2UTC_dlt, in_data.time_zone_offset);

        p_client->settings.p_callbacks->time_status_cb(p_client, p_rx_msg, &in_data);
    }
}

static void role_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_time_client_t * p_client = (mesh_time_client_t *) p_args;

    if (p_rx_msg->msg_len == TSCNS_TIME_ROLE_STATUS_MINLEN)
    {
        uint8_t role = p_rx_msg->msg[0];

        p_client->settings.p_callbacks->role_status_cb(p_client, p_rx_msg, &role);
    }
}

static void zone_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_time_client_t * p_client = (mesh_time_client_t *) p_args;
    mesh_time_zone_status_params_t in_data = {0};

    if (p_rx_msg->msg_len == TSCNS_TIME_ZONE_STATUS_MINLEN)
    {
        mesh_time_zone_status_msg_pkt_t * p_msg_params_packed = (mesh_time_zone_status_msg_pkt_t *) p_rx_msg->msg;

        in_data.time_zone_offset_current = p_msg_params_packed->time_zone_offset_current;
        in_data.time_zone_offset_new = p_msg_params_packed->time_zone_offset_new;

        in_data.TAI_zone_change = p_msg_params_packed->TAI_zone_change;
        in_data.TAI_zone_change = gx_read40p(&in_data.TAI_zone_change);

        p_client->settings.p_callbacks->zone_status_cb(p_client, p_rx_msg, &in_data);
    }
}

static void dlt_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_time_client_t * p_client = (mesh_time_client_t *) p_args;
    mesh_tai2utc_dlt_status_params_t in_data = {0};

    if (p_rx_msg->msg_len == TSCNS_TIME_TAI2UTC_DLT_STATUS_MINLEN)
    {
        mesh_tai2utc_dlt_status_msg_pkt_t * p_msg_params_packed = (mesh_tai2utc_dlt_status_msg_pkt_t *) p_rx_msg->msg;

        in_data.TAI2UTC_dlt_current = p_msg_params_packed->TAI2UTC_dlt_current;
        if (!is_little_endian)
        {
            in_data.TAI2UTC_dlt_current = in_data.TAI2UTC_dlt_current<<1;
        }
        in_data.TAI2UTC_dlt_current = gx_read16p(&in_data.TAI2UTC_dlt_current);

        in_data.TAI2UTC_dlt_new = p_msg_params_packed->TAI2UTC_dlt_new;
        if (!is_little_endian)
        {
            in_data.TAI2UTC_dlt_new = in_data.TAI2UTC_dlt_new <<1;
        }
        in_data.TAI2UTC_dlt_new = gx_read16p(&in_data.TAI2UTC_dlt_new);

        in_data.TAI_dlt_change = p_msg_params_packed->TAI_dlt_change;
        in_data.TAI_dlt_change= gx_read40p(&in_data.TAI_dlt_change);

        p_client->settings.p_callbacks->dlt_status_cb(p_client, p_rx_msg, &in_data);
    }
}

static uint8_t message_set_time_packet_create(mesh_time_set_msg_pkt_t *p_set, const mesh_time_set_params_t * p_params)
{
    mesh_time_set_params_t local_params;

    APP_LOG_INFO("%s Sending msg: SET TAI TO %d", __func__, p_params->TAI_seconds);

    local_params = *p_params;

    gx_write40p(&local_params.TAI_seconds, local_params.TAI_seconds);
    p_set->TAI_seconds = local_params.TAI_seconds;

    p_set->subsecond = local_params.subsecond;
    p_set->uncertainty = local_params.uncertainty;
    p_set->time_authority = local_params.time_authority;

    gx_write16p(&local_params.TAI2UTC_dlt, local_params.TAI2UTC_dlt);
    if (!is_little_endian)
    {
        local_params.TAI2UTC_dlt = local_params.TAI2UTC_dlt>>1;
    }
    p_set->TAI2UTC_dlt = local_params.TAI2UTC_dlt;
    p_set->time_zone_offset = local_params.time_zone_offset;

    return TSCNS_TIME_SET_MINLEN;
}

static uint8_t message_set_zone_packet_create(mesh_time_zone_set_msg_pkt_t *p_set, const mesh_time_zone_set_params_t * p_params)
{
    mesh_time_zone_set_params_t local_params;

    APP_LOG_INFO("%s Sending msg: SET ZONE TO %d", __func__, p_params->time_zone_offset_new);

    local_params = *p_params;

    gx_write40p(&local_params.TAI_zone_change, local_params.TAI_zone_change);
    p_set->TAI_zone_change = local_params.TAI_zone_change;

    p_set->time_zone_offset_new = local_params.time_zone_offset_new;

    return TSCNS_TIME_ZONE_SET_MINLEN;
}

static uint8_t message_set_tai2utc_dlt_packet_create(mesh_tai2utc_dlt_set_msg_pkt_t *p_set, const mesh_tai2utc_dlt_set_params_t * p_params)
{
    mesh_tai2utc_dlt_set_params_t local_params;

    APP_LOG_INFO("%s Sending msg: SET Delta TO %d", __func__, p_params->TAI2UTC_dlt_new);

    local_params = *p_params;

    gx_write16p(&local_params.TAI2UTC_dlt_new, local_params.TAI2UTC_dlt_new);
    if (!is_little_endian)
    {
        local_params.TAI2UTC_dlt_new = local_params.TAI2UTC_dlt_new >> 1;
    }
    p_set->TAI2UTC_dlt_new = local_params.TAI2UTC_dlt_new;
    gx_write40p(&local_params.TAI_dlt_change, local_params.TAI_dlt_change);
    p_set->TAI_dlt_change = local_params.TAI_dlt_change;

    p_set->Padding = 0;

    return TSCNS_TIME_TAI2UTC_DLT_SET_MINLEN;
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

static uint16_t model_send_unicast_dev(mesh_time_client_t *p_client, uint16_t opcode, uint8_t tx_hdl, uint8_t *p_buffer, uint16_t length)
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

static void mesh_time_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;
    uint8_t index = 0;
    switch(company_opcode)
    {
        case TSCNS_TIME_OPCODE_STATUS:
            index = 0;
            break;
        case TSCNS_TIME_ROLE_OPCODE_STATUS:
            index = 1;
            break;
        case TSCNS_TIME_ZONE_OPCODE_STATUS:
            index = 2;
            break;
        case TSCNS_TIME_TAI2UTC_DLT_OPCODE_STATUS:
            index = 3;
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

static void mesh_time_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    mesh_time_client_t * p_client = (mesh_time_client_t *) p_args;

    switch(p_sent->tx_hdl - p_client->model_instance_index * TSCNS_TIME_SERVER_TX_HDL_TOTAL)
    {
        case TSCNS_TIME_CLIENT_GET_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent get message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send get message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case TSCNS_TIME_CLIENT_SET_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent set message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send set message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case TSCNS_TIME_CLIENT_SET_UNRELIABLE_SEND_TX_HDL:
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

uint16_t mesh_time_client_init(mesh_time_client_t *p_client, uint8_t element_offset)
{
    if (NULL == p_client
        || NULL == p_client->settings.p_callbacks
        || NULL == p_client->settings.p_callbacks->time_status_cb
        || NULL == p_client->settings.p_callbacks->zone_status_cb
        || NULL == p_client->settings.p_callbacks->dlt_status_cb
        || NULL == p_client->settings.p_callbacks->role_status_cb
        || NULL == p_client->settings.p_callbacks->ack_transaction_status_cb
        || TSCNS_TIME_CLIENT_INSTANCE_COUNT_MAX <= p_client->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    endian_judge();

    mesh_time_client_register_info.p_args         = p_client;
    mesh_time_client_register_info.element_offset = element_offset;
    
    return mesh_model_register(&mesh_time_client_register_info, &p_client->model_lid);
}

uint16_t mesh_time_client_set(mesh_time_client_t * p_client, const mesh_time_set_params_t * p_params)
{
    mesh_time_set_msg_pkt_t set;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = TSCNS_TIME_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * TSCNS_TIME_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(TSCNS_TIME_OPCODE_STATUS),
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

            uint8_t msg_length = message_set_time_packet_create(&set, p_params);

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, TSCNS_TIME_OPCODE_SET, tx_hdl, (uint8_t *)&set, msg_length);
#else
            message_create(&model_msg_send, p_client->model_lid, TSCNS_TIME_OPCODE_SET, tx_hdl, (uint8_t *)&set, msg_length);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t mesh_time_client_get(mesh_time_client_t * p_client)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = TSCNS_TIME_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * TSCNS_TIME_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(TSCNS_TIME_OPCODE_STATUS),
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
            return model_send_unicast_dev(p_client, TSCNS_TIME_OPCODE_GET, tx_hdl, NULL, 0);
#else
            message_create(&model_msg_send, p_client->model_lid, TSCNS_TIME_OPCODE_GET, tx_hdl, NULL, 0);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t mesh_time_client_zone_set(mesh_time_client_t * p_client, const mesh_time_zone_set_params_t * p_params)
{
    mesh_time_zone_set_msg_pkt_t set;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = TSCNS_TIME_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * TSCNS_TIME_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(TSCNS_TIME_ZONE_OPCODE_STATUS),
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
            uint8_t msg_length = message_set_zone_packet_create(&set, p_params);

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, TSCNS_TIME_ZONE_OPCODE_SET, tx_hdl, (uint8_t *)&set, msg_length);
#else
            message_create(&model_msg_send, p_client->model_lid, TSCNS_TIME_ZONE_OPCODE_SET, tx_hdl, (uint8_t *)&set, msg_length);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t mesh_time_client_zone_get(mesh_time_client_t * p_client)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = TSCNS_TIME_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * TSCNS_TIME_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(TSCNS_TIME_ZONE_OPCODE_STATUS),
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
            return model_send_unicast_dev(p_client, TSCNS_TIME_ZONE_OPCODE_GET, tx_hdl, NULL, 0);
#else
            message_create(&model_msg_send, p_client->model_lid, TSCNS_TIME_ZONE_OPCODE_GET, tx_hdl, NULL, 0);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t mesh_time_client_tai2utc_dlt_set(mesh_time_client_t * p_client, const mesh_tai2utc_dlt_set_params_t * p_params)
{
    mesh_tai2utc_dlt_set_msg_pkt_t set;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = TSCNS_TIME_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * TSCNS_TIME_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(TSCNS_TIME_TAI2UTC_DLT_OPCODE_STATUS),
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

            uint8_t msg_length = message_set_tai2utc_dlt_packet_create(&set, p_params);

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, TSCNS_TIME_TAI2UTC_DLT_OPCODE_SET, tx_hdl, (uint8_t *)&set, msg_length);
#else
            message_create(&model_msg_send, p_client->model_lid, TSCNS_TIME_TAI2UTC_DLT_OPCODE_SET, tx_hdl, (uint8_t *)&set, msg_length);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t mesh_time_client_tai2utc_dlt_get(mesh_time_client_t * p_client)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = TSCNS_TIME_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * TSCNS_TIME_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(TSCNS_TIME_TAI2UTC_DLT_OPCODE_STATUS),
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
            return model_send_unicast_dev(p_client, TSCNS_TIME_TAI2UTC_DLT_OPCODE_GET, tx_hdl, NULL, 0);
#else
            message_create(&model_msg_send, p_client->model_lid, TSCNS_TIME_TAI2UTC_DLT_OPCODE_GET, tx_hdl, NULL, 0);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t mesh_time_client_role_set(mesh_time_client_t * p_client, const uint8_t * p_params)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = TSCNS_TIME_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * TSCNS_TIME_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(TSCNS_TIME_ROLE_OPCODE_STATUS),
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

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, TSCNS_TIME_ROLE_OPCODE_SET, tx_hdl, (uint8_t *)p_params, TSCNS_TIME_ROLE_SET_MINLEN);
#else
            message_create(&model_msg_send, p_client->model_lid, TSCNS_TIME_ROLE_OPCODE_SET, tx_hdl, (uint8_t *)p_params, TSCNS_TIME_ROLE_SET_MINLEN);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t mesh_time_client_role_get(mesh_time_client_t * p_client)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = TSCNS_TIME_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * TSCNS_TIME_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(TSCNS_TIME_ROLE_OPCODE_STATUS),
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
            return model_send_unicast_dev(p_client, TSCNS_TIME_ROLE_OPCODE_GET, tx_hdl, NULL, 0);
#else
            message_create(&model_msg_send, p_client->model_lid, TSCNS_TIME_ROLE_OPCODE_GET, tx_hdl, NULL, 0);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t mesh_time_client_setget_cancel(mesh_time_client_t * p_client)
{
    if (p_client == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    
    return mesh_model_reliable_trans_cancel(p_client->model_lid);
}

