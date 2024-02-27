/**
 ****************************************************************************************
 *
 * @file app_level_server.h
 *
 * @brief App Level Server API.
 *
 *
 ****************************************************************************************
  @attention
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
#ifndef __APP_LEVEL_SERVER_H__
#define __APP_LEVEL_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "generic_level_server.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/** Transition types */
typedef enum
{    
    TRANSITION_SET,                  /**< indicating SET message */   
    TRANSITION_DELTA_SET,            /**< indicating DELTA SET message */   
    TRANSITION_MOVE_SET,             /**< indicating MOVE SET message */    
    TRANSITION_NONE                  /**< indicating no transition */
} app_level_transition_type_t;


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
/*The HSL model need at least three level model*/
#define GENERIC_LEVEL_SERVER_INSTANCE_COUNT (3)    // should no more than GENERIC_LEVEL_SERVER_INSTANCE_COUNT_MAX

#define MODEL_TRANSITION_TIME_INVALID               (0xFFFFFFFF)

/** Internal structure for holding Set transition related variables */
typedef struct
{   
    int32_t required_delta;           /**< For storing actual required amount of level change. */    
    int16_t initial_present_level;    /**< Initial present level required for handling Set/Delta Set message. */
} set_transition_t;


/** Internal structure for holding Move transition related variables */
typedef struct
{    
    int16_t required_move;            /**< Scaled representation of the Level value. */   
    int16_t initial_present_level;    /**< Initial present level required for handling Set/Delta Set message. */
    int32_t resolution_time;          /**< The resolution_time of transition number steps*/
    int8_t number_steps;              /**< The number steps of transition time*/
    int16_t step_length;              /**< the length of each step*/
    int16_t remain_length;            /**< the remain_length = required_move % number_steps*/
} move_transition_t;


/** Internal structure to hold state and timing information. */
typedef struct
{   
    int16_t present_level;            /**< Present value of the Level state */   
    int16_t target_level;             /**< Target value of the Level state, as received from the model interface. */    
    uint32_t transition_time_ms;      /**< transition time to reach `target_level`. */   
    uint32_t delay_ms;                /**< Time to delay the processing of received SET message. */

    app_level_transition_type_t transition_type;   /** Transition Type */
    union {        
        set_transition_t set;                       /* Parameters for Set Transition */       
        move_transition_t move;                     /* Parameters for Move Transition */
    } params;
} app_level_state_t;

/** Forward declare */
typedef struct __app_level_server_t app_level_server_t;


/**
 * Application callback type for Generic Level (Delta, Move)Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     present_level             Level state to be used by the application.
 */
typedef void (*app_generic_level_set_cb_t)(const uint8_t  model_instance_index, int16_t present_level);

/**
 * Application callback type for Generic Level Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[out]    p_present_level           Application fills this value with the value retrived from the hardware interface.
 */
typedef void (*app_generic_level_get_cb_t)(const uint8_t  model_instance_index, int16_t * p_present_level);

/**
 * Application Generic Level Server model information.
 */
struct __app_level_server_t
 {
    generic_level_server_t server;    /**< Generic Level Server model information. */
    mesh_timer_t app_timer;           /**< APP timer instance. */
    app_generic_level_set_cb_t level_set_cb;  /**< Callback to be called for informing the user application to update the value*/
    app_generic_level_get_cb_t level_get_cb;  /**< Callback to be called for requesting current value from the user application */
    
    app_level_state_t state;          /**< Internal variableto to hold state and timing information */
    
    const uint32_t * p_dtt_ms;        /**< point to the default transition time*/
    
    uint32_t last_time_clock_ms;      /**< Internal variable. It is used for acquiring last time value. */
    uint16_t last_time_nb_wrap;       /**< Internal variable. It is used for acquiring last time value. */
    uint16_t client_address;          /**< The address message received. */
        
    bool value_updated;               /** Internal variable. To flag if the received message has been processed to update the present Level value */
 };

 /**
 * Initializes Application Generic Level Server model.
 *
 * @param[in]     p_server                 Application Generic Level server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     set_cb                   Application Generic Level server setting callback.
 * @param[in]     get_cb                   Application Generic Level server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_generic_level_server_init(app_level_server_t *p_server, uint8_t element_index,
                                       app_generic_level_set_cb_t set_cb, app_generic_level_get_cb_t get_cb);
 
/**
 * Application Generic Level Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Generic Level server information pointer.
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
uint16_t app_level_status_publish(app_level_server_t * p_server);
#endif /* __APP_LEVEL_SERVER_H__ */

/** @} */
