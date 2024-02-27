/**
 ****************************************************************************************
 *
 * @file mesh_model.h
 *
 * @brief Header file for Mesh Model Programming Interface
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
#ifndef __MESH_MODEL_H__
#define __MESH_MODEL_H__


/**
 ****************************************************************************************
 * @addtogroup MESH_MODEL Mesh Model
 * @{
 * @brief  Mesh Model Programming Interface
 ****************************************************************************************
 */
/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "mesh_common.h"
#include "mesh_sdk_error.h"

/** @addtogroup MESH_MODEL_DEFINES Defines
 * @{ */

/** @defgroup MESH_ACCESS_OPCODE Mesh Access Layer Opcode
 * @{ */ 
#define MESH_ACCESS_COMPANY_ID_NONE   (0xFFFF)                                                                      /**< Company ID value for Bluetooth SIG opcodes or models. */

#define MESH_ACCESS_OPCODE_VENDOR(company_opcode, company_id)  { (company_opcode), (company_id) }                   /**< Define a vendor model opcode. */

#define MESH_ACCESS_OPCODE_SIG(company_opcode)                 { (company_opcode), (MESH_ACCESS_COMPANY_ID_NONE) }  /**< Define an SIG model opcode. */
/** @} */

/** @defgroup MESH_MODEL_ID Mesh Model Identifier
 * @{ */ 
#define MESH_MODEL_VENDOR(company_model_id, company_id)  { (company_model_id), (company_id) }                       /**< Define a vendor model identifier. */

#define MESH_MODEL_SIG(company_model_id)                 { (company_model_id), (MESH_ACCESS_COMPANY_ID_NONE) }      /**< Define an SIG model identifier. */
/** @} */

/** @} */


/** @addtogroup MESH_MODEL_ENUMERATIONS Enumerations
 * @{ */
/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/**
 * @brief Reliable message transfer status codes of a mesh model
 */
typedef enum
{
    MESH_MODEL_RELIABLE_TRANS_SUCCESS,       /**< The reliable transfer completed successfully. */
    MESH_MODEL_RELIABLE_TRANS_TIMEOUT,       /**< The reliable transfer has timed out. */
    MESH_MODEL_RELIABLE_TRANS_CANCELLED,     /**< The reliable transfer has been cancelled. */
} mesh_model_reliable_trans_status_t;

/** @} */

/**@addtogroup MESH_MODEL_STRUCTURES Structures
 * @{ */
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/**
 * @brief Mesh access layer opcode
 */
typedef struct
{
    uint16_t company_opcode; /**< 2-octet (14-bit) or 1-octet (7-bit) Bluetooth SIG defined opcode or 1-octet (6-bit) vendor specific opcode. */
    uint16_t company_id;     /**< Company ID. Set to @ref MESH_ACCESS_COMPANY_ID_NONE if it is a Bluetooth SIG defined opcode. */
} mesh_access_opcode_t;

/**
 * @brief Mesh model identifier
 */
typedef struct
{
    uint16_t company_model_id; /**< Bluetooth SIG defined or vendor specific model identifier. */
    uint16_t company_id;       /**< Company ID. Set to @ref MESH_ACCESS_COMPANY_ID_NONE if it is a Bluetooth SIG defined model identifier. */
} mesh_model_id_t;

/**
* @brief Inform about new publish period of a model
*/
typedef struct
{
    mesh_lid_t model_lid;      /**< Local identifier of a model. */
    uint16_t   addr;           /**< Model publish address. */
    uint32_t   period_ms;      /**< Publish period in milliseconds. */
} mesh_model_publish_period_ind_t;             


/**
 * @brief Inform about transmission status of a message issued by a mesh model
 */

typedef struct
{
    mesh_lid_t model_lid;      /**< Local identifier of a model. */ 
    uint8_t    tx_hdl;         /**< Handle value configured by a model when a message has been requested to be sent. */                        
    uint16_t   status;         /**< Transmission status. */
} mesh_model_msg_sent_ind_t;


/**
 * @brief Inform about receiving a specific mesh message
 */
typedef struct
{
    mesh_lid_t           model_lid;     /**< Local identifier of a model. */
    mesh_access_opcode_t opcode;        /**< Mesh message operation code (can be 1-octet, 2-octet, or 3-octet operation code). */
    uint16_t             src;           /**< Source address of the message (required for a response). */
    uint16_t             appkey_index;  /**< Application key index. */
    uint16_t             netkey_index;  /**< Network key index. */
    int8_t               rssi;          /**< Measured RSSI level for the received PDU. */
    uint8_t              hop;           /**< TTL info for the received PDU. */
    uint16_t             msg_len;       /**< Message length. */
    uint8_t              msg[];         /**< Message content. */
} mesh_model_msg_ind_t;

/**
 * @brief Definition of callback function to call upon receiving a PDU for a specific mesh model.
 *
 * @param[in] p_model_msg    Pointer to the model message information.
 */
typedef void (*mesh_model_rx_cb)(mesh_model_msg_ind_t *p_model_msg, void *p_args);

/**
 * @brief Definition of callback function to call upon receiving a new publish period value.
 *
 * @param[in] p_ind    Pointer to the new publish period information.
 */
typedef void (*mesh_model_publish_period_cb)(mesh_model_publish_period_ind_t *p_ind, void *p_args);

/**
 * @brief Definition of callback function to call when PDU has been sent.
 *
 * @param[in] p_ind    Pointer to the transmission status information.
 */
typedef void (*mesh_model_sent_cb)(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);

/**
 * @brief Definition of callback function to call when the reliable message transfer completes.
 *
 * @param[in] p_args       Points to the generic argument, as @ref mesh_model_register_info_t::p_args points to.
 * @param[in] status       Model reliable message transfer status codes. 
 */
typedef void (*mesh_model_reliable_trans_cb_t)(void * p_args, mesh_model_reliable_trans_status_t status);

/**
 * @brief Mesh model callback
 */
typedef struct
{ 
    mesh_model_rx_cb             cb_rx;              /**< receiving a message for a model. */ 
    mesh_model_sent_cb           cb_sent;            /**< Callback executed when a PDU is properly sent. */
    mesh_model_publish_period_cb cb_publish_period;  /**< Callback function called when a new publish period is received. */
} mesh_model_cb_t;

/**
 * @brief Mesh model response & publish send information
 */
typedef struct
{ 
    mesh_lid_t           model_lid;        /**< Local identifier of a model. */ 
    mesh_access_opcode_t opcode;           /**< Mesh message operation code (can be 1-octet, 2-octet, or 3-octet operation code). */
    uint8_t              tx_hdl;           /**< Handle value used by a model to retrieve which message has been sent. */
    uint8_t              *p_data_send;     /**< Pointer to the buffer that contains a message to be published. */
    uint16_t             data_send_len;    /**< The buffer length. */
    uint16_t             dst;              /**< Unicast destination address of the message (source address parameter of the received request message). */
    uint16_t             appkey_index;     /**< Application key index. */
} mesh_model_send_info_t;

/**
 * @brief Reliable message transfer information of a mesh model
 */
typedef struct
{
    mesh_access_opcode_t reply_opcode;          /**< Opcode of the expected reply message. */ 
    mesh_model_reliable_trans_cb_t status_cb;   /**< Pointer to the callback function that will be called when reliable message transfer completes. */ 
    uint32_t timeout_ms;                        /**< The longest duration of a reliable message transfer procedure of a mesh model. */ 
} mesh_model_reliable_info_t;

/**
 * @brief Mesh model register information
 */
typedef struct
{
    mesh_model_id_t       model_id;       /**< Model identifier.*/
    uint8_t               element_offset; /**< Element address offset from primary element address. 
                                               Indicate which element the model is registered for.*/ 
    bool                  publish;        /**< Indicate whether the model is a publish model (true) or not (false).*/
    uint16_t              *p_opcodes;     /**< Pointer to company opcodes.*/
    uint16_t              num_opcodes;    /**< Number of company opcodes.*/
    const mesh_model_cb_t *p_cb;          /**< Pointer to callback functions defined by the model.*/
    void                  *p_args;        /**< This pointer will be supplied as an argument in the callback @ref mesh_model_cb_t.*/
} mesh_model_register_info_t;

/**
 * @brief Definition of callback function to call when a model message has been received.
 *
 * @param[in] p_rx_msg    Pointer to the received message information.
 * @param[in] p_args      Data pointer passed to the callback function.
 */
typedef void (*mesh_opcode_handler_cb_t)(const mesh_model_msg_ind_t *p_rx_msg, void *p_args);

/**
 * @brief Mesh model opcode handler
 */
typedef struct
{
    uint16_t                   opcode;  /**< The model opcode. */
    mesh_opcode_handler_cb_t   handler; /**< The opcode message handler callback for the given opcode. */
} mesh_opcode_handler_t;

/** @} */


/** @addtogroup MESH_MODEL_FUNCTION Functions
 * @{ */
 
/**
 ****************************************************************************************
 * @brief Let the model publish a message over mesh network.
 *
 * @note Message status will be reported with the model callback (@ref mesh_model_cb_t::cb_sent).
 *       There is no need to set the parameters @ref mesh_model_send_info_t::dst and @ref mesh_model_send_info_t::appkey_index.
 *       If a reliable message transfer procedure is not required by the user, the parameter p_reliable_info must be NULL.
 *
 * @param[in] p_publish_info      Pointer to the publish information.
 * @param[in] p_reliable_info     Pointer to the reliable message transfer information.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is successful.
 * @retval ::MESH_ERROR_INVALID_PARAM             Invalid parameter.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES    Insufficient resources.
 * @retval ::MESH_ERROR_INVALID_MODEL             Invalid model.
 * @retval ::MESH_ERROR_INVALID_PUBLISH_PARAMS    Invalid publish parameters.
 * @retval ::MESH_ERROR_INVALID_BINDING           Invalid binding.
 * @retval ::MESH_ERROR_INVALID_APPKEY_ID         Invalid application key index.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED        Command is disallowed.
 * @retval ::MESH_ERROR_NOT_FOUND                 Requested resource not found.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_ON     Reliable message transfer procedure is on.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 *                                                The parameter p_publish_info is NULL or the opcode (@ref mesh_model_send_info_t::opcode) is invalid.
 *                                                The user wants to create a reliable message transfer procedure, but the parameter status_cb (@ref mesh_model_reliable_info_t::status_cb) is NULL.
 ****************************************************************************************
 */
mesh_error_t mesh_model_publish(mesh_model_send_info_t* p_publish_info, mesh_model_reliable_info_t *p_reliable_info);

/**
 ****************************************************************************************
 * @brief Let the model reply a message over mesh network.
 *
 * @note Message status will be reported with the model callback (@ref mesh_model_cb_t::cb_sent).
 *
 * @param[in] p_rsp_info      Pointer to the response information.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is successful.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES    Insufficient resources.
 * @retval ::MESH_ERROR_INVALID_PARAM             Invalid parameter.
 * @retval ::MESH_ERROR_INVALID_ADDR              Invalid address.
 * @retval ::MESH_ERROR_INVALID_MODEL             Invalid model.
 * @retval ::MESH_ERROR_INVALID_BINDING           Invalid binding.
 * @retval ::MESH_ERROR_INVALID_APPKEY_ID         Invalid application key index.
 * @retval ::MESH_ERROR_NOT_FOUND                 Requested resource not found.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED        Command is disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 *                                                The parameter p_rsp_info is NULL or the opcode (@ref mesh_model_send_info_t::opcode) is invalid.
 ****************************************************************************************
 */
mesh_error_t mesh_model_rsp_send(mesh_model_send_info_t* p_rsp_info);


/**
 ****************************************************************************************
 * @brief Register a model in one element.
 *
 * @param[in]  p_register_info      Pointer to the model's registration information.
 * @param[out] p_model_lid          Pointer to the variable that contains the allocated local identifier of the model.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is successful.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED        Command is disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 *                                                The parameter p_register_info/p_model_lid is NULL or the p_opcodes (@ref mesh_model_register_info_t::p_opcodes) is NULL
 *                                                or the p_cb (@ref mesh_model_register_info_t::p_cb) is NULL.
 ****************************************************************************************
 */
mesh_error_t mesh_model_register(mesh_model_register_info_t* p_register_info, mesh_lid_t *p_model_lid);

/**
 ****************************************************************************************
 * @brief Check whether the reliable message transfer procedure of a mesh model is ongoing.
 *
 * @param[in]  model_lid   Local identifier of a model.
 * @param[out] p_state     Pointer to the variable that contains the transfer state. 
 *
 * @note If this function operation is successfull, the user can get transfer state from the parameter p_state.
 *       If the variable p_state points to is true, the reliable message transfer procedure is on, otherwise is off.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is successful.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 *                                                The parameter model_lid is invalid or p_state is NULL.
 ****************************************************************************************
 */
mesh_error_t mesh_model_reliable_trans_is_on(mesh_lid_t model_lid, bool *p_state);

/**
 ****************************************************************************************
 * @brief Cancel the reliable message transfer procedure of a mesh model.
 *
 * @param[in]  model_lid        Local identifier of a model.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is successful.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_OFF    Reliable message transfer procedure is off.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter. The parameter model_lid is invalid.
 ****************************************************************************************
 */
mesh_error_t mesh_model_reliable_trans_cancel(mesh_lid_t model_lid);

/**
 ****************************************************************************************
 * @brief Config mesh model binding or subscribe information by application.
 *
 * @note only support to operate the binding and  subscribe information.
 *
 * @param[in] p_model_config       Pointer to the config struct.
 *
 * @retval ::MESH_ERROR_NO_ERROR           Operation is successful.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM  Invalid parameter. The config is invalid.
 * @retval ::MESH_ERROR_SDK_INSUFFICIENT   Insufficient resources. Cannot add the mesh profile.
 ****************************************************************************************
 */
 uint16_t mesh_model_config_model_info(const mesh_model_config_ind_t *p_model_config);

/**
 ****************************************************************************************
 * @brief Config mesh model Model Publication parameter.
 *
 * @note the parameter is default value, if Provisioner sent Message:Config Config Model Publication Set, the default value will invalid.
 *
 * @param[in] p_msg       Pointer to the config struct.
 *
 * @retval ::MESH_ERROR_NO_ERROR           Operation is successful.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM  Invalid parameter. The config is invalid.
 * @retval ::MESH_ERROR_SDK_INSUFFICIENT   Insufficient resources. Cannot add the mesh profile.
 ****************************************************************************************
 */
uint16_t mesh_model_config_public_param(const mesh_model_config_public_param_t *p_msg);

/** @} */ 
#endif /* _MESH_MODEL_ */

/** @} */
/** @} */
