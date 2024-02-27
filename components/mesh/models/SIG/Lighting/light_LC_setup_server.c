/**
 *****************************************************************************************
 *
 * @file light_lc_setup_server.c
 *
 * @brief Light LC Setup Server API Implementation.
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
#include "light_lc_message.h"
#include "light_lc_setup_server.h"
#include "grx_sys.h"
#include "common_utils.h"
/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_property_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_property_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void light_lc_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void light_lc_setup_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
static const uint16_t light_lc_setup_server_opcode_list[] =
{
    LIGHT_LC_PROPERTY_OPCODE_GET,
    LIGHT_LC_PROPERTY_OPCODE_SET ,
    LIGHT_LC_PROPERTY_OPCODE_SET_UNACKNOWLEDGED,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {LIGHT_LC_PROPERTY_OPCODE_GET, handle_property_get_cb},
    {LIGHT_LC_PROPERTY_OPCODE_SET, handle_property_set_cb},
    {LIGHT_LC_PROPERTY_OPCODE_SET_UNACKNOWLEDGED, handle_property_set_cb},
};

static const mesh_model_cb_t light_lc_setup_server_msg_cb = {
    .cb_rx             = light_lc_setup_server_rx_cb,
    .cb_sent           = light_lc_setup_server_sent_cb,
    .cb_publish_period = NULL
};

static mesh_model_register_info_t light_lc_setup_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_LIGHTS_LCS),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)light_lc_setup_server_opcode_list,
    .num_opcodes = sizeof(light_lc_setup_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &light_lc_setup_server_msg_cb,
    .p_args = NULL,
};


uint16_t property_get_value_length(uint16_t property_id)
{
    switch(property_id)
    {
        case LIGHT_LC_REGULATOR_ACCURACY_PROPERTY:
            return 1;
        case LIGHT_LC_LIGHTNESS_ON_PROPERTY:
        case LIGHT_LC_LIGHTNESS_PROLONG_PROPERTY:
        case LIGHT_LC_LIGHTNESS_STANDBY_PROPERTY:
            return 2; //uint16
        case LIGHT_LC_AMBIENT_LUXLVL_ON_PROPERTY:
        case LIGHT_LC_AMBIENT_LUXLVL_PROLONG_PROPERTY:
        case LIGHT_LC_AMBIENT_LUXLVL_STANDBY_PROPERTY:
        case LIGHT_LC_FADE_PROPERTY:
        case LIGHT_LC_FADE_ON_PROPERTY:
        case LIGHT_LC_FADE_STANDBY_AUTO_PROPERTY:
        case LIGHT_LC_FADE_STANDBY_MANUAL_PROPERTY:
        case LIGHT_LC_TIME_OCC_DELAY_PROPERTY:
        case LIGHT_LC_TIME_PROLONG_PROPERTY:
        case LIGHT_LC_TIME_RUN_ON_PROPERTY:
            return 3 ;//uint24
        case LIGHT_LC_REGULATOR_KID_PROPERTY:
        case LIGHT_LC_REGULATOR_KIU_PROPERTY:
        case LIGHT_LC_REGULATOR_KPD_PROPERTY:
        case LIGHT_LC_REGULATOR_KPU_PROPERTY:
            return 4;//float32
        default :
            APP_LOG_INFO("[%s] ERR:unknow value length!!!", __func__);
            return 0;
    }
}

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static uint32_t property_status_send(light_lc_setup_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const light_lc_property_status_params_t * p_params)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    light_lc_property_status_msg_pkt_t *msg_pkt = NULL;
    uint8_t tx_hdl = LIGHT_LC_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * LIGHT_LC_SERVER_TX_HDL_TOTAL;
    uint32_t ERR_CODE = MESH_ERROR_NO_ERROR;

    msg_pkt = (light_lc_property_status_msg_pkt_t *)sys_malloc(p_params->value_length + 2);
    if (NULL == msg_pkt)
    {
        APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
        return MESH_ERROR_INSUFFICIENT_RESOURCES;
    }

    gx_write16p((void const *) &(msg_pkt->property_id),  p_params->property_id);
    memcpy(msg_pkt->property_value, p_params->property_value, p_params->value_length);

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_LC_PROPERTY_OPCODE_STATUS),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) msg_pkt,
        .data_send_len = p_params->value_length + 2,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };

    if (NULL == p_rx_msg)
    {
        APP_LOG_INFO("SERVER[%d] -- to publish.", p_server->model_instance_index);
        ERR_CODE = mesh_model_publish(&msg_send, NULL);
    }
    else
    {
        APP_LOG_INFO("SERVER[%d] -- to response.", p_server->model_instance_index);
        ERR_CODE = mesh_model_rsp_send(&msg_send);
    }

    if (msg_pkt != NULL)
    {
        sys_free(msg_pkt);
        msg_pkt = NULL;
    }

    return ERR_CODE;

}

static void handle_property_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_lc_setup_server_t  * p_server = (light_lc_setup_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to set light lc property state %04X!!!", p_server->model_instance_index, p_rx_msg->opcode.company_opcode);

    if (p_rx_msg->msg_len > 2)
    {
        light_lc_property_set_msg_pkt_t * msg_pkt = (light_lc_property_set_msg_pkt_t *) p_rx_msg->msg;
        light_lc_property_set_params_t in_data = {0,0,NULL};
        light_lc_property_status_params_t out_data = {0,0,NULL};

        in_data.property_id = gx_read16p((void *)&msg_pkt->property_id);
        in_data.value_length = property_get_value_length(in_data.property_id);
        if (in_data.value_length == p_rx_msg->msg_len - 2)
        {
            in_data.property_value = msg_pkt->property_value;
            p_server->settings.p_callbacks->light_lc_property_set_cbs(p_server,
                                                                                                         p_rx_msg,
                                                                                                         &in_data,
                                                                                                         (p_rx_msg->opcode.company_opcode == LIGHT_LC_PROPERTY_OPCODE_SET) ? &out_data : NULL);

            if (p_rx_msg->opcode.company_opcode == LIGHT_LC_PROPERTY_OPCODE_SET)
            {
                (void) property_status_send(p_server, p_rx_msg, &out_data);
            }
        }
    }
}

static void handle_property_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_lc_setup_server_t  * p_server = (light_lc_setup_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get light lc property state %04X!!!", p_server->model_instance_index, p_rx_msg->opcode.company_opcode);

    if (p_rx_msg->msg_len == 2)
    {
        light_lc_property_get_msg_pkt_t * msg_pkt = (light_lc_property_get_msg_pkt_t *) p_rx_msg->msg;
        light_lc_property_get_params_t in_data = {0};
        light_lc_property_status_params_t out_data = {0,0,NULL};

        in_data.property_id = gx_read16p((void *)&msg_pkt->property_id);
        out_data.value_length = property_get_value_length(in_data.property_id);

        if (out_data.value_length > 0)
        {
            out_data.property_value = (uint8_t *)sys_malloc(out_data.value_length);
            if (out_data.property_value == NULL)
            {
                return ;//MESH_ERROR_INSUFFICIENT_RESOURCES;
            }

            p_server->settings.p_callbacks->light_lc_property_get_cbs(p_server,
                                                                                                             p_rx_msg,
                                                                                                             &in_data,
                                                                                                             &out_data);

            if (out_data.value_length == property_get_value_length(in_data.property_id))
            {
                (void) property_status_send(p_server, p_rx_msg, &out_data);
            }

            if(out_data.property_value)
            {
                sys_free(out_data.property_value);
                out_data.property_value = NULL;
            }
        }
    }
}

static void light_lc_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<light_lc_setup_server_register_info.num_opcodes; i++)
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

static void light_lc_setup_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    light_lc_setup_server_t * p_server = (light_lc_setup_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * LIGHT_LC_SERVER_TX_HDL_TOTAL)
    {
        case LIGHT_LC_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case LIGHT_LC_SERVER_PUBLISH_SEND_TX_HDL:
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

uint16_t light_lc_setup_server_init(light_lc_setup_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->light_lc_property_get_cbs
        || NULL == p_server->settings.p_callbacks->light_lc_property_set_cbs
        || LIGHT_LC_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)        
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    light_lc_setup_server_register_info.p_args = p_server;
    light_lc_setup_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&light_lc_setup_server_register_info, &p_server->model_lid);
}

uint16_t light_lc_setup_server_property_status_publish(light_lc_setup_server_t * p_server, 
                                                            const light_lc_property_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return property_status_send(p_server, NULL, p_params);
}


