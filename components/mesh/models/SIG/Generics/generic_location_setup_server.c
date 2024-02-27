/**
 *****************************************************************************************
 *
 * @file generic_location_setup_server.c
 *
 * @brief Generic Location Setup Server API Implementation.
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
#include "grx_sys.h"
/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void handle_global_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_local_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void generic_location_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
//static void generic_location_setup_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t generic_location_setup_server_opcode_list[] =
{
    GENERIC_LOCATION_GLOBAL_OPCODE_SET,
    GENERIC_LOCATION_GLOBAL_OPCODE_SET_UNACK,
    GENERIC_LOCATION_LOCAL_OPCODE_SET,
    GENERIC_LOCATION_LOCAL_OPCODE_SET_UNACK
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {GENERIC_LOCATION_GLOBAL_OPCODE_SET, handle_global_set_cb},
    {GENERIC_LOCATION_GLOBAL_OPCODE_SET_UNACK, handle_global_set_cb},
    {GENERIC_LOCATION_LOCAL_OPCODE_SET, handle_local_set_cb},
    {GENERIC_LOCATION_LOCAL_OPCODE_SET_UNACK, handle_local_set_cb}
};

static const mesh_model_cb_t generic_location_setup_server_msg_cb = {
    .cb_rx             = generic_location_setup_server_rx_cb,
    .cb_sent           = NULL,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t generic_location_setup_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_GENS_LOCS),
    .element_offset = 0,
    .publish = false,
    .p_opcodes = (uint16_t *)generic_location_setup_server_opcode_list,
    .num_opcodes = sizeof(generic_location_setup_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &generic_location_setup_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static uint32_t local_status_setup_send(generic_location_setup_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const location_local_status_params_t *p_params)
{
    generic_location_local_status_msg_pkt_t msg_pkt;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? GENERIC_LOCATION_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * GENERIC_LOCATION_SERVER_TX_HDL_TOTAL
                                        : GENERIC_LOCATION_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * GENERIC_LOCATION_SERVER_TX_HDL_TOTAL;

    APP_LOG_INFO("[%s] enter, send local setup status.", __func__);

    if ((NULL == p_params)||(NULL == p_rx_msg)||(NULL == p_server) ||(NULL == p_server->location_server))
    {
        APP_LOG_INFO("SERVER[%d] -- to response err %p %p %p %p.", p_server->model_instance_index, p_params,
                                                                                                        p_rx_msg, p_server, p_server->location_server);
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    gx_write16p((void const *)&msg_pkt.local_north, p_params->local_north);
    gx_write16p((void const *)&msg_pkt.local_east, p_params->local_east);
    gx_write16p((void const *)&msg_pkt.local_altitude, p_params->local_altitude);
    msg_pkt.floor_number = p_params->floor_number;
    gx_write16p((void const *)&msg_pkt.uncertainty, p_params->uncertainty);

    if (p_server->location_server)//setup server send status
    {
        mesh_model_send_info_t msg_send =
        {
            .model_lid = p_server->location_server->model_lid,
            .opcode = MESH_ACCESS_OPCODE_SIG(GENERIC_LOCATION_LOCAL_OPCODE_STATUS),
            .tx_hdl = tx_hdl,
            .p_data_send = (uint8_t *)&msg_pkt,
            .data_send_len = GENERIC_LOCATION_LOCAL_STATUS_MAXLEN,
            .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
            .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
        };

        return mesh_model_rsp_send(&msg_send);
    }
    else
    {
        APP_LOG_ERROR("[ERROR] -- no server to send status");
        return MESH_ERROR_COMMAND_DISALLOWED;
    }
}

static uint32_t global_status_setup_send(generic_location_setup_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const location_global_status_params_t *p_params)
{
    generic_location_global_status_msg_pkt_t msg_pkt;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? GENERIC_LOCATION_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * GENERIC_LOCATION_SERVER_TX_HDL_TOTAL
                                        : GENERIC_LOCATION_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * GENERIC_LOCATION_SERVER_TX_HDL_TOTAL;

    APP_LOG_INFO("[%s] enter, send global setup status.", __func__);

    if ((NULL == p_params)||(NULL == p_rx_msg)||(NULL == p_server) ||(NULL == p_server->location_server))
    {
        APP_LOG_INFO("SERVER[%d] -- to response err %p %p %p %p.", p_server->model_instance_index, p_params,
                                                                                                        p_rx_msg, p_server, p_server->location_server);
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    gx_write32p((void const *)&msg_pkt.global_latitude, p_params->global_latitude);
    gx_write32p((void const *)&msg_pkt.global_longitude, p_params->global_longitude);
    gx_write16p((void const *)&msg_pkt.global_altitude, p_params->global_altitude);

    if (p_server->location_server)//setup server send status
    {
        mesh_model_send_info_t msg_send =
        {
            .model_lid = p_server->location_server->model_lid,
            .opcode = MESH_ACCESS_OPCODE_SIG(GENERIC_LOCATION_GLOBAL_OPCODE_STATUS),
            .tx_hdl = tx_hdl,
            .p_data_send = (uint8_t *)&msg_pkt,
            .data_send_len = GENERIC_LOCATION_GLOBAL_STATUS_MAXLEN,
            .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
            .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
        };

        APP_LOG_INFO("SERVER[%d] -- to response status opcode GENERIC_LOCATION_GLOBAL_OPCODE, ", p_server->model_instance_index);

        return mesh_model_rsp_send(&msg_send);
    }
    else
    {
        APP_LOG_ERROR("[ERROR] -- no server to send status");
        return MESH_ERROR_COMMAND_DISALLOWED;
    }
}

static inline bool set_params_validate(const mesh_model_msg_ind_t * p_rx_msg)
{
    return ((p_rx_msg->msg_len == GENERIC_LOCATION_GLOBAL_STATUS_MAXLEN)
                ||(p_rx_msg->msg_len == GENERIC_LOCATION_LOCAL_STATUS_MAXLEN));
}

static void handle_local_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    generic_location_setup_server_t * p_server = (generic_location_setup_server_t *) p_args;
    location_local_status_params_t local_state = {0,};
    location_local_status_params_t out_data = {0,};
    generic_location_local_status_msg_pkt_t *msg_params_packed = (generic_location_local_status_msg_pkt_t *) p_rx_msg->msg;
    bool ack_flag = false;

    APP_LOG_INFO("SERVER[%d] -- Receive message, want to set location state!!!", p_server->model_instance_index);

    if (set_params_validate(p_rx_msg))
    {
        switch (p_rx_msg->opcode.company_opcode)
        {
            case GENERIC_LOCATION_LOCAL_OPCODE_SET:
                ack_flag = true;
            case GENERIC_LOCATION_LOCAL_OPCODE_SET_UNACK:
                local_state.local_north = gx_read16p((void const *)&msg_params_packed->local_north);
                local_state.local_east = gx_read16p((void const *)&msg_params_packed->local_east);
                local_state.local_altitude = gx_read16p((void const *)&msg_params_packed->local_altitude);
                local_state.floor_number = msg_params_packed->floor_number;
                local_state.uncertainty = gx_read16p((void const *)&msg_params_packed->uncertainty);
                break;
            default:
                break;
        }

        p_server->settings.p_callbacks->location_cbs.set_local_cb(p_server, p_rx_msg, (void *)&local_state, (ack_flag) ? &out_data : NULL);
        if (ack_flag)
        {
            uint32_t send_status = local_status_setup_send(p_server, p_rx_msg, &out_data);
            if (MESH_ERROR_NO_ERROR != send_status)
            {
                APP_LOG_ERROR("SERVER[%d] -- Publish status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
            }
        }
    }
}

static void handle_global_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    generic_location_setup_server_t * p_server = (generic_location_setup_server_t *) p_args;
    location_global_status_params_t global_state = {0,};
    location_global_status_params_t out_data = {0,};
    generic_location_global_status_msg_pkt_t *msg_params_packed = (generic_location_global_status_msg_pkt_t *) p_rx_msg->msg;
    bool ack_flag = false;

    APP_LOG_INFO("[%s] enter.", __func__);
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to set location state!!!", p_server->model_instance_index);

    if (set_params_validate(p_rx_msg))
    {
        switch (p_rx_msg->opcode.company_opcode)
        {
            case GENERIC_LOCATION_GLOBAL_OPCODE_SET:
                ack_flag = true;
            case GENERIC_LOCATION_GLOBAL_OPCODE_SET_UNACK:
                global_state.global_latitude = gx_read32p((void const *)&msg_params_packed->global_latitude);
                global_state.global_longitude = gx_read32p((void const *)&msg_params_packed->global_longitude);
                global_state.global_altitude = gx_read16p((void const *)&msg_params_packed->global_altitude);
                break;
            default:
                break;
        }

        p_server->settings.p_callbacks->location_cbs.set_global_cb(p_server, p_rx_msg, (void *)&global_state, (ack_flag) ? &out_data : NULL);
        if (ack_flag)
        {
            uint32_t send_status = global_status_setup_send(p_server, p_rx_msg, &out_data);
            if (MESH_ERROR_NO_ERROR != send_status)
            {
                APP_LOG_ERROR("SERVER[%d] -- Publish status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
            }
        }
    }
}

static void generic_location_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;
    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<generic_location_setup_server_register_info.num_opcodes; i++)
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

/*
static void generic_location_setup_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args)
{
    generic_location_server_t * p_server = (generic_location_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * GENERIC_LOCATION_SERVER_TX_HDL_TOTAL)
    {
        case GENERIC_LOCATION_SERVER_RSP_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index)
                  : APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            break;
        case GENERIC_LOCATION_SERVER_PUBLISH_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("SERVER[%d] -- Published message!!!", p_server->model_instance_index)
                  : APP_LOG_INFO("SERVER[%d] -- Failed to published message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            break;
        default:
            APP_LOG_INFO("Never here!!!");
            break;
    }
}
*/
/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t generic_location_setup_server_init(generic_location_setup_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->location_cbs.set_global_cb
        || NULL == p_server->settings.p_callbacks->location_cbs.set_local_cb
        || GENERIC_LOCATION_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    generic_location_setup_server_register_info.p_args = p_server;
    generic_location_setup_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&generic_location_setup_server_register_info, &p_server->model_lid);
}

