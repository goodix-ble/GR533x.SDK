/**
 ****************************************************************************************
 *
 * @file led_matrix_server.c
 *
 * @brief Led Matrix Server Model.
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
 
#include "led_matrix_server.h"
#include "matrix_gui.h"
#include "matrix_panel.h"
#include <string.h>

extern uint8_t server_num;

static const uint16_t led_matrix_server_opcode_list[] =
{
    LED_MATRIX_OPCODE_PIC_SET,
    LED_MATRIX_OPCODE_BAC_SET,
};

static void handle_pic_set_cb(mesh_model_send_info_t *p_rsp_info);
static void handle_bac_set_cb(mesh_model_send_info_t *p_rsp_info);
static void handle_cpic_set_cb(mesh_model_send_info_t *p_rsp_info);
static void handle_fpic_set_cb(mesh_model_send_info_t *p_rsp_info);


static const access_opcode_handler_t m_opcode_handlers[] =
{
    {LED_MATRIX_OPCODE_PIC_SET,               handle_pic_set_cb               },
    {LED_MATRIX_OPCODE_BAC_SET,               handle_bac_set_cb               },
    {LED_MATRIX_OPCODE_CPIC_SET,              handle_cpic_set_cb              },
    {LED_MATRIX_OPCODE_FPIC_SET,              handle_fpic_set_cb              },
    {LED_MATRIX_OPCODE_STATUS ,               NULL                            },
};

static void mesh_msg_model_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void mesh_msg_model_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);
static void mesh_msg_model_publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args);

static const mesh_model_cb_t mesh_model_msg_cb = {
    .cb_rx             = mesh_msg_model_rx_cb,
    .cb_sent           = mesh_msg_model_sent_cb,
    .cb_publish_period = mesh_msg_model_publish_period_cb,
};

/*****************************************************************************
 * led matrix server model info
 *****************************************************************************/
 
static lm_model_info_t led_matrix_server = 
{
    .register_info = 
    {
        MESH_MODEL_VENDOR(LED_MATRIX_SERVER_MODEL_ID, LED_MATRIX_COMPANY_ID),
        1,
        1,
        (uint16_t *)led_matrix_server_opcode_list,
        sizeof(led_matrix_server_opcode_list) / sizeof(uint16_t),
        &mesh_model_msg_cb,
        NULL,
    },
    .model_lid = MESH_INVALID_LOCAL_ID,
};

/*****************************************************************************
 * led matrix server model register
 *****************************************************************************/

/**@brief Register led matrix server model, obtain the information of registered model.
 *
 * @return Result of register.
 */ 
uint16_t led_matrix_server_init(void)
{
     return mesh_model_register(&led_matrix_server.register_info, &led_matrix_server.model_lid);
}

/*****************************************************************************
 * led matrix server model opcode handler callbacks
 *****************************************************************************/
static void handle_pic_set_cb(mesh_model_send_info_t *p_rsp_info)
{
    if (p_rsp_info->data_send_len == sizeof(led_matrix_pic_msg_t))
    {
        APP_PRINTF("Received PIC Set Msg\n");
        if (memcmp(&led_matrix_server.lm_pic_msg.msg[0], &p_rsp_info->p_data_send[0], LED_MATRIX_PIC_MSG_LEN))
        {
            memcpy(&led_matrix_server.lm_pic_msg.msg[0], &p_rsp_info->p_data_send[0], LED_MATRIX_PIC_MSG_LEN);
            Matrix_Gui_fillScreen(hal_matrix_panel_color333(0, 0, 0));
            uint16_t color;
            memcpy((uint8_t *)&color, &led_matrix_server.lm_bac_msg.msg[0], 2);
            Matrix_Gui_draw8X8RGBbitmap(&led_matrix_server.lm_pic_msg.msg[0], color);
        }

        led_matrix_server.lm_rsp_msg.msg[0] = server_num;
        led_matrix_server.lm_rsp_msg.msg[1] = LED_MATRIX_OPCODE_PIC_SET;

        p_rsp_info->p_data_send = (uint8_t*)&led_matrix_server.lm_rsp_msg;
        p_rsp_info->data_send_len = sizeof(led_matrix_rsp_msg_t);
        p_rsp_info->trans_mic_64 = false;
        p_rsp_info->opcode.company_opcode = LED_MATRIX_OPCODE_STATUS;

        p_rsp_info->tx_hdl = LED_MATRIX_OPCODE_PIC_SET;

        if (MESH_ERROR_NO_ERROR == mesh_model_rsp_send(p_rsp_info))
        //if (MESH_ERROR_NO_ERROR == mesh_model_publish(p_rsp_info))
        {
            //APP_PRINTF("Ready to response state!!!\r\n");
        }
        else
        {
            //APP_PRINTF("Not Ready to response state!!!\r\n");
        }
    }
}

static void handle_bac_set_cb(mesh_model_send_info_t *p_rsp_info)
{
    if (p_rsp_info->data_send_len == sizeof(led_matrix_bac_msg_t))
    {
        APP_PRINTF("Received BAC Set Msg\n");
        if (memcmp(&led_matrix_server.lm_bac_msg.msg[0], &p_rsp_info->p_data_send[0], LED_MATRIX_BAC_MSG_LEN))
        {
            memcpy(&led_matrix_server.lm_bac_msg.msg[0], &p_rsp_info->p_data_send[0], LED_MATRIX_BAC_MSG_LEN);
            Matrix_Gui_fillScreen(hal_matrix_panel_color333(0, 0, 0));
            uint16_t color;
            memcpy((uint8_t *)&color, &led_matrix_server.lm_bac_msg.msg[0], 2);
            Matrix_Gui_draw8X8RGBbitmap(&led_matrix_server.lm_pic_msg.msg[0], color);
        }

        led_matrix_server.lm_rsp_msg.msg[0] = server_num;
        led_matrix_server.lm_rsp_msg.msg[1] = LED_MATRIX_OPCODE_BAC_SET;

        p_rsp_info->p_data_send = (uint8_t*)&led_matrix_server.lm_rsp_msg;
        p_rsp_info->data_send_len = sizeof(led_matrix_rsp_msg_t);
        p_rsp_info->trans_mic_64 = false;
        p_rsp_info->opcode.company_opcode = LED_MATRIX_OPCODE_STATUS;

        p_rsp_info->tx_hdl = LED_MATRIX_OPCODE_BAC_SET;

        if (MESH_ERROR_NO_ERROR == mesh_model_rsp_send(p_rsp_info))
        {
            //APP_PRINTF("Ready to response state!!!\r\n");
        }
        else
        {
            //APP_PRINTF("Not Ready to response state!!!\r\n");
        }
    }
}
static void handle_cpic_set_cb(mesh_model_send_info_t *p_rsp_info)
{
    if (p_rsp_info->data_send_len <= sizeof(led_matrix_cpic_msg_t))
    {
        uint8_t cpic_msg_len = 8;
        uint8_t i, j;
        for(i = 0; i < 8; i++)
        {
            for (j = 0; j < 8; j++)
            {
                if (p_rsp_info->p_data_send[i] >> j)
                    cpic_msg_len += 2;
            }
        }
        APP_PRINTF("Received CPIC Set Msg\n");
        if (memcmp(&led_matrix_server.lm_cpic_msg.msg[0], &p_rsp_info->p_data_send[0], cpic_msg_len))
        {
            memcpy(&led_matrix_server.lm_cpic_msg.msg[0], &p_rsp_info->p_data_send[0], cpic_msg_len);
            Matrix_Gui_fillScreen(hal_matrix_panel_color333(0, 0, 0));

            //Matrix_Gui_draw8X8FRGBbitmap(&led_matrix_server.lm_cpic_msg.msg[0], (uint16_t *)&led_matrix_server.lm_cpic_msg.msg[8]);
        }

        led_matrix_server.lm_rsp_msg.msg[0] = server_num;
        led_matrix_server.lm_rsp_msg.msg[1] = LED_MATRIX_OPCODE_CPIC_SET;

        p_rsp_info->p_data_send = (uint8_t*)&led_matrix_server.lm_rsp_msg;
        p_rsp_info->data_send_len = sizeof(led_matrix_rsp_msg_t);
        p_rsp_info->trans_mic_64 = false;
        p_rsp_info->opcode.company_opcode = LED_MATRIX_OPCODE_STATUS;

        p_rsp_info->tx_hdl = LED_MATRIX_OPCODE_CPIC_SET;

        if (MESH_ERROR_NO_ERROR == mesh_model_rsp_send(p_rsp_info))
        //if (MESH_ERROR_NO_ERROR == mesh_model_publish(p_rsp_info))
        {
            //APP_PRINTF("Ready to response state!!!\r\n");
        }
        else
        {
            //APP_PRINTF("Not Ready to response state!!!\r\n");
        }
    }
}
static void handle_fpic_set_cb(mesh_model_send_info_t *p_rsp_info)
{
    if (p_rsp_info->data_send_len == sizeof(led_matrix_fpic_msg_t))
    {
        APP_PRINTF("Received FPIC Set Msg\n");
        if (memcmp(&led_matrix_server.lm_fpic_msg.msg[0], &p_rsp_info->p_data_send[0], LED_MATRIX_FPIC_MSG_LEN))
        {
            memcpy(&led_matrix_server.lm_fpic_msg.msg[0], &p_rsp_info->p_data_send[0], LED_MATRIX_FPIC_MSG_LEN);
            Matrix_Gui_fillScreen(hal_matrix_panel_color333(0, 0, 0));
            uint16_t color;
            memcpy((uint8_t *)&color, &led_matrix_server.lm_bac_msg.msg[0], 2);
            //Matrix_Gui_draw32X32RGBbitmap(&led_matrix_server.lm_fpic_msg.msg[0], color);
        }

        led_matrix_server.lm_rsp_msg.msg[0] = server_num;
        led_matrix_server.lm_rsp_msg.msg[1] = LED_MATRIX_OPCODE_FPIC_SET;

        p_rsp_info->p_data_send = (uint8_t*)&led_matrix_server.lm_rsp_msg;
        p_rsp_info->data_send_len = sizeof(led_matrix_rsp_msg_t);
        p_rsp_info->trans_mic_64 = false;
        p_rsp_info->opcode.company_opcode = LED_MATRIX_OPCODE_STATUS;

        p_rsp_info->tx_hdl = LED_MATRIX_OPCODE_FPIC_SET;

        if (MESH_ERROR_NO_ERROR == mesh_model_rsp_send(p_rsp_info))
        //if (MESH_ERROR_NO_ERROR == mesh_model_publish(p_rsp_info))
        {
            //APP_PRINTF("Ready to response state!!!\r\n");
        }
        else
        {
            //APP_PRINTF("Not Ready to response state!!!\r\n");
        }
    }
}

/*****************************************************************************
 * led matrix server model handler callbacks
 *****************************************************************************/
static void mesh_msg_model_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{
    mesh_model_send_info_t rsp_info =
    {
        .model_lid = led_matrix_server.model_lid,
        .p_data_send = &p_model_msg->msg[0],
        .data_send_len = p_model_msg->msg_len,
        .app_key_lid = p_model_msg->app_key_lid,
        .dst = p_model_msg->src,
    };

    rsp_info.opcode.company_id = p_model_msg->opcode.company_id;
    uint8_t company_opcode = p_model_msg->opcode.company_opcode;
    access_opcode_handler_cb_t handler = m_opcode_handlers[company_opcode - OPCODE_FIRST].handler;

    if (NULL != handler)
    {
        handler(&rsp_info);
    }
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

