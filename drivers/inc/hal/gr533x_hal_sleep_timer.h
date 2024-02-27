/**
 ****************************************************************************************
 *
 * @file    gr533x_hal_sleep_timer.h
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

/** @defgroup LL_SLP_TIM SLP_TIM
  * @brief SLEEP TIMER HAL module driver.
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR533x_HAL_SLEEP_TIMER_H__
#define __GR533x_HAL_SLEEP_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gr533x_ll_sleep_timer.h"
#include "gr533x_hal_def.h"

/* Exported types ------------------------------------------------------------*/

/** @addtogroup HAL_PWR_CALLBACK_STRUCTURES Callback Structures
  * @{
  */
/** @defgroup HAL_PWR_SLEEP_ELAPSED_HANDLER HAL PWR sleep elapsed handler define
  * @{
  */

/**
  * @brief   PWR Sleep Timer Elapsed callback
  */
typedef void (*pwr_slp_elapsed_handler_t)(void);

/** @} */


/** @defgroup HAL_PWR_CALLBACK_HANDLER PWR callback handle
  * @{
  */
/**
  * @brief PWR callback handle Structure definition
  */
typedef struct _pwr_handler
{
    pwr_slp_elapsed_handler_t       pwr_slp_elapsed_hander;     /**< PWR sleep timer elapsed callback */
} pwr_handler_t;

/** @} */
/** @} */

/**
  * @defgroup  HAL_PWR_MACRO Defines
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PWR_Exported_Constants PWR Exported Constants
  * @{
  */

/** @defgroup PWR_Sleep_Timer_Mode  PWR Sleep Timer Mode
 * @{
 */
#define PWR_SLP_TIMER_MODE_NORMAL       LL_SLEEP_TIMER_SINGLE_MODE_0    /**< Start counting after sleeping and disabled when waked up */
#define PWR_SLP_TIMER_MODE_SINGLE       LL_SLEEP_TIMER_SINGLE_MODE_1    /**< Single mode(keep counting until finished) */
#define PWR_SLP_TIMER_MODE_RELOAD       LL_SLEEP_TIMER_AUTO_MODE        /**< Auto reload  */
/** @} */

/** @defgroup PWR_Timeout_definition PWR Timeout definition
 * @{
  */
#define HAL_PWR_TIMEOUT_DEFAULT_VALUE ((uint32_t)0x000FFFFF)         /**< 0xFFFFF counts */
/** @} */

/** @} */
/** @} */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HAL_PWR_DRIVER_FUNCTIONS Functions
  * @{
  */

/** @addtogroup PWR_Exported_Functions_Group1 Low Power mode configuration functions
  * @{
  */

/**
****************************************************************************************
* @brief  Configure the AON Sleep Timer mode, count and start used to wakeup MCU.
* @param[in]  mode: Specifies the sleep timer mode.
*             This parameter can be a combination of the following values:
*             @arg @ref PWR_SLP_TIMER_MODE_NORMAL
*             @arg @ref PWR_SLP_TIMER_MODE_SINGLE
*             @arg @ref PWR_SLP_TIMER_MODE_RELOAD
* @param[in]  value: Count value of the AON Sleep Timer.
* @retval ::HAL_OK: Operation is OK.
* @retval ::HAL_BUSY: Driver is busy.
* @note   The sleep clock of AON Timer is 32 KHz.
****************************************************************************************
*/
hal_status_t hal_sleep_timer_config_and_start(uint8_t mode, uint32_t value);

/**
****************************************************************************************
* @brief  stop Sleep Timer
****************************************************************************************
*/
void hal_sleep_timer_stop(void);

/**
****************************************************************************************
* @brief  Get the reload value of sleep timer
* @retval the reload value of sleep timer
****************************************************************************************
*/
uint32_t hal_sleep_timer_get_reload_value(void);

/**
****************************************************************************************
* @brief  Get the current value of sleep timer
* @retval the current value of sleep timer
****************************************************************************************
*/
uint32_t hal_sleep_timer_get_current_value(void);

/**
****************************************************************************************
* @brief  Get clock frequency of sleep timer
* @retval clock frequency of sleep timer
****************************************************************************************
*/
uint32_t hal_sleep_timer_get_clock_freq(void);

/**
****************************************************************************************
* @brief  get sleep timer is running or not
* @retval runing state of sleep timer (1 or 0).
****************************************************************************************
*/
uint8_t hal_sleep_timer_status_get(void);
/** @} */

/** @addtogroup PWR_IRQ_Handler_and_Callbacks IRQ Handler and Callbacks
  * @brief    IRQ Handler and Callbacks functions
 * @{
 */
/**
 ****************************************************************************************
 * @brief  Handle PWR Sleep Timer interrupt request.
 * @note   Only available on GR551xx_B2 and later versions.
 ****************************************************************************************
 */
void hal_pwr_sleep_timer_irq_handler(void);

/**
 ****************************************************************************************
 * @brief  PWR Sleep Timer Elapsed callback.
 * @note   Only available on GR551xx_B2 and later versions.
 *         This function should not be modified. When the callback is needed,
 *         the hal_pwr_sleep_timer_elapsed_callback can be implemented in the user file.
 ****************************************************************************************
 */
void hal_pwr_sleep_timer_elapsed_callback(void);

/** @} */
/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __GR533x_HAL_SLEEP_TIMER_H__ */

/** @} */

/** @} */

/** @} */
