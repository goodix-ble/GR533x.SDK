/**
 *****************************************************************************************
 *
 * @file light_xyl_setup_server.c
 *
 * @brief Light xyL Setup Server API Implementation.
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
#include "light_xyl_message.h"
#include "light_xyl_setup_server.h"
#include "grx_sys.h"
#include "common_utils.h"
/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_dft_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_range_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void light_xyl_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t light_xyl_setup_server_opcode_list[] =
{
    LIGHT_XYL_DEFAULT_OPCODE_SET,
    LIGHT_XYL_DEFAULT_OPCODE_SET_UNACKNOWLEDGED ,
    LIGHT_XYL_RANGE_OPCODE_SET,
    LIGHT_XYL_RANGE_OPCODE_SET_UNACKNOWLEDGED,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {LIGHT_XYL_DEFAULT_OPCODE_SET, handle_dft_set_cb},
    {LIGHT_XYL_DEFAULT_OPCODE_SET_UNACKNOWLEDGED, handle_dft_set_cb},
    {LIGHT_XYL_RANGE_OPCODE_SET, handle_range_set_cb},
    {LIGHT_XYL_RANGE_OPCODE_SET_UNACKNOWLEDGED, handle_range_set_cb},
};

static const mesh_model_cb_t light_xyl_setup_server_msg_cb = {
    .cb_rx             = light_xyl_setup_server_rx_cb,
    .cb_sent           = NULL,
    .cb_publish_period = NULL
};

static mesh_model_register_info_t light_xyl_setup_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_LIGHTS_XYLS),
    .element_offset = 0,
    .publish = false,
    .p_opcodes = (uint16_t *)light_xyl_setup_server_opcode_list,
    .num_opcodes = sizeof(light_xyl_setup_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &light_xyl_setup_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static uint16_t light_setup_message_send(light_xyl_setup_server_t * p_server,
                                                                const mesh_model_msg_ind_t *p_rx_msg,
                                                                uint16_t send_op,
                                                                uint8_t tx_hdl,
                                                                uint8_t *p_data_send,
                                                                uint16_t data_send_len)
{
    mesh_error_t status = MESH_ERROR_NO_ERROR;
    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->xyl_server->model_lid,
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

static uint16_t light_dft_status_send(light_xyl_setup_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const light_xyl_dft_status_params_t * p_params)
{
    light_xyl_dft_status_msg_pkt_t msg_pkt;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? LIGHT_XYL_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * LIGHT_XYL_SERVER_TX_HDL_TOTAL
                                        : LIGHT_XYL_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * LIGHT_XYL_SERVER_TX_HDL_TOTAL;

    APP_LOG_INFO("[%s] enter", __func__);

    gx_write16p((void const *)&(msg_pkt.ln), p_params->ln);
    gx_write16p((void const *)&(msg_pkt.x), p_params->x);
    gx_write16p((void const *)&(msg_pkt.y), p_params->y);

    return light_setup_message_send(p_server, p_rx_msg, LIGHT_XYL_DEFAULT_OPCODE_STATUS, tx_hdl, (uint8_t *)&msg_pkt, LIGHT_XYL_DEFAULT_STATUS_LEN);
}

static uint16_t light_range_status_send(light_xyl_setup_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const light_xyl_range_status_params_t * p_params)
{
    light_xyl_range_status_msg_pkt_t msg_pkt;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? LIGHT_XYL_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * LIGHT_XYL_SERVER_TX_HDL_TOTAL
                                        : LIGHT_XYL_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * LIGHT_XYL_SERVER_TX_HDL_TOTAL;

    APP_LOG_INFO("[%s] enter.", __func__);

    msg_pkt.status_code = p_params->status_code;
    gx_write16p((void const *)&(msg_pkt.range_min_x), p_params->range_min_x);
    gx_write16p((void const *)&(msg_pkt.range_max_x), p_params->range_max_x);
    gx_write16p((void const *)&(msg_pkt.range_min_y), p_params->range_min_y);
    gx_write16p((void const *)&(msg_pkt.range_max_y), p_params->range_max_y);

    return light_setup_message_send(p_server, p_rx_msg, LIGHT_XYL_RANGE_OPCODE_STATUS, tx_hdl, (uint8_t *)&msg_pkt, LIGHT_XYL_RANGE_STATUS_LEN);
}

static inline bool xyl_setup_params_validate(const mesh_model_msg_ind_t * p_rx_msg, const uint16_t opcode)
{
    return ((((opcode == LIGHT_XYL_DEFAULT_OPCODE_SET)
                        || (opcode == LIGHT_XYL_DEFAULT_OPCODE_SET_UNACKNOWLEDGED))
                        && (p_rx_msg->msg_len == LIGHT_XYL_DEFAULT_SET_LEN) )
            ||(((opcode == LIGHT_XYL_RANGE_OPCODE_SET)
                        || (opcode == LIGHT_XYL_RANGE_OPCODE_SET_UNACKNOWLEDGED))
                        && (p_rx_msg->msg_len == LIGHT_XYL_RANGE_SET_LEN) ));
}

static void handle_dft_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_xyl_setup_server_t * p_server = (light_xyl_setup_server_t *) p_args;

    APP_LOG_INFO("[%s] enter SERVER[%d] -- Receive message, want to set light xyL default state!!!", __func__, p_server->model_instance_index);

    if (xyl_setup_params_validate(p_rx_msg, p_rx_msg->opcode.company_opcode))
    {
        light_xyl_dft_set_params_t in_data = {0};
        light_xyl_dft_status_params_t out_data = {0};
        light_xyl_dft_set_msg_pkt_t * p_msg_params_packed = (light_xyl_dft_set_msg_pkt_t *) p_rx_msg->msg;

        in_data.ln = gx_read16p ((void const *)&p_msg_params_packed->ln);
        in_data.x = gx_read16p ((void const *)&p_msg_params_packed->x);
        in_data.y= gx_read16p ((void const *)&p_msg_params_packed->y);

        p_server->settings.p_callbacks->light_xyl_dft_cbs.set_cb(p_server,
                                                                p_rx_msg,
                                                                &in_data,
                                                                (p_rx_msg->opcode.company_opcode == LIGHT_XYL_DEFAULT_OPCODE_SET) ? ((void *)&out_data) : NULL);

        if (p_rx_msg->opcode.company_opcode == LIGHT_XYL_DEFAULT_OPCODE_SET)
        {
            (void) light_dft_status_send(p_server, p_rx_msg, &out_data);
        }
    }
}

static void handle_range_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_xyl_setup_server_t * p_server = (light_xyl_setup_server_t *) p_args;

    APP_LOG_INFO("[%s] enter SERVER[%d] -- Receive message, want to set light xyL range state!!!", __func__, p_server->model_instance_index);

    if (xyl_setup_params_validate(p_rx_msg, p_rx_msg->opcode.company_opcode))
    {
        light_xyl_set_range_params_t in_data = {0};
        light_xyl_range_status_params_t out_data = {0};
        light_xyl_set_range_msg_pkt_t * p_msg_params_packed = (light_xyl_set_range_msg_pkt_t *) p_rx_msg->msg;

        in_data.range_max_x = gx_read16p ((void const *)&p_msg_params_packed->range_max_x);
        in_data.range_min_x = gx_read16p ((void const *)&p_msg_params_packed->range_min_x);
        in_data.range_max_y = gx_read16p ((void const *)&p_msg_params_packed->range_max_y);
        in_data.range_min_y = gx_read16p ((void const *)&p_msg_params_packed->range_min_y);

        p_server->settings.p_callbacks->light_xyl_range_cbs.set_cb(p_server,
                                                                    p_rx_msg,
                                                                    &in_data,
                                                                    (p_rx_msg->opcode.company_opcode == LIGHT_XYL_RANGE_OPCODE_SET) ? ((void *)&out_data) : NULL);

        if ((p_rx_msg->opcode.company_opcode == LIGHT_XYL_RANGE_OPCODE_SET) && (out_data.status_code == STATUS_CODES_SUCCESS))
        {
            uint32_t send_status = light_range_status_send(p_server, p_rx_msg, &out_data);
            if (MESH_ERROR_NO_ERROR != send_status)
            {
                APP_LOG_ERROR("SERVER[%d] -- Publish status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
            }
        }
    }
}

static void light_xyl_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<light_xyl_setup_server_register_info.num_opcodes; i++)
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
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t light_xyl_setup_server_init(light_xyl_setup_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->light_xyl_dft_cbs.set_cb
        || NULL == p_server->settings.p_callbacks->light_xyl_range_cbs.set_cb
        || LIGHT_XYL_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)        
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    light_xyl_setup_server_register_info.p_args = p_server;
    light_xyl_setup_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&light_xyl_setup_server_register_info, &p_server->model_lid);
}

