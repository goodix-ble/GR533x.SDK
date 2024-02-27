/**
 ****************************************************************************************
 *
 * @file    gr533x_ll_sleep_timer.h
 * @author  BLE Driver Team
 * @brief   Header file containing functions prototypes of sleep timer LL library.
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

/** @defgroup LL_AON_TIM AON_TIM
  * @brief AON TIMER LL module driver.
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR533x_LL_SLEEP_TIMER_H__
#define __GR533x_LL_SLEEP_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gr533x.h"

#if defined(AON_CTL)

/** @defgroup AON_CTL_SLP_TIMER_CFG_0_MODE  Sleep Timer Mode
 * @{
 */
#define SLP_TIMER_CFG0_CNT_SLP_ONLY                    (0x1U << SLP_TIMER_CFG0_COUNT_MODE_Pos)           /**< Sleep_timer cnt slp onlt mode */
#define SLP_TIMER_CFG0_CNT_ANY_CONDITION               (0x0U << SLP_TIMER_CFG0_COUNT_MODE_Pos)           /**< Sleep_timer cnt any condition mode */
#define SLP_TIMER_CFG0_SINGLE_MODE                     (0x1U << SLP_TIMER_CFG0_MODE_Pos)                 /**< Sleep_timer single mode */
#define SLP_TIMER_CFG0_AUTO_RELOAD                     (0x0U << SLP_TIMER_CFG0_MODE_Pos)                 /**< Sleep_timer auto reload mode */
#define LL_SLEEP_TIMER_SINGLE_MODE_0     (SLP_TIMER_CFG0_SINGLE_MODE | SLP_TIMER_CFG0_CNT_SLP_ONLY)      /**< Sleep_timer single mode 0 */
#define LL_SLEEP_TIMER_SINGLE_MODE_1     (SLP_TIMER_CFG0_SINGLE_MODE | SLP_TIMER_CFG0_CNT_ANY_CONDITION) /**< Sleep_timer single mode 1 */
#define LL_SLEEP_TIMER_AUTO_MODE         (SLP_TIMER_CFG0_AUTO_RELOAD | SLP_TIMER_CFG0_CNT_ANY_CONDITION) /**< Sleep_timer auto mode */

/** @} */

/* Exported functions --------------------------------------------------------*/
/** @defgroup SLEEP_TIMER_LL_DRIVER_FUNCTIONS Functions
  * @{
  */

/**
  * @brief  Set the 32 bits Sleep Timer Value to WakeUp the MCU from DeepSleep Mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  SLP_TIMER_VAL_W | AON_CTL_SLP_TIMER_VAL_W_32B
  *
  * @param  value  32 bits count value loaded into the 32bit_timer
  * @retval None
  */
__STATIC_INLINE void ll_sleep_timer_set_value(uint32_t value)
{
    WRITE_REG(SLP_TIMER->TIMER_W, value);
}

/**
  * @brief  Get the 32 bit Sleep Timer Value to WakeUp the MCU from DeepSleep Mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  SLP_TIMER_VAL_W | AON_CTL_SLP_TIMER_VAL_W_32B
  *
  * @retval 32 bit AON Timer Count Value
  */
__STATIC_INLINE uint32_t ll_sleep_timer_get_value(void)
{
    return READ_REG(SLP_TIMER->TIMER_W);
}

/**
  * @brief  Get the real internal value of the sleep timer.
  *
  *  Register|BitsName
  *  --------|--------
  *  SLP_TIMER_VAL_R | AON_CTL_SLP_TIMER_VAL_R_32B
  *
  * @retval 32 bit sleep Timer Count Value
  */
__STATIC_INLINE uint32_t ll_sleep_timer_get_read_value(void)
{
    return READ_REG(SLP_TIMER->TIMER_R);
}

/**
  * @brief  check the sleep timer runing state.
  *
  *  Register|BitsName
  *  --------|--------
  *  SLP_TIMER_STS | AON_CTL_SLP_TIMER_STAT_STATUS
  *
  * @retval runing state of sleep timer (1 or 0).
  */
__STATIC_INLINE uint32_t ll_sleep_timer_is_runing(void)
{
    return (uint32_t)(READ_BITS(SLP_TIMER->STAT, SLP_TIMER_STAT_STAT) == SLP_TIMER_STAT_STAT);
}

/**
  * @brief  check the sleep timer busy state.
  *
  *  Register|BitsName
  *  --------|--------
  *  SLP_TIMER_STS | AON_CTL_SLP_TIMER_STAT_BUSY
  *
  * @retval busy state of sleep timer (1 or 0).
  */
__STATIC_INLINE uint32_t ll_sleep_timer_is_busy(void)
{
    return (uint32_t)(READ_BITS(SLP_TIMER->STAT, SLP_TIMER_STAT_BUSY) == SLP_TIMER_STAT_BUSY);
}

/**
  * @brief  Set the Sleep Timer Work Mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  SLP_TIMER_CFG_0 | AON_CTL_SLP_TIMER_CFG_0_MODE
  *
  * @param  mode of Sleep Timer work
  * @retval None
  */
__STATIC_INLINE void ll_sleep_timer_set_mode(uint32_t mode)
{
    WRITE_REG(SLP_TIMER->CFG0, SLP_TIMER_CFG0_EN | SLP_TIMER_CFG0_VAL_SET | mode | SLP_TIMER_CFG0_CFG);
}
/**
  * @brief  disable sleep timer
  *
  *  Register|BitsName
  *  --------|--------
  *  SLP_TIMER_CFG_0 | AON_TIMER_SLEEP_TIMER_CFG0_EN
  *
  * @retval None
  */
__STATIC_INLINE void ll_sleep_timer_disable(void)
{
    MODIFY_REG(SLP_TIMER->CFG0, SLP_TIMER_CFG0_EN, SLP_TIMER_CFG0_CFG);
}

/**
  * @brief  clear wake up event by sleep timer
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_SLP_EVENT | AON_CTL_SLP_EVENT_TIMER
  *
  * @retval None
  */
__STATIC_INLINE void ll_sleep_timer_clear_sleep_event(void)
{
    WRITE_REG(AON_CTL->AON_SLP_EVENT, ~AON_CTL_SLP_EVENT_SLP_TIMER);
}

/** @} */

#endif /* defined(AON_CTL) */

#ifdef __cplusplus
}
#endif

#endif /* __GR533x_LL_SLEEP_TIMER_H__ */

/** @} */

/** @} */

/** @} */
