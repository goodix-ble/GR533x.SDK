/**
 *****************************************************************************************
 *
 * @file light_xyl_message.h
 *
 * @brief Light xyL Define.
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
#ifndef __LIGHT_XYL_MESSAGE_H__
#define __LIGHT_XYL_MESSAGE_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** The allowed shortest length for the xyL Set message. */
#define LIGHT_XYL_SET_MINLEN 7
/** The allowed longest length for the xyL Set message. */
#define LIGHT_XYL_SET_MAXLEN 9

/** The allowed shortest length for the xyL Status message. */
#define LIGHT_XYL_STATUS_MINLEN 6
/** The allowed longest length for the xyL Status message. */
#define LIGHT_XYL_STATUS_MAXLEN 7

/** The allowed shortest length for the xyL target Status message. */
#define LIGHT_XYL_TARGET_STATUS_MINLEN 6
/** The allowed longest length for the xyL target Status message. */
#define LIGHT_XYL_TARGET_STATUS_MAXLEN 7

/** The allowed shortest length for the range Set message. */
#define LIGHT_XYL_RANGE_SET_LEN 8

/** The allowed shortest length for the range Status message. */
#define LIGHT_XYL_RANGE_STATUS_LEN 9

/** The allowed shortest length for the default Set message. */
#define LIGHT_XYL_DEFAULT_SET_LEN 6

/** The allowed shortest length for the default Status message. */
#define LIGHT_XYL_DEFAULT_STATUS_LEN 6

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Light xyL  model message opcodes. */
typedef enum
{
    LIGHT_XYL_OPCODE_GET = 0x8283,                                                        /** Message opcode for the Light xyL Get message. */
    LIGHT_XYL_OPCODE_SET = 0x8284,                                                        /** Message opcode for the Light xyL  Set message. */
    LIGHT_XYL_OPCODE_SET_UNACKNOWLEDGED = 0x8285,                       /** Message opcode for the Light xyL  Set Unacknowledged message. */
    LIGHT_XYL_OPCODE_STATUS = 0x8286,                                                 /** Message opcode for the Light xyL  Status message. */
    LIGHT_XYL_TARGET_OPCODE_GET = 0x8287,                                         /** Message opcode for the Light xyL  Target Get message. */
    LIGHT_XYL_TARGET_OPCODE_STATUS = 0x8288,                                   /** Message opcode for the Light xyL  Target Status message. */
    LIGHT_XYL_DEFAULT_OPCODE_GET = 0x8289,                                       /** Message opcode for the Light xyL  Default Get message. */
    LIGHT_XYL_DEFAULT_OPCODE_STATUS = 0x828a,                                 /** Message opcode for the Light xyL  Default Status message. */
    LIGHT_XYL_RANGE_OPCODE_GET = 0x828b,                                           /** Message opcode for the Light xyL  Range Get message. */
    LIGHT_XYL_RANGE_OPCODE_STATUS = 0x828c,                                    /** Message opcode for the Light xyL  Range Status message. */
} light_xyl_opcode_t;

/** Light xyL  Setup model message opcodes. */
typedef enum
{
    LIGHT_XYL_DEFAULT_OPCODE_SET = 0x828d,                                       /** Message opcode for the Light xyL  Default Set message. */
    LIGHT_XYL_DEFAULT_OPCODE_SET_UNACKNOWLEDGED = 0x828e,      /** Message opcode for the Light xyL  Default Set Unacknowledged message. */
    LIGHT_XYL_RANGE_OPCODE_SET = 0x828f,                                           /** Message opcode for the Light xyL  Range Set message. */
    LIGHT_XYL_RANGE_OPCODE_SET_UNACKNOWLEDGED = 0x8290,          /** Message opcode for the Light xyL  Range Set Unacknowledged message. */
} light_xyl_setup_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Light xyL Set message. */
typedef struct __attribute((packed))
{
    uint16_t xyl_ln;                                         /**< The target value of the Light xyL Lightness state */
    uint16_t xyl_x;                                    /**< The target value of the Light xyL Temperature state */
    uint16_t xyl_y;                                 /**< The target value of the Light xyL Delta UV state */
    uint8_t tid;                                               /**< Transaction number for application */
    uint8_t transition_time;                          /**< Encoded transition time value */
    uint8_t delay;                                          /**< Encoded message execution delay in 5 millisecond steps */
} light_xyl_set_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t ln;                                         /**< The value of the Light Lightness Default state */
    uint16_t x;                                   /**< The value of the Light xyL Temperature Default state */
    uint16_t y;                                 /**< The value of the Light xyL Delta UV Default state */
} light_xyl_dft_set_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t range_min_x;                                         /**< The value of the x Range Min field of the Light xyL Range state */
    uint16_t range_max_x;                                         /**< The value of the x Range Max field of the Light xyL Range state */
    uint16_t range_min_y;                                         /**< The value of the y Range Min field of the Light xyL Range state */
    uint16_t range_max_y;                                         /**< The value of the y Range Max field of the Light xyL Range state */
} light_xyl_set_range_msg_pkt_t;

/** Message format for the Light xyL Status message. */
typedef struct __attribute((packed))
{
    uint16_t present_xyl_ln;                                 /**< The present value of the Light xyL Lightness state */
    uint16_t present_xyl_x;                                 /**< The present value of the Light xyL x state */
    uint16_t present_xyl_y;                                 /**< The present value of the Light xyL y state */
    uint8_t remaining_time;                               /**< Encoded remaining time */
} light_xyl_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t target_xyl_ln;                                 /**< The target value of the Light xyL Lightness state */
    uint16_t target_xyl_x;                                  /**< The target value of the Light xyL x state */
    uint16_t target_xyl_y;                                  /**< The target value of the Light xyL y state */
    uint8_t remaining_time;                               /**< Encoded remaining time */
} light_xyl_target_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t ln;                                         /**< The value of the Light Lightness Default state */
    uint16_t x;                                   /**< The value of the Light xyL x Default state */
    uint16_t y;                                 /**< The value of the Light xyL y Default state */
} light_xyl_dft_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint8_t status_code;                                            /**<Status Code for the requesting message */
    uint16_t range_min_x;                                         /**< The value of the x Range Min field of the Light xyL Range state */
    uint16_t range_max_x;                                         /**< The value of the x Range Max field of the Light xyL Range state */
    uint16_t range_min_y;                                         /**< The value of the y Range Min field of the Light xyL Range state */
    uint16_t range_max_y;                                         /**< The value of the y Range Max field of the Light xyL Range state */
} light_xyl_range_status_msg_pkt_t;

#endif /* __LIGHT_XYL_MESSAGE_H__ */

/** @} */

