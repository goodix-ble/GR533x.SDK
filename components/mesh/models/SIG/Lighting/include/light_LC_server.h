/**
 *****************************************************************************************
 *
 * @file light_lc_server.h
 *
 * @brief Light LC Server API.
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
#ifndef __LIGHT_LC_SERVER_H__
#define __LIGHT_LC_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "model_common.h"
#include "light_LC_common.h"
/*
 * DEFINES
 ****************************************************************************************
 */
#define TIME_OCCUPANCY_DELAY_PROPERTY  0x003A
typedef uint32_t Motion_Sense_U24_Format;    /*< Millisecond 24 */

#define MOTION_SENSED_PROPERTY  0x0042
typedef uint8_t Motion_Sense_U8_Format;    /*< Percentage 8 */

#define PEOPLE_COUNT_PROPERTY  0x004C
typedef uint16_t People_Count_U16_Format;    /*< Uint16 */

#define PRESENCE_DETECTED_PROPERTY  0x004D
typedef uint8_t Presence_detected_U8_Format;    /*< BOOLEAN */

#define PRESENCE_AMB_LUXLVL_PROPERTY  0x004E
typedef uint32_t Presence_Amb_LuxLVL_U24_Format;    /*< Uint24 */

#define TIME_SINCE_MOTION_SENSED_PROPERTY  0x0068
typedef uint16_t Time_Since_Motion_Sense_U16_Format;    /*< seconds 16 */

#define LC_OCCUPANCY_BIT    (0x01<<0)
#define LC_AMB_LUXLVL_BIT    (0x01<<1)

#define LC_NO_OCCUPANCY_REPORT 0x00
#define LC_HAS_OCCUPANCY_REPORT 0x01
/*
 * ENUMERATIONS
 ****************************************************************************************
 */
//#define MESH_MODEL_BQB_TEST
/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
/* Forward declaration */
typedef struct __light_lc_server_t  light_lc_server_t;

/* Forward declaration */
typedef struct __light_lc_setup_server_t  light_lc_setup_server_t;

/**
 * Callback type for Light LC Mode Set/Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the light LC server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[out]   p_out                    Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*light_lc_mode_state_set_cb_t)(light_lc_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_mode_set_params_t * p_in,
                                                    light_lc_mode_status_params_t * p_out);

/**
 * Callback type for Light LC Get message.
 *
 * @param[in]     p_self                   Pointer to the light LC server model structure.
 * @param[in]     p_rx_msg              Pointer to the the received message info.
 * @param[out]   p_out                   Pointer to store the output parameters from the user application.
 */
typedef void (*light_lc_mode_state_get_cb_t)(light_lc_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    light_lc_mode_status_params_t * p_out);

/**
 * Callback type for Light LC OM Set/Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the light LC server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[out]   p_out                    Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*light_lc_om_state_set_cb_t)(light_lc_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_om_set_params_t * p_in,
                                                    light_lc_om_status_params_t * p_out);


/**
 * Callback type for Light LC OM Get message.
 *
 * @param[in]     p_self                   Pointer to the light LC server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 */
typedef void (*light_lc_om_state_get_cb_t)(light_lc_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    light_lc_om_status_params_t * p_out);

/**
 * Callback type for Light LC Light OnOff Set/Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the light LC server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[in]     p_in_transition          Pointer to optional transition parameters, if present in the incoming message.
 *                                         Otherwise, set to NULL.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*light_lc_loo_state_set_cb_t)(light_lc_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_loo_set_params_t * p_in,
                                                    const model_transition_t * p_in_transition,
                                                    light_lc_loo_status_params_t * p_out);

/**
 * Callback type for Light LC Light OnOff Get message.
 *
 * @param[in]     p_self                   Pointer to the light LC server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 */
typedef void (*light_lc_loo_state_get_cb_t)(light_lc_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    light_lc_loo_status_params_t * p_out);

/**
 * Callback type for Light LC Sensor Report message.
 *
 * @param[in]     p_self                   Pointer to the light LC server model structure.
 * @param[in]     p_rx_msg             Pointer to the the received message info.
 * @param[in]     lc_senser_mask     Sensor status bit flag.
 * @param[in]     lc_occupancy         The Light LC Occupancy state.
 * @param[in]     lc_amb_luxlvl         The Light LC Ambient LuxLevel state.
 */
typedef void (*light_lc_sensor_state_cb_t)(light_lc_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    uint8_t lc_senser_mask,
                                                    uint8_t lc_occupancy,
                                                    uint32_t lc_amb_luxlvl);

/**
 * Callback type for Light LC property Get Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the light LC server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*light_lc_property_get_cb_t)(light_lc_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_property_get_params_t * p_in,
                                                    light_lc_property_status_params_t * p_out);

/**
 * Callback type for Light LC property Set/Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the light LC server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*light_lc_property_set_cb_t)(light_lc_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_lc_property_set_params_t * p_in,
                                                    light_lc_property_status_params_t * p_out);

/**
 * Light LC Server callback list.
 */
typedef struct
{
    light_lc_mode_state_set_cb_t light_lc_mode_set_cbs;               /**< Callback for Light LC Mode Set/Set Unacknowledged message. */
    light_lc_mode_state_get_cb_t light_lc_mode_get_cbs;              /**< Callback for Light LC Mode Get message. */
    light_lc_om_state_set_cb_t light_lc_om_set_cbs;                      /**< Callback for Light LC Occupancy Mode Set/Set Unacknowledged message. */
    light_lc_om_state_get_cb_t light_lc_om_get_cbs;                     /**< Callback for Light LC Occupancy Mode Get message. */
    light_lc_loo_state_set_cb_t light_lc_loo_set_cbs;                      /**< Callback for Light LC Light OnOff Set/Set Unacknowledged message. */
    light_lc_loo_state_get_cb_t light_lc_loo_get_cbs;                     /**< Callback for Light LC Light OnOff Get message. */
    light_lc_sensor_state_cb_t light_lc_sensor_state_cbs;             /**< Callback for Light LC Sensor status message. */
} light_lc_server_callbacks_t;

typedef struct
{
    light_lc_property_get_cb_t light_lc_property_get_cbs;               /**< Callback for Light LC Property Get message. */
    light_lc_property_set_cb_t light_lc_property_set_cbs;                /**< Callback for Light LC Property Set/Set Unacknowledged message. */
} light_lc_setup_server_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    const light_lc_server_callbacks_t *p_callbacks;    /**< User provided callback for this model. */
} light_lc_server_settings_t;

typedef struct
{
    const light_lc_setup_server_callbacks_t *p_callbacks;    /**< User provided callback for this model. */
} light_lc_setup_server_settings_t;

/**
 * Light LC Server model information.
 */
struct __light_lc_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    tid_tracker_t tid_tracker;                  /**< Tid tracker. */
    light_lc_server_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */

    uint8_t * p_dtt_ms;        /**< point to the default transition time*/
};

/**
 * Light LC Setup Server model information.
 */
struct __light_lc_setup_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    light_lc_setup_server_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */

    light_lc_server_t *lc_server;
};

/**
 * Initializes Light LC Server model.
 *
 * @param[in]     p_server                 Light LC server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t light_lc_server_init(light_lc_server_t *p_server, uint8_t element_offset);

/**
 * Light LC Server publishes unsolicited mode Status message.
 *
 * @param[in]     p_server                 Light LC server information pointer.
 * @param[in]     p_params                Mode Status Message parameters.
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
uint16_t light_lc_server_mode_status_publish(light_lc_server_t * p_server, 
                                                            const light_lc_mode_status_params_t * p_params);

/**
 * Light LC Server publishes unsolicited occupancy mode Status message.
 *
 * @param[in]     p_server                 Light LC server information pointer.
 * @param[in]     p_params                Occupancy Mode Status Message parameters.
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
uint16_t light_lc_server_occ_mode_status_publish(light_lc_server_t * p_server, 
                                                            const light_lc_om_status_params_t * p_params);

/**
 * Light LC Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Light LC server information pointer.
 * @param[in]     p_params                Light Onoff Status Message parameters.
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
 uint16_t light_lc_server_loo_status_publish(light_lc_server_t * p_server, 
                                                            const light_lc_loo_status_params_t * p_params);
/*This function just for test receive a sensor message.*/                                                            
void test_receive_sensor_msg(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
#endif /* __LIGHT_LC_SERVER_H__ */

/** @} */

