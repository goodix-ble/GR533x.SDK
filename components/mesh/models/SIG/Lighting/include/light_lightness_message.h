/**
 *****************************************************************************************
 *
 * @file light_lightness_message.h
 *
 * @brief Light Lightness Define.
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
#ifndef __LIGHT_LIGHTNESS_MESSAGE_H__
#define __LIGHT_LIGHTNESS_MESSAGE_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** The allowed shortest length for the actual & linear Set message. */
#define LIGHT_LIGHTNESS_SET_MINLEN 3
/** The allowed longest length for the actual & linear Set message. */
#define LIGHT_LIGHTNESS_SET_MAXLEN 5

/** The allowed shortest length for the actual & linear Status message. */
#define LIGHT_LIGHTNESS_STATUS_MINLEN 2
/** The allowed longest length for the actual & linear Status message. */
#define LIGHT_LIGHTNESS_STATUS_MAXLEN 5

/** The allowed shortest length for the default Set message. */
#define LIGHT_LIGHTNESS_DFT_SET_LEN 2

/** The allowed shortest length for the range Set message. */
#define LIGHT_LIGHTNESS_RANGE_SET_LEN 4

/** The allowed shortest length for the default Status message. */
#define LIGHT_LIGHTNESS_DFT_STATUS_LEN 2

/** The allowed shortest length for the last Status message. */
#define LIGHT_LIGHTNESS_LAST_STATUS_LEN 2

/** The allowed shortest length for the range Status message. */
#define LIGHT_LIGHTNESS_RANGE_STATUS_LEN 5

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Light Lightness  model message opcodes. */
typedef enum
{
    LIGHT_LIGHTNESS_OPCODE_GET = 0x824B,                                                        /** Message opcode for the Light Lightness Get message. */
    LIGHT_LIGHTNESS_OPCODE_SET = 0x824C,                                                        /** Message opcode for the Light Lightness  Set message. */
    LIGHT_LIGHTNESS_OPCODE_SET_UNACKNOWLEDGED = 0x824D,                       /** Message opcode for the Light Lightness  Set Unacknowledged message. */
    LIGHT_LIGHTNESS_OPCODE_STATUS = 0x824E,                                                 /** Message opcode for the Light Lightness  Status message. */
    LIGHT_LIGHTNESS_LINEAR_OPCODE_GET = 0x824F,                                         /** Message opcode for the Light Lightness  Linear Get message. */
    LIGHT_LIGHTNESS_LINEAR_OPCODE_SET = 0x8250,                                         /** Message opcode for the Light Lightness  Linear Set message. */
    LIGHT_LIGHTNESS_LINEAR_OPCODE_SET_UNACKNOWLEDGED = 0x8251,        /** Message opcode for the Light Lightness  Linear Set Unacknowledged message. */
    LIGHT_LIGHTNESS_LINEAR_OPCODE_STATUS = 0x8252,                                  /** Message opcode for the Light Lightness  Linear Status message. */
    LIGHT_LIGHTNESS_LAST_OPCODE_GET = 0x8253,                                            /** Message opcode for the Light Lightness  Last Get message. */
    LIGHT_LIGHTNESS_LAST_OPCODE_STATUS = 0x8254,                                      /** Message opcode for the Light Lightness  Last Status message. */
    LIGHT_LIGHTNESS_DEFAULT_OPCODE_GET = 0x8255,                                     /** Message opcode for the Light Lightness  Default Get message. */
    LIGHT_LIGHTNESS_DEFAULT_OPCODE_STATUS = 0x8256,                               /** Message opcode for the Light Lightness  Default Status message. */
    LIGHT_LIGHTNESS_RANGE_OPCODE_GET = 0x8257,                                         /** Message opcode for the Light Lightness  Range Get message. */
    LIGHT_LIGHTNESS_RANGE_OPCODE_STATUS = 0x8258,                                   /** Message opcode for the Light Lightness  Range Status message. */
} light_ln_opcode_t;

/** Light Lightness  model message opcodes. */
typedef enum
{
    LIGHT_LIGHTNESS_DEFAULT_OPCODE_SET = 0x8259,                                     /** Message opcode for the Light Lightness  Default Set message. */
    LIGHT_LIGHTNESS_DEFAULT_OPCODE_SET_UNACKNOWLEDGED = 0x825A,    /** Message opcode for the Light Lightness  Default Set Unacknowledged message. */
    LIGHT_LIGHTNESS_RANGE_OPCODE_SET = 0x825B,                                        /** Message opcode for the Light Lightness  Range Set message. */
    LIGHT_LIGHTNESS_RANGE_OPCODE_SET_UNACKNOWLEDGED = 0x825C,       /** Message opcode for the Light Lightness  Range Set Unacknowledged message. */
} light_ln_setup_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Light Lightness Set message. */
typedef struct __attribute((packed))
{
    uint16_t ln;                                         /**< State to set */
    uint8_t tid;                                            /**< Transaction number for application */
    uint8_t transition_time;                                /**< Encoded transition time value */
    uint8_t delay;                                          /**< Encoded message execution delay in 5 millisecond steps */
} light_ln_set_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t ln;                                         /**< State to set */
} light_ln_set_dft_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t min_ln;                                         /**< State to set */
    uint16_t max_ln;                                         /**< State to set */
} light_ln_set_range_msg_pkt_t;

/** Message format for the Light Lightness Status message. */
typedef struct __attribute((packed))
{
    uint16_t present_ln;                                 /**< The present value of the Light Lightness state */
    uint16_t target_ln;                                  /**< The target value of the Light Lightness state (optional) */
    uint8_t remaining_time;                                 /**< Encoded remaining time */
} light_ln_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t ln;                                 /**< The last value of the Light Lightness state */
} light_ln_last_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t ln;                                 /**< The default value of the Light Lightness state */
} light_ln_dft_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint8_t status_code;
    uint16_t min_ln;                                 /**< The default value of the Light Lightness state */
    uint16_t max_ln;                                 /**< The default value of the Light Lightness state */
} light_ln_range_status_msg_pkt_t;

#endif /* __LIGHT_LIGHTNESS_MESSAGE_H__ */

/** @} */

