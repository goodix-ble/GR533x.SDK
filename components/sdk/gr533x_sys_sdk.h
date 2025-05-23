/**
 *******************************************************************************
 *
 * @file gr533x_sys.h
 *
 * @brief GR533X System API
 *
 *******************************************************************************
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
 *****************************************************************************************
 */

/**
 @addtogroup SYSTEM
 @{
 */

/**
 * @addtogroup SYS System SDK
 * @{
 * @brief Definitions and prototypes for the system SDK interface.
*/



#ifndef __GR533X_SYS_SDK_H__
#define __GR533X_SYS_SDK_H__

#include "gr533x_sys_cfg.h"
#include "gr533x_nvds.h"
#include "gr533x_pwr.h"
#include "gr5xx_fpb.h"

#include <stdint.h>
#include <stdio.h>
#include <stdbool.h>
#include <stdarg.h>

/** @addtogroup GR533X_SYS_DEFINES Defines
 * @{
 */
#define SYS_BOOT_SETTING_PATTERN          0x474F4F44
#define SYS_BOOT_SETTING_RSV_MAGIC        0xFFFFFFFF
#define SYS_BOOT_SETTING_SWD_ENABLE       0xFF
#define SYS_BOOT_SETTING_SWD_DISABLE      0xA5
#define SYS_SCA_SETTING_ADDR              0x0027F000
#define SYS_INVALID_TIMER_ID              0xFF              /**< Invalid system Timer ID. */
#define SYS_BD_ADDR_LEN                   BLE_GAP_ADDR_LEN      /**< Length of Bluetoth Device Address. */
#define SYS_CHIP_UID_LEN                  0x10              /**< Length of Bluetoth Chip UID. */
#define SYS_SET_BD_ADDR(BD_ADDR_ARRAY)    nvds_put(0xC001, SYS_BD_ADDR_LEN, BD_ADDR_ARRAY)  /**< NVDS put BD address. */
#define SYS_ROM_VERSION_ADDR              ((uint32_t)(0x200))                  /**< The rom version address. */
/** @} */

/**
 * @defgroup GR533X_SYS_TYPEDEF Typedefs
 * @{
 */
/**@brief The function pointers to register event callback. */
typedef void (*callback_t)(int);

/** @brief Timer callback type. */
typedef void (*timer_callback_t)(uint8_t timer_id);

/**@brief Printf callback type. */
typedef int (*vprintf_callback_t) (const char *fmt, va_list argp);

/**@brief raw log callback type. */
typedef uint16_t (*raw_log_send_cb_t) (uint8_t *p_data, uint16_t length);

/**@brief Low power clock update function type. */
typedef void (*void_func_t)(void);

/**@brief Low power clock update function type. */
typedef int32_t (*int_func_t)(void);

/**@brief Function type for saving user context before deep sleep. */
typedef void (*sys_context_func_t)(void);

/**@brief Error assert callback type. */
typedef void (*assert_err_cb_t)(const char *expr, const char *file, int line);

/**@brief Parameter assert callback type. */
typedef void (*assert_param_cb_t)(int param0, int param1, const char *file, int line);

/**@brief Warning assert callback type. */
typedef void (*assert_warn_cb_t)(int param0, int param1, const char *file, int line);
/** @} */

/** @addtogroup GR533X_SYS_ENUMERATIONS Enumerations
* @{*/
/**@brief Definition of Device SRAM Size Enumerations. */
typedef enum
{
    SYS_DEV_SRAM_48K          = 0x30,    /**< Supported 48K SRAM.                  */
    SYS_DEV_SRAM_64K          = 0x40,    /**< Supported 64K SRAM.                  */
    SYS_DEV_SRAM_80K          = 0x50,    /**< Supported 80K SRAM.                  */
    SYS_DEV_SRAM_96K          = 0x60,    /**< Supported 96K SRAM.                  */
} sram_size_t;

/**@brief package type. */
typedef enum
{
    PACKAGE_NONE         = 0xFFFF,  /**< Package unused. */
    PACKAGE_GR5332CENI   = 0x0200,  /**< (QFN48, 85Centigrade, 512KB Flash, 96K SRAM).  */
    PACKAGE_GR5332CENE   = 0x0201,  /**< (QFN48, 105Centigrade, 512KB Flash, 96K SRAM). */
    PACKAGE_GR5332AENI   = 0x0202,  /**< (QFN32, 85Centigrade, 512KB Flash, 96K SRAM).  */
    PACKAGE_GR5332AENE   = 0x0203,  /**< (QFN32, 105Centigrade, 512KB Flash, 96K SRAM). */
    PACKAGE_GR5331CENI   = 0x0204,  /**< (QFN48, 85Centigrade, 512KB Flash, 96K SRAM).  */
    PACKAGE_GR5331AENI   = 0x0205,  /**< (QFN32, 85Centigrade, 512KB Flash, 96K SRAM).  */
    PACKAGE_GR5330ACNI   = 0x0206,  /**< (QFN32, 85Centigrade, 256B Flash, 64K SRAM).   */
    PACKAGE_GR5330AENI   = 0x0207,  /**< (QFN32, 85Centigrade, 512B Flash, 64K SRAM).   */
    PACKAGE_GR5331DEBI   = 0x0208,  /**< (BGA45, 85Centigrade, 512B Flash, 96K SRAM).   */
} package_type_t;

/**@brief package type. */
typedef enum
{
    HW_VERSION_B2        = 0x4232,  /**< hw version B2. */
    HW_VERSION_B3        = 0x4233,  /**< hw version B3. */
} hw_version_type_t;

/** @} */

/** @addtogroup GR533X_SYS_STRUCTURES Structures
 * @{ */
/**@brief SDK version definition. */
typedef struct
{
    uint8_t  major;                         /**< Major version. */
    uint8_t  minor;                         /**< Minor version. */
    uint16_t build;                         /**< Build number. */
    uint32_t commit_id;                     /**< commit ID. */
}sdk_version_t;

/**@brief Assert callbacks.*/
typedef struct
{
    assert_err_cb_t   assert_err_cb;    /**< Assert error type callback. */
    assert_param_cb_t assert_param_cb;  /**< Assert parameter error type callback. */
    assert_warn_cb_t  assert_warn_cb;   /**< Assert warning type callback. */
}sys_assert_cb_t;

/**@brief RF trim parameter information definition. */
typedef struct
{
    int8_t  rssi_cali;    /**< RSSI calibration. */
    int8_t  tx_power;     /**< TX power. */
} rf_trim_info_t;

/**@brief ADC trim parameter information definition. */
typedef struct
{
    uint16_t adc_temp;                /**< ADC TEMP. */
    uint16_t adc_temp_ref;            /**< ADC Reference temperature*/
    uint16_t adc_vbat_div;            /**< ADC internal resistance ratio*/
    uint16_t slope_int_0p8;           /**< Internal reference 0.8v. */
    uint16_t offset_int_0p8;          /**< Internal reference 0.8v. */
    uint16_t slope_int_1p2;           /**< Internal reference 1.2v. */
    uint16_t offset_int_1p2;          /**< Internal reference 1.2v. */
    uint16_t slope_int_1p6;           /**< Internal reference 1.6v. */
    uint16_t offset_int_1p6;          /**< Internal reference 1.6v. */
    uint16_t slope_int_2p0;           /**< Internal reference 2.0v. */
    uint16_t offset_int_2p0;          /**< Internal reference 2.0v. */
    uint16_t slope_ext_1p0;           /**< External reference 1.0v. */
    uint16_t offset_ext_1p0;          /**< External reference 1.0v. */
    uint8_t  cali_mode;               /**< ADC calibration mode. */
} adc_trim_info_t;



/**@brief PMU trim parameter information definition. */
typedef struct
{
    uint8_t  io_ldo_vout;             /**< IO LDO Vout, trim step is about 13mV. */
    uint8_t  dig_ldo_1p05_coarse;     /**< DIG LDO 64m Coarse Code, trim step is about 100mV. */
    uint8_t  dig_ldo_1p05_fine;       /**< DIG LDO 64m Fine Code, trim step is about 30mV. */
    uint8_t  dig_ldo_0p9_coarse;      /**< DIG LDO 16m Coarse Code, trim step is about 100mV. */
    uint8_t  dig_ldo_0p9_fine;        /**< DIG LDO 16m Fine Code, trim step is about 30mV. */
    uint8_t  dcdc_vout1p15;           /**< DCDC 64m Vout, trim step is about 25mV. */
    uint8_t  dcdc_vout1p05;           /**< DCDC 16m Vout, trim step is about 25mV. */
    uint8_t  sys_ldo_1p15;            /**< SYSLDO 64m Vout, Trim step is about 30mV. */
    uint8_t  sys_ldo_1p05;            /**< SYSLDO 16m Vout, Trim step is about 30mV. */
} pmu_trim_info_t;

/**@brief Ringo trim information definition. */
typedef struct
{
    uint16_t ringo_dig_0p9;   /**< Ringo Value with digital core 0.9V. */
    uint16_t ringo_dig_1p05;  /**< Ringo Value with digital core 1.05V. */
} ringo_trim_info_t;

/**@brief Warm boot timing parameters(unit: us). */
typedef struct
{
    uint16_t fast_ldo_prep; /**< Fast ldo prep. */
    uint16_t hf_osc_prep;   /**< HF Osc prep. */
    uint16_t dcdc_prep;     /**< DCDC prep. */
    uint16_t dig_ldo_prep;  /**< Dig ldo prep. */
    uint16_t xo_prep;       /**< XO prep. */
    uint16_t pll_prep;      /**< PLL prep. */
    uint16_t pll_lock;      /**< PLL lock. */
    uint16_t pwr_sw_prep;   /**< PWR sw prep. */
} boot_timing_params_t;

typedef struct __attribute((packed))
{
    uint32_t    pattern;
    uint32_t    load_addr;
    uint32_t    run_addr;
    uint32_t    bin_size;
    uint32_t    fw_check_sum;
    uint8_t     check_image;
    uint8_t     boot_delay;
    uint8_t     swd_control;
    uint8_t     check_sec;
    uint8_t     pad_size;
    uint8_t     comments[20];
    uint8_t     reserved[15];
    uint32_t    setting_check_sum;
} sys_boot_setting_t;

/** @} */

/** @addtogroup GR533X_SYS_FUNCTIONS Functions
 * @{ */
/**
 *****************************************************************************************
 * @brief Malloc size memery.
 *
 * @param[in] size: memery size.
 *****************************************************************************************
 */
void *sys_malloc(uint32_t size);

/**
 *****************************************************************************************
 * @brief free memery.
 *
 * @param[in] mem_ptr: memery to be free.
 *****************************************************************************************
 */
void sys_free(void *mem_ptr);


/**
 *****************************************************************************************
 * @brief Output debug logs.
 *
 * @param[in] format: Pointer to the log information.
 *****************************************************************************************
 */
void sys_app_printf(const char *format, ...);

/**
 *****************************************************************************************
 * @brief Delay the function execution.
 *
 * @param[in] us:  Microsecond.
 *****************************************************************************************
 */
void delay_us(uint32_t us);

/**
 *****************************************************************************************
 * @brief Delay the function execution.
 *
 * @param[in] ms:  Millisecond.
 *****************************************************************************************
 */
void delay_ms(uint32_t ms);

/**
 *****************************************************************************************
 * @brief Register signal handler.
 *
 * @note This function is mainly used to register the upper-layer APP callback functions to the protocol layer,
 *       which will be invoked when there are event responses in the protocol layer.
 *****************************************************************************************
 */
void sys_signal_handler_register(callback_t isr_handler);

/**
 *****************************************************************************************
 * @brief Get SDK version.
 *
 * @note This function is mainly used to get the version of SDK.
 *
 * @param[out] p_version: The pointer to struct of @ref sdk_version_t.
 *****************************************************************************************
 */
void sys_sdk_verison_get(sdk_version_t *p_version);

/**
 *****************************************************************************************
 * @brief Save system context.
 *
 * @note This function is used to save system context before the system goes to deep sleep.
 *       Boot codes will be used to restore system context in the wakeup procedure.
 *****************************************************************************************
 */
void sys_context_save(void);

/**
 *****************************************************************************************
 * @brief Load system context.
 *
 * @note This function is used to load system context after the system goes to deep sleep.
 *****************************************************************************************
 */
void restore_sys_context(void);

/**
 *****************************************************************************************
 * @brief Encrypt and decrypt data using Present.
 *
 * @note  This function is only used to encrypt and decrypt data that needs to be stored in Flash.
 *
 * @param[in]  addr:   Operation address (Flash address minus Flash start address).
 * @param[in]  input:  Data before encryption and decryption.
 * @param[in]  size:   Data size.
 * @param[out] output: Data after encryption and decryption.
 *****************************************************************************************
 */
void sys_security_data_use_present(uint32_t addr, uint8_t *input, uint32_t size, uint8_t *output);

/**
 *****************************************************************************************
 * @brief Get the RF trim information.
 *
 * @param[out] p_rf_trim: The pointer to struct of @ref rf_trim_info_t.
 *
 * @return Result of get.
 *****************************************************************************************
 */
uint16_t sys_rf_trim_get(rf_trim_info_t *p_rf_trim);

/**
 *****************************************************************************************
 * @brief Get the ADC trim information.
 *
 * @param[out] p_adc_trim: The pointer to struct of @ref adc_trim_info_t.
 *
 * @return Result of get.
 *****************************************************************************************
 */
uint16_t sys_adc_trim_get(adc_trim_info_t *p_adc_trim);

/**
 *****************************************************************************************
 * @brief Get the PMU trim information.
 *
 * @param[out] p_pmu_trim: The pointer to struct of @ref pmu_trim_info_t.
 *
 * @return Result of get.
 *****************************************************************************************
 */
uint16_t sys_pmu_trim_get(pmu_trim_info_t *p_pmu_trim);

/**
 *****************************************************************************************
 * @brief Get the crystal trim information.
 *
 * @param[out] p_crystal_trim: offset information for crystal.
 *
 * @return Result of get.
 *****************************************************************************************
 */
uint16_t sys_crystal_trim_get(uint16_t *p_crystal_trim);

/**
 *****************************************************************************************
 * @brief Get the trim checksum.
 *
 * @param[out] p_trim_sum: The pointer to the buffer for trim checksum.
 *
 * @return Result of get.
 *****************************************************************************************
 */
uint16_t sys_trim_sum_get(uint16_t *p_trim_sum);

/**
 *****************************************************************************************
 * @brief Get the device address information.
 *
 * @param[out] p_device_addr: Bluetooth address by default.
 *
 * @return Result of get.
 *****************************************************************************************
 */
uint16_t sys_device_addr_get(uint8_t *p_device_addr);

/**
 *****************************************************************************************
 * @brief Get the HW version information.
 *
 * @param[out] p_hw_version: The pointer to the buffer for hw version.
 *
 * @return Result of get.
 *****************************************************************************************
 */
uint16_t sys_hw_version_get(hw_version_type_t *p_hw_version);
bool sys_hw_version_is_B3(void);

/**
 *****************************************************************************************
 * @brief Get the device UID information.
 *
 * @param[out] p_device_uid: Device chip UID.
 *
 * @return Result of get.
 *****************************************************************************************
 */
uint16_t sys_device_uid_get(uint8_t *p_device_uid);

/**
 *****************************************************************************************
 * @brief Get the LP gain offset 2M information.
 *
 * @param[out] p_offset: the offset of LP gain.
 *
 * @return Result of get.
 *****************************************************************************************
 */
uint16_t sys_device_lp_gain_offset_2m_get(uint8_t *p_offset);

/**
 *****************************************************************************************
 * @brief Get the RAM size information.
 *
 * @param[out] p_sram_size: The pointer to enumeration of @ref sram_size_t.
 *
 * @return Result of get.
 *****************************************************************************************
 */
uint16_t sys_device_sram_get(sram_size_t *p_sram_size);

/**
 *****************************************************************************************
 * @brief Get the chip's package type.
 *
 * @param[out] p_package_type: The pointer to enumeration of @ref package_type_t.
 *
 * @return Result of get.
 *****************************************************************************************
 */
uint16_t sys_device_package_get(package_type_t *p_package_type);
bool sys_device_is_PACKAGE_GR5331DEBI(void);

/**
 *****************************************************************************************
 * @brief Get the chip ringo trim value.
 *
 * @param[out] p_ringo_trim: The pointer to ringo trim value @ref ringo_trim_info_t.
 *
 * @return Result of get.
 *****************************************************************************************
 */
uint16_t sys_ringo_trim_get(ringo_trim_info_t *p_ringo_trim);

/**
 *****************************************************************************************
 * @brief Set low power CLK frequency.
 *
 * @param[in] user_lpclk: CLK frequency.
 *****************************************************************************************
 */
void sys_lpclk_set(uint32_t user_lpclk);

/**
 ****************************************************************************************
 * @brief Convert a duration in μs into a duration in lp cycles.
 *
 * The function converts a duration in μs into a duration in lp cycles, according to the
 * low power clock frequency (32768Hz or 32000Hz).
 *
 * @param[in] us:    Duration in μs.
 *
 * @return Duration in lpcycles.
 ****************************************************************************************
 */
uint32_t sys_us_2_lpcycles(uint32_t us);

/**
 ****************************************************************************************
 * @brief Convert a duration in lp cycles into a duration in half μs.
 *
 * The function converts a duration in lp cycles into a duration in half μs, according to the
 * low power clock frequency (32768Hz or 32000Hz).
 * @param[in]     lpcycles:    Duration in lp cycles.
 * @param[in,out] error_corr:  Insert and retrieve error created by truncating the LP Cycle Time to a half μs (in half μs).
 *
 * @return Duration in half μs
 ****************************************************************************************
 */
uint32_t sys_lpcycles_2_hus(uint32_t lpcycles, uint32_t *error_corr);

/**
 *****************************************************************************************
 * @brief Set BLE Sleep HeartBeat Period.
 * @note  The BLE Sleep HeartBeat Period is used to Wakeup BLE Periodically when BLE is IDLE.
 *
 * @param[in] period_hus: The wake up duration of BLE when BLE is IDEL.
 *            Range 0x00000000-0xFFFFFFFF (in unit of μs).
 *
 * @return Result of set.
 *****************************************************************************************
 */
uint16_t sys_ble_heartbeat_period_set(uint32_t period_hus);


/**
 *****************************************************************************************
 * @brief Get BLE Sleep HeartBeat Period.
 * @note  The BLE Sleep HeartBeat Period is used to Wakeup BLE Periodically when BLE is IDLE.
 *
 * @param[in] p_period_hus: Pointer to the wake up duration.
 *            Range 0x00000000-0xFFFFFFFF (in unit of μs).
 *
 * @return Result of get.
 *****************************************************************************************
 */
uint16_t sys_ble_heartbeat_period_get(uint32_t* p_period_hus);

/**
 ****************************************************************************************
 * @brief Set system maximum usage ratio of message heap.
 *
 * The function will used to set message ratio of message heap.
 * Valid ratio range is 50 - 100 percent in full message size.
 *
 * @param[in]     usage_ratio:  Usage ratio of message heap size.
 ****************************************************************************************
 */
void sys_max_msg_usage_ratio_set(uint8_t usage_ratio);

/**
 ****************************************************************************************
 * @brief Set system lld layer maximum usage ratio of message heap.
 *
 * The function will used to set message ratio of message heap.
 * Valid ratio range is 50 - 100 percent in full message size.
 *
 * @param[in]     usage_ratio:  Usage ratio of message heap size.
 ****************************************************************************************
 */
void sys_lld_max_msg_usage_ratio_set(uint8_t usage_ratio);

/**
 ****************************************************************************************
 * @brief Get system message heap usage ratio.
 *
 * The function will used to get message ratio of message heap.
 * This ratio is heap used percent in full message size.
 *
 * @return current heap used percent.
 ****************************************************************************************
 */
uint8_t sys_msg_usage_ratio_get(void);

/**
 ****************************************************************************************
 * @brief Get system environment heap usage ratio.
 *
 * The function will used to get environment ratio of environment heap.
 * This ratio is heap used percent in full environment size.
 *
 * @return current heap used percent.
 ****************************************************************************************
 */
uint8_t sys_env_usage_ratio_get(void);

/**
 ****************************************************************************************
 * @brief Get system attriute database heap usage ratio.
 *
 * The function will used to get attriute database ratio of attriute database heap.
 * This ratio is heap used percent in full attriute database size.
 *
 * @return current heap used percent.
 ****************************************************************************************
 */
uint8_t sys_attdb_usage_ratio_get(void);

/**
 ****************************************************************************************
 * @brief Get system non retention heap usage ratio.
 *
 * The function will used to get non retention ratio of non retention heap.
 * This ratio is heap used percent in full non retention size.
 *
 * @return current heap used percent.
 ****************************************************************************************
 */
uint8_t sys_nonret_usage_ratio_get(void);

/**
 ****************************************************************************************
 * @brief Get low power CLK frequency.
 *
 * This function is used to get the low power clock frequency.
 *
 * @return Low power CLK frequency.
 ****************************************************************************************
 */
uint32_t sys_lpclk_get(void);

/**
 ****************************************************************************************
 * @brief Get low power CLK period.
 *
 * This function is used to get the low power CLK period.
 *
 * @return Low power CLK period.
 ****************************************************************************************
 */
uint32_t sys_lpper_get(void);

/**
 *****************************************************************************************
 * @brief Register assert callbacks.
 *
 * @param[in] p_assert_cb: Pointer to assert callbacks.
 *****************************************************************************************
 */
void sys_assert_cb_register(sys_assert_cb_t *p_assert_cb);

/**
 ****************************************************************************************
 * @brief Get status of ke_event list
 *
 * @return  true: ke_event not busy, false : ke_event busy.
 ****************************************************************************************
 */
bool sys_ke_sleep_check(void);

/**
 ****************************************************************************************
 * @brief Enable swd function
 ****************************************************************************************
 */
void sys_swd_enable(void);

/**
 ****************************************************************************************
 * @brief Diable swd function
 ****************************************************************************************
 */
void sys_swd_disable(void);

/**
 ****************************************************************************************
 * @brief Set g_io_ldo_use_3p3_v  function
 ****************************************************************************************
 */
void set_io_ldo_use_3p3_v(bool flag);

/**
 ****************************************************************************************
 * @brief Set ble exchange memory base address
 * @param[in] address:  base address of ble exchange memory buffer.
 ****************************************************************************************
 */
void ble_stack_em_base_init(uint32_t address);

/**
 ****************************************************************************************
 * @brief Set ble exchange memory buffer address common offset
 * @param[in] offset:  Offset of ble exchange memory buffer.
 ****************************************************************************************
 */
void ble_em_addr_offset_set(uint16_t offset);

/**
 ****************************************************************************************
 * @brief Register the callback function of the extended llcp process
 *
 * @param[in] conn_idx:  Connect index.
 * @param[in] interval:  Connect interval (unit: 312.5 us)
 * @param[in] latency:   Connect latency (unit of connection event)
 * @param[in] superv_to: Link supervision timeout (unit of 10 ms)
 *
 * @return  Error status.
 ****************************************************************************************
 */
uint8_t sys_sdk_ultra_conn_update(uint8_t conn_idx, uint16_t interval, uint16_t latency, uint16_t superv_to);

/**
 *****************************************************************************************
 * @brief jump to app firmware.
 *
 * @param[in] fw_addr:     Firmware run address
 * @param[in] fw_bin_size: Firmware bin size
 *****************************************************************************************
 */
void sys_firmware_jump(uint32_t fw_addr, uint32_t fw_bin_size);

/** @} */
#endif

/** @} */
/** @} */
