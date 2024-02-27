/**
 *****************************************************************************************
 *
 * @file app_time_server.h
 *
 * @brief App time API.
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
#ifndef __APP_MESH_TIME_SERVER_H__
#define __APP_MESH_TIME_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "time_server.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

#define TSCNS_TIME_SERVER_INSTANCE_COUNT (1)    // should no more than TSCNS_TIME_SERVER_INSTANCE_COUNT_MAX

#define APP_TIME_ZONE_OFFSET_MIN          (-64)
#define APP_TIME_ZONE_OFFSET_MAX          (191)

#define APP_TIME_TAI_ZONE_CHANGE_MAX              (0xFFFFFFFFFF)
#define APP_TIME_TAI_ZONE_CHANGE_UNKNOW       (0x0000000000)

#define APP_TIME_TAI2UTC_DLT_MIN        (-255)
#define APP_TIME_TAI2UTC_DLT_MAX        (32512)

#define APP_TIME_TAI_DLT_CHANGE_MAX              (0xFFFFFFFFFF)
#define APP_TIME_TAI_DLT_CHANGE_UNKNOW       (0x0000000000)

#define APP_TIME_TAI2UTC_DLT_2019    (37)

typedef enum
{
    APP_TIME_ROLE_NONE,
    APP_TIME_ROLE_AUTH,
    APP_TIME_ROLE_RELAY,
    APP_TIME_ROLE_CLIENT,
    APP_TIME_ROLE_MAX,
}app_time_role_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Internal structure to hold state and timing information. */
typedef struct
{
    uint64_t TAI_seconds;             /**< The current TAI time in seconds. */
    uint8_t subsecond;                     /**< The sub-second time in units of 1/256th second. */
    uint8_t uncertainty;                     /**< The estimated uncertainty in 10-millisecond steps . */
    uint16_t time_authority;           /**< 0 = No Time Authority, 1 = Time Authority  . */
    int16_t *TAI2UTC_dlt;                   /**< Current difference between TAI and UTC in seconds. The valid range is -255 through +32512. */
    int16_t *time_zone_offset;           /**< The local time zone offset in 15-minute increments . The valid range of -64 through +191. */
} app_time_state_t;

typedef struct
{
    int16_t time_zone_offset_current;       /**< Current local time zone offset. The valid range of -64 through +191.*/
    int16_t time_zone_offset_new;            /**< Upcoming local time zone offset. The valid range of -64 through +191.*/
    uint64_t TAI_zone_change;             /**< TAI Seconds time of the upcoming Time Zone Offset change. */
}app_time_zone_status_params_t;

typedef struct
{
    int16_t TAI2UTC_dlt_current;                   /**< Current difference between TAI and UTC in seconds. The valid range is -255 through +32512.*/
    int16_t TAI2UTC_dlt_new;                        /**< Upcoming difference between TAI and UTC in seconds. The valid range is -255 through +32512.*/
    uint64_t TAI_dlt_change;                    /**< TAI Seconds time of the upcoming TAI-UTC Delta change. */
}app_tai2utc_dlt_status_params_t;

/**
 * Application callback type for   mesh time Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     state                               the Time state of an element.
 * @param[in]     zone_state                      the Time Zone Offset Current state, the Time Zone Offset New state, and the TAI of Zone Change state..
 * @param[in]     tu_dlt_state                     the TAI-UTC Delta Current state, the TAI-UTC Delta New state, and the TAI of Delta Change state..
 * @param[in]     time_role                        the Time Role state of an elementt.
 */
typedef void (*app_time_update_cb_t)(uint8_t model_instance_index,
                                                                                app_time_state_t *state,
                                                                                app_time_zone_status_params_t *zone_state, 
                                                                                app_tai2utc_dlt_status_params_t *tu_dlt_state);

/**
 * Application callback type for   mesh time Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     state                               the Time state of an element.
 * @param[in]     zone_state                      the Time Zone Offset Current state, the Time Zone Offset New state, and the TAI of Zone Change state.
 * @param[in]     tu_dlt_state                     the TAI-UTC Delta Current state, the TAI-UTC Delta New state, and the TAI of Delta Change state.
 * @param[in]     time_role                        the Time Role state of an elementt.
 */
typedef void (*app_time_get_cb_t)(uint8_t model_instance_index,
                                                                                app_time_state_t *state,
                                                                                app_time_zone_status_params_t *zone_state, 
                                                                                app_tai2utc_dlt_status_params_t *tu_dlt_state);

/**
 * Application callback type for   mesh time Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     state                               the Time state of an element.
 * @param[in]     zone_state                      the Time Zone Offset Current state, the Time Zone Offset New state, and the TAI of Zone Change state..
 * @param[in]     tu_dlt_state                     the TAI-UTC Delta Current state, the TAI-UTC Delta New state, and the TAI of Delta Change state..
 * @param[in]     time_role                        the Time Role state of an elementt.
 */
typedef void (*app_time_setup_set_cb_t)(uint8_t model_instance_index,
                                                                                app_time_state_t *state,
                                                                                app_time_zone_status_params_t *zone_state, 
                                                                                app_tai2utc_dlt_status_params_t *tu_dlt_state,
                                                                                app_time_role_t *time_role_state);

/**
 * Application callback type for   mesh time setup Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     state                               the Time state of an element.
 * @param[in]     zone_state                      the Time Zone Offset Current state, the Time Zone Offset New state, and the TAI of Zone Change state.
 * @param[in]     tu_dlt_state                     the TAI-UTC Delta Current state, the TAI-UTC Delta New state, and the TAI of Delta Change state.
 * @param[in]     time_role                        the Time Role state of an elementt.
 */
typedef void (*app_time_setup_get_cb_t)(uint8_t model_instance_index, app_time_role_t *time_role_state);

/**
 * Application   mesh time Server model information.
 */
 typedef struct
 {
    mesh_time_server_t server;                                      /**<   mesh time Server model information. */
    app_time_update_cb_t time_update_cb;                               /**< Callback to be called for informing the user application to update the value*/
    app_time_get_cb_t time_get_cb;                              /**< Callback to be called for requesting current value from the user application */

    app_time_state_t state;                                             /**< Internal variableto to hold state and timing information */
    app_time_zone_status_params_t zone_state;
    app_tai2utc_dlt_status_params_t tai2utc_dlt_state;
    app_time_role_t time_role;                                                    /**< The Time Role for the element. */

    uint16_t client_address;            /**< The address message received. */
 } app_time_server_t;

/**
 * Initializes Application   mesh time Server model.
 *
 * @param[in]     p_server                 Application   Mesh Time server information pointer.
 * @param[in]     element_offset        Element address offset from primary element address.
 * @param[in]     set_cb                    Application   Mesh Time server setting callback.
 * @param[in]     get_cb                    Application   Mesh Time server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_time_server_init(app_time_server_t *p_server, uint8_t element_offset, app_time_update_cb_t update_cb, app_time_get_cb_t get_cb);

/**
 * Application   mesh time Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application   Mesh Time server information pointer.
 *
 */
uint16_t app_time_status_publish(app_time_server_t * p_server);
uint16_t app_time_zone_status_publish(app_time_server_t * p_server);
uint16_t app_time_tai2utc_delta_status_publish(app_time_server_t * p_server);



#endif /* __APP_MESH_TIME_SERVER_H__ */

/** @} */

