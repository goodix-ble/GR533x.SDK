/**
 *****************************************************************************************
 *
 * @file mesh_dfu_common.h
 *
 * @brief Mesh DFU Common Define.
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
#ifndef __MESH_DFU_COMMON_H__
#define __MESH_DFU_COMMON_H__


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
/** Model Company ID */
#define MESH_DFU_COMPANY_ID (0x04F7)


/** Mesh DFU Server model max number */
#define MESH_DFU_SERVER_INSTANCE_COUNT_MAX              (1)
/** Mesh DFU Client model max number */
#define MESH_DFU_CLIENT_INSTANCE_COUNT_MAX              (1)

/** The total number of transmit handle for Mesh DFU Server */
#define MESH_DFU_SERVER_TX_HDL_TOTAL                    (4)
/** The transmit handle for Mesh DFU Server publish Current Version Status message */
#define MESH_DFU_SERVER_PUBLISH_CURRENT_VERSION_SEND_TX_HDL             (0x00)
/** The transmit handle for Mesh DFU Server response Current Version Status message */
#define MESH_DFU_SERVER_RSP_CURRENT_VERSION_SEND_TX_HDL                 (0x01)
/** The transmit handle for Mesh DFU Server publish New Version Status message */
#define MESH_DFU_SERVER_PUBLISH_NEW_VERSION_SEND_TX_HDL                 (0x02)
/** The transmit handle for Mesh DFU Server response New Version Status message */
#define MESH_DFU_SERVER_RSP_NEW_VERSION_SEND_TX_HDL                     (0x03)



/** The total number of transmit handle for Mesh DFU Client */
#define MESH_DFU_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for Mesh DFU Client Current Version Get message */
#define MESH_DFU_CLIENT_CURRENT_VERSION_GET_SEND_TX_HDL                 (MESH_DFU_SERVER_PUBLISH_CURRENT_VERSION_SEND_TX_HDL \
                                                              + MESH_DFU_SERVER_TX_HDL_TOTAL * MESH_DFU_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Mesh DFU Client New Version Set message */
#define MESH_DFU_CLIENT_NEW_VERSION_SET_SEND_TX_HDL                 (MESH_DFU_CLIENT_CURRENT_VERSION_GET_SEND_TX_HDL + 1)
/** The transmit handle for Mesh DFU Client New Version Set Unacknowledged message */
#define MESH_DFU_CLIENT_NEW_VERSION_SET_UNRELIABLE_SEND_TX_HDL      (MESH_DFU_CLIENT_NEW_VERSION_SET_SEND_TX_HDL + 1)

/** The reliable message timeout time */
#define MESH_DFU_RELIABLE_MSG_TIMEOUT_MS                (30000)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Mesh DFU model message opcodes. */
typedef enum
{
    MESH_DFU_OPCODE_CURRENT_VERSION_GET = 0xC1,                 /** Message opcode for the Mesh DFU Current Version Get message. */
    MESH_DFU_OPCODE_CURRENT_VERSION_STATUS = 0xC2,              /** Message opcode for the Mesh DFU Current Version Status message. */
    MESH_DFU_OPCODE_NEW_VERSION_SET = 0xC3,                     /** Message opcode for the Mesh DFU New Version Set message. */
    MESH_DFU_OPCODE_NEW_VERSION_SET_UNACKNOWLEDGED = 0xC4,      /** Message opcode for the Mesh DFU New Version Set Unacknowledged message. */
    MESH_DFU_OPCODE_NEW_VERSION_STATUS = 0xC5,                  /** Message opcode for the Mesh DFU New Version Status message. */
} mesh_dfu_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Mesh DFU Current Version Status message. */
typedef struct __attribute((packed))
{
    uint16_t company_id;                                 /**< The Company ID value of the version */
    uint16_t product_id;                                 /**< The Product ID value of the version */
    uint16_t product_version_id;                         /**< The Product Version ID value of the version */
} mesh_dfu_current_version_status_msg_pkt_t;

/** Message format for the Mesh DFU New Version Set message. */
typedef struct __attribute((packed))
{
    uint16_t company_id;                                 /**< The Company ID value of the version */
    uint16_t product_id;                                 /**< The Product ID value of the version */
    uint16_t product_version_id;                         /**< The Product Version ID value of the version */
    uint8_t  tid;                                        /**< Transaction number for application */
} mesh_dfu_new_version_set_msg_pkt_t;

/** Message format for the Mesh DFU New Version Status message. */
typedef struct __attribute((packed))
{
    uint16_t company_id;                                 /**< The present value of the Simple OnOff state */
    uint16_t product_id;                                 /**< The present value of the Simple OnOff state */
    uint16_t product_version_id;                         /**< The present value of the Simple OnOff state */
} mesh_dfu_new_version_status_msg_pkt_t;

#endif /* __MESH_DFU_COMMON_H__ */

/** @} */

