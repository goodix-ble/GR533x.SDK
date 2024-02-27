/**
 ****************************************************************************************
 *
 * @file mesh_lpn_friend.h
 *
 * @brief Header file for Mesh LPN and Friend Programming Interface
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

#ifndef __MESH_LPN_FRIEND_H__
#define __MESH_LPN_FRIEND_H__


/**
 ****************************************************************************************
 * @addtogroup MESH_LPN_FRIEND Mesh LPN and Friend
 * @{
 * @brief  Mesh LPN and Friend Programming Interface
 ****************************************************************************************
 */
/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "mesh_sdk_error.h"
#include <stdbool.h>
#include <stdint.h>

/** @addtogroup MESH_LPN_FRIEND_DEFINES Defines
 * @{ */
 
/** @} */

/** @addtogroup MESH_LPN_FRINEND_ENUMERATIONS Enumerations
 * @{ */
/*
 * ENUMERATIONS
 ****************************************************************************************
 */
 

/**
 * @brief List of friend events
 */
typedef enum
{
    MESH_FRIEND_EVENT_DISC,       /**< New Low Power Node has been discovered. */
    MESH_FRIEND_EVENT_ESTAB,      /**< Friendship established with Low Power Node. */
    MESH_FRIEND_EVENT_LOST,       /**< New Low Power Node or Friendship with low Power Node has been lost. */
} mesh_friend_event_t;

/**
 * @brief Friend state.
 */
typedef enum 
{
    MESH_FRIEND_STATE_DISABLED,       /**< Friend feature supported and disabled. */
    MESH_FRIEND_STATE_ENABLED,        /**< Friend feature supported and enabled. */
    MESH_FRIEND_STATE_NOT_SUPPORTED,  /**< Friend feature not supported. */
} mesh_friend_state_t;

/** @} */

/**@addtogroup MESH_LPN_FRIEND_STRUCTURES Structures
 * @{ */
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
 
/**
 * @brief LPN information
 */
typedef struct
{ 
    uint32_t poll_timeout;        /**< Initial value of Poll Timeout timer. */
    uint16_t prev_addr;           /**< Address of previous Friend Node. */
    uint8_t  rx_delay;            /**< Requested receive delay. */
    uint8_t  rssi_factor;         /**< RSSI factor. */
    uint8_t  rx_window_factor;    /**< Receive window factor. */
    uint8_t  min_queue_size_log;  /**< Requested minimum number of messages that the Friend node can store in its Friend Queue. */
} mesh_lpn_info_t;

/** @} */


/** @addtogroup MESH_LPN_FRIEND_FUNCTION Functions
 * @{ */
/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Enable Low Power Node feature and start looking for an available Friend node in the neighborhood.
 *
 * @param[in] p_lpn_info     Pointer to the LPN information.
 * @param[in] netkey_index   The subnet to initiate the Friendship procedure.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is successful.
 * @retval ::MESH_ERROR_INVALID_PARAM           Invalid parameter.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command is disallowed.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES  Insufficient resources.
 * @retval ::MESH_ERROR_UNSPECIFIED_ERROR       Unspecified error.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter. The parameter p_lpn_info is NULL, or netkey_index is invalid.
 ****************************************************************************************
 */
mesh_error_t mesh_lpn_friendship_setup(mesh_lpn_info_t* p_lpn_info, uint16_t netkey_index);

/**
 ****************************************************************************************
 * @brief Disable Low Power Node feature and clear the Friendship.
 *
 * @note Function callback @ref app_mesh_lpn_friend_cb_t::app_mesh_lpn_status_cb will be called in this API.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is successful.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command is disallowed.
 ****************************************************************************************
 */
mesh_error_t mesh_lpn_friendship_clear(void);

/**
 ****************************************************************************************
 * @brief Select a friend after receiving one or several Friend Offer messages. This function is used after callback
 *                             function app_mesh_lpn_friend_cb_t::app_mesh_lpn_offer_cb.
 *
 * @param[in] friend_addr     Address of the selected Friend node.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is successful.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command is disallowed.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES  Insufficient resources.
 * @retval ::MESH_ERROR_BUSY                    Requested resource is busy.
 * @retval ::MESH_ERROR_NOT_FOUND               Requested resource not found.
 ****************************************************************************************
 */
mesh_error_t mesh_lpn_friend_select(uint16_t friend_addr);

/**
 ****************************************************************************************
 * @brief LPN sends a Friend Poll to the friend node to get messages in Friend Queue.
 *
 * @note Function callback @ref app_mesh_lpn_friend_cb_t::app_mesh_lpn_poll_done_cb will be called when Friend Queue is empty.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is successful.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command is disallowed.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES  Insufficient resources.
 * @retval ::MESH_ERROR_UNSPECIFIED_ERROR       Unspecified error.
 ****************************************************************************************
 */
mesh_error_t mesh_lpn_poll_send(void);

/**
 ****************************************************************************************
 * @brief LPN gets the size of the local subscription list (the number of subscription addresses).
 *
 * @note This subscription list size is no more than the max subscription list size of the friend that the user selects.
 *
 * @return  Return the size of the local subscription list.
 ****************************************************************************************
 */
uint8_t mesh_lpn_sub_list_size_get(void);

/**
 ****************************************************************************************
 * @brief LPN gets the local subscription list.
 *
 * @param[out] p_sub_addr_list         Pointer to the subscription list.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is successful.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command is disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter. The parameter p_nb_sub_addr is NULL, or pp_sub_addr_list is NULL.
 ****************************************************************************************
 */
mesh_error_t mesh_lpn_sub_list_get(uint16_t *p_sub_addr_list);

/**
 ****************************************************************************************
 * @brief Get the Friend node address if Friendship exists.
 *
 * @param[out] p_friend_addr         Pointer to the friend address. If the friend address is 0, no Friendship exists now.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is successful.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter. The parameter p_friend_addr is NULL.
 ****************************************************************************************
 */
mesh_error_t mesh_lpn_friend_addr_get(uint16_t *p_friend_addr);

/**
 ****************************************************************************************
 * @brief Get Friend state.
 *
 * @return  Return Friend state.
 ****************************************************************************************
 */
mesh_friend_state_t mesh_friend_state_get(void);

/**
 ****************************************************************************************
 * @brief Enable or disable Friend feature.
 *
 * @note In the following cases, this function does not take effect:
 *       (1) This node does not support Friend feature;
 *       (2) This node supports Friend feature which is enabled, and the user wants to enable it again;
 *       (3) This node supports Friend feature which is disabled, and the user wants to disable it again.
 *       If this node has Friendships with one or more Low Power Nodes, and the user uses this function to
 *       disable the Friend feature, all Friendships will be terminated.
 *       Configuration Client may enable/disable this Friend feature.
 *
 * @param[in] enable Set true/false to enable/disable Friend feature.
 *
 ****************************************************************************************
 */
void mesh_friend_state_set(bool enable);

/**
 ****************************************************************************************
 * @brief Friend node gets the number of LPNs that have Friendship with this Friend node.
 *
 * @return  Return the number of LPNs.
 ****************************************************************************************
 */
uint8_t mesh_friend_lpn_nb_get(void);

 /**
 ****************************************************************************************
 * @brief Friend node gets the LPNs that have Friendship with this Friend node.
 *
 * @param[out] p_lpn_addr_list         Pointer to the LPN list.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is successful.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command is disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter. The parameter p_lpn_addr_list is NULL.
 ****************************************************************************************
 */
mesh_error_t mesh_friend_lpn_list_get(uint16_t *p_lpn_addr_list);
/** @} */

#endif /* _MESH_LPN_FRIEND_ */

/** @} */
/** @} */

