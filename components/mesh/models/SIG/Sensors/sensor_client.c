/**
 *****************************************************************************************
 *
 * @file sensor_client.c
 *
 * @brief Mesh Sensor Client API Implementation.
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
#include "sensor_client.h"
#include "common_utils.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
 
static void descriptor_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void cadence_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void settings_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void setting_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void sensor_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void column_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void series_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void sensor_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void sensor_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t sensor_client_opcode_list[] =
{
    MESH_SENSOR_DESCRIPTOR_OPCODE_STATUS,
    MESH_SENSOR_CADENCE_OPCODE_STATUS,
    MESH_SENSOR_SETTINGS_OPCODE_STATUS,
    MESH_SENSOR_SETTING_OPCODE_STATUS,
    MESH_SENSOR_OPCODE_STATUS,
    MESH_SENSOR_COLUMN_OPCODE_STATUS,
    MESH_SENSOR_SERIES_OPCODE_STATUS
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {MESH_SENSOR_DESCRIPTOR_OPCODE_STATUS, descriptor_status_handle},
    {MESH_SENSOR_CADENCE_OPCODE_STATUS, cadence_status_handle},
    {MESH_SENSOR_SETTINGS_OPCODE_STATUS, settings_status_handle},
    {MESH_SENSOR_SETTING_OPCODE_STATUS, setting_status_handle},
    {MESH_SENSOR_OPCODE_STATUS, sensor_status_handle},
    {MESH_SENSOR_COLUMN_OPCODE_STATUS, column_status_handle},
    {MESH_SENSOR_SERIES_OPCODE_STATUS, series_status_handle}
};

static const mesh_model_cb_t sensor_client_msg_cb = {
    .cb_rx             = sensor_client_rx_cb,
    .cb_sent           = sensor_client_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t sensor_client_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_SENC_SEN),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)sensor_client_opcode_list,
    .num_opcodes = sizeof(sensor_client_opcode_list) / sizeof(uint16_t),
    .p_cb = &sensor_client_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void descriptor_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_client_t * p_client = (sensor_client_t *) p_args;
    sensor_descriptor_status_params_t in_data = {0, 0, NULL};

    if (p_rx_msg->msg_len >= MESH_SENSOR_DESC_STATUS_MINLEN)
    {
        sensor_descriptor_status_msg_pkt_t * p_msg_params_packed = (sensor_descriptor_status_msg_pkt_t *) p_rx_msg->msg;

        if (p_rx_msg->msg_len == MESH_SENSOR_DESC_STATUS_MINLEN)
        {
            in_data.desc_length = p_rx_msg->msg_len;
            in_data.sensor_property_id = gx_read16p((void const *)& p_msg_params_packed->sensor_descriptor);
        }
        else if (p_rx_msg->msg_len%8 == 0)//8*N descriptor
        {
            sensor_descriptor_status_params__t *ptr = NULL;
            uint8_t recv_idx = 0;

            in_data.desc_length = p_rx_msg->msg_len/8;
            in_data.p_desc = (sensor_descriptor_status_params__t *)sys_malloc(sizeof(sensor_descriptor_status_params__t) * in_data.desc_length);

            if (NULL != in_data.p_desc)
            {
                ptr = in_data.p_desc;

                while((ptr != NULL) && (recv_idx < p_rx_msg->msg_len))
                {
                    ptr->sensor_property_id = gx_read16p((void const *)& p_msg_params_packed->sensor_descriptor);   //16 bits
                    ptr->sensor_positive_tolerance = (p_msg_params_packed->sensor_descriptor >> 16) & 0xFFF;    //12 bits
                    ptr->sensor_negative_tolerance = (p_msg_params_packed->sensor_descriptor >> 28) & 0xFFF;    //12 bits
                    ptr->sensor_sampling_function = (p_msg_params_packed->sensor_descriptor >> 40) & 0xFF;     //8 bits
                    ptr->sensor_measurement_period = (p_msg_params_packed->sensor_descriptor >> 48) & 0xFF; //8 bits
                    ptr->sensor_update_interval = (p_msg_params_packed->sensor_descriptor >> 56) & 0xFF;         //8 bits

                    recv_idx += 8;
                    ptr ++;
                    p_msg_params_packed ++;
                }
                
            }
        }
        else
        {
            in_data.desc_length = 0;
        }

        if (in_data.desc_length != 0)
        {
            p_client->settings.p_callbacks->desc_status_cb(p_client, p_rx_msg, &in_data);
        }

        if (in_data.p_desc != NULL)
        {
            sys_free(in_data.p_desc);
            in_data.p_desc = NULL;
        }
    }
}

static void cadence_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_client_t * p_client = (sensor_client_t *) p_args;
    sensor_cadence_status_params_t in_data = {0,};
    sensor_cadence_status_msg_pkt_t * p_msg_params_packed = (sensor_cadence_status_msg_pkt_t *) p_rx_msg->msg;
    bool is_signed = false;
    bool is_float = false ;
    uint8_t bit_len = 0;

    in_data.property_id = gx_read16p((void const * )&p_msg_params_packed->property_id);
    in_data.fast_cadence_period_div = p_msg_params_packed->sensor_cadence[0] & 0x7F;
    in_data.trigger_type = (p_msg_params_packed->sensor_cadence[0]>>7) & MESH_SENSOR_CADENCE_TRIGGER_PERCENT;

    if (GET_VAULE_INFO_SUCCESS == get_property_value_info(in_data.property_id, &is_signed, &is_float, &bit_len))
    {
        if (in_data.trigger_type == MESH_SENSOR_CADENCE_TRIGGER_VALUE)
        {
            in_data.property_value_length = bit_len/8;
            in_data.trigger_dlt_down = &(p_msg_params_packed->sensor_cadence[1]);
            in_data.trigger_dlt_up = &(p_msg_params_packed->sensor_cadence[1 + in_data.property_value_length]);
            in_data.min_interval = p_msg_params_packed->sensor_cadence[1 + in_data.property_value_length*2];
            in_data.fast_cadence_low = &(p_msg_params_packed->sensor_cadence[1 + in_data.property_value_length*2 +1]);
            in_data.fast_cadence_high = &(p_msg_params_packed->sensor_cadence[1 + in_data.property_value_length*2 +1 + in_data.property_value_length]);
        }
        else
        {
            in_data.property_value_length = bit_len/8;
            in_data.trigger_dlt_down = &(p_msg_params_packed->sensor_cadence[1]);
            in_data.trigger_dlt_up = &(p_msg_params_packed->sensor_cadence[3]);
            in_data.min_interval = p_msg_params_packed->sensor_cadence[5];
            in_data.fast_cadence_low = &(p_msg_params_packed->sensor_cadence[6]);
            in_data.fast_cadence_high = &(p_msg_params_packed->sensor_cadence[6 + in_data.property_value_length]);
        }

        p_client->settings.p_callbacks->cadence_status_cb(p_client, p_rx_msg, &in_data);
    }

}

static void settings_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_client_t * p_client = (sensor_client_t *) p_args;
    sensor_settings_status_params_t in_data = {0,};
    sensor_settings_status_msg_pkt_t * p_msg_params_packed = (sensor_settings_status_msg_pkt_t *) p_rx_msg->msg;

    if (p_rx_msg->msg_len >= MESH_SENSOR_SETTINGS_STATUS_MINLEN)
    {
        in_data.property_id = gx_read16p((void const * )&p_msg_params_packed->property_id);
        in_data.setting_id_number = p_rx_msg->msg_len/2 - 1;
        if (in_data.setting_id_number > 0)
        {
            in_data.setting_property_id = p_msg_params_packed->setting_property_id;
        }
        p_client->settings.p_callbacks->settings_status_cb(p_client, p_rx_msg, &in_data);
    }
}

static void setting_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_client_t * p_client = (sensor_client_t *) p_args;
    sensor_setting_status_params_t in_data = {0,};
    sensor_setting_status_msg_pkt_t * p_msg_params_packed = (sensor_setting_status_msg_pkt_t *) p_rx_msg->msg;

    if (p_rx_msg->msg_len >= MESH_SENSOR_SETTING_STATUS_MINLEN)
    {
        in_data.property_id = gx_read16p((void const * )&p_msg_params_packed->property_id);
        in_data.setting_property_id = gx_read16p((void const * )&p_msg_params_packed->setting_property_id);
        if (p_rx_msg->msg_len > MESH_SENSOR_SETTING_STATUS_MINLEN)
        {
            in_data.setting_access = p_msg_params_packed->setting_access;
            in_data.setting_raw_length = p_rx_msg->msg_len - 5;
            in_data.setting_raw = p_msg_params_packed->setting_raw;
        }
        p_client->settings.p_callbacks->setting_status_cb(p_client, p_rx_msg, &in_data);
    }
}

static void sensor_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_client_t * p_client = (sensor_client_t *) p_args;
    sensor_status_params_t in_data = {0,};
    //sensor_status_msg_pkt_t * p_msg_params_packed = (sensor_status_msg_pkt_t *) p_rx_msg->msg;
    property_value_type_t type = NOT_FIND_ID;
    uint8_t data_offset = 0;

    while(p_rx_msg->msg_len > data_offset)
    {
        in_data.format = p_rx_msg->msg[data_offset] & MESH_SENSOR_STATUS_FORMAT_B;
        if (in_data.format == MESH_SENSOR_STATUS_FORMAT_A)
        {
            in_data.sensor_data_length = (p_rx_msg->msg[data_offset]>>1) & 0xF;
            in_data.property_id = (p_rx_msg->msg[data_offset]>>5) | (p_rx_msg->msg[data_offset + 1]<<3);
            type = get_property_value_type(in_data.property_id);
            data_offset += 2;

        }
        else
        {
            in_data.sensor_data_length = (p_rx_msg->msg[data_offset]>>1) & 0x7F;
            in_data.property_id = p_rx_msg->msg[data_offset + 1] | p_rx_msg->msg[data_offset + 2]<<8;
            type = get_property_value_type(in_data.property_id);
            data_offset += 3;
        }

        if (in_data.sensor_data_length != 0x7F)// The value 0x7F represents a length of zero
        {
            switch(type)
            {
                case PROPERTY_UINT8:
                    in_data.sensor_data_length = 1;
                    break;
                case PROPERTY_UINT16:
                    in_data.sensor_data_length = 2;
                    break;
                case PROPERTY_UINT24:
                    in_data.sensor_data_length = 3;
                    break;
                case PROPERTY_UINT32:
                    in_data.sensor_data_length = 4;
                    break;
                case PROPERTY_FLOAT32:
                    in_data.sensor_data_length = 4;
                    break;
                default:
                    break;
            }
        }
        in_data.p_sensor_data = (uint8_t *)&(p_rx_msg->msg[data_offset]);
        data_offset += in_data.sensor_data_length;

        p_client->settings.p_callbacks->sensor_status_cb(p_client, p_rx_msg, &in_data);
    }
}

static void column_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_client_t * p_client = (sensor_client_t *) p_args;
    sensor_column_status_params_t in_data = {0,};
    bool is_signed = false;
    bool is_float = false ;
    uint8_t bit_len = 0;

    in_data.property_id = gx_read16p((void const *)&(p_rx_msg->msg[0]));
    if (GET_VAULE_INFO_SUCCESS == get_property_value_info(in_data.property_id, &is_signed, &is_float, &bit_len))
    {
        APP_LOG_INFO("property id 0x%x, length %d", in_data.property_id, bit_len/8);
        in_data.raw_x_length = bit_len/8;
        in_data.raw_x = (uint8_t *)&p_rx_msg->msg[2];

        if (p_rx_msg->msg_len > in_data.raw_x_length + 2)
        {
            in_data.raw_y_length = in_data.width_length = in_data.raw_x_length;
            in_data.width = (uint8_t *)&p_rx_msg->msg[2 + in_data.raw_x_length];
            in_data.raw_y = (uint8_t *)&p_rx_msg->msg[2 + in_data.raw_x_length + in_data.width_length];
        }
        p_client->settings.p_callbacks->column_status_cb(p_client, p_rx_msg, &in_data);
    }

    //APP_LOG_INFO("%s Enter: property 0x%04x, length %d, value 0x%08x", __func__, in_data.property_id, p_rx_msg->msg_len-2, *(uint32_t *)&(p_rx_msg->msg[2]));
}

static void series_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    sensor_client_t * p_client = (sensor_client_t *) p_args;
    sensor_series_status_params_t in_data = {0,};
    bool is_signed = false;
    bool is_float = false ;
    uint8_t bit_len = 0;
    uint16_t msg_offset = 0;

    in_data.property_id = gx_read16p((void const *)&(p_rx_msg->msg[0]));
    msg_offset += 2;

    if (GET_VAULE_INFO_SUCCESS == get_property_value_info(in_data.property_id, &is_signed, &is_float, &bit_len))
    {
        APP_LOG_INFO("property id 0x%x, length %d", in_data.property_id, bit_len/8);
        in_data.series_data_num = (p_rx_msg->msg_len - 2) / 3 / (bit_len/8);
        in_data.series_data = (sensor_series_status_params__t *)sys_malloc(sizeof(sensor_series_status_params__t) * in_data.series_data_num);

        if (NULL != in_data.series_data)
        {
            sensor_series_status_params__t * ptr = in_data.series_data;
            while(msg_offset  < p_rx_msg->msg_len)
            {
                ptr->raw_x_length = ptr->width_length = ptr->raw_y_length =bit_len /8;
                ptr->raw_x = (uint8_t *)&p_rx_msg->msg[msg_offset];
                ptr->width = (uint8_t *)&p_rx_msg->msg[msg_offset + ptr->raw_x_length];
                ptr->raw_y = (uint8_t *)&p_rx_msg->msg[msg_offset + ptr->raw_x_length + ptr->width_length];

                msg_offset += ptr->raw_x_length * 3;
                ptr ++;
            }
        }

        p_client->settings.p_callbacks->series_status_cb(p_client, p_rx_msg, &in_data);
        if (NULL != in_data.series_data)
        {
            sys_free(in_data.series_data);
            in_data.series_data = NULL;
        }
    }

    //APP_LOG_INFO("%s Enter: property 0x%04x, length %d, value 0x%08x", __func__, in_data.property_id, p_rx_msg->msg_len-2, *(uint32_t *)&(p_rx_msg->msg[2]));
}

#ifdef MESH_MODEL_BQB_TEST
static void message_send_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, uint8_t * p_buffer, uint16_t length)
{
    mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_SIG(company_opcode);

    // fill publish data by tx_hdl
    p_msg_tx->model_lid        = model_lid;
    p_msg_tx->opcode           = opcode;
    p_msg_tx->tx_hdl           = tx_hdl;
    p_msg_tx->p_data_send      = p_buffer;
    p_msg_tx->data_send_len    = length;
    p_msg_tx->dst              = 0x01;
    p_msg_tx->appkey_index     = 0x00;
}

static uint16_t model_send_unicast_dev(sensor_client_t *p_client, uint16_t opcode, uint8_t tx_hdl, uint8_t *p_buffer, uint16_t length)
{
    mesh_model_send_info_t model_msg_send;
    message_send_create(&model_msg_send, p_client->model_lid, opcode, tx_hdl, p_buffer, length);

    return mesh_model_pdu_send(&model_msg_send);
}
#else
static void message_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, uint8_t * p_buffer, uint16_t length)
{
    mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_SIG(company_opcode);

    // fill publish data by tx_hdl
    p_msg_tx->model_lid        = model_lid;
    p_msg_tx->opcode           = opcode;
    p_msg_tx->tx_hdl           = tx_hdl;
    p_msg_tx->p_data_send      = p_buffer;
    p_msg_tx->data_send_len    = length;
    p_msg_tx->dst              = MESH_INVALID_ADDR;
    p_msg_tx->appkey_index     = MESH_INVALID_KEY_INDEX;
}
#endif

static void sensor_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<sensor_client_register_info.num_opcodes; i++)
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

static void sensor_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args)
{
    sensor_client_t * p_client = (sensor_client_t *) p_args;
    
    switch(p_sent->tx_hdl - p_client->model_instance_index * MESH_SENSOR_CLIENT_TX_HDL_TOTAL)
    {
        case MESH_SENSOR_CLIENT_GET_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent get message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send get message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case MESH_SENSOR_CLIENT_SET_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent set message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send set message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case MESH_SENSOR_CLIENT_SET_UNRELIABLE_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent set(unreliable) message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send set(unreliable) message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        default:
            APP_LOG_INFO("msg has been sent!!!");
            break;
    }   
}



/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t sensor_client_init(sensor_client_t *p_client, uint8_t element_offset)
{
    if (NULL == p_client
        || NULL == p_client->settings.p_callbacks
        || NULL == p_client->settings.p_callbacks->desc_status_cb
        || NULL == p_client->settings.p_callbacks->cadence_status_cb
        || NULL == p_client->settings.p_callbacks->settings_status_cb
        || NULL == p_client->settings.p_callbacks->setting_status_cb
        || NULL == p_client->settings.p_callbacks->sensor_status_cb
        || NULL == p_client->settings.p_callbacks->ack_transaction_status_cb
        || MESH_SENSOR_CLIENT_INSTANCE_COUNT_MAX <= p_client->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    sensor_client_register_info.p_args         = p_client;
    sensor_client_register_info.element_offset = element_offset;
    
    return mesh_model_register(&sensor_client_register_info, &p_client->model_lid);
}

uint16_t sensor_descriptor_client_get(sensor_client_t * p_client, const sensor_descriptor_get_params_t * p_params)
{
    sensor_descriptor_get_msg_pkt_t get;
    uint16_t msg_length = 0;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = MESH_SENSOR_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * MESH_SENSOR_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_DESCRIPTOR_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

    if (p_client == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            if (p_params != NULL)
            {
                gx_write16p((void const *)&get.property_id, p_params->property_id);
                msg_length += 2;
            }

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, MESH_SENSOR_DESCRIPTOR_OPCODE_GET, tx_hdl, (uint8_t *)&get, msg_length);
#else
            message_create(&model_msg_send, p_client->model_lid, MESH_SENSOR_DESCRIPTOR_OPCODE_GET, tx_hdl, (uint8_t *)&get, msg_length);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t sensor_cadence_client_get(sensor_client_t * p_client, const sensor_cadence_get_params_t * p_params)
{
    sensor_cadence_get_msg_pkt_t get;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = MESH_SENSOR_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * MESH_SENSOR_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_CADENCE_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            gx_write16p((void const *)&get.property_id, p_params->property_id);

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, MESH_SENSOR_CADENCE_OPCODE_GET, tx_hdl, (uint8_t *)&get, MESH_SENSOR_CADENCE_GET_MINLEN);
#else
            message_create(&model_msg_send, p_client->model_lid, MESH_SENSOR_CADENCE_OPCODE_GET, tx_hdl, (uint8_t *)&get, MESH_SENSOR_CADENCE_GET_MINLEN);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t sensor_cadence_client_set(sensor_client_t * p_client, const sensor_cadence_set_params_t * p_params)
{
    sensor_cadence_set_msg_pkt_t *set = NULL;
    uint16_t msg_length = 0;
    uint16_t Err_code = MESH_ERROR_NO_ERROR;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = MESH_SENSOR_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * MESH_SENSOR_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_CADENCE_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {

            if (p_params->trigger_type == MESH_SENSOR_CADENCE_TRIGGER_VALUE)
            {
                msg_length = MESH_SENSOR_CADENCE_SET_MINLEN + p_params->property_value_length * 4;
                set = (sensor_cadence_set_msg_pkt_t *)sys_malloc(msg_length);

                if (NULL != set)
                {
                    memcpy(&(set->sensor_cadence[1]), p_params->trigger_dlt_down, p_params->property_value_length);
                    memcpy(&(set->sensor_cadence[1 + p_params->property_value_length]), p_params->trigger_dlt_up, p_params->property_value_length);
                    set->sensor_cadence[1 + p_params->property_value_length * 2] = p_params->min_interval;
                    memcpy(&(set->sensor_cadence[2 + p_params->property_value_length * 2]), p_params->fast_cadence_low, p_params->property_value_length);
                    memcpy(&(set->sensor_cadence[2 + p_params->property_value_length * 3]), p_params->fast_cadence_high, p_params->property_value_length);
                }
            }
            else if (p_params->trigger_type == MESH_SENSOR_CADENCE_TRIGGER_PERCENT)
            {
                msg_length = MESH_SENSOR_CADENCE_SET_MINLEN + 2 * 2 + p_params->property_value_length * 2;
                set = (sensor_cadence_set_msg_pkt_t *)sys_malloc(msg_length);

                if (NULL != set)
                {
                    gx_write16p(&(set->sensor_cadence[1]), *(uint16_t *)p_params->trigger_dlt_down);
                    gx_write16p(&(set->sensor_cadence[3]), *(uint16_t *)p_params->trigger_dlt_up);
                    set->sensor_cadence[5] = p_params->min_interval;
                    memcpy(&(set->sensor_cadence[6]), p_params->fast_cadence_low, p_params->property_value_length);
                    memcpy(&(set->sensor_cadence[6 + p_params->property_value_length]), p_params->fast_cadence_high, p_params->property_value_length);
                }
            }

            if (NULL != set)
            {
                gx_write16p((void const *) &set->property_id, p_params->property_id);
                set->sensor_cadence[0] = (p_params->fast_cadence_period_div & 0x7F) | ((p_params->trigger_type & MESH_SENSOR_CADENCE_TRIGGER_PERCENT)  << 7);

#ifdef MESH_MODEL_BQB_TEST
                Err_code = model_send_unicast_dev(p_client, MESH_SENSOR_CADENCE_OPCODE_SET, tx_hdl, (uint8_t *)set, msg_length);
#else
                message_create(&model_msg_send, p_client->model_lid, MESH_SENSOR_CADENCE_OPCODE_SET, tx_hdl, (uint8_t *)set, msg_length);
                Err_code = mesh_model_publish(&model_msg_send, &reliable_info);
#endif
                sys_free(set);
                set = NULL;

                return Err_code;
            }
            else
            {
                return MESH_ERROR_INSUFFICIENT_RESOURCES;
            }

        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t sensor_cadence_client_set_unack(sensor_client_t * p_client, const sensor_cadence_set_params_t * p_params)
{
    sensor_cadence_set_msg_pkt_t *set_un = NULL;
    uint8_t msg_length = 0;
    uint16_t Err_code = MESH_ERROR_NO_ERROR;
    uint8_t tx_hdl = MESH_SENSOR_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * MESH_SENSOR_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (p_params->trigger_type == MESH_SENSOR_CADENCE_TRIGGER_VALUE)
    {
        msg_length = MESH_SENSOR_CADENCE_SET_MINLEN + p_params->property_value_length * 4;
        set_un = (sensor_cadence_set_msg_pkt_t *)sys_malloc(msg_length);

        if (NULL != set_un)
        {
            memcpy(&(set_un->sensor_cadence[1]), p_params->trigger_dlt_down, p_params->property_value_length);
            memcpy(&(set_un->sensor_cadence[1 + p_params->property_value_length]), p_params->trigger_dlt_up, p_params->property_value_length);
            set_un->sensor_cadence[1 + p_params->property_value_length * 2] = p_params->min_interval;
            memcpy(&(set_un->sensor_cadence[2 + p_params->property_value_length * 2]), p_params->fast_cadence_low, p_params->property_value_length);
            memcpy(&(set_un->sensor_cadence[2 + p_params->property_value_length * 3]), p_params->fast_cadence_high, p_params->property_value_length);
        }
    }
    else if (p_params->trigger_type == MESH_SENSOR_CADENCE_TRIGGER_PERCENT)
    {
        msg_length = MESH_SENSOR_CADENCE_SET_MINLEN + 2 * 2 + p_params->property_value_length * 2;
        set_un = (sensor_cadence_set_msg_pkt_t *)sys_malloc(msg_length);

        if (NULL != set_un)
        {
            gx_write16p(&(set_un->sensor_cadence[1]), *(uint16_t *)p_params->trigger_dlt_down);
            gx_write16p(&(set_un->sensor_cadence[3]), *(uint16_t *)p_params->trigger_dlt_up);
            set_un->sensor_cadence[5] = p_params->min_interval;
            memcpy(&(set_un->sensor_cadence[6]), p_params->fast_cadence_low, p_params->property_value_length);
            memcpy(&(set_un->sensor_cadence[6 + p_params->property_value_length]), p_params->fast_cadence_high, p_params->property_value_length);
        }
    }

    if (NULL != set_un)
    {
        gx_write16p((void const *) &set_un->property_id, p_params->property_id);
        set_un->sensor_cadence[0] = (p_params->fast_cadence_period_div & 0x7F) | ((p_params->trigger_type & MESH_SENSOR_CADENCE_TRIGGER_PERCENT)  << 7);

#ifdef MESH_MODEL_BQB_TEST
        Err_code = model_send_unicast_dev(p_client, MESH_SENSOR_CADENCE_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)set_un, msg_length);
#else
        message_create(&model_msg_send, p_client->model_lid, MESH_SENSOR_CADENCE_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)set_un, msg_length);
        Err_code = mesh_model_publish(&model_msg_send, NULL);
#endif

        sys_free(set_un);
        set_un = NULL;

        return Err_code;
    }
    else
    {
        return MESH_ERROR_INSUFFICIENT_RESOURCES;
    }
}

uint16_t sensor_settings_client_get(sensor_client_t * p_client, const sensor_settings_get_params_t * p_params)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = MESH_SENSOR_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * MESH_SENSOR_CLIENT_TX_HDL_TOTAL;
    sensor_settings_get_msg_pkt_t get;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_SETTINGS_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            gx_write16p((void const *)&get.property_id, p_params->property_id);

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, MESH_SENSOR_SETTINGS_OPCODE_GET, tx_hdl, (uint8_t *)&get, MESH_SENSOR_SETTINGS_GET_MINLEN);
#else
            message_create(&model_msg_send, p_client->model_lid, MESH_SENSOR_SETTINGS_OPCODE_GET, tx_hdl, (uint8_t *)&get, MESH_SENSOR_SETTINGS_GET_MINLEN);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t sensor_setting_client_get(sensor_client_t * p_client, const sensor_setting_get_params_t * p_params)
{
    sensor_setting_get_msg_pkt_t get;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = MESH_SENSOR_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * MESH_SENSOR_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_SETTING_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            gx_write16p((void const *)&get.property_id, p_params->property_id);
            gx_write16p((void const *)&get.setting_property_id, p_params->setting_property_id);

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, MESH_SENSOR_SETTING_OPCODE_GET, tx_hdl, (uint8_t *)&get, MESH_SENSOR_SETTING_GET_MINLEN);
#else
            message_create(&model_msg_send, p_client->model_lid, MESH_SENSOR_SETTING_OPCODE_GET, tx_hdl, (uint8_t *)&get, MESH_SENSOR_SETTING_GET_MINLEN);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t sensor_setting_client_set(sensor_client_t * p_client, const sensor_setting_set_params_t * p_params)
{
    sensor_setting_set_msg_pkt_t *set = NULL;
    uint16_t msg_length = 0;
    uint16_t Err_code = MESH_ERROR_NO_ERROR;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = MESH_SENSOR_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * MESH_SENSOR_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_SETTING_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            msg_length = MESH_SENSOR_SETTING_SET_MINLEN + p_params->setting_raw_length;
            set = (sensor_setting_set_msg_pkt_t *)sys_malloc(msg_length);
            if (NULL != set)
            {
                gx_write16p((void const *)&set->property_id, p_params->property_id);
                gx_write16p((void const *)&set->setting_property_id, p_params->setting_property_id);
                memcpy(set->setting_raw, p_params->setting_raw, p_params->setting_raw_length);

#ifdef MESH_MODEL_BQB_TEST
                Err_code = model_send_unicast_dev(p_client, MESH_SENSOR_SETTING_OPCODE_SET, tx_hdl, (uint8_t *)set, msg_length);
#else
                message_create(&model_msg_send, p_client->model_lid, MESH_SENSOR_SETTING_OPCODE_SET, tx_hdl, (uint8_t *)set, msg_length);
                Err_code = mesh_model_publish(&model_msg_send, &reliable_info);
#endif
                sys_free(set);
                set = NULL;

                return Err_code;
            }
            else
            {
                return MESH_ERROR_INSUFFICIENT_RESOURCES;
            }
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t sensor_setting_client_set_unack(sensor_client_t * p_client, const sensor_setting_set_params_t * p_params)
{
    sensor_setting_set_msg_pkt_t *set_un = NULL;
    uint16_t msg_length = 0;
    uint16_t Err_code = MESH_ERROR_NO_ERROR;
    uint8_t tx_hdl = MESH_SENSOR_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * MESH_SENSOR_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    msg_length = MESH_SENSOR_SETTING_SET_MINLEN + p_params->setting_raw_length;
    set_un = (sensor_setting_set_msg_pkt_t *)sys_malloc(msg_length);
    if (NULL != set_un)
    {

        gx_write16p((void const *)&set_un->property_id, p_params->property_id);
        gx_write16p((void const *)&set_un->setting_property_id, p_params->setting_property_id);
        memcpy(set_un->setting_raw, p_params->setting_raw, p_params->setting_raw_length);

#ifdef MESH_MODEL_BQB_TEST
        Err_code = model_send_unicast_dev(p_client, MESH_SENSOR_SETTING_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)set_un, msg_length);
#else
        message_create(&model_msg_send, p_client->model_lid, MESH_SENSOR_SETTING_OPCODE_SET_UNACKNOWLEDGED, tx_hdl, (uint8_t *)set_un, msg_length);
        Err_code = mesh_model_publish(&model_msg_send, NULL);
#endif

        sys_free(set_un);
        set_un = NULL;

        return Err_code;
    }
    else
    {
        return MESH_ERROR_INSUFFICIENT_RESOURCES;
    }
}

uint16_t sensor_client_get(sensor_client_t * p_client, const sensor_get_params_t * p_params)
{
    sensor_get_msg_pkt_t get;
    uint16_t msg_length = 0;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = MESH_SENSOR_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * MESH_SENSOR_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

    if (p_client == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            if (p_params != NULL)
            {
                gx_write16p((void const *)&get.property_id, p_params->property_id);
                msg_length += 2;
            }

#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, MESH_SENSOR_OPCODE_GET, tx_hdl, (uint8_t *)&get, msg_length);
#else
            message_create(&model_msg_send, p_client->model_lid, MESH_SENSOR_OPCODE_GET, tx_hdl, (uint8_t *)&get, msg_length);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t sensor_column_client_get(sensor_client_t * p_client, const sensor_column_get_params_t * p_params)
{
    sensor_column_get_msg_pkt_t *get = NULL;
    bool reliable_trans_state = false;
    uint16_t Err_code = MESH_ERROR_NO_ERROR;
    uint8_t tx_hdl = MESH_SENSOR_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * MESH_SENSOR_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_COLUMN_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            get = sys_malloc(sizeof(sensor_column_get_msg_pkt_t) + p_params->raw_x_length);
            if (get != NULL)
            {
                gx_write16p((void const *)&get->property_id, p_params->property_id);
                memcpy(get->raw_x, p_params->raw_x, p_params->raw_x_length);

#ifdef MESH_MODEL_BQB_TEST
                Err_code = model_send_unicast_dev(p_client, MESH_SENSOR_COLUMN_OPCODE_GET, tx_hdl, (uint8_t *)get, p_params->raw_x_length + 2);
#else
                message_create(&model_msg_send, p_client->model_lid, MESH_SENSOR_COLUMN_OPCODE_GET, tx_hdl, (uint8_t *)get, p_params->raw_x_length + 2);
                Err_code = mesh_model_publish(&model_msg_send, &reliable_info);
#endif

                sys_free(get);
                get = NULL;
                return Err_code;
            }
            return MESH_ERROR_INSUFFICIENT_RESOURCES;
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t sensor_series_client_get(sensor_client_t * p_client, const sensor_series_get_params_t * p_params)
{
    sensor_series_get_msg_pkt_t *get = NULL;
    bool reliable_trans_state = false;
    uint16_t Err_code = MESH_ERROR_NO_ERROR;
    uint8_t tx_hdl = MESH_SENSOR_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * MESH_SENSOR_CLIENT_TX_HDL_TOTAL;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_send_info_t model_msg_send;
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(MESH_SENSOR_SERIES_OPCODE_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            get = sys_malloc(sizeof(sensor_series_get_msg_pkt_t) + p_params->series_x_length * 2);
            if (get != NULL)
            {
                gx_write16p((void const *)&get->property_id, p_params->property_id);
                memcpy(get->series_x, p_params->series_x1, p_params->series_x_length);
                memcpy(get->series_x + p_params->series_x_length, p_params->series_x2, p_params->series_x_length);

#ifdef MESH_MODEL_BQB_TEST
                Err_code = model_send_unicast_dev(p_client, MESH_SENSOR_SERIES_OPCODE_GET, tx_hdl, (uint8_t *)get, p_params->series_x_length * 2 + 2);
#else
                message_create(&model_msg_send, p_client->model_lid, MESH_SENSOR_SERIES_OPCODE_GET, tx_hdl, (uint8_t *)get, p_params->series_x_length * 2 + 2);
                Err_code = mesh_model_publish(&model_msg_send, &reliable_info);
#endif

                sys_free(get);
                get = NULL;
                return Err_code;
            }
            return MESH_ERROR_INSUFFICIENT_RESOURCES;
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t sensor_client_setget_cancel(sensor_client_t * p_client)
{
    if (p_client == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    
    return mesh_model_reliable_trans_cancel(p_client->model_lid);
}

