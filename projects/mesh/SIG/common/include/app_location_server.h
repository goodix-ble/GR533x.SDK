/**
 *****************************************************************************************
 *
 * @file app_location_server.h
 *
 * @brief App Location API.
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
#ifndef __APP_LOCATION_SERVER_H__
#define __APP_LOCATION_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "generic_location_server.h"
#include "generic_location_message.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

#define GENERIC_LOCATION_SERVER_INSTANCE_COUNT (2)    // should no more than GENERIC_LOCATION_SERVER_INSTANCE_COUNT_MAX

//#define MESH_MODEL_BQB_TEST

#define APP_LOCATION_FLOOR_NUMBER_MIN (-20)                    /**Floor number = -20  has a special meaning, indicating the floor -20, and also any floor below that*/
#define APP_LOCATION_FLOOR_NUMBER_MAX (232)                   /**Floor number = 232  has a special meaning, indicating the floor 232, and also any floor above that.*/
#define APP_LOCATION_FLOOR_NUMBER_GROUND_0 (233)       /** Ground floor. Floor 0.*/
#define APP_LOCATION_FLOOR_NUMBER_GROUND_1 (234)       /** Ground floor. Floor 1.*/
#define APP_LOCATION_FLOOR_NUMBER_NOT_CFG   (235)       /** Floor number Not configured*/

#define APP_LOCATION_GLOBAL_LATITUDE_NOT_CFG (1<<0)
#define APP_LOCATION_GLOBAL_LATITUDE_MIN (-90.00)           /**< Global Coordinates (Latitude). The Latitude in the range [-90,90] degrees */
#define APP_LOCATION_GLOBAL_LATITUDE_MAX (90.00)            /**< Global Coordinates (Latitude). The Latitude in the range [-90,90] degrees */

#define APP_LOCATION_GLOBAL_LONGITUDE_NOT_CFG (1<<1)
#define APP_LOCATION_GLOBAL_LONGITUDE_MIN (-180.00)     /**< Global Coordinates (Longitude). The Longitude in the range [-180, 180] degrees .*/
#define APP_LOCATION_GLOBAL_LONGITUDE_MAX (180.00)      /**< Global Coordinates (Longitude). The Longitude in the range [-180, 180] degrees .*/

#define APP_LOCATION_GLOBAL_ALTITUDE_NOT_CFG   (0x7FFF)       /** Global Altitude is not configured*/
#define APP_LOCATION_GLOBAL_ALTITUDE_MAX   (0x7FFE)               /** Global Altitude is greater than or equal to 32766 meters*/
#define APP_LOCATION_GLOBAL_ALTITUDE_MIN   (-32768)               /** Global Altitude is less than or equal -32768 meters*/

#define APP_LOCATION_LOCAL_NORTH_NOT_CFG   (0x8000)       /** The value 0x8000 means the Local North information is not configured*/
#define APP_LOCATION_LOCAL_NORTH_MAX   (32767)                /** The Local North value is encoded in decimeters and has a range of -32767 decimeters through 32767 decimeters*/
#define APP_LOCATION_LOCAL_NORTH_MIN   (-32767)              /** The Local North value is encoded in decimeters and has a range of -32767 decimeters through 32767 decimeters*/

#define APP_LOCATION_LOCAL_EAST_NOT_CFG   (0x8000)       /** The value 0x8000 means the Local East information is not configured*/
#define APP_LOCATION_LOCAL_EAST_MAX   (32767)                /** The Local East value is encoded in decimeters and has a range of -32767 decimeters through 32767 decimeters*/
#define APP_LOCATION_LOCAL_EAST_MIN   (-32767)              /** The Local East value is encoded in decimeters and has a range of -32767 decimeters through 32767 decimeters*/

#define APP_LOCATION_LOCAL_ALTITUDE_NOT_CFG   (0x7FFF)       /** Local Altitude is not configured*/
#define APP_LOCATION_LOCAL_ALTITUDE_MAX   (0x7FFE)               /** Local Altitude is greater than or equal to 32766 meters*/
#define APP_LOCATION_LOCAL_ALTITUDE_MIN   (-32768)               /** Local Altitude is less than or equal -32768 meters*/

#define APP_LOCATION_STATIONARY   0               /** the location information has a stationary location*/
#define APP_LOCATION_MOBILE   1                       /** the location information has a mobile location*/

#define APP_LOCATION_LOCAL_UPDATE_TIME_MAX   (4096000)       /** uints : ms, 4096 s*/
#define APP_LOCATION_LOCAL_UPDATE_TIME_MIN   (125)               /** uints : ms, 0.125s*/

#define APP_LOCATION_LOCAL_PRECISION_MAX   (4096000)             /** 4096 meters*/
#define APP_LOCATION_LOCAL_PRECISION_MIN   (125)                     /** 0.125 meters*/

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Internal structure to hold state and timing information. */
typedef struct
{
    uint8_t global_cfg_flag;                    /**< APP_LOCATION_GLOBAL_LATITUDE_NOT_CFG | APP_LOCATION_GLOBAL_LONGITUDE_NOT_CFG*/
    double global_latitude;                     /**< Global Coordinates (Latitude). The Latitude in the range [-90,90] degrees */
    double global_longitude;                  /**< Global Coordinates (Longitude). The Longitude in the range [-180, 180] degrees .*/
    int16_t global_altitude;                 /**<Global Altitude. */
    int16_t local_north;                       /**<Local Coordinates (North).*/
    int16_t local_east;                         /**<Local Coordinates (East).*/
    int16_t local_altitude;                   /**<Local Altitude.*/
    int16_t floor_number;                   /**<Floor Number.*/
    uint8_t stationary;                           /** 0 = stationary, 1 = mobile*/
    uint32_t update_time;                   /**<It represents the time (t) elapsed since the last update of the device's position. units:ms
                                                                 The represented range is from 125 ms through 4096000 ms*/
    uint32_t precision;                        /**  1 meters = precision * 1000. The represented range is from 0.125 meters through 4096 meters.*/
    //uint16_t uncertainty;                    /**<Uncertainty.*/
} app_location_state_t;

/**
 * Application callback type for Generic Location Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[out]     p_present_location           Application fills this value with the value retrived from the hardware interface.
 */
typedef void (*app_generic_location_get_cb_t)(uint8_t model_instance_index, app_location_state_t * p_location);

/**
 * Application Generic Location Server model information.
 */
 typedef struct
 {
    generic_location_server_t server;      /**< Generic Location Server model information. */
    app_generic_location_get_cb_t location_get_cb;    /**< Callback to be called for requesting current value from the user application */

    app_location_state_t *state;            /**< Internal variable to hold state and timing information */
    location_global_status_params_t global_state;
    location_local_status_params_t local_state;

    uint16_t client_address;            /**< The address message received. */
 } app_location_server_t;

/**
 * Initializes Application Generic Location Server model.
 *
 * @param[in]     p_server                 Application Generic location server information pointer.
 * @param[in]     element_offset        Element address offset from primary element address.
 * @param[in]     get_cb                    Application Generic location server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_generic_location_server_init(app_location_server_t *p_server, uint8_t element_offset, app_generic_location_get_cb_t get_cb);

/**
 * Application Generic Location Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Generic Location server information pointer.
 * @param[in]     global_flag              true : publish global status ; false : publish local status.
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
uint16_t app_generic_location_status_publish(app_location_server_t * p_server, bool global_flag);

/**
 * Update application location state.
 *
 * @param[out]     local_state               Application location state.
 * @param[in]       in_global                 location global state.
 * @param[in]       in_local                   location local state.
 *
 */
void generic_location_state_update(app_location_state_t *local_state, const location_global_status_params_t *in_global, const location_local_status_params_t *in_local);

/**
 * Application location state converts to global & local state.
 *
 * @param[in]     local_state               Application location state.
 * @param[out]   in_global                 location global state.
 * @param[out]   in_local                   location local state.
 *
 */
void generic_location_state_fill_p_out(app_location_state_t *in_state, location_global_status_params_t * global, location_local_status_params_t *local);

#endif /* __APP_LOCATION_SERVER_H__ */

/** @} */

