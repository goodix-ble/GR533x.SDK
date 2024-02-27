/**
 ****************************************************************************************
 *
 * @file generic_level_common.h
 *
 * @brief Generic Level Common Define.
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
#ifndef __GENERIC_LEVEL_COMMON_H__
#define __GENERIC_LEVEL_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */
/** Generic Level Server model max number */ 
#define GENERIC_LEVEL_SERVER_INSTANCE_COUNT_MAX                     (16)
/** Generic Level Client model max number */
#define GENERIC_LEVEL_CLIENT_INSTANCE_COUNT_MAX                     (16)

/** The total number of transmit handle for Generic Level Server */
#define GENERIC_LEVEL_SERVER_TX_HDL_TOTAL                           (2)
/** The transmit handle for Generic Level Server publish Status message */
#define GENERIC_LEVEL_SERVER_PUBLISH_SEND_TX_HDL                    (0x00)
/** The transmit handle for Generic Level Server response Status message */
#define GENERIC_LEVEL_SERVER_RSP_SEND_TX_HDL                        (0x01)


/** The total number of transmit handle for Generic Level Client */
#define GENERIC_LEVEL_CLIENT_TX_HDL_TOTAL                           (7)
/** The transmit handle for Generic Level Client Get message */
#define GENERIC_LEVEL_CLIENT_GET_SEND_TX_HDL                        (GENERIC_LEVEL_SERVER_PUBLISH_SEND_TX_HDL \
                                                                    + GENERIC_LEVEL_SERVER_TX_HDL_TOTAL * GENERIC_LEVEL_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Generic Level Client Set message */
#define GENERIC_LEVEL_CLIENT_SET_SEND_TX_HDL                        (GENERIC_LEVEL_CLIENT_GET_SEND_TX_HDL + 1)  
/** The transmit handle for Generic Level Client Set Unacknowledged message */ 
#define GENERIC_LEVEL_CLIENT_SET_UNRELIABLE_SEND_TX_HDL             (GENERIC_LEVEL_CLIENT_SET_SEND_TX_HDL + 1)  
/** The transmit handle for Generic Level Client Delta Set message */ 
#define GENERIC_LEVEL_CLIENT_DELTA_SET_SEND_TX_HDL                  (GENERIC_LEVEL_CLIENT_SET_UNRELIABLE_SEND_TX_HDL + 1)
/** The transmit handle for Generic Level Client Delta Set Unacknowledged message */ 
#define GENERIC_LEVEL_CLIENT_DELTA_SET_UNRELIABLE_SEND_TX_HDL       (GENERIC_LEVEL_CLIENT_DELTA_SET_SEND_TX_HDL + 1)
/** The transmit handle for Generic Level Client Move Set message */ 
#define GENERIC_LEVEL_CLIENT_MOVE_SET_SEND_TX_HDL                   (GENERIC_LEVEL_CLIENT_DELTA_SET_UNRELIABLE_SEND_TX_HDL + 1)
/** The transmit handle for Generic Level Client Move Set Unacknowledged message */ 
#define GENERIC_LEVEL_CLIENT_MOVE_SET_UNRELIABLE_SEND_TX_HDL        (GENERIC_LEVEL_CLIENT_MOVE_SET_SEND_TX_HDL + 1)

/** The reliable message timeout time */
#define GENERIC_LEVEL_RELIABLE_MSG_TIMEOUT_MS                       (30000)

/** Model Company ID */
#define GENERIC_LEVEL_COMPANY_ID 0xFFFF

/** Maximum value of the level state, as defined in the Mesh Model Specification v1.0 */
#define GENERIC_LEVEL_MAX        (0xFFFF)


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * Unpacked message structure typedefs are used for API interfaces and for implementing model code.
 */

/* Parameters for the generic_level Set message. */
typedef struct
{
    int16_t level;                                        /**< Value of the Level state */
    uint8_t tid;                                          /**< Transaction ID */
} generic_level_set_params_t;

/* Message format for the generic_level Delta Set message. */
typedef struct
{
    int32_t delta_level;                                  /**< Value of the Delta Level state */
    uint8_t tid;                                          /**< Transaction ID */
} generic_level_delta_set_params_t;

/* Message format for the generic_level Move Set message. */
typedef struct
{
    int16_t move_level;                                    /**< Value of the Move Level state */
    uint8_t tid;                                           /**< Transaction ID */
} generic_level_move_set_params_t;

/* Parameters for the generic_level Status message. */
typedef struct
{
    int16_t present_level;                                 /**< The present value of the Generic Level state */
    int16_t target_level;                                  /**< The target value of the Generic Level state (optional) */
    uint32_t remaining_time_ms;                            /**< Remaining time value in milliseconds */
} generic_level_status_params_t;

#endif /* __GENERIC_LEVEL_COMMON_H__ */

/** @} */
