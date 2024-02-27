/**
 *****************************************************************************************
 *
 * @file light_lc_setup_server.h
 *
 * @brief Light LC Setup Server API.
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
#ifndef __LIGHT_LC_SETUP_SERVER_H__
#define __LIGHT_LC_SETUP_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "model_common.h"
#include "light_lc_common.h"
#include "light_lc_server.h"

/*
 * DEFINES
 ****************************************************************************************
 */
#define LIGHT_LC_AMBIENT_LUXLVL_ON_PROPERTY 0x002B
typedef uint32_t Light_Control_Ambient_LuxLvl_on_U24_Format;    /*< Millisecond 24 */

#define LIGHT_LC_AMBIENT_LUXLVL_PROLONG_PROPERTY 0x002C
typedef uint32_t Light_Control_Ambient_LuxLvl_Prolong_U24_Format;    /*< Millisecond 24 */

#define LIGHT_LC_AMBIENT_LUXLVL_STANDBY_PROPERTY 0x002D
typedef uint32_t Light_Control_Ambient_LuxLvl_Standby_U24_Format;    /*< Millisecond 24 */

#define LIGHT_LC_LIGHTNESS_ON_PROPERTY 0x002E
typedef uint16_t Light_Control_Lightness_on_U16_Format;    /*< uint16 */

#define LIGHT_LC_LIGHTNESS_PROLONG_PROPERTY 0x002F
typedef uint16_t Light_Control_Lightness_Prolong_U16_Format;    /*< uint16 */

#define LIGHT_LC_LIGHTNESS_STANDBY_PROPERTY 0x0030
typedef uint16_t Light_Control_Lightness_Standby_U16_Format;    /*< uint16 */

#define LIGHT_LC_REGULATOR_ACCURACY_PROPERTY 0x0031
typedef uint8_t Light_Control_Regulator_Accuracy_U8_Format;    /*< Percentage 8 */

#define LIGHT_LC_REGULATOR_KID_PROPERTY 0x0032
typedef float Light_Control_Regulator_KID_F32_Format;    /*< Float 32 */

#define LIGHT_LC_REGULATOR_KIU_PROPERTY 0x0033
typedef float Light_Control_Regulator_KIU_F32_Format;     /*< Float 32 */

#define LIGHT_LC_REGULATOR_KPD_PROPERTY 0x0034
typedef float Light_Control_Regulator_KPD_F32_Format;     /*< Float 32 */

#define LIGHT_LC_REGULATOR_KPU_PROPERTY 0x0035
typedef float Light_Control_Regulator_KPU_F32_Format;     /*< Float 32 */

#define LIGHT_LC_FADE_PROPERTY 0x0036
typedef uint32_t Light_Control_Time_Fade_U24_Format;    /*< Millisecond 24 */

#define LIGHT_LC_FADE_ON_PROPERTY 0x0037
typedef uint32_t Light_Control_Time_Fade_ON_U24_Format;    /*< Millisecond 24 */

#define LIGHT_LC_FADE_STANDBY_AUTO_PROPERTY 0x0038
typedef uint32_t Light_Control_Time_Fade_Standby_Auto_U24_Format;    /*< Millisecond 24 */

#define LIGHT_LC_FADE_STANDBY_MANUAL_PROPERTY 0x0039
typedef uint32_t Light_Control_Time_Fade_Standby_Manual_U24_Format;    /*< Millisecond 24 */

#define LIGHT_LC_TIME_OCC_DELAY_PROPERTY 0x003A
typedef uint32_t Light_Control_Time_Occupancy_Delay_U24_Format;    /*< Millisecond 24 */

#define LIGHT_LC_TIME_PROLONG_PROPERTY 0x003B
typedef uint32_t Light_Control_Time_Prolong_U24_Format;    /*< Millisecond 24 */

#define LIGHT_LC_TIME_RUN_ON_PROPERTY 0x003C
typedef uint32_t Light_Control_Time_Run_on_U24_Format;    /*< Millisecond 24 */

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */


/**
 * Initializes Light LC Setup  Server model.
 *
 * @param[in]     p_server                 Light LC Setup server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t light_lc_setup_server_init(light_lc_setup_server_t *p_server, uint8_t element_offset);

/**
 * Light LC Server publishes unsolicited property Status message.
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
 uint16_t light_lc_setup_server_property_status_publish(light_lc_setup_server_t * p_server, 
                                                            const light_lc_property_status_params_t * p_params);
/**
 * Get the property value length of the property.
 *
 * @param[in]     property_id                 Input the property id
 *
 * @retval                                    property value length.
 */                                                            
uint16_t property_get_value_length(uint16_t property_id);

#endif /* __LIGHT_LC_SETUP_SERVER_H__ */

/** @} */

