/**
 *****************************************************************************************
 *
 * @file user_mesh_callback.c
 *
 * @brief  MESH Callback Function Implementation.
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
#include "app_log.h"
#include "mesh_common.h"
#include "user_app.h"
#include "user_auto_prov.h"
#include "user_model_server.h"

/*
 * DEFINES
 *****************************************************************************************
 */
 /** Size (in octets) of an encryption key.*/
#define NRF_MESH_KEY_SIZE  (16)

/** Static authentication data */
#define STATIC_AUTH_DATA {0x6E, 0x6F, 0x72, 0x64, 0x69, 0x63, 0x5F, 0x65, 0x78, 0x61, 0x6D, 0x70, 0x6C, 0x65, 0x5F, 0x31}

/*
 * LOCAL FUNCTION DECLARATION
 *****************************************************************************************
 */
static void mesh_init_cmp_callback(void);
static void mesh_enabled_callback(mesh_error_t status);
static void mesh_prov_state_callback(mesh_provee_state_t state, uint16_t prim_addr);
static void mesh_prov_param_req_callback(void);
static void mesh_prov_auth_data_req_callback(bool pub_key_oob_flag, mesh_prov_auth_method_t auth_method, uint16_t auth_action, uint8_t auth_size);
static void mesh_node_reset_callback(void);

/*
 * LOCAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
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

static app_mesh_common_cb_t app_mesh_common_cb =
{
    .app_mesh_enabled_cb             = mesh_enabled_callback,
    .app_mesh_prov_state_cb          = mesh_prov_state_callback,
    .app_mesh_prov_param_req_cb      = mesh_prov_param_req_callback,
    .app_mesh_prov_pub_key_ind_cb    = NULL,
    .app_mesh_prov_oob_auth_req_cb   = mesh_prov_auth_data_req_callback,
    .app_mesh_attention_cb           = NULL,
    .app_mesh_node_reset_cb          = mesh_node_reset_callback,
    .app_mesh_key_ind_cb             = NULL,
    .app_mesh_model_config_ind_cb    = NULL,
};

static app_mesh_health_cb_t app_mesh_health_cb =
{
    .app_mesh_fault_get_cb           = NULL,
    .app_mesh_fault_test_cb          = NULL,
    .app_mesh_fault_clear_cb         = NULL,
    .app_mesh_fault_period_cb        = NULL,
};

static app_mesh_lpn_friend_cb_t app_mesh_lpn_friend_cb =
{
    .app_mesh_lpn_status_cb          = NULL,
    .app_mesh_lpn_offer_cb           = NULL,
    .app_mesh_lpn_poll_done_cb       = NULL,
};

/*
 * GLOBLE VARIABLE DEFINITIONS
 *****************************************************************************************
 */
mesh_stack_config_t mesh_stack_config =
{
    .p_composition_data                     = &mesh_composition_data,
    .p_dev_name                             = NULL,
    .dev_name_len                           = 0,
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

mesh_callback_t app_mesh_callback =
{
    .app_mesh_init_cmp_callback       = mesh_init_cmp_callback,
    .app_mesh_common_callback         = &app_mesh_common_cb,
    .app_mesh_health_callback         = &app_mesh_health_cb,
    .app_mesh_lpn_friend_callback     = &app_mesh_lpn_friend_cb,
};

/*
 * LOCAL FUNCTION DEFINITIONS
 *****************************************************************************************
 */
static void mesh_init_cmp_callback(void)
{
    APP_LOG_INFO("mesh stack init cmp\n");

    //register model
    if (MESH_ERROR_NO_ERROR == app_model_server_init())
    {
        APP_LOG_INFO("Register model successful!");

        // if user need to start anthor ble adv, please set address type to non-rpa for mesh adv
        //mesh_addr_type_set(MESH_ADDR_TYPE_NON_RPA);

        #if (MESH_CLEAR_BOND_INFO)
        extern uint16_t m_api_storage_clear(void);
        m_api_storage_clear();
        #endif

        #if (MESH_AUTO_PROV)
        // init auto prov info
        mesh_auto_prov_info_init();
        #endif

        mesh_enable();
    }
}

static void mesh_prov_state_callback(mesh_provee_state_t state, uint16_t prim_addr)
{
    APP_LOG_INFO("prov_state = %d, primary address is %d!", state, prim_addr);

    #if (MESH_AUTO_PERFORMANCE_TEST)
    if (MESH_PROVEE_STATE_PROV == state)
    {
        extern void app_rcv_msg_timer_init(void);
        app_rcv_msg_timer_init();

        // set default net tx parameter
        extern uint8_t g_net_tx_count;
        extern uint8_t g_net_tx_intv;
        mesh_net_tx_param_set(g_net_tx_count, g_net_tx_intv);

        // set default relay tx parameter
        extern uint8_t g_relay_tx_count;
        extern uint8_t g_relay_tx_intv;
        mesh_relay_tx_param_set(g_relay_tx_count, g_relay_tx_intv);
    }
    #endif
}

static void mesh_prov_param_req_callback(void)
{
    mesh_prov_param_t prov_param_rsp =
    {
        /// OOB information
        .oob_info = 0,
        /// URI hash
        .uri_hash = 0,
        /// not use URI hash
        .uri_hash_flag = false,
        /// Public key OOB information available
        .pub_key_oob_flag = false,
        /// Static OOB information available
        .static_oob_flag = true,
        /// Maximum size of Output OOB supported
        .output_oob_size = 0,
        /// Supported Output OOB Actions, invalid
        .output_oob_action = 0,
        /// Maximum size in octets of Input OOB supported
        .input_oob_size = 0,
        /// Supported Input OOB Actions, set invalid
        .input_oob_action = 0,
    };

    // set device uuid
    sys_device_uid_get(prov_param_rsp.dev_uuid);

    mesh_prov_param_rsp(&prov_param_rsp);
}

static void utils_reverse_array(uint8_t * p_array, uint16_t size)
{
    for(uint16_t i = 0; i < size / 2; ++i)
    {
        uint8_t temp = p_array[i];
        p_array[i] = p_array[size - i - 1];
        p_array[size - i - 1] = temp;
    }
}

static void mesh_prov_auth_data_req_callback(bool pub_key_oob_flag, mesh_prov_auth_method_t auth_method, uint16_t auth_action, uint8_t auth_size)
{
    APP_LOG_INFO("Auth data req: pub_key_oob_flag = %d, auth_method = %d, auth_action = %d, auth_size = %d!!!", pub_key_oob_flag, auth_method, auth_action, auth_size);
    
    bool accept = true;
    uint8_t static_data[NRF_MESH_KEY_SIZE] = STATIC_AUTH_DATA;
    utils_reverse_array(&static_data[0], NRF_MESH_KEY_SIZE);
    mesh_prov_oob_auth_rsp(accept, &static_data[0], NRF_MESH_KEY_SIZE);
}

static void mesh_node_reset_callback(void)
{
    APP_LOG_INFO("[%s] enter!", __func__);

    if (MESH_ERROR_NO_ERROR == mesh_stack_reset(true))
    {
        APP_LOG_INFO("Test mesh reset!!!");
    }
}

static void mesh_enabled_callback(mesh_error_t status)
{
    if(status == MESH_ERROR_NO_ERROR)
    {
        APP_LOG_INFO("Light%d Mesh enable successful", g_light_node_id + 1);
    }

    mesh_relay_state_set(true);
}
