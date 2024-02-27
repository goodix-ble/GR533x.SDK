/**
 *****************************************************************************************
 *
 * @file app_location_server.c
 *
 * @brief APP Location API Implementation.
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
#include "app_location_server.h"
#include "generic_location_server.h"
#include "app_log.h"
#include "user_app.h"


/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void generic_location_state_get_cb(generic_location_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg,
                                               void * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const generic_location_server_callbacks_t location_srv_cbs =
{
    .location_cbs.get_cb = generic_location_state_get_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static uint32_t uncertainty_decode(int8_t value)
{
    return ((uint32_t)(1<<value) * 125);
}

static uint16_t uncertainty_encode(uint32_t value)
{
    APP_LOG_INFO("[%s] enter ", __func__);
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

static void generic_location_state_get_cb(generic_location_server_t *p_self, const mesh_model_msg_ind_t * p_rx_msg, void * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    app_location_server_t *p_server = PARENT_BY_FIELD_GET(app_location_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Requirement: Provide the current value of the local state */
    p_server->location_get_cb(p_server->server.model_instance_index, p_server->state);
     if (p_rx_msg->opcode.company_opcode == GENERIC_LOCATION_GLOBAL_OPCODE_GET)
    {
        app_location_state_t app_loc_state;
        generic_location_state_update(&app_loc_state, &p_server->global_state, NULL);

        APP_LOG_INFO("golbal lat %f=%f, long %f=%f", app_loc_state.global_latitude, p_server->state->global_latitude, app_loc_state.global_longitude, p_server->state->global_longitude);
        if (((app_loc_state.global_latitude > p_server->state->global_latitude) && ((app_loc_state.global_latitude - p_server->state->global_latitude) > 0.000002))
            ||((app_loc_state.global_latitude < p_server->state->global_latitude) && ((p_server->state->global_latitude - app_loc_state.global_latitude) > 0.000002))
            ||((app_loc_state.global_longitude > p_server->state->global_longitude) && ((app_loc_state.global_longitude - p_server->state->global_longitude) > 0.000002))
            ||((app_loc_state.global_longitude < p_server->state->global_longitude) && ((p_server->state->global_longitude - app_loc_state.global_longitude)> 0.000002)))
        {
            generic_location_state_fill_p_out(p_server->state, (location_global_status_params_t *)p_out, NULL);
        }
        else
        {
            *(location_global_status_params_t *)p_out = p_server->global_state;
        }
    }
    else
    {
       generic_location_state_fill_p_out(p_server->state, NULL, (location_local_status_params_t *)p_out);
    }


}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */
void generic_location_state_update(app_location_state_t *local_state, const location_global_status_params_t *in_global, const location_local_status_params_t *in_local)
{
    //const double esp = 0.000001;

    if (!local_state)
    {
        APP_LOG_INFO("[%s] enter, error : please bonding correct server state", __func__);
        return ;
    }

    if (in_global)
    {
        if(in_global->global_latitude ==  GENERIC_LOC_GLOBAL_LAT_NOT_CONFIG)
        {
            local_state->global_cfg_flag |= APP_LOCATION_GLOBAL_LATITUDE_NOT_CFG;
        }
        else
        {
            local_state->global_cfg_flag &= ~APP_LOCATION_GLOBAL_LATITUDE_NOT_CFG;
            local_state->global_latitude = (float)LOCATION_LATITUDE_DECODE(in_global->global_latitude);
        }

        if(in_global->global_longitude ==  GENERIC_LOC_GLOBAL_LONG_NOT_CONFIG)
        {
            local_state->global_cfg_flag |= APP_LOCATION_GLOBAL_LONGITUDE_NOT_CFG;
        }
        else
        {
            local_state->global_cfg_flag &= ~APP_LOCATION_GLOBAL_LONGITUDE_NOT_CFG;
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
        local_state->update_time = uncertainty_decode((in_local->uncertainty>>8) & 0x0F );
        local_state->precision = uncertainty_decode((in_local->uncertainty>>12) & 0x0F);
        APP_LOG_INFO("[%s] enter, 0x%04x, %d, %d", __func__, in_local->uncertainty,  (in_local->uncertainty>>8), (in_local->uncertainty>>12));
    }

}

void generic_location_state_fill_p_out(app_location_state_t *in_state, location_global_status_params_t * global, location_local_status_params_t *local)
{
    //const double esp = 0.000001;
    APP_LOG_INFO("[%s] enter, msg fill ", __func__);

    if (global)
    {
        if (in_state->global_cfg_flag&APP_LOCATION_GLOBAL_LATITUDE_NOT_CFG)
        {
            global->global_latitude = GENERIC_LOC_GLOBAL_LAT_NOT_CONFIG;
        }
        else
        {
            global->global_latitude =  (int32_t)LOCATION_LATITUDE_ENCODE(in_state->global_latitude);;
        }

         if (in_state->global_cfg_flag&APP_LOCATION_GLOBAL_LONGITUDE_NOT_CFG)
        {
            global->global_longitude = GENERIC_LOC_GLOBAL_LONG_NOT_CONFIG;
        }
         else
        {
            global->global_longitude =  (int32_t)LOCATION_LONGITUDE_ENCODE(in_state->global_longitude);
        }

        global->global_altitude = in_state->global_altitude;
        APP_LOG_INFO("global msg : lat %04X, long %04X, alt %02X", global->global_latitude, global->global_longitude, global->global_altitude);
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
        local->uncertainty = ((uint16_t)in_state->stationary&0x01)
                                            |(uncertainty_encode(in_state->update_time)<<8)
                                            |(uncertainty_encode(in_state->precision)<<12);

        APP_LOG_INFO("local msg : north 0x%02X, east 0x%02X, alt 0x%02X, floor %d, uncertainty 0x%02X", local->local_north, local->local_east, local->local_altitude, local->floor_number, local->uncertainty);
    }

}

uint16_t app_generic_location_status_publish(app_location_server_t * p_server, bool global_flag)
{
    location_global_status_params_t global_status;
    location_local_status_params_t local_status;
    void *p_out = NULL;

    p_server->location_get_cb(p_server->server.model_instance_index, p_server->state);
    generic_location_state_fill_p_out(p_server->state, &global_status, &local_status);

    if (global_flag)
    {
        app_location_state_t app_loc_state;
        generic_location_state_update(&app_loc_state, &p_server->global_state, NULL);

        if (((app_loc_state.global_latitude > p_server->state->global_latitude) && ((app_loc_state.global_latitude - p_server->state->global_latitude) > 0.000002))
            ||((app_loc_state.global_latitude < p_server->state->global_latitude) && ((p_server->state->global_latitude - app_loc_state.global_latitude) > 0.000002))
            ||((app_loc_state.global_longitude > p_server->state->global_longitude) && ((app_loc_state.global_longitude - p_server->state->global_longitude) > 0.000002))
            ||((app_loc_state.global_longitude < p_server->state->global_longitude) && ((p_server->state->global_longitude - app_loc_state.global_longitude)> 0.000002)))
        {
            p_out = (void *)&global_status;
        }
        else
        {
            p_out = (void *)&p_server->global_state;
        }

    }
    else
    {
        p_out = (void *)&local_status;
    }
    return generic_location_server_status_publish(&p_server->server, global_flag, p_out);
}

uint16_t app_generic_location_server_init(app_location_server_t *p_server, uint8_t element_offset, app_generic_location_get_cb_t get_cb)
{
    if(( p_server == NULL) || (GENERIC_LOCATION_SERVER_INSTANCE_COUNT <= element_offset) || (NULL == p_server->state))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->location_get_cb = get_cb;

    p_server->state->global_cfg_flag = APP_LOCATION_GLOBAL_LATITUDE_NOT_CFG|APP_LOCATION_GLOBAL_LONGITUDE_NOT_CFG;
    p_server->state->global_latitude = APP_LOCATION_GLOBAL_LATITUDE_MIN;
    p_server->state->global_longitude = APP_LOCATION_GLOBAL_LONGITUDE_MIN;
    p_server->state->global_altitude= APP_LOCATION_GLOBAL_ALTITUDE_NOT_CFG;
    p_server->state->local_north = APP_LOCATION_LOCAL_NORTH_NOT_CFG;
    p_server->state->local_east = APP_LOCATION_LOCAL_EAST_NOT_CFG;
    p_server->state->local_altitude= APP_LOCATION_LOCAL_ALTITUDE_NOT_CFG;
    p_server->state->floor_number= APP_LOCATION_FLOOR_NUMBER_NOT_CFG;
    p_server->state->stationary= APP_LOCATION_STATIONARY;
    p_server->state->update_time= APP_LOCATION_LOCAL_UPDATE_TIME_MIN;
    p_server->state->precision= APP_LOCATION_LOCAL_PRECISION_MIN;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->server.settings.p_callbacks = &location_srv_cbs;
        
    return generic_location_server_init(&p_server->server, element_offset);
}
