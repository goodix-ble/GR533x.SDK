/**
 *****************************************************************************************
 *
 * @file generic_power_onoff_behavior.h
 *
 * @brief Mesh Ponoff Behavior API.
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
 
 /**
 * @addtogroup MESH
 * @{
 */
#ifndef __MESH_PONOFF_BEHAVIOR_H__
#define __MESH_PONOFF_BEHAVIOR_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "app_power_onoff_server.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * DEFINES
 ****************************************************************************************
 */
#define POWERUP_PARAM_TAG                      0x0910

// onpowerup tag range from 0x0911~ 0x09FF
#define BIND_PARAM_TAG(instance, state_idx)      (0x0911 + (instance<<4 | state_idx))
#define SUPPORT_MAX_INSTANCE                   0x06    // max range is 0x0E
//#define SUPPORT_MAX_STATE_INDEX             0xE
#define BIND_STATUS_LEN                        sizeof(bind_status_store_t)

typedef enum
{
    OnPowerUp_Bind_OnOff_State,                         //generic onoff state
    OnPowerUp_Bind_Power_Level_State,                   //generic power level state
    OnPowerUp_Bind_Lightness_State,                 //Light lightness state
    OnPowerUp_Bind_CTL_Temp_State,               //CTL temperature state
    OnPowerUp_Bind_CTL_DLT_State,                  //CTL Delta UV state
    OnPowerUp_Bind_HSL_Hue_State = 5,           // HSL Hue state
    OnPowerUp_Bind_HSL_Saturation_State,      // HSL Saturation state
    OnPowerUp_Bind_xyL_X_State,                     //xyL x state
    OnPowerUp_Bind_xyL_Y_State,                     //xyL y state
    OnPowerUp_Bind_LC_mode_State,                     //LC mode state
    OnPowerUp_Bind_LC_om_State,                     //LC om state
    OnPowerUp_Bind_LC_loo_State,                     //LC loo state
    OnPowerUp_Bind_Property_Auto_LC_loo_State,             //Property Auto LC loo state
    OnPowerUp_Bind_Property_Manual_LC_loo_State,             //Property Manual LC loo state
    OnPowerUp_Bind_State_Max = 0xE,     //do not modify this enum value
}OnPowerUp_Bind_State_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/*
The bind state value which need store to flash, them will be used when power up.
*/
typedef struct __attribute((packed))
{
    int16_t off_value;
    int16_t on_value;
    int16_t restore_value;
}bind_status_store_t;
/**
 * Store the power onoff value, it should be called after changed the power onff value.
 */
void power_onoff_value_store(void);
/**
 * Store the bind state value, it should be called after changed the bind state (last/default) value.
 *
 * @param[in]     bind_instance_index     Bind state instance. Range in [0x00~0x0E]
 * @param[in]     state_enum              Bind state sequence number of an element. Range in [0x00~0x0E]
 * @param[in]     off_value               Bind state will be set to this value when power onoff equal to 0.
 * @param[in]     on_value                Bind state will be set to this value when power onoff equal to 1.
 * @param[in]     restore_value           Bind state will be set to this value when power onoff equal to 2.
 *
 * @retval ::NVDS_SUCCESS                            Operation is Success.
 * @retval ::NVDS_LENGTH_OUT_OF_RANGE      Store the bind state to flash faild, the bind_instance_index more than store support.
 * @retval ::NVDS_INVALID_PARA                    NVDS invalid params.
 */
uint8_t store_status_before_power_down(uint16_t bind_instance_index, OnPowerUp_Bind_State_t state_enum, uint16_t off_value, uint16_t on_value, uint16_t restore_value);
/**
 * Set the bind state value by power onoff value.it should be called when power up.
 *
 * @param[in]     bind_instance_index         Bind state instance. Range in [0x00~0x0E]
 * @param[in]     state_enum                  Bind state sequence number of an element. Range in [0x00~0x0E]
 * @param[in]     power_onoff_instance_index  which power off instance value will be using to do power up behavior.
 * @param[out]    bind_state                  The Bind state will be seted valued.
 */
void power_up_sequence_behavior(uint8_t bind_instance_index, uint8_t power_onoff_instance_index, OnPowerUp_Bind_State_t state_enum, uint16_t* bind_state);

/**
 * Clear nvds tag about on power up model .
 */
void clear_power_up_bind_state(void);
#endif /* __MESH_PONOFF_BEHAVIOR_H__ */
/** @} */
 
