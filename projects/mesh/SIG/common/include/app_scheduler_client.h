/**
 *****************************************************************************************
 *
 * @file app_scheduler_client.h
 *
 * @brief App Scheduler API.
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
#ifndef __APP_MESH_SCHEDULER_CLIENT_H__
#define __APP_MESH_SCHEDULER_CLIENT_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "scheduler_client.h"


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */
#define TSCNS_SCHEDULER_CLIENT_INSTANCE_COUNT (2)    // should no more than TSCNS_SCHEDULER_CLIENT_INSTANCE_COUNT_MAX

#define TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_MIN 0x00    //min year
#define TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_MAX 0x63    //max year
#define TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_ANY 0x64    //Any year

#define TSCNS_SCHEDULER_REGISTER_MONTH_BIT_OFFSET(month) (0x01<<(month-1))
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
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */


/**
 * Initializes Application Mesh Scheduler Client model.
 *
 * @param[in]     p_client                 Application Mesh Scheduler Client information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     client_cb                Application Mesh Scheduler client callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_mesh_scheduler_client_init(mesh_scheduler_client_t *p_client, uint8_t element_offset, const mesh_scheduler_client_callbacks_t *client_cb);

#endif /* __APP_MESH_SCHEDULER_CLIENT_H__ */

/** @} */
