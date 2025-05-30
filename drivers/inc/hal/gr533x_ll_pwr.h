/**
 ****************************************************************************************
 *
 * @file    gr533x_ll_pwr.h
 * @author  BLE Driver Team
 * @brief   Header file containing functions prototypes of PWR LL library.
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

/** @defgroup LL_PWR PWR
  * @brief PWR LL module driver.
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR533x_LL_PWR_H__
#define __GR533x_LL_PWR_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gr533x.h"

#if defined(AON_CTL) && defined(AON_IO)

/**
  * @defgroup  PWR_LL_MACRO Defines
  * @{
  */
/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_LL_EC_WAKEUP_COND  Wakeup Condition
  * @{
  */
#define LL_PWR_WKUP_COND_EXT                AON_CTL_MCU_WAKEUP_CTRL_EXT                         /**< External wakeup: AON_GPIO      */
#define LL_PWR_WKUP_COND_TIMER              AON_CTL_MCU_WAKEUP_CTRL_SLP_TIMER                   /**< AON Timer wakeup               */
#define LL_PWR_WKUP_COND_BLE                AON_CTL_MCU_WAKEUP_CTRL_SMS_OSC                     /**< BLE wakeup                     */
#define LL_PWR_WKUP_COND_CLDR               AON_CTL_MCU_WAKEUP_CTRL_RTC0                        /**< RTC0 wakeup                    */
#define LL_PWR_WKUP_COND_AON_WDT            AON_CTL_MCU_WAKEUP_CTRL_AON_WDT                     /**< AON WDT reahch 0 wakeup        */
#define LL_PWR_WKUP_COND_COMP_RISE          AON_CTL_MCU_WAKEUP_CTRL_COMP_RISE                   /**< COMP rise wakeup               */
#define LL_PWR_WKUP_COND_COMP_FALL          AON_CTL_MCU_WAKEUP_CTRL_COMP_FALL                   /**< COMP fall wakeup               */
#define LL_PWR_WKUP_COND_ALL                AON_CTL_WAKEUP_CTRL_SEL                             /**< All wakeup sources mask        */

/** @} */

/** @defgroup PWR_LL_EC_WAKEUP_EVT Wakeup Event
  * @{
  */
#define LL_PWR_WKUP_EVENT_BLE               AON_CTL_SLP_EVENT_SMS_OSC                           /**< BLE Timer wakeup event             */
#define LL_PWR_WKUP_EVENT_TIMER             AON_CTL_SLP_EVENT_SLP_TIMER                         /**< AON Timer wakeup event             */
#define LL_PWR_WKUP_EVENT_EXT               AON_CTL_SLP_EVENT_EXT                               /**< External wakeup event: AON_GPIO    */
#define LL_PWR_WKUP_EVENT_COMP_RISE         AON_CTL_SLP_EVENT_COMP_RISE                         /**< Comparator rise wakeup event       */
#define LL_PWR_WKUP_EVENT_COMP_FALL         AON_CTL_SLP_EVENT_COMP_FALL                         /**< Comparator fall wakeup event       */
#define LL_PWR_WKUP_EVENT_WDT               AON_CTL_SLP_EVENT_AON_WDT                           /**< AON WDT Alarm wakeup event         */
#define LL_PWR_WKUP_EVENT_CLDR              AON_CTL_SLP_EVENT_RTC0                              /**< RTC0 wakeup event                  */
#define LL_PWR_WKUP_EVENT_ALL               AON_CTL_SLP_EVENT_ALL                               /**< All event mask  */
/** @} */

/** @defgroup PWR_LL_EC_AON_IRQ Condition
  * @{
  */
#define LL_PWR_AON_IRQ_EVT_BLE_PWR_ON       AON_CTL_AON_IRQ_BLE_PWR                             /**< BLE power up done IRQ event        */
#define LL_PWR_AON_IRQ_EVT_BLE_PWR_DN       AON_CTL_AON_IRQ_BLE_PWR_DN                          /**< BLE power down done IRQ event      */
#define LL_PWR_AON_IRQ_EVT_BOD_RISE         AON_CTL_AON_IRQ_PMU_BOD_RISE                        /**< BOD rise edge IRQ event            */
#define LL_PWR_AON_IRQ_EVT_CPLL_DN          AON_CTL_AON_IRQ_AONPLL_CHG                          /**< PLL power on done IRQ event        */
#define LL_PWR_AON_IRQ_EVT_BOD_FALL         AON_CTL_AON_IRQ_PMU_BOD_FALL                        /**< PMU BOD fall edge IRQ event        */
#define LL_PWR_AON_IRQ_EVT_BLE_MAC          AON_CTL_AON_IRQ_BLE_MAC_IRQ                         /**< BLE MAC IRQ event                  */
#define LL_PWR_AON_IRQ_EVT_SLP_FAIL         AON_CTL_AON_IRQ_SLP_FAIL_IRQ                        /**< Sleep fail IRQ event               */
#define LL_PWR_AON_IRQ_EVT_ALL              AON_CTL_AON_IRQ_BLE_ALL                             /**< All IRQ event mask                 */

/** @} */

/** @defgroup PWR_LL_EC_AON_IRQ_EVT Event
  * @{
  */
#define LL_PWR_AON_IRQ_EN_BLE_PWR_ON        AON_CTL_AON_IRQ_EN_BLE_PWR_ON                       /**< BLE power up done IRQ EN           */
#define LL_PWR_AON_IRQ_EN_BLE_PWR_DN        AON_CTL_AON_IRQ_EN_BLE_PWR_DN                       /**< BLE power down done IRQ EN         */
#define LL_PWR_AON_IRQ_EN_BOD_RISE          AON_CTL_AON_IRQ_EN_PMU_BOD_RISE                     /**< BOD rise edge IRQ EN               */
#define LL_PWR_AON_IRQ_EN_CPLL_DN           AON_CTL_AON_IRQ_EN_AONPLL_CHG                       /**< PLL power on done IRQ EN           */
#define LL_PWR_AON_IRQ_EN_BOD_FALL          AON_CTL_AON_IRQ_EN_PMU_BOD_FALL                     /**< PMU BOD fall edge IRQ EN           */
#define LL_PWR_AON_IRQ_EN_BLE_MAC           AON_CTL_AON_IRQ_EN_BLE_MAC_IRQ                      /**< BLE MAC IRQ EN                     */
#define LL_PWR_AON_IRQ_EN_SLP_FAIL          AON_CTL_AON_IRQ_EN_SLP_FAIL_IRQ                     /**< Sleep fail IRQ EN                  */
#define LL_PWR_AON_IRQ_EN_ALL               AON_CTL_AON_IRQ_EN_ALL                              /**< All IRQ EN                         */
/** @} */


/** @defgroup PWR_LL_EC_PSC_CMD  Power State Control Commands
 * @{
 */

/** @} */
/** @} */

/** @defgroup PWR_LL_EC_DPAD_VALUE  Dpad LE State
 * @{
 */
#define LL_PWR_DPAD_LE_OFF                  (0x00000000U)   /**< Dpad LE LOW */
#define LL_PWR_DPAD_LE_ON                   (0x00000001U)   /**< Dpad LE High  */
/** @} */

/** @} */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PWR_LL_Exported_Functions PWR Exported Functions
  * @{
  */

/** @defgroup PWR_LL_EF_Low_Power_Mode_Configuration Low power mode configuration
  * @{
  */

/**
  * @brief  Set the DeepSleep WakeUp Condition
  *
  *  Register|BitsName
  *  --------|--------
  *  MCU_WAKEUP_CTRL | MCU_WAKEUP_CTRL
  *
  * @param  condition This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WKUP_COND_EXT
  *         @arg @ref LL_PWR_WKUP_COND_TIMER
  *         @arg @ref LL_PWR_WKUP_COND_BLE
  *         @arg @ref LL_PWR_WKUP_COND_CLDR
  *         @arg @ref LL_PWR_WKUP_COND_AON_WDT
  *         @arg @ref LL_PWR_WKUP_COND_COMP_RISE
  *         @arg @ref LL_PWR_WKUP_COND_COMP_FALL
  *         @arg @ref LL_PWR_WKUP_COND_ALL
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_wakeup_condition(uint32_t condition)
{
    SET_BITS(AON_CTL->MCU_WAKEUP_CTRL, condition);
}

/**
  * @brief  Clear the DeepSleep WakeUp Condition
  *
  *  Register|BitsName
  *  --------|--------
  *  MCU_WAKEUP_CTRL | MCU_WAKEUP_CTRL
  *
  * @param  condition This parameter can be one of the following values:
  *         @arg @ref LL_PWR_WKUP_COND_EXT
  *         @arg @ref LL_PWR_WKUP_COND_TIMER
  *         @arg @ref LL_PWR_WKUP_COND_BLE
  *         @arg @ref LL_PWR_WKUP_COND_CLDR
  *         @arg @ref LL_PWR_WKUP_COND_AON_WDT
  *         @arg @ref LL_PWR_WKUP_COND_COMP_RISE
  *         @arg @ref LL_PWR_WKUP_COND_COMP_FALL
  *         @arg @ref LL_PWR_WKUP_COND_ALL
  * @retval None
  */
__STATIC_INLINE void ll_pwr_clear_wakeup_condition(uint32_t condition)
{
    CLEAR_BITS(AON_CTL->MCU_WAKEUP_CTRL, condition);
}

/**
  * @brief  Get the Selected DeepSleep WakeUp Condition
  *
  *  Register|BitsName
  *  --------|--------
  *  MCU_WAKEUP_CTRL | MCU_WAKEUP_CTRL
  *
  * @retval Returned value can be one of the following values:
  *         @arg @ref LL_PWR_WKUP_COND_EXT
  *         @arg @ref LL_PWR_WKUP_COND_TIMER
  *         @arg @ref LL_PWR_WKUP_COND_BLE
  *         @arg @ref LL_PWR_WKUP_COND_CLDR
  *         @arg @ref LL_PWR_WKUP_COND_AON_WDT
  *         @arg @ref LL_PWR_WKUP_COND_COMP_RISE
  *         @arg @ref LL_PWR_WKUP_COND_COMP_FALL
  *         @arg @ref LL_PWR_WKUP_COND_ALL
  */
__STATIC_INLINE uint32_t ll_pwr_get_wakeup_condition(void)
{
    return ((uint32_t)READ_BITS(AON_CTL->MCU_WAKEUP_CTRL, LL_PWR_WKUP_COND_ALL));
}

/**
  * @brief  Get the Event that triggered the DeepSleep WakeUp.
 *  @note     Only available on GR551xx_B2 and later version
 *
  *  Register|BitsName
  *  --------|--------
  *  AON_SLP_EVENT | AON_SLP_EVENT
  *
  * @retval Returned value can be combination of the following values:
  *         @arg @ref LL_PWR_WKUP_EVENT_BLE
  *         @arg @ref LL_PWR_WKUP_EVENT_TIMER
  *         @arg @ref LL_PWR_WKUP_EVENT_EXT
  *         @arg @ref LL_PWR_WKUP_EVENT_COMP_RISE
  *         @arg @ref LL_PWR_WKUP_EVENT_COMP_FALL
  *         @arg @ref LL_PWR_WKUP_EVENT_WDT
  *         @arg @ref LL_PWR_WKUP_EVENT_CLDR
  */
__STATIC_INLINE uint32_t ll_pwr_get_wakeup_event(void)
{
    return ((uint32_t)READ_BITS(AON_CTL->AON_SLP_EVENT, LL_PWR_WKUP_EVENT_ALL));
}

/**
  * @brief  Set the 32 bits AON Sleep Timer Value to WakeUp the MCU from DeepSleep Mode.
  * @note   After the value was set, use LL_PWR_CMD_32_TIMER_LD command to
  *         load the configuration into Power State Controller.
  *
  *  Register|BitsName
  *  --------|--------
  *  SLEEP_TIMER_W | SLEEP_TIMER_W
  *
  * @param  value  32 bits count value loaded into the t32bit_timer
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_sleep_timer_value(uint32_t value)
{
    WRITE_REG(SLP_TIMER->TIMER_W, value);
}

/**
  * @brief  Read the AON Sleep Timer counter current value.
  *
  *  Register|BitsName
  *  --------|--------
  *  SLEEP_TIMER_R | PWR_CTL_TIMER_32B
  *
  * @retval 32 bit AON Timer Count Value
  */
__STATIC_INLINE uint32_t ll_pwr_get_sleep_timer_read_value(void)
{
    return READ_REG(SLP_TIMER->TIMER_R);
}


/**
  * @brief  Enable the SMC WakeUp Request.
  * @note   Once this is set up, MCU will wake up SMC, and this bit need to be cleared by MCU.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_MISC | SMC_WAKEUP_REQ
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_enable_smc_wakeup_req(void)
{
    SET_BITS(AON_CTL->BLE_MISC, AON_CTL_BLE_MISC_SMC_WAKEUP_REQ);
}

/**
  * @brief  Disable the SMC WakeUp Request.
  * @note   This function is used to clear SMC WakeUp Request.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_MISC | SMC_WAKEUP_REQ
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_disable_smc_wakeup_req(void)
{
    CLEAR_BITS(AON_CTL->BLE_MISC, AON_CTL_BLE_MISC_SMC_WAKEUP_REQ);
}

/**
  * @brief  Check if the SMC WakeUp Request was enabled or disabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_MISC | SMC_WAKEUP_REQ
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwr_is_enabled_smc_wakeup_req(void)
{
    return (READ_BITS(AON_CTL->BLE_MISC, AON_CTL_BLE_MISC_SMC_WAKEUP_REQ) == AON_CTL_BLE_MISC_SMC_WAKEUP_REQ);
}

/**
  * @brief  Set the DPAD LE value during sleep and after wake up.
  *
  *  Register|BitsName
  *  --------|--------
  *  DPAD_LE_CTRL | DPAD_LE_SLP_VAL
  *  DPAD_LE_CTRL | DPAD_LE_WKUP_VAL
  *
  * @param  sleep  This parameter can be one of the following values:
  *         @arg @ref LL_PWR_DPAD_LE_OFF
  *         @arg @ref LL_PWR_DPAD_LE_ON
  * @param  wakeup This parameter can be one of the following values:
  *         @arg @ref LL_PWR_DPAD_LE_OFF
  *         @arg @ref LL_PWR_DPAD_LE_ON
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_dpad_le_value(uint32_t sleep, uint32_t wakeup)
{
    MODIFY_REG(AON_PWR->DPAD_LE_CTRL, AON_PWR_DPAD_LE_CTRL_SLEEP, (sleep << AON_PWR_DPAD_LE_CTRL_SLEEP_Pos));
    MODIFY_REG(AON_PWR->DPAD_LE_CTRL, AON_PWR_DPAD_LE_CTRL_WAKEUP, (wakeup << AON_PWR_DPAD_LE_CTRL_WAKEUP_Pos));
}

/** @} */

/** @addtogroup PWR_LL_EF_Communication_Configuration BLE Communication timer and core configuration function
  * @{
  */

/**
  * @brief  Enable the Communication Timer Reset.
  * @note   Comm timer can be reset when all ble connection were disconnected and
  *         MCU was ready to enter into deepsleep mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  COMM_CTRL | COMM_TIMER_RST_N
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_enable_comm_timer_reset(void)
{
    CLEAR_BITS(AON_PWR->COMM_TIMER_PWR_CTRL, AON_PWR_COMM_TIMER_PWR_CTRL_RST_N);
}

/**
  * @brief  Disable the Communication Timer Reset, and set Communication Timer to running state.
  * @note   After powered up, Comm Timer need to enter into running mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  COMM_CTRL | COMM_TIMER_RST_N
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_disable_comm_timer_reset(void)
{
    SET_BITS(AON_PWR->COMM_TIMER_PWR_CTRL, AON_PWR_COMM_TIMER_PWR_CTRL_RST_N);
}

/**
  * @brief  Check if the Communication Timer Reset was enabled or disabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  COMM_CTRL | COMM_TIMER_RST_N
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwr_is_enabled_comm_timer_reset(void)
{
    return ((uint32_t)(READ_BITS(AON_PWR->COMM_TIMER_PWR_CTRL, AON_PWR_COMM_TIMER_PWR_CTRL_RST_N) == 0x0U));
}

/**
  * @brief  Enable the Communication Core Reset.
  * @note   Comm Core can be reset when all ble connection were disconnected and
  *         MCU was ready to enter into deepsleep mode, and When COMM_CORE_RST_N
  *         is 0, the ble is held in reset.
  *
  *  Register|BitsName
  *  --------|--------
  *  COMM_CTRL | COMM_CORE_RST_N
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_enable_comm_core_reset(void)
{
    CLEAR_BITS(AON_PWR->COMM_CORE_PWR_CTRL_SW, AON_PWR_COMM_CORE_PWR_CTRL_SW_RST_N);
}

/**
  * @brief  Disable the Communication Core Reset, and set Communication Core to running state.
  * @note   After powered up, Comm Core need to enter into running mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  COMM_CTRL | COMM_CORE_RST_N
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_disable_comm_core_reset(void)
{
    SET_BITS(AON_PWR->COMM_CORE_PWR_CTRL_SW, AON_PWR_COMM_CORE_PWR_CTRL_SW_RST_N);
}

/**
  * @brief  Check if the Communication Core Reset was enabled or disabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  COMM_CTRL | COMM_CORE_RST_N
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwr_is_enabled_comm_core_reset(void)
{
    return ((uint32_t)(READ_BITS(AON_PWR->COMM_CORE_PWR_STAT, AON_PWR_COMM_CORE_PWR_STAT_RST_N_RD) == 0x0U));
}

/**
  * @brief Enable the Communication Timer Power, the Communication Timer will be Powered Up.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | ISO_EN_PD_COMM_TIMER
  *  BLE_PWR_CTL | PWR_EN_PD_COMM_TIMER
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_enable_comm_timer_power(void)
{
    SET_BITS(AON_PWR->COMM_TIMER_PWR_CTRL, AON_PWR_COMM_TIMER_PWR_CTRL_ISO_EN);
    SET_BITS(AON_PWR->COMM_TIMER_PWR_CTRL, AON_PWR_COMM_TIMER_PWR_CTRL_EN);
    CLEAR_BITS(AON_PWR->COMM_TIMER_PWR_CTRL, AON_PWR_COMM_TIMER_PWR_CTRL_ISO_EN);
}

/**
  * @brief  Disable the Communication Timer Power, the Communication Timer will be Powered Down.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | ISO_EN_PD_COMM_TIMER
  *  BLE_PWR_CTL | PWR_EN_PD_COMM_TIMER
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_disable_comm_timer_power(void)
{
    SET_BITS(AON_PWR->COMM_TIMER_PWR_CTRL, AON_PWR_COMM_TIMER_PWR_CTRL_EN);
    SET_BITS(AON_PWR->COMM_TIMER_PWR_CTRL, AON_PWR_COMM_TIMER_PWR_CTRL_ISO_EN);
    CLEAR_BITS(AON_PWR->COMM_TIMER_PWR_CTRL, AON_PWR_COMM_TIMER_PWR_CTRL_EN);
}

/**
  * @brief Check if the Communication Timer Power was enabled or disabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | ISO_EN_PD_COMM_TIMER
  *  BLE_PWR_CTL | PWR_EN_PD_COMM_TIMER
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_FORCEINLINE uint32_t ll_pwr_is_enabled_comm_timer_power(void)
{
    return ((uint32_t)(READ_BITS(AON_PWR->COMM_TIMER_PWR_CTRL, AON_PWR_COMM_TIMER_PWR_CTRL_EN) == AON_PWR_COMM_TIMER_PWR_CTRL_EN));
}

/**
  * @brief Enable the Communication Core Power, the Communication Core will be Powered Up.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | ISO_EN_PD_COMM_CORE
  *  BLE_PWR_CTL | PWR_EN_PD_COMM_CORE
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_enable_comm_core_power(void)
{
    SET_BITS(AON_PWR->COMM_CORE_PWR_CTRL_SW, AON_PWR_COMM_CORE_PWR_CTRL_SW_CORE_EN);
    CLEAR_BITS(AON_PWR->COMM_CORE_PWR_CTRL_SW, AON_PWR_COMM_CORE_PWR_CTRL_SW_ISO_EN);
}

/**
  * @brief  Disable the Communication Core Power, the Communication Core will be Powered Down.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | ISO_EN_PD_COMM_CORE
  *  BLE_PWR_CTL | PWR_EN_PD_COMM_CORE
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_disable_comm_core_power(void)
{
    SET_BITS(AON_PWR->COMM_CORE_PWR_CTRL_SW, AON_PWR_COMM_CORE_PWR_CTRL_SW_ISO_EN);
    CLEAR_BITS(AON_PWR->COMM_CORE_PWR_CTRL_SW, AON_PWR_COMM_CORE_PWR_CTRL_SW_CORE_EN);
}

/**
  * @brief Check if the Communication Core Power was enabled or disabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | ISO_EN_PD_COMM_CORE
  *  BLE_PWR_CTL | PWR_EN_PD_COMM_CORE
  *
  * @retval None
  */
__STATIC_INLINE uint32_t ll_pwr_is_enabled_comm_core_power(void)
{
    return ((uint32_t)(READ_BITS(AON_PWR->COMM_CORE_PWR_STAT, AON_PWR_COMM_CORE_PWR_STAT_CORE_EN_RD) == AON_PWR_COMM_CORE_PWR_STAT_CORE_EN_RD));
}

/**
  * @brief Enable high frequency crystal oscillator sleep mode, and diable OSC.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_OSC_SLEEP_EN
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_enable_osc_sleep(void)
{
    SET_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_OSC_SLEEP_EN);
}

/**
  * @brief Disable high frequency crystal oscillator sleep mode.
  * @note  Switch OSC from sleep mode into normal active mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_OSC_SLEEP_EN
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_disable_osc_sleep(void)
{
    CLEAR_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_OSC_SLEEP_EN);
}

/**
  * @brief Check if the OSC sleep mode was enabled or disabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_OSC_SLEEP_EN
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwr_is_enabled_osc_sleep(void)
{
    return ((uint32_t)(READ_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_OSC_SLEEP_EN) == AON_CTL_COMM_CTRL_DEEPSLCNTL_OSC_SLEEP_EN));
}

/**
  * @brief Enable Radio sleep mode, and disable Radio module.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_RADIO_SLEEP_EN
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_enable_radio_sleep(void)
{
    SET_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_RADIO_SLEEP_EN);
}

/**
  * @brief Disable Radio sleep mode.
  * @note  Switch Radio from sleep mode into normal active mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_RADIO_SLEEP_EN
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_disable_radio_sleep(void)
{
    CLEAR_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_RADIO_SLEEP_EN);
}

/**
  * @brief Check if the Radio sleep mode was enabled or disabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_RADIO_SLEEP_EN
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwr_is_enabled_radio_sleep(void)
{
    return ((uint32_t)(READ_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_RADIO_SLEEP_EN) == AON_CTL_COMM_CTRL_DEEPSLCNTL_RADIO_SLEEP_EN));
}

/**
  * @brief Enable Communication Core Deep Sleep Mode.
  * @note  This bit is reset on DEEP_SLEEP_STAT falling edge.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_DEEP_SLEEP_ON
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_enable_comm_core_deep_sleep(void)
{
    SET_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_ON);
}

/**
  * @brief Disable Communication Core Deep Sleep Mode.
  * @note  Switch Communication Core from sleep mode into normal active mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_DEEP_SLEEP_ON
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_disable_comm_core_deep_sleep(void)
{
    CLEAR_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_ON);
}

/**
  * @brief Check if the Communication Core Deep Sleep Mode was enabled or disabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_DEEP_SLEEP_ON
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwr_is_enabled_comm_core_deep_sleep(void)
{
    return ((uint32_t)(READ_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_ON) == AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_ON));
}

/**
  * @brief Enable Wake Up Request from Software.
  * @note  Applies when system is in Deep Sleep Mode. It wakes up the Communication Core
  *        when written with a 1. No action happens if it is written with 0.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_SOFT_WAKEUP_REQ
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_enable_comm_soft_wakeup_req(void)
{
    SET_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_SOFT_WAKEUP_REQ);
}

/**
  * @brief Check if the Wake Up Request was enabled or disabled.
  * @note  Resets at 0 means request action is performed.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_SOFT_WAKEUP_REQ
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwr_is_enabled_soft_wakeup_req(void)
{
    return ((uint32_t)(READ_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_SOFT_WAKEUP_REQ) == AON_CTL_COMM_CTRL_DEEPSLCNTL_SOFT_WAKEUP_REQ));
}

/**
  * @brief Enable Communication Core external wakeup.
  * @note  After this configuration, Communication Core can be woken up by external wake-up
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_EXTWKUPDSB
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_enable_comm_core_ext_wakeup(void)
{
    CLEAR_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_EXTWKUPDSB);
}

/**
  * @brief Disable Communication Core external wakeup.
  * @note  After this configuration, Communication Core cannot be woken up by external wake-up
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_EXTWKUPDSB
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_disable_comm_core_ext_wakeup(void)
{
    SET_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_EXTWKUPDSB);
}

/**
  * @brief Check if the Communication Core external wakeup was enabled or disabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  BLE_PWR_CTL | COMM_DEEPSLCNTL_EXTWKUPDSB
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwr_is_enabled_comm_core_ext_wakeup(void)
{
    return ((uint32_t)(READ_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_EXTWKUPDSB) == 0x0U));
}

/**
  * @brief  Set the time in low_power_clk clock cycles to spend in Deep Sleep Mode before waking-up the device.
  *
  *  Register|BitsName
  *  --------|--------
  *  COMM_TIMER_CFG_0 | AON_COMM_TMR_DEEPSLWKUP_DEEPSLTIME
  *
  * @param  time  32 bit clock cycles loaded into the AON_COMM_TMR_DEEPSLWKUP_DEEPSLTIME
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_comm_core_wakeup_time(uint32_t time)
{
    WRITE_REG(AON_CTL->COMM_TIMER_CFG0, time);
}

/**
  * @brief  Get the time in low_power_clk clock cycles to spend in Deep Sleep Mode before waking-up the device.
  *
  *  Register|BitsName
  *  --------|--------
  *  COMM_TIMER_CFG_0 | AON_COMM_TMR_DEEPSLWKUP_DEEPSLTIME
  *
  * @retval Clock cycles to spend in Deep Sleep Mode before waking-up the device
  */
__STATIC_FORCEINLINE uint32_t ll_pwr_get_comm_wakeup_time(void)
{
    return ((uint32_t)READ_REG(AON_CTL->COMM_TIMER_CFG0));
}

/**
  * @brief  Get the actual duration of the last deep sleep phase measured in low_power_clk clock cycle.
  *
  *  Register|BitsName
  *  --------|--------
  *  COMM_TMR_REG | DEEPSLDUR
  *
  * @retval Sleep duration
  */
__STATIC_FORCEINLINE uint32_t ll_pwr_get_comm_sleep_duration(void)
{
    return ((uint32_t)READ_REG(AON_CTL->COMM_TIMER_STAT));
}

/**
  * @brief  Set the wakeup timing in low_power_clk clock cycles to spend when waking-up the device.
  *
  *  Register|BitsName
  *  --------|--------
  *  COMM_TIMER_CFG_1 | TWEXT
  *  COMM_TIMER_CFG_1 | TWOSC
  *  COMM_TIMER_CFG_1 | TWRM
  *
  * @param  twext   Time in low power oscillator cycles allowed for stabilization of the high frequency
  *                 oscillator following an external wake–up request (signal wakeup_req).
  * @param  twosc   Time in low power oscillator cycles allowed for stabilization of the high frequency
  *                 oscillator when the deep–sleep mode has been left due to sleep–timer expiry.
  * @param  twrm    Time in low power oscillator cycles allowed for the radio module to leave low–power mode.
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_comm_wakeup_timing(uint32_t twext, uint32_t twosc, uint32_t twrm)
{
    WRITE_REG(AON_CTL->COMM_TIMER_CFG1, (twext << AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWEXT_Pos) |
                              (twosc << AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWOSC_Pos) |
                              (twrm  << AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWRM_Pos));
}

/**
  * @brief  Read the wakeup timing in low_power_clk clock cycles to spend when waking-up the device.
  *
  *  Register|BitsName
  *  --------|--------
  *  COMM_TIMER_CFG_1 | TWEXT
  *  COMM_TIMER_CFG_1 | TWOSC
  *  COMM_TIMER_CFG_1 | TWRM
  *
  * @retval COMM_TMR_ENBPRESET Register value
  */
__STATIC_INLINE uint32_t ll_pwr_read_comm_wakeup_timing(void)
{
    return ((uint32_t)READ_REG(AON_CTL->COMM_TIMER_CFG1));
}

/**
  * @brief  Read the Twosc of the wakeup timing in low_power_clk clock cycles to spend when waking-up the device.
  *
  * @retval TWOSC value
  */
__STATIC_FORCEINLINE uint32_t ll_pwr_read_comm_wakeup_timing_twosc(void)
{
    return ((((uint32_t)READ_REG(AON_CTL->COMM_TIMER_CFG1) & AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWOSC_Msk)) >> AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWOSC_Pos);
}

/** @} */

/** @defgroup PWR_LL_EF_FLAG_Management FLAG_Management
  * @{
  */

/**
  * @brief  Get the External Wake Up Status.
  * @note   0 means not waked up and 1 means waked up.
  *
  *  Register|BitsName
  *  --------|--------
  *  EXT_WAKEUP_STAT | EXT_WKUP_STATUS
  *
  * @retval Returned value can be a combination of the following values:
  *         LL_PWR_EXTWKUP_PIN0
  *         LL_PWR_EXTWKUP_PIN1
  *         LL_PWR_EXTWKUP_PIN2
  *         LL_PWR_EXTWKUP_PIN3
  *         LL_PWR_EXTWKUP_PIN4
  *         LL_PWR_EXTWKUP_PIN5
  *         LL_PWR_EXTWKUP_PIN6
  *         LL_PWR_EXTWKUP_PIN7
  *         LL_PWR_EXTWKUP_PIN_ALL
  */
__STATIC_INLINE uint32_t ll_pwr_get_ext_wakeup_status(void)
{
    return ((uint32_t)(READ_BITS(AON_CTL->EXT_WAKEUP_STAT, AON_IO_EXT_WAKEUP_STAT_STAT) >> AON_IO_EXT_WAKEUP_STAT_STAT_POS));
}

/**
  * @brief  Clear the External Wake Up Status.
  *
  *  Register|BitsName
  *  --------|--------
  *  EXT_WAKEUP_STAT | EXT_WKUP_STATUS
  *
  * @param  wakeup_pin This parameter can be a combination of the following values:
  *         LL_PWR_EXTWKUP_PIN0
  *         LL_PWR_EXTWKUP_PIN1
  *         LL_PWR_EXTWKUP_PIN2
  *         LL_PWR_EXTWKUP_PIN3
  *         LL_PWR_EXTWKUP_PIN4
  *         LL_PWR_EXTWKUP_PIN5
  *         LL_PWR_EXTWKUP_PIN6
  *         LL_PWR_EXTWKUP_PIN7
  *         LL_PWR_EXTWKUP_PIN_ALL
  * @retval None
  */
__STATIC_INLINE void ll_pwr_clear_ext_wakeup_status(uint32_t wakeup_pin)
{
    WRITE_REG(AON_CTL->EXT_WAKEUP_STAT, ~(wakeup_pin << AON_IO_EXT_WAKEUP_STAT_STAT_POS));
}

/**
  * @brief  Clear the Event that triggered the DeepSleep WakeUp.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_SLEEP_EVENT | AON_SLEEP_EVENT
  *
  * @param  event This parameter can be a combination of the following values:
  *         @arg @ref LL_PWR_WKUP_EVENT_BLE
  *         @arg @ref LL_PWR_WKUP_EVENT_TIMER
  *         @arg @ref LL_PWR_WKUP_EVENT_EXT
  *         @arg @ref LL_PWR_WKUP_EVENT_COMP_RISE
  *         @arg @ref LL_PWR_WKUP_EVENT_COMP_FALL
  *         @arg @ref LL_PWR_WKUP_EVENT_WDT
  *         @arg @ref LL_PWR_WKUP_EVENT_CLDR
  * @retval None
  */
__STATIC_INLINE void ll_pwr_clear_wakeup_event(uint32_t event)
{
    WRITE_REG(AON_CTL->AON_SLP_EVENT, ~(event & LL_PWR_WKUP_EVENT_ALL));
}

/**
  * @brief  Indicate if the Communication Core is in Deep Sleep Mode.
  * @note   When Communication Core is in Deep Sleep Mode, only low_power_clk is running.
  *
  *  Register|BitsName
  *  --------|--------
  *  COMM_CTRL | COMM_DEEPSLCNTL_DEEP_SLEEP_STAT
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwr_is_active_flag_comm_deep_sleep_stat(void)
{
    return (READ_BITS(AON_CTL->COMM_CTRL, AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_STAT) == AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_STAT);
}

/**
  * @brief  Disable cache function
  * @note  The cache should be closed before chip go to deepsleep.
  *
  *  Register|BitsName
  *  --------|--------
  *  CACHE.CTRL0 |EN
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_disable_cache_module(void)
{
    SET_BITS(XQSPI->CACHE.CTRL0, XQSPI_CACHE_CTRL0_DIS);
    __NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();__NOP();
}

/**
  * @brief  Set DCDC prepare timing.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_PWR | DCDC
  *
  * @param value setting value.
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_dcdc_prepare_timing(uint32_t value)
{
    MODIFY_REG(AON_PWR->A_TIMING_CTRL0, AON_PWR_A_TIMING_CTRL0_DCDC, (value << AON_PWR_A_TIMING_CTRL0_DCDC_Pos));
}

/**
  * @brief  Set digtal LDO prepare timing.
  *
  *  Register|BitsName
  *  --------|--------
  *  A_TIMING_CTRL0 | DIG_LDO
  *
  * @param value setting value.
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_dig_ldo_prepare_timing(uint32_t value)
{
    MODIFY_REG(AON_PWR->A_TIMING_CTRL0, AON_PWR_A_TIMING_CTRL0_DIG_LDO, (value << AON_PWR_A_TIMING_CTRL0_DIG_LDO_Pos));
}


/**
  * @brief  Set fast LDO prepare timing.
  *
  *  Register|BitsName
  *  --------|--------
  *  A_TIMING_CTRL1 | FAST_LDO
  *
  * @param value setting value.
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_fast_ldo_prepare_timing(uint32_t value)
{
    MODIFY_REG(AON_PWR->A_TIMING_CTRL1, AON_PWR_A_TIMING_CTRL1_FAST_LDO, (value << AON_PWR_A_TIMING_CTRL1_FAST_LDO_Pos));
}

/**
  * @brief  Set HF OSC prepare timing.
  *
  *  Register|BitsName
  *  --------|--------
  *  A_TIMING_CTRL1 | HF_OSC
  *
  * @param value setting value.
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_hf_osc_prepare_timing(uint32_t value)
{
    MODIFY_REG(AON_PWR->A_TIMING_CTRL1, AON_PWR_A_TIMING_CTRL1_HF_OSC, (value << AON_PWR_A_TIMING_CTRL1_HF_OSC_Pos));
}

/**
  * @brief  Set PLL lock prepare timing.
  *
  *  Register|BitsName
  *  --------|--------
  *  A_TIMING_CTRL2 | PLL_LOCK
  *
  * @param value setting value.
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_pll_lock_timing(uint32_t value)
{
    MODIFY_REG(AON_PWR->A_TIMING_CTRL2, AON_PWR_A_TIMING_CTRL2_PLL_LOCK, (value << AON_PWR_A_TIMING_CTRL2_PLL_LOCK_Pos));
}

/**
  * @brief  Set PLL prepare timing.
  *
  *  Register|BitsName
  *  --------|--------
  *  A_TIMING_CTRL2 | PLL
  *
  * @param value setting value.
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_pll_prepare_timing(uint32_t value)
{
    MODIFY_REG(AON_PWR->A_TIMING_CTRL2, AON_PWR_A_TIMING_CTRL2_PLL, (value << AON_PWR_A_TIMING_CTRL2_PLL_Pos));
}

/**
  * @brief  Set power switch prepare timing.
  *
  *  Register|BitsName
  *  --------|--------
  *  A_TIMING_CTRL3 | PWR_SWITCH
  *
  * @param value setting value.
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_pwr_switch_prepare_timing(uint32_t value)
{
    MODIFY_REG(AON_PWR->A_TIMING_CTRL3, AON_PWR_A_TIMING_CTRL3_PWR_SWITCH, (value << AON_PWR_A_TIMING_CTRL3_PWR_SWITCH_Pos));
}

/**
  * @brief  Set Set XO prepare timing.
  *
  *  Register|BitsName
  *  --------|--------
  *  A_TIMING_CTRL3 | CTRL3_XO
  *
  * @param value setting value.
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_xo_prepare_timing(uint32_t value)
{
    MODIFY_REG(AON_PWR->A_TIMING_CTRL3, AON_PWR_A_TIMING_CTRL3_XO, (value << AON_PWR_A_TIMING_CTRL3_XO_Pos));
}

/**
  * @brief ll_pwr_set_pwr_mode
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_START_CFG | AON_PWR_AON_START_CFG_POWER_MODE
  *
  * @param value setting value.
  * @retval None
  */
__STATIC_INLINE void ll_pwr_set_pwr_mode(uint32_t value)
{
    MODIFY_REG(AON_PWR->AON_START_CFG, AON_PWR_AON_START_CFG_POWER_MODE,value << AON_PWR_AON_START_CFG_POWER_MODE_Pos);
}


/**
  * @brief Turn off enable xo/pll in warm boot.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_START_CFG | AON_PWR_AON_START_CFG_XO_EN_PWR | AON_PWR_AON_START_CFG_PLL_EN_PWR
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_turn_off_enable_xo_pll_after_dcdc_ready(void)
{
    CLEAR_BITS(AON_PWR->AON_START_CFG, AON_PWR_AON_START_CFG_XO_EN_PWR|AON_PWR_AON_START_CFG_PLL_EN_PWR);
}

/**
  * @brief Turn on enable xo/pll in srpg.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_START_CFG | AON_PWR_AON_START_CFG_XO_EN_PWR | AON_PWR_AON_START_CFG_PLL_EN_PWR
  *
  * @retval None
  */
__STATIC_INLINE void ll_pwr_turn_on_enable_xo_pll_after_dcdc_ready(void)
{
    SET_BITS(AON_PWR->AON_START_CFG, AON_PWR_AON_START_CFG_XO_EN_PWR|AON_PWR_AON_START_CFG_PLL_EN_PWR);
}

/**
  * @brief  Set the AON IRQ Condition
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_IRQ_EN | AON_IRQ_EN
  *
  * @param  condition This parameter can be one of the following values:
  *         @arg @ref LL_PWR_AON_IRQ_EN_BLE_PWR_ON
  *         @arg @ref LL_PWR_AON_IRQ_EN_BLE_PWR_DN
  *         @arg @ref LL_PWR_AON_IRQ_EN_BOD_RISE
  *         @arg @ref LL_PWR_AON_IRQ_EN_CPLL_DN
  *         @arg @ref LL_PWR_AON_IRQ_EN_BOD_FALL
  *         @arg @ref LL_PWR_AON_IRQ_EN_BLE_MAC
  *         @arg @ref LL_PWR_AON_IRQ_EN_SLP_FAIL
  *         @arg @ref LL_PWR_AON_IRQ_EN_ALL
  * @retval None
  */
__STATIC_INLINE void ll_pwr_enable_aon_irq(uint32_t condition)
{
    SET_BITS(AON_CTL->AON_IRQ_EN, condition);
}

/**
  * @brief  clear the AON IRQ Condition
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_IRQ_EN | AON_IRQ_EN
  *
  * @param  condition This parameter can be one of the following values:
  *         @arg @ref LL_PWR_AON_IRQ_EN_BLE_PWR_ON
  *         @arg @ref LL_PWR_AON_IRQ_EN_BLE_PWR_DN
  *         @arg @ref LL_PWR_AON_IRQ_EN_BOD_RISE
  *         @arg @ref LL_PWR_AON_IRQ_EN_CPLL_DN
  *         @arg @ref LL_PWR_AON_IRQ_EN_BOD_FALL
  *         @arg @ref LL_PWR_AON_IRQ_EN_BLE_MAC
  *         @arg @ref LL_PWR_AON_IRQ_EN_SLP_FAIL
  *         @arg @ref LL_PWR_AON_IRQ_EN_ALL
  * @retval None
  */
__STATIC_INLINE void ll_pwr_disable_aon_irq(uint32_t condition)
{
    CLEAR_BITS(AON_CTL->AON_IRQ_EN, condition);
}

/**
  * @brief  Clear the AON IRQ EVENT
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_IRQ | AON_IRQ
  *
  * @param  condition This parameter can be one of the following values:
  *         @arg @ref LL_PWR_AON_IRQ_EVT_BLE_PWR_ON
  *         @arg @ref LL_PWR_AON_IRQ_EVT_BLE_PWR_DN
  *         @arg @ref LL_PWR_AON_IRQ_EVT_BOD_RISE
  *         @arg @ref LL_PWR_AON_IRQ_EVT_CPLL_DN
  *         @arg @ref LL_PWR_AON_IRQ_EVT_BOD_FALL
  *         @arg @ref LL_PWR_AON_IRQ_EVT_BLE_MAC
  *         @arg @ref LL_PWR_AON_IRQ_EVT_SLP_FAIL
  *         @arg @ref LL_PWR_AON_IRQ_EVT_ALL
  * @retval None
  */
__STATIC_INLINE void ll_pwr_clear_aon_irq_event(uint32_t condition)
{
    CLEAR_BITS(AON_CTL->AON_IRQ, condition);
}


/** @} */

/** @} */

#endif /* defined(AON) */

#ifdef __cplusplus
}
#endif

#endif /* __GR533x_LL_PWR_H__ */

/** @} */

/** @} */

/** @} */
