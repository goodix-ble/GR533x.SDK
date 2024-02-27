/**
 *****************************************************************************************
 *
 * @file simple_onoff_common.h
 *
 * @brief Simple On Off Common Define.
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
#ifndef __SIMPLE_ONOFF_COMMON_H__
#define __SIMPLE_ONOFF_COMMON_H__


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
/** Simple On Off Server model max number */
#define SIMPLE_ONOFF_SERVER_INSTANCE_COUNT_MAX              (16)
/** Simple On Off Client model max number */
#define SIMPLE_ONOFF_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for Simple On Off Server */
#define SIMPLE_ONOFF_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for Simple On Off Server publish Status message */
#define SIMPLE_ONOFF_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for Simple On Off Server response Status message */
#define SIMPLE_ONOFF_SERVER_RSP_SEND_TX_HDL                 (0x01)


/** The total number of transmit handle for Simple On Off Client */
#define SIMPLE_ONOFF_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for Simple On Off Client Get message */
#define SIMPLE_ONOFF_CLIENT_GET_SEND_TX_HDL                 (SIMPLE_ONOFF_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + SIMPLE_ONOFF_SERVER_TX_HDL_TOTAL * SIMPLE_ONOFF_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Simple On Off Client Set message */
#define SIMPLE_ONOFF_CLIENT_SET_SEND_TX_HDL                 (SIMPLE_ONOFF_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for Simple On Off Client Set Unacknowledged message */
#define SIMPLE_ONOFF_CLIENT_SET_UNRELIABLE_SEND_TX_HDL      (SIMPLE_ONOFF_CLIENT_SET_SEND_TX_HDL + 1)

/** The reliable message timeout time */
#define SIMPLE_ONOFF_RELIABLE_MSG_TIMEOUT_MS                (30000)

/** Model Company ID */
#define SIMPLE_ONOFF_COMPANY_ID (0x04F7)

/** Maximum value of the onoff state.*/
#define SIMPLE_ONOFF_MAX        (0x01)

/** The allowed length for the Set message. */
#define SIMPLE_ONOFF_SET_LEN (2)

/** The allowed length for the Status message. */
#define SIMPLE_ONOFF_STATUS_LEN (1)
/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Simple On Off model message opcodes. */
typedef enum
{
    SIMPLE_ONOFF_OPCODE_GET = 0xC1,                 /** Message opcode for the Simple On Off Get message. */
    SIMPLE_ONOFF_OPCODE_SET = 0xC2,                 /** Message opcode for the Simple On Off Set message. */
    SIMPLE_ONOFF_OPCODE_SET_UNACKNOWLEDGED = 0xC3,  /** Message opcode for the Simple On Off Set Unacknowledged message. */
    SIMPLE_ONOFF_OPCODE_STATUS = 0xC4,              /** Message opcode for the Simple On Off Status message. */
} simple_onoff_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Simple On Off Set message. */
typedef struct __attribute((packed))
{
    uint8_t on_off;                                         /**< State to set */
    uint8_t tid;                                            /**< Transaction number for application */
} simple_onoff_set_msg_pkt_t;

/** Message format for the Simple On Off Status message. */
typedef struct __attribute((packed))
{
    uint8_t present_on_off;                                 /**< The present value of the Simple OnOff state */
} simple_onoff_status_msg_pkt_t;

#endif /* __SIMPLE_ONOFF_COMMON_H__ */

/** @} */

