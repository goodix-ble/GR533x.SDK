/**
 ******************************************************************************
 *
 * @file platform_sdk.h
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
 *****************************************************************************************
 */


/**
 * @addtogroup SYSTEM
 * @{
 */
 /**
  @addtogroup Plat_SDK Platform SDK
  @{
  @brief Definitions and prototypes for the Platform SDK
 */

#ifndef _PLATFORM_SDK_H
#define _PLATFORM_SDK_H

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include "system_gr533x.h"
#include "gr533x_hal_def.h"
#include "gr533x_ll_xqspi.h"

/** @} */

/**@addtogroup PlAT_SDK_ENUM Enumerations
 * @{ */

/**@brief system clock and run mode. */
typedef enum
{
   XIP_64M = 0,            /**< XIP 64M. */
   XIP_48M,                /**< XIP 48M. */
   XIP_XO16M,              /**< XIP XO 16M. */
   XIP_24M,                /**< XIP 24M. */
   XIP_16M,                /**< XIP 16M. */
   XIP_32M,                /**< XIP 32M. */
   MIRROR_64M,             /**< MIRROR 64M. */
   MIRROR_48M,             /**< MIRROR 48M. */
   MIRROR_XO16M,           /**< MIRROR X) 16M. */
   MIRROR_24M,             /**< MIRROR 24M. */
   MIRROR_16M,             /**< MIRROR 16M. */
   MIRROR_32M,             /**< MIRROR 32M. */
} table_idx_t;

/**@brief slow clock type. */
typedef enum
{
    RC_OSC_CLK = 0,        /**< RC OSC CLOCK. */
    RTC_OSC_CLK,           /**< RTC OSC CLOCK. */
} slow_clock_type_t;


/**@brief memory power setting mode. */
typedef enum
{
   MEM_POWER_FULL_MODE = 0,   /**< Full mode. */
   MEM_POWER_AUTO_MODE,       /**< Auto mode. */
} mem_power_t;

 /**@brief system power mode. */
 typedef enum
 {
    DCDC_MODE   = 0,        /**< Start with DCDC only. */
    SYSLDO_MODE = 1,        /**< Start with SYSLDO only. */
    DCDC_MODE_2 = 2,        /**< Start with SYSLDO and work with DCDC. */
 } sys_power_t;

 /** @} */

/** @addtogroup PLAT_SDK_FUNCTIONS Functions
 * @{ */

/**@brief clock calibration notify callback. */
typedef void (*clock_calib_notify_cb_t)(float SlowClockFreq);

/**
 ****************************************************************************************
 * @brief   platform sdk init function.
 * @retval :  void
 ****************************************************************************************
 */
void platform_sdk_init(void);
void platform_sdk_warmboot_init(void);

/**
 ****************************************************************************************
 * @brief  Set the memory power management mode, which can be automatic mode or full power on mode.
 * @param[in] mem_pwr_mode : MEM_POWER_FULL_MODE or MEM_POWER_AUTO_MODE.
 * @retval : void
 ****************************************************************************************
 */
void mem_pwr_mgmt_mode_set(mem_power_t mem_pwr_mode);

/**
 ****************************************************************************************
 * @brief  Control the memory power supply by specifying start address and length.
 * @param[in] start_addr : the start address of memory that user want to config
 * @param[in] size       : the size of memory that user want to config
 * @retval : void
 ****************************************************************************************
 */
void mem_pwr_mgmt_mode_set_from(uint32_t start_addr, uint32_t size);

/**
 ****************************************************************************************
 * @brief  Enable patch function.
 * @param[in] table_idx :  Start Index Number.
 * @param[in] dur_offset   :  duration setting.
 * @param[in] ext_offset   :  ext wakeup setting.
 * @param[in] osc_offset   :  pre-wakeup setting.
 * @retval :  void
 ****************************************************************************************
 */
void system_lp_table_update_twval(table_idx_t table_idx, int16_t dur_offset, int16_t ext_offset, int16_t osc_offset);

/**
 ****************************************************************************************
 * @brief  Platform low power clock init function.
 * @param[in] sys_clock:  System clock.
 * @param[in] slow_clock:  External RTC setting or internal RNG_OSC/RC_32K setting.
 * @param[in] accuracy  :  Low speed clock accuracy.
 * @param[in] xo_offset :  Clock calibration parameter.
 * @retval :  void
 ****************************************************************************************
 */
void platform_clock_init(mcu_clock_type_t sys_clock, slow_clock_type_t slow_clock, uint16_t accuracy, uint16_t xo_offset);

/**
 ****************************************************************************************
 * @brief  Platform rc calibration function.
 * @retval :  void
 ****************************************************************************************
 */
void platform_rc_calibration(void);

/**
 ****************************************************************************************
 * @brief  Power Management warm boot.
 *
 * @retval :  void
 ****************************************************************************************
 */
void pwr_mgmt_warm_boot(void);

/**
 ****************************************************************************************
 * @brief  Handle Clock calibration interrupt request.
 * @retval :  void
 ****************************************************************************************
 */
void clock_calibration_irq_handler(void);

/**
 ****************************************************************************************
 * @brief  update comm wakeup timing settings according to lf clock
 * @retval :  void
 ****************************************************************************************
 */
void pwr_mgmt_update_comm_wkup_timing_param(void);

/**
 ****************************************************************************************
 * @brief  Platform init function.
 * @retval :  void
 ****************************************************************************************
 */
void platform_init(void);

/**
 ****************************************************************************************
 * @brief  System power starup mode.
 * @param[in] sys_power : System power up mode to be configured.
 * @retval : void
 ****************************************************************************************
 */
void system_power_mode(sys_power_t sys_power);

/**
 ****************************************************************************************
 * @brief  PMU init function.
 * @param[in] clock_type :  clock type to be configured.
 * @retval : void
 ****************************************************************************************
 */
void system_pmu_init(mcu_clock_type_t clock_type);

/**
 ****************************************************************************************
 * @brief  PMU deinit function.
 * @retval : void
 ****************************************************************************************
 */
void tx_power_15dbm_pmu_apply(void);
void tx_power_normal_pmu_apply(void);
void system_pmu_deinit(void);

/**
 ****************************************************************************************
 * @brief  the first warm boot stage.
 * @retval :  void
 ****************************************************************************************
 */
void warm_boot_first(void);

 /**
 ****************************************************************************************
 * @brief  the second warm boot stage..
 * @retval :  void
 ****************************************************************************************
 */
void warm_boot_second(void);

/**
 ****************************************************************************************
 * @brief  Warm boot process.
 * @retval :  void
 ****************************************************************************************
 */
void warm_boot(void);

/**
 ****************************************************************************************
 * @brief  PMU calibration handler.
 * @param[in] p_arg : no args.
 * @retval :  void
 ****************************************************************************************
 */
void pmu_and_clock_calibration_handler(void* p_arg);
void pmu_calibration_handler(void);

/**
 ****************************************************************************************
 * @brief  Register the clock calibration completion callback.
 * @param[in] calib_notify_cb : Calibration completion callback.
 *
 * @retval ::SDK_SUCCESS: Register callback Successfully.
 * @retval ::SDK_ERR_POINTER_NULL: calib_notify_cb is null pointer.
 * @retval ::SDK_ERR_LIST_FULL: Operation is failed, the clock calibration completion callback is full.
 ****************************************************************************************
 */
uint16_t clock_calib_notify_register(clock_calib_notify_cb_t calib_notify_cb);

/**
 ****************************************************************************************
 * @brief  Unregister the clock calibration completion callback.
 * @param[in] calib_notify_cb : Calibration completion callback.
 *
 * @retval ::SDK_SUCCESS: Unregister callback Successfully.
 * @retval ::SDK_ERR_POINTER_NULL: calib_notify_cb is null pointer.
 * @retval ::SDK_ERR_LIST_ITEM_NOT_FOUND: Operation is failed, the clock calibration completion has not been registered.
 ****************************************************************************************
 */
uint16_t clock_calib_notify_unregister(clock_calib_notify_cb_t calib_notify_cb);

/**
 ****************************************************************************************
 * @brief  stop calibration.
 * @retval :  void
 ****************************************************************************************
 */
void system_pmu_calibration_stop(void);

/**
 ****************************************************************************************
 * @brief  get ddvs ringo count
 * @retval :  ringo count
 ****************************************************************************************
 */
uint32_t sys_pmu_ddvs_ringo_get(void);

/**
 ****************************************************************************************
 * @brief  set dcdc sysldo & digocre
 * @retval :  void
 ****************************************************************************************
 */
void sys_dcdc_sysldo_dcore_init(void);

/**
 ****************************************************************************************
 * @brief  adjust digcore with ddvs
 * @param[in] clock_type :  clock type
 ****************************************************************************************
 */
void sys_pmu_ddvs_dcore_adjust(uint8_t clock_type);
/**
 ****************************************************************************************
 * @brief  adjust digcore with ddvs
 * @retval bool
 ****************************************************************************************
 */
bool sys_pmu_is_ss_chip(void);
bool sys_pmu_is_ff_chip(void);

/** @} */

#endif

/** @} */
