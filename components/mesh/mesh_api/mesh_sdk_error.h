/**
 ****************************************************************************************
 *
 * @file mesh_sdk_error.h
 *
 * @brief File that contains error codes
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

/**
 ****************************************************************************************
 * @addtogroup MESH_ERROR_CODE  Mesh Error Code
 * @{
 * @brief  Mesh API Error Code
 ****************************************************************************************
 */
#ifndef __MESH_SDK_ERROR_H__
#define __MESH_SDK_ERROR_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */


/** @addtogroup MESH_ERROR_CODE_DEFINES Defines
 * @{ */
 

/*
 * DEFINES
 ****************************************************************************************
 */

#define MESH_ERROR_PROTOCOL_CODE     (0x0080)                                   /**< Mesh Error Protocol Group Code. */
#define MESH_ERROR_PROVISIONING_CODE (0x0081)                                   /**< Mesh Error Provisioning Group Code. */
#define MESH_ERROR_INTERNAL_CODE     (0x0082)                                   /**< Mesh Error Internal Group Code. */
#define MESH_ERROR_LPN_CODE          (0x0083)                                   /**< Mesh Error Low Power Node Group Code. */
#define MESH_ERROR_MODEL_CODE        (0x0084)                                   /**< Mesh Error Model Group Code. */
#define MESH_ERROR_TIMER_CODE        (0x0085)                                   /**< Mesh Error Common Timer Group Code. */
#define MESH_ERROR_SDK_CODE          (0x0086)                                   /**< Mesh Error SDK Group Code. */

#define MESH_ERROR(grp, suberror) ((MESH_ERROR_##grp##_CODE) | (suberror << 8)) /**< Mesh Error Codes. */

/** @} */


/** @addtogroup MESH_ERROR_CODE_ENUMERATIONS Enumerations
 * @{ */
 

/**
 * @brief Mesh errors
 */
typedef enum
{
    MESH_ERROR_NO_ERROR                             = 0x0000,                     /**< Operation is successful. */

    /* **************************************************************** */
    /* *                     PROTOCOL ERROR CODES                     * */
    /* **************************************************************** */

    MESH_ERROR_INVALID_ADDR                         = MESH_ERROR(PROTOCOL, 0x01), /**< Invalid address. */ 
    MESH_ERROR_INVALID_MODEL                        = MESH_ERROR(PROTOCOL, 0x02), /**< Invalid model. */
    MESH_ERROR_INVALID_APPKEY_ID                    = MESH_ERROR(PROTOCOL, 0x03), /**< Invalid application key index. */
    MESH_ERROR_INVALID_NETKEY_ID                    = MESH_ERROR(PROTOCOL, 0x04), /**< Invalid network key index. */ 
    MESH_ERROR_INSUFFICIENT_RESOURCES               = MESH_ERROR(PROTOCOL, 0x05), /**< Insufficient resources. */ 
    MESH_ERROR_KEY_ID_ALREADY_STORED                = MESH_ERROR(PROTOCOL, 0x06), /**< Application/network key index is already stored. */ 
    MESH_ERROR_INVALID_PUBLISH_PARAMS               = MESH_ERROR(PROTOCOL, 0x07), /**< Invalid publish parameters. */
    MESH_ERROR_NOT_A_SUBSCRIBE_MODEL                = MESH_ERROR(PROTOCOL, 0x08), /**< Cannot support subscribing. */
    MESH_ERROR_STORAGE_FAILURE                      = MESH_ERROR(PROTOCOL, 0x09), /**< Storage failure. */ 
    MESH_ERROR_NOT_SUPPORTED                        = MESH_ERROR(PROTOCOL, 0x0A), /**< Cannot support the feature. */ 
    MESH_ERROR_CANNOT_UPDATE                        = MESH_ERROR(PROTOCOL, 0x0B), /**< Cannot update. */ 
    MESH_ERROR_CANNOT_REMOVE                        = MESH_ERROR(PROTOCOL, 0x0C), /**< Cannot remove. */ 
    MESH_ERROR_CANNOT_BIND                          = MESH_ERROR(PROTOCOL, 0x0D), /**< Cannot bind. */ 
    MESH_ERROR_TEMP_UNABLE_TO_CHANGE_STATE          = MESH_ERROR(PROTOCOL, 0x0E), /**< Unable to change state temporarily. */ 
    MESH_ERROR_CANNOT_SET                           = MESH_ERROR(PROTOCOL, 0x0F), /**< Cannot set. */ 
    MESH_ERROR_UNSPECIFIED_ERROR                    = MESH_ERROR(PROTOCOL, 0x10), /**< Unspecified error. */ 
    MESH_ERROR_INVALID_BINDING                      = MESH_ERROR(PROTOCOL, 0x11), /**< Invalid binding. */

    /* **************************************************************** */
    /* *                     PROVISIONING ERROR CODES                 * */
    /* **************************************************************** */

    MESH_ERROR_PROV_PROHIBITED                      = MESH_ERROR(PROVISIONING, 0x00), /**< Prohibited. */
    MESH_ERROR_PROV_INVALID_PDU                     = MESH_ERROR(PROVISIONING, 0x01), /**< The provisioning protocol PDU is not recognized by the device. */ 
    MESH_ERROR_PROV_INVALID_FORMAT                  = MESH_ERROR(PROVISIONING, 0x02), /**< The arguments of the protocol PDU are not expected values,
                                                                                            or the length of the PDU is different from the expected value. */ 
    MESH_ERROR_PROV_UNEXPECTED_PDU                  = MESH_ERROR(PROVISIONING, 0x03), /**< The PDU received was not expected at this moment of the procedure. */ 
    MESH_ERROR_PROV_CONFIRMATION_FAILED             = MESH_ERROR(PROVISIONING, 0x04), /**< The computed confirmation value was not successfully verified. */ 
    MESH_ERROR_PROV_OUT_OF_RESOURCES                = MESH_ERROR(PROVISIONING, 0x05), /**< The provisioning protocol cannot be continued due to insufficient resources in the device. */ 
    MESH_ERROR_PROV_DECRYPTION_FAILED               = MESH_ERROR(PROVISIONING, 0x06), /**< The data block was not successfully decrypted. */ 
    MESH_ERROR_PROV_UNEXPECTED                      = MESH_ERROR(PROVISIONING, 0x07), /**< An unexpected error occurred, and it may not be recovered. */ 
    MESH_ERROR_PROV_CANNOT_ASSIGN_ADDR              = MESH_ERROR(PROVISIONING, 0x08), /**< The device cannot assign consecutive unicast addresses to all elements. */

    /* **************************************************************** */
    /* *                     INTERNAL ERROR CODES                     * */
    /* **************************************************************** */
    MESH_ERROR_INVALID_PARAM                        = MESH_ERROR(INTERNAL, 0x01), /**< Invalid parameter. */
    MESH_ERROR_COMMAND_DISALLOWED                   = MESH_ERROR(INTERNAL, 0x02), /**< Command is disallowed. */
    MESH_ERROR_MIC_ERROR                            = MESH_ERROR(INTERNAL, 0x03), /**< MIC error. */
    MESH_ERROR_BUSY                                 = MESH_ERROR(INTERNAL, 0x04), /**< Requested resource is busy. */
    MESH_ERROR_TIME_PAST                            = MESH_ERROR(INTERNAL, 0x05), /**< Requested time value is past. */
    MESH_ERROR_NOT_FOUND                            = MESH_ERROR(INTERNAL, 0x06), /**< Requested resource not found. */
    MESH_ERROR_SEQ_ERROR                            = MESH_ERROR(INTERNAL, 0x07), /**< Sequence number error. */
    MESH_ERROR_BEARER_CLOSED                        = MESH_ERROR(INTERNAL, 0x08), /**< Bearer instance has been closed. */
    MESH_ERROR_PROVISIONING_FAILED                  = MESH_ERROR(INTERNAL, 0x09), /**< Provisioning failed. */
    MESH_ERROR_PROVISIONING_TIMEOUT                 = MESH_ERROR(INTERNAL, 0x0A), /**< Provisioning timeout - transaction or link timeout. */
    MESH_ERROR_ECDH_FAILED                          = MESH_ERROR(INTERNAL, 0x0B), /**< Failed to access ECDH - critical error. */
    MESH_ERROR_NO_EFFECT                            = MESH_ERROR(INTERNAL, 0x0C), /**< Request has no effect. */
    MESH_ERROR_CANNOT_FRAGMENT                      = MESH_ERROR(INTERNAL, 0x0D), /**< Cannot fragment message due to lack of resources. */

    /* **************************************************************** */
    /* *                  LOW POWER NODE ERROR CODES                  * */
    /* **************************************************************** */ 
    MESH_ERROR_LPN_ESTAB_FAILED                     = MESH_ERROR(LPN, 0x01),      /**< Establishment failed after several attempts. */
    MESH_ERROR_LPN_ESTAB_FAILED_KEY                 = MESH_ERROR(LPN, 0x02),      /**< Establishment failed due to failure during generation of friend keys. */
    MESH_ERROR_LPN_ESTAB_FAILED_UPD                 = MESH_ERROR(LPN, 0x03),      /**< Establishment failed because no Friend Update message was received 
                                                                                        after transmission of Friend Poll. */
    MESH_ERROR_LPN_FRIEND_LOST_LOCAL                = MESH_ERROR(LPN, 0x04),      /**< Friendship stopped due to local request. */
    MESH_ERROR_LPN_FRIEND_LOST_TIMEOUT              = MESH_ERROR(LPN, 0x05),      /**< Friendship lost due to request timeout. */

    /* **************************************************************** */
    /* *                      MODEL ERROR CODES                       * */
    /* **************************************************************** */ 
    MESH_ERROR_MODEL_UNSUPPORTED_APID               = MESH_ERROR(MODEL, 0x01),    /**< Unsupported model API identifier. */
    MESH_ERROR_MODEL_INVALID_APID                   = MESH_ERROR(MODEL, 0x02),    /**< Invalid model API identifier. */
    MESH_ERROR_MODEL_UNKNOWN_MDL_ID                 = MESH_ERROR(MODEL, 0x03),    /**< Unknown model identifier. */
    MESH_ERROR_MODEL_INVALID_MDL_ID                 = MESH_ERROR(MODEL, 0x04),    /**< Invalid model identifier. */

    /* **************************************************************** */
    /* *                  MESH COMMON TIMER ERROR CODES                  * */
    /* **************************************************************** */ 
    MESH_ERROR_TIMER_INVALID_PARAM                  = MESH_ERROR(TIMER, 0x01),    /**< Invalid parameter. */
    MESH_ERROR_TIMER_INSUFFICIENT                   = MESH_ERROR(TIMER, 0x02),    /**< Timer is insufficient. */

    /* **************************************************************** */
    /* *                  MESH SDK ERROR CODES                  * */
    /* **************************************************************** */ 
    MESH_ERROR_SDK_INVALID_PARAM                    = MESH_ERROR(SDK, 0x01),     /**< Invalid parameter. */ 
    MESH_ERROR_SDK_INSUFFICIENT                     = MESH_ERROR(SDK, 0x02),     /**< Insufficient resources. */
    MESH_ERROR_SDK_RELIABLE_TRANS_ON                = MESH_ERROR(SDK, 0x03),     /**< Reliable message transfer procedure is on. */
    MESH_ERROR_SDK_RELIABLE_TRANS_OFF               = MESH_ERROR(SDK, 0x04),     /**< Reliable message transfer procedure is off. */
    MESH_ERROR_SDK_FRIENDSHIP_NOT_EXIST             = MESH_ERROR(SDK, 0x05),     /**< Friendship not exist. */
} mesh_error_t;

/** @} */
#endif /* _MESH_SDK_ERROR_ */

/** @} */
/** @} */

