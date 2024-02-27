/**
 *****************************************************************************************
 *
 * @file app_light_lc_setup_server.c
 *
 * @brief APP Light LC Setup API Implementation.
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
#include "app_light_lc_setup_server.h"
#include "light_lc_setup_server.h"
#include "app_log.h"
#include "user_app.h"
#include "mesh_scenes_common.h"

/*
 * DEFINES
 ****************************************************************************************
 */
#define PROPERTY_SNYC_IN (0)
#define PROPERTY_SNYC_OUT (1)
/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void light_lc_property_state_get_cb(light_lc_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_property_get_params_t * p_in,
                                                    light_lc_property_status_params_t * p_out);

static void light_lc_property_state_set_cb(light_lc_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_property_set_params_t * p_in,
                                                    light_lc_property_status_params_t * p_out);

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
static app_light_lc_property_state_t local_lc_property[LIGHT_LC_INSTANCE_COUNT] = {0,};

const light_lc_setup_server_callbacks_t light_lc_setup_srv_cbs =
{
    .light_lc_property_get_cbs = light_lc_property_state_get_cb,
    .light_lc_property_set_cbs = light_lc_property_state_set_cb,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static inline void gx_write16p(void const *ptr16, uint16_t value)
{
    uint8_t *ptr=(uint8_t*)ptr16;

    *ptr++ = value&0xff;
    *ptr = (value&0xff00)>>8;
}

static inline uint16_t gx_read16p(void const *ptr16)
{
    uint16_t value = ((uint8_t *)ptr16)[0] | ((uint8_t *)ptr16)[1] << 8;
    return value;
}

static inline uint32_t gx_read24p(void const *ptr24)
{
    uint16_t addr_l, addr_h;
    addr_l = gx_read16p(ptr24);
    addr_h = *((uint8_t *)ptr24 + 2) & 0x00FF;
    return ((uint32_t)addr_l | (uint32_t)addr_h << 16);
}

static inline void gx_write24p(void const *ptr24, uint32_t value)
{
    uint8_t *ptr=(uint8_t*)ptr24;

    *ptr++ = (uint8_t)(value&0xff);
    *ptr++ = (uint8_t)((value&0xff00)>>8);
    *ptr++ = (uint8_t)((value&0xff0000)>>16);
}

static inline void gx_write32p(void const *ptr32, uint32_t value)
{
    uint8_t *ptr=(uint8_t*)ptr32;

    *ptr++ = (uint8_t)(value&0xff);
    *ptr++ = (uint8_t)((value&0xff00)>>8);
    *ptr++ = (uint8_t)((value&0xff0000)>>16);
    *ptr = (uint8_t)((value&0xff000000)>>24);
}

static inline uint32_t gx_read32p(void const *ptr32)
{
    uint16_t addr_l, addr_h;
    addr_l = gx_read16p(ptr32);
    addr_h = gx_read16p((uint8_t *)ptr32 + 2);
    return ((uint32_t)addr_l | (uint32_t)addr_h << 16);
}

static uint16_t light_lc_property_states_sync( app_light_lc_property_state_t * state, uint16_t property_id, uint8_t *property_value, uint8_t sync_in)
{
    uint16_t length = 0;

    if ((state == NULL) || (property_value == NULL))
    {
        APP_LOG_INFO("[%s] ERR: invalid parameter", __func__);
        return length;
    }

    switch(property_id)
    {
        case LIGHT_LC_REGULATOR_ACCURACY_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Regulator_Accuracy = *property_value;
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                *property_value = state->Regulator_Accuracy;
            }

            length = 1;
            break;
        case LIGHT_LC_LIGHTNESS_ON_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Lightness_on = gx_read16p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write16p(property_value, state->Lightness_on);
            }
            length = 2;
            break;
        case LIGHT_LC_LIGHTNESS_PROLONG_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Lightness_prolong = gx_read16p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write16p(property_value, state->Lightness_prolong);
            }
            length = 2;
            break;
        case LIGHT_LC_LIGHTNESS_STANDBY_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Lightness_standby = gx_read16p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write16p(property_value, state->Lightness_standby);
            }
            length = 2;
            break;
        case LIGHT_LC_AMBIENT_LUXLVL_ON_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->LuxLvl_on = gx_read24p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write24p(property_value, state->LuxLvl_on);
            }
            length = 3;
            break;
        case LIGHT_LC_AMBIENT_LUXLVL_PROLONG_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->LuxLvl_prolong = gx_read24p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write24p(property_value, state->LuxLvl_prolong);
            }
            length = 3;
            break;
        case LIGHT_LC_AMBIENT_LUXLVL_STANDBY_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->LuxLvl_standby = gx_read24p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write24p(property_value, state->LuxLvl_standby);
            }
            length = 3;
            break;
        case LIGHT_LC_FADE_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Time_fade = gx_read24p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write24p(property_value, state->Time_fade);
            }
            length = 3;
            break;
        case LIGHT_LC_FADE_ON_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Time_fade_on = gx_read24p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write24p(property_value, state->Time_fade_on);
            }
            length = 3;
            break;
        case LIGHT_LC_FADE_STANDBY_AUTO_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Time_fade_standby_auto = gx_read24p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write24p(property_value, state->Time_fade_standby_auto);
            }
            length = 3;
            break;
        case LIGHT_LC_FADE_STANDBY_MANUAL_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Time_fade_standby_manual = gx_read24p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write24p(property_value, state->Time_fade_standby_manual);
            }
            length = 3;
            break;
        case LIGHT_LC_TIME_OCC_DELAY_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Time_occupancy_delay = gx_read24p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write24p(property_value, state->Time_occupancy_delay);
            }
            length = 3;
            break;
        case LIGHT_LC_TIME_PROLONG_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Time_prolong = gx_read24p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write24p(property_value, state->Time_prolong);
            }
            length = 3;
            break;
        case LIGHT_LC_TIME_RUN_ON_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Time_run_on = gx_read24p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write24p(property_value, state->Time_run_on);
            }
            length = 3;
            break;
        case LIGHT_LC_REGULATOR_KID_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Regulator_kid = gx_read32p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write32p(property_value, state->Regulator_kid);
            }
            length = 4;
            break;
        case LIGHT_LC_REGULATOR_KIU_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Regulator_kiu = gx_read32p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write32p(property_value, state->Regulator_kiu);
            }
            length = 4;
            break;
        case LIGHT_LC_REGULATOR_KPD_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Regulator_kpd = gx_read32p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write32p(property_value, state->Regulator_kpd);
            }
            length = 4;
            break;
        case LIGHT_LC_REGULATOR_KPU_PROPERTY:
            if (sync_in == PROPERTY_SNYC_IN)
            {
                state->Regulator_kpu = gx_read32p(property_value);
            }
            else if (sync_in == PROPERTY_SNYC_OUT)
            {
                gx_write32p(property_value, state->Regulator_kpu);
            }
            length = 4;
            break;
        default :
            APP_LOG_INFO("[%s] ERR:unknow value length!!!", __func__);
            break;
    }

    return length;
}

static void light_lc_publish_recall_property(app_light_lc_setup_server_t *p_server, app_light_lc_property_state_t * local_state)
{
    uint16_t property_id = LIGHT_LC_AMBIENT_LUXLVL_ON_PROPERTY;
    uint8_t property_data[100] = {0,};
    uint16_t total_length = 0;
    uint16_t property_length = 0;
    light_lc_property_status_params_t pub_out = {0,};

    while(property_id <= LIGHT_LC_TIME_RUN_ON_PROPERTY)
    {
        if ((property_id >= LIGHT_LC_REGULATOR_KID_PROPERTY) && (property_id <= LIGHT_LC_REGULATOR_KPU_PROPERTY))
        {
            float property_value = 0.0;
            float property_local_value = 0.0;
            if ((0 != (property_length = light_lc_property_states_sync(local_state, property_id, (uint8_t *)&property_local_value, PROPERTY_SNYC_OUT)))
                && (0 != (property_length = light_lc_property_states_sync(&p_server->state->lc_property, property_id, (uint8_t *)&property_value, PROPERTY_SNYC_OUT))))
            {
                if ((property_value > property_local_value) || (property_value < property_local_value))
                {
                    if (pub_out.property_id == 0)
                    {
                        pub_out.property_id = property_id;
                    }
                    gx_write16p(&(property_data[total_length]), property_id);
                    total_length += 2;
                    memcpy(&(property_data[total_length]), &property_value, property_length);
                    total_length += property_length;
                    APP_LOG_INFO("find regulator property id 0x%04x, property value %f", property_id, property_value);
                }
            }
        }
        else
        {
            uint32_t property_value = 0;
            uint32_t property_local_value = 0;
            if ((0 != (property_length = light_lc_property_states_sync(local_state, property_id, (uint8_t *)&property_local_value, PROPERTY_SNYC_OUT)))
                    && (0 != (property_length = light_lc_property_states_sync(&p_server->state->lc_property, property_id, (uint8_t *)&property_value, PROPERTY_SNYC_OUT))))
            {
                if (property_value !=  property_local_value)
                {
                    if (pub_out.property_id == 0)
                    {
                        pub_out.property_id = property_id;
                    }
                    gx_write16p(&(property_data[total_length]), property_id);
                    total_length += 2;
                    memcpy(&(property_data[total_length]), &property_value, property_length);
                    total_length += property_length;
                    APP_LOG_INFO("find other property id 0x%04x, property value 0x%x", property_id, property_value);
                }
            }
        }

        property_id ++;
    }

    APP_LOG_INFO("%s : total length %d", __func__, total_length);
    pub_out.value_length = total_length -2;
    pub_out.property_value = &(property_data[2]);
    if (pub_out.property_id != 0)
    {
        light_lc_setup_server_property_status_publish(&(p_server->server), &pub_out);
    }
}

static void light_lc_property_state_set_cb(light_lc_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_property_set_params_t * p_in,
                                                    light_lc_property_status_params_t * p_out)
{
    app_light_lc_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lc_setup_server_t, server, p_self);
    light_lc_property_status_params_t pub_out = {
        .property_id = p_in->property_id,
        .value_length = p_in->value_length,
        .property_value = p_in->property_value,
    };

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET property: 0x%04X", __func__, p_self->model_instance_index, p_in->property_id);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    /* Prepare response */
    if (0 != (light_lc_property_states_sync(&p_server->state->lc_property, p_in->property_id, p_in->property_value, PROPERTY_SNYC_IN))
        && (p_out != NULL))
    {
        //p_server->light_lc_setup_set_cb(p_server->server.model_instance_index, &(p_server->state->state));
        p_out->property_id = p_in->property_id;
        p_out->value_length = p_in->value_length;
        p_out->property_value = p_in->property_value;

        //light_lc_state_machine(p_server->state);
    }

    // TODO: modify tmp property store.
    local_lc_property[p_self->model_instance_index] = p_server->state->lc_property;
    light_lc_setup_server_property_status_publish(p_self, &pub_out);
}

static void light_lc_property_state_get_cb(light_lc_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_property_get_params_t * p_in,
                                                    light_lc_property_status_params_t * p_out)
{
    app_light_lc_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_light_lc_setup_server_t, server, p_self);

    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: get property 0x%04x", __func__, p_self->model_instance_index, p_in->property_id);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    if (0 != (p_out->value_length = light_lc_property_states_sync(&p_server->state->lc_property, p_in->property_id, p_out->property_value, PROPERTY_SNYC_OUT)))
    {
        p_out->property_id = p_in->property_id;
    }

    // TODO: get property report
    //p_server->light_lc_setup_set_cb(p_server->server.model_instance_index, &(p_server->state->state));
}

static void app_light_lc_setup_scene_recall_cb(void *p_server, uint8_t *stored_state, uint16_t state_length)
{
    app_light_lc_setup_server_t *recal_server = (app_light_lc_setup_server_t *)p_server;

    APP_LOG_INFO(" [%s] enter ", __func__);
    APP_LOG_INFO("server lc setup recall state: addr %p = %p, length %d", stored_state, &(recal_server->state->lc_property), state_length);

    if (NULL == p_server)
    {
        APP_LOG_INFO(" [%s] exit : Unknow server state to recall !!!", __func__);
        return ;
    }

    if (state_length != sizeof(recal_server->state->lc_property))
    {
        APP_LOG_INFO(" [%s] exit : invalid recall param!!!", __func__);
        return ;
    }

    //light_lc_publish_all_property(recal_server, &(recal_server->state->lc_property));
    light_lc_publish_recall_property(recal_server, &(local_lc_property[recal_server->server.model_instance_index]));
    local_lc_property[recal_server->server.model_instance_index] = recal_server->state->lc_property;
    //recal_server->light_lc_set_cb(recal_server->server.model_instance_index, &(recal_server->state.lc_loo.present_loo), &(recal_server->state.lc_linear.value));
}
/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */
uint16_t app_light_lc_setup_server_property_status_publish(app_light_lc_setup_server_t *p_server, uint16_t property_id)
{
    uint16_t res_status = MESH_ERROR_SDK_INVALID_PARAM;
    light_lc_property_status_params_t property_status_params = {0, 0, NULL};
    property_status_params.value_length = property_get_value_length(property_id);
    if (property_status_params.value_length == 0)
    {
        APP_LOG_ERROR("Input invalid property id");
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    else
    {
        property_status_params.property_value = sys_malloc(sizeof(uint8_t) * property_status_params.value_length);
        if(property_status_params.property_value == NULL)
            return MESH_ERROR_SDK_INSUFFICIENT;
    }
    
    if (0 != (property_status_params.value_length = light_lc_property_states_sync(&p_server->state->lc_property, property_id, property_status_params.property_value, PROPERTY_SNYC_OUT)))
    {
        property_status_params.property_id = property_id;
        res_status = light_lc_setup_server_property_status_publish(&p_server->server, &property_status_params);
    }
    else
    {
        APP_LOG_ERROR("Light control property sync error");
        res_status = MESH_ERROR_SDK_INVALID_PARAM;
    }
    sys_free(property_status_params.property_value);
    property_status_params.property_value = NULL;
    return res_status;
}
uint16_t app_light_lc_setup_server_init(app_light_lc_setup_server_t *p_server, uint8_t element_offset, app_light_lc_set_cb_t set_cb)
{
    if(( p_server == NULL)
        || (LIGHT_LC_INSTANCE_COUNT <= element_offset)
        ||(p_server->server.lc_server == NULL)
        || (p_server->state == NULL))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    APP_LOG_INFO("lc setup 0x%p 0x%p", p_server->state, &(p_server->state->lc_property));
    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->light_lc_setup_set_cb = set_cb;

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->server.settings.p_callbacks = &light_lc_setup_srv_cbs;
    mesh_scenes_state_store_with_scene(element_offset, app_light_lc_setup_scene_recall_cb, (void *)p_server, (uint8_t *)&p_server->state->lc_property, sizeof(p_server->state->lc_property));

    local_lc_property[element_offset] = p_server->state->lc_property;
    return light_lc_setup_server_init(&p_server->server, element_offset);
}

