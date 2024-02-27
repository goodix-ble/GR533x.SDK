/**
 ****************************************************************************************
 *
 * @file    gr533x_hal_exflash.h
 * @author  BLE Driver Team
 * @brief   Header file containing functions prototypes of EXFLASH HAL library.
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

/** @defgroup HAL_EXFLASH EXFLASH
  * @brief exFlash HAL module driver.
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR533x_HAL_EXFLASH_H__
#define __GR533x_HAL_EXFLASH_H__

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gr533x_ll_xqspi.h"
#include "gr533x_hal_xqspi.h"
#include "gr533x_hal_def.h"

/* Exported types ------------------------------------------------------------*/
/**
  * @defgroup  HAL_EXFLASH_MACRO Defines
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup EXFLASH_EXPORTED_CONSTANTS EXFLASH Exported Constants
  * @{
  */

/** @defgroup EXFLASH_ERROR_CODE EXFLASH Error Code
  * @{
  */
#define EXFLASH_ERROR_NONE                ((uint32_t)0x00000000) /**< No error                */
#define EXFLASH_ERROR_TIMEOUT             ((uint32_t)0x00000001) /**< Timeout error           */
#define EXFLASH_ERROR_STATUS              ((uint32_t)0x00000002) /**< Timeout error           */
#define EXFLASH_ERROR_TRANSFER            ((uint32_t)0x00000003) /**< Transfer error          */
#define EXFLASH_ERROR_ID                  ((uint32_t)0x00000004) /**< Flash ID error          */
#define EXFLASH_ERROR_QUAD                ((uint32_t)0x00000005) /**< Quad mode error         */
#define EXFLASH_ERROR_INVALID_PARAM       ((uint32_t)0x00000006) /**< Invalid parameters error */
#define EXFLASH_ERROR_INIT                ((uint32_t)0x00000007) /**< Invalid parameters error */
#define EXFLASH_ERROR_DEINIT              ((uint32_t)0x00000008) /**< Invalid parameters error */
#define EXFLASH_ERROR_WAKEUP              ((uint32_t)0x00000009) /**< Invalid parameters error */
#define EXFLASH_ERROR_DEEPSLEEP           ((uint32_t)0x0000000A) /**< Invalid parameters error */
#define EXFLASH_ERROR_SUSPEND             ((uint32_t)0x0000000B) /**< Invalid parameters error */
#define EXFLASH_ERROR_RESUME              ((uint32_t)0x0000000C) /**< Invalid parameters error */
#define EXFLASH_ERROR_LOCK                ((uint32_t)0x0000000D) /**< Invalid parameters error */
#define EXFLASH_ERROR_UNLOCK              ((uint32_t)0x0000000E) /**< Invalid parameters error */
#define EXFLASH_ERROR_RESET               ((uint32_t)0x0000000F) /**< Invalid parameters error */
#define EXFLASH_ERROR_ENABLE_QUAD         ((uint32_t)0x00000010) /**< Invalid parameters error */
#define EXFLASH_ERROR_BUSY                ((uint32_t)0x00000011) /**< Invalid parameters error */
/** @} */

/** @defgroup EXFLASH_PROTECTED_AREA_SIZE EXFLASH Protected Area Sizes
  * @{
  */
#define EXFLASH_PROTECT_AREA_00000        0x00   /**< If CMP set to 0, Non-Protection blocks. If CMP set to 1, All Block Protected. */
#define EXFLASH_PROTECT_AREA_00001        0x01   /**< If CMP set to 0, the protected data portion is the upper 1/8 of flash memory,
                                                      If CMP set to 1, the protected data portion is the lower 7/8 of flash memory */
#define EXFLASH_PROTECT_AREA_00010        0x02   /**< If CMP set to 0, the protected data portion is the upper 1/4 of flash memory,
                                                      If CMP set to 1, the protected data portion is the lower 3/4 of flash memory */
#define EXFLASH_PROTECT_AREA_00011        0x03   /**< If CMP set to 0, the protected data portion is the upper 1/2 of flash memory,
                                                      If CMP set to 1, the protected data portion is the lower 1/2 of flash memory */
#define EXFLASH_PROTECT_AREA_01001        0x09   /**< If CMP set to 0, the protected data portion is the lower 1/8 of flash memory,
                                                      If CMP set to 1, the protected data portion is the upper 7/8 of flash memory */
#define EXFLASH_PROTECT_AREA_01010        0x0A   /**< If CMP set to 0, the protected data portion is the lower 1/4 of flash memory,
                                                      If CMP set to 1, the protected data portion is the upper 3/4 of flash memory */
#define EXFLASH_PROTECT_AREA_01011        0x0B   /**< If CMP set to 0, the protected data portion is the lower 1/2 of flash memory,
                                                      If CMP set to 1, the protected data portion is the upper 1/2 of flash memory */
#define EXFLASH_PROTECT_AREA_00100        0x04   /**< If CMP set to 0, All Block Protected,  If CMP set to 1, Non-Protection blocks */
#define EXFLASH_PROTECT_AREA_10001        0x11   /**< If CMP set to 0, the protected data portion is the upper 1/128 of flash memory,
                                                      If CMP set to 1, the protected data portion is the lower 127/128 of flash memory */
#define EXFLASH_PROTECT_AREA_10010        0x12   /**< If CMP set to 0, the protected data portion is the upper 1/64 of flash memory,
                                                      If CMP set to 1, the protected data portion is the lower 63/64 of flash memory */
#define EXFLASH_PROTECT_AREA_10011        0x13   /**< If CMP set to 0, the protected data portion is the upper 1/32 of flash memory,
                                                      If CMP set to 1, the protected data portion is the lower 31/32 of flash memory */
#define EXFLASH_PROTECT_AREA_10100        0x14   /**< If CMP set to 0, the protected data portion is the upper 1/16 of flash memory,
                                                      If CMP set to 1, the protected data portion is the lower 15/16 of flash memory */
#define EXFLASH_PROTECT_AREA_10110        0x16   /**< If CMP set to 0, the protected data portion is the upper 1/16 of flash memory,
                                                      If CMP set to 1, the protected data portion is the lower 15/16 of flash memory */
#define EXFLASH_PROTECT_AREA_11001        0x19   /**< If CMP set to 0, the protected data portion is the lower 1/128 of flash memory,
                                                      If CMP set to 1, the protected data portion is the upper 127/128 of flash memory */
#define EXFLASH_PROTECT_AREA_11010        0x1A   /**< If CMP set to 0, the protected data portion is the lower 1/64 of flash memory,
                                                      If CMP set to 1, the protected data portion is the upper 63/64 of flash memory */
#define EXFLASH_PROTECT_AREA_11011        0x1B   /**< If CMP set to 0, the protected data portion is the lower 1/32 of flash memory,
                                                      If CMP set to 1, the protected data portion is the upper 31/32 of flash memory */
#define EXFLASH_PROTECT_AREA_11100        0x1C   /**< If CMP set to 0, the protected data portion is the lower 1/16 of flash memory,
                                                      If CMP set to 1, the protected data portion is the upper 15/16 of flash memory */
#define EXFLASH_PROTECT_AREA_11110        0x1E   /**< If CMP set to 0, the protected data portion is the lower 1/16 of flash memory,
                                                      If CMP set to 1, the protected data portion is the upper 15/16 of flash memory */
#define EXFLASH_PROTECT_AREA_11111        0x1F   /**< If CMP set to 0, All Block Protected,  If CMP set to 1, Non-Protection blocks */
/** @} */

/** @defgroup EXFLASH_OTP_LOCK EXFLASH OTP Locked
  * @{
  */
#define EXFLASH_LOCK_OTP1                 0x01   /**< Security register #1  */
#define EXFLASH_LOCK_OTP2                 0x02   /**< Security register #2  */
#define EXFLASH_LOCK_OTP3                 0x04   /**< Security register #3  */
/** @} */

/** @defgroup EXFLASH_ERASE_TYPE EXFLASH Erase Type
  * @{
  */
#define EXFLASH_ERASE_SECTOR              0      /**< Sector erase */
#define EXFLASH_ERASE_BLOCK32K            1      /**< block32 erase   */
#define EXFLASH_ERASE_BLOCK               2      /**< block erase */
#define EXFLASH_ERASE_CHIP                3      /**< Chip erase   */
/** @} */

/** @defgroup EXFLASH_BLOCK_PROTECT EXFLASH Block Protect
  * @{
  */
#define EXFLASH_SINGLE_PAGE_TYPE          0      /**< single page */
#define EXFLASH_DUAL_PAGE_TYPE            1      /**< dual page   */
/** @} */

/** @defgroup EXFLASH_OTP_ADDR EXFLASH OTP Address
  * @{
  */
#define EXFLASH_OTP_BASEADDR1             0x001000   /**< Security register #1  */
#define EXFLASH_OTP_BASEADDR2             0x002000   /**< Security register #2  */
#define EXFLASH_OTP_BASEADDR3             0x003000   /**< Security register #2  */
/** @} */


/** @defgroup EXFLASH_SIZE_INFO EXFLASH Size Information
  * @{
  */
#define EXFLASH_SIZE_PAGE_BYTES           ((uint32_t)256)      /**< Page size in Bytes     */
#define EXFLASH_SIZE_SECTOR_BYTES         ((uint32_t)4096)     /**< Sector size in Bytes   */
#define EXFLASH_SIZE_BLOCK_32K_BYTES      ((uint32_t)32768)    /**< block_32K size in Bytes   */
#define EXFLASH_SIZE_BLOCK_BYTES          ((uint32_t)65536)    /**< block size in Bytes   */

#define EXFLASH_SIZE_CHIP_BYTES           ((uint32_t)0x800000) /**< Chip size in Bytes     */
#define EXFLASH_START_ADDR                FLASH_BASE           /**< Flash start address    */
#define EXFLASH_SIZE                      GR533X_FLASH_SIZE    /**< Flash size             */
#define EXFLASH_END_ADDR                  (EXFLASH_START_ADDR + EXFLASH_SIZE) /**< Flash end address    */

#define EXFLASH_ALIAS_OFFSET              (0x02000000UL)       /**< Alias address offset   */
/** @} */

/** @} */

/** @} */

/** @addtogroup HAL_EXFLASH_ENUMERATIONS Enumerations
  * @{
  */
enum
{
    EXFLASH_CONFIG_CACHE_MODE             = 0x00,
    EXFLASH_CONFIG_READ_CMD               = 0x01,
    EXFLASH_CONFIG_BAUD_RATE              = 0x02,
    EXFLASH_CONFIG_CLOCK_MODE             = 0x03,
    EXFLASH_CONFIG_CACHE_FLUSH            = 0x04,
    EXFLASH_CONFIG_PAGE_TYPE              = 0x05,
};
/** @} */

/** @addtogroup HAL_EXFLASH_STRUCTURES Structures
  * @{
  */
/**
  * @brief exFlash AC characteristics
  */
typedef struct _exflash_timing_param
{
    uint8_t  flash_tVSL;       /**< VCC(min.) to device operation. Uint: 10us */

    uint8_t  flash_tESL;       /**< Erase suspend latency. Uint: 5us */

    uint8_t  flash_tPSL;       /**< Program suspend latency. Uint: 5us */

    uint8_t  flash_tPRS;       /**< Latency between program resume and next suspend. Uint: 5us */

    uint8_t  flash_tERS;       /**< Latency between erase resume and next suspend. Uint: 5us */

    uint8_t  flash_tDP;        /**< CS# High to Deep Power-down Mode. Uint: 5us */

    uint8_t  flash_tRES2;      /**< CS# High To Standby Mode With Electronic Signature Read. Uint: 5us */

    uint8_t  flash_tRDINT;     /**< Read status register interval when wait busy. Uint: 5us */
} exflash_timing_param_t;

/**
  * @brief HP Mode structure definition
  */
typedef ll_xqspi_hp_init_t exflash_hp_init_t;

/**
  * @brief EXFLASH function Structure definition
  */
typedef struct
{
    uint32_t (*p_exflash_config)(uint32_t configure, uint32_t value);                /**< Flash parameter configuration */
    uint32_t (*p_exflash_enable_quad)(ll_xqspi_hp_init_t hp_init);                   /**< Enable Quad mode to allow Quad operation */
    uint32_t (*p_exflash_read)(uint32_t addr, uint8_t *p_data, uint32_t size);       /**< Read an amount of data with specified instruction and address from flash */
    uint32_t (*p_exflash_write)(uint32_t addr, uint8_t *p_data, uint32_t size);      /**< Write an amount of data with specified instruction and address to flash */
    uint32_t (*p_exflash_erase)(uint32_t erase_type, uint32_t addr, uint32_t size);  /**< Erase flash region */
    uint32_t (*p_exflash_block_protect)(uint32_t cmp, uint32_t bp);                  /**< Lock area of flash to be software protected against Write and Erase operation */
    uint32_t (*p_exflash_suspend)(void);                                             /**< Suspend flash pragram/erase */
    uint32_t (*p_exflash_resume)(void);                                              /**< Resume flash pragram/erase */
    uint32_t (*p_exflash_deepsleep)(void);                                           /**< The exFlash will go to the Deep Power-Down Mode */
    uint32_t (*p_exflash_wakeup)(void);                                              /**< ExFlash will be released from Deep Power-Down Mode */
    uint32_t (*p_exflash_sr_erase)(uint32_t addr);                                   /**< Erase single flash security register */
    uint32_t (*p_exflash_sr_program)(uint32_t addr, uint8_t *p_data, uint32_t size); /**< Write an amount of data into flash security register */
    uint32_t (*p_exflash_sr_read)(uint32_t addr, uint8_t *p_data, uint32_t size);    /**< Read an amount of data from flash security register */
    uint32_t (*p_exflash_sr_protect)(uint32_t lb);                                   /**< This function provide the write protect control and status to the Security Registers */
}exflash_func_t;
/** @} */

/**
  * @defgroup  HAL_EXFLASH_MACRO Defines
  * @{
  */

/** @defgroup EXFLASH_EXPORTED_CONSTANTS EXFLASH Exported Constants
  * @{
  */

/** @defgroup EXFLASH_RETRY_DEFINITION EXFLASH Repeat Times definition
  * @{
  */
#define HAL_EXFLASH_RETRY_DEFAULT_VALUE     ((uint32_t)400000)          /**< 400000 times */
/** @} */

/** @} */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup EXFLASH_EXPORTED_MACROS EXFLASH Exported Macros
  * @{
  */

/** @brief  Enable the specified exFlash power.
  * @retval None
  */
#define __HAL_EXFLASH_POWER_ON()                                    ll_xqspi_enable_exflash_power()

/** @brief  Disable the specified exFlash power.
  * @retval None
  */
#define __HAL_EXFLASH_POWER_OFF()                                   ll_xqspi_disable_exflash_power()

/** @} */

/* Private macros ------------------------------------------------------------*/
/** @defgroup EXFLASH_PRIVATE_MACRO EXFLASH Private Macros
  * @{
  */

/** @} */

/** @} */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup HAL_EXFLASH_DRIVER_FUNCTIONS Functions
  * @{
  */

/** @defgroup EXFLASH_Exported_Functions_Group1 Initialization and de-initialization functions
 *  @brief    Initialization and de-initialization functions
 *
@verbatim
 ===============================================================================
              ##### Initialization and de-initialization functions #####
 ===============================================================================
    [..]  This subsection provides a set of functions allowing to initialize and
          de-initialize the exFlash peripheral:

      (+) User must implement hal_exflash_msp_init() function in which he configures
          all related peripherals resources (GPIO, DMA, IT and NVIC ).

      (+) Call the function hal_exflash_deinit() to restore the default configuration
          of the selected exFlash peripheral.

@endverbatim
  * @{
  */

/**
 ****************************************************************************************
 * @brief  Initialize the exFlash according to the specified parameters
 *         in the exflash_init_t and initialize the associated handle.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
uint32_t hal_exflash_init(exflash_func_t *exflash_func);

/** @} */

/** @defgroup EXFLASH_EXPORTED_FUNCTIONS_GROUP2 IO operation functions
 *  @brief   Data transfers functions
 *
@verbatim
  ==============================================================================
                      ##### IO operation functions #####
 ===============================================================================
 [..]
    This subsection provides a set of functions allowing to manage the exFlash
    data transfers.

    [..] The exFlash supports XIP and QSPI mode:

    (#) There are only one modes of transfer:
       (++) Blocking mode: The communication is performed in polling mode.
            The HAL status of all data processing is returned by the same function
            after finishing transfer.

@endverbatim
  * @{
  */
/**
 ****************************************************************************************
 * @brief  Configure flash electrical characteristic parameters
 *
 * @param[in] p_time: flash timing characteristics
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
*/
void hal_exflash_timing_set(exflash_timing_param_t *p_time);

/**
 ****************************************************************************************
 * @brief  Get flash id and size
 *
 * @param[out] id: Pointer to flash id
 * @param[out] size: Pointer to flash size
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
*/
void hal_exflash_get_info(uint32_t *id, uint32_t *size);


/**
 ****************************************************************************************
 * @brief  flash parameter configuration
 *
 * @param[in] configure: flash parameter configuration item
 * @param[in] value: flash parameter configuration value
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
*/
uint32_t hal_exflash_config(uint32_t configure, uint32_t value);

/**
 ****************************************************************************************
 * @brief  Enable Quad mode to allow Quad operation.
 *
 * @note   This function is used only in Mirror Mode.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
uint32_t hal_exflash_enable_quad(ll_xqspi_hp_init_t hp_init);


/**
 ****************************************************************************************
 * @brief  Write an amount of data with specified instruction and address to flash.
 *
 * @note   This function is used only in Indirect Write Mode. In secure mode, address alignment requires 4 bytes.
 *
 * @param[in]  addr: Address to write data in flash, start at @ref EXFLASH_START_ADDR.
 * @param[in]  p_data: Pointer to data buffer
 * @param[in]  size: Size of buffer bytes
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
uint32_t hal_exflash_write(uint32_t addr, uint8_t *p_data, uint32_t size);

/**
 ****************************************************************************************
 * @brief  Read an amount of data with specified instruction and address from flash.
 *
 * @note   This function is used only in non-encrypted Indirect Read Mode.
 *
 * @param[in]  addr: Address to read data in flash, start at @ref EXFLASH_START_ADDR.
 * @param[out] p_data: Pointer to data buffer
 * @param[in]  size: Size of buffer bytes
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
uint32_t hal_exflash_read(uint32_t addr, uint8_t *p_data, uint32_t size);

/**
 ****************************************************************************************
 * @brief  Erase flash region.
 *
 * @note   All sectors that have address in range of [addr, addr+len] will be erased. If addr is not sector aligned,
 *         preceding data on the sector that addr belongs to will also be erased. If (addr + size) is not sector
 *         aligned, the whole sector will also be erased. If erase_type is @ref EXFLASH_ERASE_CHIP , all data in flash
 *         will be erased ignored addr and size.
 *
 * @param[in]  erase_type: Erase flash with page/sector/chip.
 *                    @arg @ref EXFLASH_ERASE_SECTOR
 *                    @arg @ref EXFLASH_ERASE_CHIP
 * @param[in]  addr: Address to erased data in flash, start at @ref EXFLASH_START_ADDR.
 * @param[in]  size: Size of erased bytes.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
uint32_t hal_exflash_erase(uint32_t erase_type, uint32_t addr, uint32_t size);

/**
 ****************************************************************************************
 * @brief  Lock area of flash to be software protected against Write and Erase operation..
 *
 * @param[in] cmp: It is used in conjunction the BPs bits to provide more flexibility for the array protection.
 * @param[in] bp: Specifies the value to be written to the selected bit.
 *         This parameter can be one of the EXFLASH_PROTECTED_AREA_SIZE values:
 *            @arg @ref EXFLASH_PROTECT_AREA_00000
 *            @arg @ref EXFLASH_PROTECT_AREA_00001
 *            @arg @ref EXFLASH_PROTECT_AREA_00010
 *            @arg @ref EXFLASH_PROTECT_AREA_00011
 *            @arg @ref EXFLASH_PROTECT_AREA_01001
 *            @arg @ref EXFLASH_PROTECT_AREA_01010
 *            @arg @ref EXFLASH_PROTECT_AREA_01011
 *            @arg @ref EXFLASH_PROTECT_AREA_00100
 *            @arg @ref EXFLASH_PROTECT_AREA_10001
 *            @arg @ref EXFLASH_PROTECT_AREA_10010
 *            @arg @ref EXFLASH_PROTECT_AREA_10011
 *            @arg @ref EXFLASH_PROTECT_AREA_10100
 *            @arg @ref EXFLASH_PROTECT_AREA_10110
 *            @arg @ref EXFLASH_PROTECT_AREA_11001
 *            @arg @ref EXFLASH_PROTECT_AREA_11010
 *            @arg @ref EXFLASH_PROTECT_AREA_11011
 *            @arg @ref EXFLASH_PROTECT_AREA_11100
 *            @arg @ref EXFLASH_PROTECT_AREA_11110
 *            @arg @ref EXFLASH_PROTECT_AREA_11111
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
uint32_t hal_exflash_block_protect(uint32_t cmp, uint32_t bp);

/**
 ****************************************************************************************
 * @brief  the exFlash will go to the Deep Power-Down Mode.
 *
 * @note   This function is used only in Mirror Mode.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
uint32_t hal_exflash_deepsleep(void);

/**
 ****************************************************************************************
 * @brief  exFlash will be released from Deep Power-Down Mode.
 *
 * @note   This function is used only in Mirror Mode.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
uint32_t hal_exflash_wakeup(void);

/**
 ****************************************************************************************
 * @brief  Erase single flash security register.
 *
 * @note   This function erase only single security register.
 *         If initial_mode is XIP, it will swich to QSPI mode to execute command and switch to XIP mode finally.
 *
 * @param[in]  addr: Security Registers address of flash
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
uint32_t hal_exflash_sr_erase(uint32_t addr);

/**
 ****************************************************************************************
 * @brief  Write an amount of data into flash security register
 *
 * @note   This function is used only in non-encrypted Indirect Write Mode.
 *         If initial_mode is XIP, it will swich to QSPI mode to execute command and switch to XIP mode finally.
 *
 * @param[in]  addr: Security Registers address of flash
 * @param[out] p_data: Pointer to data buffer
 * @param[in]  size: Size of data buffer bytes, and need be smaller than single security register
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
uint32_t hal_exflash_sr_program(uint32_t addr, uint8_t *p_data, uint32_t size);

/**
 ****************************************************************************************
 * @brief  Read an amount of data from flash security register
 *
 * @note   This function is used only in non-encrypted Indirect Read Mode.
 *         If initial_mode is XIP, it will swich to QSPI mode to execute command and switch to XIP mode finally.
 *
 * @param[in]  addr: Security Registers address of flash
 * @param[out] p_data: Pointer to data buffer
 * @param[in]  size: Size of data buffer bytes, and need be smaller than single security register
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
uint32_t hal_exflash_sr_read(uint32_t addr, uint8_t *p_data, uint32_t size);

/**
 ****************************************************************************************
 * @brief  This function provide the write protect control and status to the Security Registers.
 *
 * @note   The LB3-BL1bits of flash status register are One Time Programmable, once its set to 1, 
 *         the Security Registers will become read-only permanently.
 *
 * @param[in] lb: Locked security registers.
 *         This parameter can be a combination of the following values:
 *         @arg @ref EXFLASH_LOCK_OTP1
 *         @arg @ref EXFLASH_LOCK_OTP2
 *         @arg @ref EXFLASH_LOCK_OTP3
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
uint32_t hal_exflash_sr_protect(uint32_t lb);

/**
 ****************************************************************************************
 * @brief  This function reads the status register of a flash.
 *
 * @note The status register is a 16-bit register that provides information about the flash operation status.
 *
 * @param[in] p_reg_status: Pointer of status register.
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_exflash_read_status_reg(uint16_t* p_reg_status);

/**
 ****************************************************************************************
 * @brief  This function writes the status register of a flash.
 *
 * @note The status register is a 16-bit register that provides information about the flash operation status.
 *
 * @param reg_status: An integer value representing the content to be written to the flash status register.
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_exflash_write_status_reg(uint16_t reg_status);

/**
 ****************************************************************************************
 * @brief  This function serves to read UID of flash
 *
 * @param[out]  uid: store 16 Byte flash UID
 *
 * @retval ::HAL_OK: Operation is OK.
 * @retval ::HAL_ERROR: Parameter error or operation not supported.
 * @retval ::HAL_BUSY: Driver is busy.
 * @retval ::HAL_TIMEOUT: Timeout occurred.
 ****************************************************************************************
 */
hal_status_t hal_exflash_read_uid(uint8_t *uid);
/** @} */

/** @} */

#ifdef __cplusplus
}
#endif

#endif /* __GR533x_HAL_EXFLASH_H__ */

/** @} */

/** @} */

/** @} */
