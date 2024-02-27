/**
 *****************************************************************************************
 *
 * @file app_location.h
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
#ifndef __APP_LOCATION_CLIENT_H__
#define __APP_LOCATION_CLIENT_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "generic_location_client.h"
#include "generic_location_message.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */
typedef enum
{
   APP_GENERIC_LOCATION_GLOBAL_GET,
   APP_GENERIC_LOCATION_GLOBAL_SET,
   APP_GENERIC_LOCATION_GLOBAL_SET_UNACK,
   APP_GENERIC_LOCATION_LOCAL_GET,
   APP_GENERIC_LOCATION_LOCAL_SET,
   APP_GENERIC_LOCATION_LOCAL_SET_UNACK
}app_location_cmd_t;

/*
 * DEFINES
 ****************************************************************************************
 */
#define GENERIC_LOCATION_CLIENT_INSTANCE_COUNT (2)    // should no more than GENERIC_LOCATION_CLIENT_INSTANCE_COUNT_MAX

#define APP_LOCATION_FLOOR_NUMBER_MIN (-20)                    /**Floor number = -20  has a special meaning, indicating the floor -20, and also any floor below that*/
#define APP_LOCATION_FLOOR_NUMBER_NOT_CFG   (235)       /** Floor number Not configured*/

#define APP_LOCATION_GLOBAL_LATITUDE_NOT_CFG (1<<0)
#define APP_LOCATION_GLOBAL_LATITUDE_MIN (-90.00)           /**< Global Coordinates (Latitude). The Latitude in the range [-90,90] degrees */
#define APP_LOCATION_GLOBAL_LATITUDE_MAX (90.00)            /**< Global Coordinates (Latitude). The Latitude in the range [-90,90] degrees */

#define APP_LOCATION_GLOBAL_LONGITUDE_NOT_CFG (1<<1)
#define APP_LOCATION_GLOBAL_LONGITUDE_MIN (-180.00)     /**< Global Coordinates (Longitude). The Longitude in the range [-180, 180] degrees .*/
#define APP_LOCATION_GLOBAL_LONGITUDE_MAX (180.00)      /**< Global Coordinates (Longitude). The Longitude in the range [-180, 180] degrees .*/

#define APP_LOCATION_LOCAL_UPDATE_TIME_MAX   (4096000)       /** uints : ms, 4096 s*/
#define APP_LOCATION_LOCAL_UPDATE_TIME_MIN   (125)               /** uints : ms, 0.125s*/

#define APP_LOCATION_LOCAL_PRECISION_MAX   (4096000)             /** 4096 meters*/
#define APP_LOCATION_LOCAL_PRECISION_MIN   (125)                     /** 0.125 meters*/

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

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
} app_location_set_param_t;

/**
 * cover generic model state to app model data.
 *
 * @param[out]     local_state          Application Generic Location Model status pointer.
 * @param[in]       in_global            location global status pointer.
 * @param[in]       in_local              location local status pointer.
 *
 */
void generic_location_status_update(app_location_set_param_t *local_state, location_global_status_params_t *in_global, location_local_status_params_t *in_local);

/**
 * Application Generic Location Model send cmd interface.
 *
 * @param[in]     p_client              Application Generic Location Model information pointer.
 * @param[in]     cmd                   Command enum.
 * @param[in]     p_params           Application Generic Location Model status pointer.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
*/
 uint16_t app_generic_location_sent(generic_location_client_t * p_client, app_location_cmd_t cmd, app_location_set_param_t * p_params);

#ifdef MESH_MODEL_BQB_TEST
uint16_t app_generic_location_pt_sent(generic_location_client_t * p_client, app_location_cmd_t cmd, uint8_t buf[]);
#endif

/**
 * Initializes Application Generic Location Client model.
 *
 * @param[in]     p_client                 Application Generic Location Client information pointer.
 * @param[in]     element_offset       Element address offset from primary element address.
 * @param[in]     client_cb                Application Generic Location client callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_generic_location_client_init(generic_location_client_t *p_client, uint8_t element_offset, const generic_location_client_callbacks_t *client_cb);

#endif /* __APP_LOCATION_CLIENT_H__ */

/** @} */
