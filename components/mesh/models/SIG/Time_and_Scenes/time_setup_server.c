/**
 *****************************************************************************************
 *
 * @file time_setup_server.c
 *
 * @brief mesh time setup Server API Implementation.
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
#include "time_server.h"
#include "time_setup_server.h"
#include "common_utils.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_time_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_zone_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_tai2utc_dlt_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_role_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_role_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void mesh_time_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void mesh_time_setup_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t mesh_time_setup_server_opcode_list[] =
{
    TSCNS_TIME_OPCODE_SET,
    TSCNS_TIME_ZONE_OPCODE_SET,
    TSCNS_TIME_TAI2UTC_DLT_OPCODE_SET,
    TSCNS_TIME_ROLE_OPCODE_GET,
    TSCNS_TIME_ROLE_OPCODE_SET,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {TSCNS_TIME_OPCODE_SET, handle_time_set_cb},
    {TSCNS_TIME_ZONE_OPCODE_SET, handle_zone_set_cb},
    {TSCNS_TIME_TAI2UTC_DLT_OPCODE_SET, handle_tai2utc_dlt_set_cb},
    {TSCNS_TIME_ROLE_OPCODE_GET, handle_role_get_cb},
    {TSCNS_TIME_ROLE_OPCODE_SET, handle_role_set_cb}
};

static const mesh_model_cb_t mesh_time_setup_server_msg_cb = {
    .cb_rx             = mesh_time_setup_server_rx_cb,
    .cb_sent           = mesh_time_setup_server_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t mesh_time_setup_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_TSCNS_TIMS),
    .element_offset = 0,
    .publish = false,
    .p_opcodes = (uint16_t *)mesh_time_setup_server_opcode_list,
    .num_opcodes = sizeof(mesh_time_setup_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &mesh_time_setup_server_msg_cb,
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

static mesh_error_t time_setup_message_send(mesh_time_setup_server_t * p_server,
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
        msg_send.model_lid = p_server->time_server->model_lid;
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


static uint16_t time_role_status_send(mesh_time_setup_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const uint8_t * role)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    uint8_t tx_hdl = (NULL == p_rx_msg) ? TSCNS_TIME_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * TSCNS_TIME_SERVER_TX_HDL_TOTAL
                                        : TSCNS_TIME_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * TSCNS_TIME_SERVER_TX_HDL_TOTAL;

    return time_setup_message_send(p_server, p_rx_msg, TSCNS_TIME_ROLE_OPCODE_STATUS, tx_hdl, (uint8_t *)role, TSCNS_TIME_ROLE_STATUS_MINLEN);
}

static void handle_time_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_time_setup_server_t  * p_server = (mesh_time_setup_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);

    mesh_time_set_params_t in_data = {0};
    mesh_time_status_params_t out_data = {0};
    mesh_time_set_msg_pkt_t * p_msg_params_packed = (mesh_time_set_msg_pkt_t *) p_rx_msg->msg;

    if (p_rx_msg->msg_len == TSCNS_TIME_SET_MINLEN)
    {
        in_data.TAI_seconds = p_msg_params_packed->TAI_seconds;
        in_data.TAI_seconds = gx_read40p(&in_data.TAI_seconds);

        in_data.subsecond = p_msg_params_packed->subsecond;
        in_data.uncertainty = p_msg_params_packed->uncertainty;
        in_data.time_authority = p_msg_params_packed->time_authority;

        in_data.TAI2UTC_dlt = p_msg_params_packed->TAI2UTC_dlt;
        in_data.TAI2UTC_dlt = gx_read16p(&in_data.TAI2UTC_dlt);

        in_data.time_zone_offset = p_msg_params_packed->time_zone_offset;

        p_server->settings.p_callbacks->times_cbs.set_cb(p_server,
                                                                                 p_rx_msg,
                                                                                 &in_data,
                                                                                 &out_data);

        (void) time_status_send(p_server->time_server, p_rx_msg, &out_data);
    }
}

static void handle_zone_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_time_setup_server_t  * p_server = (mesh_time_setup_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);

    mesh_time_zone_set_params_t in_data = {0};
    mesh_time_zone_status_params_t out_data = {0};
    mesh_time_zone_set_msg_pkt_t * p_msg_params_packed = (mesh_time_zone_set_msg_pkt_t *) p_rx_msg->msg;

    if (p_rx_msg->msg_len == TSCNS_TIME_ZONE_SET_MINLEN)
    {
        in_data.TAI_zone_change = p_msg_params_packed->TAI_zone_change;
        in_data.TAI_zone_change = gx_read40p(&in_data.TAI_zone_change);

        in_data.time_zone_offset_new = p_msg_params_packed->time_zone_offset_new;

        p_server->settings.p_callbacks->times_cbs.zone_set_cb(p_server,
                                                                                     p_rx_msg,
                                                                                     &in_data,
                                                                                     &out_data);

        (void) time_zone_status_send(p_server->time_server, p_rx_msg, &out_data);
    }
}

static void handle_tai2utc_dlt_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_time_setup_server_t  * p_server = (mesh_time_setup_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);

    mesh_tai2utc_dlt_set_params_t in_data = {0};
    mesh_tai2utc_dlt_status_params_t out_data = {0};
    mesh_tai2utc_dlt_set_msg_pkt_t * p_msg_params_packed = (mesh_tai2utc_dlt_set_msg_pkt_t *) p_rx_msg->msg;

    if (p_rx_msg->msg_len == TSCNS_TIME_TAI2UTC_DLT_SET_MINLEN)
    {
        in_data.TAI2UTC_dlt_new = p_msg_params_packed->TAI2UTC_dlt_new;
        if (!is_little_endian)
        {
            in_data.TAI2UTC_dlt_new = in_data.TAI2UTC_dlt_new <<1;
        }
        in_data.TAI2UTC_dlt_new = gx_read16p(&in_data.TAI2UTC_dlt_new);
        in_data.TAI_dlt_change = p_msg_params_packed->TAI_dlt_change;
        in_data.TAI_dlt_change = gx_read40p(&in_data.TAI_dlt_change);

        p_server->settings.p_callbacks->times_cbs.dlt_set_cb(p_server,
                                                                                     p_rx_msg,
                                                                                     &in_data,
                                                                                     &out_data);

        (void) time_dlt_status_send(p_server->time_server, p_rx_msg, &out_data);
    }
}

static void handle_role_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_time_setup_server_t  * p_server = (mesh_time_setup_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);

    if (p_rx_msg->msg_len == TSCNS_TIME_ROLE_SET_MINLEN)
    {
        uint8_t role = p_rx_msg->msg[0];

        p_server->settings.p_callbacks->times_cbs.role_set_cb(p_server,
                                                                                     p_rx_msg,
                                                                                     role,
                                                                                     &role);

        if (role == p_rx_msg->msg[0])
        {
            (void) time_role_status_send(p_server, p_rx_msg, &role);
        }
    }
}

static inline bool get_params_validate(const mesh_model_msg_ind_t * p_rx_msg)
{
    return (p_rx_msg->msg_len == 0);
}

static void handle_role_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_time_setup_server_t * p_server = (mesh_time_setup_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   

    uint8_t out_data = 0;

    if (get_params_validate(p_rx_msg))
    {
        p_server->settings.p_callbacks->times_cbs.role_get_cb(p_server, p_rx_msg, &out_data);
        (void) time_role_status_send(p_server, p_rx_msg, &out_data);
    }
}

static void mesh_time_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<mesh_time_setup_server_register_info.num_opcodes; i++)
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

static void mesh_time_setup_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    mesh_time_setup_server_t * p_server = (mesh_time_setup_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * TSCNS_TIME_SERVER_TX_HDL_TOTAL)
    {
        case TSCNS_TIME_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case TSCNS_TIME_SERVER_PUBLISH_SEND_TX_HDL:
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
uint16_t mesh_time_server_role_status_publish(mesh_time_setup_server_t * p_server, const uint8_t * role)
{
    if (NULL == p_server || NULL == role)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return time_role_status_send(p_server, NULL, role);
}

uint16_t mesh_time_setup_server_init(mesh_time_setup_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->times_cbs.set_cb
        || NULL == p_server->settings.p_callbacks->times_cbs.zone_set_cb
        || NULL == p_server->settings.p_callbacks->times_cbs.dlt_set_cb
        || NULL == p_server->settings.p_callbacks->times_cbs.role_set_cb
        || NULL == p_server->settings.p_callbacks->times_cbs.role_get_cb
        || TSCNS_TIME_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)        
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    mesh_time_setup_server_register_info.p_args = p_server;
    mesh_time_setup_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&mesh_time_setup_server_register_info, &p_server->model_lid);
}

