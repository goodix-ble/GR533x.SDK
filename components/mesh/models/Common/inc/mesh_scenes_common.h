/**
 *****************************************************************************************
 *
 * @file app_scene_server.h
 *
 * @brief App Scene API.
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
#ifndef __MESH_SCENES_COMMON_H__
#define __MESH_SCENES_COMMON_H__

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

#define MESH_SCENE_STATUS_CODE_SUCCESS       0x0000
#define MESH_SCENE_STATUS_CODE_REG_FULL     0x0100
#define MESH_SCENE_STATUS_CODE_NOT_FOUND  0x0200
#define MESH_SCENE_STATUS_CODE_OTHER           0x0300

#define MESH_SCENE_STATUS_CODE_DECODE(x)    (((x)&0xFF00) >> 8)

typedef enum
{
    //Success code
    MODEL_SCENES_SUCCESS = MESH_SCENE_STATUS_CODE_SUCCESS,
    MODEL_SCENES_SUCCESS_REPEAT_REGISTER,

    //Scene Register Full Err code
    MODEL_SCENES_ERR_LIST_OVERFULL = MESH_SCENE_STATUS_CODE_REG_FULL,
    MODEL_SCENES_ERR_UNSPECIFIED,

    //Scene Not Found Err code
    MODEL_SCENES_ERR_NOT_FOUND = MESH_SCENE_STATUS_CODE_NOT_FOUND,
    MODEL_SCENES_ERR_EMPTY_LIST,

    //other Err code
    MODEL_SCENES_ERR_SCENNE_CHECK_FAILUER = MESH_SCENE_STATUS_CODE_OTHER,

    MODEL_SCENES_STATE_ENUM_MAX,
}model_scenes_state_t;

/*
 * DEFINES
 ****************************************************************************************
 */
#define MESH_SCENES_SCENE_ELEMENT_CNT_MAX 4
#define MESH_SCENES_SCENE_STORE_LIST_CNT_MAX 8

#define MESH_SCENES_SCENE_STORE_STATE_CNT_MAX 16

#define MESH_SCENES_SCENE_VALUE_PROHIBITED 0x0000

#define MESH_SCENES_SCENE_ELEMENT_INVALID 0xFF

#define MESH_SCENES_SCENE_REGISTER_MAGIC_VALUE 0xCD10
#define MESH_SCENES_SCENE_STORE_MAGIC_VALUE 0xCD11
#define MESH_SCENES_SCENE_MAGIC_VALUE_NONE 0xFFFF

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
typedef void (*mesh_scenes_notice_model_cb)(void *p_server, uint8_t *recall_state, uint16_t state_length);

typedef struct __attribute((packed))
{
    mesh_scenes_notice_model_cb cb;
    void *p_server;
    uint16_t state_length;
    uint8_t *state_ptr;
}mesh_scenes_register_node_t;

typedef struct
{
    uint8_t element_offset;
    uint16_t scene_state_length;        //mesh_scenes_store_list_t.scene_state_values[] total length
    struct gx_list *scene_list;
    bool scene_registerd;
    uint16_t scene_registerd_magic;
}mesh_scenes_register_list_t;

typedef struct __attribute((packed))
{
    mesh_scenes_notice_model_cb cb;
    void *p_server;
    uint16_t state_length;
    uint8_t *state_ptr;
    uint8_t scene_state_value[];
}mesh_scenes_store_list_node_t;

typedef struct 
{
    uint8_t element_offset;
    uint16_t scene_number;
    uint16_t scene_state_length;
    bool scene_stored;
    uint16_t scene_stored_magic;
    uint8_t *scene_state_values;
}mesh_scenes_store_list_t;

/**
 * Verify current scene state value.
 *
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     scene_number           Be verified scene state number.
 *
 * @retval ::MODEL_SCENES_SUCCESS                                   Operation is Success.
 * @retval ::MODEL_SCENES_SUCCESS_REPEAT_REGISTER      Repetitive Operation.
 * @retval ::MODEL_SCENES_ERR_LIST_OVERFULL                   List is full.
 * @retval ::MODEL_SCENES_ERR_UNSPECIFIED                      Unspecified error.
 */
model_scenes_state_t mesh_scenes_current_scene_verify(uint8_t element_offset, uint16_t scene_number);

/**
 * Get current scene number.
 *
 * @param[in]     element_offset           Element address offset from primary element address.
 *
 * @retval ::uint16_t scene_number      Current scene number.
 */
uint16_t mesh_scenes_current_scene_get(uint8_t element_offset);

/**
 * Register store with scene state pointer.
 *
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     model_cb                  Recall Callback.
 * @param[in]     stored_state              Store with scene state pointer.
 * @param[in]     state_length              Store with scene state value length.
 *
 * @retval ::MODEL_SCENES_SUCCESS                                   Operation is Success.
 * @retval ::MODEL_SCENES_SUCCESS_REPEAT_REGISTER      Repetitive Operation.
 * @retval ::MODEL_SCENES_ERR_LIST_OVERFULL                   List is full.
 * @retval ::MODEL_SCENES_ERR_UNSPECIFIED                      Unspecified error.
 */
model_scenes_state_t mesh_scenes_state_store_with_scene(uint8_t element_offset, mesh_scenes_notice_model_cb model_cb, void *p_server, uint8_t *stored_state, uint16_t state_length);

/**
 * Store the current state of an element as a Scene.
 *
 * @param[in]     element_offset                Element address offset from primary element address.
 * @param[in]     scene_number                The number of the scene to be stored.
 * @param[in]     target_scene_number      The target number of the scene transition.
 *
 * @retval ::MODEL_SCENES_SUCCESS                                   Operation is Success.
 * @retval ::MODEL_SCENES_ERR_EMPTY_LIST                        Store with scene state list not found.
 * @retval ::MODEL_SCENES_ERR_LIST_OVERFULL                   List is full.
 * @retval ::MODEL_SCENES_ERR_UNSPECIFIED                      Unspecified error.
 */
model_scenes_state_t mesh_scenes_scene_store(uint8_t element_offset, uint16_t scene_number, uint16_t target_scene_number);

/**
 * recall the current state of an element from a previously stored scene.
 *
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     scene_number           The number of the scene to be recalled.
 *
 * @retval ::MODEL_SCENES_SUCCESS                                   Operation is Success.
 * @retval ::MODEL_SCENES_ERR_NOT_FOUND                        Scene Not Found.
 */
model_scenes_state_t mesh_scenes_scene_recall(uint8_t element_offset, uint16_t scene_number);

/**
 * get the current status of the Scene Register of an element.
 *
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     out_length                 The max number of the output list element can be stored.
 * @param[out]   p_out                        Pointer to store the output list of scenes stored within an element.
 *
 * @retval ::uint16_t                            The number of the output list element.
 */
uint16_t mesh_scenes_scene_register_get(uint8_t element_offset, uint16_t out_length, uint16_t *p_out );

/**
 * Delete a Scene from the Scene Register state of an element.
 *
 * @param[in]     element_offset           Element address offset from primary element address.
 * @param[in]     scene_number           The number of the scene to be recalled.
 *
 * @retval ::MODEL_SCENES_SUCCESS                                   Operation is Success.
 * @retval ::MODEL_SCENES_ERR_NOT_FOUND                        Scene Not Found.
 */
model_scenes_state_t mesh_scenes_scene_delete(uint8_t element_offset, uint16_t scene_number);

/**
 * Deinitializes  the scene memory.
 *
 * @param[in]     None.
 *
 * @retval ::None
 */
void mesh_scenes_deinit(void);

/**
 * Initializes  the scene memory.
 *
 * @param[in]     None.
 *
 * @retval ::None
 */
void mesh_scenes_init(void);

#endif /* __MESH_SCENES_COMMON_H__ */
/** @} */
 
