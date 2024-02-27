/**
 *****************************************************************************************
 *
 * @file scheduler_message.h
 *
 * @brief  Mesh Scheduler Message Define.
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
#ifndef __TSCNS_SCHEDULER_MESSAGE_H__
#define __TSCNS_SCHEDULER_MESSAGE_H__


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
#define TSCNS_SCHEDULER_ACTION_SET_MINLEN 10
/** The allowed shortest length for the scheduler action Get message. */
#define TSCNS_SCHEDULER_ACTION_GET_MINLEN 1

/** The allowed shortest length for the Status message. */
#define TSCNS_SCHEDULER_STATUS_MINLEN 2
/** The allowed shortest length for the scheduler action Status message. */
#define TSCNS_SCHEDULER_ACTION_STATUS_MINLEN 10

/** The Schedule Register state fields length*/
#define TSCNS_SCHEDULER_REGISTER_INDEX_LEN 4
#define TSCNS_SCHEDULER_REGISTER_YEAR_LEN 7
#define TSCNS_SCHEDULER_REGISTER_MONTH_LEN 12
#define TSCNS_SCHEDULER_REGISTER_DAY_LEN 5
#define TSCNS_SCHEDULER_REGISTER_HOUR_LEN 5
#define TSCNS_SCHEDULER_REGISTER_MINUTE_LEN 6
#define TSCNS_SCHEDULER_REGISTER_SECOND_LEN 6
#define TSCNS_SCHEDULER_REGISTER_DAYWEEK_LEN 7
#define TSCNS_SCHEDULER_REGISTER_ACTION_LEN 4
#define TSCNS_SCHEDULER_REGISTER_TRANS_TIME_LEN 8
#define TSCNS_SCHEDULER_REGISTER_SCENE_NUMBER_LEN 16

/** The Schedule Register state fields mask bits*/
#define TSCNS_SCHEDULER_REGISTER_INDEX_MASK 0xF
#define TSCNS_SCHEDULER_REGISTER_YEAR_MASK 0x7F
#define TSCNS_SCHEDULER_REGISTER_MONTH_MASK 0xFFF
#define TSCNS_SCHEDULER_REGISTER_DAY_MASK 0x1F
#define TSCNS_SCHEDULER_REGISTER_HOUR_MASK 0x1F
#define TSCNS_SCHEDULER_REGISTER_MINUTE_MASK 0x3F
#define TSCNS_SCHEDULER_REGISTER_SECOND_MASK 0x3F
#define TSCNS_SCHEDULER_REGISTER_DAYWEEK_MASK 0x7F
#define TSCNS_SCHEDULER_REGISTER_ACTION_MASK 0x0F
#define TSCNS_SCHEDULER_REGISTER_TRANS_TIME_MASK 0xFF
#define TSCNS_SCHEDULER_REGISTER_SCENE_NUMBER_LSBMASK 0x00FF
#define TSCNS_SCHEDULER_REGISTER_SCENE_NUMBER_MSBMASK 0xFF00

#define TSCNS_SCHEDULER_REGISTER_YEAR_OFFSET                          (TSCNS_SCHEDULER_REGISTER_INDEX_LEN )
#define TSCNS_SCHEDULER_REGISTER_MONTH_OFFSET                       (TSCNS_SCHEDULER_REGISTER_YEAR_OFFSET + TSCNS_SCHEDULER_REGISTER_YEAR_LEN)
#define TSCNS_SCHEDULER_REGISTER_DAY_OFFSET                            (TSCNS_SCHEDULER_REGISTER_MONTH_OFFSET + TSCNS_SCHEDULER_REGISTER_MONTH_LEN)
#define TSCNS_SCHEDULER_REGISTER_HOUR_OFFSET                          (TSCNS_SCHEDULER_REGISTER_DAY_OFFSET + TSCNS_SCHEDULER_REGISTER_DAY_LEN)
#define TSCNS_SCHEDULER_REGISTER_MINUTE_OFFSET                      (TSCNS_SCHEDULER_REGISTER_HOUR_OFFSET + TSCNS_SCHEDULER_REGISTER_HOUR_LEN)
#define TSCNS_SCHEDULER_REGISTER_SECOND_OFFSET                      (TSCNS_SCHEDULER_REGISTER_MINUTE_OFFSET + TSCNS_SCHEDULER_REGISTER_MINUTE_LEN)
#define TSCNS_SCHEDULER_REGISTER_DAYWEEK_OFFSET                   (TSCNS_SCHEDULER_REGISTER_SECOND_OFFSET + TSCNS_SCHEDULER_REGISTER_SECOND_LEN)
#define TSCNS_SCHEDULER_REGISTER_ACTION_OFFSET                      (TSCNS_SCHEDULER_REGISTER_DAYWEEK_OFFSET + TSCNS_SCHEDULER_REGISTER_DAYWEEK_LEN)
#define TSCNS_SCHEDULER_REGISTER_TRANS_TIME_OFFSET              (TSCNS_SCHEDULER_REGISTER_ACTION_OFFSET + TSCNS_SCHEDULER_REGISTER_ACTION_LEN)
#define TSCNS_SCHEDULER_REGISTER_SCENE_NUMBER_1OFFSET       (TSCNS_SCHEDULER_REGISTER_TRANS_TIME_OFFSET + TSCNS_SCHEDULER_REGISTER_TRANS_TIME_LEN)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/**   mesh scheduler model message opcodes. */
typedef enum
{
    TSCNS_SCHEDULER_OPCODE_ACTION_GET = 0x8248,                                   /** Message opcode for the scheduler register action Get message. */
    TSCNS_SCHEDULER_OPCODE_ACTION_STATUS = 0x5F,                                /** Message opcode for the scheduler register Status message. */
    TSCNS_SCHEDULER_OPCODE_GET = 0x8249,                                                 /** Message opcode for the scheduler register Get message. */
    TSCNS_SCHEDULER_OPCODE_STATUS = 0x824A,                                           /** Message opcode for the scheduler Status message. */
    TSCNS_SCHEDULER_OPCODE_ACTION_SET = 0x60,                                       /** Message opcode for the scheduler register action Set message. */
    TSCNS_SCHEDULER_OPCODE_ACTION_SET_UNACKNOWLEDGED = 0x61,      /** Message opcode for the scheduler register action Set unacknowledge message. */
} mesh_scheduler_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the   mesh scheduler Set message. */
typedef struct __attribute((packed))
{
    uint64_t scheduler_reg_H64;               /**< Bit field defining an entry in the Schedule Register. field 0 is 64 bits */
    uint16_t scheduler_reg_L12;           /**< Bit field defining an entry in the Schedule Register. field 1 is 16 bits */

} mesh_scheduler_action_set_msg_pkt_t;

/** Parameters for the scheduler Status message. */
typedef struct __attribute((packed))
{
    uint64_t scheduler_reg_H64;               /**< Bit field defining an entry in the Schedule Register. field 0 is 64 bits */
    uint16_t scheduler_reg_L12;           /**< Bit field defining an entry in the Schedule Register. field 1 is 16 bits */

} mesh_scheduler_action_status_msg_pkt_t;

#endif /* __TSCNS_SCHEDULER_MESSAGE_H__ */

/** @} */

