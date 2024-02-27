/**
 *****************************************************************************************
 *
 * @file time_message.h
 *
 * @brief  Mesh Time Message Define.
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
#ifndef __TSCNS_TIME_MESSAGE_H__
#define __TSCNS_TIME_MESSAGE_H__


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
#define TSCNS_TIME_SET_MINLEN 10
/** The allowed shortest length for the time zone Set message. */
#define TSCNS_TIME_ZONE_SET_MINLEN 6
/** The allowed shortest length for the tai-utc delta Set message. */
#define TSCNS_TIME_TAI2UTC_DLT_SET_MINLEN 7
/** The allowed shortest length for the time role Set message. */
#define TSCNS_TIME_ROLE_SET_MINLEN 1

/** The allowed shortest length for the Status message. */
#define TSCNS_TIME_STATUS_MINLEN 10
/** The allowed shortest length for the time zone Status message. */
#define TSCNS_TIME_ZONE_STATUS_MINLEN 7
/** The allowed shortest length for the tai-utc delta Status message. */
#define TSCNS_TIME_TAI2UTC_DLT_STATUS_MINLEN 9
/** The allowed shortest length for the role Status message. */
#define TSCNS_TIME_ROLE_STATUS_MINLEN 1


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/**   mesh time model message opcodes. */
typedef enum
{
    TSCNS_TIME_OPCODE_GET = 0x8237,                     /** Message opcode for the time state Get message. */
    TSCNS_TIME_OPCODE_SET = 0x5c,                         /** Message opcode for the time state  Set message. */
    TSCNS_TIME_OPCODE_STATUS = 0x5d,                  /** Message opcode for the time Status message. */
    TSCNS_TIME_ROLE_OPCODE_GET = 0x8238,           /** Message opcode for the time role state Get message. */
    TSCNS_TIME_ROLE_OPCODE_SET = 0x8239,           /** Message opcode for the time role state Set message. */
    TSCNS_TIME_ROLE_OPCODE_STATUS = 0x823a,    /** Message opcode for the time role Status message. */
    TSCNS_TIME_ZONE_OPCODE_GET = 0x823b,          /** Message opcode for the time zone state Get message. */
    TSCNS_TIME_ZONE_OPCODE_SET = 0x823c,          /** Message opcode for the time zone state Set message. */
    TSCNS_TIME_ZONE_OPCODE_STATUS = 0x823d,   /** Message opcode for the time zone Status message. */
    TSCNS_TIME_TAI2UTC_DLT_OPCODE_GET = 0x823e,            /** Message opcode for the tai-utc delta state Get message. */
    TSCNS_TIME_TAI2UTC_DLT_OPCODE_SET = 0x823f,            /** Message opcode for the tai-utc delta state Set message. */
    TSCNS_TIME_TAI2UTC_DLT_OPCODE_STATUS = 0x8240,      /** Message opcode for the tai-utc delta Status message. */
} mesh_time_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the   mesh time Set message. */
typedef struct __attribute((packed))
{
    uint64_t TAI_seconds:40;             /**< The current TAI time in seconds. */
    uint8_t subsecond;                     /**< The sub-second time in units of 1/256th second. */
    uint8_t uncertainty;                     /**< The estimated uncertainty in 10-millisecond steps . */
    uint16_t time_authority:1;           /**< 0 = No Time Authority, 1 = Time Authority  . */
    uint16_t TAI2UTC_dlt:15;         /**< Current difference between TAI and UTC in seconds  . */
    uint8_t time_zone_offset;           /**< The local time zone offset in 15-minute increments  . */
} mesh_time_set_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint8_t time_zone_offset_new;            /**< Current local time zone offset. */
    uint64_t TAI_zone_change:40;             /**< TAI Seconds time of the upcoming Time Zone Offset change. */
}mesh_time_zone_set_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t TAI2UTC_dlt_new:15;            /**< Upcoming difference between TAI and UTC in seconds. */
    uint16_t Padding:1;                             /**< Always 0b0. Other values are Prohibited.. */
    uint64_t TAI_dlt_change:40;              /**< TAI Seconds time of the upcoming TAI-UTC Delta change. */
}mesh_tai2utc_dlt_set_msg_pkt_t;

/** Parameters for the time Status message. */
typedef struct __attribute((packed))
{
    uint64_t TAI_seconds:40;             /**< The current TAI time in seconds. */
    uint8_t subsecond;                     /**< The sub-second time in units of 1/256th second. */
    uint8_t uncertainty;                     /**< The estimated uncertainty in 10-millisecond steps . */
    uint16_t time_authority:1;           /**< 0 = No Time Authority, 1 = Time Authority  . */
    uint16_t TAI2UTC_dlt:15;         /**< Current difference between TAI and UTC in seconds  . */
    uint8_t time_zone_offset;           /**< The local time zone offset in 15-minute increments  . */
} mesh_time_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint8_t time_zone_offset_current;       /**< Current local time zone offset. */
    uint8_t time_zone_offset_new;            /**< Upcoming local time zone offset. */
    uint64_t TAI_zone_change:40;             /**< TAI Seconds time of the upcoming Time Zone Offset change. */
}mesh_time_zone_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t TAI2UTC_dlt_current:15;            /**< Upcoming difference between TAI and UTC in seconds. */
    uint16_t Padding_1:1;                             /**< Always 0b0. Other values are Prohibited.. */
    uint16_t TAI2UTC_dlt_new:15;            /**< Upcoming difference between TAI and UTC in seconds. */
    uint16_t Padding_2:1;                             /**< Always 0b0. Other values are Prohibited.. */
    uint64_t TAI_dlt_change:40;              /**< TAI Seconds time of the upcoming TAI-UTC Delta change. */
}mesh_tai2utc_dlt_status_msg_pkt_t;
#endif /* __TSCNS_TIME_MESSAGE_H__ */

/** @} */

