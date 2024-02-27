/**
 ****************************************************************************************
 *
 * @file    gr533x_hal_tim.h
 * @author  BLE Driver Team
 * @brief   Header file containing functions prototypes of TIMER HAL library.
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

/** @addtogroup HAL_DRIVER HAL Driver
  * @{
  */

/** @defgroup HAL_TIMER TIMER
  * @brief TIM HAL module driver.
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR533x_HAL_TIMER_H__
#define __GR533x_HAL_TIMER_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gr533x_hal_def.h"
#include "gr533x_ll_tim.h"

/* Exported types ------------------------------------------------------------*/
/** @addtogroup HAL_TIMER_ENUMERATIONS Enumerations
  * @{
  */

/** @defgroup HAL_TIMER_state HAL TIMER state
  * @{
  */

/**
  * @brief  HAL TIMER State Enumerations definition
  */
typedef enum
{
    HAL_TIMER_STATE_RESET             = 0x00,    /**< Peripheral not yet initialized or disabled  */
    HAL_TIMER_STATE_READY             = 0x01,    /**< Peripheral Initialized and ready for use    */
    HAL_TIMER_STATE_BUSY              = 0x02,    /**< An internal process is ongoing              */
    HAL_TIMER_STATE_ERROR             = 0x04     /**< Reception process is ongoing                */
} hal_timer_state_t;

/**
  * @brief  HAL TIMER capture type Enumerations definition
  */
typedef enum
{
    HAL_TIMER_CAPTURE_NONE             = 0x00,    /**< Set timer capture NONE                      */
    HAL_TIMER_CAPTURE_FALLING          = 0x01,    /**< Set timer capture io falling edge           */
    HAL_TIMER_CAPTURE_RISING           = 0x02,    /**< Set timer capture io rising edge            */
    HAL_TIMER_CAPTURE_BOTH             = 0x03,    /**< Set timer capture io both edge              */
} hal_timer_capture_type_t;

/**
  * @brief  HAL TIMER capture pin Enumerations definition
  */
typedef enum
{
    HAL_TIMER_CAPTURE_GPIO_PIN_0              = 0x00,    /**< capture GPIO_PIN_0                   */
    HAL_TIMER_CAPTURE_GPIO_PIN_1              = 0x01,    /**< capture GPIO_PIN_1                   */
    HAL_TIMER_CAPTURE_GPIO_PIN_2              = 0x02,    /**< capture GPIO_PIN_2                   */
    HAL_TIMER_CAPTURE_GPIO_PIN_3              = 0x03,    /**< capture GPIO_PIN_3                   */
    HAL_TIMER_CAPTURE_GPIO_PIN_4              = 0x04,    /**< capture GPIO_PIN_4                   */
    HAL_TIMER_CAPTURE_GPIO_PIN_5              = 0x05,    /**< capture GPIO_PIN_5                   */
    HAL_TIMER_CAPTURE_GPIO_PIN_6              = 0x06,    /**< capture GPIO_PIN_6                   */
    HAL_TIMER_CAPTURE_GPIO_PIN_7              = 0x07,    /**< capture GPIO_PIN_7                   */
    HAL_TIMER_CAPTURE_GPIO_PIN_8              = 0x08,    /**< capture GPIO_PIN_8                   */
    HAL_TIMER_CAPTURE_GPIO_PIN_9              = 0x09,    /**< capture GPIO_PIN_9                   */
    HAL_TIMER_CAPTURE_GPIO_PIN_10             = 0x0A,    /**< capture GPIO_PIN_10                  */
    HAL_TIMER_CAPTURE_GPIO_PIN_11             = 0x0B,    /**< capture GPIO_PIN_11                  */
    HAL_TIMER_CAPTURE_GPIO_PIN_12             = 0x0C,    /**< capture GPIO_PIN_12                  */
    HAL_TIMER_CAPTURE_GPIO_PIN_13             = 0x0D,    /**< capture GPIO_PIN_13                  */
    HAL_TIMER_CAPTURE_AON_GPIO_PIN_0          = 0x0E,    /**< capture AON_GPIO_PIN_0               */
    HAL_TIMER_CAPTURE_AON_GPIO_PIN_1          = 0x0F,    /**< capture AON_GPIO_PIN_1               */
    HAL_TIMER_CAPTURE_AON_GPIO_PIN_2          = 0x10,    /**< capture AON_GPIO_PIN_2               */
    HAL_TIMER_CAPTURE_AON_GPIO_PIN_3          = 0x11,    /**< capture AON_GPIO_PIN_3               */
    HAL_TIMER_CAPTURE_AON_GPIO_PIN_4          = 0x12,    /**< capture AON_GPIO_PIN_4               */
    HAL_TIMER_CAPTURE_AON_GPIO_PIN_5          = 0x13,    /**< capture AON_GPIO_PIN_5               */
    HAL_TIMER_CAPTURE_AON_GPIO_PIN_6          = 0x14,    /**< capture AON_GPIO_PIN_6               */
    HAL_TIMER_CAPTURE_AON_GPIO_PIN_7          = 0x15,    /**< capture AON_GPIO_PIN_7               */
    HAL_TIMER_CAPTURE_MSIO_PIN_0              = 0x16,    /**< capture MSIO_PIN_0                   */
    HAL_TIMER_CAPTURE_MSIO_PIN_1              = 0x17,    /**< capture MSIO_PIN_1                   */
    HAL_TIMER_CAPTURE_MSIO_PIN_2              = 0x18,    /**< capture MSIO_PIN_2                   */
    HAL_TIMER_CAPTURE_MSIO_PIN_3              = 0x19,    /**< capture MSIO_PIN_3                   */
    HAL_TIMER_CAPTURE_MSIO_PIN_4              = 0x1A,    /**< capture MSIO_PIN_4                   */
    HAL_TIMER_CAPTURE_MSIO_PIN_5              = 0x1B,    /**< capture MSIO_PIN_5                   */
    HAL_TIMER_CAPTURE_MSIO_PIN_6              = 0x1C,    /**< capture MSIO_PIN_6                   */
    HAL_TIMER_CAPTURE_MSIO_PIN_7              = 0x1D,    /**< capture MSIO_PIN_7                   */
    HAL_TIMER_CAPTURE_MSIO_PIN_8              = 0x1E,    /**< capture MSIO_PIN_8                   */
    HAL_TIMER_CAPTURE_MSIO_PIN_9              = 0x1F,    /**< capture MSIO_PIN_9                   */
} hal_timer_capture_pin_t;

/** @} */

/** @} */

/** @addtogroup HAL_TIMER_STRUCTURES Structures
  * @{
  */

/** @defgroup TIMER_Configuration TIMER Configuration
  * @{
  */

/**
  * @brief TIMER capture channel Structure definition
  */
typedef struct _hal_timer_capture_channel_init
{
    hal_timer_capture_type_t  edge_capture;                   /**< Specifies the edge caputre type. */
    hal_timer_capture_pin_t    capture_pin;                    /**< Soecufies the capture io pin.    */
} hal_timer_capture_channel_init_t;

/**
  * @brief TIMER init Structure definition
  */
typedef struct _timer_init
{
    uint32_t auto_reload;                                     /**< Specifies the auto-reload value. */
    hal_timer_capture_channel_init_t  capture_channel0;       /**< Capture channel0 config.         */
    hal_timer_capture_channel_init_t  capture_channel1;       /**< Capture channel1 config.         */
    hal_timer_capture_channel_init_t  capture_channel2;       /**< Capture channel2 config.         */
    hal_timer_capture_channel_init_t  capture_channel3;       /**< Capture channel3 config.         */
} timer_init_t;

/** @} */

/** @defgroup TIMER_handle TIMER handle
  * @{
  */

/**
  * @brief TIMER handle Structure definition
  */
typedef struct _timer_handle
{
    timer_regs_t             *p_instance;     /**< Register base address          */

    timer_init_t             init;            /**< TIMER Base required parameters */

    __IO hal_lock_t          lock;            /**< Locking object                 */

    __IO hal_timer_state_t   state;           /**< TIMER operation state          */

} timer_handle_t;
/** @} */

/** @} */

/** @addtogroup HAL_TIMER_CALLBACK_STRUCTURES Callback Structures
  * @{
  */

/** @defgroup HAL_TIMER_Callback Callback
  * @{
  */

/**
  * @brief HAL_TIMER Callback function definition
  */

typedef struct _hal_timer_base_callback
{
    void (*timer_msp_init)(timer_handle_t *p_timer);                /**< TIMER init MSP callback            */
    void (*timer_msp_deinit)(timer_handle_t *p_timer);              /**< TIMER de-init MSP callback         */
    void (*timer_period_elapsed_callback)(timer_handle_t *p_timer); /**< TIMER period elapsed callback      */
} hal_timer_base_callback_t;

/** @} */

/** @} */

/**
  * @defgroup  HAL_TIMER_MACRO Defines
  * @{
  */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup TIMER_Exported_Macros TIMER Exported Macros
  * @{
  */

/** @brief  Reset TIMER handle states.
  * @param  __HANDLE__ TIMER handle.
  * @retval None
  */
#define __HAL_TIMER_RESET_HANDLE_STATE(__HANDLE__)               ((__HANDLE__)->state = HAL_TIMER_STATE_RESET)

/** @brief  Enable the specified TIMER peripheral.
  * @param  __HANDLE__ Specifies the TIMER Handle.
  * @retval None
  */
#define __HAL_TIMER_ENABLE(__HANDLE__)                           SET_BITS((__HANDLE__)->p_instance->CTRL, TIMER_CTRL_EN)

/** @brief  Disable the specified TIMER peripheral.
  * @param  __HANDLE__ Specifies the TIMER Handle.
  * @retval None
  */
#define __HAL_TIMER_DISABLE(__HANDLE__)                          CLEAR_BITS((__HANDLE__)->p_instance->CTRL, TIMER_CTRL_EN)

/** @brief  Enable the TIMER all interrupt.
  * @param  __HANDLE__ Specifies the TIMER Handle.
  * @retval None
  */
#define __HAL_TIMER_ENABLE_ALL_IT(__HANDLE__)                    ll_timer_enable_all_it((__HANDLE__)->p_instance)

/** @brief  Disable the TIMER all interrupt.
  * @param  __HANDLE__ Specifies the TIMER Handle.
  * @retval None
  */
#define __HAL_TIMER_DISABLE_ALL_IT(__HANDLE__)                   ll_timer_disable_all_it((__HANDLE__)->p_instance)

/** @brief  Check whether the TIMER interrupt has occurred or not.
  * @param  __HANDLE__ Specifies the TIMER Handle.
  * @retval The new state of TIMER interrupt (SET or RESET).
  */
#define __HAL_TIMER_GET_FLAG_IT(__HANDLE__)                      ll_timer_is_active_flag_it(__HANDLE__->p_instance)

/** @} */

/** @} */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HAL_TIMER_DRIVER_FUNCTIONS Functions
  * @{
  */

/** @addtogroup TIMER_Exported_Functions_Group1 Initialization and de-initialization functions
  * @brief    Initialization and de-initialization functions
  *
  * @verbatim
===============================================================================
            ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]
        This section provides functions allowing to:
        (+) Initialize and configure the TIMER.
        (+) De-initialize the TIMER.
        (+) Start the Timer.
        (+) Stop the Timer.
        (+) Start the Timer and enable interrupt.
        (+) Stop the Timer and disable interrupt.

@endverbatim
  * @{
  */

/**
 ****************************************************************************************
 * @brief  Initialize the TIMER according to the specified parameters
 *         in the timer_init_t and initialize the associated handle.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_timer_init(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  De-initialize the TIMER peripheral.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_timer_deinit(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  Initialize the TIMER MSP.
 * @note   This function should not be modified. When the callback is needed,
 *         the hal_timer_base_msp_init could be implemented in the user file.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 ****************************************************************************************
 */
void hal_timer_msp_init(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  De-initialize the TIMER MSP.
 * @note   This function should not be modified. When the callback is needed,
 *         the hal_timer_base_msp_deinit could be implemented in the user file.
 * @param[in]  p_timer: Pointer to a TIM handle which contains the configuration
 *                 information for the specified TIMER module.
 ****************************************************************************************
 */
void hal_timer_msp_deinit(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  Starts the TIMER counter.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_timer_start(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  Stops the TIMER counter.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_timer_stop(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  Starts the TIMER counter in interrupt mode.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_timer_start_it(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  Stops the TIMER counter in interrupt mode.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_timer_stop_it(timer_handle_t *p_timer);

/** @} */

/** @addtogroup TIMER_IRQ_Handler_and_Callbacks IRQ Handler and Callbacks
  * @brief    IRQ Handler and Callbacks functions
 * @{
 */

/**
 ****************************************************************************************
 * @brief Handle TIMER interrupt request.
 * @param[in] p_timer: TIMER handle.
 ****************************************************************************************
 */
void hal_timer_irq_handler(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  Period elapsed callback in non-blocking mode.
 * @note   This function should not be modified. When the callback is needed,
            the hal_timer_period_elapsed_callback can be implemented in the user file.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 ****************************************************************************************
 */
void hal_timer_period_elapsed_callback(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  channel0 event callback in non-blocking mode.
 * @note   This function should not be modified. When the callback is needed,
            the hal_timer_channel0_event_callback can be implemented in the user file.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 ****************************************************************************************
 */
void hal_timer_channel0_event_callback(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  channel1 event callback in non-blocking mode.
 * @note   This function should not be modified. When the callback is needed,
            the hal_timer_channel1_event_callback can be implemented in the user file.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 ****************************************************************************************
 */
void hal_timer_channel1_event_callback(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  channel2 event callback in non-blocking mode.
 * @note   This function should not be modified. When the callback is needed,
            the hal_timer_channel2_event_callback can be implemented in the user file.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 ****************************************************************************************
 */
void hal_timer_channel2_event_callback(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  channel3 event callback in non-blocking mode.
 * @note   This function should not be modified. When the callback is needed,
            the hal_timer_channel3_event_callback can be implemented in the user file.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 ****************************************************************************************
 */
void hal_timer_channel3_event_callback(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  ble pulse 1 event callback in non-blocking mode.
 * @note   This function should not be modified. When the callback is needed,
            the hal_timer_channel3_event_callback can be implemented in the user file.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 ****************************************************************************************
 */
void hal_timer_blepulse1_event_callback(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  ble pulse 2 event callback in non-blocking mode.
 * @note   This function should not be modified. When the callback is needed,
            the hal_timer_channel3_event_callback can be implemented in the user file.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 ****************************************************************************************
 */
void hal_timer_blepulse2_event_callback(timer_handle_t *p_timer);

/** @} */

/** @addtogroup TIMER_Exported_Functions_Group2 Peripheral Control and State functions
 *  @brief   TIMER Peripheral State functions
 *
@verbatim
  ==============================================================================
            ##### Peripheral Control and State functions #####
  ==============================================================================
    [..]
    This subsection provides functions allowing to :
      (+) Return the TIMER handle state.
      (+) Configure the TIMER.

@endverbatim
  * @{
  */

/**
 ****************************************************************************************
 * @brief  Return the TIMER handle state.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 * @retval ::HAL_TIMER_STATE_RESET: Peripheral not yet initialized or disabled.
 * @retval ::HAL_TIMER_STATE_READY: Peripheral Initialized and ready for use.
 * @retval ::HAL_TIMER_STATE_BUSY: An internal process is ongoing.
 * @retval ::HAL_TIMER_STATE_ERROR: Reception process is ongoing.
 ****************************************************************************************
 */
hal_timer_state_t hal_timer_get_state(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  TIMER configuration
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                      information for the specified TIMER module.
 * @param[in]  p_structure: The TIMER configuration structure
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_timer_set_config(timer_handle_t *p_timer, timer_init_t *p_structure);

/**
 ****************************************************************************************
 * @brief  Get current value of channel0.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 * @retval ::Current timer value
 ****************************************************************************************
 */
uint32_t hal_timer_get_channel0_val(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  Get current value of channel1.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 * @retval ::Current timer value
 ****************************************************************************************
 */
uint32_t hal_timer_get_channel1_val(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  Get current value of channel2.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 * @retval ::Current timer value
 ****************************************************************************************
 */
uint32_t hal_timer_get_channel2_val(timer_handle_t *p_timer);

/**
 ****************************************************************************************
 * @brief  Get current value of channel3.
 * @param[in]  p_timer: Pointer to a TIMER handle which contains the configuration
 *                 information for the specified TIMER module.
 * @retval ::Current timer value
 ****************************************************************************************
 */
uint32_t hal_timer_get_channel3_val(timer_handle_t *p_timer);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __GR533x_HAL_TIMER_H__ */

/** @} */

/** @} */

/** @} */
