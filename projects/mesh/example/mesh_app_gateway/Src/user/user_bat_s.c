/**
 *****************************************************************************************
 *
 * @file user_bat_s.c
 *
 * @brief User function Implementation.
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
 *****************************************************************************************
 */
#include "grx_sys.h"
#include "app_error.h"
#include "utility.h"
#include "app_timer.h"
#include "board_SK.h"
#include "app_log.h"
#include "sensorsim.h"
#include "user_bat_s.h"
#include "user_app.h"
#include "mesh_common.h"
#include "mesh_model.h"
#include "user_model_client.h"

/*
 * DEFINES
 *****************************************************************************************
 */

/**@brief sensorsim data. */
#define BATTERY_LEVEL_MEAS_INTERVAL        2000                 /**< Battery level measurement interval (in unit of 1 ms). */
#define MIN_BATTERY_LEVEL                  81                   /**< Minimum simulated battery level. */
#define MAX_BATTERY_LEVEL                  100                  /**< Maximum simulated battery level. */
#define BATTERY_LEVEL_INCREMENT            1                    /**< Increment between each simulated battery level measurement. */
#define CONN_LINK_MAX                      CFG_MAX_CONNECTIONS  /**< Maximum number of connect links which are allowed. */

/*
 * LOCAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */

static uint8_t              s_conn_counter;             /**< The counter of established connections. */
static bool                 s_bat_ntfs[CONN_LINK_MAX];  /**< The array for BAT notification flag of each connection. */
static uint8_t              s_bat_ntf_counter;          /**< The counter of the connnection with BAT notification. */

static app_timer_id_t       s_bat_timer_id;             /**< Battery timer id. */
static bool                 s_bat_timer_set;
static sensorsim_cfg_t      s_bat_sim_cfg;              /** Battery Level sensor simulator configuration. */
static sensorsim_state_t    s_bat_sim_state;            /** Battery Level sensor simulator state. */
static uint8_t              s_bat_lvl;

/*
 * LOCAL FUNCTION DEFINITIONS
 *****************************************************************************************
 */
/**
 *****************************************************************************************
 *@brief Function for initializing the sensor simulators.
 *****************************************************************************************
 */
static void sensor_simulator_init(void)
{
    s_bat_sim_cfg.min          = MIN_BATTERY_LEVEL;
    s_bat_sim_cfg.max          = MAX_BATTERY_LEVEL;
    s_bat_sim_cfg.incr         = BATTERY_LEVEL_INCREMENT;
    s_bat_sim_cfg.start_at_max = true;

    sensorsim_init(&s_bat_sim_state, &s_bat_sim_cfg);
} 

/**
 *****************************************************************************************
 * @brief Perform battery measurement and updating the battery level in Battery Service.
 *****************************************************************************************
 */
static void battery_level_update(void *p_arg)
{
    s_bat_lvl = (uint8_t)sensorsim_measure(&s_bat_sim_state, &s_bat_sim_cfg);

    for (uint8_t i = 0; i < CONN_LINK_MAX; i++)
    {
        if (s_bat_ntfs[i])
        {
            sdk_err_t error_code;
            error_code = bat_s_batt_lvl_update(i, 0, s_bat_lvl);

            if (SDK_ERR_NTF_DISABLED != error_code)
            {
                APP_ERROR_CHECK(error_code);
            }
        }
    }
}

/**
 *****************************************************************************************
 * @brief Process battery service event.
 *
 *****************************************************************************************
 */
static void battery_service_process_event(bat_s_evt_t *p_evt)
{
    switch (p_evt->evt_type) 
    {
        case BAT_S_EVT_NOTIFICATION_ENABLED:
            APP_LOG_INFO("Battery Level Notification Enabled");
            s_bat_ntf_counter++;
            s_bat_ntfs[p_evt->conn_idx] = true;
            break;

        case BAT_S_EVT_NOTIFICATION_DISABLED:
            APP_LOG_INFO("Battery Level Notification Disabled");
            s_bat_ntf_counter--;
            s_bat_ntfs[p_evt->conn_idx] = false;
            break;

        case BAT_S_EVT_WRITE_TEMP_VALUE:
            APP_LOG_INFO("receive write data, conn_idx = %d, length = %d", p_evt->conn_idx, p_evt->temp_value_len);
            for (uint8_t i = 0; i < p_evt->temp_value_len; i++)
            {
                APP_LOG_INFO("%02x", p_evt->temp_value[i]);
            }

            extern void handle_rcv_temp_data(uint8_t *p_data, uint8_t data_len);
            handle_rcv_temp_data(p_evt->temp_value, p_evt->temp_value_len);
            break;

        default:
            break;
     }
}

/**
 *****************************************************************************************
 * @brief Initialize services that will be used by the application.
 *****************************************************************************************
 */
static void services_init(void)
{
    sdk_err_t  error_code;
    bat_s_init_t bat_s_env_init[1];

    /*------------------------------------------------------------------*/
    bat_s_env_init[0].char_mask   = 0x7F;
    bat_s_env_init[0].batt_lvl    = 0;
    bat_s_env_init[0].evt_handler = battery_service_process_event;
    error_code = bat_s_service_init(bat_s_env_init, 1);
    APP_ERROR_CHECK(error_code);
}

/**
 *****************************************************************************************
 * @brief Function for initializing app timer
 *****************************************************************************************
 */
static void timer_init(void)
{
    sdk_err_t error_code;

    error_code = app_timer_create(&s_bat_timer_id, ATIMER_REPEAT, battery_level_update);
    APP_ERROR_CHECK(error_code);
}

/*
 * GLOBAL FUNCTION DEFINITIONS
 *****************************************************************************************
 */
void user_bat_s_connect_handler(uint8_t conn_idx)
{
    sdk_err_t error_code;

    if (!s_bat_timer_set)
    {
        error_code = app_timer_start(s_bat_timer_id, BATTERY_LEVEL_MEAS_INTERVAL, NULL);
        APP_ERROR_CHECK(error_code);
        s_bat_timer_set = true;
    }

    s_conn_counter++;
}

void user_bat_s_disconnect_handler(uint8_t conn_idx, uint8_t reason)
{
    s_conn_counter--;
    s_bat_ntfs[conn_idx] = false;

    if (0 == s_conn_counter)
    {
        app_timer_stop(s_bat_timer_id);
        s_bat_timer_set = false;
    }
}

void user_bat_s_init(void)
{
    sensor_simulator_init();
    services_init();
    timer_init();
}
