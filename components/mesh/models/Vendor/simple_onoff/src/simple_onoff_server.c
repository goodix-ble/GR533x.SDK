/**
 *****************************************************************************************
 *
 * @file simple_onoff_server.c
 *
 * @brief Simple On Off Server API Implementation.
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
#include "simple_onoff_server.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void simple_on_off_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void simple_on_off_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);
static void publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args);


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t simple_on_off_server_opcode_list[] =
{
    SIMPLE_ONOFF_OPCODE_GET,
    SIMPLE_ONOFF_OPCODE_SET,
    SIMPLE_ONOFF_OPCODE_SET_UNACKNOWLEDGED,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {SIMPLE_ONOFF_OPCODE_GET, handle_get_cb},
    {SIMPLE_ONOFF_OPCODE_SET, handle_set_cb},
    {SIMPLE_ONOFF_OPCODE_SET_UNACKNOWLEDGED, handle_set_cb},
};

static const mesh_model_cb_t simple_on_off_server_msg_cb = {
    .cb_rx             = simple_on_off_server_rx_cb,
    .cb_sent           = simple_on_off_server_sent_cb,
    .cb_publish_period = publish_period_cb,
};

static mesh_model_register_info_t simple_on_off_server_register_info = 
{
    .model_id = MESH_MODEL_VENDOR(SIMPLE_ON_OFF_SERVER_MODEL_ID, SIMPLE_ONOFF_COMPANY_ID),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)simple_on_off_server_opcode_list,
    .num_opcodes = sizeof(simple_on_off_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &simple_on_off_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static uint32_t status_send(simple_onoff_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const simple_onoff_status_msg_pkt_t * p_params)
{
    simple_onoff_status_msg_pkt_t msg_pkt;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? SIMPLE_ONOFF_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * SIMPLE_ONOFF_SERVER_TX_HDL_TOTAL
                                        : SIMPLE_ONOFF_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * SIMPLE_ONOFF_SERVER_TX_HDL_TOTAL;

    if (p_params->present_on_off > SIMPLE_ONOFF_MAX)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    msg_pkt.present_on_off = p_params->present_on_off;

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_VENDOR(SIMPLE_ONOFF_OPCODE_STATUS, SIMPLE_ONOFF_COMPANY_ID),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) &msg_pkt,
        .data_send_len = SIMPLE_ONOFF_STATUS_LEN,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };

    APP_LOG_INFO("SERVER[%d] -- present_on_off = %d.", p_server->model_instance_index, msg_pkt.present_on_off);

    if (NULL == p_rx_msg)
    {
        
        APP_LOG_INFO("SERVER[%d] -- to publish.", p_server->model_instance_index);
        return mesh_model_publish(&msg_send, NULL);
    }
    else
    {
        APP_LOG_INFO("SERVER[%d] -- to response.", p_server->model_instance_index);
        return mesh_model_rsp_send(&msg_send);
    }
}

static inline bool set_params_validate(const mesh_model_msg_ind_t * p_rx_msg, const simple_onoff_set_msg_pkt_t * p_params)
{
    return ((p_rx_msg->msg_len == SIMPLE_ONOFF_SET_LEN) && (p_params->on_off <= SIMPLE_ONOFF_MAX));
}

static bool model_tid_validate(tid_filter_t * p_tid_filter, const mesh_model_msg_ind_t * p_rx_msg, uint8_t tid)
{
    if (p_tid_filter->src != p_rx_msg->src || p_tid_filter->old_tid != tid)
    {
        p_tid_filter->src = p_rx_msg->src;
        p_tid_filter->old_tid = tid;

        p_tid_filter->new_transaction = true;
    }
    else
    {
        p_tid_filter->new_transaction = false;
    }

    return p_tid_filter->new_transaction;
}

static void handle_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    uint32_t send_status = MESH_ERROR_NO_ERROR;
    simple_onoff_server_t  * p_server = (simple_onoff_server_t  *) p_args;
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to set on-off state!!!", p_server->model_instance_index);
    
    simple_onoff_set_msg_pkt_t * p_msg_params_packed = (simple_onoff_set_msg_pkt_t *) p_rx_msg->msg;
    simple_onoff_status_msg_pkt_t out_data =
    {
        .present_on_off = p_msg_params_packed->on_off,
    };
    
    if (set_params_validate(p_rx_msg, p_msg_params_packed))
    {
        if (model_tid_validate(&p_server->tid_filter, p_rx_msg, p_msg_params_packed->tid))
        {
            p_server->client_address = p_rx_msg->src;
            p_server->settings.p_callbacks->onoff_cbs.set_cb(p_server->model_instance_index, p_msg_params_packed->on_off);

            // response
            if (SIMPLE_ONOFF_OPCODE_SET == p_rx_msg->opcode.company_opcode)
            {
                send_status = status_send(p_server, p_rx_msg, &out_data);
                if (MESH_ERROR_NO_ERROR != send_status)
                {
                    APP_LOG_WARNING("SERVER[%d] -- Response status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
                }
            }

            // publish
            send_status = status_send(p_server, NULL, &out_data);
            if (MESH_ERROR_NO_ERROR != send_status)
            {
                APP_LOG_WARNING("SERVER[%d] -- Publish status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
            }
        }
    }
}

static inline bool get_params_validate(const mesh_model_msg_ind_t * p_rx_msg)
{
    return (p_rx_msg->msg_len == 0);
}

static void handle_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    simple_onoff_server_t * p_server = (simple_onoff_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get on-off state!!!", p_server->model_instance_index);

    simple_onoff_status_msg_pkt_t out_data = {0};

    if (get_params_validate(p_rx_msg))
    {
        p_server->client_address = p_rx_msg->src;
        p_server->settings.p_callbacks->onoff_cbs.get_cb(p_server->model_instance_index, &out_data.present_on_off);
        uint32_t send_status = status_send(p_server, p_rx_msg, &out_data);
        if (MESH_ERROR_NO_ERROR != send_status)
        {
            APP_LOG_ERROR("SERVER[%d] -- Publish status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
        }
    }
}

static void simple_on_off_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = m_opcode_handlers[company_opcode - SIMPLE_ONOFF_OPCODE_GET].handler;

    if (NULL != handler)
    {
        handler(p_model_msg, p_args);
    }
}

static void simple_on_off_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    simple_onoff_server_t * p_server = (simple_onoff_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * SIMPLE_ONOFF_SERVER_TX_HDL_TOTAL)
    {
        case SIMPLE_ONOFF_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case SIMPLE_ONOFF_SERVER_PUBLISH_SEND_TX_HDL:
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

static void publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args)
{
    APP_LOG_INFO("model_id:%d, addr:0x%x, period_ms:%d", p_ind->model_lid, p_ind->addr, p_ind->period_ms);
}


/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t simple_onoff_server_init(simple_onoff_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->onoff_cbs.set_cb
        || NULL == p_server->settings.p_callbacks->onoff_cbs.get_cb
        || SIMPLE_ONOFF_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)        
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    simple_on_off_server_register_info.p_args = p_server;
    simple_on_off_server_register_info.element_offset = element_offset;
    
    return mesh_model_register(&simple_on_off_server_register_info, &p_server->model_lid);
}

uint16_t simple_onoff_server_status_publish(simple_onoff_server_t * p_server, const simple_onoff_status_msg_pkt_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return status_send(p_server, NULL, p_params);
}

