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
#include "user_bat_s.h"
#include "app_timer.h"

/*
 * DEFINES
 *****************************************************************************************
 */
#define ADV_INTERVAL              160     /**< The fast advertising min interval (unit: 0.625ms, 100ms). */
#define RPA_RENEW_TIME            1500    /**< Rpa address renew time (1500s). */

#define AUTO_SEND_MSG_INTERVAL    2000    /**< Auto send message interval(ms), default is 2s. */
#define AUTO_SEND_MSG_COUNT       500     /**< Auto send message count for one loop test. */

#if (MESH_AUTO_PERFORMANCE_TEST)
#define AUTO_SEND_MSG_DELAY_TIME  30000   /**< Delay time for start new net tx param test, default is 30s. */
#define AUTO_SEND_MSG_LOOP_COUNT  7       /**< Loop test count. */
#endif

/*
 * LOCAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
#if (START_BLE_ADV)
static const uint8_t s_adv_data_set[] =
{
    0x09,
    BLE_GAP_AD_TYPE_COMPLETE_NAME,
    'A', 'd', 'v', ' ', 'D', 'e', 'm', 'o',
};

static ble_gap_adv_time_param_t adv_time_param =
{
    .duration     = 0,
    .max_adv_evt  = 0,
};
#endif

static app_timer_id_t s_auto_send_msg_timer_id;
uint32_t s_auto_send_msg_cnt = 0;

#if (MESH_AUTO_PERFORMANCE_TEST)
static app_timer_id_t s_delay_timer_id;
static uint8_t s_loop_test_count = 0;
uint8_t g_net_tx_count = 2;
uint8_t g_net_tx_intv = 2;   // 10ms random delay, interval is 20ms ~ 30ms
#endif

/*
 * EXTERNAL VARIABLE DECLARATION
 *****************************************************************************************
 */
extern mesh_stack_config_t mesh_stack_config;
extern mesh_callback_t app_mesh_callback;

/*
 * GLOBAL FUNCTION DEFINITIONS
 *****************************************************************************************
 */
#if (START_BLE_ADV)
void start_adv(void)
{
    sdk_err_t   error_code;
    ble_gap_adv_param_t adv_param;

    memset(&adv_param, 0x00, sizeof(ble_gap_adv_param_t));
    adv_param.adv_intv_max    = ADV_INTERVAL;
    adv_param.adv_intv_min    = ADV_INTERVAL;
    adv_param.adv_mode        = BLE_GAP_ADV_TYPE_ADV_IND;
    adv_param.chnl_map        = BLE_GAP_ADV_CHANNEL_37_38_39;
    adv_param.disc_mode       = BLE_GAP_DISC_MODE_GEN_DISCOVERABLE;
    adv_param.filter_pol      = BLE_GAP_ADV_ALLOW_SCAN_ANY_CON_ANY;

    error_code = ble_gap_adv_param_set(0, BLE_GAP_OWN_ADDR_STATIC, &adv_param);
    APP_ERROR_CHECK(error_code);

    error_code = ble_gap_adv_data_set(0, BLE_GAP_ADV_DATA_TYPE_DATA, s_adv_data_set, sizeof(s_adv_data_set));
    APP_ERROR_CHECK(error_code);

    error_code = ble_gap_adv_start(0, &adv_time_param);
    APP_ERROR_CHECK(error_code);
}
#endif

/*
 * LOCAL FUNCTION DEFINITIONS
 *****************************************************************************************
 */
#if (MESH_AUTO_PERFORMANCE_TEST)
static void delay_timer_cb(void *p_arg)
{
    sdk_err_t   error_code;

    // start test timer for new test
    error_code = app_timer_start(s_auto_send_msg_timer_id, AUTO_SEND_MSG_INTERVAL, NULL);
    APP_ERROR_CHECK(error_code);
}
#endif

static void auto_send_msg_timer_cb(void *p_arg)
{
    s_auto_send_msg_cnt++;
    APP_LOG_INFO("send_msg_cnt = %d\n", s_auto_send_msg_cnt);

    extern void test_send_message(void);
    test_send_message();

    if (s_auto_send_msg_cnt == AUTO_SEND_MSG_COUNT)
    {
        // stop timer
        app_timer_stop(s_auto_send_msg_timer_id);

        // reset message count
        s_auto_send_msg_cnt = 0;

        #if (MESH_AUTO_PERFORMANCE_TEST)
        APP_LOG_INFO("finish test, loop_test_count = %d, net_tx_count = %d",
            s_loop_test_count, g_net_tx_count);

        s_loop_test_count++;

        if (s_loop_test_count < AUTO_SEND_MSG_LOOP_COUNT)
        {
            // start delay timer for new net tx param test
            app_timer_start(s_delay_timer_id, AUTO_SEND_MSG_DELAY_TIME, NULL);

            // set new net tx parameter
            g_net_tx_count++;
            mesh_net_tx_param_set(g_net_tx_count, g_net_tx_intv);
        }
        #else
        APP_LOG_INFO("finish test");
        #endif
    }
}

void app_start_auto_send_msg(void)
{
    APP_LOG_INFO("app_start_auto_send_msg");
    app_timer_start(s_auto_send_msg_timer_id, AUTO_SEND_MSG_INTERVAL, NULL);
    s_auto_send_msg_cnt = 0;
}

void app_stop_auto_send_msg(void)
{
    APP_LOG_INFO("app_stop_auto_send_msg");
    app_timer_stop(s_auto_send_msg_timer_id);
    s_auto_send_msg_cnt = 0;
}

static void app_timer_init(void)
{
    sdk_err_t   error_code;

    #if (MESH_AUTO_PERFORMANCE_TEST)
    error_code = app_timer_create(&s_delay_timer_id, ATIMER_ONE_SHOT, delay_timer_cb);
    APP_ERROR_CHECK(error_code);
    #endif

    error_code = app_timer_create(&s_auto_send_msg_timer_id, ATIMER_REPEAT, auto_send_msg_timer_cb);
    APP_ERROR_CHECK(error_code);
}

static void gap_params_init(void)
{
    sdk_err_t   error_code;

    // set security paramter
    ble_sec_param_t sec_param;
    sec_param.level = BLE_SEC_MODE1_LEVEL2;
    sec_param.io_cap = BLE_SEC_IO_NO_INPUT_NO_OUTPUT;
    sec_param.oob = false;
    sec_param.auth = BLE_SEC_AUTH_BOND;
    sec_param.key_size = 16;
    sec_param.ikey_dist = BLE_SEC_KDIST_ALL;
    sec_param.rkey_dist = BLE_SEC_KDIST_ALL;
    error_code = ble_sec_params_set(&sec_param);
    APP_ERROR_CHECK(error_code);

    // enable privacy
    error_code = ble_gap_privacy_params_set(RPA_RENEW_TIME, true);
    APP_ERROR_CHECK(error_code);

    // init timer
    app_timer_init();
}

static void ble_app_init(void)
{
    sdk_version_t version;

    sys_sdk_verison_get(&version);
    APP_LOG_INFO("Goodix BLE SDK V%d.%d.%d (commit %x)",
        version.major, version.minor, version.build, version.commit_id);

    // gap params init for ble
    gap_params_init();
    // service init for ble
    user_bat_s_init();
    // mesh stack init
    mesh_stack_init(&mesh_stack_config, &app_mesh_callback);
}

static void app_sec_rcv_enc_req_handler(uint8_t conn_idx, const ble_sec_evt_enc_req_t *p_enc_req)
{
    ble_sec_cfm_enc_t cfm_enc;
    uint32_t tk;

    if (NULL == p_enc_req)
    {
        return;
    }

    memset((uint8_t *)&cfm_enc, 0, sizeof(cfm_enc));

    switch (p_enc_req->req_type)
    {
        // User needs to decide whether to accept the pair request.
        case BLE_SEC_PAIR_REQ:
            cfm_enc.req_type = BLE_SEC_PAIR_REQ;
            cfm_enc.accept   = true;
            break;

        case BLE_SEC_TK_REQ:
            APP_LOG_INFO("Input pin code: 999999.");
            cfm_enc.req_type = BLE_SEC_TK_REQ;
            cfm_enc.accept   = true;
            tk = 999999;
            memset(cfm_enc.data.tk.key, 0, 16);
            cfm_enc.data.tk.key[0] = (uint8_t)((tk & 0x000000FF) >> 0);
            cfm_enc.data.tk.key[1] = (uint8_t)((tk & 0x0000FF00) >> 8);
            cfm_enc.data.tk.key[2] = (uint8_t)((tk & 0x00FF0000) >> 16);
            cfm_enc.data.tk.key[3] = (uint8_t)((tk & 0xFF000000) >> 24);
            break;

        default:
            break;
    }

    ble_sec_enc_cfm(conn_idx, &cfm_enc);
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
            #if (START_BLE_ADV)
            start_adv();
            #endif
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
            //APP_LOG_INFO("adv report");
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
            user_bat_s_connect_handler(p_evt->evt.gapc_evt.index);
            break;

        case BLE_GAPC_EVT_DISCONNECTED:
            APP_LOG_INFO("disconnected, index = %d, status = 0x%x", p_evt->evt.gapc_evt.index, p_evt->evt_status);
            user_bat_s_disconnect_handler(p_evt->evt.gapc_evt.index, p_evt->evt.gapc_evt.params.disconnected.reason);
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
            app_sec_rcv_enc_req_handler(p_evt->evt.sec_evt.index, &(p_evt->evt.sec_evt.params.enc_req));
            break;

        case BLE_SEC_EVT_LINK_ENCRYPTED:
            if (BLE_SUCCESS == p_evt->evt_status)
            {
                APP_LOG_INFO("Link has been successfully encrypted, conn_idx = %d.", p_evt->evt.sec_evt.index);
            }
            else
            {
                APP_LOG_INFO("Pairing failed for error 0x%x, conn_idx = %d.", p_evt->evt_status, p_evt->evt.sec_evt.index);
            }
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
