/**
 *****************************************************************************************
 *
 * @file scheduler_common.h
 *
 * @brief  Mesh Scheduler Common Define.
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
#ifndef __TSCNS_SCHEDULER_COMMON_H__
#define __TSCNS_SCHEDULER_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "scheduler_message.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/**   mesh scheduler Server model max number */
#define TSCNS_SCHEDULER_SERVER_INSTANCE_COUNT_MAX              (16)
/**   mesh scheduler Client model max number */
#define TSCNS_SCHEDULER_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for   mesh scheduler Server */
#define TSCNS_SCHEDULER_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for   mesh scheduler Server publish Status message */
#define TSCNS_SCHEDULER_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for   mesh scheduler Server response Status message */
#define TSCNS_SCHEDULER_SERVER_RSP_SEND_TX_HDL                 (0x01)

/** The total number of transmit handle for   mesh scheduler Client */
#define TSCNS_SCHEDULER_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for   mesh scheduler Client Get message */
#define TSCNS_SCHEDULER_CLIENT_GET_SEND_TX_HDL                 (TSCNS_SCHEDULER_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + TSCNS_SCHEDULER_SERVER_TX_HDL_TOTAL * TSCNS_SCHEDULER_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for   mesh scheduler Client Set message */
#define TSCNS_SCHEDULER_CLIENT_SET_SEND_TX_HDL                 (TSCNS_SCHEDULER_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for   mesh scheduler Client Set Unacknowledged message */
#define TSCNS_SCHEDULER_CLIENT_SET_UNRELIABLE_SEND_TX_HDL      (TSCNS_SCHEDULER_CLIENT_SET_SEND_TX_HDL + 1)

/** The reliable message timeout scheduler */
#define TSCNS_SCHEDULER_RELIABLE_MSG_TIMEOUT_MS                (30000)


/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Permanet parameters for the   mesh scheduler Set message. */
typedef struct
{
    uint8_t index;                             /**< Index of the Schedule Register entry to set . */
    uint8_t year;                               /**< Scheduled year for the action. */
    uint16_t month;                          /**< Scheduled month for the action. */
    uint8_t day;                                /**< Scheduled day for the action. */
    uint8_t hour;                              /**< Scheduled hour for the action. */
    uint8_t minute;                          /**< Scheduled minute for the action. */
    uint8_t second;                          /**< Scheduled second for the action. */
    uint8_t dayofweek;                   /**< Schedule days of the week for the action. */
    uint8_t action;                           /**< Action to be performed at the scheduled time. */
    uint8_t transition_time;            /**< Transition time for this action. */
    uint16_t scene_number;         /**< Scene number to be used for some actions. */
} mesh_scheduler_action_set_params_t;

typedef struct
{
    uint8_t index;                             /**< Index of the Schedule Register entry to set . */
    uint8_t year;                               /**< Scheduled year for the action. */
    uint16_t month;                          /**< Scheduled month for the action. */
    uint8_t day;                                /**< Scheduled day for the action. */
    uint8_t hour;                              /**< Scheduled hour for the action. */
    uint8_t minute;                         /**< Scheduled minute for the action. */
    uint8_t second;                          /**< Scheduled second for the action. */
    uint8_t dayofweek;                   /**< Schedule days of the week for the action. */
    uint8_t action;                           /**< Action to be performed at the scheduled time. */
    uint8_t transition_time;            /**< Transition time for this action. */
    uint16_t scene_number;         /**< Scene number to be used for some actions. */
}mesh_scheduler_action_status_params_t;

/**
 * Package the scheduler register into air package with bit field.
 *
 * @param[in]     p_server                 Application Mesh Scheduler setup server information pointer.
 * @param[in]     element_offset        Element address offset from primary element address.
 * @param[in]     set_cb                    Application Mesh Scheduler server setting callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                       Operation is Success.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t scheduler_pack_action_status(mesh_scheduler_action_status_msg_pkt_t *msg_pkt, const mesh_scheduler_action_status_params_t * p_params);

/**
 * Un-package the air package with bit field into scheduler register.
 *
 * @param[in]     p_server                 Application Mesh Scheduler setup server information pointer.
 * @param[in]     element_offset        Element address offset from primary element address.
 * @param[in]     set_cb                    Application Mesh Scheduler server setting callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                       Operation is Success.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t scheduler_unpack_action_status(mesh_scheduler_action_set_params_t * p_params, mesh_scheduler_action_set_msg_pkt_t *msg_pkt);

#endif /* __TSCNS_SCHEDULER_COMMON_H__ */

/** @} */

