/**
 *****************************************************************************************
 *
 * @file harmony_mesh_server.c
 *
 * @brief harmony mesh vendor Server API Implementation.
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
#include "harmony_mesh_server.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_notify_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void harmony_mesh_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void harmony_mesh_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);
static void publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args);


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t harmony_mesh_server_opcode_list[] =
{
    HARMONY_MESH_OPCODE_GET ,
    HARMONY_MESH_OPCODE_SET ,
    HARMONY_MESH_OPCODE_SET_UNACK ,
    HARMONY_MESH_OPCODE_SET_STATUS ,
    HARMONY_MESH_OPCODE_CHANGE_NOTIFY ,
    HARMONY_MESH_OPCODE_CHANGE_NOTIFY_STATUS ,
    HARMONY_MESH_OPCODE_CHANGE_NOTIFY_UNACK ,
    HARMONY_MESH_OPCODE_GET_STATUS ,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {HARMONY_MESH_OPCODE_GET, handle_get_cb},
    {HARMONY_MESH_OPCODE_SET, handle_set_cb},
    {HARMONY_MESH_OPCODE_SET_UNACK, handle_set_cb},
    {HARMONY_MESH_OPCODE_SET_STATUS, NULL},
    {HARMONY_MESH_OPCODE_CHANGE_NOTIFY, NULL},
    {HARMONY_MESH_OPCODE_CHANGE_NOTIFY_STATUS, handle_notify_cb},
    {HARMONY_MESH_OPCODE_CHANGE_NOTIFY_UNACK, NULL},
    {HARMONY_MESH_OPCODE_GET_STATUS, NULL},
};

static const mesh_model_cb_t harmony_mesh_server_msg_cb = {
    .cb_rx             = harmony_mesh_server_rx_cb,
    .cb_sent           = harmony_mesh_server_sent_cb,
    .cb_publish_period = publish_period_cb,
};

static mesh_model_register_info_t harmony_mesh_server_register_info =
{
    .model_id = MESH_MODEL_VENDOR(HARMONY_MESH_SERVER_MODEL_ID, HARMONY_MESH_COMPANY_ID),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)harmony_mesh_server_opcode_list,
    .num_opcodes = sizeof(harmony_mesh_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &harmony_mesh_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static uint32_t status_send(harmony_mesh_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  uint16_t vendor_opcode,
                                  const uint8_t tid,
                                  const uint16_t attri_type,
                                  uint8_t *p_out,
                                  uint16_t p_out_len)
{
    if (p_out_len > HARMONY_MESH_VALUE_MAX)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    mesh_error_t status_ret = MESH_ERROR_NO_ERROR;
    harmony_mesh_status_msg_pkt_t *msg_pkt = sys_malloc(sizeof(harmony_mesh_status_msg_pkt_t) + p_out_len);
    uint8_t tx_hdl = (NULL == p_rx_msg) ? HARMONY_MESH_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * HARMONY_MESH_SERVER_TX_HDL_TOTAL
                                        : HARMONY_MESH_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * HARMONY_MESH_SERVER_TX_HDL_TOTAL;

    msg_pkt->tid = tid;
    msg_pkt->attri_type = attri_type;
    memcpy(msg_pkt->payload, p_out, p_out_len);

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_VENDOR(vendor_opcode, HARMONY_MESH_COMPANY_ID),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) msg_pkt,
        .data_send_len = sizeof(harmony_mesh_status_msg_pkt_t) + p_out_len,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };

    APP_LOG_INFO("SERVER[%d] -- ATT type = 0x%04x", p_server->model_instance_index, msg_pkt->attri_type);

    if (NULL == p_rx_msg)
    {
        APP_LOG_INFO("SERVER[%d] -- to publish.", p_server->model_instance_index);
        status_ret = mesh_model_publish(&msg_send, NULL);
    }
    else
    {
        APP_LOG_INFO("SERVER[%d] -- to response.", p_server->model_instance_index);
        status_ret = mesh_model_rsp_send(&msg_send);
    }

    sys_free(msg_pkt);
    msg_pkt = NULL;

    return status_ret;
}

static inline bool rx_params_validate(const mesh_model_msg_ind_t * p_rx_msg)
{
    return (p_rx_msg->msg_len >= HARMONY_MESH_RX_LEN);
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
    harmony_mesh_server_t  * p_server = (harmony_mesh_server_t  *) p_args;
    uint8_t p_out[HARMONY_MESH_VALUE_MAX] = {0};
    uint16_t p_out_len = 0;
    harmony_mesh_rx_msg_pkt_t * p_msg_params_packed = (harmony_mesh_rx_msg_pkt_t *) p_rx_msg->msg;
    uint16_t attri_type = ((p_msg_params_packed->attri_type&0xFF) << 8) | ((p_msg_params_packed->attri_type&0xFF00)>>8);

    APP_LOG_INFO("SERVER[%d] tid[%d] -- Receive message, want to set attribute type 0x%04x state!!!", (int)p_msg_params_packed->tid, p_server->model_instance_index, attri_type);

    if (rx_params_validate(p_rx_msg))
    {
        if (model_tid_validate(&p_server->tid_filter, p_rx_msg, p_msg_params_packed->tid))
        {
            p_server->client_address = p_rx_msg->src;
            p_server->settings.p_callbacks->state_cbs.set_cb(p_server->model_instance_index,
                                                                                                attri_type,
                                                                                                p_msg_params_packed->payload,
                                                                                                p_rx_msg->msg_len - 3/* TID(1 byte)+ATT(2 bytes)*/,
                                                                                                p_out,
                                                                                                &p_out_len);

            // response
            if (HARMONY_MESH_OPCODE_SET == p_rx_msg->opcode.company_opcode)
            {
                send_status = status_send(p_server, p_rx_msg, HARMONY_MESH_OPCODE_SET_STATUS, p_msg_params_packed->tid, p_msg_params_packed->attri_type, p_out, p_out_len);
                if (MESH_ERROR_NO_ERROR != send_status)
                {
                    APP_LOG_WARNING("SERVER[%d] -- Response status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
                }
            }
        }
    }
}

static void handle_notify_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    harmony_mesh_server_t  * p_server = (harmony_mesh_server_t  *) p_args;
    harmony_mesh_rx_msg_pkt_t * p_msg_params_packed = (harmony_mesh_rx_msg_pkt_t *) p_rx_msg->msg;
    uint16_t attri_type = ((p_msg_params_packed->attri_type&0xFF) << 8) | ((p_msg_params_packed->attri_type&0xFF00)>>8);

    APP_LOG_INFO("SERVER[%d] tid[%d] -- Receive message, want to notify attribute type 0x%04x state!!!", (int)p_msg_params_packed->tid, p_server->model_instance_index, attri_type);

    //if (rx_params_validate(p_rx_msg))
    {
        //if (model_tid_validate(&p_server->tid_filter, p_rx_msg, p_msg_params_packed->tid))
        {
            p_server->client_address = p_rx_msg->src;
            p_server->settings.p_callbacks->state_change_cbs.change_notify_status_cb(p_server->model_instance_index, attri_type);
        }
    }
}

static void handle_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    harmony_mesh_server_t * p_server = (harmony_mesh_server_t *) p_args;
    harmony_mesh_rx_msg_pkt_t * p_msg_params_packed = (harmony_mesh_rx_msg_pkt_t *) p_rx_msg->msg;
    uint8_t p_out[HARMONY_MESH_VALUE_MAX] = {0};
    uint16_t p_out_len = 0;
    uint16_t attri_type = ((p_msg_params_packed->attri_type&0xFF) << 8) | ((p_msg_params_packed->attri_type&0xFF00)>>8);

    APP_LOG_INFO("SERVER[%d] tid[%d] -- Receive message, want to get attribute type 0x%04x state!!!", (int)p_msg_params_packed->tid, p_server->model_instance_index, attri_type);

    if (rx_params_validate(p_rx_msg))
    {

        p_server->client_address = p_rx_msg->src;
        p_server->settings.p_callbacks->state_cbs.get_cb(p_server->model_instance_index,
                                                                                                attri_type,
                                                                                                p_out,
                                                                                                &p_out_len);

        uint32_t send_status = status_send(p_server, p_rx_msg, HARMONY_MESH_OPCODE_GET_STATUS, p_msg_params_packed->tid, p_msg_params_packed->attri_type, p_out, p_out_len);
        if (MESH_ERROR_NO_ERROR != send_status)
        {
            APP_LOG_WARNING("SERVER[%d] -- Response status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
        }
    }
}

static void harmony_mesh_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = m_opcode_handlers[company_opcode - HARMONY_MESH_OPCODE_GET].handler;

    if (NULL != handler)
    {
        handler(p_model_msg, p_args);
    }
}

static void harmony_mesh_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    harmony_mesh_server_t * p_server = (harmony_mesh_server_t *) p_args;
    harmony_mesh_status_msg_pkt_t *msg_pkt = (harmony_mesh_status_msg_pkt_t *)p_buf;

    switch(p_sent->tx_hdl - p_server->model_instance_index * HARMONY_MESH_SERVER_TX_HDL_TOTAL)
    {
        case HARMONY_MESH_SERVER_RSP_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("SERVER[%d] tid[%d] ATT type = 0x%04x -- Responsed get or set message!!!", p_server->model_instance_index, (int)msg_pkt->tid, msg_pkt->attri_type)
                  : APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            break;
        case HARMONY_MESH_SERVER_PUBLISH_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("SERVER[%d] tid[%d] ATT type = 0x%04x -- Published message!!!", p_server->model_instance_index, (int)msg_pkt->tid, msg_pkt->attri_type)
                  : APP_LOG_INFO("SERVER[%d] -- Failed to published message, status = %x!!!", p_server->model_instance_index, p_sent->status);
                  
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

static void mesh_model_reliable_trans_cb(void * p_args, mesh_model_reliable_trans_status_t status)
{
    static int count = 0;
    switch(status)
    {
        case MESH_MODEL_RELIABLE_TRANS_SUCCESS:
            count++;
            APP_LOG_INFO("Mesh model reliable translation has been successfully.[%d]", count);
        break;
        case MESH_MODEL_RELIABLE_TRANS_TIMEOUT:
            APP_LOG_INFO("Mesh model reliable translation has been timeout.");
        break;
        case MESH_MODEL_RELIABLE_TRANS_CANCELLED:
            APP_LOG_INFO("Mesh model reliable translation canceled.");
        break;
        default:
            APP_LOG_INFO("Invalid status.");
        break;
    }
}

static uint32_t status_send_reliable(harmony_mesh_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  uint16_t vendor_opcode,
                                  uint16_t reply_opceode,
                                  const uint8_t tid,
                                  const uint16_t attri_type,
                                  uint8_t *p_out,
                                  uint16_t p_out_len, uint16_t timeout)
{
    if (p_out_len > HARMONY_MESH_VALUE_MAX)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    mesh_error_t status_ret = MESH_ERROR_NO_ERROR;
    harmony_mesh_status_msg_pkt_t *msg_pkt = sys_malloc(sizeof(harmony_mesh_status_msg_pkt_t) + p_out_len);
    uint8_t tx_hdl = (NULL == p_rx_msg) ? HARMONY_MESH_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * HARMONY_MESH_SERVER_TX_HDL_TOTAL
                                        : HARMONY_MESH_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * HARMONY_MESH_SERVER_TX_HDL_TOTAL;

    msg_pkt->tid = tid;
    msg_pkt->attri_type = attri_type;
    memcpy(msg_pkt->payload, p_out, p_out_len);

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_VENDOR(vendor_opcode, HARMONY_MESH_COMPANY_ID),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) msg_pkt,
        .data_send_len = sizeof(harmony_mesh_status_msg_pkt_t) + p_out_len,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };

    APP_LOG_INFO("SERVER[%d] -- ATT type = 0x%04x.", p_server->model_instance_index, msg_pkt->attri_type);

    if (NULL == p_rx_msg)
    {
        APP_LOG_INFO("SERVER[%d] -- to publish.", p_server->model_instance_index);
        mesh_model_reliable_info_t reliable_info =
        {
            .reply_opcode   = MESH_ACCESS_OPCODE_VENDOR(reply_opceode, HARMONY_MESH_COMPANY_ID),
            .status_cb      = mesh_model_reliable_trans_cb,
            .timeout_ms     = timeout,
        };
        status_ret = mesh_model_publish(&msg_send, &reliable_info);
    }

    sys_free(msg_pkt);
    msg_pkt = NULL;

    return status_ret;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t harmony_mesh_server_init(harmony_mesh_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->state_cbs.set_cb
        || NULL == p_server->settings.p_callbacks->state_cbs.get_cb
        || HARMONY_MESH_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    harmony_mesh_server_register_info.p_args = p_server;
    harmony_mesh_server_register_info.element_offset = element_offset;

    return mesh_model_register(&harmony_mesh_server_register_info, &p_server->model_lid);
}

uint16_t harmony_mesh_server_status_notify_with_ack(harmony_mesh_server_t * p_server, const uint8_t tid, const uint16_t attri_type, uint8_t *p_out, uint16_t p_out_len)
{
    if (NULL == p_server)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return status_send_reliable(p_server, NULL, HARMONY_MESH_OPCODE_CHANGE_NOTIFY, HARMONY_MESH_OPCODE_CHANGE_NOTIFY_STATUS, \
        tid, attri_type, p_out, p_out_len, 6000);
}

uint16_t harmony_mesh_server_status_notify_without_ack(harmony_mesh_server_t * p_server, const uint8_t tid, const uint16_t attri_type, uint8_t *p_out, uint16_t p_out_len)
{
    if (NULL == p_server || NULL == p_out)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return status_send(p_server, NULL, HARMONY_MESH_OPCODE_CHANGE_NOTIFY_UNACK, tid, attri_type, p_out, p_out_len);
}


