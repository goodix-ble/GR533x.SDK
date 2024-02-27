/**
 *****************************************************************************************
 *
 * @file app_light_lc_server.h
 *
 * @brief App Light LC API.
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
#ifndef __APP_LIGHT_LC_SERVER_H__
#define __APP_LIGHT_LC_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "light_lc_setup_server.h"


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */
//#define MESH_MODEL_BQB_TEST

#define LIGHT_LC_INSTANCE_COUNT (2)    // should no more than LIGHT_LIGHTNESS_SERVER_INSTANCE_COUNT_MAX

#define LIGHT_LC_MODE_STATE_ON  (0x01)
#define LIGHT_LC_MODE_STATE_OFF  (0x00)
#define LIGHT_LC_OCC_MODE_STATE_OCC  (0x01)
#define LIGHT_LC_OCC_MODE_STATE_NO_OCC  (0x00)
#define LIGHT_LC_OCC_REPORT_BEEN_OCC  (0x01)
#define LIGHT_LC_OCC_REPORT_NO_OCC  (0x00)
#define LIGHT_LC_LOO_MODE_STATE_ON  (0x01)
#define LIGHT_LC_LOO_MODE_STATE_OFF  (0x00)

/* Light LC State Machine states */
typedef enum 
{
    LIGHT_LC_STATE_MECHINE_STATES_OFF,
    LIGHT_LC_STATE_MECHINE_STATES_STANDBY,
    LIGHT_LC_STATE_MECHINE_STATES_FADE_ON,
    LIGHT_LC_STATE_MECHINE_STATES_RUN,
    LIGHT_LC_STATE_MECHINE_STATES_FADE,
    LIGHT_LC_STATE_MECHINE_STATES_PROLONG,
    LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_AUTO,
    LIGHT_LC_STATE_MECHINE_STATES_FADE_STANDBY_MANUAL,
    LIGHT_LC_STATE_MECHINE_STATES_MAX
}Light_lc_state_mechine_states_t;

/* Light LC State Machine events */
typedef enum 
{
    LIGHT_LC_STATE_MECHINE_EVENTS_MODE_ON,
    LIGHT_LC_STATE_MECHINE_EVENTS_MODE_OFF,
    LIGHT_LC_STATE_MECHINE_EVENTS_OCC_ON,
    LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_ON,
    LIGHT_LC_STATE_MECHINE_EVENTS_LIGHT_OFF,
    LIGHT_LC_STATE_MECHINE_EVENTS_TIMER_OFF,
    LIGHT_LC_STATE_MECHINE_EVENTS_MAX
}Light_lc_state_mechine_events_t;

/* Light LC State Machine conditions */
typedef enum 
{
    LIGHT_LC_STATE_MECHINE_CONDITIONS_ANY,
    LIGHT_LC_STATE_MECHINE_CONDITIONS_AUTO_OCC,
    LIGHT_LC_STATE_MECHINE_CONDITIONS_NO_AUTO_OCC,
    LIGHT_LC_STATE_MECHINE_CONDITIONS_OCC_ON,
    LIGHT_LC_STATE_MECHINE_CONDITIONS_OCC_OFF,
    LIGHT_LC_STATE_MECHINE_CONDITIONS_MAX
}Light_lc_state_mechine_conditions_t;

/* Light LC State Machine actions */
#define LIGHT_LC_STATE_MECHINE_ACTIONS_NO_ACTION (0x00)
#define LIGHT_LC_STATE_MECHINE_ACTIONS_SET_ON (0x01 << 0)
#define LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OFF (0x01 << 1)
#define LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OCC_ON (0x01 << 2)
#define LIGHT_LC_STATE_MECHINE_ACTIONS_SET_OCC_OFF (0x01 << 3)
#define LIGHT_LC_STATE_MECHINE_ACTIONS_SET_TIMER (0x01 << 4)

/* Tn values for Set Timer */
typedef enum 
{
    LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_ANY,
    LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T1,
    LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T2,
    LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T3,
    LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T4,
    LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T5,
    LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_T6,
    LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_TRANSITION,
    LIGHT_LC_STATE_MECHINE_ACTIONS_TIME_MAX
}Light_lc_state_mechine_actions_timer_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
typedef struct
{
    uint8_t lc_onoff;                    /**< represents occupancy reported by an occupancy sensor. */
    uint16_t lc_linear;                       /*< represents the Ambient LuxLevel level*/
}app_user_light_lc_state_t;

/** Internal structure to hold state and timing information. */
typedef struct
{
    uint16_t lightness_output;
    uint32_t luxlvl_output;                       /*< represents the Ambient LuxLevel level*/
    uint32_t regulator_output;                       /*< represents the Ambient LuxLevel level*/
}app_light_lc_output_state_t;

typedef struct
{
    bool present_loo;             /**< Present value of the OnOff state. */
    bool target_loo;              /**< Target value of the OnOff state, as received from the model interface. */
    uint32_t remaining_time_ms;      /**< Remaining time to reach `target lightness`. */
    uint32_t delay_ms;                       /**< Time to delay the processing of received SET message. */
} app_light_lc_loo_state_t;

typedef struct
{
    uint8_t mode;                                       /**< The value of the Light LC Mode state*/
} app_light_lc_mode_state_t;

typedef struct
{
    uint8_t mode;                                       /**< The value of the Light LC Occupancy Mode state*/
} app_light_lc_om_state_t;

typedef struct
{
    uint8_t value;                                      /**< Light LC Occupancy states*/
} app_light_lc_occ_value_t;

typedef struct
{
    Presence_Amb_LuxLVL_U24_Format value;   /**<Light LC Ambient LuxLevel states*/
} app_light_lc_Amb_LuxLVL_state_t;

typedef struct
{
    uint16_t value;
} app_light_lc_linear_value_t;

typedef struct
{
    Light_Control_Ambient_LuxLvl_on_U24_Format LuxLvl_on;    /*< Millisecond 24 */
    Light_Control_Ambient_LuxLvl_Prolong_U24_Format LuxLvl_prolong;    /*< Millisecond 24 */
    Light_Control_Ambient_LuxLvl_Standby_U24_Format LuxLvl_standby;    /*< Millisecond 24 */
    Light_Control_Lightness_on_U16_Format Lightness_on;    /*< uint16 */
    Light_Control_Lightness_Prolong_U16_Format Lightness_prolong;    /*< uint16 */
    Light_Control_Lightness_Standby_U16_Format Lightness_standby;    /*< uint16 */
    Light_Control_Regulator_Accuracy_U8_Format Regulator_Accuracy;    /*< Percentage 8 */
    Light_Control_Regulator_KID_F32_Format Regulator_kid;    /*< Float 32 */
    Light_Control_Regulator_KIU_F32_Format Regulator_kiu;     /*< Float 32 */
    Light_Control_Regulator_KPD_F32_Format Regulator_kpd;     /*< Float 32 */
    Light_Control_Regulator_KPU_F32_Format Regulator_kpu;     /*< Float 32 */
    Light_Control_Time_Fade_U24_Format Time_fade;    /*< Millisecond 24 */
    Light_Control_Time_Fade_ON_U24_Format Time_fade_on;    /*< Millisecond 24 */
    Light_Control_Time_Fade_Standby_Auto_U24_Format Time_fade_standby_auto;    /*< Millisecond 24 */
    Light_Control_Time_Fade_Standby_Manual_U24_Format Time_fade_standby_manual;    /*< Millisecond 24 */
    Light_Control_Time_Occupancy_Delay_U24_Format Time_occupancy_delay;    /*< Millisecond 24 */
    Light_Control_Time_Prolong_U24_Format Time_prolong;    /*< Millisecond 24 */
    Light_Control_Time_Run_on_U24_Format Time_run_on;    /*< Millisecond 24 */

    #define Light_lc_set_timer_t1 Time_fade_on
    #define Light_lc_set_timer_t2 Time_run_on
    #define Light_lc_set_timer_t3 Time_fade
    #define Light_lc_set_timer_t4 Time_prolong
    #define Light_lc_set_timer_t5 Time_fade_standby_auto
    #define Light_lc_set_timer_t6 Time_fade_standby_manual
} app_light_lc_property_state_t;

typedef struct
{
    app_light_lc_loo_state_t lc_loo;
    app_light_lc_mode_state_t lc_mode;
    app_light_lc_om_state_t lc_om;
    app_light_lc_occ_value_t lc_occ_value;
    app_light_lc_Amb_LuxLVL_state_t lc_LuxLVL;
    app_light_lc_linear_value_t lc_linear;
    app_light_lc_property_state_t lc_property;
    app_light_lc_output_state_t output_state;

    Light_lc_state_mechine_states_t machine_state;
    Light_lc_state_mechine_states_t next_machine_state;

    mesh_timer_t machine_timer;                /**< actual state timer instance. */
}app_light_lc_state_t;

typedef struct
{
    Light_lc_state_mechine_states_t current_state;
    Light_lc_state_mechine_events_t events;
    Light_lc_state_mechine_conditions_t conditon;
    uint8_t action;
    Light_lc_state_mechine_actions_timer_t Transition_time;
    Light_lc_state_mechine_states_t next_state;
}app_light_lc_machine_transtion_action_t;

/**
 * Application callback type for Light LC Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     onoff                              light onoff state to be used by the application.
 * @param[in]     linear_value                    light linear to be used by the application.
 *
 */
typedef void (*app_light_lc_set_cb_t)(uint8_t model_instance_index, bool * onoff, uint16_t * linear_value);

/**
 * Application callback type for Light LC Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     onoff                              light onoff state to be used by the application.
 * @param[in]     linear_value                    light linear to be used by the application.
 *
 */
typedef void (*app_light_lc_get_cb_t)(uint8_t model_instance_index, bool * onoff, uint16_t * linear_value);

/**
 * Application Light LC Server model information.
 */
 typedef struct
 {
    light_lc_server_t server;                           /**< Light LC Server model information. */
    app_light_lc_set_cb_t light_lc_set_cb;      /**< Callback to be called for informing the user application to update the value*/
    app_light_lc_get_cb_t light_lc_get_cb;      /**< Callback to be called for requesting current value from the user application */

    app_light_lc_state_t state;                         /**< Internal variableto to hold state and timing information */
    mesh_timer_t loo_state_timer;                /**< actual state timer instance. */

    uint32_t loo_last_time_clock_ms;                /**< Internal variable. It is used for acquiring last time value. */
    uint16_t loo_last_time_nb_wrap;                 /**< Internal variable. It is used for acquiring last time value. */

    uint16_t client_address;                        /**< The address message received. */

    bool value_updated;                             /**< Internal variable. To flag if the received message has been processed to update the lightness value */
 } app_light_lc_server_t;

/**
 * Initializes Application Light LC Server model.
 *
 * @param[in]     p_server                 Application Light LC server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     set_cb                   Application Light LC server setting callback.
 * @param[in]     get_cb                   Application Light LC server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_light_lc_server_init(app_light_lc_server_t *p_server, uint8_t element_offset, app_light_lc_set_cb_t set_cb, app_light_lc_get_cb_t get_cb);

/**
 * Application Light LC Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Light LC server information pointer.
 *
 * @retval ::MESH_ERROR_NO_ERROR                  Operation is Success.
 * @retval ::MESH_ERROR_INVALID_PARAM             Invalid Parameter.
 * @retval ::MESH_ERROR_INSUFFICIENT_RESOURCES    Insufficient Resources.
 * @retval ::MESH_ERROR_INVALID_MODEL             Invalid Model.
 * @retval ::MESH_ERROR_INVALID_PUBLISH_PARAMS    Invalid Publish Parameters.
 * @retval ::MESH_ERROR_INVALID_BINDING           Invalid Binding.
 * @retval ::MESH_ERROR_INVALID_APPKEY_ID         Invalid AppKey Index.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED        Command Disallowed.
 * @retval ::MESH_ERROR_NOT_FOUND                 Resource requested not found.
 * @retval ::MESH_ERROR_SDK_RELIABLE_TRANS_ON     Reliable message transfer procedure is on.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM         Invalid Parameter.
 */

uint16_t app_light_lc_mode_status_publish(app_light_lc_server_t * p_server);
uint16_t app_light_lc_om_status_publish(app_light_lc_server_t * p_server);
uint16_t app_light_lc_loo_status_publish(app_light_lc_server_t * p_server);

/**
 * Application Light LC Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Light LC server information pointer.
 * @param[in]     lc_mode                  Application Light LC server state information pointer.
 * @param[in]     event                      Light LC State Machine state.
 *
 */
void light_lc_state_machine(app_light_lc_server_t * p_server, app_light_lc_state_t *lc_mode, Light_lc_state_mechine_events_t event);
#endif /* __APP_LIGHT_LC_SERVER_H__ */

/** @} */

