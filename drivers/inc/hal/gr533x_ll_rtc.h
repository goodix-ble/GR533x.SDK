/**
 ****************************************************************************************
 *
 * @file    gr533x_ll_rtc.h
 * @author  BLE Driver Team
 * @brief   Header file containing functions prototypes of RTC LL library.
 *
 ****************************************************************************************
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
 ****************************************************************************************
 */

/** @addtogroup PERIPHERAL Peripheral Driver
  * @{
  */

/** @addtogroup LL_DRIVER LL Driver
  * @{
  */

/** @defgroup LL_RTC RTC
  * @brief RTC LL module driver.
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR533X_LL_RTC_H__
#define __GR533X_LL_RTC_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gr533x.h"

/**
  * @defgroup RTC_LL_MACRO Defines
  * @{
  */
/* Exported constants --------------------------------------------------------*/
/** @defgroup RTC_LL_Exported_Constants RTC Exported Constants
  * @{
  */
/** @defgroup RTC_LL_EC_CLOCK_DIV Clock divider
  * @{
  */
#define LL_RTC_DIV_NONE                 ((uint32_t)0x00U)                                   /**< Select SLP_CLK       */
#define LL_RTC_DIV_2                    ((uint32_t)0x01U << RTC_CFG1_DIV_Pos)               /**< Select 1/32 divider  */
#define LL_RTC_DIV_4                    ((uint32_t)0x02U << RTC_CFG1_DIV_Pos)               /**< Select 1/32 divider  */
#define LL_RTC_DIV_8                    ((uint32_t)0x03U << RTC_CFG1_DIV_Pos)               /**< Select 1/32 divider  */
#define LL_RTC_DIV_16                   ((uint32_t)0x04U << RTC_CFG1_DIV_Pos)               /**< Select 1/32 divider  */
#define LL_RTC_DIV_32                   ((uint32_t)0x05U << RTC_CFG1_DIV_Pos)               /**< Select 1/64 divider  */
#define LL_RTC_DIV_64                   ((uint32_t)0x06U << RTC_CFG1_DIV_Pos)               /**< Select 1/128 divider */
#define LL_RTC_DIV_128                  ((uint32_t)0x07U << RTC_CFG1_DIV_Pos)               /**< Select 1/256 divider */
/** @} */

/** @defgroup AON_CTL_RTC_TIMER_PERIODIC_SEL  RTC Periodic timer select defines
 * @{
 */
#define LL_RTC_TIMER_TICK_TYPE_SINGLE   (0x0U)                                              /**< Select periodic alarm one-time     */
#define LL_RTC_TIMER_TICK_TYPE_AUTO     (0x1U)                                              /**< Select periodic alarm auto-reload  */
/** @} */

/** @defgroup RTC_READ_CONFIG  RTC CFG0 register read defines
 * @{
 */
/**
  * @brief LL RTC Read CFG
  */
#define   READ_CFG0_CFG(RTCx)           (READ_BITS(RTCx->CFG0, RTC_CFG0_EN | \
                                            RTC_CFG0_ALARM_EN | \
                                            RTC_CFG0_TICK_EN | \
                                            RTC_CFG0_TICK_MDOE))
/** @} */

/** @} */

/** @} */

/* Exported functions --------------------------------------------------------*/
/** @defgroup RTC_LL_DRIVER_FUNCTIONS Functions
  * @{
  */

/** @defgroup RTC_LL_EF_Configuration Configuration functions
  * @{
  */

/**
  * @brief  Enable RTC counter.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_CFG0 | EN
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_enable(rtc_regs_t* RTCx)
{
    WRITE_REG(RTCx->CFG0, RTC_CFG0_CFG | RTC_CFG0_EN);
}

/**
  * @brief  Disable RTC counter.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_CFG0 | EN
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_disable(rtc_regs_t* RTCx)
{
    MODIFY_REG(RTCx->CFG0, 0xFFFFFFFF, RTC_CFG0_CFG);
}

/**
  * @brief  Check if the RTC peripheral is enabled or disabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_CFG0 | EN
  *
  * @param RTCx RTC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_rtc_is_enabled(rtc_regs_t* RTCx)
{
    return (READ_BITS(RTCx->CFG0, RTC_CFG0_EN) == RTC_CFG0_EN);
}

/**
  * @brief  Reloads RTC counter.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_W | TIMER_VALUE
  *
  * @param RTCx RTC instance
  * @param counter RTC counter
  * @retval None
  */
__STATIC_INLINE void ll_rtc_reload_counter(rtc_regs_t* RTCx, uint32_t counter)
{
    WRITE_REG(RTCx->TIMER_W, counter);
}

/**
  * @brief  Reloads RTC counter and request.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_W | TIMER_VALUE
  *  RTC_CFG0 | VAL_LOAD
  *
  * @param RTCx RTC instance
  * @param start_value RTC counter
  * @retval None
  */
__STATIC_INLINE void ll_rtc_start_value_set_and_request(rtc_regs_t* RTCx, uint32_t start_value)
{
    WRITE_REG(RTCx->TIMER_W, start_value);
    WRITE_REG(RTCx->CFG0, RTC_CFG0_CFG | RTC_CFG0_TIMER_SET | (READ_CFG0_CFG(RTCx)));
}

/**
  * @brief  Reloads RTC alarm.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_W | ALARM_VAL_LOAD
  *
  * @param RTCx RTC instance
  * @param value RTC alarm value
  * @retval None
  */
__STATIC_INLINE void ll_rtc_reload_alarm(rtc_regs_t* RTCx, uint32_t value)
{
    WRITE_REG(RTCx->ALARM_W, value);
}

/**
  * @brief  Reloads RTC alarm and request.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_ALARM_W | ALARM_VAL_LOAD
  *  RTC_CFG0 | ALARM_VALUE
  *
  * @param RTCx RTC instance
  * @param alarm_value RTC alarm value
  * @retval None
  */
__STATIC_INLINE void ll_rtc_alarm_value_set_and_request(rtc_regs_t* RTCx, uint32_t alarm_value)
{
    WRITE_REG(RTCx->ALARM_W, alarm_value);
    WRITE_REG(RTCx->CFG0, RTC_CFG0_CFG | RTC_CFG0_ALARM_SET | (READ_CFG0_CFG(RTCx)));
}

/**
  * @brief  Reloads RTC perd_alarm.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_W | ALARM_VAL_LOAD
  *
  * @param RTCx RTC instance
  * @param tick RTC tick value
  * @retval None
  */
__STATIC_INLINE void ll_rtc_reload_tick(rtc_regs_t* RTCx, uint32_t tick)
{
    WRITE_REG(RTCx->TICK_W, tick);
}

/**
  * @brief  Reloads RTC tick and request.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TICK_W | TICK_VAL_LOAD
  *  RTC_CFG0 | TICK_VALUE
  *
  * @param RTCx RTC instance
  * @param alarm_value RTC tick value
  * @retval None
  */
__STATIC_INLINE void ll_rtc_tick_value_set_and_request(rtc_regs_t* RTCx, uint32_t alarm_value)
{
    WRITE_REG(RTCx->ALARM_W, alarm_value);
    WRITE_REG(RTCx->CFG0, RTC_CFG0_CFG | RTC_CFG0_TICK_SET | (READ_CFG0_CFG(RTCx)));
}

/**
  * @brief  Read the RTC counter config value.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_W | TIMER_VAL_READ
  *
  * @param RTCx RTC instance
  * @retval Value for current counter which should ranging between 0 ~ 0xFFFF_FFFF
  */
__STATIC_INLINE uint32_t ll_rtc_get_write_counter(rtc_regs_t* RTCx)
{
    return (uint32_t)READ_REG(RTCx->TIMER_W);
}

/**
  * @brief  Read the RTC counter current value.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_R | TIMER_VAL_READ
  *
  * @param RTCx RTC instance
  * @retval Value for current counter which should ranging between 0 ~ 0xFFFF_FFFF
  */
__STATIC_INLINE uint32_t ll_rtc_get_read_counter(rtc_regs_t* RTCx)
{
    return (uint32_t)READ_REG(RTCx->TIMER_R);
}

/**
  * @brief  Read the RTC counter config alarm value.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_ALARM_W | CAL_ALARM
  *
  * @param RTCx RTC instance
  * @retval Value for current alarm which should ranging between 0 ~ 0xFFFF_FFFF
  */
__STATIC_INLINE uint32_t ll_rtc_get_write_alarm(rtc_regs_t* RTCx)
{
    return (uint32_t)READ_REG(RTCx->ALARM_W);
}

/**
  * @brief  Read the RTC counter current alarm value.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_ALARM_R | CAL_ALARM
  *
  * @param RTCx RTC instance
  * @retval Value for current alarm which should ranging between 0 ~ 0xFFFF_FFFF
  */
__STATIC_INLINE uint32_t ll_rtc_get_read_alarm(rtc_regs_t* RTCx)
{
    return (uint32_t)READ_REG(RTCx->ALARM_R);
}

/**
  * @brief  Read the RTC counter config tick value.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TICK_W | TICK_SET
  *
  * @param RTCx RTC instance
  * @retval Value for current tick which should ranging between 0 ~ 0xFFFF_FFFF
  */
__STATIC_INLINE uint32_t ll_rtc_get_write_tick(rtc_regs_t* RTCx)
{
    return (uint32_t)READ_REG(RTCx->TICK_W);
}

/**
  * @brief  Read the RTC counter current tick value.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TICK_R | TICK_RD
  *
  * @param RTCx RTC instance
  * @retval Value for current tick which should ranging between 0 ~ 0xFFFF_FFFF
  */
__STATIC_INLINE uint32_t ll_rtc_get_read_tick(rtc_regs_t* RTCx)
{
    return (uint32_t)READ_REG(RTCx->TICK_R);
}

/**
  * @brief  Get the RTC wrap-around value.
  * @note   The value should be read multiple times until get the same value in at least two reads.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_STAT | WRAP_CNT
  *
  * @param RTCx RTC instance
  * @retval Value between Min_Data=0 and Max_Data=0xF
  */
__STATIC_INLINE uint32_t ll_rtc_get_wrapcnt(rtc_regs_t* RTCx)
{
    return (uint32_t)(READ_BITS(RTCx->STAT, RTC_STAT_WRAP_CNT) >> RTC_STAT_WRAP_CNT_Pos);
}

/**
  * @brief  The RTC is busy.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_STAT | BUSY
  *
  * @param RTCx RTC instance
  * @retval Value between Min_Data=0 and Max_Data=0xF
  */
__STATIC_INLINE uint32_t ll_rtc_is_busy(rtc_regs_t* RTCx)
{
    return (uint32_t)(READ_BITS(RTCx->STAT, RTC_STAT_BUSY) == RTC_STAT_BUSY);
}

/**
  * @brief  The RTC is running.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_STAT | RUNNING
  *
  * @param RTCx RTC instance
  * @retval Value between Min_Data=0 and Max_Data=0xF
  */
__STATIC_INLINE uint32_t ll_rtc_is_running(rtc_regs_t* RTCx)
{
    return (uint32_t)(READ_BITS(RTCx->STAT, RTC_STAT_STAT) == RTC_STAT_STAT);
}

/**
  * @brief  CLear RTC wrap.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_CFG0 | Wrap counter clear
  *
  * @param RTCx RTC instance
  * @retval None
  */

__STATIC_INLINE void ll_rtc_clear_wrap_and_request(rtc_regs_t* RTCx)
{
    WRITE_REG(RTCx->CFG0, RTC_CFG0_CFG | RTC_CFG0_WRAP_CLR | (READ_CFG0_CFG(RTCx)));
}

/**
  * @brief  Select the RTC clock divider.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_CFG1 | CLK_SEL
  *
  * @param RTCx RTC instance
  * @param  div This parameter can be one of the following values:
  *         @arg @ref LL_RTC_DIV_NONE
  *         @arg @ref LL_RTC_DIV_2
  *         @arg @ref LL_RTC_DIV_4
  *         @arg @ref LL_RTC_DIV_8
  *         @arg @ref LL_RTC_DIV_16
  *         @arg @ref LL_RTC_DIV_32
  *         @arg @ref LL_RTC_DIV_64
  *         @arg @ref LL_RTC_DIV_128
  * @retval None
  */
__STATIC_INLINE void ll_rtc_set_clock_div(rtc_regs_t* RTCx, uint32_t div)
{
    MODIFY_REG(RTCx->CFG1, RTC_CFG1_DIV, div);
}

/**
  * @brief  Set RTC alarm.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_CTL | ALARM_EN
  *
  * @param RTCx RTC instance
  * @param value RTC alarm value
  * @retval None
  */
__STATIC_INLINE void ll_rtc_set_alarm(rtc_regs_t* RTCx, uint32_t value)
{
    WRITE_REG(RTCx->ALARM_W, value);
    WRITE_REG(RTCx->CFG0, RTC_CFG0_CFG | RTC_CFG0_ALARM_EN | RTC_CFG0_ALARM_SET | (READ_CFG0_CFG(RTCx)));
}

/**
  * @brief  Enable RTC alarm interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_CTL | ALARM_INT_EN
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_it_enable_alarm(rtc_regs_t* RTCx)
{
    SET_BITS(RTCx->INT_EN, RTC_INT_EN_ALARM);
}

/**
  * @brief  Disable RTC alarm.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_CTL | ALARM_DISBALE
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_disable_alarm(rtc_regs_t* RTCx)
{
    WRITE_REG(RTCx->CFG0, ((READ_CFG0_CFG(RTCx)) & (~RTC_CFG0_ALARM_EN) & (~RTC_CFG0_ALARM_SET)) | RTC_CFG0_CFG);
}

/**
  * @brief  Disable RTC alarm interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_INT_EN | ALARM_INT_EN
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_it_disable_alarm(rtc_regs_t* RTCx)
{
    CLEAR_BITS(RTCx->INT_EN, RTC_INT_EN_ALARM);
}

/**
  * @brief  Check if the RTC alarm interrupt is enabled or disabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_CTL | ALARM_INT_EN
  *
  * @param RTCx RTC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_rtc_it_is_enabled_alarm(rtc_regs_t* RTCx)
{
    return (uint32_t)((READ_BITS(RTCx->CFG0, RTC_CFG0_ALARM_EN) == RTC_CFG0_ALARM_EN) &&
                    (READ_BITS(RTCx->INT_EN, RTC_INT_EN_ALARM) == RTC_INT_EN_ALARM));
}

/**
  * @brief  Set RTCx alarm_mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTCx_TIMER_CTL | TICK_EN
  * 
  * @param RTCx RTC instance
  * @param  tick_mode This parameter can be a one of the following values:
  *         @arg @ref LL_RTC_TIMER_TICK_TYPE_SINGLE
  *         @arg @ref LL_RTC_TIMER_TICK_TYPE_AUTO
  * @retval None
*/
__STATIC_INLINE void ll_rtc_set_tick_mode(rtc_regs_t* RTCx, uint8_t tick_mode)
{
    if(0 == tick_mode)
    {
        CLEAR_BITS(RTCx->CFG0, ((~tick_mode) << RTC_CFG0_TICK_MDOE_Pos));
    }
    else
    {
        SET_BITS(RTCx->CFG0, (tick_mode << RTC_CFG0_TICK_MDOE_Pos));
    }
}

/**
  * @brief  Enable RTC tick interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_INT_EN | TICK_INT_EN
  * 
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_it_enable_tick(rtc_regs_t* RTCx)
{
    SET_BITS(RTCx->INT_EN, RTC_INT_EN_TICK);
}

/**
  * @brief  Disable RTCx tick.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTCx_TIMER_CTL | TICK_EN
  * 
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_disable_tick(rtc_regs_t* RTCx)
{
    WRITE_REG(RTCx->CFG0, ((READ_CFG0_CFG(RTCx)) & (~RTC_CFG0_TICK_EN) & (~RTC_CFG0_TICK_SET)) | RTC_CFG0_CFG);
}

/**
  * @brief  Disable RTC tick interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_INT_EN | TICK0_INT_EN
  * 
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_it_disable_tick(rtc_regs_t* RTCx)
{
    CLEAR_BITS(RTCx->INT_EN, RTC_INT_EN_TICK);
}

/**
  * @brief  Check if the RTC alarm interrupt is enabled or disabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_CTL | TICK_EN
  *  RTC_INT_EN | TICK_INT_EN
  * 
  * @param RTCx RTC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_rtc_it_is_enabled_tick(rtc_regs_t* RTCx)
{
    return (uint32_t)((READ_BITS(RTCx->CFG0, RTC_CFG0_TICK_EN) == RTC_CFG0_TICK_EN) &&
                    (READ_BITS(RTCx->INT_EN, RTC_INT_EN_TICK) == RTC_INT_EN_TICK));
}

/**
  * @brief  Reloads RTCx tick counter and request.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTCx_TIMER_W | TIMER_VALUE
  *  RTCx_CFG0 | VAL_LOAD
  * 
  * @param RTCx RTC instance
  * @param tick_reload RTC tick counter
  * @retval None
  */
__STATIC_INLINE void ll_rtc_reload_tick_and_request(rtc_regs_t* RTCx, uint32_t tick_reload)
{
    WRITE_REG(RTCx->TICK_W, tick_reload);
    WRITE_REG(RTCx->CFG0, RTC_CFG0_CFG | RTC_CFG0_TICK_EN| RTC_CFG0_TICK_SET | (READ_CFG0_CFG(RTCx)));
}

/**
  * @brief  Restart RTCx tick counter and request.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTCx_CFG0 | RTC_CFG0_TICK_EN
  * 
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_restart_tick(rtc_regs_t* RTCx)
{
    WRITE_REG(RTCx->CFG0, RTC_CFG0_CFG | RTC_CFG0_TICK_EN | (READ_CFG0_CFG(RTCx)));
}

/**
  * @brief  Enable RTC wrap interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_CTL | WRAP_INT_EN
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_it_enable_wrap(rtc_regs_t* RTCx)
{
    SET_BITS(RTCx->INT_EN, RTC_INT_EN_WRAP);
}

/**
  * @brief  Disable RTC wrap interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_CTL | WRAP_INT_EN
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_it_disable_wrap(rtc_regs_t* RTCx)
{
    CLEAR_BITS(RTCx->INT_EN, RTC_INT_EN_WRAP);
}

/**
  * @brief  Check if the RTC wrap interrupt is enabled or disabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_TIMER_CTL | WRAP_INT_EN
  *
  * @param RTCx RTC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_rtc_it_is_enabled_wrap(rtc_regs_t* RTCx)
{
    return (uint32_t)(READ_BITS(RTCx->INT_EN, RTC_INT_EN_WRAP) == RTC_INT_EN_WRAP);
}

/** @} */

/** @defgroup RTC_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Indicate if the RTC alarm event flag is set or not.
  * @note   This bit is set by hardware when the counter has reached alarm value.
  *         It can be cleared by writing 0 to this bit.
  *
  *  Register|BitsName
  *  --------|--------
  *  SLP_EVENT | RTC_TIMER_ALARM
  *
  * @param RTCx RTC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_rtc_is_active_flag_alarm(rtc_regs_t* RTCx)
{
    return (uint32_t)(READ_BITS(RTCx->INT_STAT, RTC_INT_STAT_ALARM) == RTC_INT_STAT_ALARM);
}

/**
  * @brief  Indicate if the RTC wrap event flag is set or not.
  * @note   This bit is set by hardware when the counter has overflow.
  *         It can be cleared by writing 0 to this bit.
  *
  *  Register|BitsName
  *  --------|--------
  *  SLP_EVENT | CALENDAR_TIMER_WRAP
  *
  * @param RTCx RTC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_rtc_is_active_flag_wrap(rtc_regs_t* RTCx)
{
    return (uint32_t)(READ_BITS(RTCx->INT_STAT, RTC_INT_STAT_WRAP) == RTC_INT_STAT_WRAP);
}

/**
  * @brief  Indicate if the RTC tick event flag is set or not.
  * @note   This bit is set by hardware when the counter has reached to 0.
  *         It can be cleared by writing 1 to this bit.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_INT_STAT | TICK_INT_STAT
  *
  * @param RTCx RTC instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_rtc_is_active_flag_tick(rtc_regs_t* RTCx)
{
    return (uint32_t)(READ_BITS(RTCx->INT_STAT, RTC_INT_STAT_TICK) == RTC_INT_STAT_TICK);
}

/**
  * @brief  Clear RTC alarm interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  SLP_EVENT| RTC_TIMER_ALARM
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_clear_flag_alarm(rtc_regs_t* RTCx)
{
    WRITE_REG(RTCx->INT_STAT, RTC_INT_STAT_ALARM);
}

/**
  * @brief  Clear RTC wrap interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  RTC_INT_STAT| RTC_TICK
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_clear_flag_wrap(rtc_regs_t* RTCx)
{
    WRITE_REG(RTCx->INT_STAT, RTC_INT_STAT_WRAP);
}

/**
  * @brief  Clear RTC tick interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  SLP_EVENT| RTC_TIMER_WRAP
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_clear_flag_tick(rtc_regs_t* RTCx)
{
    WRITE_REG(RTCx->INT_STAT, RTC_INT_STAT_TICK);
}

/**
  * @brief  Clear RTC interrupt event.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_MISC | AON_SLP_EVENT
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_clear_it_event(rtc_regs_t* RTCx)
{
    WRITE_REG(AON_CTL->AON_SLP_EVENT, ~AON_CTL_SLP_EVENT_RTC0);
}

/**
  * @brief  Clear RTC tick interrupt event.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_MISC | AON_SLP_EVENT
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_clear_tick_it_event(rtc_regs_t* RTCx)
{
    WRITE_REG(AON_CTL->AON_SLP_EVENT, ~AON_CTL_SLP_EVENT_RTC0);
}

/**
  * @brief  Enable RTC alarm wakeup interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_MISC | MCU_WAKEUP_CTRL
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_it_enable_wakeup_by_rtc(rtc_regs_t* RTCx)
{
    SET_BITS(AON_CTL->MCU_WAKEUP_CTRL, AON_CTL_MCU_WAKEUP_CTRL_RTC0);
}

/**
  * @brief  Disable RTC alarm wakeup interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_MISC | MCU_WAKEUP_CTRL
  *
  * @param RTCx RTC instance
  * @retval None
  */
__STATIC_INLINE void ll_rtc_it_disable_wakeup_by_rtc(rtc_regs_t* RTCx)
{
    CLEAR_BITS(AON_CTL->MCU_WAKEUP_CTRL, AON_CTL_MCU_WAKEUP_CTRL_RTC0);
}

/** @} */

/** @} */


#ifdef __cplusplus
}
#endif

#endif /* __GR55XX_LL_RTC_H__ */

/** @} */

/** @} */

/** @} */
