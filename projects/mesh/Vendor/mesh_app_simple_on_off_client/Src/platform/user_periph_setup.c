/**
 *****************************************************************************************
 *
 * @file user_periph_setup.c
 *
 * @brief  User Periph Init Function Implementation.
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
 *****************************************************************************************
 */
#include "user_app.h"
#include "user_periph_setup.h"
#include "gr_includes.h"
#include "app_assert.h"
#include "app_log.h"
#include "hal_flash.h"
#include "custom_config.h"
#include "app_pwr_mgmt.h"
#include "board_SK.h"
#include "mesh_common.h"
#include "simple_onoff_client.h"

extern simple_onoff_client_t simple_on_off_client[SIMPLE_ONOFF_CLIENT_INSTANCE_COUNT];

/*define the uart receive data length*/
#define UART_RX_LEN             (2048)
#define UART_TX_LEN             (4096)

#define APP_STATE_ON  (1)
#define APP_STATE_OFF (0)

/*
 * LOCAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
/**@brief Bluetooth device address. */
static const uint8_t  s_bd_addr[SYS_BD_ADDR_LEN] = {0xa3, 0xa3, 0xa3, 0xa3, 0xa3, 0xa3};

static uint8_t s_uart_rx_buffer[UART_RX_LEN];
static uint8_t s_uart_tx_buffer[UART_TX_LEN];

static app_uart_params_t s_uart_param;

/*
 * LOCAL  FUNCTION DEFINITIONS
 *****************************************************************************************
 */
static void mesh_test_uart_data_handler(uint8_t *buf, uint8_t len)
{
    simple_onoff_set_msg_pkt_t set_params;
    static uint8_t tid = 0;
    uint16_t status = MESH_ERROR_NO_ERROR;
    
    if (2 == len && SIMPLE_ONOFF_CLIENT_INSTANCE_COUNT > buf[0])
    {
        switch (buf[1])
        {
            case 0:
                mesh_stack_reset(true);
                break;
            case 1:
                // ON, SET
                set_params.on_off = APP_STATE_ON;
                set_params.tid = tid++;
                
                status = simple_onoff_client_set(&simple_on_off_client[buf[0]], &set_params);
                    
                if (MESH_ERROR_NO_ERROR == status)
                {
                    APP_LOG_INFO("CLIENT[%d] -- CAN send SET message.", simple_on_off_client[buf[0]].model_instance_index);
                }
                else
                {
                    APP_LOG_INFO("CLIENT[%d] -- CAN NOT send SET message.", simple_on_off_client[buf[0]].model_instance_index);
                }
                break;
            case 2:
                // OFF, SET
                set_params.on_off = APP_STATE_OFF;
                set_params.tid = tid++;
                
                status = simple_onoff_client_set(&simple_on_off_client[buf[0]], &set_params);
                if (MESH_ERROR_NO_ERROR == status)
                {
                    APP_LOG_INFO("CLIENT[%d] -- CAN send SET message.", simple_on_off_client[buf[0]].model_instance_index);
                }
                else
                {
                    APP_LOG_INFO("CLIENT[%d] -- CAN NOT send SET message.", simple_on_off_client[buf[0]].model_instance_index);
                }                
                break;
            case 3:
                // ON, SET UN
                set_params.on_off = APP_STATE_ON;
                set_params.tid = tid++;
                
                status = simple_onoff_client_set_unack(&simple_on_off_client[buf[0]], &set_params);
                if (MESH_ERROR_NO_ERROR == status)
                {
                    APP_LOG_INFO("CLIENT[%d] -- CAN send SET UN message.", simple_on_off_client[buf[0]].model_instance_index);
                }
                else
                {
                    APP_LOG_INFO("CLIENT[%d] -- CAN NOT send SET UN message.", simple_on_off_client[buf[0]].model_instance_index);
                }                
                break;                
            case 4:
                // OFF, SET UN
                set_params.on_off = APP_STATE_OFF;
                set_params.tid = tid++;
                
                status = simple_onoff_client_set_unack(&simple_on_off_client[buf[0]], &set_params);
                if (MESH_ERROR_NO_ERROR == status)
                {
                    APP_LOG_INFO("CLIENT[%d] -- CAN send SET UN message.", simple_on_off_client[buf[0]].model_instance_index);
                }
                else
                {
                    APP_LOG_INFO("CLIENT[%d] -- CAN NOT send SET UN message.", simple_on_off_client[buf[0]].model_instance_index);
                }                     
                break; 
            case 5:
                // GET               
                status = simple_onoff_client_get(&simple_on_off_client[buf[0]]);
                if (MESH_ERROR_NO_ERROR == status)
                {
                    APP_LOG_INFO("CLIENT[%d] -- CAN send GET message.", simple_on_off_client[buf[0]].model_instance_index);
                }
                else
                {
                    APP_LOG_INFO("CLIENT[%d] -- CAN NOT send GET message.", simple_on_off_client[buf[0]].model_instance_index);
                }                     
                break;
            case 6:
                // CANCEL GET/SET               
                status = simple_onoff_client_setget_cancel(&simple_on_off_client[buf[0]]);
                if (MESH_ERROR_NO_ERROR == status)
                {
                    APP_LOG_INFO("CLIENT[%d] -- Operation is Success.", simple_on_off_client[buf[0]].model_instance_index);
                }
                else
                {
                    APP_LOG_INFO("CLIENT[%d] -- Reliable message transfer procedure is off or invalid parameter.", simple_on_off_client[buf[0]].model_instance_index);
                }   
                break;  
            default:
                break;
        }
    }
}

static void app_uart_data_tx_send(uint8_t *p_data, uint16_t length)
{
    app_uart_transmit_async(APP_UART_ID, p_data, length);
}

static void app_uart_data_flush(void)
{
    app_uart_flush(APP_UART_ID);
}
static void app_log_assert_init(void)
{
    app_log_init_t log_init;

    log_init.filter.level                 = APP_LOG_LVL_DEBUG;
    log_init.fmt_set[APP_LOG_LVL_ERROR]   = APP_LOG_FMT_ALL & (~APP_LOG_FMT_TAG);
    log_init.fmt_set[APP_LOG_LVL_WARNING] = APP_LOG_FMT_LVL;
    log_init.fmt_set[APP_LOG_LVL_INFO]    = APP_LOG_FMT_LVL;
    log_init.fmt_set[APP_LOG_LVL_DEBUG]   = APP_LOG_FMT_LVL;

    app_log_init(&log_init, app_uart_data_tx_send, app_uart_data_flush);
    app_assert_init();
}

static void uart_evt_handler(app_uart_evt_t * p_evt)
{
    if (APP_UART_EVT_RX_DATA == p_evt->type)
    {
        mesh_test_uart_data_handler(s_uart_rx_buffer, p_evt->data.size);
        memset(s_uart_rx_buffer, 0, UART_RX_LEN);
        app_uart_receive_async(APP_UART_ID, s_uart_rx_buffer, UART_RX_LEN);
    }
    else if (APP_UART_EVT_ERROR == p_evt->type)
    {
        APP_LOG_INFO("err_code = %d\n", p_evt->data.error_code);
        memset(s_uart_rx_buffer, 0, UART_RX_LEN);
        app_uart_receive_async(APP_UART_ID, s_uart_rx_buffer, UART_RX_LEN);
    }
}

static void uart_init(void)
{
    app_uart_tx_buf_t uart_buffer;

    uart_buffer.tx_buf                = s_uart_tx_buffer;
    uart_buffer.tx_buf_size           = UART_TX_LEN;

    s_uart_param.id                   = APP_UART_ID;
    s_uart_param.init.baud_rate       = APP_UART_BAUDRATE;
    s_uart_param.init.data_bits       = UART_DATABITS_8;
    s_uart_param.init.stop_bits       = UART_STOPBITS_1;
    s_uart_param.init.parity          = UART_PARITY_NONE;
    s_uart_param.init.hw_flow_ctrl    = UART_HWCONTROL_NONE;
    s_uart_param.init.rx_timeout_mode = UART_RECEIVER_TIMEOUT_ENABLE;
    s_uart_param.pin_cfg.rx.type      = APP_UART_RX_IO_TYPE;
    s_uart_param.pin_cfg.rx.pin       = APP_UART_RX_PIN;
    s_uart_param.pin_cfg.rx.mux       = APP_UART_RX_PINMUX;
    s_uart_param.pin_cfg.tx.type      = APP_UART_TX_IO_TYPE;
    s_uart_param.pin_cfg.tx.pin       = APP_UART_TX_PIN;
    s_uart_param.pin_cfg.tx.mux       = APP_UART_TX_PINMUX;

    app_uart_init(&s_uart_param, uart_evt_handler, &uart_buffer);
    app_uart_receive_async(APP_UART_ID, s_uart_rx_buffer, UART_RX_LEN);
}

/*
 * GLOBAL FUNCTION DEFINITIONS
 *****************************************************************************************
 */
void app_periph_init(void)
{
    SYS_SET_BD_ADDR(s_bd_addr);
    app_log_assert_init();
    uart_init();
    pwr_mgmt_mode_set(PMR_MGMT_ACTIVE_MODE);
}
