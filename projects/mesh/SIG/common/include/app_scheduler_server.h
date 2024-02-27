/**
 *****************************************************************************************
 *
 * @file app_schedulerserver.h
 *
 * @brief App scheduler API.
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
#ifndef __APP_MESH_SCHEDULER_SERVER_H__
#define __APP_MESH_SCHEDULER_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "scheduler_server.h"
#include "grx_hal.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

#define TSCNS_SCHEDULER_SERVER_INSTANCE_COUNT (1)    // should no more than TSCNS_SCHEDULER_SERVER_INSTANCE_COUNT_MAX

#define TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_MIN 0x00    //min year
#define TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_MAX 0x63    //max year
#define TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_ANY 0x64    //Any year

#define TSCNS_SCHEDULER_REGISTER_MONTH_BIT_OFFSET(month) (0x01<<((month)-1))
#define TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_MIN 01       //January
#define TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_MAX 12       //December
#define TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_ANY 0x00    //Any month

#define TSCNS_SCHEDULER_REGISTER_DAY_OF_MONTH_VALUE_MIN 0x01
#define TSCNS_SCHEDULER_REGISTER_DAY_OF_MONTH_VALUE_MAX 0x1F
#define TSCNS_SCHEDULER_REGISTER_DAY_OF_MONTH_VALUE_ANY 0x00    //Any day

#define TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_MIN 0x00
#define TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_MAX 0x17
#define TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_ANY 0x18     //Any hour of the day
#define TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_ONCE 0x19    //Once a day (at a random hour)

#define TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_MIN 0x00
#define TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_MAX 0x3B
#define TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_ANY 0x3C      //Any minute of the hour
#define TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_EV15 0x3D     //Every 15 minutes (minute modulo 15 is 0) (0, 15, 30, 45)
#define TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_EV20 0x3E     //Every 20 minutes (minute modulo 20 is 0) (0, 20, 40)
#define TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_ONCE 0x3F     //Once an hour (at a random minute)

#define TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_MIN 0x00
#define TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_MAX 0x3B
#define TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_ANY 0x3C      //Any second of the minute
#define TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_EV15 0x3D     //Every 15 seconds (minute modulo 15 is 0) (0, 15, 30, 45)
#define TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_EV20 0x3E     //Every 20 seconds (minute modulo 20 is 0) (0, 20, 40)
#define TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_ONCE 0x3F     //Once an minute (at a random seconds)

#define TSCNS_SCHEDULER_REGISTER_DAY_OF_WEEK_BIT_OFFSET(week) (0x01<<(((week)+7-1)%7))
#define TSCNS_SCHEDULER_REGISTER_DAY_OF_WEEK_VALUE_MIN 0x00         //Sunday
#define TSCNS_SCHEDULER_REGISTER_DAY_OF_WEEK_VALUE_MAX 0x06         //Saturday
#define TSCNS_SCHEDULER_REGISTER_DAY_OF_WEEK_VALUE_ANY 0x07         //any day of week
#define TSCNS_SCHEDULER_SCHEDULED_ON_MONDAY         (0x01<<0)
#define TSCNS_SCHEDULER_SCHEDULED_ON_TUESDAY        (0x01<<1)
#define TSCNS_SCHEDULER_SCHEDULED_ON_WEDNESDAY   (0x01<<2)
#define TSCNS_SCHEDULER_SCHEDULED_ON_THURSDAY      (0x01<<3)
#define TSCNS_SCHEDULER_SCHEDULED_ON_FRIDAY           (0x01<<4)
#define TSCNS_SCHEDULER_SCHEDULED_ON_SATURDAY      (0x01<<5)
#define TSCNS_SCHEDULER_SCHEDULED_ON_SUNDAY          (0x01<<6)
#define TSCNS_SCHEDULER_SCHEDULED_ON_ALL_WEEK       0x7F

#define TSCNS_SCHEDULER_REGISTER_ACTION_TURN_OFF 0x00
#define TSCNS_SCHEDULER_REGISTER_ACTION_TURN_ON 0x01
#define TSCNS_SCHEDULER_REGISTER_ACTION_SCENE_RECALL 0x02
#define TSCNS_SCHEDULER_REGISTER_ACTION_NO_ACTION 0x0F

#define TSCNS_SCHEDULER_REGISTER_NO_SCENE 0x0000

#define TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG (0x1<<7)

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Internal structure to hold state and timing information. */
typedef struct
{
    bool registered;                         /**< Schedule Register entry registed flag . */
    uint8_t index;                             /**< Index of the Schedule Register entry to set . */
    uint8_t year;                               /**< Scheduled year for the action. */
    uint16_t month;                          /**< Scheduled month for the action. */
    uint8_t day;                                /**< Scheduled day for the action. */
    uint8_t hour;                              /**< Scheduled hour for the action. */
    uint8_t minute;                          /**< Scheduled minute for the action. */
    uint8_t second;                          /**< Scheduled second for the action. */
    uint8_t dayofweek;                   /**< Schedule days of the week for the action. */
    uint8_t action;                           /**< Action to be performed at the scheduled time. */
    uint8_t transition_time;            /**< Transition time for this action. */
    uint16_t scene_number;         /**< Scene number to be used for some actions. */
} app_scheduler_action_t;

/**
 * Application callback type for   mesh scheduler Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     action                             An entry in the Schedule Register.
 */
typedef void (*app_scheduler_setup_set_cb_t)(uint8_t model_instance_index,uint8_t index,
                                                                                app_scheduler_action_t *action);

/**
 * Application   mesh scheduler Server model information.
 */
 typedef struct
 {
    mesh_scheduler_server_t server;                                      /**<   mesh scheduler Server model information. */

    app_scheduler_action_t *schedule_register_list;             /**<  The Schedule Register state is a 16-entry, zero-based, indexed array.*/
    uint16_t register_list_cnt;                                               /**<  schedule_register_list array number, default 16 */

    uint16_t client_address;                                                 /**< The address message received. */
 } app_scheduler_server_t;

/**
 * Application mesh scheduler setup Server model information.
 */
typedef struct
 {
    mesh_scheduler_setup_server_t server;                                      /**<   mesh time Server model information. */
    app_scheduler_setup_set_cb_t scheduler_set_cb;                      /**< Callback to be called for informing the user application to update the action*/

    app_scheduler_action_t *schedule_register_list;                      /**<  The Schedule Register state is a 16-entry, zero-based, indexed array.*/
    uint8_t register_list_cnt;                                                         /**<  schedule_register_list array number, default 16 */

    uint16_t client_address;                                                          /**< The address message received. */
 } app_scheduler_setup_server_t;

typedef struct
{
    bool alarm_flag;                                            //alram is running
    calendar_handle_t *g_calendar_handle;        //calendar handle
    app_scheduler_setup_server_t *p_server;      //mesh scheduler Setup Server model information.
    app_scheduler_action_t active_action;           //Current active action
}app_scheduler_active_action_t;

/**
 * Initializes Application   mesh scheduler Server model.
 *
 * @param[in]     p_server                 Application Mesh Scheduler server information pointer.
 * @param[in]     element_offset        Element address offset from primary element address.
 * @param[in]     reg_list                   The Schedule Register state is a 16-entry, zero-based, indexed array..
 * @param[in]     reg_number            The Schedule Register state array number.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_scheduler_server_init(app_scheduler_server_t *p_server, uint8_t element_offset, app_scheduler_action_t *reg_list, uint16_t reg_number);

/**
 * Application   mesh scheduler Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application   Mesh Scheduler server information pointer.
 *
 */
uint16_t app_scheduler_status_publish(app_scheduler_server_t * p_server);

/**
 * Application   mesh scheduler Server publishes unsolicited Action Status message.
 *
 * @param[in]     p_server                 Application   Mesh Scheduler server information pointer.
 * @param[in]     index                    Index of the Schedule Register entry to publish.
 *
 */
uint16_t app_scheduler_action_status_publish(app_scheduler_server_t * p_server, uint8_t index);


#endif /* __APP_MESH_SCHEDULER_SERVER_H__ */

/** @} */

