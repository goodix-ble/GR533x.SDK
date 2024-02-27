/**
 *****************************************************************************************
 *
 * @file app_sensor_server.c
 *
 * @brief APP Sensor API Implementation.
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
#include "app_sensor_server.h"
#include "sensor_server.h"
#include "app_log.h"
#include "user_app.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void sensor_desc_state_get_cb(sensor_server_t * p_self,
                                            const mesh_model_msg_ind_t * p_rx_msg,
                                            sensor_descriptor_get_params_t * p_in,
                                            sensor_descriptor_status_params_t* p_out);

static void sensor_state_get_cb(sensor_server_t * p_self,
                                        const mesh_model_msg_ind_t * p_rx_msg,
                                        const sensor_get_params_t * p_in,
                                        sensor_status_params_t ** p_out,
                                        uint16_t *p_out_length,
                                        bool map_pub);


static void sensor_column_state_get_cb(sensor_server_t * p_self,
                                            const mesh_model_msg_ind_t * p_rx_msg,
                                            const sensor_column_get_params_t * p_in,
                                            sensor_column_status_params_t * p_out);

static void sensor_series_state_get_cb(sensor_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    const sensor_series_get_params_t *p_in,
                                                    sensor_series_status_params_t * p_out);

static void sensor_publish_period_cb(sensor_server_t * p_self, const mesh_model_publish_period_ind_t * p_rx_msg);

static bool sensor_state_trigger_publish(app_sensor_server_t *p_server, uint16_t trigger_id, int32_t trigger_delta_value);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
const sensor_server_callbacks_t sensor_srv_cbs =
{
    .sensor_cbs.descrip_get_cb = sensor_desc_state_get_cb,
    .sensor_cbs.get_cb = sensor_state_get_cb,
    .sensor_cbs.column_get_cb = sensor_column_state_get_cb,
    .sensor_cbs.series_get_cb = sensor_series_state_get_cb,
    .sensor_cbs.publish_period_cb = sensor_publish_period_cb
    
};

sensor_descriptor_status_params_t local_decriptor_reg = {0, 0, NULL};
app_sensor_cadence_t local_cadence_reg = {0,NULL};
sensor_settings_status_params_t *local_settings_reg = NULL;
sensor_setting_status_params_t *local_setting_reg = NULL;
app_sensor_status_t local_sensor_reg = {0, NULL};//sensor property register, could be a list.
sensor_column_status_params_t * local_column_reg = NULL;
sensor_series_status_params_t *local_series_reg = NULL;

mesh_timer_t min_peroid_ctrl_timer;
app_sensor_min_period_ctrl_t app_sensor_min_period_ctrl = 
{
    .p_server = NULL,
    .trigger_id = 0x0000,
    .trigger_delta_value = 0,
    .trigger_flag = true,
    .trigger_min_period = 0,
};
/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static void sensor_desc_state_get_cb(sensor_server_t * p_self,
                                                                        const mesh_model_msg_ind_t * p_rx_msg,
                                                                        sensor_descriptor_get_params_t * p_in,
                                                                        sensor_descriptor_status_params_t* p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    if (NULL != local_decriptor_reg.p_desc)
    {
        if (NULL == p_in)
        {
            memcpy(p_out, &local_decriptor_reg, sizeof(sensor_descriptor_status_params_t));
        }
        else
        {
            uint16_t i = 0;
            for(i=0; i<local_decriptor_reg.desc_length; i++)
            {
                if (local_decriptor_reg.p_desc[i].sensor_property_id == p_in->property_id)
                {
                    p_out->desc_length = 1;
                    p_out->p_desc = &(local_decriptor_reg.p_desc[i]);
                    break;
                }
            }
            
            if (i == local_decriptor_reg.desc_length)
            {
                p_out->desc_length = 2;
                p_out->sensor_property_id = p_in->property_id;
                p_out->p_desc = NULL;
            }
        }
    }
    else
    {
        p_out->desc_length = 2;
        p_out->sensor_property_id = p_in->property_id;
        p_out->p_desc = NULL;
    }
}

static void sensor_state_get_cb(sensor_server_t * p_self,
                                                                        const mesh_model_msg_ind_t * p_rx_msg,
                                                                        const sensor_get_params_t * p_in,
                                                                        sensor_status_params_t ** p_out,
                                                                        uint16_t *p_out_length,
                                                                        bool map_pub)
{
    app_sensor_server_t *p_server = PARENT_BY_FIELD_GET(app_sensor_server_t, server, p_self);
    uint16_t idx = 0;

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    /* save the address of message from */
    if (NULL != p_rx_msg)
    {
        p_server->client_address = p_rx_msg->src;
    }

    if ((0 != local_sensor_reg.sensor_state_number)&&(NULL != local_sensor_reg.p_sensor))
    {
        sensor_status_params_t *ptr = NULL;

        if (NULL == p_in)//get all sensor property
        {
            if (!map_pub)
            {
                *p_out = (sensor_status_params_t *)sys_malloc(sizeof(sensor_status_params_t) * local_sensor_reg.sensor_state_number);//free source after message sent
                if (NULL != *p_out)
                {
                    memcpy(*p_out, local_sensor_reg.p_sensor, sizeof(sensor_status_params_t) * local_sensor_reg.sensor_state_number);
                    *p_out_length = local_sensor_reg.sensor_state_number;//sizeof(sensor_status_params_t) * 1;
                }

                return ;
            }
            else if ((local_sensor_reg.sensor_pub_number > 0) && (NULL != local_sensor_reg.sensor_pub_map))
            {
                uint16_t out_idx = 0;
                *p_out = (sensor_status_params_t *)sys_malloc(sizeof(sensor_status_params_t) * local_sensor_reg.sensor_pub_number);//free source after message sent
                for (idx=0; idx<local_sensor_reg.sensor_state_number; idx++)
                {
                    if (SENSOR_PUB_ON == local_sensor_reg.sensor_pub_map[idx])
                    {
                        memcpy(&((*p_out)[out_idx]), &(local_sensor_reg.p_sensor[idx]), sizeof(sensor_status_params_t));
                        out_idx ++;
                    }
                }
                *p_out_length = local_sensor_reg.sensor_pub_number;
                local_sensor_reg.sensor_pub_number = 0;
                memset(local_sensor_reg.sensor_pub_map, SENSOR_PUB_OFF, local_sensor_reg.sensor_state_number);
                return ;
            }
        }
        else 
        {
            for (idx=0; idx<local_sensor_reg.sensor_state_number; idx++)
            {
                ptr = &(local_sensor_reg.p_sensor[idx]);
                if (p_in->property_id == ptr->property_id)
                {
                    *p_out = (sensor_status_params_t *)sys_malloc(sizeof(sensor_status_params_t));
                    if (NULL != *p_out)
                    {
                        memcpy(*p_out, ptr, sizeof(sensor_status_params_t));
                        *p_out_length = 1;//sizeof(sensor_status_params_t);
                    }
                    break;
                }
            }
        }

        if (idx == local_sensor_reg.sensor_state_number)
        {
            *p_out = (sensor_status_params_t *)sys_malloc(sizeof(sensor_status_params_t));
            if (NULL != *p_out)
            {
                (*p_out)->property_id = p_in->property_id;
                (*p_out)->format = 0x01;
                (*p_out)->sensor_data_length = 0x80;
                *p_out_length = 1;//sizeof(sensor_status_params_t);
            }
        }
    }
    else
    {
        if (NULL != p_in)
        {
            *p_out = (sensor_status_params_t *)sys_malloc(sizeof(sensor_status_params_t));
            if (NULL != *p_out)
            {
                (*p_out)->property_id = p_in->property_id;
                (*p_out)->format = 0x01;
                (*p_out)->sensor_data_length = 0x80;
                *p_out_length = 1;//sizeof(sensor_status_params_t);
            }
        }
    }
}

static void sensor_column_state_get_cb(sensor_server_t * p_self,
                                                                        const mesh_model_msg_ind_t * p_rx_msg,
                                                                        const sensor_column_get_params_t * p_in,
                                                                        sensor_column_status_params_t * p_out)
{
    if ((NULL != local_column_reg)
            && (p_in->property_id == local_column_reg->property_id)
            && (0 == memcmp(p_in->raw_x, local_column_reg->raw_x, p_in->raw_x_length)))
    {
        memcpy(p_out, local_column_reg, sizeof(sensor_column_status_params_t));
    }
    else
    {
        p_out->property_id = p_in->property_id;
        p_out->raw_x_length = p_in->raw_x_length;
        p_out->raw_x = p_in->raw_x;
    }
}

static void sensor_series_state_get_cb(sensor_server_t * p_self,
                                                                        const mesh_model_msg_ind_t * p_rx_msg,
                                                                        const sensor_series_get_params_t *p_in,
                                                                        sensor_series_status_params_t * p_out)
{
    property_value_type_t type = NOT_FIND_ID;
    uint32_t value_x1 = 0, value_x2 = 0, value_x3 = 0;
    float fvalue_x1 = 0.0f, fvalue_x2 = 0.0f, fvalue_x3 = 0.0f;

    if ((NULL != local_series_reg)
        &&(1 == local_series_reg->series_data_num)// only 1 column data surpport for test
        &&(NULL != local_series_reg->series_data)
        && (p_in->property_id == local_series_reg->property_id))
    {
        bool inc_flag = false;

        if (p_in ->series_x_length != 0)
        {
            type = get_property_value_type(p_in->property_id);
            switch(type)
            {
                case PROPERTY_UINT8:
                    value_x1 = *p_in->series_x1;
                    value_x2 = *p_in->series_x2;
                    value_x3 = *local_series_reg->series_data[0].raw_x;
                    if (value_x1 <= value_x2)
                    {
                        if ((value_x3 <= value_x2) && (value_x3 >= value_x1))
                        {
                            inc_flag = true;
                        }
                    }
                    break;
                case PROPERTY_UINT16:
                    value_x1 = p_in->series_x1[0] | p_in->series_x1[1];
                    value_x2 = p_in->series_x2[0] | p_in->series_x2[1];
                    value_x3 = local_series_reg->series_data[0].raw_x[0] | local_series_reg->series_data[0].raw_x[1];
                    if (value_x1 <= value_x2)
                    {
                        if ((value_x3 <= value_x2) && (value_x3 >= value_x1))
                        {
                            inc_flag = true;
                        }
                    }
                    break;
                case PROPERTY_UINT24:
                    value_x1 = p_in->series_x1[0] | p_in->series_x1[1] | p_in->series_x1[2] ;
                    value_x2 = p_in->series_x2[0] | p_in->series_x2[1] | p_in->series_x2[2];
                    value_x3 = local_series_reg->series_data[0].raw_x[0] | local_series_reg->series_data[0].raw_x[1] | local_series_reg->series_data[0].raw_x[2];
                    if (value_x1 <= value_x2)
                    {
                        if ((value_x3 <= value_x2) && (value_x3 >= value_x1))
                        {
                            inc_flag = true;
                        }
                    }
                    break;
                case PROPERTY_UINT32:
                    value_x1 = p_in->series_x1[0] | p_in->series_x1[1] | p_in->series_x1[2] | p_in->series_x1[3] ;
                    value_x2 = p_in->series_x2[0] | p_in->series_x2[1] | p_in->series_x2[2] | p_in->series_x1[3] ;
                    value_x3 = local_series_reg->series_data[0].raw_x[0] | local_series_reg->series_data[0].raw_x[1]
                                        | local_series_reg->series_data[0].raw_x[2] | local_series_reg->series_data[0].raw_x[3];
                    if (value_x1 <= value_x2)
                    {
                        if ((value_x3 <= value_x2) && (value_x3 >= value_x1))
                        {
                            inc_flag = true;
                        }
                    }
                    break;
                case PROPERTY_FLOAT32:
                    fvalue_x1 = p_in->series_x1[0] | p_in->series_x1[1] | p_in->series_x1[2] | p_in->series_x1[3] ;
                    fvalue_x2 = p_in->series_x2[0] | p_in->series_x2[1] | p_in->series_x2[2] | p_in->series_x1[3] ;
                    fvalue_x3 = local_series_reg->series_data[0].raw_x[0] | local_series_reg->series_data[0].raw_x[1]
                                        | local_series_reg->series_data[0].raw_x[2] | local_series_reg->series_data[0].raw_x[3];
                    if (fvalue_x1 < fvalue_x2)
                    {
                        if ((fvalue_x3 < fvalue_x2) && (fvalue_x3 > fvalue_x1))
                        {
                            inc_flag = true;
                        }
                    }
                    break;
                default:
                    break;
            }
        }
        else// response all series data
        {
            inc_flag = true;
        }

        if (inc_flag)
        {
            memcpy(p_out, local_series_reg, sizeof(sensor_series_status_params_t));
        }
        else
        {
            p_out->property_id = p_in->property_id;
            p_out->series_data_num = 0;
        }
    }
    else
    {
        p_out->property_id = p_in->property_id;
        p_out->series_data_num = 0;
    }
}

static uint32_t value_calc(uint32_t value, uint32_t dlt_value, bool decrese_flag)
{
    if (dlt_value == 0)
    {
        return value;
    }

    if (decrese_flag)
    {
        if (value < dlt_value)
        {
            value = 0;
        }
        else
        {
            value -= dlt_value;
        }
    }
    else
    {
        value += dlt_value;
    }

    return value;
}

static bool sensor_set_property_value(uint16_t property_id, uint8_t *p_property_value, uint8_t *p_set_value, bool decrese_flag)
{
    uint32_t property_value = 0;
    uint32_t dlt_value = 0;
    if ((NULL == p_property_value) || (NULL == p_set_value))
    {
        return false;
    }

    switch(property_id)
    {
        case 0x0042:
            break;
        case 0x004E://present ambient light level, uints is uint24
            property_value = (uint32_t)p_property_value[0]|(uint32_t)p_property_value[1]<<8|(uint32_t)p_property_value[2]<<16;
            dlt_value = (uint32_t)p_set_value[0]|(uint32_t)p_set_value[1]<<8|(uint32_t)p_set_value[2]<<16;
            property_value = value_calc(property_value, dlt_value, decrese_flag);
            p_property_value[0] = property_value&0xFF;
            p_property_value[1] = (property_value>>8)&0xFF;
            p_property_value[2] = (property_value>>16)&0xFF;
            break;
        default:
            return false;
    }

    return true;
}

static bool compare_fast_cadence_value(sensor_cadence_status_params_t *p_cadence, sensor_status_params_t *p_sensor)
{
    uint32_t property_value = 0;
    uint32_t low_value = 0;
    uint32_t high_value = 0;

    if (p_cadence->property_id != p_sensor->property_id)
    {
        return false;
    }

    switch(p_cadence->property_id)
    {
        case 0x0042:
            property_value = p_sensor->p_sensor_data[0];
            low_value = p_cadence->fast_cadence_low[0];
            high_value = p_cadence->fast_cadence_high[0];
            break;
        case 0x004E://present ambient light level, uints is uint24
            property_value = (uint32_t)p_sensor->p_sensor_data[0] | (uint32_t)(p_sensor->p_sensor_data[1] << 8) | (uint32_t)(p_sensor->p_sensor_data[2] << 16);
            low_value = (uint32_t)p_cadence->fast_cadence_low[0] | (uint32_t)(p_cadence->fast_cadence_low[1] << 8) | (uint32_t)(p_cadence->fast_cadence_low[2] << 16);
            high_value = (uint32_t)p_cadence->fast_cadence_high[0] | (uint32_t)(p_cadence->fast_cadence_high[1] << 8) | (uint32_t)(p_cadence->fast_cadence_high[2] << 16);
            break;
        default :
            APP_LOG_INFO("[%s] Err : can't find property record !!!", __func__);
            return false;
    }

    APP_LOG_INFO("[%s] property id 0x%04x, value 0x%04x in [0x%04x, 0x%04x]", __func__, p_cadence->property_id, property_value, low_value, high_value);
    if (low_value >= high_value)// outside the range 
    {
        if ((property_value >= low_value) || (property_value <= high_value))
        {
            return true;
        }
    }
    else if (low_value < high_value)// inside the range 
    {
        if ((property_value >= low_value) && (property_value <= high_value))
        {
            return true;
        }
    }

    return false;
}

static uint32_t sensor_calc_state_publish_time(app_sensor_server_t * p_server)
{
    uint32_t delay_ms = 0;//local_cadence_reg.delay_ms_in_period;
    
    if (p_server->publish_period_ms != 0)
    {
        uint16_t cadence_idx = 0;
        uint16_t sensor_idx = 0;
        sensor_cadence_status_params_t *cadence_ptr = NULL;
        sensor_status_params_t *sensor_ptr = NULL;
        uint32_t div_delay_min = 0;
        uint32_t min_interval = 0;
        uint32_t next_triggert_pub = 0xFFFFFFFF;
        uint32_t min_triggert_pub = 0xFFFFFFFF;

        local_sensor_reg.sensor_pub_number = 0;
        memset(local_sensor_reg.sensor_pub_map, SENSOR_PUB_OFF, local_sensor_reg.sensor_state_number);

        for (cadence_idx=0; cadence_idx<local_cadence_reg.candece_number; cadence_idx++)
        {
            cadence_ptr = &(local_cadence_reg.p_candece[cadence_idx]);

            for (sensor_idx = 0; sensor_idx < local_sensor_reg.sensor_state_number; sensor_idx++)
            {
                sensor_ptr = &local_sensor_reg.p_sensor[sensor_idx];
                if ((cadence_ptr->property_id == sensor_ptr->property_id) && (compare_fast_cadence_value(cadence_ptr, sensor_ptr)))
                {
                    div_delay_min = p_server->publish_period_ms / (0x0001 << cadence_ptr->fast_cadence_period_div);
                    min_interval = (uint32_t)0x01 << cadence_ptr->min_interval;
                    div_delay_min = div_delay_min < min_interval ? min_interval : div_delay_min;

                    next_triggert_pub = (local_cadence_reg.delay_ms_in_period/div_delay_min +1 ) * div_delay_min;
                    min_triggert_pub = min_triggert_pub > next_triggert_pub ? next_triggert_pub : min_triggert_pub;

                    if (min_triggert_pub == next_triggert_pub)
                    //if (delay_ms == div_delay_min)
                    {
                        local_sensor_reg.sensor_pub_map[sensor_idx] = SENSOR_PUB_ON;//publish
                        local_sensor_reg.sensor_pub_number ++;
                    }
                    else if (min_triggert_pub > next_triggert_pub)//if (delay_ms > div_delay_min)
                    {
                        memset(local_sensor_reg.sensor_pub_map, SENSOR_PUB_OFF, local_sensor_reg.sensor_state_number);
                        //delay_ms = div_delay_min;
                        min_triggert_pub = next_triggert_pub;
                        local_sensor_reg.sensor_pub_map[sensor_idx] = SENSOR_PUB_ON;//publish
                        local_sensor_reg.sensor_pub_number = 1;
                    }
                }
            }
        }

        if (min_triggert_pub != 0xFFFFFFFF)
        {
            delay_ms = min_triggert_pub - local_cadence_reg.delay_ms_in_period;
            local_cadence_reg.delay_ms_in_period = min_triggert_pub%p_server->publish_period_ms;
        }
        else
        {
            local_cadence_reg.delay_ms_in_period = 0;
        }
        APP_LOG_INFO("[%s] calculate publish ms : %d, next pub %d, next period pub %d.", __func__, delay_ms, min_triggert_pub, local_cadence_reg.delay_ms_in_period);
    }

    return delay_ms;
}

static void sensor_state_process_timing(app_sensor_server_t * p_server)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    // if the timer isn't in list, no error occurs.
    mesh_timer_clear(&p_server->pub_timer.timer_id);

    /* Process timing requirements */
    if (p_server->publish_period_ms != 0)
    {
        p_server->pub_timer.delay_ms = sensor_calc_state_publish_time(p_server);
        if (p_server->pub_timer.delay_ms == 0)
        {
            p_server->pub_timer.delay_ms = p_server->publish_period_ms;
        }
        mesh_timer_set(&p_server->pub_timer);
    }
}

static void sensor_publish_period_cb(sensor_server_t * p_self,
                                                                        const mesh_model_publish_period_ind_t * p_rx_msg)
{
    app_sensor_server_t *p_server = PARENT_BY_FIELD_GET(app_sensor_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter.", __func__);

    p_server->publish_period_ms = p_rx_msg->period_ms;
    local_cadence_reg.delay_ms_in_period = 0;

    sensor_server_status_publish(&p_server->server, false);
    sensor_state_process_timing(p_server);
}

static void sensor_state_period_timer_cb(void * p_context)
{    
    app_sensor_server_t * p_server = (app_sensor_server_t *) p_context;

    APP_LOG_INFO("[%s] enter.", __func__);

    if (local_cadence_reg.delay_ms_in_period == 0)
    {
        sensor_server_status_publish(&p_server->server, false);//publish all
    }
    else
    {
        sensor_server_status_publish(&p_server->server, true);
    }
    sensor_state_process_timing(p_server);
}

static void sensor_min_period_process_timing(app_sensor_min_period_ctrl_t *p_min_ctrl)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    mesh_timer_clear(&min_peroid_ctrl_timer.timer_id);
    if (p_min_ctrl->trigger_min_period != 0)
    {
        min_peroid_ctrl_timer.delay_ms = p_min_ctrl->trigger_min_period * 1000;
        app_sensor_min_period_ctrl.trigger_flag = false;
        mesh_timer_set(&min_peroid_ctrl_timer);
        APP_LOG_INFO("pub sensor trigger !!");
    }
    else
    {
        app_sensor_min_period_ctrl.trigger_flag = true;
    }
}

static void sensor_min_period_ctrl_timer_cb(void * p_context)
{
    app_sensor_min_period_ctrl_t *min_ctrl = (app_sensor_min_period_ctrl_t *)p_context;
    APP_LOG_INFO("[%s] enter.", __func__);

    if (min_ctrl != NULL)
    {
        min_ctrl->trigger_flag = true;

        if ((min_ctrl->p_server != NULL)
            && (min_ctrl->trigger_id != 0x0000))
        {
            if (sensor_state_trigger_publish(min_ctrl->p_server, min_ctrl->trigger_id, min_ctrl->trigger_delta_value))
            {
                sensor_server_status_publish(&min_ctrl->p_server->server, true);
                APP_LOG_INFO("pub sensor trigger !!");
            }

            min_ctrl->p_server = NULL;
            min_ctrl->trigger_id = 0x0000;
            min_ctrl->trigger_flag = false;

            sensor_min_period_process_timing(min_ctrl);
        }
        else
        {
            min_ctrl->p_server = NULL;
            min_ctrl->trigger_id = 0x0000;
        }
    }
}

static int8_t sensor_state_calc_delta_percent(uint16_t property_id, int32_t trigger_delta_value)
{
    int8_t percent_value = 0;
    float percent_valuef = 0.0f;

    switch (property_id)
    {
        case 0x004E:
            percent_valuef = trigger_delta_value/ (0xFFFFFF/100); 
            break;
        default:
            break;
    }

    percent_value = percent_valuef;
    APP_LOG_INFO("[%s] percent is %d = %f.", __func__, percent_value, percent_valuef);
    return percent_value;
}

static bool sensor_state_compare_delta_trigger(sensor_cadence_status_params_t *trigger_cadence, int32_t trigger_delta_value)
{
    uint32_t property_value_down = 0;
    uint32_t property_value_up = 0;

    if ((NULL == trigger_cadence)|| (0 == trigger_delta_value))
    {
        return false;
    }

    switch (trigger_cadence->property_id)
    {
        case 0x004E:
            property_value_down = (uint32_t)trigger_cadence->trigger_dlt_down[0] |(uint32_t)trigger_cadence->trigger_dlt_down[1]<<8 |(uint32_t)trigger_cadence->trigger_dlt_down[2]<<16;
            property_value_up = (uint32_t)trigger_cadence->trigger_dlt_up[0] |(uint32_t)trigger_cadence->trigger_dlt_up[1]<<8 |(uint32_t)trigger_cadence->trigger_dlt_up[2]<<16;
            break;
        default:
            break;
    }

    APP_LOG_INFO("[%s] : value 0x%x in [0x%x, 0x%x]", __func__, trigger_delta_value, property_value_down, property_value_up);
    if ((trigger_delta_value > 0) && (property_value_up != 0))
    {
        return (property_value_up < trigger_delta_value);
    }
    else if ((trigger_delta_value < 0) && (property_value_down != 0))
    {
        return (property_value_down < (-trigger_delta_value));
    }

    return false;
}

static bool sensor_state_trigger_judge(sensor_cadence_status_params_t *trigger_cadence, int32_t trigger_delta_value)
{
    if ((NULL == trigger_cadence) || (0 == trigger_delta_value))
    {
        return false;
    }

    APP_LOG_INFO("type %d", trigger_cadence->trigger_type);
    if (MESH_SENSOR_CADENCE_TRIGGER_VALUE == trigger_cadence->trigger_type)
    {
        return sensor_state_compare_delta_trigger(trigger_cadence, trigger_delta_value);
    }
    else if (MESH_SENSOR_CADENCE_TRIGGER_PERCENT == trigger_cadence->trigger_type)
    {
        int32_t percent_value = sensor_state_calc_delta_percent(trigger_cadence->property_id, trigger_delta_value);

        percent_value *= 100;
        APP_LOG_INFO("[%s] : percent %d in [%d, %d]", __func__, percent_value,  trigger_cadence->trigger_dlt_down[0] |trigger_cadence->trigger_dlt_down[1]<<8, trigger_cadence->trigger_dlt_up[0] |trigger_cadence->trigger_dlt_up[1]<<8);
        if (percent_value > 0)
        {
            return (percent_value > (trigger_cadence->trigger_dlt_up[0] |trigger_cadence->trigger_dlt_up[1]<<8 ));
        }
        else if (percent_value < 0)
        {
            return ((-percent_value) > (trigger_cadence->trigger_dlt_down[0] |trigger_cadence->trigger_dlt_down[1]<<8 ));
        }
    }
    
    return false;
}

static bool sensor_state_trigger_publish(app_sensor_server_t *p_server, uint16_t trigger_id, int32_t trigger_delta_value)
{
    uint16_t cadence_idx = 0;
    uint16_t sensor_idx = 0;
    sensor_cadence_status_params_t *cadence_ptr = NULL;
    sensor_status_params_t *sensor_ptr = NULL;

    APP_LOG_INFO("[%s] trigger id 0x%04x, trigger value 0x%08x", __func__, trigger_id, trigger_delta_value);
    for (cadence_idx=0; cadence_idx<local_cadence_reg.candece_number; cadence_idx++)
    {
        cadence_ptr = &(local_cadence_reg.p_candece[cadence_idx]);
        APP_LOG_INFO("cadence id 0x%04x", cadence_ptr->property_id);
        if (cadence_ptr->property_id == trigger_id)
        {
            if (true == sensor_state_trigger_judge(cadence_ptr, trigger_delta_value))
            {
                for (sensor_idx = 0; sensor_idx < local_sensor_reg.sensor_state_number; sensor_idx++)
                {
                    sensor_ptr = &local_sensor_reg.p_sensor[sensor_idx];
                    if (sensor_ptr->property_id == trigger_id)
                    {
                        local_sensor_reg.sensor_pub_map[sensor_idx] = SENSOR_PUB_ON;
                        local_sensor_reg.sensor_pub_number = 1;
                        APP_LOG_INFO("trigger id 0x%04x success", trigger_id);
                        return true;
                    }
                }
            }
            break;
        }
    }

    APP_LOG_INFO("trigger id 0x%04x failure", trigger_id);
    return false;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */
void app_sensor_desc_status_register(sensor_descriptor_status_params__t * reg, uint16_t reg_length)
{
    local_decriptor_reg.desc_length = reg_length;
    local_decriptor_reg.p_desc = reg;
}

void app_sensor_cadence_status_register(sensor_cadence_status_params_t * reg, uint16_t reg_length)
{
    local_cadence_reg.candece_number = reg_length;
    local_cadence_reg.p_candece = reg;
}

void app_sensor_settings_status_register(sensor_settings_status_params_t * reg)
{
    local_settings_reg = reg;
}

void app_sensor_setting_status_register(sensor_setting_status_params_t * reg)
{
    local_setting_reg = reg;
}

void app_sensor_state_status_register(sensor_status_params_t * reg, uint8_t *pub_map, uint16_t reg_length)
{
    local_sensor_reg.sensor_state_number = reg_length;
    local_sensor_reg.sensor_pub_number = 0;
    local_sensor_reg.sensor_pub_map = pub_map;
    local_sensor_reg.p_sensor = reg;
}

void app_sensor_column_status_register(sensor_column_status_params_t * reg)
{
    local_column_reg = reg;
}
void app_sensor_series_status_register(sensor_series_status_params_t * reg)
{
    local_series_reg = reg;
}

static uint32_t sensor_state_covert_raw_to_value(uint16_t property_id, uint8_t *delta_value, uint16_t value_length)
{
    uint32_t property_value = 0;
    switch(property_id)
    {
        case 0x004E:
            property_value = (uint32_t)delta_value[0]|(uint32_t)delta_value[1]<<8|(uint32_t)delta_value[2]<<16;
            break;
        default:
            break;
    }

    return property_value;
}

void app_sensor_status_update(app_sensor_server_t * p_server, uint16_t property_id, uint8_t *delta_value, uint16_t value_length, bool decrese_flag)
{
    int32_t property_value = 0;
    uint16_t cadence_idx = 0;
    sensor_cadence_status_params_t *local_ptr = NULL;

    if ((local_sensor_reg.sensor_state_number != 0) && (local_sensor_reg.p_sensor != NULL))
    {
        uint16_t idx = 0;
        for (idx = 0; idx < local_sensor_reg.sensor_state_number; idx ++)
        {
            if (local_sensor_reg.p_sensor[idx].property_id == property_id)
            {
                sensor_set_property_value(property_id, local_sensor_reg.p_sensor[idx].p_sensor_data, delta_value, decrese_flag);
                break;
            }
        }

        property_value = sensor_state_covert_raw_to_value(property_id, delta_value, value_length);
        if (property_value == 0)
        {
            return ;
        }

        property_value = decrese_flag?(-property_value):property_value;

        for (cadence_idx=0; cadence_idx<local_cadence_reg.candece_number; cadence_idx++)
        {
            local_ptr = &(local_cadence_reg.p_candece[cadence_idx]);
            if ((NULL != local_ptr) && (local_ptr->property_id == property_id))
            {
                APP_LOG_INFO("find property id 0x%04x, cadence min interval 0x%x!!!", local_ptr->property_id, local_ptr->min_interval);
                break;
            }
        }

        if ((app_sensor_min_period_ctrl.trigger_flag == false)
                && ((app_sensor_min_period_ctrl.p_server == NULL)
                    || (app_sensor_min_period_ctrl.trigger_id== 0x0000)))
        {
            app_sensor_min_period_ctrl.p_server = p_server;
            app_sensor_min_period_ctrl.trigger_id = property_id;
            app_sensor_min_period_ctrl.trigger_delta_value = property_value;
            app_sensor_min_period_ctrl.trigger_min_period = local_ptr->min_interval;
        }
        else if (app_sensor_min_period_ctrl.trigger_flag == true)
        {
            app_sensor_min_period_ctrl.trigger_min_period = local_ptr->min_interval;
            sensor_min_period_process_timing(&app_sensor_min_period_ctrl);
            if (sensor_state_trigger_publish(p_server, property_id, property_value))
            {
                sensor_server_status_publish(&p_server->server, true);
            }
        }
    }
}

void app_sensor_status_publish(app_sensor_server_t * p_server)
{
    (void) sensor_server_status_publish(&p_server->server, false);
}

uint16_t app_sensor_server_init(app_sensor_server_t *p_server, uint8_t element_offset)
{
    if(( p_server == NULL) || (MESH_SENSOR_SERVER_INSTANCE_COUNT <= element_offset))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;
    p_server->client_address = MESH_INVALID_ADDR;
    p_server->server.settings.p_callbacks = &sensor_srv_cbs;

    p_server->pub_timer.callback = sensor_state_period_timer_cb;
    p_server->pub_timer.p_args = p_server;
    p_server->pub_timer.timer_id = MESH_INVALID_TIMER_ID;
    p_server->pub_timer.reload = true;
    p_server->publish_period_ms = 0;

    min_peroid_ctrl_timer.callback = sensor_min_period_ctrl_timer_cb;
    min_peroid_ctrl_timer.p_args = &app_sensor_min_period_ctrl;
    min_peroid_ctrl_timer.timer_id = MESH_INVALID_TIMER_ID;
    min_peroid_ctrl_timer.reload = false;

    return sensor_server_init(&p_server->server, element_offset);
}
