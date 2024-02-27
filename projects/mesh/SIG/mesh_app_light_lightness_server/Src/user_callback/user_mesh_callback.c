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

#define APP_LOG_TAG "user_mesh_callback.c"

/*
 * INCLUDE FILES
 *****************************************************************************************
 */
#include "app_log.h"
#include "mesh_common.h"
#include "user_app.h"

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
static void mesh_prov_state_callback(mesh_provee_state_t status, uint16_t prim_addr);
static void mesh_enabled_callback(mesh_error_t status);
static void mesh_prov_param_req_callback(void);
static void utils_reverse_array(uint8_t * p_array, uint16_t size);
static void mesh_prov_auth_data_req_callback(bool pub_key_oob_flag, mesh_prov_auth_method_t auth_method, uint16_t auth_action, uint8_t auth_size);
static void mesh_node_reset_callback(void); 

/*
 * GLOBAL FUNCTION DECLARATION
 *****************************************************************************************
 */
bool mesh_enable_flag = false;

/*
 * GLOBAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
app_mesh_common_cb_t app_mesh_common_cb =
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

app_mesh_health_cb_t app_mesh_health_cb =
{
    .app_mesh_fault_get_cb           = NULL,
    .app_mesh_fault_test_cb          = NULL,
    .app_mesh_fault_clear_cb         = NULL,
    .app_mesh_fault_period_cb        = NULL,
};

app_mesh_lpn_friend_cb_t app_mesh_lpn_friend_cb =
{
    .app_mesh_lpn_status_cb          = NULL,
    .app_mesh_lpn_offer_cb           = NULL,
    .app_mesh_lpn_poll_done_cb       = NULL,
};

/*
 * LOCAL FUNCTION DEFINITIONS
 *****************************************************************************************
 */
static void mesh_prov_state_callback(mesh_provee_state_t state, uint16_t prim_addr)
{
    APP_LOG_INFO("prov_state = %d, primary address is %d!", state, prim_addr);
}

static void mesh_enabled_callback(mesh_error_t status)
{
    mesh_stack_version_t version_number = 
    {
        .p_spec_version = NULL,
        .p_sdk_version = (mesh_sdk_version_t*)sys_malloc(sizeof(mesh_sdk_version_t))
    };

    if(status == MESH_ERROR_NO_ERROR)
    {
        mesh_version_get(&version_number);
        mesh_enable_flag = true;
        APP_LOG_INFO("Mesh enable successful, Mesh stack verison: %d.%d.%d", 
                    version_number.p_sdk_version->mesh_sdk_version_major,
                    version_number.p_sdk_version->mesh_sdk_version_minor,
                    version_number.p_sdk_version->mesh_sdk_version_revision);
    }
    else
    {
        APP_LOG_INFO("Mesh enable failure , error code is 0x%04x", status);
        mesh_enable_flag = false;
    }

    sys_free(version_number.p_sdk_version);
    version_number.p_sdk_version = NULL;
}

static void mesh_prov_param_req_callback(void)
{
    mesh_prov_param_t prov_param_rsp = 
    {
        /// Device UUID
        .dev_uuid = {0x00, 0x1B, 0xDC, 0x08, 0x10, 0x21, 0x0B, 0x0E, 0x0A, 0x0C, 0x00, 0x0B, 0x0E, 0x0A, 0x0C, 0x12},
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

