/**
 *****************************************************************************************
 *
 * @file sensor_setup_server.c
 *
 * @brief Generic On Off Server API Implementation.
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
#include "sensor_message.h"
#include "sensor_setup_server.h"
#include "common_utils.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_cadence_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_settings_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_setting_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_cadence_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_setting_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void sensor_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void sensor_setup_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t sensor_setup_server_opcode_list[] =
{
    MESH_SENSOR_CADENCE_OPCODE_GET,
    MESH_SENSOR_CADENCE_OPCODE_SET,
    MESH_SENSOR_CADENCE_OPCODE_SET_UNACKNOWLEDGED,
    MESH_SENSOR_SETTINGS_OPCODE_GET,
    MESH_SENSOR_SETTING_OPCODE_GET,
    MESH_SENSOR_SETTING_OPCODE_SET,
    MESH_SENSOR_SETTING_OPCODE_SET_UNACKNOWLEDGED
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {MESH_SENSOR_CADENCE_OPCODE_GET, handle_cadence_get_cb},
    {MESH_SENSOR_CADENCE_OPCODE_SET, handle_cadence_set_cb},
    {MESH_SENSOR_CADENCE_OPCODE_SET_UNACKNOWLEDGED, handle_cadence_set_cb},
    {MESH_SENSOR_SETTINGS_OPCODE_GET, handle_settings_get_cb},
    {MESH_SENSOR_SETTING_OPCODE_GET, handle_setting_get_cb},
    {MESH_SENSOR_SETTING_OPCODE_SET, handle_setting_set_cb},
    {MESH_SENSOR_SETTING_OPCODE_SET_UNACKNOWLEDGED, handle_setting_set_cb},
};

static const mesh_model_cb_t sensor_setup_server_msg_cb = {
    .cb_rx             = sensor_setup_server_rx_cb,
    .cb_sent           = sensor_setup_server_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t sensor_setup_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_SENS_SENS),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)sensor_setup_server_opcode_list,
    .num_opcodes = sizeof(sensor_setup_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &sensor_setup_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static uint32_t cadence_status_send(sensor_setup_server_t * p_server,
                                                                  const mesh_model_msg_ind_t *p_rx_msg,
                                                                  const sensor_cadence_status_params_t * p_params)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    sensor_cadence_status_msg_pkt_t *msg_pkt = NULL;
    uint16_t total_length = 0;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? MESH_SENSOR_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL
                                        : MESH_SENSOR_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL;
    uint32_t ERR_CODE = MESH_ERROR_NO_ERROR;

    if (p_params->property_value_length > 0)
    {
        total_length += 4 + p_params->property_value_length * 2;

        if (p_params->trigger_type&0x01 == MESH_SENSOR_CADENCE_TRIGGER_PERCENT)
        {
            total_length += 2 * 2;
        }
        else
        {
            total_length += p_params->property_value_length * 2;
        }

        msg_pkt = (sensor_cadence_status_msg_pkt_t *)sys_malloc(total_length);
        if (msg_pkt == NULL)
        {
            APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
            return MESH_ERROR_INSUFFICIENT_RESOURCES;
        }

        msg_pkt->sensor_cadence[0] = (p_params->fast_cadence_period_div&0x7F) | ((p_params->trigger_type&MESH_SENSOR_CADENCE_TRIGGER_PERCENT)<<7);

        if ((p_params->trigger_type&0x01) == MESH_SENSOR_CADENCE_TRIGGER_PERCENT)
        {
            msg_pkt->sensor_cadence[1] = p_params->trigger_dlt_down[0];
            msg_pkt->sensor_cadence[2] = p_params->trigger_dlt_down[1];
            msg_pkt->sensor_cadence[3] = p_params->trigger_dlt_up[0];
            msg_pkt->sensor_cadence[4] = p_params->trigger_dlt_up[1];
            msg_pkt->sensor_cadence[5] = p_params->min_interval;
            memcpy(&(msg_pkt->sensor_cadence[6]), p_params->fast_cadence_low, p_params->property_value_length);
            memcpy(&(msg_pkt->sensor_cadence[6 + p_params->property_value_length]), p_params->fast_cadence_high, p_params->property_value_length);
        }
        else
        {
            memcpy(&(msg_pkt->sensor_cadence[1]), p_params->trigger_dlt_down, p_params->property_value_length);
            memcpy(&(msg_pkt->sensor_cadence[1 + p_params->property_value_length]), p_params->trigger_dlt_up, p_params->property_value_length);
            msg_pkt->sensor_cadence[1 + p_params->property_value_length * 2] = p_params->min_interval;
            memcpy(&(msg_pkt->sensor_cadence[2 + p_params->property_value_length * 2]), p_params->fast_cadence_low, p_params->property_value_length);
            memcpy(&(msg_pkt->sensor_cadence[2 + p_params->property_value_length * 2 + p_params->property_value_length]), p_params->fast_cadence_high, p_params->property_value_length);
        }
    }
    else
    {
        total_length = 2;
        msg_pkt = (sensor_cadence_status_msg_pkt_t *)sys_malloc(total_length);
        if (msg_pkt == NULL)
        {
            APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
            return MESH_ERROR_INSUFFICIENT_RESOURCES;
        }
    }
    gx_write16p((void const *) &(msg_pkt->property_id),  p_params->property_id);
    APP_LOG_INFO("recv property id: %04x, length %d", p_params->property_id, p_params->property_value_length);

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_CADENCE_OPCODE_STATUS),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) msg_pkt,
        .data_send_len = total_length,
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

static uint32_t settings_status_send(sensor_setup_server_t * p_server,
                                                                  const mesh_model_msg_ind_t *p_rx_msg,
                                                                  const sensor_settings_status_params_t * p_params)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    sensor_settings_status_msg_pkt_t *msg_pkt = NULL;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? MESH_SENSOR_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL
                                        : MESH_SENSOR_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL;
    uint32_t ERR_CODE = MESH_ERROR_NO_ERROR;

    msg_pkt = (sensor_settings_status_msg_pkt_t *)sys_malloc(2 + p_params->setting_id_number * 2);
    if (msg_pkt == NULL)
    {
        APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
        return MESH_ERROR_INSUFFICIENT_RESOURCES;
    }

    gx_write16p((void const *) &(msg_pkt->property_id),  p_params->property_id);
    for (uint8_t i=0; i<p_params->setting_id_number; i++)
    {
        msg_pkt->setting_property_id[i] = p_params->setting_property_id[i];
        msg_pkt->setting_property_id[i+1] = p_params->setting_property_id[i+1];
    }

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_SETTINGS_OPCODE_STATUS),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) msg_pkt,
        .data_send_len = 2 + p_params->setting_id_number * 2,
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

static uint32_t setting_status_send(sensor_setup_server_t * p_server,
                                                                  const mesh_model_msg_ind_t *p_rx_msg,
                                                                  const sensor_setting_status_params_t * p_params)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    sensor_setting_status_msg_pkt_t *msg_pkt = NULL;
    uint16_t total_length = 0;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? MESH_SENSOR_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL
                                        : MESH_SENSOR_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL;
    uint32_t ERR_CODE = MESH_ERROR_NO_ERROR;

    total_length = 5 + p_params->setting_raw_length;
    msg_pkt = (sensor_setting_status_msg_pkt_t *)sys_malloc(total_length);
    if (msg_pkt == NULL)
    {
        APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
        return MESH_ERROR_INSUFFICIENT_RESOURCES;
    }

    gx_write16p((void const *) &(msg_pkt->property_id),  p_params->property_id);
    gx_write16p((void const *) &(msg_pkt->setting_property_id),  p_params->setting_property_id);
    if (p_params->setting_raw_length > 0)
    {
        msg_pkt->setting_access = p_params->setting_access;
        memcpy(msg_pkt->setting_raw , p_params->setting_raw, p_params->setting_raw_length);
    }
    else
    {
        total_length --;
    }

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_SETTING_OPCODE_STATUS),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) msg_pkt,
        .data_send_len = total_length,
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

static void handle_cadence_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_setup_server_t  * p_server = (sensor_setup_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to set cadence state!!!", p_server->model_instance_index);
    
    sensor_cadence_set_params_t in_data = {0};
    sensor_cadence_status_params_t out_data = {0};
    sensor_cadence_set_msg_pkt_t * p_msg_params_packed = (sensor_cadence_set_msg_pkt_t *) p_rx_msg->msg;

    if (p_rx_msg->msg_len > MESH_SENSOR_CADENCE_SET_MINLEN)
    {
        in_data.property_id = gx_read16p((const void *)&p_msg_params_packed->property_id);
        if (in_data.property_id == 0x0000)
        {
            APP_LOG_WARNING("warning : invalid property id !!!");
            return ;
        }

        in_data.fast_cadence_period_div = p_msg_params_packed->sensor_cadence[0] & 0x7F;
        if (in_data.fast_cadence_period_div > MESH_SENSOR_STATUS_CADENCE_DIV_MAX)//The valid range for the Fast Cadence Period Divisor state is 0-15
        {
            APP_LOG_WARNING("warning : invalid period div !!!");
            return ;
        }
        in_data.trigger_type = (p_msg_params_packed->sensor_cadence[0]) >> 7;

        if (in_data.trigger_type == MESH_SENSOR_CADENCE_TRIGGER_PERCENT)
        {
            in_data.property_value_length = (p_rx_msg->msg_len - MESH_SENSOR_CADENCE_SET_MINLEN - 2*2)/2;
            if (in_data.property_value_length*2 != (p_rx_msg->msg_len - MESH_SENSOR_CADENCE_SET_MINLEN - 2*2))
            {
                APP_LOG_WARNING("warning : invalid message length !!!");
                return ;
            }
            in_data.trigger_dlt_down = &(p_msg_params_packed->sensor_cadence[1]);
            in_data.trigger_dlt_up = &(p_msg_params_packed->sensor_cadence[3]);
            in_data.min_interval = p_msg_params_packed->sensor_cadence[5];
            in_data.fast_cadence_low = &(p_msg_params_packed->sensor_cadence[6]);
            in_data.fast_cadence_high = &(p_msg_params_packed->sensor_cadence[6 + in_data.property_value_length]);
        }
        else
        {
            in_data.property_value_length = (p_rx_msg->msg_len - MESH_SENSOR_CADENCE_SET_MINLEN)/4;
            if (in_data.property_value_length*4 != (p_rx_msg->msg_len - MESH_SENSOR_CADENCE_SET_MINLEN))
            {
                APP_LOG_WARNING("warning : invalid message length !!!");
                return ;
            }
            in_data.trigger_dlt_down = &(p_msg_params_packed->sensor_cadence[1]);
            in_data.trigger_dlt_up = &(p_msg_params_packed->sensor_cadence[1 + in_data.property_value_length]);
            in_data.min_interval = p_msg_params_packed->sensor_cadence[1 + in_data.property_value_length*2];
            in_data.fast_cadence_low = &(p_msg_params_packed->sensor_cadence[1 + in_data.property_value_length*2 +1]);
            in_data.fast_cadence_high = &(p_msg_params_packed->sensor_cadence[1 + in_data.property_value_length*2 +1 + in_data.property_value_length]);

        }

        if (in_data.min_interval > MESH_SENSOR_STATUS_MIN_INTERVAL_MAX)
        {
            return ;
        }
        APP_LOG_INFO("recv property id: %04x, length %d", in_data.property_id, in_data.property_value_length);
        APP_LOG_INFO("%d, %d", in_data.fast_cadence_period_div, in_data.trigger_type);
        p_server->settings.p_callbacks->sensor_setup_cbs.cadence_set_cb(p_server,
                                                                                                                 p_rx_msg,
                                                                                                                 &in_data,
                                                                                                                 (p_rx_msg->opcode.company_opcode == MESH_SENSOR_CADENCE_OPCODE_SET) ? &out_data : NULL);

        if (p_rx_msg->opcode.company_opcode == MESH_SENSOR_CADENCE_OPCODE_SET)
        {
            (void) cadence_status_send(p_server, p_rx_msg, &out_data);
        }
    }
}

static void handle_setting_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_setup_server_t  * p_server = (sensor_setup_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to set cadence state!!!", p_server->model_instance_index);
    
    sensor_setting_set_params_t in_data = {0};
    sensor_setting_status_params_t out_data = {0};
    sensor_setting_set_msg_pkt_t * p_msg_params_packed = (sensor_setting_set_msg_pkt_t *) p_rx_msg->msg;

    if (p_rx_msg->msg_len > MESH_SENSOR_CADENCE_SET_MINLEN)
    {
        in_data.property_id = gx_read16p((const void *)&p_msg_params_packed->property_id);
        in_data.setting_property_id = gx_read16p((const void *)&p_msg_params_packed->setting_property_id);
        if ((in_data.property_id == 0x0000) || (in_data.setting_property_id == 0x0000))
        {
            return ;
        }
        in_data.setting_raw_length = p_rx_msg->msg_len - 4;
        in_data.setting_raw = p_msg_params_packed->setting_raw;

        p_server->settings.p_callbacks->sensor_setup_cbs.setting_set_cb(p_server,
                                                                                                         p_rx_msg,
                                                                                                         &in_data,
                                                                                                         (p_rx_msg->opcode.company_opcode == MESH_SENSOR_SETTING_OPCODE_SET) ? &out_data : NULL);

        //if (out_data.setting_raw_length > 0)
        {
            if (out_data.setting_access == MESH_SENSOR_SETTING_ACCESS_RD)
            {
                out_data.setting_raw_length = 0;
            }

            if (p_rx_msg->opcode.company_opcode == MESH_SENSOR_SETTING_OPCODE_SET)
            {
                (void) setting_status_send(p_server, p_rx_msg, &out_data);
            }
        }
    }
}

static void handle_cadence_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_setup_server_t * p_server = (sensor_setup_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get cadence state!!!", p_server->model_instance_index);

    if (p_rx_msg->msg_len == 2)
    {
        sensor_cadence_status_params_t out_data = {0};
        sensor_cadence_get_params_t in_data = {0};
        sensor_cadence_get_msg_pkt_t *msg_pkt = (sensor_cadence_get_msg_pkt_t *)p_rx_msg->msg;

        in_data.property_id = gx_read16p((const void *)&msg_pkt->property_id);
        if (in_data.property_id == 0x0000)
        {
            return ;
        }
        p_server->settings.p_callbacks->sensor_setup_cbs.cadence_get_cb(p_server, p_rx_msg, &in_data, &out_data);
        (void) cadence_status_send(p_server, p_rx_msg, &out_data);
    }
}
static void handle_settings_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_setup_server_t * p_server = (sensor_setup_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get settings state!!!", p_server->model_instance_index);

    if (p_rx_msg->msg_len == 2)
		{
        sensor_settings_get_params_t in_data = {0};
        sensor_settings_get_msg_pkt_t *msg_pkt = (sensor_settings_get_msg_pkt_t *)p_rx_msg->msg;
        sensor_settings_status_params_t out_data = {0};

        in_data.property_id = gx_read16p((const void *)&msg_pkt->property_id);
        if (in_data.property_id == 0x0000)
        {
            return ;
        }
        p_server->settings.p_callbacks->sensor_setup_cbs.settings_get_cb(p_server, p_rx_msg, &in_data, &out_data);
        (void) settings_status_send(p_server, p_rx_msg, &out_data);
    }
}

static void handle_setting_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_setup_server_t * p_server = (sensor_setup_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get setting state!!!", p_server->model_instance_index);


    sensor_setting_get_msg_pkt_t *msg_pkt = (sensor_setting_get_msg_pkt_t *)p_rx_msg->msg;
    if (p_rx_msg->msg_len == 4)
    {
        sensor_setting_status_params_t out_data = {0};
        sensor_setting_get_params_t in_data = {0};

        in_data.property_id = gx_read16p((const void *)&msg_pkt->property_id);
        in_data.setting_property_id = gx_read16p((const void *)&msg_pkt->setting_property_id);
        if ((in_data.property_id == 0x0000) || (in_data.setting_property_id == 0x0000))
        {
            return ;
        }

        p_server->settings.p_callbacks->sensor_setup_cbs.setting_get_cb(p_server, p_rx_msg, &in_data, &out_data);
        (void) setting_status_send(p_server, p_rx_msg, &out_data);
    }
}

static void sensor_setup_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;
    mesh_opcode_handler_cb_t handler = NULL;

    APP_LOG_INFO("%s ", __func__);

    for(uint8_t i = 0; i<sensor_setup_server_register_info.num_opcodes; i++)
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

static void sensor_setup_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    sensor_setup_server_t * p_server = (sensor_setup_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL)
    {
        case MESH_SENSOR_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case MESH_SENSOR_SERVER_PUBLISH_SEND_TX_HDL:
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

uint16_t sensor_setup_server_init(sensor_setup_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->sensor_setup_cbs.cadence_get_cb
        || NULL == p_server->settings.p_callbacks->sensor_setup_cbs.cadence_set_cb
        || NULL == p_server->settings.p_callbacks->sensor_setup_cbs.settings_get_cb
        || NULL == p_server->settings.p_callbacks->sensor_setup_cbs.setting_get_cb
        || NULL == p_server->settings.p_callbacks->sensor_setup_cbs.setting_set_cb
        || MESH_SENSOR_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)        
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    sensor_setup_server_register_info.p_args = p_server;
    sensor_setup_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&sensor_setup_server_register_info, &p_server->model_lid);
}

uint16_t sensor_setup_server_cadence_status_publish(sensor_setup_server_t * p_server, 
                                                            const sensor_cadence_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return cadence_status_send(p_server, NULL, p_params);
}

uint16_t sensor_setup_server_settings_status_publish(sensor_setup_server_t * p_server, 
                                                            const sensor_settings_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return settings_status_send(p_server, NULL, p_params);
}

uint16_t sensor_setup_server_setting_status_publish(sensor_setup_server_t * p_server, 
                                                            const sensor_setting_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return setting_status_send(p_server, NULL, p_params);
}

