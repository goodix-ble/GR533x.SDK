/**
 *****************************************************************************************
 *
 * @file harmony_mesh_common.h
 *
 * @brief Harmony mesh verdor  Common Define.
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
#ifndef __HARMONY_MESH_COMMON_H__
#define __HARMONY_MESH_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include <stddef.h>

/*
 * DEFINES
 ****************************************************************************************
 */
/** Harmony mesh verdor  Server model max number */
#define HARMONY_MESH_SERVER_INSTANCE_COUNT_MAX              (16)
/** Harmony mesh verdor  Client model max number */
#define HARMONY_MESH_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for Harmony mesh verdor  Server */
#define HARMONY_MESH_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for Harmony mesh verdor  Server publish Status message */
#define HARMONY_MESH_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for Harmony mesh verdor  Server response Status message */
#define HARMONY_MESH_SERVER_RSP_SEND_TX_HDL                 (0x01)


/** The total number of transmit handle for Harmony mesh verdor  Client */
#define HARMONY_MESH_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for Harmony mesh verdor  Client Get message */
#define HARMONY_MESH_CLIENT_GET_SEND_TX_HDL                 (HARMONY_MESH_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + HARMONY_MESH_SERVER_TX_HDL_TOTAL * HARMONY_MESH_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Harmony mesh verdor  Client Set message */
#define HARMONY_MESH_CLIENT_SET_SEND_TX_HDL                 (HARMONY_MESH_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for Harmony mesh verdor  Client Set Unacknowledged message */
#define HARMONY_MESH_CLIENT_SET_UNRELIABLE_SEND_TX_HDL      (HARMONY_MESH_CLIENT_SET_SEND_TX_HDL + 1)

/** The reliable message timeout time */
#define HARMONY_MESH_RELIABLE_MSG_TIMEOUT_MS                (30000)

/** Model Company ID */
#define HARMONY_MESH_COMPANY_ID (0x027D)

/** The allowed length for the Set message. */
#define HARMONY_MESH_RX_LEN (3)

/** Maximum length of the attribute value.*/
#define HARMONY_MESH_VALUE_MAX        (374)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Harmony mesh verdor  model message opcodes. */
typedef enum
{
    HARMONY_MESH_OPCODE_GET = 0xD0,                 /** Message opcode for the Harmony mesh verdor  Get message. */
    HARMONY_MESH_OPCODE_SET = 0xD1,                 /** Message opcode for the Harmony mesh verdor  Set message. */
    HARMONY_MESH_OPCODE_SET_UNACK = 0xD2,  /** Message opcode for the Harmony mesh verdor  Set Unacknowledged message. */
    HARMONY_MESH_OPCODE_SET_STATUS = 0xD3,                 /** Message opcode for the Harmony mesh verdor  Set message. */
    HARMONY_MESH_OPCODE_CHANGE_NOTIFY = 0xD4,                 /** Message opcode for the Harmony mesh verdor  Set message. */
    HARMONY_MESH_OPCODE_CHANGE_NOTIFY_STATUS = 0xD5,                 /** Message opcode for the Harmony mesh verdor  Set message. */
    HARMONY_MESH_OPCODE_CHANGE_NOTIFY_UNACK = 0xD6,                 /** Message opcode for the Harmony mesh verdor  Set message. */
    HARMONY_MESH_OPCODE_GET_STATUS = 0xD7,                 /** Message opcode for the Harmony mesh verdor  Get message. */
} harmony_mesh_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Harmony mesh verdor  Set message. */
typedef struct __attribute((packed))
{
    uint8_t tid;                                                        /**< Transaction number for application */
    uint16_t attri_type;                                         /**< attribute type to operate */
    uint8_t payload[];                                            /**< attribute type to operate */
} harmony_mesh_rx_msg_pkt_t;

/** Message format for the Harmony mesh verdor  Status message. */
typedef struct __attribute((packed))
{
    uint8_t tid;                                                        /**< Transaction number for application */
    uint16_t attri_type;                                         /**< attribute type to operate */
    uint8_t payload[];                                            /**< attribute type to operate */
} harmony_mesh_status_msg_pkt_t;

#endif /* __HARMONY_MESH_COMMON_H__ */

/** @} */

