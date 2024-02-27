/**
 *****************************************************************************************
 *
 * @file mesh_property.h
 *
 * @brief mesh property API define
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
#ifndef __MESH_PROPERTY_H__
#define __MESH_PROPERTY_H__



/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "grx_sys.h"
#include <stdbool.h>
#include <stdint.h>
#include <gx_list.h>

/*
 * DEFINES
 ****************************************************************************************
 */

#define MAX_PROPERTY_LIST_NUM                           16
#define PROPERTY_ID_NUMBER                              23

#define LIGHT_CONTROL_TIME_OCCUPANCY_DELAY_ID              0x003A
#define LIGHT_CONTROL_TIME_FADE_ON_ID                      0x0037
#define LIGHT_CONTROL_TIME_RUN_ON_ID                       0x003C
#define LIGHT_CONTROL_TIME_FADE_ID                         0x0036
#define LIGHT_CONTROL_TIME_PROLONG_ID                      0x003B
#define LIGHT_CONTROL_TIME_FADE_STANDBY_AUTO_ID            0x0038
#define LIGHT_CONTROL_TIME_FADE_STANDBY_MANUAL_ID          0x0039
#define LIGHT_CONTROL_LIGHTNESS_ON_ID                      0x002E
#define LIGHT_CONTROL_LIGHTNESS_PROLONG_ID                 0x002F
#define LIGHT_CONTROL_LIGHTNESS_STANDBY_ID                 0x0030
#define LIGHT_CONTROL_AMBIENT_LUXLEVEL_ON_ID               0x002B
#define LIGHT_CONTROL_AMBIENT_LUXLEVEL_PROLONG_ID          0x002C
#define LIGHT_CONTROL_AMBIENT_LUXLEVEL_STANDBY_ID          0x002D
#define LIGHT_CONTROL_REGULATOR_KIU_ID                     0x0033
#define LIGHT_CONTROL_REGULATOR_KID_ID                     0x0032
#define LIGHT_CONTROL_REGULATOR_KPU_ID                     0x0035
#define LIGHT_CONTROL_REGULATOR_KPD_ID                     0x0034
#define LIGHT_CONTROL_REGULATOR_ACCURACY_ID                0x0031
#define MOTION_SENSED_ID                                   0x0042
#define TIME_SINCE_MOTION_SENSED_ID                        0x0068
#define PEOPLE_COUNT_ID                                    0x004C
#define PRESENCE_DETECTED_ID                               0x004D
#define PRESENT_AMBIENT_LIGHT_LEVEL_ID                     0x004E
#define TOTAL_LIGHT_EXPOSE_TIME_ID                         0x006F

#define UNKNOW_PROPERTY_ID     0xFFFF
#define INVILID_PROPERTY_ID     0x0000

#define PROP_DFT_ACCESS  is_user_property_read
#define PROP_DFT_VALUE   0

typedef enum 
{
    not_user_property = 0x00,//admin and manufacture
    is_user_property_read = 0x01,//admin and manufacture
    is_user_property_write = 0x02,//only admin
    is_user_property_read_write = 0x03,//only admin
}admin_mfr_access_t;
/*
whether the access is one or three , all can pass BQB test.
*/
typedef struct
{
    uint16_t property_id;
    uint8_t access;
    uint8_t value_length;
    uint8_t* property_value;
}device_property_t;

typedef enum
{
    NOT_FIND_ID = 0x00,
    PROPERTY_UINT8 = 0x01,
    PROPERTY_UINT16 = 0x02,
    PROPERTY_UINT24 = 0x03,
    PROPERTY_UINT32 = 0x04,
    PROPERTY_FLOAT32 = 0x05,
}property_value_type_t;

typedef enum
{
    GET_VAULE_INFO_SUCCESS = 0x00,
    GET_VAULE_INFO_FAILED = 0x01,
}property_value_info_t;

typedef enum
{
    INIT_SUCCESS = 0x00,
    LIST_INDEX_ERROR = 0x01,
    ID_NUM_ERROR = 0x02,
    ID_NOT_SUPPORT = 0x03,
}property_list_init_error_t;

typedef enum
{
    ADD_SUCCESS = 0x00,
    ADD_FAILED = 0x01,
}property_list_add_error_t;

/**
 * Add a property to the list after the list has been init.
 *
 * @param[in]     list_index       Input list index.
 * @param[in]     property_id      Input property id.
 *
 * @retval ::true       value length is valid
 * @retval ::false      value length is invalid.
 */
property_list_add_error_t property_list_add(uint8_t list_index, uint16_t property_id);

/**
 * Check if the property value length is valid.
 *
 * @param[in]     property_id             Input property id.
 * @param[in]     property_value_len      Value length of property ID.
 *
 * @retval ::true       value length is valid
 * @retval ::false      value length is invalid.
 */
bool is_property_msg_length_valid(uint16_t property_id, uint16_t property_value_len);

/**
 * Get value type of the properrty id.
 *
 * @param[in]     property_id             Input property id.
 *
 * @retval NOT_FIND_ID          Not find the property id
 * @retval PROPERTY_UINT8       The value type of the input property id is uint8
 * @retval PROPERTY_UINT16      The value type of the input property id is uint16
 * @retval PROPERTY_UINT24      The value type of the input property id is uint24
 * @retval PROPERTY_UINT32      The value type of the input property id is uint32
 * @retval PROPERTY_FLOAT32     The value type of the input property id is float32
 */
property_value_type_t get_property_value_type(uint16_t property_id);

/**
 * Get value length of the properrty id.
 *
 * @param[in]     property_id             Input property id.
 *
 * @retval length          The value length of the input property
 */
uint16_t get_property_value_length(uint16_t property_id);

/**
 * Get value type of the properrty id.
 *
 * @param[in]     property_id             Input property id.
 * @param[out]    is_signed               The value type of input property id is signed or not
 * @param[out]    is_signed               The value type of input property id is float or not
 * @param[out]    is_signed               The value bit length of input property id
 
 * @retval GET_VAULE_INFO_SUCCESS          Get property value information success
 * @retval GET_VAULE_INFO_FAILED           Get property value information failed
 */
property_value_info_t get_property_value_info(uint16_t property_id, bool* is_signed, bool* is_float, uint8_t* bit_len);

/**
 * Init property list.
 *
 * @param[in]     list_index             Input list index.
 * @param[in]     property_id[]          Input property ids to init
 * @param[in]     id_num                 Input property id number

 * @retval INIT_SUCCESS          Init the property list success
 * @retval LIST_INDEX_ERROR      Input list index is invalid
 * @retval ID_NUM_ERROR          Input property id number is invalid
 * @retval ID_NOT_SUPPORT        Input property id is invalid
 */
property_list_init_error_t property_list_init(uint8_t list_index, uint16_t property_id[], uint8_t id_num);

/**
 * Get the property value information.
 *
 * @param[in]     list_index             Input list index.
 * @param[in]     property_id            Input property id

 * @retval device_property_t          The property value information of the input property id 
 */
device_property_t* property_search(uint8_t list_index, uint16_t property_id);
/**
 * Get the property number of the list.
 *
 * @param[in]     list_index             Input list index.

 * @retval  The property number of the list.
 */
uint16_t get_list_property_num(uint8_t list_index);

/**
 * Get the property ids list.
 *
 * @param[in]     list_index             Input list index.

 * @retval   All the property ids of the input list.
 */
uint16_t* get_list_property_ids(uint8_t list_index);

/**
 * Destroy all property list.
 */
void destroy_property_list(void);

#endif /* __MESH_PROPERTY_H__ */

/** @} */
