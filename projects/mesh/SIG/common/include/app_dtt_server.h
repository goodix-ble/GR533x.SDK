/**
 ****************************************************************************************
 *
 * @file app_default_transition_time_server.h
 *
 * @brief Header file for App Default Transition Timer Server Programming Interface
 *
 ****************************************************************************************
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
#ifndef __APP_DEFAULT_TRANSITION_TIME_SERVER_H__
#define __APP_DEFAULT_TRANSITION_TIME_SERVER_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"
#include "generic_dtt_server.h"

#define GENERIC_DTT_SERVER_INSTANCE_COUNT (2)    // should no more than GENERIC_DTT_SERVER_INSTANCE_COUNT_MAX

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
    /** Present value of the default_transition_time state */
    uint8_t present_default_transition_time;
} app_default_transition_time_state_t;

typedef void (*app_default_transition_time_set_cb_t)(uint8_t model_instance_index, uint8_t default_transition_time);

typedef void (*app_default_transition_time_get_cb_t)(uint8_t model_instance_index, uint8_t * p_present_default_transition_time);


 typedef struct
 {
    generic_default_transition_time_server_t server;
    //mesh_timer_t app_timer;
    app_default_transition_time_set_cb_t default_transition_time_set_cb;
    app_default_transition_time_get_cb_t default_transition_time_get_cb;
    
    //status
    app_default_transition_time_state_t state;
 
    uint16_t client_address;
    /** Internal variable. To flag if the received message has been processed to update the present
     * dtt value */
    bool value_updated;
 } app_default_transition_time_server_t;

uint16_t app_default_transition_time_status_publish(app_default_transition_time_server_t * p_server);

uint16_t app_generic_default_transition_time_server_init(app_default_transition_time_server_t *p_server, uint8_t element_offset, app_default_transition_time_set_cb_t set_cb, app_default_transition_time_get_cb_t get_cb);

#endif

