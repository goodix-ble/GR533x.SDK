/**
 *****************************************************************************************
 *
 * @file mesh_bind.c
 *
 * @brief Mesh Bind API Implementation.
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
#include "mesh_bind.h"
#include "app_log.h"


struct gx_list *bind_list = NULL;

static gx_list_hdr_t *mesh_model_bind_search(uint32_t model_id, uint8_t model_instance_index)
{
    //APP_LOG_INFO("%s", __func__);
    if (NULL == bind_list)
    {
        return NULL;
    }
    gx_list_hdr_t *p_node = gx_list_pick_front(bind_list);
    while(p_node)
    {
        model_bind_t * ptr_m = (model_bind_t *)p_node->ptr;
        if ((ptr_m->model_id == model_id)
                &&( ptr_m->model_instance_index == model_instance_index))
        {
            return p_node;
        }
        p_node = gx_list_next(p_node);
    }

    return NULL;
}

uint16_t mesh_model_bind_list_add(uint32_t model_id, uint8_t model_instance_index, void *p_server, mesh_model_bind_notice_cb cb)
{
    if ((NULL != cb)&&(model_id != 0x00000000)&&(NULL != bind_list))
    {
        model_bind_t *p_data = NULL;
        gx_list_hdr_t * list_node = NULL;

        if (NULL == (list_node = mesh_model_bind_search(model_id, model_instance_index)))
        {
            p_data = (model_bind_t *)sys_malloc(sizeof(model_bind_t));
            list_node = (gx_list_hdr_t *)sys_malloc(sizeof(gx_list_hdr_t));
        }
        else
        {
            p_data = (model_bind_t *)list_node;
        }

        if ((NULL != p_data)&&(NULL != list_node))
        {
            p_data->cb = cb;
            p_data->p_server = p_server;
            p_data->model_instance_index = model_instance_index;
            p_data->model_id = model_id;

            list_node->ptr = (void *)p_data;
            return (gx_list_push_front(bind_list, list_node))?MODEL_BIND_SUCCESS:MODEL_BIND_ERR_LIST_OVERFULL;
        }
        else
        {
            if (NULL != p_data)
            {
                sys_free(p_data);
            }

            if (NULL != list_node)
            {
                sys_free(list_node);
            }

            return MODEL_BIND_ERR_UNSPECIFIED;
        }
    }

    return MODEL_BIND_ERR_INVILID_PARAM;
}

bool mesh_model_bind_list_remov(uint32_t model_id, uint8_t model_instance_index)
{
    if ((model_id != 0x00000000)&&(NULL != bind_list))
    {
        gx_list_hdr_t * list_node = NULL;

        if (NULL != (list_node = mesh_model_bind_search(model_id, model_instance_index)))
        {
            if(gx_list_extract(bind_list, list_node))
            {
                if(list_node->ptr)
                {
                    sys_free(list_node->ptr);
                    list_node->ptr = NULL;
                }

                if(list_node)
                {
                    sys_free(list_node);
                    list_node = NULL;
                }

                return true;
            }
        }

    }

    return false;
}

bool mesh_model_bind_check(uint8_t model_instance_index, uint32_t dst_model_id, uint32_t src_model_id, void *p_data, uint16_t data_len)
{
    if (NULL == bind_list)
    {
        return false;
    }
    gx_list_hdr_t *p_node = mesh_model_bind_search(dst_model_id, model_instance_index);

    if (NULL != p_node)
    {
        model_bind_t *p_bind_ins = (model_bind_t *)p_node->ptr;

        if (p_bind_ins && p_bind_ins->cb)
        {
            return p_bind_ins->cb(p_bind_ins->p_server, src_model_id, p_data, data_len);
        }
    }

    return false;
}

void mesh_model_bind_list_destroy(void)
{
    struct gx_list_hdr *p_node = NULL;
    int16_t loop_cnt = 0;

    if(bind_list)
    {
        while(NULL != (p_node = gx_list_pop_front(bind_list)))
        {
            if(p_node->ptr)
            {
                sys_free(p_node->ptr);
                p_node->ptr = NULL;
            }

            sys_free(p_node);
            p_node = NULL;

            loop_cnt ++;
            if(bind_list->maxcnt < loop_cnt)//something error
            {
                break;
            }
        }

        sys_free(bind_list);
        bind_list = NULL;
    }
}

bool mesh_model_bind_list_init(uint16_t model_number_max)
{
    if(bind_list)
    {
        mesh_model_bind_list_destroy();
    }

    bind_list = (gx_list_t *)sys_malloc(sizeof(gx_list_t));

    if (NULL != bind_list)
    {
        gx_list_init(bind_list, model_number_max);
        return true;
    }

    return false;
}

