/**
 *****************************************************************************************
 *
 * @file time_common.c
 *
 * @brief APP Mesh Time Common API Implementation.
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
#include "time_common.h"
#include "mesh_common.h"
#include "app_log.h"


 


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */
bool is_little_endian = true;

/* The TAI Seconds state is the current TAI time in seconds after the epoch 2000-01-01T00:00:00 TAI */
const mesh_utc_time_t base_time =
{
    .sec = 0, 
    .min = 0, 
    .hour = 0, 
    .date = 01,
    .mon = 01, 
    .year = 00,   /**< Specifies the Calendar year which stars from 2000.*/
    .week = 5,    /**< Saturday */
};
static const int Days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
static const int leap_Days[12]={31,29,31,30,31,30,31,31,30,31,30,31};

calendar_handle_t g_calendar_handle;
int16_t time_zone_current = 0;
int16_t time_tai2utc_dlt = 0;
int16_t hundred_year_wrap = 0;

time_update_scheduler_cb_t time_scheduler_cb = NULL;
/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */



/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */
void app_mesh_time_init(void)
{
    uint16_t status ;

#ifdef HAL_CALENDAR_MODULE_ENABLED
    status = (uint16_t)hal_calendar_init(&g_calendar_handle);
#endif
    APP_LOG_INFO("[%s] calendar init status %d", __func__, status);
}

calendar_handle_t *app_mesh_time_get_handle(void)
{
    return &g_calendar_handle;
}

uint16_t app_mesh_time_sec_convert_local_time(uint64_t sec, uint8_t subsec, mesh_utc_time_t*utc_time)
{
    uint32_t dates = sec / APP_TIME_SECS_PER_DAY;
    uint8_t week = dates %7;
    uint16_t years = utc_time->year + 2000;
    int mons_idx = 0;
    uint32_t TAI_seconds = sec;

    APP_LOG_INFO("%s TAI_seconds %d!", __func__, TAI_seconds);
    if (!utc_time)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (utc_time)
    {
        utc_time->week = (week + utc_time->week)%7;

        for(;;)
        {
            if ((((years%4)==0)&&((years%100)!=0))  ||((years%400)==0)) //leap year
            {
                if (sec >= APP_TIME_SECS_LEAP_YEAR)
                {
                    years ++;
                    sec -= APP_TIME_SECS_LEAP_YEAR;
                    continue;
                }
                else
                {
                    utc_time->sec += sec % APP_TIME_SECS_PER_MIN;
                    utc_time->min += (sec % APP_TIME_SECS_PER_HOUR) / APP_TIME_SECS_PER_MIN;
                    utc_time->hour += (sec % APP_TIME_SECS_PER_DAY) / APP_TIME_SECS_PER_HOUR;
                    dates = (sec % APP_TIME_SECS_LEAP_YEAR) / APP_TIME_SECS_PER_DAY;

                    while(dates >= leap_Days[mons_idx])
                    {
                        utc_time->mon ++;
                        dates -= leap_Days[mons_idx];
                        mons_idx ++;
                        if (mons_idx == 12)
                        {
                            return MESH_ERROR_UNSPECIFIED_ERROR;
                        }
                    }

                    utc_time->date += dates;
                }
            }
            else
            {
                if (sec >= APP_TIME_SECS_PER_YEAR)
                {
                    years ++;
                    sec -= APP_TIME_SECS_PER_YEAR;
                    continue;
                }
                else
                {
                        utc_time->sec += sec % APP_TIME_SECS_PER_MIN;
                        utc_time->min += (sec % APP_TIME_SECS_PER_HOUR) / APP_TIME_SECS_PER_MIN;
                        utc_time->hour += (sec % APP_TIME_SECS_PER_DAY) / APP_TIME_SECS_PER_HOUR;
                        dates = (sec % APP_TIME_SECS_PER_YEAR) / APP_TIME_SECS_PER_DAY;

                        while(dates >= Days[mons_idx])
                        {
                            utc_time->mon ++;
                            dates -= Days[mons_idx];
                            mons_idx ++;
                            if (mons_idx == 12)
                            {
                                return MESH_ERROR_UNSPECIFIED_ERROR;
                            }
                        }

                        utc_time->date += dates;
                    }
            }

            break;
        }

        utc_time->year = years - 2000;
        utc_time->ms = subsec *1000/256;

        hundred_year_wrap = utc_time->year /100;
        /* no need check date wrap*/
        APP_LOG_INFO("[%s] update time, %d-%02d-%02d %02d:%02d:%02d", __func__, years, utc_time->mon, utc_time->date, utc_time->hour, utc_time->min, utc_time->sec);
    }

    return MESH_ERROR_NO_ERROR;
}

uint16_t app_mesh_time_local_time_convert_sec(mesh_utc_time_t*utc_time, uint64_t *TAI_sec, uint8_t *subsec)
{
    uint64_t seconds = 0;
    uint16_t years = 0;
    uint8_t mon_idx = 0;

    if ((!utc_time) || ((!TAI_sec) && (!subsec)))
    {
        APP_LOG_INFO("[%s] ERR : invalid param !!!");
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    years = utc_time->year + 2000;

    if ((((years%4)==0)&&((years%100)!=0))  ||((years%400)==0)) //leap year
    {
        while (mon_idx < utc_time->mon -1)
        {
            seconds += leap_Days[mon_idx] * APP_TIME_SECS_PER_DAY;
            mon_idx ++;
        }
    }
    else
    {
        while(mon_idx < utc_time->mon -1)
        {
            seconds += Days[mon_idx] * APP_TIME_SECS_PER_DAY;
            mon_idx ++;
        }
    }
    seconds += (utc_time->date-1)*APP_TIME_SECS_PER_DAY;
    seconds += utc_time->hour*APP_TIME_SECS_PER_HOUR;
    seconds += utc_time->min*APP_TIME_SECS_PER_MIN;
    seconds += utc_time->sec;
    years --;

    while(years >= 2000)
    {
        if ((((years%4)==0)&&((years%100)!=0))  ||((years%400)==0)) //leap year
        {
            seconds += APP_TIME_SECS_LEAP_YEAR;
        }
        else
        {
            seconds += APP_TIME_SECS_PER_YEAR;
        }
        years --;
    }

    if (TAI_sec)
    {
        seconds += time_tai2utc_dlt;
        *TAI_sec = seconds;
    }

    if (subsec)
    {
        *subsec = utc_time->ms * 256/1000;
    }

    return MESH_ERROR_NO_ERROR;
}

uint16_t app_mesh_time_set_local_utc_time(mesh_utc_time_t *time_set)
{
    calendar_time_t set_time = {0,};

    if ((!time_set)
        ||((time_set->sec > 59)
            ||(time_set->min > 59)
            ||(time_set->hour > 23)
            ||((time_set->date > 31) ||(time_set->date < 1))
            ||((time_set->mon > 12) ||(time_set->mon < 1))
            //||(time_set->year > 99)
            ||(time_set->week > 6)
            ||(time_set->ms > 999)))
    {
        APP_LOG_INFO("[%s] invalid paramter !!!!!!", __func__);

        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    
    hal_calendar_get_time(&g_calendar_handle, &set_time);
    
    set_time.sec = time_set->sec;
    set_time.min = time_set->min;
    set_time.hour = time_set->hour;
    set_time.date = time_set->date;
    set_time.mon = time_set->mon;
    set_time.year = time_set->year%100;
    set_time.week = time_set->week;
    set_time.ms = time_set->ms;

    hundred_year_wrap = time_set->year/100;
    if (HAL_ERROR == hal_calendar_init_time(&g_calendar_handle, &set_time))
    {
        APP_LOG_INFO("Set system time failed!");
    }
    else
    {
        if (NULL != time_scheduler_cb)
        {
            time_scheduler_cb(time_set);
        }
        APP_LOG_INFO("[%s] update time, 20%02d-%02d-%02d %02d:%02d:%02d week %d", __func__, set_time.year+hundred_year_wrap*100, set_time.mon, set_time.date, set_time.hour, set_time.min, set_time.sec, set_time.week);
    }

    return MESH_ERROR_NO_ERROR;
}

void app_mesh_time_set_rtc_callback_interval(uint32_t interval)
{
    hal_calendar_set_tick(&g_calendar_handle, interval);
}


/*
uint16_t app_mesh_time_get_local_TAI_time(mesh_tai_time_t *time_get)
{
    calendar_time_t get_time;

    if (!time_get)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    hal_calendar_get_time(&g_calendar_handle, &get_time);

    time_get->sec = get_time.sec;
    time_get->min = get_time.min;
    time_get->hour = get_time.hour;
    time_get->date = get_time.date;
    time_get->mon= get_time.mon;
    time_get->year = get_time.year;
    time_get->week = get_time.week;
    time_get->ms = get_time.ms;

    return MESH_ERROR_NO_ERROR;
}
*/
void app_mesh_time_set_time_zone(int16_t time_zone)
{
    time_zone_current = time_zone;
    APP_LOG_INFO("[%s] time zone offset %d!", __func__, time_zone_current);
}

int16_t app_mesh_time_get_time_zone(void)
{
    APP_LOG_INFO("[%s] time zone offset %d!", __func__, time_zone_current);
    return time_zone_current;
}

void app_mesh_time_set_time_tai2utc_dlt(int16_t dlt)
{
    time_tai2utc_dlt = dlt;
    APP_LOG_INFO("[%s] time tai-utc delta %d!", __func__, time_tai2utc_dlt);
}

int16_t app_mesh_time_get_time_tai2utc_dlt(void)
{
    APP_LOG_INFO("[%s] time tai-utc delta %d!", __func__, time_tai2utc_dlt);
    return time_tai2utc_dlt;
}

uint16_t app_mesh_time_get_local_utc_time(mesh_utc_time_t *time_get)
{
    calendar_time_t get_time;
    hal_calendar_get_time(&g_calendar_handle, &get_time);

    time_get->sec = get_time.sec;
    time_get->min = get_time.min;
    time_get->hour = get_time.hour;
    time_get->date = get_time.date;
    time_get->mon = get_time.mon;
    time_get->year = get_time.year + hundred_year_wrap*100;
    time_get->week = get_time.week;
    time_get->ms = get_time.ms;

    //APP_LOG_INFO("%s 2%03d-%02d-%02d, delta %d!", __func__, time_get->year, time_get->mon, time_get->date, time_tai2utc_dlt);
/*
    calendar_time_t get_time;

    if (!time_get)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    hal_calendar_get_time(&g_calendar_handle, &get_time);

    time_get->sec = get_time.sec;
    time_get->min = get_time.min;
    time_get->hour = get_time.hour;
    time_get->date = get_time.date;
    time_get->mon= get_time.mon;
    time_get->year = get_time.year;
    time_get->week = get_time.week;
    time_get->ms = get_time.ms;

    if (0 != time_zone_current)
    {        
        time_get->min += (time_zone_current%4)*15;
        if (time_get->min > 59)
        {
            time_get->min = time_get->min%60;
            time_get->hour ++;
        }

        time_get->hour += (time_zone_current/4);
        if (time_get->hour > 23)
        {
            time_get->hour = time_get->hour%24;
            time_get->date ++;
            time_get->week = (time_get->week+1)%7;
        }

        if (((((time_get->year%4)==0)&&((time_get->year%100)!=0))  ||((time_get->year%400)==0)) //leap year
                &&(time_get->mon == 2))
        {
            if ((time_get->date > leap_Days[2])
            {
                time_get->date = time_get->date - leap_Days[2];
                time_get->mon ++;
            }
        }
        else if (time_get->date > Days[time_get->mon])
        {
            time_get->date = time_get->date - Days[time_get->mon];
            time_get->mon ++;
        }

        if (time_get->mon > 12)
        {
            time_get->mon = time_get->mon-12;
            time_get->year ++;
        }
    }
*/
    return MESH_ERROR_NO_ERROR;
}

void app_mesh_time_set_local_time_by_tai_sec(uint64_t TAI_sec, uint8_t subsec)
{
    uint64_t UTC_sec = 0;
    uint8_t subsecond = subsec;
    calendar_time_t set_time;
    mesh_utc_time_t utc_time = base_time;
    uint32_t TAI_seconds = TAI_sec;

    APP_LOG_INFO("[%s] TAI_seconds %d!", __func__, TAI_seconds);
    UTC_sec = TAI_sec - time_tai2utc_dlt;

    app_mesh_time_sec_convert_local_time(UTC_sec, subsecond, &utc_time);

    set_time.sec = utc_time.sec;
    set_time.min = utc_time.min;
    set_time.hour = utc_time.hour;
    set_time.date = utc_time.date;
    set_time.mon = utc_time.mon;
    set_time.year = utc_time.year%100;
    set_time.week = utc_time.week;
    set_time.ms = utc_time.ms;


    if (HAL_ERROR == hal_calendar_init_time(&g_calendar_handle, &set_time))
    {
        APP_LOG_INFO("Set system time failed!");
    }

    if (NULL != time_scheduler_cb)
    {
        time_scheduler_cb(&utc_time);
    }
    return ;
}

uint16_t app_mesh_time_get_TAI_time_sec(uint64_t *TAI_sec, uint8_t *subsec)
{
    calendar_time_t get_time;
    mesh_utc_time_t utc_time;

    if ((!TAI_sec) && (!subsec))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    hal_calendar_get_time(&g_calendar_handle, &get_time);

    utc_time.sec = get_time.sec;
    utc_time.min = get_time.min;
    utc_time.hour = get_time.hour;
    utc_time.date = get_time.date;
    utc_time.mon = get_time.mon;
    utc_time.year = get_time.year + hundred_year_wrap * 100;
    utc_time.week = get_time.week;
    utc_time.ms = get_time.ms;

    APP_LOG_INFO("[%s] local time, 2%03d-%02d-%02d %02d:%02d:%02d week:%d", __func__, utc_time.year, get_time.mon, get_time.date, get_time.hour, get_time.min, get_time.sec, get_time.week);

    app_mesh_time_local_time_convert_sec(&utc_time, TAI_sec, subsec);

    APP_LOG_INFO("[%s] get TAI seconds:%lld, subsec %d", __func__, *TAI_sec, *subsec);
    return MESH_ERROR_NO_ERROR;
}

void app_mesh_time_set_scheduler_cb(time_update_scheduler_cb_t cb)
{
    time_scheduler_cb = cb;
}
