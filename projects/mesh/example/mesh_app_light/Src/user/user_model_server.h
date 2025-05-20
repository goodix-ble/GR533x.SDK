/**
 *****************************************************************************************
 *
 * @file user_model_server.h
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
#ifndef __USER_MODEL_SERVER_H__
#define __USER_MODEL_SERVER_H__

#include <stdint.h>
#include "mesh_common.h"

extern mesh_lid_t g_app_model_server_local_id;

/*
 * DEFINES
 ****************************************************************************************
 */

/** APP model Client ID */
#define APP_MODEL_SERVER_ID (0x1000)

/** Company ID */
#define APP_MODEL_COMPANY_ID (0x04F7)

typedef enum
{
    APP_MODEL_OPCODE_SERVER_SEND_DATA = 0xC1,  /** Message opcode for the server send data to client. */
    APP_MODEL_OPCODE_CLIENT_SEND_DATA = 0xC2,  /** Message opcode for the client send data to server. */
} app_model_opcode_t;

typedef enum
{
    APP_CMD_CLOSE_LIGHT,
    APP_CMD_OPEN_LIGHT,
    APP_CMD_START_AUTO_SEND_MSG,
    APP_CMD_STOP_AUTO_SEND_MSG,
    APP_CMD_SET_NET_TX_COUNT,
    APP_CMD_SET_AUTO_SEND_MSG_LEN,
    APP_CMD_MAX,
} app_model_cmd_id_t;

/*
 * GLOBAL FUNCTION DECLARATION
 *****************************************************************************************
 */

/**
 *****************************************************************************************
 * @brief Function for app model server init.
 *****************************************************************************************
 */
uint16_t app_model_server_init(void);

#endif
