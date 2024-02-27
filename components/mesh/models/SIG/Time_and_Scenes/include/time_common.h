/**
 *****************************************************************************************
 *
 * @file time_common.h
 *
 * @brief  Mesh Time Common Define.
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
#ifndef __TSCNS_TIME_COMMON_H__
#define __TSCNS_TIME_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include "grx_hal.h"

/*
 * DEFINES
 ****************************************************************************************
 */

/**   mesh time Server model max number */
#define TSCNS_TIME_SERVER_INSTANCE_COUNT_MAX              (16)
/**   mesh time Client model max number */
#define TSCNS_TIME_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for   mesh time Server */
#define TSCNS_TIME_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for   mesh time Server publish Status message */
#define TSCNS_TIME_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for   mesh time Server response Status message */
#define TSCNS_TIME_SERVER_RSP_SEND_TX_HDL                 (0x01)

/** The total number of transmit handle for   mesh time Client */
#define TSCNS_TIME_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for   mesh time Client Get message */
#define TSCNS_TIME_CLIENT_GET_SEND_TX_HDL                 (TSCNS_TIME_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + TSCNS_TIME_SERVER_TX_HDL_TOTAL * TSCNS_TIME_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for   mesh time Client Set message */
#define TSCNS_TIME_CLIENT_SET_SEND_TX_HDL                 (TSCNS_TIME_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for   mesh time Client Set Unacknowledged message */
#define TSCNS_TIME_CLIENT_SET_UNRELIABLE_SEND_TX_HDL      (TSCNS_TIME_CLIENT_SET_SEND_TX_HDL + 1)

/** The reliable message timeout time */
#define TSCNS_TIME_RELIABLE_MSG_TIMEOUT_MS                (30000)

#define TSCNS_TIME_ZONE_OFFSET_ENCODE(x)          (((int16_t)x)+64)
#define TSCNS_TIME_ZONE_OFFSET_DECODE(x)          (((int16_t)x)-64)

#define TSCNS_TIME_TAI_ZONE_CHANGE_MAX              (0xFFFFFFFFFF)
#define TSCNS_TIME_TAI_ZONE_CHANGE_UNKNOW       (0x0000000000)

#define TSCNS_TIME_TAI2UTC_DLT_ENCODE(x)        ((x)+255)
#define TSCNS_TIME_TAI2UTC_DLT_DECODE(x)        ((x)-255)

#define TSCNS_TIME_TAI_DLT_CHANGE_MAX              (0xFFFFFFFFFF)
#define TSCNS_TIME_TAI_DLT_CHANGE_UNKNOW       (0x0000000000)

#define APP_TIME_SECS_PER_MIN   (60) 
#define APP_TIME_SECS_PER_HOUR   (APP_TIME_SECS_PER_MIN * 60)
#define APP_TIME_SECS_PER_DAY   (APP_TIME_SECS_PER_HOUR * 24) 
#define APP_TIME_SECS_PER_YEAR   (APP_TIME_SECS_PER_DAY * 365) 
#define APP_TIME_SECS_LEAP_YEAR   (APP_TIME_SECS_PER_YEAR + APP_TIME_SECS_PER_DAY) 

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

typedef struct local_time_t
{
    uint8_t sec;                    /**< Specifies the Calendar time seconds.
                                         This parameter must be a number between min_value = 0 and max_value = 59. */

    uint8_t min;                    /**< Specifies the Calendar time minutes.
                                         This parameter must be a number between min_value = 0 and max_value = 59. */

    uint8_t hour;                   /**< Specifies the Calendar time hour.
                                         This parameter must be a number between min_value = 0 and max_value = 23. */

    uint8_t date;                   /**< Specifies the Calendar date.
                                         This parameter must be a number between min_value = 1 and max_value = 31. */

    uint8_t mon;                    /**< Specifies the Calendar month.
                                         This parameter must be a number between min_value = 1 and max_value = 12. */

    uint16_t year;                   /**< Specifies the Calendar year which stars from 2000.*/

    uint8_t week;                   /**< Specifies the Calendar weekday.
                                         This parameter must be a number between min_value = 0 and max_value = 6.  value 0 means Sunday*/

    uint16_t ms;                    /**< Specifies the Calendar time milliseconds.
                                        This parameter must be a number between min_value = 0 and max_value = 999. */
} mesh_tai_time_t;

typedef struct local_time_t mesh_utc_time_t;
/** Permanet parameters for the   mesh time Set message. */
typedef struct
{
    uint64_t TAI_seconds;             /**< The current TAI time in seconds. */
    uint8_t subsecond;                     /**< The sub-second time in units of 1/256th second. */
    uint8_t uncertainty;                     /**< The estimated uncertainty in 10-millisecond steps . */
    uint8_t time_authority;           /**< 0 = No Time Authority, 1 = Time Authority  . */
    uint16_t TAI2UTC_dlt;         /**< Current difference between TAI and UTC in seconds  . 0x00FF represents a value of 0 and 0x7FFF represents a value of 32512 */
    uint8_t time_zone_offset;           /**< The local time zone offset in 15-minute increments  . 0x40 represents a value of 0 and 0xFF represents a value of 191*/
} mesh_time_set_params_t;

typedef struct
{
    uint8_t time_zone_offset_new;            /**< Current local time zone offset. 0x40 represents a value of 0 and 0xFF represents a value of 191*/
    uint64_t TAI_zone_change;             /**< TAI Seconds time of the upcoming Time Zone Offset change. */
}mesh_time_zone_set_params_t;

typedef struct
{
    uint16_t TAI2UTC_dlt_new;            /**< Upcoming difference between TAI and UTC in seconds. 0x00FF represents a value of 0 and 0x7FFF represents a value of 32512*/
    uint64_t TAI_dlt_change;              /**< TAI Seconds time of the upcoming TAI-UTC Delta change. */
}mesh_tai2utc_dlt_set_params_t;

/** Parameters for the time Status message. */
typedef struct
{
    uint64_t TAI_seconds;             /**< The current TAI time in seconds. */
    uint8_t subsecond;                     /**< The sub-second time in units of 1/256th second. */
    uint8_t uncertainty;                     /**< The estimated uncertainty in 10-millisecond steps . */
    uint8_t time_authority;           /**< 0 = No Time Authority, 1 = Time Authority  . */
    uint16_t TAI2UTC_dlt;         /**< Current difference between TAI and UTC in seconds  . 0x00FF represents a value of 0 and 0x7FFF represents a value of 32512 */
    uint8_t time_zone_offset;           /**< The local time zone offset in 15-minute increments  . 0x40 represents a value of 0 and 0xFF represents a value of 191*/
} mesh_time_status_params_t;

typedef struct
{
    uint8_t time_zone_offset_current;       /**< Current local time zone offset. 0x40 represents a value of 0 and 0xFF represents a value of 191*/
    uint8_t time_zone_offset_new;            /**< Upcoming local time zone offset. 0x40 represents a value of 0 and 0xFF represents a value of 191*/
    uint64_t TAI_zone_change;             /**< TAI Seconds time of the upcoming Time Zone Offset change. */
}mesh_time_zone_status_params_t;

typedef struct
{
    uint16_t TAI2UTC_dlt_current;            /**< Upcoming difference between TAI and UTC in seconds. 0x00FF represents a value of 0 and 0x7FFF represents a value of 32512*/
    uint16_t TAI2UTC_dlt_new;                /**< Upcoming difference between TAI and UTC in seconds. 0x00FF represents a value of 0 and 0x7FFF represents a value of 32512*/
    uint64_t TAI_dlt_change;                   /**< TAI Seconds time of the upcoming TAI-UTC Delta change. */
}mesh_tai2utc_dlt_status_params_t;

/**
 * Callback type for Time zone state Update
 *
 * @param[in]     None
 */
typedef void (*time_zone_update_cb_t)(void);

/**
 * Callback type for Time TAI-UTC Delta state Update
 *
 * @param[in]     None
 */
typedef void (*time_dlt_update_cb_t)(void);

/**
 * Callback type for scheduler state Update
 *
 * @param[in]     None
 */
typedef void (*time_update_scheduler_cb_t)(mesh_utc_time_t *local_time);

/**
 * Application Initialize mesh time service.
 *
 * @param[in]     zone_cb   Time zone cffset new state update callback
 * @param[in]     dlt_cb      TAI-UTC Delta new state update callback
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
*/
//void app_mesh_time_init(time_zone_update_cb_t zone_cb, time_dlt_update_cb_t dlt_cb);
void app_mesh_time_init(void);

/**
 * Application sets local TAI time.
 *
 * @param[in]     time_set                 TAI time struct pointer.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
*/
uint16_t app_mesh_time_set_local_utc_time(mesh_utc_time_t *time_set);

/**
 * Application sets rtc callback interval.
 *
 * @param[in]     interval                 Rtc callback interval [ms].
 *
*/
void app_mesh_time_set_rtc_callback_interval(uint32_t interval);

/**
 * Application gets local TAI time.
 *
 * @param[out]     time_get                 TAI time struct pointer.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
//uint16_t app_mesh_time_get_local_TAI_time(mesh_tai_time_t *time_get);

/**
 * Application set local time zone.
 *
 * @param[in]     time_zone                                    The local time zone offset in 15-minute increments . The valid range of -64 through +191.
 *
 */
void app_mesh_time_set_time_zone(int16_t time_zone);

/**
 * Application gets local time zone.
 *
 *
 * @retval ::time_zone                       The local time zone offset in 15-minute increments . The valid range of -64 through +191.
 */
int16_t app_mesh_time_get_time_zone(void);

/**
 * Application set local time tai-utc delta.
 *
 * @param[in]     dlt                                               Current difference between TAI and UTC in seconds. The valid range is -255 through +32512.
 *
 */
void app_mesh_time_set_time_tai2utc_dlt(int16_t dlt);

/**
 * Application gets local time zone.
 *
 *
 * @retval ::dlt                       Current difference between TAI and UTC in seconds. The valid range is -255 through +32512.
 */
int16_t app_mesh_time_get_time_tai2utc_dlt(void);

/**
 * Application gets local UTC time.
 *
 * @param[out]     time_get                 utc time struct pointer.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_mesh_time_get_local_utc_time(mesh_utc_time_t *time_get);

/**
 * Application get local TAI time.
 *
 * @param[out]     TAI_sec                 The current TAI time in seconds after the epoch 2000-01-01T00:00:00 TAI.
 * @param[out]     subsec                   The Subsecond is a fractional part of the TAI time, in units of 1/256th seconds..
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_mesh_time_get_TAI_time_sec(uint64_t *TAI_sec, uint8_t *subsec);

/**
 * Application set local time by TAI seconds.
 *
 * @param[out]     time_set                 The current TAI time in seconds after the epoch 2000-01-01T00:00:00 TAI.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
void app_mesh_time_set_local_time_by_tai_sec(uint64_t TAI_sec, uint8_t subsec);

/**
 * Application get local calendar handle.
 *
 * @param[in]     None.
 *
 * @retval ::calendar handle.
 */
calendar_handle_t *app_mesh_time_get_handle(void);

/**
 * Application converts local TAI time in seconds into local TAI time.
 *
 * @param[in]     TAI_sec                 The current TAI time in seconds after the epoch 2000-01-01T00:00:00 TAI.
 * @param[in]     subsec                   The Subsecond is a fractional part of the TAI time, in units of 1/256th seconds..
 * @param[out]     TAI_time              The TAI time pointer.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_UNSPECIFIED_ERROR        Unspecified error.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_mesh_time_sec_convert_local_time(uint64_t sec, uint8_t subsec, mesh_utc_time_t*utc_time);

/**
 * Application converts local TAI time into local TAI time in seconds .
 *
 * @param[in]     TAI_time              The TAI time pointer.
 * @param[out]     TAI_sec              The current TAI time in seconds after the epoch 2000-01-01T00:00:00 TAI.
 * @param[out]     subsec                The Subsecond is a fractional part of the TAI time, in units of 1/256th seconds..
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t app_mesh_time_local_time_convert_sec(mesh_utc_time_t*utc_time, uint64_t *TAI_sec, uint8_t *subsec);

/**
 * Application register scheduler callback for time update.
 *
 * @param[in]     cb                    Scheduler callback.
 *
 * @retval ::None.
 */
void app_mesh_time_set_scheduler_cb(time_update_scheduler_cb_t cb);

#endif /* __TSCNS_TIME_COMMON_H__ */

/** @} */

