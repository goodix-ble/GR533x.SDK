/**
 ****************************************************************************************
 *
 * @file generic_property_common.h
 *
 * @brief Generic Property Common Define.
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
#ifndef __GENERIC_PROPERTY_COMMON_H__
#define __GENERIC_PROPERTY_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */
/** Generic Property Server model max number */ 
#define GENERIC_PROPERTY_SERVER_INSTANCE_COUNT_MAX                     (16)
/** Generic Property Client model max number */
#define GENERIC_PROPERTY_CLIENT_INSTANCE_COUNT_MAX                     (16)

/** The total number of transmit handle for Generic Property Server */
#define GENERIC_PROPERTY_SERVER_TX_HDL_TOTAL                           (2)
/** The transmit handle for Generic Property Server publish Status message */
#define GENERIC_PROPERTY_SERVER_PUBLISH_SEND_TX_HDL                    (0x00)
/** The transmit handle for Generic Property Server response Status message */
#define GENERIC_PROPERTY_SERVER_RSP_SEND_TX_HDL                        (0x01)


/** The total number of transmit handle for Generic Property Client */
#define GENERIC_PROPERTY_CLIENT_TX_HDL_TOTAL                           (3)
/** The transmit handle for Generic Property Client Get message */
#define GENERIC_PROPERTY_CLIENT_GET_SEND_TX_HDL                        (GENERIC_PROPERTY_SERVER_PUBLISH_SEND_TX_HDL \
                                                                    + GENERIC_PROPERTY_SERVER_TX_HDL_TOTAL * GENERIC_PROPERTY_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Generic Property Client Set message */
#define GENERIC_PROPERTY_CLIENT_SET_SEND_TX_HDL                        (GENERIC_PROPERTY_CLIENT_GET_SEND_TX_HDL + 1)  
/** The transmit handle for Generic Property Client Set Unacknowledged message */ 
#define GENERIC_PROPERTY_CLIENT_SET_UNRELIABLE_SEND_TX_HDL             (GENERIC_PROPERTY_CLIENT_SET_SEND_TX_HDL + 1)  


/** The reliable message timeout time */
#define GENERIC_PROPERTY_RELIABLE_MSG_TIMEOUT_MS                       (30000)

/** Model Company ID */
#define GENERIC_PROPERTY_COMPANY_ID 0xFFFF

/**to do:
        The page 83 of the Spec note that if the Access(0x02 can be written) is not allow read, 
        the Access should be reply to client,but Property Value should be omitted.
        this is conflict with the note(C.1) which on the page 61 of the Spec.
        */
#define REPLY_ACCESS_OMIT_VALUE    1

/*
 * ENUMERATIONS
 ****************************************************************************************
 */
typedef enum
{
    not_user_prop = 0x00,
    read = 0x01,
    write = 0x02,
    read_write = 0x03,
}access_t;


/*
 * Unpacked message structure typedefs are used for API interfaces and for implementing model code.
 */

/* Parameters for the generic property Set message. */
typedef struct
{
    uint16_t property_id;                                 /*< Property ID to Generic User Property set */
    uint16_t value_length;                                /*< The length of Property Value */                                          /**< Transaction ID */
    uint8_t* property_value;                             /*< Property Value to be the Generic User Property set */
} generic_property_user_set_params_t;

/* Message format for the generic property Admin Set message. */
typedef struct
{
    uint16_t property_id;                                 /*< Property ID to Generic Admin Property set */
    uint8_t access;                                       /*Enumeration indicating Admin access.*/
    uint16_t value_length;                                /*< The length of Property Value */
    uint8_t* property_value;                             /*< Property Value to be the Generic Admin Property set */
} generic_property_admin_set_params_t;

/* Message format for the generic property Manufacture Set message. */
typedef struct
{
    uint16_t property_id;                                 /*< Property ID to Generic manufacturer Property set */
    uint8_t access;                                       /*Enumeration indicating manufacturer access.*/
} generic_property_mfr_set_params_t;

/* Message format for the generic property User/Admin/Manufacture Get message. */
typedef struct
{
    uint16_t property_id;                                 /*< Property ID to Generic user/admin/manufacturer Property get */
} generic_property_uam_get_params_t;

/* Message format for the generic properties Client Get message. */
typedef struct
{
    uint16_t property_id;                                 /*< Property ID to Generic client Properties get */
} generic_properties_client_get_params_t;

/* Parameters for the generic property User/Admin/Manufacture Status message. */
typedef struct
{
    uint16_t property_id;                                 /*< The Properity ID of the Generic  Property state */
    uint8_t access;                                       /*< The Access of the Generic  Property state (optional) */
    uint16_t value_length;                                /*< Property Value to be the Generic Property set */
    uint8_t* property_value;                             /*< The length of Property Value */
} generic_property_uam_status_params_t;

/* Parameters for the generic properties User/Admin/Manufacture/Client Status message. */
typedef struct
{
    uint16_t id_number;                               /*< The Properity ID of the Generic  Property state */
    uint16_t* property_id;                           /* The number of Properity ID*/      
} generic_properties_uamc_status_params_t;

#endif /* __GENERIC_PROPERTY_COMMON_H__ */

/** @} */
