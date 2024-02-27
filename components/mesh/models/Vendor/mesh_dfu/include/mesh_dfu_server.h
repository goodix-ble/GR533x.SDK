/**
 *****************************************************************************************
 *
 * @file mesh_dfu_server.h
 *
 * @brief Mesh DFU Server API.
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

 /**
 * @addtogroup MESH
 * @{
 */
#ifndef __MESH_DFU_SERVER_H__
#define __MESH_DFU_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "mesh_dfu_common.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/** Mesh DFU Server model ID */
#define MESH_DFU_SERVER_MODEL_ID (0x0010)

#define MESH_DFU_NEW_VERSION_RSP_MARK (1u << 0)
#define MESH_DFU_NEW_VERSION_PUB_MARK (1u << 1)


/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/* Forward declaration */
typedef struct __mesh_dfu_server_t  mesh_dfu_server_t;

/**
 * Callback type for Mesh DFU New Version Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     DFU                       DFU state to be used by the application.
 */
typedef void (*mesh_dfu_state_set_cb_t)(uint8_t model_instance_index, mesh_dfu_new_version_status_msg_pkt_t new_version);

/**
 * Callback type for Mesh DFU Current Version Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     p_present_onoff           Application fills this value with the value retrived from the hardware interface.
 */
typedef void (*mesh_dfu_state_get_cb_t)(uint8_t model_instance_index, mesh_dfu_current_version_status_msg_pkt_t * p_current_version);

/**
 * Transaction callbacks for the Mesh DFU state.
 */
typedef struct
{
    mesh_dfu_state_set_cb_t set_cb;     /**< Callback for Mesh DFU New Version Set/Set Unacknowledged message. */
    mesh_dfu_state_get_cb_t get_cb;     /**< Callback for Mesh DFU Current Version Get message. */
} mesh_dfu_server_state_cbs_t;

/**
 * Mesh DFU Server callback list.
 */
typedef struct
{
    mesh_dfu_server_state_cbs_t dfu_cbs;  /**< Callback list for Mesh DFU Server. */
} mesh_dfu_server_callbacks_t;

/** Information of the Version. */
typedef struct
{
    uint16_t company_id;                                 /**< The Company ID value of the version */
    uint16_t product_id;                                 /**< The Product ID value of the version */
    uint16_t product_version_id;                         /**< The Product Version ID value of the version */
} mesh_dfu_version_status_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    const mesh_dfu_server_callbacks_t *p_callbacks;     /**< User provided callback for this model. */
    mesh_dfu_version_status_t current_version;          /** Information of the Current Version. */
    mesh_dfu_version_status_t new_version;              /** Information of the New Version. */
    // for mesh_dfu_new_version_status_msg_pkt_t send
    uint8_t expect_new_version_rsp_pub;                 /** Mark of the expected transmission. */
    uint8_t actual_new_version_rsp_pub;                 /** Mark of the actual transmission. */
} mesh_dfu_server_settings_t;

/** Structure for tracking TID expiry for the models */
typedef struct
{
    uint16_t src;               /**< Source address */
    uint8_t old_tid;            /**< Previously received TID */
    bool new_transaction;       /**< New transaction indicator flag */
} dfu_tid_filter_t;

/**
 * Mesh DFU Server model information.
 */
struct __mesh_dfu_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    dfu_tid_filter_t tid_filter;                /**< Tid tracker. */
    mesh_dfu_server_settings_t settings;        /**< Settings for this model instance. */
    uint16_t client_address;                    /**< The address message received. */
    uint8_t model_instance_index;               /**< Model instance index. */
};

/**
 * Initializes Mesh DFU Server model.
 *
 * @param[in]     p_server                 Mesh DFU server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command is disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t mesh_dfu_server_init(mesh_dfu_server_t *p_server, uint8_t element_offset);

#endif /* __MESH_DFU_SERVER_H__ */

/** @} */

