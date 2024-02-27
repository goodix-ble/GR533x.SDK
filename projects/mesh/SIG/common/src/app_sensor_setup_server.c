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
#include "app_sensor_setup_server.h"
#include "app_sensor_server.h"
#include "sensor_setup_server.h"
#include "app_log.h"
#include "user_app.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void sensor_cadence_state_get_cb(sensor_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const sensor_cadence_get_params_t * p_in,
                                                    sensor_cadence_status_params_t * p_out);

static void sensor_cadence_state_set_cb(sensor_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const sensor_cadence_set_params_t * p_in,
                                                    sensor_cadence_status_params_t * p_out);

static void sensor_settings_state_get_cb(sensor_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const sensor_settings_get_params_t * p_in,
                                                    sensor_settings_status_params_t * p_out);

static void sensor_setting_state_get_cb(sensor_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const sensor_setting_get_params_t * p_in,
                                                    sensor_setting_status_params_t * p_out);

static void sensor_setting_state_set_cb(sensor_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const sensor_setting_set_params_t * p_in,
                                                    sensor_setting_status_params_t * p_out);


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
const sensor_setup_server_callbacks_t sensor_setup_srv_cbs =
{
    .sensor_setup_cbs.cadence_get_cb = sensor_cadence_state_get_cb,
    .sensor_setup_cbs.cadence_set_cb = sensor_cadence_state_set_cb,
    .sensor_setup_cbs.settings_get_cb = sensor_settings_state_get_cb,
    .sensor_setup_cbs.setting_get_cb = sensor_setting_state_get_cb,
    .sensor_setup_cbs.setting_set_cb = sensor_setting_state_set_cb,
};

extern app_sensor_cadence_t local_cadence_reg;//trggier dlt length should more than 2
extern sensor_settings_status_params_t *local_settings_reg;
extern sensor_setting_status_params_t *local_setting_reg;

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static void sensor_cadence_state_get_cb(sensor_setup_server_t  * p_self,
                                                                                const mesh_model_msg_ind_t *p_rx_msg,
                                                                                const sensor_cadence_get_params_t * p_in,
                                                                                sensor_cadence_status_params_t * p_out)
{
    app_sensor_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_sensor_setup_server_t, server, p_self);
    sensor_cadence_status_params_t *local_ptr = NULL;
    uint16_t i = 0;
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    for(i=0; i<local_cadence_reg.candece_number; i++)
    {   
        local_ptr = &(local_cadence_reg.p_candece[i]);
        if ((NULL != local_ptr) && (local_ptr->property_id == p_in->property_id))
        {
            memcpy(p_out, local_ptr, sizeof(sensor_cadence_status_params_t));
            break;
        }
    }

    if (i == local_cadence_reg.candece_number)
    {
        p_out->property_id = p_in->property_id;
        p_out->property_value_length = 0;
        p_out->trigger_dlt_down = NULL;
        p_out->trigger_dlt_up = NULL;
        p_out->fast_cadence_low = NULL;
        p_out->fast_cadence_high = NULL;
    }

}

static void sensor_cadence_state_set_cb(sensor_setup_server_t  * p_self,
                                                                                const mesh_model_msg_ind_t *p_rx_msg,
                                                                                const sensor_cadence_set_params_t * p_in,
                                                                                sensor_cadence_status_params_t * p_out)
{
    app_sensor_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_sensor_setup_server_t, server, p_self);
    sensor_cadence_status_params_t pub_param;
    sensor_cadence_status_params_t *local_ptr = NULL;
    uint16_t i = 0;
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET ", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    APP_LOG_INFO("property id set 0x%04x, value length %d", p_in->property_id, p_in->property_value_length);
    for (i=0; i<local_cadence_reg.candece_number; i++)
    {
        local_ptr = &(local_cadence_reg.p_candece[i]);
        APP_LOG_INFO("property id 0x%04x, value length %d", local_ptr->property_id, local_ptr->property_value_length);
        if ((NULL != local_ptr) && (local_ptr->property_id == p_in->property_id) && (local_ptr->property_value_length == p_in->property_value_length))
        {
            local_ptr->fast_cadence_period_div = p_in->fast_cadence_period_div;
            local_ptr->trigger_type = p_in->trigger_type;
            if (local_ptr->trigger_type == MESH_SENSOR_CADENCE_TRIGGER_VALUE)
            {
                memcpy(local_ptr->trigger_dlt_down, p_in->trigger_dlt_down, local_ptr->property_value_length);
                memcpy(local_ptr->trigger_dlt_up, p_in->trigger_dlt_up, local_ptr->property_value_length);
            }
            else
            {
                memcpy(local_ptr->trigger_dlt_down, p_in->trigger_dlt_down, 2);
                memcpy(local_ptr->trigger_dlt_up, p_in->trigger_dlt_up, 2);
            }

            memcpy(local_ptr->fast_cadence_low, p_in->fast_cadence_low, local_ptr->property_value_length);
            memcpy(local_ptr->fast_cadence_high, p_in->fast_cadence_high, local_ptr->property_value_length);

            local_ptr->min_interval = p_in->min_interval;
            memcpy(&pub_param, local_ptr, sizeof(sensor_cadence_status_params_t));
            break;
        }
    }

    if (i == local_cadence_reg.candece_number)
    {
        pub_param.property_id = p_in->property_id;
        pub_param.property_value_length = 0;
        pub_param.trigger_dlt_down = NULL;
        pub_param.trigger_dlt_up = NULL;
        pub_param.fast_cadence_low = NULL;
        pub_param.fast_cadence_high = NULL;
    }

    if (NULL != p_out)
    {
        APP_LOG_INFO("property id out 0x%04x, pub 0x%04x", p_out->property_id, pub_param.property_id);
        memcpy(p_out, &pub_param, sizeof(sensor_cadence_status_params_t));
    }

    p_server->cadence_set_cb(p_server->server.model_instance_index, &pub_param);
    sensor_setup_server_cadence_status_publish(p_self, &pub_param);
}

static void sensor_settings_state_get_cb(sensor_setup_server_t  * p_self,
                                                                                const mesh_model_msg_ind_t *p_rx_msg,
                                                                                const sensor_settings_get_params_t * p_in,
                                                                                sensor_settings_status_params_t * p_out)
{
    app_sensor_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_sensor_setup_server_t, server, p_self);
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    if ((NULL != local_settings_reg) && (local_settings_reg->property_id == p_in->property_id))
    {
        memcpy(p_out, local_settings_reg, sizeof(sensor_settings_status_params_t));
    }
    else
    {
        p_out->property_id = p_in->property_id;
        p_out->setting_id_number = 0;
        p_out->setting_property_id = NULL;
    }
}

static void sensor_setting_state_get_cb(sensor_setup_server_t  * p_self,
                                                                            const mesh_model_msg_ind_t *p_rx_msg,
                                                                            const sensor_setting_get_params_t * p_in,
                                                                            sensor_setting_status_params_t * p_out)
{
    app_sensor_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_sensor_setup_server_t, server, p_self);
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    if ((NULL != local_setting_reg)
            && (local_setting_reg->property_id == p_in->property_id)
            && (local_setting_reg->setting_property_id == p_in->setting_property_id))
    {
        memcpy(p_out, local_setting_reg, sizeof(sensor_setting_status_params_t));
    }
    else
    {
        p_out->property_id = p_in->property_id;
        p_out->setting_property_id = p_in->setting_property_id;
        p_out->setting_raw_length = 0;
    }
}

static void sensor_setting_state_set_cb(sensor_setup_server_t  * p_self,
                                                                            const mesh_model_msg_ind_t *p_rx_msg,
                                                                            const sensor_setting_set_params_t * p_in,
                                                                            sensor_setting_status_params_t * p_out)
{
    app_sensor_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_sensor_setup_server_t, server, p_self);
    sensor_setting_status_params_t pub_param;
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: GET ", __func__, p_self->model_instance_index);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    if ((NULL != local_setting_reg)
            && (local_setting_reg->property_id == p_in->property_id)
            && (local_setting_reg->setting_property_id == p_in->setting_property_id))
    {
        if ((local_setting_reg->setting_access == MESH_SENSOR_SETTING_ACCESS_RW)
                && (local_setting_reg->setting_raw_length == p_in->setting_raw_length))
        {
            local_setting_reg->property_id = p_in->property_id;
            local_setting_reg->setting_property_id= p_in->setting_property_id;
            memcpy(local_setting_reg->setting_raw, p_in->setting_raw, local_setting_reg->setting_raw_length);

            memcpy(&pub_param, p_in, sizeof(sensor_setting_status_params_t));
        }
        else if (local_setting_reg->setting_access == MESH_SENSOR_SETTING_ACCESS_RD)
        {
            memcpy(&pub_param, local_setting_reg, sizeof(sensor_setting_status_params_t));
        }
    }
    else
    {
        pub_param.property_id = p_in->property_id;
        pub_param.setting_property_id = p_in->setting_property_id;
        pub_param.setting_raw_length = 0;
    }

    if (NULL != p_out)
    {
        memcpy(p_out, &pub_param, sizeof(sensor_setting_status_params_t));
    }

    p_server->setting_get_cb(p_server->server.model_instance_index, &pub_param);
    sensor_setup_server_setting_status_publish(p_self, &pub_param);
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */
uint16_t app_sensor_setup_server_init(app_sensor_setup_server_t *p_server, uint8_t element_offset, app_sensor_cadence_set_cb_t cadence_set_cb, app_sensor_setting_set_cb_t setting_set_cb)
{
    if(( p_server == NULL) || (MESH_SENSOR_SERVER_INSTANCE_COUNT <= element_offset))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.settings.p_callbacks = &sensor_setup_srv_cbs;
    p_server->server.model_instance_index = element_offset;

    p_server->cadence_set_cb = cadence_set_cb;
    p_server->setting_get_cb = setting_set_cb;
    p_server->client_address = MESH_INVALID_ADDR;
        
    return sensor_setup_server_init(&p_server->server, element_offset);
}
