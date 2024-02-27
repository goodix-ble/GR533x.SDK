/**
 *****************************************************************************************
 *
 * @file light_HSL_message.h
 *
 * @brief Light HSL Message Define.
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
#ifndef __LIGHT_HSL_MESSAGE_H__
#define __LIGHT_HSL_MESSAGE_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** The allowed shortest length for the HSL Set message. */
#define LIGHT_HSL_SET_MINLEN 7
/** The allowed longest length for the HSL Set message. */
#define LIGHT_HSL_SET_MAXLEN 9

/** The allowed shortest length for the HSL Status message. */
#define LIGHT_HSL_STATUS_MINLEN 6
/** The allowed longest length for the HSL Status message. */
#define LIGHT_HSL_STATUS_MAXLEN 7

/** The allowed shortest length for the HSL Target Status message. */
#define LIGHT_HSL_TARGET_STATUS_MINLEN 6
/** The allowed longest length for the HSL Target Status message. */
#define LIGHT_HSL_TARGET_STATUS_MAXLEN 7

/** The allowed shortest length for the HSL Hue Set message. */
#define LIGHT_HSL_HUE_SET_MINLEN 3
/** The allowed longest length for the HSL Hue Set message. */
#define LIGHT_HSL_HUE_SET_MAXLEN 5

/** The allowed shortest length for the HSL Hue Status message. */
#define LIGHT_HSL_HUE_STATUS_MINLEN 2
/** The allowed longest length for the HSL Hue Status message. */
#define LIGHT_HSL_HUE_STATUS_MAXLEN 5

/** The allowed shortest length for the HSL Saturation Set message. */
#define LIGHT_HSL_SATURATION_SET_MINLEN 3
/** The allowed longest length for the HSL Saturation Set message. */
#define LIGHT_HSL_SATURATION_SET_MAXLEN 5

/** The allowed shortest length for the HSL Saturation Status message. */
#define LIGHT_HSL_SATURATION_STATUS_MINLEN 2
/** The allowed longest length for the HSL Saturation Status message. */
#define LIGHT_HSL_SATURATION_STATUS_MAXLEN 5

/** The allowed shortest length for the default Set message. */
#define LIGHT_HSL_DFT_SET_LEN 6

/** The allowed shortest length for the range Set message. */
#define LIGHT_HSL_RANGE_SET_LEN 8

/** The allowed shortest length for the default Status message. */
#define LIGHT_HSL_DFT_STATUS_LEN 6

/** The allowed shortest length for the range Status message. */
#define LIGHT_HSL_RANGE_STATUS_LEN 9

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Light HSL  model message opcodes. */
typedef enum
{
    LIGHT_HSL_OPCODE_GET = 0x826D,                                                        /** Message opcode for the Light HSL Get message. */
    LIGHT_HSL_OPCODE_SET = 0x8276,                                                        /** Message opcode for the Light HSL  Set message. */
    LIGHT_HSL_OPCODE_SET_UNACKNOWLEDGED = 0x8277,                       /** Message opcode for the Light HSL  Set Unacknowledged message. */
    LIGHT_HSL_OPCODE_STATUS = 0x8278,                                                 /** Message opcode for the Light HSL  Status message. */
    
    LIGHT_HSL_HUE_OPCODE_GET = 0x826E,                                         /** Message opcode for the Light HSL  Hue Get message. */
    LIGHT_HSL_HUE_OPCODE_SET = 0x826F,                                         /** Message opcode for the Light HSL  Hue Set message. */
    LIGHT_HSL_HUE_OPCODE_SET_UNACKNOWLEDGED = 0x8270,        /** Message opcode for the Light HSL  Hue Set Unacknowledged message. */
    LIGHT_HSL_HUE_OPCODE_STATUS = 0x8271,                                  /** Message opcode for the Light HSL  Hue Status message. */

    LIGHT_HSL_SATURATION_OPCODE_GET = 0x8272,                                         /** Message opcode for the Light HSL  Saturation Get message. */
    LIGHT_HSL_SATURATION_OPCODE_SET = 0x8273,                                         /** Message opcode for the Light HSL  Saturation Set message. */
    LIGHT_HSL_SATURATION_OPCODE_SET_UNACKNOWLEDGED = 0x8274,        /** Message opcode for the Light HSL  Saturation Set Unacknowledged message. */
    LIGHT_HSL_SATURATION_OPCODE_STATUS = 0x8275,                                  /** Message opcode for the Light HSL  Saturation Status message. */

    
    LIGHT_HSL_TARGET_OPCODE_GET = 0x8279,                                            /** Message opcode for the Light HSL  Target Get message. */
    LIGHT_HSL_TARGET_OPCODE_STATUS = 0x827A,                                      /** Message opcode for the Light HSL  Target Status message. */
    
    LIGHT_HSL_DEFAULT_OPCODE_GET = 0x827B,                                     /** Message opcode for the Light HSL  Default Get message. */
    LIGHT_HSL_DEFAULT_OPCODE_STATUS = 0x827C,                               /** Message opcode for the Light HSL  Default Status message. */
    
    LIGHT_HSL_RANGE_OPCODE_GET = 0x827D,                                         /** Message opcode for the Light HSL  Range Get message. */
    LIGHT_HSL_RANGE_OPCODE_STATUS = 0x827E,                                   /** Message opcode for the Light HSL  Range Status message. */
} light_HSL_opcode_t;

/** Light HSL  model message opcodes. */
typedef enum
{
    LIGHT_HSL_DEFAULT_OPCODE_SET = 0x827F,                   /** Message opcode for the Light HSL  Default Set message. */
    LIGHT_HSL_DEFAULT_OPCODE_SET_UNACKNOWLEDGED = 0x8280,    /** Message opcode for the Light HSL  Default Set Unacknowledged message. */
    LIGHT_HSL_RANGE_OPCODE_SET = 0x8281,                     /** Message opcode for the Light HSL  Range Set message. */
    LIGHT_HSL_RANGE_OPCODE_SET_UNACKNOWLEDGED = 0x8282,        /** Message opcode for the Light HSL  Range Set Unacknowledged message. */
} light_HSL_setup_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Light HSL Set message. */
typedef struct __attribute((packed))
{
    uint16_t HSL_ln;                                          /**< Lightness State to set */
    uint16_t HSL_hue;                                         /**< Hue State to set */
    uint16_t HSL_stt;                                         /**< Saturation State to set */
    uint8_t tid;                                            /**< Transaction number for application */
    uint8_t transition_time;                                /**< Encoded transition time value */
    uint8_t delay;                                          /**< Encoded message execution delay in 5 millisecond steps */
} light_HSL_set_msg_pkt_t;

/** Message format for the Light HSL Hue Set message. */
typedef struct __attribute((packed))
{
    uint16_t hue;                                           /**< Hue State to set */
    uint8_t tid;                                            /**< Transaction number for application */
    uint8_t transition_time;                                /**< Encoded transition time value */
    uint8_t delay;                                          /**< Encoded message execution delay in 5 millisecond steps */
} light_HSL_hue_set_msg_pkt_t;

/** Message format for the Light HSL Saturation Set message. */
typedef struct __attribute((packed))
{
    uint16_t stt;                                           /**< Saturation State to set */
    uint8_t tid;                                            /**< Transaction number for application */
    uint8_t transition_time;                                /**< Encoded transition time value */
    uint8_t delay;                                          /**< Encoded message execution delay in 5 millisecond steps */
} light_HSL_stt_set_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t ln;                                          /**<Lightness State to set */
    uint16_t hue;                                         /**<Hue State to set */
    uint16_t stt;                                         /**<Saturation State to set */
} light_HSL_set_dft_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t min_hue;                                         /**< Hue Rang Min to set */
    uint16_t max_hue;                                         /**< Hue Rang Max State to set */
    uint16_t min_stt;                                         /**< Saturation Rang Min State to set */
    uint16_t max_stt;                                         /**< Hue Rang Max State to set */
} light_HSL_set_range_msg_pkt_t;

/** Message format for the Light HSL Status message. */
typedef struct __attribute((packed))
{
    uint16_t HSL_ln;                                  /**< The present value of the Light HSL Lightness state */
    uint16_t HSL_hue;                                 /**< The present value of the Light HSL Hue state */
    uint16_t HSL_stt;                                 /**< The present value of the Light HSL Saturation state */
    uint8_t remaining_time;                                 /**< Encoded remaining time */
} light_HSL_status_msg_pkt_t;

/** Message format for the Light HSL Target Status message. */
typedef struct __attribute((packed))
{
    uint16_t HSL_ln;                                  /**< The target value of the Light HSL Lightness state */
    uint16_t HSL_hue;                                 /**< The target value of the Light HSL Hue state */
    uint16_t HSL_stt;                                 /**< The target value of the Light HSL Saturation state */
    uint8_t remaining_time;                                 /**< Encoded remaining time */
} light_HSL_target_status_msg_pkt_t;

/** Message format for the Light HSL Hue Status message. */
typedef struct __attribute((packed))
{
    uint16_t present_hue;                                  /**< The present value of the Light HSL Hue state */
    uint16_t target_hue;                                 /**< The target value of the Light HSL Hue state */
    uint8_t remaining_time;                                 /**< Encoded remaining time */
} light_HSL_hue_status_msg_pkt_t;

/** Message format for the Light HSL Saturation Status message. */
typedef struct __attribute((packed))
{
    uint16_t present_stt;                                  /**< The present value of the Light HSL Saturation state */
    uint16_t target_stt;                                 /**< The target value of the Light HSL Saturation state */
    uint8_t remaining_time;                                 /**< Encoded remaining time */
} light_HSL_stt_status_msg_pkt_t;


typedef struct __attribute((packed))
{
    uint16_t ln;                                          /**<Lightness Default State*/                                /**< The default value of the Light HSL state */
    uint16_t hue;                                         /**<Hue Default State */
    uint16_t stt;                                         /**<Saturation Default State*/
} light_HSL_dft_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint8_t status_code;
    uint16_t min_hue;                                 /**< The Hue Rang Min value of the Light HSL Hue state */
    uint16_t max_hue;                                 /**< The Hue Rang Max value of the Light HSL Hue state */
    uint16_t min_stt;                                 /**< The Saturation Rang Min value of the Light HSL Saturation state */
    uint16_t max_stt;                                 /**< The Saturation Rang Max value of the Light HSL Saturation state */
} light_HSL_range_status_msg_pkt_t;

#endif /* __LIGHT_HSL_MESSAGE_H__ */

/** @} */

