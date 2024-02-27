/**
 ****************************************************************************************
 *
 * @file generic_power_onoff_message.h
 *
 * @brief Generic Power OnOff Message Define.
 *
 *
 ****************************************************************************************
  @attention
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
#ifndef __GENERIC_POWER_ONOFF_MESSAGE_H__
#define __GENERIC_POWER_ONOFF_MESSAGE_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "generic_power_onoff_common.h"


/*
 * DEFINES
 ****************************************************************************************
 */
/** define the message length of generic power onoff client model. */
#define GENERIC_POWER_ONOFF_MSG_LEN 1
/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/* Generic Power On Off model message opcodes. */
typedef enum
{
    GENERIC_POWER_ONOFF_OPCODE_GET = 0x8211,
    GENERIC_POWER_ONOFF_OPCODE_SET = 0x8213,
    GENERIC_POWER_ONOFF_OPCODE_SET_UNACKNOWLEDGED = 0x8214,
    GENERIC_POWER_ONOFF_OPCODE_STATUS = 0x8212,
} generic_power_onoff_opcode_t;


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/* Packed message structure typedefs are used for packing and unpacking byte stream. */

/* Message format for the generic_level Set message. */
typedef struct __attribute((packed))
{
    uint8_t on_power_up;                                /**< Value of the on_power_up state */
} generic_power_onoff_set_msg_pkt_t;


/* Message format for the generic_level Status message. */
typedef struct __attribute((packed))
{
    uint8_t on_power_up;                                /**< Value of the on_power_up state */
} generic_power_onoff_status_msg_pkt_t;

#endif /* __GENERIC_POWER_ONOFF_MESSAGE_H__ */

/** @} */
