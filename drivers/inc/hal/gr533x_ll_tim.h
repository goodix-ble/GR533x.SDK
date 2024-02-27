/**
 ****************************************************************************************
 *
 * @file    gr533x_ll_tim.h
 * @author  BLE Driver Team
 * @brief   Header file containing functions prototypes of TIMER LL library.
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

/** @defgroup LL_TIMER TIMER
  * @brief TIMER LL module driver.
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR533X_LL_TIMER_H__
#define __GR533X_LL_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gr533x.h"

#if defined (TIMER0) || defined (TIMER1)

/** @defgroup TIMER_LL_STRUCTURES Structures
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup TIMER_LL_ES_INIT TIMER Exported init structures
  * @{
  */

/**
  * @brief  LL TIMER capture type Enumerations definition
  */
typedef enum
{
    LL_TIMER_CAPTURE_NONE             = 0x00,    /**< Set timer capture NONE                      */
    LL_TIMER_CAPTURE_FALLING          = 0x01,    /**< Set timer capture io falling edge           */
    LL_TIMER_CAPTURE_RISING           = 0x02,    /**< Set timer capture io rising edge            */
    LL_TIMER_CAPTURE_BOTH             = 0x03,    /**< Set timer capture io both edge              */
} ll_timer_capture_type_t;

/**
  * @brief  LL TIMER capture pin Enumerations definition
  */
typedef enum
{
    LL_TIMER_CAPTURE_IO0              = 0x00,    /**< capture IO0                                 */
    LL_TIMER_CAPTURE_IO1              = 0x01,    /**< capture IO1                                 */
    LL_TIMER_CAPTURE_IO2              = 0x02,    /**< capture IO2                                 */
    LL_TIMER_CAPTURE_IO3              = 0x03,    /**< capture IO3                                 */
    LL_TIMER_CAPTURE_IO4              = 0x04,    /**< capture IO4                                 */
    LL_TIMER_CAPTURE_IO5              = 0x05,    /**< capture IO5                                 */
    LL_TIMER_CAPTURE_IO6              = 0x06,    /**< capture IO6                                 */
    LL_TIMER_CAPTURE_IO7              = 0x07,    /**< capture IO7                                 */
    LL_TIMER_CAPTURE_IO8              = 0x08,    /**< capture IO8                                 */
    LL_TIMER_CAPTURE_IO9              = 0x09,    /**< capture IO9                                 */
    LL_TIMER_CAPTURE_IO10             = 0x0A,    /**< capture IO10                                */
    LL_TIMER_CAPTURE_IO11             = 0x0B,    /**< capture IO11                                */
    LL_TIMER_CAPTURE_IO12             = 0x0C,    /**< capture IO12                                */
    LL_TIMER_CAPTURE_IO13             = 0x0D,    /**< capture IO13                                */
    LL_TIMER_CAPTURE_IO14             = 0x0E,    /**< capture IO14                                */
    LL_TIMER_CAPTURE_IO15             = 0x0F,    /**< capture IO15                                */
    LL_TIMER_CAPTURE_IO16             = 0x10,    /**< capture IO16                                */
    LL_TIMER_CAPTURE_IO17             = 0x11,    /**< capture IO17                                */
    LL_TIMER_CAPTURE_IO18             = 0x12,    /**< capture IO18                                */
    LL_TIMER_CAPTURE_IO19             = 0x13,    /**< capture IO19                                */
    LL_TIMER_CAPTURE_IO20             = 0x14,    /**< capture IO20                                */
    LL_TIMER_CAPTURE_IO21             = 0x15,    /**< capture IO21                                */
    LL_TIMER_CAPTURE_IO22             = 0x16,    /**< capture IO22                                */
    LL_TIMER_CAPTURE_IO23             = 0x17,    /**< capture IO23                                */
    LL_TIMER_CAPTURE_IO24             = 0x18,    /**< capture IO24                                */
    LL_TIMER_CAPTURE_IO25             = 0x19,    /**< capture IO25                                */
    LL_TIMER_CAPTURE_IO26             = 0x1A,    /**< capture IO26                                */
    LL_TIMER_CAPTURE_IO27             = 0x1B,    /**< capture IO27                                */
    LL_TIMER_CAPTURE_IO28             = 0x1C,    /**< capture IO28                                */
    LL_TIMER_CAPTURE_IO29             = 0x1D,    /**< capture IO29                                */
    LL_TIMER_CAPTURE_IO30             = 0x1E,    /**< capture IO30                                */
    LL_TIMER_CAPTURE_IO31             = 0x1F,    /**< capture IO31                                */
} ll_timer_capture_pin_t;

/**
  * @brief LL TIMER capture channel Structure definition
  */
typedef struct _ll_timer_capture_channel_init
{
    ll_timer_capture_type_t  ll_edge_capture;                   /**< Specifies the edge caputre type. */
    ll_timer_capture_pin_t   ll_capture_pin;                    /**< Soecufies the capture io pin.    */
} ll_timer_capture_channel_init_t;

/**
  * @brief LL TIMER init Structure definition
  */
typedef struct _ll_timer_init_t
{
    uint32_t auto_reload;                                   /**< Specifies the auto reload value to be loaded into the active
                                                               Auto-Reload Register at the next update event.
                                                               This parameter must be a number between Min_Data=0x00000000 and Max_Data=0xFFFFFFFF.
                                                               Some timer instances may support 32 bits counters. In that case this parameter must be a number between 0x0000 and 0xFFFFFFFF.

                                                               This feature can be modified afterwards using unitary function @ref ll_timer_set_auto_reload().*/

    ll_timer_capture_channel_init_t  ll_capture_channel0;      /**< Capture channel0 config.         */
    ll_timer_capture_channel_init_t  ll_capture_channel1;      /**< Capture channel1 config.         */
    ll_timer_capture_channel_init_t  ll_capture_channel2;      /**< Capture channel2 config.         */
    ll_timer_capture_channel_init_t  ll_capture_channel3;      /**< Capture channel3 config.         */
} ll_timer_init_t;

/** @} */

/** @} */

/**
  * @defgroup  TIMER_LL_TIMER_MACRO Defines
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup TIMER_LL_Exported_Constants TIMER Exported Constants
  * @{
  */

/** @defgroup TIMER_LL_EC_DEFAULT_CONFIG InitStrcut default configuartion
  * @{
  */
/**
  * @brief LL TIMER InitStrcut default configuartion
  */
#define TIMER_DEFAULT_CONFIG                \
{                                         \
    .auto_reload = SystemCoreClock - 1,    \
}

/** @} */

/** @defgroup TIMER_INTSTAT identify
  * @{
  */
/**
  * @brief LL TIMER Interrupt source identify
  */
#define LL_TIMER_INTSTAT_COUNTDONE                      TIMER_COUNTDONE_INT_STAT         /**< COUNTDONE flag */
#define LL_TIMER_INTSTAT_CH0                            TIMER_CH0_INT_STAT               /**< CHANNEL0 flag  */
#define LL_TIMER_INTSTAT_CH1                            TIMER_CH1_INT_STAT               /**< CHANNEL1 flag  */
#define LL_TIMER_INTSTAT_CH2                            TIMER_CH2_INT_STAT               /**< CHANNEL2 flag  */
#define LL_TIMER_INTSTAT_CH3                            TIMER_CH3_INT_STAT               /**< CHANNEL3 flag  */
#define LL_TIMER_INTSTAT_BLEPULSE1                      TIMER_BLEPULSE1_INT_STAT         /**< BLE PULSE 1 flag  */
#define LL_TIMER_INTSTAT_BLEPULSE2                      TIMER_BLEPULSE2_INT_STAT         /**< BLE PULSE 2 flag  */
/** @} */

/** @} */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup TIMER_LL_Exported_Macros TIMER Exported Macros
  * @{
  */

/** @defgroup TIMER_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in TIMER register
  * @param  __instance__ TIMER instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_TIMER_WriteReg(__instance__, __REG__, __VALUE__)   WRITE_REG(__instance__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in TIMER register
  * @param  __instance__ TIMER instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_TIMER_ReadReg(__instance__, __REG__)               READ_REG(__instance__->__REG__)

/** @} */

/** @} */

/** @} */

/* Exported functions --------------------------------------------------------*/
/** @defgroup TIMER_LL_DRIVER_FUNCTIONS Functions
  * @{
  */

/** @defgroup TIMER_LL_EF_Configuration Configuration functions
  * @{
  */

/**
  * @brief  Enable timer counter.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_enable_counter(timer_regs_t *TIMERx)
{
    SET_BITS(TIMERx->CTRL, TIMER_CTRL_EN);
}

/**
  * @brief  Disable timer counter.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_disable_counter(timer_regs_t *TIMERx)
{
    CLEAR_BITS(TIMERx->CTRL, TIMER_CTRL_EN);
}

/**
  * @brief  Indicate whether the timer counter is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | EN
  *
  * @param  TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_timer_is_enabled_counter(timer_regs_t *TIMERx)
{
    return (READ_BITS(TIMERx->CTRL, TIMER_CTRL_EN) == (TIMER_CTRL_EN));
}

/**
  * @brief  Set the counter value.
  *
  *  Register|BitsName
  *  --------|--------
  *  VALUE | VALUE
  *
  * @param  TIMERx Timer instance
  * @param  counter Counter value (between Min_Data=0 and Max_Data=0xFFFFFFFF)
  * @retval None
  */
__STATIC_INLINE void ll_timer_set_counter(timer_regs_t *TIMERx, uint32_t counter)
{
    WRITE_REG(TIMERx->VALUE, counter);
}

/**
  * @brief  Get the counter value.
  *
  *  Register|BitsName
  *  --------|--------
  *  VALUE | VALUE
  *
  * @param  TIMERx Timer instance
  * @retval Counter value (between Min_Data=0 and Max_Data=0xFFFFFFFF)
  */
__STATIC_INLINE uint32_t ll_timer_get_counter(timer_regs_t *TIMERx)
{
    return (uint32_t)(READ_REG(TIMERx->VALUE));
}

/**
  * @brief  Set the auto-reload value.
  * @note   The counter is blocked while the auto-reload value is null.
  *
  *  Register|BitsName
  *  --------|--------
  *  RELOAD | RELOAD
  *
  * @param  TIMERx Timer instance
  * @param  auto_reload between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_timer_set_auto_reload(timer_regs_t *TIMERx, uint32_t auto_reload)
{
    WRITE_REG(TIMERx->RELOAD, auto_reload);
}

/**
  * @brief  Get the auto-reload value.
  *
  *  Register|BitsName
  *  --------|--------
  *  RELOAD | RELOAD
  *
  * @param  TIMERx Timer instance
  * @retval Auto-reload value
  */
__STATIC_INLINE uint32_t ll_timer_get_auto_reload(timer_regs_t *TIMERx)
{
    return (uint32_t)(READ_REG(TIMERx->RELOAD));
}

/** @} */

/** @defgroup TIM_LL_EF_IT_Management IT_Management
  * @{
  */

/**
  * @brief  Enable timer all interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_COUNTDONE_INT_EN | TIMER_CH0_INT_EN | TIMER_CH1_INT_EN | TIMER_CH2_INT_EN | TIMER_CH3_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_enable_all_it(timer_regs_t *TIMERx)
{
    SET_BITS(TIMERx->INTEN, TIMER_COUNTDONE_INT_EN | \
                            TIMER_CH0_INT_EN       | \
                            TIMER_CH1_INT_EN       | \
                            TIMER_CH2_INT_EN       | \
                            TIMER_CH3_INT_EN);
}

/**
  * @brief  Disable timer all interrput.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_COUNTDONE_INT_EN | TIMER_CH0_INT_EN | TIMER_CH1_INT_EN | TIMER_CH2_INT_EN | TIMER_CH3_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_disable_all_it(timer_regs_t *TIMERx)
{
    CLEAR_BITS(TIMERx->INTEN, TIMER_COUNTDONE_INT_EN | \
                              TIMER_CH0_INT_EN       | \
                              TIMER_CH1_INT_EN       | \
                              TIMER_CH2_INT_EN       | \
                              TIMER_CH3_INT_EN);
}

/**
  * @brief  Enable timer countdone interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_COUNTDONE_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_enable_countdone_it(timer_regs_t *TIMERx)
{
    SET_BITS(TIMERx->INTEN, TIMER_COUNTDONE_INT_EN);
}

/**
  * @brief  Disable timer countdone interrput.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_COUNTDONE_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_disable_countdone_it(timer_regs_t *TIMERx)
{
    CLEAR_BITS(TIMERx->INTEN, TIMER_COUNTDONE_INT_EN);
}

/**
  * @brief  Enable timer channel0 interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_CH0_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_enable_channel0_it(timer_regs_t *TIMERx)
{
    SET_BITS(TIMERx->INTEN, TIMER_CH0_INT_EN);
}

/**
  * @brief  Disable timer channel0 interrput.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_CH0_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_disable_channel0_it(timer_regs_t *TIMERx)
{
    CLEAR_BITS(TIMERx->INTEN, TIMER_CH0_INT_EN);
}

/**
  * @brief  Enable timer channel1 interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_CH1_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_enable_channel1_it(timer_regs_t *TIMERx)
{
    SET_BITS(TIMERx->INTEN, TIMER_CH1_INT_EN);
}

/**
  * @brief  Disable timer channel1 interrput.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_CH1_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_disable_channel1_it(timer_regs_t *TIMERx)
{
    CLEAR_BITS(TIMERx->INTEN, TIMER_CH1_INT_EN);
}

/**
  * @brief  Enable timer channel2 interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_CH2_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_enable_channel2_it(timer_regs_t *TIMERx)
{
    SET_BITS(TIMERx->INTEN, TIMER_CH2_INT_EN);
}

/**
  * @brief  Disable timer channel2 interrput.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_CH2_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_disable_channel2_it(timer_regs_t *TIMERx)
{
    CLEAR_BITS(TIMERx->INTEN, TIMER_CH2_INT_EN);
}

/**
  * @brief  Enable timer channel3 interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_CH3_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_enable_channel3_it(timer_regs_t *TIMERx)
{
    SET_BITS(TIMERx->INTEN, TIMER_CH3_INT_EN);
}

/**
  * @brief  Disable timer channel3 interrput.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_CH3_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_disable_channel3_it(timer_regs_t *TIMERx)
{
    CLEAR_BITS(TIMERx->INTEN, TIMER_CH3_INT_EN);
}

/**
  * @brief  Enable timer ble pulse 1 interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_BLEPULSE1_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_enable_blepulse1_it(timer_regs_t *TIMERx)
{
    SET_BITS(TIMERx->INTEN, TIMER_BLEPULSE1_INT_EN);
}

/**
  * @brief  Disable timer ble pulse 1 interrput.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_BLEPULSE1_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_disable_blepulse1_it(timer_regs_t *TIMERx)
{
    CLEAR_BITS(TIMERx->INTEN, TIMER_BLEPULSE1_INT_EN);
}

/**
  * @brief  Enable timer ble pulse 2 interrupt.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_BLEPULSE2_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_enable_blepulse2_it(timer_regs_t *TIMERx)
{
    SET_BITS(TIMERx->INTEN, TIMER_BLEPULSE2_INT_EN);
}

/**
  * @brief  Disable timer ble pulse 2 interrput.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTEN | TIMER_BLEPULSE2_INT_EN
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_disable_blepulse2_it(timer_regs_t *TIMERx)
{
    CLEAR_BITS(TIMERx->INTEN, TIMER_BLEPULSE2_INT_EN);
}

/**
  * @brief  Indicate whether the timer interrput is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | INTEN
  *
  * @param  TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_timer_is_enabled_it(timer_regs_t *TIMERx)
{
    return (READ_BITS(TIMERx->INTEN, TIMER_COUNTDONE_INT_EN) >> TIMER_COUNTDONE_INT_EN_Pos | \
            READ_BITS(TIMERx->INTEN, TIMER_CH0_INT_EN) >> TIMER_CH0_INT_EN_Pos             | \
            READ_BITS(TIMERx->INTEN, TIMER_CH1_INT_EN) >> TIMER_CH1_INT_EN_Pos             | \
            READ_BITS(TIMERx->INTEN, TIMER_CH2_INT_EN) >> TIMER_CH2_INT_EN_Pos             | \
            READ_BITS(TIMERx->INTEN, TIMER_CH3_INT_EN) >> TIMER_CH3_INT_EN_Pos);
}
/** @} */

/** @defgroup TIM_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Clear the COUNTDONE interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | INTSTAT
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_clear_countdone_flag_it(timer_regs_t *TIMERx)
{
    WRITE_REG(TIMERx->INTSTAT, TIMER_COUNTDONE_INT_STAT);
}

/**
  * @brief  Clear the CHANNEL0 interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | INTSTAT
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_clear_channel0_flag_it(timer_regs_t *TIMERx)
{
    WRITE_REG(TIMERx->INTSTAT, TIMER_CH0_INT_STAT);
}

/**
  * @brief  Clear the CHANNEL1 interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | INTSTAT
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_clear_channel1_flag_it(timer_regs_t *TIMERx)
{
    WRITE_REG(TIMERx->INTSTAT, TIMER_CH1_INT_STAT);
}

/**
  * @brief  Clear the CHANNEL2 interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | INTSTAT
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_clear_channel2_flag_it(timer_regs_t *TIMERx)
{
    WRITE_REG(TIMERx->INTSTAT, TIMER_CH2_INT_STAT);
}

/**
  * @brief  Clear the CHANNEL3 interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | INTSTAT
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_clear_channel3_flag_it(timer_regs_t *TIMERx)
{
    WRITE_REG(TIMERx->INTSTAT, TIMER_CH3_INT_STAT);
}

/**
  * @brief  Clear the ble pulse 1 interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | INTSTAT
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_clear_blepulse1_flag_it(timer_regs_t *TIMERx)
{
    WRITE_REG(TIMERx->INTSTAT, TIMER_BLEPULSE1_INT_STAT);
}

/**
  * @brief  Clear the ble pulse 2 interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | INTSTAT
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_clear_blepulse2_flag_it(timer_regs_t *TIMERx)
{
    WRITE_REG(TIMERx->INTSTAT, TIMER_BLEPULSE2_INT_STAT);
}

/**
  * @brief  Clear the all interrupt flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | INTSTAT
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_clear_all_flag_it(timer_regs_t *TIMERx)
{
    WRITE_REG(TIMERx->INTSTAT, TIMER_INT_STAT);
}

/**
  * @brief  Indicate whether interrupt flag (INTSTAT) is set (interrupt is pending).
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | INTSTAT
  *
  * @param  TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_timer_is_active_flag_it(timer_regs_t *TIMERx)
{
    return (READ_BITS(TIMERx->INTSTAT, TIMER_INT_STAT) != TIMER_INT_STAT_Pos);
}

/** @} */

/** @defgroup TIM_LL_Init Initialization and de-initialization functions
  * @{
  */

/**
  * @brief  De-initialize TIMER registers (Registers restored to their default values).
  * @param  TIMERx TIMER instance
  * @retval An error_status_t enumeration value:
  *          - SUCCESS: TIMER registers are de-initialized
  *          - ERROR: TIMER registers are not de-initialized
  */
error_status_t ll_timer_deinit(timer_regs_t *TIMERx);

/**
  * @brief  Initialize TIMER registers according to the specified
  *         parameters in TIMER_InitStruct.
  * @param  TIMERx TIMER instance
  * @param  p_timer_init Pointer to a ll_timer_init_t structure that contains the configuration
  *                        information for the specified TIM peripheral.
  * @retval An error_status_t enumeration value:
  *          - SUCCESS: TIMER registers are initialized according to p_timer_init content
  *          - ERROR: Problem occurred during TIMER Registers initialization
  */
error_status_t ll_timer_init(timer_regs_t *TIMERx, ll_timer_init_t *p_timer_init);

/**
  * @brief Set each field of a @ref ll_timer_init_t type structure to default value.
  * @param p_timer_init  Pointer to a @ref ll_timer_init_t structure
  *                        whose fields will be set to default values.
  * @retval None
  */
void ll_timer_struct_init(ll_timer_init_t *p_timer_init);

/**
  * @brief  Set timer channel0 capture type.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH0_EDGE_DET
  *
  * @param  TIMERx Timer instance
  * @param  ll_edge_capture edge capture type
  * @retval None
  */
__STATIC_INLINE void ll_timer_set_channel0_capture_type(timer_regs_t *TIMERx, ll_timer_capture_type_t ll_edge_capture)
{
    MODIFY_REG(TIMERx->CTRL, TIMER_CH0_EDGE_DET, ll_edge_capture << TIMER_CH0_EDGE_DET_Pos);
}

/**
  * @brief  Get timer channel0 capture type.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH0_EDGE_DET
  *
  * @param  TIMERx Timer instance
  * @retval capture type of channel0
  */
__STATIC_INLINE ll_timer_capture_type_t ll_timer_get_channel0_capture_type(timer_regs_t *TIMERx)
{
    return (ll_timer_capture_type_t )(READ_BITS(TIMERx->CTRL, TIMER_CH0_EDGE_DET) >> TIMER_CH0_EDGE_DET_Pos);
}

/**
  * @brief  Set timer channel1 capture type.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH1_EDGE_DET
  *
  * @param  TIMERx Timer instance
  * @param  ll_edge_capture edge capture type
  * @retval None
  */
__STATIC_INLINE void ll_timer_set_channel1_capture_type(timer_regs_t *TIMERx, ll_timer_capture_type_t ll_edge_capture)
{
    MODIFY_REG(TIMERx->CTRL, TIMER_CH1_EDGE_DET, ll_edge_capture << TIMER_CH1_EDGE_DET_Pos);
}

/**
  * @brief  Get timer channel1 capture type.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH1_EDGE_DET
  *
  * @param  TIMERx Timer instance
  * @retval capture type of channel1
  */
__STATIC_INLINE ll_timer_capture_type_t ll_timer_get_channel1_capture_type(timer_regs_t *TIMERx)
{
    return (ll_timer_capture_type_t )(READ_BITS(TIMERx->CTRL, TIMER_CH1_EDGE_DET) >> TIMER_CH1_EDGE_DET_Pos);
}

/**
  * @brief  Set timer channel2 capture type.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH2_EDGE_DET
  *
  * @param  TIMERx Timer instance
  * @param  ll_edge_capture edge capture type
  * @retval None
  */
__STATIC_INLINE void ll_timer_set_channel2_capture_type(timer_regs_t *TIMERx, ll_timer_capture_type_t ll_edge_capture)
{
    MODIFY_REG(TIMERx->CTRL, TIMER_CH2_EDGE_DET, ll_edge_capture << TIMER_CH2_EDGE_DET_Pos);
}

/**
  * @brief  Get timer channel2 capture type.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH2_EDGE_DET
  *
  * @param  TIMERx Timer instance
  * @retval capture type of channel2
  */
__STATIC_INLINE ll_timer_capture_type_t ll_timer_get_channel2_capture_type(timer_regs_t *TIMERx)
{
    return (ll_timer_capture_type_t )(READ_BITS(TIMERx->CTRL, TIMER_CH2_EDGE_DET) >> TIMER_CH2_EDGE_DET_Pos);
}

/**
  * @brief  Set timer channel3 capture type.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH3_EDGE_DET
  *
  * @param  TIMERx Timer instance
  * @param  ll_edge_capture edge capture type
  * @retval None
  */
__STATIC_INLINE void ll_timer_set_channel3_capture_type(timer_regs_t *TIMERx, ll_timer_capture_type_t ll_edge_capture)
{
    MODIFY_REG(TIMERx->CTRL, TIMER_CH3_EDGE_DET, ll_edge_capture << TIMER_CH3_EDGE_DET_Pos);
}

/**
  * @brief  Get timer channel3 capture type.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH3_EDGE_DET
  *
  * @param  TIMERx Timer instance
  * @retval capture type of channel3
  */
__STATIC_INLINE ll_timer_capture_type_t ll_timer_get_channel3_capture_type(timer_regs_t *TIMERx)
{
    return (ll_timer_capture_type_t )(READ_BITS(TIMERx->CTRL, TIMER_CH3_EDGE_DET) >> TIMER_CH3_EDGE_DET_Pos);
}

/**
  * @brief  Set timer channel0 capture pin.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH0_PIN_SELECT
  *
  * @param  TIMERx Timer instance
  * @param  ll_capture_pin capture pin select
  * @retval None
  */
__STATIC_INLINE void ll_timer_set_channel0_capture_pin(timer_regs_t *TIMERx, ll_timer_capture_pin_t ll_capture_pin)
{
    MODIFY_REG(TIMERx->CTRL, TIMER_CH0_PIN_SELECT, ll_capture_pin << TIMER_CH0_PIN_SELECT_Pos);
}

/**
  * @brief  Get timer channel0 capture pin
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH0_PIN_SELECT
  *
  * @param  TIMERx Timer instance
  * @retval capture pin of channel0
  */
__STATIC_INLINE ll_timer_capture_pin_t ll_timer_get_channel0_capture_pin(timer_regs_t *TIMERx)
{
    return (ll_timer_capture_pin_t )(READ_BITS(TIMERx->CTRL, TIMER_CH0_PIN_SELECT) >> TIMER_CH0_PIN_SELECT_Pos);
}

/**
  * @brief  Set timer channel1 capture pin.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH1_PIN_SELECT
  *
  * @param  TIMERx Timer instance
  * @param  ll_capture_pin capture pin select
  * @retval None
  */
__STATIC_INLINE void ll_timer_set_channel1_capture_pin(timer_regs_t *TIMERx, ll_timer_capture_pin_t ll_capture_pin)
{
    MODIFY_REG(TIMERx->CTRL, TIMER_CH1_PIN_SELECT, ll_capture_pin << TIMER_CH1_PIN_SELECT_Pos);
}

/**
  * @brief  Get timer channel1 capture pin
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH1_PIN_SELECT
  *
  * @param  TIMERx Timer instance
  * @retval capture pin of channel1
  */
__STATIC_INLINE ll_timer_capture_pin_t ll_timer_get_channel1_capture_pin(timer_regs_t *TIMERx)
{
    return (ll_timer_capture_pin_t )(READ_BITS(TIMERx->CTRL, TIMER_CH1_PIN_SELECT) >> TIMER_CH1_PIN_SELECT_Pos);
}

/**
  * @brief  Set timer channel2 capture pin.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH2_PIN_SELECT
  *
  * @param  TIMERx Timer instance
  * @param  ll_capture_pin capture pin select
  * @retval None
  */
__STATIC_INLINE void ll_timer_set_channel2_capture_pin(timer_regs_t *TIMERx, ll_timer_capture_pin_t ll_capture_pin)
{
    MODIFY_REG(TIMERx->CTRL, TIMER_CH2_PIN_SELECT, ll_capture_pin << TIMER_CH2_PIN_SELECT_Pos);
}

/**
  * @brief  Get timer channel2 capture pin
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH2_PIN_SELECT
  *
  * @param  TIMERx Timer instance
  * @retval capture pin of channel2
  */
__STATIC_INLINE ll_timer_capture_pin_t ll_timer_get_channel2_capture_pin(timer_regs_t *TIMERx)
{
    return (ll_timer_capture_pin_t )(READ_BITS(TIMERx->CTRL, TIMER_CH2_PIN_SELECT) >> TIMER_CH2_PIN_SELECT_Pos);
}

/**
  * @brief  Set timer channel3 capture pin.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH3_PIN_SELECT
  *
  * @param  TIMERx Timer instance
  * @param  ll_capture_pin capture pin select
  * @retval None
  */
__STATIC_INLINE void ll_timer_set_channel3_capture_pin(timer_regs_t *TIMERx, ll_timer_capture_pin_t ll_capture_pin)
{
    MODIFY_REG(TIMERx->CTRL, TIMER_CH3_PIN_SELECT, ll_capture_pin << TIMER_CH3_PIN_SELECT_Pos);
}

/**
  * @brief  Get timer channel3 capture pin
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | TIMER_CH3_PIN_SELECT
  *
  * @param  TIMERx Timer instance
  * @retval capture pin of channel3
  */
__STATIC_INLINE ll_timer_capture_pin_t ll_timer_get_channel3_capture_pin(timer_regs_t *TIMERx)
{
    return (ll_timer_capture_pin_t )(READ_BITS(TIMERx->CTRL, TIMER_CH3_PIN_SELECT) >> TIMER_CH3_PIN_SELECT_Pos);
}

/**
  * @brief  Get timer interrupt flag
  *
  *  Register|BitsName
  *  --------|--------
  *  INTSTAT | COUNTDONE_INTSTAT/CHx_INTSTAT
  *
  * @param  TIMERx Timer instance
  * @retval interrupt flag
  */
__STATIC_INLINE uint32_t ll_timer_get_it_flag(timer_regs_t *TIMERx)
{
    return (uint32_t )(READ_BITS(TIMERx->INTSTAT, TIMER_INT_STAT));
}

/**
  * @brief  Get current value of channel0.
  *
  *  Register|BitsName
  *  --------|--------
  *  CHANNEL0_VAL | CHANNEL0_VAL
  *
  * @param  TIMERx Timer instance
  * @retval Current timer value
  */
__STATIC_INLINE uint32_t ll_timer_get_channel0_val(timer_regs_t *TIMERx)
{
    return (uint32_t )(READ_REG(TIMERx->CHANNEL0_VAL));
}

/**
  * @brief  Get current value of channel1.
  *
  *  Register|BitsName
  *  --------|--------
  *  CHANNEL1_VAL | CHANNEL1_VAL
  *
  * @param  TIMERx Timer instance
  * @retval Current timer value
  */
__STATIC_INLINE uint32_t ll_timer_get_channel1_val(timer_regs_t *TIMERx)
{
    return (uint32_t )(READ_REG(TIMERx->CHANNEL1_VAL));
}

/**
  * @brief  Get current value of channel2.
  *
  *  Register|BitsName
  *  --------|--------
  *  CHANNEL2_VAL | CHANNEL2_VAL
  *
  * @param  TIMERx Timer instance
  * @retval Current timer value
  */
__STATIC_INLINE uint32_t ll_timer_get_channel2_val(timer_regs_t *TIMERx)
{
    return (uint32_t )(READ_REG(TIMERx->CHANNEL2_VAL));
}

/**
  * @brief  Get current value of channel3.
  *
  *  Register|BitsName
  *  --------|--------
  *  CHANNEL3_VAL | CHANNEL3_VAL
  *
  * @param  TIMERx Timer instance
  * @retval Current timer value
  */
__STATIC_INLINE uint32_t ll_timer_get_channel3_val(timer_regs_t *TIMERx)
{
    return (uint32_t )(READ_REG(TIMERx->CHANNEL3_VAL));
}

/**
  * @brief  Enable timer BLE pulse.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | BLE_PULSE_CTRL
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_enable_ble_pulse(timer_regs_t *TIMERx)
{
    SET_BITS(TIMERx->CTRL, TIMER_BLE_PULSE_CTRL);
}

/**
  * @brief  Disable timer BLE pulse.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | BLE_PULSE_CTRL
  *
  * @param  TIMERx Timer instance
  * @retval None
  */
__STATIC_INLINE void ll_timer_disable_ble_pulse(timer_regs_t *TIMERx)
{
    CLEAR_BITS(TIMERx->CTRL, TIMER_BLE_PULSE_CTRL);
}

/**
  * @brief  Indicate whether the timer BLE pulse is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  CTRL | BLE_PULSE_CTRL
  *
  * @param  TIMERx Timer instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_timer_is_enabled_ble_pulse(timer_regs_t *TIMERx)
{
    return (READ_BITS(TIMERx->CTRL, TIMER_BLE_PULSE_CTRL) == (TIMER_BLE_PULSE_CTRL));
}

/**
  * @brief  Set the BLE count value1.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_COUNTVAL1 | BLE_VAL1
  *
  * @param  TIMERx Timer instance
  * @param  value count value between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_timer_set_BLE_val1(timer_regs_t *TIMERx, uint32_t value)
{
    WRITE_REG(TIMERx->BLE_COUNTVAL1, value);
}

/**
  * @brief  Get the BLE count value1.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_COUNTVAL1 | BLE_VAL1
  *
  * @param  TIMERx Timer instance
  * @retval BLE count value1
  */
__STATIC_INLINE uint32_t ll_timer_get_BLE_val1(timer_regs_t *TIMERx)
{
    return (uint32_t)(READ_REG(TIMERx->BLE_COUNTVAL1));
}

/**
  * @brief  Set the BLE count value2.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_COUNTVAL2 | BLE_VAL2
  *
  * @param  TIMERx Timer instance
  * @param  value count value between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_timer_set_BLE_val2(timer_regs_t *TIMERx, uint32_t value)
{
    WRITE_REG(TIMERx->BLE_COUNTVAL2, value);
}

/**
  * @brief  Get the BLE count value2.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_COUNTVAL2 | BLE_VAL2
  *
  * @param  TIMERx Timer instance
  * @retval BLE count value2
  */
__STATIC_INLINE uint32_t ll_timer_get_BLE_val2(timer_regs_t *TIMERx)
{
    return (uint32_t)(READ_REG(TIMERx->BLE_COUNTVAL2));
}

/**
  * @brief  Set the BLE pulse width.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PULSEWIDTH | BLE_PLS
  *
  * @param  TIMERx Timer instance
  * @param  width pulse width
  * @retval None
  */
__STATIC_INLINE void ll_timer_set_BLE_pulse_width(timer_regs_t *TIMERx, uint32_t width)
{
    MODIFY_REG(TIMERx->BLE_PULSEWIDTH, TIMER_BLE_PLS, width << TIMER_BLE_PLS_Pos);
}

/**
  * @brief  Get the BLE pulse width.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PULSEWIDTH | BLE_PLS
  *
  * @param  TIMERx Timer instance
  * @retval BLE pulse width
  */
__STATIC_INLINE uint32_t ll_timer_get_pulse_width(timer_regs_t *TIMERx)
{
    return (uint32_t)(READ_BITS(TIMERx->BLE_PULSEWIDTH, TIMER_BLE_PLS) >> TIMER_BLE_PLS_Pos);
}

/** @} */

/** @} */

#endif /* TIMER0 || TIMER1 */

#ifdef __cplusplus
}
#endif

#endif /* __GR533X_LL_TIMER_H__ */

/** @} */

/** @} */

/** @} */
