/**
 *****************************************************************************************
 *
 * @file app_scene_server.c
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
#include "gx_list.h"
#include "mesh_scenes_common.h"
#include "app_log.h"
/*
 * DEFINES
 ****************************************************************************************
 */

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */

/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
static mesh_scenes_register_list_t mesh_scenes_register_list[MESH_SCENES_SCENE_ELEMENT_CNT_MAX];
static mesh_scenes_store_list_t mesh_scenes_store_list[MESH_SCENES_SCENE_STORE_LIST_CNT_MAX];
/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
void mesh_scenes_list_destroy(struct gx_list **init_list)
{
    struct gx_list_hdr *p_node = NULL;
    int16_t loop_cnt = 0;

    if(*init_list)
    {
        while(NULL != (p_node = gx_list_pop_front(*init_list)))
        {
            if(p_node->ptr)
            {
                sys_free(p_node->ptr);
                p_node->ptr = NULL;
            }

            sys_free(p_node);
            p_node = NULL;

            loop_cnt ++;
            if((*init_list)->maxcnt < loop_cnt)//something error
            {
                break;
            }
        }

        sys_free(*init_list);
        *init_list = NULL;
    }
}

static bool mesh_scenes_list_init(struct gx_list **init_list)
{
    if (*init_list)
    {
        return false;
    }

    *init_list = (gx_list_t *)sys_malloc(sizeof(gx_list_t));

    if (NULL != *init_list)
    {
        gx_list_init(*init_list, MESH_SCENES_SCENE_STORE_STATE_CNT_MAX);
        return true;
    }

    return false;
}

static gx_list_hdr_t *mesh_scenes_register_state_search(struct gx_list *list, uint8_t *stored_state)
{
    gx_list_hdr_t *p_node = NULL;

    //APP_LOG_INFO("%s", __func__);
    if (NULL == list)
    {
        return NULL;
    }

    p_node = gx_list_pick_front(list);

    while(p_node)
    {
        mesh_scenes_register_node_t * ptr_m = (mesh_scenes_register_node_t *)p_node->ptr;
        if (ptr_m->state_ptr == stored_state)
        {
            return p_node;
        }
        p_node = gx_list_next(p_node);
    }

    return NULL;
}

static mesh_scenes_register_list_t *mesh_scenes_get_register_scene(uint8_t element_offset)
{
    uint16_t idx = 0;
    mesh_scenes_register_list_t *ptr = NULL;

    for (idx=0; idx<MESH_SCENES_SCENE_ELEMENT_CNT_MAX; idx++)
    {
        if ((NULL == ptr) && (mesh_scenes_register_list[idx].scene_registerd == false))
        {
            ptr = &mesh_scenes_register_list[idx];
        }

        if ((mesh_scenes_register_list[idx].element_offset == element_offset)
            && (mesh_scenes_register_list[idx].scene_registerd == true))
        {
            ptr = &mesh_scenes_register_list[idx];
        }
    }

    //if already initialized 
    if (ptr->scene_registerd_magic != MESH_SCENES_SCENE_REGISTER_MAGIC_VALUE)
    {
        APP_LOG_INFO("[%s] %d register list does not initialize.", __func__, __LINE__);
        ptr = NULL;
    }

    return ptr;
}

static mesh_scenes_store_list_t *mesh_scenes_get_store_scene(uint8_t element_offset, uint16_t scene_number)
{
    uint16_t idx = 0;
    mesh_scenes_store_list_t *ptr = NULL;

    if (MESH_SCENES_SCENE_VALUE_PROHIBITED == scene_number)
    {
        return NULL;
    }

    for (idx=0; idx<MESH_SCENES_SCENE_STORE_LIST_CNT_MAX; idx++)
    {
        if ((NULL == ptr) && (mesh_scenes_store_list[idx].scene_stored == false))
        {
            ptr = &mesh_scenes_store_list[idx];
        }

        if ((mesh_scenes_store_list[idx].scene_stored == true)
            &&(mesh_scenes_store_list[idx].element_offset == element_offset)
            && (mesh_scenes_store_list[idx].scene_number == scene_number))
        {
            ptr = &mesh_scenes_store_list[idx];
            break;
        }
    }

    //if already initialized 
    if (ptr->scene_stored_magic != MESH_SCENES_SCENE_STORE_MAGIC_VALUE)
    {
        APP_LOG_INFO("[%s] %d store list does not initialize.", __func__, __LINE__);
        ptr = NULL;
    }

    return ptr;
}

static model_scenes_state_t mesh_scenes_store_current_register_state(mesh_scenes_register_list_t *reg_list, mesh_scenes_store_list_t *sto_list)
{
    uint16_t total_store_length = 0;

    APP_LOG_INFO("[%s] Enter.", __func__);

    if ((NULL == reg_list)||(NULL == reg_list->scene_list)
        ||(NULL == sto_list) || (NULL == sto_list->scene_state_values))
    {
        APP_LOG_INFO("[%s] %d exit.", __func__, __LINE__);
        return MODEL_SCENES_ERR_EMPTY_LIST;
    }

    if (reg_list ->scene_state_length > sto_list->scene_state_length)
    {
        APP_LOG_INFO("storing warning : register length %d greater than store scene length %d !!!", reg_list ->scene_state_length, sto_list->scene_state_length);
    }

    gx_list_hdr_t *p_node = gx_list_pick_front(reg_list->scene_list);
    while (total_store_length < (sto_list->scene_state_length-sizeof(mesh_scenes_store_list_node_t)))
    {
        mesh_scenes_register_node_t *register_node = NULL;

        if (NULL == p_node)//has stored all register state
        {
            APP_LOG_INFO("store broken : register list empty !!!");
            break;
        }

        register_node = (mesh_scenes_register_node_t *)p_node->ptr;

        if (NULL != register_node)
        {
            mesh_scenes_store_list_node_t *p_store_node = (mesh_scenes_store_list_node_t *)&sto_list->scene_state_values[total_store_length];

            p_store_node->cb = register_node->cb;
            p_store_node->p_server = register_node->p_server;
            p_store_node->state_length = register_node->state_length;
            p_store_node->state_ptr = register_node->state_ptr;
            memcpy(p_store_node->scene_state_value, register_node->state_ptr, register_node->state_length);

            total_store_length += sizeof(mesh_scenes_store_list_node_t) + p_store_node->state_length;
            APP_LOG_INFO("storing continue : register node 0x%p, total length %d, current length %d", register_node, sto_list->scene_state_length, total_store_length);
        }
        else
        {
            APP_LOG_INFO("storing warning : register node null !!!");
        }
        p_node = gx_list_next(p_node);
    }
    APP_LOG_INFO("storing complete : target total length %d, store current length %d", sto_list->scene_state_length, total_store_length);

    return MODEL_SCENES_SUCCESS;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */
model_scenes_state_t mesh_scenes_current_scene_verify(uint8_t element_offset, uint16_t scene_number)
{
    mesh_scenes_store_list_t *p_store_scene = mesh_scenes_get_store_scene(element_offset, scene_number);
    uint16_t scene_arr_offset = 0;

    APP_LOG_INFO("[%s] Enter.", __func__);

    if ((NULL == p_store_scene)
        ||(0 == p_store_scene->scene_state_length)
        ||(NULL == p_store_scene->scene_state_values)
        || (false == p_store_scene->scene_stored))
    {
        APP_LOG_INFO("[%s] %d exit.", __func__, __LINE__);
        return MODEL_SCENES_ERR_NOT_FOUND;
    }

    while (scene_arr_offset < (p_store_scene->scene_state_length-sizeof(mesh_scenes_store_list_node_t)))
    {
        mesh_scenes_store_list_node_t *p_store_node = (mesh_scenes_store_list_node_t *)&p_store_scene->scene_state_values[scene_arr_offset];

        if (0 != memcmp(p_store_node->scene_state_value, p_store_node->state_ptr, p_store_node->state_length))
        {
            APP_LOG_INFO("verify failure : value pointer %p, value length %d", p_store_node->state_ptr, p_store_node->state_length);
            return MODEL_SCENES_ERR_SCENNE_CHECK_FAILUER;
        }
        scene_arr_offset += sizeof(mesh_scenes_store_list_node_t) + p_store_node->state_length;
        APP_LOG_INFO("verify continue : total length %d, current offset %d", p_store_scene->scene_state_length, scene_arr_offset);
        APP_LOG_INFO("verify node :  %p, value length %d", p_store_node->state_ptr, p_store_node->state_length);
    }
    APP_LOG_INFO("verify complete : target total length %d, recall current length %d", p_store_scene->scene_state_length, scene_arr_offset);
    APP_LOG_INFO("scene verify success element %d, scene number 0x%04x", element_offset, scene_number);

    return MODEL_SCENES_SUCCESS;

}

uint16_t mesh_scenes_current_scene_get(uint8_t element_offset)
{
    mesh_scenes_store_list_t *p_store_scene = NULL;
    mesh_scenes_register_list_t *p_register_scene = mesh_scenes_get_register_scene(element_offset);
    uint16_t idx = 0;
    uint16_t current_scene = MESH_SCENES_SCENE_VALUE_PROHIBITED;

    for (idx=0; idx<MESH_SCENES_SCENE_STORE_LIST_CNT_MAX; idx++)
    {
        p_store_scene = (&mesh_scenes_store_list[idx]);

        if ((p_store_scene->scene_stored == true)
            &&(p_store_scene->element_offset == element_offset)
            && (p_store_scene->scene_number != MESH_SCENES_SCENE_VALUE_PROHIBITED)
            && (p_store_scene->scene_stored_magic == MESH_SCENES_SCENE_STORE_MAGIC_VALUE))
        {
            if (MODEL_SCENES_SUCCESS == mesh_scenes_current_scene_verify(p_store_scene->element_offset, p_store_scene->scene_number))
            {
                current_scene = p_store_scene->scene_number;
                break;
            }
        }
    }

    return current_scene;
}

model_scenes_state_t mesh_scenes_state_store_with_scene(uint8_t element_offset, mesh_scenes_notice_model_cb model_cb, void *p_server, uint8_t *stored_state, uint16_t state_length)
{
    mesh_scenes_register_list_t *p_scene = mesh_scenes_get_register_scene(element_offset);
    mesh_scenes_register_node_t *register_node =  NULL;
    struct gx_list_hdr * p_node = NULL;

    APP_LOG_INFO("[%s] Enter.", __func__);

    if (NULL == p_scene)
    {
        APP_LOG_INFO("[%s] %d exit.", __func__, __LINE__);
        return MODEL_SCENES_ERR_LIST_OVERFULL;
    }

    if (NULL == p_scene->scene_list)
    {
        if (!mesh_scenes_list_init(&p_scene->scene_list))
        {
            APP_LOG_INFO("[%s] %d exit.", __func__, __LINE__);
            return MODEL_SCENES_ERR_UNSPECIFIED;
        }
    }
    else
    {
        if (NULL != mesh_scenes_register_state_search(p_scene->scene_list, stored_state))
        {
            APP_LOG_INFO("[%s] %d exit.", __func__, __LINE__);
            return MODEL_SCENES_SUCCESS_REPEAT_REGISTER;
        }
    }

    if (NULL == (register_node =  (mesh_scenes_register_node_t *)sys_malloc(sizeof(mesh_scenes_register_node_t))))
    {
        APP_LOG_INFO("[%s] %d exit.", __func__, __LINE__);
        return MODEL_SCENES_ERR_UNSPECIFIED;
    }
    register_node->cb = model_cb;
    register_node->p_server = p_server;
    register_node->state_length = state_length;
    register_node->state_ptr = stored_state;

    if (NULL == (p_node = (gx_list_hdr_t *)sys_malloc(sizeof(gx_list_hdr_t))))
    {
        APP_LOG_INFO("[%s] %d exit.", __func__, __LINE__);
        return MODEL_SCENES_ERR_UNSPECIFIED;
    }
    p_node->ptr = (void *)register_node;
    if (!gx_list_push_front(p_scene->scene_list, p_node))
    {
        return MODEL_SCENES_ERR_LIST_OVERFULL;
    }

    p_scene->element_offset = element_offset;
    p_scene->scene_state_length += sizeof(mesh_scenes_register_node_t) + state_length;
    p_scene->scene_registerd = true;

    APP_LOG_INFO("scene state register node 0x%p success : addr=%p, length=%d.", register_node, stored_state, state_length);
    APP_LOG_INFO("element %d, scene states register number is %d, register total length is %d", element_offset, p_scene->scene_list->cnt, p_scene->scene_state_length);

    return MODEL_SCENES_SUCCESS;
}

model_scenes_state_t mesh_scenes_scene_store(uint8_t element_offset, uint16_t scene_number, uint16_t target_scene_number)
{
    mesh_scenes_register_list_t *p_register_scene = mesh_scenes_get_register_scene(element_offset);
    mesh_scenes_store_list_t *p_store_scene = mesh_scenes_get_store_scene(element_offset, scene_number);
    mesh_scenes_store_list_t *p_target_scene = mesh_scenes_get_store_scene(element_offset, target_scene_number);

    model_scenes_state_t ret = MODEL_SCENES_SUCCESS;

    APP_LOG_INFO("[%s] Enter.", __func__);

    if ((NULL == p_register_scene) || (NULL == p_store_scene))
    {
        APP_LOG_INFO("[%s] %d exit.", __func__, __LINE__);
        return MODEL_SCENES_ERR_LIST_OVERFULL;
    }

    if (NULL == p_register_scene->scene_list)
    {
        APP_LOG_INFO("[%s] %d exit.", __func__, __LINE__);
        return MODEL_SCENES_ERR_EMPTY_LIST;
    }

    if (NULL != p_target_scene)
    {
        p_store_scene->scene_state_length = p_target_scene->scene_state_length;
    }
    else
    {
        p_store_scene->scene_state_length = p_register_scene->scene_state_length;
    }

    if (p_store_scene->scene_stored == false)
    {
        if (NULL == (p_store_scene->scene_state_values = (uint8_t *)sys_malloc(p_store_scene->scene_state_length)))
        {
            APP_LOG_INFO("[%s] %d exit.", __func__, __LINE__);
            return MODEL_SCENES_ERR_UNSPECIFIED;
        }
    }

    if (NULL != p_target_scene)
    {
        p_store_scene->element_offset = p_target_scene->element_offset;
        p_store_scene->scene_number = scene_number;
        memcpy(p_store_scene->scene_state_values, p_target_scene->scene_state_values, p_store_scene->scene_state_length);
        p_store_scene->scene_stored = true;
        APP_LOG_INFO("scene store target scene success element %d, scene number 0x%04x, target scene number 0x%04x", element_offset, scene_number, target_scene_number);
    }
    else if (MODEL_SCENES_SUCCESS == (ret = mesh_scenes_store_current_register_state(p_register_scene, p_store_scene)))
    {
        p_store_scene->element_offset = element_offset;
        p_store_scene->scene_number = scene_number;
        p_store_scene->scene_stored = true;
        APP_LOG_INFO("scene store success element %d, scene number 0x%04x", element_offset, scene_number);
    }

    return ret;
}

model_scenes_state_t mesh_scenes_scene_recall(uint8_t element_offset, uint16_t scene_number)
{
    mesh_scenes_store_list_t *p_store_scene = mesh_scenes_get_store_scene(element_offset, scene_number);
    uint16_t recall_arr_offset = 0;

    APP_LOG_INFO("[%s] Enter.", __func__);

    if ((NULL == p_store_scene)
        ||(0 == p_store_scene->scene_state_length)
        ||(NULL == p_store_scene->scene_state_values)
        || (false == p_store_scene->scene_stored))
    {
        APP_LOG_INFO("[%s] %d exit.", __func__, __LINE__);
        return MODEL_SCENES_ERR_NOT_FOUND;
    }

    while (recall_arr_offset < (p_store_scene->scene_state_length-sizeof(mesh_scenes_store_list_node_t)))
    {
        mesh_scenes_store_list_node_t *p_store_node = (mesh_scenes_store_list_node_t *)&p_store_scene->scene_state_values[recall_arr_offset];

        memcpy(p_store_node->state_ptr, p_store_node->scene_state_value, p_store_node->state_length);
        if (NULL != p_store_node->cb)
        {
            p_store_node->cb(p_store_node->p_server, p_store_node->state_ptr, p_store_node->state_length);
        }

        recall_arr_offset += sizeof(mesh_scenes_store_list_node_t) + p_store_node->state_length;
        //APP_LOG_INFO("recalling continue : total length %d, current offset %d", p_store_scene->scene_state_length, recall_arr_offset);
        //APP_LOG_INFO("recalling node :  %p, value length %d", p_store_node->state_ptr, p_store_node->state_length);
    }
    APP_LOG_INFO("recalling complete : target total length %d, recall current length %d", p_store_scene->scene_state_length, recall_arr_offset);
    APP_LOG_INFO("scene recall success element %d, scene number 0x%04x", element_offset, scene_number);

    return MODEL_SCENES_SUCCESS;

}

uint16_t mesh_scenes_scene_register_get(uint8_t element_offset, uint16_t out_length, uint16_t *p_out )
{
    uint16_t idx = 0;
    uint16_t get_cnt = 0;

    APP_LOG_INFO("[%s] Enter.", __func__);

    if ((out_length == 0) || (NULL == p_out))
    {
        APP_LOG_INFO("scene register get complete : count %d", get_cnt);
        return get_cnt;
    }

    for (idx=0; idx<MESH_SCENES_SCENE_STORE_LIST_CNT_MAX; idx++)
    {
        if ((mesh_scenes_store_list[idx].element_offset == element_offset)
            && (mesh_scenes_store_list[idx].scene_stored == true)
            && (mesh_scenes_store_list[idx].scene_stored_magic == MESH_SCENES_SCENE_STORE_MAGIC_VALUE)
            && (out_length > get_cnt))
        {
            p_out[get_cnt] = mesh_scenes_store_list[idx].scene_number;
            get_cnt++;
            APP_LOG_INFO("scene register get Scene Number 0x%04x, count %d, get buffer length %d", mesh_scenes_store_list[idx].scene_number, get_cnt, out_length);
        }
    }

    APP_LOG_INFO("scene register get complete : count %d", get_cnt);
    return get_cnt;
}

model_scenes_state_t mesh_scenes_scene_delete(uint8_t element_offset, uint16_t scene_number)
{
    mesh_scenes_store_list_t *p_store_scene = mesh_scenes_get_store_scene(element_offset, scene_number);

    APP_LOG_INFO("[%s] Enter.", __func__);

    if ((NULL == p_store_scene)
        ||(0 == p_store_scene->scene_state_length)
        ||(NULL == p_store_scene->scene_state_values)
        || (false == p_store_scene->scene_stored))
    {
        APP_LOG_INFO("[%s] %d exit.", __func__, __LINE__);
        return MODEL_SCENES_ERR_NOT_FOUND;
    }

    p_store_scene->scene_number = MESH_SCENES_SCENE_VALUE_PROHIBITED;
    p_store_scene->scene_state_length = 0;
    if (p_store_scene->scene_state_values != NULL)
    {
        sys_free(p_store_scene->scene_state_values);
        p_store_scene->scene_state_values = NULL;
    }
    p_store_scene->scene_stored = false;
    APP_LOG_INFO("scene delete success element %d, scene number 0x%04x", element_offset, scene_number);

    return MODEL_SCENES_SUCCESS;
}

void mesh_scenes_deinit(void)
{
    uint16_t idx = 0;

    APP_LOG_INFO("[%s] Enter.", __func__);

    for (idx=0; idx<MESH_SCENES_SCENE_ELEMENT_CNT_MAX; idx++)
    {
        if (MESH_SCENES_SCENE_REGISTER_MAGIC_VALUE == mesh_scenes_register_list[idx].scene_registerd_magic)
        {
            mesh_scenes_register_list[idx].scene_state_length = 0;

            if (NULL != mesh_scenes_register_list[idx].scene_list)
            {
                mesh_scenes_list_destroy(&mesh_scenes_register_list[idx].scene_list);
            }

            mesh_scenes_register_list[idx].scene_registerd = false;
            mesh_scenes_register_list[idx].scene_registerd_magic = MESH_SCENES_SCENE_MAGIC_VALUE_NONE;
        }
    }

    for (idx=0; idx<MESH_SCENES_SCENE_STORE_LIST_CNT_MAX; idx++)
    {
        if (MESH_SCENES_SCENE_STORE_MAGIC_VALUE == mesh_scenes_store_list[idx].scene_stored_magic)
        {
            mesh_scenes_store_list[idx].scene_number = MESH_SCENES_SCENE_VALUE_PROHIBITED;
            mesh_scenes_store_list[idx].scene_state_length = 0;

            if (NULL != mesh_scenes_store_list[idx].scene_state_values)
            {
                sys_free(mesh_scenes_store_list[idx].scene_state_values);
                mesh_scenes_store_list[idx].scene_state_values = NULL;
            }

            mesh_scenes_store_list[idx].scene_stored = false;
            mesh_scenes_store_list[idx].scene_stored_magic = MESH_SCENES_SCENE_MAGIC_VALUE_NONE;
        }
    }

}

void mesh_scenes_init(void)
{
    uint16_t idx = 0;

    APP_LOG_INFO("[%s] Enter.", __func__);

    mesh_scenes_deinit();

    for (idx=0; idx<MESH_SCENES_SCENE_ELEMENT_CNT_MAX; idx++)
    {
        if (MESH_SCENES_SCENE_REGISTER_MAGIC_VALUE != mesh_scenes_register_list[idx].scene_registerd_magic)
        {
            mesh_scenes_register_list[idx].scene_state_length = 0;
            mesh_scenes_register_list[idx].scene_list = NULL;
            mesh_scenes_register_list[idx].scene_registerd = false;
            mesh_scenes_register_list[idx].scene_registerd_magic = MESH_SCENES_SCENE_REGISTER_MAGIC_VALUE;
        }
    }

    for (idx=0; idx<MESH_SCENES_SCENE_STORE_LIST_CNT_MAX; idx++)
    {
        if (MESH_SCENES_SCENE_STORE_MAGIC_VALUE != mesh_scenes_store_list[idx].scene_stored_magic)
        {
            mesh_scenes_store_list[idx].scene_number = MESH_SCENES_SCENE_VALUE_PROHIBITED;
            mesh_scenes_store_list[idx].scene_state_length = 0;
            mesh_scenes_store_list[idx].scene_state_values = NULL;
            mesh_scenes_store_list[idx].scene_stored = false;
            mesh_scenes_store_list[idx].scene_stored_magic = MESH_SCENES_SCENE_STORE_MAGIC_VALUE;
        }
    }
    return ;
}

