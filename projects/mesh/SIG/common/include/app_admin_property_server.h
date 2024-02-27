/**
 ****************************************************************************************
 *
 * @file app_admin_property_server.h
 *
 * @brief App Admin Property Server API.
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
#ifndef __APP_ADMIN_PROPERTY_SERVER_H__
#define __APP_ADMIN_PROPERTY_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "generic_admin_property_server.h"


#define GENERIC_ADMIN_PROPERTY_SERVER_INSTANCE_COUNT (2)    // should no more than GENERIC_PROPERTY_SERVER_INSTANCE_COUNT_MAX

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */


/** Internal structure to hold state and timing information. */
typedef struct
{   
    int16_t property_id;           /**< Present value of the Admin Property state */   
    uint8_t access;                /**< Target value of the Admin Property state, as received from the model interface. */    
    uint16_t value_length;
    uint8_t* property_value;
} app_admin_property_state_t;

typedef struct
{
    uint16_t id_number;
    uint16_t* property_id;
}app_admin_properties_state_t;
/** Forward declare */
typedef struct __app_admin_property_server_t app_admin_property_server_t;


/**
 * Application callback type for Generic Admin Property Set/Set Unacknowledged message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[in]     admin_property_state       Application fills this value with the value retrived from the hardware interface.
 */
typedef void (*app_generic_admin_property_set_cb_t)(const uint8_t  model_instance_index, app_admin_property_state_t* admin_property_state);

/**
 * Application callback type for Generic Admin Property Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[out]    admin_property_state       Admin Property state to be get by the application.
 */
typedef void (*app_generic_admin_property_get_cb_t)(const uint8_t  model_instance_index, app_admin_property_state_t* admin_property_state);

/**
 * Application callback type for Generic Admin Properties Get message.
 *
 * @param[in]     model_instance_index      Model instance index.
 * @param[out]    p_present_property        Admin Properties state to be get by the application.
 */
typedef void (*app_generic_admin_properties_get_cb_t)(const uint8_t  model_instance_index, app_admin_properties_state_t* admin_properties_state);

/**
 * Application Generic Admin Property Server model information.
 */
struct __app_admin_property_server_t
 {
    generic_admin_property_server_t server;    /**< Generic Admin Property Server model information. */
    app_generic_admin_property_set_cb_t admin_property_set_cb;  /**< Callback to be called for informing the admin application to update the value*/
    app_generic_admin_property_get_cb_t admin_property_get_cb;  /**< Callback to be called for requesting current value from the admin application */
    app_generic_admin_properties_get_cb_t admin_properties_get_cb;
     
    app_admin_property_state_t admin_property_state;          /**< Internal variableto to hold state and timing information */
    app_admin_properties_state_t admin_properties_state;
    bool value_updated;               /** Internal variable. To flag if the received message has been processed to update the present Admin Property value */
 };

 /**
 * Initializes Application Generic Admin Property Server model.
 *
 * @param[in]     p_server                 Application Generic Admin Property server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     set_cb                   Application Generic Admin Property server setting callback.
 * @param[in]     get_cb                   Application Generic Admin Property server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_generic_admin_property_server_init(app_admin_property_server_t *p_server, uint8_t element_offset,
                                               app_generic_admin_property_set_cb_t admin_property_set_cb, 
                                               app_generic_admin_property_get_cb_t admin_property_get_cb,
                                               app_generic_admin_properties_get_cb_t admin_properties_get_cb);
/**
 * Application Generic Admin Property Server publishes unsolicited Status message.
 *
 * @param[in]     p_server                 Application Generic Admin Property server information pointer.
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
uint16_t app_generic_admin_property_status_publish(app_admin_property_server_t * p_server);
#endif /* __APP_ADMIN_PROPERTY_SERVER_H__ */

/** @} */
