/**
 *****************************************************************************************
 *
 * @file app_scheduler_setup_server.h
 *
 * @brief App time setup API.
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
#ifndef __APP_MESH_SCHEDULER_SETUP_SERVER_H__
#define __APP_MESH_SCHEDULER_SETUP_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "app_scheduler_server.h"
#include "scheduler_server.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */
#define TSCNS_SCHEDULER_INVALID_CHECK_SECONDS    0xFF
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef struct
{
    bool check_valid;                       //alarm is triggered,begin to check seconds
    uint8_t check_secs;                    //check seconds value
    bool action_pending;                //check action is pending
}app_sheduler_alarm_seconds_check_t;

struct date_time_cvt_flag_t
{
    bool flag;                  //Any data flag
    uint16_t t_data;        //time data
};

typedef void (*scheduler_user_report_cb_t)(uint8_t action, uint8_t transition_time, uint16_t scene_number);

/**
 * Application check register action every seconds.
 *
 * @param[in]     None.
 *
 * @retval ::None.
 */
 void app_sheduler_alarm_seconds_check(void);

/**
 * Initializes Application   mesh time setup Server model.
 *
 * @param[in]     p_server                 Application   Mesh Time setup server information pointer.
 * @param[in]     element_offset        Element address offset from primary element address.
 * @param[in]     set_cb                    Application   Mesh Time server setting callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_scheduler_setup_server_init(app_scheduler_setup_server_t *p_server, uint8_t element_offset, app_scheduler_setup_set_cb_t set_cb);


/**
 * Application user register do action report callback.
 *
 * @param[in]     cb                 Scheduler report do action callback.
 *
 */
void scheduler_user_report_cb_register(scheduler_user_report_cb_t cb);
#endif /* __APP_MESH_SCHEDULER_SETUP_SERVER_H__ */

/** @} */

