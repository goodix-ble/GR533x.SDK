/**
 ****************************************************************************************
 *
 * @file    gr533x_ll_clk.h
 * @author  BLE Driver Team
 * @brief   Header file containing functions prototypes of CLOCK LL library.
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

/** @defgroup LL_CLK LL Clock
  * @brief CLOCK CALIBRATION LL module driver.
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR533X_LL_CLK_H_
#define __GR533X_LL_CLK_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gr533x_hal.h"

/** @defgroup CLK_SOURCE Clock source
  * @{
  */
#define LL_CLK_SEL_SOURCE_CPLL_CLK          (0UL)                               /**< Select CPLL clk as the source of the 192MHz clock */
#define LL_CLK_SEL_SOURCE_HF_OSC_CLK        (1UL)                               /**< Select hf osc clk as the source of the 192MHz clock */
/** @} */

/** @defgroup SLOW_CLK_SOURCE Slow clock source
  * @{
  */

#define LL_SLOW_CLK_RNG                     AON_CTL_MCU_SLOW_CLK_CTRL_SEL_RNG   /**< Select RNG_OSC clk as the source of the slow clock */
#define LL_SLOW_CLK_RC                      AON_CTL_MCU_SLOW_CLK_CTRL_SEL_RC    /**< Select RC_32K clk as the source of the slow clock */
#define LL_SLOW_CLK_RTC                     AON_CTL_MCU_SLOW_CLK_CTRL_SEL_RTC   /**< Select RTC_32K clk as the source of the slow clock */
/** @} */

/** @defgroup CLK_SELECT Clock select
  * @{
  */
#define LL_CLK_CPLL_S64M_CLK                AON_CTL_MCU_CLK_CTRL_SEL_64M        /**< Select PLL/HF_OSC 64MHz clk as system clock */
#define LL_CLK_XO_S16M_CLK                  AON_CTL_MCU_CLK_CTRL_SEL_XO_16M     /**< Select XO 16MHz clk as system clock */
#define LL_CLK_CPLL_S16M_CLK                AON_CTL_MCU_CLK_CTRL_SEL_16M        /**< Select PLL/HF_OSC 16MHz clk as system clock */
#define LL_CLK_CPLL_T32M_CLK                AON_CTL_MCU_CLK_CTRL_SEL_32M        /**< Select PLL/HF_OSC 32MHz clk as system clock */
/** @} */

/** @defgroup XO_PLL_STATE XO pll state
  * @{
  */
#define LL_CLK_XO_PLL_PLL_STAT              (1UL)                               /**< Check CPLL STAT */
#define LL_CLK_XO_PLL_XO_STAT               (2UL)                               /**< Check XO STAT */
#define LL_CLK_XO_PLL_HF_STAT               (4UL)                               /**< Check HF STAT */
/** @} */

/** @defgroup AON_SLOW_CLK_SOURCE AON_SLOW clock source
  * @{
  */
#define LL_AON_SLOW_CLK_256K                (0UL)                               /**< Select aon slow clk 256k */
#define LL_AON_SLOW_CLK_32K                 (1UL)                               /**< Select aon slow clk 32k */
/** @} */

/** @defgroup CLK_LL_DRIVER_FUNCTIONS Functions
  * @{
  */

/**
  * @brief  Get system clock.
  *
  *  Register|BitsName
  *  --------|--------
  *  MCU_CLK_CTRL | CLK_CTRL_SEL
  *
  * @retval System clock
  *
  */
__STATIC_INLINE uint32_t ll_clk_get_sys_clk(void)
{
    return READ_BITS(AON_CTL->MCU_CLK_CTRL, AON_CTL_MCU_CLK_CTRL_SEL);
}

/**
  * @brief  Set system clock.
  *
  *  Register|BitsName
  *  --------|--------
  *  MCU_CLK_CTRL | CLK_CTRL_SEL
  *
  * @param  clk_sel This parameter can be a combination of the following values:
  *         @arg @ref LL_CLK_CPLL_S64M_CLK
  *         @arg @ref LL_CLK_XO_S16M_CLK
  *         @arg @ref LL_CLK_CPLL_S16M_CLK
  *         @arg @ref LL_CLK_CPLL_T32M_CLK
  * @retval None
  *
  */
__STATIC_INLINE void ll_clk_set_sys_clk(uint32_t clk_sel)
{
    MODIFY_REG(AON_CTL->MCU_CLK_CTRL, AON_CTL_MCU_CLK_CTRL_SEL, clk_sel);
}

/**
  * @brief  Select clock source.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_CLK | CAL_FST_CLK
  *
  * @param  src_sel This parameter can be a combination of the following values:
  *         @arg @ref LL_CLK_SEL_SOURCE_CPLL_CLK
  *         @arg @ref LL_CLK_SEL_SOURCE_HF_OSC_CLK
  * @retval None
  *
  */
__STATIC_INLINE void ll_clk_select_source(uint32_t src_sel)
{
    MODIFY_REG(AON_CTL->AON_CLK, AON_CTL_AON_CLK_CAL_FST_CLK, src_sel);
}

/**
  * @brief  start XO and PLL
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_PWR | XO_PLL_SET
  *
  * @retval void.
  *
  */
__STATIC_INLINE void ll_clk_start_xo_pll(void)
{
    MODIFY_REG(AON_PWR->XO_PLL_SET, AON_PWR_XO_PLL_SET_PLL_SET_Msk | AON_PWR_XO_PLL_SET_XO_SET_Msk, AON_PWR_XO_PLL_SET_PLL_SET | AON_PWR_XO_PLL_SET_XO_SET);
}

/**
  * @brief  stop XO and PLL
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_PWR | XO_PLL_CLR
  *
  * @retval void.
  *
  */
__STATIC_INLINE void ll_clk_stop_xo_pll(void)
{
    MODIFY_REG(AON_PWR->XO_PLL_CLR, AON_PWR_XO_PLL_SET_PLL_SET_Msk | AON_PWR_XO_PLL_SET_XO_SET_Msk, AON_PWR_XO_PLL_SET_PLL_SET | AON_PWR_XO_PLL_SET_XO_SET);
}

/**
  * @brief  Get XO PLL status.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_PWR | XO_PLL_STAT
  *
  * @retval xo pll status value.
  *
  */
__STATIC_INLINE uint32_t ll_clk_get_hf_status(void)
{
    return READ_BITS(AON_PWR->XO_PLL_STAT, AON_PWR_XO_PLL_STAT_PLL_STAT |
                                           AON_PWR_XO_PLL_STAT_XO_STAT  |
                                           AON_PWR_XO_PLL_STAT_HF_STAT);
}

/**
  * @brief  Get system slow clock.
  *
  *  Register|BitsName
  *  --------|--------
  *  MCU_CLK_CTRL | CLK_CTRL_SEL
  *
  * @retval System slow clock
  *
  */
__STATIC_INLINE uint32_t ll_clk_get_sys_slow_clk(void)
{
    return READ_BITS(AON_CTL->MCU_CLK_CTRL, AON_CTL_MCU_SLOW_CLK_CTRL_SEL);
}

/**
  * @brief  Set system clock.
  *
  *  Register|BitsName
  *  --------|--------
  *  MCU_CLK_CTRL | CLK_CTRL_SEL
  *
  * @param  clk_sel This parameter can be a combination of the following values:
  *         @arg @ref LL_SLOW_CLK_RNG
  *         @arg @ref LL_SLOW_CLK_RC
  *         @arg @ref LL_SLOW_CLK_RTC
  * @retval None
  *
  */
__STATIC_INLINE void ll_clk_set_sys_slow_clk(uint32_t clk_sel)
{
    MODIFY_REG(AON_CTL->MCU_CLK_CTRL, AON_CTL_MCU_SLOW_CLK_CTRL_SEL, clk_sel);
}

/**
  * @brief  Set system clock.
  *
  *  Register|BitsName
  *  --------|--------
  *  MCU_CLK_CTRL | AON_CLK_CTRL_SEL
  *
  * @param  clk_sel This parameter can be a combination of the following values:
  *         @arg @ref LL_AON_SLOW_CLK_256K
  *         @arg @ref LL_AON_SLOW_CLK_32K
  * @retval None
  *
  */
__STATIC_INLINE void ll_clk_set_aon_slow_clk(uint32_t clk_sel)
{
    MODIFY_REG(AON_CTL->MCU_CLK_CTRL, AON_CTL_MCU_CLK_CTRL_SLOW_CLK_SEL, (clk_sel << AON_CTL_MCU_CLK_CTRL_SLOW_CLK_SEL_Pos));
}

/** @} */
#ifdef __cplusplus
}
#endif

#endif

/** @} */

/** @} */

/** @} */
