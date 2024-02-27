/**
 ****************************************************************************************
 *
 * @file    gr533x_hal_dma.h
 * @author  BLE Driver Team
 * @brief   Header file containing functions prototypes of DMA HAL library.
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

/** @defgroup HAL_DMA DMA
  * @brief DMA HAL module driver.
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR533x_HAL_DMA_H__
#define __GR533x_HAL_DMA_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gr533x_ll_dma.h"
#include "gr533x_hal_def.h"
#include <stdbool.h>

/* Exported types ------------------------------------------------------------*/
/** @addtogroup HAL_DMA_ENUMERATIONS Enumerations
  * @{
  */

/** @defgroup HAL_DMA_state HAL DMA state
  * @{
  */

/**
  * @brief  HAL DMA State Enumerations definition
  */
typedef enum
{
    HAL_DMA_STATE_RESET             = 0x00U,  /**< DMA not yet initialized or disabled */
    HAL_DMA_STATE_READY             = 0x01U,  /**< DMA process success and ready for use   */
    HAL_DMA_STATE_BUSY              = 0x02U,  /**< DMA process is ongoing              */
    HAL_DMA_STATE_TIMEOUT           = 0x03U,  /**< DMA timeout state                   */
    HAL_DMA_STATE_ERROR             = 0x04U,  /**< DMA error state                     */
} hal_dma_state_t;
/** @} */

/** @defgroup HAL_DMA_channel HAL DMA channel
  * @{
  */

/**
  * @brief  HAL DMA Channel Enumerations definition
  */
typedef enum
{
    DMA_Channel0 = 0U,      /**< Channel 0     */
    DMA_Channel1 = 1U,      /**< Channel 1     */
    DMA_Channel2 = 2U,      /**< Channel 2     */
    DMA_Channel3 = 3U,      /**< Channel 3     */
    DMA_Channel4 = 4U,      /**< Channel 4     */
    DMA_Channel_NUM_MAX     /**< Only for check parameter, not used as input parameters. */
} dma_channel_t;
/** @} */

/** @defgroup HAL_DMA_callback_ID HAL DMA callback ID
  * @{
  */

/**
  * @brief  HAL DMA Callback ID Enumerations definition
  */
typedef enum
{
    HAL_DMA_XFER_TFR_CB_ID           = 0x00,    /**< Full transfer     */
    HAL_DMA_XFER_BLK_CB_ID           = 0x01,    /**< Block transfer    */
    HAL_DMA_XFER_ERROR_CB_ID         = 0x02,    /**< Error             */
    HAL_DMA_XFER_ABORT_CB_ID         = 0x03,    /**< Abort             */
    HAL_DMA_XFER_ALL_CB_ID           = 0x04     /**< All               */
} hal_dma_callback_id_t;
/** @} */

/** @} */


/** @addtogroup HAL_DMA_STRUCTURES Structures
  * @{
  */

/**
  * @brief  DMA LOCK Structure definition
  */
typedef struct _dma_lock_config
{
    uint32_t channel_lock_en;            /**< Specifies the dma channel lock enable.
                                             This parameter can be a value of @ref DMA_CHANNEL_LOCK_EN */

    uint32_t channel_lock_level;        /**< Specifies the dma channel lock level.
                                             This parameter can be a value of @ref DMA_CHANNEL_LOCK_LEVEL */

    uint32_t bus_lock_en;               /**< Specifies the dma bus lock enable.
                                             This parameter can be a value of @ref DMA_BUS_LOCK_EN */

    uint32_t bus_lock_level;            /**< Specifies the dma bus lock level.
                                             This parameter can be a value of @ref DMA_BUS_LOCK_LEVEL */
} dma_lock_config;

/** @} */


/** @addtogroup HAL_DMA_STRUCTURES Structures
  * @{
  */

/**
  * @brief  DMA Configuration Structure definition
  */
typedef struct _dma_init
{
    uint32_t src_request;               /**< Specifies the source request selected for the specified channel.
                                             This parameter can be a value of @ref DMA_request */

    uint32_t dst_request;               /**< Specifies the destination request selected for the specified channel.
                                             This parameter can be a value of @ref DMA_request */

    uint32_t direction;                 /**< Specifies if the data will be transferred from memory to peripheral,
                                             from memory to memory or from peripheral to memory.
                                             This parameter can be a value of @ref DMA_Data_transfer_direction */

    uint32_t src_increment;             /**< Specifies whether the srouce address register should be incremented or decrement or not.
                                             This parameter can be a value of @ref DMA_Source_incremented_mode */

    uint32_t dst_increment;             /**< Specifies whether the destination address register should be incremented or decrement or not.
                                             This parameter can be a value of @ref DMA_Destination_incremented_mode */

    uint32_t src_data_alignment;        /**< Specifies the source data width.
                                             This parameter can be a value of @ref DMA_Source_data_size */

    uint32_t dst_data_alignment;        /**< Specifies the destination data width.
                                             This parameter can be a value of @ref DMA_Destination_data_size */

    uint32_t priority;                  /**< Specifies the software priority for the DMA Channel.
                                             This parameter can be a value of @ref DMA_Priority_level */
} dma_init_t;

/** @} */

/** @addtogroup DMA_handle DMA handle
  * @{
  */

/**
  * @brief  DMA handle Structure definition
  */
typedef struct _dma_handle
{
    dma_regs_t               *p_instance;                                         /**< DMA registers base address             */

    dma_channel_t           channel;                                              /**< DMA Channel Number                  */

    dma_init_t              init;                                                 /**< DMA communication parameters        */

    hal_lock_t              lock;                                                 /**< DMA locking object                  */

    __IO hal_dma_state_t    state;                                                /**< DMA transfer state                  */

    void                    *p_parent;                                            /**< Parent object state                 */

    void                    (* xfer_tfr_callback)(struct _dma_handle *p_dma);     /**< DMA transfer complete callback      */

    void                    (* xfer_blk_callback)(struct _dma_handle *p_dma);     /**< DMA block complete callback         */

    void                    (* xfer_error_callback)(struct _dma_handle *p_dma);   /**< DMA transfer error callback         */

    void                    (* xfer_abort_callback)(struct _dma_handle *p_dma);   /**< DMA transfer abort callback         */

    __IO uint32_t           error_code;                                           /**< DMA Error code                      */

    uint32_t                retention[5];                                         /**< DMA important register information. */
} dma_handle_t;

/** @} */

/**
  * @defgroup  HAL_DMA_MACRO Defines
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup DMA_Exported_Constants DMA Exported Constants
  * @{
  */

/** @defgroup DMA_Error_Code DMA Error Code
  * @{
  */
#define HAL_DMA_ERROR_NONE              ((uint32_t)0x00000000U)    /**< No error             */
#define HAL_DMA_ERROR_TE                ((uint32_t)0x00000001U)    /**< Transfer error       */
#define HAL_DMA_ERROR_NO_XFER           ((uint32_t)0x00000004U)    /**< no ongoing transfer  */
#define HAL_DMA_ERROR_TIMEOUT           ((uint32_t)0x00000020U)    /**< Timeout error        */
#define HAL_DMA_ERROR_INVALID_PARAM     ((uint32_t)0x00000008U)    /**< Invalid parameters error */
/** @} */

/** @defgroup DMA_request DMA request definitions
  * @{
  */
/********************************* definition for DMA0 HS **************************************/
#define DMA0_REQUEST_CTE             LL_DMA0_PERIPH_CTE       /**< DMA CTE transmit request */
#define DMA0_REQUEST_PWM0            LL_DMA0_PERIPH_PWM0      /**< DMA PWM0 transmit request */
#define DMA0_REQUEST_SPIM_TX         LL_DMA0_PERIPH_SPIM_TX   /**< DMA SPIM transmit request */
#define DMA0_REQUEST_SPIM_RX         LL_DMA0_PERIPH_SPIM_RX   /**< DMA SPIM RX transmit request */
#define DMA0_REQUEST_SPIS_TX         LL_DMA0_PERIPH_SPIS_TX   /**< DMA SPIS TX transmit request */
#define DMA0_REQUEST_SPIS_RX         LL_DMA0_PERIPH_SPIS_RX   /**< DMA SPIS RX transmit request */
#define DMA0_REQUEST_UART0_TX        LL_DMA0_PERIPH_UART0_TX  /**< DMA UART0 TX transmit request */
#define DMA0_REQUEST_UART0_RX        LL_DMA0_PERIPH_UART0_RX  /**< DMA UART0 RX transmit request */
#define DMA0_REQUEST_UART1_TX        LL_DMA0_PERIPH_UART1_TX  /**< DMA UART1 TX transmit request */
#define DMA0_REQUEST_UART1_RX        LL_DMA0_PERIPH_UART1_RX  /**< DMA UART1 RX transmit request */
#define DMA0_REQUEST_SNSADC          LL_DMA0_PERIPH_SNSADC    /**< DMA SNSADC transmit request */
#define DMA0_REQUEST_I2C0_TX         LL_DMA0_PERIPH_I2C0_TX   /**< DMA peripheral type is I2C0 TX  */
#define DMA0_REQUEST_I2C0_RX         LL_DMA0_PERIPH_I2C0_RX   /**< DMA peripheral type is I2C0 RX  */
#define DMA0_REQUEST_I2C1_TX         LL_DMA0_PERIPH_I2C1_TX   /**< DMA peripheral type is I2C1 TX  */
#define DMA0_REQUEST_I2C1_RX         LL_DMA0_PERIPH_I2C1_RX   /**< DMA peripheral type is I2C1 RX  */
#define DMA0_REQUEST_MEM             LL_DMA0_PERIPH_MEM       /**< DMA is Memory transmit request */

/** @} */

/** @defgroup DMA_Data_transfer_direction DMA Data Transfer directions
  * @{
  */
#define DMA_MEMORY_TO_MEMORY         LL_DMA_DIRECTION_MEMORY_TO_MEMORY    /**< Memory to memory direction     */
#define DMA_MEMORY_TO_PERIPH         LL_DMA_DIRECTION_MEMORY_TO_PERIPH    /**< Memory to peripheral direction */
#define DMA_PERIPH_TO_MEMORY         LL_DMA_DIRECTION_PERIPH_TO_MEMORY    /**< Peripheral to memory direction */
#define DMA_PERIPH_TO_PERIPH         LL_DMA_DIRECTION_PERIPH_TO_PERIPH    /**< Peripheral to Peripheral direction */
/** @} */

/** @defgroup DMA_Source_incremented_mode DMA Source Incremented Mode
  * @{
  */
#define DMA_SRC_INCREMENT            LL_DMA_SRC_INCREMENT      /**< Source increment mode */
#define DMA_SRC_DECREMENT            LL_DMA_SRC_DECREMENT      /**< Source decrement mode */
#define DMA_SRC_NO_CHANGE            LL_DMA_SRC_NO_CHANGE      /**< Source no change mode */
/** @} */

/** @defgroup DMA_Destination_incremented_mode DMA Destination Incremented Mode
  * @{
  */
#define DMA_DST_INCREMENT            LL_DMA_DST_INCREMENT      /**< Destination increment mode */
#define DMA_DST_DECREMENT            LL_DMA_DST_DECREMENT      /**< Destination decrement mode */
#define DMA_DST_NO_CHANGE            LL_DMA_DST_NO_CHANGE      /**< Destination no change mode */
/** @} */

/** @defgroup DMA_Source_data_size DMA Source Data Size Alignment
  * @{
  */
#define DMA_SDATAALIGN_BYTE          LL_DMA_SDATAALIGN_BYTE     /**< Source data alignment : Byte     */
#define DMA_SDATAALIGN_HALFWORD      LL_DMA_SDATAALIGN_HALFWORD /**< Source data alignment : HalfWord */
#define DMA_SDATAALIGN_WORD          LL_DMA_SDATAALIGN_WORD     /**< Source data alignment : Word     */
/** @} */

/** @defgroup DMA_Destination_data_size DMA Destination Data Size Alignment
  * @{
  */
#define DMA_DDATAALIGN_BYTE          LL_DMA_DDATAALIGN_BYTE      /**< Destination data alignment : Byte     */
#define DMA_DDATAALIGN_HALFWORD      LL_DMA_DDATAALIGN_HALFWORD  /**< Destination data alignment : HalfWord */
#define DMA_DDATAALIGN_WORD          LL_DMA_DDATAALIGN_WORD      /**< Destination data alignment : Word     */
/** @} */

/** @} */

/** @defgroup DMA_Priority_level DMA Priority Level
  * @{
  */
#define DMA_PRIORITY_LOW             LL_DMA_PRIORITY_0    /**< Priority level : Low       */
#define DMA_PRIORITY_MEDIUM          LL_DMA_PRIORITY_1    /**< Priority level : Medium    */
#define DMA_PRIORITY_HIGH            LL_DMA_PRIORITY_2    /**< Priority level : High      */
#define DMA_PRIORITY_VERY_HIGH       LL_DMA_PRIORITY_3    /**< Priority level : Very High */
/** @} */

/** @defgroup DMA_CHANNEL_LOCK_EN DMA Channel Lock Enable
  * @{
  */
#define DMA_HAL_CHANNEL_LOCK_ENABLE  LL_DMA_LOCK_CH_ENABLE      /**< DMA Channel Lock Enable */
#define DMA_HAL_CHANNEL_LOCK_DISABLE LL_DMA_LOCK_CH_DISABLE     /**< DMA Channel Lock Disable */
/** @} */

/** @defgroup DMA_CHANNEL_LOCK_LEVEL DMA Channel Lock Level
  * @{
  */
#define DMA_HAL_CHANNEL_LOCK_TFR     LL_DMA_LOCK_CH_LEVEL_TFR   /**< DMA Channel Lock Over complete DMA transfer */
#define DMA_HAL_CHANNEL_LOCK_BLK     LL_DMA_LOCK_CH_LEVEL_BLK   /**< DMA Channel Lock Over complete DMA block transfer */
#define DMA_HAL_CHANNEL_LOCK_TRANS   LL_DMA_LOCK_CH_LEVEL_TRANS /**< DMA Channel Lock Over complete DMA transaction */
/** @} */

/** @defgroup DMA_BUS_LOCK_EN DMA Channel Lock Enable
  * @{
  */
#define DMA_HAL_BUS_LOCK_ENABLE     LL_DMA_LOCK_BUS_ENABLE      /**< DMA Bus Lock Enable */
#define DMA_HAL_BUS_LOCK_DISABLE    LL_DMA_LOCK_BUS_DISABLE     /**< DMA Bus Lock Disable */
/** @} */

/** @defgroup DMA_BUS_LOCK_LEVEL DMA Bus Lock Level
  * @{
  */
#define DMA_HAL_BUS_LOCK_TFR        LL_DMA_LOCK_BUS_LEVEL_TFR   /**< DMA Bus Lock Over complete DMA transfer */
#define DMA_HAL_BUS_LOCK_BLK        LL_DMA_LOCK_BUS_LEVEL_BLK   /**< DMA Bus Lock Over complete DMA block transfer */
#define DMA_HAL_BUS_LOCK_TRANS      LL_DMA_LOCK_BUS_LEVEL_TRANS /**< DMA Bus Lock Over complete DMA transaction */
/** @} */


/* Private macros ------------------------------------------------------------*/
/** @defgroup DMA_Private_Macro DMA Private Macros
  * @{
  */

/** @brief  Check if DMA instance is valid.
  * @param  __p_instance__ DMA instance.
  * @retval SET (__p_instance__ is valid) or RESET (__p_instance__ is invalid)
  */
#define IS_DMA_ALL_P_INSTANCE(__p_instance__) (((__p_instance__) == DMA0))

/** @brief  Check if DMA channel instance is valid.
  * @param  __instance__ DMA channel instance.
  * @retval SET (__instance__ is valid) or RESET (__instance__ is invalid)
  */

#define IS_DMA_ALL_INSTANCE(__instance__) (((__instance__) == DMA_Channel0) || \
                                           ((__instance__) == DMA_Channel1) || \
                                           ((__instance__) == DMA_Channel2) || \
                                           ((__instance__) == DMA_Channel3) || \
                                           ((__instance__) == DMA_Channel4))



/** @brief  Check if DMA request is valid.
  * @param  __REQUEST__ DMA request.
  * @retval SET (__REQUEST__ is valid) or RESET (__REQUEST__ is invalid)
  */

#define IS_DMA_ALL_REQUEST(__REQUEST__)   (((__REQUEST__) == DMA0_REQUEST_SPIM_TX)      || \
                                           ((__REQUEST__) == DMA0_REQUEST_SPIM_RX)      || \
                                           ((__REQUEST__) == DMA0_REQUEST_SPIS_TX)      || \
                                           ((__REQUEST__) == DMA0_REQUEST_SPIS_RX)      || \
                                           ((__REQUEST__) == DMA0_REQUEST_UART0_TX)     || \
                                           ((__REQUEST__) == DMA0_REQUEST_UART0_RX)     || \
                                           ((__REQUEST__) == DMA0_REQUEST_UART1_TX)     || \
                                           ((__REQUEST__) == DMA0_REQUEST_UART1_RX)     || \
                                           ((__REQUEST__) == DMA0_REQUEST_SNSADC)       || \
                                           ((__REQUEST__) == DMA0_REQUEST_MEM)          || \
                                           ((__REQUEST__) == DMA0_REQUEST_I2C0_TX)      || \
                                           ((__REQUEST__) == DMA0_REQUEST_I2C0_RX)      || \
                                           ((__REQUEST__) == DMA0_REQUEST_I2C1_TX)      || \
                                           ((__REQUEST__) == DMA0_REQUEST_I2C1_RX))

/** @brief  Check if DMA direction is valid.
  * @param  __DIRECTION__ DMA direction.
  * @retval SET (__DIRECTION__ is valid) or RESET (__DIRECTION__ is invalid)
  */
#define IS_DMA_DIRECTION(__DIRECTION__)   (((__DIRECTION__) == DMA_MEMORY_TO_MEMORY) || \
                                           ((__DIRECTION__) == DMA_MEMORY_TO_PERIPH) || \
                                           ((__DIRECTION__) == DMA_PERIPH_TO_MEMORY) || \
                                           ((__DIRECTION__) == DMA_PERIPH_TO_PERIPH))

/** @brief  Check if DMA buffer size is valid.
  * @param  __SIZE__ DMA buffer size.
  * @retval SET (__SIZE__ is valid) or RESET (__SIZE__ is invalid)
  */
#define IS_DMA_BUFFER_SIZE(__SIZE__)      (((__SIZE__) >= 0x1) && ((__SIZE__) <= 0xFFF))

/** @brief  Check if DMA source address increment state is valid.
  * @param  __STATE__ DMA source address increment state.
  * @retval SET (__STATE__ is valid) or RESET (__STATE__ is invalid)
  */
#define IS_DMA_SOURCE_INC_STATE(__STATE__)      (((__STATE__) == DMA_SRC_INCREMENT) || \
                                                 ((__STATE__) == DMA_SRC_DECREMENT) || \
                                                 ((__STATE__) == DMA_SRC_NO_CHANGE))

/** @brief  Check if DMA destination address increment state is valid.
  * @param  __STATE__ DMA destination address increment state.
  * @retval SET (__STATE__ is valid) or RESET (__STATE__ is invalid)
  */
#define IS_DMA_DESTINATION_INC_STATE(__STATE__) (((__STATE__) == DMA_DST_INCREMENT)  || \
                                                 ((__STATE__) == DMA_DST_DECREMENT)  || \
                                                 ((__STATE__) == DMA_DST_NO_CHANGE))

/** @brief  Check if DMA source data size is valid.
  * @param  __SIZE__ DMA source data size.
  * @retval SET (__SIZE__ is valid) or RESET (__SIZE__ is invalid)
  */
#define IS_DMA_SOURCE_DATA_SIZE(__SIZE__)       (((__SIZE__) == DMA_SDATAALIGN_BYTE)     || \
                                                 ((__SIZE__) == DMA_SDATAALIGN_HALFWORD) || \
                                                 ((__SIZE__) == DMA_SDATAALIGN_WORD))

/** @brief  Check if DMA destination data size is valid.
  * @param  __SIZE__ DMA destination data size.
  * @retval SET (__SIZE__ is valid) or RESET (__SIZE__ is invalid)
  */
#define IS_DMA_DESTINATION_DATA_SIZE(__SIZE__)  (((__SIZE__) == DMA_DDATAALIGN_BYTE)     || \
                                                 ((__SIZE__) == DMA_DDATAALIGN_HALFWORD) || \
                                                 ((__SIZE__) == DMA_DDATAALIGN_WORD ))

/** @brief  Check if DMA priority is valid.
  * @param  __PRIORITY__ DMA priority.
  * @retval SET (__PRIORITY__ is valid) or RESET (__PRIORITY__ is invalid)
  */
#define IS_DMA_PRIORITY(__PRIORITY__)   (((__PRIORITY__) == DMA_PRIORITY_LOW )   || \
                                         ((__PRIORITY__) == DMA_PRIORITY_MEDIUM) || \
                                         ((__PRIORITY__) == DMA_PRIORITY_HIGH)   || \
                                         ((__PRIORITY__) == DMA_PRIORITY_VERY_HIGH))

/** @} */

/** @} */


/* Exported functions --------------------------------------------------------*/
/** @addtogroup HAL_DMA_DRIVER_FUNCTIONS Functions
  * @{
  */

/** @defgroup DMA_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief   Initialization and de-initialization functions
 *
@verbatim
 ===============================================================================
             ##### Initialization and de-initialization functions  #####
 ===============================================================================
    [..]
    This section provides functions allowing to initialize the DMA Channel source
    and destination addresses, incrementation and data sizes, transfer direction,
    circular/normal mode selection, memory-to-memory mode selection and Channel priority value.
    [..]
    The hal_dma_init() function follows the DMA configuration procedures as described in
    reference manual.

@endverbatim
  * @{
  */

/**
 ****************************************************************************************
 * @brief  Initialize the DMA according to the specified
 *         parameters in the dma_init_t and initialize the associated handle.
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_init(dma_handle_t *p_dma);

/**
 ****************************************************************************************
 * @brief  De-initialize the DMA peripheral.
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_deinit (dma_handle_t *p_dma);

/** @} */


/** @defgroup DMA_Exported_Functions_Group2 Input and Output operation functions
 *  @brief   Input and Output operation functions
 *
@verbatim
 ===============================================================================
                      #####  IO operation functions  #####
 ===============================================================================
    [..]  This section provides functions allowing to:
      (+) Configure the source, destination address and data length and Start DMA transfer
      (+) Configure the source, destination address and data length and
          Start DMA transfer with interrupt
      (+) Abort DMA transfer
      (+) Poll for transfer complete
      (+) Handle DMA interrupt request

@endverbatim
  * @{
  */

/**
 ****************************************************************************************
 * @brief  Start the DMA Transfer.
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 * @param[in]  src_address: The source memory Buffer address
 * @param[in]  dst_address: The destination memory Buffer address
 * @param[in]  data_length: The length of data to be transferred from source to destination, ranging between 0 and 4095.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_start (dma_handle_t *p_dma, uint32_t src_address, uint32_t dst_address, uint32_t data_length);

/**
 ****************************************************************************************
 * @brief  Start the DMA Transfer whit channel lock and bus lock.
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 * @param[in]  src_address: The source memory Buffer address
 * @param[in]  dst_address: The destination memory Buffer address
 * @param[in]  data_length: The length of data to be transferred from source to destination, ranging between 0 and 4095.
 * @param[in]  lock_config: The Config of DMA channel and bus lock.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_start_lock(dma_handle_t *p_dma, uint32_t src_address, uint32_t dst_address, uint32_t data_length, dma_lock_config *lock_config);

/**
 ****************************************************************************************
 * @brief  Start the DMA Transfer with interrupt enabled & Channel Diabled.
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 * @param[in]  src_address: The source memory Buffer address
 * @param[in]  dst_address: The destination memory Buffer address
 * @param[in]  data_length: The length of data to be transferred from source to destination,  ranging between 0 and 4095.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_start_it_dc(dma_handle_t *p_dma, uint32_t src_address, uint32_t dst_address, uint32_t data_length);

/**
 ****************************************************************************************
 * @brief  Start the DMA Transfer with interrupt enabled & Channel Enabled.
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 * @param[in]  src_address: The source memory Buffer address
 * @param[in]  dst_address: The destination memory Buffer address
 * @param[in]  data_length: The length of data to be transferred from source to destination,  ranging between 0 and 4095.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_start_it(dma_handle_t *p_dma, uint32_t src_address, uint32_t dst_address, uint32_t data_length);

/**
 ****************************************************************************************
 * @brief  Start the DMA Transfer with interrupt enabled、channel lock and bus lock.
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 * @param[in]  src_address: The source memory Buffer address
 * @param[in]  dst_address: The destination memory Buffer address
 * @param[in]  data_length: The length of data to be transferred from source to destination, ranging between 0 and 4095.
 * @param[in]  lock_config: The Config of DMA channel and bus lock.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_start_it_lock(dma_handle_t *p_dma, uint32_t src_address, uint32_t dst_address, uint32_t data_length, dma_lock_config *lock_config);

/**
 ****************************************************************************************
 * @brief  Abort the DMA Transfer.
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_abort(dma_handle_t *p_dma);

/**
 ****************************************************************************************
 * @brief  Aborts the DMA Transfer in Interrupt mode.
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_abort_it(dma_handle_t *p_dma);

/**
 ****************************************************************************************
 * @brief  Polling for transfer complete.
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 * @param[in]  timeout: Timeout duration.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_poll_for_transfer(dma_handle_t *p_dma, uint32_t timeout);

/** @} */

/** @addtogroup DMA_IRQ_Handler_and_Callbacks IRQ Handler and Callbacks
  * @brief    IRQ Handler and Callbacks functions
 * @{
 */

/**
 ****************************************************************************************
 * @brief  Handle DMA interrupt request.
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 ****************************************************************************************
 */
void hal_dma_irq_handler(dma_handle_t *p_dma);

/**
 ****************************************************************************************
 * @brief  Register callbacks
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 * @param[in]  id: User Callback identifer. This parameter can be one of the following values:
 *         @arg @ref HAL_DMA_XFER_TFR_CB_ID
 *         @arg @ref HAL_DMA_XFER_BLK_CB_ID
 *         @arg @ref HAL_DMA_XFER_ERROR_CB_ID
 *         @arg @ref HAL_DMA_XFER_ABORT_CB_ID
 * @param[in]  callback: Pointer to private callbacsk function which has pointer to a dma_handle_t structure as parameter.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_register_callback(dma_handle_t *p_dma, hal_dma_callback_id_t id, void (* callback)( dma_handle_t * p_dma));

/**
 ****************************************************************************************
 * @brief  UnRegister callbacks
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 * @param[in]  id: User Callback identifer. This parameter can be a combiantion of the following values:
 *         @arg @ref HAL_DMA_XFER_TFR_CB_ID
 *         @arg @ref HAL_DMA_XFER_BLK_CB_ID
 *         @arg @ref HAL_DMA_XFER_ERROR_CB_ID
 *         @arg @ref HAL_DMA_XFER_ABORT_CB_ID
 *         @arg @ref HAL_DMA_XFER_ALL_CB_ID
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_unregister_callback(dma_handle_t *p_dma, hal_dma_callback_id_t id);

/** @} */

/** @defgroup DMA_Exported_Functions_Group3 Peripheral State and Errors functions
 *  @brief    Peripheral State and Errors functions
 *
@verbatim
 ===============================================================================
            ##### Peripheral State and Errors functions #####
 ===============================================================================
    [..]
    This subsection provides functions allowing to
      (+) Check the DMA state
      (+) Get error code

@endverbatim
  * @{
  */

/**
 ****************************************************************************************
 * @brief  Return the DMA hande state.
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 *
 * @retval ::HAL_DMA_STATE_RESET: DMA not yet initialized or disabled.
 * @retval ::HAL_DMA_STATE_READY: DMA process succeeded and ready for use.
 * @retval ::HAL_DMA_STATE_BUSY: DMA process is ongoing.
 * @retval ::HAL_DMA_STATE_TIMEOUT: DMA timeout state.
 * @retval ::HAL_DMA_STATE_ERROR: DMA error state.
 ****************************************************************************************
 */
hal_dma_state_t hal_dma_get_state(dma_handle_t *p_dma);

/**
 ****************************************************************************************
 * @brief  Return the DMA error code.
 *
 * @param[in]  p_dma: Pointer to a DMA handle which contains the configuration information for the specified DMA Channel.
 *
 * @return DMA Error Code
 ****************************************************************************************
 */
uint32_t hal_dma_get_error(dma_handle_t *p_dma);

/**
 ****************************************************************************************
 * @brief  Suspend some registers related to DMA configuration before sleep.
 * @param[in] p_dma: Pointer to a DMA handle which contains the configuration
 *                 information for the specified DMA module.
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_suspend_reg(dma_handle_t *p_dma);

/**
 ****************************************************************************************
 * @brief  Restore some registers related to DMA configuration after sleep.
 *         This function must be used in conjunction with the hal_dma_resume_reg().
 * @param[in] p_dma: Pointer to a DMA handle which contains the configuration
 *                 information for the specified DMA module.
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_dma_resume_reg(dma_handle_t *p_dma);

/**
 ****************************************************************************************
 * @brief  set the flag if DMAn has been used before sleep
 * @param[in] p_dma: Pointer to a DMA handle which contains the configuration
 *                 information for the specified DMA module.
 * @retval ::None
 ****************************************************************************************
 */
void dma_set_renew_flag(dma_handle_t *p_dma);

/**
 ****************************************************************************************
 * @brief  resume dma regs before using if just waked up from sleep /only need to clear sleep_flag
 *          if on initial or deinitial state.
 * @param[in] p_dma: Pointer to a DMA handle which contains the configuration
 *                 information for the specified DMA module.
 * @param[in] init_flag: true: use in init function or deinit function
 *                   fault: not use in init function or deinit function
 * @retval ::None
 ****************************************************************************************
 */
void dma_resume_before_using(dma_handle_t *p_dma, bool init_flag);

/**
 ****************************************************************************************
 * @brief  Suspend the register of the specified DMA channel.
 * @param[in] p_dma: Pointer to a DMA handle which contains the configuration
 *                 information for the specified DMA module.
 * @param[in] channel: dma channel,can be one of the values of dma_channel_t.
 * @retval ::None
 ****************************************************************************************
 */
void hal_dma_suspend_channel(dma_handle_t *p_dma, uint32_t channel);

/**
 ****************************************************************************************
 * @brief  Resume the register of the specified DMA channel.
 * @param[in] p_dma: Pointer to a DMA handle which contains the configuration
 *                 information for the specified DMA module.
 * @param[in] channel: dma channel,can be one of the values of dma_channel_t.
 * @retval ::None
 ****************************************************************************************
 */
void hal_dma_resume_channel(dma_handle_t *p_dma, uint32_t channel);

/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __GR533x_HAL_DMA_H__*/

/** @} */

/** @} */

/** @} */
