/**
 *****************************************************************************************
 *
 * @file generic_power_level_server.c
 *
 * @brief Generic Power Level Server API Implementation.
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
#include "generic_power_level_message.h"
#include "generic_power_level_server.h"
#include "grx_sys.h"
#include "common_utils.h"
/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void generic_power_level_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void generic_power_level_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t generic_power_level_server_opcode_list[] =
{
    GENERIC_POWER_LEVEL_OPCODE_GET,
    GENERIC_POWER_LEVEL_OPCODE_SET ,
    GENERIC_POWER_LEVEL_OPCODE_SET_UNACKNOWLEDGED,
    GENERIC_POWER_LEVEL_LAST_OPCODE_GET,
    GENERIC_POWER_LEVEL_DEFAULT_OPCODE_GET,
    GENERIC_POWER_LEVEL_RANGE_OPCODE_GET,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {GENERIC_POWER_LEVEL_OPCODE_GET, handle_get_cb},
    {GENERIC_POWER_LEVEL_OPCODE_SET, handle_set_cb},
    {GENERIC_POWER_LEVEL_OPCODE_SET_UNACKNOWLEDGED, handle_set_cb},
    {GENERIC_POWER_LEVEL_LAST_OPCODE_GET, handle_get_cb},
    {GENERIC_POWER_LEVEL_DEFAULT_OPCODE_GET, handle_get_cb},
    {GENERIC_POWER_LEVEL_RANGE_OPCODE_GET, handle_get_cb},
};

static const mesh_model_cb_t generic_power_level_server_msg_cb = {
    .cb_rx             = generic_power_level_server_rx_cb,
    .cb_sent           = generic_power_level_server_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t generic_power_level_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_GENS_PLVL),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)generic_power_level_server_opcode_list,
    .num_opcodes = sizeof(generic_power_level_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &generic_power_level_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static uint32_t status_send(generic_power_level_server_t * p_server,
                            const mesh_model_msg_ind_t *p_rx_msg,
                            const generic_power_level_status_params_u * p_params)
{
    APP_LOG_INFO("[%s] enter, send generic power level status.", __func__);
    
    generic_power_level_status_msg_pkt_t *msg_pkt = NULL;
    generic_power_level_last_status_msg_pkt_t *msg_pkt_last = NULL;
    generic_power_level_dft_status_msg_pkt_t *msg_pkt_dft = NULL;
    generic_power_level_range_status_msg_pkt_t *msg_pkt_range = NULL;
    uint8_t *p_send_data = NULL;
    uint16_t send_op = GENERIC_POWER_LEVEL_OPCODE_STATUS;
    uint16_t data_send_len = 0;
    mesh_error_t status = MESH_ERROR_SDK_INVALID_PARAM;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? GENERIC_POWER_LEVEL_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * GENERIC_POWER_LEVEL_SERVER_TX_HDL_TOTAL
                                        : GENERIC_POWER_LEVEL_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * GENERIC_POWER_LEVEL_SERVER_TX_HDL_TOTAL;

    if (NULL != p_rx_msg)
    {
        switch(p_rx_msg->opcode.company_opcode)
        {
            case GENERIC_POWER_LEVEL_OPCODE_GET:
            case GENERIC_POWER_LEVEL_OPCODE_SET:
                msg_pkt = (generic_power_level_status_msg_pkt_t *)sys_malloc(sizeof(generic_power_level_status_msg_pkt_t));
                p_send_data = (uint8_t *)msg_pkt;

                if(NULL == p_send_data)
                {
                    return MESH_ERROR_INSUFFICIENT_RESOURCES;
                }

                if (p_params->power.remaining_time_ms > TRANSITION_TIME_STEP_10M_MAX)
                {
                    return MESH_ERROR_SDK_INVALID_PARAM;
                }

                gx_write16p( (void const *)&(msg_pkt->present_power), p_params->power.present_power);
                data_send_len += 2;
                if (p_params->power.remaining_time_ms > 0)
                {
                    gx_write16p( (void const *)&(msg_pkt->target_power), p_params->power.target_power);
                    msg_pkt->remaining_time = model_transition_time_encode(p_params->power.remaining_time_ms);
                    data_send_len += 3;
                }
            break;

            case GENERIC_POWER_LEVEL_LAST_OPCODE_GET:
                send_op = GENERIC_POWER_LEVEL_LAST_OPCODE_STATUS;
                msg_pkt_last = (generic_power_level_last_status_msg_pkt_t *)sys_malloc(sizeof(generic_power_level_last_status_msg_pkt_t));
                p_send_data = (uint8_t *)msg_pkt_last;
                if(NULL == p_send_data)
                {
                    return MESH_ERROR_INSUFFICIENT_RESOURCES;
                }

                gx_write16p( (void const *)&(msg_pkt_last->power), p_params->power_last.power);
                data_send_len += 2;
            break;

            case GENERIC_POWER_LEVEL_DEFAULT_OPCODE_GET:
                send_op = GENERIC_POWER_LEVEL_DEFAULT_OPCODE_STATUS;
                msg_pkt_dft = (generic_power_level_dft_status_msg_pkt_t *)sys_malloc(sizeof(generic_power_level_dft_status_msg_pkt_t));
                p_send_data = (uint8_t *)msg_pkt_dft;
                if(NULL == p_send_data)
                {
                    return MESH_ERROR_INSUFFICIENT_RESOURCES;
                }

                gx_write16p( (void const *)&(msg_pkt_dft->power), p_params->power_dft.power);
                data_send_len += 2;
            break;

            case GENERIC_POWER_LEVEL_RANGE_OPCODE_GET:
                send_op = GENERIC_POWER_LEVEL_RANGE_OPCODE_STATUS;
                msg_pkt_range = (generic_power_level_range_status_msg_pkt_t *)sys_malloc(sizeof(generic_power_level_range_status_msg_pkt_t));
                p_send_data = (uint8_t *)msg_pkt_range;
                if(NULL == p_send_data)
                {
                    return MESH_ERROR_INSUFFICIENT_RESOURCES;
                }

                msg_pkt_range->status_code = p_params->power_range.status_code;
                data_send_len += 1;
                gx_write16p( (void const *)&(msg_pkt_range->min_power), p_params->power_range.min_power);
                data_send_len += 2;
                gx_write16p( (void const *)&(msg_pkt_range->max_power), p_params->power_range.max_power);
                data_send_len += 2;
            break;

            default:
            break;
        }
    }
    else
    {
        send_op = GENERIC_POWER_LEVEL_OPCODE_STATUS;
        msg_pkt = (generic_power_level_status_msg_pkt_t *)sys_malloc(sizeof(generic_power_level_status_msg_pkt_t));
        p_send_data = (uint8_t *)msg_pkt;

        if(NULL == p_send_data)
        {
            return MESH_ERROR_INSUFFICIENT_RESOURCES;
        }

        gx_write16p( (void const *)&(msg_pkt->present_power), p_params->power.present_power);
        data_send_len += 2;
        if (p_params->power.remaining_time_ms > 0)
        {
            gx_write16p( (void const *)&(msg_pkt->target_power), p_params->power.target_power);
            msg_pkt->remaining_time = model_transition_time_encode(p_params->power.remaining_time_ms);
            data_send_len += 3;
        }
    }

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(send_op),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) p_send_data,
        .data_send_len = data_send_len,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };


    if (NULL == p_rx_msg)
    {
        APP_LOG_INFO("SERVER[%d] -- to publish , send opcode:%04X, data length:%d.",
                p_server->model_instance_index, send_op, data_send_len);
        status = mesh_model_publish(&msg_send, NULL);
    }
    else
    {
        APP_LOG_INFO("SERVER[%d] -- to response , recv opcode:%04X, response opcode:%04X, data length:%d.",
                p_server->model_instance_index, p_rx_msg->opcode.company_opcode, send_op, data_send_len);
        status = mesh_model_rsp_send(&msg_send);
    }

    if(p_send_data)
    {
        sys_free(p_send_data);
        p_send_data = NULL;
    }

    return status;
}

static inline bool set_params_validate(const mesh_model_msg_ind_t * p_rx_msg)
{
    return (p_rx_msg->msg_len == GENERIC_POWER_LEVEL_SET_MINLEN 
                    || p_rx_msg->msg_len == GENERIC_POWER_LEVEL_SET_MAXLEN);
}

static void handle_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    generic_power_level_server_t  * p_server = (generic_power_level_server_t  *) p_args;

    APP_LOG_INFO("SERVER[%d] -- Receive message, want to set Generic Power Level state!!!", p_server->model_instance_index);

    if (set_params_validate(p_rx_msg))
    {
        generic_power_level_state_set_cb_t set_cb_local = NULL;
        generic_power_level_set_params_t in_data = {0};
        model_transition_t in_data_tr = {0};
        generic_power_level_status_params_u out_data = {0};
        generic_power_level_set_msg_pkt_t * p_msg_params_packed = (generic_power_level_set_msg_pkt_t *) p_rx_msg->msg;
        bool ack_flag = false;
        if (GENERIC_POWER_LEVEL_OPCODE_SET == p_rx_msg->opcode.company_opcode)
        {
            ack_flag = true;
        }

        in_data.power = gx_read16p ((void const *)&p_msg_params_packed->power);
        in_data.tid = p_msg_params_packed->tid;

        if (model_tid_validate(&p_server->tid_tracker, p_rx_msg, p_rx_msg->opcode.company_opcode, in_data.tid))
        {
            if (p_rx_msg->msg_len == GENERIC_POWER_LEVEL_SET_MAXLEN)
            {
                if (!model_transition_time_is_valid(p_msg_params_packed->transition_time))
                {
                    return;
                }

                in_data_tr.transition_time_ms = model_transition_time_decode(p_msg_params_packed->transition_time);
                in_data_tr.delay_ms = model_delay_decode(p_msg_params_packed->delay);
                APP_LOG_INFO("SERVER[%d] -- transition_time_ms = %d", p_server->model_instance_index, in_data_tr.transition_time_ms);
                APP_LOG_INFO("SERVER[%d] -- delay_ms = %d", p_server->model_instance_index, in_data_tr.delay_ms);
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
            set_cb_local = p_server->settings.p_callbacks->generic_power_level_cbs.set_cb;

            if (NULL != set_cb_local)
            {
                set_cb_local(p_server,
                             p_rx_msg,
                             &in_data,
                             ((p_rx_msg->msg_len == GENERIC_POWER_LEVEL_SET_MINLEN)&&(p_server->p_dtt_ms == NULL)) ? NULL : &in_data_tr,
                             (ack_flag) ? &out_data : NULL);
            }
            
            if (p_rx_msg->opcode.company_opcode == GENERIC_POWER_LEVEL_OPCODE_SET)
            {
                uint32_t send_status = status_send(p_server, p_rx_msg, &out_data);
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

static void handle_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    generic_power_level_server_t * p_server = (generic_power_level_server_t *) p_args;
    generic_power_level_status_params_u out_data = {0};
    generic_power_level_state_get_cb_t get_cb_local = NULL;

    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get state opcode %04X!!!", p_server->model_instance_index, p_rx_msg->opcode.company_opcode);

    if (get_params_validate(p_rx_msg))
    {
        switch (p_rx_msg->opcode.company_opcode)
        {
            case GENERIC_POWER_LEVEL_OPCODE_GET:
                get_cb_local = p_server->settings.p_callbacks->generic_power_level_cbs.get_cb;
                break;

            case GENERIC_POWER_LEVEL_LAST_OPCODE_GET:
                get_cb_local = p_server->settings.p_callbacks->generic_power_level_last_cbs.get_cb;
                break;

            case GENERIC_POWER_LEVEL_DEFAULT_OPCODE_GET:
                get_cb_local = p_server->settings.p_callbacks->generic_power_level_dft_cbs.get_cb;
                break;

            case GENERIC_POWER_LEVEL_RANGE_OPCODE_GET:
                get_cb_local = p_server->settings.p_callbacks->generic_power_level_range_cbs.get_cb;
                break;

            default:
                break;
        }

        if(get_cb_local)
        {
            get_cb_local(p_server, p_rx_msg, &out_data);
            uint32_t send_status = status_send(p_server, p_rx_msg, &out_data);
            if (MESH_ERROR_NO_ERROR != send_status)
            {
                APP_LOG_ERROR("SERVER[%d] -- Response status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
            }
        }
    }
}

static void generic_power_level_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<generic_power_level_server_register_info.num_opcodes; i++)
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

static void generic_power_level_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    generic_power_level_server_t * p_server = (generic_power_level_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * GENERIC_POWER_LEVEL_SERVER_TX_HDL_TOTAL)
    {
        case GENERIC_POWER_LEVEL_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case GENERIC_POWER_LEVEL_SERVER_PUBLISH_SEND_TX_HDL:
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

uint16_t generic_power_level_server_init(generic_power_level_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->generic_power_level_cbs.get_cb
        || NULL == p_server->settings.p_callbacks->generic_power_level_cbs.set_cb
        || NULL == p_server->settings.p_callbacks->generic_power_level_dft_cbs.get_cb
        || NULL == p_server->settings.p_callbacks->generic_power_level_last_cbs.get_cb
        || NULL == p_server->settings.p_callbacks->generic_power_level_range_cbs.get_cb
        || GENERIC_POWER_LEVEL_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)        
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    generic_power_level_server_register_info.p_args = p_server;
    generic_power_level_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&generic_power_level_server_register_info, &p_server->model_lid);
}

uint16_t generic_power_level_server_status_publish(generic_power_level_server_t * p_server, 
                                                            const generic_power_level_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return status_send(p_server, NULL, (const generic_power_level_status_params_u *)p_params);
}

