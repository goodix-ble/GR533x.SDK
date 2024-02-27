/**
 *****************************************************************************************
 *
 * @file gx_list.c
 *
 * @brief Gx List API Implementation.
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
#include "app_log.h"

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

void gx_list_init(struct gx_list *list, uint16_t max_cnt)
{
    if( NULL != list)
    {
        list->first = list->last = NULL;
        list->cnt = 0;
        list->maxcnt = (max_cnt == 0) ? GX_LIST_DEFAULT_MAX_CNT:max_cnt;
     }

    return ;
}

bool gx_list_push_back(struct gx_list *list, struct gx_list_hdr *list_hdr)
{
    if (( NULL != list) && ( list->cnt < list->maxcnt ) && (list_hdr != NULL))
    {
        //add first list node
        if( 0 == list->cnt)
        {
            list->first = list->last = list_hdr;
            list->first->next = NULL;
            list->first->prev = NULL;
        }
        else
        {
            list->last->next = list_hdr;
            list_hdr->prev = list->last;
            list->last = list_hdr;
            list->last->next = NULL;
        }
        list->cnt ++;
        
        return true;
    }

    return false;
}

bool gx_list_push_front(struct gx_list *list, struct gx_list_hdr *list_hdr)
{
    if (( NULL != list) && ( list->cnt < list->maxcnt ) && (list_hdr != NULL))
    {
        //add first list node
        if( 0 == list->cnt)
        {
            list->first = list->last = list_hdr;
            list->first->prev = NULL;
            list->last->next = NULL;
        }
        else
        {
            list_hdr->next = list->first;
            list->first->prev = list_hdr;
            list->first = list_hdr;
            list->first->prev = NULL;
        }
        list->cnt ++;
        return true;
    }

    return false;
}

struct gx_list_hdr *gx_list_pop_front(struct gx_list *list)
{
    struct gx_list_hdr *p_node = NULL;

    if (( NULL != list) && ( 0 != list->cnt))
    {
        p_node = list->first;
        list->first = list->first->next;
        p_node->next = NULL;
        list->first->prev = NULL;
        list->cnt --;
    }

    return p_node;
}

struct gx_list_hdr *gx_list_pop_back(struct gx_list *list)
{
    struct gx_list_hdr *p_node = NULL;

    if (( NULL != list) && ( 0 != list->cnt))
    {
        p_node = list->last;
        list->last = list->last->prev;
        p_node->prev= NULL;
        list->last->next = NULL;
        list->cnt --;
    }

    return p_node;

}

bool gx_list_extract(struct gx_list *list, struct gx_list_hdr *list_hdr)
{
    struct gx_list_hdr *p_node = gx_list_pick_front(list);

    if (( NULL != list) && ( 0 != list->cnt))
    {
        while(p_node && (0 != list->cnt))
        {
            if(list_hdr == p_node)
            {
                if (NULL != list_hdr->prev)
                {
                    list_hdr->prev->next = list_hdr->next;
                }

                if (NULL != list_hdr->next)
                {
                    list_hdr->next->prev = list_hdr->prev;
                }

                list_hdr->prev = NULL;
                list_hdr->next = NULL;
                list->cnt --;

                return true;
            }

            p_node = gx_list_next(p_node);
        }
    }
    return false;
}
