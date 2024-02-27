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
#include "simple_onoff_server.h"
#include "mesh_stack_config.h"

/*
 * LOCAL FUNCTION DECLARATION
 *****************************************************************************************
 */
static void app_onoff_server_set_cb(uint8_t model_instance_index, uint8_t onoff);
static void app_onoff_server_get_cb(uint8_t model_instance_index, uint8_t * p_present_onoff);

static uint16_t app_simple_onoff_server_init(void);
static void mesh_init_cmp_callback(void);

/*
 * GLOBAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
extern app_mesh_common_cb_t app_mesh_common_cb;
extern app_mesh_health_cb_t app_mesh_health_cb;
extern app_mesh_lpn_friend_cb_t app_mesh_lpn_friend_cb;

/*
 * LOCAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
static const simple_onoff_server_callbacks_t server_cbs =
{
    .onoff_cbs.set_cb = app_onoff_server_set_cb,
    .onoff_cbs.get_cb = app_onoff_server_get_cb,
};
 
static uint8_t pin_onoff[SIMPLE_ONOFF_SERVER_INSTANCE_COUNT] = {0};
static simple_onoff_server_t simple_on_off_server[SIMPLE_ONOFF_SERVER_INSTANCE_COUNT];

static mesh_composition_data_t mesh_composition_data =
{
    .cid = MESH_DEVICE_COMPANY_ID,
    .pid = MESH_DEVICE_PRODUCT_ID,
    .vid = MESH_DEVICE_VERSION_ID,
    .features = MESH_DEVICE_FEATURES,
};

#if (MESH_DEVICE_FEATURES & MESH_FEATURE_MASK_FRIEND)
static mesh_friend_param_t mesh_friend_param =
{
    .friend_rx_window = MESH_FRIEND_RX_WINDOW,
    .friend_queue_size = MESH_FRIEND_QUEUE_SIZE,
    .friend_subs_list_size = MESH_FRIEND_SUB_LIST_SIZE,
};
#endif

static mesh_stack_config_t mesh_stack_config =
{
    .p_composition_data                     = &mesh_composition_data,
    .p_dev_name                             = (uint8_t *)MESH_DEVICE_NAME,
    .dev_name_len                           = sizeof(MESH_DEVICE_NAME) - 1,
    .net_cache_size                         = MESH_NET_CACHE_SIZE,
    .net_replay_list_size                   = MESH_NET_REPLAY_LIST_SIZE,
    .net_seq_number_block_size              = MESH_NET_SEQ_NUMBER_BLOCK_SIZE,
    .net_seq_number_threshold_ivupdate      = MESH_NET_SEQ_NUMBER_THRESHOLD_IVUPDATE,
    .model_num_max                          = MESH_MODEL_NUM_MAX,
    .subs_list_size_max_per_model           = MESH_SUBS_LIST_SIZE_MAX_PER_MODEL,
    .virt_addr_list_size_max                = MESH_VIRT_ADDR_LIST_SIZE_MAX,
    .appkey_model_bind_num_max              = MESH_APPKEY_MODEL_BIND_NUM_MAX,

#if (MESH_DEVICE_FEATURES & MESH_FEATURE_MASK_PROXY)
    .proxy_connect_num_max                  = CFG_MAX_CONNECTIONS,
    .proxy_filter_list_size_max_per_conn    = MESH_PROXY_FILTER_LIST_SIZE_MAX_PER_CONN,
#else
    .proxy_connect_num_max                  = 0,
    .proxy_filter_list_size_max_per_conn    = 0,
#endif

#if (MESH_DEVICE_FEATURES & MESH_FEATURE_MASK_FRIEND)
    .p_friend_param                         = &mesh_friend_param,
    .friend_friendship_num_max              = MESH_FRIEND_FRIENDSHIP_NUM_MAX,
#else
    .p_friend_param                         = NULL,
    .friend_friendship_num_max              = 0,
#endif
};

static mesh_callback_t app_mesh_callback = 
{
    .app_mesh_init_cmp_callback       = mesh_init_cmp_callback,
    .app_mesh_common_callback         = &app_mesh_common_cb,
    .app_mesh_health_callback         = &app_mesh_health_cb,
    .app_mesh_lpn_friend_callback     = &app_mesh_lpn_friend_cb,
};

/*
 * LOCAL  FUNCTION DEFINITIONS
 *****************************************************************************************
 */

/** Callback for updating the "hardware" state */
static void app_onoff_server_set_cb(uint8_t model_instance_index, uint8_t onoff)
{
    pin_onoff[model_instance_index] = onoff;
    APP_LOG_INFO("SERVER[%d] -- User Callback: set pin is %d!", model_instance_index, pin_onoff[model_instance_index]);
}

/** Callback for reading the "hardware" state */
static void app_onoff_server_get_cb(uint8_t model_instance_index, uint8_t * p_present_onoff)
{
    *p_present_onoff = pin_onoff[model_instance_index];
    APP_LOG_INFO("SERVER[%d] -- User Callback: get pin is %d!", model_instance_index, pin_onoff[model_instance_index]);
}

/** Add simple onoff service */
static uint16_t app_simple_onoff_server_init(void)
{
    uint16_t status = MESH_ERROR_NO_ERROR;
    
    for (uint8_t i = 0; i < SIMPLE_ONOFF_SERVER_INSTANCE_COUNT; i++)
    {
        simple_on_off_server[i].model_lid = MESH_INVALID_LOCAL_ID;
        simple_on_off_server[i].settings.p_callbacks = &server_cbs;
        simple_on_off_server[i].client_address = MESH_INVALID_ADDR;
        simple_on_off_server[i].model_instance_index = i;

        status = simple_onoff_server_init(&simple_on_off_server[i], i);
        
        if(MESH_ERROR_NO_ERROR != status)
        {
            return status;
        }
    }

    return status;
}

static void mesh_init_cmp_callback(void)
{
    //set run time
    mesh_run_time_set(1000, 0);
    //register model
    if (MESH_ERROR_NO_ERROR == app_simple_onoff_server_init())
    {
        APP_LOG_INFO("Register model successful!");
        mesh_enable();
    }
}

/*
 * GLOBAL FUNCTION DEFINITIONS
 *****************************************************************************************
 */
void ble_app_init(void)
{
    sdk_version_t     version;

    sys_sdk_verison_get(&version);
    APP_LOG_INFO("Goodix BLE SDK V%d.%d.%d (commit %x)",
                 version.major, version.minor, version.build, version.commit_id);

    APP_LOG_INFO("Mesh App start");
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
            break;

        case BLE_GAPM_EVT_ADV_STOP:
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
            break;

        case BLE_GAPM_EVT_SCAN_STOP:
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
            break;

        case BLE_GAPC_EVT_DISCONNECTED:
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
