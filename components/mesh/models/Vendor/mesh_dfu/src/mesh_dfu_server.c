/**
 *****************************************************************************************
 *
 * @file mesh_dfu_server.c
 *
 * @brief Mesh DFU Off Server API Implementation.
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
#include "mesh_dfu_server.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void mesh_dfu_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void mesh_dfu_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t mesh_dfu_server_opcode_list[] =
{
    MESH_DFU_OPCODE_CURRENT_VERSION_GET,
    MESH_DFU_OPCODE_NEW_VERSION_SET,
    MESH_DFU_OPCODE_NEW_VERSION_SET_UNACKNOWLEDGED,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {MESH_DFU_OPCODE_CURRENT_VERSION_GET, handle_get_cb},
    {MESH_DFU_OPCODE_NEW_VERSION_SET, handle_set_cb},
    {MESH_DFU_OPCODE_NEW_VERSION_SET_UNACKNOWLEDGED, handle_set_cb},
};

static const mesh_model_cb_t mesh_dfu_server_msg_cb = {
    .cb_rx             = mesh_dfu_server_rx_cb,
    .cb_sent           = mesh_dfu_server_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t mesh_dfu_server_register_info = 
{
    .model_id = MESH_MODEL_VENDOR(MESH_DFU_SERVER_MODEL_ID, MESH_DFU_COMPANY_ID),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)mesh_dfu_server_opcode_list,
    .num_opcodes = sizeof(mesh_dfu_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &mesh_dfu_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static uint32_t status_send(mesh_dfu_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const uint8_t *p_params, bool new_version)
{                        
    mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_VENDOR(MESH_DFU_OPCODE_CURRENT_VERSION_STATUS, MESH_DFU_COMPANY_ID);
    uint16_t len = sizeof(mesh_dfu_current_version_status_msg_pkt_t);
    
    uint8_t tx_hdl = (NULL == p_rx_msg) ? MESH_DFU_SERVER_PUBLISH_CURRENT_VERSION_SEND_TX_HDL + p_server->model_instance_index * MESH_DFU_SERVER_TX_HDL_TOTAL
                                        : MESH_DFU_SERVER_RSP_CURRENT_VERSION_SEND_TX_HDL + p_server->model_instance_index * MESH_DFU_SERVER_TX_HDL_TOTAL;

    if (true == new_version)
    {
        opcode.company_opcode = MESH_DFU_OPCODE_NEW_VERSION_STATUS;
        len = sizeof(mesh_dfu_new_version_status_msg_pkt_t);
        
        tx_hdl = (NULL == p_rx_msg) ? MESH_DFU_SERVER_PUBLISH_NEW_VERSION_SEND_TX_HDL + p_server->model_instance_index * MESH_DFU_SERVER_TX_HDL_TOTAL
                                                : MESH_DFU_SERVER_RSP_NEW_VERSION_SEND_TX_HDL + p_server->model_instance_index * MESH_DFU_SERVER_TX_HDL_TOTAL;
    }

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *)p_params,
        .data_send_len = len,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };
    
    msg_send.opcode = opcode;

    if (NULL == p_rx_msg)
    {
        
        APP_LOG_INFO("DFUSERVER[%d] -- to publish.", p_server->model_instance_index);
        return mesh_model_publish(&msg_send, NULL);
    }
    else
    {
        APP_LOG_INFO("DFUSERVER[%d] -- to response.", p_server->model_instance_index);
        return mesh_model_rsp_send(&msg_send);
    }
}

static bool set_params_validate(const mesh_model_msg_ind_t * p_rx_msg, const mesh_dfu_server_t *p_server)
{
    bool valid = false;

    if (p_rx_msg->msg_len == sizeof(mesh_dfu_new_version_set_msg_pkt_t))
    {
        mesh_dfu_version_status_t * p_new_version = (mesh_dfu_version_status_t *) p_rx_msg->msg;

        valid = (p_new_version->company_id == p_server->settings.current_version.company_id)
                && (p_new_version->product_id == p_server->settings.current_version.product_id)
                && (p_new_version->product_version_id > p_server->settings.current_version.product_version_id);
    }

    return valid;
}

static bool model_tid_validate(dfu_tid_filter_t * p_tid_filter, const mesh_model_msg_ind_t * p_rx_msg, uint8_t tid)
{
    if (p_tid_filter->src != p_rx_msg->src || p_tid_filter->old_tid != tid)
    {
        p_tid_filter->src = p_rx_msg->src;
        p_tid_filter->old_tid = tid;

        p_tid_filter->new_transaction = true;
    }
    else
    {
        p_tid_filter->new_transaction = false;
    }

    return p_tid_filter->new_transaction;
}

static void handle_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    uint32_t send_status = MESH_ERROR_NO_ERROR;
    mesh_dfu_server_t  *p_server = (mesh_dfu_server_t  *) p_args;
    APP_LOG_INFO("DFUSERVER%d] -- Receive message, want to set new version!!!", p_server->model_instance_index);
    
    mesh_dfu_new_version_set_msg_pkt_t * p_msg_params_packed = (mesh_dfu_new_version_set_msg_pkt_t *) p_rx_msg->msg;
    mesh_dfu_new_version_status_msg_pkt_t out_data =
    {
        .company_id         = p_msg_params_packed->company_id,
        .product_id         = p_msg_params_packed->product_id,
        .product_version_id = p_msg_params_packed->product_version_id,
    };
    
    if (set_params_validate(p_rx_msg, p_server))
    {
        if (model_tid_validate(&p_server->tid_filter, p_rx_msg, p_msg_params_packed->tid))
        {
            p_server->client_address = p_rx_msg->src;
            p_server->settings.p_callbacks->dfu_cbs.set_cb(p_server->model_instance_index, out_data);

            // response
            if (MESH_DFU_OPCODE_NEW_VERSION_SET == p_rx_msg->opcode.company_opcode)
            {
                send_status = status_send(p_server, p_rx_msg, (uint8_t *)&out_data, true);
                if (MESH_ERROR_NO_ERROR != send_status)
                {
                    APP_LOG_WARNING("DFUSERVER%d] -- Response status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
                }
                else
                {
                    p_server->settings.expect_new_version_rsp_pub |= MESH_DFU_NEW_VERSION_RSP_MARK;
                }
            }

            // publish
            send_status = status_send(p_server, NULL, (uint8_t *)&out_data, true);
            if (MESH_ERROR_NO_ERROR != send_status)
            {
                APP_LOG_WARNING("DFUSERVER%d] -- Publish status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
            }
            else
            {
                p_server->settings.expect_new_version_rsp_pub |= MESH_DFU_NEW_VERSION_PUB_MARK;
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
    mesh_dfu_server_t * p_server = (mesh_dfu_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   
    APP_LOG_INFO("DFUSERVER[%d] -- Receive message, want to get current version!!!", p_server->model_instance_index);

    mesh_dfu_current_version_status_msg_pkt_t out_data = {0};

    if (get_params_validate(p_rx_msg))
    {
        p_server->client_address = p_rx_msg->src;
        p_server->settings.p_callbacks->dfu_cbs.get_cb(p_server->model_instance_index, &out_data);
        uint32_t send_status = status_send(p_server, p_rx_msg, (uint8_t *)&out_data, false);
        if (MESH_ERROR_NO_ERROR != send_status)
        {
            APP_LOG_WARNING("DFUSERVER[%d] -- Publish status faild, error code: 0x%04x", p_server->model_instance_index, send_status);
        }
    }
}

static void mesh_dfu_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;
    mesh_opcode_handler_cb_t handler = NULL;
    
    for (uint8_t i = 0; i < sizeof(m_opcode_handlers)/sizeof(m_opcode_handlers[0]); i++)
    {
        if (company_opcode == m_opcode_handlers[i].opcode)
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

static void mesh_dfu_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    mesh_dfu_server_t * p_server = (mesh_dfu_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * MESH_DFU_SERVER_TX_HDL_TOTAL)
    {
        case MESH_DFU_SERVER_RSP_CURRENT_VERSION_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("DFUSERVER[%d] -- Responsed get current version message!!!", p_server->model_instance_index)
                  : APP_LOG_INFO("DFUSERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            break;
        case MESH_DFU_SERVER_PUBLISH_CURRENT_VERSION_SEND_TX_HDL:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("DFUSERVER[%d] -- Published current version message!!!", p_server->model_instance_index)
                  : APP_LOG_INFO("DFUSERVER[%d] -- Failed to published message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            break;
        case MESH_DFU_SERVER_RSP_NEW_VERSION_SEND_TX_HDL:
            if (MESH_ERROR_NO_ERROR == p_sent->status
                && MESH_DFU_NEW_VERSION_RSP_MARK == (p_server->settings.expect_new_version_rsp_pub & MESH_DFU_NEW_VERSION_RSP_MARK))
            {
                p_server->settings.actual_new_version_rsp_pub |= MESH_DFU_NEW_VERSION_RSP_MARK;
            }
            else
            {
                p_server->settings.expect_new_version_rsp_pub = 0;
                p_server->settings.actual_new_version_rsp_pub = 0;
            }
        
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("DFUSERVER[%d] -- Responsed set new version message!!!", p_server->model_instance_index)
                  : APP_LOG_INFO("DFUSERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            break;
        case MESH_DFU_SERVER_PUBLISH_NEW_VERSION_SEND_TX_HDL:
            if (MESH_ERROR_NO_ERROR == p_sent->status
                && MESH_DFU_NEW_VERSION_PUB_MARK == (p_server->settings.expect_new_version_rsp_pub & MESH_DFU_NEW_VERSION_PUB_MARK))
            {
                p_server->settings.actual_new_version_rsp_pub |= MESH_DFU_NEW_VERSION_PUB_MARK;
            }
            else
            {
                p_server->settings.expect_new_version_rsp_pub = 0;
                p_server->settings.actual_new_version_rsp_pub = 0;
            }
        
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_LOG_INFO("DFUSERVER[%d] -- Published new version message!!!", p_server->model_instance_index)
                  : APP_LOG_INFO("DFUSERVER[%d] -- Failed to published message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            break;
            
        default:
            APP_LOG_INFO("Never here!!!");
            break;
    }

    if (p_server->settings.expect_new_version_rsp_pub == p_server->settings.actual_new_version_rsp_pub
        && 0 != p_server->settings.expect_new_version_rsp_pub)
    {
        p_server->settings.expect_new_version_rsp_pub = 0;
        p_server->settings.actual_new_version_rsp_pub = 0;
        
        APP_LOG_INFO("****HERE, ENTER INTO DFU APP!!!****");
    }
}



/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t mesh_dfu_server_init(mesh_dfu_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->dfu_cbs.set_cb
        || NULL == p_server->settings.p_callbacks->dfu_cbs.get_cb
        || MESH_DFU_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)        
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    mesh_dfu_server_register_info.p_args = p_server;
    mesh_dfu_server_register_info.element_offset = element_offset;
    
    return mesh_model_register(&mesh_dfu_server_register_info, &p_server->model_lid);
}

