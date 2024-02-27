/**
 *****************************************************************************************
 *
 * @file generic_default_transition_time_message.h
 *
 * @brief Generic Default Transition Time Message Define.
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
#ifndef __GENERIC_DEFAULT_TRANSITION_TIME_MESSAGE_H__
#define __GENERIC_DEFAULT_TRANSITION_TIME_MESSAGE_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>


/*
 * DEFINES
 ****************************************************************************************
 */

/** The allowed longest length for the Set message. */
#define GENERIC_DEFAULT_TRANSITION_TIME_SET_MAXLEN 1

/** The allowed longest length for the Status message. */
#define GENERIC_DEFAULT_TRANSITION_TIME_STATUS_MAXLEN 1


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Generic On Off model message opcodes. */
typedef enum
{
    GENERIC_DEFAULT_TRANSITION_TIME_OPCODE_GET = 0x820D,                    /** Message opcode for the Generic Default Transition Time Get message. */
    GENERIC_DEFAULT_TRANSITION_TIME_OPCODE_SET = 0x820E,                    /** Message opcode for the Generic Default Transition Time Set message. */
    GENERIC_DEFAULT_TRANSITION_TIME_OPCODE_SET_UNACKNOWLEDGED = 0x820F,     /** Message opcode for the Generic Default Transition Time Set Unacknowledged message. */
    GENERIC_DEFAULT_TRANSITION_TIME_OPCODE_STATUS = 0x8210,                 /** Message opcode for the Generic Default Transition Time Status message. */
} generic_default_transition_time_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Generic Default Transition Time Set message. */
typedef struct __attribute((packed))
{
    uint8_t default_transition_time;                                         /**< State to set */
} generic_default_transition_time_set_msg_pkt_t;

/** Message format for the Generic Default Transition Time Status message. */
typedef struct __attribute((packed))
{
    uint8_t present_default_transition_time;                                 /**< The present value of the Generic default transition time state */
} generic_default_transition_time_status_msg_pkt_t;

#endif /* __GENERIC_DEFAULT_TRANSITION_TIME_MESSAGE_H__ */

/** @} */
