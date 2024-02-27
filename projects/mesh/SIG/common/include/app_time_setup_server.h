/**
 *****************************************************************************************
 *
 * @file app_time_setup_server.h
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
#ifndef __APP_MESH_TIME_SETUP_SERVER_H__
#define __APP_MESH_TIME_SETUP_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "app_time_server.h"
#include "time_server.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
typedef struct
 {
    mesh_time_setup_server_t server;                                      /**<   mesh time Server model information. */
    app_time_setup_set_cb_t time_set_cb;                               /**< Callback to be called for informing the user application to update the value*/
    app_time_setup_get_cb_t time_get_cb;                              /**< Callback to be called for requesting current value from the user application */

    app_time_state_t *state;                                             /**< Internal variableto to hold state and timing information */
    app_time_zone_status_params_t *zone_state;
    app_tai2utc_dlt_status_params_t *tai2utc_dlt_state;
    app_time_role_t *time_role;                                                    /**< The Time Role for the element. */

    uint16_t client_address;            /**< The address message received. */
 } app_time_setup_server_t;

 typedef struct
{
    app_time_setup_server_t *p_server;
    //uint8_t time_zone_offset_new;            /**< Current local time zone offset. */
    uint64_t TAI_zone_change:40;             /**< TAI Seconds time of the upcoming Time Zone Offset change. */
    //calendar_time_t zone_change_time;    /**< TAI Seconds time of the upcoming Time Zone Offset change. */
    void *dst_ptr;
}mesh_time_zone_new_t;

typedef struct
{
    app_time_setup_server_t *p_server;
    //uint16_t TAI2UTC_dlt_new;            /**< Upcoming difference between TAI and UTC in seconds. */
    uint64_t TAI_dlt_change:40;              /**< TAI Seconds time of the upcoming TAI-UTC Delta change. */
    void *dst_ptr;
}mesh_tai2utc_dlt_new_t;

/**
 * Application mesh time Server model information.
 */

/**
 * Update time zone change.
 *
 * @param[in]     None.
 *
 */
 void app_mesh_time_zone_change_update(void);

/**
 * Update time TAI to UTC Delta change.
 *
 * @param[in]     None.
 *
 */
void app_mesh_time_delta_change_update(void);

/**
 * Initializes Application   mesh time setup Server model.
 *
 * @param[in]     p_server                 Application   Mesh Time setup server information pointer.
 * @param[in]     element_offset        Element address offset from primary element address.
 * @param[in]     set_cb                    Application   Mesh Time server setting callback.
 * @param[in]     get_cb                    Application   Mesh Time server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_time_setup_server_init(app_time_setup_server_t *p_server, uint8_t element_offset, app_time_setup_set_cb_t set_cb, app_time_setup_get_cb_t get_cb);

/**
 * Application  mesh time setup Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application   Mesh Time setup server information pointer.
 *
 */
uint16_t app_time_role_status_publish(app_time_setup_server_t * p_server);
#endif /* __APP_MESH_TIME_SETUP_SERVER_H__ */

/** @} */

