/**
 *****************************************************************************************
 *
 * @file mesh_property.c
 *
 * @brief Mesh Property API Implementation.
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
#include "mesh_property.h"

static gx_list_t* property_list[MAX_PROPERTY_LIST_NUM] = {NULL};
static uint16_t property_list_ids_num[MAX_PROPERTY_LIST_NUM] = {0};
static uint16_t* property_list_ids[MAX_PROPERTY_LIST_NUM] = {NULL};

static void bubble_sort(uint16_t property_id[], uint8_t id_num)
{
    uint16_t temp = 0; 
    for(int i = 0; i < id_num; i++)
    {
        for(int j = 0; j < id_num - i - 1; j++)
        {
            if (property_id[j] > property_id[j+1])
                {
                temp = property_id[j];
                property_id[j] = property_id[j+1];
                property_id[j+1] = temp;
            }
        }
    }
}
property_value_type_t get_property_value_type(uint16_t property_id)
{
    property_value_type_t value_type = NOT_FIND_ID;
    if ((property_id >= 0x0036 && property_id <= 0x003C)
        || (property_id >= 0x002B && property_id <= 0x002D)
        || property_id == 0x004E
        || (property_id >= 0x006A && property_id <= 0x006F))
    {
        value_type = PROPERTY_UINT24;
    }
    else if ((property_id >= 0x002E && property_id <= 0x0030) || property_id == 0x0068 ||property_id == 0x004C)
    {
        value_type = PROPERTY_UINT16;
    }
    else if (property_id == 0x0031 || property_id == 0x0042 || property_id == 0x004D)
    {
        value_type = PROPERTY_UINT8;
    }
    else if (property_id >= 0x0032 && property_id <= 0x0035)
    {
        value_type = PROPERTY_FLOAT32;
    }
    else
    {
        value_type = NOT_FIND_ID;
    }
    return value_type;
}

uint16_t get_property_value_length(uint16_t property_id)
{
    uint16_t value_length = 0;
    if ((property_id >= 0x0036 && property_id <= 0x003C)
        || (property_id >= 0x002B && property_id <= 0x002D)
        || property_id == 0x004E
        || (property_id >= 0x006A && property_id <= 0x006F))
    {
        value_length = 3;
    }
    else if ((property_id >= 0x002E && property_id <= 0x0030) || property_id == 0x0068 ||property_id == 0x004C)
    {
        value_length = 2;
    }
    else if (property_id == 0x0031 || property_id == 0x0042 || property_id == 0x004D)
    {
        value_length = 1;
    }
    else if (property_id >= 0x0032 && property_id <= 0x0035)
    {
        value_length = 4;
    }
    else
    {
        value_length = 0;
    }
    return value_length;
}

property_value_info_t get_property_value_info(uint16_t property_id, bool* is_signed, bool* is_float, uint8_t* bit_len)
{
    if ((property_id >= 0x0036 && property_id <= 0x003C)
        || (property_id >= 0x002B && property_id <= 0x002D)
        || property_id == 0x004E
        || property_id == 0x006F)
    {
        *is_signed = false;
        *is_float = false;
        *bit_len = 24;
    }
    else if ((property_id >= 0x002E && property_id <= 0x0030) || property_id == 0x0068 ||property_id == 0x004C)
    {
        *is_signed = false;
        *is_float = false;
        *bit_len = 16;
    }
    else if (property_id == 0x0031 || property_id == 0x0042 || property_id == 0x004D)
    {
        *is_signed = false;
        *is_float = false;
        *bit_len = 8;
    }
    else if (property_id >= 0x0032 && property_id <= 0x0035)
    {
        *is_signed = true;
        *is_float = true;
        *bit_len = 32;
    }
    else
    {
        return GET_VAULE_INFO_FAILED;
    }
    
    return GET_VAULE_INFO_SUCCESS;
}

property_list_add_error_t property_list_add(uint8_t list_index, uint16_t property_id)
{
    uint16_t* p_buffer = sys_malloc(sizeof(uint16_t) * (property_list_ids_num[list_index] + 1));
    if (p_buffer == NULL)
    {
        APP_LOG_ERROR("Malloc failed!");
        return ADD_FAILED;
    }
    p_buffer[0] = property_id;
    memcpy(p_buffer+1, property_list_ids[list_index],property_list_ids_num[list_index] * sizeof(uint16_t));
    bubble_sort(p_buffer, property_list_ids_num[list_index] + 1);
    sys_free(property_list_ids[list_index]);
    property_list_ids[list_index] = p_buffer;
    property_list_ids_num[list_index]++;
    
    bool is_signed;
    bool is_float;
    uint8_t bit_len;
    uint8_t status = get_property_value_info(property_id, &is_signed, &is_float, &bit_len);
    if (status == GET_VAULE_INFO_SUCCESS)
    {
        device_property_t* p_data = (device_property_t*)sys_malloc(sizeof(device_property_t));
        gx_list_hdr_t* list_node = (gx_list_hdr_t*)sys_malloc(sizeof(gx_list_hdr_t));
        p_data->property_id = property_id;
        p_data->access = PROP_DFT_ACCESS;//Other value can not pass BQB
        p_data->value_length = bit_len / 8;
        p_data->property_value = sys_malloc(p_data->value_length * sizeof(uint8_t));
        memset(p_data->property_value, 0, p_data->value_length);
        list_node->ptr = p_data;
        gx_list_push_back(property_list[list_index], list_node);
    }
    else
    {
        APP_LOG_INFO("Input property id is not support!");
        return ADD_FAILED;
    }

    return ADD_SUCCESS;
}

property_list_init_error_t property_list_init(uint8_t list_index, uint16_t property_id[], uint8_t id_num)
{
    if (id_num <= 0)
    {
        APP_LOG_ERROR("Input id number must more than zero!");
        return ID_NUM_ERROR;
    }
    if (MAX_PROPERTY_LIST_NUM <= list_index)
    {
        APP_LOG_ERROR("Input list index more than support!");
        return LIST_INDEX_ERROR;
    }
    bubble_sort(property_id, id_num);
    property_list[list_index] = (gx_list_t *)sys_malloc(sizeof(gx_list_t));
    gx_list_init(property_list[list_index], PROPERTY_ID_NUMBER);
    
    bool is_signed;
    bool is_float;
    uint8_t bit_len;
    property_list_ids[list_index] = sys_malloc(sizeof(uint16_t) * id_num);
    for(int i = 0; i < id_num; i++)
    {
        uint8_t status = get_property_value_info(property_id[i], &is_signed, &is_float, &bit_len);
        if (status == GET_VAULE_INFO_SUCCESS)
        {
            device_property_t* p_data = (device_property_t*)sys_malloc(sizeof(device_property_t));
            gx_list_hdr_t* list_node = (gx_list_hdr_t*)sys_malloc(sizeof(gx_list_hdr_t));
            p_data->property_id = property_id[i];
            p_data->access = PROP_DFT_ACCESS;//Other value can not pass BQB
            p_data->value_length = bit_len / 8;
            p_data->property_value = sys_malloc(p_data->value_length * sizeof(uint8_t));
            memset(p_data->property_value, 0, p_data->value_length);
            list_node->ptr = p_data;
            gx_list_push_back(property_list[list_index], list_node);
            property_list_ids_num[list_index]++;
            property_list_ids[list_index][i] = property_id[i];
        }
        else
        {
            APP_LOG_INFO("Input property id is not support!");
            return ID_NOT_SUPPORT;
        }
    }
    return INIT_SUCCESS;
}

device_property_t* property_search(uint8_t list_index, uint16_t property_id)
{
    if (NULL == property_list[list_index])
    {
        APP_LOG_INFO("[%s] property list is null!", __func__);
        return NULL;
    }
    gx_list_hdr_t *p_node = gx_list_pick_front(property_list[list_index]);
    while(p_node)
    {
        device_property_t* device_property = p_node->ptr;
        if (device_property->property_id == property_id)
        {
            return device_property;
        }
        p_node = gx_list_next(p_node);
    }
    return NULL;
}


bool is_property_msg_length_valid(uint16_t property_id, uint16_t property_value_len)
{
    uint16_t value_len = 0;
    property_value_type_t property_value_type = get_property_value_type(property_id);
    if (PROPERTY_FLOAT32 == property_value_type)
    {
        value_len = sizeof(uint32_t);
    }
    else
    {
        value_len = property_value_type;
    }
    if (property_value_len == value_len)
    {
        return true;
    }
    else
    {
        return false;
    }
}

uint16_t get_list_property_num(uint8_t list_index)
{
    return property_list_ids_num[list_index];
}

uint16_t* get_list_property_ids(uint8_t list_index)
{
    return property_list_ids[list_index];
}

void destroy_property_list(void)
{
    struct gx_list_hdr *p_node = NULL;
    int16_t loop_cnt = 0;
    for(uint8_t i = 0; i < MAX_PROPERTY_LIST_NUM;  i++)
    {
        property_list_ids_num[i] = 0;
        sys_free(property_list_ids[i]);
        property_list_ids[i] = NULL;
        if (NULL != property_list[i])
        {
            while(NULL != (p_node = gx_list_pop_front(property_list[i])))
            {
                if(p_node->ptr)
                {
                    device_property_t* p_data = p_node->ptr;
                    sys_free(p_data->property_value);
                    p_data->property_value = NULL;
                    p_data->value_length = 0;
                    sys_free(p_data);
                    p_data = NULL;
                }

                sys_free(p_node);
                p_node = NULL;

                loop_cnt ++;
                if(property_list[i]->maxcnt < loop_cnt)
                {
                    loop_cnt = 0;
                    break;
                }
            }
            sys_free(property_list[i]);
            property_list[i] = NULL;
        }
    }
}



