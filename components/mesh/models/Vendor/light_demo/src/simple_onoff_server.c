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

//static void handle_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
//static void handle_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_light_demo_server_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void simple_on_off_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void simple_on_off_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);
static void publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args);

extern void light_demo_pkt_loss_check_stop(void);
extern void light_demo_pkt_loss_check_task(simple_onoff_server_t * p_server, uint16_t pkt_loss_check_id);
extern bool light_demo_pkt_loss_check_begin(uint16_t max_pkt);
extern void light_demo_pkt_loss_check_reset(void);
extern void light_demo_report_pkt_loss(simple_onoff_server_t * p_server);

extern uint16_t pkt_loss_check_total_pkt;

static uint16_t light_demo_model_total_rx_pkt = 0;
/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t simple_on_off_server_opcode_list[] =
{
    //light demo opcode
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_SET_COLOR,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_SET_BACK_ONOFF,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_CHECK_TRANS_DELAY,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_REPORT_TRANS_DELAY,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_CHECK_PKT_LOSS,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_REPORT_PKT_LOSS,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_CHECK_TOTAL_PKT,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_REPORT_TOTAL_PKT,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_RESET_TOTAL_PKT,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_BEGIN_SYNC_CLOCK,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_REPORT_KEY_EVENT,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_BEGIN_UPGRADE,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_SET_COLOR_DISK,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_SET_DISK_COLOR,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_DISPLAY_PRIM_ADDR,
    LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_SEND_TEST_DATA
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    //light demo opcode
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_SET_COLOR, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_SET_BACK_ONOFF, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_CHECK_TRANS_DELAY, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_REPORT_TRANS_DELAY, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_CHECK_PKT_LOSS, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_REPORT_PKT_LOSS, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_CHECK_TOTAL_PKT, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_REPORT_TOTAL_PKT, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_RESET_TOTAL_PKT, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_BEGIN_SYNC_CLOCK, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_REPORT_KEY_EVENT, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_BEGIN_UPGRADE, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_SET_COLOR_DISK, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_SET_DISK_COLOR, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_DISPLAY_PRIM_ADDR, handle_light_demo_server_cb},
    {LIGHT_DEMO_OPCODE_BASE_C_PART|LIGHT_DEMO_OPCODE_SEND_TEST_DATA, handle_light_demo_server_cb},
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
static uint32_t demo_status_send(simple_onoff_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const light_demo_set_msg_pkt_t * p_params)
{
    light_demo_set_msg_pkt_t msg_pkt;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? SIMPLE_ONOFF_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * SIMPLE_ONOFF_SERVER_TX_HDL_TOTAL
                                        : SIMPLE_ONOFF_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * SIMPLE_ONOFF_SERVER_TX_HDL_TOTAL;

    msg_pkt.light_demo_opcode = p_params->light_demo_opcode;
    msg_pkt.buf_len = p_params->buf_len;
    if(p_params->buf_len != 0)
    {
        memcpy(msg_pkt.buf, p_params->buf, p_params->buf_len);
    }

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(p_params->light_demo_opcode |LIGHT_DEMO_OPCODE_BASE_S_PART),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) &msg_pkt,
        .data_send_len = msg_pkt.buf_len + 4,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };

    APP_LOG_INFO("SERVER[%d] -- opcode = 0x%04X.", p_server->model_instance_index, msg_pkt.light_demo_opcode);

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

static uint32_t  simple_light_demo_proc(simple_onoff_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const light_demo_set_msg_pkt_t * p_params)
{
    uint32_t send_status = MESH_ERROR_NO_ERROR;
    uint16_t opcode = p_rx_msg->opcode.company_opcode & 0xFF;
    light_demo_set_msg_pkt_t out_data;

    switch(opcode)
    {
        case LIGHT_DEMO_OPCODE_CHECK_TRANS_DELAY:
        {
            //send_status = light_demo_check_delay_rsp(p_server, p_rx_msg, p_params);
            send_status = demo_status_send(p_server, NULL, p_params);
            break;
        }
        case LIGHT_DEMO_OPCODE_CHECK_PKT_LOSS:
        {
            uint32_t status = MESH_ERROR_NO_ERROR;
            uint16_t max_pkt_num = p_params->buf[0]|(p_params->buf[1]<<8);
            uint32_t total_timeout = max_pkt_num * (p_params->buf[2]|(p_params->buf[3]<<8));

            if (light_demo_pkt_loss_check_begin(max_pkt_num))
            {
                p_server->light_demo_timer.delay_ms = total_timeout + 500;//addition more 10s for last message retry
                status = mesh_timer_set(&(p_server->light_demo_timer));

                APP_LOG_INFO("begin to checkout packet loss, max number is %d, %d, ", max_pkt_num, (p_params->buf[2]|(p_params->buf[3]<<8)));
            }
            else
            {
                status = MESH_ERROR_SDK_INVALID_PARAM;
            }

            out_data.light_demo_opcode = p_params->light_demo_opcode;
            out_data.buf_len = 2;
            out_data.buf[0] = status%0xFF;
            out_data.buf[1] = (status>>8)&0xFF;
            send_status = demo_status_send(p_server, NULL, &out_data);
            break;
        }
        case LIGHT_DEMO_OPCODE_CHECK_TOTAL_PKT:
        {
            out_data.light_demo_opcode = LIGHT_DEMO_OPCODE_REPORT_TOTAL_PKT;
            out_data.buf_len = 2;
            out_data.buf[0] = light_demo_model_total_rx_pkt%0xFF;
            out_data.buf[1] = (light_demo_model_total_rx_pkt>>8)&0xFF;
            send_status = demo_status_send(p_server, NULL, &out_data);
            break;
        }
        case LIGHT_DEMO_OPCODE_RESET_TOTAL_PKT:
        {
            light_demo_model_total_rx_pkt = 0;
            break;
        }
        case LIGHT_DEMO_OPCODE_BEGIN_SYNC_CLOCK:
            break;
        case LIGHT_DEMO_OPCODE_SET_COLOR_DISK:
        {
            out_data.light_demo_opcode = p_params->light_demo_opcode;
            out_data.buf_len = 1;
            out_data.buf[0] = 00;
            send_status = demo_status_send(p_server, NULL, &out_data);
            break;
        }
        case LIGHT_DEMO_OPCODE_SEND_TEST_DATA:
        {
            uint16_t check_sent_pkt_id = p_params->buf[0]|(p_params->buf[1]<<8);
            light_demo_pkt_loss_check_task(p_server, check_sent_pkt_id);
            break;
        }
    }

    if (MESH_ERROR_NO_ERROR != send_status)
    {
        APP_LOG_WARNING("SERVER[%d] -- Response status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
    }
    
    return send_status;
}

static void handle_light_demo_server_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    simple_onoff_server_t  * p_server = (simple_onoff_server_t  *) p_args;    
    light_demo_set_msg_pkt_t * p_msg_params_packed = (light_demo_set_msg_pkt_t *) p_rx_msg->msg;

    APP_LOG_INFO("SERVER[%d] -- Receive message, want to set 0x%04X state!!!", p_server->model_instance_index, p_msg_params_packed->light_demo_opcode);

    if (p_msg_params_packed->light_demo_opcode < LIGHT_DEMO_OPCODE_SET_MAX)
    {
        light_demo_set_params_t light_set_param;

        light_set_param.light_demo_opcode = p_msg_params_packed->light_demo_opcode;
        light_set_param.buf_len = p_msg_params_packed->buf_len;
        memcpy(light_set_param.buf, p_msg_params_packed->buf, p_msg_params_packed->buf_len);

        p_server->client_address = p_rx_msg->src;

        if (p_server->settings.p_callbacks->onoff_cbs.light_demo_cb)
        {
            p_server->settings.p_callbacks->onoff_cbs.light_demo_cb(p_server->model_instance_index, &light_set_param);
        }

        simple_light_demo_proc(p_server, p_rx_msg, p_msg_params_packed);
    }
}


static void simple_on_off_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    APP_LOG_INFO("server rx opcode 0x%04X!!!", company_opcode);
    mesh_opcode_handler_cb_t handler = m_opcode_handlers[company_opcode - m_opcode_handlers[0].opcode].handler;

    if (NULL != handler)
    {
        light_demo_model_total_rx_pkt ++;
        handler(p_model_msg, p_args);
    }
}

static void simple_on_off_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    simple_onoff_server_t * p_server = (simple_onoff_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * SIMPLE_ONOFF_SERVER_TX_HDL_TOTAL)
    {
        case SIMPLE_ONOFF_SERVER_RSP_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index)
                  : APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            break;
        case SIMPLE_ONOFF_SERVER_PUBLISH_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("SERVER[%d] -- Published message!!!", p_server->model_instance_index)
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

static void light_demo_timer_cb(void * p_context)
{
    APP_LOG_INFO("[%s] enter:pkt loss check timeout,  report result !! ", __func__);
    
    simple_onoff_server_t * p_server = (simple_onoff_server_t *) p_context;

    mesh_timer_clear(&p_server->light_demo_timer.timer_id);

    light_demo_pkt_loss_check_stop();

    light_demo_report_pkt_loss(p_server);

    light_demo_pkt_loss_check_reset();
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

    p_server->light_demo_timer.callback = light_demo_timer_cb;
    p_server->light_demo_timer.p_args = p_server;
    p_server->light_demo_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->light_demo_timer.reload = false;

    simple_on_off_server_register_info.p_args = p_server;
    simple_on_off_server_register_info.element_offset = element_offset;
    
    return mesh_model_register(&simple_on_off_server_register_info, &p_server->model_lid);
}

uint16_t light_demo_server_status_publish(simple_onoff_server_t * p_server, const light_demo_set_msg_pkt_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return demo_status_send(p_server, NULL, p_params);
}

