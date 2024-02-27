/**
 *****************************************************************************************
 *
 * @file app_battery_server.h
 *
 * @brief App Battery API.
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
#ifndef __APP_BATTERY_SERVER_H__
#define __APP_BATTERY_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "generic_battery_server.h"
#include "generic_battery_message.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

#define GENERIC_BATTERY_SERVER_INSTANCE_COUNT (2)    // should no more than GENERIC_BATTERY_SERVER_INSTANCE_COUNT_MAX

#define APP_BATTERY_LEVEL_PER_MAX GENERIC_BATTERY_LEVEL_PER_MAX        /** The percentage of the charge level. 100% represents fully charged*/
#define APP_BATTERY_LEVEL_PER_MIN GENERIC_BATTERY_LEVEL_PER_MIN         /** The percentage of the charge level. 100% represents fully discharged*/
#define APP_BATTERY_LEVEL_PER_UNKNOW GENERIC_BATTERY_LEVEL_PER_UNKNOW /** The percentage of the charge level is unknown*/

#define APP_BATTERY_TIME_DISCHARGE_MIN GENERIC_BATTERY_TIME_DISCHARGE_MIN       /** The minimum remaining time (in minutes) of the discharging process*/
#define APP_BATTERY_TIME_DISCHARGE_MAX GENERIC_BATTERY_TIME_DISCHARGE_MAX      /** The maximum remaining time (in minutes) of the discharging process*/
#define APP_BATTERY_TIME_DISCHARGE_UNKNOW GENERIC_BATTERY_TIME_DISCHARGE_UNKNOW   /** The remaining time of the discharging process is not known*/

#define APP_BATTERY_TIME_CHARGE_MIN GENERIC_BATTERY_TIME_CHARGE_MIN       /** The minimum remaining time (in minutes) of the charging process*/
#define APP_BATTERY_TIME_CHARGE_MAX GENERIC_BATTERY_TIME_CHARGE_MAX      /** The maximum remaining time (in minutes) of the charging process*/
#define APP_BATTERY_TIME_CHARGE_UNKNOW GENERIC_BATTERY_TIME_CHARGE_UNKNOW   /** The remaining time of the charging process is not known*/

/** The Generic Battery Flags Presence state bit field indicates presence of a battery.*/
#define APP_BATTERY_NOT_PRESENT GENERIC_BATTERY_NOT_PRESENT                         /** The battery is not present.*/
#define APP_BATTERY_PRESENT_REMV GENERIC_BATTERY_PRESENT_REMV                     /** The battery is present and is removable.*/
#define APP_BATTERY_PRESENT_NON_REMV GENERIC_BATTERY_PRESENT_NON_REMV    /** The battery is present and is non-removable.*/
#define APP_BATTERY_PRESENT_UNKNOW GENERIC_BATTERY_PRESENT_UNKNOW          /** The battery presence is unknown.*/

/** The Generic Battery Flags Indicator state bit field indicates the charge level of a battery.*/
#define APP_BATTERY_CHARGE_CRITICALLY_LOW_LVL GENERIC_BATTERY_CHARGE_CRITICALLY_LOW_LVL   /** The battery charge is Critically Low Level.*/
#define APP_BATTERY_CHARGE_LOW_LVL GENERIC_BATTERY_CHARGE_LOW_LVL                                           /** The battery charge is Low Level.*/
#define APP_BATTERY_CHARGE_GOOD_LVL GENERIC_BATTERY_CHARGE_GOOD_LVL                                      /** The battery charge is Good Level.*/
#define APP_BATTERY_CHARGE_PRESENT_UNKNOW GENERIC_BATTERY_CHARGE_PRESENT_UNKNOW            /** The battery charge is unknown.*/

/** The Generic Battery Flags Charging state bit field indicates whether a battery is charging.*/
#define APP_BATTERY_NOT_CHARGEABLE GENERIC_BATTERY_NOT_CHARGEABLE                                        /** The battery is not chargeable.*/
#define APP_BATTERY_CHARGEABLE_NO_CHARGEING GENERIC_BATTERY_CHARGEABLE_NO_CHARGEING   /** The battery is chargeable and is not charging.*/
#define APP_BATTERY_CHARGEABLE_IN_CHARGEING GENERIC_BATTERY_CHARGEABLE_IN_CHARGEING     /** The battery is chargeable and is charging.*/
#define APP_BATTERY_CHARGEING_UNKNOW GENERIC_BATTERY_CHARGEING_UNKNOW                             /** The battery charging state is unknown.*/

/** Generic Battery Flags Serviceability Bit Offset.*/
#define APP_BATTERY_SERVICEABILITY_RESERVED GENERIC_BATTERY_SERVICEABILITY_RESERVED     /** Reserved for Future Use*/
#define APP_BATTERY_NOT_REQUEST_SERVICE GENERIC_BATTERY_NOT_REQUEST_SERVICE                 /** The battery does not require service.*/
#define APP_BATTERY_REQUEST_SERVICE GENERIC_BATTERY_REQUEST_SERVICE                                 /** The battery requires service.*/
#define APP_BATTERY_SERVICEABILITY_UNKNOW GENERIC_BATTERY_SERVICEABILITY_UNKNOW         /** The battery serviceability is unknown.*/

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Internal structure to hold state and timing information. */
typedef struct
{
    uint8_t battery_level;                         /**< Present level of the battery state.  from 0 percent through 100 percent.*/
    uint32_t time_to_discharge;              /**< The value of the Generic Battery Time to Discharge state. */
    uint32_t time_to_charge;                   /**<The value of the Generic Battery Time to Charge state. */
    uint8_t flags_presence;                     /**<Generic Battery Flags Presence.*/
    uint8_t flags_indicator;                     /**<Generic Battery Flags Indicator.*/
    uint8_t flags_charging;                     /**<Generic Battery Flags Charging.*/
    uint8_t flags_serviceability;             /**<Generic Battery Flags Serviceability.*/
} app_battery_state_t;

/**
 * Application callback type for Generic Battery Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[out]     p_present_battery           Application fills this value with the value retrived from the hardware interface.
 */
typedef void (*app_generic_battery_get_cb_t)(uint8_t model_instance_index, app_battery_state_t * p_present_battery);

/**
 * Application Generic Battery Server model information.
 */
 typedef struct
 {
    generic_battery_server_t server;      /**< Generic Battery Server model information. */
    app_generic_battery_get_cb_t battery_get_cb;    /**< Callback to be called for requesting current value from the user application */

    app_battery_state_t state;            /**< Internal variable to hold state and timing information */

    uint16_t client_address;            /**< The address message received. */
 } app_battery_server_t;

/**
 * Initializes Application Generic Battery Server model.
 *
 * @param[in]     p_server                 Application Generic battery server information pointer.
 * @param[in]     element_offset        Element address offset from primary element address.
 * @param[in]     get_cb                    Application Generic battery server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_generic_battery_server_init(app_battery_server_t *p_server, uint8_t element_offset, app_generic_battery_get_cb_t get_cb);

/**
 * Application Generic Battery Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Generic battery server information pointer.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is Success.
 * @retval ::MESH_ERROR_INVALID_PARAM             Invalid Parameter.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES    Insufficient Resources.
 * @retval ::MESH_ERROR_INVALID_MODEL             Invalid Model.
 * @retval ::MESH_ERROR_INVALID_PUBLISH_PARAMS    Invalid Publish Parameters.
 * @retval ::MESH_ERROR_INVALID_BINDING           Invalid Binding.
 * @retval ::MESH_ERROR_INVALID_APPKEY_ID         Invalid AppKey Index.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED        Command Disallowed.
 * @retval ::MESH_ERROR_NOT_FOUND                 Resource requested not found.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_ON     Reliable message transfer procedure is on.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 */
uint16_t app_generic_battery_status_publish(app_battery_server_t * p_server);

#endif /* __APP_BATTERY_SERVER_H__ */

/** @} */

