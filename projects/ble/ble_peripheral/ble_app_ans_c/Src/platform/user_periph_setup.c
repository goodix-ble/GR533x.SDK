/**
 *****************************************************************************************
 *
 * @file user_periph_setup.c
 *
 * @brief  User Periph Init Function Implementation.
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
#include "user_periph_setup.h"
#include "ans_c.h"
#include "board_SK.h"
#include "gr_includes.h"
#include "app_log.h"
#include "app_assert.h"
#include "hal_flash.h"
#include "custom_config.h"

/*
 * LOCAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
/**< Bluetooth device address. */
static const uint8_t  s_bd_addr[SYS_BD_ADDR_LEN] = {0x01, 0x00, 0xcf, 0x3e, 0xcb, 0xea};
static uint8_t        s_ctrl_point_exchange;


/*
 * GLOBAL FUNCTION DEFINITIONS
 *****************************************************************************************
 */
void app_key_evt_handler(uint8_t key_id, app_key_click_type_t key_click_type)
{
    ans_c_ctrl_pt_t ctrl_pt;

    if (BSP_KEY_OK_ID == key_id)
    {
        if (APP_KEY_SINGLE_CLICK == key_click_type)
        {
            APP_LOG_DEBUG("Get New Alert information.");
            ctrl_pt.cmd_id = ANS_C_CTRL_PT_NTF_NEW_INC_ALERT_IMME;
            ctrl_pt.cat_id = ANS_C_CAT_ID_ALL;
            ans_c_ctrl_point_set(0, &ctrl_pt);
        }
        else if (APP_KEY_DOUBLE_CLICK == key_click_type)
        {
            APP_LOG_DEBUG("Get Unread Alert information.");
            ctrl_pt.cmd_id = ANS_C_CTRL_PT_NTF_UNREAD_CAT_STA_IMME;
            ctrl_pt.cat_id = ANS_C_CAT_ID_ALL;
            ans_c_ctrl_point_set(0, &ctrl_pt);
        }
        else if (APP_KEY_LONG_CLICK == key_click_type)
        {
            if (0 == s_ctrl_point_exchange)
            {
                APP_LOG_DEBUG("Enable all new alert category notify.");
                ctrl_pt.cmd_id = ANS_C_CTRL_PT_EN_NEW_INC_ALERT_NTF;
                ctrl_pt.cat_id = ANS_C_CAT_ID_ALL;
                ans_c_ctrl_point_set(0, &ctrl_pt);
                s_ctrl_point_exchange++;
            }
            else if (1 == s_ctrl_point_exchange)
            {
                APP_LOG_DEBUG("Enable all unread alert category notify.");
                ctrl_pt.cmd_id = ANS_C_CTRL_PT_EN_UNREAD_CAT_STA_NTF;
                ctrl_pt.cat_id = ANS_C_CAT_ID_ALL;
                ans_c_ctrl_point_set(0, &ctrl_pt);
                s_ctrl_point_exchange--;
            }
        }
    }
}

void app_periph_init(void)
{
    SYS_SET_BD_ADDR(s_bd_addr);
    board_init();
    pwr_mgmt_mode_set(PMR_MGMT_SLEEP_MODE);
}



