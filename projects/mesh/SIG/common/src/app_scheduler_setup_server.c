/**
 *****************************************************************************************
 *
 * @file app_scheduler_setup_server.c
 *
 * @brief APP mesh scheduler API Implementation.
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
 #include <stdlib.h>
#include "time_common.h"
#include "app_scheduler_setup_server.h"
#include "scheduler_setup_server.h"
#include "app_log.h"
#include "user_app.h"
#include "mesh_bind.h"

/*
 * DEFINES
 ****************************************************************************************
 */
#define FORMAT_VALUE_RANGE(value, max, min) ((value) = ((value) > (max)) ? (max) : (((value) < (min)) ? (min):(value)))
#define T_YEAR_OFFSET     0
#define T_MONTH_OFFSET  1
#define T_DAY_OFFSET       2
#define T_HOUR_OFFSET     3
#define T_MINUTE_OFFSET 4
#define T_SECOND_OFFSET 5
#define T_MAX_OFFSET       6

#define CMP_DF 0
#define GT_LO 1
#define EQ_LO 2
#define LT_LO 3
/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void app_mesh_scheduler_action_set_cb(mesh_scheduler_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const mesh_scheduler_action_set_params_t * p_in, mesh_scheduler_action_status_params_t * p_out);

static bool app_mesh_scheduler_active_action_update(app_scheduler_setup_server_t *p_server, app_scheduler_action_t *new_action, mesh_utc_time_t *local_time);

static app_scheduler_setup_server_t *schedule_instance_action[TSCNS_SCHEDULER_SERVER_INSTANCE_COUNT] = {NULL,};

static app_scheduler_active_action_t schedule_active_action = {
    .alarm_flag = false,
    .g_calendar_handle = NULL,
    .p_server = NULL,
    .active_action.registered = false,
};
/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

const mesh_scheduler_server_callbacks_t scheduler_setup_srv_cbs =
{
    .scheduler_cbs.get_cb = NULL,
    .scheduler_cbs.action_get_cb = NULL,
    .scheduler_cbs.action_set_cb = app_mesh_scheduler_action_set_cb,
};

static app_sheduler_alarm_seconds_check_t alarm_secs_check = 
{
    .check_valid = false,
    .check_secs = TSCNS_SCHEDULER_INVALID_CHECK_SECONDS,
    .action_pending = false,
};

static mesh_utc_time_t local_time_sec;

static const int Days[12]={31,28,31,30,31,30,31,31,30,31,30,31};
static const int leap_Days[12]={31,29,31,30,31,30,31,31,30,31,30,31};

static scheduler_user_report_cb_t scheduler_user_report_cb = NULL;
/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

extern calendar_handle_t g_calendar_handle;
/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */
static bool app_mesh_scheduler_calc_recent_month(app_scheduler_action_t *cvt_action, uint16_t *in_month)
{
    uint16_t run_month = *in_month;

    if (run_month > TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_MAX)
    {
        return false;
    }

    while(1)
    {
        if (cvt_action->month == (cvt_action->month |TSCNS_SCHEDULER_REGISTER_MONTH_BIT_OFFSET(run_month)))
        {
            break;
        }

        run_month++;
        if (run_month > TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_MAX)
        {
            return false;
        }
    }

    *in_month = run_month;
    return true;
}

static bool app_mesh_scheduler_convert_date(struct date_time_cvt_flag_t cvt_flag[T_MAX_OFFSET], app_scheduler_action_t *cvt_action, mesh_utc_time_t *local_time)
{
    uint16_t month_cvt = TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_MIN;

    if (cvt_action->year == TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_ANY)
    {
        cvt_flag[T_YEAR_OFFSET].flag = true;
        cvt_flag[T_YEAR_OFFSET].t_data = local_time->year;
    }
    else
    {
        cvt_flag[T_YEAR_OFFSET].t_data = cvt_action->year;
    }

    if (cvt_action->month == TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_ANY)
    {
        cvt_flag[T_MONTH_OFFSET].flag = true;
        cvt_flag[T_MONTH_OFFSET].t_data = local_time->mon;
    }
    else
    {

        if ((cvt_action->year != TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_ANY) && (cvt_action->year == local_time->year))
        {
            month_cvt = local_time->mon;
        }

        if (false == app_mesh_scheduler_calc_recent_month(cvt_action, &month_cvt))
        {
            cvt_action->registered = false;
            return cvt_action->registered;
        }

        cvt_flag[T_MONTH_OFFSET].t_data = month_cvt;
        month_cvt ++;
    }

    if (cvt_action->day != TSCNS_SCHEDULER_REGISTER_DAY_OF_MONTH_VALUE_ANY)
    {
        cvt_flag[T_DAY_OFFSET].t_data = cvt_action->day;
    }
    else//day of week
    {
        cvt_flag[T_DAY_OFFSET].flag = true;
        if (TSCNS_SCHEDULER_SCHEDULED_ON_ALL_WEEK == (cvt_action->dayofweek & TSCNS_SCHEDULER_SCHEDULED_ON_ALL_WEEK))
        {
            cvt_flag[T_DAY_OFFSET].t_data = local_time->date;
        }
        else if (0 != (cvt_action->dayofweek & TSCNS_SCHEDULER_SCHEDULED_ON_ALL_WEEK))
        {
            int8_t i = 0;

            for (i=1; i < 7; i++ )
            {
                int8_t week_bit = TSCNS_SCHEDULER_REGISTER_DAY_OF_WEEK_BIT_OFFSET((i + local_time->week)%7);
                if (cvt_action->dayofweek & week_bit)
                {
                    //unmask converted week day
                    //cvt_action->dayofweek = cvt_action->dayofweek & (~week_bit);
                    break;
                }
            }

            if (i != 7)
            {
                cvt_flag[T_DAY_OFFSET].t_data = local_time->date+i;

                if ((((cvt_flag[T_YEAR_OFFSET].t_data%4)==0)&&((cvt_flag[T_YEAR_OFFSET].t_data%100)!=0))  ||((cvt_flag[T_YEAR_OFFSET].t_data%400)==0))//leap year
                {
                    if (cvt_flag[T_DAY_OFFSET].t_data > leap_Days[cvt_flag[T_MONTH_OFFSET].t_data])
                    {
                        cvt_flag[T_DAY_OFFSET].t_data -= leap_Days[cvt_flag[T_MONTH_OFFSET].t_data];
                    }
                }
                else
                {
                    if (cvt_flag[T_DAY_OFFSET].t_data > Days[cvt_flag[T_MONTH_OFFSET].t_data])
                    {
                        cvt_flag[T_DAY_OFFSET].t_data -= Days[cvt_flag[T_MONTH_OFFSET].t_data];
                    }
                }

                if (cvt_flag[T_DAY_OFFSET].t_data != local_time->date+i)
                {
                    if (cvt_flag[T_MONTH_OFFSET].flag == true)
                    {
                        cvt_flag[T_MONTH_OFFSET].t_data ++;

                        if (cvt_flag[T_MONTH_OFFSET].t_data > TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_MAX)
                        {
                            if (cvt_flag[T_YEAR_OFFSET].flag == true)
                            {
                                cvt_flag[T_YEAR_OFFSET].t_data ++;
                                if (cvt_flag[T_YEAR_OFFSET].t_data > TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_MAX)
                                {
                                    cvt_action->registered = false;
                                    APP_LOG_INFO("[%s] line %d : ERR : sheduler year more than 2099!!!!", __func__, __LINE__);
                                    return false;
                                }
                            }
                            else
                            {
                                cvt_action->registered = false;
                                APP_LOG_INFO("[%s] line %d : ERR : sheduler year more than 2099!!!!", __func__, __LINE__);
                                return false;
                            }
                        }
                    }
                    else if (true == app_mesh_scheduler_calc_recent_month(cvt_action, &month_cvt))
                    {
                        APP_LOG_INFO("convert next month %d", month_cvt);
                        cvt_flag[T_MONTH_OFFSET].t_data = month_cvt;
                    }
                    else if (cvt_flag[T_YEAR_OFFSET].flag == true)
                    {
                        cvt_flag[T_YEAR_OFFSET].t_data ++;
                        if (cvt_flag[T_YEAR_OFFSET].t_data > TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_MAX)
                        {
                            cvt_action->registered = false;
                            APP_LOG_INFO("[%s] line %d : ERR : sheduler year more than 2099!!!!", __func__, __LINE__);
                            return false;
                        }
                    }
                    else
                    {
                        cvt_action->registered = false;
                        APP_LOG_INFO("[%s] line %d : ERR : sheduler year more than 2099!!!!", __func__, __LINE__);
                        return false;
                    }
                }

            }
        }
    }
    //APP_LOG_INFO("[%s] line %d : convert data to : 2%03d-%02d-%02d", __func__, __LINE__, cvt_flag[T_YEAR_OFFSET].t_data, cvt_flag[T_MONTH_OFFSET].t_data, cvt_flag[T_DAY_OFFSET].t_data);

    return true;
}

static void app_mesh_scheduler_convert_time(struct date_time_cvt_flag_t cvt_flag[6], app_scheduler_action_t *cvt_action, mesh_utc_time_t *local_time)
{
    cvt_action->hour = cvt_action->hour&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG);
    cvt_action->minute = cvt_action->minute&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG);
    cvt_action->second = cvt_action->second&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG);

    if (cvt_action->hour == TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_ANY)
    {
        cvt_flag[T_HOUR_OFFSET].flag = true;
        cvt_flag[T_HOUR_OFFSET].t_data = local_time->hour;
    }
    else
    {
        cvt_flag[T_HOUR_OFFSET].t_data = cvt_action->hour;
    }

    if (cvt_action->minute == TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_ANY)
    {
        cvt_flag[T_MINUTE_OFFSET].flag = true;
        cvt_flag[T_MINUTE_OFFSET].t_data = local_time->min;
    }
    else if (cvt_action->minute == TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_EV15)
    {
        cvt_flag[T_MINUTE_OFFSET].flag = true;
        cvt_flag[T_MINUTE_OFFSET].t_data = (( local_time->min + 15)/15*15)%60;
    }
    else if (cvt_action->minute == TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_EV20)
    {
        cvt_flag[T_MINUTE_OFFSET].flag = true;
        cvt_flag[T_MINUTE_OFFSET].t_data = (( local_time->min + 20)/20*20)%60;
    }
    else
    {
        cvt_flag[T_MINUTE_OFFSET].t_data = cvt_action->minute;
    }

    if (cvt_action->second == TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_ANY)
    {
        cvt_flag[T_SECOND_OFFSET].flag = true;
        cvt_flag[T_SECOND_OFFSET].t_data = local_time->sec;
    }
    else if (cvt_action->second == TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_EV15)
    {
        cvt_flag[T_SECOND_OFFSET].flag = true;
        cvt_flag[T_SECOND_OFFSET].t_data = (( local_time->sec + 15)/15*15)%60;
    }
    else if (cvt_action->second == TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_EV20)
    {
        cvt_flag[T_SECOND_OFFSET].flag = true;
        cvt_flag[T_SECOND_OFFSET].t_data = (( local_time->sec + 20)/20*20)%60;
    }
    else
    {
        cvt_flag[T_SECOND_OFFSET].t_data = cvt_action->second;
    }
}

static bool app_mesh_scheduler_convert_setting_to_recent_date(app_scheduler_action_t *cvt_action, mesh_utc_time_t *local_time)
{
    struct date_time_cvt_flag_t cvt_flag[T_MAX_OFFSET] =
    {
        {false, 0}, {false, 0}, {false, 0},
        {false, 0}, {false, 0}, {false, 0}
    };// 0:year, 1:month, 2:day, 3:hour, 4:minute, 5:second
    uint16_t cvt_date_t[T_MAX_OFFSET] ={0, };
    uint16_t local_date_t[T_MAX_OFFSET] ={0, };

    //app_scheduler_action_t *prt_time = cvt_action;
    //APP_LOG_INFO("%s : 2%03d-%02d-%02d %02d:%02d:%02d", __func__, prt_time->year, prt_time->month, prt_time->day, prt_time->hour&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG),
                                                                                                    //prt_time->minute&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG),
                                                                                                    //prt_time->second&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG));

    if (cvt_action->registered == false)
    {
        return false;
    }

    if (false == app_mesh_scheduler_convert_date(cvt_flag, cvt_action, local_time))
    {
        return false;
    }
    app_mesh_scheduler_convert_time(cvt_flag, cvt_action, local_time);

    local_date_t[T_YEAR_OFFSET] = local_time->year;
    local_date_t[T_MONTH_OFFSET] = local_time->mon;
    local_date_t[T_DAY_OFFSET] = local_time->date;
    local_date_t[T_HOUR_OFFSET] = local_time->hour;
    local_date_t[T_MINUTE_OFFSET] = local_time->min;
    local_date_t[T_SECOND_OFFSET] = local_time->sec;

    cvt_date_t[T_YEAR_OFFSET] = cvt_flag[T_YEAR_OFFSET].t_data;
    cvt_date_t[T_MONTH_OFFSET] = cvt_flag[T_MONTH_OFFSET].t_data;
    cvt_date_t[T_DAY_OFFSET] = cvt_flag[T_DAY_OFFSET].t_data;
    cvt_date_t[T_HOUR_OFFSET] = cvt_flag[T_HOUR_OFFSET].t_data;
    cvt_date_t[T_MINUTE_OFFSET] = cvt_flag[T_MINUTE_OFFSET].t_data;
    cvt_date_t[T_SECOND_OFFSET] = cvt_flag[T_SECOND_OFFSET].t_data;
    
    APP_LOG_INFO("[%s], convert time : 2%03d-%02d-%02d %02d:%02d:%02d, local time : 2%03d-%02d-%02d %02d:%02d:%02d",
        __func__, cvt_date_t[T_YEAR_OFFSET], cvt_date_t[T_MONTH_OFFSET], cvt_date_t[T_DAY_OFFSET], cvt_date_t[T_HOUR_OFFSET],
        cvt_date_t[T_MINUTE_OFFSET], cvt_date_t[T_SECOND_OFFSET],
        local_time->year, local_time->mon, local_time->date, local_time->hour, local_time->min, local_time->sec);

    {
        int8_t idx = 0;
        int8_t lo_idx = 0;
        uint8_t cmp_lo = CMP_DF;

        for (idx =0; idx<T_MAX_OFFSET; idx ++)
        {
            if (((GT_LO == cmp_lo) || (LT_LO == cmp_lo))
                && (cvt_flag[idx].flag == true))
            {
                cvt_flag[idx].t_data = 0;
            }

            if ((cmp_lo == CMP_DF) && (cvt_flag[idx].t_data > local_date_t[idx]))
            {
                cmp_lo = GT_LO;
            }

            if ((cmp_lo == CMP_DF) && (cvt_flag[idx].t_data < local_date_t[idx]))
            {
                cmp_lo = LT_LO;
                lo_idx = idx;
            }
        }

        idx = 0;
        if (CMP_DF == cmp_lo)//all equ
        {
            for (idx =T_SECOND_OFFSET; idx >= T_YEAR_OFFSET; idx --)
            {
                if (cvt_flag[idx].flag == true)
                {
                    cvt_flag[idx].t_data ++;
                    break;
                }
            }
        }
        else if (LT_LO == cmp_lo)
        {
            for (idx = lo_idx-1; idx >= T_YEAR_OFFSET; idx --)
            {
                if (cvt_flag[idx].flag == true)
                {
                    cvt_flag[idx].t_data ++;
                    break;
                }
            }
        }

        cmp_lo = CMP_DF;
        for (idx =T_YEAR_OFFSET; idx<T_MAX_OFFSET; idx ++)
        {
            if(cvt_flag[idx].t_data < local_date_t[idx])
            {
                cmp_lo = LT_LO;
                break;
            }

            if(cvt_flag[idx].t_data > local_date_t[idx])
            {
                cmp_lo = GT_LO;
                break;
            }
        }

        //convert time great than local time, convert time is valid
        if (cmp_lo == GT_LO)
        {
            bool incr_hb = false;
            for (idx = T_SECOND_OFFSET; idx >= T_YEAR_OFFSET; idx --)
            {
                if ((cvt_flag[idx].flag == true) && ((cvt_flag[idx].t_data != cvt_date_t[idx]) || (incr_hb == true)))
                {
                    if (incr_hb == true)
                    {
                        cvt_flag[idx].t_data ++;
                        incr_hb = false;
                        APP_LOG_INFO("%s:%d, increase", __func__, __LINE__);
                    }

                    switch(idx)
                    {
                        case T_YEAR_OFFSET:
                            if (cvt_flag[idx].t_data > TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_MAX)
                            {
                                cvt_action->registered = false;
                                APP_LOG_INFO("%s:%d, Error : year more than 2099!!!", __func__, __LINE__);
                                return false;
                            }
                            break;
                        case T_MONTH_OFFSET:
                            if (cvt_flag[idx].t_data > TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_MAX)
                            {
                                incr_hb = true;
                                APP_LOG_INFO("%s:%d, Month increase ", __func__, __LINE__);
                                cvt_flag[idx].t_data = TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_MIN;
                            }

                            if (cvt_flag[idx].t_data == 0)
                            {
                                cvt_flag[idx].t_data = TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_MIN;
                            }
                            break;
                        case T_DAY_OFFSET:
                            if (cvt_flag[idx].t_data > TSCNS_SCHEDULER_REGISTER_DAY_OF_MONTH_VALUE_MAX)
                            {
                                incr_hb = true;
                                APP_LOG_INFO("%s:%d, Date increase ", __func__, __LINE__);
                                cvt_flag[idx].t_data = TSCNS_SCHEDULER_REGISTER_DAY_OF_MONTH_VALUE_MIN;
                            }

                            if (cvt_flag[idx].t_data == 0)
                            {
                                cvt_flag[idx].t_data = TSCNS_SCHEDULER_REGISTER_DAY_OF_MONTH_VALUE_MIN;
                            }
                            break;
                        case T_HOUR_OFFSET:
                            if (cvt_flag[idx].t_data > TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_MAX)
                            {
                                incr_hb = true;
                                APP_LOG_INFO("%s:%d, Hour increase ", __func__, __LINE__);
                                cvt_flag[idx].t_data = TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_MIN;
                            }
                            break;
                        case T_MINUTE_OFFSET:
                            if (cvt_flag[idx].t_data > TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_MAX)
                            {
                                incr_hb = true;
                                APP_LOG_INFO("%s:%d, Minute increase ", __func__, __LINE__);
                                cvt_flag[idx].t_data = TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_MIN;
                            }
                            break;
                        case T_SECOND_OFFSET:
                            if (cvt_flag[idx].t_data > TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_MAX)
                            {
                                incr_hb = true;
                                APP_LOG_INFO("%s:%d, Second increase ", __func__, __LINE__);
                                cvt_flag[idx].t_data = TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_MIN;
                            }
                            break;
                        default:
                            break;
                    }
                }
            }

            if (true == incr_hb)
            {
                cvt_action->registered = false;
                APP_LOG_INFO("%s:%d, Error : time passed!!!", __func__, __LINE__);
                return false;
            }
        }
        else//convert time is invalid
        {
            cvt_action->registered = false;
            APP_LOG_INFO("%s:%d, Error : time passed!!!", __func__, __LINE__);
            return false;
        }
    }

    cvt_action->year = cvt_flag[T_YEAR_OFFSET].t_data;
    cvt_action->month = cvt_flag[T_MONTH_OFFSET].t_data;
    cvt_action->day = cvt_flag[T_DAY_OFFSET].t_data;
    cvt_action->hour = cvt_flag[T_HOUR_OFFSET].t_data;
    cvt_action->minute = cvt_flag[T_MINUTE_OFFSET].t_data;
    cvt_action->second = cvt_flag[T_SECOND_OFFSET].t_data;
    cvt_action->registered = true;

    APP_LOG_INFO("[%s], convert time : 2%03d-%02d-%02d %02d:%02d:%02d, local time : 2%03d-%02d-%02d %02d:%02d:%02d",
        __func__, cvt_action->year, cvt_action->month, cvt_action->day, cvt_action->hour&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG),
        cvt_action->minute&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG), cvt_action->second&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG),
        local_time->year, local_time->mon, local_time->date, local_time->hour, local_time->min, local_time->sec);

    return true;
}

static void app_mesh_scheduler_refresh_action_alarm(mesh_utc_time_t *local_time)
{
    calendar_alarm_t alarm;

    if ( NULL == schedule_active_action.g_calendar_handle )
    {
        APP_LOG_INFO("[%s] %d : calendar do not init !!!", __func__, __LINE__);
        return ;
    }

    if (schedule_active_action.active_action.registered == false)
    {
        APP_LOG_INFO("[%s] %d : scheduler register action invalid !!!", __func__, __LINE__);
        return ;
    }

    if (schedule_active_action.alarm_flag == true)
    {
        APP_LOG_INFO("[%s] %d : disable calendar alarm event !!!", __func__, __LINE__);
        hal_calendar_disable_event(schedule_active_action.g_calendar_handle, CALENDAR_ALARM_DISABLE_DATE); 
        schedule_active_action.alarm_flag = false;
    }

    //day of week judge
    if ((0 != (schedule_active_action.active_action.dayofweek & TSCNS_SCHEDULER_SCHEDULED_ON_ALL_WEEK))
        &&(TSCNS_SCHEDULER_SCHEDULED_ON_ALL_WEEK != (schedule_active_action.active_action.dayofweek & TSCNS_SCHEDULER_SCHEDULED_ON_ALL_WEEK)))
    {
        //alarm bit 0 is sunday, shedulerday of week bit 0 is monday
        uint8_t alarm_week_mask = (schedule_active_action.active_action.dayofweek & TSCNS_SCHEDULER_SCHEDULED_ON_ALL_WEEK)<<1;

        if (schedule_active_action.active_action.dayofweek & TSCNS_SCHEDULER_SCHEDULED_ON_SUNDAY)
        {
            alarm_week_mask = TSCNS_SCHEDULER_SCHEDULED_ON_ALL_WEEK&(alarm_week_mask & 0x01);//mask alarm sundays
        }

        alarm.alarm_sel = CALENDAR_ALARM_SEL_WEEKDAY;
        alarm.alarm_date_week_mask = alarm_week_mask;
    }
    else
    {
        alarm.alarm_sel = CALENDAR_ALARM_SEL_DATE;
        alarm.alarm_date_week_mask = schedule_active_action.active_action.day;
    }

    //alarm hour
    alarm.hour = schedule_active_action.active_action.hour&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG);
    /*
    if (alarm.hour == TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_ANY)
    {
        alarm.hour = local_time->hour;
    }
    */
    //alarm minute
    alarm.min  = schedule_active_action.active_action.minute&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG);
    /*
    if (alarm.min == TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_ANY)
    {
        alarm.min = (local_time->min+1)%60;//next 
        if (alarm.min == 0)
        {
            alarm.hour = (alarm.hour+1)%24;
        }
    }
    else if (alarm.min == TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_EV15)
    {
        alarm.min = ((alarm.min + 15)/15*15)%60;
        if (alarm.min == 0)
        {
            alarm.hour = (alarm.hour+1)%24;
        }
    }
    else if (alarm.min == TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_EV20)
    {
        alarm.min = ((alarm.min + 20)/20*20)%60;
        if (alarm.min == 0)
        {
            alarm.hour = (alarm.hour+1)%24;
        }
    }
    */

    if ((local_time->hour != alarm.hour) || (local_time->min != alarm.min))
    {
        uint16_t ret = 0;
        ret = hal_calendar_set_alarm(schedule_active_action.g_calendar_handle, &alarm);
        schedule_active_action.alarm_flag = true;
        alarm_secs_check.check_valid = false;
        //alarm_secs_check.action_pending = true;

        APP_LOG_INFO("[%s] : set new alarm ret = %d, alarm triggered : 2%03d-%02d-%02d %02d:%02d:%02d, action %d, index %d",__func__, ret,
            schedule_active_action.active_action.year, schedule_active_action.active_action.month, schedule_active_action.active_action.day,
            schedule_active_action.active_action.hour&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG),
            schedule_active_action.active_action.minute&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG),
            schedule_active_action.active_action.second&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG),
            schedule_active_action.active_action.action, schedule_active_action.active_action.index);
    }
    else//same minute, check second immediately
    {
        alarm_secs_check.check_valid = true;
        alarm_secs_check.action_pending = true;
        APP_LOG_INFO("[%s] : check old alarm: %02d:%02d ", __func__, schedule_active_action.active_action.minute, schedule_active_action.active_action.second);
    }

    alarm_secs_check.check_secs = schedule_active_action.active_action.second&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG);
    // Debug
    APP_LOG_INFO("alarm_secs_check.check_secs:%d,%d", alarm_secs_check.check_secs, __LINE__);
}

static void app_mesh_scheduler_refresh_element_action(mesh_utc_time_t *local_time)
{
    int8_t idx = 0;
    int8_t element_idx = 0;
    int8_t action_update_flag = 0;
    app_scheduler_setup_server_t *action_server = NULL;

    for (element_idx=0; element_idx<TSCNS_SCHEDULER_SERVER_INSTANCE_COUNT; element_idx++)
    {
        action_server = schedule_instance_action[element_idx];
        if (NULL != action_server)
        {
            for (idx = 0; idx < action_server->register_list_cnt; idx ++)
            {
                if (app_mesh_scheduler_active_action_update(action_server, &action_server->schedule_register_list[idx], local_time))
                {
                    action_update_flag++;
                }
            }
        }
    }
    APP_LOG_INFO("[%s]:debug %d ,%d", __func__, schedule_active_action.active_action.registered, schedule_active_action.alarm_flag);
    //if (action_update_flag > 0)
    if ((action_update_flag > 0)
        || ((true == schedule_active_action.active_action.registered) && (false == schedule_active_action.alarm_flag)))
    {
        app_mesh_scheduler_refresh_action_alarm(local_time);
    }
}

static bool app_mesh_action_registed_valid(app_scheduler_action_t *new_action, mesh_utc_time_t *local_time)
{
    //mesh_utc_time_t local_time;

    //app_mesh_time_get_local_utc_time(&local_time);
    //app_scheduler_action_t *prt_time = new_action;
    uint16_t max_cvt_month_mark = 0;

    if (TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_ANY != new_action->month)
    {
        uint16_t max_cvt_month = 0;

        max_cvt_month = TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_MIN;
        while(1)
        {
            if(new_action->month == (new_action->month |TSCNS_SCHEDULER_REGISTER_MONTH_BIT_OFFSET(max_cvt_month)))
            {
                max_cvt_month_mark = max_cvt_month;
            }

            max_cvt_month ++;
            if (max_cvt_month > TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_MAX)
            {
                break;
            }
        }
        APP_LOG_INFO("%s:%d sheduler max month=%d register month 0x%x!!!", __func__, __LINE__, max_cvt_month_mark, new_action->month);
    }

    if (new_action->registered == false)
    {
        return false;
    }

    if (local_time->year > new_action->year)
    {
        new_action->registered = false;
        APP_LOG_INFO("%s:%d  year compare fail", __func__, __LINE__);
        return false;
    }

     if ((local_time->year == new_action->year)
            &&(new_action->month != TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_ANY)
            //&& (local_time->mon > new_action->month))
            && (local_time->mon > max_cvt_month_mark))
    {
        new_action->registered = false;
        APP_LOG_INFO("%s:%d  month compare fail", __func__, __LINE__);
        return false;
    }

    if ((local_time->year == new_action->year)
            //&&(local_time->mon == new_action->month)
            &&(local_time->mon == max_cvt_month_mark)
            &&(new_action->day != TSCNS_SCHEDULER_REGISTER_DAY_OF_MONTH_VALUE_ANY)
            &&(local_time->date > new_action->day))
    {
        new_action->registered = false;
        APP_LOG_INFO("%s:%d  date compare fail", __func__, __LINE__);
        return false;
    }

    if ((local_time->year == new_action->year)
            //&&(local_time->mon == new_action->month)
            &&(local_time->mon == max_cvt_month_mark)
            &&(local_time->date == new_action->day)
            &&(local_time->hour > new_action->hour))
    {
        new_action->registered = false;
        APP_LOG_INFO("%s:%d  hour compare fail", __func__, __LINE__);
        return false;
    }

    if ((local_time->year == new_action->year)
            //&&(local_time->mon == new_action->month)
            &&(local_time->mon == max_cvt_month_mark)
            &&(local_time->date == new_action->day)
            &&(local_time->hour == new_action->hour)
            &&(local_time->min > new_action->minute))
    {
        new_action->registered = false;
        APP_LOG_INFO("%s:%d  minute compare fail", __func__, __LINE__);
        return false;
    }

    if ((local_time->year == new_action->year)
            //&&(local_time->mon == new_action->month)
            &&(local_time->mon == max_cvt_month_mark)
            &&(local_time->date == new_action->day)
            &&(local_time->hour == new_action->hour)
            &&(local_time->min == new_action->minute)
            &&(local_time->sec > new_action->second))
    {
        new_action->registered = false;
        APP_LOG_INFO("%s:%d  second compare fail", __func__, __LINE__);
        return false;
    }

    //APP_LOG_INFO("%s : 2%03d-%02d-%02d %02d:%02d:%02d", __func__, prt_time->year, prt_time->month, prt_time->day, prt_time->hour&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG),
    //                                                                                                        prt_time->minute&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG),
    //                                                                                                        prt_time->second&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG));
    return true;
}

static bool app_mesh_scheduler_active_action_update(app_scheduler_setup_server_t *p_server, app_scheduler_action_t *new_action, mesh_utc_time_t *local_time)
{
    //uint16_t reg_schedules = 0;
    app_scheduler_action_t *action_ptr = &schedule_active_action.active_action;
    app_scheduler_action_t action_tmp_new = *new_action;
    //mesh_utc_time_t local_time;

    //app_scheduler_action_t *prt_time = new_action;

    if ((NULL == p_server) || (NULL == new_action) ||(false == app_mesh_action_registed_valid(new_action, local_time)))
    {
        //app_mesh_action_registed_valid(action_ptr, local_time);
        return false;
    }
    //APP_LOG_INFO("%s : 2%03d-%02d-%02d %02d:%02d:%02d", __func__, prt_time->year, prt_time->month, prt_time->day, prt_time->hour&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG),
    //                                                                                                            prt_time->minute&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG),
    //                                                                                                            prt_time->second&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG));

    //app_mesh_time_get_local_utc_time(&local_time);
    new_action->registered = app_mesh_scheduler_convert_setting_to_recent_date(&action_tmp_new, local_time);
    APP_LOG_INFO("%s:%d month 0x%x", __func__, __LINE__, new_action->month);
    //app_mesh_scheduler_convert_setting_to_recent_date(action_ptr, local_time);

    if ((true == action_ptr->registered) && (true == action_tmp_new.registered))
    {

        //if (true == action_tmp_new.registered)
        {
            if((action_ptr->year != TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_ANY)
                    &&(action_tmp_new.year != TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_ANY)
                    &&(action_ptr->year > action_tmp_new.year))
            {
                schedule_active_action.active_action = action_tmp_new;
                schedule_active_action.p_server = p_server;
                return true;
            }
            else if (action_ptr->year < action_tmp_new.year)
            {
                APP_LOG_INFO("%s:%d, ERR:year passed", __func__, __LINE__);
                return false;
            }

            if ((action_ptr->month != TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_ANY)
                    &&(action_tmp_new.month != TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_ANY)
                    &&(action_ptr->month > action_tmp_new.month))
            {
                schedule_active_action.active_action = action_tmp_new;
                schedule_active_action.p_server = p_server;
                return true;
            }
            else if (action_ptr->month < action_tmp_new.month)
            {
                APP_LOG_INFO("%s:%d, ERR:month passed", __func__, __LINE__);
                return false;
            }

            if ((action_ptr->day != TSCNS_SCHEDULER_REGISTER_DAY_OF_MONTH_VALUE_ANY)
                    &&(action_tmp_new.day != TSCNS_SCHEDULER_REGISTER_DAY_OF_MONTH_VALUE_ANY)
                    &&(action_ptr->day > action_tmp_new.day))
            {
                schedule_active_action.active_action = action_tmp_new;
                schedule_active_action.p_server = p_server;
                return true;
            }
            else if (action_ptr->day < action_tmp_new.day)
            {
                APP_LOG_INFO("%s:%d, ERR:day passed", __func__, __LINE__);
                return false;
            }


            if ((action_ptr->hour != TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_ANY)
                    &&(action_tmp_new.hour != TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_ANY)
                    &&((action_ptr->hour&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG)) > (action_tmp_new.hour&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG))))
            {
                schedule_active_action.active_action = action_tmp_new;
                schedule_active_action.p_server = p_server;
                return true;
            }
            else if ((action_ptr->hour&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG)) < (action_tmp_new.hour&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG)))
            {
                APP_LOG_INFO("%s:%d, ERR:hour passed", __func__, __LINE__);
                return false;
            }

            if ((action_ptr->minute != TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_ANY)
                    &&(action_tmp_new.minute != TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_ANY)
                    &&((action_ptr->minute&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG)) > (action_tmp_new.minute&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG))))
            {
                schedule_active_action.active_action = action_tmp_new;
                schedule_active_action.p_server = p_server;
                return true;
            }
            else if ((action_ptr->minute&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG)) < (action_tmp_new.minute&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG)))
            {
                APP_LOG_INFO("%s:%d, ERR:minute passed", __func__, __LINE__);
                return false;
            }

            if ((action_ptr->second != TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_ANY)
                    &&(action_tmp_new.second != TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_ANY)
                    &&((action_ptr->second&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG)) > (action_tmp_new.second&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG))))
            {
                schedule_active_action.active_action = action_tmp_new;
                schedule_active_action.p_server = p_server;
                return true;
            }
            else if ((action_ptr->second&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG)) < (action_tmp_new.second&(~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG)))
            {
                APP_LOG_INFO("%s:%d, ERR:second passed", __func__, __LINE__);
                return false;
            }

        }
    }
    else if (action_tmp_new.registered == true)
    {
        schedule_active_action.active_action = action_tmp_new;
        schedule_active_action.p_server = p_server;

        //prt_time = &schedule_active_action.active_action;
        //APP_LOG_INFO("%s %d: 2%03d-%02d-%02d %02d:%02d:%02d", __func__, __LINE__, prt_time->year, prt_time->month, prt_time->day, prt_time->hour, prt_time->minute, prt_time->second);

        return true;
    }

    APP_LOG_INFO("%s:%d, action update failed", __func__, __LINE__);
    return false;
}

static bool app_mesh_scheduler_register_action_update(app_scheduler_action_t* schedule_register, const mesh_scheduler_action_set_params_t * p_in, mesh_utc_time_t *local_time)
{
    //const mesh_scheduler_action_set_params_t *prt_time = p_in;
    //APP_LOG_INFO("%s : 2%03d-%02d-%02d %02d:%02d:%02d", __func__, prt_time->year, prt_time->month, prt_time->day, prt_time->hour, prt_time->minute, prt_time->second);
    if ((p_in->year > TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_ANY)
            || (p_in->hour>TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_ONCE))
    {
        return false;
    }

    if ((NULL != schedule_register) && (NULL != p_in) && (NULL != local_time))
    {
        schedule_register->year = p_in->year;
        schedule_register->year = schedule_register->year > TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_ANY ? TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_ANY:schedule_register->year;

        schedule_register->month = p_in->month;
        schedule_register->day = p_in->day;
        schedule_register->hour = p_in->hour;
        schedule_register->hour = schedule_register->hour>TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_ONCE ? TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_ONCE:schedule_register->hour;

        if (schedule_register->hour == TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_ONCE)
        {
            if ((local_time->year == schedule_register->year)
                &&(local_time->mon == schedule_register->month)
                &&(local_time->date == schedule_register->day))
            {
                schedule_register->hour = local_time->hour + ((rand()%(TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_MAX-local_time->hour+1))|TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG);
                if ((p_in->minute >= local_time->min) && (schedule_register->hour == local_time->hour))
                {
                    schedule_register->hour ++;
                    if (schedule_register->hour > TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_MAX)
                    {
                        schedule_register->registered = false;
                        APP_LOG_INFO("%s:%d ERR:invalid sheduler hour=%d !!!", __func__, __LINE__, p_in->hour);
                        return schedule_register->registered;
                    }
                }
            }
            else
            {
                schedule_register->hour = (rand()%(TSCNS_SCHEDULER_REGISTER_HOUR_OF_DAY_VALUE_MAX+1)) |TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG;
            }
        }

        schedule_register->minute = p_in->minute;
        if (schedule_register->minute == TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_ONCE)
        {
            if ((local_time->year == schedule_register->year)
                &&(local_time->mon == schedule_register->month)
                &&(local_time->date == schedule_register->day)
                &&(local_time->hour == schedule_register->hour))
            {
                schedule_register->minute = local_time->min + ((rand()%(TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_MAX-local_time->min+1))|TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG);
                if ((p_in->second >= local_time->sec) && (schedule_register->minute == local_time->min))
                {
                    schedule_register->minute ++;
                    if (schedule_register->minute > TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_MAX)
                    {
                        schedule_register->registered = false;
                        APP_LOG_INFO("%s:%d ERR:invalid sheduler minute=%d !!!", __func__, __LINE__, p_in->minute);
                        return schedule_register->registered;
                    }
                }
            }
            else
            {
                schedule_register->minute = (rand()%TSCNS_SCHEDULER_REGISTER_MINUTE_VALUE_MAX) |TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG;
            }
        }

        schedule_register->second = p_in->second;
        if (schedule_register->second == TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_ONCE)
        {
            if ((local_time->year == schedule_register->year)
                &&(local_time->mon == schedule_register->month)
                &&(local_time->date == schedule_register->day)
                &&(local_time->hour == schedule_register->hour)
                &&(local_time->min == schedule_register->minute))
            {
                schedule_register->second = local_time->sec + ((rand()%(TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_MAX-local_time->sec+1))|TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG);
                if (schedule_register->second == local_time->sec)
                {
                    schedule_register->second ++;
                    if (schedule_register->second > TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_MAX)
                    {
                        schedule_register->registered = false;
                        APP_LOG_INFO("%s:%d ERR:invalid sheduler second=%d !!!", __func__, __LINE__, p_in->second);
                        return schedule_register->registered;
                    }
                }
            }
            else
            {
                schedule_register->second = (rand()%TSCNS_SCHEDULER_REGISTER_SECOND_VALUE_MAX) |TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG;
            }
        }

        schedule_register->dayofweek = p_in->dayofweek;
        schedule_register->action = p_in->action;
        schedule_register->transition_time = p_in->transition_time;
        schedule_register->scene_number = p_in->scene_number;
        schedule_register->index = p_in->index;
    }

    if (TSCNS_SCHEDULER_REGISTER_ACTION_NO_ACTION != schedule_register->action)
    {
        schedule_register->registered = true;
    }
    else
    {
        APP_LOG_INFO("%s:%d ERR:invalid sheduler action=%d !!!", __func__, __LINE__, schedule_register->action);
        schedule_register->registered = false;
    }

    return schedule_register->registered;
}

static void app_scheduler_do_action(void)
{
    switch(schedule_active_action.active_action.action)
    {
        case TSCNS_SCHEDULER_REGISTER_ACTION_TURN_OFF:
            APP_LOG_INFO("[%s] action index %d, action off !!!", __func__, schedule_active_action.active_action.index);
            break;
        case TSCNS_SCHEDULER_REGISTER_ACTION_TURN_ON:
            APP_LOG_INFO("[%s] action index %d, action on !!!", __func__, schedule_active_action.active_action.index);
            break;
        case TSCNS_SCHEDULER_REGISTER_ACTION_SCENE_RECALL:
            APP_LOG_INFO("[%s] action index %d, action recall !!!", __func__, schedule_active_action.active_action.index);
            break;
        default:
            APP_LOG_INFO("[%s] unknow action type !!!", __func__);
            break;
    }
    if (scheduler_user_report_cb != NULL)
    {
        scheduler_user_report_cb(schedule_active_action.active_action.action,
                                 schedule_active_action.active_action.transition_time,
                                 schedule_active_action.active_action.scene_number);
    }
    schedule_active_action.active_action.registered = false;
    //schedule_active_action.active_action.registed =
        //app_scheduler_registed_action_refresh(schedule_active_action.p_server, schedule_active_action.active_action.index);
}

static void app_mesh_scheduler_action_set_cb(mesh_scheduler_setup_server_t *p_self, const mesh_model_msg_ind_t *p_rx_msg,
                                               const mesh_scheduler_action_set_params_t * p_in, mesh_scheduler_action_status_params_t * p_out)
{
    APP_LOG_INFO("[%s] enter, SERVER[%d] -- msg: SET index: %x", __func__, p_self->model_instance_index, p_in->index);

    app_scheduler_setup_server_t *p_server = PARENT_BY_FIELD_GET(app_scheduler_setup_server_t, server, p_self);

    /* save the address of message from */
    p_server->client_address = p_rx_msg->src;

    if ((NULL != p_server->schedule_register_list) && (p_in->index < p_server->register_list_cnt))
    {
        if (app_mesh_scheduler_register_action_update(&p_server->schedule_register_list[p_in->index], p_in, &local_time_sec))
        {
            if (app_mesh_scheduler_active_action_update(p_server, &p_server->schedule_register_list[p_in->index], &local_time_sec))
            {
                APP_LOG_INFO("%s:%d month 0x%x", __func__, __LINE__, p_server->schedule_register_list[p_in->index].month);
                app_mesh_scheduler_refresh_action_alarm(&local_time_sec);
            }

            p_server->scheduler_set_cb(p_server->server.model_instance_index, p_in->index, &p_server->schedule_register_list[p_in->index]);
            APP_LOG_INFO("%s:%d month 0x%x", __func__, __LINE__, p_server->schedule_register_list[p_in->index].month);

            /* Prepare response */
            if (NULL != p_out)
            {
                memcpy(p_out, p_in, sizeof(mesh_scheduler_action_status_params_t));
            }
        }
    }
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
*/
void scheduler_user_report_cb_register(scheduler_user_report_cb_t cb)
{
    scheduler_user_report_cb = cb;
}

void hal_calendar_alarm_callback(calendar_handle_t *hcldr)
{
    calendar_time_t time;

    APP_LOG_INFO("This is an alarm.");
    hal_calendar_get_time(hcldr, &time);
    APP_LOG_INFO("Current alarm time: 2%03d-%02d-%02d %02d:%02d:%02d",  time.year, time.mon, time.date, time.hour, time.min, time.sec);

    schedule_active_action.alarm_flag = false;
    alarm_secs_check.check_valid = true;
    alarm_secs_check.action_pending = true;
}

void app_sheduler_alarm_seconds_check(void)
{
    app_mesh_time_get_local_utc_time(&local_time_sec);

    if (local_time_sec.sec <= 1)
    {
        APP_LOG_INFO("Current check time: 2%03d-%02d-%02d %02d:%02d:%02d",  local_time_sec.year, local_time_sec.mon, local_time_sec.date, local_time_sec.hour, local_time_sec.min, local_time_sec.sec);
        APP_LOG_INFO("alarm_secs_check.check_secs = %d, alarm_secs_check.check_valid = %d", alarm_secs_check.check_secs, alarm_secs_check.check_valid);
    }

    if ((TSCNS_SCHEDULER_INVALID_CHECK_SECONDS != alarm_secs_check.check_secs)
                &&(alarm_secs_check.check_valid == true)
                &&(schedule_active_action.active_action.registered == true))
    {
        //calendar_time_t time;

        //hal_calendar_get_time(&schedule_active_action.g_calendar_handle, &time);
        if (/*((0 != (schedule_active_action.active_action.dayofweek & TSCNS_SCHEDULER_SCHEDULED_ON_ALL_WEEK))
                &&(TSCNS_SCHEDULER_SCHEDULED_ON_ALL_WEEK != (schedule_active_action.active_action.dayofweek & TSCNS_SCHEDULER_SCHEDULED_ON_ALL_WEEK)))
            ||*/
            (((TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_ANY == schedule_active_action.active_action.year)
                ||((TSCNS_SCHEDULER_REGISTER_YEAR_VALUE_ANY != schedule_active_action.active_action.year)
                    &&(local_time_sec.year == schedule_active_action.active_action.year)))

                &&((TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_ANY == schedule_active_action.active_action.month)
                    ||((TSCNS_SCHEDULER_REGISTER_MONTH_VALUE_ANY != schedule_active_action.active_action.month)
                        &&(local_time_sec.mon == schedule_active_action.active_action.month)))

                &&((TSCNS_SCHEDULER_REGISTER_DAY_OF_MONTH_VALUE_ANY == schedule_active_action.active_action.day)
                    ||((TSCNS_SCHEDULER_REGISTER_DAY_OF_MONTH_VALUE_ANY != schedule_active_action.active_action.day)
                        &&(local_time_sec.date == schedule_active_action.active_action.day))))
                ||(alarm_secs_check.action_pending == true))
        {
            uint8_t active_second = schedule_active_action.active_action.second & (~TSCNS_SCHEDULER_REGISTER_RANDOM_FLAG);

            APP_LOG_INFO("Current alarm time seconds: %02d:%02d",  local_time_sec.sec, active_second);

            if ((local_time_sec.sec == active_second) || ((local_time_sec.sec >= ((active_second+1)%60)) && (alarm_secs_check.action_pending == true)))
            {
                app_scheduler_do_action();
                alarm_secs_check.action_pending = false;
            }

            if (local_time_sec.sec < ((active_second+1)%61))//chech 3 seconds after action done
            {
                app_mesh_scheduler_refresh_element_action(&local_time_sec);
            }

            if (0)//(local_time_sec.sec == 59)
            {
                app_mesh_scheduler_refresh_element_action(&local_time_sec);
                alarm_secs_check.check_secs = TSCNS_SCHEDULER_INVALID_CHECK_SECONDS;
                alarm_secs_check.check_valid = false;
                alarm_secs_check.action_pending = false;
            }
        }
        else//invalid date time
        {
            alarm_secs_check.check_secs = TSCNS_SCHEDULER_INVALID_CHECK_SECONDS;
            alarm_secs_check.check_valid = false;
        }
    }
    else //if (schedule_active_action.alarm_flag == false)
    {
        if (local_time_sec.sec < 2)//check 3 seconds every minutes
        {
            app_mesh_scheduler_refresh_action_alarm(&local_time_sec);
        }
        //app_mesh_scheduler_refresh_element_action(&local_time_sec);
    }
}

void app_scheduler_time_update_cb(mesh_utc_time_t *local_time_in)
{
    APP_LOG_INFO("%s : local time update !!!", __func__);
    app_mesh_scheduler_refresh_action_alarm(local_time_in);
}

uint16_t app_scheduler_setup_server_init(app_scheduler_setup_server_t *p_server, uint8_t element_offset, app_scheduler_setup_set_cb_t set_cb)
{
    if(( p_server == NULL)
        || (TSCNS_SCHEDULER_SERVER_INSTANCE_COUNT <= element_offset)
        || (p_server->server.scheduler_server == NULL)
        || (p_server->schedule_register_list == NULL)
        || (p_server->register_list_cnt == 0))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    p_server->server.model_lid = MESH_INVALID_LOCAL_ID;
    p_server->server.model_instance_index = element_offset;

    p_server->scheduler_set_cb = set_cb;

    APP_LOG_INFO("debug %s : %d!", __func__, __LINE__);

    p_server->client_address = MESH_INVALID_ADDR;

    p_server->server.settings.p_callbacks = &scheduler_setup_srv_cbs;

    schedule_instance_action[element_offset] = p_server;
    schedule_active_action.g_calendar_handle = app_mesh_time_get_handle();
    app_mesh_time_set_scheduler_cb(app_scheduler_time_update_cb);

    return mesh_scheduler_setup_server_init(&p_server->server, element_offset);
}

