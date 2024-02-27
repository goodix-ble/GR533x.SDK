/**
 ****************************************************************************************
 *
 * @file led_matrix_client.c
 *
 * @brief Led Matrix Client Model.
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
#include "led_matrix_client.h"
#include <string.h>

static const uint16_t led_matrix_client_opcode_list[] =
{
    LED_MATRIX_OPCODE_STATUS,
};

static void handle_status_cb(mesh_model_send_info_t *p_rsp_info);

static const access_opcode_handler_t m_opcode_handlers[] =
{
    {LED_MATRIX_OPCODE_PIC_SET,          NULL            },
    {LED_MATRIX_OPCODE_BAC_SET,          NULL            },
    {LED_MATRIX_OPCODE_STATUS,           handle_status_cb},
};

static void mesh_msg_model_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void mesh_msg_model_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args);
static void mesh_msg_model_publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args);

static const mesh_model_cb_t mesh_model_msg_cb = {
    .cb_rx             = mesh_msg_model_rx_cb,
    .cb_sent           = mesh_msg_model_sent_cb,
    .cb_publish_period = mesh_msg_model_publish_period_cb,
};

uint16_t server_bit_map = 0;
uint16_t server_bit_map2 = 0;

static uint8_t lm_timer_id = 0xFF;
//static uint8_t re_tx_count = 0;
// avoid re_tx msg from mesh lib to cause bit_map chaos
static bool rx_flag = false;

static bool seg_flag = false;
static bool need_seg = false;

static bool trans_active[LED_MATRIX_CLIENT_COUNT];

lm_model_info_t led_matrix_client[LED_MATRIX_CLIENT_COUNT];
lm_model_info_t led_matrix_client_temp[LED_MATRIX_CLIENT_COUNT];

/*****************************************************************************
 * led matrix client model register
 *****************************************************************************/
/**@brief Register led matrix client model, obtain the information of registered model.
 *
 * @return Result of register.
 */
uint16_t led_matrix_client_init(void)
{
    uint16_t status = MESH_ERROR_NO_ERROR;

    for (uint8_t i = 0; i < LED_MATRIX_CLIENT_COUNT; i++)
    {
        trans_active[i] = false;
        led_matrix_client[i].register_info.model_id.company_id = LED_MATRIX_COMPANY_ID;
        led_matrix_client[i].register_info.model_id.company_model_id = LED_MATRIX_CLIENT_MODEL_ID;
        led_matrix_client[i].register_info.element_offset = i + 1;
        led_matrix_client[i].register_info.publish = 1;
        led_matrix_client[i].register_info.p_opcodes = (uint16_t *)led_matrix_client_opcode_list;
        led_matrix_client[i].register_info.num_opcodes = sizeof(led_matrix_client_opcode_list) / sizeof(uint16_t);
        led_matrix_client[i].register_info.p_cb = &mesh_model_msg_cb;
        led_matrix_client[i].register_info.p_args = NULL,
        led_matrix_client[i].model_lid = MESH_INVALID_LOCAL_ID;
        memset(&led_matrix_client[i].lm_pic_msg.msg[0], 0xFF, LED_MATRIX_PIC_MSG_LEN);
        memset(&led_matrix_client[i].lm_bac_msg.msg[0], 0xFF, LED_MATRIX_BAC_MSG_LEN);

        status = mesh_model_register(&led_matrix_client[i].register_info, &led_matrix_client[i].model_lid);
        if (MESH_ERROR_NO_ERROR != status)
        {
            return status;
        }
    }

    return status;
}

/*****************************************************************************
 * led matrix client model opcode handler callbacks
 *****************************************************************************/

static void handle_status_cb(mesh_model_send_info_t *p_rsp_info)
{
    if (p_rsp_info->data_send_len == sizeof(led_matrix_rsp_msg_t))
    {
        // get index
        uint8_t index = p_rsp_info->p_data_send[0];

        if (memcmp(&led_matrix_client[index].lm_rsp_msg.msg[0], &p_rsp_info->p_data_send[0], LED_MATRIX_RSP_MSG_LEN))
        {
            memcpy(&led_matrix_client[index].lm_rsp_msg.msg[0], &p_rsp_info->p_data_send[0], LED_MATRIX_RSP_MSG_LEN);
        }

        /*switch (p_rsp_info->p_data_send[1])
        {
            case LED_MATRIX_OPCODE_PIC_SET:
                APP_PRINTF("[client[%d]]:Server has received the picture set message!!!\r\n", index);
                break;
            case LED_MATRIX_OPCODE_BAC_SET:
                APP_PRINTF("[client[%d]]:Server has received the brightness and chromaticity set message!!!\r\n", index);
                break;
            default:
                break;
        }*/
    }
}


/*****************************************************************************
 * led matrix client model handler callbacks
 *****************************************************************************/

static void led_matrix_rx_timeout(uint8_t timer_id)
{
    rx_flag = false;
    server_bit_map = 0;
    server_bit_map2 = 0;
    need_seg = false;
    seg_flag = false;
    mesh_timer_clear(lm_timer_id);
    lm_timer_id = 0xFF;
    memset(trans_active, 0, LED_MATRIX_CLIENT_COUNT);
}

static void led_matrix_rx_check()
{
    printf("retransport, current bit: %04X\n", server_bit_map);
    uint16_t bit_map_temp = server_bit_map;
    server_bit_map2 = bit_map_temp;
    int i;

    if (bit_map_temp == 0)
    {
        printf("received all\n\n\n");
        led_matrix_rx_timeout(lm_timer_id);
    }
    else

    {
        for (i = 0; i < LED_MATRIX_CLIENT_COUNT; i++)
        {
            if ((bit_map_temp >> i) & 0x01)
            {
                led_matrix_client_msg_send(i, led_matrix_client[i].current_msg);
            }
        }
    }

}
static void mesh_msg_model_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{

//    printf("received rsp\n");
    mesh_model_send_info_t rsp_info =
    {
        .model_lid = p_model_msg->model_lid,
        .p_data_send = &p_model_msg->msg[0],
        .data_send_len = p_model_msg->msg_len,
        .app_key_lid = p_model_msg->app_key_lid,
        .dst = p_model_msg->src,
    };

    uint8_t company_opcode = p_model_msg->opcode.company_opcode;
    access_opcode_handler_cb_t handler = m_opcode_handlers[company_opcode - OPCODE_FIRST].handler;

    if (NULL != handler)
    {
        handler(&rsp_info);
    }

    if (rx_flag)
    {
//        server_bit_map &= ~(1 << (p_model_msg->msg[0]));
        uint8_t index = p_model_msg->msg[0];
        server_bit_map &= ~(1 << index);
        printf("update bit map: %04X\n", server_bit_map);
        switch (led_matrix_client[index].current_msg)
        {
            case LED_MATRIX_OPCODE_PIC_SET:
                if (memcmp(&led_matrix_client[index].lm_pic_msg.msg[0], &led_matrix_client_temp[index].lm_pic_msg.msg[0], 8))
                {
                    memcpy(&led_matrix_client[index].lm_pic_msg.msg[0], &led_matrix_client_temp[index].lm_pic_msg.msg[0], 8);
                }
                break;
            case LED_MATRIX_OPCODE_BAC_SET:
                if (memcmp(&led_matrix_client[index].lm_bac_msg.msg[0], &led_matrix_client_temp[index].lm_bac_msg.msg[0], 2))
                {
                    memcpy(&led_matrix_client[index].lm_bac_msg.msg[0], &led_matrix_client_temp[index].lm_bac_msg.msg[0], 2);
                }
                break;
            case LED_MATRIX_OPCODE_CPIC_SET:
                if (memcmp(&led_matrix_client[index].lm_cpic_msg.msg[0], &led_matrix_client_temp[index].lm_cpic_msg.msg[0], 136))
                {
                    memcpy(&led_matrix_client[index].lm_cpic_msg.msg[0], &led_matrix_client_temp[index].lm_cpic_msg.msg[0], 136);
                }
                break;
            case LED_MATRIX_OPCODE_FPIC_SET:
                if (memcmp(&led_matrix_client[index].lm_fpic_msg.msg[0], &led_matrix_client_temp[index].lm_fpic_msg.msg[0], 128))
                {
                    memcpy(&led_matrix_client[index].lm_fpic_msg.msg[0], &led_matrix_client_temp[index].lm_fpic_msg.msg[0], 128);
                }
                break;
            default:
                break;
        }
    }
}


static void mesh_msg_model_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args)
{
    uint8_t model_lid_base = led_matrix_client[0].model_lid;
    uint8_t index = p_sent->model_lid - model_lid_base;
    seg_flag = false;
    trans_active[index] = false;
    /*switch (p_sent->tx_hdl)
    {
        case LED_MATRIX_OPCODE_PIC_SET:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_PRINTF("[client[%d]]:Sent picture set message!!!\r\n", index)
                                                  : APP_PRINTF("[client[%d]]:Failed to send picture set message, status = %x!!!\r\n", index, p_sent->status);
            break;
        case LED_MATRIX_OPCODE_BAC_SET:
            (MESH_ERROR_NO_ERROR == p_sent->status) ? APP_PRINTF("[client[%d]]:Sent brightness and chromaticity set message!!!\r\n", index)
                                                  : APP_PRINTF("[client[%d]]:Failed to send brightness and chromaticity set message, status = %x!!!\r\n", index, p_sent->status);
            break;
        default:
            APP_PRINTF("Never here!!!\r\n");
            break;
    }*/
    if (rx_flag)
    {
        server_bit_map2 &= ~(1 << index);
        if (server_bit_map2 == 0)
        {
            led_matrix_rx_check();
        }
    }
}

static void mesh_msg_model_publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args)
{

}

/*****************************************************************************
 * Send message
 *****************************************************************************/
void led_matrix_client_msg_send(uint8_t index, uint16_t opcode)
{
    if (trans_active[index])
        return;

    //printf("Send msg, server num: %d\n", index);

    uint8_t tx_hdl = opcode;

    mesh_model_send_info_t model_msg_send;

    // fill publish data
    model_msg_send.model_lid             = led_matrix_client[index].model_lid;
    model_msg_send.opcode.company_opcode = opcode;
    model_msg_send.opcode.company_id     = LED_MATRIX_COMPANY_ID;
    model_msg_send.tx_hdl                = tx_hdl;
    model_msg_send.trans_mic_64          = false;
    switch (opcode)
    {
        case LED_MATRIX_OPCODE_PIC_SET:
        {
            model_msg_send.p_data_send = (uint8_t *)malloc(sizeof(led_matrix_pic_msg_t));
            model_msg_send.data_send_len = sizeof(led_matrix_pic_msg_t);
            memcpy(&model_msg_send.p_data_send[0], &led_matrix_client_temp[index].lm_pic_msg.msg[0], sizeof(led_matrix_pic_msg_t));
            break;
        }
        case LED_MATRIX_OPCODE_BAC_SET:
        {
            model_msg_send.p_data_send = (uint8_t *)malloc(sizeof(led_matrix_bac_msg_t));
            model_msg_send.data_send_len = sizeof(led_matrix_bac_msg_t);
            memcpy(&model_msg_send.p_data_send[0], &led_matrix_client_temp[index].lm_bac_msg.msg[0], sizeof(led_matrix_bac_msg_t));
            break;
        }
        case LED_MATRIX_OPCODE_CPIC_SET:
        {
            uint8_t cpic_msg_len = 8;
            uint8_t i, j;
            for(i = 0; i < 8; i++)
            {
                for (j = 0; j < 8; j++)
                {
                    if (led_matrix_client[index].lm_cpic_msg.msg[i] >> j)
                        cpic_msg_len += 2;
                }
            }
            model_msg_send.p_data_send = (uint8_t *)malloc(cpic_msg_len);
            model_msg_send.data_send_len = cpic_msg_len;
            memcpy(&model_msg_send.p_data_send[0], &led_matrix_client_temp[index].lm_cpic_msg.msg[0], cpic_msg_len);
            break;
        }
        case LED_MATRIX_OPCODE_FPIC_SET:
        {
            model_msg_send.p_data_send = (uint8_t *)malloc(sizeof(led_matrix_fpic_msg_t));
            model_msg_send.data_send_len = sizeof(led_matrix_fpic_msg_t);
            memcpy(&model_msg_send.p_data_send[0], &led_matrix_client_temp[index].lm_fpic_msg.msg[0], sizeof(led_matrix_fpic_msg_t));
            break;
        }
        default:
            printf("Error opcode\n");
            return;
    }

    /*printf("send msg, data:0x");
    for (int i = 0; i < model_msg_send.data_send_len; i++)
        printf("%02X ", model_msg_send.p_data_send[i]);
    printf("\n");*/

    if (!need_seg)
    {
        uint16_t status = mesh_model_publish(&model_msg_send, NULL);
        if (MESH_ERROR_NO_ERROR == status)
        {
            trans_active[index] = true;
            //APP_PRINTF("Ready to publish message!!!\r\n");
        } 
        else
        {
            //APP_PRINTF("Not ready to publish message, status: %X!!!!\r\n", status);
        }
    }
    else
    {
        //led_matrix_seg_msg_send(&model_msg_send);
        if (!seg_flag && index == 12)
        {
            printf("publish msg\n");
            printf("msg_len: %d\n", model_msg_send.data_send_len);
            mesh_model_publish(&model_msg_send, NULL);
            seg_flag = true;
            rx_flag = false;
        }
    }

    free(model_msg_send.p_data_send);
}
static uint8_t press_test_flag = 0;
static uint8_t press_test_data[2200];

void led_matrix_client_msg_all_send(uint8_t opcode)
{
    if (opcode == 0xFF) // press_test
    {
        if ((press_test_flag++) % 7)
        {
            memset(&press_test_data[0], press_test_flag, 129);
            press_test_data[0] = 0x01;
            led_matrix_client_serverice_send(129, &press_test_data[0]);
        }
        else
        {
            memset(&press_test_data[0], press_test_flag, 3);
            press_test_data[0] = 0x02;
            led_matrix_client_serverice_send(3, &press_test_data[0]);
        }
    }
    else if (opcode == 0xFE)// test cpic
    {
        for (uint32_t i = 0; i < 2177; i++)
            press_test_data[i] = press_test_flag++;
        press_test_data[0] = 0x03;
        led_matrix_client_serverice_send(2177, &press_test_data[0]);
    }
    else if (opcode == 0xFD)// test fpic
    {
        for (uint32_t i = 0; i < 2049; i++)
            press_test_data[i] = press_test_flag++;
        press_test_data[0] = 0x04;
        led_matrix_client_serverice_send(2049, &press_test_data[0]);
    }
    else
    {
        for (uint8_t i = 0; i < LED_MATRIX_CLIENT_COUNT; i++)
        {
            if ((server_bit_map >> i) & 0x01)
            {
                printf("msg num: %d\n", i);
                rx_flag = true;
                // mark msg which is being sent for re_tx
                led_matrix_client[i].current_msg = opcode;
                led_matrix_client_msg_send(i, opcode);
            }
        }
    }
}


void led_matrix_client_serverice_send(uint32_t len, uint8_t* p_data)
{
    printf("last bitmap1: %04X bitmap2: %04X\n", server_bit_map, server_bit_map2);
    if (rx_flag)
        return;

    int i;
    if (p_data[0] == 0x01 && len == 129)
    {
        for (i = 0; i < 16; i++)
        {
            if (memcmp(&led_matrix_client[i].lm_pic_msg.msg[0], &p_data[8*i+1], 8))
            {
                memcpy(&led_matrix_client_temp[i].lm_pic_msg.msg[0], &p_data[8*i+1], 8);
                server_bit_map |= (1u << i);
            }
        }
        server_bit_map2 = server_bit_map;
        led_matrix_client_msg_all_send(LED_MATRIX_OPCODE_PIC_SET);
    }
    if (p_data[0] == 0x02 && len == 3)
    {
        if(0 == memcmp(&led_matrix_client[0].lm_bac_msg.msg[0], &p_data[1], 2))
            return;

        server_bit_map = 0xffff;
        server_bit_map2 = 0xffff;
        for (i = 0; i < 16; i++)
        {
            memcpy(&led_matrix_client_temp[i].lm_bac_msg.msg[0], &p_data[1], 2);
        }
        led_matrix_client_msg_all_send(LED_MATRIX_OPCODE_BAC_SET); 
        

        /*for (i = 0; i < 16; i++)
        {
            if (memcmp(&led_matrix_client[i].lm_bac_msg.msg[0], &p_data[1], 2))
            {
                memcpy(&led_matrix_client[i].lm_bac_msg.msg[0], &p_data[1], 2);
                server_bit_map |= 1u << i;
            }
        }
        server_bit_map2 = server_bit_map;
        led_matrix_client_msg_all_send(LED_MATRIX_OPCODE_BAC_SET);*/
    }
    if (p_data[0] == 0x03 && len == 2177)
    {
        for (i = 0; i < 16; i++)
        {
            if (memcmp(&led_matrix_client[i].lm_cpic_msg.msg[0], &p_data[136*i+1], 136))
            {
                memcpy(&led_matrix_client_temp[i].lm_cpic_msg.msg[0], &p_data[136*i+1], 136);
                server_bit_map |= 1u << i;
            }
        }
        server_bit_map2 = server_bit_map;
        need_seg = true;
        led_matrix_client_msg_all_send(LED_MATRIX_OPCODE_CPIC_SET);
    }
    if (p_data[0] == 0x04 && len == 2049)
    {
        for (i = 0; i < 16; i++)
        {
            if (memcmp(&led_matrix_client[i].lm_fpic_msg.msg[0], &p_data[128*i+1], 128))
            {
                memcpy(&led_matrix_client_temp[i].lm_fpic_msg.msg[0], &p_data[128*i+1], 128);
                server_bit_map |= 1u << i;
            }
        }
        server_bit_map2 = server_bit_map;
        need_seg = true;
        led_matrix_client_msg_all_send(LED_MATRIX_OPCODE_FPIC_SET);
    }
    if (lm_timer_id == 0xFF && !need_seg)
        mesh_timer_set(500, false, led_matrix_rx_timeout, &lm_timer_id);

    printf("server_bit_map: %04X\n", server_bit_map);
}

