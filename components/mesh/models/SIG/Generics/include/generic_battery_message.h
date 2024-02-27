/**
 *****************************************************************************************
 *
 * @file generic_battery_message.h
 *
 * @brief Generic Battery Message Define.
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
#ifndef __GENERIC_BATTERY_MESSAGE_H__
#define __GENERIC_BATTERY_MESSAGE_H__


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
#define GENERIC_BATTERY_STATUS_MAXLEN 8

#define GENERIC_BATTERY_LEVEL_PER_MAX (0x64)        /** The percentage of the charge level. 100% represents fully charged*/
#define GENERIC_BATTERY_LEVEL_PER_MIN (0x00)         /** The percentage of the charge level. 100% represents fully discharged*/
#define GENERIC_BATTERY_LEVEL_PER_UNKNOW (0xFF) /** The percentage of the charge level is unknown*/

#define GENERIC_BATTERY_TIME_DISCHARGE_MIN (0x000000)       /** The minimum remaining time (in minutes) of the discharging process*/
#define GENERIC_BATTERY_TIME_DISCHARGE_MAX (0xFFFFFE)      /** The maximum remaining time (in minutes) of the discharging process*/
#define GENERIC_BATTERY_TIME_DISCHARGE_UNKNOW (0xFFFFFF)   /** The remaining time of the discharging process is not known*/

#define GENERIC_BATTERY_TIME_CHARGE_MIN (0x000000)       /** The minimum remaining time (in minutes) of the charging process*/
#define GENERIC_BATTERY_TIME_CHARGE_MAX (0xFFFFFE)      /** The maximum remaining time (in minutes) of the charging process*/
#define GENERIC_BATTERY_TIME_CHARGE_UNKNOW (0xFFFFFF)   /** The remaining time of the charging process is not known*/

#define GENERIC_BATTERY_FLAGS_PRESENCE 0               /** Generic Battery Flags Presence Bit Offset. The Generic Battery Flags Presence state bit field indicates presence of a battery.*/
#define GENERIC_BATTERY_NOT_PRESENT (0x00)             /** The battery is not present.*/
#define GENERIC_BATTERY_PRESENT_REMV (0x01)           /** The battery is present and is removable.*/
#define GENERIC_BATTERY_PRESENT_NON_REMV (0x02)  /** The battery is present and is non-removable.*/
#define GENERIC_BATTERY_PRESENT_UNKNOW (0x03)     /** The battery presence is unknown.*/

#define GENERIC_BATTERY_FLAGS_INDICATOR 2                               /** Generic Battery Flags Indicator Bit Offset.The Generic Battery Flags Indicator state bit field indicates the charge level of a battery.*/
#define GENERIC_BATTERY_CHARGE_CRITICALLY_LOW_LVL (0x00)   /** The battery charge is Critically Low Level.*/
#define GENERIC_BATTERY_CHARGE_LOW_LVL (0x01)                        /** The battery charge is Low Level.*/
#define GENERIC_BATTERY_CHARGE_GOOD_LVL (0x02)                      /** The battery charge is Good Level.*/
#define GENERIC_BATTERY_CHARGE_PRESENT_UNKNOW (0x03)        /** The battery charge is unknown.*/

#define GENERIC_BATTERY_FLAGS_CHARGEING 4                            /** Generic Battery Flags Charging Bit Offset.The Generic Battery Flags Charging state bit field indicates whether a battery is charging.*/
#define GENERIC_BATTERY_NOT_CHARGEABLE (0x00)                      /** The battery is not chargeable.*/
#define GENERIC_BATTERY_CHARGEABLE_NO_CHARGEING (0x01)   /** The battery is chargeable and is not charging.*/
#define GENERIC_BATTERY_CHARGEABLE_IN_CHARGEING (0x02)    /** The battery is chargeable and is charging.*/
#define GENERIC_BATTERY_CHARGEING_UNKNOW (0x03)                /** The battery charging state is unknown.*/

#define GENERIC_BATTERY_FLAGS_SERVICEABILITY 6                   /** Generic Battery Flags Serviceability Bit Offset.*/
#define GENERIC_BATTERY_SERVICEABILITY_RESERVED (0x00)     /** Reserved for Future Use*/
#define GENERIC_BATTERY_NOT_REQUEST_SERVICE (0x01)           /** The battery does not require service.*/
#define GENERIC_BATTERY_REQUEST_SERVICE (0x02)                    /** The battery requires service.*/
#define GENERIC_BATTERY_SERVICEABILITY_UNKNOW (0x03)       /** The battery serviceability is unknown.*/

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Generic Battery model message opcodes. */
typedef enum
{
    GENERIC_BATTERY_OPCODE_GET = 0x8223,                     /** Message opcode for the Generic Battery Get message. */
    GENERIC_BATTERY_OPCODE_STATUS = 0x8224,               /** Message opcode for the Generic Battery Status message. */
} generic_battery_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Generic Battery Status message. */
typedef struct __attribute((packed))
{
    uint8_t battery_level;                             /**< Present level of the battery state. */
    uint32_t time_to_discharge:24;              /**< The value of the Generic Battery Time to Discharge state. */
    uint32_t time_to_charge:24;                   /**<The value of the Generic Battery Time to Charge state. */
    uint8_t flags;                                           /**<The value of the Generic Battery Flags state.*/
} generic_battery_status_msg_pkt_t;

#endif /* __GENERIC_BATTERY_MESSAGE_H__ */

/** @} */

