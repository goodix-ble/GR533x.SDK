/**
 *****************************************************************************************
 *
 * @file generic_onoff_message.h
 *
 * @brief Generic On Off Message Define.
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
#ifndef __GENERIC_ONOFF_MESSAGE_H__
#define __GENERIC_ONOFF_MESSAGE_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** The allowed shortest length for the Set message. */
#define GENERIC_ONOFF_SET_MINLEN 2
/** The allowed longest length for the Set message. */
#define GENERIC_ONOFF_SET_MAXLEN 4

/** The allowed shortest length for the Status message. */
#define GENERIC_ONOFF_STATUS_MINLEN 1
/** The allowed longest length for the Status message. */
#define GENERIC_ONOFF_STATUS_MAXLEN 3


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Generic On Off model message opcodes. */
typedef enum
{
    GENERIC_ONOFF_OPCODE_GET = 0x8201,                  /** Message opcode for the Generic On Off Get message. */
    GENERIC_ONOFF_OPCODE_SET = 0x8202,                  /** Message opcode for the Generic On Off Set message. */
    GENERIC_ONOFF_OPCODE_SET_UNACKNOWLEDGED = 0x8203,   /** Message opcode for the Generic On Off Set Unacknowledged message. */
    GENERIC_ONOFF_OPCODE_STATUS = 0x8204,               /** Message opcode for the Generic On Off Status message. */
} generic_onoff_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Generic On Off Set message. */
typedef struct __attribute((packed))
{
    uint8_t on_off;                                         /**< State to set */
    uint8_t tid;                                            /**< Transaction number for application */
    uint8_t transition_time;                                /**< Encoded transition time value */
    uint8_t delay;                                          /**< Encoded message execution delay in 5 millisecond steps */
} generic_onoff_set_msg_pkt_t;

/** Message format for the Generic On Off Status message. */
typedef struct __attribute((packed))
{
    uint8_t present_on_off;                                 /**< The present value of the Generic On Off state */
    uint8_t target_on_off;                                  /**< The target value of the Generic On Off state (optional) */
    uint8_t remaining_time;                                 /**< Encoded remaining time */
} generic_onoff_status_msg_pkt_t;

#endif /* __GENERIC_ONOFF_MESSAGE_H__ */

/** @} */

