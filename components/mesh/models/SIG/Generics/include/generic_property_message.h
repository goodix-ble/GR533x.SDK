/**
 ****************************************************************************************
 *
 * @file generic_property_message.h
 *
 * @brief Generic Property Message Define.
 * 
 ****************************************************************************************
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
#ifndef __GENERIC_PROPERTY_MESSAGE_H__
#define __GENERIC_PROPERTY_MESSAGE_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>


/*
 * DEFINES
 ****************************************************************************************
 */


/* Shortest allowed length for the Status message. */
#define GENERIC_PROPERTY_UAM_STATUS_MINLEN 2

/* Shortest allowed length for the Status message. */
#define GENERIC_PROPERTIES_UAMC_STATUS_MINLEN 0

/* Shortest allowed length for the User Set message. */
#define GENERIC_PROPERTY_USER_SET_MINLEN 2

/* Shortest allowed length for the Admin Set message. */
#define GENERIC_PROPERTY_ADMIN_SET_MINLEN 3

/* Shortest allowed length for the Manufacturer Set message. */
#define GENERIC_PROPERTY_MFR_SET_LEN 3

/* Shortest allowed length for the User/Admin/Manufacturer Get message. */
#define GENERIC_PROPERTY_UAM_GET_LEN 2

/* Shortest allowed length for the Client Get message. */
#define GENERIC_PROPERTIES_CLIENT_GET_LEN 2

#ifndef UNKNOW_PROPERTY_ID
#define UNKNOW_PROPERTY_ID     0xFFFF
#define INVILID_PROPERTY_ID     0x0000
#endif
/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/* Generic property model message opcodes. */
typedef enum
{
    GENERIC_PROPERTIES_OPCODE_MFR_GET = 0x822A,                    /** Message opcode for the Generic Properties Get message. */
    GENERIC_PROPERTIES_OPCODE_MFR_STATUS = 0x43,                   /** Message opcode for the Generic Properties Status message. */
    GENERIC_PROPERTY_OPCODE_MFR_GET = 0x822B,                      /** Message opcode for the Generic Property Get message. */
    GENERIC_PROPERTY_OPCODE_MFR_SET = 0x44,                        /** Message opcode for the Generic Property Set message. */
    GENERIC_PROPERTY_OPCODE_MFR_SET_UNACKNOWLEDGED = 0x45,         /** Message opcode for the Generic Property Set Unacknowledged message. */
    GENERIC_PROPERTY_OPCODE_MFR_STATUS = 0x46,                     /** Message opcode for the Generic Property Status message. */
    
    GENERIC_PROPERTIES_OPCODE_ADMIN_GET = 0x822C,
    GENERIC_PROPERTIES_OPCODE_ADMIN_STATUS = 0x47,
    GENERIC_PROPERTY_OPCODE_ADMIN_GET = 0x822D,
    GENERIC_PROPERTY_OPCODE_ADMIN_SET = 0x48,                /** Message opcode for the Generic Property Admin Set message. */
    GENERIC_PROPERTY_OPCODE_ADMIN_SET_UNACKNOWLEDGED = 0x49,   /** Message opcode for the Generic Property Admin Set Unacknowledged message. */
    GENERIC_PROPERTY_OPCODE_ADMIN_STATUS = 0x4A,
    
    GENERIC_PROPERTIES_OPCODE_USER_GET = 0x822E,
    GENERIC_PROPERTIES_OPCODE_USER_STATUS = 0x4B,
    GENERIC_PROPERTY_OPCODE_USER_GET = 0x822F,
    GENERIC_PROPERTY_OPCODE_USER_SET = 0x4C,                   /** Message opcode for the Generic Property User Set message. */
    GENERIC_PROPERTY_OPCODE_USER_SET_UNACKNOWLEDGED = 0x4D,    /** Message opcode for the Generic Property User Set Unacknowledged message. */
    GENERIC_PROPERTY_OPCODE_USER_STATUS = 0x4E,

    GENERIC_PROPERTIES_OPCODE_CLIENT_GET = 0X4F,
    GENERIC_PROPERTIES_OPCODE_CLIENT_STATUS = 0X50,
} generic_property_opcode_t;


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/* Packed message structure typedefs are used for packing and unpacking byte stream. */

/* Message format for the generic property User Set message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                 /*< Property ID to Generic User Property set */
    uint8_t* property_value;                             /*< Property Value to be the Generic User Property set */
} generic_property_user_set_msg_pkt_t;

/* Message format for the generic property Admin Set message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                 /*< Property ID to Generic Admin Property set */
    uint8_t access;                                       /*Enumeration indicating Admin access.*/
    uint8_t* property_value;                             /*< Property Value to be the Generic Admin Property set */
} generic_property_admin_set_msg_pkt_t;

/* Message format for the generic property Manufacturer Set message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                 /*< Property ID to Generic manufacturer Property set */
    uint8_t access;                                       /*Enumeration indicating manufacturer access.*/
} generic_property_mfr_set_msg_pkt_t;


/* Message format for the generic property User/Admin/Manufacturer Status message. */
typedef struct __attribute((packed))
{
    uint16_t property_id;                                 /*< The Properity ID of the Generic  Property state */
    uint8_t access;                                       /*< The Access of the Generic  Property state (optional) */
    uint8_t* property_value;                             /*< Property Value to be the Generic Property set */
} generic_property_uam_status_msg_pkt_t;

/* Message format for the generic property User/Admin/Manufacturer/Client Status message. */
typedef struct __attribute((packed))
{
    uint16_t id_number;                                     /* The number of Properity ID*/
    uint16_t* property_id;                                 /*< The Properity ID of the Generic Property state */
} generic_properties_uamc_status_msg_pkt_t;

#endif /* __GENERIC_PROPERTY_MESSAGE_H__ */

/** @} */
