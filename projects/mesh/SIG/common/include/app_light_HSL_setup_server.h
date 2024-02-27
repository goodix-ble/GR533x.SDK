/**
 *****************************************************************************************
 *
 * @file app_light_HSL_setup.h
 *
 * @brief App Light HSL Setup Server API.
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
#ifndef __APP_LIGHT_HSL_SETUP_SERVER_H__
#define __APP_LIGHT_HSL_SETUP_SERVER_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "app_light_HSL_server.h"
#include "light_HSL_server.h"


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * DEFINES
 ****************************************************************************************
 */

//#define LIGHT_HSL_SETUP_INSTANCE_COUNT (LIGHT_HSL_INSTANCE_COUNT)    // shall equal to LIGHT_HSL_INSTANCE_COUNT

#define STATUS_CODES_SUCCESS 0x00   //Success
#define STATUS_CODES_ERR_MIN 0x01   //Cannot Set Range Min
#define STATUS_CODES_ERR_MAX 0x02   //Cannot Set Range Max

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/**
 * Application Light HSL Setup Server model information.
 */
 typedef struct
 {
    light_HSL_setup_server_t server;                           /**< Light HSL Setup Server model information. */
    app_light_HSL_set_cb_t light_HSL_setup_set_cb;     /**< Callback to be called for informing the user application to update the value*/

    app_light_HSL_state_t *state;             /**< point to server state */

    uint16_t client_address;                        /**< The address message received. */

 } app_light_HSL_setup_server_t;

/**
 * Initializes Application Light HSL Setup Server model.
 *
 * @param[in]     p_server                 Application Light HSL Setup server information pointer.
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     set_cb                   Application Light HSL Setup server setting callback.
 * @param[in]     get_cb                   Application Light HSL Setup server get callback.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_COMMAND_DISALLOWED      Command Disallowed.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_light_HSL_setup_server_init(app_light_HSL_setup_server_t *p_server, uint8_t element_offset, app_light_HSL_set_cb_t set_cb);

#endif /* __APP_LIGHT_HSL_SETUP_SERVER_H__ */

/** @} */

