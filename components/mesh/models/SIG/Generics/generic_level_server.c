/**
 ****************************************************************************************
 *
 * @file generic_level_server.c
 *
 * @brief Generic Level Server API Implementation.
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
#include "generic_level_message.h"
#include "generic_level_server.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */


static void handle_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_delta_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_move_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void generic_level_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void generic_level_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
static const uint16_t generic_level_server_opcode_list[] =
{
    GENERIC_LEVEL_OPCODE_GET,
    GENERIC_LEVEL_OPCODE_SET,
    GENERIC_LEVEL_OPCODE_SET_UNACKNOWLEDGED,
    GENERIC_LEVEL_OPCODE_DELTA_SET,
    GENERIC_LEVEL_OPCODE_DELTA_SET_UNACKNOWLEDGED,
    GENERIC_LEVEL_OPCODE_MOVE_SET,
    GENERIC_LEVEL_OPCODE_MOVE_SET_UNACKNOWLEDGED,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {GENERIC_LEVEL_OPCODE_GET, handle_get_cb},
    {GENERIC_LEVEL_OPCODE_SET, handle_set_cb},
    {GENERIC_LEVEL_OPCODE_SET_UNACKNOWLEDGED, handle_set_cb},
    {GENERIC_LEVEL_OPCODE_STATUS, NULL},
    {GENERIC_LEVEL_OPCODE_DELTA_SET,handle_delta_set_cb},
    {GENERIC_LEVEL_OPCODE_DELTA_SET_UNACKNOWLEDGED,handle_delta_set_cb},
    {GENERIC_LEVEL_OPCODE_MOVE_SET,handle_move_set_cb},
    {GENERIC_LEVEL_OPCODE_MOVE_SET_UNACKNOWLEDGED,handle_move_set_cb},
};


static const mesh_model_cb_t generic_level_server_msg_cb = {
    .cb_rx             = generic_level_server_rx_cb,
    .cb_sent           = generic_level_server_sent_cb,
    .cb_publish_period = NULL,
};


static mesh_model_register_info_t generic_level_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_GENS_LVL),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)generic_level_server_opcode_list,
    .num_opcodes = sizeof(generic_level_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &generic_level_server_msg_cb,
    .p_args = NULL,
};


/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static uint32_t status_send(generic_level_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const generic_level_status_params_t * p_params)
{
    generic_level_status_msg_pkt_t msg_pkt;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? GENERIC_LEVEL_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * GENERIC_LEVEL_SERVER_TX_HDL_TOTAL
                                        : GENERIC_LEVEL_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * GENERIC_LEVEL_SERVER_TX_HDL_TOTAL;

    if ((p_params->remaining_time_ms > TRANSITION_TIME_STEP_10M_MAX) && (p_params->remaining_time_ms != 0xFFFFFFFF))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    msg_pkt.present_level = p_params->present_level;
    if (p_params->remaining_time_ms > 0)
    {
        msg_pkt.target_level = p_params->target_level;
        msg_pkt.remaining_time = model_transition_time_encode(p_params->remaining_time_ms);
    }

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(GENERIC_LEVEL_OPCODE_STATUS),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) &msg_pkt,
        .data_send_len = p_params->remaining_time_ms > 0 ? GENERIC_LEVEL_STATUS_MAXLEN : GENERIC_LEVEL_STATUS_MINLEN,       
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };

    if (p_params->remaining_time_ms > 0)
    {
        APP_LOG_INFO("SERVER[%d] -- present_level = %d, target_level = %d, remaining_time = %d.",
                p_server->model_instance_index, msg_pkt.present_level, msg_pkt.target_level, msg_pkt.remaining_time);
    }
    else
    {
        APP_LOG_INFO("SERVER[%d] -- present_level = %d.", p_server->model_instance_index, msg_pkt.present_level);
    }

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
    generic_level_server_t * p_server = (generic_level_server_t *) p_args;
  
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get level state!!!", p_server->model_instance_index);

    generic_level_status_params_t out_data = {0};

    if (get_params_validate(p_rx_msg))
    {
        p_server->settings.p_callbacks->level_cbs.get_cb(p_server, p_rx_msg, &out_data);
        uint32_t send_status = status_send(p_server, p_rx_msg, &out_data);
        if (MESH_ERROR_NO_ERROR != send_status)
        {
            APP_LOG_ERROR("SERVER[%d] -- Response status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
        }
    }
}

static inline bool set_params_validate(const mesh_model_msg_ind_t * p_rx_msg, const generic_level_set_msg_pkt_t * p_params)
{
    return (p_rx_msg->msg_len == GENERIC_LEVEL_SET_MINLEN || p_rx_msg->msg_len == GENERIC_LEVEL_SET_MAXLEN);
}

static void handle_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    generic_level_server_t  * p_server = (generic_level_server_t  *) p_args;

    APP_LOG_INFO("SERVER[%d] -- Receive message, want to set level state!!!", p_server->model_instance_index);
    
    generic_level_set_params_t in_data = {0};
    model_transition_t in_data_tr = {0};
    generic_level_status_params_t out_data = {0};
    generic_level_set_msg_pkt_t * p_msg_params_packed = (generic_level_set_msg_pkt_t *) p_rx_msg->msg;

    if (set_params_validate(p_rx_msg, p_msg_params_packed))
    {
        in_data.level = p_msg_params_packed->level;
        in_data.tid = p_msg_params_packed->tid;

        if (model_tid_validate(&p_server->tid_tracker, p_rx_msg, GENERIC_LEVEL_OPCODE_SET, in_data.tid))
        {
            if (p_rx_msg->msg_len == GENERIC_LEVEL_SET_MAXLEN)
            {
                if (!model_transition_time_is_valid(p_msg_params_packed->transition_time))
                {
                    APP_LOG_INFO("SERVER[%d] -- model transition time is not valid.", p_server->model_instance_index);
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
            
            p_server->settings.p_callbacks->level_cbs.set_cb(p_server,
                                                             p_rx_msg,
                                                             &in_data,
                                                             ((p_rx_msg->msg_len == GENERIC_LEVEL_SET_MINLEN)&&(p_server->p_dtt_ms == NULL)) ? NULL : &in_data_tr,
                                                             (p_rx_msg->opcode.company_opcode == GENERIC_LEVEL_OPCODE_SET) ? &out_data : NULL);

            if (p_rx_msg->opcode.company_opcode == GENERIC_LEVEL_OPCODE_SET)
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

static inline bool delta_set_params_validate(const mesh_model_msg_ind_t * p_rx_msg, const generic_level_delta_set_msg_pkt_t * p_params)
{
    return (p_rx_msg->msg_len == GENERIC_LEVEL_DELTA_SET_MINLEN || p_rx_msg->msg_len == GENERIC_LEVEL_DELTA_SET_MAXLEN);
}

static void handle_delta_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    generic_level_server_t  * p_server = (generic_level_server_t  *) p_args;

    APP_LOG_INFO("SERVER[%d] -- Receive message, want to delta_set level state!!!", p_server->model_instance_index);
    
    generic_level_delta_set_params_t in_data = {0};
    model_transition_t in_data_tr = {0};
    generic_level_status_params_t out_data = {0};
    generic_level_delta_set_msg_pkt_t * p_msg_params_packed = (generic_level_delta_set_msg_pkt_t *) p_rx_msg->msg;

    if (delta_set_params_validate(p_rx_msg, p_msg_params_packed))
    {
        in_data.delta_level = p_msg_params_packed->delta_level;
        in_data.tid = p_msg_params_packed->tid;
        if (!model_tid_validate(&p_server->tid_tracker, p_rx_msg, GENERIC_LEVEL_OPCODE_DELTA_SET, in_data.tid))
        {
            APP_LOG_INFO("tid %d[0x%x], level %d[0x%x]",  in_data.tid,  in_data.tid,  in_data.delta_level, in_data.delta_level);
        }

        if (p_rx_msg->msg_len == GENERIC_LEVEL_DELTA_SET_MAXLEN)
        {
            if (!model_transition_time_is_valid(p_msg_params_packed->transition_time))
            {
                APP_LOG_INFO("SERVER[%d] --model transition time is not valid", p_server->model_instance_index);
                return;
            }

            in_data_tr.transition_time_ms = model_transition_time_decode(p_msg_params_packed->transition_time);
            in_data_tr.delay_ms = model_delay_decode(p_msg_params_packed->delay);
            APP_LOG_INFO("SERVER[%d] -- transition_time_ms = %d.", p_server->model_instance_index, in_data_tr.transition_time_ms);
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
        
         p_server->settings.p_callbacks->level_cbs.delta_set_cb(p_server,
                                                               p_rx_msg,
                                                               &in_data,
                                                               ((p_rx_msg->msg_len == GENERIC_LEVEL_DELTA_SET_MINLEN)&&(p_server->p_dtt_ms == NULL)) ? NULL : &in_data_tr,
                                                               (p_rx_msg->opcode.company_opcode == GENERIC_LEVEL_OPCODE_DELTA_SET) ? &out_data : NULL);

        if (p_rx_msg->opcode.company_opcode == GENERIC_LEVEL_OPCODE_DELTA_SET)
        {
            uint32_t send_status = status_send(p_server, p_rx_msg, &out_data);
            if (MESH_ERROR_NO_ERROR != send_status)
            {
                APP_LOG_ERROR("SERVER[%d] -- Response status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
            }
        }
    }
}


static inline bool move_set_params_validate(const mesh_model_msg_ind_t * p_rx_msg, const generic_level_move_set_msg_pkt_t * p_params)
{
    return (p_rx_msg->msg_len == GENERIC_LEVEL_MOVE_SET_MINLEN || p_rx_msg->msg_len == GENERIC_LEVEL_MOVE_SET_MAXLEN);
}

static void handle_move_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    generic_level_server_t  * p_server = (generic_level_server_t  *) p_args;

    APP_LOG_INFO("SERVER[%d] -- Receive message, want to move_set level state!!!", p_server->model_instance_index);
    
    generic_level_move_set_params_t in_data = {0};
    model_transition_t in_data_tr = {0};
    generic_level_status_params_t out_data = {0};
    generic_level_move_set_msg_pkt_t * p_msg_params_packed = (generic_level_move_set_msg_pkt_t *) p_rx_msg->msg;

    if (move_set_params_validate(p_rx_msg, p_msg_params_packed))
    {
        in_data.move_level = p_msg_params_packed->move_level;
        in_data.tid = p_msg_params_packed->tid;

        if (model_tid_validate(&p_server->tid_tracker, p_rx_msg, GENERIC_LEVEL_OPCODE_MOVE_SET, in_data.tid))
        {
            if (p_rx_msg->msg_len == GENERIC_LEVEL_MOVE_SET_MAXLEN)
            {
                if (!model_transition_time_is_valid(p_msg_params_packed->transition_time))
                {
                    APP_LOG_INFO("SERVER[%d] --model transition time is not valid", p_server->model_instance_index);
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

            if (in_data_tr.transition_time_ms == 0)
            {
                //do nothing : If the resulting Transition Time is equal to 0, the Generic Move Set command will not initiate any Generic Level state change
            }
            else
            {
                p_server->settings.p_callbacks->level_cbs.move_set_cb(p_server,
                                                                   p_rx_msg,
                                                                   &in_data,
                                                                    &in_data_tr,
                                                                   (p_rx_msg->opcode.company_opcode == GENERIC_LEVEL_OPCODE_MOVE_SET) ? &out_data : NULL);
            }

            if (p_rx_msg->opcode.company_opcode == GENERIC_LEVEL_OPCODE_MOVE_SET)
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

static void generic_level_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = m_opcode_handlers[company_opcode - GENERIC_LEVEL_OPCODE_GET].handler;

    if (NULL != handler)
    {
        handler(p_model_msg, p_args);
    }
}

static void generic_level_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    generic_level_server_t * p_server = (generic_level_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * GENERIC_LEVEL_SERVER_TX_HDL_TOTAL)
    {
        case GENERIC_LEVEL_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed get or (delta,move)set message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case GENERIC_LEVEL_SERVER_PUBLISH_SEND_TX_HDL:
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

uint16_t generic_level_server_init(generic_level_server_t * p_server, uint8_t element_offset)
{
    if (p_server == NULL ||
        p_server->settings.p_callbacks == NULL ||
        p_server->settings.p_callbacks->level_cbs.set_cb == NULL ||
        p_server->settings.p_callbacks->level_cbs.delta_set_cb == NULL ||
        p_server->settings.p_callbacks->level_cbs.move_set_cb == NULL ||
        p_server->settings.p_callbacks->level_cbs.get_cb == NULL ||
        GENERIC_LEVEL_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    generic_level_server_register_info.p_args = p_server;
    generic_level_server_register_info.element_offset = element_offset;

    return mesh_model_register(&generic_level_server_register_info, &p_server->model_lid);
}

uint16_t generic_level_server_status_publish(generic_level_server_t * p_server, const generic_level_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return status_send(p_server, NULL, p_params);
}
