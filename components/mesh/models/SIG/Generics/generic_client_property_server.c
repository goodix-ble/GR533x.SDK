/**
 ****************************************************************************************
 *
 * @file generic_client_property_server.c
 *
 * @brief Generic Client Property Server API Implementation.
 *
 ****************************************************************************************
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
#include "generic_property_message.h"
#include "generic_client_property_server.h"
#include "common_utils.h"
#include "grx_sys.h"
#include "mesh_property.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */


static void handle_client_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void generic_client_property_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void generic_client_property_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
static const uint16_t generic_client_property_server_opcode_list[] =
{
    GENERIC_PROPERTIES_OPCODE_CLIENT_GET,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {GENERIC_PROPERTIES_OPCODE_CLIENT_GET, handle_client_get_cb},
};


static const mesh_model_cb_t generic_client_property_server_msg_cb = {
    .cb_rx             = generic_client_property_server_rx_cb,
    .cb_sent           = generic_client_property_server_sent_cb,
    .cb_publish_period = NULL,
};


static mesh_model_register_info_t generic_client_property_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_GENS_CPROP),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)generic_client_property_server_opcode_list,
    .num_opcodes = sizeof(generic_client_property_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &generic_client_property_server_msg_cb,
    .p_args = NULL,
};
/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */


static uint32_t client_properties_status_send(generic_client_property_server_t * p_server,
                                          const mesh_model_msg_ind_t *p_rx_msg,
                                          const generic_properties_uamc_status_params_t * p_params)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    uint8_t tx_hdl = (NULL == p_rx_msg) ? GENERIC_PROPERTY_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * GENERIC_PROPERTY_SERVER_TX_HDL_TOTAL
                                        : GENERIC_PROPERTY_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * GENERIC_PROPERTY_SERVER_TX_HDL_TOTAL;
    uint16_t status;
    uint8_t* p_buffer = NULL;
    uint16_t send_len = 0;
    if (p_params->id_number != 0)
    {
        send_len = p_params->id_number * sizeof(uint16_t);
        p_buffer = sys_malloc(sizeof(uint8_t) * send_len);
        for(int i = 0; i < p_params->id_number; i++)
        {
            gx_write16p(p_buffer + 2*i, p_params->property_id[i]);
        }
    }
    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(GENERIC_PROPERTIES_OPCODE_CLIENT_STATUS),
        .tx_hdl = tx_hdl,
        .p_data_send = p_buffer,
        .data_send_len = send_len,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };

    if (NULL == p_rx_msg)
    {
        APP_LOG_INFO("SERVER[%d] -- to publish.", p_server->model_instance_index);
        status = mesh_model_publish(&msg_send, NULL);
    }
    else
    {
        APP_LOG_INFO("SERVER[%d] -- to response.", p_server->model_instance_index);
        status = mesh_model_rsp_send(&msg_send);
    }
    
    sys_free(p_buffer);
    return status;
}
 

 
static void handle_client_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    generic_client_property_server_t * p_server = (generic_client_property_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get client properties state!!!", p_server->model_instance_index);
    if (p_rx_msg->opcode.company_opcode == GENERIC_PROPERTIES_OPCODE_CLIENT_GET)
    {
        generic_properties_client_get_params_t in_data = {0};
        generic_properties_uamc_status_params_t out_data = {0};
        if (p_rx_msg->msg_len == GENERIC_PROPERTIES_CLIENT_GET_LEN)
        {
            in_data.property_id = gx_read16(p_rx_msg->msg);
            if (INVILID_PROPERTY_ID == in_data.property_id)
            {
                return ;
            }
            p_server->settings.p_callbacks->property_cbs.client_properties_get_cb(p_server,p_rx_msg,&in_data,&out_data);
            if (out_data.id_number == 0)
            {
                APP_LOG_INFO("[%s] Property ID not exist.", __func__);
            }
            uint32_t send_status = client_properties_status_send(p_server, p_rx_msg, &out_data);
            if (MESH_ERROR_NO_ERROR != send_status)
            {
                APP_LOG_ERROR("SERVER[%d] -- Publish status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
            }
        }
    }
}



static void generic_client_property_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;
    mesh_opcode_handler_cb_t handler = NULL;
    if (company_opcode == GENERIC_PROPERTIES_OPCODE_CLIENT_GET)
    {
        handler = m_opcode_handlers[0].handler;
    }
    if (NULL != handler)
    {
        handler(p_model_msg, p_args);
    }
}

static void generic_client_property_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    generic_client_property_server_t * p_server = (generic_client_property_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * GENERIC_PROPERTY_SERVER_TX_HDL_TOTAL)
    {
        case GENERIC_PROPERTY_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case GENERIC_PROPERTY_SERVER_PUBLISH_SEND_TX_HDL:
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

uint16_t generic_client_property_server_init(generic_client_property_server_t * p_server, uint8_t element_offset)
{
    if (p_server == NULL ||
        p_server->settings.p_callbacks == NULL ||
        p_server->settings.p_callbacks->property_cbs.client_properties_get_cb == NULL ||
        GENERIC_PROPERTY_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    generic_client_property_server_register_info.p_args = p_server;
    generic_client_property_server_register_info.element_offset = element_offset;
    
    return mesh_model_register(&generic_client_property_server_register_info, &p_server->model_lid);
}


uint16_t generic_client_properties_server_status_publish(generic_client_property_server_t * p_server, const generic_properties_uamc_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return client_properties_status_send(p_server, NULL, p_params);
}
