/**
 *****************************************************************************************
 *
 * @file sensor_server.c
 *
 * @brief Mesh Sensor Server API Implementation.
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
#include "sensor_server.h"
#include "common_utils.h"
/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_descriptor_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_sensor_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_column_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_series_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void sensor_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void sensor_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);
static void sensor_server_publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t sensor_server_opcode_list[] =
{
    MESH_SENSOR_DESCRIPTOR_OPCODE_GET,
    MESH_SENSOR_OPCODE_GET,
    MESH_SENSOR_COLUMN_OPCODE_GET,
    MESH_SENSOR_SERIES_OPCODE_GET,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {MESH_SENSOR_DESCRIPTOR_OPCODE_GET, handle_descriptor_get_cb},
    {MESH_SENSOR_OPCODE_GET, handle_sensor_get_cb},
    {MESH_SENSOR_COLUMN_OPCODE_GET, handle_column_get_cb},
    {MESH_SENSOR_SERIES_OPCODE_GET, handle_series_get_cb},
};

static const mesh_model_cb_t sensor_server_msg_cb = {
    .cb_rx             = sensor_server_rx_cb,
    .cb_sent           = sensor_server_sent_cb,
    .cb_publish_period = sensor_server_publish_period_cb,
};

static mesh_model_register_info_t sensor_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_SENS_SEN),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)sensor_server_opcode_list,
    .num_opcodes = sizeof(sensor_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &sensor_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static uint32_t desc_status_send(sensor_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const sensor_descriptor_status_params_t * p_params)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    sensor_descriptor_status_msg_pkt_t *msg_pkt = NULL;
    uint16_t msg_length = 0;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? MESH_SENSOR_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL
                                        : MESH_SENSOR_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL;
    uint32_t ERR_CODE = MESH_ERROR_NO_ERROR;

    if ((p_params->p_desc != NULL) && (p_params->desc_length != 0))
    {
        msg_pkt = (sensor_descriptor_status_msg_pkt_t *)sys_malloc(p_params->desc_length * sizeof(sensor_descriptor_status_msg_pkt_t));
        if (msg_pkt == NULL)
        {
            APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
            return MESH_ERROR_INSUFFICIENT_RESOURCES;
        }
        for (uint8_t i = 0; i < p_params->desc_length; i++)
        {
            msg_pkt[i].sensor_descriptor = (uint64_t)p_params->p_desc[i].sensor_property_id
                                                                | ((uint64_t)(p_params->p_desc[i].sensor_positive_tolerance&SENSOR_TOLERANCE_MASK)<<16)
                                                                | ((uint64_t)(p_params->p_desc[i].sensor_negative_tolerance&SENSOR_TOLERANCE_MASK)<<28)
                                                                | ((uint64_t)(p_params->p_desc[i].sensor_sampling_function)<<40)
                                                                | ((uint64_t)(p_params->p_desc[i].sensor_measurement_period)<<48)
                                                                | ((uint64_t)(p_params->p_desc[i].sensor_update_interval)<<56);
            msg_length += 8;
        }

    }
    else if ((p_params->desc_length == 2) && (0x0000 != p_params->sensor_property_id))
    {
        msg_pkt = (sensor_descriptor_status_msg_pkt_t *)sys_malloc(2);
        if (msg_pkt == NULL)
        {
            APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
            return MESH_ERROR_INSUFFICIENT_RESOURCES;
        }
        gx_write16p((void const *) &(msg_pkt->sensor_descriptor),  p_params->sensor_property_id);
        msg_length = 2;
    }
    else
    {
        APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_DESCRIPTOR_OPCODE_STATUS),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) msg_pkt,
        .data_send_len = msg_length,
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

static uint32_t sensor_status_send(sensor_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const sensor_status_params_t * p_params,
                                  const uint16_t p_params_length)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    uint8_t *msg_pkt = NULL;
    uint16_t total_length = 0;

    uint8_t tx_hdl = (NULL == p_rx_msg) ? MESH_SENSOR_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL
                                        : MESH_SENSOR_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL;
    uint32_t ERR_CODE = MESH_ERROR_NO_ERROR;

    if ((NULL != p_params) && (0 != p_params_length))
    {
        uint16_t sensor_state_length = p_params_length;
        uint8_t *p_data = NULL;

        while(sensor_state_length)
        {
            if ((p_params[sensor_state_length-1].format & MESH_SENSOR_STATUS_FORMAT_B) == MESH_SENSOR_STATUS_FORMAT_B)
            {
                total_length += 3;
            }
            else
            {
                total_length += 2;
            }

            if (p_params[sensor_state_length-1].sensor_data_length < 0x80)
            {
                total_length += p_params[sensor_state_length-1].sensor_data_length;
            }

            sensor_state_length --;
        }

        msg_pkt = (uint8_t *)sys_malloc(total_length);
        if (msg_pkt == NULL)
        {
            APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
            return MESH_ERROR_INSUFFICIENT_RESOURCES;
        }

        p_data = msg_pkt;

        for (uint8_t i=0; i<p_params_length; i++)
        {
            if ((p_params[i].format & MESH_SENSOR_STATUS_FORMAT_B) == MESH_SENSOR_STATUS_FORMAT_B)
            {
                *p_data = MESH_SENSOR_STATUS_FORMAT_B | (((p_params[i].sensor_data_length-1)&0x7F)<<1) ;
                p_data ++;
                *p_data = p_params[i].property_id & 0xFF;
                p_data++;
                *p_data = (p_params[i].property_id>>8) & 0xFF;
                p_data++;
            }
            else
            {
                *p_data = MESH_SENSOR_STATUS_FORMAT_A | (((p_params[i].sensor_data_length-1)&0xF)<<1) | (p_params[i].property_id<<5);
                p_data ++;
                *p_data = (p_params[i].property_id>>3);
                p_data ++;
            }

            if (p_params[i].sensor_data_length < 0x80)
            {
                memcpy(p_data, p_params[i].p_sensor_data, p_params[i].sensor_data_length);
                p_data += p_params[i].sensor_data_length;
            }
        }

        APP_LOG_INFO("[%s]:%d send data length %d.", __func__, __LINE__, total_length);
    }
    else
    {
        APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_OPCODE_STATUS),
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

static uint32_t column_status_send(sensor_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const sensor_column_status_params_t * p_params)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    sensor_column_status_msg_pkt_t *msg_pkt = NULL;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? MESH_SENSOR_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL
                                        : MESH_SENSOR_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL;
    uint16_t total_length = 0;
    uint32_t ERR_CODE = MESH_ERROR_NO_ERROR;

    if ((p_params->raw_x != NULL) && (p_params->raw_x_length != 0))
    {
        msg_pkt = (sensor_column_status_msg_pkt_t *)sys_malloc(p_params->raw_x_length + p_params->raw_y_length + p_params->width_length + SENSOR_PROPERTY_ID_LENGTH);
        if (msg_pkt == NULL)
        {
            APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
            return MESH_ERROR_INSUFFICIENT_RESOURCES;
        }
        gx_write16p((void const *) &(msg_pkt->property_id),  p_params->property_id);
        total_length += SENSOR_PROPERTY_ID_LENGTH;
        memcpy(msg_pkt->column_data, p_params->raw_x, p_params->raw_x_length);
        total_length += p_params->raw_x_length;

        if ((p_params->width!= NULL) && (p_params->width_length!= 0) && (p_params->raw_y != NULL) && (p_params->raw_y_length != 0))
        {
            memcpy(msg_pkt->column_data + p_params->raw_x_length, p_params->width, p_params->width_length);
            total_length += p_params->width_length;
            memcpy(msg_pkt->column_data + p_params->raw_x_length + p_params->width_length, p_params->raw_y, p_params->raw_y_length);
            total_length += p_params->raw_y_length;
        }
    }    
    else
    {
        APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_COLUMN_OPCODE_STATUS),
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

static uint32_t series_status_send(sensor_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const sensor_series_status_params_t * p_params)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    sensor_series_status_msg_pkt_t *msg_pkt = NULL;
    uint16_t raw_length = SENSOR_PROPERTY_ID_LENGTH;

    uint8_t tx_hdl = (NULL == p_rx_msg) ? MESH_SENSOR_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL
                                        : MESH_SENSOR_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * MESH_SENSOR_SERVER_TX_HDL_TOTAL;
    uint32_t ERR_CODE = MESH_ERROR_NO_ERROR;

    if (p_params != NULL)
    {

        if ((p_params->series_data_num != 0) && (NULL != p_params->series_data))
        {
            raw_length += p_params->series_data_num * (p_params->series_data[0].raw_x_length + p_params->series_data[0].width_length + p_params->series_data[0].raw_y_length);
        }

        msg_pkt = (sensor_series_status_msg_pkt_t *)sys_malloc(raw_length);
        if (msg_pkt == NULL)
        {
            APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
            return MESH_ERROR_INSUFFICIENT_RESOURCES;
        }
        gx_write16p((void const *) &(msg_pkt->property_id),  p_params->property_id);

        if (raw_length > SENSOR_PROPERTY_ID_LENGTH)
        {
            uint8_t *p_series_data = NULL;

            p_series_data = msg_pkt->series_data;
            for (uint8_t i=0; i<p_params->series_data_num; i++)
            {
                memcpy(p_series_data, p_params->series_data[i].raw_x, p_params->series_data[i].raw_x_length);
                p_series_data ++;
                memcpy(p_series_data, p_params->series_data[i].width, p_params->series_data[i].width_length);
                p_series_data ++;
                memcpy(p_series_data, p_params->series_data[i].raw_y, p_params->series_data[i].raw_y_length);
                p_series_data ++;
            }
        }

        APP_LOG_INFO("[%s]:%d send data length %d.", __func__, __LINE__, raw_length);
    }    
    else
    {
        APP_LOG_INFO("[%s]:%d err return.", __func__, __LINE__);
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_SERIES_OPCODE_STATUS),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) msg_pkt,
        .data_send_len = raw_length,
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

static void handle_descriptor_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_server_t * p_server = (sensor_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get sensor descriptor state!!!", p_server->model_instance_index);

    sensor_descriptor_status_params_t out_data = {
        .desc_length = 0,
        .p_desc = NULL,
    };
    sensor_descriptor_get_msg_pkt_t *msg_pkt = (sensor_descriptor_get_msg_pkt_t *)p_rx_msg->msg;
    sensor_descriptor_get_params_t p_desc_get ;

    if (p_rx_msg->msg_len == 2)
    {
        p_desc_get.property_id = gx_read16p((const void *)&msg_pkt->property_id);
        if (p_desc_get.property_id == 0x0000)
        {
            return ;
        }
    }

    if ((p_rx_msg->msg_len == 0) || (p_rx_msg->msg_len == 2))
    {
        p_server->settings.p_callbacks->sensor_cbs.descrip_get_cb(p_server, p_rx_msg, (p_rx_msg->msg_len == 2)?(&p_desc_get):NULL, &out_data);
        (void) desc_status_send(p_server, p_rx_msg, &out_data);
    }
}

static void handle_sensor_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_server_t * p_server = (sensor_server_t *) p_args;
    sensor_status_params_t *out_data_ptr = NULL;
    uint16_t out_length = 0;
    sensor_get_msg_pkt_t *msg_pkt = (sensor_get_msg_pkt_t *)p_rx_msg->msg;
    sensor_get_params_t p_sensor_get ;

    APP_LOG_INFO("[%s] enter.", __func__);   
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get sensor state!!!", p_server->model_instance_index);

    if (p_rx_msg->msg_len == 2)
    {
        p_sensor_get.property_id = gx_read16p((const void *)&msg_pkt->property_id);

        if (p_sensor_get.property_id == 0x0000)
        {
            return ;
        }
    }

    if ((p_rx_msg->msg_len == 0) || (p_rx_msg->msg_len == 2))
    {
        p_server->settings.p_callbacks->sensor_cbs.get_cb(p_server, p_rx_msg, (p_rx_msg->msg_len == 2)?(&p_sensor_get):NULL, &out_data_ptr, &out_length, false);
        if ((out_length != 0) && (NULL != out_data_ptr))
        {
            (void) sensor_status_send(p_server, p_rx_msg, out_data_ptr, out_length);

            sys_free(out_data_ptr);
            out_data_ptr = NULL;
        }
    }
}

static void handle_column_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_server_t * p_server = (sensor_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get sensor column state!!!", p_server->model_instance_index);

    sensor_column_status_params_t out_data = {
        .raw_x_length = 0,
        .raw_x = NULL,
        .width_length = 0,
        .width = NULL,
        .raw_y_length = 0,
        .raw_y = NULL,
    };
    sensor_column_get_msg_pkt_t *msg_pkt = (sensor_column_get_msg_pkt_t *)p_rx_msg->msg;
    sensor_column_get_params_t p_column_get ;

    p_column_get.raw_x_length = p_rx_msg->msg_len-2;
    p_column_get.property_id = gx_read16p((const void *)&msg_pkt->property_id);
    if (p_column_get.property_id == 0x0000)
    {
        return ;
    }
    p_column_get.raw_x = msg_pkt->raw_x;

    p_server->settings.p_callbacks->sensor_cbs.column_get_cb(p_server, p_rx_msg, &p_column_get, &out_data);
    (void) column_status_send(p_server, p_rx_msg, &out_data);
}

static void handle_series_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_server_t * p_server = (sensor_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);   
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get sensor series state!!!", p_server->model_instance_index);

    sensor_series_status_params_t out_data = {
        .series_data_num = 0,
        .series_data = NULL,
    };
    sensor_series_get_msg_pkt_t *msg_pkt = (sensor_series_get_msg_pkt_t *)p_rx_msg->msg;
    sensor_series_get_params_t p_series_get ;

    p_series_get.property_id = gx_read16p((const void *)&msg_pkt->property_id);
    if (p_series_get.property_id == 0x0000)
    {
        return ;
    }

    if (p_rx_msg->msg_len-2 > 0)
    {
        p_series_get.series_x_length = (p_rx_msg->msg_len-2)/2;
        p_series_get.series_x1 = &(msg_pkt->series_x[0]);
        p_series_get.series_x2 = &(msg_pkt->series_x[p_series_get.series_x_length]);

    }
    else
    {
        p_series_get.series_x_length = 0;
    }
    p_server->settings.p_callbacks->sensor_cbs.series_get_cb(p_server, p_rx_msg, &p_series_get, &out_data);
    (void) series_status_send(p_server, p_rx_msg, &out_data);

}

static void sensor_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;
    APP_LOG_INFO("%s  0x%x", __func__, company_opcode);

    for(uint8_t i = 0; i<sensor_server_register_info.num_opcodes; i++)
    {
        APP_LOG_INFO("0x%x : 0x%x", company_opcode, m_opcode_handlers[i].opcode);

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

static void sensor_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    sensor_server_t * p_server = (sensor_server_t *) p_args;
    
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

static void sensor_server_publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args)
{
    sensor_server_t * p_server = (sensor_server_t *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);

    p_server->settings.p_callbacks->sensor_cbs.publish_period_cb(p_server, p_ind);
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t sensor_server_init(sensor_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->sensor_cbs.descrip_get_cb
        || NULL == p_server->settings.p_callbacks->sensor_cbs.get_cb
        || NULL == p_server->settings.p_callbacks->sensor_cbs.column_get_cb
        || NULL == p_server->settings.p_callbacks->sensor_cbs.series_get_cb
        || NULL == p_server->settings.p_callbacks->sensor_cbs.publish_period_cb
        || MESH_SENSOR_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)        
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    sensor_server_register_info.p_args = p_server;
    sensor_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&sensor_server_register_info, &p_server->model_lid);
}

uint16_t sensor_server_desc_status_publish(sensor_server_t * p_server, 
                                                            const sensor_descriptor_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return desc_status_send(p_server, NULL, p_params);
}

uint16_t sensor_server_status_publish(sensor_server_t * p_server, bool pub_map)
{
    uint16_t out_length = 0;
    sensor_status_params_t *out_data_ptr = NULL;
    uint16_t Err_code = MESH_ERROR_NO_ERROR;

    APP_LOG_INFO("[%s]:pub_map %d", __func__, pub_map);
    if (NULL == p_server)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->settings.p_callbacks->sensor_cbs.get_cb(p_server, NULL, NULL, &out_data_ptr, &out_length, pub_map);
    if ((out_length != 0) && (NULL != out_data_ptr))
    {
        Err_code = sensor_status_send(p_server, NULL, out_data_ptr, out_length);

        sys_free(out_data_ptr);
        out_data_ptr = NULL;
    }

    return Err_code;
}

