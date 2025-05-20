/**
 ****************************************************************************************
 *
 * @file mesh_common.h
 *
 * @brief Header file for Mesh Common Programming Interface
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
 
 /**
 * @addtogroup MESH
 * @{
 */

#ifndef __MESH_COMMON_H__
#define __MESH_COMMON_H__

/**
 ****************************************************************************************
 * @addtogroup MESH_COMMON Mesh Common
 * @{
 * @brief  Mesh Common Programming Interface
 ****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "mesh_sdk_error.h"
#include "mesh_lpn_friend.h"
#include <stdbool.h>
#include <stdint.h>


/** @addtogroup MESH_COMMON_DEFINES Defines
 * @{ */

/** @defgroup MESH_INVALID  Invalid Value Definition
 * @{ */
#define MESH_INVALID_LOCAL_ID              (0xFF)         /**< Invalid mesh local identifier. */
#define MESH_INVALID_TIMER_ID              (0xFFFFFFFF)   /**< Invalid mesh timer identifier. */
#define MESH_INVALID_KEY_INDEX             (0xFFFF)       /**< Invalid application/network key index. */
#define MESH_INVALID_ADDR                  (0x0000)       /**< Invalid address (unassigned address). */
/** @} */

/** @defgroup MESH_MASK_SUPPORTED_FEATURE  Supported Node Feature Mask
 * @{ */
#define MESH_FEATURE_MASK_RELAY            (1u << 0)   /**< Relay feature supported. */
#define MESH_FEATURE_MASK_PROXY            (1u << 1)   /**< Proxy feature supported. */
#define MESH_FEATURE_MASK_FRIEND           (1u << 2)   /**< Friend feature supported. */
#define MESH_FEATURE_MASK_LOW_POWER        (1u << 3)   /**< Low Power feature supported. */
/** @} */

/** @defgroup MESH_PROV_OOB_INFO_MASK Unprovisioned Device Beacon OOB Information Mask
 * @{ */
#define MESH_PROV_OOB_INFO_MASK_OTHER                       (1u << 0)   /**< Other locations. */
#define MESH_PROV_OOB_INFO_MASK_ELECTRONIC_OR_URI           (1u << 1)   /**< Electronic/URI. */
#define MESH_PROV_OOB_INFO_MASK_2D_MACHINE_READABLE_CODE    (1u << 2)   /**< 2D machine-readable code. */
#define MESH_PROV_OOB_INFO_MASK_BAR_CODE                    (1u << 3)   /**< Bar code. */
#define MESH_PROV_OOB_INFO_MASK_NFC                         (1u << 4)   /**< Near Field Communication (NFC). */
#define MESH_PROV_OOB_INFO_MASK_NUMBER                      (1u << 5)   /**< Number. */
#define MESH_PROV_OOB_INFO_MASK_STRING                      (1u << 6)   /**< String. */
#define MESH_PROV_OOB_INFO_MASK_ON_BOX                      (1u << 11)  /**< On box. */
#define MESH_PROV_OOB_INFO_MASK_INSIDE_BOX                  (1u << 12)  /**< Inside box. */
#define MESH_PROV_OOB_INFO_MASK_ON_PIECE_OF_PAPER           (1u << 13)  /**< On piece of paper. */
#define MESH_PROV_OOB_INFO_MASK_INSIDE_MANUAL               (1u << 14)  /**< Inside manual. */
#define MESH_PROV_OOB_INFO_MASK_ON_DEVICE                   (1u << 15)  /**< On device. */
/** @} */

/** @defgroup MESH_PROV_OUT_OOB_ACTION_MASK  Output OOB Action Mask
 * @{ */
#define MESH_PROV_OUT_OOB_MASK_BLINK        (1u << 0)  /**< Output OOB Action: Blink. */
#define MESH_PROV_OUT_OOB_MASK_BEEP         (1u << 1)  /**< Output OOB Action: Beep. */
#define MESH_PROV_OUT_OOB_MASK_VIBRATE      (1u << 2)  /**< Output OOB Action: Vibrate. */
#define MESH_PROV_OUT_OOB_MASK_NUMERIC      (1u << 3)  /**< Output OOB Action: Output Numeric. */
#define MESH_PROV_OUT_OOB_MASK_ALPHANUMERIC (1u << 4)  /**< Output OOB Action: Output Alphanumeric. */
/** @} */

/** @defgroup MESH_PROV_IN_OOB_ACTION_MASK  Input OOB Action Mask
 * @{ */
#define MESH_PROV_IN_OOB_MASK_PUSH         (1u << 0)   /**< Input OOB Action: Push. */
#define MESH_PROV_IN_OOB_MASK_TWIST        (1u << 1)   /**< Input OOB Action: Twist. */
#define MESH_PROV_IN_OOB_MASK_NUMERIC      (1u << 2)   /**< Input OOB Action: Input Numeric. */
#define MESH_PROV_IN_OOB_MASK_ALPHANUMERIC (1u << 3)   /**< Input OOB Action: Input Alphanumeric. */
/** @} */

/** @} */


/** @addtogroup MESH_COMMON_ENUMERATIONS Enumerations
 * @{ */

/**
 * @brief Authentication Method field values
 */
typedef enum
{ 
    MESH_PROV_AUTH_NO_OOB,     /**< No OOB authentication is used. */
    MESH_PROV_AUTH_STATIC_OOB, /**< Static OOB authentication is used. */
    MESH_PROV_AUTH_OUTPUT_OOB, /**< Output OOB authentication is used. */
    MESH_PROV_AUTH_INPUT_OOB,  /**< Input OOB authentication is used. */
} mesh_prov_auth_method_t;

/**
 * @brief Output OOB Action field values
 */
typedef enum
{
    MESH_PROV_OUT_OOB_BLINK        = 0x00, /**< Output OOB Action: Blink. */
    MESH_PROV_OUT_OOB_BEEP         = 0x01, /**< Output OOB Action: Beep. */
    MESH_PROV_OUT_OOB_VIBRATE      = 0x02, /**< Output OOB Action: Vibrate. */
    MESH_PROV_OUT_OOB_NUMERIC      = 0x03, /**< Output OOB Action: Output Numeric. */
    MESH_PROV_OUT_OOB_ALPHANUMERIC = 0x04, /**< Output OOB Action: Output Alphanumeric. */
} mesh_prov_output_oob_action_t;

/**
 * @brief Input OOB Action field values
 */
typedef enum
{
    MESH_PROV_IN_OOB_PUSH         = 0x00, /**< Input OOB Action: Push. */
    MESH_PROV_IN_OOB_TWIST        = 0x01, /**< Input OOB Action: Twist. */
    MESH_PROV_IN_OOB_NUMERIC      = 0x02, /**< Input OOB Action: Input Numeric. */
    MESH_PROV_IN_OOB_ALPHANUMERIC = 0x03, /**< Input OOB Action: Input Alphanumeric. */
} mesh_prov_input_oob_action_t;

/**
 * @brief Proxy connectable advertising state update types
 */
typedef enum 
{
    MESH_PROXY_ADV_STATE_NODE_STOP = 0,  /**< Advertising with Node Identity stopped. */
    MESH_PROXY_ADV_STATE_NODE_START,     /**< Advertising with Node Identity started. */
    MESH_PROXY_ADV_STATE_NET_STOP,       /**< Advertising with Network ID stopped. */
    MESH_PROXY_ADV_STATE_NET_START,      /**< Advertising with Network ID started. */
} mesh_proxy_adv_state_t;

/**
 * @brief Mesh application/network key types
 */
typedef enum
{
    MESH_KEY_TYPE_NET,      /**< Network key type. */
    MESH_KEY_TYPE_APP,      /**< Application key type. */
    MESH_KEY_TYPE_INVALID,  /**< Invalid key type. */
} mesh_key_type_t;

/**
 * @brief Mesh model config types
 */
typedef enum
{
    MESH_MODEL_CONFIG_TYPE_BINDING,     /**< Model binding config type. */
    MESH_MODEL_CONFIG_TYPE_PUBLISH,     /**< Model publish config type. */
    MESH_MODEL_CONFIG_TYPE_SUBSCRIBE,   /**< Model subscribe config type. */
} mesh_model_config_type_t;

/**
 * @brief Proxy state.
 */
typedef enum
{
    MESH_PROXY_STATE_DISABLED,       /**< Proxy feature supported and disabled. */
    MESH_PROXY_STATE_ENABLED,        /**< Proxy feature supported and enabled. */
    MESH_PROXY_STATE_NOT_SUPPORTED,  /**< Proxy feature not supported. */
} mesh_proxy_state_t;

/**
 * @brief Relay state.
 */
typedef enum
{
    MESH_RELAY_STATE_DISABLED,       /**< Relay feature supported and disabled. */
    MESH_RELAY_STATE_ENABLED,        /**< Relay feature supported and enabled. */
    MESH_RELAY_STATE_NOT_SUPPORTED,  /**< Relay feature not supported. */
} mesh_relay_state_t;

/**
 * @brief Beacon state.
 */
typedef enum
{
    MESH_BEACON_STATE_DISABLED,       /**< The secure network beacon is disabled. */
    MESH_BEACON_STATE_ENABLED,        /**< The secure network beacon is enabled. */
} mesh_beacon_state_t;

/**
 * @brief Mesh prov adv types
 */
typedef enum
{
    MESH_UNPROV_ADV,     /**< Unprov adv type.  */
    MESH_PB_GATT_ADV,    /**< PB_gatt adv type. */
    MESH_STATIC_ADV,     /**< Static adv type.  */
} mesh_adv_type_t;

/**
 * @brief Provisionee state.
 */
typedef enum
{
    MESH_PROVEE_STATE_UNPROV = 0x00,    /**< The node is not provisioned or provision failed. */
    MESH_PROVEE_STATE_BEING_PROV,       /**< The node is being provisioned. */
    MESH_PROVEE_STATE_PROV              /**< The node has been provisioned or provision successed. */
} mesh_provee_state_t;

/**
 * @brief Mesh address types
 */
typedef enum
{
    MESH_ADDR_TYPE_IDENTITY,     /**< Public or static address. */
    MESH_ADDR_TYPE_RPA,          /**< Rpa address.  */
    MESH_ADDR_TYPE_NON_RPA,      /**< Non rpa address. */
} mesh_addr_type_t;

/**
 * @brief Mesh prov info update types
 */
typedef enum
{
    MESH_PROV_INFO_UPD_TYPE_ADDR    = 1 << 0,     /**< Unicate address. */
    MESH_PROV_INFO_UPD_TYPE_DEV_KEY = 1 << 1,     /**< Device key. */
    MESH_PROV_INFO_UPD_TYPE_NET_KEY = 1 << 2,     /**< Net key. */
    MESH_PROV_INFO_UPD_TYPE_APP_KEY = 1 << 3,     /**< App key. */
} mesh_prov_info_upd_type_t;

/** @} */

/**@addtogroup MESH_COMMON_STRUCTURES Structures
 * @{ */

/**
 * @brief Mesh local identifier
 */
typedef uint8_t mesh_lid_t;

/**
 * @brief Timer callback type.
 */
typedef void (*mesh_timer_callback_t)(void *p_args);

/**
 * @brief Mesh init complete callback
 */
typedef void (*app_mesh_init_cmp_cb_t)(void);


/**
 * @brief Mesh provisioning parameter structure
 */
typedef struct
{
    uint8_t  dev_uuid[16];       /**< Unprovisioned device beacon information: Device UUID. */
    uint16_t oob_info;           /**< Unprovisioned device beacon information: OOB information,
                                      see @ref MESH_PROV_OOB_INFO_MASK. */
    uint32_t uri_hash;           /**< Unprovisioned device beacon information: URI hash. */
    bool     uri_hash_flag;      /**< Unprovisioned device beacon information:
                                      true, use URI hash;
                                      false, do not use URI hash, the uri_hash may not be set. */
    bool     pub_key_oob_flag;   /**< Provisioning capabilities information:
                                      true (public key OOB information is available);
                                      false (public key OOB information is not available). */
    bool     static_oob_flag;    /**< Provisioning capabilities information:
                                      true (Static OOB information is available);
                                      false (Static OOB information is not available). */
    uint8_t  output_oob_size;    /**< Provisioning capabilities information: maximum size of Output OOB supported.
                                      If the value is 0x00, the device does not support Output OOB;
                                      if the value is 0x01-0x08, the value represents the maximum size in octets supported by the device;
                                      if the value is 0x09-0xFF, the value is reserved for future use (the value is invalid now). */
    uint16_t output_oob_action;  /**< Provisioning capabilities information: supported Output OOB Actions,
                                      see @ref MESH_PROV_OUT_OOB_ACTION_MASK. */
    uint8_t  input_oob_size;     /**< Provisioning capabilities information: maximum size in octets of Input OOB supported.
                                      if the value is 0x00, the device does not support Input OOB;
                                      if the value is 0x01-0x08, the value represents the maximum size in octets supported by the device;
                                      if the value is 0x09-0xFF, the value is reserved for future use (the value is invalid now). */
    uint16_t input_oob_action;   /**< Provisioning capabilities information: supported Input OOB Actions,
                                      see @ref MESH_PROV_IN_OOB_ACTION_MASK. */
} mesh_prov_param_t;

/**
 * @brief Mesh network key indication structure
 */
typedef struct
{
    mesh_key_type_t key_type;        /**< Key type. */
    uint16_t netkey_index;           /**< Network key index. */
    bool added;                      /**< This network key is added or deleted. */
} mesh_netkey_ind_t;

/**
 * @brief Mesh application key indication structure
 */
typedef struct
{
    mesh_key_type_t key_type;         /**< Key type. */
    uint16_t appkey_index;            /**< Application key index. */
    uint16_t netkey_index;            /**< Network key index to which the application key is bound. */
    bool added;                       /**< This application key is added or deleted. */
} mesh_appkey_ind_t;

/**
 * @brief Mesh application/network key indication
 */
typedef union
{
    mesh_key_type_t key_type;        /**< Key type. */
    mesh_netkey_ind_t netkey_ind;    /**< Network key indication. */
    mesh_appkey_ind_t appkey_ind;    /**< Application key indication. */
} mesh_key_ind_t;

/**
 * @brief Mesh model binding indication structure
 */
typedef struct
{
    mesh_model_config_type_t model_config_type;     /**< Model config type. */
    mesh_lid_t model_lid;                           /**< Local identifier of a model. */
    uint16_t appkey_index;                          /**< Application key index. */
    bool bind;                                      /**< This model is binding or unbinding. */
} mesh_model_binding_ind_t;

/**
 * @brief Mesh model publish indication structure
 */
typedef struct
{
    mesh_model_config_type_t model_config_type;     /**< Model config type. */
    mesh_lid_t model_lid;                           /**< Local identifier of a model. */
    uint16_t publish_addr;                          /**< Model publish address. */
    mesh_lid_t virtual_addr_lid;                    /**< If the model publish address is a virtual address, this value represents the local identifier of the virtual address. */
} mesh_model_publish_ind_t;

/**
 * @brief Mesh model subscribe indication structure
 */
typedef struct
{
    mesh_model_config_type_t model_config_type;     /**< Model config type. */
    mesh_lid_t model_lid;                           /**< Local identifier of a model. */
    uint8_t subscribe_addr_nb;                      /**< The number of model subscribe addresses. */
    uint16_t *p_subscribe_addr_list;                /**< Model subscribe address list. */
} mesh_model_subscribe_ind_t;

/**
 * @brief Mesh model config indication structure
 */
typedef union
{
    mesh_model_config_type_t model_config_type;         /**< Model config type. */
    mesh_model_binding_ind_t model_binding_ind;         /**< Model binding indication. */
    mesh_model_publish_ind_t model_publish_ind;         /**< Model publish indication. */
    mesh_model_subscribe_ind_t model_subscribe_ind;     /**< Model subscribe indication. */
} mesh_model_config_ind_t;

/**
 * @brief Mesh specification version structure
 */
typedef struct
{
    uint8_t mesh_spec_version_major;    /**< Mesh specification version (major version number). */
    uint8_t mesh_spec_version_minor;    /**< Mesh specification version (minor version number). */
    uint8_t mesh_spec_version_revision; /**< Mesh specification version (revision version number). */
} mesh_spec_version_t;

/**
 * @brief Mesh SDK version structure
 */
typedef struct
{
    uint8_t mesh_sdk_version_major;     /**< Mesh SDK version (major version number). */
    uint8_t mesh_sdk_version_minor;     /**< Mesh SDK version (minor version number). */
    uint8_t mesh_sdk_version_revision;  /**< Mesh SDK version (revision version number). */
} mesh_sdk_version_t;

/**
 * @brief Mesh stack version structure
 */
typedef struct
{
    mesh_spec_version_t *p_spec_version; /**< Mesh specification version. */
    mesh_sdk_version_t  *p_sdk_version;  /**< Mesh SDK version. */
} mesh_stack_version_t;

/**
 * @brief Mesh Composition Data structure
 */
typedef struct
{
    uint16_t cid;      /**< 16-bit company identifier assigned by the Bluetooth SIG. */
    uint16_t pid;      /**< 16-bit vendor-assigned product identifier. */
    uint16_t vid;      /**< 16-bit vendor-assigned product version identifier. */
    uint16_t features; /**< For supported features of the device, see @ref MESH_MASK_SUPPORTED_FEATURE. */
} mesh_composition_data_t;

/**
 * @brief Mesh friend parameter structure
 */
typedef struct
{ 
    uint8_t friend_rx_window;      /**< Receive window in milliseconds when Friend feature is supported.
                                        The value range is 0x01-0xFF.*/ 
    uint8_t friend_queue_size;     /**< Queue size when Friend feature is supported. 
                                        The value range is 0x02-0xFF.*/ 
    uint8_t friend_subs_list_size; /**< Subscription list size when Friend feature is supported. 
                                        The value range is 0x01-0x0A.*/
} mesh_friend_param_t;

/**
 * @brief Mesh stack config structure
 */
typedef struct
{
    mesh_composition_data_t  *p_composition_data;                       /**< The pointer to mesh composition data. */
    const uint8_t            *p_dev_name;                               /**< The pointer to mesh device name. */
    uint16_t                 dev_name_len;                              /**< Length of the mesh device name. */
    uint8_t                  net_cache_size;                            /**< The size of the network message cache. */
    uint16_t                 net_replay_list_size;                      /**< The size of the Replay Protection list. */
    uint16_t                 net_seq_number_block_size;                 /**< The distance between the network sequence numbers, for every persistent storage write. */
    uint32_t                 net_seq_number_threshold_ivupdate;         /**< The sequence number value that triggers the start of an IV Update procedure. */
    uint8_t                  model_num_max;                             /**< Maximum number of models supported by the device. */
    uint8_t                  subs_list_size_max_per_model;              /**< Maximum subscription list size for a model instance. */
    uint8_t                  virt_addr_list_size_max;                   /**< Maximum virtual address list size supported by the device. */
    uint8_t                  appkey_model_bind_num_max;                 /**< Maximum number of bind between application key and model. */
    uint8_t                  proxy_connect_num_max;                     /**< Maximum number of the Proxy connection. */
    uint16_t                 proxy_filter_list_size_max_per_conn;       /**< Maximum size of the Proxy filter list for an active connection. */
    uint8_t                  friend_friendship_num_max;                 /**< Maximum number of Friendships the Friend node can supported. */
    mesh_friend_param_t      *p_friend_param;                           /**< The pointer to mesh friend parameter. */
    uint32_t                 unprov_adv_timeout;                        /**< The time of the Unprov_adv timeout(ms), 0 means no limited. */
    uint32_t                 pb_gatt_adv_timeout;                       /**< The time of the PB_gatt_adv timeout(ms), 0 means no limited. */
    uint32_t                 unprov_beacon_period_time;                 /**< The time of the unprov_adv beacon period(ms), 0 means using default config. */
    uint32_t                 unprov_beacon_duration_time;               /**< The time of the unprov_adv beacon duration(10 ms), 0 means using default config. */
    uint32_t                 static_adv_period_time;                    /**< The time of the static_adv period(ms), 0 means using default config. */
    uint32_t                 static_adv_duration_time;                  /**< The time of the static_adv duration(10 ms), 0 means using default config. */
} mesh_stack_config_t;

/**
 * @brief Mesh auto provsion information structure
 */
typedef struct mesh_auto_prov_info
{
    uint16_t unicast_addr;      /**< Unicast address. */
    uint8_t dev_key[16];        /**< Device key. */
    uint8_t net_key[16];        /**< Network key. */
    uint8_t app_key[16];        /**< Application key. */
} mesh_auto_prov_info_t;

/// Publication parameters structure
typedef struct mesh_model_config_public_param
{
    mesh_lid_t model_lid;     /**< Local identifier of a model. */
    uint16_t publish_addr;    /**< Publish address. */
    uint16_t appkey_index;    /**< Application key index. */
    uint8_t  friend_cred;     /**< Friendship credential flag. */
    uint8_t  ttl;             /**< Publish TTL. */
    uint8_t  period;          /**< Period for periodic status publishing. */
    uint8_t  retx_params;     /**< Retransmission parameters.  */
                              /**< Bit 0-2: Number of retransmissions for each message.  */
                              /**< Bit 0-2: Bit 3-7: Number of 50-ms steps between retransmissions.  */
} mesh_model_config_public_param_t;

/**
 * @brief Mesh timer structure
 */
typedef struct
{
    mesh_timer_callback_t callback;     /**< Callback function to be executed when the timer expires. */
    void *p_args;                       /**< Data pointer passed to the callback function. */
    uint32_t delay_ms;                  /**< Delay time before the timer expires; the minimum value is 3 (unit: ms). */
    uint32_t timer_id;                  /**< Timer identifier. */
    bool reload;                        /**< Set to true if the timer should be restarted automatically when it expired; otherwise set to false. */
} mesh_timer_t;

/**
 * @brief Mesh Profile Callback Structure
 */
typedef struct
{
    /**< Callback executed at the end of @ref mesh_enable. */
    void (*app_mesh_enabled_cb)(mesh_error_t status);

    /**< Callback used to inform application about provisioning state. */
    void (*app_mesh_prov_state_cb)(mesh_provee_state_t state, uint16_t prim_addr);

    /**< Callback used to request provisioning parameters to the application. */
    void (*app_mesh_prov_param_req_cb)(void);

    /**< Callback used to inform the application that the local public key is avaliable,
         and can be transmitted by specified OOB method in @ref mesh_prov_param_t::oob_info.
         The pointer p_pub_key_x points to the X Coordinate of public Key (32 bytes LSB).
         the pointer p_pub_key_y points to the Y Coordinate of public Key (32 bytes LSB).
         Note: this callback will be called if @ref mesh_prov_param_t::oob_info is not 0.
         after this callback, the space that p_pub_key_x/p_pub_key_y points to will be freed. */
    void (*app_mesh_prov_pub_key_ind_cb)(const uint8_t *p_pub_key_x, const uint8_t *p_pub_key_y);

    /**< Callback used to request out of band authentication data.
         If pub_key_oob_flag is true, the provisioner chooses public key OOB method.
         If auth_method is MESH_PROV_AUTH_NO_OOB, the auth_action and auth_size are 0.
         If auth_method is MESH_PROV_AUTH_STATIC_OOB, the auth_action is 0 and auth_size is 16.
         If auth_method is MESH_PROV_AUTH_OUTPUT_OOB, the auth_action type is @ref mesh_prov_output_oob_action_t.
         If auth_method is MESH_PROV_AUTH_INPUT_OOB, the auth_action type is @ref mesh_prov_input_oob_action_t. */
    void (*app_mesh_prov_oob_auth_req_cb)(bool pub_key_oob_flag, mesh_prov_auth_method_t auth_method, uint16_t auth_action, uint8_t auth_size);

    /**< Callback used to inform application about start/end of attention timer. */
    void (*app_mesh_attention_cb)(uint8_t attention_state);

    /**< Callback used to inform application about received node reset request. */
    void (*app_mesh_node_reset_cb)(void);

    /**< Callback used to inform application about application/network key added or deleted. */
    void (*app_mesh_key_ind_cb)(const mesh_key_ind_t *p_key_ind);

    /**< Callback used to inform application about changed model config. */
    void (*app_mesh_model_config_ind_cb)(const mesh_model_config_ind_t *p_model_config_ind);

    /**< Callback used to inform application prov adv timeout. */
    void (*app_mesh_adv_timeout_cb)(mesh_adv_type_t adv_type);

    /**< Callback used to inform application about gateway offline. */
    void (*app_mesh_gateway_offline_cb)(void);

} app_mesh_common_cb_t;

/**
 * @brief Callback Structure of Health Model for primary element
 */
typedef struct
{
    /**< Callback used to request list of faults for primary element. */
    void (*app_mesh_fault_get_cb)(uint16_t comp_id);

    /**< Callback used to request test of faults for primary element. */
    void (*app_mesh_fault_test_cb)(uint16_t comp_id, uint8_t test_id, bool cfm_needed);

    /**< Callback used to inform application that fault status for primary element must be cleared. */
    void (*app_mesh_fault_clear_cb)(uint16_t comp_id);

    /**< Callback used to inform application that fault period for primary element has been updated. */
    void (*app_mesh_fault_period_cb)(uint32_t period_ms, uint32_t period_fault_ms);

} app_mesh_health_cb_t;

/**
 * @brief Callback Structure of LPN and Friend feature
 */
typedef struct
{
    /**< Callback used to inform application of friendship update as low power node. */
    void (*app_mesh_lpn_status_cb)(mesh_error_t status, uint16_t friend_addr);

    /**< Callback used to inform application about receiving a Friend Offer message. */
    void (*app_mesh_lpn_offer_cb)(uint16_t friend_addr, uint8_t rx_window,
        uint8_t queue_size, uint8_t subs_list_size, int8_t rssi);

    /**< Callback used to inform application that the messages in friend queue have been obtained. */
    void (*app_mesh_lpn_poll_done_cb)(void);

    /**< Callback used to inform application about friend event as friend node. */
    void (*app_mesh_friend_status_cb)(mesh_friend_event_t evt, uint16_t lpn_addr, mesh_lid_t lpn_lid);

} app_mesh_lpn_friend_cb_t;

/**
 * @brief Mesh Callback Structure
 */
typedef struct
{
    /**< Callback used to inform application that the mesh stack initiation completes. */
    app_mesh_init_cmp_cb_t     app_mesh_init_cmp_callback;

    /**< The pointer to mesh common callback. */
    app_mesh_common_cb_t       *app_mesh_common_callback;

    /**< The pointer to mesh health callback. */
    app_mesh_health_cb_t       *app_mesh_health_callback;

    /**< The pointer to mesh low power node and friend callback. */
    app_mesh_lpn_friend_cb_t   *app_mesh_lpn_friend_callback;

} mesh_callback_t;

/** @} */


/*
 * FUNCTIONS DEFINITION FOR MESH PROFILE
 ****************************************************************************************
 */

/** @addtogroup MESH_COMMON_FUNCTION Functions
 * @{ */

/**
 ****************************************************************************************
 * @brief Mesh stack initiation
 *
 * @note Function callback @ref mesh_callback_t::app_mesh_init_cmp_callback will be called when mesh stack initiation completes.
 *       This function does not take effect if the number of added profiles has reached the maximum value.
 *       The space input parameters point to should not be released by the user after this function is called.
 *
 * @param[in] p_stack_config       Pointer to the initial config.
 * @param[in] p_mesh_callback      Pointer to the structure of application callbacks.
 *
 * @retval ::MESH_ERROR_NO_ERROR           Operation is successful.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM  Invalid parameter. The config is invalid.
 * @retval ::MESH_ERROR_SDK_INSUFFICIENT   Insufficient resources. Cannot add the mesh profile.
 ****************************************************************************************
 */
mesh_error_t mesh_stack_init(mesh_stack_config_t *p_stack_config, mesh_callback_t *p_mesh_callback);

/**
 ****************************************************************************************
 * @brief Mesh auto provision information set.
 *
 * @param[in] p_auto_prov_info      Pointer to the auto provison information.
 *
 * @retval ::MESH_ERROR_NO_ERROR           Operation is successful.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM  Invalid parameter. The parameter p_auto_prov_info is NULL.
 ****************************************************************************************
 */
mesh_error_t mesh_auto_prov_info_set(mesh_auto_prov_info_t *p_auto_prov_info);

/**
 ****************************************************************************************
 * @brief Mesh auto provision information get.
 *
 * @param[out] p_auto_prov_info      Pointer to the auto provison information.
 *
 * @retval ::MESH_ERROR_NO_ERROR           Operation is successful.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM  Invalid parameter. The parameter p_auto_prov_info is NULL.
 ****************************************************************************************
 */
mesh_error_t mesh_auto_prov_info_get(mesh_auto_prov_info_t *p_auto_prov_info);

/**
 ****************************************************************************************
 * @brief Mesh provision information update.
 *
 * @param[in] p_prov_info_upd      Pointer to the provison information updated.
 * @param[in] upd_type             Update type info, @ref mesh_prov_info_upd_type_t.
 *
 * @retval ::MESH_ERROR_NO_ERROR           Operation is successful.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM  Invalid parameter. The parameter p_prov_info_upd is NULL.
 ****************************************************************************************
 */
mesh_error_t mesh_prov_info_update(mesh_auto_prov_info_t *p_prov_info_upd, uint16_t upd_type);

/**
 ****************************************************************************************
 * @brief Mesh stack reset
 *
 * @note This function may clear stored mesh information. Callback function will be called when mesh stack reset completes.
 *
 * @param[in] flash_clear      Set to true if the flash should be cleared, otherwise set to false.
 *
 * @retval ::MESH_ERROR_NO_ERROR           Operation is successful.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM  Invalid parameter. The parameter p_reset_cb is NULL.
 ****************************************************************************************
 */
mesh_error_t mesh_stack_reset(bool flash_clear);

/**
 ****************************************************************************************
 * @brief Enable Mesh profile.
 *
 * @note Function callback @ref app_mesh_common_cb_t::app_mesh_enabled_cb will be called after enablation completes.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is successful.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command is disallowed.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES  Insufficient resources.
 *
 ****************************************************************************************
 */
mesh_error_t mesh_enable(void);

/**
 ****************************************************************************************
 * @brief Set mesh address type, default is MESH_ADDR_TYPE_IDENTITY.
 ****************************************************************************************
 */
void mesh_addr_type_set(mesh_addr_type_t addr_type);

/**
 ****************************************************************************************
 * @brief Provide provisioning parameters for the provisioning module.
 *
 * @param[in] p_param           Pointer to the provisioning parameters.
 *
 * @retval ::MESH_ERROR_NO_ERROR            Operation is successful.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM   Invalid parameter. The parameter p_param is NULL;
 *                                          Input/Output OOB authentication parameters are invalid;
 *                                          public key OOB parameters are invalid;
 *                                          no need to provide provisioning parameters currently.
 *
 ****************************************************************************************
 */
mesh_error_t mesh_prov_param_rsp(mesh_prov_param_t *p_param);

 
/**
 ****************************************************************************************
 * @brief Provide authentication data for the provisioning module.
 *
 * @note If choosed auth method is MESH_PROV_AUTH_NO_OOB, the parameter p_auth_data can be NULL and auth_size is 0.
 *       If choosed auth method is MESH_PROV_AUTH_STATIC_OOB, the parameter auth_size must be 16.
 *       If choosed auth method is MESH_PROV_AUTH_OUTPUT_OOB, the parameter auth_size must be the same as the parameter auth_size in @ref app_mesh_common_cb_t::app_mesh_prov_oob_auth_req_cb.
 *       If choosed auth method is MESH_PROV_AUTH_INPUT_OOB, the parameter auth_size must be the same as the parameter auth_size in @ref app_mesh_common_cb_t::app_mesh_prov_oob_auth_req_cb.
 *
 * @param[in] accept            True: pairing request accepted; false: pairing request rejected.
 * @param[in] p_auth_data       Pointer to the authentication data (LSB for a number or array of bytes).
 * @param[in] auth_size         Authentication data size (Note: it should be equal to the requested auth size; otherwise, pairing will be rejected automatically).
 *
 ****************************************************************************************
 */
void mesh_prov_oob_auth_rsp(bool accept, const uint8_t* p_auth_data, uint8_t auth_size);

/**
 ****************************************************************************************
 * @brief Start or stop connectable advertising with node identity.
 *
 * @note If the user wants to start connectable advertising with node identity while connectable advertising with network ID is ongoing,
 *       the current advertising will be stopped and the connectable advertising with node identity will be started.
 *       The connectable advertising with node identity lasts for 60 seconds. 
 *       When connectable advertising with node identity is stopped while Proxy feature is enabled, 
 *       the connectable advertising with network ID will be started.
 *       
 * @param[in] enable      Start or stop advertising.
 *
 * @retval ::MESH_ERROR_NO_ERROR            Operation is successful.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED  Command is disallowed.
 * @retval ::MESH_ERROR_INVALID_NETKEY_ID   Invalid network key index.
 * @retval ::MESH_ERROR_BUSY                Requested resource is busy.
 *
 ****************************************************************************************
 */
mesh_error_t mesh_node_identity_adv_enable(bool enable);

/**
 ****************************************************************************************
 * @brief Get Proxy state.
 *
 * @return  Return Proxy state.
 ****************************************************************************************
 */
mesh_proxy_state_t mesh_proxy_state_get(void);

/**
 ****************************************************************************************
 * @brief Enable or disable Proxy feature.
 *
 * @note In the following cases, this function does not take effect:
 *       (1) This node does not support Proxy feature;
 *       (2) This node supports Proxy feature which is enabled, and the user wants to enable it again;
 *       (3) This node supports Proxy feature which is disabled, and the user wants to disable it again.
 *       If the Proxy feature is enabled, the connectable advertising with network ID will be started.
 *       Configuration Client may enable/disable this Proxy feature.
 *
 * @param[in] enable     Set true/false to enable/disable Proxy feature.
 *
 ****************************************************************************************
 */
void mesh_proxy_state_set(bool enable);

/**
 ****************************************************************************************
 * @brief Get relay state.
 *
 * @return  Return relay state.
 ****************************************************************************************
 */
mesh_relay_state_t mesh_relay_state_get(void);

/**
 ****************************************************************************************
 * @brief Enable or disable relay feature.
 *
 * @note In the following cases, this function does not take effect:
 *       (1) This node does not support relay feature;
 *       (2) This node supports relay feature which is enabled, and the user wants to enable it again;
 *       (3) This node supports relay feature which is disabled, and the user wants to disable it again.
 *       Configuration Client may enable/disable this relay feature.
 *
 * @param[in] enable     Set true/false to enable/disable relay feature.
 *
 ****************************************************************************************
 */
void mesh_relay_state_set(bool enable);

/**
 ****************************************************************************************
 * @brief Get secure network beacon state.
 *
 * @return  Return secure network beacon state.
 ****************************************************************************************
 */
mesh_beacon_state_t mesh_sec_beacon_state_get(void);

/**
 ****************************************************************************************
 * @brief Enable or disable secure network beacon.
 *
 * @note In the following cases, this function does not take effect:
 *       (1) The secure network beacon is enabled, and the user wants to enable it again;
 *       (2) The secure network beacon is disabled, and the user wants to disable it again.
 *       Configuration Client may enable/disable this secure network beacon.
 *
 * @param[in] enable     Set true/false to enable/disable secure network beacon.
 *
 ****************************************************************************************
 */
void mesh_sec_beacon_state_set(bool enable);

/**
 ****************************************************************************************
 * @brief Provide fault status for primary element.
 *
 * @param[in] comp_id           Company ID.
 * @param[in] test_id           Test ID.
 * @param[in] length            Length of fault array.
 * @param[in] p_fault_array     Pointer to the fault array.
 *
 ****************************************************************************************
 */
void mesh_health_status_send(uint16_t comp_id, uint8_t test_id, uint8_t length, uint8_t *p_fault_array);

/**
 ****************************************************************************************
 * @brief Provide fault status for primary element.
 *
 * @param[in] accept            True: request accepted; false: request rejected.
 * @param[in] comp_id           Company ID.
 * @param[in] test_id           Test ID.
 * @param[in] length            Length of fault array.
 * @param[in] p_fault_array     Pointer to the fault array.
 *
 ****************************************************************************************
 */
void mesh_health_cfm(bool accept, uint16_t comp_id, uint8_t test_id, uint8_t length, uint8_t *p_fault_array);

/**
 ****************************************************************************************
 * @brief Enable or disable IV Update test mode.
 *
 * @param[in] enable      Enable or disable IV Update test mode.
 *
 ****************************************************************************************
 */
void mesh_ivupdate_test_mode(bool enable);

/**
 ****************************************************************************************
 * @brief Get device run time.
 *
 * @param[out] p_clock_ms      Pointer to a variable that contains the current clock in milliseconds.
 * @param[out] p_nb_wrap       Pointer to a variable that contains the number of wraps.
 *
 ****************************************************************************************
 */
void mesh_run_time_get(uint32_t *p_clock_ms, uint16_t *p_nb_wrap);
 
/**
 ****************************************************************************************
 * @brief Set device run time.
 *
 * @param[in] clock_ms       Current clock in milliseconds.
 * @param[in] nb_wrap        Number of wraps.
 *
 ****************************************************************************************
 */
void mesh_run_time_set(uint32_t clock_ms, uint16_t nb_wrap);

/**
 ****************************************************************************************
 * @brief Get Mesh Stack version.
 *
 * @note If p_spec_version (see @ref mesh_stack_version_t::p_spec_version) is NULL, the mesh specification version cannot be obtained;
 *       if p_sdk_version (see @ref mesh_stack_version_t::p_sdk_version) is NULL, the mesh SDK version cannot be obtained.
 *
 * @param[out] p_version_number       Pointer to structure in which version information will be provided. Do not set it to NULL.
 *
 ****************************************************************************************
 */
void mesh_version_get(mesh_stack_version_t *p_version_number);

/**
 ****************************************************************************************
 * @brief Set and start a timer.
 * @param[in, out]  p_mesh_tk_timer     Pointer to a new allocated mesh timer.
 *
 * @retval ::MESH_ERROR_NO_ERROR            Operation is successful.
 * @retval ::MESH_ERROR_TIMER_INVALID_PARAM Invalid parameter.
 * @retval ::MESH_ERROR_TIMER_INSUFFICIENT  Timer is insufficient.
 *
 * @note
 * If this function fails, the timer_id (@ref mesh_timer_t::timer_id) will be set to 0xFFFFFFFF.
 * The space the p_mesh_tk_timer points to cannot be released when the timer is alive because the timer_id (@ref mesh_timer_t::timer_id)
 * is set to 0xFFFFFFFF when the timer expires.
 *
 ****************************************************************************************
 */
mesh_error_t mesh_timer_set(mesh_timer_t *p_mesh_tk_timer);

/**
 ****************************************************************************************
 * @brief Remove an alive timer.
 * @param[in, out]  p_timer_id     Pointer to timer identifier.
 *
 * @retval ::MESH_ERROR_NO_ERROR            Operation is successful.
 * @retval ::MESH_ERROR_TIMER_INVALID_PARAM Invalid parameter.
 *
 * @note
 * If the parameter p_timer_id is NULL or the timer identifier p_timer_id points to is invalid, this function will fail.
 * If this function succeeds, the timer identifier p_timer_id points to will be 0xFFFFFFFF. 
 * The pointer p_timer_id is recommended to point to the timer_id (@ref mesh_timer_t::timer_id).
 *
 ****************************************************************************************
 */
mesh_error_t mesh_timer_clear(uint32_t *p_timer_id);

/**
 ****************************************************************************************
 * @brief Get mesh primary address.
 *
 * @return uint16 Mesh primary address.
 *
 ****************************************************************************************
 */
uint16_t mesh_get_prim_addr(void);

/**
 ****************************************************************************************
 * @brief Get provisionee state.
 *
 * @return  Return provisionee state.
 ****************************************************************************************
 */
mesh_provee_state_t mesh_provisionee_state_get(void);

/**
 ****************************************************************************************
 * @brief Start unprov_adv, static_adv or pb_gatt_adv.
 *
 * @param[in] adv_type        Mesh adv type.
 *
 ****************************************************************************************
 */
mesh_error_t mesh_start_prov_adv(mesh_adv_type_t adv_type);

/**
 ****************************************************************************************
 * @brief Stop unprov_adv, static_adv or pb_gatt_adv.
 *
 * @param[in] adv_type        Mesh adv type.
 *
 ****************************************************************************************
 */
mesh_error_t mesh_stop_prov_adv(mesh_adv_type_t adv_type);

/**
 ****************************************************************************************
 * @brief Set mesh static_adv_data.
 *
 * @param[in] p_dev_uuid       Pointer to the device uuid.
 * @param[in] oob_info         Device oob info.
 *
 ****************************************************************************************
 */
mesh_error_t mesh_static_adv_data_set(uint8_t *p_dev_uuid, uint16_t oob_info);

/**
 ****************************************************************************************
 * @brief Start scan by user.
 *
 ****************************************************************************************
 */
mesh_error_t mesh_scan_start_by_user(void);

/**
 ****************************************************************************************
 * @brief Stop scan by user.
 *
 ****************************************************************************************
 */
mesh_error_t mesh_scan_stop_by_user(void);

/**
 ****************************************************************************************
 * @brief Enable or disable heartbeat subscription.
 *
 * @param[in] enable: Set true/false to enable/disable heartbeat subscription.
 *
 ****************************************************************************************
 */
void mesh_hb_subs_set(bool enable);

/**
 ****************************************************************************************
 * @brief Enable or disable heartbeat publication.
 *
 * @param[in] enable: Set true/false to enable/disable heartbeat publication.
 *
 ****************************************************************************************
 */
void mesh_hb_pub_set(bool enable);

/**
 ****************************************************************************************
 * @brief set network transmit param.
 *
 * @param[in] net_tx_count:     Set network transmit count(range:1~8).
 * @param[in] net_tx_intv:      Set network transmit interval(unit:10ms; range:1~32).
 *
 ****************************************************************************************
 */
void mesh_net_tx_param_set(uint8_t net_tx_count, uint8_t net_tx_intv);

/**
 ****************************************************************************************
 * @brief set relay transmit param.
 *
 * @param[in] relay_tx_count:     Set relay transmit count(range:1~8).
 * @param[in] relay_tx_intv:      Set relay transmit interval(unit:10ms; range:1~32).
 *
 ****************************************************************************************
 */
void mesh_relay_tx_param_set(uint8_t relay_tx_count, uint8_t relay_tx_intv);

/** @} */

#endif /* MESH_COMMON_ */
/** @} */
/** @} */
