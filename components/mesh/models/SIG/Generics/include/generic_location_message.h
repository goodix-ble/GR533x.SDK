/**
 *****************************************************************************************
 *
 * @file generic_location_message.h
 *
 * @brief Generic Location Message Define.
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
#ifndef __GENERIC_LOCATION_MESSAGE_H__
#define __GENERIC_LOCATION_MESSAGE_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** The allowed longest length for the Status message. */
#define GENERIC_LOCATION_GLOBAL_STATUS_MAXLEN 10
#define GENERIC_LOCATION_LOCAL_STATUS_MAXLEN 9

#define GENERIC_LOC_GLOBAL_LAT_NOT_CONFIG     (0x80000000)              /** Location Global Latitude Not Configured.*/
#define GENERIC_LOC_GLOBAL_LAT_MAX                   (((int32_t)1<<31)-1)      /** Location Global Latitude Maximum value.*/
#define GENERIC_LOC_GLOBAL_LAT_MIN                   (-(((int32_t)1<<31)-1))  /** Location Global Latitude Minimum value.*/

#define GENERIC_LOC_GLOBAL_LONG_NOT_CONFIG   (0x80000000)                /** Location Global Longitude Not Configured.*/
#define GENERIC_LOC_GLOBAL_LONG_MAX                   ((int32_t)1<<31-1)      /** Location Global Longitude Maximum value.*/
#define GENERIC_LOC_GLOBAL_LONG_MIN                   (-((int32_t)1<<31-1))  /** Location Global Longitude Minimum value.*/

#define GENERIC_LOC_GLOBAL_ALT_NOT_CONFIG     (0x7FFF)               /** Location Global Altitude Not Configured.*/
#define GENERIC_LOC_GLOBAL_ALT_MAX                   (0x7FFE)               /** Location Global Altitude is greater than or equal to 32766 meters*/
#define GENERIC_LOC_GLOBAL_ALT_MIN                   (-32768)               /** Location Global Altitude is less than or equal -32768 meters*/

#define GENERIC_LOC_LOCAL_NORTH_NOT_CONFIG   (0x8000)            /** Location Local North Not Configured.*/
#define GENERIC_LOC_LOCAL_NORTH_MAX                 (32767)             /** The Local North value is encoded in decimeters and has a range of -32767 decimeters through 32767 decimeters*/
#define GENERIC_LOC_LOCAL_NORTH_MIN                 (-32767)           /** The Local North value is encoded in decimeters and has a range of -32767 decimeters through 32767 decimeters*/

#define GENERIC_LOC_LOCAL_EAST_NOT_CONFIG     (0x8000)            /** Location Local East Not Configured.*/
#define GENERIC_LOC_LOCAL_EAST_MAX                   (32767)              /** Location Local East value is encoded in decimeters and has a range of -32767 decimeters through 32767 decimeters*/
#define GENERIC_LOC_LOCAL_EAST_MIN                   (-32767)             /** Location Local East value is encoded in decimeters and has a range of -32767 decimeters through 32767 decimeters*/

#define GENERIC_LOC_LOCAL_ALT_NOT_CONFIG       (0x7FFF)            /** Location Local Altitude Not Configured.*/
#define GENERIC_LOC_LOCAL_ALT_MAX                     (0x7FFE)            /** Location Local Altitude is greater than or equal to 32766 meters*/
#define GENERIC_LOC_LOCAL_ALT_MIN                     (-32768)            /** Location Local Altitude is less than or equal -32768 meters*/

#define GENERIC_LOC_FLOOR_NOT_CONFIG               (0xFF)               /** Floor Number Not Configured.*/

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Generic Location model message opcodes. */
typedef enum
{
    GENERIC_LOCATION_GLOBAL_OPCODE_GET = 0x8225,               /** Message opcode for the Generic Location Global Get message. */
    GENERIC_LOCATION_GLOBAL_OPCODE_STATUS = 0x40,            /** Message opcode for the Generic Location Global Status message. */
    GENERIC_LOCATION_LOCAL_OPCODE_GET = 0x8226,                 /** Message opcode for the Generic Location Local Get message. */
    GENERIC_LOCATION_LOCAL_OPCODE_STATUS = 0x8227,           /** Message opcode for the Generic Location Local Status message. */

    GENERIC_LOCATION_GLOBAL_OPCODE_SET = 0x41,                  /** Message opcode for the Generic Location Global Set message. */
    GENERIC_LOCATION_GLOBAL_OPCODE_SET_UNACK = 0x42,     /** Message opcode for the Generic Location Global Set Unacknowledged message. */
    GENERIC_LOCATION_LOCAL_OPCODE_SET = 0x8228,                /** Message opcode for the Generic Location Local Set message. */
    GENERIC_LOCATION_LOCAL_OPCODE_SET_UNACK = 0x8229,   /** Message opcode for the Generic Location Local Set Unacknowledgedmessage. */
} generic_location_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Generic Location Status message. */
typedef struct __attribute((packed))
{
    int32_t global_latitude;
    int32_t global_longitude;
    int16_t global_altitude;
} generic_location_global_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    int16_t local_north;
    int16_t local_east;
    int16_t local_altitude;
    uint8_t floor_number;
    uint16_t uncertainty;
} generic_location_local_status_msg_pkt_t;

#endif /* __GENERIC_LOCATION_MESSAGE_H__ */

/** @} */

