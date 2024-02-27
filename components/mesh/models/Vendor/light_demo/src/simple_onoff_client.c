/**
 *****************************************************************************************
 *
 * @file simple_on_off_client.c
 *
 * @brief Simple On Off Client API Implementation.
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
#include "simple_onoff_client.h"
#include "user_periph_setup.h"
#include <string.h>
/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
//static void status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_light_demo_client_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void simple_on_off_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void simple_on_off_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args);

extern check_pkt_loss_param_t client_check_pkt_loss_param;
extern void light_demo_reset_pkt_sent_engine(void);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t simple_on_off_client_opcode_list[] =
{
    LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_CHECK_TRANS_DELAY,
    LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_REPORT_TRANS_DELAY,
    LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_CHECK_PKT_LOSS,
    LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_REPORT_PKT_LOSS,
    LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_CHECK_TOTAL_PKT,
    LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_REPORT_TOTAL_PKT,
    LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_RESET_TOTAL_PKT,
    LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_BEGIN_SYNC_CLOCK,
    LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_REPORT_KEY_EVENT,
    LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_BEGIN_UPGRADE,
    LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_SET_COLOR_DISK,
    LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_SET_DISK_COLOR,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    //{SIMPLE_ONOFF_OPCODE_STATUS, status_handle},
    //light demo opcode
    //{LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_SET_COLOR, handle_light_demo_client_cb},
    //{LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_SET_BACK_ONOFF, handle_light_demo_client_cb},
    {LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_CHECK_TRANS_DELAY, handle_light_demo_client_cb},
    {LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_REPORT_TRANS_DELAY, handle_light_demo_client_cb},
    {LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_CHECK_PKT_LOSS, handle_light_demo_client_cb},
    {LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_REPORT_PKT_LOSS, handle_light_demo_client_cb},
    {LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_CHECK_TOTAL_PKT, handle_light_demo_client_cb},
    {LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_REPORT_TOTAL_PKT, handle_light_demo_client_cb},
    {LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_RESET_TOTAL_PKT, handle_light_demo_client_cb},
    {LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_BEGIN_SYNC_CLOCK, handle_light_demo_client_cb},
    {LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_REPORT_KEY_EVENT, handle_light_demo_client_cb},
    {LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_BEGIN_UPGRADE, handle_light_demo_client_cb},
    {LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_SET_COLOR_DISK, handle_light_demo_client_cb},
    {LIGHT_DEMO_OPCODE_BASE_S_PART|LIGHT_DEMO_OPCODE_SET_DISK_COLOR, handle_light_demo_client_cb},
};

static const mesh_model_cb_t simple_on_off_client_msg_cb = {
    .cb_rx             = simple_on_off_client_rx_cb,
    .cb_sent           = simple_on_off_client_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t simple_on_off_client_register_info = 
{
    .model_id = MESH_MODEL_VENDOR(SIMPLE_ON_OFF_CLIENT_MODEL_ID, SIMPLE_ONOFF_COMPANY_ID),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)simple_on_off_client_opcode_list,
    .num_opcodes = sizeof(simple_on_off_client_opcode_list) / sizeof(uint16_t),
    .p_cb = &simple_on_off_client_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
/*
static void status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    simple_onoff_client_t * p_client = (simple_onoff_client_t *) p_args;

    if (p_rx_msg->msg_len == SIMPLE_ONOFF_STATUS_LEN)
    {
        p_client->settings.p_callbacks->onoff_status_cb(p_client, p_rx_msg, (simple_onoff_status_msg_pkt_t *)p_rx_msg->msg);
    }
}
*/
static void handle_light_demo_client_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    uint16_t opcode = p_rx_msg->opcode.company_opcode & 0xFF;
    simple_onoff_client_t * p_client = (simple_onoff_client_t *) p_args;

    switch(opcode)
    {
        case LIGHT_DEMO_OPCODE_CHECK_TRANS_DELAY:
            p_client->settings.p_callbacks->light_demo_status_cb(p_client, p_rx_msg, (light_demo_set_msg_pkt_t *)p_rx_msg->msg);
            break;
        case LIGHT_DEMO_OPCODE_CHECK_PKT_LOSS:
            p_client->settings.p_callbacks->light_demo_status_cb(p_client, p_rx_msg, (light_demo_set_msg_pkt_t *)p_rx_msg->msg);
            break;
        case LIGHT_DEMO_OPCODE_REPORT_PKT_LOSS:
            p_client->settings.p_callbacks->light_demo_status_cb(p_client, p_rx_msg, (light_demo_set_msg_pkt_t *)p_rx_msg->msg);
            break;
        case LIGHT_DEMO_OPCODE_CHECK_TOTAL_PKT:
            break;
        case LIGHT_DEMO_OPCODE_REPORT_TOTAL_PKT:
            p_client->settings.p_callbacks->light_demo_status_cb(p_client, p_rx_msg, (light_demo_set_msg_pkt_t *)p_rx_msg->msg);
            break;
        case LIGHT_DEMO_OPCODE_RESET_TOTAL_PKT:
            break;
        case LIGHT_DEMO_OPCODE_BEGIN_SYNC_CLOCK:
            p_client->settings.p_callbacks->light_demo_status_cb(p_client, p_rx_msg, (light_demo_set_msg_pkt_t *)p_rx_msg->msg);
            break;
        case LIGHT_DEMO_OPCODE_REPORT_KEY_EVENT:
            p_client->settings.p_callbacks->light_demo_status_cb(p_client, p_rx_msg, (light_demo_set_msg_pkt_t *)p_rx_msg->msg);
            break;
        case LIGHT_DEMO_OPCODE_SET_COLOR_DISK:
            p_client->settings.p_callbacks->light_demo_status_cb(p_client, p_rx_msg, (light_demo_set_msg_pkt_t *)p_rx_msg->msg);
            break;
        default:
            APP_LOG_INFO("Client RX unknow opcode 0x%04X!!!!!", opcode);
            break;
    }
}

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

static void message_send_create(mesh_model_pdu_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
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
    p_msg_tx->friendship_credential = false;
    p_msg_tx->ttl = 0xFF;
}

static uint16_t model_send_unicast_dev(simple_onoff_client_t *p_client, uint16_t dst, uint16_t opcode, uint16_t appkey_index, uint8_t tx_hdl, uint8_t *p_buffer, uint16_t length, bool reliable_send)
{
    mesh_model_pdu_send_info_t model_msg_send;

    message_send_create(&model_msg_send, p_client->model_lid, opcode, tx_hdl, p_buffer, length);

    model_msg_send.dst = dst;
    model_msg_send.appkey_index = MESH_INVALID_KEY_INDEX;

    if (reliable_send)
    {
        bool reliable_trans_state = false;
        mesh_model_reliable_info_t reliable_info =
        {
            .reply_opcode = MESH_ACCESS_OPCODE_SIG((opcode&0xFF) | LIGHT_DEMO_OPCODE_BASE_S_PART),
            .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
            .timeout_ms = p_client->settings.timeout_ms,
        };

        if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
        {
            if (reliable_trans_state)
            {
                return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
            }
            else
            {
                return mesh_model_pdu_send(&model_msg_send, &reliable_info);
            }
        }
        else
        {
            return MESH_ERROR_SDK_INVALID_PARAM; 
        }
    }
    else
    {
        return mesh_model_pdu_send(&model_msg_send, NULL);
    }

}

static void simple_on_off_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    APP_LOG_INFO("Client rx opcode 0x%04X!!!", company_opcode);
    mesh_opcode_handler_cb_t handler = m_opcode_handlers[company_opcode - m_opcode_handlers[0].opcode].handler;

    if (NULL != handler)
    {
        handler(p_model_msg, p_args);
    }
}

static void simple_on_off_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args)
{
    simple_onoff_client_t * p_client = (simple_onoff_client_t *) p_args;
    
    switch(p_sent->tx_hdl - p_client->model_instance_index * SIMPLE_ONOFF_CLIENT_TX_HDL_TOTAL)
    {
        case SIMPLE_ONOFF_CLIENT_GET_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("CLIENT[%d] -- Sent get message!!!", p_client->model_instance_index)
                  : APP_LOG_INFO("CLIENT[%d] -- Failed to send get message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            p_client->tx_hdl_busy = false;
            break;
        case SIMPLE_ONOFF_CLIENT_SET_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("CLIENT[%d] -- Sent set message!!!", p_client->model_instance_index)
                  : APP_LOG_INFO("CLIENT[%d] -- Failed to send set message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            p_client->tx_hdl_busy = false;
            break;
        case SIMPLE_ONOFF_CLIENT_SET_UNRELIABLE_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("CLIENT[%d] -- Sent set(unreliable) message!!!", p_client->model_instance_index)
                  : APP_LOG_INFO("CLIENT[%d] -- Failed to send set(unreliable) message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            p_client->tx_hdl_busy = false;
            break;
        default:
            APP_LOG_INFO("msg has been sent!!!");
            p_client->tx_hdl_busy = false;
            break;
    }
}

static void light_demo_client_timer_cb(void * p_context)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    uint16_t status = MESH_ERROR_NO_ERROR;  
    simple_onoff_client_t * p_client = (simple_onoff_client_t *) p_context;
    light_demo_set_params_t sent_demo_params;

    mesh_timer_clear(&p_client->light_demo_timer.timer_id);

    p_client->light_demo_timer.delay_ms = client_check_pkt_loss_param.delay_ms;

    if (client_check_pkt_loss_param.begin_flag && client_check_pkt_loss_param.store_flag)
    {
        sent_demo_params.light_demo_opcode = LIGHT_DEMO_OPCODE_SEND_TEST_DATA;
        sent_demo_params.buf_len = 2;
        sent_demo_params.buf[0] = client_check_pkt_loss_param.check_sent_pkt_id&0xFF;
        sent_demo_params.buf[1] = (client_check_pkt_loss_param.check_sent_pkt_id>>8)&0xFF;
        status = light_client_demo_set_unack(p_client, (sent_demo_params.buf_len+4), &sent_demo_params, client_check_pkt_loss_param.check_addr);

        APP_LOG_INFO("SEND_TEST_DATA [ %d ] times, to device 0x%04X, status 0x%04X", client_check_pkt_loss_param.check_sent_pkt_id, client_check_pkt_loss_param.check_addr, status);
        client_check_pkt_loss_param.check_sent_pkt_id ++;

        if (client_check_pkt_loss_param.check_sent_pkt_id <= client_check_pkt_loss_param.check_max_pkt_num)
        {
            if (client_check_pkt_loss_param.delay_ms != 0)
            {
                p_client->light_demo_timer.reload = false;
                p_client->light_demo_timer.delay_ms = client_check_pkt_loss_param.delay_ms;

                mesh_timer_set(&(p_client->light_demo_timer));
            }
        }
        else
        {
            light_demo_reset_pkt_sent_engine();
            APP_LOG_INFO("check pkt loss task done !!!!!");
        }
    }
}
/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t simple_onoff_client_init(simple_onoff_client_t *p_client, uint8_t element_offset)
{
    if (NULL == p_client
        || NULL == p_client->settings.p_callbacks
        || NULL == p_client->settings.p_callbacks->onoff_status_cb
        || NULL == p_client->settings.p_callbacks->ack_transaction_status_cb
        || SIMPLE_ONOFF_CLIENT_INSTANCE_COUNT_MAX <= p_client->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_client->light_demo_timer.callback = light_demo_client_timer_cb;
    p_client->light_demo_timer.p_args = p_client;
    p_client->light_demo_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_client->light_demo_timer.reload = false;

    simple_on_off_client_register_info.p_args         = p_client;
    simple_on_off_client_register_info.element_offset = element_offset;
    
    return mesh_model_register(&simple_on_off_client_register_info, &p_client->model_lid);
}

uint16_t simple_onoff_client_set(simple_onoff_client_t * p_client, const simple_onoff_set_msg_pkt_t * p_params)
{
    mesh_model_send_info_t model_msg_send;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = SIMPLE_ONOFF_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * SIMPLE_ONOFF_CLIENT_TX_HDL_TOTAL;
    uint16_t status  = MESH_ERROR_NO_ERROR;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_VENDOR(SIMPLE_ONOFF_OPCODE_STATUS, SIMPLE_ONOFF_COMPANY_ID),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
    
    if ((p_client == NULL) || (p_params == NULL) || (p_client->tx_hdl_busy == true))
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
            message_create(&model_msg_send, p_client->model_lid, SIMPLE_ONOFF_OPCODE_SET, tx_hdl, (uint8_t *)p_params, SIMPLE_ONOFF_SET_LEN);
            
            status = mesh_model_publish(&model_msg_send, &reliable_info);
            p_client->tx_hdl_busy = (status==MESH_ERROR_NO_ERROR)?true:false;
            return status;
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t simple_onoff_client_set_unack(simple_onoff_client_t * p_client, const simple_onoff_set_msg_pkt_t * p_params)
{
    mesh_model_send_info_t model_msg_send;
    uint8_t tx_hdl = SIMPLE_ONOFF_CLIENT_SET_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * SIMPLE_ONOFF_CLIENT_TX_HDL_TOTAL;
    uint16_t status  = MESH_ERROR_NO_ERROR;

    if ((p_client == NULL) || (p_params == NULL) || (p_client->tx_hdl_busy == true))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    message_create(&model_msg_send, p_client->model_lid, SIMPLE_ONOFF_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)p_params, SIMPLE_ONOFF_SET_LEN);

    status = mesh_model_publish(&model_msg_send, NULL);
    p_client->tx_hdl_busy = (status==MESH_ERROR_NO_ERROR)?true:false;
    return status;
}

uint16_t simple_onoff_client_get(simple_onoff_client_t * p_client)
{
    mesh_model_send_info_t model_msg_send;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = SIMPLE_ONOFF_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * SIMPLE_ONOFF_CLIENT_TX_HDL_TOTAL;
    uint16_t status  = MESH_ERROR_NO_ERROR;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_VENDOR(SIMPLE_ONOFF_OPCODE_STATUS, SIMPLE_ONOFF_COMPANY_ID),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
    
    if ((p_client == NULL) || (p_client->tx_hdl_busy == true))
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
            message_create(&model_msg_send, p_client->model_lid, SIMPLE_ONOFF_OPCODE_GET, tx_hdl, NULL, 0);
            
            status = mesh_model_publish(&model_msg_send, &reliable_info);
            p_client->tx_hdl_busy = (status==MESH_ERROR_NO_ERROR)?true:false;
            return status;
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t simple_onoff_client_setget_cancel(simple_onoff_client_t * p_client)
{
    uint16_t status  = MESH_ERROR_NO_ERROR;
    if (p_client == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    status = mesh_model_reliable_trans_cancel(p_client->model_lid);
    if (status == MESH_ERROR_NO_ERROR)
    {
        p_client->tx_hdl_busy = false;
    }
    return status;
}

uint16_t light_client_demo_set(simple_onoff_client_t * p_client, uint16_t msg_length, const light_demo_set_params_t * p_params, uint16_t dst)
{
    light_demo_set_msg_pkt_t set;
    uint8_t tx_hdl = SIMPLE_ONOFF_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * SIMPLE_ONOFF_CLIENT_TX_HDL_TOTAL;
    uint16_t status  = MESH_ERROR_NO_ERROR;

    if ((p_client == NULL) || (p_params == NULL) || (p_client->tx_hdl_busy == true))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    set.light_demo_opcode = p_params->light_demo_opcode;
    set.buf_len = p_params->buf_len;
    if (p_params->buf_len > 0)
    {
        memcpy(set.buf, p_params->buf, set.buf_len);
    }

    status = model_send_unicast_dev(p_client, dst, LIGHT_DEMO_OPCODE_BASE_C_PART|p_params->light_demo_opcode, MESH_INVALID_KEY_INDEX, tx_hdl, (uint8_t *)&set, msg_length, true);
    p_client->tx_hdl_busy = (status==MESH_ERROR_NO_ERROR)?true:false;
    return status;
}

uint16_t light_client_demo_set_unack(simple_onoff_client_t * p_client, uint16_t msg_length, const light_demo_set_params_t * p_params, uint16_t dst)
{
    light_demo_set_msg_pkt_t set_un;
    uint8_t tx_hdl = SIMPLE_ONOFF_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * SIMPLE_ONOFF_CLIENT_TX_HDL_TOTAL;
    uint16_t status  = MESH_ERROR_NO_ERROR;

    if ((p_client == NULL) || (p_params == NULL) || (p_client->tx_hdl_busy == true))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    set_un.light_demo_opcode = p_params->light_demo_opcode;
    set_un.buf_len = p_params->buf_len;
    if (p_params->buf_len > 0)
    {
        memcpy(set_un.buf, p_params->buf, set_un.buf_len);
    }

    status = model_send_unicast_dev(p_client, dst, LIGHT_DEMO_OPCODE_BASE_C_PART|p_params->light_demo_opcode, MESH_INVALID_KEY_INDEX, tx_hdl, (uint8_t *)&set_un, msg_length, false);
    p_client->tx_hdl_busy = (status==MESH_ERROR_NO_ERROR)?true:false;
    return status;
}
