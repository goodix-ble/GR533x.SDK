/**
 *****************************************************************************************
 *
 * @file light_ctl_server.c
 *
 * @brief Light CTL Server API Implementation.
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
#include "light_ctl_message.h"
#include "light_ctl_server.h"
#include "grx_sys.h"
#include "common_utils.h"
/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_ctl_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_ctl_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_temp_range_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_dft_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void light_ctl_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void light_ctl_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t light_ctl_server_opcode_list[] =
{
    LIGHT_CTL_OPCODE_GET,
    LIGHT_CTL_OPCODE_SET ,
    LIGHT_CTL_OPCODE_SET_UNACKNOWLEDGED,
    LIGHT_CTL_TEMP_RANGE_OPCODE_GET,
    LIGHT_CTL_DFT_OPCODE_GET,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {LIGHT_CTL_OPCODE_GET, handle_ctl_get_cb},
    {LIGHT_CTL_OPCODE_SET, handle_ctl_set_cb},
    {LIGHT_CTL_OPCODE_SET_UNACKNOWLEDGED, handle_ctl_set_cb},
    {LIGHT_CTL_TEMP_RANGE_OPCODE_GET, handle_temp_range_get_cb},
    {LIGHT_CTL_DFT_OPCODE_GET, handle_dft_get_cb}
};

static const mesh_model_cb_t light_ctl_server_msg_cb = {
    .cb_rx             = light_ctl_server_rx_cb,
    .cb_sent           = light_ctl_server_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t light_ctl_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_LIGHTS_CTL),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)light_ctl_server_opcode_list,
    .num_opcodes = sizeof(light_ctl_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &light_ctl_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static mesh_error_t light_ctl_message_send(light_ctl_server_t * p_server,
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

static uint16_t light_ctl_status_send(light_ctl_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const light_ctl_status_params_t * p_params)
{
    light_ctl_status_msg_pkt_t msg_pkt;
    uint16_t data_send_len = LIGHT_CTL_STATUS_MINLEN;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? LIGHT_CTL_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * LIGHT_CTL_SERVER_TX_HDL_TOTAL
                                        : LIGHT_CTL_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * LIGHT_CTL_SERVER_TX_HDL_TOTAL;

    APP_LOG_INFO("[%s] enter, send ctl status.", __func__);

    if (p_params->present_ctl_temp > LIGHT_CTL_TEMPERATURE_MAX ||
        p_params->present_ctl_temp  < LIGHT_CTL_TEMPERATURE_MIN ||
        p_params->remaining_time_ms > TRANSITION_TIME_STEP_10M_MAX)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    gx_write16p((void const *)&(msg_pkt.present_ctl_ln), p_params->present_ctl_ln);
    gx_write16p((void const *)&(msg_pkt.present_ctl_temp), p_params->present_ctl_temp);

    if (p_params->remaining_time_ms >0)
    {
        gx_write16p((void const *)&(msg_pkt.target_ctl_ln), p_params->target_ctl_ln);
        gx_write16p((void const *)&(msg_pkt.target_ctl_temp), p_params->target_ctl_temp);
        msg_pkt.remaining_time = model_transition_time_encode(p_params->remaining_time_ms);
        data_send_len = LIGHT_CTL_STATUS_MAXLEN;
    }

    return light_ctl_message_send(p_server, p_rx_msg, LIGHT_CTL_OPCODE_STATUS, tx_hdl, (uint8_t *)&msg_pkt, data_send_len);
}

static uint16_t light_ctl_temp_range_status_send(light_ctl_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const light_ctl_range_status_params_t * p_params)
{
    light_ctl_range_status_msg_pkt_t msg_pkt;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? LIGHT_CTL_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * LIGHT_CTL_SERVER_TX_HDL_TOTAL
                                        : LIGHT_CTL_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * LIGHT_CTL_SERVER_TX_HDL_TOTAL;

    APP_LOG_INFO("[%s] enter, send ctl temp status.", __func__);

    msg_pkt.status_code = p_params->status_code;
    gx_write16p((void const *)&(msg_pkt.range_max), p_params->range_max);
    gx_write16p((void const *)&(msg_pkt.range_min), p_params->range_min);

    return light_ctl_message_send(p_server, p_rx_msg, LIGHT_CTL_TEMP_RANGE_OPCODE_STATUS, tx_hdl, (uint8_t *)&msg_pkt, LIGHT_CTL_RANGE_STATUS_LEN);    
}

static uint16_t light_ctl_dft_status_send(light_ctl_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const light_ctl_dft_status_params_t * p_params)
{
    light_ctl_dft_status_msg_pkt_t msg_pkt;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? LIGHT_CTL_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * LIGHT_CTL_SERVER_TX_HDL_TOTAL
                                        : LIGHT_CTL_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * LIGHT_CTL_SERVER_TX_HDL_TOTAL;

    APP_LOG_INFO("[%s] enter, send ctl default status.", __func__);

    gx_write16p((void const *)&(msg_pkt.ln), p_params->ln);
    gx_write16p((void const *)&(msg_pkt.temp), p_params->temp);
    gx_write16p((void const *)&(msg_pkt.dlt_uv), p_params->dlt_uv);

    return light_ctl_message_send(p_server, p_rx_msg, LIGHT_CTL_DFT_OPCODE_STATUS, tx_hdl, (uint8_t *)&msg_pkt, LIGHT_CTL_DFT_STATUS_LEN);    
}

static inline bool ctl_set_params_validate(const mesh_model_msg_ind_t * p_rx_msg, const uint16_t opcode)
{
    return (((opcode == LIGHT_CTL_OPCODE_SET)
                        || (opcode == LIGHT_CTL_OPCODE_SET_UNACKNOWLEDGED))
                    && (p_rx_msg->msg_len == LIGHT_CTL_SET_MINLEN 
                        || p_rx_msg->msg_len == LIGHT_CTL_SET_MAXLEN) );
            
}

static void handle_ctl_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_ctl_server_t * p_server = (light_ctl_server_t *) p_args;

    APP_LOG_INFO("SERVER[%d] -- Receive message, want to set light ctl state!!!", p_server->model_instance_index);

    if (ctl_set_params_validate(p_rx_msg, p_rx_msg->opcode.company_opcode))
    {
        light_ctl_set_params_t in_data = {0};
        model_transition_t in_data_tr = {0};
        light_ctl_status_params_t out_data = {0};
        light_ctl_set_msg_pkt_t * p_msg_params_packed = (light_ctl_set_msg_pkt_t *) p_rx_msg->msg;

        in_data.ctl_ln= gx_read16p ((void const *)&p_msg_params_packed->ctl_ln);
        in_data.ctl_temp = gx_read16p ((void const *)&p_msg_params_packed->ctl_temp);
        in_data.ctl_dlt_uv = gx_read16p ((void const *)&p_msg_params_packed->ctl_dlt_uv);
        in_data.tid = p_msg_params_packed->tid;

        if ((LIGHT_CTL_TEMPERATURE_MIN > in_data.ctl_temp) ||(LIGHT_CTL_TEMPERATURE_MAX < in_data.ctl_temp))
        {
            //invalid param, do nothing.
            return ;
        }

        if (model_tid_validate(&p_server->tid_tracker, p_rx_msg, p_rx_msg->opcode.company_opcode, in_data.tid))
        {
            if (p_rx_msg->msg_len == LIGHT_CTL_SET_MAXLEN)
            {
                if (!model_transition_time_is_valid(p_msg_params_packed->transition_time))
                {
                    return;
                }

                in_data_tr.transition_time_ms = model_transition_time_decode(p_msg_params_packed->transition_time);
                in_data_tr.delay_ms = model_delay_decode(p_msg_params_packed->delay);
                APP_LOG_INFO("SERVER[%d] -- transition_time_ms = %d, delay_ms = %d", p_server->model_instance_index, in_data_tr.transition_time_ms, in_data_tr.delay_ms);
            }
            else
            {
                if (p_server->p_dtt_ms == NULL)
                {
                    model_update_dtt_ptr(&(p_server->p_dtt_ms));
                }

                if (p_server->p_dtt_ms != NULL)
                {
                    in_data_tr.transition_time_ms = model_transition_time_decode(*p_server->p_dtt_ms);
                    in_data_tr.delay_ms = 0;

                    APP_LOG_INFO("SERVER[%d] -- default transition time = %d", p_server->model_instance_index, in_data_tr.transition_time_ms);
                }
            }
            p_server->settings.p_callbacks->light_ctl_cbs.set_cb(p_server,
                                                                                            p_rx_msg,
                                                                                            &in_data,
                                                                                            ((p_rx_msg->msg_len == LIGHT_CTL_SET_MINLEN)&&(p_server->p_dtt_ms == NULL)) ? NULL : &in_data_tr,
                                                                                            (p_rx_msg->opcode.company_opcode == LIGHT_CTL_OPCODE_SET) ? ((void *)&out_data) : NULL);

            if (p_rx_msg->opcode.company_opcode == LIGHT_CTL_OPCODE_SET)
            {
                uint16_t send_status = light_ctl_status_send(p_server, p_rx_msg, &out_data);
                if (MESH_ERROR_NO_ERROR != send_status)
                {
                    APP_LOG_ERROR("SERVER[%d] -- Response status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
                }
            }
        }
    }
}

static inline bool get_params_validate(const mesh_model_msg_ind_t * p_rx_msg)
{
    return (p_rx_msg->msg_len == 0);
}

static void handle_ctl_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_ctl_server_t * p_server = (light_ctl_server_t *) p_args;
    light_ctl_status_params_t out_data = {0};
  
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get light ctl state!!!", p_server->model_instance_index);

    if (get_params_validate(p_rx_msg))
    {
        p_server->settings.p_callbacks->light_ctl_cbs.get_cb(p_server, p_rx_msg, (void *)&out_data);
        uint16_t send_status = light_ctl_status_send(p_server, p_rx_msg, &out_data);
        if (MESH_ERROR_NO_ERROR != send_status)
        {
            APP_LOG_ERROR("SERVER[%d] -- Response status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
        }
    }
}

static void handle_temp_range_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_ctl_server_t * p_server = (light_ctl_server_t *) p_args;
    light_ctl_range_status_params_t out_data = {0};
    
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get light ctl range state!!!", p_server->model_instance_index);    

    if (get_params_validate(p_rx_msg))
    {
        p_server->settings.p_callbacks->light_ctl_temp_range_cbs.get_cb(p_server, p_rx_msg, (void *)&out_data);
        uint16_t send_status = light_ctl_temp_range_status_send(p_server, p_rx_msg, &out_data);
        if (MESH_ERROR_NO_ERROR != send_status)
        {
            APP_LOG_ERROR("SERVER[%d] -- Response status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
        }
    }
}

static void handle_dft_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_ctl_server_t * p_server = (light_ctl_server_t *) p_args;
    light_ctl_dft_status_params_t out_data = {0};

    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get light ctl default state!!!", p_server->model_instance_index);   

    if (get_params_validate(p_rx_msg))
    {
        p_server->settings.p_callbacks->light_ctl_dft_cbs.get_cb(p_server, p_rx_msg, (void *)&out_data);
        uint16_t send_status = light_ctl_dft_status_send(p_server, p_rx_msg, &out_data);
        if (MESH_ERROR_NO_ERROR != send_status)
        {
            APP_LOG_ERROR("SERVER[%d] -- Response status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
        }
    }
}

static void light_ctl_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<light_ctl_server_register_info.num_opcodes; i++)
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

static void light_ctl_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    light_ctl_server_t * p_server = (light_ctl_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * LIGHT_CTL_SERVER_TX_HDL_TOTAL)
    {
        case LIGHT_CTL_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case LIGHT_CTL_SERVER_PUBLISH_SEND_TX_HDL:
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

uint16_t light_ctl_server_init(light_ctl_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->light_ctl_cbs.get_cb
        || NULL == p_server->settings.p_callbacks->light_ctl_cbs.set_cb
        || NULL == p_server->settings.p_callbacks->light_ctl_dft_cbs.get_cb
        || NULL == p_server->settings.p_callbacks->light_ctl_temp_range_cbs.get_cb
        || LIGHT_CTL_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    light_ctl_server_register_info.p_args = p_server;
    light_ctl_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&light_ctl_server_register_info, &p_server->model_lid);
}

uint16_t light_ctl_server_status_publish(light_ctl_server_t * p_server, 
                                                            const light_ctl_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return light_ctl_status_send(p_server, NULL, p_params);
}

