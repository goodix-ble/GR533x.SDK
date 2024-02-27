/**
 *****************************************************************************************
 *
 * @file generic_battery_server.c
 *
 * @brief Generic Battery Server API Implementation.
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
#include "generic_battery_message.h"
#include "generic_battery_server.h"
#include "common_utils.h"
/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void generic_battery_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void generic_battery_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t generic_battery_server_opcode_list[] =
{
    GENERIC_BATTERY_OPCODE_GET
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {GENERIC_BATTERY_OPCODE_GET, handle_get_cb}
};

static const mesh_model_cb_t generic_battery_server_msg_cb = {
    .cb_rx             = generic_battery_server_rx_cb,
    .cb_sent           = generic_battery_server_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t generic_battery_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_GENS_BAT),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)generic_battery_server_opcode_list,
    .num_opcodes = sizeof(generic_battery_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &generic_battery_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static inline bool send_params_validate(const generic_battery_status_params_t * p_params)
{
    return (((p_params->battery_level <= GENERIC_BATTERY_LEVEL_PER_MAX)
                    || (p_params->battery_level == 0xFF))
                &&(p_params->time_to_discharge <= GENERIC_BATTERY_TIME_DISCHARGE_UNKNOW)
                &&(p_params->time_to_charge <= GENERIC_BATTERY_TIME_CHARGE_UNKNOW)
                &&(p_params->flags_presence <= GENERIC_BATTERY_PRESENT_UNKNOW)
                &&(p_params->flags_indicator <= GENERIC_BATTERY_CHARGE_PRESENT_UNKNOW)
                &&(p_params->flags_charging <= GENERIC_BATTERY_CHARGEING_UNKNOW)
                &&(p_params->flags_serviceability <= GENERIC_BATTERY_SERVICEABILITY_UNKNOW));
}
static uint32_t status_send(generic_battery_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const generic_battery_status_params_t * p_params)
{
    APP_LOG_INFO("[%s] enter, send generic battery status.", __func__);
    
    generic_battery_status_msg_pkt_t msg_pkt;
    uint32_t time_to_discharge;
    uint32_t time_to_charge;

    uint8_t tx_hdl = (NULL == p_rx_msg) ? GENERIC_BATTERY_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * GENERIC_BATTERY_SERVER_TX_HDL_TOTAL
                                        : GENERIC_BATTERY_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * GENERIC_BATTERY_SERVER_TX_HDL_TOTAL;

    if (!send_params_validate(p_params))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    msg_pkt.battery_level = p_params->battery_level;

    gx_write24p(&time_to_discharge, p_params->time_to_discharge);
    gx_write24p(&time_to_charge, p_params->time_to_charge);
    msg_pkt.time_to_discharge = time_to_discharge;
    msg_pkt.time_to_charge = time_to_charge;

    msg_pkt.flags = (p_params->flags_presence<<GENERIC_BATTERY_FLAGS_PRESENCE) 
                                | (p_params->flags_indicator<<GENERIC_BATTERY_FLAGS_INDICATOR)
                                | (p_params->flags_charging<<GENERIC_BATTERY_FLAGS_CHARGEING)
                                | (p_params->flags_serviceability<<GENERIC_BATTERY_FLAGS_SERVICEABILITY);

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(GENERIC_BATTERY_OPCODE_STATUS),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) &msg_pkt,
        .data_send_len = GENERIC_BATTERY_STATUS_MAXLEN,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };

    APP_LOG_INFO("SERVER[%d] -- battery level = %d, discharge time minutes %d, charge time minutes %d, flags 0x%02x", 
                                p_server->model_instance_index, p_params->battery_level, p_params->time_to_discharge, p_params->time_to_charge, msg_pkt.flags);

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

static inline bool get_params_validate(const mesh_model_msg_ind_t * p_rx_msg)
{
    return (p_rx_msg->msg_len == 0);
}

static void handle_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    generic_battery_server_t * p_server = (generic_battery_server_t *) p_args;

    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get battery state!!!", p_server->model_instance_index);

    generic_battery_status_params_t out_data = {0};

    if (get_params_validate(p_rx_msg))
    {
        p_server->settings.p_callbacks->battery_cbs.get_cb(p_server, p_rx_msg, &out_data);
        uint32_t send_status = status_send(p_server, p_rx_msg, &out_data);
        if (MESH_ERROR_NO_ERROR != send_status)
        {
            APP_LOG_ERROR("SERVER[%d] -- Publish status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
        }
    }
}

static void generic_battery_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = m_opcode_handlers[company_opcode - GENERIC_BATTERY_OPCODE_GET].handler;

    if (NULL != handler)
    {
        handler(p_model_msg, p_args);
    }
}

static void generic_battery_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    generic_battery_server_t * p_server = (generic_battery_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * GENERIC_BATTERY_SERVER_TX_HDL_TOTAL)
    {
        case GENERIC_BATTERY_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case GENERIC_BATTERY_SERVER_PUBLISH_SEND_TX_HDL:
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

uint16_t generic_battery_server_init(generic_battery_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->battery_cbs.get_cb
        || GENERIC_BATTERY_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    generic_battery_server_register_info.p_args = p_server;
    generic_battery_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&generic_battery_server_register_info, &p_server->model_lid);
}

uint16_t generic_battery_server_status_publish(generic_battery_server_t * p_server, 
                                                            const generic_battery_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params || (!send_params_validate(p_params)))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return status_send(p_server, NULL, p_params);
}

