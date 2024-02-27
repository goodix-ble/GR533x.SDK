/**
 *****************************************************************************************
 *
 * @file scene_message.h
 *
 * @brief  Mesh Scene Message Define.
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
#ifndef __TSCNS_SCENE_MESSAGE_H__
#define __TSCNS_SCENE_MESSAGE_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** The allowed shortest length for the Store message. */
#define TSCNS_SCENE_STORE_MINLEN 2
/** The allowed shortest length for the scene Recall message. */
#define TSCNS_SCENE_RECALL_MINLEN 3
/** The allowed longest length for the scene Recall message. */
#define TSCNS_SCENE_RECALL_MAXLEN 5
/** The allowed shortest length for the scene Delete message. */
#define TSCNS_SCENE_DELETE_MINLEN 2


/** The allowed shortest length for the Status message. */
#define TSCNS_SCENE_STATUS_MINLEN 3
/** The allowed longest length for the Status message. */
#define TSCNS_SCENE_STATUS_MAXLEN 6
/** The allowed shortest length for the scene Register Status message. */
#define TSCNS_SCENE_REGISTER_STATUS_MINLEN 3


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/**   mesh scene model message opcodes. */
typedef enum
{
    TSCNS_SCENE_OPCODE_GET = 0x8241,                                            /** Message opcode for the scene state Get message. */
    TSCNS_SCENE_OPCODE_RECALL = 0x8242,                                       /** Message opcode for the scene state Recall message. */
    TSCNS_SCENE_OPCODE_RECALL_UNACKNOWLEDGED = 0x8243,      /** Message opcode for the scene state  Recall unacknowledge message. */
    TSCNS_SCENE_OPCODE_STATUS = 0x5e,                                         /** Message opcode for the scene Status message. */
    TSCNS_SCENE_REGISTER_OPCODE_GET = 0x8244,                          /** Message opcode for the scene state register Get message. */
    TSCNS_SCENE_REGISTER_OPCODE_STATUS = 0x8245,                    /** Message opcode for the scene register Status message. */
    TSCNS_SCENE_OPCODE_STORE = 0x8246,                                        /** Message opcode for the scene state Store message. */
    TSCNS_SCENE_OPCODE_STORE_UNACKNOWLEDGED = 0x8247,       /** Message opcode for the scene state  Store unacknowledge message. */
    TSCNS_SCENE_OPCODE_DELETE = 0x829e,                                      /** Message opcode for the scene state Delete message. */
    TSCNS_SCENE_OPCODE_DELETE_UNACKNOWLEDGED = 0x829f,     /** Message opcode for the scene state  Delete  unacknowledge message. */
} mesh_scene_opcode_t;

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Packed message structure typedefs are used for packing and unpacking byte stream. */

/** Message format for the Mesh Scene Set message. */
typedef struct __attribute((packed))
{
    uint16_t scene_number;                          /**< The number of the scene to be stored  . */
} mesh_scene_store_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t scene_number;                          /**< The number of the scene to be recalled. */
    uint8_t tid;                                               /**< Transaction number for application */
    uint8_t transition_time;                          /**< Encoded transition time value */
    uint8_t delay;                                          /**< Encoded message execution delay in 5 millisecond steps */
}mesh_scene_recall_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint16_t scene_number;                         /**< The number of the scene to be deleted  . */
} mesh_scene_delete_msg_pkt_t;

/** Parameters for the scene Status message. */
typedef struct __attribute((packed))
{
    uint8_t status_code;                                 /**<The Status Code field identifies the status code for the last operation */
    uint16_t current_scene;                           /**< Scene Number of a current scene. */
    uint16_t target_scene;                             /**< Scene Number of a target scene.  */
    uint8_t remaining_time;                          /**< Encoded remaining time */
} mesh_scene_status_msg_pkt_t;

typedef struct __attribute((packed))
{
    uint8_t status_code;                               /**<The Status Code field identifies the status code for the previous operation.*/
    uint16_t current_scene;                          /**< Scene Number of a current scene.*/
    uint16_t scene[];                                     /**< A list of scenes stored within an element. */
}mesh_scene_register_status_msg_pkt_t;

#endif /* __TSCNS_SCENE_MESSAGE_H__ */

/** @} */

