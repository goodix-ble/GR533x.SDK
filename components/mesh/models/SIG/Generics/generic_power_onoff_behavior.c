/**
 *****************************************************************************************
 *
 * @file mesh_ponoff_behavior.c
 *
 * @brief Mesh Power On Off Behavior API Implementation.
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
#include "generic_power_onoff_behavior.h"
#include "app_log.h"
#include "grx_sys.h"

extern uint8_t pin_on_power_up[];

void power_onoff_value_store(void)
{
    uint8_t status = nvds_put(NV_TAG_APP(POWERUP_PARAM_TAG),GENERIC_POWER_ONOFF_SERVER_INSTANCE_COUNT, &pin_on_power_up[0]);
    if (NVDS_SUCCESS == status)
    {
        APP_LOG_INFO("[%s] :Store power onoff state success.", __func__);
    }
    else
    {
        APP_LOG_ERROR("[%s] :Store power onoff state fail.", __func__);
    }
}

uint8_t store_status_before_power_down(uint16_t bind_instance_index, OnPowerUp_Bind_State_t state_enum, uint16_t off_value, uint16_t on_value, uint16_t restore_value)
{
    APP_LOG_INFO("[%s] :enter index:%d, binding nvds tag is 0x%x.", __func__, bind_instance_index, BIND_PARAM_TAG(bind_instance_index, state_enum));
    if(bind_instance_index > GENERIC_POWER_ONOFF_SERVER_INSTANCE_COUNT)
    {
        APP_LOG_INFO("[%s] :Unless CTL HSL XYL model, the bind state instance should not be more than generic power onoff instance.", __func__);
    }
    if(bind_instance_index > SUPPORT_MAX_INSTANCE)
    {
        APP_LOG_ERROR("[%s] :The support max bind state instace is :%d.", __func__, SUPPORT_MAX_INSTANCE);
        return NVDS_LENGTH_OUT_OF_RANGE;
    }

    if(state_enum > OnPowerUp_Bind_State_Max)
    {
        APP_LOG_ERROR("[%s] :The support max bind state index is :%d.", __func__, OnPowerUp_Bind_State_Max);
        return NVDS_INVALID_PARA;
    }

    uint8_t store_array[BIND_STATUS_LEN];
    store_array[0] = (uint8_t)off_value;
    store_array[1] = (uint8_t)(off_value >> 8);
    store_array[2] = (uint8_t)on_value;
    store_array[3] = (uint8_t)(on_value >> 8);
    store_array[4] = (uint8_t)restore_value;
    store_array[5] = (uint8_t)(restore_value >> 8);
    uint8_t status = nvds_put(NV_TAG_APP(BIND_PARAM_TAG(bind_instance_index, state_enum)),BIND_STATUS_LEN, &store_array[0]);
    if (NVDS_SUCCESS == status)
    {
        APP_LOG_INFO("[%s] :store bind state success off_value:%d, on_value:%d, restore_value:%d.", __func__, off_value, on_value, restore_value);
    }
    return status;
}

static uint8_t get_powerup_store_status(uint16_t bind_instance_index, OnPowerUp_Bind_State_t state_enum, bind_status_store_t* bind_status)
{
    APP_LOG_INFO("[%s] :enter index:%d.", __func__, bind_instance_index);
    uint8_t store_array[BIND_STATUS_LEN];
    uint16_t store_array_len1 = BIND_STATUS_LEN;
    uint16_t store_array_len2 = GENERIC_POWER_ONOFF_SERVER_INSTANCE_COUNT;
    uint8_t status1 = nvds_get(NV_TAG_APP(BIND_PARAM_TAG(bind_instance_index, state_enum)), &store_array_len1, &store_array[0]);
    uint8_t status2 = nvds_get(NV_TAG_APP(POWERUP_PARAM_TAG), &store_array_len2, &pin_on_power_up[0]);
    if(status2 != NVDS_SUCCESS)
    {
        APP_LOG_INFO("[%s] :Get on_power_up value from nvds failed.", __func__);
    }
    if (status1 == NVDS_SUCCESS)
    {
        APP_LOG_INFO("[%s] :NVDS get success.", __func__);
        bind_status->off_value = (uint16_t)store_array[0] | (uint16_t)store_array[1] << 8;
        bind_status->on_value = (uint16_t)store_array[2] | (uint16_t)store_array[3] << 8;
        bind_status->restore_value = (uint16_t)store_array[4] | (uint16_t)store_array[5] << 8;
    }
    return status1;
}


void power_up_sequence_behavior(uint8_t bind_instance_index, uint8_t power_onoff_instance_index, OnPowerUp_Bind_State_t state_enum, uint16_t* bind_state)
{
    if (GENERIC_POWER_ONOFF_SERVER_INSTANCE_COUNT <= power_onoff_instance_index)
    {
        APP_LOG_ERROR("[%s] :the input power onoff instance index is invalid.", __func__);
        return;
    }
    bind_status_store_t bind_status;
    uint8_t status = get_powerup_store_status(bind_instance_index, state_enum, &bind_status);
    if (NVDS_SUCCESS == status)
    {
        if (0x00 == pin_on_power_up[power_onoff_instance_index])
        {
            *bind_state = bind_status.off_value;
            APP_LOG_INFO("[%s] :The value of OnPowerUp is 0x00, set the bind state to off value: %d.", __func__, *bind_state);
        }
        else if (0x01 == pin_on_power_up[power_onoff_instance_index])
        {
            *bind_state = bind_status.on_value;
            APP_LOG_INFO("[%s] :The value of OnPowerUp is 0x01, set the bind state to on value: %d.", __func__, *bind_state);
        }
        else if (0x02 == pin_on_power_up[power_onoff_instance_index])
        {
            *bind_state = bind_status.restore_value;
            APP_LOG_INFO("[%s] :The value of OnPowerUp is 0x02, set the bind state to restore value: %d. ", __func__, *bind_state);
        }
    }
    else
    {
        APP_LOG_WARNING("[%s] : Bind state not be stored before power down. ", __func__);
    }
}

void clear_power_up_bind_state(void)
{
    APP_LOG_INFO("Clear nvds tag about on power up.");
    for (uint8_t j = 0; j <= SUPPORT_MAX_INSTANCE; j++)
    {
        for (uint8_t i = 0; i < OnPowerUp_Bind_State_Max; i++)
        {
            nvds_del(BIND_PARAM_TAG(j, i));
        }
    }
}


