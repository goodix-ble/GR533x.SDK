/**
 *****************************************************************************************
 *
 * @file app_time_server.c
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
#include "app_time_server.h"
#include "time_server.h"
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
static void app_mesh_time_state_get_cb(mesh_time_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               mesh_time_status_params_t * p_out);

static void app_mesh_time_state_propag_cb(mesh_time_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const mesh_time_set_params_t * p_in, mesh_time_status_params_t * p_out, bool *pub);

static void app_mesh_time_zone_state_get_cb(mesh_time_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               mesh_time_zone_status_params_t * p_out);

static void app_mesh_tai2utc_dlt_state_get_cb(mesh_time_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               mesh_tai2utc_dlt_status_params_t * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const mesh_time_server_callbacks_t time_srv_cbs =
{
    .times_cbs.set_cb = NULL,
    .times_cbs.get_cb = app_mesh_time_state_get_cb,
    .times_cbs.propag_cb = app_mesh_time_state_propag_cb,
    .times_cbs.zone_set_cb = NULL,
    .times_cbs.zone_get_cb = app_mesh_time_zone_state_get_cb,
    .times_cbs.dlt_set_cb = NULL,
    .times_cbs.dlt_get_cb = app_mesh_tai2utc_dlt_state_get_cb,
    .times_cbs.role_set_cb = NULL,
    .times_cbs.role_get_cb = NULL,
};

/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */
#ifdef HAL_CALENDAR_MODULE_ENABLED
extern calendar_handle_t g_calendar_handle;
#endif

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static void app_mesh_time_state_get_cb(mesh_time_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               mesh_time_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_time_server_t *p_server = PARENT_BY_FIELD_GET(app_time_server_t, server, p_self);
    app_time_state_t time_state_get;
    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the Time state */
    p_server->time_get_cb(p_server->server.model_instance_index, &time_state_get, NULL, NULL);

    
    p_server->state.TAI_seconds = time_state_get.TAI_seconds;
    p_server->state.subsecond = time_state_get.subsecond;
    p_server->state.uncertainty = time_state_get.uncertainty;
    p_server->state.time_authority = time_state_get.time_authority;
    // time zone update, notice user app
    if (*time_state_get.time_zone_offset != *p_server->state.time_zone_offset)
    {
        p_server->time_update_cb(p_server->server.model_instance_index, &p_server->state, NULL, NULL);
    }

    // TAI-UTC delta update, notice user app
    if (*time_state_get.TAI2UTC_dlt != *p_server->state.TAI2UTC_dlt)
    {
        p_server->time_update_cb(p_server->server.model_instance_index, &p_server->state, NULL, NULL);
    }

    FORMAT_VALUE_RANGE(*p_server->state.TAI2UTC_dlt, APP_TIME_TAI2UTC_DLT_MAX, APP_TIME_TAI2UTC_DLT_MIN);
    FORMAT_VALUE_RANGE(*p_server->state.time_zone_offset, APP_TIME_ZONE_OFFSET_MAX, APP_TIME_ZONE_OFFSET_MIN);
    
    p_out->TAI_seconds = p_server->state.TAI_seconds;
    p_out->subsecond = p_server->state.subsecond?1:0;
    p_out->uncertainty = p_server->state.uncertainty?1:0;
    p_out->time_authority = p_server->state.time_authority;
    p_out->TAI2UTC_dlt = TSCNS_TIME_TAI2UTC_DLT_ENCODE(*p_server->state.TAI2UTC_dlt);
    p_out->time_zone_offset = TSCNS_TIME_ZONE_OFFSET_ENCODE(*p_server->state.time_zone_offset);

}

static void app_mesh_time_state_propag_cb(mesh_time_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const mesh_time_set_params_t * p_in, mesh_time_status_params_t * p_out, bool *pub)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET: %x", __func__, p_self->model_instance_index, p_in->TAI_seconds);

    app_time_server_t *p_server = PARENT_BY_FIELD_GET(app_time_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;
    *pub = true;

    if ((p_server->time_role == APP_TIME_ROLE_NONE) || (p_server->time_role == APP_TIME_ROLE_AUTH) || (p_server->time_role >= APP_TIME_ROLE_MAX))
    {
        *pub = false;

        return ;
    }

    /* Update internal representation of Time value, process timing */
    p_server->state.TAI_seconds = p_in->TAI_seconds;
    p_server->state.subsecond = p_in->subsecond;
    p_server->state.uncertainty = p_in->uncertainty;
    p_server->state.time_authority = p_in->time_authority;
    *p_server->state.TAI2UTC_dlt = TSCNS_TIME_TAI2UTC_DLT_DECODE(p_in->TAI2UTC_dlt);
    *p_server->state.time_zone_offset = TSCNS_TIME_ZONE_OFFSET_DECODE(p_in->time_zone_offset);

    FORMAT_VALUE_RANGE(*p_server->state.TAI2UTC_dlt, APP_TIME_TAI2UTC_DLT_MAX, APP_TIME_TAI2UTC_DLT_MIN);
    FORMAT_VALUE_RANGE(*p_server->state.time_zone_offset, APP_TIME_ZONE_OFFSET_MAX, APP_TIME_ZONE_OFFSET_MIN);
    p_server->zone_state.time_zone_offset_current = *p_server->state.time_zone_offset;
    p_server->tai2utc_dlt_state.TAI2UTC_dlt_current  = *p_server->state.TAI2UTC_dlt;
    app_mesh_time_set_time_tai2utc_dlt(p_server->tai2utc_dlt_state.TAI2UTC_dlt_current);
    app_mesh_time_set_time_zone(p_server->zone_state.time_zone_offset_current);//beijing time zone

    p_server->time_update_cb(p_server->server.model_instance_index, &p_server->state, NULL, NULL);

    //app_mesh_time_set_local_TAI_time_by_sec(p_server->state.TAI_seconds, p_server->state.subsecond);
    /* Prepare response */
    p_out->TAI_seconds = p_server->state.TAI_seconds;
    p_out->subsecond = p_server->state.subsecond;
    p_out->uncertainty = p_server->state.uncertainty;
    p_out->time_authority = p_server->state.time_authority;
    p_out->TAI2UTC_dlt = TSCNS_TIME_TAI2UTC_DLT_ENCODE(*p_server->state.TAI2UTC_dlt);
    p_out->time_zone_offset = TSCNS_TIME_ZONE_OFFSET_ENCODE(*p_server->state.time_zone_offset);

    if (p_server->time_role == APP_TIME_ROLE_CLIENT)
    {
        *pub = false;

        return ;
    }
}

static void app_mesh_time_zone_state_get_cb(mesh_time_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               mesh_time_zone_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_time_server_t *p_server = PARENT_BY_FIELD_GET(app_time_server_t, server, p_self);
    app_time_zone_status_params_t time_zone_get;
    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the Time state */
    p_server->time_get_cb(p_server->server.model_instance_index, NULL, &time_zone_get, NULL);

    /* time zone update, notice user app*/
    if (time_zone_get.time_zone_offset_current != p_server->zone_state.time_zone_offset_current)
    {
        p_server->time_update_cb(p_server->server.model_instance_index, NULL, &p_server->zone_state, NULL);
    }

    FORMAT_VALUE_RANGE(p_server->zone_state.time_zone_offset_current, APP_TIME_ZONE_OFFSET_MAX, APP_TIME_ZONE_OFFSET_MIN);
    FORMAT_VALUE_RANGE(p_server->zone_state.time_zone_offset_new, APP_TIME_ZONE_OFFSET_MAX, APP_TIME_ZONE_OFFSET_MIN);

    /* Prepare response */
    p_out->time_zone_offset_current = TSCNS_TIME_ZONE_OFFSET_ENCODE(p_server->zone_state.time_zone_offset_current);
    p_out->time_zone_offset_new = TSCNS_TIME_ZONE_OFFSET_ENCODE(p_server->zone_state.time_zone_offset_new);
    p_out->TAI_zone_change = p_server->zone_state.TAI_zone_change;

    app_mesh_time_set_time_zone(p_out->time_zone_offset_current);
}

static void app_mesh_tai2utc_dlt_state_get_cb(mesh_time_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               mesh_tai2utc_dlt_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_time_server_t *p_server = PARENT_BY_FIELD_GET(app_time_server_t, server, p_self);
    app_tai2utc_dlt_status_params_t tai2utc_dlt_get;
    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the Time state */
    p_server->time_get_cb(p_server->server.model_instance_index, NULL, NULL, &tai2utc_dlt_get);

    /* TAI-UTC delta update, notice user app*/
    if (tai2utc_dlt_get.TAI2UTC_dlt_current != p_server->tai2utc_dlt_state.TAI2UTC_dlt_current)
    {
        p_server->time_update_cb(p_server->server.model_instance_index, NULL, NULL, &p_server->tai2utc_dlt_state);
    }

    FORMAT_VALUE_RANGE(p_server->tai2utc_dlt_state.TAI2UTC_dlt_current, APP_TIME_TAI2UTC_DLT_MAX, APP_TIME_TAI2UTC_DLT_MIN);
    FORMAT_VALUE_RANGE(p_server->tai2utc_dlt_state.TAI2UTC_dlt_new, APP_TIME_TAI2UTC_DLT_MAX, APP_TIME_TAI2UTC_DLT_MIN);

    /* Prepare response */
    p_out->TAI2UTC_dlt_current = TSCNS_TIME_TAI2UTC_DLT_ENCODE(p_server->tai2utc_dlt_state.TAI2UTC_dlt_current);
    p_out->TAI2UTC_dlt_new = TSCNS_TIME_TAI2UTC_DLT_ENCODE(p_server->tai2utc_dlt_state.TAI2UTC_dlt_new);
    p_out->TAI_dlt_change = p_server->tai2utc_dlt_state.TAI_dlt_change;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_time_status_publish(app_time_server_t * p_server)
{
    if ((p_server->time_role == APP_TIME_ROLE_NONE) || (p_server->time_role == APP_TIME_ROLE_CLIENT) || (p_server->time_role >= APP_TIME_ROLE_MAX))
    {
        APP_LOG_INFO("[%s] TIME_ROLE:%d, The element does not publish", __func__, p_server->time_role);
        return MESH_ERROR_COMMAND_DISALLOWED;
    }
    p_server->time_get_cb(p_server->server.model_instance_index, &p_server->state, NULL, NULL);

    mesh_time_status_params_t status =
    {
        .TAI_seconds = p_server->state.TAI_seconds,
        .subsecond = p_server->state.subsecond,
        .uncertainty = p_server->state.uncertainty,
        .time_authority = p_server->state.time_authority,
        .TAI2UTC_dlt = TSCNS_TIME_TAI2UTC_DLT_ENCODE(*p_server->state.TAI2UTC_dlt),
        .time_zone_offset = TSCNS_TIME_ZONE_OFFSET_ENCODE(*p_server->state.time_zone_offset)
    };
    return mesh_time_server_status_publish(&p_server->server, &status);
}

uint16_t app_time_zone_status_publish(app_time_server_t * p_server)
{
    p_server->time_get_cb(p_server->server.model_instance_index, NULL, &p_server->zone_state, NULL);
    mesh_time_zone_status_params_t status =
    {
        .time_zone_offset_current = TSCNS_TIME_ZONE_OFFSET_ENCODE(p_server->zone_state.time_zone_offset_current),
        .time_zone_offset_new = TSCNS_TIME_ZONE_OFFSET_ENCODE(p_server->zone_state.time_zone_offset_new),
        .TAI_zone_change = p_server->zone_state.TAI_zone_change,
    };
    return mesh_time_server_zone_status_publish(&p_server->server, &status);
}

uint16_t app_time_tai2utc_delta_status_publish(app_time_server_t * p_server)
{
    p_server->time_get_cb(p_server->server.model_instance_index, NULL, &p_server->zone_state, NULL);
    mesh_tai2utc_dlt_status_params_t status =
    {
        .TAI2UTC_dlt_current = TSCNS_TIME_TAI2UTC_DLT_ENCODE(p_server->tai2utc_dlt_state.TAI2UTC_dlt_current),
        .TAI2UTC_dlt_new = TSCNS_TIME_TAI2UTC_DLT_ENCODE(p_server->tai2utc_dlt_state.TAI2UTC_dlt_new),
        .TAI_dlt_change = p_server->tai2utc_dlt_state.TAI_dlt_change,
    };
    return mesh_time_server_tai2utc_delta_status_publish(&p_server->server, &status);
}

uint16_t app_time_server_init(app_time_server_t *p_server, uint8_t element_offset, app_time_update_cb_t update_cb, app_time_get_cb_t get_cb)
{
    if(( p_server == NULL) || (TSCNS_TIME_SERVER_INSTANCE_COUNT <= element_offset))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    app_mesh_time_init();

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->time_update_cb = update_cb;
    p_server->time_get_cb = get_cb;

    app_mesh_time_get_TAI_time_sec(&p_server->state.TAI_seconds , &p_server->state.subsecond);
    p_server->state.uncertainty = 0;
    p_server->state.time_authority = 1;

    p_server->state.TAI2UTC_dlt = &p_server->tai2utc_dlt_state.TAI2UTC_dlt_current;
    p_server->state.time_zone_offset = &p_server->zone_state.time_zone_offset_current;

    p_server->zone_state.time_zone_offset_current = 8*4;//beijing time zone
    p_server->zone_state.time_zone_offset_new = 8*4;//beijing time zone
    p_server->zone_state.TAI_zone_change = APP_TIME_TAI_ZONE_CHANGE_UNKNOW;

    p_server->tai2utc_dlt_state.TAI2UTC_dlt_current = APP_TIME_TAI2UTC_DLT_2019;// current_TAI minus current_UTC, this value equals 37 now.
    p_server->tai2utc_dlt_state.TAI2UTC_dlt_new= APP_TIME_TAI2UTC_DLT_2019;// current_TAI minus current_UTC, this value equals 37 now.
    p_server->tai2utc_dlt_state.TAI_dlt_change = APP_TIME_TAI_DLT_CHANGE_UNKNOW;
    app_mesh_time_set_time_tai2utc_dlt(APP_TIME_TAI2UTC_DLT_2019);
    app_mesh_time_set_time_zone(8*4);//beijing time zone

    p_server->time_role = APP_TIME_ROLE_RELAY;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->server.settings.p_callbacks = &time_srv_cbs;

    return mesh_time_server_init(&p_server->server, element_offset);
}

