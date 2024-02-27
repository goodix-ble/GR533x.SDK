/**
 *****************************************************************************************
 *
 * @file generic_power_level_message.h
 *
 * @brief Generic Power Level Message Define.
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
#ifndef __GENERIC_POWER_LEVEL_MESSAGE_H__
#define __GENERIC_POWER_LEVEL_MESSAGE_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** The allowed shortest length for the actual Set message. */
#define GENERIC_POWER_LEVEL_SET_MINLEN 3
/** The allowed longest length for the actual Set message. */
#define GENERIC_POWER_LEVEL_SET_MAXLEN 5

/** The allowed shortest length for the actual Status message. */
#define GENERIC_POWER_LEVEL_STATUS_MINLEN 2
/** The allowed longest length for the actual Status message. */
#define GENERIC_POWER_LEVEL_STATUS_MAXLEN 5

/** The allowed shortest length for the default Set message. */
#define GENERIC_POWER_LEVEL_DFT_SET_LEN 2

/** The allowed shortest length for the range Set message. */
#define GENERIC_POWER_LEVEL_RANGE_SET_LEN 4

/** The allowed shortest length for the default Status message. */
#define GENERIC_POWER_LEVEL_DFT_STATUS_LEN 2

/** The allowed shortest length for the last Status message. */
#define GENERIC_POWER_LEVEL_LAST_STATUS_LEN 2

/** The allowed shortest length for the range Status message. */
#define GENERIC_POWER_LEVEL_RANGE_STATUS_LEN 5

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Generic Power Level  model message opcodes. */
typedef enum
{
    GENERIC_POWER_LEVEL_OPCODE_GET = 0x8215,                                       /** Message opcode for the Generic Power Level Get message. */
    GENERIC_POWER_LEVEL_OPCODE_SET = 0x8216,                                       /** Message opcode for the Generic Power Level  Set message. */
    GENERIC_POWER_LEVEL_OPCODE_SET_UNACKNOWLEDGED = 0x8217,                        /** Message opcode for the Generic Power Level  Set Unacknowledged message. */
    GENERIC_POWER_LEVEL_OPCODE_STATUS = 0x8218,                                    /** Message opcode for the Generic Power Level  Status message. */
    GENERIC_POWER_LEVEL_LAST_OPCODE_GET = 0x8219,                                  /** Message opcode for the Generic Power Level  Last Get message. */
    GENERIC_POWER_LEVEL_LAST_OPCODE_STATUS = 0x821A,                               /** Message opcode for the Generic Power Level  Last Status message. */
    GENERIC_POWER_LEVEL_DEFAULT_OPCODE_GET = 0x821B,                               /** Message opcode for the Generic Power Level  Default Get message. */
    GENERIC_POWER_LEVEL_DEFAULT_OPCODE_STATUS = 0x821C,                            /** Message opcode for the Generic Power Level  Default Status message. */
    GENERIC_POWER_LEVEL_RANGE_OPCODE_GET = 0x821D,                                 /** Message opcode for the Generic Power Level  Range Get message. */
    GENERIC_POWER_LEVEL_RANGE_OPCODE_STATUS = 0x821E,                              /** Message opcode for the Generic Power Level  Range Status message. */
} generic_power_level_opcode_t;

/** Generic Power Level  model message opcodes. */
typedef enum
{
    GENERIC_POWER_LEVEL_DEFAULT_OPCODE_SET = 0x821F,                   /** Message opcode for the Generic Power Level  Default Set message. */
    GENERIC_POWER_LEVEL_DEFAULT_OPCODE_SET_UNACKNOWLEDGED = 0x8220,    /** Message opcode for the Generic Power Level  Default Set Unacknowledged message. */
    GENERIC_POWER_LEVEL_RANGE_OPCODE_SET = 0x8221,                     /** Message opcode for the Generic Power Level  Range Set message. */
    GENERIC_POWER_LEVEL_RANGE_OPCODE_SET_UNACKNOWLEDGED = 0x8222,      /** Message opcode for the Generic Power Level  Range Set Unacknowledged message. */
} generic_power_level_setup_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Generic Power Level Set message. */
typedef struct __attribute((packed))
{
    uint16_t power;                                         /**< State to set */
    uint8_t tid;                                            /**< Transaction number for application */
    uint8_t transition_time;                                /**< Encoded transition time value */
    uint8_t delay;                                          /**< Encoded message execution delay in 5 millisecond steps */
} generic_power_level_set_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t power;                                         /**< State to set */
} generic_power_level_set_dft_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t min_power;                                         /**< State to set */
    uint16_t max_power;                                         /**< State to set */
} generic_power_level_set_range_msg_pkt_t;

/** Message format for the Generic Power Level Status message. */
typedef struct __attribute((packed))
{
    uint16_t present_power;                                 /**< The present value of the Generic Power Level state */
    uint16_t target_power;                                  /**< The target value of the Generic Power Level state (optional) */
    uint8_t remaining_time;                                 /**< Encoded remaining time */
} generic_power_level_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t power;                                 /**< The last value of the Generic Power Level state */
} generic_power_level_last_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t power;                                 /**< The default value of the Generic Power Level state */
} generic_power_level_dft_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint8_t status_code;
    uint16_t min_power;                                 /**< The default value of the Generic Power Level state */
    uint16_t max_power;                                 /**< The default value of the Generic Power Level state */
} generic_power_level_range_status_msg_pkt_t;

#endif /* __GENERIC_POWER_LEVEL_MESSAGE_H__ */

/** @} */

