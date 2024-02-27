/**
 ****************************************************************************************
 *
 * @file    gr533x_hal_conf.h
 * @author  BLE Driver Team
 * @brief   HAL configuration file.
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR533x_HAL_CONF_H__
#define __GR533x_HAL_CONF_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Exported types ------------------------------------------------------------*/
/* Exported constants --------------------------------------------------------*/

/* ########################## Module Selection ############################## */
/**
  * @brief This is the list of modules to be used in the HAL driver
  */
#define HAL_MODULE_ENABLED              /**< Enable HAL module driver          */
#define HAL_ADC_MODULE_ENABLED          /**< Enable ADC HAL module driver      */
#define HAL_AON_GPIO_MODULE_ENABLED     /**< Enable AON GPIO HAL module driver */
#define HAL_CORTEX_MODULE_ENABLED       /**< Enable CORTEX HAL module driver   */
#define HAL_DMA_MODULE_ENABLED          /**< Enable DMA HAL module driver      */
#define HAL_DUAL_TIMER_MODULE_ENABLED   /**< Enable DUAL TIM module driver     */
#define HAL_EXFLASH_MODULE_ENABLED      /**< Enable EXFLASH module driver      */
#define HAL_GPIO_MODULE_ENABLED         /**< Enable GPIO module driver         */
#define HAL_I2C_MODULE_ENABLED          /**< Enable I2C module driver          */
#define HAL_MSIO_MODULE_ENABLED         /**< Enable MSIO module driver         */
#define HAL_PWM_MODULE_ENABLED          /**< Enable PWM module driver          */
#define HAL_PWR_MODULE_ENABLED          /**< Enable PWR module driver          */
#define HAL_SPI_MODULE_ENABLED          /**< Enable SPI module driver          */
#define HAL_TIMER_MODULE_ENABLED        /**< Enable TIM module driver          */
#define HAL_UART_MODULE_ENABLED         /**< Enable UART module driver         */
#define HAL_WDT_MODULE_ENABLED          /**< Enable WDT module driver          */
#define HAL_XQSPI_MODULE_ENABLED        /**< Enable XQSPI module driver        */
#define HAL_AON_WDT_MODULE_ENABLED      /**< Enable AON WDT module driver      */
#define HAL_CALENDAR_MODULE_ENABLED     /**< Enable CALENDAR module driver     */
#define HAL_RTC_MODULE_ENABLED          /**< Enable RTC module driver          */
#define HAL_EFUSE_MODULE_ENABLED        /**< Enable EFUSE module driver        */
#define HAL_CGC_MODULE_ENABLED          /**< Enable CGC module driver          */
#define HAL_RNG_MODULE_ENABLED          /**< Enable RNG module driver          */
#define HAL_COMP_MODULE_ENABLED         /**< Enable COMP module driver         */
#define HAL_PWR_MGMT_ENABLED            /**< Enable PWR MGMT module driver     */
#define HAL_SLEEP_TIMER_MODULE_ENABLED  /**< Enable SLEPP TIMER module driver  */
#define HAL_CLOCK_MODULE_ENABLED        /**< Enable clock manage module driver */
#define HAL_PMU_MODULE_ENABLED          /**< Enable PMU module driver          */
#define HAL_BR_MODULE_ENABLED           /**< Enable bridge layer module driver */
#define HAL_BOD_MODULE_ENABLED          /**< Enable BOD module driver */

#define HAL_PARAMS_CHECK          1     /**< Params check */
#define HAL_STATUS_CHECK          1     /**< Status check */
#define HAL_PWMG_STATE_CHECK      1     /**< Pwmg state check */

/* ########################### System Configuration ######################### */
/**
  * @brief This is the HAL system configuration section
  */
#define  TICK_INT_PRIORITY            ((uint32_t)(1U<<(__NVIC_PRIO_BITS - 4)) - 1U) /*!< tick interrupt priority (lowest by default) by group priority 4. */
#define  USE_RTOS                     0U                                            /*!< use rtos */

/* ########################## Assert Selection ############################## */
/**
  * @brief Uncomment the line below to expanse the "gr_assert_param" macro in the
  *        HAL drivers code
  */
/* #define USE_FULL_ASSERT    1U */

/* Includes ------------------------------------------------------------------*/
#include "gr533x.h"
/**
  * @brief Include module's header file
  */
#ifdef HAL_CORTEX_MODULE_ENABLED
#include "gr533x_hal_cortex.h"
#endif /* HAL_CORTEX_MODULE_ENABLED */

#ifdef HAL_ADC_MODULE_ENABLED
#include "gr533x_hal_adc.h"
#endif /* HAL_ADC_MODULE_ENABLED */

#ifdef HAL_AON_GPIO_MODULE_ENABLED
#include "gr533x_hal_aon_gpio.h"
#endif /* HAL_AON_GPIO_MODULE_ENABLED */

#ifdef HAL_AON_WDT_MODULE_ENABLED
#include "gr533x_hal_aon_wdt.h"
#endif /* HAL_AON_WDT_MODULE_ENABLED */

#ifdef HAL_CALENDAR_MODULE_ENABLED
#include "gr533x_hal_calendar.h"
#endif /* HAL_CALENDAR_MODULE_ENABLED */

#ifdef HAL_DMA_MODULE_ENABLED
#include "gr533x_hal_dma.h"
#endif /* HAL_DMA_MODULE_ENABLED */

#ifdef HAL_DUAL_TIMER_MODULE_ENABLED
#include "gr533x_hal_dual_tim.h"
#endif /* HAL_DUAL_TIMER_MODULE_ENABLED */

#ifdef HAL_GPIO_MODULE_ENABLED
#include "gr533x_hal_gpio.h"
#endif /* HAL_GPIO_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
#include "gr533x_hal_i2c.h"
#endif /* HAL_I2C_MODULE_ENABLED */

#ifdef HAL_MSIO_MODULE_ENABLED
#include "gr533x_hal_msio.h"
#endif /* HAL_MSIO_MODULE_ENABLED */

#ifdef HAL_PWM_MODULE_ENABLED
#include "gr533x_hal_pwm.h"
#endif /* HAL_PWM_MODULE_ENABLED */

#ifdef HAL_PWR_MODULE_ENABLED
#include "gr533x_hal_pwr.h"
#endif /* HAL_PWR_MODULE_ENABLED */

#ifdef HAL_SPI_MODULE_ENABLED
#include "gr533x_hal_spi.h"
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_TIMER_MODULE_ENABLED
#include "gr533x_hal_tim.h"
#endif /* HAL_TIMER_MODULE_ENABLED */

#ifdef HAL_UART_MODULE_ENABLED
#include "gr533x_hal_uart.h"
#endif /* HAL_UART_MODULE_ENABLED */

#ifdef HAL_WDT_MODULE_ENABLED
#include "gr533x_hal_wdt.h"
#endif /* HAL_WDT_MODULE_ENABLED */

#ifdef HAL_XQSPI_MODULE_ENABLED
#include "gr533x_hal_xqspi.h"
#endif /* HAL_XQSPI_MODULE_ENABLED */

#ifdef HAL_EXFLASH_MODULE_ENABLED
#include "gr533x_hal_exflash.h"
#endif /* HAL_EXFLASH_MODULE_ENABLED */

#ifdef HAL_EFUSE_MODULE_ENABLED
#include "gr533x_hal_efuse.h"
#endif /* HAL_EFUSE_MODULE_ENABLED */

#ifdef HAL_CGC_MODULE_ENABLED
#include "gr533x_hal_cgc.h"
#endif /* HAL_CGC_MODULE_ENABLED */

#ifdef HAL_RNG_MODULE_ENABLED
#include "gr533x_hal_rng.h"
#endif /* HAL_RNG_MODULE_ENABLED */

#ifdef HAL_COMP_MODULE_ENABLED
#include "gr533x_hal_comp.h"
#endif /* HAL_COMP_MODULE_ENABLED */

#ifdef HAL_SLEEP_TIMER_MODULE_ENABLED
#include "gr533x_hal_sleep_timer.h"
#endif /* HAL_SLEEP_TIMER_MODULE_ENABLED */

#ifdef HAL_RTC_MODULE_ENABLED
#include "gr533x_hal_rtc.h"
#endif /* HAL_RTC_MODULE_ENABLED */

#ifdef HAL_PWR_MGMT_ENABLED
#include "gr533x_hal_pwr_mgmt.h"
#endif

#ifdef HAL_CLOCK_MODULE_ENABLED
#include "gr533x_hal_clock.h"
#endif /* HAL_CLOCK_MODULE_ENABLED */

#ifdef HAL_PMU_MODULE_ENABLED
#include "gr533x_ll_aon_pmu.h"
#include "gr533x_ll_aon_rf.h"
#include "gr533x_ll_clk_cal.h"
#include "gr533x_ll_ddvs.h"
#endif /* HAL_PMU_MODULE_ENABLED */

#ifdef HAL_BR_MODULE_ENABLED
#include "gr533x_hal_br.h"
#endif /* HAL_BR_MODULE_ENABLED */

#ifdef HAL_BOD_MODULE_ENABLED
#include "gr533x_hal_bod.h"
#endif

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The gr_assert_param macro is used for function's parameters check.
  * @param  expr If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
#define gr_assert_param(expr) ((expr) ? (void)0U : assert_failed((char *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
__STATIC_INLINE void assert_failed(char *file, uint32_t line)
{

}
#else
#define gr_assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */

#ifdef __cplusplus
}
#endif

#endif /* __GR533x_HAL_CONF_H__ */

