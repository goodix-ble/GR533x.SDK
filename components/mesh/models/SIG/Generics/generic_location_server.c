/**
 *****************************************************************************************
 *
 * @file generic_location_server.c
 *
 * @brief Generic Location Server API Implementation.
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
#include "generic_location_server.h"
#include "common_utils.h"
/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void generic_location_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void generic_location_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t generic_location_server_opcode_list[] =
{
    GENERIC_LOCATION_GLOBAL_OPCODE_GET,
    GENERIC_LOCATION_GLOBAL_OPCODE_STATUS,
    GENERIC_LOCATION_LOCAL_OPCODE_GET,
    GENERIC_LOCATION_LOCAL_OPCODE_STATUS,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {GENERIC_LOCATION_GLOBAL_OPCODE_GET, handle_get_cb},
    {GENERIC_LOCATION_LOCAL_OPCODE_GET, handle_get_cb}
};

static const mesh_model_cb_t generic_location_server_msg_cb = {
    .cb_rx             = generic_location_server_rx_cb,
    .cb_sent           = generic_location_server_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t generic_location_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_GENS_LOC),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)generic_location_server_opcode_list,
    .num_opcodes = sizeof(generic_location_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &generic_location_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static uint32_t status_send(generic_location_server_t * p_server,
                                                  const mesh_model_msg_ind_t *p_rx_msg,
                                                  bool global_flag, 
                                                  const void * p_params)
{
    
    generic_location_global_status_msg_pkt_t msg_pkt_g;
    location_global_status_params_t *p_global_out = NULL;
    generic_location_local_status_msg_pkt_t msg_pkt_l;
    location_local_status_params_t *p_local_out = NULL;

    uint16_t data_send_len = 0;
    uint16_t op_status = GENERIC_LOCATION_GLOBAL_OPCODE_STATUS;
    uint8_t *p_data = NULL;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? GENERIC_LOCATION_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * GENERIC_LOCATION_SERVER_TX_HDL_TOTAL
                                        : GENERIC_LOCATION_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * GENERIC_LOCATION_SERVER_TX_HDL_TOTAL;

    APP_LOG_INFO("[%s] enter, send location status.", __func__);

    if (global_flag)
    {
        op_status = GENERIC_LOCATION_GLOBAL_OPCODE_STATUS;
        p_data = (uint8_t *)&msg_pkt_g;
        p_global_out = (location_global_status_params_t *)p_params;
        //send_params_format(p_global_out);

        gx_write32p((void const *)&msg_pkt_g.global_latitude, p_global_out->global_latitude);
        gx_write32p((void const *)&msg_pkt_g.global_longitude, p_global_out->global_longitude);
        gx_write16p((void const *)&msg_pkt_g.global_altitude, p_global_out->global_altitude);
        data_send_len = GENERIC_LOCATION_GLOBAL_STATUS_MAXLEN;
    }
    else
    {
        op_status = GENERIC_LOCATION_LOCAL_OPCODE_STATUS;
        p_data = (uint8_t *)&msg_pkt_l;
        p_local_out = (location_local_status_params_t *)p_params;

        gx_write16p((void const *)&msg_pkt_l.local_north, p_local_out->local_north);
        gx_write16p((void const *)&msg_pkt_l.local_east, p_local_out->local_east);
        gx_write16p((void const *)&msg_pkt_l.local_altitude, p_local_out->local_altitude);
        msg_pkt_l.floor_number = p_local_out->floor_number;
        gx_write16p((void const *)&msg_pkt_l.uncertainty, p_local_out->uncertainty);
        data_send_len = GENERIC_LOCATION_LOCAL_STATUS_MAXLEN;
    }

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(op_status),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) p_data,
        .data_send_len = data_send_len,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };

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
    generic_location_server_t * p_server = (generic_location_server_t *) p_args;
    bool global_flag = false;

    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get location state!!!", p_server->model_instance_index);

    location_global_status_params_t out_data_g = {0};
    location_local_status_params_t out_data_l = {0};
    void * p_out_data = NULL;

    if (get_params_validate(p_rx_msg))
    {
        if (p_rx_msg->opcode.company_opcode == GENERIC_LOCATION_GLOBAL_OPCODE_GET)
        {
            global_flag = true;
            p_out_data = (void * )&out_data_g;
        }
        else
        {
            global_flag = false;
            p_out_data = (void * )&out_data_l;
        }

        p_server->settings.p_callbacks->location_cbs.get_cb(p_server, p_rx_msg, p_out_data);
        uint32_t send_status = status_send(p_server, p_rx_msg, global_flag, p_out_data);
        if (MESH_ERROR_NO_ERROR != send_status)
        {
            APP_LOG_ERROR("SERVER[%d] -- Publish status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
        }
    }
}

static void generic_location_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;
    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<generic_location_server_register_info.num_opcodes; i++)
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

static void generic_location_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    generic_location_server_t * p_server = (generic_location_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * GENERIC_LOCATION_SERVER_TX_HDL_TOTAL)
    {
        case GENERIC_LOCATION_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case GENERIC_LOCATION_SERVER_PUBLISH_SEND_TX_HDL:
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

uint16_t generic_location_server_init(generic_location_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->location_cbs.get_cb
        || GENERIC_LOCATION_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    generic_location_server_register_info.p_args = p_server;
    generic_location_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&generic_location_server_register_info, &p_server->model_lid);
}

uint16_t generic_location_server_status_publish(generic_location_server_t * p_server, bool global_flag, const void * p_params)
{
    if (NULL == p_server || NULL == p_params )
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return status_send(p_server, NULL, global_flag, p_params);
}

