/**
 *****************************************************************************************
 *
 * @file scene_server.c
 *
 * @brief Mesh Scene Server API Implementation.
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
#include "scene_message.h"
#include "scene_server.h"
#include "grx_sys.h"
#include "common_utils.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_scene_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_scene_register_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_scene_recall_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void mesh_scene_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void mesh_scene_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

bool is_scene_little_endian = true;

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t mesh_scene_server_opcode_list[] =
{
    TSCNS_SCENE_OPCODE_GET,
    TSCNS_SCENE_REGISTER_OPCODE_GET,
    TSCNS_SCENE_OPCODE_RECALL,
    TSCNS_SCENE_OPCODE_RECALL_UNACKNOWLEDGED,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {TSCNS_SCENE_OPCODE_GET, handle_scene_get_cb},
    {TSCNS_SCENE_REGISTER_OPCODE_GET, handle_scene_register_get_cb},
    {TSCNS_SCENE_OPCODE_RECALL, handle_scene_recall_cb},
    {TSCNS_SCENE_OPCODE_RECALL_UNACKNOWLEDGED, handle_scene_recall_cb},
};

static const mesh_model_cb_t mesh_scene_server_msg_cb = {
    .cb_rx             = mesh_scene_server_rx_cb,
    .cb_sent           = mesh_scene_server_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t mesh_scene_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_TSCNS_SCN),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)mesh_scene_server_opcode_list,
    .num_opcodes = sizeof(mesh_scene_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &mesh_scene_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static bool endian_judge(void)
{
    uint16_t i= 0x01;
    uint8_t *p = (uint8_t *)&i;

    return (is_scene_little_endian = (*p == 0x01)?true:false);
}

static mesh_error_t scene_message_send(mesh_scene_server_t * p_server,
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

static uint32_t scene_status_send(mesh_scene_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const mesh_scene_status_params_t * p_params)
{
    mesh_scene_status_msg_pkt_t msg_pkt;
    uint16_t data_send_len = TSCNS_SCENE_STATUS_MINLEN;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? TSCNS_SCENE_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * TSCNS_SCENE_SERVER_TX_HDL_TOTAL
                                        : TSCNS_SCENE_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * TSCNS_SCENE_SERVER_TX_HDL_TOTAL;

    APP_LOG_INFO("[%s] enter.", __func__);

    if (p_params->remaining_time_ms > TRANSITION_TIME_STEP_10M_MAX)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    gx_write16p((void const *)&(msg_pkt.current_scene), p_params->current_scene);
    msg_pkt.status_code = p_params->status_code;

    if (p_params->remaining_time_ms >0)
    {
        gx_write16p((void const *)&(msg_pkt.target_scene), p_params->target_scene);
        msg_pkt.remaining_time = model_transition_time_encode(p_params->remaining_time_ms);
        data_send_len = TSCNS_SCENE_STATUS_MAXLEN;
    }

    return scene_message_send(p_server, p_rx_msg, TSCNS_SCENE_OPCODE_STATUS, tx_hdl, (uint8_t *)&msg_pkt, data_send_len);
}

static inline bool recall_params_validate(const mesh_model_msg_ind_t * p_rx_msg, const uint16_t opcode)
{
    return (((opcode == TSCNS_SCENE_OPCODE_RECALL)
                        || (opcode == TSCNS_SCENE_OPCODE_RECALL_UNACKNOWLEDGED))
                    && (p_rx_msg->msg_len == TSCNS_SCENE_RECALL_MINLEN 
                        || p_rx_msg->msg_len == TSCNS_SCENE_RECALL_MAXLEN) );
}

static inline bool get_params_validate(const mesh_model_msg_ind_t * p_rx_msg)
{
    return (p_rx_msg->msg_len == 0);
}

static void handle_scene_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_scene_server_t * p_server = (mesh_scene_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   

    mesh_scene_status_params_t out_data = {0};

    if (get_params_validate(p_rx_msg))
    {
        p_server->settings.p_callbacks->scenes_cbs.get_cb(p_server, p_rx_msg, &out_data);
        (void) scene_status_send(p_server, p_rx_msg, &out_data);
    }
}

static void handle_scene_recall_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_scene_server_t * p_server = (mesh_scene_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   

    if (recall_params_validate(p_rx_msg, p_rx_msg->opcode.company_opcode))
    {
        mesh_scene_recall_params_t in_data = {0};
        model_transition_t in_data_tr = {0};
        mesh_scene_status_params_t out_data = {0};
        mesh_scene_recall_msg_pkt_t * p_msg_params_packed = (mesh_scene_recall_msg_pkt_t *) p_rx_msg->msg;

        in_data.scene_number= gx_read16p ((void const *)&p_msg_params_packed->scene_number);
        in_data.tid = p_msg_params_packed->tid;

        if (model_tid_validate(&p_server->tid_tracker, p_rx_msg, p_rx_msg->opcode.company_opcode, in_data.tid))
        {
            if (p_rx_msg->msg_len == TSCNS_SCENE_RECALL_MAXLEN)
            {
                if (!model_transition_time_is_valid(p_msg_params_packed->transition_time))
                {
                    return;
                }

                in_data_tr.transition_time_ms = model_transition_time_decode(p_msg_params_packed->transition_time);
                in_data_tr.delay_ms = model_delay_decode(p_msg_params_packed->delay);
                APP_LOG_INFO("SERVER[%d] -- transition_time_ms = %d., delay_ms = %d", p_server->model_instance_index, in_data_tr.transition_time_ms, in_data_tr.delay_ms);
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

            p_server->settings.p_callbacks->scenes_cbs.recall_cb(p_server,
                                                                                            p_rx_msg,
                                                                                            &in_data,
                                                                                            ((p_rx_msg->msg_len == TSCNS_SCENE_RECALL_MINLEN)&&(p_server->p_dtt_ms == NULL)) ? NULL : &in_data_tr,
                                                                                            (p_rx_msg->opcode.company_opcode == TSCNS_SCENE_OPCODE_RECALL) ? ((void *)&out_data) : NULL);

            if (p_rx_msg->opcode.company_opcode == TSCNS_SCENE_OPCODE_RECALL)
            {
                (void) scene_status_send(p_server, p_rx_msg, &out_data);
            }
        }
    }
}

static void handle_scene_register_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    mesh_scene_server_t * p_server = (mesh_scene_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   

    mesh_scene_register_status_params_t out_data = {0};

    if (get_params_validate(p_rx_msg))
    {
        p_server->settings.p_callbacks->scenes_cbs.register_get_cb(p_server, p_rx_msg, &out_data);
        (void) scene_regester_status_send(p_server, p_rx_msg, &out_data);
    }
}

static void mesh_scene_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<mesh_scene_server_register_info.num_opcodes; i++)
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

static void mesh_scene_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    mesh_scene_server_t * p_server = (mesh_scene_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * TSCNS_SCENE_SERVER_TX_HDL_TOTAL)
    {
        case TSCNS_SCENE_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case TSCNS_SCENE_SERVER_PUBLISH_SEND_TX_HDL:
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
uint32_t scene_regester_status_send(mesh_scene_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const mesh_scene_register_status_params_t * p_params)
{    
    mesh_scene_register_status_msg_pkt_t *msg_pkt =
                    (mesh_scene_register_status_msg_pkt_t *)sys_malloc(sizeof(mesh_scene_register_status_msg_pkt_t) + p_params->scene_cnt*sizeof(uint16_t));
    uint16_t scene_offset = 0;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? TSCNS_SCENE_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * TSCNS_SCENE_SERVER_TX_HDL_TOTAL
                                        : TSCNS_SCENE_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * TSCNS_SCENE_SERVER_TX_HDL_TOTAL;

    APP_LOG_INFO("[%s] enter.", __func__);

    msg_pkt->status_code = p_params->status_code;
    gx_write16p((const void *)&msg_pkt->current_scene, p_params->current_scene);
    while (p_params->scene_cnt > scene_offset)
    {
        gx_write16p(&(p_params->scene[scene_offset]), p_params->scene[scene_offset]);
        scene_offset++;

        if (scene_offset >= TSCNS_SCENE_REGISTER_SCENE_NUMBER_CNT_MAX)
        {
            break;
        }
    }

    memcpy((void *)msg_pkt->scene, p_params->scene, p_params->scene_cnt*sizeof(uint16_t));

    return scene_message_send(p_server,
                                                        p_rx_msg,
                                                        TSCNS_SCENE_REGISTER_OPCODE_STATUS,
                                                        tx_hdl,
                                                        (uint8_t *)msg_pkt,
                                                        sizeof(mesh_scene_register_status_msg_pkt_t)+p_params->scene_cnt*sizeof(uint16_t) );
}

uint16_t mesh_scene_server_init(mesh_scene_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->scenes_cbs.get_cb
        || NULL == p_server->settings.p_callbacks->scenes_cbs.recall_cb
        || NULL == p_server->settings.p_callbacks->scenes_cbs.register_get_cb
        || TSCNS_SCENE_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)        
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    endian_judge();
    mesh_scene_server_register_info.p_args = p_server;
    mesh_scene_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&mesh_scene_server_register_info, &p_server->model_lid);
}

uint16_t mesh_scene_server_status_publish(mesh_scene_server_t * p_server, 
                                                            const mesh_scene_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return scene_status_send(p_server, NULL, p_params);
}

uint16_t mesh_scene_server_register_status_publish(mesh_scene_server_t * p_server,
                                                            const mesh_scene_register_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return scene_regester_status_send(p_server, NULL, p_params);
}
