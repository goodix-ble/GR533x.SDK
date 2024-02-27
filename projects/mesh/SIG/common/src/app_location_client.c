/**
 *****************************************************************************************
 *
 * @file app_location_client.c
 *
 * @brief APP Location Client API Implementation.
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
#include "app_location_client.h"
#include "generic_location_client.h"
#include "app_log.h"
#include "user_app.h"


/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static uint16_t uncertainty_encode(uint32_t value)
{
    APP_LOG_INFO("[%s] enter %d", __func__, value);
    if(value < 1000)
    {
        if(value >= 500)
        {
            return 2;
        }
        else if(value >= 250)
        {
            return 1;
        }
        else
        {
            return 0;
        }
    }
    else
    {
        uint16_t m_value = value/1000;
        uint8_t power = 3;

        while(m_value)
        {
            m_value = m_value>>1;
            power++;
            if (power > 15)
            {
                return 15;
            }
        }

        return (power-1);
    }
}

static void generic_location_param_fill_p_out(app_location_set_param_t *in_state, location_global_status_params_t * global, location_local_status_params_t *local)
{
    //const double esp = 0.000001;
    APP_LOG_INFO("[%s] enter ", __func__);

    if (global)
    {
        if (in_state->global_cfg_flag&APP_LOCATION_GLOBAL_LATITUDE_NOT_CFG)
        {
            global->global_latitude = GENERIC_LOC_GLOBAL_LAT_NOT_CONFIG;
        }
        else
        {
            if ((-90) > (int32_t)in_state->global_latitude)
            {
                in_state->global_latitude = APP_LOCATION_GLOBAL_LATITUDE_MIN;
            }
            else if (90 < (int32_t)in_state->global_latitude)
            {
                in_state->global_latitude = APP_LOCATION_GLOBAL_LATITUDE_MAX;
            }
            global->global_latitude =  (int32_t)LOCATION_LATITUDE_ENCODE(in_state->global_latitude);
            #ifdef MESH_MODEL_BQB_TEST
                    global->global_latitude = global->global_latitude + 0xee27a3;
            #endif
        }

         if (in_state->global_cfg_flag&APP_LOCATION_GLOBAL_LONGITUDE_NOT_CFG)
        {
            global->global_longitude = GENERIC_LOC_GLOBAL_LONG_NOT_CONFIG;
        }
         else
        {
            if ((-180) > (int32_t)in_state->global_longitude)
            {
                in_state->global_latitude = APP_LOCATION_GLOBAL_LONGITUDE_MIN;
            }
            else if (180 < (int32_t)in_state->global_longitude)
            {
                in_state->global_latitude = APP_LOCATION_GLOBAL_LONGITUDE_MAX;
            }
            global->global_longitude =  (int32_t)LOCATION_LONGITUDE_ENCODE(in_state->global_longitude);
            #ifdef MESH_MODEL_BQB_TEST
                    global->global_longitude = global->global_longitude + 0x90a595;
            #endif
        }
        global->global_altitude = in_state->global_altitude;
    }

    if (local)
    {
        local->local_north = in_state->local_north;
        local->local_east = in_state->local_east;
        local->local_altitude = in_state->local_altitude;

        if (in_state->floor_number < APP_LOCATION_FLOOR_NUMBER_MIN)
        {
            in_state->floor_number = APP_LOCATION_FLOOR_NUMBER_MIN;
        }
        else if(in_state->floor_number > APP_LOCATION_FLOOR_NUMBER_NOT_CFG)
        {
            in_state->floor_number = APP_LOCATION_FLOOR_NUMBER_NOT_CFG;
        }
        local->floor_number = LOCATION_FLOOR_NUMBER_ENCODE(in_state->floor_number);


        if (in_state->update_time > APP_LOCATION_LOCAL_UPDATE_TIME_MAX)
        {
            in_state->update_time = APP_LOCATION_LOCAL_UPDATE_TIME_MAX;
        }
        else if (in_state->update_time < APP_LOCATION_LOCAL_UPDATE_TIME_MIN)
        {
            in_state->update_time = APP_LOCATION_LOCAL_UPDATE_TIME_MIN;
        }
        if (in_state->precision > APP_LOCATION_LOCAL_PRECISION_MAX)
        {
            in_state->precision = APP_LOCATION_LOCAL_PRECISION_MAX;
        }
        else if (in_state->precision < APP_LOCATION_LOCAL_PRECISION_MIN)
        {
            in_state->precision = APP_LOCATION_LOCAL_PRECISION_MIN;
        }

        APP_LOG_INFO("in_state->update_time %d precision %d", in_state->update_time, in_state->precision);
        local->uncertainty = ((uint16_t)in_state->stationary&0x01)
                                            |(uncertainty_encode(in_state->update_time)<<8)
                                            |(uncertainty_encode(in_state->precision)<<12);
        APP_LOG_INFO("local->uncertainty 0X%04X ", local->uncertainty);
    }

}

static uint32_t uncertainty_decode(uint16_t value)
{
    APP_LOG_INFO("[%s] enter ", __func__);
    return ((uint32_t)(1<<value) * 125);
}

void generic_location_status_update(app_location_set_param_t *local_state, location_global_status_params_t *in_global, location_local_status_params_t *in_local)
{
    //const double esp = 0.000001;

    APP_LOG_INFO("[%s] enter ", __func__);
    if (in_global)
    {
        if(in_global->global_latitude ==  GENERIC_LOC_GLOBAL_LAT_NOT_CONFIG)
        {
            local_state->global_cfg_flag |= APP_LOCATION_GLOBAL_LATITUDE_NOT_CFG;
        }
        else
        {
            local_state->global_latitude = (float)LOCATION_LATITUDE_DECODE(in_global->global_latitude);
        }

        if(in_global->global_longitude ==  GENERIC_LOC_GLOBAL_LONG_NOT_CONFIG)
        {
            local_state->global_cfg_flag |= APP_LOCATION_GLOBAL_LONGITUDE_NOT_CFG;
        }
        else
        {
            local_state->global_longitude = (float)LOCATION_LONGITUDE_DECODE(in_global->global_longitude);
        }

        local_state->global_altitude = in_global->global_altitude;
    }

    if(in_local)
    {
        local_state->local_north = in_local->local_north;
        local_state->local_east = in_local->local_east;
        local_state->local_altitude = in_local->local_altitude;

        //in_local->floor_number = (in_local->floor_number>APP_LOCATION_FLOOR_NUMBER_NOT_CFG)?APP_LOCATION_FLOOR_NUMBER_NOT_CFG:in_local->floor_number;
        local_state->floor_number = LOCATION_FLOOR_NUMBER_DECODE((int16_t)in_local->floor_number);

        local_state->stationary = in_local->uncertainty & 0x01;
        local_state->update_time = uncertainty_decode((in_local->uncertainty>>8) & 0x0F);
        local_state->precision = uncertainty_decode((in_local->uncertainty>>12) & 0x0F);
    }

}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_generic_location_sent(generic_location_client_t * p_client, app_location_cmd_t cmd, app_location_set_param_t * p_params)
{
    location_global_status_params_t global_param = {0,};
    location_local_status_params_t local_param = {0,};
    uint16_t ret = MESH_ERROR_NO_ERROR;

    APP_LOG_INFO("[%s] enter ", __func__);
    switch(cmd)
    {
        case APP_GENERIC_LOCATION_GLOBAL_GET:
            ret = generic_location_client_get(p_client, GLOBAL);
            break;
        case APP_GENERIC_LOCATION_GLOBAL_SET:
            generic_location_param_fill_p_out(p_params, &global_param, NULL);
            ret = generic_location_global_set(p_client, &global_param, true);
            break;
        case APP_GENERIC_LOCATION_GLOBAL_SET_UNACK:
            generic_location_param_fill_p_out(p_params, &global_param, NULL);
            ret =  generic_location_global_set(p_client, &global_param, false);
            break;
        case APP_GENERIC_LOCATION_LOCAL_GET:
            ret = generic_location_client_get(p_client, LOCAL);
            break;
        case APP_GENERIC_LOCATION_LOCAL_SET:
            generic_location_param_fill_p_out(p_params, NULL, &local_param);
            ret = generic_location_local_set(p_client, &local_param, true);
            break;
        case APP_GENERIC_LOCATION_LOCAL_SET_UNACK:
            generic_location_param_fill_p_out(p_params, NULL, &local_param);
            ret = generic_location_local_set(p_client, &local_param, false);
            break;
        default:
            ret = MESH_ERROR_SDK_INVALID_PARAM;
            break;
    }

    return ret;
}

#ifdef MESH_MODEL_BQB_TEST
uint16_t app_generic_location_pt_sent(generic_location_client_t * p_client, app_location_cmd_t cmd, uint8_t buf[])
{
    location_global_status_params_t global_param = {0,};
    location_local_status_params_t local_param = {0,};
    uint16_t ret = MESH_ERROR_NO_ERROR;

    APP_LOG_INFO("[%s] enter ", __func__);
    switch(cmd)
    {
        case APP_GENERIC_LOCATION_GLOBAL_GET:
            ret = generic_location_client_get(p_client, GLOBAL);
            break;
        case APP_GENERIC_LOCATION_GLOBAL_SET:
            global_param.global_latitude = buf[0] | buf[1]<<8 | buf[2]<<16 | buf[3]<<24;
            global_param.global_longitude = buf[4] | buf[5]<<8 | buf[6]<<16 | buf[7]<<24;
            global_param.global_altitude= buf[8] | buf[9]<<8;
            ret = generic_location_global_set(p_client, &global_param, true);
            break;
        case APP_GENERIC_LOCATION_GLOBAL_SET_UNACK:
            global_param.global_latitude = buf[0] | buf[1]<<8 | buf[2]<<16 | buf[3]<<24;
            global_param.global_longitude = buf[4] | buf[5]<<8 | buf[6]<<16 | buf[7]<<24;
            global_param.global_altitude= buf[8] | buf[9]<<8;
            ret =  generic_location_global_set(p_client, &global_param, false);
            break;
        case APP_GENERIC_LOCATION_LOCAL_GET:
            ret = generic_location_client_get(p_client, LOCAL);
            break;
        case APP_GENERIC_LOCATION_LOCAL_SET:
            local_param.local_north = buf[0] | buf[1]<<8;
            local_param.local_east= buf[2] | buf[3]<<8;
            local_param.local_altitude = buf[4] | buf[5]<<8;
            local_param.floor_number = buf[6];
            local_param.uncertainty = buf[7] | buf[8]<<8;
            ret = generic_location_local_set(p_client, &local_param, true);
            break;
        case APP_GENERIC_LOCATION_LOCAL_SET_UNACK:
            local_param.local_north = buf[0] | buf[1]<<8;
            local_param.local_east= buf[2] | buf[3]<<8;
            local_param.local_altitude = buf[4] | buf[5]<<8;
            local_param.floor_number = buf[6];
            local_param.uncertainty = buf[7] | buf[8]<<8;
            ret = generic_location_local_set(p_client, &local_param, false);
            break;
        default:
            ret = MESH_ERROR_SDK_INVALID_PARAM;
            break;
    }

    return ret;
}
#endif

uint16_t app_generic_location_client_init(generic_location_client_t *p_client, uint8_t element_offset, const generic_location_client_callbacks_t *client_cb)
{
    APP_LOG_INFO("[%s] enter , client callback pointer %p status cb:%p ack cb:%p.", __func__, client_cb, client_cb->location_status_cb, client_cb->ack_transaction_status_cb);
    if(( p_client == NULL)  ||  (GENERIC_LOCATION_CLIENT_INSTANCE_COUNT <= element_offset))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_client->model_lid = MESH_INVALID_LOCAL_ID;
    p_client->settings.timeout_ms = 10000; // NOTE!!! NO LESS THAN 30000MS.
    p_client->settings.p_callbacks = client_cb;
    p_client->model_instance_index = element_offset;

    return generic_location_client_init(p_client, element_offset);
}
