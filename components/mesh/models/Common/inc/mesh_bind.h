/**
 ****************************************************************************************
 *
 * @file mesh_bind.h
 *
 * @brief Header file for Mesh Module Bind Api
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
#ifndef _MESH_BIND_H_
#define _MESH_BIND_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "mesh_common.h"

/*
 * DEFINES
 ****************************************************************************************
 */

#define MODEL_BIND_SUCCESS              0x00
#define MODEL_BIND_ERR_LIST_OVERFULL    0x01
#define MODEL_BIND_ERR_INVILID_PARAM    0x02
#define MODEL_BIND_ERR_UNSPECIFIED        0x03

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef bool (*mesh_model_bind_notice_cb)(void *p_server, uint32_t src_model_id, void *p_data, uint16_t data_len);

typedef struct
{
    uint32_t       model_id;                             /**< Model ID of model .*/
    uint8_t model_instance_index;
    void *p_server;
    mesh_model_bind_notice_cb cb;
}model_bind_t;


/**
 * Add a bind callback
 *
 * @param[in]     model_id                              self module id..
 * @param[in]     model_instance_index           module instance index .
 * @param[in]     p_server                              pointer module server instance.
 * @param[in]     cb                                        pointer module handle callback function.
 *
 * @retval ::MODEL_BIND_SUCCESS                      Operation is Success.
 * @retval ::MODEL_BIND_ERR_LIST_OVERFULL      Bind list is full.
 * @retval ::MODEL_BIND_ERR_INVILID_PARAM      Invalid parameter.
 * @retval ::MODEL_BIND_ERR_UNSPECIFIED         Unspecified error.
 */

extern uint16_t mesh_model_bind_list_add(uint32_t model_id, uint8_t model_instance_index, void *p_server, mesh_model_bind_notice_cb cb);

/**
 * Add a bind callback
 *
 * @param[in]     model_id                              self module id..
 * @param[in]     model_instance_index           module instance index .
 * @param[in]     p_server                              pointer module server instance.
 * @param[in]     cb                                        pointer module handle callback function.
 *
 * @retval ::true       handle bind success
 * @retval ::false      handle bind failure.
 */
extern bool mesh_model_bind_list_remov(uint32_t model_id, uint8_t model_instance_index);

/**
 * Check if the binded module exists
 *
 * @param[in]     model_instance_index             binded mesh max number.
 * @param[in]     dst_model_id                          destination module id.
 * @param[in]     src_model_id                          source module id.
 * @param[in]     p_data                                   pointer source module changed data.
 * @param[in]     data_len                                 source module changed data length.
 *
 * @retval ::true       handle bind success
 * @retval ::false      handle bind failure.
 */
extern bool mesh_model_bind_check(uint8_t model_instance_index, uint32_t dst_model_id, uint32_t src_model_id, void *p_data, uint16_t data_len);

/**
 * Destroy  model bind list struct.
 *
 */
void mesh_model_bind_list_destroy(void);

/**
 * Initializes model bind list struct.
 *
 * @param[in]     model_number_max   binded mesh max number.
 *
 * @retval ::true       Initializes success.
 * @retval ::false      Initializes failure.
 */
extern bool mesh_model_bind_list_init(uint16_t model_number_max);


#endif /*  _MESH_BIND_H_  */
/** @} */

