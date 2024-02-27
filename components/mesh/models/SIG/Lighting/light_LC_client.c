/**
 *****************************************************************************************
 *
 * @file light_lc_client.c
 *
 * @brief Light LC Client API Implementation.
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
#include "light_LC_message.h"
#include "light_LC_client.h"
#include "common_utils.h"
#include "grx_sys.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
 
static void lc_mode_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void lc_loo_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void lc_property_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);


static void light_lc_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void light_lc_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
static const uint16_t light_lc_client_opcode_list[] =
{
    LIGHT_LC_MODE_OPCODE_STATUS,
    LIGHT_LC_OM_OPCODE_STATUS,
    LIGHT_LC_LOO_OPCODE_STATUS,
    LIGHT_LC_PROPERTY_OPCODE_STATUS,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {LIGHT_LC_MODE_OPCODE_STATUS, lc_mode_status_handle},
    {LIGHT_LC_OM_OPCODE_STATUS, lc_mode_status_handle},
    {LIGHT_LC_LOO_OPCODE_STATUS, lc_loo_status_handle},
    {LIGHT_LC_PROPERTY_OPCODE_STATUS, lc_property_status_handle},
};

static const mesh_model_cb_t light_lc_client_msg_cb = {
    .cb_rx             = light_lc_client_rx_cb,
    .cb_sent           = light_lc_client_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t light_lc_client_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_LIGHTC_LC),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)light_lc_client_opcode_list,
    .num_opcodes = sizeof(light_lc_client_opcode_list) / sizeof(uint16_t),
    .p_cb = &light_lc_client_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void lc_mode_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_lc_client_t * p_client = (light_lc_client_t *) p_args;

    if ((p_rx_msg->msg_len == LIGHT_LC_MODE_STATUS_MINLEN) ||(p_rx_msg->msg_len == LIGHT_LC_OM_STATUS_MINLEN))
    {

        if (p_rx_msg->opcode.company_opcode == LIGHT_LC_MODE_OPCODE_STATUS)
        {
            light_lc_mode_status_params_t in_data = {0};
            light_lc_mode_status_msg_pkt_t * p_msg_params_packed = (light_lc_mode_status_msg_pkt_t *) p_rx_msg->msg;

            in_data.mode = p_msg_params_packed->mode;
            p_client->settings.p_callbacks->lc_mode_status_cb(p_client, p_rx_msg, &in_data);
        }
        else if (p_rx_msg->opcode.company_opcode == LIGHT_LC_OM_OPCODE_STATUS)
        {
            light_lc_om_status_params_t in_data = {0};
            light_lc_om_status_msg_pkt_t * p_msg_params_packed = (light_lc_om_status_msg_pkt_t *) p_rx_msg->msg;

            in_data.mode = p_msg_params_packed->mode;
            p_client->settings.p_callbacks->lc_om_status_cb(p_client, p_rx_msg, &in_data);
        }
    }
}

static void lc_loo_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_lc_client_t * p_client = (light_lc_client_t *) p_args;
    light_lc_loo_status_params_t in_data = {0, 0, 0};

    if ((p_rx_msg->msg_len == LIGHT_LC_LOO_STATUS_MINLEN) || (p_rx_msg->msg_len == LIGHT_LC_LOO_STATUS_MAXLEN))
    {
        light_lc_loo_status_msg_pkt_t * p_msg_params_packed = (light_lc_loo_status_msg_pkt_t *) p_rx_msg->msg;

        in_data.present_loo = p_msg_params_packed->present_loo;
        if (p_rx_msg->msg_len == LIGHT_LC_LOO_STATUS_MINLEN)
        {
            in_data.target_loo = p_msg_params_packed->present_loo;
        }
        else
        {
            in_data.target_loo = p_msg_params_packed->target_loo;
            in_data.remaining_time_ms = model_transition_time_decode(p_msg_params_packed->remaining_time);
        }
        p_client->settings.p_callbacks->lc_loo_status_cb(p_client, p_rx_msg, &in_data);
    }
}

static void lc_property_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_lc_client_t * p_client = (light_lc_client_t *) p_args;
    light_lc_property_status_params_t in_data = {0};

    if (p_rx_msg->msg_len >= 2)
    {
        light_lc_property_status_msg_pkt_t * p_msg_params_packed = (light_lc_property_status_msg_pkt_t *) p_rx_msg->msg;
        in_data.property_id = gx_read16p((void *)&p_msg_params_packed->property_id);
        in_data.value_length = p_rx_msg->msg_len-2;
        in_data.property_value = p_msg_params_packed->property_value;

        p_client->settings.p_callbacks->lc_property_status_cb(p_client, p_rx_msg, &in_data);
    }
}

static uint8_t message_set_packet_create(light_lc_loo_set_msg_pkt_t *p_set, const light_lc_loo_set_params_t * p_params,
                                      const model_transition_t * p_transition)
{
    APP_LOG_INFO("Sending msg: SET LC ONOFF TO %d", p_params->loo);
    
    p_set->loo = p_params->loo;
    p_set->tid = p_params->tid;

    if (p_transition != NULL)
    {
        p_set->transition_time = model_transition_time_encode(p_transition->transition_time_ms);
        p_set->delay = model_delay_encode(p_transition->delay_ms);
        return LIGHT_LC_LOO_SET_MAXLEN;
    }
    else
    {
        return LIGHT_LC_LOO_SET_MINLEN;
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

static uint16_t model_send_unicast_dev(light_lc_client_t *p_client, uint16_t opcode, uint8_t tx_hdl, uint8_t *p_buffer, uint16_t length)
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
    p_msg_tx->model_lid              = model_lid;
    p_msg_tx->opcode                = opcode;
    p_msg_tx->tx_hdl                = tx_hdl;   
    p_msg_tx->p_data_send           = p_buffer;
    p_msg_tx->data_send_len         = length;
    p_msg_tx->dst                   = MESH_INVALID_ADDR;
    p_msg_tx->appkey_index         = MESH_INVALID_KEY_INDEX;
}

#endif

static void light_lc_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<light_lc_client_register_info.num_opcodes; i++)
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

static void light_lc_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args)
{
    light_lc_client_t * p_client = (light_lc_client_t *) p_args;
    
    switch(p_sent->tx_hdl - p_client->model_instance_index * LIGHT_LC_CLIENT_TX_HDL_TOTAL)
    {
        case LIGHT_LC_CLIENT_GET_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent get message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send get message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case LIGHT_LC_CLIENT_SET_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent set message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send set message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case LIGHT_LC_CLIENT_SET_UNRELIABLE_SEND_TX_HDL:
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

uint16_t light_lc_client_init(light_lc_client_t *p_client, uint8_t element_offset)
{
    if (NULL == p_client
        || NULL == p_client->settings.p_callbacks
        || NULL == p_client->settings.p_callbacks->lc_mode_status_cb
        || NULL == p_client->settings.p_callbacks->lc_om_status_cb
        || NULL == p_client->settings.p_callbacks->lc_loo_status_cb
        || NULL == p_client->settings.p_callbacks->lc_property_status_cb
        || NULL == p_client->settings.p_callbacks->ack_transaction_status_cb
        || LIGHT_LC_CLIENT_INSTANCE_COUNT_MAX <= p_client->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    light_lc_client_register_info.p_args         = p_client;
    light_lc_client_register_info.element_offset = element_offset;
    
    return mesh_model_register(&light_lc_client_register_info, &p_client->model_lid);
}

uint16_t light_lc_client_mode_set(light_lc_client_t * p_client, const light_lc_mode_set_params_t * p_params)
{
    light_lc_mode_set_msg_pkt_t set;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_LC_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_LC_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_LC_MODE_OPCODE_STATUS),
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
            set.mode = p_params->mode;
#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, LIGHT_LC_MODE_OPCODE_SET, tx_hdl, (uint8_t *)&set, LIGHT_LC_MODE_SET_MINLEN);
#else
            message_create(&model_msg_send, p_client->model_lid,
                                           LIGHT_LC_MODE_OPCODE_SET,
                                           tx_hdl, (uint8_t *)&set, LIGHT_LC_MODE_SET_MINLEN);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t light_lc_client_mode_set_unack(light_lc_client_t * p_client, const light_lc_mode_set_params_t * p_params)
{
    light_lc_mode_set_msg_pkt_t set_un;
    uint8_t tx_hdl = LIGHT_LC_CLIENT_SET_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * LIGHT_LC_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
#endif
    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    set_un.mode = p_params->mode;
#ifdef MESH_MODEL_BQB_TEST
    return model_send_unicast_dev(p_client, LIGHT_LC_MODE_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, LIGHT_LC_MODE_SET_MINLEN);
#else
    message_create(&model_msg_send, p_client->model_lid,
                   LIGHT_LC_MODE_OPCODE_SET_UNACKNOWLEDGED, 
                   tx_hdl, (uint8_t *)&set_un, LIGHT_LC_MODE_SET_MINLEN);

    return mesh_model_publish(&model_msg_send, NULL);
#endif
}

uint16_t light_lc_client_mode_get(light_lc_client_t * p_client)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_LC_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_LC_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_LC_MODE_OPCODE_STATUS),
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
            return model_send_unicast_dev(p_client, LIGHT_LC_MODE_OPCODE_GET, tx_hdl, NULL, LIGHT_LC_MODE_GET_MINLEN);
#else
            message_create(&model_msg_send, p_client->model_lid, 
                           LIGHT_LC_MODE_OPCODE_GET, 
                           tx_hdl, NULL, LIGHT_LC_MODE_GET_MINLEN);
            
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t light_lc_client_om_set(light_lc_client_t * p_client, const light_lc_om_set_params_t * p_params)
{
    light_lc_om_set_msg_pkt_t set;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_LC_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_LC_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_LC_OM_OPCODE_STATUS),
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
            set.mode = p_params->mode;

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, LIGHT_LC_OM_OPCODE_SET, tx_hdl, (uint8_t *)&set, LIGHT_LC_OM_SET_MINLEN);
#else
            message_create(&model_msg_send, p_client->model_lid,
                                           LIGHT_LC_OM_OPCODE_SET,
                                           tx_hdl, (uint8_t *)&set, LIGHT_LC_OM_SET_MINLEN);

            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t light_lc_client_om_set_unack(light_lc_client_t * p_client, const light_lc_om_set_params_t * p_params)
{
    light_lc_om_set_msg_pkt_t set_un;
    uint8_t tx_hdl = LIGHT_LC_CLIENT_SET_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * LIGHT_LC_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    set_un.mode = p_params->mode;
#ifdef MESH_MODEL_BQB_TEST
    return model_send_unicast_dev(p_client, LIGHT_LC_OM_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, LIGHT_LC_OM_SET_MINLEN);
#else
    message_create(&model_msg_send, p_client->model_lid,
                   LIGHT_LC_OM_OPCODE_SET_UNACKNOWLEDGED, 
                   tx_hdl, (uint8_t *)&set_un, LIGHT_LC_OM_SET_MINLEN);

    return mesh_model_publish(&model_msg_send, NULL);
#endif
}

uint16_t light_lc_client_om_get(light_lc_client_t * p_client)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_LC_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_LC_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_LC_OM_OPCODE_STATUS),
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
            return model_send_unicast_dev(p_client, LIGHT_LC_OM_OPCODE_GET, tx_hdl, NULL, LIGHT_LC_OM_GET_MINLEN);
#else
            message_create(&model_msg_send, p_client->model_lid, 
                           LIGHT_LC_OM_OPCODE_GET, 
                           tx_hdl, NULL, LIGHT_LC_OM_GET_MINLEN);
            
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t light_lc_loo_client_set(light_lc_client_t * p_client, const light_lc_loo_set_params_t * p_params, const model_transition_t * p_transition)
{
    light_lc_loo_set_msg_pkt_t set;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_LC_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_LC_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_LC_LOO_OPCODE_STATUS),
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
            uint8_t msg_length = message_set_packet_create(&set, p_params, p_transition);
#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, LIGHT_LC_LOO_OPCODE_SET, tx_hdl, (uint8_t *)&set, msg_length);
#else
            message_create(&model_msg_send, p_client->model_lid, LIGHT_LC_LOO_OPCODE_SET, tx_hdl, (uint8_t *)&set, msg_length);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}


uint16_t light_lc_loo_client_set_unack(light_lc_client_t * p_client, const light_lc_loo_set_params_t * p_params, const model_transition_t * p_transition)
{
    light_lc_loo_set_msg_pkt_t set_un;
    uint8_t tx_hdl = LIGHT_LC_CLIENT_SET_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * LIGHT_LC_CLIENT_TX_HDL_TOTAL;
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
    uint8_t msg_length = message_set_packet_create(&set_un, p_params, p_transition);

#ifdef MESH_MODEL_BQB_TEST
    return model_send_unicast_dev(p_client, LIGHT_LC_LOO_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, msg_length);
#else
    message_create(&model_msg_send, p_client->model_lid, LIGHT_LC_LOO_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)&set_un, msg_length);
    return mesh_model_publish(&model_msg_send, NULL);
#endif
}


uint16_t light_lc_loo_client_get(light_lc_client_t * p_client)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_LC_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_LC_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_LC_LOO_OPCODE_STATUS),
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
            return model_send_unicast_dev(p_client, LIGHT_LC_LOO_OPCODE_GET, tx_hdl, NULL, 0);
#else
            message_create(&model_msg_send, p_client->model_lid, 
                           LIGHT_LC_LOO_OPCODE_GET, 
                           tx_hdl, NULL, 0);
            
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t light_lc_client_property_set(light_lc_client_t * p_client, const light_lc_property_set_params_t * p_params)
{
    light_lc_property_set_msg_pkt_t *set = NULL;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_LC_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_LC_CLIENT_TX_HDL_TOTAL;
    uint16_t Err_code = MESH_ERROR_NO_ERROR;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_LC_PROPERTY_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    set = (light_lc_property_set_msg_pkt_t *)sys_malloc(p_params->value_length + 2);

    if (set != NULL)
    {
        if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
        {
            if (reliable_trans_state)
            {
                return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
            }
            else
            {
                gx_write16p((const void *)&(set->property_id), p_params->property_id);
                memcpy(set->property_value, p_params->property_value, p_params->value_length);

#ifdef MESH_MODEL_BQB_TEST
                Err_code = model_send_unicast_dev(p_client, LIGHT_LC_PROPERTY_OPCODE_SET, tx_hdl, (uint8_t *)set, p_params->value_length + 2);
#else
                message_create(&model_msg_send, p_client->model_lid,
                                               LIGHT_LC_PROPERTY_OPCODE_SET,
                                               tx_hdl, (uint8_t *)set, p_params->value_length + 2);

                Err_code = mesh_model_publish(&model_msg_send, &reliable_info);
#endif
            }
        }
        else
        {
            Err_code = MESH_ERROR_SDK_INVALID_PARAM; 
        }

        sys_free(set);
        set = NULL;
    }
    else
    {
        Err_code = MESH_ERROR_INSUFFICIENT_RESOURCES;
    }

    return Err_code;
}

uint16_t light_lc_client_property_set_unack(light_lc_client_t * p_client, const light_lc_property_set_params_t * p_params)
{
    light_lc_property_set_msg_pkt_t *set_un = NULL;
    uint8_t tx_hdl = LIGHT_LC_CLIENT_SET_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * LIGHT_LC_CLIENT_TX_HDL_TOTAL;
    uint16_t Err_code = MESH_ERROR_NO_ERROR;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    set_un = (light_lc_property_set_msg_pkt_t *)sys_malloc(p_params->value_length + 2);
    if (set_un != NULL)
    {
        gx_write16p((const void *)&(set_un->property_id), p_params->property_id);
        memcpy(set_un->property_value, p_params->property_value, p_params->value_length);

#ifdef MESH_MODEL_BQB_TEST
        Err_code = model_send_unicast_dev(p_client, LIGHT_LC_PROPERTY_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)set_un, p_params->value_length + 2);
#else
        message_create(&model_msg_send, p_client->model_lid,
                       LIGHT_LC_PROPERTY_OPCODE_SET_UNACKNOWLEDGED,
                       tx_hdl, (uint8_t *)set_un, p_params->value_length + 2);

        Err_code = mesh_model_publish(&model_msg_send, NULL);
#endif
        sys_free(set_un);
        set_un = NULL;
    }
    else
    {
        Err_code = MESH_ERROR_INSUFFICIENT_RESOURCES;
    }

    return Err_code;
}

uint16_t light_lc_client_property_get(light_lc_client_t * p_client, const light_lc_property_get_params_t * p_params)
{
    light_lc_property_get_msg_pkt_t get;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = LIGHT_LC_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * LIGHT_LC_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_LC_PROPERTY_OPCODE_STATUS),
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
            gx_write16p((const void *)&(get.property_id), p_params->property_id);
#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, LIGHT_LC_PROPERTY_OPCODE_GET, tx_hdl, (uint8_t *)&get, LIGHT_LC_PROPERTY_GET_MINLEN);
#else
            message_create(&model_msg_send, p_client->model_lid, 
                           LIGHT_LC_PROPERTY_OPCODE_GET, 
                           tx_hdl, (uint8_t *)&get, LIGHT_LC_PROPERTY_GET_MINLEN);
            
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t light_lc_client_setget_cancel(light_lc_client_t * p_client)
{
    if (p_client == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    
    return mesh_model_reliable_trans_cancel(p_client->model_lid);
}

