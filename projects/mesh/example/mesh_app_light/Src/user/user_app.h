/**
 *****************************************************************************************
 *
 * @file user_app.h
 *
 * @brief Header file - User Function
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
#ifndef __USER_APP_H__
#define __USER_APP_H__

#include "gr_includes.h"

/*
 * DEFINES
 ****************************************************************************************
 */
#define SIMPLE_ONOFF_SERVER_INSTANCE_COUNT (1)    // should no more than SIMPLE_ONOFF_SERVER_INSTANCE_COUNT_MAX.
#define MESH_AUTO_PROV                     (0)    // support auto provision.
#define MESH_AUTO_PERFORMANCE_TEST         (0)    // test the package receipt rate for the light node
#define MESH_CLEAR_BOND_INFO               (0)    // clear provision information firstly after application started.

typedef enum
{
    LIGHT_NODE_ID_1,
    LIGHT_NODE_ID_2,
    LIGHT_NODE_ID_3,
    LIGHT_NODE_ID_4,
    LIGHT_NODE_ID_5,
    LIGHT_NODE_ID_6,
} light_node_id_t;

extern light_node_id_t g_light_node_id;

/*
 * GLOBAL FUNCTION DECLARATION
 *****************************************************************************************
 */

/**
 *****************************************************************************************
 * @brief Function for user ble event handler.
 *****************************************************************************************
 */
void ble_evt_handler(const ble_evt_t *p_evt);

#endif

