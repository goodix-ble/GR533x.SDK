/**
 *****************************************************************************************
 *
 * @file light_xyl_server.h
 *
 * @brief Light xyL Server API.
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
#ifndef __LIGHT_XYL_SERVER_H__
#define __LIGHT_XYL_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "model_common.h"
#include "light_xyl_common.h"
/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
/* Forward declaration */
typedef struct __light_xyl_server_t  light_xyl_server_t;

/* Forward declaration */
typedef struct __light_xyl_setup_server_t  light_xyl_setup_server_t;

/* Forward declaration */
typedef struct __light_xyl_temp_server_t  light_xyl_temp_server_t;

/**
 * Callback type for Light xyL Set/Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the light xyL server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[in]     p_in_transition          Pointer to optional transition parameters, if present in the incoming message.
 *                                         Otherwise, set to NULL.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*light_xyl_state_set_cb_t)(light_xyl_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const light_xyl_set_params_t * p_in,
                                                    const model_transition_t * p_in_transition,
                                                    void * p_out);


/**
 * Callback type for Light xyL Get message.
 *
 * @param[in]     p_self                   Pointer to the light xyL server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 */
typedef void (*light_xyl_state_get_cb_t)(light_xyl_server_t * p_self,
                                                    const mesh_model_msg_ind_t * p_rx_msg,
                                                    void * p_out);

/**
 * Callback type for Light xyL Setup Set/Set Unacknowledged message.
 *
 * @param[in]     p_self                   Pointer to the light xyL server model structure.
 * @param[in]     p_rx_msg                 Pointer to the the received message info.
 * @param[in]     p_in                     Pointer to the permanet parameters of set/set unacknowledged message.
 * @param[out]    p_out                    Pointer to store the output parameters from the user application.
 *                                         If this is a set unacknowledged message, set to NULL.
 */
typedef void (*light_xyl_state_setup_cb_t)(light_xyl_setup_server_t  * p_self,
                                                    const mesh_model_msg_ind_t *p_rx_msg,
                                                    const void * p_in,
                                                    void * p_out);

/**
 * Transaction callbacks for the Light xyL state.
 */
typedef struct
{
    light_xyl_state_set_cb_t set_cb;        /**< Callback for Light xyL Set/Set Unacknowledged message. */
    light_xyl_state_get_cb_t get_cb;        /**< Callback for Light xyL Get message. */
} light_xyl_state_cbs_t;

typedef struct
{
    light_xyl_state_get_cb_t get_cb;        /**< Callback for Light xyL Target Get message. */
} light_xyl_target_state_cbs_t;

typedef struct
{
    light_xyl_state_setup_cb_t set_cb;        /**< Callback for Light xyL Default Set/Set Unacknowledged message. */
    light_xyl_state_get_cb_t get_cb;           /**< Callback for Light xyL Default Get message. */
} light_xyl_dft_state_cbs_t;

typedef struct
{
    light_xyl_state_setup_cb_t set_cb;        /**< Callback for Light xyL Range Set/Set Unacknowledged message. */
    light_xyl_state_get_cb_t get_cb;           /**< Callback for Light xyL Range Get message. */
} light_xyl_range_state_cbs_t;

/**
 * Light xyL Server callback list.
 */
typedef struct
{
    light_xyl_state_cbs_t light_xyl_cbs;                                             /**< Callback list for Light xyL state. */
    light_xyl_target_state_cbs_t light_xyl_target_cbs;                       /**< Callback list for Light xyL Target state. */
    light_xyl_range_state_cbs_t light_xyl_range_cbs;                        /**< Callback list for Light xyL Range  state. */
    light_xyl_dft_state_cbs_t light_xyl_dft_cbs;                                 /**< Callback list for Light xyL Default state. */
} light_xyl_server_callbacks_t;

/**
 * User provided settings and callbacks for this model instance.
 */
typedef struct
{
    const light_xyl_server_callbacks_t *p_callbacks;    /**< User provided callback for this model. */
} light_xyl_server_settings_t;

/**
 * Light xyL Server model information.
 */
struct __light_xyl_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    tid_tracker_t tid_tracker;                  /**< Tid tracker. */
    light_xyl_server_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;        /**< Model instance index. */

    uint8_t * p_dtt_ms;                           /**< point to the default transition time*/
};

/**
 * Light xyL Setup Server model information.
 */
struct __light_xyl_setup_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    light_xyl_server_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;        /**< Model instance index. */
    light_xyl_server_t *xyl_server;
};

/**
 * Light xyL temperature Server model information.
 */
struct __light_xyl_temp_server_t
{
    mesh_lid_t model_lid;                       /**< Model local identifier. */
    tid_tracker_t tid_tracker;                  /**< Tid tracker. */
    light_xyl_server_settings_t settings;   /**< Settings for this model instance. */
    uint8_t model_instance_index;               /**< Model instance index. */
    light_xyl_server_t *xyl_server;
};

/**
 * Initializes Light xyL Server model.
 *
 * @param[in]     p_server                 Light xyL server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t light_xyl_server_init(light_xyl_server_t *p_server, uint8_t element_offset);

/**
 * Light xyL Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Light xyL server information pointer.
 * @param[in]     p_params                 Status Message parameters.
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
uint16_t light_xyl_server_status_publish(light_xyl_server_t * p_server, 
                                             const light_xyl_status_params_t * p_params);

#endif /* __LIGHT_XYL_SERVER_H__ */

/** @} */

