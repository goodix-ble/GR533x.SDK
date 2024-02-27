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
#include "model_common.h"
#include "app_onoff_client.h"
#include "app_level_client.h"
#include "app_light_lightness_client.h"
#include "mesh_stack_config.h"

/*
 * LOCAL FUNCTION DECLARATION
 *****************************************************************************************
 */
static void app_gen_onoff_client_transaction_status_cb(void * p_args, mesh_model_reliable_trans_status_t status);

static void app_generic_onoff_client_status_cb(const generic_onoff_client_t * p_self,
                                     const mesh_model_msg_ind_t * p_rx_msg, generic_onoff_status_params_t * p_in);

static void app_gen_level_client_transaction_status_cb(void * p_args, mesh_model_reliable_trans_status_t status);

static void app_generic_level_client_status_cb(const generic_level_client_t * p_self,
                                     const mesh_model_msg_ind_t * p_rx_msg, const generic_level_status_params_t * p_in);

static void app_light_ln_actual_client_status_cb(const light_ln_client_t * p_self,
                                                 const mesh_model_msg_ind_t * p_rx_msg,
                                                 light_ln_status_params_t * p_in);
                                          
static void app_light_ln_linear_client_status_cb(const light_ln_client_t * p_self,
                                                 const mesh_model_msg_ind_t * p_rx_msg,
                                                 light_ln_status_params_t * p_in);

static void app_light_ln_last_client_status_cb(const light_ln_client_t * p_self,
                                                const mesh_model_msg_ind_t * p_rx_msg,
                                                light_ln_last_status_params_t * p_in);
                                                
static void app_light_ln_dft_client_status_cb(const light_ln_client_t * p_self,
                                               const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_dft_status_params_t * p_in);
                                               
static void app_light_ln_range_client_status_cb(const light_ln_client_t * p_self,
                                               const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_range_status_params_t * p_in);
                                          
static void app_light_ln_client_transaction_status_cb(void * p_args, mesh_model_reliable_trans_status_t status);

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

static const generic_onoff_client_callbacks_t onoff_client_cbs =
{
    .onoff_status_cb = app_generic_onoff_client_status_cb,
    .ack_transaction_status_cb = app_gen_onoff_client_transaction_status_cb,
};

static const generic_level_client_callbacks_t level_client_cbs =
{
    .level_status_cb = app_generic_level_client_status_cb,
    .ack_transaction_status_cb = app_gen_level_client_transaction_status_cb,
};

static const light_ln_client_callbacks_t client_cbs =
{
    .ln_actual_status_cb = app_light_ln_actual_client_status_cb,
    .ln_linear_status_cb = app_light_ln_linear_client_status_cb,
    .ln_last_status_cb = app_light_ln_last_client_status_cb,
    .ln_dft_status_cb = app_light_ln_dft_client_status_cb,
    .ln_range_status_cb = app_light_ln_range_client_status_cb,
    .ack_transaction_status_cb = app_light_ln_client_transaction_status_cb,
};

generic_level_client_t generic_level_client[LIGHT_LIGHTNESS_CLIENT_INSTANCE_COUNT];

generic_onoff_client_t generic_on_off_client[LIGHT_LIGHTNESS_CLIENT_INSTANCE_COUNT];

light_ln_client_t light_ln_client[LIGHT_LIGHTNESS_CLIENT_INSTANCE_COUNT];

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

/** Generic Level client model interface: Process the received status message in this callback */
static void app_generic_level_client_status_cb(const generic_level_client_t * p_self,
                                     const mesh_model_msg_ind_t * p_rx_msg, const generic_level_status_params_t * p_in)
{
    if (p_in->remaining_time_ms > 0)
    {
        APP_LOG_INFO("CLIENT[%d] -- Level server: 0x%04x, Present Level: %d, Target Level: %d, Remaining Time: %d ms",
                    p_self->model_instance_index, p_rx_msg->src, p_in->present_level, p_in->target_level, p_in->remaining_time_ms);
    }
    else
    {
        APP_LOG_INFO("CLIENT[%d] -- Level server: 0x%04x, Present Level: %d",p_self->model_instance_index, p_rx_msg->src, p_in->present_level);
    }
}

/* Acknowledged transaction status callback, if acknowledged transfer fails, application can
* determine suitable course of action (e.g. re-initiate previous transaction) by using this
* callback.
*/
static void app_gen_level_client_transaction_status_cb(void * p_args, mesh_model_reliable_trans_status_t status)
{
    generic_level_client_t * p_self = (generic_level_client_t *)p_args;
    
    switch(status)
    {
        case MESH_MODEL_RELIABLE_TRANS_SUCCESS:
            APP_LOG_INFO("CLIENT[%d] -- Acknowledged transfer success.", p_self->model_instance_index);
            break;
        case MESH_MODEL_RELIABLE_TRANS_TIMEOUT:
            APP_LOG_INFO("CLIENT[%d] -- Acknowledged transfer timeout.", p_self->model_instance_index);
            break;
        case MESH_MODEL_RELIABLE_TRANS_CANCELLED:
            APP_LOG_INFO("CLIENT[%d] -- Acknowledged transfer cancelled.", p_self->model_instance_index);
            break;
        default:
            break;
    }
}

/** Generic OnOff client model interface: Process the received status message in this callback */
static void app_generic_onoff_client_status_cb(const generic_onoff_client_t * p_self,
                                     const mesh_model_msg_ind_t * p_rx_msg, generic_onoff_status_params_t * p_in)
{
    if (p_in->remaining_time_ms > 0)
    {
        APP_LOG_INFO("CLIENT[%d] -- OnOff server: 0x%04x, Present OnOff: %d, Target OnOff: %d, Remaining Time: %d ms",
                    p_self->model_instance_index, p_rx_msg->src, p_in->present_on_off, p_in->target_on_off, p_in->remaining_time_ms);
    }
    else
    {
        APP_LOG_INFO("CLIENT[%d] -- OnOff server: 0x%04x, Present OnOff: %d",p_self->model_instance_index, p_rx_msg->src, p_in->present_on_off);
    }
}

/*
 * Acknowledged transaction status callback, if acknowledged transfer fails, application can
 * determine suitable course of action (e.g. re-initiate previous transaction) by using this
 * callback.
 */
static void app_gen_onoff_client_transaction_status_cb(void * p_args, mesh_model_reliable_trans_status_t status)
{
    generic_onoff_client_t * p_self = (generic_onoff_client_t *)p_args;
    
    switch(status)
    {
        case MESH_MODEL_RELIABLE_TRANS_SUCCESS:
            APP_LOG_INFO("CLIENT[%d] -- Acknowledged transfer success.", p_self->model_instance_index);
            break;
        case MESH_MODEL_RELIABLE_TRANS_TIMEOUT:
            APP_LOG_INFO("CLIENT[%d] -- Acknowledged transfer timeout.", p_self->model_instance_index);
            break;
        case MESH_MODEL_RELIABLE_TRANS_CANCELLED:
            APP_LOG_INFO("CLIENT[%d] -- Acknowledged transfer cancelled.", p_self->model_instance_index);
            break;
        default:
            break;
    }
}

/** Light Lightness client model interface: Process the received status message in this callback */
static void app_light_ln_actual_client_status_cb(const light_ln_client_t * p_self,
                                                 const mesh_model_msg_ind_t * p_rx_msg,
                                                 light_ln_status_params_t * p_in)
{
    if (p_in->remaining_time_ms > 0)
    {
        APP_LOG_INFO("CLIENT[%d] -- Lightness server: 0x%04x, Present Lightness Acutal: %d, Target Lightness Acutal: %d, Remaining Time: %d ms",
                    p_self->model_instance_index, p_rx_msg->src, p_in->present_ln, p_in->target_ln, p_in->remaining_time_ms);
    }
    else
    {
        APP_LOG_INFO("CLIENT[%d] -- Lightness server: 0x%04x, Present Lightness Acutal: %d",p_self->model_instance_index, p_rx_msg->src, p_in->present_ln);
    }
}

static void app_light_ln_linear_client_status_cb(const light_ln_client_t * p_self,
                                                 const mesh_model_msg_ind_t * p_rx_msg,
                                                 light_ln_status_params_t * p_in)
{
    if (p_in->remaining_time_ms > 0)
    {
        APP_LOG_INFO("CLIENT[%d] -- Lightness server: 0x%04x, Present Lightness Linear: %d, Target Lightness Linear: %d, Remaining Time: %d ms",
                    p_self->model_instance_index, p_rx_msg->src, p_in->present_ln, p_in->target_ln, p_in->remaining_time_ms);
    }
    else
    {
        APP_LOG_INFO("CLIENT[%d] -- Lightness server: 0x%04x, Present Lightness Linear: %d",p_self->model_instance_index, p_rx_msg->src, p_in->present_ln);
    }
}

static void app_light_ln_last_client_status_cb(const light_ln_client_t * p_self,
                                                const mesh_model_msg_ind_t * p_rx_msg,
                                                light_ln_last_status_params_t * p_in)
{
        APP_LOG_INFO("CLIENT[%d] -- Lightness server: 0x%04x, Lightness Last: %d",p_self->model_instance_index, p_rx_msg->src, p_in->ln);
}

                                                
static void app_light_ln_dft_client_status_cb(const light_ln_client_t * p_self,
                                               const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_dft_status_params_t * p_in)
{
        APP_LOG_INFO("CLIENT[%d] -- Lightness server: 0x%04x, Lightness Default: %d",p_self->model_instance_index, p_rx_msg->src, p_in->ln);
}
                                               
static void app_light_ln_range_client_status_cb(const light_ln_client_t * p_self,
                                               const mesh_model_msg_ind_t * p_rx_msg,
                                               light_ln_range_status_params_t * p_in)
{
        APP_LOG_INFO("CLIENT[%d] -- Lightness server: 0x%04x, Lightness Range Status Code: %d, Lightness Range Min: %d, Lightness Range Max: %d",
                      p_self->model_instance_index, p_rx_msg->src, p_in->status_code, p_in->min_ln, p_in->max_ln);
}

/*
 * Acknowledged transaction status callback, if acknowledged transfer fails, application can
 * determine suitable course of action (e.g. re-initiate previous transaction) by using this
 * callback.
 */
static void app_light_ln_client_transaction_status_cb(void * p_args, mesh_model_reliable_trans_status_t status)
{
    light_ln_client_t * p_self = (light_ln_client_t *)p_args;

    switch(status)
    {
        case MESH_MODEL_RELIABLE_TRANS_SUCCESS:
            APP_LOG_INFO("CLIENT[%d] -- Acknowledged transfer success.", p_self->model_instance_index);
            break;
        case MESH_MODEL_RELIABLE_TRANS_TIMEOUT:
            APP_LOG_INFO("CLIENT[%d] -- Acknowledged transfer timeout.", p_self->model_instance_index);
            break;
        case MESH_MODEL_RELIABLE_TRANS_CANCELLED:
            APP_LOG_INFO("CLIENT[%d] -- Acknowledged transfer cancelled.", p_self->model_instance_index);
            break;
        default:
            break;
    }
}

static uint16_t app_model_client_init(void)
{
    uint16_t status = MESH_ERROR_NO_ERROR;
    
    for (uint8_t i = 0; i < LIGHT_LIGHTNESS_CLIENT_INSTANCE_COUNT; i++)
    {
        status = app_generic_onoff_client_init(&generic_on_off_client[i], i, &onoff_client_cbs);
        if(MESH_ERROR_NO_ERROR != status)
        {
            return status;
        }

        status = app_generic_level_client_init(&generic_level_client[i], i, &level_client_cbs);
        if(MESH_ERROR_NO_ERROR != status)
        {
            return status;
        }

        status = app_light_ln_client_init(&light_ln_client[i], i, &client_cbs);
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
    if (MESH_ERROR_NO_ERROR == app_model_client_init())
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
