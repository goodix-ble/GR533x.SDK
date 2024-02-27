/**
 *****************************************************************************************
 *
 * @file app_scene_client.c
 *
 * @brief APP Mesh Scene API Implementation.
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "app_scene_client.h"
#include "scene_client.h"
#include "app_log.h"
#include "user_app.h"


/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t app_mesh_scene_client_init(mesh_scene_client_t *p_client, uint8_t element_offset, const mesh_scene_client_callbacks_t *client_cb)
{
    APP_LOG_INFO("CLIENT[%d] -- Scene client: 0x%04x, element idx: %d",element_offset, p_client, element_offset);
    if(( p_client == NULL) || (TSCNS_SCENE_CLIENT_INSTANCE_COUNT <= element_offset))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_client->model_lid = MESH_INVALID_LOCAL_ID;
    p_client->settings.timeout_ms = 10000; // NOTE!!! NO LESS THAN 30000MS.
    p_client->settings.p_callbacks = client_cb;
    p_client->model_instance_index = element_offset;

    return mesh_scene_client_init(p_client, element_offset);
}
