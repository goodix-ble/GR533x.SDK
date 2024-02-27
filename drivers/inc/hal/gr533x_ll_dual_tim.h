/**
 ****************************************************************************************
 *
 * @file    gr533x_ll_dual_tim.h
 * @author  BLE Driver Team
 * @brief   Header file containing functions prototypes of DUAL TIMER LL library.
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

/** @defgroup LL_DUAL_TIMER DUAL_TIMER
  * @brief DUAL TIM LL module driver.
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR533X_LL_DUAL_TIMER_H__
#define __GR533X_LL_DUAL_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gr533x.h"

#if defined (DUAL_TIMER0) || defined (DUAL_TIMER1)

/** @defgroup DUAL_TIMER_LL_STRUCTURES Structures
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup DUAL_TIMER_LL_ES_INIT DUAL_TIM Exported init structures
  * @{
  */

/**
  * @brief LL DUAL TIMER init Structure definition
  */
typedef struct _ll_dual_timer_init
{
    uint32_t prescaler;         /**< Specifies the prescaler value used to divide the TIMER clock.
                                   This parameter can be a value of @ref DUAL_TIMER_EC_LL_PRESCALER.

                                   This feature can be modified afterwards using unitary function @ref ll_dual_timer_set_prescaler().*/

    uint32_t counter_size;       /**< Specifies the prescaler value used to divide the DUAL_TIMER clock.
                                   This parameter can be a value of @ref DUAL_TIMER_EC_LL_COUNTERSIZE.

                                   This feature can be modified afterwards using unitary function @ref ll_dual_timer_set_counter_size().*/

    uint32_t counter_mode;       /**< Specifies the counter mode.
                                   This parameter can be a value of @ref DUAL_TIMER_LL_EC_COUNTERMODE.

                                   This feature can be modified afterwards using unitary function @ref ll_dual_timer_set_counter_mode().*/

    uint32_t auto_reload;        /**< Specifies the auto reload value to be loaded into the active
                                   Auto-Reload Register at the next update event.
                                   This parameter must be a number between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF.
                                   Some timer instances may support 16 bits counters. In that case this parameter must be a number between 0x0000 and 0xFFFF.

                                   This feature can be modified afterwards using unitary function @ref ll_dual_timer_set_auto_reload().*/
} ll_dual_timer_init_t;

/** @} */

/** @} */

/**
  * @defgroup  DUAL_TIMER_LL_MACRO Defines
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DUAL_TIMER_LL_Exported_Constants DUAL_TIM Exported Constants
  * @{
  */

/** @defgroup DUAL_TIMER_LL_EC_COUNTERMODE DUAL_TIM counter mode
  * @{
  */
#define LL_DUAL_TIMER_FREERUNNING_MODE        0x00000000U           /**< Free running mode */
#define LL_DUAL_TIMER_PERIODIC_MODE           DUAL_TIMER_CTRL_MODE    /**< Periodic mode */
/** @} */

/** @defgroup DUAL_TIMER_EC_LL_PRESCALER DUAL_TIM prescaler
  * @{
  */
#define LL_DUAL_TIMER_PRESCALER_DIV0          0x00000000U                     /**< 0 stage  of prescale, clock is divided by 1.   */
#define LL_DUAL_TIMER_PRESCALER_DIV16         (1UL << DUAL_TIMER_CTRL_PRE_Pos)  /**< 4 stages of prescale, clock is divided by 16.  */
#define LL_DUAL_TIMER_PRESCALER_DIV256        (2UL << DUAL_TIMER_CTRL_PRE_Pos)  /**< 8 stages of prescale, clock is divided by 256. */
/** @} */

/** @defgroup DUAL_TIMER_EC_LL_COUNTERSIZE DUAL_TIM counter size
  * @{
  */
#define LL_DUAL_TIMER_COUNTERSIZE_16          0x00000000U         /**< Counter size 16 bits */
#define LL_DUAL_TIMER_COUNTERSIZE_32          DUAL_TIMER_CTRL_SIZE  /**< Counter size 32 bits */
/** @} */

/** @defgroup DUAL_TIMER_EC_LL_IO_ACTION DUAL_TIM io action
  * @{
  */
#define LL_DUAL_TIMER_IO_ACTION_NONE          0x00000000U             /**< Do noting */
#define LL_DUAL_TIMER_IO_ACTION_SET           0x00000001U             /**< io set    */
#define LL_DUAL_TIMER_IO_ACTION_RESET         0x00000002U             /**< io reset  */
#define LL_DUAL_TIMER_IO_ACTION_TOGGLE        0x00000003U             /**< io toggle */
/** @} */

/** @defgroup DUAL_TIMER_EC_LL_IO_INIT DUAL_TIM io init
  * @{
  */
#define LL_DUAL_TIMER_IO_INIT_RESET           0x00000000U             /**< io init reset */
#define LL_DUAL_TIMER_IO_INIT_SET             0x00000001U             /**< io init set   */
/** @} */

/** @defgroup DUAL_TIMER_EC_LL_INTSTAT DUAL_TIM Interrupt source identify
  * @{
  */
#define LL_DUAL_TIMER_INTSTAT_COUNTDONE         DUAL_TIMER_ISR_TI              /**< COUNTDONE flag          */
#define LL_DUAL_TIMER_INTSTAT_ACT_START         DUAL_TIMER_INT_ACT_START       /**< Action Start flag       */
#define LL_DUAL_TIMER_INTSTAT_IOA_ACT_C1        DUAL_TIMER_INT_IOA_ACT_C1      /**< IOA Action Count 1 flag */
#define LL_DUAL_TIMER_INTSTAT_IOA_ACT_C2        DUAL_TIMER_INT_IOA_ACT_C2      /**< IOA Action Count 2 flag */
#define LL_DUAL_TIMER_INTSTAT_ACT_PERIOD        DUAL_TIMER_INT_ACT_PERIOD      /**< Action Period flag      */
#define LL_DUAL_TIMER_INTSTAT_ACT_STOP          DUAL_TIMER_INT_ACT_STOP        /**< Action Stop flag        */
#define LL_DUAL_TIMER_INTSTAT_IOB_ACT_C1        DUAL_TIMER_INT_IOB_ACT_C1      /**< IOB Action Count 1 flag */
#define LL_DUAL_TIMER_INTSTAT_IOB_ACT_C2        DUAL_TIMER_INT_IOB_ACT_C2      /**< IOB Action Count 2 flag */
#define LL_DUAL_TIMER_INTSTAT_IOC_ACT_C1        DUAL_TIMER_INT_IOC_ACT_C1      /**< IOC Action Count 1 flag */
#define LL_DUAL_TIMER_INTSTAT_IOC_ACT_C2        DUAL_TIMER_INT_IOC_ACT_C2      /**< IOC Action Count 2 flag */
#define LL_DUAL_TIMER_INTSTAT_BLEPULSE1         DUAL_TIMER_INT_BLEPULSE1       /**< BLE Pulse Count 1 flag  */
#define LL_DUAL_TIMER_INTSTAT_BLEPULSE2         DUAL_TIMER_INT_BLEPULSE2       /**< BLE Pulse Count 2 flag  */
/** @} */

/** @defgroup DUAL_TIMER_LL_EC_DEFAULT_CONFIG InitStrcut default configuartion
  * @{
  */

/**
  * @brief LL DUAL_TIMER InitStrcut default configuartion
  */
#define DUAL_TIMER_DEFAULT_CONFIG                     \
{                                                   \
    .prescaler   = LL_DUAL_TIMER_PRESCALER_DIV0,      \
    .counter_size = LL_DUAL_TIMER_COUNTERSIZE_32,      \
    .counter_mode = LL_DUAL_TIMER_PERIODIC_MODE,       \
    .auto_reload  = SystemCoreClock - 1,             \
}
/** @} */

/** @} */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup DUAL_TIMER_LL_Exported_Macros DUAL_TIM Exported Macros
  * @{
  */

/** @defgroup DUAL_TIMER_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in DUAL_TIMER register
  * @param  __instance__ DUAL_TIMER instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_DUAL_TIMER_WriteReg(__instance__, __REG__, __VALUE__)  WRITE_REG(__instance__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in DUAL_TIMER register
  * @param  __instance__ DUAL_TIMER instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_DUAL_TIMER_ReadReg(__instance__, __REG__)              READ_REG(__instance__->__REG__)

/** @} */

/** @} */

/** @} */

/* Exported functions --------------------------------------------------------*/
/** @defgroup DUAL_TIMER_LL_DRIVER_FUNCTIONS Functions
  * @{
  */

/** @defgroup DUAL_TIMER_LL_EF_Configuration Configuration functions
  * @{
  */


/**
  * @brief  Enable dual_timer counter.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | EN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_counter(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_EN);
}

/**
  * @brief  Disable dual_timer counter.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | EN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_counter(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_EN);
}

/**
  * @brief  Indicate whether the dual_timer counter is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | EN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_counter(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_EN) == (DUAL_TIMER_CTRL_EN));
}

/**
  * @brief  Set the counter mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | MODE
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  counter_mode This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_FREERUNNING_MODE
  *         @arg @ref LL_DUAL_TIMER_PERIODIC_MODE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_counter_mode(dual_timer_regs_t *DUAL_TIMERx, uint32_t counter_mode)
{
    MODIFY_REG(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_MODE, counter_mode);
}

/**
  * @brief  Get the counter mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | MODE
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_FREERUNNING_MODE
  *         @arg @ref LL_DUAL_TIMER_PERIODIC_MODE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_counter_mode(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_MODE));
}

/**
  * @brief  Set the prescaler.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | PRE
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  prescaler This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_PRESCALER_DIV0
  *         @arg @ref LL_DUAL_TIMER_PRESCALER_DIV16
  *         @arg @ref LL_DUAL_TIMER_PRESCALER_DIV256
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_prescaler(dual_timer_regs_t *DUAL_TIMERx, uint32_t prescaler)
{
    MODIFY_REG(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_PRE, prescaler);
}

/**
  * @brief  Get the prescaler.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | PRE
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_PRESCALER_DIV0
  *         @arg @ref LL_DUAL_TIMER_PRESCALER_DIV16
  *         @arg @ref LL_DUAL_TIMER_PRESCALER_DIV256
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_prescaler(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_PRE));
}

/**
  * @brief  Set the counter size.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | SIZE
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  counter_size This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_COUNTERSIZE_16
  *         @arg @ref LL_DUAL_TIMER_COUNTERSIZE_32
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_counter_size(dual_timer_regs_t *DUAL_TIMERx, uint32_t counter_size)
{
    MODIFY_REG(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_SIZE, counter_size);
}

/**
  * @brief  Get the counter size.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | SIZE
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_COUNTERSIZE_16
  *         @arg @ref LL_DUAL_TIMER_COUNTERSIZE_32
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_counter_size(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_SIZE));
}

/**
  * @brief  Enable one-shot mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | ONESHOT
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_oneshot(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_ONESHOT);
}

/**
  * @brief  Disable one-shot mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | ONESHOT
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_oneshot(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_ONESHOT);
}

/**
  * @brief  Indicate whether the one-shot mode is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | ONESHOT
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_oneshot(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_ONESHOT) == (DUAL_TIMER_CTRL_ONESHOT));
}

/**
  * @brief  Get the counter value.
  *
  *  Register|BitsName
  *  --------|--------
  *  VALUE | VALUE
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Counter value (between Min_Data=0 and Max_Data=0xFFFFFFFF)
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_counter(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)(READ_REG(DUAL_TIMERx->VALUE));
}

/**
  * @brief  Set the auto-reload value.
  * @note   The counter is blocked while the auto-reload value is null.
  *
  *  Register|BitsName
  *  --------|--------
  *  RELOAD | RELOAD
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  auto_reload between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_auto_reload(dual_timer_regs_t *DUAL_TIMERx, uint32_t auto_reload)
{
    WRITE_REG(DUAL_TIMERx->RELOAD, auto_reload);
}

/**
  * @brief  Get the auto-reload value.
  *
  *  Register|BitsName
  *  --------|--------
  *  RELOAD | RELOAD
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Auto-reload value
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_auto_reload(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)(READ_REG(DUAL_TIMERx->RELOAD));
}

/**
  * @brief  Set the backgroud-reload value.
  *
  *  Register|BitsName
  *  --------|--------
  *  BG_LOAD | BG_LOAD
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  background_reload between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_background_reload(dual_timer_regs_t *DUAL_TIMERx, uint32_t background_reload)
{
    WRITE_REG(DUAL_TIMERx->BG_LOAD, background_reload);
}

/**
  * @brief  Get the backgroud-reload value.
  *
  *  Register|BitsName
  *  --------|--------
  *  BG_LOAD | BG_LOAD
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_background_reload(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)(READ_REG(DUAL_TIMERx->BG_LOAD));
}

/**
  * @brief  Enable dual_timer IOA ctrl.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOA
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_ioa_ctrl(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOA);
}

/**
  * @brief  Disable dual_timer IOA ctrl.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOA
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_ioa_ctrl(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOA);
}

/**
  * @brief  Indicate whether the dual_timer IOA ctrl is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOA
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_ioa_ctrl(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOA) == (DUAL_TIMER_CTRL_IOA));
}

/**
  * @brief  Enable dual_timer IOB ctrl.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOB
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_iob_ctrl(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOB);
}

/**
  * @brief  Disable dual_timer IOB ctrl.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOB
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_iob_ctrl(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOB);
}

/**
  * @brief  Indicate whether the dual_timer IOB ctrl is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOB
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_iob_ctrl(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOB) == (DUAL_TIMER_CTRL_IOB));
}

/**
  * @brief  Enable dual_timer IOC ctrl.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOC
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_ioc_ctrl(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOC);
}

/**
  * @brief  Disable dual_timer IOC ctrl.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOC
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_ioc_ctrl(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOC);
}

/**
  * @brief  Indicate whether the dual_timer IOC ctrl is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOC
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_ioc_ctrl(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOC) == (DUAL_TIMER_CTRL_IOC));
}

/**
  * @brief  Enable dual_timer BLE ctrl.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | BLE
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_ble_ctrl(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_BLE);
}

/**
  * @brief  Disable dual_timer BLE ctrl.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | BLE
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_ble_ctrl(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_BLE);
}

/**
  * @brief  Indicate whether the dual_timer BLE ctrl is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | BLE
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_ble_ctrl(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_BLE) == (DUAL_TIMER_CTRL_BLE));
}

/**
  * @brief  Set the ioa count 1 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  COUNT_A1IO | COUNT_A1IO
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  count_value count 1 value between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioa_count1(dual_timer_regs_t *DUAL_TIMERx, uint32_t count_value)
{
    WRITE_REG(DUAL_TIMERx->COUNT_A1IO, count_value);
}

/**
  * @brief  Get the ioa count 1 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  COUNT_A1IO | COUNT_A1IO
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioa_count1(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)(READ_REG(DUAL_TIMERx->COUNT_A1IO));
}

/**
  * @brief  Set the ioa count 2 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  COUNT_A2IO | COUNT_A2IO
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  count_value count 2 value between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioa_count2(dual_timer_regs_t *DUAL_TIMERx, uint32_t count_value)
{
    WRITE_REG(DUAL_TIMERx->COUNT_A2IO, count_value);
}

/**
  * @brief  Get the ioa count 2 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  COUNT_A2IO | COUNT_A2IO
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioa_count2(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)(READ_REG(DUAL_TIMERx->COUNT_A2IO));
}

/**
  * @brief  Set the iob count 1 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  COUNT_B1IO | COUNT_B1IO
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  count_value count 1 value between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_iob_count1(dual_timer_regs_t *DUAL_TIMERx, uint32_t count_value)
{
    WRITE_REG(DUAL_TIMERx->COUNT_B1IO, count_value);
}

/**
  * @brief  Get the iob count 1 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  COUNT_B1IO | COUNT_B1IO
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_iob_count1(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)(READ_REG(DUAL_TIMERx->COUNT_B1IO));
}

/**
  * @brief  Set the iob count 2 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  COUNT_B2IO | COUNT_B2IO
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  count_value count 2 value between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_iob_count2(dual_timer_regs_t *DUAL_TIMERx, uint32_t count_value)
{
    WRITE_REG(DUAL_TIMERx->COUNT_B2IO, count_value);
}

/**
  * @brief  Get the iob count 2 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  COUNT_B2IO | COUNT_B2IO
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_iob_count2(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)(READ_REG(DUAL_TIMERx->COUNT_B2IO));
}

/**
  * @brief  Set the ioc count 1 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  COUNT_C1IO | COUNT_C1IO
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  count_value count 1 value between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioc_count1(dual_timer_regs_t *DUAL_TIMERx, uint32_t count_value)
{
    WRITE_REG(DUAL_TIMERx->COUNT_C1IO, count_value);
}

/**
  * @brief  Get the ioc count 1 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  COUNT_C1IO | COUNT_C1IO
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioc_count1(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)(READ_REG(DUAL_TIMERx->COUNT_C1IO));
}

/**
  * @brief  Set the ioc count 2 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  COUNT_C2IO | COUNT_C2IO
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  count_value count 2 value between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioc_count2(dual_timer_regs_t *DUAL_TIMERx, uint32_t count_value)
{
    WRITE_REG(DUAL_TIMERx->COUNT_C2IO, count_value);
}

/**
  * @brief  Get the ioc count 2 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  COUNT_C2IO | COUNT_C2IO
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioc_count2(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)(READ_REG(DUAL_TIMERx->COUNT_C2IO));
}

/**
  * @brief  Set ioa action when timer start.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOA_ACT_CTRL_START
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioa_action_start(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOA_ACT_CTRL_START, (action << DUAL_TIMER_IOA_ACT_CTRL_START_Pos));
}

/**
  * @brief  Get ioa action when timer start.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOA_ACT_CTRL_START
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioa_action_start(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOA_ACT_CTRL_START) >> DUAL_TIMER_IOA_ACT_CTRL_START_Pos));
}

/**
  * @brief  Set ioa action when value meets to COUNT_A1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOA_ACT_CTRL_C1
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioa_action_count1(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOA_ACT_CTRL_C1, (action << DUAL_TIMER_IOA_ACT_CTRL_C1_Pos));
}

/**
  * @brief  Get ioa action when value meets to COUNT_A1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOA_ACT_CTRL_C1
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioa_action_count1(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOA_ACT_CTRL_C1) >> DUAL_TIMER_IOA_ACT_CTRL_C1_Pos));
}

/**
  * @brief  Set ioa action when value meets to COUNT_A2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOA_ACT_CTRL_C2
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioa_action_count2(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOA_ACT_CTRL_C2, (action << DUAL_TIMER_IOA_ACT_CTRL_C2_Pos));
}

/**
  * @brief  Get ioa action when value meets to COUNT_A2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOA_ACT_CTRL_C2
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioa_action_count2(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOA_ACT_CTRL_C2) >> DUAL_TIMER_IOA_ACT_CTRL_C2_Pos));
}

/**
  * @brief  Set ioa action when value downs to 0.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOA_ACT_CTRL_PERIOD
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioa_action_period(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOA_ACT_CTRL_PERIOD, (action << DUAL_TIMER_IOA_ACT_CTRL_PERIOD_Pos));
}

/**
  * @brief  Get ioa action when value downs to 0.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOA_ACT_CTRL_PERIOD
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioa_action_period(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOA_ACT_CTRL_PERIOD) >> DUAL_TIMER_IOA_ACT_CTRL_PERIOD_Pos));
}

/**
  * @brief  Set ioa action when timer stop.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOA_ACT_CTRL_STOP
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioa_action_stop(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOA_ACT_CTRL_STOP, (action << DUAL_TIMER_IOA_ACT_CTRL_STOP_Pos));
}

/**
  * @brief  Get ioa action when timer stop.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOA_ACT_CTRL_STOP
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioa_action_stop(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOA_ACT_CTRL_STOP) >> DUAL_TIMER_IOA_ACT_CTRL_STOP_Pos));
}

/**
  * @brief  Set iob action when timer start.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOB_ACT_CTRL_START
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_iob_action_start(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOB_ACT_CTRL_START, (action << DUAL_TIMER_IOB_ACT_CTRL_START_Pos));
}

/**
  * @brief  Get iob action when timer start.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOB_ACT_CTRL_START
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_iob_action_start(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOB_ACT_CTRL_START) >> DUAL_TIMER_IOB_ACT_CTRL_START_Pos));
}

/**
  * @brief  Set iob action when value meets to COUNT_B1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOB_ACT_CTRL_C1
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_iob_action_count1(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOB_ACT_CTRL_C1, (action << DUAL_TIMER_IOB_ACT_CTRL_C1_Pos));
}

/**
  * @brief  Get iob action when value meets to COUNT_B1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOB_ACT_CTRL_C1
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_iob_action_count1(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOB_ACT_CTRL_C1) >> DUAL_TIMER_IOB_ACT_CTRL_C1_Pos));
}

/**
  * @brief  Set iob action when value meets to COUNT_B2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOB_ACT_CTRL_C2
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_iob_action_count2(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOB_ACT_CTRL_C2, (action << DUAL_TIMER_IOB_ACT_CTRL_C2_Pos));
}

/**
  * @brief  Get iob action when value meets to COUNT_B2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOB_ACT_CTRL_C2
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_iob_action_count2(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOB_ACT_CTRL_C2) >> DUAL_TIMER_IOB_ACT_CTRL_C2_Pos));
}

/**
  * @brief  Set iob action when value downs to 0.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOB_ACT_CTRL_PERIOD
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_iob_action_period(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOB_ACT_CTRL_PERIOD, (action << DUAL_TIMER_IOB_ACT_CTRL_PERIOD_Pos));
}

/**
  * @brief  Get iob action when value downs to 0.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOB_ACT_CTRL_PERIOD
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_iob_action_period(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOB_ACT_CTRL_PERIOD) >> DUAL_TIMER_IOB_ACT_CTRL_PERIOD_Pos));
}

/**
  * @brief  Set iob action when timer stop.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOB_ACT_CTRL_STOP
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_iob_action_stop(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOB_ACT_CTRL_STOP, (action << DUAL_TIMER_IOB_ACT_CTRL_STOP_Pos));
}

/**
  * @brief  Get iob action when timer stop.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOB_ACT_CTRL_STOP
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_iob_action_stop(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOB_ACT_CTRL_STOP) >> DUAL_TIMER_IOB_ACT_CTRL_STOP_Pos));
}

/**
  * @brief  Set ioc action when timer start.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOC_ACT_CTRL_START
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioc_action_start(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOC_ACT_CTRL_START, (action << DUAL_TIMER_IOC_ACT_CTRL_START_Pos));
}

/**
  * @brief  Get ioc action when timer start.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOC_ACT_CTRL_START
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioc_action_start(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOC_ACT_CTRL_START) >> DUAL_TIMER_IOC_ACT_CTRL_START_Pos));
}

/**
  * @brief  Set ioc action when value meets to COUNT_C1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOC_ACT_CTRL_C1
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioc_action_count1(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOC_ACT_CTRL_C1, (action << DUAL_TIMER_IOC_ACT_CTRL_C1_Pos));
}

/**
  * @brief  Get ioc action when value meets to COUNT_C1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOC_ACT_CTRL_C1
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioc_action_count1(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOC_ACT_CTRL_C1) >> DUAL_TIMER_IOC_ACT_CTRL_C1_Pos));
}

/**
  * @brief  Set ioc action when value meets to COUNT_C2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOC_ACT_CTRL_C2
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioc_action_count2(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOC_ACT_CTRL_C2, (action << DUAL_TIMER_IOC_ACT_CTRL_C2_Pos));
}

/**
  * @brief  Get ioc action when value meets to COUNT_C2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOC_ACT_CTRL_C2
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioc_action_count2(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOC_ACT_CTRL_C2) >> DUAL_TIMER_IOC_ACT_CTRL_C2_Pos));
}

/**
  * @brief  Set ioc action when value downs to 0.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOC_ACT_CTRL_PERIOD
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioc_action_period(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOC_ACT_CTRL_PERIOD, (action << DUAL_TIMER_IOC_ACT_CTRL_PERIOD_Pos));
}

/**
  * @brief  Get ioc action when value downs to 0.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOC_ACT_CTRL_PERIOD
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioc_action_period(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOC_ACT_CTRL_PERIOD) >> DUAL_TIMER_IOC_ACT_CTRL_PERIOD_Pos));
}

/**
  * @brief  Set ioc action when timer stop.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOC_ACT_CTRL_STOP
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  action This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioc_action_stop(dual_timer_regs_t *DUAL_TIMERx, uint32_t action)
{
    MODIFY_REG(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOC_ACT_CTRL_STOP, (action << DUAL_TIMER_IOC_ACT_CTRL_STOP_Pos));
}

/**
  * @brief  Get ioc action when timer stop.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_ACT_CTRL | IOC_ACT_CTRL_STOP
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_NONE
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_SET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_ACTION_TOGGLE
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioc_action_stop(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_ACT_CTRL, DUAL_TIMER_IOC_ACT_CTRL_STOP) >> DUAL_TIMER_IOC_ACT_CTRL_STOP_Pos));
}

/**
  * @brief  Set ioa initial vaule when DUAL_TIMER_CTRL_IOA is disable.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_INIT_SET | IOA_ACT_INIT
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_INIT_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_INIT_SET
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioa_action_init(dual_timer_regs_t *DUAL_TIMERx, uint32_t value)
{
    MODIFY_REG(DUAL_TIMERx->IO_INIT_SET, DUAL_TIMER_IOA_ACT_INIT, (value << DUAL_TIMER_IOA_ACT_INIT_Pos));
}

/**
  * @brief  Get ioa initial vaule.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_INIT_SET | IOA_ACT_INIT
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_INIT_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_INIT_SET
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioa_action_init(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_INIT_SET, DUAL_TIMER_IOA_ACT_INIT) >> DUAL_TIMER_IOA_ACT_INIT_Pos));
}

/**
  * @brief  Set iob initial vaule when DUAL_TIMER_CTRL_IOB is disable.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_INIT_SET | IOB_ACT_INIT
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_INIT_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_INIT_SET
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_iob_action_init(dual_timer_regs_t *DUAL_TIMERx, uint32_t value)
{
    MODIFY_REG(DUAL_TIMERx->IO_INIT_SET, DUAL_TIMER_IOB_ACT_INIT, (value << DUAL_TIMER_IOB_ACT_INIT_Pos));
}

/**
  * @brief  Get iob initial vaule.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_INIT_SET | IOB_ACT_INIT
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_INIT_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_INIT_SET
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_iob_action_init(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_INIT_SET, DUAL_TIMER_IOB_ACT_INIT) >> DUAL_TIMER_IOB_ACT_INIT_Pos));
}

/**
  * @brief  Set ioc initial vaule when DUAL_TIMER_CTRL_IOC is disable.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_INIT_SET | IOC_ACT_INIT
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  value This parameter can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_INIT_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_INIT_SET
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ioc_action_init(dual_timer_regs_t *DUAL_TIMERx, uint32_t value)
{
    MODIFY_REG(DUAL_TIMERx->IO_INIT_SET, DUAL_TIMER_IOC_ACT_INIT, (value << DUAL_TIMER_IOC_ACT_INIT_Pos));
}

/**
  * @brief  Get ioc initial vaule.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_INIT_SET | IOC_ACT_INIT
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_DUAL_TIMER_IO_INIT_RESET
  *         @arg @ref LL_DUAL_TIMER_IO_INIT_SET
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ioc_action_init(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->IO_INIT_SET, DUAL_TIMER_IOC_ACT_INIT) >> DUAL_TIMER_IOC_ACT_INIT_Pos));
}

/**
  * @brief  Set the one-time reload value.
  *
  *  Register|BitsName
  *  --------|--------
  *  TP_LOAD | TP_LOAD
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  onetime_reload between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_onetime_reload(dual_timer_regs_t *DUAL_TIMERx, uint32_t onetime_reload)
{
    WRITE_REG(DUAL_TIMERx->TP_LOAD, onetime_reload);
}

/**
  * @brief  Get the one-time reload value.
  *
  *  Register|BitsName
  *  --------|--------
  *  TP_LOAD | TP_LOAD
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_onetime_reload(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)(READ_REG(DUAL_TIMERx->TP_LOAD));
}

/**
  * @brief  Set the BLE count 1 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_COUNT1 | BLE_COUNT1
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  count_value count 1 value between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ble_count1(dual_timer_regs_t *DUAL_TIMERx, uint32_t count_value)
{
    WRITE_REG(DUAL_TIMERx->BLE_COUNT1, count_value);
}

/**
  * @brief  Get the BLE count 1 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_COUNT1 | BLE_COUNT1
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ble_count1(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)(READ_REG(DUAL_TIMERx->BLE_COUNT1));
}

/**
  * @brief  Set the BLE count 2 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_COUNT2 | BLE_COUNT2
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  count_value count 2 value between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ble_count2(dual_timer_regs_t *DUAL_TIMERx, uint32_t count_value)
{
    WRITE_REG(DUAL_TIMERx->BLE_COUNT2, count_value);
}

/**
  * @brief  Get the BLE count 2 value.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_COUNT2 | BLE_COUNT2
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ble_count2(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)(READ_REG(DUAL_TIMERx->BLE_COUNT2));
}

/**
  * @brief  Set the BLE pulse width.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PULSEWIDTH | BLE_PULSEWIDTH
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  width pulse width
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_ble_pulse_width(dual_timer_regs_t *DUAL_TIMERx, uint32_t width)
{
    MODIFY_REG(DUAL_TIMERx->BLE_PULSEWIDTH, DUAL_TIMER_BLE_PULSEWIDTH, (width << DUAL_TIMER_BLE_PULSEWIDTH_Pos));
}

/**
  * @brief  Get the BLE pulse width.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PULSEWIDTH | BLE_PULSEWIDTH
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval BLE pulse width
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_ble_pulse_width(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)((READ_BITS(DUAL_TIMERx->BLE_PULSEWIDTH, DUAL_TIMER_BLE_PULSEWIDTH) >> DUAL_TIMER_BLE_PULSEWIDTH_Pos));
}

/**
  * @brief  Set the period count in period mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  PERIOD_COUNT | PERIOD_COUNT
  *
  * @param  DUAL_TIMERx Timer instance
  * @param  count between Min_Data=2 and Max_Data=0xFFFF
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_set_period_count(dual_timer_regs_t *DUAL_TIMERx, uint32_t count)
{
    WRITE_REG(DUAL_TIMERx->PERIOD_COUNT, count);
}

/**
  * @brief  Get the period count in period mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  PERIOD_COUNT | PERIOD_COUNT
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval Return value between Min_Data=2 and Max_Data=0xFFFF
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_period_count(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t)(READ_REG(DUAL_TIMERx->PERIOD_COUNT));
}
/** @} */

/** @defgroup DUAL_TIM_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable dual_timer interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_it(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_INTEN);
}

/**
  * @brief  Disable dual_timer interrput.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_it(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_INTEN);
}

/**
  * @brief  Indicate whether the dual_timer interrput is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_INTEN) == (DUAL_TIMER_CTRL_INTEN));
}

/**
  * @brief  Enable dual_timer action interrupt when timer start.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | ACT_START_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_act_start_it(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_ACT_START_INTEN);
}

/**
  * @brief  Disable dual_timer action interrupt when timer start.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | ACT_START_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_act_start_it(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_ACT_START_INTEN);
}

/**
  * @brief  Indicate whether the dual_timer action interrupt when timer start is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | ACT_START_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_act_start_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_ACT_START_INTEN) == (DUAL_TIMER_CTRL_ACT_START_INTEN));
}

/**
  * @brief  Enable dual_timer action interrupt when timer value meets to COUNT_A1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOA_ACT_C1_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_ioa_act_c1_it(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOA_ACT_C1_INTEN);
}

/**
  * @brief  Disable dual_timer action interrupt when timer value meets to COUNT_A1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOA_ACT_C1_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_ioa_act_c1_it(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOA_ACT_C1_INTEN);
}

/**
  * @brief  Indicate whether the dual_timer action interrupt when timer value meets to COUNT_A1IO is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOA_ACT_C1_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_ioa_act_c1_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOA_ACT_C1_INTEN) == (DUAL_TIMER_CTRL_IOA_ACT_C1_INTEN));
}

/**
  * @brief  Enable dual_timer action interrupt when timer value meets to COUNT_A2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOA_ACT_C2_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_ioa_act_c2_it(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOA_ACT_C2_INTEN);
}

/**
  * @brief  Disable dual_timer action interrupt when timer value meets to COUNT_A2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOA_ACT_C2_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_ioa_act_c2_it(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOA_ACT_C2_INTEN);
}

/**
  * @brief  Indicate whether the dual_timer action interrupt when timer value meets to COUNT_A2IO is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOA_ACT_C2_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_ioa_act_c2_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOA_ACT_C2_INTEN) == (DUAL_TIMER_CTRL_IOA_ACT_C2_INTEN));
}

/**
  * @brief  Enable dual_timer action interrupt when timer value meets to 0.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | ACT_PERIOD_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_act_period_it(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_ACT_PERIOD_INTEN);
}

/**
  * @brief  Disable dual_timer action interrupt when timer value meets to 0.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | ACT_PERIOD_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_act_period_it(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_ACT_PERIOD_INTEN);
}

/**
  * @brief  Indicate whether the dual_timer action interrupt when timer value meets to 0 is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | ACT_PERIOD_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_act_period_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_ACT_PERIOD_INTEN) == (DUAL_TIMER_CTRL_ACT_PERIOD_INTEN));
}

/**
  * @brief  Enable dual_timer action interrupt when timer stop.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | ACT_STOP_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_act_stop_it(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_ACT_STOP_INTEN);
}

/**
  * @brief  Disable dual_timer action interrupt when timer stop.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | ACT_STOP_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_act_stop_it(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_ACT_STOP_INTEN);
}

/**
  * @brief  Indicate whether the dual_timer action interrupt when timer stop.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | ACT_STOP_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_act_stop_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_ACT_STOP_INTEN) == (DUAL_TIMER_CTRL_ACT_STOP_INTEN));
}

/**
  * @brief  Enable dual_timer action interrupt when timer value meets to COUNT_B1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOB_ACT_C1_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_iob_act_c1_it(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOB_ACT_C1_INTEN);
}

/**
  * @brief  Disable dual_timer action interrupt when timer value meets to COUNT_B1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOB_ACT_C1_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_iob_act_c1_it(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOB_ACT_C1_INTEN);
}

/**
  * @brief  Indicate whether the dual_timer action interrupt when timer value meets to COUNT_B1IO is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOB_ACT_C1_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_iob_act_c1_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOB_ACT_C1_INTEN) == (DUAL_TIMER_CTRL_IOB_ACT_C1_INTEN));
}

/**
  * @brief  Enable dual_timer action interrupt when timer value meets to COUNT_B2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOB_ACT_C2_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_iob_act_c2_it(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOB_ACT_C2_INTEN);
}

/**
  * @brief  Disable dual_timer action interrupt when timer value meets to COUNT_B2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOB_ACT_C2_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_iob_act_c2_it(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOB_ACT_C2_INTEN);
}

/**
  * @brief  Indicate whether the dual_timer action interrupt when timer value meets to COUNT_B2IO is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOB_ACT_C2_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_iob_act_c2_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOB_ACT_C2_INTEN) == (DUAL_TIMER_CTRL_IOB_ACT_C2_INTEN));
}

/**
  * @brief  Enable dual_timer action interrupt when timer value meets to COUNT_C1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOC_ACT_C1_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_ioc_act_c1_it(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOC_ACT_C1_INTEN);
}

/**
  * @brief  Disable dual_timer action interrupt when timer value meets to COUNT_C1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOC_ACT_C1_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_ioc_act_c1_it(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOC_ACT_C1_INTEN);
}

/**
  * @brief  Indicate whether the dual_timer action interrupt when timer value meets to COUNT_C1IO is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOC_ACT_C1_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_ioc_act_c1_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOC_ACT_C1_INTEN) == (DUAL_TIMER_CTRL_IOC_ACT_C1_INTEN));
}

/**
  * @brief  Enable dual_timer action interrupt when timer value meets to COUNT_C2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOC_ACT_C2_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_ioc_act_c2_it(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOC_ACT_C2_INTEN);
}

/**
  * @brief  Disable dual_timer action interrupt when timer value meets to COUNT_C2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOC_ACT_C2_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_ioc_act_c2_it(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOC_ACT_C2_INTEN);
}

/**
  * @brief  Indicate whether the dual_timer action interrupt when timer value meets to COUNT_C2IO is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | IOC_ACT_C2_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_ioc_act_c2_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_IOC_ACT_C2_INTEN) == (DUAL_TIMER_CTRL_IOC_ACT_C2_INTEN));
}

/**
  * @brief  Enable dual_timer interrupt when timer value meets to BLE_COUNT1.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | BLEPULSE1_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_ble_pulse1_it(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_BLEPULSE1_INTEN);
}

/**
  * @brief  Disable dual_timer interrupt when timer value meets to BLE_COUNT1.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | BLEPULSE1_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_ble_pulse1_it(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_BLEPULSE1_INTEN);
}

/**
  * @brief  Indicate whether the dual_timer interrupt when timer value meets to BLE_COUNT1 is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | BLEPULSE1_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_ble_pulse1_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_BLEPULSE1_INTEN) == (DUAL_TIMER_CTRL_BLEPULSE1_INTEN));
}

/**
  * @brief  Enable dual_timer interrupt when timer value meets to BLE_COUNT2.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | BLEPULSE2_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_enable_ble_pulse2_it(dual_timer_regs_t *DUAL_TIMERx)
{
    SET_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_BLEPULSE2_INTEN);
}

/**
  * @brief  Disable dual_timer interrupt when timer value meets to BLE_COUNT2.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | BLEPULSE2_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_disable_ble_pulse2_it(dual_timer_regs_t *DUAL_TIMERx)
{
    CLEAR_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_BLEPULSE2_INTEN);
}

/**
  * @brief  Indicate whether the dual_timer interrupt when timer value meets to BLE_COUNT2 is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | BLEPULSE2_INTEN
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_enabled_ble_pulse2_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->CTRL, DUAL_TIMER_CTRL_BLEPULSE2_INTEN) == (DUAL_TIMER_CTRL_BLEPULSE2_INTEN));
}
/** @} */

/** @defgroup DUAL_TIMER_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Clear the interrupt flag (INTSTAT).
  *

  *  Register|BitsName
  *  --------|--------
  *  INTCLR | INTCLR
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_clear_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    WRITE_REG(DUAL_TIMERx->INTCLR, DUAL_TIMER_INT_CLR);
}

/**
  * @brief  Indicate whether interrupt flag (INTSTAT) is set (interrupt is pending).
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | INTSTAT
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_active_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->INTSTAT, DUAL_TIMER_ISR_TI) == (DUAL_TIMER_ISR_TI));
}

/**
  * @brief  Get Dual_timer raw interrupt flags
  *
  *  Register|BitsName
  *  --------|--------
  *  RAW_INTSTAT | RAW_INTSTAT
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_raw_it_flag(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_REG(DUAL_TIMERx->RAW_INTSTAT));
}

/**
  * @brief  Get dual timer interrupt flag
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | INTSTAT
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval interrupt flag
  */
__STATIC_INLINE uint32_t ll_dual_timer_get_it_flag(dual_timer_regs_t *DUAL_TIMERx)
{
    return (uint32_t )(READ_BITS(DUAL_TIMERx->INTSTAT, DUAL_TIMER_INT_STAT));
}

/**
  * @brief  Indicate whether action interrupt flag is set when timer start.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | ACT_START
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_action_start_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->INTSTAT, DUAL_TIMER_INT_ACT_START) == (DUAL_TIMER_INT_ACT_START));
}

/**
  * @brief  Indicate whether action interrupt flag is set when timer value meets to COUNT_A1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | IOA_ACT_C1
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_ioa_action_c1_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->INTSTAT, DUAL_TIMER_INT_IOA_ACT_C1) == (DUAL_TIMER_INT_IOA_ACT_C1));
}

/**
  * @brief  Indicate whether action interrupt flag is set when timer value meets to COUNT_A2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | IOA_ACT_C2
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_ioa_action_c2_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->INTSTAT, DUAL_TIMER_INT_IOA_ACT_C2) == (DUAL_TIMER_INT_IOA_ACT_C2));
}

/**
  * @brief  Indicate whether action interrupt flag is set when timer value meets to 0.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | ACT_PERIOD
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_action_period_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->INTSTAT, DUAL_TIMER_INT_ACT_PERIOD) == (DUAL_TIMER_INT_ACT_PERIOD));
}

/**
  * @brief  Indicate whether action interrupt flag is set when timer stop.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | ACT_STOP
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_action_stop_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->INTSTAT, DUAL_TIMER_INT_ACT_STOP) == (DUAL_TIMER_INT_ACT_STOP));
}

/**
  * @brief  Indicate whether action interrupt flag is set when timer value meets to COUNT_B1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | IOB_ACT_C1
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_iob_action_c1_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->INTSTAT, DUAL_TIMER_INT_IOB_ACT_C1) == (DUAL_TIMER_INT_IOB_ACT_C1));
}

/**
  * @brief  Indicate whether action interrupt flag is set when timer value meets to COUNT_B2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | IOB_ACT_C2
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_iob_action_c2_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->INTSTAT, DUAL_TIMER_INT_IOB_ACT_C2) == (DUAL_TIMER_INT_IOB_ACT_C2));
}

/**
  * @brief  Indicate whether action interrupt flag is set when timer value meets to COUNT_C1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | IOC_ACT_C1
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_ioc_action_c1_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->INTSTAT, DUAL_TIMER_INT_IOC_ACT_C1) == (DUAL_TIMER_INT_IOC_ACT_C1));
}

/**
  * @brief  Indicate whether action interrupt flag is set when timer value meets to COUNT_C2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | IOC_ACT_C2
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_ioc_action_c2_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->INTSTAT, DUAL_TIMER_INT_IOC_ACT_C2) == (DUAL_TIMER_INT_IOC_ACT_C2));
}

/**
  * @brief  Indicate whether interrupt flag is set when timer value meets to BLE_COUNT1.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | BLEPULSE1
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_ble_pulse1_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->INTSTAT, DUAL_TIMER_INT_BLEPULSE1) == (DUAL_TIMER_INT_BLEPULSE1));
}

/**
  * @brief  Indicate whether interrupt flag is set when timer value meets to BLE_COUNT2.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | BLEPULSE2
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_dual_timer_is_ble_pulse2_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    return (READ_BITS(DUAL_TIMERx->INTSTAT, DUAL_TIMER_INT_BLEPULSE2) == (DUAL_TIMER_INT_BLEPULSE2));
}

/**
  * @brief  Clear the start action interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_BLE_INTCLR | ACT_START_INTCLR
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_clear_act_start_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    WRITE_REG(DUAL_TIMERx->IO_BLE_INTCLR, DUAL_TIMER_ACT_START_INTCLR);
}

/**
  * @brief  Clear the ioa action interrupt flag when timer value meets to COUNT_A1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_BLE_INTCLR | IOA_ACT_C1_INTCLR
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_clear_ioa_act_c1_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    WRITE_REG(DUAL_TIMERx->IO_BLE_INTCLR, DUAL_TIMER_IOA_ACT_C1_INTCLR);
}

/**
  * @brief  Clear the ioa action interrupt flag when timer value meets to COUNT_A2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_BLE_INTCLR | IOA_ACT_C2_INTCLR
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_clear_ioa_act_c2_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    WRITE_REG(DUAL_TIMERx->IO_BLE_INTCLR, DUAL_TIMER_IOA_ACT_C2_INTCLR);
}

/**
  * @brief  Clear the period action interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_BLE_INTCLR | ACT_PERIOD_INTCLR
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_clear_act_period_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    WRITE_REG(DUAL_TIMERx->IO_BLE_INTCLR, DUAL_TIMER_ACT_PERIOD_INTCLR);
}

/**
  * @brief  Clear the stop action interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_BLE_INTCLR | ACT_STOP_INTCLR
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_clear_act_stop_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    WRITE_REG(DUAL_TIMERx->IO_BLE_INTCLR, DUAL_TIMER_ACT_STOP_INTCLR);
}

/**
  * @brief  Clear the iob action interrupt flag when timer value meets to COUNT_B1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_BLE_INTCLR | IOB_ACT_C1_INTCLR
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_clear_iob_act_c1_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    WRITE_REG(DUAL_TIMERx->IO_BLE_INTCLR, DUAL_TIMER_IOB_ACT_C1_INTCLR);
}

/**
  * @brief  Clear the iob action interrupt flag when timer value meets to COUNT_B2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_BLE_INTCLR | IOB_ACT_C2_INTCLR
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_clear_iob_act_c2_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    WRITE_REG(DUAL_TIMERx->IO_BLE_INTCLR, DUAL_TIMER_IOB_ACT_C2_INTCLR);
}

/**
  * @brief  Clear the ioc action interrupt flag when timer value meets to COUNT_C1IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_BLE_INTCLR | IOC_ACT_C1_INTCLR
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_clear_ioc_act_c1_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    WRITE_REG(DUAL_TIMERx->IO_BLE_INTCLR, DUAL_TIMER_IOC_ACT_C1_INTCLR);
}

/**
  * @brief  Clear the ioc action interrupt flag when timer value meets to COUNT_C2IO.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_BLE_INTCLR | IOC_ACT_C2_INTCLR
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_clear_ioc_act_c2_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    WRITE_REG(DUAL_TIMERx->IO_BLE_INTCLR, DUAL_TIMER_IOC_ACT_C2_INTCLR);
}

/**
  * @brief  Clear the interrupt flag when timer value meets to BLE_COUNT1.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_BLE_INTCLR | BLEPULSE1_INTCLR
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_clear_ble_pulse1_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    WRITE_REG(DUAL_TIMERx->IO_BLE_INTCLR, DUAL_TIMER_BLEPULSE1_INTCLR);
}

/**
  * @brief  Clear the interrupt flag when timer value meets to BLE_COUNT2.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_BLE_INTCLR | BLEPULSE2_INTCLR
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_clear_ble_pulse2_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    WRITE_REG(DUAL_TIMERx->IO_BLE_INTCLR, DUAL_TIMER_BLEPULSE2_INTCLR);
}

/**
  * @brief  Clear all of the io action interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  IO_BLE_INTCLR | ACT_ALL_INTCLR
  *
  * @param  DUAL_TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_dual_timer_clear_act_all_flag_it(dual_timer_regs_t *DUAL_TIMERx)
{
    WRITE_REG(DUAL_TIMERx->IO_BLE_INTCLR, DUAL_TIMER_IO_ACT_ALL_INTCLR);
}
/** @} */

/** @defgroup DUAL_TIMER_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

/**
  * @brief  De-initialize DUAL_TIMER registers (Registers restored to their default values).
  * @param  DUAL_TIMERx DUAL_TIM instance
  * @retval An error_status_t enumeration value:
  *          - SUCCESS: DUAL_TIMER registers are de-initialized
  *          - ERROR: DUAL_TIMER registers are not de-initialized
  */
error_status_t ll_dual_timer_deinit(dual_timer_regs_t *DUAL_TIMERx);

/**
  * @brief  Initialize DUAL_TIMER registers according to the specified
  *         parameters in p_dual_timer_init.
  * @param  DUAL_TIMERx DUAL_TIMER instance
  * @param  p_dual_timer_init Pointer to a ll_dual_timer_init_t structure that contains the configuration
  *                         information for the specified DUAL_TIMER peripheral.
  * @retval An error_status_t enumeration value:
  *          - SUCCESS: DUAL_TIMER registers are initialized according to p_dual_timer_init content
  *          - ERROR: Problem occurred during DUAL_TIM Registers initialization
  */
error_status_t ll_dual_timer_init(dual_timer_regs_t *DUAL_TIMERx, ll_dual_timer_init_t *p_dual_timer_init);

/** @} */

/** @} */


#endif /* DUAL_TIMER0 || DUAL_TIMER1 */

#ifdef __cplusplus
}
#endif

#endif /* __GR533X_LL_DUAL_TIMER_H__ */

/** @} */

/** @} */

/** @} */
