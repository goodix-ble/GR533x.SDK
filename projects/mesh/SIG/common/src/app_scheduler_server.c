/**
 *****************************************************************************************
 *
 * @file app_scheduler_server.c
 *
 * @brief APP Mesh Scheduler API Implementation.
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "app_scheduler_server.h"
#include "scheduler_server.h"
#include "app_log.h"
#include "user_app.h"
#include "mesh_bind.h"

/*
 * DEFINES
 ****************************************************************************************
 */
#define FORMAT_VALUE_RANGE(value, max, min) ((value) = ((value) > (max)) ? (max) : (((value) < (min)) ? (min):(value)))

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void app_mesh_scheduler_get_cb(mesh_scheduler_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    uint16_t * p_out);

static void app_mesh_scheduler_action_get_cb(mesh_scheduler_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    const uint8_t p_in,
                                                    mesh_scheduler_action_status_params_t * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const mesh_scheduler_server_callbacks_t scheduler_srv_cbs =
{
    .scheduler_cbs.get_cb = app_mesh_scheduler_get_cb,
    .scheduler_cbs.action_get_cb = app_mesh_scheduler_action_get_cb,
    .scheduler_cbs.action_set_cb = NULL,
};

const app_scheduler_action_t base_action = 
{
    .registered = false,
    .year = TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_ANY,
    .month = TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_ANY,
    .day = TSCNS_SCHEDULER_REGISTER_DAY_OF_MONTH_VALUE_ANY,
    .hour = TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_ANY,
    .minute = TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_ANY,
    .second = TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_ANY,
    .dayofweek = TSCNS_SCHEDULER_REGISTER_DAY_OF_WEEK_VALUE_ANY,
    .action = TSCNS_SCHEDULER_REGISTER_ACTION_NO_ACTION,
    .transition_time = 0x00,
    .scene_number = TSCNS_SCHEDULER_REGISTER_NO_SCENE
};
/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static void app_mesh_scheduler_get_cb(mesh_scheduler_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    uint16_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_scheduler_server_t *p_server = PARENT_BY_FIELD_GET(app_scheduler_server_t, server, p_self);
    uint16_t idx = 0;
    uint16_t reg_schedules = 0;

    for(idx = 0; idx < p_server->register_list_cnt; idx ++)
    {
        if ((NULL != p_server->schedule_register_list) && (p_server->schedule_register_list[idx].registered))
        {
            reg_schedules |= 0x1<<idx;
        }
    }

    * p_out = reg_schedules;
}

static void app_mesh_scheduler_action_get_cb(mesh_scheduler_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    const uint8_t p_in,
                                                    mesh_scheduler_action_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: get index: %x", __func__, p_self->model_instance_index, p_in);

    app_scheduler_server_t *p_server = PARENT_BY_FIELD_GET(app_scheduler_server_t, server, p_self);
    app_scheduler_action_t *get_action = (app_scheduler_action_t *)&base_action;
    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    if (p_in >= p_server->register_list_cnt)
    {
        return ;
    }

    if ((NULL != p_server->schedule_register_list) && (p_in < p_server->register_list_cnt) && (p_server->schedule_register_list[p_in].registered))
    {
        get_action = &(p_server->schedule_register_list[p_in]);
    }

    p_out->index = p_in;
    p_out->year = get_action->year;
    p_out->month = get_action->month;
    p_out->day = get_action->day;
    p_out->hour = (get_action->hour&TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG) ? TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_ONCE : get_action->hour;
    p_out->minute = (get_action->minute&TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG) ? TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_ONCE : get_action->minute;
    p_out->second = (get_action->second&TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG) ? TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_ONCE : get_action->second;
    p_out->dayofweek = get_action->dayofweek;
    p_out->action = get_action->action;
    p_out->transition_time = get_action->transition_time;
    p_out->scene_number = get_action->scene_number;

    //memcpy(&p_out->year, &(get_action->year), sizeof(mesh_scheduler_action_status_params_t) - ((uint8_t *)p_out-(&p_out->year)));
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_scheduler_status_publish(app_scheduler_server_t * p_server)
{
    uint16_t reg_schedules = 0;
    uint16_t idx = 0;

    for(idx = 0; idx < p_server->register_list_cnt; idx ++)
    {
        if ((NULL != p_server->schedule_register_list) && (p_server->schedule_register_list[idx].registered))
        {
            reg_schedules |= 0x1<<idx;
        }
    }

    return mesh_scheduler_server_status_publish(&p_server->server, &reg_schedules);
}

uint16_t app_scheduler_action_status_publish(app_scheduler_server_t * p_server, uint8_t index)
{
    app_scheduler_action_t *get_action = (app_scheduler_action_t *)&base_action;
    mesh_scheduler_action_status_params_t * p_out;
    /* save the address of message from */

    if (index >= p_server->register_list_cnt)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if ((NULL != p_server->schedule_register_list) && (index < p_server->register_list_cnt) && (p_server->schedule_register_list[index].registered))
    {
        get_action = &(p_server->schedule_register_list[index]);
    }

    p_out->index = index;
    p_out->year = get_action->year;
    p_out->month = get_action->month;
    p_out->day = get_action->day;
    p_out->hour = (get_action->hour&TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG) ? TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_ONCE : get_action->hour;
    p_out->minute = (get_action->minute&TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG) ? TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_ONCE : get_action->minute;
    p_out->second = (get_action->second&TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG) ? TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_ONCE : get_action->second;
    p_out->dayofweek = get_action->dayofweek;
    p_out->action = get_action->action;
    p_out->transition_time = get_action->transition_time;
    p_out->scene_number = get_action->scene_number;
    return mesh_scheduler_server_action_status_publish(&p_server->server, p_out);
}

uint16_t app_scheduler_server_init(app_scheduler_server_t *p_server, uint8_t element_offset, /*app_scheduler_update_cb_t update_cb, */app_scheduler_action_t *reg_list, uint16_t reg_number)
{
    if(( p_server == NULL) || (TSCNS_SCHEDULER_SERVER_INSTANCE_COUNT <= element_offset) || (NULL == reg_list) || (0 == reg_number))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    //p_server->scheduler_update_cb = update_cb;

    p_server->schedule_register_list = reg_list;
    p_server->register_list_cnt = reg_number;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->server.settings.p_callbacks = &scheduler_srv_cbs;

    return mesh_scheduler_server_init(&p_server->server, element_offset);
}

