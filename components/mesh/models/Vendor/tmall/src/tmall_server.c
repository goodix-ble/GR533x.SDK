/**
 ****************************************************************************************
 *
 * @file tmall_server.c
 *
 * @brief Tmall Server Model.
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
 
#include "tmall_server.h"
#include <string.h>

static const uint16_t tmall_server_opcode_list[] =
{
    TMALL_OPCODE_ATTR_GET,
    TMALL_OPCODE_ATTR_SET,
    TMALL_OPCODE_ATTR_SET_UNACK,
    TMALL_OPCODE_ATTR_STATUS,
    TMALL_OPCODE_ATTR_INDICATION,
    TMALL_OPCODE_ATTR_CONFIRMATION,
    TMALL_OPCODE_TRANSPARENT,
};

static void handle_cb(mesh_model_send_info_t *p_rsp_info);
static void mesh_msg_model_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void mesh_msg_model_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);
static void mesh_msg_model_publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args);

static const mesh_model_cb_t mesh_model_msg_cb = {
    .cb_rx             = mesh_msg_model_rx_cb,
    .cb_sent           = mesh_msg_model_sent_cb,
    .cb_publish_period = mesh_msg_model_publish_period_cb,
};

/*****************************************************************************
 * tmall server model info
 *****************************************************************************/
 
static tmall_model_info_t tmall_server = 
{
    .register_info = 
    {
        MESH_MODEL_VENDOR(TMALL_SERVER_MODEL_ID, TMALL_COMPANY_ID),
        0,
        1,
        (uint16_t *)tmall_server_opcode_list,
        sizeof(tmall_server_opcode_list) / sizeof(uint16_t),
        &mesh_model_msg_cb,
        NULL,
    },
    .model_lid = MESH_INVALID_LOCAL_ID,
};

static uint8_t global_tid = 0;

/*****************************************************************************
* tmall server model fan init
*****************************************************************************/
static void attr_msg_init(tmall_attr_ind_t* p_attr, uint16_t attr_type, uint16_t param_len)
{
    p_attr->attr_type = attr_type;
    p_attr->attr_param_len = param_len;
}
static void tmall_server_fan_init(void)
{
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[0], 0x010A, 1);      // wind_speed
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[1], 0x010E, 2);      // humidity
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[2], 0x0521, 1);      // direction
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[3], 0x050D, 1);      // screen_display
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[4], 0x010E, 2);      // target_humidity
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[5], 0x0119, 2);      // vertical_angle
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[6], 0x011A, 2);      // horizontal_angle
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[7], 0x0500, 1);      // horizontal_rotate
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[8], 0x0501, 1);      // vertical_rotate
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[9], 0x0505, 1);      // Negative_ions
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[10], 0x050C, 1);     // child_lock
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[11], 0x0537, 1);     // clean
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[12], 0x0539, 1);     // hot_wind
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[13], 0x0523, 1);     // person_sense
    attr_msg_init(&tmall_server.tmall_fan.fan_attr[14], 0xF009, 1);     // failure_report
}


/*****************************************************************************
 * tmall server model register
 *****************************************************************************/
uint16_t tmall_server_init(void)
{
    tmall_server_fan_init();
    return mesh_model_register(&tmall_server.register_info, &tmall_server.model_lid);
}

/*****************************************************************************
 * led matrix server model opcode handler callbacks
 *****************************************************************************/
static uint8_t attr_msg_get(uint16_t attr_type, uint16_t* p_attr_len)
{
    uint8_t index = 0xFF;
    for (int i = 0; i < 15; i++)
    {
        if (attr_type == tmall_server.tmall_fan.fan_attr[i].attr_type)
        {
            p_attr_len[0] = tmall_server.tmall_fan.fan_attr[i].attr_param_len;
            index = i;
            break;
        }
    }
    return index;
}

static uint8_t tx_hdl_get()
{
    return 0;
}

static uint16_t attr_type_reverse_get(uint8_t* p_data)
{
    return ((uint16_t)p_data[1] << 8) | (uint16_t)p_data[0];
}

static void handle_cb(mesh_model_send_info_t *p_rsp_info)
{
    uint16_t opcode = p_rsp_info->opcode.company_opcode;
    int data_in_len = p_rsp_info->data_send_len - 1;
    uint16_t data_out_len = 1;
    uint16_t attr_type;
    uint16_t attr_len;
    uint8_t index;
    uint8_t* p_data_in = &p_rsp_info->p_data_send[1];
    uint8_t* p_data_out = malloc(60);
    uint8_t* p_data_temp = p_data_out;
    p_data_temp[0] = global_tid++;
    p_data_temp++;

    switch (opcode)
    {
        case TMALL_OPCODE_ATTR_GET:
        {
            while (data_in_len > 0)
            {
                attr_type = attr_type_reverse_get(p_data_in);
                index = attr_msg_get(attr_type, &attr_len);
                if (0xFF != index)
                {
                    memcpy(p_data_temp, p_data_in, 2);
                    data_in_len -= 2;
                    p_data_in += 2;
                    data_out_len += 2;
                    p_data_temp += 2;

                    memcpy(p_data_temp, &tmall_server.tmall_fan.fan_attr[index].attr_param[0], attr_len);
                    data_out_len += attr_len;
                    p_data_temp += attr_len;
                }
            }
            p_rsp_info->p_data_send = p_data_out;
            p_rsp_info->data_send_len = data_out_len;
            p_rsp_info->trans_mic_64 = false;
            p_rsp_info->opcode.company_opcode = TMALL_OPCODE_ATTR_STATUS;
            p_rsp_info->tx_hdl = TMALL_OPCODE_ATTR_GET;

            if (MESH_ERROR_NO_ERROR == mesh_model_rsp_send(p_rsp_info))
            {
                APP_PRINTF("Ready to response state!!!\r\n");
            }
            else
            {
                APP_PRINTF("Not Ready to response state!!!\r\n");
            }
            break;
        }
        case TMALL_OPCODE_ATTR_SET:
        {
            while (data_in_len > 0)
            {
                attr_type = attr_type_reverse_get(p_data_in);
                index = attr_msg_get(attr_type, &attr_len);
                if (0xFF != index)
                {
                    memcpy(p_data_temp, p_data_in, 2);
                    data_in_len -= 2;
                    p_data_in += 2;
                    data_out_len += 2;
                    p_data_temp += 2;

                    memcpy(&tmall_server.tmall_fan.fan_attr[index].attr_param[0], p_data_in, attr_len);
                    data_in_len -= attr_len;
                    p_data_in += attr_len;

                    memcpy(p_data_temp, &tmall_server.tmall_fan.fan_attr[index].attr_param[0], attr_len);
                    data_out_len += attr_len;
                    p_data_temp += attr_len;
                }

            }
            p_rsp_info->p_data_send = p_data_out;
            p_rsp_info->data_send_len = data_out_len;
            p_rsp_info->trans_mic_64 = false;
            p_rsp_info->opcode.company_opcode = TMALL_OPCODE_ATTR_STATUS;
            p_rsp_info->tx_hdl = TMALL_OPCODE_ATTR_SET;

            if (MESH_ERROR_NO_ERROR == mesh_model_rsp_send(p_rsp_info))
            {
                APP_PRINTF("Ready to response state!!!\r\n");
            }
            else
            {
                APP_PRINTF("Not Ready to response state!!!\r\n");
            }

            p_rsp_info->tx_hdl = TMALL_OPCODE_ATTR_SET + 1;
            if (MESH_ERROR_NO_ERROR == mesh_model_publish(p_rsp_info, NULL))
            {
                APP_PRINTF("Ready to publish state!!!\r\n");
            }
            else
            {
                APP_PRINTF("Not Ready to publish state!!!\r\n");
            }
            break;
        }
        case TMALL_OPCODE_ATTR_SET_UNACK:
        {
            while (data_in_len > 0)
            {
                attr_type = attr_type_reverse_get(p_data_in);
                index = attr_msg_get(attr_type, &attr_len);
                if (0xFF != index)
                {
                    memcpy(p_data_temp, p_data_in, 2);
                    data_in_len -= 2;
                    p_data_in += 2;
                    data_out_len += 2;
                    p_data_temp += 2;

                    memcpy(&tmall_server.tmall_fan.fan_attr[index].attr_param[0], p_data_in, attr_len);
                    data_in_len -= attr_len;
                    p_data_in += attr_len;

                    memcpy(p_data_temp, &tmall_server.tmall_fan.fan_attr[index].attr_param[0], attr_len);
                    data_out_len += attr_len;
                    p_data_temp += attr_len;
                }
            }
            p_rsp_info->p_data_send = p_data_out;
            p_rsp_info->data_send_len = data_out_len;
            p_rsp_info->trans_mic_64 = false;
            p_rsp_info->opcode.company_opcode = TMALL_OPCODE_ATTR_STATUS;
            p_rsp_info->tx_hdl = TMALL_OPCODE_ATTR_SET_UNACK;

            if (MESH_ERROR_NO_ERROR == mesh_model_publish(p_rsp_info, NULL))
            {
                APP_PRINTF("Ready to publish state!!!\r\n");
            }
            else
            {
                APP_PRINTF("Not Ready to publish state!!!\r\n");
            }
            break;
        }
        case TMALL_OPCODE_ATTR_INDICATION:
        {
            break;
        }
        case TMALL_OPCODE_ATTR_CONFIRMATION:
        {
            break;
        }
        case TMALL_OPCODE_TRANSPARENT:
        {
            break;
        }
        default:
            break;
    }
    free(p_data_out);
}

/*****************************************************************************
 * led matrix server model handler callbacks
 *****************************************************************************/
static void mesh_msg_model_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{
    mesh_model_send_info_t rsp_info =
    {
        .model_lid = tmall_server.model_lid,
        .p_data_send = &p_model_msg->msg[0],
        .data_send_len = p_model_msg->msg_len,
        .app_key_lid = p_model_msg->app_key_lid,
        .dst = p_model_msg->src,
    };
    rsp_info.opcode.company_id = p_model_msg->opcode.company_id;
    rsp_info.opcode.company_opcode = p_model_msg->opcode.company_opcode;

    handle_cb(&rsp_info);
}


static void mesh_msg_model_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    /*switch(p_sent->tx_hdl)
    {
        case LED_MATRIX_OPCODE_PIC_SET:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_PRINTF("Responsed picture message!!!\r\n")
                                                  : APP_PRINTF("Failed to responsed picture message, status = %x!!!\r\n", p_sent->status);
            break;
        case LED_MATRIX_OPCODE_BAC_SET:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_PRINTF("Responsed brightness and chromaticity message!!!\r\n")
                                                  : APP_PRINTF("Failed to responsed brightness and chromaticity message, status = %x!!!\r\n", p_sent->status);
            break;
        case LED_MATRIX_OPCODE_CPIC_SET:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_PRINTF("Responsed color picture message!!!\r\n")
                                                  : APP_PRINTF("Failed to responsed color picture message, status = %x!!!\r\n", p_sent->status);
            break;
        case LED_MATRIX_OPCODE_FPIC_SET:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_PRINTF("Responsed full picture message!!!\r\n")
                                                  : APP_PRINTF("Failed to responsed full picture message, status = %x!!!\r\n", p_sent->status);
            break;
        default:
            APP_PRINTF("Never here!!!\r\n");
            break;
    }*/
}

static void mesh_msg_model_publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args)
{
    
}

