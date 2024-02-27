/**
 *****************************************************************************************
 *
 * @file light_lc_server.c
 *
 * @brief Light LC Server API Implementation.
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
#include "app_log.h"
#include "light_lc_message.h"
#include "light_lc_server.h"
#include "grx_sys.h"
#include "common_utils.h"
#include "app_light_lc_server.h"
/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

static void handle_mode_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_mode_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_OM_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_OM_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_loo_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_loo_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_sensor_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void light_lc_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void light_lc_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
static const uint16_t light_lc_server_opcode_list[] =
{
    LIGHT_LC_MODE_OPCODE_GET,
    LIGHT_LC_MODE_OPCODE_SET ,
    LIGHT_LC_MODE_OPCODE_SET_UNACKNOWLEDGED,
    LIGHT_LC_OM_OPCODE_GET,
    LIGHT_LC_OM_OPCODE_SET,
    LIGHT_LC_OM_OPCODE_SET_UNACKNOWLEDGED,
    LIGHT_LC_LOO_OPCODE_GET,
    LIGHT_LC_LOO_OPCODE_SET,
    LIGHT_LC_LOO_OPCODE_SET_UNACKNOWLEDGED,
    LIGHT_LC_SENSOR_OPCODE_STATUS,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {LIGHT_LC_MODE_OPCODE_GET, handle_mode_get_cb},
    {LIGHT_LC_MODE_OPCODE_SET, handle_mode_set_cb},
    {LIGHT_LC_MODE_OPCODE_SET_UNACKNOWLEDGED, handle_mode_set_cb},
    {LIGHT_LC_OM_OPCODE_GET, handle_OM_get_cb},
    {LIGHT_LC_OM_OPCODE_SET, handle_OM_set_cb},
    {LIGHT_LC_OM_OPCODE_SET_UNACKNOWLEDGED, handle_OM_set_cb},
    {LIGHT_LC_LOO_OPCODE_GET, handle_loo_get_cb},
    {LIGHT_LC_LOO_OPCODE_SET, handle_loo_set_cb},
    {LIGHT_LC_LOO_OPCODE_SET_UNACKNOWLEDGED, handle_loo_set_cb},
    {LIGHT_LC_SENSOR_OPCODE_STATUS, handle_sensor_status_cb},
};

static const mesh_model_cb_t light_lc_server_msg_cb = {
    .cb_rx             = light_lc_server_rx_cb,
    .cb_sent           = light_lc_server_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t light_lc_server_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_LIGHTS_LC),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)light_lc_server_opcode_list,
    .num_opcodes = sizeof(light_lc_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &light_lc_server_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static uint32_t mode_status_send(light_lc_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const light_lc_mode_status_params_t * p_params)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    light_lc_mode_status_msg_pkt_t msg_pkt;
    uint8_t tx_hdl = LIGHT_LC_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * LIGHT_LC_SERVER_TX_HDL_TOTAL;
    uint32_t ERR_CODE = MESH_ERROR_NO_ERROR;

    msg_pkt.mode = p_params->mode;

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_LC_MODE_OPCODE_STATUS),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) &msg_pkt,
        .data_send_len = LIGHT_LC_MODE_STATUS_MINLEN,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };

    if (NULL == p_rx_msg)
    {
        APP_LOG_INFO("SERVER[%d] -- to publish.", p_server->model_instance_index);
        ERR_CODE = mesh_model_publish(&msg_send, NULL);
    }
    else
    {
        APP_LOG_INFO("SERVER[%d] -- to response.", p_server->model_instance_index);
        ERR_CODE = mesh_model_rsp_send(&msg_send);
    }

    return ERR_CODE;

}

static uint32_t om_status_send(light_lc_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const light_lc_om_status_params_t * p_params)
{
    APP_LOG_INFO("[%s] enter.", __func__);

    light_lc_om_status_msg_pkt_t msg_pkt;
    uint8_t tx_hdl = LIGHT_LC_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * LIGHT_LC_SERVER_TX_HDL_TOTAL;
    uint32_t ERR_CODE = MESH_ERROR_NO_ERROR;

    msg_pkt.mode = p_params->mode;

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_LC_OM_OPCODE_STATUS),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) &msg_pkt,
        .data_send_len = LIGHT_LC_OM_STATUS_MINLEN,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };

    if (NULL == p_rx_msg)
    {
        APP_LOG_INFO("SERVER[%d] -- to publish.", p_server->model_instance_index);
        ERR_CODE = mesh_model_publish(&msg_send, NULL);
    }
    else
    {
        APP_LOG_INFO("SERVER[%d] -- to response.", p_server->model_instance_index);
        ERR_CODE = mesh_model_rsp_send(&msg_send);
    }

    return ERR_CODE;

}

static uint32_t loo_status_send(light_lc_server_t * p_server,
                                  const mesh_model_msg_ind_t *p_rx_msg,
                                  const light_lc_loo_status_params_t * p_params)
{
    APP_LOG_INFO("[%s] enter.", __func__);
    
    light_lc_loo_status_msg_pkt_t msg_pkt;
    uint8_t tx_hdl = (NULL == p_rx_msg) ? LIGHT_LC_SERVER_PUBLISH_SEND_TX_HDL + p_server->model_instance_index * LIGHT_LC_SERVER_TX_HDL_TOTAL
                                        : LIGHT_LC_SERVER_RSP_SEND_TX_HDL + p_server->model_instance_index * LIGHT_LC_SERVER_TX_HDL_TOTAL;


    if (p_params->remaining_time_ms > TRANSITION_TIME_STEP_10M_MAX)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    msg_pkt.present_loo = p_params->present_loo;
    if (p_params->remaining_time_ms > 0)
    {
        msg_pkt.target_loo = p_params->target_loo;
        msg_pkt.remaining_time = model_transition_time_encode(p_params->remaining_time_ms);
    }

    mesh_model_send_info_t msg_send =
    {
        .model_lid = p_server->model_lid,
        .opcode = MESH_ACCESS_OPCODE_SIG(LIGHT_LC_LOO_OPCODE_STATUS),
        .tx_hdl = tx_hdl,
        .p_data_send = (uint8_t *) &msg_pkt,
        .data_send_len = p_params->remaining_time_ms > 0 ? LIGHT_LC_LOO_STATUS_MAXLEN : LIGHT_LC_LOO_STATUS_MINLEN,
        .dst = (NULL == p_rx_msg) ? MESH_INVALID_ADDR : p_rx_msg->src,
        .appkey_index = (NULL == p_rx_msg) ? MESH_INVALID_KEY_INDEX : p_rx_msg->appkey_index,
    };

    if (p_params->remaining_time_ms > 0)
    {
        APP_LOG_INFO("SERVER[%d] light LC Light -- present_on_off = %d, target_on_off = %d, remaining_time = %d.",
                p_server->model_instance_index, msg_pkt.present_loo, msg_pkt.target_loo, msg_pkt.remaining_time);
    }
    else
    {
        APP_LOG_INFO("SERVER[%d] light LC Light -- present_on_off = %d.", p_server->model_instance_index, msg_pkt.present_loo);
    }

    if (NULL == p_rx_msg)
    {
        
        APP_LOG_INFO("SERVER[%d] -- to publish.", p_server->model_instance_index);
        return mesh_model_publish(&msg_send, NULL);
    }
    else
    {
        APP_LOG_INFO("SERVER[%d] -- to response.", p_server->model_instance_index);
        return mesh_model_rsp_send(&msg_send);
    }
}

static void handle_mode_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_lc_server_t  * p_server = (light_lc_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to set light LC mode state!!!", p_server->model_instance_index);

    if (p_rx_msg->msg_len == LIGHT_LC_MODE_SET_MINLEN)
    {
        light_lc_mode_set_params_t in_data = {0};
        light_lc_mode_status_params_t out_data = {0};
        light_lc_mode_set_msg_pkt_t * p_msg_params_packed = (light_lc_mode_set_msg_pkt_t *) p_rx_msg->msg;

        in_data.mode = p_msg_params_packed->mode;
        p_server->settings.p_callbacks->light_lc_mode_set_cbs(p_server,
                                                            p_rx_msg,
                                                            &in_data,
                                                            (LIGHT_LC_MODE_OPCODE_SET == p_rx_msg->opcode.company_opcode) ? &out_data : NULL);

        if (LIGHT_LC_MODE_OPCODE_SET == p_rx_msg->opcode.company_opcode)
        {
            (void) mode_status_send(p_server, p_rx_msg, &out_data);
        }
    }
}

static void handle_mode_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_lc_server_t  * p_server = (light_lc_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get light LC mode state!!!", p_server->model_instance_index);

    if (p_rx_msg->msg_len == LIGHT_LC_MODE_GET_MINLEN)
    {
        light_lc_mode_status_params_t out_data = {0};

        p_server->settings.p_callbacks->light_lc_mode_get_cbs(p_server,
                                                            p_rx_msg,
                                                            &out_data);

        (void) mode_status_send(p_server, p_rx_msg, &out_data);
    }
}

static void handle_OM_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_lc_server_t  * p_server = (light_lc_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to set light LC Occupancy mode state!!!", p_server->model_instance_index);

    if (p_rx_msg->msg_len == LIGHT_LC_OM_SET_MINLEN)
    {
        light_lc_om_set_params_t in_data = {0};
        light_lc_om_status_params_t out_data = {0};
        light_lc_om_set_msg_pkt_t * p_msg_params_packed = (light_lc_om_set_msg_pkt_t *) p_rx_msg->msg;

        in_data.mode = p_msg_params_packed->mode;
        p_server->settings.p_callbacks->light_lc_om_set_cbs(p_server,
                                                                                            p_rx_msg,
                                                                                            &in_data,
                                                                                            (LIGHT_LC_OM_OPCODE_SET == p_rx_msg->opcode.company_opcode) ? &out_data : NULL);

        if (LIGHT_LC_OM_OPCODE_SET == p_rx_msg->opcode.company_opcode)
        {
            (void) om_status_send(p_server, p_rx_msg, &out_data);
        }
    }
}

static void handle_OM_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_lc_server_t  * p_server = (light_lc_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get light LC Occupancy mode state!!!", p_server->model_instance_index);

    if (p_rx_msg->msg_len == LIGHT_LC_OM_GET_MINLEN)
    {
        light_lc_om_status_params_t out_data = {0};

        p_server->settings.p_callbacks->light_lc_om_get_cbs(p_server,
                                                            p_rx_msg,
                                                            &out_data);

        (void) om_status_send(p_server, p_rx_msg, &out_data);
    }
}

static void handle_loo_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_lc_server_t  * p_server = (light_lc_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to set light LC Light OnOff state!!!", p_server->model_instance_index);

    if ((p_rx_msg->msg_len == LIGHT_LC_LOO_SET_MINLEN) || (p_rx_msg->msg_len == LIGHT_LC_LOO_SET_MAXLEN))
    {
        light_lc_loo_set_params_t in_data = {0};
        model_transition_t in_data_tr = {0};
        light_lc_loo_status_params_t out_data = {0};
        light_lc_loo_set_msg_pkt_t * p_msg_params_packed = (light_lc_loo_set_msg_pkt_t *) p_rx_msg->msg;

        in_data.loo= p_msg_params_packed->loo;
        in_data.tid = p_msg_params_packed->tid;

        if (model_tid_validate(&p_server->tid_tracker, p_rx_msg, p_rx_msg->opcode.company_opcode, in_data.tid))
        {
            if (p_rx_msg->msg_len == LIGHT_LC_LOO_SET_MAXLEN)
            {
                if (!model_transition_time_is_valid(p_msg_params_packed->transition_time))
                {
                    return;
                }

                in_data_tr.transition_time_ms = model_transition_time_decode(p_msg_params_packed->transition_time);
                in_data_tr.delay_ms = model_delay_decode(p_msg_params_packed->delay);
                APP_LOG_INFO("SERVER[%d] -- transition_time_ms = %d, delay_ms = %d", p_server->model_instance_index, in_data_tr.transition_time_ms, in_data_tr.delay_ms);
            }
            else
            {
                if (p_server->p_dtt_ms == NULL)
                {
                    model_update_dtt_ptr(&(p_server->p_dtt_ms));
                }

                if (p_server->p_dtt_ms != NULL)
                {
                    in_data_tr.transition_time_ms = model_transition_time_decode(*p_server->p_dtt_ms);
                    in_data_tr.delay_ms = 0;

                    APP_LOG_INFO("SERVER[%d] -- default transition time = %d", p_server->model_instance_index, in_data_tr.transition_time_ms);
                }
            }

            p_server->settings.p_callbacks->light_lc_loo_set_cbs(p_server,
                                                                                            p_rx_msg,
                                                                                            &in_data,
                                                                                            ((p_rx_msg->msg_len == LIGHT_LC_LOO_SET_MINLEN)&&(p_server->p_dtt_ms == NULL)) ? NULL : &in_data_tr,
                                                                                            (p_rx_msg->opcode.company_opcode == LIGHT_LC_LOO_OPCODE_SET) ? ((void *)&out_data) : NULL);

            if (p_rx_msg->opcode.company_opcode == LIGHT_LC_LOO_OPCODE_SET)
            {
                (void) loo_status_send(p_server, p_rx_msg, &out_data);
            }
        }
    }
}

static void handle_loo_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_lc_server_t  * p_server = (light_lc_server_t  *) p_args;

    APP_LOG_INFO("[%s] enter.", __func__);
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get light LC Light OnOff state!!!", p_server->model_instance_index);

    if (p_rx_msg->msg_len == LIGHT_LC_LOO_GET_MINLEN)
    {
        light_lc_loo_status_params_t out_data = {0};

        p_server->settings.p_callbacks->light_lc_loo_get_cbs(p_server,
                                                            p_rx_msg,
                                                            &out_data);

        (void) loo_status_send(p_server, p_rx_msg, &out_data);
    }
}

static void delay_set_Light_LC_OCC_timer_cb(void * p_context)
{
    app_light_lc_server_t  * p_server = (app_light_lc_server_t  *) p_context;
    p_server->state.lc_occ_value.value = LC_HAS_OCCUPANCY_REPORT;
    if (p_server->state.lc_om.mode == LIGHT_LC_OCC_MODE_STATE_OCC)
    {
        light_lc_state_machine(p_server, &p_server->state, LIGHT_LC_STATE_MECHINE_EVENTS_OCC_ON);
    }
}

static void handle_sensor_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    light_lc_server_t  * p_server = (light_lc_server_t  *) p_args;
    uint16_t total_length = p_rx_msg->msg_len;
    uint8_t i = 0;
    for(i = 0;i < p_rx_msg->msg_len;i++)
    {
        APP_LOG_INFO("p_rx_msg->msg[%d]:0x%x", i, p_rx_msg->msg[i]);
    }

    light_lc_property_status_msg_pkt_t * msg_pkt = (light_lc_property_status_msg_pkt_t *) p_rx_msg->msg;
    uint8_t *msg_ptr = (uint8_t *)p_rx_msg->msg;
    uint8_t lc_senser_mask = 0;
    uint8_t lc_occupancy = LC_NO_OCCUPANCY_REPORT;
    uint32_t lc_amb_luxlvl = 0;

    APP_LOG_INFO("[%s] enter.", __func__);
    APP_LOG_INFO("SERVER[%d] -- Receive message, want to get light LC sensor state!!!", p_server->model_instance_index);

    while(total_length > 2)
    {
        uint16_t lc_sensor_property_id = gx_read16p((void *)&msg_pkt->property_id);
        APP_LOG_INFO("[%s],lc_sensor_property_id:0x%x", __func__, lc_sensor_property_id);

        switch(lc_sensor_property_id)
        {
            case MOTION_SENSED_PROPERTY:
            {
                Motion_Sense_U8_Format value = msg_pkt->property_value[0];
                APP_LOG_INFO("[%s],value:0x%x", __func__, value);
                if (value > 0)
                {
                    lc_senser_mask |= LC_OCCUPANCY_BIT;
                    lc_occupancy = LC_HAS_OCCUPANCY_REPORT;
                }
                msg_ptr += sizeof(light_lc_property_status_msg_pkt_t) + sizeof(Motion_Sense_U8_Format);
                total_length -= (sizeof(light_lc_property_status_msg_pkt_t) + sizeof(Motion_Sense_U8_Format));
            }
            break;
            case PEOPLE_COUNT_PROPERTY:
            {
                People_Count_U16_Format value = gx_read16p((void *)msg_pkt->property_value);

                if (value > 0)
                {
                    lc_senser_mask |= LC_OCCUPANCY_BIT;
                    lc_occupancy = LC_HAS_OCCUPANCY_REPORT;
                }
                msg_ptr += sizeof(light_lc_property_status_msg_pkt_t) + sizeof(People_Count_U16_Format);
                total_length -= sizeof(light_lc_property_status_msg_pkt_t) + sizeof(People_Count_U16_Format);
            }
            break;
            case PRESENCE_DETECTED_PROPERTY:
            {
                Presence_detected_U8_Format value = msg_pkt->property_value[0];

                if (value > 0)
                {
                    lc_senser_mask |= LC_OCCUPANCY_BIT;
                    lc_occupancy = LC_HAS_OCCUPANCY_REPORT;
                }
                msg_ptr += sizeof(light_lc_property_status_msg_pkt_t) + sizeof(Presence_detected_U8_Format);
                total_length -= sizeof(light_lc_property_status_msg_pkt_t) + sizeof(Presence_detected_U8_Format);
            }
            break;
            case TIME_SINCE_MOTION_SENSED_PROPERTY:
            {
                Time_Since_Motion_Sense_U16_Format value = gx_read16p((void *)msg_pkt->property_value);
#ifdef MESH_MODEL_BQB_TEST
                lc_senser_mask |= LC_OCCUPANCY_BIT;
#else
                app_light_lc_server_t *app_server = PARENT_BY_FIELD_GET(app_light_lc_server_t, server, p_server);
                if (((uint32_t)value)*1000 > app_server->state.lc_property.Time_occupancy_delay)
                {
                    APP_LOG_WARNING("TIME_SINCE_MOTION_SENSED_PROPERTY value is more than Light LC Occupancy Delay state", value);
                    return;
                }
                else
                {
                    mesh_timer_t delay_timer;
                    delay_timer.timer_id = MESH_INVALID_TIMER_ID;
                    delay_timer.p_args = app_server;
                    delay_timer.reload = false;
                    delay_timer.delay_ms = app_server->state.lc_property.Time_occupancy_delay - (((uint32_t)value)*1000);
                    delay_timer.callback = delay_set_Light_LC_OCC_timer_cb;
                    mesh_timer_set(&delay_timer);
                }
#endif
                msg_ptr += sizeof(light_lc_property_status_msg_pkt_t) + sizeof(Time_Since_Motion_Sense_U16_Format);
                total_length -= sizeof(light_lc_property_status_msg_pkt_t) + sizeof(Time_Since_Motion_Sense_U16_Format);
            }
            break;
            case PRESENCE_AMB_LUXLVL_PROPERTY:
            {
                Presence_Amb_LuxLVL_U24_Format value = gx_read24p((void *)msg_pkt->property_value);

                lc_senser_mask |= LC_AMB_LUXLVL_BIT;
                lc_amb_luxlvl = value;

                msg_ptr += sizeof(light_lc_property_status_msg_pkt_t) + sizeof(Presence_Amb_LuxLVL_U24_Format) -1;
                total_length -= sizeof(light_lc_property_status_msg_pkt_t) + sizeof(Presence_Amb_LuxLVL_U24_Format) -1;
            }
            break;
            default:
            {
                APP_LOG_WARNING("can't find property 0x%04x !!!", lc_sensor_property_id);
            }
            return;
        }

        msg_pkt = (light_lc_property_status_msg_pkt_t *)msg_ptr;
    }

    if ((lc_senser_mask & (LC_OCCUPANCY_BIT |LC_AMB_LUXLVL_BIT)) != 0)
    {
        APP_LOG_INFO("[%s]:light_lc_sensor_state_cbs", __func__);
        p_server->settings.p_callbacks->light_lc_sensor_state_cbs(p_server,
                                                                    p_rx_msg,
                                                                    lc_senser_mask,
                                                                    lc_occupancy,
                                                                    lc_amb_luxlvl);
    }
}

static void light_lc_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    mesh_opcode_handler_cb_t handler = NULL;

    for(uint8_t i = 0; i<light_lc_server_register_info.num_opcodes; i++)
    {
        if(company_opcode == m_opcode_handlers[i].opcode)
        {
            handler = m_opcode_handlers[i].handler;
            break;
        }
    }

    if (NULL != handler)
    {
        handler(p_model_msg, p_args);
    }
}

static void light_lc_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    light_lc_server_t * p_server = (light_lc_server_t *) p_args;
    
    switch(p_sent->tx_hdl - p_server->model_instance_index * LIGHT_LC_SERVER_TX_HDL_TOTAL)
    {
        case LIGHT_LC_SERVER_RSP_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Responsed get or set message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to responsed get or set message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        case LIGHT_LC_SERVER_PUBLISH_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("SERVER[%d] -- Published message!!!", p_server->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("SERVER[%d] -- Failed to published message, status = %x!!!", p_server->model_instance_index, p_sent->status);
            }
            break;
        default:
            APP_LOG_INFO("Never here!!!");
            break;
    }
}



/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t light_lc_server_init(light_lc_server_t *p_server, uint8_t element_offset)
{
    //note: check parameters!!!
    if (NULL == p_server
        || NULL == p_server->settings.p_callbacks
        || NULL == p_server->settings.p_callbacks->light_lc_mode_set_cbs
        || NULL == p_server->settings.p_callbacks->light_lc_mode_get_cbs
        || NULL == p_server->settings.p_callbacks->light_lc_om_set_cbs
        || NULL == p_server->settings.p_callbacks->light_lc_om_get_cbs
        || NULL == p_server->settings.p_callbacks->light_lc_loo_set_cbs
        || NULL == p_server->settings.p_callbacks->light_lc_loo_get_cbs
        || NULL == p_server->settings.p_callbacks->light_lc_sensor_state_cbs
        || LIGHT_LC_SERVER_INSTANCE_COUNT_MAX <= p_server->model_instance_index)        
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    light_lc_server_register_info.p_args = p_server;
    light_lc_server_register_info.element_offset = element_offset;  //note: element_offset should < mesh_prov_param_t::nb_element!!!
    
    return mesh_model_register(&light_lc_server_register_info, &p_server->model_lid);
}

uint16_t light_lc_server_mode_status_publish(light_lc_server_t * p_server, 
                                                            const light_lc_mode_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return mode_status_send(p_server, NULL, p_params);
}

uint16_t light_lc_server_occ_mode_status_publish(light_lc_server_t * p_server, 
                                                            const light_lc_om_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return om_status_send(p_server, NULL, p_params);
}

uint16_t light_lc_server_loo_status_publish(light_lc_server_t * p_server, 
                                                            const light_lc_loo_status_params_t * p_params)
{
    if (NULL == p_server || NULL == p_params)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    return loo_status_send(p_server, NULL, p_params);
}

void test_receive_sensor_msg(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    handle_sensor_status_cb(p_rx_msg, p_args);
    uint8_t i = 0;
    for(i = 0;i < p_rx_msg->msg_len;i++)
    {
        APP_LOG_INFO("[%s]p_rx_msg->msg[%d]:0x%x", __func__, i, p_rx_msg->msg[i]);
    }
}
