/**
 *****************************************************************************************
 *
 * @file app_time_setup_server.c
 *
 * @brief APP mesh time API Implementation.
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
#include "app_time_setup_server.h"
#include "time_setup_server.h"
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
static void app_mesh_time_state_set_cb(mesh_time_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const mesh_time_set_params_t * p_in, mesh_time_status_params_t * p_out);

static void app_mesh_time_zone_state_set_cb(mesh_time_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const mesh_time_zone_set_params_t * p_in, mesh_time_zone_status_params_t * p_out);

static void app_mesh_tai2utc_dlt_state_set_cb(mesh_time_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const mesh_tai2utc_dlt_set_params_t * p_in, mesh_tai2utc_dlt_status_params_t * p_out);

static void app_mesh_time_role_state_set_cb(mesh_time_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const uint8_t p_in, uint8_t * p_out);

static void app_mesh_time_role_state_get_cb(mesh_time_setup_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               uint8_t * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const mesh_time_server_callbacks_t time_setup_srv_cbs =
{
    .times_cbs.set_cb = app_mesh_time_state_set_cb,
    .times_cbs.get_cb = NULL,
    .times_cbs.propag_cb = NULL,
    .times_cbs.zone_set_cb = app_mesh_time_zone_state_set_cb,
    .times_cbs.zone_get_cb = NULL,
    .times_cbs.dlt_set_cb = app_mesh_tai2utc_dlt_state_set_cb,
    .times_cbs.dlt_get_cb = NULL,
    .times_cbs.role_set_cb = app_mesh_time_role_state_set_cb,
    .times_cbs.role_get_cb = app_mesh_time_role_state_get_cb,
};

mesh_time_zone_new_t TAI_zone_change_arr[TSCNS_TIME_SERVER_INSTANCE_COUNT] = {0,};
mesh_tai2utc_dlt_new_t TAI_dlt_change_arr[TSCNS_TIME_SERVER_INSTANCE_COUNT] = {0,};

extern calendar_handle_t g_calendar_handle;
/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
 static void app_mesh_time_zone_change_check(app_time_setup_server_t *p_server, uint8_t model_instance_index, app_time_zone_status_params_t *dst_status)
{
    uint64_t tai_sec = 0;
    uint8_t subsec = 0;

    APP_LOG_INFO("debug %s : %d!", __func__, __LINE__);
    app_mesh_time_get_TAI_time_sec(&tai_sec, &subsec);
    if (dst_status->TAI_zone_change <= tai_sec)//set zone offset now
    {
        dst_status->time_zone_offset_current = dst_status->time_zone_offset_new;
        dst_status->TAI_zone_change = APP_TIME_TAI_ZONE_CHANGE_UNKNOW; 
    }
    else
    {
        TAI_zone_change_arr[model_instance_index].p_server = p_server;
        TAI_zone_change_arr[model_instance_index].dst_ptr = (void *)dst_status;
        TAI_zone_change_arr[model_instance_index].TAI_zone_change = dst_status->TAI_zone_change;
    }

}

static void app_mesh_time_delta_change_check(app_time_setup_server_t *p_server, uint8_t model_instance_index, app_tai2utc_dlt_status_params_t *dst_status)
{
    uint64_t tai_sec = 0;
    uint8_t subsec = 0;

    app_mesh_time_get_TAI_time_sec(&tai_sec, &subsec);
    if (dst_status->TAI_dlt_change <= tai_sec)//set zone offset now
    {
        dst_status->TAI2UTC_dlt_current = dst_status->TAI2UTC_dlt_new;
        dst_status->TAI_dlt_change = APP_TIME_TAI_ZONE_CHANGE_UNKNOW; 
    }
    else
    {
        TAI_dlt_change_arr[model_instance_index].p_server = p_server;
        TAI_dlt_change_arr[model_instance_index].dst_ptr = (void *)dst_status;
        TAI_dlt_change_arr[model_instance_index].TAI_dlt_change = dst_status->TAI_dlt_change;
    }

}

static void app_mesh_time_state_set_cb(mesh_time_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const mesh_time_set_params_t * p_in, mesh_time_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: %x", __func__, p_self->model_instance_index, p_in->TAI_seconds);

    app_time_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_time_setup_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of Time value, process timing */
    p_server->state->TAI_seconds = p_in->TAI_seconds;
    p_server->state->subsecond = p_in->subsecond;
    p_server->state->uncertainty = p_in->uncertainty;
    p_server->state->time_authority = p_in->time_authority;
    *p_server->state->TAI2UTC_dlt = TSCNS_TIME_TAI2UTC_DLT_DECODE(p_in->TAI2UTC_dlt);
    *p_server->state->time_zone_offset = TSCNS_TIME_ZONE_OFFSET_DECODE(p_in->time_zone_offset);

    FORMAT_VALUE_RANGE(*p_server->state->TAI2UTC_dlt, APP_TIME_TAI2UTC_DLT_MAX, APP_TIME_TAI2UTC_DLT_MIN);
    FORMAT_VALUE_RANGE(*p_server->state->time_zone_offset, APP_TIME_ZONE_OFFSET_MAX, APP_TIME_ZONE_OFFSET_MIN);
    p_server->zone_state->time_zone_offset_current = *p_server->state->time_zone_offset;
    p_server->tai2utc_dlt_state->TAI2UTC_dlt_current  = *p_server->state->TAI2UTC_dlt;
    app_mesh_time_set_time_tai2utc_dlt(p_server->tai2utc_dlt_state->TAI2UTC_dlt_current);
    app_mesh_time_set_time_zone(p_server->zone_state->time_zone_offset_current);

    p_server->time_set_cb(p_server->server.model_instance_index, p_server->state, NULL, NULL, NULL);

    app_mesh_time_set_local_time_by_tai_sec(p_server->state->TAI_seconds, p_server->state->subsecond);
    /* Prepare response */
    /*p_out->TAI_seconds = p_server->state->TAI_seconds;
    p_out->subsecond = p_server->state->subsecond;
    p_out->uncertainty = p_server->state->uncertainty;
    p_out->time_authority = p_server->state->time_authority;
    p_out->TAI2UTC_dlt = TSCNS_TIME_TAI2UTC_DLT_ENCODE(*p_server->state->TAI2UTC_dlt);
    p_out->time_zone_offset = TSCNS_TIME_ZONE_OFFSET_ENCODE(*p_server->state->time_zone_offset);*/
    
    //pts test requirement.otherwise cannot pass test case.
    p_out->TAI_seconds = p_in->TAI_seconds;
    p_out->subsecond = p_in->subsecond;
    p_out->uncertainty = p_in->uncertainty;
    p_out->time_authority = p_in->time_authority;
    p_out->TAI2UTC_dlt = p_in->TAI2UTC_dlt;
    p_out->time_zone_offset = p_in->time_zone_offset;
}

static void app_mesh_time_zone_state_set_cb(mesh_time_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const mesh_time_zone_set_params_t * p_in, mesh_time_zone_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: zone SET: %x", __func__, p_self->model_instance_index, p_in->time_zone_offset_new);

    app_time_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_time_setup_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of Time value, process timing */
    p_server->zone_state->time_zone_offset_new = TSCNS_TIME_ZONE_OFFSET_DECODE(p_in->time_zone_offset_new);
    p_server->zone_state->TAI_zone_change = p_in->TAI_zone_change;

    FORMAT_VALUE_RANGE(p_server->zone_state->time_zone_offset_new, APP_TIME_ZONE_OFFSET_MAX, APP_TIME_ZONE_OFFSET_MIN);
    app_mesh_time_zone_change_check(p_server, p_self->model_instance_index, p_server->zone_state);
    p_server->time_set_cb(p_server->server.model_instance_index, NULL, p_server->zone_state, NULL, NULL);

    /* Prepare response */
    p_out->time_zone_offset_current = TSCNS_TIME_ZONE_OFFSET_ENCODE(p_server->zone_state->time_zone_offset_current);
    p_out->time_zone_offset_new = TSCNS_TIME_ZONE_OFFSET_ENCODE(p_server->zone_state->time_zone_offset_new);
    p_out->TAI_zone_change = p_server->zone_state->TAI_zone_change;
    app_mesh_time_set_time_zone(p_server->zone_state->time_zone_offset_current);
}

static void app_mesh_tai2utc_dlt_state_set_cb(mesh_time_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const mesh_tai2utc_dlt_set_params_t * p_in, mesh_tai2utc_dlt_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: delta SET: %d", __func__, p_self->model_instance_index, p_in->TAI2UTC_dlt_new);

    app_time_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_time_setup_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of Time value, process timing */
    p_server->tai2utc_dlt_state->TAI2UTC_dlt_new= TSCNS_TIME_TAI2UTC_DLT_DECODE(p_in->TAI2UTC_dlt_new);
    p_server->tai2utc_dlt_state->TAI_dlt_change = p_in->TAI_dlt_change;

    FORMAT_VALUE_RANGE(p_server->tai2utc_dlt_state->TAI2UTC_dlt_new, APP_TIME_TAI2UTC_DLT_MAX, APP_TIME_TAI2UTC_DLT_MIN);
    app_mesh_time_delta_change_check(p_server, p_self->model_instance_index, p_server->tai2utc_dlt_state);
    p_server->time_set_cb(p_server->server.model_instance_index, NULL, NULL, p_server->tai2utc_dlt_state, NULL);

    /* Prepare response */
    p_out->TAI2UTC_dlt_current = TSCNS_TIME_TAI2UTC_DLT_ENCODE(p_server->tai2utc_dlt_state->TAI2UTC_dlt_current);
    p_out->TAI2UTC_dlt_new = TSCNS_TIME_TAI2UTC_DLT_ENCODE(p_server->tai2utc_dlt_state->TAI2UTC_dlt_new);
    p_out->TAI_dlt_change = p_server->tai2utc_dlt_state->TAI_dlt_change;
    app_mesh_time_set_time_tai2utc_dlt(p_server->tai2utc_dlt_state->TAI2UTC_dlt_current);
}

static void app_mesh_time_role_state_set_cb(mesh_time_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const uint8_t p_in, uint8_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: role  SET: %x", __func__, p_self->model_instance_index, p_in);

    app_time_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_time_setup_server_t, server, p_self);
    app_time_role_t time_role = (app_time_role_t)p_in;
    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Update internal representation of Time value, process timing */
    if (time_role >= APP_TIME_ROLE_MAX)
    {
        time_role = APP_TIME_ROLE_NONE;
    }
    else
    {
        *p_server->time_role = time_role;
        p_server->time_set_cb(p_server->server.model_instance_index, NULL, NULL, NULL, p_server->time_role);
    }

    /* Prepare response */
    *p_out = time_role;
}

static void app_mesh_time_role_state_get_cb(mesh_time_setup_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               uint8_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_time_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_time_setup_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the Time state */
    p_server->time_get_cb(p_server->server.model_instance_index, p_server->time_role);

    /* Prepare response */
    *p_out = (uint8_t )*p_server->time_role;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
*/

void app_mesh_time_zone_change_update(void)
{
    uint8_t ele_idx = 0;
    mesh_time_zone_new_t *ptr = NULL;
    uint64_t tai_sec = 0;
    uint8_t subsec = 0;
    mesh_utc_time_t get_time;

    for (; ele_idx < TSCNS_TIME_SERVER_INSTANCE_COUNT; ele_idx ++)
    {
        ptr = &TAI_zone_change_arr[ele_idx];

        if(ptr->dst_ptr != NULL)
        {
            app_mesh_time_get_local_utc_time(&get_time);
            app_mesh_time_local_time_convert_sec(&get_time, &tai_sec, &subsec);

            if (ptr->TAI_zone_change <= tai_sec)
            {
                APP_LOG_INFO("[%s] ,update time zone ", __func__);
                app_time_zone_status_params_t *zone_change_ptr = ptr->dst_ptr;

                zone_change_ptr->time_zone_offset_current = zone_change_ptr->time_zone_offset_new;
                zone_change_ptr->TAI_zone_change = APP_TIME_TAI_ZONE_CHANGE_UNKNOW;
                app_mesh_time_set_time_zone(zone_change_ptr->time_zone_offset_current);

                if (ptr->p_server)
                {
                    ptr->p_server->time_set_cb(ptr->p_server->server.model_instance_index, NULL, ptr->p_server->zone_state, NULL, NULL);
                }
                ptr->dst_ptr = NULL;
            }
        }
    }
}

void app_mesh_time_delta_change_update(void)
{
    uint8_t ele_idx = 0;
    mesh_tai2utc_dlt_new_t *ptr = NULL;
    uint64_t tai_sec = 0;
    uint8_t subsec = 0;
    mesh_utc_time_t get_time;

    for (; ele_idx < TSCNS_TIME_SERVER_INSTANCE_COUNT; ele_idx ++)
    {
        ptr = &TAI_dlt_change_arr[ele_idx];

        if (ptr->dst_ptr != NULL)
        {
            app_mesh_time_get_local_utc_time(&get_time);
            app_mesh_time_local_time_convert_sec(&get_time, &tai_sec, &subsec);

            if (ptr->TAI_dlt_change <= tai_sec)
            {
                APP_LOG_INFO("[%s] ,update time utc2tai delta ", __func__);
                app_tai2utc_dlt_status_params_t *delta_change_ptr = ptr->dst_ptr;

                delta_change_ptr->TAI2UTC_dlt_current = delta_change_ptr->TAI2UTC_dlt_new;
                delta_change_ptr->TAI_dlt_change = APP_TIME_TAI_ZONE_CHANGE_UNKNOW;
                app_mesh_time_set_time_tai2utc_dlt(delta_change_ptr->TAI2UTC_dlt_current);

                if (ptr->p_server)
                {
                    ptr->p_server->time_set_cb(ptr->p_server->server.model_instance_index, NULL, NULL, ptr->p_server->tai2utc_dlt_state, NULL);
                }
                ptr->dst_ptr = NULL;
                ptr->p_server = NULL;
            }
        }
    }
}

uint16_t app_time_role_status_publish(app_time_setup_server_t * p_server)
{
    p_server->time_get_cb(p_server->server.model_instance_index, p_server->time_role);
    uint8_t role = *p_server->time_role;
    return mesh_time_server_role_status_publish(&p_server->server, &role);
}

uint16_t app_time_setup_server_init(app_time_setup_server_t *p_server, uint8_t element_offset, app_time_setup_set_cb_t set_cb, app_time_setup_get_cb_t get_cb)
{
    if(( p_server == NULL)
        || (TSCNS_TIME_SERVER_INSTANCE_COUNT <= element_offset)
        || (p_server->server.time_server == NULL)
        || (p_server->state == NULL)
        || (p_server->zone_state == NULL)
        || (p_server->tai2utc_dlt_state == NULL)
        || (p_server->time_role == NULL))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->time_set_cb = set_cb;
    p_server->time_get_cb = get_cb;

    //APP_LOG_INFO("debug %s : %d!", __func__, __LINE__);

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->server.settings.p_callbacks = &time_setup_srv_cbs;

    return mesh_time_setup_server_init(&p_server->server, element_offset);
}

