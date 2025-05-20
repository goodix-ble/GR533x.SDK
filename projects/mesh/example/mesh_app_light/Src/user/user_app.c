/**
 *****************************************************************************************
 *
 * @file user_app.c
 *
 * @brief User function Implementation.
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
#include "grx_sys.h"
#include "app_log.h"
#include "app_error.h"
#include "mesh_common.h"
#include "mesh_model.h"
#include "simple_onoff_client.h"
#include "user_app.h"
#include "mesh_stack_config.h"
#include "app_timer.h"

#if (MESH_AUTO_PERFORMANCE_TEST)
#define RCV_MSG_TIMEOUT           20000       // receive mesh message timeout time, default is 20s
#define AUTO_SEND_MSG_LOOP_COUNT  7           // loop test count

uint8_t g_net_tx_count = 2;
uint8_t g_net_tx_intv = 2;          // 10ms random delay, interval is 20ms ~ 30ms
uint8_t g_relay_tx_count = 2;
uint8_t g_relay_tx_intv = 2;        // 10ms random delay, interval is 20ms ~ 30ms
static uint8_t s_loop_test_count = 0;
#endif

/*
 * EXTERNAL VARIABLE DECLARATION
 *****************************************************************************************
 */
extern mesh_stack_config_t mesh_stack_config;
extern mesh_callback_t app_mesh_callback;

#if (MESH_AUTO_PERFORMANCE_TEST)
static app_timer_id_t s_rcv_msg_timeout_timer_id;

static void app_rcv_msg_timeout_cb(void *p_arg)
{
    sdk_err_t   error_code;
	extern uint32_t s_rcv_msg_count;

    APP_LOG_INFO("finish test, loop_test_count = %d, net_tx_count = %d, relay_tx_count = %d, rcv_msg_count = %d",
        s_loop_test_count, g_net_tx_count, g_relay_tx_count, s_rcv_msg_count);

    s_loop_test_count++;

    if (s_loop_test_count < AUTO_SEND_MSG_LOOP_COUNT)
    {
        // reset rcv message count
        s_rcv_msg_count = 0;

        // set new net tx parameter
        g_net_tx_count++;
        mesh_net_tx_param_set(g_net_tx_count, g_net_tx_intv);

        // set new relay tx parameter
        g_relay_tx_count++;
        mesh_relay_tx_param_set(g_relay_tx_count, g_relay_tx_intv);

        error_code = app_timer_start(s_rcv_msg_timeout_timer_id, RCV_MSG_TIMEOUT, NULL);
        APP_ERROR_CHECK(error_code);
    }
}

void app_restart_timer(void)
{
    sdk_err_t   error_code;

    // stop timer
    app_timer_stop(s_rcv_msg_timeout_timer_id);

    error_code = app_timer_start(s_rcv_msg_timeout_timer_id, RCV_MSG_TIMEOUT, NULL);
    APP_ERROR_CHECK(error_code);
}

void app_rcv_msg_timer_init(void)
{
    sdk_err_t   error_code;

    error_code = app_timer_create(&s_rcv_msg_timeout_timer_id, ATIMER_ONE_SHOT, app_rcv_msg_timeout_cb);
    APP_ERROR_CHECK(error_code);

    error_code = app_timer_start(s_rcv_msg_timeout_timer_id, RCV_MSG_TIMEOUT, NULL);
    APP_ERROR_CHECK(error_code);
}
#endif

uint8_t s_device_name[] = {'G', 'o', 'o', 'd', 'i', 'x', '_', 'L', 'i', 'g', 'h', 't', '1'};

static void ble_app_init(void)
{
    sdk_version_t version;

    sys_sdk_verison_get(&version);
    APP_LOG_INFO("Goodix BLE SDK V%d.%d.%d (commit %x)",
        version.major, version.minor, version.build, version.commit_id);

    // set device name according the light node id
    uint8_t device_name_len = sizeof(s_device_name);
    s_device_name[device_name_len - 1] += (g_light_node_id - LIGHT_NODE_ID_1);
    mesh_stack_config.p_dev_name = s_device_name,
    mesh_stack_config.dev_name_len = device_name_len;

    // mesh stack init
    mesh_stack_init(&mesh_stack_config, &app_mesh_callback);
}

void ble_evt_handler(const ble_evt_t *p_evt)
{
    switch(p_evt->evt_id)
    {
        case BLE_COMMON_EVT_STACK_INIT:
            ble_app_init();
            break;

        case BLE_GAPM_EVT_ADV_START:
            APP_LOG_INFO("adv started, index = %d, status = 0x%x", p_evt->evt.gapm_evt.index, p_evt->evt_status);
            break;

        case BLE_GAPM_EVT_ADV_STOP:
            APP_LOG_INFO("adv stopped, index = %d, status = 0x%x", p_evt->evt.gapm_evt.index, p_evt->evt_status);
            break;

        case BLE_GAPM_EVT_CH_MAP_SET:
            break;

        case BLE_GAPM_EVT_WHITELIST_SET:
            break;

        case BLE_GAPM_EVT_PER_ADV_LIST_SET:
            break;

        case BLE_GAPM_EVT_PRIVACY_MODE_SET:
            break;

        case BLE_GAPM_EVT_LEPSM_REGISTER:
            break;

        case BLE_GAPM_EVT_LEPSM_UNREGISTER:
            break;

        case BLE_GAPM_EVT_SCAN_REQUEST:
            break;

        case BLE_GAPM_EVT_ADV_DATA_UPDATE:
            break;

        case BLE_GAPM_EVT_SCAN_START:
            APP_LOG_INFO("scan started, index = %d, status = 0x%x", p_evt->evt.gapm_evt.index, p_evt->evt_status);
            break;

        case BLE_GAPM_EVT_SCAN_STOP:
            APP_LOG_INFO("scan stopped, index = %d, status = 0x%x", p_evt->evt.gapm_evt.index, p_evt->evt_status);
            break;

        case BLE_GAPM_EVT_ADV_REPORT:
            break;

        case BLE_GAPM_EVT_SYNC_ESTABLISH:
            break;

        case BLE_GAPM_EVT_SYNC_STOP:
            break;

        case BLE_GAPM_EVT_SYNC_LOST:
            break;

        case BLE_GAPM_EVT_READ_RSLV_ADDR:
            break;

        case BLE_GAPC_EVT_PHY_UPDATED:
            break;

        case BLE_GAPM_EVT_DEV_INFO_GOT:
            break;

        case BLE_GAPC_EVT_CONNECTED:
            APP_LOG_INFO("connected, index = %d, status = 0x%x", p_evt->evt.gapc_evt.index, p_evt->evt_status);
            break;

        case BLE_GAPC_EVT_DISCONNECTED:
            APP_LOG_INFO("disconnected, index = %d, status = 0x%x", p_evt->evt.gapc_evt.index, p_evt->evt_status);
            break;

        case BLE_GAPC_EVT_CONN_PARAM_UPDATE_REQ:
            ble_gap_conn_param_update_reply(p_evt->evt.gapc_evt.index, true);
            break;

        case BLE_GAPC_EVT_CONN_PARAM_UPDATED:
            break;

        case BLE_GAPC_EVT_CONNECT_CANCLE:
            break;

        case BLE_GAPC_EVT_AUTO_CONN_TIMEOUT:
            break;

        case BLE_GAPC_EVT_PEER_NAME_GOT:
            break;

        case BLE_GAPC_EVT_CONN_INFO_GOT:
            break;

        case BLE_GAPC_EVT_PEER_INFO_GOT:
            break;

        case BLE_GAPC_EVT_DATA_LENGTH_UPDATED:
            break;

        case BLE_GATT_COMMON_EVT_MTU_EXCHANGE:
            break;

        case BLE_GATT_COMMON_EVT_PRF_REGISTER:
            break;

        case BLE_GATTS_EVT_READ_REQUEST:
            break;

        case BLE_GATTS_EVT_WRITE_REQUEST:
            break;

        case BLE_GATTS_EVT_PREP_WRITE_REQUEST:
            break;

        case BLE_GATTS_EVT_NTF_IND:
            break;

        case BLE_GATTS_EVT_CCCD_RECOVERY:
            break;

        case BLE_GATTC_EVT_SRVC_BROWSE:
            break;

        case BLE_GATTC_EVT_PRIMARY_SRVC_DISC:
            break;

        case BLE_GATTC_EVT_INCLUDE_SRVC_DISC:
            break;

        case BLE_GATTC_EVT_CHAR_DISC:
            break;

        case BLE_GATTC_EVT_CHAR_DESC_DISC:
            break;

        case BLE_GATTC_EVT_READ_RSP:
            break;

        case BLE_GATTC_EVT_WRITE_RSP:
            break;

        case BLE_GATTC_EVT_NTF_IND:
            break;

        case BLE_SEC_EVT_LINK_ENC_REQUEST:
            break;

        case BLE_SEC_EVT_LINK_ENCRYPTED:
            break;

        case BLE_SEC_EVT_KEY_PRESS_NTF:
            break;

        case BLE_SEC_EVT_KEY_MISSING:
            break;

        case BLE_L2CAP_EVT_CONN_REQ:
            break;

        case BLE_L2CAP_EVT_CONN_IND:
            break;

        case BLE_L2CAP_EVT_ADD_CREDITS_IND:
            break;

        case BLE_L2CAP_EVT_DISCONNECTED:
            break;

        case BLE_L2CAP_EVT_SDU_RECV:
            break;

        case BLE_L2CAP_EVT_SDU_SEND:
            break;

        case BLE_L2CAP_EVT_ADD_CREDITS_CPLT:
            break;
    }
}
