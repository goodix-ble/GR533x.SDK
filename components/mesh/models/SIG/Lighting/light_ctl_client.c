/**
 *****************************************************************************************
 *
 * @file light_ctl_client.c
 *
 * @brief Light CTL Client API Implementation.
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
#include "light_ctl_message.h"
#include "light_ctl_client.h"
#include "common_utils.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void light_ctl_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void light_temp_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void light_dft_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void light_temp_range_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void light_ctl_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void light_ctl_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
static const uint16_t light_ctl_client_opcode_list[] =
{
    LIGHT_CTL_OPCODE_STATUS,
    LIGHT_CTL_TEMP_RANGE_OPCODE_STATUS,
    LIGHT_CTL_TEMP_OPCODE_STATUS,
    LIGHT_CTL_DFT_OPCODE_STATUS,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {LIGHT_CTL_OPCODE_STATUS, light_ctl_status_handle},
    {LIGHT_CTL_TEMP_RANGE_OPCODE_STATUS, light_temp_range_status_handle},
    {LIGHT_CTL_TEMP_OPCODE_STATUS, light_temp_status_handle},
    {LIGHT_CTL_DFT_OPCODE_STATUS, light_dft_status_handle},
};

static const mesh_model_cb_t light_ctl_client_msg_cb = {
    .cb_rx             = light_ctl_client_rx_cb,
    .cb_sent           = light_ctl_client_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t light_ctl_client_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_LIGHTC_CTL),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)light_ctl_client_opcode_list,
    .num_opcodes = sizeof(light_ctl_client_opcode_list) / sizeof(uint16_t),
    .p_cb = &light_ctl_client_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static void light_ctl_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_ctl_client_t * p_client = (light_ctl_client_t *) p_args;
    light_ctl_status_params_t in_data = {0};

    APP_LOG_INFO("[%s] enter: receive status length = %d", __func__, p_rx_msg->msg_len);

    if (p_rx_msg->msg_len == LIGHT_CTL_STATUS_MINLEN || p_rx_msg->msg_len == LIGHT_CTL_STATUS_MAXLEN)
    {
        light_ctl_status_msg_pkt_t * p_msg_params_packed = (light_ctl_status_msg_pkt_t *) p_rx_msg->msg;

        if (p_rx_msg->msg_len == LIGHT_CTL_STATUS_MINLEN)
        {
            in_data.present_ctl_ln = gx_read16p((const void *)&p_msg_params_packed->present_ctl_ln);
            in_data.present_ctl_temp = gx_read16p((const void *)&p_msg_params_packed->present_ctl_temp);
            in_data.remaining_time_ms = 0;
        }
        else
        {
            in_data.present_ctl_ln = gx_read16p((const void *)&p_msg_params_packed->present_ctl_ln);
            in_data.present_ctl_temp = gx_read16p((const void *)&p_msg_params_packed->present_ctl_temp);
            in_data.target_ctl_ln = gx_read16p((const void *)&p_msg_params_packed->target_ctl_ln);
            in_data.target_ctl_temp = gx_read16p((const void *)&p_msg_params_packed->target_ctl_temp);
            in_data.remaining_time_ms = model_transition_time_decode(p_msg_params_packed->remaining_time);
        }

        p_client->settings.p_callbacks->ctl_ln_status_cb(p_client, p_rx_msg, &in_data);
    }
}

static void light_temp_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_ctl_client_t * p_client = (light_ctl_client_t *) p_args;
    light_ctl_temp_status_params_t in_data = {0};

    APP_LOG_INFO("[%s] enter: receive status length = %d", __func__, p_rx_msg->msg_len);
    if (p_rx_msg->msg_len == LIGHT_CTL_TEMP_STATUS_MINLEN || p_rx_msg->msg_len == LIGHT_CTL_TEMP_STATUS_MAXLEN)
    {
        light_ctl_temp_status_msg_pkt_t * p_msg_params_packed = (light_ctl_temp_status_msg_pkt_t *) p_rx_msg->msg;

        if (p_rx_msg->msg_len == LIGHT_CTL_TEMP_STATUS_MINLEN)
        {
            in_data.present_ctl_temp = gx_read16p((const void *)&p_msg_params_packed->present_ctl_temp);
            in_data.present_ctl_dlt_uv = gx_read16p((const void *)&p_msg_params_packed->present_ctl_dlt_uv);
            in_data.remaining_time_ms = 0;
        }
        else
        {
            in_data.present_ctl_temp = gx_read16p((const void *)&p_msg_params_packed->present_ctl_temp);
            in_data.present_ctl_dlt_uv = gx_read16p((const void *)&p_msg_params_packed->present_ctl_dlt_uv);
            in_data.target_ctl_temp = gx_read16p((const void *)&p_msg_params_packed->target_ctl_temp);
            in_data.target_ctl_dlt_uv = gx_read16p((const void *)&p_msg_params_packed->target_ctl_dlt_uv);
            in_data.remaining_time_ms = model_transition_time_decode(p_msg_params_packed->remaining_time);
        }

        p_client->settings.p_callbacks->ctl_temp_status_cb(p_client, p_rx_msg, &in_data);
    }
}

static void light_dft_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_ctl_client_t * p_client = (light_ctl_client_t *) p_args;
    light_ctl_dft_status_params_t in_data = {0};

    APP_LOG_INFO("[%s] enter: receive status length = %d", __func__, p_rx_msg->msg_len);

    if (p_rx_msg->msg_len == LIGHT_CTL_DFT_STATUS_LEN)
    {
        light_ctl_dft_status_msg_pkt_t * p_msg_params_packed = (light_ctl_dft_status_msg_pkt_t *) p_rx_msg->msg;
        in_data.ln = gx_read16p((const void *)&p_msg_params_packed->ln );
        in_data.temp = gx_read16p((const void *)&p_msg_params_packed->temp);
        in_data.dlt_uv = gx_read16p((const void *)&p_msg_params_packed->dlt_uv);

        p_client->settings.p_callbacks->ctl_dft_status_cb(p_client, p_rx_msg, &in_data);
    }
}

static void light_temp_range_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_ctl_client_t * p_client = (light_ctl_client_t *) p_args;
    light_ctl_range_status_params_t in_data = {0};

    APP_LOG_INFO("[%s] enter: receive status length = %d", __func__, p_rx_msg->msg_len);

    if (p_rx_msg->msg_len == LIGHT_CTL_RANGE_STATUS_LEN)
    {
        light_ctl_range_status_msg_pkt_t * p_msg_params_packed = (light_ctl_range_status_msg_pkt_t *) p_rx_msg->msg;
        in_data.range_max = gx_read16p((const void *)&p_msg_params_packed->range_max);
        in_data.range_min = gx_read16p((const void *)&p_msg_params_packed->range_min);
        in_data.status_code = p_msg_params_packed->status_code;

        p_client->settings.p_callbacks->ctl_range_status_cb(p_client, p_rx_msg, &in_data);
    }
}


static uint8_t message_set_ctl_packet_create(light_ctl_set_msg_pkt_t *p_set, const light_ctl_set_params_t * p_params,
                                      const model_transition_t * p_transition)
{
    APP_LOG_INFO("[%s] Sending msg: SET CTL, lightness: %d temperature:%d delta_uv:%d", __func__, p_params->ctl_ln, p_params->ctl_temp, p_params->ctl_dlt_uv);

    gx_write16p((const void *)&(p_set->ctl_ln), p_params->ctl_ln);
    gx_write16p((const void *)&(p_set->ctl_temp), p_params->ctl_temp);
    gx_write16p((const void *)&(p_set->ctl_dlt_uv), p_params->ctl_dlt_uv);
    p_set->tid = p_params->tid;

    if (p_transition != NULL)
    {
        p_set->transition_time = model_transition_time_encode(p_transition->transition_time_ms);
        p_set->delay = model_delay_encode(p_transition->delay_ms);
        return LIGHT_CTL_SET_MAXLEN;
    }
    else
    {
        return LIGHT_CTL_SET_MINLEN;
    }
}

static uint8_t message_set_temp_packet_create(light_ctl_temp_set_msg_pkt_t *p_set, const light_ctl_temp_set_params_t * p_params,
                                      const model_transition_t * p_transition)
{
    APP_LOG_INFO("[%s] Sending msg: SET CTL, temperature:%d delta_uv:%d", __func__, p_params->ctl_temp, p_params->ctl_dlt_uv);

    gx_write16p((const void *)&(p_set->ctl_temp), p_params->ctl_temp);
    gx_write16p((const void *)&(p_set->ctl_dlt_uv), p_params->ctl_dlt_uv);
    p_set->tid = p_params->tid;

    if (p_transition != NULL)
    {
        p_set->transition_time = model_transition_time_encode(p_transition->transition_time_ms);
        p_set->delay = model_delay_encode(p_transition->delay_ms);
        return LIGHT_CTL_TEMP_SET_MAXLEN;
    }
    else
    {
        return LIGHT_CTL_TEMP_SET_MINLEN;
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

static uint16_t model_send_unicast_dev(light_ctl_client_t *p_client, uint16_t opcode, uint8_t tx_hdl, uint8_t *p_buffer, uint16_t length)
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

static void light_ctl_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;
    uint8_t index = 0;
    switch(company_opcode)
    {
        case LIGHT_CTL_OPCODE_STATUS:
            index = 0;
            break;
        case LIGHT_CTL_TEMP_RANGE_OPCODE_STATUS:
            index = 1;
            break;
        case LIGHT_CTL_TEMP_OPCODE_STATUS:
            index = 2;
            break;
        case LIGHT_CTL_DFT_OPCODE_STATUS:
            index = 3;
            break;
        default:
            break;
    }

    mesh_opcode_handler_cb_t handler = m_opcode_handlers[index].handler;

    if (NULL != handler)
    {
        handler(p_model_msg, p_args);
    }
}

static void light_ctl_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    light_ctl_client_t * p_client = (light_ctl_client_t *) p_args;

    switch(p_sent->tx_hdl - p_client->model_instance_index * LIGHT_CTL_CLIENT_TX_HDL_TOTAL)
    {
        case LIGHT_CTL_CLIENT_GET_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent get message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send get message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case LIGHT_CTL_CLIENT_SET_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent set message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send set message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case LIGHT_CTL_CLIENT_SET_UNRELIABLE_SEND_TX_HDL:
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

uint16_t light_ctl_client_init(light_ctl_client_t *p_client, uint8_t element_offset)
{
    if (NULL == p_client
        || NULL == p_client->settings.p_callbacks
        || NULL == p_client->settings.p_callbacks->ctl_ln_status_cb
        || NULL == p_client->settings.p_callbacks->ctl_temp_status_cb
        || NULL == p_client->settings.p_callbacks->ctl_dft_status_cb
        || NULL == p_client->settings.p_callbacks->ctl_range_status_cb
        || NULL == p_client->settings.p_callbacks->ack_transaction_status_cb
        || LIGHT_CTL_CLIENT_INSTANCE_COUNT_MAX <= p_client->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    light_ctl_client_register_info.p_args         = p_client;
    light_ctl_client_register_info.element_offset = element_offset;
    
    return mesh_model_register(&light_ctl_client_register_info, &p_client->model_lid);
}

uint16_t light_ctl_client_set(light_ctl_client_t * p_client, const light_ctl_set_params_t * p_params,
                                  const model_transition_t * p_transition)
{
    light_ctl_set_msg_pkt_t set;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_CTL_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_CTL_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_CTL_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (p_transition != NULL &&
        (p_transition->transition_time_ms > TRANSITION_TIME_MAX_MS ||
         p_transition->delay_ms > DELAY_TIME_MAX_MS))
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
            uint8_t msg_length = message_set_ctl_packet_create(&set, p_params, p_transition);
#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, LIGHT_CTL_OPCODE_SET, tx_hdl, (uint8_t *)&set, msg_length);
#else
            message_create(&model_msg_send, p_client->model_lid, LIGHT_CTL_OPCODE_SET, tx_hdl, (uint8_t *)&set, msg_length);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t light_ctl_client_set_unack(light_ctl_client_t * p_client, const light_ctl_set_params_t * p_params,
                                        const model_transition_t * p_transition)
{
    light_ctl_set_msg_pkt_t set_un;
    uint8_t tx_hdl = LIGHT_CTL_CLIENT_SET_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * LIGHT_CTL_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (p_transition != NULL &&
        (p_transition->transition_time_ms > TRANSITION_TIME_MAX_MS ||
         p_transition->delay_ms > DELAY_TIME_MAX_MS))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    uint8_t msg_length = message_set_ctl_packet_create(&set_un, p_params, p_transition);
#ifdef MESH_MODEL_BQB_TEST
    return model_send_unicast_dev(p_client, LIGHT_CTL_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, msg_length);
#else
    message_create(&model_msg_send, p_client->model_lid, LIGHT_CTL_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, msg_length);
    return mesh_model_publish(&model_msg_send, NULL);
#endif
}

uint16_t light_ctl_client_get(light_ctl_client_t * p_client)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_CTL_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_CTL_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_CTL_OPCODE_STATUS),
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
            return model_send_unicast_dev(p_client, LIGHT_CTL_OPCODE_GET, tx_hdl, NULL, 0);
#else
            message_create(&model_msg_send, p_client->model_lid, LIGHT_CTL_OPCODE_GET, tx_hdl, NULL, 0);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t light_ctl_temp_client_set(light_ctl_client_t * p_client, const light_ctl_temp_set_params_t * p_params,
                                  const model_transition_t * p_transition)
{
    light_ctl_temp_set_msg_pkt_t set;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_CTL_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_CTL_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_CTL_TEMP_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (p_transition != NULL &&
        (p_transition->transition_time_ms > TRANSITION_TIME_MAX_MS ||
         p_transition->delay_ms > DELAY_TIME_MAX_MS))
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
            uint8_t msg_length = message_set_temp_packet_create(&set, p_params, p_transition);
#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, LIGHT_CTL_TEMP_OPCODE_SET, tx_hdl, (uint8_t *)&set, msg_length);
#else
            message_create(&model_msg_send, p_client->model_lid, LIGHT_CTL_TEMP_OPCODE_SET, tx_hdl, (uint8_t *)&set, msg_length);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t light_ctl_temp_client_set_unack(light_ctl_client_t * p_client, const light_ctl_temp_set_params_t * p_params,
                                        const model_transition_t * p_transition)
{
    light_ctl_temp_set_msg_pkt_t set_un;
    uint8_t tx_hdl = LIGHT_CTL_CLIENT_SET_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * LIGHT_CTL_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (p_transition != NULL &&
        (p_transition->transition_time_ms > TRANSITION_TIME_MAX_MS ||
         p_transition->delay_ms > DELAY_TIME_MAX_MS))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    uint8_t msg_length = message_set_temp_packet_create(&set_un, p_params, p_transition);
#ifdef MESH_MODEL_BQB_TEST
    return model_send_unicast_dev(p_client, LIGHT_CTL_TEMP_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, msg_length);
#else
    message_create(&model_msg_send, p_client->model_lid, LIGHT_CTL_TEMP_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, msg_length);
    return mesh_model_publish(&model_msg_send, NULL);
#endif
}

uint16_t light_ctl_temp_client_get(light_ctl_client_t * p_client)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_CTL_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_CTL_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_CTL_TEMP_OPCODE_STATUS),
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
            return model_send_unicast_dev(p_client, LIGHT_CTL_TEMP_OPCODE_GET, tx_hdl, NULL, 0);
#else
            message_create(&model_msg_send, p_client->model_lid, LIGHT_CTL_TEMP_OPCODE_GET, tx_hdl, NULL, 0);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}



uint16_t light_ctl_dft_client_set(light_ctl_client_t * p_client, const light_ctl_dft_set_params_t * p_params)
{
    light_ctl_dft_set_msg_pkt_t set;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_CTL_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_CTL_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_CTL_DFT_OPCODE_STATUS),
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
            gx_write16p((const void *)&(set.ln), p_params->ln);
            gx_write16p((const void *)&(set.temp), p_params->temp);
            gx_write16p((const void *)&(set.dlt_uv), p_params->dlt_uv);

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, LIGHT_CTL_DFT_OPCODE_SET, tx_hdl, (uint8_t *)&set, LIGHT_CTL_DFT_SET_LEN);
#else
            message_create(&model_msg_send, p_client->model_lid, LIGHT_CTL_DFT_OPCODE_SET, tx_hdl, (uint8_t *)&set, LIGHT_CTL_DFT_SET_LEN);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}


uint16_t light_ctl_dft_client_set_unack(light_ctl_client_t * p_client, const light_ctl_dft_set_params_t * p_params)
{
    light_ctl_dft_set_msg_pkt_t set_un;
    uint8_t tx_hdl = LIGHT_CTL_CLIENT_SET_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * LIGHT_CTL_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    gx_write16p((const void *)&(set_un.ln), p_params->ln);
    gx_write16p((const void *)&(set_un.temp), p_params->temp);
    gx_write16p((const void *)&(set_un.dlt_uv), p_params->dlt_uv);

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, LIGHT_CTL_DFT_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, LIGHT_CTL_DFT_SET_LEN);
#else
            message_create(&model_msg_send, p_client->model_lid, LIGHT_CTL_DFT_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, LIGHT_CTL_DFT_SET_LEN);
            return mesh_model_publish(&model_msg_send, NULL);
#endif
}


uint16_t light_ctl_dft_client_get(light_ctl_client_t * p_client)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_CTL_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_CTL_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_CTL_DFT_OPCODE_STATUS),
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
            return model_send_unicast_dev(p_client, LIGHT_CTL_DFT_OPCODE_GET, tx_hdl, NULL, 0);
#else
            message_create(&model_msg_send, p_client->model_lid, LIGHT_CTL_DFT_OPCODE_GET, tx_hdl, NULL, 0);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t light_ctl_range_client_set(light_ctl_client_t * p_client, const light_ctl_set_range_params_t * p_params)
{
    light_ctl_set_range_msg_pkt_t set;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_CTL_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_CTL_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_CTL_TEMP_RANGE_OPCODE_STATUS),
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
            gx_write16p((const void *)&(set.range_min), p_params->range_min);
            gx_write16p((const void *)&(set.range_max), p_params->range_max);

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, LIGHT_CTL_TEMP_RANGE_OPCODE_SET, tx_hdl, (uint8_t *)&set, LIGHT_CTL_RANGE_SET_LEN);
#else
            message_create(&model_msg_send, p_client->model_lid, LIGHT_CTL_TEMP_RANGE_OPCODE_SET, tx_hdl, (uint8_t *)&set, LIGHT_CTL_RANGE_SET_LEN);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}


uint16_t light_ctl_range_client_set_unack(light_ctl_client_t * p_client, const light_ctl_set_range_params_t * p_params)
{
    light_ctl_set_range_msg_pkt_t set_un;
    uint8_t tx_hdl = LIGHT_CTL_CLIENT_SET_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * LIGHT_CTL_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    gx_write16p((const void *)&(set_un.range_min), p_params->range_min);
    gx_write16p((const void *)&(set_un.range_max), p_params->range_max);

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, LIGHT_CTL_TEMP_RANGE_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, LIGHT_CTL_RANGE_SET_LEN);
#else
            message_create(&model_msg_send, p_client->model_lid, LIGHT_CTL_TEMP_RANGE_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, LIGHT_CTL_RANGE_SET_LEN);
            return mesh_model_publish(&model_msg_send, NULL);
#endif
}


uint16_t light_ctl_range_client_get(light_ctl_client_t * p_client)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_CTL_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_CTL_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_CTL_TEMP_RANGE_OPCODE_STATUS),
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
            return model_send_unicast_dev(p_client, LIGHT_CTL_TEMP_RANGE_OPCODE_GET, tx_hdl, NULL, 0);
#else
            message_create(&model_msg_send, p_client->model_lid, LIGHT_CTL_TEMP_RANGE_OPCODE_GET, tx_hdl, NULL, 0);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

