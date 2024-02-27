/**************************************************************************//**
 * @file     gr53xx_int.h
 * @brief    CMSIS Cortex-M# Core Peripheral Access Layer Header File for
 *           Device gr552xx
 * @version  V1.00
 * @date     03. Feb 2020
 ******************************************************************************/
/*
 * Copyright (c) 2016-2020, Shenzhen Huiding Technology Co., Ltd
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/** @addtogroup Device_Included
  * @{
  */

/** @addtogroup GR552xx_int
  * @{
  */

#ifndef __GR53xx_INT_H__
#define __GR53xx_INT_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "core_cm4.h"             /*      Cortex-M4 processor and core peripherals */
#include <stdint.h>

#if   defined (__CC_ARM)
    #pragma push
    #pragma anon_unions
#elif defined (__ICCARM__)
    #pragma language=extended
#elif defined(__ARMCC_VERSION) && (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic push
    #pragma clang diagnostic ignored "-Wc11-extensions"
    #pragma clang diagnostic ignored "-Wreserved-id-macro"
#elif defined (__GNUC__)
    /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
    /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
    #pragma warning 586
#elif defined (__CSMC__)
    /* anonymous unions are enabled by default */
#else
    #warning Not supported compiler type
#endif

/* ================================================================================================================= */
/* ================                       Device Specific Peripheral Section                        ================ */
/* ================================================================================================================= */

/** @addtogroup Peripheral_registers_structures
  * @{
  */

/**
  * @brief MCU Retention
  */

typedef struct _mcu_pad_ctrl_regs
{
    __IOM uint32_t DPAD_MUX[5];             /**< DPAD mux selction Register,                                                      Address offset: 0x0000 */
    __IOM uint32_t AON_PAD_MUX[2];          /**< AON PAD mux selction Register,                                                   Address offset: 0x0014 */
    __IOM uint32_t MSIO_PAD_MUX[3];         /**< MSIO PAD mux selction Register,                                                  Address offset: 0x001C */
    __IOM uint32_t PAD_IE_AUTO_EN;          /**< Auto IE of dpad, msio pad and aon pad,                                           Address offset: 0x0028 */
    __IOM uint32_t DPAD_IE_BUS;             /**< Input enable, Logic HIGH enables the input buffer                                Address offset: 0x002C */
    __IOM uint32_t DPAD_PE_BUS;             /**< Pull enable Logic HIGH enables weak pull device                                  Address offset: 0x0030 */
    __IOM uint32_t DPAD_PS_BUS;             /**< Pull select. Logic HIGH selects pull-up, logic LOW selected pulldown,            Address offset: 0x0034 */
    __IOM uint32_t DPAD_IS_BUS;             /**< Input select Logic LOW selects CMOS input, and logic HIGH selects Schmitt input, Address offset: 0x0038 */
    __IOM uint32_t DPAD_SR_BUS;             /**< Logic HIGH selects slow slew rate, logic LOW selects fast slew rate.             Address offset: 0x003C */
    __IOM uint32_t DPAD_DS0_BUS;            /**< Used to select output drive strength..,                                          Address offset: 0x0040 */
    __IOM uint32_t DPAD_DS1_BUS;            /**< Used to select output drive strength.,                                           Address offset: 0x0044 */
    __IOM uint32_t DPAD_POE_BUS;            /**< Parametric inverted data for PAD Logic LOW forces PO HIGH,                       Address offset: 0x0048 */
} mcu_pad_ctrl_reg_t;

/**
  * @brief AON_CTL
  */
typedef struct _aon_ctl_regs
{
    __IOM uint32_t MCU_CLK_CTRL;              /**< MCU Clock select Register,                                            Address offset: 0x0000 */
    __IOM uint32_t MCU_MISC_CFG;              /**< MCU misc settings Register,                                           Address offset: 0x0004 */
    __IOM uint32_t XO_CTRL;                   /**< XO control Register,                                                  Address offset: 0x0008 */
    __IOM uint32_t FLASH_CACHE_CTRL0;         /**< flash cache control Register 0,                                       Address offset: 0x000C */
    __IOM uint32_t FLASH_CACHE_CTRL1;         /**< flash cache control Register 1,                                       Address offset: 0x0010 */
    __OM  uint32_t DIGIO_FST_CLK;             /**< Clock for digital IO LDO,                                             Address offset: 0x0014 */
    __IOM uint32_t AON_CLK;                   /**< Aon Fast clock Select Register,                                       Address offset: 0x0018 */
    __IOM uint32_t RESERVED0[1];              /**< RESERVED,                                                             Address offset: 0x001C */
    __IOM uint32_t TPP_ANA;                   /**< TPP ANA Register,                                                     Address offset: 0x0020 */
    __IOM uint32_t AON_PWR_SAVING;            /**< TPP ANA Register,                                                     Address offset: 0x0024 */
    __IOM uint32_t RESERVED1[22];             /**< RESERVED,                                                             Address offset: 0x0028 */
    __IOM uint32_t MCU_WAKEUP_CTRL;           /**< MCU wake up control Register,                                         Address offset: 0x0080 */
    __IOM uint32_t AON_SLP_EVENT;             /**< AON sleep event Register,                                             Address offset: 0x0084 */
    __IOM uint32_t RESERVED2[1];              /**< RESERVED,                                                             Address offset: 0x0088 */
    __IOM uint32_t AON_SLP_EVENT_RAW;         /**< AON sleep event Register,                                             Address offset: 0x008C */
    __IOM uint32_t RESERVED3[2];              /**< RESERVED,                                                             Address offset: 0x0090 */
    __IOM uint32_t AON_IRQ;                   /**< AON IRQ Register,                                                     Address offset: 0x0098 */
    __IOM uint32_t AON_IRQ_EN;                /**< AON IRQ mask Register,                                                Address offset: 0x009C */
    __IOM uint32_t RESERVED4[2];              /**< RESERVED,                                                             Address offset: 0x00A0 */
    __IOM uint32_t AON_DBG_CTRL;              /**< AON sleep control Register,                                           Address offset: 0x00A8 */
    __IOM uint32_t RESERVED5[69];             /**< RESERVED,                                                             Address offset: 0x00AC */
    __IOM uint32_t MEM_MARGIN;                /**< memory margin Register,                                               Address offset: 0x01C0 */
    __IOM uint32_t MEM_PARAM;                 /**< memory param Register ,                                               Address offset: 0x01C4 */
    __IOM uint32_t RESERVED6[14];             /**< RESERVED,                                                             Address offset: 0x01C8 */
    __IOM uint32_t EXT_WAKEUP_CTRL0;          /**< external wake up control Register 0,                                  Address offset: 0x0200 */
    __IOM uint32_t EXT_WAKEUP_CTRL1;          /**< external wake up control Register 1,                                  Address offset: 0x0204 */
    __IOM uint32_t EXT_WAKEUP_STAT;           /**< external wake up status Register,                                     Address offset: 0x0208 */
    __IOM uint32_t RESERVED7[29];             /**< RESERVED,                                                             Address offset: 0x020C */
    __IOM uint32_t COMM_CTRL;                 /**< comm control Register,                                                Address offset: 0x0280 */
    __IOM uint32_t BLE_MISC;                  /**< BLE misc Register,                                                    Address offset: 0x0284 */
    __IOM uint32_t COMM_TIMER_CFG0;           /**< comm configure Register 0,                                            Address offset: 0x0288 */
    __IOM uint32_t COMM_TIMER_CFG1;           /**< comm configure Register 1,                                            Address offset: 0x028C */
    __IOM uint32_t BLE_DEEP_SLP_CORR_EN;      /**< BLE Deep Sleep Correction Enables,                                    Address offset: 0x0290 */
    __IOM uint32_t BLE_DEEP_SLP_HW_TIMER_CORR;/**< Configures the HW auto correction,                                    Address offset: 0x0294 */
    __IOM uint32_t COMM_TIMER_STAT;           /**< comm_timer register,                                                  Address offset: 0x0298 */
    __IOM uint32_t RESERVED8[9];              /**< RESERVED,                                                             Address offset: 0x029C */
    __IOM uint32_t PMU_COMP_GLITCH_REMOVE;     /**< PMU comp glitch remove cycle,                                         Address offset: 0x02C0 */
    __IOM uint32_t RESERVED9[31];             /**< RESERVED,                                                             Address offset: 0x02C4 */
    __IOM uint32_t SOFTWARE_REG0;             /**< software Register 0,                                                  Address offset: 0x0340 */
    __IOM uint32_t SOFTWARE_REG1;             /**< software Register 1,                                                  Address offset: 0x0344 */
    __IOM uint32_t SLP_BUSY_STAT;             /**< Sleep busy status,                                                    Address offset: 0x0348 */
    __IOM uint32_t SLP_BUSY_BYPASS;           /**< Sleep busy bypass,                                                    Address offset: 0x034C */
    __IOM uint32_t RESERVED10[12];            /**< RESERVED,                                                             Address offset: 0x0350 */
    __IOM uint32_t DBG_REG0;                  /**< debug Register 0,                                                     Address offset: 0x0380 */
    __IOM uint32_t DBG_REG_RST_SRC;           /**< Debug reset source status                                             Address offset: 0x0384 */
    __IOM uint32_t RESERVED11[6];             /**< RESERVED,                                                             Address offset: 0x0388 */
    __IOM uint32_t MEM_BOND_OPT_REG;          /**< SRAM bonding option,                                                  Address offset: 0x03A0 */
} aon_ctl_regs_t;

/**
  * @brief AON_MEM
  */
typedef struct _aon_mem_regs
{
    __IOM uint32_t MEM_PWR_SLP0;              /**< memory power sleep Register 0,                                        Address offset: 0x0480 */
    __IOM uint32_t MEM_PWR_SLP1;              /**< memory power sleep Register 1,                                        Address offset: 0x0484 */
    __IOM uint32_t MEM_PWR_WKUP0;             /**< memory power wake up Register 0,                                      Address offset: 0x0488 */
    __IOM uint32_t MEM_PWR_WKUP1;             /**< memory power wake up Register 1,                                      Address offset: 0x048C */
    __IOM uint32_t MEM_PWR_APPLY;             /**< memory power apply Register ,                                         Address offset: 0x0490 */
    __IOM uint32_t RESERVED0[1];              /**< RESERVED,                                                             Address offset: 0x0494 */
    __IOM uint32_t MEM_PWR_STAT0;             /**< Memory power status 0,                                                Address offset: 0x0498 */
    __IOM uint32_t MEM_PWR_STAT1;             /**< Memory power status 1,                                                Address offset: 0x049C */
} aon_mem_regs_t;

/**
  * @brief AON_PWR
  */
typedef struct _aon_pwr_regs
{
    __IOM uint32_t A_TIMING_CTRL0;            /**< analog timing control Register 0,                                     Address offset: 0x0400 */
    __IOM uint32_t A_TIMING_CTRL1;            /**< analog timing control Register 1,                                     Address offset: 0x0404 */
    __IOM uint32_t A_TIMING_CTRL2;            /**< analog timing control Register 2,                                     Address offset: 0x0408 */
    __IOM uint32_t A_TIMING_CTRL3;            /**< analog timing control Register 3,                                     Address offset: 0x040C */
    __IOM uint32_t A_TIMING_CTRL4;            /**< analog timing control Register 4,                                     Address offset: 0x0410 */
    __IOM uint32_t RESERVED1[3];              /**< RESERVED,                                                             Address offset: 0x0414 */
    __IOM uint32_t A_SLP_CFG;                 /**< analog sleep configure Register,                                      Address offset: 0x0420 */
    __IOM uint32_t AON_START_CFG;             /**< AON start configure Register,                                         Address offset: 0x0424 */
    __IOM uint32_t DPAD_LE_CTRL;              /**< DPAD LE control Register,                                             Address offset: 0x0428 */
    __IOM uint32_t RESERVED2[4];              /**< RESERVED,                                                             Address offset: 0x042C */
    __IOM uint32_t AON_SLP_CTRL;              /**< AON sleep control Register,                                           Address offset: 0x043C */
    __OM  uint32_t XO_PLL_SET;                /**< XO PLL setting Register,                                              Address offset: 0x0440 */
    __IOM uint32_t XO_PLL_CLR;                /**< XO PLL Clear Register,                                                Address offset: 0x0444 */
    __IOM uint32_t XO_PLL_STAT;               /**< XO PLL status Register,                                               Address offset: 0x0448 */
    __IOM uint32_t PWR_SET;                   /**< PWR Status Register,                                                  Address offset: 0x044C */
    __IOM uint32_t PWR_CLR;                   /**< PWR Status Register,                                                  Address offset: 0x0450 */
    __OM  uint32_t PWR_STAT;                  /**< PWR Status Register,                                                  Address offset: 0x0454 */
    __IOM uint32_t RESERVED3[10];             /**< RESERVED,                                                             Address offset: 0x0458 */
    __IOM uint32_t MEM_PWR_SLP0;              /**< memory power sleep Register 0,                                        Address offset: 0x0480 */
    __IOM uint32_t MEM_PWR_SLP1;              /**< memory power sleep Register 1,                                        Address offset: 0x0484 */
    __IOM uint32_t MEM_PWR_WKUP0;             /**< memory power wake up Register 0,                                      Address offset: 0x0488 */
    __IOM uint32_t MEM_PWR_WKUP1;             /**< memory power wake up Register 1,                                      Address offset: 0x048C */
    __IOM uint32_t MEM_PWR_APPLY;             /**< memory power apply Register ,                                         Address offset: 0x0490 */
    __IOM uint32_t RESERVED4[1];              /**< RESERVED,                                                             Address offset: 0x0494 */
    __IOM uint32_t MEM_PWR_STAT0;             /**< Memory power status 0,                                                Address offset: 0x0498 */
    __IOM uint32_t MEM_PWR_STAT1;             /**< Memory power status 1,                                                Address offset: 0x049C */
    __IOM uint32_t RESERVED5[7];              /**< RESERVED,                                                             Address offset: 0x04A0 */
    __IOM uint32_t MEM_PWR_DBG;               /**< MEM_PWR_DBG,                                                          Address offset: 0x04BC */
    __IOM uint32_t COMM_CORE_PWR_CTRL_SW;     /**< BLE power control Register,                                           Address offset: 0x04C0 */
    __IOM uint32_t COMM_CORE_PWR_CTRL_HW_CFG; /**< BLE power control Register,                                           Address offset: 0x04C4 */
    __IOM uint32_t COMM_CORE_PWR_CTRL_HW_CTRL;/**< BLE power control Register,                                           Address offset: 0x04C8 */
    __IOM uint32_t COMM_CORE_PWR_CTRL_HW_STAT;/**< BLE power control Register,                                           Address offset: 0x04CC */
    __IOM uint32_t COMM_CORE_PWR_CTRL_PD_DLY; /**< BLE power control Register,                                           Address offset: 0x04D0 */
    __IOM uint32_t COMM_CORE_PWR_STAT;        /**< BLE power control Register,                                           Address offset: 0x04D4 */
    __IOM uint32_t RESERVED7[2];              /**< RESERVED,                                                             Address offset: 0x04D8 */
    __IOM uint32_t COMM_TIMER_PWR_CTRL;       /**< BLE power control Register,                                           Address offset: 0x04E0 */
    __IOM uint32_t RESERVED8[1];              /**< RESERVED,                                                             Address offset: 0x04E4 */
    __IOM uint32_t SOFTWARE_REG_3;            /**< SOFTWARE_REG_3,                                                       Address offset: 0x04E8 */
} aon_pwr_regs_t;

/**
  * @brief AON_PMU
  */
typedef struct _aon_pmu_regs
{
    __IOM uint32_t SNSADC_CFG;              /**< AON_PMU_REG_SNSADC_CFG,            Address offset: 0x00 */
    __IOM uint32_t RF_REG_0;                /**< AON_PMU_REG_RF_REG_0,              Address offset: 0x04 */
    __IOM uint32_t RF_REG_1;                /**< AON_PMU_REG_RF_REG_1,              Address offset: 0x08 */
    __IOM uint32_t RF_REG_2;                /**< AON_PMU_REG_RF_REG_2,              Address offset: 0x0C */
    __IOM uint32_t RF_REG_3;                /**< AON_PMU_REG_RF_REG_3,              Address offset: 0x10 */
    __IOM uint32_t RF_REG_4;                /**< AON_PMU_REG_RF_REG_4,              Address offset: 0x14 */
    __IM  uint32_t RESERVED0[10];           /**< Reserved,                          Address offset: 0x18 */
    __IOM uint32_t COMP_REG_0;              /**< AON_PMU_REG_COMP_REG_0,            Address offset: 0x40 */
    __IOM uint32_t COMP_REG_1;              /**< AON_PMU_REG_COMP_REG_1,            Address offset: 0x44 */
    __IOM uint32_t RC_RTC_REG_0;            /**< AON_PMU_REG_RC_RTC_REG_0,          Address offset: 0x48 */
    __IOM uint32_t RESERVED4;               /**< RESERVED,                          Address offset: 0x4C */
    __IOM uint32_t FS_REG_0;                /**< AON_PMU_REG_FS_REG_0,              Address offset: 0x50 */
    __IOM uint32_t FS_REG_1;                /**< AON_PMU_REG_FS_REG_1,              Address offset: 0x54 */
    __IM  uint32_t RESERVED1[15];           /**< Reserved,                          Address offset: 0x58 */
    __IOM uint32_t PMU_TON_CFG;             /**< AON_PMU_REG_PMU_TON_CFG,           Address offset: 0x94 */
    __IM  uint32_t RESERVED2[10];           /**< Reserved,                          Address offset: 0x98 */
    __IOM uint32_t PMU_INTF_OVR_EN_0;       /**< AON_PMU_REG_PMU_INTF_OVR_EN_0,     Address offset: 0xC0 */
    __IOM uint32_t PMU_INTF_OVR_VAL_0;      /**< AON_PMU_REG_PMU_INTF_OVR_VAL_0,    Address offset: 0xC4 */
    __IOM uint32_t PMU_DVS_CFG_0;           /**< PMU_ADVS_CFG_0,                    Address offset: 0xC8 */
    __IOM uint32_t RESERVED5[2];            /**< RESERVED,                          Address offset: 0xCC */
    __IOM uint32_t MPX_CFG;                 /**< MPX_CFG,                           Address offset: 0xD4 */
    __IOM uint32_t RESERVED3[2];            /**< RESERVED,                          Address offset: 0xD8 */
    __IOM uint32_t PMU_INTF_OVR_RD0;        /**< PMU_INTF_OVR_RD_0,                 Address offset: 0xE0 */
} aon_pmu_regs_t;

/**
  * @brief RTC
  */
typedef struct _rtc_regs
{
    __IOM uint32_t CFG0;                      /**< Calendar timer configure Register 0,                                  Address offset: 0x0000 */
    __IOM uint32_t CFG1;                      /**< Calendar timer configure Register 1,                                  Address offset: 0x0004 */
    __IOM uint32_t RESERVED0[3];              /**< RESERVED,                                                             Address offset: 0x0008 */
    __IOM uint32_t INT_EN;                    /**< Enable/Disable corresponding alarm IRQ Register,                      Address offset: 0x0014 */
    __IOM uint32_t INT_STAT;                  /**< Calendar timer alarm status Register,                                 Address offset: 0x0018 */
    __IOM uint32_t RESERVED1[7];              /**< RESERVED,                                                             Address offset: 0x001C */
    __IOM uint32_t STAT;                      /**< Calendar timer status Register,                                       Address offset: 0x0038 */
    __IOM uint32_t RESERVED2[1];              /**< RESERVED,                                                             Address offset: 0x003C */
    __IOM uint32_t ALARM_W;                   /**< Calendar timer alarm value write Register,                            Address offset: 0x0040 */
    __IOM uint32_t TIMER_W;                   /**< Calendar timer value write Register,                                  Address offset: 0x0044 */
    __IOM uint32_t TICK_W;                    /**< Calendar Tick value write Register,                                   Address offset: 0x0048 */
    __IOM uint32_t RESERVED3[1];              /**< RESERVED,                                                             Address offset: 0x004C */
    __IOM uint32_t TIMER_R;                   /**< Calendar timer value read Register,                                   Address offset: 0x0050 */
    __IOM uint32_t ALARM_R;                   /**< Calendar timer alarm value read Register,                             Address offset: 0x0054 */
    __IOM uint32_t TICK_R;                    /**< Calendar Tick value read Register,                                    Address offset: 0x0058 */
} rtc_regs_t;

/**
  * @brief SLP_TIMER
  */
typedef struct _slp_timer_regs
{
    __IOM uint32_t CFG0;                      /**< sleep timer configure Register 0 ,                                    Address offset: 0x0500 */
    __IOM uint32_t RESERVED0[13];             /**< RESERVED,                                                             Address offset: 0x0504 */
    __IOM uint32_t STAT;                      /**< sleep timer status Register,                                          Address offset: 0x0538 */
    __IOM uint32_t RESERVED1[1];              /**< RESERVED,                                                             Address offset: 0x053C */
    __IOM uint32_t TIMER_W;                   /**< sleep timer value write Register,                                     Address offset: 0x0540 */
    __IOM uint32_t RESERVED2[1];              /**< RESERVED,                                                             Address offset: 0x0544 */
    __IOM uint32_t TIMER_R;                   /**< sleep timer value read Register,                                      Address offset: 0x0548 */
} slp_timer_regs_t;

/**
  * @brief AON_WDT
  */
typedef struct _aon_wdt_regs
{
    __IOM uint32_t CFG0;                      /**< watchdog timer configure Register 0,                                  Address offset: 0x0700 */
    __OM  uint32_t LOCK;                      /**< watchdog timer lock Register,                                         Address offset: 0x0704 */
    __IOM uint32_t RESERVED0[12];             /**< RESERVED,                                                             Address offset: 0x0708 */
    __IOM uint32_t STAT;                      /**< watchdog timer status Register,                                       Address offset: 0x0738 */
    __IOM uint32_t RESERVED1[1];              /**< RESERVED,                                                             Address offset: 0x073C */
    __IOM uint32_t TIMER_W;                   /**< watchdog timer value write Register,                                  Address offset: 0x0740 */
    __IOM uint32_t ALARM_W;                   /**< watchdog timer alarm Register ,                                       Address offset: 0x0744 */
    __IOM uint32_t RESERVED2[1];              /**< RESERVED,                                                             Address offset: 0x0748 */
    __IOM uint32_t TIMER_R;                   /**< watchdog timer value read Register,                                   Address offset: 0x074C */
    __IOM uint32_t ALARM_R;                   /**< watchdog timer alarm read Register,                                   Address offset: 0x0750 */
} aon_wdt_regs_t;

/**
  * @brief AON_IO
  */
typedef struct _aon_io_regs
{
    __IOM uint32_t AON_PAD_CTRL0;             /**< AON PAD control 0 Register,                                           Address offset: 0x00 */
    __IOM uint32_t AON_PAD_CTRL1;             /**< AON PAD control 1 Register,                                           Address offset: 0x04 */
    __IOM uint32_t AON_PAD_CTRL2;             /**< RESERVED,                                                             Address offset: 0x08 */
    __IOM uint32_t AON_PAD_CTRL3;             /**< RESERVED,                                                             Address offset: 0x0C */
    __IOM uint32_t AON_PAD_CLK;               /**< RESERVED,                                                             Address offset: 0x10 */
    __IOM uint32_t AON_MCU_OVR;               /**< AON PAD MCU OVER,                                                     Address offset: 0x14 */
} aon_io_regs_t;

/**
  * @brief AON_MSIO
  */
typedef struct _aon_msio_regs
{
    __IOM uint32_t MSIO_A_PAD_CFG0;           /**< MISO PAD Configuration 0 Register,                                    Address offset: 0x00 */
    __IOM uint32_t MSIO_A_PAD_CFG1;           /**< MISO PAD Configuration 1 Register,                                    Address offset: 0x04 */
    __IOM uint32_t MSIO_A_PAD_CFG2;           /**< MISO PAD Configuration 2 Register,                                    Address offset: 0x08 */
    __IOM uint32_t MSIO_A_PAD_CFG3;           /**< MISO PAD Configuration 3 Register,                                    Address offset: 0x0C */
    __IOM uint32_t MSIO_MCU_OVR;          /**< MISO PAD OVR Register,                                                Address offset: 0x10 */
} aon_msio_regs_t;

/**
  * @brief AON_RF
  */
typedef struct _aon_rf_regs
{
    __IOM uint32_t RF5;                     /**< AON_PMU_REG_RF_REG_5,              Address offset: 0x00 */
    __IOM uint32_t RF6;                     /**< AON_PMU_REG_RF_REG_6,              Address offset: 0x04 */
    __IOM uint32_t RF7;                     /**< AON_PMU_REG_RF_REG_7,              Address offset: 0x08 */
    __IOM uint32_t RF8;                     /**< AON_PMU_REG_RF_REG_8,              Address offset: 0x0C */
    __IOM uint32_t RF9;                     /**< AON_PMU_REG_RF_REG_9,              Address offset: 0x10 */
    __IM  uint32_t RESERVED0[11];           /**< Reserved,                          Address offset: 0x14 */
    __IOM uint32_t RF_RD_REG_0;             /**< AON_PMU_REG_RF_RD_REG_0,           Address offset: 0x40 */
    __IM  uint32_t RESERVED1[9];            /**< Reserved,                          Address offset: 0x44 */
    __IOM uint32_t RF_XO_BIAS_VAL;          /**< AON_RF_XO_BIAS_VAL,                Address offset: 0x68 */
    __IM  uint32_t RESERVED2[21];           /**< Reserved,                          Address offset: 0x6C */
    __IOM uint32_t RF_INTF_OVR_EN_0;        /**< AON_PMU_REG_RF_INTF_OVR_EN_0,      Address offset: 0xC0 */
    __IOM uint32_t RF_INTF_OVR_VAL_0;       /**< AON_PMU_REG_RF_INTF_OVR_VAL_0,     Address offset: 0xC4 */
} aon_rf_regs_t;

/**
  * @brief CLK_CAL
  */
typedef struct _clk_cal_regs
{
    __IOM uint32_t SL_CLK_CTRL;               /**< Clock Calibration Register,                                           Address offset: 0x0000 */
    __IOM uint32_t SL_CLK_CNT;                /**< Clock Calibration Count Register,                                     Address offset: 0x0004 */
    __IOM uint32_t SL_CLK_STAT;               /**< Clock Calibration Status Register,                                    Address offset: 0x0008 */
    __IOM uint32_t SL_CLK_CNT0;               /**< Calibrated counter value Register 0,                                  Address offset: 0x000C */
    __IOM uint32_t SL_CLK_CNT1;               /**< Calibrated counter value Register 1,                                  Address offset: 0x0010 */
    __IOM uint32_t SL_CLK_INT_EN;             /**< Calibrated interrupt enable Register,                                 Address offset: 0x0014 */
    __IOM uint32_t SL_CLK_INT_CLR;            /**< Calibrated clear interrupt Register,                                  Address offset: 0x0018 */
    __IOM uint32_t RESERVED0[1];              /**< RESERVED,                                                             Address offset: 0x001C */
    __IOM uint32_t SL_CLK_SEL;                /**< Select slow clock source,                                             Address offset: 0x0020 */
    __IOM uint32_t RESERVED1[55];             /**< RESERVED,                                                             Address offset: 0x0024 */
    __IOM uint32_t HS_CLK_CTRL;               /**< Clock Calibration Register,                                           Address offset: 0x0100 */
    __IOM uint32_t HS_CLK_CNT;                /**< Clock Calibration Count Register,                                     Address offset: 0x0104 */
    __IOM uint32_t HS_CLK_STAT;               /**< Clock Calibration Status Register,                                    Address offset: 0x0108 */
    __IOM uint32_t HS_CLK_CNT0;               /**< Calibrated counter value Register 0,                                  Address offset: 0x010C */
    __IOM uint32_t HS_CLK_CNT1;               /**< Calibrated counter value Register 1,                                  Address offset: 0x0110 */
    __IOM uint32_t HS_CLK_INT_EN;             /**< Calibrated interrupt enable Register,                                 Address offset: 0x0114 */
    __IOM  uint32_t HS_CLK_INT_CLR;            /**< Calibrated clear interrupt Register,                                  Address offset: 0x0118 */
    __IOM uint32_t RESERVED2[1];              /**< RESERVED,                                                             Address offset: 0x011C */
    __IOM uint32_t HS_CLK_SEL;                /**< Select slow clock source,                                             Address offset: 0x0120 */
} clk_cal_regs_t;

/**
  * @brief DDVS_CTRL
  */
typedef struct _ddvs_ctrl_regs
{
    __IOM uint32_t DDVS_EN;              /**< DDVS_EN,            Address offset: 0x00 */
    __IOM uint32_t DDVS_CFG_1;           /**< DDVS_CFG_1,         Address offset: 0x04 */
    __IOM uint32_t DDVS_CFG_2;           /**< DDVS_CFG_2,         Address offset: 0x08 */
    __IOM uint32_t DDVS_RINGO_CNT_01;    /**< DDVS_RINGO_CNT_01,  Address offset: 0x0C */
    __IOM uint32_t DDVS_RINGO_CNT_23;    /**< DDVS_RINGO_CNT_23,  Address offset: 0x10 */
    __IOM uint32_t DDVS_FSM;             /**< DDVS_CLK_CTRL,      Address offset: 0x14 */
    __IOM uint32_t DDVS_RSVD[10];        /**< DDVS_RSVD[10],      Address offset: 0x18 */
    __IOM uint32_t DDVS_CLK_CTRL;        /**< DDVS_CLK_CTRL,      Address offset: 0x40 */
} ddvs_ctrl_regs_t;

/**
  * @brief HTABLE_AM_CM
  */
typedef struct _htable_amcm_regs
{
    __IOM uint32_t COMM_HTABLE_AMCM_CFG;             /**< COMM_HTABLE_AMCM_CFG,             Address offset: 0x00 */
    __IOM uint32_t COMM_HTABLE_AM_CMD;               /**< COMM_HTABLE_AM_CMD,               Address offset: 0x04 */
    __IOM uint32_t COMM_HTABLE_CM_REG1_ADDR;         /**< COMM_HTABLE_CM_REG1_ADDR,         Address offset: 0x08 */
    __IOM uint32_t COMM_HTABLE_CM_REG1_VALUE;        /**< COMM_HTABLE_CM_REG1_VALUE,        Address offset: 0x0C */
    __IOM uint32_t COMM_HTABLE_CM_REG2_ADDR;         /**< COMM_HTABLE_CM_REG2_ADDR,         Address offset: 0x10 */
    __IOM uint32_t COMM_HTABLE_CM_REG2_VALUE;        /**< COMM_HTABLE_CM_REG2_VALUE,        Address offset: 0x14 */
    __IOM uint32_t COMM_HTABLE_CM_REG3_ADDR;         /**< COMM_HTABLE_CM_REG3_ADDR,         Address offset: 0x18 */
    __IOM uint32_t COMM_HTABLE_CM_REG3_VALUE;        /**< COMM_HTABLE_CM_REG3_VALUE,        Address offset: 0x1C */
    __IOM uint32_t COMM_HTABLE_CM_REG4_ADDR;         /**< COMM_HTABLE_CM_REG4_ADDR,         Address offset: 0x20 */
    __IOM uint32_t COMM_HTABLE_CM_REG4_VALUE;        /**< COMM_HTABLE_CM_REG4_VALUE,        Address offset: 0x24 */
    __IOM uint32_t COMM_HTABLE_AM_ADD_FUNC_CFG0;     /**< COMM_HTABLE_AM_ADD_FUNC_CFG0,     Address offset: 0x28 */
    __IOM uint32_t COMM_HTABLE_AM_DLY_CFG0;          /**< COMM_HTABLE_AM_DLY_CFG0,          Address offset: 0x2C */
    __IOM uint32_t COMM_HTABLE_AM_CTL_CFG0;          /**< COMM_HTABLE_AM_CTL_CFG0,          Address offset: 0x30 */
    __IOM uint32_t COMM_HTABLE_AM_ADD_FUNC_CFG1;     /**< COMM_HTABLE_AM_ADD_FUNC_CFG1,     Address offset: 0x34 */
    __IOM uint32_t COMM_HTABLE_AM_DLY_CFG1;          /**< COMM_HTABLE_AM_DLY_CFG1,          Address offset: 0x38 */
    __IOM uint32_t COMM_HTABLE_AM_CTL_CFG1;          /**< COMM_HTABLE_AM_CTL_CFG1,          Address offset: 0x3C */
    __IOM uint32_t COMM_HTABLE_AM_SRAM_CFG1;         /**< COMM_HTABLE_AM_SRAM_CFG1,         Address offset: 0x40 */
    __IOM uint32_t COMM_HTABLE_AM_SWCNTL_CFG;        /**< COMM_HTABLE_AM_SWCNTL_CFG,        Address offset: 0x44 */
    __IOM uint32_t COMM_HTABLE_AM_SWCNTL_SRAM;       /**< COMM_HTABLE_AM_SWCNTL_SRAM,       Address offset: 0x48 */
    __IOM uint32_t COMM_HTABLE_AM_SWCNTL_ENABLE;     /**< COMM_HTABLE_AM_SWCNTL_ENABLE,     Address offset: 0x4C */
    __IOM uint32_t COMM_HTABLE_AM_IRQ_MSK_ADDR;      /**< COMM_HTABLE_AM_IRQ_MSK_ADDR,      Address offset: 0x50 */
    __IOM uint32_t COMM_HTABLE_AM_IRQ_ACK_ADDR;      /**< COMM_HTABLE_AM_IRQ_ACK_ADDR,      Address offset: 0x54 */
    __IOM uint32_t COMM_HTABLE_AM_IRQ_VEC_ADDR;      /**< COMM_HTABLE_AM_IRQ_VEC_ADDR,      Address offset: 0x58 */
    __IOM uint32_t COMM_HTABLE_MON_SEL_ADDR;         /**< COMM_HTABLE_MON_SEL_ADDR,         Address offset: 0x5C */
    __IOM uint32_t COMM_HTABLE_AM0_STATRST_IRQ_MSK;  /**< COMM_HTABLE_AM0_STATRST_IRQ_MSK,  Address offset: 0x60 */
    __IOM uint32_t COMM_HTABLE_AM1_STATRST_IRQ_MSK;  /**< COMM_HTABLE_AM1_STATRST_IRQ_MSK,  Address offset: 0x64 */
    __IOM uint32_t COMM_HTABLE_SWC_STATRST_IRQ_MSK;  /**< COMM_HTABLE_SWC_STATRST_IRQ_MSK,  Address offset: 0x68 */
} htable_amcm_regs_t;

/** @} */ /* End of group Peripheral_registers_structures */

/* ====================================  End of section using anonymous unions  ==================================== */
#if   defined (__CC_ARM)
    #pragma pop
#elif defined (__ICCARM__)
    /* leave anonymous unions enabled */
#elif (__ARMCC_VERSION >= 6010050)
    #pragma clang diagnostic pop
#elif defined (__GNUC__)
    /* anonymous unions are enabled by default */
#elif defined (__TMS470__)
    /* anonymous unions are enabled by default */
#elif defined (__TASKING__)
    #pragma warning restore
#elif defined (__CSMC__)
    /* anonymous unions are enabled by default */
#else
    #warning Not supported compiler type
#endif


/* ================================================================================================================= */
/* ================                     Device Specific Peripheral Address Map                      ================ */
/* ================================================================================================================= */
/** @addtogroup Peripheral_memory_map
* @{
*/
#define AON_MSIO_BASE           ((uint32_t)0x4000AA00UL)
#define AON_IO_BASE             ((uint32_t)0x4000AA14UL)
#define AON_MEM_BASE            ((uint32_t)0x4000A480UL)


#define AON_CTL_BASE            ((uint32_t)0x4000A000UL)
#define AON_PWR_BASE            ((uint32_t)0x4000A400UL)
#define SLP_TIMER_BASE          ((uint32_t)0x4000A500UL)
#define RTC0_BASE               ((uint32_t)0x4000A600UL)
#define AON_WDT_BASE            ((uint32_t)0x4000A700UL)
#define AON_PMU_BASE            ((uint32_t)0x4000A800UL)
#define AON_RF_BASE             ((uint32_t)0x4000A900UL)
#define MCU_SUB_BASE            ((uint32_t)0x4000E000UL)
#define CLK_CAL_BASE            ((uint32_t)0x4000E400UL)
#define DDVS_CTRL_BASE          ((uint32_t)0x4000E800UL)
#define MCU_PAD_BASE            ((uint32_t)0x4000E900UL)
#define HOPPING_TABLE_BASE      ((uint32_t)0x4000CD00UL)
/** @} */ /* End of group Peripheral_registers_structures */

/* ================================================================================================================= */
/* ================                             Peripheral declaration                              ================ */
/* ================================================================================================================= */

/** @addtogroup Peripheral_declaration
  * @{
  */
#define AON_IO                  ((aon_io_regs_t *)AON_IO_BASE)
#define AON_MEM                 ((aon_mem_regs_t *)AON_MEM_BASE)
#define AON_MSIO                ((aon_msio_regs_t *)AON_MSIO_BASE)
#define AON_CTL                 ((aon_ctl_regs_t *)AON_CTL_BASE)
#define AON_PWR                 ((aon_pwr_regs_t *)AON_PWR_BASE)
#define AON_PMU                 ((aon_pmu_regs_t *)AON_PMU_BASE)
#define AON_RF                  ((aon_rf_regs_t *)AON_RF_BASE)
#define MCU_SUB                 ((mcu_sub_regs_t *)MCU_SUB_BASE)
#define CLK_CAL                 ((clk_cal_regs_t *)CLK_CAL_BASE)
#define DDVS_CTRL               ((ddvs_ctrl_regs_t *)DDVS_CTRL_BASE)

#define SLP_TIMER               ((slp_timer_regs_t *)SLP_TIMER_BASE)
#define CALENDAR                ((rtc_regs_t *)RTC0_BASE)
#define AON_WDT                 ((aon_wdt_regs_t *)AON_WDT_BASE)
#define MCU_PAD                 ((mcu_pad_ctrl_reg_t *)MCU_PAD_BASE)
#define HTABLE_AMCM             ((htable_amcm_regs_t *)HOPPING_TABLE_BASE)
/** @} */ /* End of group Peripheral_declaration */

/** @addtogroup Peripheral_Registers_Bits_Definition
  * @{
  */

/* ================================================================================================================= */
/* ================                                    AON CTL                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for AON_CTL_MCU_CLK_CTRL register  *******************/
#define AON_CTL_MCU_CLK_CTRL_SEL_Pos                            (0U)
#define AON_CTL_MCU_CLK_CTRL_SEL_Len                            (3U)
#define AON_CTL_MCU_CLK_CTRL_SEL_Msk                            (0x7U << AON_CTL_MCU_CLK_CTRL_SEL_Pos)
#define AON_CTL_MCU_CLK_CTRL_SEL                                AON_CTL_MCU_CLK_CTRL_SEL_Msk
#define AON_CTL_MCU_CLK_CTRL_SEL_64M                            (0x0U << AON_CTL_MCU_CLK_CTRL_SEL_Pos)
#define AON_CTL_MCU_CLK_CTRL_SEL_32M                            (0x1U << AON_CTL_MCU_CLK_CTRL_SEL_Pos)
#define AON_CTL_MCU_CLK_CTRL_SEL_XO_16M                         (0x2U << AON_CTL_MCU_CLK_CTRL_SEL_Pos)
#define AON_CTL_MCU_CLK_CTRL_SEL_16M                            (0x3U << AON_CTL_MCU_CLK_CTRL_SEL_Pos)
#define AON_CTL_MCU_CLK_CTRL_SEL_8M                             (0x4U << AON_CTL_MCU_CLK_CTRL_SEL_Pos)
#define AON_CTL_MCU_CLK_CTRL_SEL_2M                             (0x5U << AON_CTL_MCU_CLK_CTRL_SEL_Pos)

#define AON_CTL_MCU_SLOW_CLK_CTRL_SEL_Pos                       (4U)
#define AON_CTL_MCU_SLOW_CLK_CTRL_SEL_Len                       (2U)
#define AON_CTL_MCU_SLOW_CLK_CTRL_SEL_Msk                       (0x3U << AON_CTL_MCU_SLOW_CLK_CTRL_SEL_Pos)
#define AON_CTL_MCU_SLOW_CLK_CTRL_SEL                            AON_CTL_MCU_SLOW_CLK_CTRL_SEL_Msk
#define AON_CTL_MCU_SLOW_CLK_CTRL_SEL_RNG                       (0x1U << AON_CTL_MCU_SLOW_CLK_CTRL_SEL_Pos)
#define AON_CTL_MCU_SLOW_CLK_CTRL_SEL_RC                        (0x2U << AON_CTL_MCU_SLOW_CLK_CTRL_SEL_Pos)
#define AON_CTL_MCU_SLOW_CLK_CTRL_SEL_RTC                       (0x3U << AON_CTL_MCU_SLOW_CLK_CTRL_SEL_Pos)

#define AON_CTL_MCU_CLK_CTRL_WKUP_CLK_SEL_Pos                   (8U)
#define AON_CTL_MCU_CLK_CTRL_WKUP_CLK_SEL_Len                   (3U)
#define AON_CTL_MCU_CLK_CTRL_WKUP_CLK_SEL_Msk                   (0x7UL << AON_CTL_MCU_CLK_CTRL_WKUP_CLK_SEL_Pos)
#define AON_CTL_MCU_CLK_CTRL_WKUP_CLK_SEL                       AON_CTL_MCU_CLK_CTRL_WKUP_CLK_SEL_Msk

#define AON_CTL_MCU_CLK_CTRL_WKUP_CLK_EN_Pos                    (12U)
#define AON_CTL_MCU_CLK_CTRL_WKUP_CLK_EN_Len                    (1U)
#define AON_CTL_MCU_CLK_CTRL_WKUP_CLK_EN_Msk                    (0x1UL << AON_CTL_MCU_CLK_CTRL_WKUP_CLK_EN_Pos)
#define AON_CTL_MCU_CLK_CTRL_WKUP_CLK_EN                        AON_CTL_MCU_CLK_CTRL_WKUP_CLK_EN_Msk

#define AON_CTL_MCU_CLK_CTRL_SER_CLK_SEL_Pos                    (16U)
#define AON_CTL_MCU_CLK_CTRL_SER_CLK_SEL_Len                    (3U)
#define AON_CTL_MCU_CLK_CTRL_SER_CLK_SEL_Msk                    (0x7UL << AON_CTL_MCU_CLK_CTRL_SER_CLK_SEL_Pos)
#define AON_CTL_MCU_CLK_CTRL_SER_CLK_SEL                        AON_CTL_MCU_CLK_CTRL_SER_CLK_SEL_Msk

#define AON_CTL_MCU_CLK_CTRL_SYS_CLK_RD_Pos                     (24U)
#define AON_CTL_MCU_CLK_CTRL_SYS_CLK_RD_Len                     (3U)
#define AON_CTL_MCU_CLK_CTRL_SYS_CLK_RD_Msk                     (0x7UL << AON_CTL_MCU_CLK_CTRL_SYS_CLK_RD_Pos)
#define AON_CTL_MCU_CLK_CTRL_SYS_CLK_RD                         AON_CTL_MCU_CLK_CTRL_SYS_CLK_RD_Msk

#define AON_CTL_MCU_CLK_CTRL_SLOW_CLK_SEL_Pos                   (27U)
#define AON_CTL_MCU_CLK_CTRL_SLOW_CLK_SEL_Len                   (2U)
#define AON_CTL_MCU_CLK_CTRL_SLOW_CLK_SEL_Msk                   (0x3UL << AON_CTL_MCU_CLK_CTRL_SLOW_CLK_SEL_Pos)
#define AON_CTL_MCU_CLK_CTRL_SLOW_CLK_SEL                       AON_CTL_MCU_CLK_CTRL_SLOW_CLK_SEL_Msk

#define AON_CTL_MCU_CLK_CTRL_RNG_2MHZ_CLK_EN_Pos                (30U)
#define AON_CTL_MCU_CLK_CTRL_RNG_2MHZ_CLK_EN_Len                (1U)
#define AON_CTL_MCU_CLK_CTRL_RNG_2MHZ_CLK_EN_Msk                (0x1UL << AON_CTL_MCU_CLK_CTRL_RNG_2MHZ_CLK_EN_Pos)
#define AON_CTL_MCU_CLK_CTRL_RNG_2MHZ_CLK_EN                    AON_CTL_MCU_CLK_CTRL_RNG_2MHZ_CLK_EN_Msk

/*******************  Bit definition for MCU_MISC_CFG register  **********/
#define AON_CTL_MCU_MISC_CFG_SWD_ENABLE_Pos                     (8U)
#define AON_CTL_MCU_MISC_CFG_SWD_ENABLE_Len                     (1U)
#define AON_CTL_MCU_MISC_CFG_SWD_ENABLE_Msk                     (0x1U << AON_CTL_MCU_MISC_CFG_SWD_ENABLE_Pos)
#define AON_CTL_MCU_MISC_CFG_SWD_ENABLE                          AON_CTL_MCU_MISC_CFG_SWD_ENABLE_Msk

/*******************  Bit definition for XO_CTRL register  **********/
#define AON_CTL_XO_CTRL_BYP_Pos                                 (24U)
#define AON_CTL_XO_CTRL_BYP_Len                                 (1U)
#define AON_CTL_XO_CTRL_BYP_Msk                                 (0x1U << AON_CTL_XO_CTRL_BYP_Pos)
#define AON_CTL_XO_CTRL_BYP                                      AON_CTL_XO_CTRL_BYP_Msk

#define AON_CTL_XO_CTRL_2MHZ_OUT_Pos                            (0U)
#define AON_CTL_XO_CTRL_2MHZ_OUT_Len                            (1U)
#define AON_CTL_XO_CTRL_2MHZ_OUT_Msk                            (0x1U << AON_CTL_XO_CTRL_2MHZ_OUT_Pos)
#define AON_CTL_XO_CTRL_2MHZ_OUT                                 AON_CTL_XO_CTRL_2MHZ_OUT_Msk

#define AON_CTL_XO_CTRL_2MHZ_ENA_Pos                            (8U)
#define AON_CTL_XO_CTRL_2MHZ_ENA_Len                            (1U)
#define AON_CTL_XO_CTRL_2MHZ_ENA_Msk                            (0x1U << AON_CTL_XO_CTRL_2MHZ_ENA_Pos)
#define AON_CTL_XO_CTRL_2MHZ_ENA                                 AON_CTL_XO_CTRL_2MHZ_ENA_Msk

/*******************  Bit definition for FLASH_CACHE_CTRL_0 register  **********/
#define AON_CTL_FLASH_CACHE_XF_TAG_RET_Pos                      (8U)
#define AON_CTL_FLASH_CACHE_XF_TAG_RET_Len                      (1U)
#define AON_CTL_FLASH_CACHE_XF_TAG_RET_Msk                      (0x1U << AON_CTL_FLASH_CACHE_XF_TAG_RET_Pos)
#define AON_CTL_FLASH_CACHE_XF_TAG_RET                          AON_CTL_FLASH_CACHE_XF_TAG_RET_Msk

#define AON_CTL_FLASH_CACHE_XF_XO_DIV1_Pos                      (4U)
#define AON_CTL_FLASH_CACHE_XF_XO_DIV1_Len                      (1U)
#define AON_CTL_FLASH_CACHE_XF_XO_DIV1_Msk                      (0x1U << AON_CTL_FLASH_CACHE_XF_XO_DIV1_Pos)
#define AON_CTL_FLASH_CACHE_XF_XO_DIV1                          AON_CTL_FLASH_CACHE_XF_XO_DIV1_Msk

#define AON_CTL_FLASH_CACHE_XF_SCK_CLK_SEL_Pos                  (0U)
#define AON_CTL_FLASH_CACHE_XF_SCK_CLK_SEL_Len                  (3U)
#define AON_CTL_FLASH_CACHE_XF_SCK_CLK_SEL_Msk                  (0x7U << AON_CTL_FLASH_CACHE_XF_SCK_CLK_SEL_Pos)
#define AON_CTL_FLASH_CACHE_XF_SCK_CLK_SEL                      AON_CTL_FLASH_CACHE_XF_SCK_CLK_SEL_Msk
#define AON_CTL_FLASH_CACHE_XF_SCK_CLK_64M                      (0x0U << AON_CTL_FLASH_CACHE_XF_SCK_CLK_SEL_Pos)
#define AON_CTL_FLASH_CACHE_XF_SCK_CLK_48M                      (0x1U << AON_CTL_FLASH_CACHE_XF_SCK_CLK_SEL_Pos)
#define AON_CTL_FLASH_CACHE_XF_SCK_CLK_32M                      (0x2U << AON_CTL_FLASH_CACHE_XF_SCK_CLK_SEL_Pos)
#define AON_CTL_FLASH_CACHE_XF_SCK_CLK_16M                      (0x3U << AON_CTL_FLASH_CACHE_XF_SCK_CLK_SEL_Pos)
#define AON_CTL_FLASH_CACHE_XF_SCK_CLK_XO_16M                   (0x4U << AON_CTL_FLASH_CACHE_XF_SCK_CLK_SEL_Pos)

/*******************  Bit definition for FLASH_CACHE_CTRL_1 register  **********/
#define AON_CTL_FLASH_CACHE_PAD_EN_Pos                          (0U)
#define AON_CTL_FLASH_CACHE_PAD_EN_Len                          (1U)
#define AON_CTL_FLASH_CACHE_PAD_EN_Msk                          (0x1U << AON_CTL_FLASH_CACHE_PAD_EN_Pos)
#define AON_CTL_FLASH_CACHE_PAD_EN                              AON_CTL_FLASH_CACHE_PAD_EN_Msk

#define AON_CTL_FLASH_CACHE_PAD_BYPASS_Pos                      (2U)
#define AON_CTL_FLASH_CACHE_PAD_BYPASS_Len                      (1U)
#define AON_CTL_FLASH_CACHE_PAD_BYPASS_Msk                      (0x1U << AON_CTL_FLASH_CACHE_PAD_BYPASS_Pos)
#define AON_CTL_FLASH_CACHE_PAD_BYPASS                          AON_CTL_FLASH_CACHE_PAD_BYPASS_Msk

/*******************  Bit definition for DIG_IO_LDO_FST_CLK register  **********/
#define AON_CTL_DIG_IO_LDO_FST_CLK_SEL_Pos                      (8U)
#define AON_CTL_DIG_IO_LDO_FST_CLK_SEL_Len                      (1U)
#define AON_CTL_DIG_IO_LDO_FST_CLK_SEL_Msk                      (0x1U << AON_CTL_DIG_IO_LDO_FST_CLK_SEL_Pos)
#define AON_CTL_DIG_IO_LDO_FST_CLK_SEL                          AON_CTL_DIG_IO_LDO_FST_CLK_SEL_Msk

#define AON_CTL_DIG_IO_LDO_FST_CLK_EN_Pos                       (0U)
#define AON_CTL_DIG_IO_LDO_FST_CLK_EN_Len                       (1U)
#define AON_CTL_DIG_IO_LDO_FST_CLK_EN_Msk                       0x1U << AON_CTL_DIG_IO_LDO_FST_CLK_EN_Pos)
#define AON_CTL_DIG_IO_LDO_FST_CLK_EN                           AON_CTL_DIG_IO_LDO_FST_CLK_EN_Msk

/*******************  Bit definition for AON_CLK register  **********/
#define AON_CTL_AON_CLK_CAL_FST_CLK_Pos                         (0U)
#define AON_CTL_AON_CLK_CAL_FST_CLK_Len                         (1U)
#define AON_CTL_AON_CLK_CAL_FST_CLK_Msk                         (0x1U << AON_CTL_AON_CLK_CAL_FST_CLK_Pos)
#define AON_CTL_AON_CLK_CAL_FST_CLK                             AON_CTL_AON_CLK_CAL_FST_CLK_Msk

#define AON_CTL_AON_CLK_WAKUP_CLK_EN_Pos                        (4U)
#define AON_CTL_AON_CLK_WAKUP_CLK_EN_Len                        (1U)
#define AON_CTL_AON_CLK_WAKUP_CLK_EN_Msk                        (0x1U << AON_CTL_AON_CLK_WAKUP_CLK_EN_Pos)
#define AON_CTL_AON_CLK_WAKUP_CLK_EN                            AON_CTL_AON_CLK_WAKUP_CLK_EN_Msk

#define AON_CTL_AON_CLK_WAKUP_FAST_CLK_SEL_Pos                  (8U)
#define AON_CTL_AON_CLK_WAKUP_FAST_CLK_SEL_Len                  (1U)
#define AON_CTL_AON_CLK_WAKUP_FAST_CLK_SEL_Msk                  (0x1U << AON_CTL_AON_CLK_WAKUP_FAST_CLK_SEL_Pos)
#define AON_CTL_AON_CLK_WAKUP_FAST_CLK_SEL                      AON_CTL_AON_CLK_WAKUP_FAST_CLK_SEL_Msk

/*******************  Bit definition for TPP_ANA register  *******************/
#define AON_CTL_TPP_ANA_EN_N_Pos                                (0U)
#define AON_CTL_TPP_ANA_EN_N_Len                                (1U)
#define AON_CTL_TPP_ANA_EN_N_Msk                                (0x1U << AON_CTL_TPP_ANA_EN_Pos)
#define AON_CTL_TPP_ANA_EN_N                                    AON_CTL_TPP_ANA_EN_Msk

#define AON_CTL_TPP_ANA_EN_N_RD_Pos                             (8U)
#define AON_CTL_TPP_ANA_EN_N_RD_Len                             (1U)
#define AON_CTL_TPP_ANA_EN_N_RD_Msk                             (0x1U << AON_CTL_TPP_ANA_EN_N_RD_Pos)
#define AON_CTL_TPP_ANA_EN_N_RD                                 AON_CTL_TPP_ANA_EN_N_RD_Msk

/*******************  Bit definition for AON_PWR_SAVING register  *******************/
#define AON_CTL_PWR_SAVING_EN_Pos                               (0U)
#define AON_CTL_PWR_SAVING_EN_Len                               (1U)
#define AON_CTL_PWR_SAVING_EN_Msk                               (0x1U << AON_CTL_PWR_SAVING_EN_Pos)
#define AON_CTL_PWR_SAVING_EN                                   AON_CTL_PWR_SAVING_EN_Msk

/*******************  Bit definition for AON_CTL_MCU_WAKEUP_CTRL register  *******************/
#define AON_CTL_WAKEUP_CTRL_SEL_Pos                             (0U)
#define AON_CTL_WAKEUP_CTRL_SEL_Len                             (7U)
#define AON_CTL_WAKEUP_CTRL_SEL_Msk                             (0x7FU << AON_CTL_WAKEUP_CTRL_SEL_Pos)
#define AON_CTL_WAKEUP_CTRL_SEL                                 AON_CTL_WAKEUP_CTRL_SEL_Msk

#define AON_CTL_MCU_WAKEUP_CTRL_SLP_TIMER_Pos                   (0U)
#define AON_CTL_MCU_WAKEUP_CTRL_SLP_TIMER_Len                   (1U)
#define AON_CTL_MCU_WAKEUP_CTRL_SLP_TIMER_Msk                   (0x1UL << AON_CTL_MCU_WAKEUP_CTRL_SLP_TIMER_Pos)
#define AON_CTL_MCU_WAKEUP_CTRL_SLP_TIMER                       AON_CTL_MCU_WAKEUP_CTRL_SLP_TIMER_Msk

#define AON_CTL_MCU_WAKEUP_CTRL_EXT_Pos                         (1U)
#define AON_CTL_MCU_WAKEUP_CTRL_EXT_Len                         (1U)
#define AON_CTL_MCU_WAKEUP_CTRL_EXT_Msk                         (0x1UL << AON_CTL_MCU_WAKEUP_CTRL_EXT_Pos)
#define AON_CTL_MCU_WAKEUP_CTRL_EXT                             AON_CTL_MCU_WAKEUP_CTRL_EXT_Msk

#define AON_CTL_MCU_WAKEUP_CTRL_SMS_OSC_Pos                     (2U)
#define AON_CTL_MCU_WAKEUP_CTRL_SMS_OSC_Len                     (1U)
#define AON_CTL_MCU_WAKEUP_CTRL_SMS_OSC_Msk                     (0x1UL << AON_CTL_MCU_WAKEUP_CTRL_SMS_OSC_Pos)
#define AON_CTL_MCU_WAKEUP_CTRL_SMS_OSC                         AON_CTL_MCU_WAKEUP_CTRL_SMS_OSC_Msk

#define AON_CTL_MCU_WAKEUP_CTRL_RTC0_Pos                        (3U)
#define AON_CTL_MCU_WAKEUP_CTRL_RTC0_Len                        (1U)
#define AON_CTL_MCU_WAKEUP_CTRL_RTC0_Msk                        (0x1UL << AON_CTL_MCU_WAKEUP_CTRL_RTC0_Pos)
#define AON_CTL_MCU_WAKEUP_CTRL_RTC0                            AON_CTL_MCU_WAKEUP_CTRL_RTC0_Msk

#define AON_CTL_MCU_WAKEUP_CTRL_COMP_RISE_Pos                   (4U)
#define AON_CTL_MCU_WAKEUP_CTRL_COMP_RISE_Len                   (1U)
#define AON_CTL_MCU_WAKEUP_CTRL_COMP_RISE_Msk                   (0x1UL << AON_CTL_MCU_WAKEUP_CTRL_COMP_RISE_Pos)
#define AON_CTL_MCU_WAKEUP_CTRL_COMP_RISE                       AON_CTL_MCU_WAKEUP_CTRL_COMP_RISE_Msk

#define AON_CTL_MCU_WAKEUP_CTRL_AON_WDT_Pos                     (5U)
#define AON_CTL_MCU_WAKEUP_CTRL_AON_WDT_Len                     (1U)
#define AON_CTL_MCU_WAKEUP_CTRL_AON_WDT_Msk                     (0x1UL << AON_CTL_MCU_WAKEUP_CTRL_AON_WDT_Pos)
#define AON_CTL_MCU_WAKEUP_CTRL_AON_WDT                         AON_CTL_MCU_WAKEUP_CTRL_AON_WDT_Msk

#define AON_CTL_MCU_WAKEUP_CTRL_COMP_FALL_Pos                   (6U)
#define AON_CTL_MCU_WAKEUP_CTRL_COMP_FALL_Len                   (1U)
#define AON_CTL_MCU_WAKEUP_CTRL_COMP_FALL_Msk                   (0x1UL << AON_CTL_MCU_WAKEUP_CTRL_COMP_FALL_Pos)
#define AON_CTL_MCU_WAKEUP_CTRL_COMP_FALL                       AON_CTL_MCU_WAKEUP_CTRL_COMP_FALL_Msk

/*******************  Bit definition for AON_CTL_SLP_EVENT register  *******************/
#define AON_CTL_SLP_EVENT_ALL_Pos                               (0U)
#define AON_CTL_SLP_EVENT_ALL_Len                               (7U)
#define AON_CTL_SLP_EVENT_ALL_Msk                               (0x7FUL << AON_CTL_SLP_EVENT_ALL_Pos)
#define AON_CTL_SLP_EVENT_ALL                                   AON_CTL_SLP_EVENT_ALL_Msk

#define AON_CTL_SLP_EVENT_SLP_TIMER_Pos                         (0U)
#define AON_CTL_SLP_EVENT_SLP_TIMER_Len                         (1U)
#define AON_CTL_SLP_EVENT_SLP_TIMER_Msk                         (0x1UL << AON_CTL_SLP_EVENT_SLP_TIMER_Pos)
#define AON_CTL_SLP_EVENT_SLP_TIMER                             AON_CTL_SLP_EVENT_SLP_TIMER_Msk

#define AON_CTL_SLP_EVENT_EXT_Pos                               (1U)
#define AON_CTL_SLP_EVENT_EXT_Len                               (1U)
#define AON_CTL_SLP_EVENT_EXT_Msk                               (0x1UL << AON_CTL_SLP_EVENT_EXT_Pos)
#define AON_CTL_SLP_EVENT_EXT                                   AON_CTL_SLP_EVENT_EXT_Msk

#define AON_CTL_SLP_EVENT_SMS_OSC_Pos                           (2U)
#define AON_CTL_SLP_EVENT_SMS_OSC_Len                           (1U)
#define AON_CTL_SLP_EVENT_SMS_OSC_Msk                           (0x1UL << AON_CTL_SLP_EVENT_SMS_OSC_Pos)
#define AON_CTL_SLP_EVENT_SMS_OSC                               AON_CTL_SLP_EVENT_SMS_OSC_Msk

#define AON_CTL_SLP_EVENT_RTC0_Pos                              (3U)
#define AON_CTL_SLP_EVENT_RTC0_Len                              (1U)
#define AON_CTL_SLP_EVENT_RTC0_Msk                              (0x1UL << AON_CTL_SLP_EVENT_RTC0_Pos)
#define AON_CTL_SLP_EVENT_RTC0                                  AON_CTL_SLP_EVENT_RTC0_Msk

#define AON_CTL_SLP_EVENT_COMP_RISE_Pos                         (4U)
#define AON_CTL_SLP_EVENT_COMP_RISE_Len                         (1U)
#define AON_CTL_SLP_EVENT_COMP_RISE_Msk                         (0x1UL << AON_CTL_SLP_EVENT_COMP_RISE_Pos)
#define AON_CTL_SLP_EVENT_COMP_RISE                             AON_CTL_SLP_EVENT_COMP_RISE_Msk

#define AON_CTL_SLP_EVENT_AON_WDT_Pos                           (5U)
#define AON_CTL_SLP_EVENT_AON_WDT_Len                           (1U)
#define AON_CTL_SLP_EVENT_AON_WDT_Msk                           (0x1UL << AON_CTL_SLP_EVENT_AON_WDT_Pos)
#define AON_CTL_SLP_EVENT_AON_WDT                               AON_CTL_SLP_EVENT_AON_WDT_Msk

#define AON_CTL_SLP_EVENT_COMP_FALL_Pos                         (6U)
#define AON_CTL_SLP_EVENT_COMP_FALL_Len                         (1U)
#define AON_CTL_SLP_EVENT_COMP_FALL_Msk                         (0x1UL << AON_CTL_SLP_EVENT_COMP_FALL_Pos)
#define AON_CTL_SLP_EVENT_COMP_FALL                             AON_CTL_SLP_EVENT_COMP_FALL_Msk

/*******************  Bit definition for AON_CTL_SLP_EVENT_RAW register  *******************/
#define AON_CTL_SLP_EVENT_RAW_SLP_TIMER_Pos                     (0U)
#define AON_CTL_SLP_EVENT_RAW_SLP_TIMER_Len                     (1U)
#define AON_CTL_SLP_EVENT_RAW_SLP_TIMER_Msk                     (0x1UL << AON_CTL_SLP_EVENT_RAW_SLP_TIMER_Pos)
#define AON_CTL_SLP_EVENT_RAW_SLP_TIMER                         AON_CTL_SLP_EVENT_RAW_SLP_TIMER_Msk

#define AON_CTL_SLP_EVENT_RAW_EXT_Pos                           (1U)
#define AON_CTL_SLP_EVENT_RAW_EXT_Len                           (1U)
#define AON_CTL_SLP_EVENT_RAW_EXT_Msk                           (0x1UL << AON_CTL_SLP_EVENT_RAW_EXT_Pos)
#define AON_CTL_SLP_EVENT_RAW_EXT                               AON_CTL_SLP_EVENT_RAW_EXT_Msk

#define AON_CTL_SLP_EVENT_RAW_SMS_OSC_Pos                       (2U)
#define AON_CTL_SLP_EVENT_RAW_SMS_OSC_Len                       (1U)
#define AON_CTL_SLP_EVENT_RAW_SMS_OSC_Msk                       (0x1UL << AON_CTL_SLP_EVENT_RAW_SMS_OSC_Pos)
#define AON_CTL_SLP_EVENT_RAW_SMS_OSC                           AON_CTL_SLP_EVENT_RAW_SMS_OSC_Msk

#define AON_CTL_SLP_EVENT_RAW_RTC0_Pos                          (3U)
#define AON_CTL_SLP_EVENT_RAW_RTC0_Len                          (1U)
#define AON_CTL_SLP_EVENT_RAW_RTC0_Msk                          (0x1UL << AON_CTL_SLP_EVENT_RAW_RTC0_Pos)
#define AON_CTL_SLP_EVENT_RAW_RTC0                              AON_CTL_SLP_EVENT_RAW_RTC0_Msk

#define AON_CTL_SLP_EVENT_RAW_PMU_MSIO_Pos                      (4U)
#define AON_CTL_SLP_EVENT_RAW_PMU_MSIO_Len                      (1U)
#define AON_CTL_SLP_EVENT_RAW_PMU_MSIO_Msk                      (0x1UL << AON_CTL_SLP_EVENT_RAW_PMU_MSIO_Pos)
#define AON_CTL_SLP_EVENT_RAW_PMU_MSIO                          AON_CTL_SLP_EVENT_RAW_PMU_MSIO_Msk

#define AON_CTL_SLP_EVENT_RAW_AON_WDT_Pos                       (5U)
#define AON_CTL_SLP_EVENT_RAW_AON_WDT_Len                       (1U)
#define AON_CTL_SLP_EVENT_RAW_AON_WDT_Msk                       (0x1UL << AON_CTL_SLP_EVENT_RAW_AON_WDT_Pos)
#define AON_CTL_SLP_EVENT_RAW_AON_WDT                           AON_CTL_SLP_EVENT_RAW_AON_WDT_Msk

#define AON_CTL_SLP_EVENT_RAW_PMU_COMP_Pos                      (6U)
#define AON_CTL_SLP_EVENT_RAW_PMU_COMP_Len                      (1U)
#define AON_CTL_SLP_EVENT_RAW_PMU_COMP_Msk                      (0x1UL << AON_CTL_SLP_EVENT_RAW_PMU_COMP_Pos)
#define AON_CTL_SLP_EVENT_RAW_PMU_COMP                          AON_CTL_SLP_EVENT_RAW_PMU_COMP_Msk

/*******************  Bit definition for AON_CTL_AON_IRQ register  *******************/
#define AON_CTL_AON_IRQ_BLE_ALL_Pos                             (0U)
#define AON_CTL_AON_IRQ_BLE_ALL_Len                             (6U)
#define AON_CTL_AON_IRQ_BLE_ALL_Msk                             (0x7FUL << AON_CTL_AON_IRQ_BLE_ALL_Pos)
#define AON_CTL_AON_IRQ_BLE_ALL                                 AON_CTL_AON_IRQ_BLE_ALL_Msk

#define AON_CTL_AON_IRQ_BLE_PWR_Pos                             (0U)
#define AON_CTL_AON_IRQ_BLE_PWR_Len                             (1U)
#define AON_CTL_AON_IRQ_BLE_PWR_Msk                             (0x1UL << AON_CTL_AON_IRQ_BLE_PWR_Pos)
#define AON_CTL_AON_IRQ_BLE_PWR                                 AON_CTL_AON_IRQ_BLE_PWR_Msk

#define AON_CTL_AON_IRQ_BLE_PWR_DN_Pos                          (1U)
#define AON_CTL_AON_IRQ_BLE_PWR_DN_Len                          (1U)
#define AON_CTL_AON_IRQ_BLE_PWR_DN_Msk                          (0x1UL << AON_CTL_AON_IRQ_BLE_PWR_DN_Pos)
#define AON_CTL_AON_IRQ_BLE_PWR_DN                               AON_CTL_AON_IRQ_BLE_PWR_DN_Msk

#define AON_CTL_AON_IRQ_PMU_BOD_RISE_Pos                        (2U)
#define AON_CTL_AON_IRQ_PMU_BOD_RISE_Len                        (1U)
#define AON_CTL_AON_IRQ_PMU_BOD_RISE_Msk                        (0x1UL << AON_CTL_AON_IRQ_PMU_BOD_RISE_Pos)
#define AON_CTL_AON_IRQ_PMU_BOD_RISE                             AON_CTL_AON_IRQ_PMU_BOD_RISE_Msk

#define AON_CTL_AON_IRQ_AONPLL_CHG_Pos                          (3U)
#define AON_CTL_AON_IRQ_AONPLL_CHG_Len                          (1U)
#define AON_CTL_AON_IRQ_AONPLL_CHG_Msk                          (0x1UL << AON_CTL_AON_IRQ_AONPLL_CHG_Pos)
#define AON_CTL_AON_IRQ_AONPLL_CHG                               AON_CTL_AON_IRQ_AONPLL_CHG_Msk

#define AON_CTL_AON_IRQ_PMU_BOD_FALL_Pos                        (4U)
#define AON_CTL_AON_IRQ_PMU_BOD_FALL_Len                        (1U)
#define AON_CTL_AON_IRQ_PMU_BOD_FALL_Msk                        (0x1UL << AON_CTL_AON_IRQ_PMU_BOD_FALL_Pos)
#define AON_CTL_AON_IRQ_PMU_BOD_FALL                             AON_CTL_AON_IRQ_PMU_BOD_FALL_Msk

#define AON_CTL_AON_IRQ_BLE_MAC_IRQ_Pos                         (5U)
#define AON_CTL_AON_IRQ_BLE_MAC_IRQ_Len                         (1U)
#define AON_CTL_AON_IRQ_BLE_MAC_IRQ_Msk                         (0x1UL << AON_CTL_AON_IRQ_BLE_MAC_IRQ_Pos)
#define AON_CTL_AON_IRQ_BLE_MAC_IRQ                             AON_CTL_AON_IRQ_BLE_MAC_IRQ_Msk

#define AON_CTL_AON_IRQ_SLP_FAIL_IRQ_Pos                        (6U)
#define AON_CTL_AON_IRQ_SLP_FAIL_IRQ_Len                        (1U)
#define AON_CTL_AON_IRQ_SLP_FAIL_IRQ_Msk                        (0x1UL << AON_CTL_AON_IRQ_SLP_FAIL_IRQ_Pos)
#define AON_CTL_AON_IRQ_SLP_FAIL_IRQ                            AON_CTL_AON_IRQ_SLP_FAIL_IRQ_Msk

/*******************  Bit definition for AON_CTL_AON_IRQ_EN register  *******************/
#define AON_CTL_AON_IRQ_EN_ALL_Pos                              (0U)
#define AON_CTL_AON_IRQ_EN_ALL_Len                              (6U)
#define AON_CTL_AON_IRQ_EN_ALL_Msk                              (0x7FUL << AON_CTL_AON_IRQ_EN_ALL_Pos)
#define AON_CTL_AON_IRQ_EN_ALL                                  AON_CTL_AON_IRQ_EN_ALL_Msk

#define AON_CTL_AON_IRQ_EN_BLE_PWR_ON_Pos                       (0U)
#define AON_CTL_AON_IRQ_EN_BLE_PWR_ON_Len                       (1U)
#define AON_CTL_AON_IRQ_EN_BLE_PWR_ON_Msk                       (0x1UL << AON_CTL_AON_IRQ_EN_BLE_PWR_ON_Pos)
#define AON_CTL_AON_IRQ_EN_BLE_PWR_ON                           AON_CTL_AON_IRQ_EN_BLE_PWR_ON_Msk

#define AON_CTL_AON_IRQ_EN_BLE_PWR_DN_Pos                       (1U)
#define AON_CTL_AON_IRQ_EN_BLE_PWR_DN_Len                       (1U)
#define AON_CTL_AON_IRQ_EN_BLE_PWR_DN_Msk                       (0x1UL << AON_CTL_AON_IRQ_EN_BLE_PWR_DN_Pos)
#define AON_CTL_AON_IRQ_EN_BLE_PWR_DN                           AON_CTL_AON_IRQ_EN_BLE_PWR_DN_Msk

#define AON_CTL_AON_IRQ_EN_PMU_BOD_RISE_Pos                     (2U)
#define AON_CTL_AON_IRQ_EN_PMU_BOD_RISE_Len                     (1U)
#define AON_CTL_AON_IRQ_EN_PMU_BOD_RISE_Msk                     (0x1UL << AON_CTL_AON_IRQ_EN_PMU_BOD_RISE_Pos)
#define AON_CTL_AON_IRQ_EN_PMU_BOD_RISE                         AON_CTL_AON_IRQ_EN_PMU_BOD_RISE_Msk

#define AON_CTL_AON_IRQ_EN_AONPLL_CHG_Pos                       (3U)
#define AON_CTL_AON_IRQ_EN_AONPLL_CHG_Len                       (1U)
#define AON_CTL_AON_IRQ_EN_AONPLL_CHG_Msk                       (0x1UL << AON_CTL_AON_IRQ_EN_AONPLL_CHG_Pos)
#define AON_CTL_AON_IRQ_EN_AONPLL_CHG                           AON_CTL_AON_IRQ_EN_AONPLL_CHG_Msk

#define AON_CTL_AON_IRQ_EN_PMU_BOD_FALL_Pos                     (4U)
#define AON_CTL_AON_IRQ_EN_PMU_BOD_FALL_Len                     (1U)
#define AON_CTL_AON_IRQ_EN_PMU_BOD_FALL_Msk                     (0x1UL << AON_CTL_AON_IRQ_EN_PMU_BOD_FALL_Pos)
#define AON_CTL_AON_IRQ_EN_PMU_BOD_FALL                         AON_CTL_AON_IRQ_EN_PMU_BOD_FALL_Msk

#define AON_CTL_AON_IRQ_EN_BLE_MAC_IRQ_Pos                      (5U)
#define AON_CTL_AON_IRQ_EN_BLE_MAC_IRQ_Len                      (1U)
#define AON_CTL_AON_IRQ_EN_BLE_MAC_IRQ_Msk                      (0x1UL << AON_CTL_AON_IRQ_EN_BLE_MAC_IRQ_Pos)
#define AON_CTL_AON_IRQ_EN_BLE_MAC_IRQ                          AON_CTL_AON_IRQ_EN_BLE_MAC_IRQ_Msk

#define AON_CTL_AON_IRQ_EN_SLP_FAIL_IRQ_Pos                     (6U)
#define AON_CTL_AON_IRQ_EN_SLP_FAIL_IRQ_Len                     (1U)
#define AON_CTL_AON_IRQ_EN_SLP_FAIL_IRQ_Msk                     (0x1UL << AON_CTL_AON_IRQ_EN_SLP_FAIL_IRQ_Pos)
#define AON_CTL_AON_IRQ_EN_SLP_FAIL_IRQ                         AON_CTL_AON_IRQ_EN_SLP_FAIL_IRQ_Msk

/*******************  Bit definition for AON_CTL_AON_DBG_CTRL register  *******************/
#define AON_CTL_AON_DBG_CTRL_SLP_TIMER_Pos                      (0U)
#define AON_CTL_AON_DBG_CTRL_SLP_TIMER_Len                      (1U)
#define AON_CTL_AON_DBG_CTRL_SLP_TIMER_Msk                      (0x1UL << AON_CTL_AON_DBG_CTRL_SLP_TIMER_Pos)
#define AON_CTL_AON_DBG_CTRL_SLP_TIMER                          AON_CTL_AON_DBG_CTRL_SLP_TIMER_Msk

#define AON_CTL_AON_DBG_CTRL_RTC_Pos                            (1U)
#define AON_CTL_AON_DBG_CTRL_RTC_Len                            (1U)
#define AON_CTL_AON_DBG_CTRL_RTC_Msk                            (0x1UL << AON_CTL_AON_DBG_CTRL_RTC_Pos)
#define AON_CTL_AON_DBG_CTRL_RTC                                AON_CTL_AON_DBG_CTRL_RTC_Msk

#define AON_CTL_AON_DBG_CTRL_AON_WDT_Pos                        (2U)
#define AON_CTL_AON_DBG_CTRL_AON_WDT_Len                        (1U)
#define AON_CTL_AON_DBG_CTRL_AON_WDT_Msk                        (0x1UL << AON_CTL_AON_DBG_CTRL_AON_WDT_Pos)
#define AON_CTL_AON_DBG_CTRL_AON_WDT                            AON_CTL_AON_DBG_CTRL_AON_WDT_Msk

#define AON_CTL_AON_DBG_CTRL_DBG_SLP_Pos                        (16U)
#define AON_CTL_AON_DBG_CTRL_DBG_SLP_Len                        (1U)
#define AON_CTL_AON_DBG_CTRL_DBG_SLP_Msk                        (0x1UL << AON_CTL_AON_DBG_CTRL_DBG_SLP_Pos)
#define AON_CTL_AON_DBG_CTRL_DBG_SLP                            AON_CTL_AON_DBG_CTRL_DBG_SLP_Msk

/*******************  Bit definition for MEM_MARGIN register  **********/
#define AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_RWM_Pos             (6U)
#define AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_RWM_Len             (2U)
#define AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_RWM_Msk             (0x3U << AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_RWM_Pos)
#define AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_RWM                 AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_RWM_Msk

#define AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_WM_Pos              (5U)
#define AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_WM_Len              (1U)
#define AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_WM_Msk              (0x1U << AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_WM_Pos)
#define AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_WM                  AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_WM_Msk

#define AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_RM_Pos              (4U)
#define AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_RM_Len              (1U)
#define AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_RM_Msk              (0x1U << AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_RM_Pos)
#define AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_RM                  AON_CTL_MEM_MARGIN_NON_CRITICAL_MEM_RM_Msk

#define AON_CTL_MEM_MARGIN_CRITICAL_MEM_RWM_Pos                 (2U)
#define AON_CTL_MEM_MARGIN_CRITICAL_MEM_RWM_Len                 (2U)
#define AON_CTL_MEM_MARGIN_CRITICAL_MEM_RWM_Msk                 (0x3U << AON_CTL_MEM_MARGIN_CRITICAL_MEM_RWM_Pos)
#define AON_CTL_MEM_MARGIN_CRITICAL_MEM_RWM                     AON_CTL_MEM_MARGIN_CRITICAL_MEM_RWM_Msk

#define AON_CTL_MEM_MARGIN_CRITICAL_MEM_WM_Pos                  (1U)
#define AON_CTL_MEM_MARGIN_CRITICAL_MEM_WM_Len                  (1U)
#define AON_CTL_MEM_MARGIN_CRITICAL_MEM_WM_Msk                  (0x1U << AON_CTL_MEM_MARGIN_CRITICAL_MEM_WM_Pos)
#define AON_CTL_MEM_MARGIN_CRITICAL_MEM_WM                      AON_CTL_MEM_MARGIN_CRITICAL_MEM_WM_Msk

#define AON_CTL_MEM_MARGIN_CRITICAL_MEM_RM_Pos                  (0U)
#define AON_CTL_MEM_MARGIN_CRITICAL_MEM_RM_Len                  (1U)
#define AON_CTL_MEM_MARGIN_CRITICAL_MEM_RM_Msk                  (0x1U << AON_CTL_MEM_MARGIN_CRITICAL_MEM_RM_Pos)
#define AON_CTL_MEM_MARGIN_CRITICAL_MEM_RM                       AON_CTL_MEM_MARGIN_CRITICAL_MEM_RM_Msk

/*******************  Bit definition for MEM_PARAM register  **********/
#define AON_CTL_MEM_PARAM_MEM_BTRM_Pos                          (0U)
#define AON_CTL_MEM_PARAM_MEM_BTRM_Len                          (4U)
#define AON_CTL_MEM_PARAM_MEM_BTRM_Msk                          (0xFU << AON_CTL_MEM_PARAM_MEM_BTRM_Pos)
#define AON_CTL_MEM_PARAM_MEM_BTRM                              AON_CTL_MEM_PARAM_MEM_BTRM_Msk


/*******************  Bit definition for AON_CTL_EXT_WAKEUP_CTRL0 register  *******************/
#define AON_CTL_EXT_WAKEUP_CTRL0_SRC_EN_Pos                     (0U)
#define AON_CTL_EXT_WAKEUP_CTRL0_SRC_EN_Len                     (8U)
#define AON_CTL_EXT_WAKEUP_CTRL0_SRC_EN_Msk                     (0xFFUL << AON_CTL_EXT_WAKEUP_CTRL0_SRC_EN_Pos)
#define AON_CTL_EXT_WAKEUP_CTRL0_SRC_EN                         AON_CTL_EXT_WAKEUP_CTRL0_SRC_EN_Msk

#define AON_CTL_EXT_WAKEUP_CTRL0_INVERT_Pos                     (8U)
#define AON_CTL_EXT_WAKEUP_CTRL0_INVERT_Len                     (8U)
#define AON_CTL_EXT_WAKEUP_CTRL0_INVERT_Msk                     (0xFFUL << AON_CTL_EXT_WAKEUP_CTRL0_INVERT_Pos)
#define AON_CTL_EXT_WAKEUP_CTRL0_INVERT                         AON_CTL_EXT_WAKEUP_CTRL0_INVERT_Msk

/*******************  Bit definition for AON_CTL_EXT_WAKEUP_CTRL1 register  *******************/
#define AON_CTL_EXT_WAKEUP_CTRL1_EDGE_EN_Pos                    (0U)
#define AON_CTL_EXT_WAKEUP_CTRL1_EDGE_EN_Len                    (8U)
#define AON_CTL_EXT_WAKEUP_CTRL1_EDGE_EN_Msk                    (0xFFUL << AON_CTL_EXT_WAKEUP_CTRL1_EDGE_EN_Pos)
#define AON_CTL_EXT_WAKEUP_CTRL1_EDGE_EN                        AON_CTL_EXT_WAKEUP_CTRL1_EDGE_EN_Msk

#define AON_CTL_EXT_WAKEUP_CTRL1_EDGE_TYPE_Pos                  (8U)
#define AON_CTL_EXT_WAKEUP_CTRL1_EDGE_TYPE_Len                  (8U)
#define AON_CTL_EXT_WAKEUP_CTRL1_EDGE_TYPE_Msk                  (0xFFUL << AON_CTL_EXT_WAKEUP_CTRL1_EDGE_TYPE_Pos)
#define AON_CTL_EXT_WAKEUP_CTRL1_EDGE_TYPE                      AON_CTL_EXT_WAKEUP_CTRL1_EDGE_TYPE_Msk

#define AON_CTL_EXT_WAKEUP_CTRL1_EDGE_BOTH_Pos                  (16U)
#define AON_CTL_EXT_WAKEUP_CTRL1_EDGE_BOTH_Len                  (8U)
#define AON_CTL_EXT_WAKEUP_CTRL1_EDGE_BOTH_Msk                  (0xFFUL << AON_CTL_EXT_WAKEUP_CTRL1_EDGE_BOTH_Pos)
#define AON_CTL_EXT_WAKEUP_CTRL1_EDGE_BOTH                      AON_CTL_EXT_WAKEUP_CTRL1_EDGE_BOTH_Msk

/*******************  Bit definition for AON_CTL_EXT_WAKEUP_STAT register  *******************/
#define AON_CTL_EXT_WAKEUP_STAT_STAT_Pos                        (0U)
#define AON_CTL_EXT_WAKEUP_STAT_STAT_Len                        (8U)
#define AON_CTL_EXT_WAKEUP_STAT_STAT_Msk                        (0xFFUL << AON_CTL_EXT_WAKEUP_STAT_STAT_Pos)
#define AON_CTL_EXT_WAKEUP_STAT_STAT                            AON_CTL_EXT_WAKEUP_STAT_STAT_Msk

/*******************  Bit definition for COMM_CTRL register  **********/
#define AON_CTL_COMM_CTRL_TIMER_CLK_SEL_Pos                     (16U)
#define AON_CTL_COMM_CTRL_TIMER_CLK_SEL_Len                     (2U)
#define AON_CTL_COMM_CTRL_TIMER_CLK_SEL_Msk                     (0x3U << AON_CTL_COMM_CTRL_TIMER_CLK_SEL_Pos)
#define AON_CTL_COMM_CTRL_TIMER_CLK_SEL                         AON_CTL_COMM_CTRL_TIMER_CLK_SEL_Msk
#define AON_CTL_COMM_CTRL_TIMER_CLK_SEL_RTC                     (0x00 << AON_CTL_COMM_CTRL_TIMER_CLK_SEL_Pos)
#define AON_CTL_COMM_CTRL_TIMER_CLK_SEL_RC                      (0x01 << AON_CTL_COMM_CTRL_TIMER_CLK_SEL_Pos)
#define AON_CTL_COMM_CTRL_TIMER_CLK_SEL_RNG                     (0x03 << AON_CTL_COMM_CTRL_TIMER_CLK_SEL_Pos)

#define AON_CTL_COMM_CTRL_DEEPSLCNTL_EXTWKUPDSB_Pos             (9U)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_EXTWKUPDSB_Len             (1U)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_EXTWKUPDSB_Msk             (0x1U << AON_CTL_COMM_CTRL_DEEPSLCNTL_EXTWKUPDSB_Pos)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_EXTWKUPDSB                 AON_CTL_COMM_CTRL_DEEPSLCNTL_EXTWKUPDSB_Msk

#define AON_CTL_COMM_CTRL_DEEPSLCNTL_SOFT_WAKEUP_REQ_Pos        (8U)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_SOFT_WAKEUP_REQ_Len        (1U)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_SOFT_WAKEUP_REQ_Msk        (0x1U << AON_CTL_COMM_CTRL_DEEPSLCNTL_SOFT_WAKEUP_REQ_Pos)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_SOFT_WAKEUP_REQ            AON_CTL_COMM_CTRL_DEEPSLCNTL_SOFT_WAKEUP_REQ_Msk

#define AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_ON_Pos          (6U)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_ON_Len          (1U)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_ON_Msk          (0x1U << AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_ON_Pos)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_ON              AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_ON_Msk

#define AON_CTL_COMM_CTRL_DEEPSLCNTL_RADIO_SLEEP_EN_Pos         (5U)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_RADIO_SLEEP_EN_Len         (1U)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_RADIO_SLEEP_EN_Msk         (0x1U << AON_CTL_COMM_CTRL_DEEPSLCNTL_RADIO_SLEEP_EN_Pos)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_RADIO_SLEEP_EN             AON_CTL_COMM_CTRL_DEEPSLCNTL_RADIO_SLEEP_EN_Msk

#define AON_CTL_COMM_CTRL_DEEPSLCNTL_OSC_SLEEP_EN_Pos           (4U)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_OSC_SLEEP_EN_Len           (1U)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_OSC_SLEEP_EN_Msk           (0x1U << AON_CTL_COMM_CTRL_DEEPSLCNTL_OSC_SLEEP_EN_Pos)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_OSC_SLEEP_EN               AON_CTL_COMM_CTRL_DEEPSLCNTL_OSC_SLEEP_EN_Msk

#define AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_STAT_Pos        (2U)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_STAT_Len        (1U)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_STAT_Msk        (0x1U << AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_STAT_Pos)
#define AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_STAT            AON_CTL_COMM_CTRL_DEEPSLCNTL_DEEP_SLEEP_STAT_Msk

/*******************  Bit definition for BLE_MISC register  **********/
#define AON_CTL_BLE_MISC_SMC_WAKEUP_REQ_Pos                     (0U)
#define AON_CTL_BLE_MISC_SMC_WAKEUP_REQ_Len                     (1U)
#define AON_CTL_BLE_MISC_SMC_WAKEUP_REQ_Msk                     (0x1U << AON_CTL_BLE_MISC_SMC_WAKEUP_REQ_Pos)
#define AON_CTL_BLE_MISC_SMC_WAKEUP_REQ                         AON_CTL_BLE_MISC_SMC_WAKEUP_REQ_Msk

/*******************  Bit definition for COMM_TIMER_CFG_0 register  **********/
#define AON_CTL_COMM_TIMER_CFG0_DEEPSLWKUP_Pos                  (0U)
#define AON_CTL_COMM_TIMER_CFG0_DEEPSLWKUP_Len                  (32U)
#define AON_CTL_COMM_TIMER_CFG0_DEEPSLWKUP_Msk                  (0xFFFFFFFFU)
#define AON_CTL_COMM_TIMER_CFG0_DEEPSLWKUP                      AON_CTL_COMM_TIMER_CFG0_DEEPSLWKUP_Msk

/*******************  Bit definition for COMM_TIMER_CFG_1 register  **********/
#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_Pos                   (0U)
#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_Len                   (32U)
#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_Msk                   (0xFFFFFFFFU)
#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET                       AON_CTL_COMM_TIMER_CFG1_ENBPRESET_Msk

#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWEXT_Pos             (21U)
#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWEXT_Len             (11U)
#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWEXT_Msk             (0x07FFU << AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWEXT_Pos)
#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWEXT                 AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWEXT_Msk

#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWOSC_Pos             (10U)
#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWOSC_Len             (11U)
#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWOSC_Msk             (0x07FFU << AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWOSC_Pos)
#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWOSC                 AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWOSC_Msk

#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWRM_Pos              (0U)
#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWRM_Len              (10U)
#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWRM_Msk              (0x03FFU << AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWRM_Pos)
#define AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWRM                  AON_CTL_COMM_TIMER_CFG1_ENBPRESET_TWRM_Msk

/*******************  Bit definition for AON_CTL_BLE_DEEP_SLP_CORR_EN register  *******************/
#define AON_CTL_BLE_DEEP_SLP_CORR_EN_FW_EN_Pos                  (0U)
#define AON_CTL_BLE_DEEP_SLP_CORR_EN_FW_EN_Len                  (1U)
#define AON_CTL_BLE_DEEP_SLP_CORR_EN_FW_EN_Msk                  (0x1UL << AON_CTL_BLE_DEEP_SLP_CORR_EN_FW_EN_Pos)
#define AON_CTL_BLE_DEEP_SLP_CORR_EN_FW_EN                      AON_CTL_BLE_DEEP_SLP_CORR_EN_FW_EN_Msk

#define AON_CTL_BLE_DEEP_SLP_CORR_EN_HW_EN_Pos                  (1U)
#define AON_CTL_BLE_DEEP_SLP_CORR_EN_HW_EN_Len                  (1U)
#define AON_CTL_BLE_DEEP_SLP_CORR_EN_HW_EN_Msk                  (0x1UL << AON_CTL_BLE_DEEP_SLP_CORR_EN_HW_EN_Pos)
#define AON_CTL_BLE_DEEP_SLP_CORR_EN_HW_EN                      AON_CTL_BLE_DEEP_SLP_CORR_EN_HW_EN_Msk

/*******************  Bit definition for AON_CTL_BLE_DEEP_SLP_HW_TIMER_CORR register  *******************/
#define AON_CTL_BLE_DEEP_SLP_HW_TIMER_CORR_WAIT_Pos             (0U)
#define AON_CTL_BLE_DEEP_SLP_HW_TIMER_CORR_WAIT_Len             (10U)
#define AON_CTL_BLE_DEEP_SLP_HW_TIMER_CORR_WAIT_Msk             (0x3FFUL << AON_CTL_BLE_DEEP_SLP_HW_TIMER_CORR_WAIT_Pos)
#define AON_CTL_BLE_DEEP_SLP_HW_TIMER_CORR_WAIT                 AON_CTL_BLE_DEEP_SLP_HW_TIMER_CORR_WAIT_Msk

#define AON_CTL_BLE_DEEP_SLP_HW_TIMER_CORR_RTC_TOSC_Pos         (12U)
#define AON_CTL_BLE_DEEP_SLP_HW_TIMER_CORR_RTC_TOSC_Len         (18U)
#define AON_CTL_BLE_DEEP_SLP_HW_TIMER_CORR_RTC_TOSC_Msk         (0x3FFFFUL << AON_CTL_BLE_DEEP_SLP_HW_TIMER_CORR_RTC_TOSC_Pos)
#define AON_CTL_BLE_DEEP_SLP_HW_TIMER_CORR_RTC_TOSC             AON_CTL_BLE_DEEP_SLP_HW_TIMER_CORR_RTC_TOSC_Msk

/*******************  Bit definition for AON_CTL_COMM_TIMER_STAT register  *******************/
#define AON_CTL_COMM_TIMER_STAT_DEEPSLSTAT_Pos                  (0U)
#define AON_CTL_COMM_TIMER_STAT_DEEPSLSTAT_Len                  (32U)
#define AON_CTL_COMM_TIMER_STAT_DEEPSLSTAT_Msk                  (0xFFFFFFFFUL << AON_CTL_COMM_TIMER_STAT_DEEPSLSTAT_Pos)
#define AON_CTL_COMM_TIMER_STAT_DEEPSLSTAT                      AON_CTL_COMM_TIMER_STAT_DEEPSLSTAT_Msk

/*******************  Bit definition for AON_CTL_PMU_COMP_GLITCH_REMOVE register  *******************/
#define AON_CTL_PMU_COMP_GLITCH_REMOVE_CYCLE_Pos                (0U)
#define AON_CTL_PMU_COMP_GLITCH_REMOVE_CYCLE_Len                (3U)
#define AON_CTL_PMU_COMP_GLITCH_REMOVE_CYCLE_Msk                (0x7UL << AON_CTL_PMU_COMP_GLITCH_REMOVE_CYCLE_Pos)
#define AON_CTL_PMU_COMP_GLITCH_REMOVE_CYCLE                    AON_CTL_PMU_COMP_GLITCH_REMOVE_CYCLE_Msk

/*******************  Bit definition for SOFTWARE_REG_0 register  **********/
#define AON_CTL_SOFTWARE_REG0_Pos                               (0U)
#define AON_CTL_SOFTWARE_REG0_Len                               (32U)
#define AON_CTL_SOFTWARE_REG0_Msk                               (0xFFFFFFFFU)
#define AON_CTL_SOFTWARE_REG0                                   AON_CTL_SOFTWARE_REG0_Msk

/*******************  Bit definition for SOFTWARE_REG_1 register  **********/
#define AON_CTL_SOFTWARE_REG1_Pos                               (0U)
#define AON_CTL_SOFTWARE_REG1_Len                               (32U)
#define AON_CTL_SOFTWARE_REG1_Msk                               (0xFFFFFFFFU)
#define AON_CTL_SOFTWARE_REG1                                   AON_CTL_SOFTWARE_REG1_Msk

/*******************  Bit definition for SLP_BUSY_STS register  *******************/
#define AON_CTL_SLP_BUSY_STS_Pos                                (0U)
#define AON_CTL_SLP_BUSY_STS_Len                                (16U)
#define AON_CTL_SLP_BUSY_STS_Msk                                (0xFFFFUL << AON_CTL_SLP_BUSY_STS_Pos)
#define AON_CTL_SLP_BUSY_STS                                    AON_CTL_SLP_BUSY_STS_Msk

/*******************  Bit definition for SLP_BUSY_BYPASS register  *******************/
#define AON_CTL_SLP_BUSY_BYPASS_Pos                             (1U)
#define AON_CTL_SLP_BUSY_BYPASS_Len                             (16U)
#define AON_CTL_SLP_BUSY_BYPASS_Msk                             (0xFFFFUL << AON_CTL_SLP_BUSY_BYPASS_Pos)
#define AON_CTL_SLP_BUSY_BYPASS                                 AON_CTL_SLP_BUSY_BYPASS_Msk

/*******************  Bit definition for DBG_REG0 register  *******************/
#define AON_CTL_DBG_REG0_DBG_SYS_CLK_SEL_Pos                    (0U)
#define AON_CTL_DBG_REG0_DBG_SYS_CLK_SEL_Len                    (1U)
#define AON_CTL_DBG_REG0_DBG_SYS_CLK_SEL_Msk                    (0x1UL << AON_CTL_DBG_REG0_DBG_SYS_CLK_SEL_Pos)
#define AON_CTL_DBG_REG0_DBG_SYS_CLK_SEL                        AON_CTL_DBG_REG0_DBG_SYS_CLK_SEL_Msk

#define AON_CTL_DBG_REG0_DBG_BUS_SEL_Pos                        (4U)
#define AON_CTL_DBG_REG0_DBG_BUS_SEL_Len                        (4U)
#define AON_CTL_DBG_REG0_DBG_BUS_SEL_Msk                        (0xFUL << AON_CTL_DBG_REG0_DBG_BUS_SEL_Pos)
#define AON_CTL_DBG_REG0_DBG_BUS_SEL                            AON_CTL_DBG_REG0_DBG_BUS_SEL_Msk

#define AON_CTL_DBG_REG0_DBG_FLAGL_EN_Pos                       (8U)
#define AON_CTL_DBG_REG0_DBG_FLAGL_EN_Len                       (1U)
#define AON_CTL_DBG_REG0_DBG_FLAGL_EN_Msk                       (0x1UL << AON_CTL_DBG_REG0_DBG_FLAGL_EN_Pos)
#define AON_CTL_DBG_REG0_DBG_FLAGL_EN                           AON_CTL_DBG_REG0_DBG_FLAGL_EN_Msk

#define AON_CTL_DBG_REG0_DBG_FLAGSELL_Pos                       (9U)
#define AON_CTL_DBG_REG0_DBG_FLAGSELL_Len                       (1U)
#define AON_CTL_DBG_REG0_DBG_FLAGSELL_Msk                       (0x1UL << AON_CTL_DBG_REG0_DBG_FLAGSELL_Pos)
#define AON_CTL_DBG_REG0_DBG_FLAGSELL                           AON_CTL_DBG_REG0_DBG_FLAGSELL_Msk

#define AON_CTL_DBG_REG0_DBG_FLAGH_EN_Pos                       (12U)
#define AON_CTL_DBG_REG0_DBG_FLAGH_EN_Len                       (1U)
#define AON_CTL_DBG_REG0_DBG_FLAGH_EN_Msk                       (0x1UL << AON_CTL_DBG_REG0_DBG_FLAGH_EN_Pos)
#define AON_CTL_DBG_REG0_DBG_FLAGH_EN                           AON_CTL_DBG_REG0_DBG_FLAGH_EN_Msk

#define AON_CTL_DBG_REG0_DBG_FLAGSELH_Pos                       (13U)
#define AON_CTL_DBG_REG0_DBG_FLAGSELH_Len                       (2U)
#define AON_CTL_DBG_REG0_DBG_FLAGSELH_Msk                       (0x3UL << AON_CTL_DBG_REG0_DBG_FLAGSELH_Pos)
#define AON_CTL_DBG_REG0_DBG_FLAGSELH                           AON_CTL_DBG_REG0_DBG_FLAGSELH_Msk

/*******************  Bit definition for DBG_REG_RST_SRC register  *******************/
#define AON_CTL_DBG_REG_RST_SRC_STS_Pos                         (0U)
#define AON_CTL_DBG_REG_RST_SRC_STS_Len                         (6U)
#define AON_CTL_DBG_REG_RST_SRC_STS_Msk                         (0x3FUL << AON_CTL_DBG_REG_RST_SRC_STS_Pos)
#define AON_CTL_DBG_REG_RST_SRC_STS                             AON_CTL_DBG_REG_RST_SRC_STS_Msk
#define AON_CTL_DBG_REG_RST_SRC_SYS_RST                         (0x1UL << AON_CTL_DBG_REG_RST_SRC_STS_Pos)
#define AON_CTL_DBG_REG_RST_SRC_SYS_WDT_RST                     (0x2UL << AON_CTL_DBG_REG_RST_SRC_STS_Pos)
#define AON_CTL_DBG_REG_RST_SRC_AON_WDT_RST                     (0x4UL << AON_CTL_DBG_REG_RST_SRC_STS_Pos)
#define AON_CTL_DBG_REG_RST_SRC_SYS_FULL_RST                    (0x8UL << AON_CTL_DBG_REG_RST_SRC_STS_Pos)
#define AON_CTL_DBG_REG_RST_SRC_POR_RST                         (0x10UL << AON_CTL_DBG_REG_RST_SRC_STS_Pos)
#define AON_CTL_DBG_REG_RST_SRC_SLP_RST                         (0x20UL << AON_CTL_DBG_REG_RST_SRC_STS_Pos)

#define AON_CTL_DBG_REG_RST_SRC_RDY_Pos                         (16U)
#define AON_CTL_DBG_REG_RST_SRC_RDY_Len                         (1U)
#define AON_CTL_DBG_REG_RST_SRC_RDY_Msk                         (0x1UL << AON_CTL_DBG_REG_RST_SRC_RDY_Pos)
#define AON_CTL_DBG_REG_RST_SRC_RDY                             AON_CTL_DBG_REG_RST_SRC_RDY_Msk

#define AON_CTL_DBG_REG_RST_SRC_EN_Pos                          (24U)
#define AON_CTL_DBG_REG_RST_SRC_EN_Len                          (1U)
#define AON_CTL_DBG_REG_RST_SRC_EN_Msk                          (0x1UL << AON_CTL_DBG_REG_RST_SRC_EN_Pos)
#define AON_CTL_DBG_REG_RST_SRC_EN                              AON_CTL_DBG_REG_RST_SRC_EN_Msk

#define AON_CTL_DBG_REG_RST_SRC_CFG_BUSY_Pos                    (30U)
#define AON_CTL_DBG_REG_RST_SRC_CFG_BUSY_Len                    (1U)
#define AON_CTL_DBG_REG_RST_SRC_CFG_BUSY_Msk                    (0x1UL << AON_CTL_DBG_REG_RST_SRC_CFG_BUSY_Pos)
#define AON_CTL_DBG_REG_RST_SRC_CFG_BUSY                        AON_CTL_DBG_REG_RST_SRC_CFG_BUSY_Msk

#define AON_CTL_DBG_REG_RST_SRC_CFG_Pos                         (31U)
#define AON_CTL_DBG_REG_RST_SRC_CFG_Len                         (1U)
#define AON_CTL_DBG_REG_RST_SRC_CFG_Msk                         (0x1UL << AON_CTL_DBG_REG_RST_SRC_CFG_Pos)
#define AON_CTL_DBG_REG_RST_SRC_CFG                             AON_CTL_DBG_REG_RST_SRC_CFG_Msk

/*******************  Bit definition for MEM_BOND_OPT_REG register  *******************/
#define AON_CTL_MEM_BOND_OPT_REG_BOND_OPT_Pos                   (0U)
#define AON_CTL_MEM_BOND_OPT_REG_BOND_OPT_Len                   (2U)
#define AON_CTL_MEM_BOND_OPT_REG_BOND_OPT_Msk                   (0x3UL << AON_CTL_MEM_BOND_OPT_REG_BOND_OPT_Pos)
#define AON_CTL_MEM_BOND_OPT_REG_BOND_OPT                       AON_CTL_MEM_BOND_OPT_REG_BOND_OPT_Msk

#define AON_CTL_MEM_BOND_OPT_REG_MAGIC_WORD_Pos                 (16U)
#define AON_CTL_MEM_BOND_OPT_REG_MAGIC_WORD_Len                 (16U)
#define AON_CTL_MEM_BOND_OPT_REG_MAGIC_WORD_Msk                 (0xFFFFUL << AON_CTL_MEM_BOND_OPT_REG_MAGIC_WORD_Pos)
#define AON_CTL_MEM_BOND_OPT_REG_MAGIC_WORD                     AON_CTL_MEM_BOND_OPT_REG_MAGIC_WORD_Msk

/* ================================================================================================================= */
/* ================                                    AON PMU                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for SNSADC_CFG register  **********/
#define AON_PMU_SNSADC_CFG_SNSADC_REG4_Pos                      (24U)
#define AON_PMU_SNSADC_CFG_SNSADC_REG4_Len                      (8U)
#define AON_PMU_SNSADC_CFG_SNSADC_REG4_Msk                      (0xFFU << AON_PMU_SNSADC_CFG_SNSADC_REG4_Pos)
#define AON_PMU_SNSADC_CFG_SNSADC_REG4                          AON_PMU_SNSADC_CFG_SNSADC_REG4_Msk
#define AON_PMU_SNSADC_CFG_MAS_RST_Pos                          (31U)
#define AON_PMU_SNSADC_CFG_MAS_RST_Msk                          (0x1U <<  AON_PMU_SNSADC_CFG_MAS_RST_Pos)
#define AON_PMU_SNSADC_CFG_EN_Pos                               (30U)
#define AON_PMU_SNSADC_CFG_EN_Msk                               (0x1U <<  AON_PMU_SNSADC_CFG_EN_Pos)
#define AON_PMU_SNSADC_CFG_REF_SEL_Pos                          (27U)
#define AON_PMU_SNSADC_CFG_REF_SEL_Msk                          (0x7U <<  AON_PMU_SNSADC_CFG_REF_SEL_Pos)
#define AON_PMU_SNSADC_CFG_REF_HP_Pos                           (24U)
#define AON_PMU_SNSADC_CFG_REF_HP_Msk                           (0x7U <<  AON_PMU_SNSADC_CFG_REF_HP_Pos)

#define AON_PMU_SNSADC_CFG_SNSADC_REG3_Pos                      (16U)
#define AON_PMU_SNSADC_CFG_SNSADC_REG3_Len                      (8U)
#define AON_PMU_SNSADC_CFG_SNSADC_REG3_Msk                      (0xFFU << AON_PMU_SNSADC_CFG_SNSADC_REG3_Pos)
#define AON_PMU_SNSADC_CFG_SNSADC_REG3                          AON_PMU_SNSADC_CFG_SNSADC_REG3_Msk
#define AON_PMU_SNSADC_CFG_CHN_P_Pos                            (20U)
#define AON_PMU_SNSADC_CFG_CHN_P_Msk                            (0xFU <<  AON_PMU_SNSADC_CFG_CHN_P_Pos)
#define AON_PMU_SNSADC_CFG_CHN_N_Pos                            (16U)
#define AON_PMU_SNSADC_CFG_CHN_N_Msk                            (0xFU <<  AON_PMU_SNSADC_CFG_CHN_N_Pos)

#define AON_PMU_SNSADC_CFG_SNSADC_REG2_Pos                      (8U)
#define AON_PMU_SNSADC_CFG_SNSADC_REG2_Len                      (8U)
#define AON_PMU_SNSADC_CFG_SNSADC_REG2_Msk                      (0xFFU << AON_PMU_SNSADC_CFG_SNSADC_REG2_Pos)
#define AON_PMU_SNSADC_CFG_SNSADC_REG2                          AON_PMU_SNSADC_CFG_SNSADC_REG2_Msk
#define AON_PMU_SNSADC_CFG_TEMP_EN_Pos                          (15U)
#define AON_PMU_SNSADC_CFG_TEMP_EN_Msk                          (0x1U <<  AON_PMU_SNSADC_CFG_TEMP_EN_Pos)
#define AON_PMU_SNSADC_CFG_VBAT_EN_Pos                          (14U)
#define AON_PMU_SNSADC_CFG_VBAT_EN_Msk                          (0x1U <<  AON_PMU_SNSADC_CFG_VBAT_EN_Pos)
#define AON_PMU_SNSADC_CFG_SINGLE_EN_Pos                        (13U)
#define AON_PMU_SNSADC_CFG_SINGLE_EN_Msk                        (0x1U <<  AON_PMU_SNSADC_CFG_SINGLE_EN_Pos)
#define AON_PMU_SNSADC_CFG_OFS_CAL_EN_Pos                       (12U)
#define AON_PMU_SNSADC_CFG_OFS_CAL_EN_Msk                       (0x1U <<  AON_PMU_SNSADC_CFG_OFS_CAL_EN_Pos)
#define AON_PMU_SNSADC_CFG_DYMAMIC_Pos                          (8U)
#define AON_PMU_SNSADC_CFG_DYMAMIC_Msk                          (0x7U <<  AON_PMU_SNSADC_CFG_DYMAMIC_Pos)

#define AON_PMU_SNSADC_CFG_SNSADC_REG1_Pos                      (0U)
#define AON_PMU_SNSADC_CFG_SNSADC_REG1_Len                      (8U)
#define AON_PMU_SNSADC_CFG_SNSADC_REG1_Msk                      (0xFFU << AON_PMU_SNSADC_CFG_SNSADC_REG1_Pos)
#define AON_PMU_SNSADC_CFG_SNSADC_REG1                          AON_PMU_SNSADC_CFG_SNSADC_REG1_Msk
#define AON_PMU_SNSADC_CFG_REF_VALUE_Pos                        (0U)
#define AON_PMU_SNSADC_CFG_REF_VALUE_Msk                        (0xFU <<  AON_PMU_SNSADC_CFG_REF_VALUE_Pos)

/*******************  Bit definition for RF_REG_0 register  **********/
#define AON_PMU_RF_REG_0_IO_LDO_BYPASS_Pos                      (31U)
#define AON_PMU_RF_REG_0_IO_LDO_BYPASS_Len                      (1U)
#define AON_PMU_RF_REG_0_IO_LDO_BYPASS_Msk                      (0x1U << AON_PMU_RF_REG_0_IO_LDO_BYPASS_Pos)
#define AON_PMU_RF_REG_0_IO_LDO_BYPASS                          AON_PMU_RF_REG_0_IO_LDO_BYPASS_Msk

#define AON_PMU_RF_REG_0_IO_LDO_REG1_Pos                        (24U)
#define AON_PMU_RF_REG_0_IO_LDO_REG1_Len                        (7U)
#define AON_PMU_RF_REG_0_IO_LDO_REG1_Msk                        (0x7FU << AON_PMU_RF_REG_0_IO_LDO_REG1_Pos)
#define AON_PMU_RF_REG_0_IO_LDO_REG1                            AON_PMU_RF_REG_0_IO_LDO_REG1_Msk

#define AON_PMU_RF_REG_0_AON_LDO_Pos                            (20U)
#define AON_PMU_RF_REG_0_AON_LDO_Len                            (3U)
#define AON_PMU_RF_REG_0_AON_LDO_Msk                            (0x7U << AON_PMU_RF_REG_0_AON_LDO_Pos)
#define AON_PMU_RF_REG_0_AON_LDO                                AON_PMU_RF_REG_0_AON_LDO_Msk

#define AON_PMU_RF_REG_0_BGAP_STATIC_EN_LV_Pos                  (19U)
#define AON_PMU_RF_REG_0_BGAP_STATIC_EN_LV_Len                  (1U)
#define AON_PMU_RF_REG_0_BGAP_STATIC_EN_LV_Msk                  (0x1U <<  AON_PMU_RF_REG_0_BGAP_STATIC_EN_LV_Pos)
#define AON_PMU_RF_REG_0_BGAP_STATIC_EN_LV_EN                   (0x1U <<  AON_PMU_RF_REG_0_BGAP_STATIC_EN_LV_Pos)
#define AON_PMU_RF_REG_0_BGAP_STATIC_EN_LV_DIS                  (0x0U <<  AON_PMU_RF_REG_0_BGAP_STATIC_EN_LV_Pos)

#define AON_PMU_RF_REG_0_DYN_CLK_Pos                            (16U)
#define AON_PMU_RF_REG_0_DYN_CLK_Len                            (3U)
#define AON_PMU_RF_REG_0_DYN_CLK_Msk                            (0x7U <<  AON_PMU_RF_REG_0_DYN_CLK_Pos)
#define AON_PMU_RF_REG_0_DYN_CLK                                AON_PMU_RF_REG_0_DYN_CLK_Msk

#define AON_PMU_RF_REG_0_TEMPCO_Pos                             (13U)
#define AON_PMU_RF_REG_0_TEMPCO_Len                             (3U)
#define AON_PMU_RF_REG_0_TEMPCO_Msk                             (0x7U << AON_PMU_RF_REG_0_TEMPCO_Pos)
#define AON_PMU_RF_REG_0_TEMPCO                                 AON_PMU_RF_REG_0_TEMPCO_Msk

#define AON_PMU_RF_REG_0_RET_LDO_Pos                            (10U)
#define AON_PMU_RF_REG_0_RET_LDO_Len                            (3U)
#define AON_PMU_RF_REG_0_RET_LDO_Msk                            (0x7U << AON_PMU_RF_REG_0_RET_LDO_Pos)
#define AON_PMU_RF_REG_0_RET_LDO                                AON_PMU_RF_REG_0_RET_LDO_Msk

#define AON_PMU_RF_REG_0_RTC_EN_Pos                             (7U)
#define AON_PMU_RF_REG_0_RTC_EN_Len                             (1U)
#define AON_PMU_RF_REG_0_RTC_EN_Msk                             (0x1U << AON_PMU_RF_REG_0_RTC_EN_Pos)
#define AON_PMU_RF_REG_0_RTC_EN                                 AON_PMU_RF_REG_0_RTC_EN_Msk
#define AON_PMU_RF_REG_0_RTC_DIS                                (0x0U << AON_PMU_RF_REG_0_RTC_EN_Pos)

#define AON_PMU_RF_REG_0_CGM_MODE_Pos                           (6U)
#define AON_PMU_RF_REG_0_CGM_MODE_Len                           (1U)
#define AON_PMU_RF_REG_0_CGM_MODE_Msk                           (0x1U <<  AON_PMU_RF_REG_0_CGM_MODE_Pos)
#define AON_PMU_RF_REG_0_CGM_MODE                               AON_PMU_RF_REG_0_CGM_MODE_Msk

#define AON_PMU_RF_REG_0_32KHZ_1V_Pos                           (5U)
#define AON_PMU_RF_REG_0_32KHZ_1V_Len                           (1U)
#define AON_PMU_RF_REG_0_32KHZ_1V_Msk                           (0x1U <<  AON_PMU_RF_REG_0_32KHZ_1V_Pos)
#define AON_PMU_RF_REG_0_32KHZ_1V                               AON_PMU_RF_REG_0_32KHZ_1V_Msk

#define AON_PMU_RF_REG_0_RTC_GM_Pos                             (0U)
#define AON_PMU_RF_REG_0_RTC_GM_Len                             (5U)
#define AON_PMU_RF_REG_0_RTC_GM_Msk                             (0x1FU <<  AON_PMU_RF_REG_0_RTC_GM_Pos)
#define AON_PMU_RF_REG_0_RTC_GM                                 AON_PMU_RF_REG_0_RTC_GM_Msk

/*******************  Bit definition for RF_REG_1 register  **********/
#define AON_PMU_RF_REG_1_DCDC_VOLT_STEP_Pos                     (23U)
#define AON_PMU_RF_REG_1_DCDC_VOLT_STEP_Len                     (1U)
#define AON_PMU_RF_REG_1_DCDC_VOLT_STEP_Msk                     (0x1U << AON_PMU_RF_REG_1_DCDC_VOLT_STEP_Pos)
#define AON_PMU_RF_REG_1_DCDC_VOLT_STEP                         AON_PMU_RF_REG_1_DCDC_VOLT_STEP_Msk

#define AON_PMU_RF_REG_1_DCDC_VREG_Pos                          (19U)
#define AON_PMU_RF_REG_1_DCDC_VREG_Len                          (5U)
#define AON_PMU_RF_REG_1_DCDC_VREG_Msk                          (0x1FU << AON_PMU_RF_REG_1_DCDC_VREG_Pos)
#define AON_PMU_RF_REG_1_DCDC_VREG                              AON_PMU_RF_REG_1_DCDC_VREG_Msk

#define AON_PMU_RF_REG_1_BUCK_CLK_TRIM_Pos                      (11U)
#define AON_PMU_RF_REG_1_BUCK_CLK_TRIM_Len                      (5U)
#define AON_PMU_RF_REG_1_BUCK_CLK_TRIM_Msk                      (0x1FU << AON_PMU_RF_REG_1_BUCK_CLK_TRIM_Pos)
#define AON_PMU_RF_REG_1_BUCK_CLK_TRIM                          AON_PMU_RF_REG_1_BUCK_CLK_TRIM_Msk

#define AON_PMU_RF_REG_1_BUCK_DEADTIME_SEL_Pos                  (8U)
#define AON_PMU_RF_REG_1_BUCK_DEADTIME_SEL_Len                  (3U)
#define AON_PMU_RF_REG_1_BUCK_DEADTIME_SEL_Msk                  (0x7 << AON_PMU_RF_REG_1_BUCK_DEADTIME_SEL_Pos)
#define AON_PMU_RF_REG_1_BUCK_DEADTIME_SEL                       AON_PMU_RF_REG_1_BUCK_DEADTIME_SEL_Msk

#define AON_PMU_RF_REG_1_DCDC_CLK_Pos                           (6U)
#define AON_PMU_RF_REG_1_DCDC_CLK_Len                           (1U)
#define AON_PMU_RF_REG_1_DCDC_CLK_Msk                           (0x1U << AON_PMU_RF_REG_1_DCDC_CLK_Pos)
#define AON_PMU_RF_REG_1_DCDC_CLK                               AON_PMU_RF_REG_1_DCDC_CLK_Msk

#define AON_PMU_RF_REG_1_BUCK_PMMOSNUM_SEL_Pos                  (0U)
#define AON_PMU_RF_REG_1_BUCK_PMMOSNUM_SEL_Len                  (2U)
#define AON_PMU_RF_REG_1_BUCK_PMMOSNUM_SEL_Msk                  (0x3 << AON_PMU_RF_REG_1_BUCK_PMMOSNUM_SEL_Pos)
#define AON_PMU_RF_REG_1_BUCK_PMMOSNUM_SEL                      AON_PMU_RF_REG_1_BUCK_PMMOSNUM_SEL_Msk

/*******************  Bit definition for RF_REG_2 register  **********/
#define AON_PMU_RF_REG_2_PMU_BG_Pos                             (16U)
#define AON_PMU_RF_REG_2_PMU_BG_Len                             (8U)
#define AON_PMU_RF_REG_2_PMU_BG_Msk                             (0xFFU << AON_PMU_RF_REG_2_PMU_BG_Pos)
#define AON_PMU_RF_REG_2_PMU_BG                                 AON_PMU_RF_REG_2_PMU_BG_Msk

#define AON_PMU_RF_REG_2_EFUSE_VDDQ_EN_DEL_Pos                  (12U)
#define AON_PMU_RF_REG_2_EFUSE_VDDQ_EN_DEL_Len                  (1U)
#define AON_PMU_RF_REG_2_EFUSE_VDDQ_EN_DEL_Msk                  (0x1U << AON_PMU_RF_REG_2_EFUSE_VDDQ_EN_DEL_Pos)
#define AON_PMU_RF_REG_2_EFUSE_VDDQ_EN_DEL                      AON_PMU_RF_REG_2_EFUSE_VDDQ_EN_DEL_Msk

#define AON_PMU_RF_REG_2_EFUSE_VDDQ_EN_Pos                      (11U)
#define AON_PMU_RF_REG_2_EFUSE_VDDQ_EN_Len                      (1U)
#define AON_PMU_RF_REG_2_EFUSE_VDDQ_EN_Msk                      (0x1U << AON_PMU_RF_REG_2_EFUSE_VDDQ_EN_Pos)
#define AON_PMU_RF_REG_2_EFUSE_VDDQ_EN                          AON_PMU_RF_REG_2_EFUSE_VDDQ_EN_Msk

#define AON_PMU_RF_REG_2_EFUSE_VDD_EN_Pos                       (10U)
#define AON_PMU_RF_REG_2_EFUSE_VDD_EN_Len                       (1U)
#define AON_PMU_RF_REG_2_EFUSE_VDD_EN_Msk                       (0x1U << AON_PMU_RF_REG_2_EFUSE_VDD_EN_Pos)
#define AON_PMU_RF_REG_2_EFUSE_VDD_EN                           AON_PMU_RF_REG_2_EFUSE_VDD_EN_Msk

#define AON_PMU_RF_REG_2_GP_REG1_Pos                            (8U)
#define AON_PMU_RF_REG_2_GP_REG1_Len                            (8U)
#define AON_PMU_RF_REG_2_GP_REG1_Msk                            (0xFFU << AON_PMU_RF_REG_2_GP_REG1_Pos)
#define AON_PMU_RF_REG_2_GP_REG1                                AON_PMU_RF_REG_2_GP_REG1_Msk

#define AON_PMU_RF_REG_2_MUX1_REG1_Pos                          (0U)
#define AON_PMU_RF_REG_2_MUX1_REG1_Len                          (8U)
#define AON_PMU_RF_REG_2_MUX1_REG1_Msk                          (0xFFU << AON_PMU_RF_REG_2_MUX1_REG1_Pos)
#define AON_PMU_RF_REG_2_MUX1_REG1                              AON_PMU_RF_REG_2_MUX1_REG1_Msk

/*******************  Bit definition for RF_REG_3 register  **********/\
#define AON_PMU_RF_REG_3_BOD2_PWR_CTRL_POST_Pos                 (29U)
#define AON_PMU_RF_REG_3_BOD2_PWR_CTRL_POST_Len                 (1U)
#define AON_PMU_RF_REG_3_BOD2_PWR_CTRL_POST_Msk                 (0x1U << AON_PMU_RF_REG_3_BOD2_PWR_CTRL_POST_Pos)
#define AON_PMU_RF_REG_3_BOD2_PWR_CTRL_POST                     AON_PMU_RF_REG_3_BOD2_PWR_CTRL_POST_Msk

#define AON_PMU_RF_REG_3_BOD2_BYPASS_Pos                        (28U)
#define AON_PMU_RF_REG_3_BOD2_BYPASS_Len                        (1U)
#define AON_PMU_RF_REG_3_BOD2_BYPASS_Msk                        (0x1U << AON_PMU_RF_REG_3_BOD2_BYPASS_Pos)
#define AON_PMU_RF_REG_3_BOD2_BYPASS                            AON_PMU_RF_REG_3_BOD2_BYPASS_Msk

#define AON_PMU_RF_REG_3_COMP_INT_Pos                           (26U)
#define AON_PMU_RF_REG_3_COMP_INT_Len                           (1U)
#define AON_PMU_RF_REG_3_COMP_INT_Msk                           (0x1U << AON_PMU_RF_REG_3_COMP_INT_Pos)
#define AON_PMU_RF_REG_3_COMP_INT                               AON_PMU_RF_REG_3_COMP_INT_Msk

#define AON_PMU_RF_REG_3_BOD2_INT_Pos                           (25U)
#define AON_PMU_RF_REG_3_BOD2_INT_Len                           (1U)
#define AON_PMU_RF_REG_3_BOD2_INT_Msk                           (0x1U << AON_PMU_RF_REG_3_BOD2_INT_Pos)
#define AON_PMU_RF_REG_3_BOD2_INT                               AON_PMU_RF_REG_3_BOD2_INT_Msk

#define AON_PMU_RF_REG_3_BOD2_OK_Pos                            (24U)
#define AON_PMU_RF_REG_3_BOD2_OK_Len                            (1U)
#define AON_PMU_RF_REG_3_BOD2_OK_Msk                            (0x1U << AON_PMU_RF_REG_3_BOD2_OK_Pos)
#define AON_PMU_RF_REG_3_BOD2_OK                                AON_PMU_RF_REG_3_BOD2_OK_Msk

#define AON_PMU_RF_REG_3_BOD_STATIC_Pos                         (5U)
#define AON_PMU_RF_REG_3_BOD_STATIC_Len                         (1U)
#define AON_PMU_RF_REG_3_BOD_STATIC_Msk                         (0x1U <<  AON_PMU_RF_REG_3_BOD_STATIC_Pos)
#define AON_PMU_RF_REG_3_BOD_STATIC_EN                          (0x1U <<  AON_PMU_RF_REG_3_BOD_STATIC_Pos)
#define AON_PMU_RF_REG_3_BOD_STATIC_DIS                         (0x0U <<  AON_PMU_RF_REG_3_BOD_STATIC_Pos)

#define AON_PMU_RF_REG_3_BOD2_LVL_CTRL_LV_Pos                   (2U)
#define AON_PMU_RF_REG_3_BOD2_LVL_CTRL_LV_Len                   (3U)
#define AON_PMU_RF_REG_3_BOD2_LVL_CTRL_LV_Msk                   (0x7U <<  AON_PMU_RF_REG_3_BOD2_LVL_CTRL_LV_Pos)
#define AON_PMU_RF_REG_3_BOD2_LVL_CTRL_LV                       AON_PMU_RF_REG_3_BOD2_LVL_CTRL_LV_Msk

#define AON_PMU_RF_REG_3_BOD2_EN_Pos                            (1U)
#define AON_PMU_RF_REG_3_BOD2_EN_Len                            (1U)
#define AON_PMU_RF_REG_3_BOD2_EN_Msk                            (0x1U <<  AON_PMU_RF_REG_3_BOD2_EN_Pos)
#define AON_PMU_RF_REG_3_BOD2_EN                                (0x1U <<  AON_PMU_RF_REG_3_BOD2_EN_Pos)
#define AON_PMU_RF_REG_3_BOD2_DIS                               (0x0U <<  AON_PMU_RF_REG_3_BOD2_EN_Pos)

#define AON_PMU_RF_REG_3_BOD_EN_Pos                             (0U)
#define AON_PMU_RF_REG_3_BOD_EN_Len                             (1U)
#define AON_PMU_RF_REG_3_BOD_EN_Msk                             (0x1U <<  AON_PMU_RF_REG_3_BOD_EN_Pos)
#define AON_PMU_RF_REG_3_BOD_EN                                 (0x1U <<  AON_PMU_RF_REG_3_BOD_EN_Pos)
#define AON_PMU_RF_REG_3_BOD_DIS                                (0x0U <<  AON_PMU_RF_REG_3_BOD_EN_Pos)

#define AON_PMU_RF_REG_3_BOD_REG1_Pos                           (0U)
#define AON_PMU_RF_REG_3_BOD_REG1_Len                           (8U)
#define AON_PMU_RF_REG_3_BOD_REG1_Msk                           (0xFFU << AON_PMU_RF_REG_3_BOD_REG1_Pos)
#define AON_PMU_RF_REG_3_BOD_REG1                               AON_PMU_RF_REG_3_BOD_REG1_Msk

/*******************  Bit definition for RF_REG_4 register  **********/
#define AON_PMU_RF_REG_4_DIG_LDO_BLEED_EN_Pos                   (23U)
#define AON_PMU_RF_REG_4_DIG_LDO_BLEED_EN_Len                   (1U)
#define AON_PMU_RF_REG_4_DIG_LDO_BLEED_EN_Msk                   (0x1U << AON_PMU_RF_REG_4_DIG_LDO_BLEED_EN_Pos)
#define AON_PMU_RF_REG_4_DIG_LDO_BLEED_EN                       AON_PMU_RF_REG_4_DIG_LDO_BLEED_EN_Msk

#define AON_PMU_RF_REG_4_DIG_LDO_BYPASS_EN_Pos                   (22U)
#define AON_PMU_RF_REG_4_DIG_LDO_BYPASS_EN_Len                   (1U)
#define AON_PMU_RF_REG_4_DIG_LDO_BYPASS_EN_Msk                   (0x1U << AON_PMU_RF_REG_4_DIG_LDO_BYPASS_EN_Pos)
#define AON_PMU_RF_REG_4_DIG_LDO_BYPASS_EN                       AON_PMU_RF_REG_4_DIG_LDO_BYPASS_EN_Msk

#define AON_PMU_RF_REG_4_DIG_LDO_COARSE_TUNE_Pos                (20U)
#define AON_PMU_RF_REG_4_DIG_LDO_COARSE_TUNE_Len                (2U)
#define AON_PMU_RF_REG_4_DIG_LDO_COARSE_TUNE_Msk                (0x3U << AON_PMU_RF_REG_4_DIG_LDO_COARSE_TUNE_Pos)
#define AON_PMU_RF_REG_4_DIG_LDO_COARSE_TUNE                    AON_PMU_RF_REG_4_DIG_LDO_COARSE_TUNE_Msk

#define AON_PMU_RF_REG_4_DCDC_REG6_Pos                          (8U)
#define AON_PMU_RF_REG_4_DCDC_REG6_Len                          (8U)
#define AON_PMU_RF_REG_4_DCDC_REG6_Msk                          (0xFFU << AON_PMU_RF_REG_4_DCDC_REG6_Pos)
#define AON_PMU_RF_REG_4_DCDC_REG6                              AON_PMU_RF_REG_4_DCDC_REG6_Msk

#define AON_PMU_RF_REG_4_DCDC_REG5_Pos                          (0U)
#define AON_PMU_RF_REG_4_DCDC_REG5_Len                          (8U)
#define AON_PMU_RF_REG_4_DCDC_REG5_Msk                          (0xFFU << AON_PMU_RF_REG_4_DCDC_REG5_Pos)
#define AON_PMU_RF_REG_4_DCDC_REG5                              AON_PMU_RF_REG_4_DCDC_REG5_Msk

/*******************  Bit definition for AON_PMU_COMP_REG0 register  *******************/
#define AON_PMU_COMP_REG0_COMP_REG3_Pos                         (16U)
#define AON_PMU_COMP_REG0_COMP_REG3_Len                         (8U)
#define AON_PMU_COMP_REG0_COMP_REG3_Msk                         (0xFFUL << AON_PMU_COMP_REG3_Pos)
#define AON_PMU_COMP_REG0_COMP_REG3                             AON_PMU_COMP_REG3_Msk

#define AON_PMU_COMP_REG0_COMP_REG2_Pos                         (8U)
#define AON_PMU_COMP_REG0_COMP_REG2_Len                         (8U)
#define AON_PMU_COMP_REG0_COMP_REG2_Msk                         (0xFFUL << AON_PMU_COMP_REG2_Pos)
#define AON_PMU_COMP_REG0_COMP_REG2                             AON_PMU_COMP_REG2_Msk

#define AON_PMU_COMP_REG0_COMP_REG1_Pos                         (0U)
#define AON_PMU_COMP_REG0_COMP_REG1_Len                         (8U)
#define AON_PMU_COMP_REG0_COMP_REG1_Msk                         (0xFFUL << AON_PMU_COMP_REG1_Pos)
#define AON_PMU_COMP_REG0_COMP_REG1                             AON_PMU_COMP_REG1_Msk

/*******************  Bit definition for AON_PMU_COMP_REG1 register  *******************/
#define AON_PMU_COMP_REG1_COMP_REG5_Pos                         (8U)
#define AON_PMU_COMP_REG1_COMP_REG5_Len                         (8U)
#define AON_PMU_COMP_REG1_COMP_REG5_Msk                         (0xFFUL << AON_PMU_COMP_REG5_Pos)
#define AON_PMU_COMP_REG1_COMP_REG5                             AON_PMU_COMP_REG5_Msk

#define AON_PMU_COMP_REG1_COMP_REG4_Pos                         (0U)
#define AON_PMU_COMP_REG1_COMP_REG4_Len                         (8U)
#define AON_PMU_COMP_REG1_COMP_REG4_Msk                         (0xFFUL << AON_PMU_COMP_REG4_Pos)
#define AON_PMU_COMP_REG1_COMP_REG4                             AON_PMU_COMP_REG4_Msk

/*******************  Bit definition for AON_PMU_RC_RTC_REG0 register  *******************/
#define AON_PMU_RC_RTC_REG0_RTC_CAP_Pos                         (24U)
#define AON_PMU_RC_RTC_REG0_RTC_CAP_Len                         (8U)
#define AON_PMU_RC_RTC_REG0_RTC_CAP_Msk                         (0xFFUL << AON_PMU_RC_RTC_REG0_RTC_CAP_Pos)
#define AON_PMU_RC_RTC_REG0_RTC_CAP                             AON_PMU_RC_RTC_REG0_RTC_CAP_Msk

#define AON_PMU_RC_RTC_REG0_RTC_CS_Pos                          (16U)
#define AON_PMU_RC_RTC_REG0_RTC_CS_Len                          (5U)
#define AON_PMU_RC_RTC_REG0_RTC_CS_Msk                          (0x1FUL << AON_PMU_RC_RTC_REG0_RTC_CS_Pos)
#define AON_PMU_RC_RTC_REG0_RTC_CS                              AON_PMU_RC_RTC_REG0_RTC_CS_Msk

#define AON_PMU_RC_RTC_REG0_RCOSC_Pos                           (15U)
#define AON_PMU_RC_RTC_REG0_RCOSC_Len                           (1U)
#define AON_PMU_RC_RTC_REG0_RCOSC_Msk                           (0x1UL << AON_PMU_RC_RTC_REG0_RCOSC_Pos)
#define AON_PMU_RC_RTC_REG0_RCOSC                               AON_PMU_RC_RTC_REG0_RCOSC_Msk

/*******************  Bit definition for AON_PMU_DCDC_LDO_REG0 register  *******************/
#define AON_PMU_DCDC_LDO_REG0_CLK_DIV_SEL_Pos                   (16U)
#define AON_PMU_DCDC_LDO_REG0_CLK_DIV_SEL_Len                   (2U)
#define AON_PMU_DCDC_LDO_REG0_CLK_DIV_SEL_Msk                   (0x3UL << AON_PMU_DCDC_LDO_REG0_CLK_DIV_SEL_Pos)
#define AON_PMU_DCDC_LDO_REG0_CLK_DIV_SEL                       AON_PMU_DCDC_LDO_REG0_CLK_DIV_SEL_Msk

#define AON_PMU_DCDC_LDO_REG0_BOOST_STEP_Pos                    (30U)
#define AON_PMU_DCDC_LDO_REG0_BOOST_STEP_Len                    (2U)
#define AON_PMU_DCDC_LDO_REG0_BOOST_STEP_Msk                    (0x3UL << AON_PMU_DCDC_LDO_REG0_BOOST_STEP_Pos)
#define AON_PMU_DCDC_LDO_REG0_BOOST_STEP                        AON_PMU_DCDC_LDO_REG0_BOOST_STEP_Msk

/*******************  Bit definition for AON_PMU_FS_REG0 register  *******************/
#define AON_PMU_FS_REG_0_FINE_CODE_Pos                          (16U)
#define AON_PMU_FS_REG_0_FINE_CODE_Len                          (8U)
#define AON_PMU_FS_REG_0_FINE_CODE_Msk                          (0xFFUL << AON_PMU_FS_REG_0_FINE_CODE_Pos)
#define AON_PMU_FS_REG_0_FINE_CODE                              AON_PMU_FS_REG_0_FINE_CODE_Msk

/*******************  Bit definition for AON_PMU_FS_REG1 register  *******************/
#define AON_PMU_FS_REG_1_SYSLDO_CODE_Pos                        (8U)
#define AON_PMU_FS_REG_1_SYSLDO_CODE_Len                        (4U)
#define AON_PMU_FS_REG_1_SYSLDO_CODE_Msk                        (0xFUL << AON_PMU_FS_REG_1_SYSLDO_CODE_Pos)
#define AON_PMU_FS_REG_1_SYSLDO_CODE                            AON_PMU_FS_REG_1_SYSLDO_CODE_Msk

#define AON_PMU_FS_REG1_FS_REG5_Pos                             (8U)
#define AON_PMU_FS_REG1_FS_REG5_Len                             (8U)
#define AON_PMU_FS_REG1_FS_REG5_Msk                             (0xFFUL << AON_PMU_FS_REG1_FS_REG5_Pos)
#define AON_PMU_FS_REG1_FS_REG5                                 AON_PMU_FS_REG1_FS_REG5_Msk

#define AON_PMU_FS_REG_1_FINE_CODE_H_Pos                        (6U)
#define AON_PMU_FS_REG_1_FINE_CODE_H_Len                        (1U)
#define AON_PMU_FS_REG_1_FINE_CODE_H_Msk                        (0x1UL << AON_PMU_FS_REG_1_FINE_CODE_H_Pos)
#define AON_PMU_FS_REG_1_FINE_CODE_H                            AON_PMU_FS_REG_1_FINE_CODE_H_Msk

#define AON_PMU_FS_REG_1_COARSE_CODE_Pos                        (0U)
#define AON_PMU_FS_REG_1_COARSE_CODE_Len                        (4U)
#define AON_PMU_FS_REG_1_COARSE_CODE_Msk                        (0xFUL << AON_PMU_FS_REG_1_COARSE_CODE_Pos)
#define AON_PMU_FS_REG_1_COARSE_CODE                            AON_PMU_FS_REG_1_COARSE_CODE_Msk

#define AON_PMU_FS_REG1_FS_REG4_Pos                             (0U)
#define AON_PMU_FS_REG1_FS_REG4_Len                             (8U)
#define AON_PMU_FS_REG1_FS_REG4_Msk                             (0xFFUL << AON_PMU_FS_REG1_FS_REG4_Pos)
#define AON_PMU_FS_REG1_FS_REG4                                 AON_PMU_FS_REG1_FS_REG4_Msk

/*******************  Bit definition for AON_PMU_LPD_REG register  *******************/
#define AON_PMU_LDP_VAON_ACTIVE_Pos                             (0U)
#define AON_PMU_LDP_VAON_ACTIVE_Len                             (3U)
#define AON_PMU_LDP_VAON_ACTIVE_Msk                             (0x7UL << AON_PMU_LDP_VAON_ACTIVE_Pos)
#define AON_PMU_LDP_VAON_ACTIVE                                 AON_PMU_LDP_VAON_ACTIVE_Msk

#define AON_PMU_LDP_VAON_SLEEP_Pos                              (4U)
#define AON_PMU_LDP_VAON_SLEEP_Len                              (3U)
#define AON_PMU_LDP_VAON_SLEEP_Msk                              (0x7UL << AON_PMU_LDP_VAON_SLEEP_Pos)
#define AON_PMU_LDP_VAON_SLEEP                                  AON_PMU_LDP_VAON_SLEEP_Msk

/*******************  Bit definition for AON_PMU_TON_REG register  *******************/
#define AON_PMU_TON_CTRL_ON_Pos                                 (0U)
#define AON_PMU_TON_CTRL_ON_Len                                 (4U)
#define AON_PMU_TON_CTRL_ON_Msk                                 (0xFUL << AON_PMU_TON_CTRL_ON_Pos)
#define AON_PMU_TON_CTRL_ON                                     AON_PMU_TON_CTRL_ON_Msk

#define AON_PMU_TON_CTRL_OFF_Pos                                (8U)
#define AON_PMU_TON_CTRL_OFF_Len                                (4U)
#define AON_PMU_TON_CTRL_OFF_Msk                                (0xFUL << AON_PMU_TON_CTRL_OFF_Pos)
#define AON_PMU_TON_CTRL_OFF                                    AON_PMU_TON_CTRL_OFF_Msk

/*******************  Bit definition for AON_PMU_INTF_OVR_EN0 register  **********/
#define AON_PMU_AVS_CTL_REF_EN_Pos                              (8U)
#define AON_PMU_AVS_CTL_REF_EN_Len                              (1U)
#define AON_PMU_AVS_CTL_REF_EN_Msk                              (0x1U << AON_PMU_AVS_CTL_REF_EN_Pos)
#define AON_PMU_AVS_CTL_REF_EN                                  AON_PMU_AVS_CTL_REF_EN_Msk

#define AON_PMU_RNG_OSC_CLK_EN_Pos                              (7U)
#define AON_PMU_RNG_OSC_CLK_EN_Len                              (1U)
#define AON_PMU_RNG_OSC_CLK_EN_Msk                              (0x1U << AON_PMU_RNG_OSC_CLK_EN_Pos)
#define AON_PMU_RNG_OSC_CLK_EN                                  AON_PMU_RNG_OSC_CLK_EN_Msk

#define AON_PMU_STB_IO_LDO_Pos                                  (6U)
#define AON_PMU_STB_IO_LDO_Len                                  (1U)
#define AON_PMU_STB_IO_LDO_Msk                                  (0x1U << AON_PMU_STB_IO_LDO_Pos)
#define AON_PMU_STB_IO_LDO                                      AON_PMU_STB_IO_LDO_Msk

#define AON_PMU_IO_LDO_EN_Pos                                   (5U)
#define AON_PMU_IO_LDO_EN_Len                                   (1U)
#define AON_PMU_IO_LDO_EN_Msk                                   (0x1U << AON_PMU_IO_LDO_EN_Pos)
#define AON_PMU_IO_LDO_EN                                       AON_PMU_IO_LDO_EN_Msk

#define AON_PMU_DIG_LDO_EN_Pos                                  (3U)
#define AON_PMU_DIG_LDO_EN_Len                                  (1U)
#define AON_PMU_DIG_LDO_EN_Msk                                  (0x1U << AON_PMU_DIG_LDO_EN_Pos)
#define AON_PMU_DIG_LDO_EN                                      AON_PMU_DIG_LDO_EN_Msk

#define AON_PMU_HF_OSC_EN_Pos                                   (2U)
#define AON_PMU_HF_OSC_EN_Len                                   (1U)
#define AON_PMU_HF_OSC_EN_Msk                                   (0x1U << AON_PMU_HF_OSC_EN_Pos)
#define AON_PMU_HF_OSC_EN                                       AON_PMU_HF_OSC_EN_Msk

#define AON_PMU_SYS_LDO_EN_Pos                                  (1U)
#define AON_PMU_SYS_LDO_EN_Len                                  (1U)
#define AON_PMU_SYS_LDO_EN_Msk                                  (0x1U << AON_PMU_SYS_LDO_EN_Pos)
#define AON_PMU_SYS_LDO_EN                                      AON_PMU_SYS_LDO_EN_Msk

#define AON_PMU_DCDC_EN_Pos                                     (0U)
#define AON_PMU_DCDC_EN_Len                                     (1U)
#define AON_PMU_DCDC_EN_Msk                                     (0x1U << AON_PMU_DCDC_EN_Pos)
#define AON_PMU_DCDC_EN                                         AON_PMU_DCDC_EN_Msk

/*******************  Bit definition for AON_PMU_INTF_OVR_VAL0 register  **********/
#define AON_PMU_VAL_AVS_CTL_REF_Pos                             (9U)
#define AON_PMU_VAL_AVS_CTL_REF_Len                             (5U)
#define AON_PMU_VAL_AVS_CTL_REF_Msk                             (0x1FU << AON_PMU_VAL_AVS_CTL_REF_Pos)
#define AON_PMU_VAL_AVS_CTL_REF                                 AON_PMU_VAL_AVS_CTL_REF_Msk

#define AON_PMU_VAL_RNG_OSC_CLK_EN_Pos                          (7U)
#define AON_PMU_VAL_RNG_OSC_CLK_EN_Len                          (1U)
#define AON_PMU_VAL_RNG_OSC_CLK_EN_Msk                          (0x1U << AON_PMU_VAL_RNG_OSC_CLK_EN_Pos)
#define AON_PMU_VAL_RNG_OSC_CLK_EN                              AON_PMU_VAL_RNG_OSC_CLK_EN_Msk

#define AON_PMU_VAL_STB_IO_LDO_Pos                              (6U)
#define AON_PMU_VAL_STB_IO_LDO_Len                              (1U)
#define AON_PMU_VAL_STB_IO_LDO_Msk                              (0x1U << AON_PMU_VAL_STB_IO_LDO_Pos)
#define AON_PMU_VAL_STB_IO_LDO                                  AON_PMU_VAL_STB_IO_LDO_Msk

#define AON_PMU_VAL_IO_LDO_EN_Pos                               (5U)
#define AON_PMU_VAL_IO_LDO_EN_Len                               (1U)
#define AON_PMU_VAL_IO_LDO_EN_Msk                               (0x1U << AON_PMU_VAL_IO_LDO_EN_Pos)
#define AON_PMU_VAL_IO_LDO_EN                                   AON_PMU_VAL_IO_LDO_EN_Msk

#define AON_PMU_VAL_DIG_LDO_EN_Pos                              (3U)
#define AON_PMU_VAL_DIG_LDO_EN_Len                              (1U)
#define AON_PMU_VAL_DIG_LDO_EN_Msk                              (0x1U << AON_PMU_VAL_DIG_LDO_EN_Pos)
#define AON_PMU_VAL_DIG_LDO_EN                                  AON_PMU_VAL_DIG_LDO_EN_Msk

#define AON_PMU_VAL_HF_OSC_EN_Pos                               (2U)
#define AON_PMU_VAL_HF_OSC_EN_Len                               (1U)
#define AON_PMU_VAL_HF_OSC_EN_Msk                               (0x1U << AON_PMU_VAL_HF_OSC_EN_Pos)
#define AON_PMU_VAL_HF_OSC_EN                                   AON_PMU_VAL_HF_OSC_EN_Msk

#define AON_PMU_VAL_SYS_LDO_EN_Pos                              (1U)
#define AON_PMU_VAL_SYS_LDO_EN_Len                              (1U)
#define AON_PMU_VAL_SYS_LDO_EN_Msk                              (0x1U << AON_PMU_VAL_SYS_LDO_EN_Pos)
#define AON_PMU_VAL_SYS_LDO_EN                                  AON_PMU_VAL_SYS_LDO_EN_Msk

#define AON_PMU_VAL_DCDC_EN_Pos                                 (0U)
#define AON_PMU_VAL_DCDC_EN_Len                                 (1U)
#define AON_PMU_VAL_DCDC_EN_Msk                                 (0x1U << AON_PMU_VAL_DCDC_EN_Pos)
#define AON_PMU_VAL_DCDC_EN                                     AON_PMU_VAL_DCDC_EN_Msk

/*******************  Bit definition for AON_PMU_PMU_INTF_OVR_RD0 register  *******************/
#define AON_PMU_RD_AVS_CTL_REF_Pos                              (9U)
#define AON_PMU_RD_AVS_CTL_REF_Len                              (5U)
#define AON_PMU_RD_AVS_CTL_REF_Msk                              (0x1FU << AON_PMU_RD_AVS_CTL_REF_Pos)
#define AON_PMU_RD_AVS_CTL_REF                                  AON_PMU_RD_AVS_CTL_REF_Msk

#define AON_PMU_RD_RNG_OSC_CLK_EN_Pos                           (7U)
#define AON_PMU_RD_RNG_OSC_CLK_EN_Len                           (1U)
#define AON_PMU_RD_RNG_OSC_CLK_EN_Msk                           (0x1U << AON_PMU_RD_RNG_OSC_CLK_EN_Pos)
#define AON_PMU_RD_RNG_OSC_CLK_EN                               AON_PMU_RD_RNG_OSC_CLK_EN_Msk

#define AON_PMU_RD_STB_IO_LDO_Pos                               (6U)
#define AON_PMU_RD_STB_IO_LDO_Len                               (1U)
#define AON_PMU_RD_STB_IO_LDO_Msk                               (0x1U << AON_PMU_RD_STB_IO_LDO_Pos)
#define AON_PMU_RD_STB_IO_LDO                                   AON_PMU_RD_STB_IO_LDO_Msk

#define AON_PMU_RD_IO_LDO_EN_Pos                                (5U)
#define AON_PMU_RD_IO_LDO_EN_Len                                (1U)
#define AON_PMU_RD_IO_LDO_EN_Msk                                (0x1U << AON_PMU_RD_IO_LDO_EN_Pos)
#define AON_PMU_RD_IO_LDO_EN                                    AON_PMU_RD_IO_LDO_EN_Msk

#define AON_PMU_RD_DIG_LDO_EN_Pos                               (3U)
#define AON_PMU_RD_DIG_LDO_EN_Len                               (1U)
#define AON_PMU_RD_DIG_LDO_EN_Msk                               (0x1U << AON_PMU_RD_DIG_LDO_EN_Pos)
#define AON_PMU_RD_DIG_LDO_EN                                   AON_PMU_RD_DIG_LDO_EN_Msk

#define AON_PMU_RD_HF_OSC_EN_Pos                                (2U)
#define AON_PMU_RD_HF_OSC_EN_Len                                (1U)
#define AON_PMU_RD_HF_OSC_EN_Msk                                (0x1U << AON_PMU_RD_HF_OSC_EN_Pos)
#define AON_PMU_RD_HF_OSC_EN                                    AON_PMU_RD_HF_OSC_EN_Msk

#define AON_PMU_RD_SYS_LDO_EN_Pos                               (1U)
#define AON_PMU_RD_SYS_LDO_EN_Len                               (1U)
#define AON_PMU_RD_SYS_LDO_EN_Msk                               (0x1U << AON_PMU_RD_FAST_LDO_EN_Pos)
#define AON_PMU_RD_SYS_LDO_EN                                   AON_PMU_RD_FAST_LDO_EN_Msk

#define AON_PMU_RD_DCDC_EN_Pos                                  (0U)
#define AON_PMU_RD_DCDC_EN_Len                                  (1U)
#define AON_PMU_RD_DCDC_EN_Msk                                  (0x1U << AON_PMU_RD_DCDC_EN_Pos)
#define AON_PMU_RD_DCDC_EN                                      AON_PM_RD_DCDC_EN_Msk


/*******************  Bit definition for AON_PMU_ADVS_CFG_0 register  ******************************/
#define AON_PMU_ADVS_DCDC_EN_LIMITER_Pos                     (0U)
#define AON_PMU_ADVS_DCDC_EN_LIMITER_Len                     (1U)
#define AON_PMU_ADVS_DCDC_EN_LIMITER_Msk                     (0x1UL << AON_PMU_ADVS_DCDC_EN_LIMITER_Pos)
#define AON_PMU_ADVS_DCDC_EN_LIMITER                         AON_PMU_ADVS_DCDC_EN_LIMITER_Msk

#define AON_PMU_ADVS_DCDC_VTBIAS_SLOPE_CTRL_Pos              (1U)
#define AON_PMU_ADVS_DCDC_VTBIAS_SLOPE_CTRL_Len              (1U)
#define AON_PMU_ADVS_DCDC_VTBIAS_SLOPE_CTRL_Msk              (0x1UL << AON_PMU_ADVS_DCDC_VTBIAS_SLOPE_CTRL_Pos)
#define AON_PMU_ADVS_DCDC_VTBIAS_SLOPE_CTRL                  AON_PMU_ADVS_DCDC_VTBIAS_SLOPE_CTRL_Msk

#define AON_PMU_ADVS_DCDC_EN_BLK_Pos                         (2U)
#define AON_PMU_ADVS_DCDC_EN_BLK_Len                         (1U)
#define AON_PMU_ADVS_DCDC_EN_BLK_Msk                         (0x1UL << AON_PMU_ADVS_DCDC_EN_BLK_Pos)
#define AON_PMU_ADVS_DCDC_EN_BLK                             AON_PMU_ADVS_DCDC_EN_BLK_Msk

#define AON_PMU_ADVS_DCDC_EN_VTBIAS_Pos                      (3U)
#define AON_PMU_ADVS_DCDC_EN_VTBIAS_Len                      (1U)
#define AON_PMU_ADVS_DCDC_EN_VTBIAS_Msk                      (0x1UL << AON_PMU_ADVS_DCDC_EN_VTBIAS_Pos)
#define AON_PMU_ADVS_DCDC_EN_VTBIAS                          AON_PMU_ADVS_DCDC_EN_VTBIAS_Msk

#define AON_PMU_ADVS_DCDC_VTBIAS_CTRL_LIMIT_2_0_Pos          (8U)
#define AON_PMU_ADVS_DCDC_VTBIAS_CTRL_LIMIT_2_0_Len          (2U)
#define AON_PMU_ADVS_DCDC_VTBIAS_CTRL_LIMIT_2_0_Msk          (0x3UL << AON_PMU_ADVS_DCDC_VTBIAS_CTRL_LIMIT_2_0_Pos)
#define AON_PMU_ADVS_DCDC_VTBIAS_CTRL_LIMIT_2_0              AON_PMU_ADVS_DCDC_VTBIAS_CTRL_LIMIT_2_0_Msk

#define AON_PMU_ADVS_DCDC_VTBIAS_CTRL_VT_2_0_Pos             (12U)
#define AON_PMU_ADVS_DCDC_VTBIAS_CTRL_VT_2_0_Len             (3U)
#define AON_PMU_ADVS_DCDC_VTBIAS_CTRL_VT_2_0_Msk             (0x7UL << AON_PMU_ADVS_DCDC_VTBIAS_CTRL_VT_2_0_Pos)
#define AON_PMU_ADVS_DCDC_VTBIAS_CTRL_VT_2_0                 AON_PMU_ADVS_DCDC_VTBIAS_CTRL_VT_2_0_Msk

#define AON_PMU_ADVS_LPD_VTBIAS_CTRL_Pos                     (16U)
#define AON_PMU_ADVS_LPD_VTBIAS_CTRL_Len                     (7U)
#define AON_PMU_ADVS_LPD_VTBIAS_CTRL_Msk                     (0x7FUL << AON_PMU_ADVS_LPD_VTBIAS_CTRL_Pos)
#define AON_PMU_ADVS_LPD_VTBIAS_CTRL                         AON_PMU_ADVS_LPD_VTBIAS_CTRL_Msk

#define AON_PMU_ADVS_LPD_VTBIAS_EN_Pos                       (23U)
#define AON_PMU_ADVS_LPD_VTBIAS_EN_Len                       (1U)
#define AON_PMU_ADVS_LPD_VTBIAS_EN_Msk                       (0x1UL << AON_PMU_ADVS_LPD_VTBIAS_EN_Pos)
#define AON_PMU_ADVS_LPD_VTBIAS_EN                           AON_PMU_ADVS_LPD_VTBIAS_EN_Msk

/*******************  Bit definition for AON_PMU_ADVS_CFG_1 register  ******************************/
#define AON_PMU_ADVS_DIGCORE_EN_LIMITER_Pos                  (4U)
#define AON_PMU_ADVS_DIGCORE_EN_LIMITER_Len                  (1U)
#define AON_PMU_ADVS_DIGCORE_EN_LIMITER_Msk                  (0x1UL << AON_PMU_ADVS_DIGCORE_EN_LIMITER_Pos)
#define AON_PMU_ADVS_DIGCORE_EN_LIMITER                      AON_PMU_ADVS_DIGCORE_EN_LIMITER_Msk

#define AON_PMU_ADVS_DIGCORE_VTBIAS_SLOPE_CTRL_Pos           (5U)
#define AON_PMU_ADVS_DIGCORE_VTBIAS_SLOPE_CTRL_Len           (1U)
#define AON_PMU_ADVS_DIGCORE_VTBIAS_SLOPE_CTRL_Msk           (0x1UL << AON_PMU_ADVS_DIGCORE_VTBIAS_SLOPE_CTRL_Pos)
#define AON_PMU_ADVS_DIGCORE_VTBIAS_SLOPE_CTRL               AON_PMU_ADVS_DIGCORE_VTBIAS_SLOPE_CTRL_Msk

#define AON_PMU_ADVS_DIGCORE_EN_BLK_Pos                      (6U)
#define AON_PMU_ADVS_DIGCORE_EN_BLK_Len                      (1U)
#define AON_PMU_ADVS_DIGCORE_EN_BLK_Msk                      (0x1UL << AON_PMU_ADVS_DIGCORE_EN_BLK_Pos)
#define AON_PMU_ADVS_DIGCORE_EN_BLK                          AON_PMU_ADVS_DIGCORE_EN_BLK_Msk

#define AON_PMU_ADVS_DIGCORE_EN_VTBIAS_Pos                   (7U)
#define AON_PMU_ADVS_DIGCORE_EN_VTBIAS_Len                   (1U)
#define AON_PMU_ADVS_DIGCORE_EN_VTBIAS_Msk                   (0x1UL << AON_PMU_ADVS_DIGCORE_EN_VTBIAS_Pos)
#define AON_PMU_ADVS_DIGCORE_EN_VTBIAS                       AON_PMU_ADVS_DIGCORE_EN_VTBIAS_Msk

#define AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_LIMIT_2_0_Pos       (8U)
#define AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_LIMIT_2_0_Len       (2U)
#define AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_LIMIT_2_0_Msk       (0x3UL << AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_LIMIT_2_0_Pos)
#define AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_LIMIT_2_0           AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_LIMIT_2_0_Msk

#define AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_VT_2_0_Pos          (12U)
#define AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_VT_2_0_Len          (3U)
#define AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_VT_2_0_Msk          (0x7UL << AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_VT_2_0_Pos)
#define AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_VT_2_0              AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_VT_2_0_Msk

/* ================================================================================================================= */
/* ================                                        AON_PWR                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for AON_PWR_A_TIMING_CTRL0 register  *******************/
#define AON_PWR_A_TIMING_CTRL0_DCDC_Pos                     (0U)
#define AON_PWR_A_TIMING_CTRL0_DCDC_Len                     (9U)
#define AON_PWR_A_TIMING_CTRL0_DCDC_Msk                     (0x1FFUL << AON_PWR_A_TIMING_CTRL0_DCDC_Pos)
#define AON_PWR_A_TIMING_CTRL0_DCDC                         AON_PWR_A_TIMING_CTRL0_DCDC_Msk

#define AON_PWR_A_TIMING_CTRL0_DIG_LDO_Pos                  (16U)
#define AON_PWR_A_TIMING_CTRL0_DIG_LDO_Len                  (9U)
#define AON_PWR_A_TIMING_CTRL0_DIG_LDO_Msk                  (0x1FFUL << AON_PWR_A_TIMING_CTRL0_DIG_LDO_Pos)
#define AON_PWR_A_TIMING_CTRL0_DIG_LDO                      AON_PWR_A_TIMING_CTRL0_DIG_LDO_Msk

/*******************  Bit definition for AON_PWR_A_TIMING_CTRL1 register  *******************/
#define AON_PWR_A_TIMING_CTRL1_FAST_LDO_Pos                 (0U)
#define AON_PWR_A_TIMING_CTRL1_FAST_LDO_Len                 (9U)
#define AON_PWR_A_TIMING_CTRL1_FAST_LDO_Msk                 (0x1FFUL << AON_PWR_A_TIMING_CTRL1_FAST_LDO_Pos)
#define AON_PWR_A_TIMING_CTRL1_FAST_LDO                     AON_PWR_A_TIMING_CTRL1_FAST_LDO_Msk

#define AON_PWR_A_TIMING_CTRL1_HF_OSC_Pos                   (16U)
#define AON_PWR_A_TIMING_CTRL1_HF_OSC_Len                   (9U)
#define AON_PWR_A_TIMING_CTRL1_HF_OSC_Msk                   (0x1FFUL << AON_PWR_A_TIMING_CTRL1_HF_OSC_Pos)
#define AON_PWR_A_TIMING_CTRL1_HF_OSC                       AON_PWR_A_TIMING_CTRL1_HF_OSC_Msk

/*******************  Bit definition for AON_PWR_A_TIMING_CTRL2 register  *******************/
#define AON_PWR_A_TIMING_CTRL2_PLL_LOCK_Pos                 (0U)
#define AON_PWR_A_TIMING_CTRL2_PLL_LOCK_Len                 (9U)
#define AON_PWR_A_TIMING_CTRL2_PLL_LOCK_Msk                 (0x1FFUL << AON_PWR_A_TIMING_CTRL2_PLL_LOCK_Pos)
#define AON_PWR_A_TIMING_CTRL2_PLL_LOCK                     AON_PWR_A_TIMING_CTRL2_PLL_LOCK_Msk

#define AON_PWR_A_TIMING_CTRL2_PLL_Pos                      (16U)
#define AON_PWR_A_TIMING_CTRL2_PLL_Len                      (9U)
#define AON_PWR_A_TIMING_CTRL2_PLL_Msk                      (0x1FFUL << AON_PWR_A_TIMING_CTRL2_PLL_Pos)
#define AON_PWR_A_TIMING_CTRL2_PLL                          AON_PWR_A_TIMING_CTRL2_PLL_Msk

/*******************  Bit definition for AON_PWR_A_TIMING_CTRL3 register  *******************/
#define AON_PWR_A_TIMING_CTRL3_PWR_SWITCH_Pos               (0U)
#define AON_PWR_A_TIMING_CTRL3_PWR_SWITCH_Len               (9U)
#define AON_PWR_A_TIMING_CTRL3_PWR_SWITCH_Msk               (0x1FFUL << AON_PWR_A_TIMING_CTRL3_PWR_SWITCH_Pos)
#define AON_PWR_A_TIMING_CTRL3_PWR_SWITCH                   AON_PWR_A_TIMING_CTRL3_PWR_SWITCH_Msk

#define AON_PWR_A_TIMING_CTRL3_XO_Pos                       (16U)
#define AON_PWR_A_TIMING_CTRL3_XO_Len                       (9U)
#define AON_PWR_A_TIMING_CTRL3_XO_Msk                       (0x1FFUL << AON_PWR_A_TIMING_CTRL3_XO_Pos)
#define AON_PWR_A_TIMING_CTRL3_XO                           AON_PWR_A_TIMING_CTRL3_XO_Msk

/*******************  Bit definition for AON_PWR_A_TIMING_CTRL4 register  *******************/
#define AON_PWR_A_TIMING_CTRL4_XO_BIAS_SW_Pos               (0U)
#define AON_PWR_A_TIMING_CTRL4_XO_BIAS_SW_Len               (9U)
#define AON_PWR_A_TIMING_CTRL4_XO_BIAS_SW_Msk               (0x1FFUL << AON_PWR_A_TIMING_CTRL4_XO_BIAS_SW_Pos)
#define AON_PWR_A_TIMING_CTRL4_XO_BIAS_SW                   AON_PWR_A_TIMING_CTRL4_XO_BIAS_SW_Msk

#define AON_PWR_A_TIMING_CTRL4_RF_TUNE_Pos                  (16U)
#define AON_PWR_A_TIMING_CTRL4_RF_TUNE_Len                  (9U)
#define AON_PWR_A_TIMING_CTRL4_RF_TUNE_Msk                  (0x1FFUL << AON_PWR_A_TIMING_CTRL4_RF_TUNE_Pos)
#define AON_PWR_A_TIMING_CTRL4_RF_TUNE                      AON_PWR_A_TIMING_CTRL4_RF_TUNE_Msk

/*******************  Bit definition for AON_PWR_A_SLP_CFG register  *******************/
#define AON_PWR_A_SLP_CFG_TRN_OFF_DCDC_Pos                  (0U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_DCDC_Len                  (1U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_DCDC_Msk                  (0x1UL << AON_PWR_A_SLP_CFG_TRN_OFF_DCDC_Pos)
#define AON_PWR_A_SLP_CFG_TRN_OFF_DCDC                      AON_PWR_A_SLP_CFG_TRN_OFF_DCDC_Msk

#define AON_PWR_A_SLP_CFG_TRN_OFF_DIG_LDO_Pos               (1U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_DIG_LDO_Len               (1U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_DIG_LDO_Msk               (0x1UL << AON_PWR_A_SLP_CFG_TRN_OFF_DIG_LDO_Pos)
#define AON_PWR_A_SLP_CFG_TRN_OFF_DIG_LDO                   AON_PWR_A_SLP_CFG_TRN_OFF_DIG_LDO_Msk

#define AON_PWR_A_SLP_CFG_TRN_OFF_HF_OSC_Pos                (2U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_HF_OSC_Len                (1U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_HF_OSC_Msk                (0x1UL << AON_PWR_A_SLP_CFG_TRN_OFF_HF_OSC_Pos)
#define AON_PWR_A_SLP_CFG_TRN_OFF_HF_OSC                    AON_PWR_A_SLP_CFG_TRN_OFF_HF_OSC_Msk

#define AON_PWR_A_SLP_CFG_TRN_OFF_IO_LDO_Pos                (3U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_IO_LDO_Len                (1U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_IO_LDO_Msk                (0x1UL << AON_PWR_A_SLP_CFG_TRN_OFF_IO_LDO_Pos)
#define AON_PWR_A_SLP_CFG_TRN_OFF_IO_LDO                    AON_PWR_A_SLP_CFG_TRN_OFF_IO_LDO_Msk

#define AON_PWR_A_SLP_CFG_TRN_OFF_FAST_LDO_Pos              (4U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_FAST_LDO_Len              (1U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_FAST_LDO_Msk              (0x1UL << AON_PWR_A_SLP_CFG_TRN_OFF_FAST_LDO_Pos)
#define AON_PWR_A_SLP_CFG_TRN_OFF_FAST_LDO                  AON_PWR_A_SLP_CFG_TRN_OFF_FAST_LDO_Msk

#define AON_PWR_A_SLP_CFG_TRN_OFF_XO_Pos                    (16U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_XO_Len                    (1U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_XO_Msk                    (0x1UL << AON_PWR_A_SLP_CFG_TRN_OFF_XO_Pos)
#define AON_PWR_A_SLP_CFG_TRN_OFF_XO                        AON_PWR_A_SLP_CFG_TRN_OFF_XO_Msk

#define AON_PWR_A_SLP_CFG_TRN_OFF_PLL_Pos                   (17U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_PLL_Len                   (1U)
#define AON_PWR_A_SLP_CFG_TRN_OFF_PLL_Msk                   (0x1UL << AON_PWR_A_SLP_CFG_TRN_OFF_PLL_Pos)
#define AON_PWR_A_SLP_CFG_TRN_OFF_PLL                       AON_PWR_A_SLP_CFG_TRN_OFF_PLL_Msk

#define AON_PWR_A_SLP_CFG_TRN_ON_STB_LDO_Pos                (18U)
#define AON_PWR_A_SLP_CFG_TRN_ON_STB_LDO_Len                (1U)
#define AON_PWR_A_SLP_CFG_TRN_ON_STB_LDO_Msk                (0x1UL << AON_PWR_A_SLP_CFG_TRN_ON_STB_LDO_Pos)
#define AON_PWR_A_SLP_CFG_TRN_ON_STB_LDO                    AON_PWR_A_SLP_CFG_TRN_ON_STB_LDO_Msk

/*******************  Bit definition for AON_PWR_AON_START_CFG register  *******************/
#define AON_PWR_AON_START_CFG_POWER_MODE_Pos                (1U)
#define AON_PWR_AON_START_CFG_POWER_MODE_Len                (2U)
#define AON_PWR_AON_START_CFG_POWER_MODE_Msk                (0x3UL << AON_PWR_AON_START_CFG_POWER_MODE_Pos)
#define AON_PWR_AON_START_CFG_POWER_MODE                    AON_PWR_AON_START_CFG_POWER_MODE_Msk
#define AON_PWR_AON_START_CFG_DCDC_ONLY                     (0)
#define AON_PWR_AON_START_CFG_SYSLDO_ONLY                   (1)
#define AON_PWR_AON_START_CFG_SYSLDO_AND_DCDC_CLOSE_SYSLDO  (2)
#define AON_PWR_AON_START_CFG_SYSLDO_AND_DCDC               (3)


#define AON_PWR_AON_START_CFG_XO_EN_PWR_Pos                 (4U)
#define AON_PWR_AON_START_CFG_XO_EN_PWR_Len                 (1U)
#define AON_PWR_AON_START_CFG_XO_EN_PWR_Msk                 (0x1UL << AON_PWR_AON_START_CFG_XO_EN_PWR_Pos)
#define AON_PWR_AON_START_CFG_XO_EN_PWR                     AON_PWR_AON_START_CFG_XO_EN_PWR_Msk

#define AON_PWR_AON_START_CFG_PLL_EN_PWR_Pos                (6U)
#define AON_PWR_AON_START_CFG_PLL_EN_PWR_Len                (1U)
#define AON_PWR_AON_START_CFG_PLL_EN_PWR_Msk                (0x1UL << AON_PWR_AON_START_CFG_PLL_EN_PWR_Pos)
#define AON_PWR_AON_START_CFG_PLL_EN_PWR                    AON_PWR_AON_START_CFG_PLL_EN_PWR_Msk

/*******************  Bit definition for AON_PWR_DPAD_LE_CTRL register  *******************/
#define AON_PWR_DPAD_LE_CTRL_WR_Pos                         (0U)
#define AON_PWR_DPAD_LE_CTRL_WR_Len                         (1U)
#define AON_PWR_DPAD_LE_CTRL_WR_Msk                         (0x1UL << AON_PWR_DPAD_LE_CTRL_WR_Pos)
#define AON_PWR_DPAD_LE_CTRL_WR                             AON_PWR_DPAD_LE_CTRL_WR_Msk

#define AON_PWR_DPAD_LE_CTRL_APPLY_WR_Pos                   (2U)
#define AON_PWR_DPAD_LE_CTRL_APPLY_WR_Len                   (1U)
#define AON_PWR_DPAD_LE_CTRL_APPLY_WR_Msk                   (0x1UL << AON_PWR_DPAD_LE_CTRL_APPLY_WR_Pos)
#define AON_PWR_DPAD_LE_CTRL_APPLY_WR                       AON_PWR_DPAD_LE_CTRL_APPLY_WR_Msk

#define AON_PWR_DPAD_LE_CTRL_READ_Pos                       (8U)
#define AON_PWR_DPAD_LE_CTRL_READ_Len                       (1U)
#define AON_PWR_DPAD_LE_CTRL_READ_Msk                       (0x1UL << AON_PWR_DPAD_LE_CTRL_READ_Pos)
#define AON_PWR_DPAD_LE_CTRL_READ                           AON_PWR_DPAD_LE_CTRL_READ_Msk

#define AON_PWR_DPAD_LE_CTRL_BUSY_Pos                       (10U)
#define AON_PWR_DPAD_LE_CTRL_BUSY_Len                       (1U)
#define AON_PWR_DPAD_LE_CTRL_BUSY_Msk                       (0x1UL << AON_PWR_DPAD_LE_CTRL_BUSY_Pos)
#define AON_PWR_DPAD_LE_CTRL_BUSY                           AON_PWR_DPAD_LE_CTRL_BUSY_Msk

#define AON_PWR_DPAD_LE_CTRL_SLEEP_Pos                      (16U)
#define AON_PWR_DPAD_LE_CTRL_SLEEP_Len                      (1U)
#define AON_PWR_DPAD_LE_CTRL_SLEEP_Msk                      (0x1UL << AON_PWR_DPAD_LE_CTRL_SLEEP_Pos)
#define AON_PWR_DPAD_LE_CTRL_SLEEP                          AON_PWR_DPAD_LE_CTRL_SLEEP_Msk

#define AON_PWR_DPAD_LE_CTRL_WAKEUP_Pos                     (18U)
#define AON_PWR_DPAD_LE_CTRL_WAKEUP_Len                     (1U)
#define AON_PWR_DPAD_LE_CTRL_WAKEUP_Msk                     (0x1UL << AON_PWR_DPAD_LE_CTRL_WAKEUP_Pos)
#define AON_PWR_DPAD_LE_CTRL_WAKEUP                         AON_PWR_DPAD_LE_CTRL_WAKEUP_Msk

/*******************  Bit definition for AON_PWR_AON_SLP_CTRL register  *******************/
#define AON_PWR_AON_SLP_CTRL_REQ_Pos                        (0U)
#define AON_PWR_AON_SLP_CTRL_REQ_Len                        (1U)
#define AON_PWR_AON_SLP_CTRL_REQ_Msk                        (0x1UL << AON_PWR_AON_SLP_CTRL_REQ_Pos)
#define AON_PWR_AON_SLP_CTRL_REQ                            AON_PWR_AON_SLP_CTRL_REQ_Msk

#define AON_PWR_AON_SLP_CTRL_PRO_Pos                        (8U)
#define AON_PWR_AON_SLP_CTRL_PRO_Len                        (1U)
#define AON_PWR_AON_SLP_CTRL_PRO_Msk                        (0x1UL << AON_PWR_AON_SLP_CTRL_PRO_Pos)
#define AON_PWR_AON_SLP_CTRL_PRO                            AON_PWR_AON_SLP_CTRL_PRO_Msk

/*******************  Bit definition for AON_PWR_XO_PLL_SET register  *******************/
#define AON_PWR_XO_PLL_SET_PLL_SET_Pos                      (0U)
#define AON_PWR_XO_PLL_SET_PLL_SET_Len                      (1U)
#define AON_PWR_XO_PLL_SET_PLL_SET_Msk                      (0x1UL << AON_PWR_XO_PLL_SET_PLL_SET_Pos)
#define AON_PWR_XO_PLL_SET_PLL_SET                          AON_PWR_XO_PLL_SET_PLL_SET_Msk

#define AON_PWR_XO_PLL_SET_XO_SET_Pos                       (1U)
#define AON_PWR_XO_PLL_SET_XO_SET_Len                       (1U)
#define AON_PWR_XO_PLL_SET_XO_SET_Msk                       (0x1UL << AON_PWR_XO_PLL_SET_XO_SET_Pos)
#define AON_PWR_XO_PLL_SET_XO_SET                           AON_PWR_XO_PLL_SET_XO_SET_Msk

#define AON_PWR_XO_PLL_SET_HF_OSC_SET_Pos                   (2U)
#define AON_PWR_XO_PLL_SET_HF_OSC_SET_Len                   (1U)
#define AON_PWR_XO_PLL_SET_HF_OSC_SET_Msk                   (0x1UL << AON_PWR_XO_PLL_SET_HF_OSC_SET_Pos)
#define AON_PWR_XO_PLL_SET_HF_OSC_SET                       AON_PWR_XO_PLL_SET_HF_OSC_SET_Msk

/*******************  Bit definition for AON_PWR_XO_PLL_CLR register  *******************/
#define AON_PWR_XO_PLL_CLR_PLL_CLR_Pos                      (0U)
#define AON_PWR_XO_PLL_CLR_PLL_CLR_Len                      (1U)
#define AON_PWR_XO_PLL_CLR_PLL_CLR_Msk                      (0x1UL << AON_PWR_XO_PLL_CLR_PLL_CLR_Pos)
#define AON_PWR_XO_PLL_CLR_PLL_CLR                          AON_PWR_XO_PLL_CLR_PLL_CLR_Msk

#define AON_PWR_XO_PLL_CLR_XO_CLR_Pos                       (1U)
#define AON_PWR_XO_PLL_CLR_XO_CLR_Len                       (1U)
#define AON_PWR_XO_PLL_CLR_XO_CLR_Msk                       (0x1UL << AON_PWR_XO_PLL_CLR_XO_CLR_Pos)
#define AON_PWR_XO_PLL_CLR_XO_CLR                           AON_PWR_XO_PLL_CLR_XO_CLR_Msk

#define AON_PWR_XO_PLL_CLR_HF_OSC_CLR_Pos                   (2U)
#define AON_PWR_XO_PLL_CLR_HF_OSC_CLR_Len                   (1U)
#define AON_PWR_XO_PLL_CLR_HF_OSC_CLR_Msk                   (0x1UL << AON_PWR_XO_PLL_CLR_HF_OSC_CLR_Pos)
#define AON_PWR_XO_PLL_CLR_HF_OSC_CLR                       AON_PWR_XO_PLL_CLR_HF_OSC_CLR_Msk

/*******************  Bit definition for AON_PWR_XO_PLL_STAT register  *******************/
#define AON_PWR_XO_PLL_STAT_PLL_STAT_Pos                    (0U)
#define AON_PWR_XO_PLL_STAT_PLL_STAT_Len                    (1U)
#define AON_PWR_XO_PLL_STAT_PLL_STAT_Msk                    (0x1UL << AON_PWR_XO_PLL_STAT_PLL_STAT_Pos)
#define AON_PWR_XO_PLL_STAT_PLL_STAT                        AON_PWR_XO_PLL_STAT_PLL_STAT_Msk

#define AON_PWR_XO_PLL_STAT_XO_STAT_Pos                     (1U)
#define AON_PWR_XO_PLL_STAT_XO_STAT_Len                     (1U)
#define AON_PWR_XO_PLL_STAT_XO_STAT_Msk                     (0x1UL << AON_PWR_XO_PLL_STAT_XO_STAT_Pos)
#define AON_PWR_XO_PLL_STAT_XO_STAT                         AON_PWR_XO_PLL_STAT_XO_STAT_Msk

#define AON_PWR_XO_PLL_STAT_HF_STAT_Pos                     (2U)
#define AON_PWR_XO_PLL_STAT_HF_STAT_Len                     (1U)
#define AON_PWR_XO_PLL_STAT_HF_STAT_Msk                     (0x1UL << AON_PWR_XO_PLL_STAT_HF_STAT_Pos)
#define AON_PWR_XO_PLL_STAT_HF_STAT                         AON_PWR_XO_PLL_STAT_HF_STAT_Msk

/*******************  Bit definition for AON_PWR_PWR_SET register  *******************/
#define AON_PWR_PWR_SET_DCDC_SET_Pos                        (0U)
#define AON_PWR_PWR_SET_DCDC_SET_Len                        (1U)
#define AON_PWR_PWR_SET_DCDC_SET_Msk                        (0x1UL << AON_PWR_PWR_SET_DCDC_SET_Pos)
#define AON_PWR_PWR_SET_DCDC_SET                            AON_PWR_PWR_SET_DCDC_SET_Msk

#define AON_PWR_PWR_SET_DIG_LDO_SET_Pos                     (1U)
#define AON_PWR_PWR_SET_DIG_LDO_SET_Len                     (1U)
#define AON_PWR_PWR_SET_DIG_LDO_SET_Msk                     (0x1UL << AON_PWR_PWR_SET_DIG_LDO_SET_Pos)
#define AON_PWR_PWR_SET_DIG_LDO_SET                         AON_PWR_PWR_SET_DIG_LDO_SET_Msk

#define AON_PWR_PWR_SET_FAST_LDO_SET_Pos                    (2U)
#define AON_PWR_PWR_SET_FAST_LDO_SET_Len                    (1U)
#define AON_PWR_PWR_SET_FAST_LDO_SET_Msk                    (0x1UL << AON_PWR_PWR_SET_FAST_LDO_SET_Pos)
#define AON_PWR_PWR_SET_FAST_LDO_SET                        AON_PWR_PWR_SET_FAST_LDO_SET_Msk

#define AON_PWR_PWR_SET_IO_LDO_SET_Pos                      (4U)
#define AON_PWR_PWR_SET_IO_LDO_SET_Len                      (1U)
#define AON_PWR_PWR_SET_IO_LDO_SET_Msk                      (0x1UL << AON_PWR_PWR_SET_IO_LDO_SET_Pos)
#define AON_PWR_PWR_SET_IO_LDO_SET                          AON_PWR_PWR_SET_IO_LDO_SET_Msk

#define AON_PWR_PWR_SET_STB_IO_LDO_SET_Pos                  (5U)
#define AON_PWR_PWR_SET_STB_IO_LDO_SET_Len                  (1U)
#define AON_PWR_PWR_SET_STB_IO_LDO_SET_Msk                  (0x1UL << AON_PWR_PWR_SET_STB_IO_LDO_SET_Pos)
#define AON_PWR_PWR_SET_STB_IO_LDO_SET                      AON_PWR_PWR_SET_STB_IO_LDO_SET_Msk

/*******************  Bit definition for AON_PWR_PWR_CLR register  *******************/
#define AON_PWR_PWR_CLR_DCDC_CLR_Pos                        (0U)
#define AON_PWR_PWR_CLR_DCDC_CLR_Len                        (1U)
#define AON_PWR_PWR_CLR_DCDC_CLR_Msk                        (0x1UL << AON_PWR_PWR_CLR_DCDC_CLR_Pos)
#define AON_PWR_PWR_CLR_DCDC_CLR                            AON_PWR_PWR_CLR_DCDC_CLR_Msk

#define AON_PWR_PWR_CLR_DIG_LDO_CLR_Pos                     (1U)
#define AON_PWR_PWR_CLR_DIG_LDO_CLR_Len                     (1U)
#define AON_PWR_PWR_CLR_DIG_LDO_CLR_Msk                     (0x1UL << AON_PWR_PWR_CLR_DIG_LDO_CLR_Pos)
#define AON_PWR_PWR_CLR_DIG_LDO_CLR                         AON_PWR_PWR_CLR_DIG_LDO_CLR_Msk

#define AON_PWR_PWR_CLR_FAST_LDO_CLR_Pos                    (2U)
#define AON_PWR_PWR_CLR_FAST_LDO_CLR_Len                    (1U)
#define AON_PWR_PWR_CLR_FAST_LDO_CLR_Msk                    (0x1UL << AON_PWR_PWR_CLR_FAST_LDO_CLR_Pos)
#define AON_PWR_PWR_CLR_FAST_LDO_CLR                        AON_PWR_PWR_CLR_FAST_LDO_CLR_Msk

#define AON_PWR_PWR_CLR_IO_LDO_CLR_Pos                      (4U)
#define AON_PWR_PWR_CLR_IO_LDO_CLR_Len                      (1U)
#define AON_PWR_PWR_CLR_IO_LDO_CLR_Msk                      (0x1UL << AON_PWR_PWR_CLR_IO_LDO_CLR_Pos)
#define AON_PWR_PWR_CLR_IO_LDO_CLR                          AON_PWR_PWR_CLR_IO_LDO_CLR_Msk

#define AON_PWR_PWR_CLR_STD_IO_LDO_CLR_Pos                  (5U)
#define AON_PWR_PWR_CLR_STD_IO_LDO_CLR_Len                  (1U)
#define AON_PWR_PWR_CLR_STD_IO_LDO_CLR_Msk                  (0x1UL << AON_PWR_PWR_CLR_STD_IO_LDO_CLR_Pos)
#define AON_PWR_PWR_CLR_STD_IO_LDO_CLR                       AON_PWR_PWR_CLR_STD_IO_LDO_CLR_Msk

/*******************  Bit definition for AON_PWR_PWR_STAT register  *******************/
#define AON_PWR_PWR_STAT_DCDC_AVL_Pos                       (0U)
#define AON_PWR_PWR_STAT_DCDC_AVL_Len                       (1U)
#define AON_PWR_PWR_STAT_DCDC_AVL_Msk                       (0x1UL << AON_PWR_PWR_STAT_DCDC_AVL_Pos)
#define AON_PWR_PWR_STAT_DCDC_AVL                           AON_PWR_PWR_STAT_DCDC_AVL_Msk

#define AON_PWR_PWR_STAT_DIG_LDO_AVL_Pos                    (1U)
#define AON_PWR_PWR_STAT_DIG_LDO_AVL_Len                    (1U)
#define AON_PWR_PWR_STAT_DIG_LDO_AVL_Msk                    (0x1UL << AON_PWR_PWR_STAT_DIG_LDO_AVL_Pos)
#define AON_PWR_PWR_STAT_DIG_LDO_AVL                        AON_PWR_PWR_STAT_DIG_LDO_AVL_Msk

#define AON_PWR_PWR_STAT_FAST_LDO_AVL_Pos                   (2U)
#define AON_PWR_PWR_STAT_FAST_LDO_AVL_Len                   (1U)
#define AON_PWR_PWR_STAT_FAST_LDO_AVL_Msk                   (0x1UL << AON_PWR_PWR_STAT_FAST_LDO_AVL_Pos)
#define AON_PWR_PWR_STAT_FAST_LDO_AVL                       AON_PWR_PWR_STAT_FAST_LDO_AVL_Msk

/*******************  Bit definition for AON_PWR_MEM_PWR_SLP0 register  *******************/
#define AON_PWR_MEM_PWR_SLP0_SET00_Pos                      (0U)
#define AON_PWR_MEM_PWR_SLP0_SET00_Len                      (2U)
#define AON_PWR_MEM_PWR_SLP0_SET00_Msk                      (0x3UL << AON_PWR_MEM_PWR_SLP0_SET00_Pos)
#define AON_PWR_MEM_PWR_SLP0_SET00                          AON_PWR_MEM_PWR_SLP0_SET00_Msk

#define AON_PWR_MEM_PWR_SLP0_SET01_Pos                      (2U)
#define AON_PWR_MEM_PWR_SLP0_SET01_Len                      (2U)
#define AON_PWR_MEM_PWR_SLP0_SET01_Msk                      (0x3UL << AON_PWR_MEM_PWR_SLP0_SET01_Pos)
#define AON_PWR_MEM_PWR_SLP0_SET01                          AON_PWR_MEM_PWR_SLP0_SET01_Msk

#define AON_PWR_MEM_PWR_SLP0_SET02_Pos                      (4U)
#define AON_PWR_MEM_PWR_SLP0_SET02_Len                      (2U)
#define AON_PWR_MEM_PWR_SLP0_SET02_Msk                      (0x3UL << AON_PWR_MEM_PWR_SLP0_SET02_Pos)
#define AON_PWR_MEM_PWR_SLP0_SET02                          AON_PWR_MEM_PWR_SLP0_SET02_Msk

#define AON_PWR_MEM_PWR_SLP0_SET03_Pos                      (6U)
#define AON_PWR_MEM_PWR_SLP0_SET03_Len                      (2U)
#define AON_PWR_MEM_PWR_SLP0_SET03_Msk                      (0x3UL << AON_PWR_MEM_PWR_SLP0_SET03_Pos)
#define AON_PWR_MEM_PWR_SLP0_SET03                          AON_PWR_MEM_PWR_SLP0_SET03_Msk

#define AON_PWR_MEM_PWR_SLP0_SET04_Pos                      (8U)
#define AON_PWR_MEM_PWR_SLP0_SET04_Len                      (2U)
#define AON_PWR_MEM_PWR_SLP0_SET04_Msk                      (0x3UL << AON_PWR_MEM_PWR_SLP0_SET04_Pos)
#define AON_PWR_MEM_PWR_SLP0_SET04                          AON_PWR_MEM_PWR_SLP0_SET04_Msk

/*******************  Bit definition for AON_PWR_MEM_PWR_SLP1 register  *******************/
#define AON_PWR_MEM_PWR_SLP1_HTM_DM_SET_Pos                 (2U)
#define AON_PWR_MEM_PWR_SLP1_HTM_DM_SET_Len                 (2U)
#define AON_PWR_MEM_PWR_SLP1_HTM_DM_SET_Msk                 (0x3UL << AON_PWR_MEM_PWR_SLP1_HTM_DM_SET_Pos)
#define AON_PWR_MEM_PWR_SLP1_HTM_DM_SET                     AON_PWR_MEM_PWR_SLP1_HTM_DM_SET_Msk

#define AON_PWR_MEM_PWR_SLP1_ICACHE_SET_Pos                 (4U)
#define AON_PWR_MEM_PWR_SLP1_ICACHE_SET_Len                 (2U)
#define AON_PWR_MEM_PWR_SLP1_ICACHE_SET_Msk                 (0x3UL << AON_PWR_MEM_PWR_SLP1_ICACHE_SET_Pos)
#define AON_PWR_MEM_PWR_SLP1_ICACHE_SET                     AON_PWR_MEM_PWR_SLP1_ICACHE_SET_Msk

/*******************  Bit definition for AON_PWR_MEM_PWR_WKUP0 register  *******************/
#define AON_PWR_MEM_PWR_WKUP0_SET00_Pos                     (0U)
#define AON_PWR_MEM_PWR_WKUP0_SET00_Len                     (2U)
#define AON_PWR_MEM_PWR_WKUP0_SET00_Msk                     (0x3UL << AON_PWR_MEM_PWR_WKUP0_SET00_Pos)
#define AON_PWR_MEM_PWR_WKUP0_SET00                         AON_PWR_MEM_PWR_WKUP0_SET00_Msk

#define AON_PWR_MEM_PWR_WKUP0_SET01_Pos                     (2U)
#define AON_PWR_MEM_PWR_WKUP0_SET01_Len                     (2U)
#define AON_PWR_MEM_PWR_WKUP0_SET01_Msk                     (0x3UL << AON_PWR_MEM_PWR_WKUP0_SET01_Pos)
#define AON_PWR_MEM_PWR_WKUP0_SET01                         AON_PWR_MEM_PWR_WKUP0_SET01_Msk

#define AON_PWR_MEM_PWR_WKUP0_SET02_Pos                     (4U)
#define AON_PWR_MEM_PWR_WKUP0_SET02_Len                     (2U)
#define AON_PWR_MEM_PWR_WKUP0_SET02_Msk                     (0x3UL << AON_PWR_MEM_PWR_WKUP0_SET02_Pos)
#define AON_PWR_MEM_PWR_WKUP0_SET02                         AON_PWR_MEM_PWR_WKUP0_SET02_Msk

#define AON_PWR_MEM_PWR_WKUP0_SET03_Pos                     (6U)
#define AON_PWR_MEM_PWR_WKUP0_SET03_Len                     (2U)
#define AON_PWR_MEM_PWR_WKUP0_SET03_Msk                     (0x3UL << AON_PWR_MEM_PWR_WKUP0_SET03_Pos)
#define AON_PWR_MEM_PWR_WKUP0_SET03                         AON_PWR_MEM_PWR_WKUP0_SET03_Msk

#define AON_PWR_MEM_PWR_WKUP0_SET04_Pos                     (8U)
#define AON_PWR_MEM_PWR_WKUP0_SET04_Len                     (2U)
#define AON_PWR_MEM_PWR_WKUP0_SET04_Msk                     (0x3UL << AON_PWR_MEM_PWR_WKUP0_SET04_Pos)
#define AON_PWR_MEM_PWR_WKUP0_SET04                         AON_PWR_MEM_PWR_WKUP0_SET04_Msk

/*******************  Bit definition for AON_PWR_MEM_PWR_WKUP1 register  *******************/
#define AON_PWR_MEM_PWR_WKUP1_HTM_DM_Pos                    (2U)
#define AON_PWR_MEM_PWR_WKUP1_HTM_DM_Len                    (2U)
#define AON_PWR_MEM_PWR_WKUP1_HTM_DM_Msk                    (0x3UL << AON_PWR_MEM_PWR_WKUP1_HTM_DM_Pos)
#define AON_PWR_MEM_PWR_WKUP1_HTM_DM                        AON_PWR_MEM_PWR_WKUP1_HTM_DM_Msk
#define AON_PWR_MEM_PWR_WKUP1_HTM_DM_OFF                    (0x0U << AON_PWR_MEM_PWR_WKUP1_HTM_DM_Pos)
#define AON_PWR_MEM_PWR_WKUP1_HTM_DM_FULL                   (0x2U << AON_PWR_MEM_PWR_WKUP1_HTM_DM_Pos)
#define AON_PWR_MEM_PWR_WKUP1_HTM_DM_RETE                   (0x3U << AON_PWR_MEM_PWR_WKUP1_HTM_DM_Pos)

#define AON_PWR_MEM_PWR_WKUP1_ICACHE_Pos                    (4U)
#define AON_PWR_MEM_PWR_WKUP1_ICACHE_Len                    (2U)
#define AON_PWR_MEM_PWR_WKUP1_ICACHE_Msk                    (0x3UL << AON_PWR_MEM_PWR_WKUP1_ICACHE_Pos)
#define AON_PWR_MEM_PWR_WKUP1_ICACHE                        AON_PWR_MEM_PWR_WKUP1_ICACHE_Msk
#define AON_PWR_MEM_PWR_WKUP1_ICACHE_OFF                    (0x0U << AON_PWR_MEM_PWR_WKUP1_ICACHE_Pos)
#define AON_PWR_MEM_PWR_WKUP1_ICACHE_FULL                   (0x2U << AON_PWR_MEM_PWR_WKUP1_ICACHE_Pos)
#define AON_PWR_MEM_PWR_WKUP1_ICACHE_RETE                   (0x3U << AON_PWR_MEM_PWR_WKUP1_ICACHE_Pos)

/*******************  Bit definition for AON_PWR_MEM_PWR_APPLY register  *******************/
#define AON_PWR_MEM_PWR_APPLY_APPLY_Pos                     (0U)
#define AON_PWR_MEM_PWR_APPLY_APPLY_Len                     (1U)
#define AON_PWR_MEM_PWR_APPLY_APPLY_Msk                     (0x1UL << AON_PWR_MEM_PWR_APPLY_APPLY_Pos)
#define AON_PWR_MEM_PWR_APPLY                               AON_PWR_MEM_PWR_APPLY_APPLY_Msk

#define AON_PWR_MEM_PWR_APPLY_BUSY_Pos                      (16U)
#define AON_PWR_MEM_PWR_APPLY_BUSY_Len                      (1U)
#define AON_PWR_MEM_PWR_APPLY_BUSY_Msk                      (0x1UL << AON_PWR_MEM_PWR_APPLY_BUSY_Pos)
#define AON_PWR_MEM_PWR_APPLY_BUSY                          AON_PWR_MEM_PWR_APPLY_BUSY_Msk

/*******************  Bit definition for AON_PWR_MEM_PWR_STAT0 register  *******************/
#define AON_PWR_MEM_PWR_STAT0_SET00_Pos                     (0U)
#define AON_PWR_MEM_PWR_STAT0_SET00_Len                     (2U)
#define AON_PWR_MEM_PWR_STAT0_SET00_Msk                     (0x3UL << AON_PWR_MEM_PWR_STAT0_SET00_Pos)
#define AON_PWR_MEM_PWR_STAT0_SET00                         AON_PWR_MEM_PWR_STAT0_SET00_Msk

#define AON_PWR_MEM_PWR_STAT0_SET01_Pos                     (2U)
#define AON_PWR_MEM_PWR_STAT0_SET01_Len                     (2U)
#define AON_PWR_MEM_PWR_STAT0_SET01_Msk                     (0x3UL << AON_PWR_MEM_PWR_STAT0_SET01_Pos)
#define AON_PWR_MEM_PWR_STAT0_SET01                         AON_PWR_MEM_PWR_STAT0_SET01_Msk

#define AON_PWR_MEM_PWR_STAT0_SET02_Pos                     (4U)
#define AON_PWR_MEM_PWR_STAT0_SET02_Len                     (2U)
#define AON_PWR_MEM_PWR_STAT0_SET02_Msk                     (0x3UL << AON_PWR_MEM_PWR_STAT0_SET02_Pos)
#define AON_PWR_MEM_PWR_STAT0_SET02                         AON_PWR_MEM_PWR_STAT0_SET02_Msk

#define AON_PWR_MEM_PWR_STAT0_SET03_Pos                     (6U)
#define AON_PWR_MEM_PWR_STAT0_SET03_Len                     (2U)
#define AON_PWR_MEM_PWR_STAT0_SET03_Msk                     (0x3UL << AON_PWR_MEM_PWR_STAT0_SET03_Pos)
#define AON_PWR_MEM_PWR_STAT0_SET03                         AON_PWR_MEM_PWR_STAT0_SET03_Msk

#define AON_PWR_MEM_PWR_STAT0_SET04_Pos                     (8U)
#define AON_PWR_MEM_PWR_STAT0_SET04_Len                     (2U)
#define AON_PWR_MEM_PWR_STAT0_SET04_Msk                     (0x3UL << AON_PWR_MEM_PWR_STAT0_SET04_Pos)
#define AON_PWR_MEM_PWR_STAT0_SET04                         AON_PWR_MEM_PWR_STAT0_SET04_Msk

/*******************  Bit definition for AON_PWR_MEM_PWR_STAT1 register  *******************/
#define AON_PWR_MEM_PWR_STAT1_HTM_DM_SET_Pos                (2U)
#define AON_PWR_MEM_PWR_STAT1_HTM_DM_SET_Len                (2U)
#define AON_PWR_MEM_PWR_STAT1_HTM_DM_SET_Msk                (0x3UL << AON_PWR_MEM_PWR_STAT1_HTM_DM_SET_Pos)
#define AON_PWR_MEM_PWR_STAT1_HTM_DM_SET                    AON_PWR_MEM_PWR_STAT1_HTM_DM_SET_Msk

#define AON_PWR_MEM_PWR_STAT1_ICACHE_SET_Pos                (4U)
#define AON_PWR_MEM_PWR_STAT1_ICACHE_SET_Len                (2U)
#define AON_PWR_MEM_PWR_STAT1_ICACHE_SET_Msk                (0x3UL << AON_PWR_MEM_PWR_STAT1_ICACHE_SET_Pos)
#define AON_PWR_MEM_PWR_STAT1_ICACHE_SET                    AON_PWR_MEM_PWR_STAT1_ICACHE_SET_Msk

/*******************  Bit definition for MEM_PWR_DBG register  *******************/
#define AON_PWR_MEM_PWR_DBG_RESET_ON_SRAM_Pos               (0U)
#define AON_PWR_MEM_PWR_DBG_RESET_ON_SRAM_Len               (1U)
#define AON_PWR_MEM_PWR_DBG_RESET_ON_SRAM_Msk               (0x1UL << AON_PWR_MEM_PWR_DBG_RESET_ON_SRAM_Pos)
#define AON_PWR_MEM_PWR_DBG_RESET_ON_SRAM                   AON_PWR_MEM_PWR_DBG_RESET_ON_SRAM_Msk

/*******************  Bit definition for AON_PWR_COMM_CORE_PWR_CTRL_SW register  *******************/
#define AON_PWR_COMM_CORE_PWR_CTRL_SW_CORE_EN_Pos           (0U)
#define AON_PWR_COMM_CORE_PWR_CTRL_SW_CORE_EN_Len           (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_SW_CORE_EN_Msk           (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_SW_CORE_EN_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_SW_CORE_EN               AON_PWR_COMM_CORE_PWR_CTRL_SW_CORE_EN_Msk

#define AON_PWR_COMM_CORE_PWR_CTRL_SW_ISO_EN_Pos            (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_SW_ISO_EN_Len            (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_SW_ISO_EN_Msk            (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_SW_ISO_EN_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_SW_ISO_EN                AON_PWR_COMM_CORE_PWR_CTRL_SW_ISO_EN_Msk

#define AON_PWR_COMM_CORE_PWR_CTRL_SW_RST_N_Pos             (2U)
#define AON_PWR_COMM_CORE_PWR_CTRL_SW_RST_N_Len             (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_SW_RST_N_Msk             (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_SW_RST_N_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_SW_RST_N                 AON_PWR_COMM_CORE_PWR_CTRL_SW_RST_N_Msk


/*******************  Bit definition for AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG register  *******************/
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_CTRL_SEL_Pos      (0U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_CTRL_SEL_Len      (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_CTRL_SEL_Msk      (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_CTRL_SEL_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_CTRL_SEL          AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_CTRL_SEL_Msk

#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_HW_EN_Pos         (8U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_HW_EN_Len         (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_HW_EN_Msk         (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_HW_EN_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_HW_EN             AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_HW_EN_Msk

#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_AUTO_EN_Pos       (9U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_AUTO_EN_Len       (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_AUTO_EN_Msk       (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_AUTO_EN_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_AUTO_EN           AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_AUTO_EN_Msk

#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_PD_HOLD_EN_Pos    (10U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_PD_HOLD_EN_Len    (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_PD_HOLD_EN_Msk    (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_PD_HOLD_EN_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_PD_HOLD_EN        AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_PD_HOLD_EN_Msk

#define AON_PWR_COMM_CORE_PWR_CTRL_PLL_AUTO_ON_Pos          (11U)
#define AON_PWR_COMM_CORE_PWR_CTRL_PLL_AUTO_ON_Len          (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_PLL_AUTO_ON_Msk          (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_PLL_AUTO_ON_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_PLL_AUTO_ON              AON_PWR_COMM_CORE_PWR_CTRL_PLL_AUTO_ON_Msk

#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_HW_EN_RD_Pos      (16U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_HW_EN_RD_Len      (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_HW_EN_RD_Msk      (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_HW_EN_RD_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_HW_EN_RD          AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_HW_EN_RD_Msk

#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_AUTO_EN_RD_Pos    (17U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_AUTO_EN_RD_Len    (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_AUTO_EN_RD_Msk    (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_AUTO_EN_RD_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_AUTO_EN_RD        AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_AUTO_EN_RD_Msk

#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_PD_HOLD_EN_RD_Pos (18U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_PD_HOLD_EN_RD_Len (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_PD_HOLD_EN_RD_Msk (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_PD_HOLD_EN_RD_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_PD_HOLD_EN_RD     AON_PWR_COMM_CORE_PWR_CTRL_HW_CFG_PD_HOLD_EN_RD_Msk

/*******************  Bit definition for AON_PWR_COMM_CORE_PWR_CTRL_HW_CTRL register  *******************/
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CTRL_REQ_Pos          (0U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CTRL_REQ_Len          (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CTRL_REQ_Msk          (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_HW_CTRL_REQ_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CTRL_REQ              AON_PWR_COMM_CORE_PWR_CTRL_HW_CTRL_REQ_Msk

#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CTRL_DIS_Pos          (8U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CTRL_DIS_Len          (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CTRL_DIS_Msk          (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_HW_CTRL_DIS_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_CTRL_DIS              AON_PWR_COMM_CORE_PWR_CTRL_HW_CTRL_DIS_Msk

/*******************  Bit definition for AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT register  *******************/
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_BUSY_Pos         (0U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_BUSY_Len         (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_BUSY_Msk         (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_BUSY_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_BUSY             AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_BUSY_Msk

#define AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_HW_PWR_Pos       (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_HW_PWR_Len       (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_HW_PWR_Msk       (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_HW_PWR_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_HW_PWR           AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_HW_PWR_Msk

#define AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_HW_PD_WAIT_Pos   (2U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_HW_PD_WAIT_Len   (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_HW_PD_WAIT_Msk   (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_HW_PD_WAIT_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_HW_PD_WAIT       AON_PWR_COMM_CORE_PWR_CTRL_HW_STAT_HW_PD_WAIT_Msk

/*******************  Bit definition for AON_PWR_COMM_CORE_PWR_CTRL_HW_PD_DLY register  *******************/
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_PD_DLY_Pos            (0U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_PD_DLY_Len            (8U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_PD_DLY_Msk            (0xFFUL << AON_PWR_COMM_CORE_PWR_CTRL_HW_PD_DLY_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_PD_DLY                AON_PWR_COMM_CORE_PWR_CTRL_HW_PD_DLY_Msk

#define AON_PWR_COMM_CORE_PWR_CTRL_HW_PD_FLAG_Pos           (16U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_PD_FLAG_Len           (1U)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_PD_FLAG_Msk           (0x1UL << AON_PWR_COMM_CORE_PWR_CTRL_HW_PD_FLAG_Pos)
#define AON_PWR_COMM_CORE_PWR_CTRL_HW_PD_FLAG               AON_PWR_COMM_CORE_PWR_CTRL_HW_PD_FLAG_Msk

/*******************  Bit definition for AON_PWR_COMM_CORE_PWR_STAT register  *******************/
#define AON_PWR_COMM_CORE_PWR_STAT_CORE_EN_RD_Pos           (0U)
#define AON_PWR_COMM_CORE_PWR_STAT_CORE_EN_RD_Len           (1U)
#define AON_PWR_COMM_CORE_PWR_STAT_CORE_EN_RD_Msk           (0x1UL << AON_PWR_COMM_CORE_PWR_STAT_CORE_EN_RD_Pos)
#define AON_PWR_COMM_CORE_PWR_STAT_CORE_EN_RD               AON_PWR_COMM_CORE_PWR_STAT_CORE_EN_RD_Msk

#define AON_PWR_COMM_CORE_PWR_STAT_ISO_EN_RD_Pos            (1U)
#define AON_PWR_COMM_CORE_PWR_STAT_ISO_EN_RD_Len            (1U)
#define AON_PWR_COMM_CORE_PWR_STAT_ISO_EN_RD_Msk            (0x1UL << AON_PWR_COMM_CORE_PWR_STAT_ISO_EN_RD_Pos)
#define AON_PWR_COMM_CORE_PWR_STAT_ISO_EN_RD                AON_PWR_COMM_CORE_PWR_STAT_ISO_EN_RD_Msk

#define AON_PWR_COMM_CORE_PWR_STAT_RST_N_RD_Pos             (2U)
#define AON_PWR_COMM_CORE_PWR_STAT_RST_N_RD_Len             (1U)
#define AON_PWR_COMM_CORE_PWR_STAT_RST_N_RD_Msk             (0x1UL << AON_PWR_COMM_CORE_PWR_STAT_RST_N_RD_Pos)
#define AON_PWR_COMM_CORE_PWR_STAT_RST_N_RD                 AON_PWR_COMM_CORE_PWR_STAT_RST_N_RD_Msk

/*******************  Bit definition for AON_PWR_COMM_TIMER_PWR_CTRL register  *******************/
#define AON_PWR_COMM_TIMER_PWR_CTRL_EN_Pos                  (0U)
#define AON_PWR_COMM_TIMER_PWR_CTRL_EN_Len                  (1U)
#define AON_PWR_COMM_TIMER_PWR_CTRL_EN_Msk                  (0x1UL << AON_PWR_COMM_TIMER_PWR_CTRL_EN_Pos)
#define AON_PWR_COMM_TIMER_PWR_CTRL_EN                      AON_PWR_COMM_TIMER_PWR_CTRL_EN_Msk

#define AON_PWR_COMM_TIMER_PWR_CTRL_ISO_EN_Pos              (1U)
#define AON_PWR_COMM_TIMER_PWR_CTRL_ISO_EN_Len              (1U)
#define AON_PWR_COMM_TIMER_PWR_CTRL_ISO_EN_Msk              (0x1UL << AON_PWR_COMM_TIMER_PWR_CTRL_ISO_EN_Pos)
#define AON_PWR_COMM_TIMER_PWR_CTRL_ISO_EN                  AON_PWR_COMM_TIMER_PWR_CTRL_ISO_EN_Msk

#define AON_PWR_COMM_TIMER_PWR_CTRL_RST_N_Pos               (2U)
#define AON_PWR_COMM_TIMER_PWR_CTRL_RST_N_Len               (1U)
#define AON_PWR_COMM_TIMER_PWR_CTRL_RST_N_Msk               (0x1UL << AON_PWR_COMM_TIMER_PWR_CTRL_RST_N_Pos)
#define AON_PWR_COMM_TIMER_PWR_CTRL_RST_N                   AON_PWR_COMM_TIMER_PWR_CTRL_RST_N_Msk

/*******************  Bit definition for AON_PWR_COMM_TIMER_PWR_CTRL register  *******************/
#define AON_PWR_COMM_SOFTWARE_REG3_Pos                      (0U)
#define AON_PWR_COMM_SOFTWARE_REG3_Len                      (32U)
#define AON_PWR_COMM_SOFTWARE_REG3_Msk                      (0xFFFFFFFFUL << AON_PWR_COMM_SOFTWARE_REG3_Pos)
#define AON_PWR_COMM_SOFTWARE_REG3                          AON_PWR_COMM_SOFTWARE_REG3_Msk


/* ================================================================================================================= */
/* ================                                        AON_WDT                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for AON_WDT_CFG0 register  *******************/
#define AON_WDT_CFG0_EN_Pos                                 (0U)
#define AON_WDT_CFG0_EN_Len                                 (1U)
#define AON_WDT_CFG0_EN_Msk                                 (0x1UL << AON_WDT_CFG0_EN_Pos)
#define AON_WDT_CFG0_EN                                     AON_WDT_CFG0_EN_Msk

#define AON_WDT_CFG0_TIMER_SET_Pos                          (1U)
#define AON_WDT_CFG0_TIMER_SET_Len                          (1U)
#define AON_WDT_CFG0_TIMER_SET_Msk                          (0x1UL << AON_WDT_CFG0_TIMER_SET_Pos)
#define AON_WDT_CFG0_TIMER_SET                              AON_WDT_CFG0_TIMER_SET_Msk

#define AON_WDT_CFG0_ALARM_EN_Pos                           (2U)
#define AON_WDT_CFG0_ALARM_EN_Len                           (1U)
#define AON_WDT_CFG0_ALARM_EN_Msk                           (0x1UL << AON_WDT_CFG0_ALARM_EN_Pos)
#define AON_WDT_CFG0_ALARM_EN                               AON_WDT_CFG0_ALARM_EN_Msk

#define AON_WDT_CFG0_ALARM_SET_Pos                          (3U)
#define AON_WDT_CFG0_ALARM_SET_Len                          (1U)
#define AON_WDT_CFG0_ALARM_SET_Msk                          (0x1UL << AON_WDT_CFG0_ALARM_SET_Pos)
#define AON_WDT_CFG0_ALARM_SET                              AON_WDT_CFG0_ALARM_SET_Msk

#define AON_WDT_CFG0_CFG_Pos                                (24U)
#define AON_WDT_CFG0_CFG_Len                                (1U)
#define AON_WDT_CFG0_CFG_Msk                                (0x1UL << AON_WDT_CFG0_CFG_Pos)
#define AON_WDT_CFG0_CFG                                    AON_WDT_CFG0_CFG_Msk


/*******************  Bit definition for AON_WDT_LOCK register  *******************/
#define AON_WDT_LOCK_STAT_Pos                               (0U)
#define AON_WDT_LOCK_STAT_Len                               (1U)
#define AON_WDT_LOCK_STAT_Msk                               (0x1UL << AON_WDT_LOCK_STAT_Pos)
#define AON_WDT_LOCK_STAT                                   AON_WDT_LOCK_STAT_Msk

#define AON_WDT_LOCK_LOCK_SET_Pos                           (1U)
#define AON_WDT_LOCK_LOCK_SET_Len                           (31U)
#define AON_WDT_LOCK_LOCK_SET_Msk                           (0x7FFFFFFFUL << AON_WDT_LOCK_LOCK_SET_Pos)
#define AON_WDT_LOCK_LOCK_SET                               AON_WDT_LOCK_LOCK_SET_Msk


/*******************  Bit definition for AON_WDT_STAT register  *******************/
#define AON_WDT_STAT_STAT_Pos                               (0U)
#define AON_WDT_STAT_STAT_Len                               (1U)
#define AON_WDT_STAT_STAT_Msk                               (0x1UL << AON_WDT_STAT_STAT_Pos)
#define AON_WDT_STAT_STAT                                   AON_WDT_STAT_STAT_Msk

#define AON_WDT_STAT_BUSY_Pos                               (1U)
#define AON_WDT_STAT_BUSY_Len                               (1U)
#define AON_WDT_STAT_BUSY_Msk                               (0x1UL << AON_WDT_STAT_BUSY_Pos)
#define AON_WDT_STAT_BUSY                                   AON_WDT_STAT_BUSY_Msk


/*******************  Bit definition for AON_WDT_CLK register  *******************/
#define AON_WDT_CLK_SEL_Pos                                 (0U)
#define AON_WDT_CLK_SEL_Len                                 (2U)
#define AON_WDT_CLK_SEL_Msk                                 (0x3UL << AON_WDT_CLK_SEL_Pos)
#define AON_WDT_CLK_SEL                                     AON_WDT_CLK_SEL_Msk


/*******************  Bit definition for AON_WDT_TIMER_W register  *******************/
#define AON_WDT_TIMER_W_VAL_Pos                             (0U)
#define AON_WDT_TIMER_W_VAL_Len                             (32U)
#define AON_WDT_TIMER_W_VAL_Msk                             (0xFFFFFFFFUL << AON_WDT_TIMER_W_VAL_Pos)
#define AON_WDT_TIMER_W_VAL                                 AON_WDT_TIMER_W_VAL_Msk


/*******************  Bit definition for AON_WDT_ALARM_W register  *******************/
#define AON_WDT_ALARM_W_VAL_Pos                             (0U)
#define AON_WDT_ALARM_W_VAL_Len                             (16U)
#define AON_WDT_ALARM_W_VAL_Msk                             (0xFFFFUL << AON_WDT_ALARM_W_VAL_Pos)
#define AON_WDT_ALARM_W_VAL                                 AON_WDT_ALARM_W_VAL_Msk


/*******************  Bit definition for AON_WDT_TIMER_R register  *******************/
#define AON_WDT_TIMER_R_VAL_Pos                             (0U)
#define AON_WDT_TIMER_R_VAL_Len                             (32U)
#define AON_WDT_TIMER_R_VAL_Msk                             (0xFFFFFFFFUL << AON_WDT_TIMER_R_VAL_Pos)
#define AON_WDT_TIMER_R_VAL                                 AON_WDT_TIMER_R_VAL_Msk


/*******************  Bit definition for AON_WDT_ALARM_R register  *******************/
#define AON_WDT_ALARM_R_VAL_Pos                             (0U)
#define AON_WDT_ALARM_R_VAL_Len                             (16U)
#define AON_WDT_ALARM_R_VAL_Msk                             (0xFFFFUL << AON_WDT_ALARM_R_VAL_Pos)
#define AON_WDT_ALARM_R_VAL                                 AON_WDT_ALARM_R_VAL_Msk


/* ================================================================================================================= */
/* ================                                        AON_RF                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for AON_RF_RF5 register  *******************/
#define AON_RF_RF5_SIG_SEL_Pos                              (0U)
#define AON_RF_RF5_SIG_SEL_Len                              (3U)
#define AON_RF_RF5_SIG_SEL_Msk                              (0x7UL << AON_RF_RF5_SIG_SEL_Pos)
#define AON_RF_RF5_SIG_SEL                                  AON_RF_RF5_SIG_SEL_Msk

#define AON_RF_RF5_BLK_SEL_Pos                              (4U)
#define AON_RF_RF5_BLK_SEL_Len                              (3U)
#define AON_RF_RF5_BLK_SEL_Msk                              (0x7UL << AON_RF_RF5_BLK_SEL_Pos)
#define AON_RF_RF5_BLK_SEL                                  AON_RF_RF5_BLK_SEL_Msk

#define AON_RF_RF5_TEST_MUX_EN_Pos                          (7U)
#define AON_RF_RF5_TEST_MUX_EN_Len                          (1U)
#define AON_RF_RF5_TEST_MUX_EN_Msk                          (0x1UL << AON_RF_RF5_TEST_MUX_EN_Pos)
#define AON_RF_RF5_TEST_MUX_EN                              AON_RF_RF5_TEST_MUX_EN_Msk

#define AON_RF_RF5_ADC_MUX_EN_Pos                           (16U)
#define AON_RF_RF5_ADC_MUX_EN_Len                           (1U)
#define AON_RF_RF5_ADC_MUX_EN_Msk                           (0x1UL << AON_RF_RF5_ADC_MUX_EN_Pos)
#define AON_RF_RF5_ADC_MUX_EN                               AON_RF_RF5_ADC_MUX_EN_Msk

#define AON_RF_RF5_ADX_MUX_EN_Pos                           (21U)
#define AON_RF_RF5_ADX_MUX_EN_Len                           (1U)
#define AON_RF_RF5_ADX_MUX_EN_Msk                           (0x1UL << AON_RF_RF5_ADX_MUX_EN_Pos)
#define AON_RF_RF5_ADX_MUX_EN                               AON_RF_RF5_ADX_MUX_EN_Msk

#define AON_RF_RF5_IN_SEL_ADC_Pos                           (22U)
#define AON_RF_RF5_IN_SEL_ADC_Len                           (1U)
#define AON_RF_RF5_IN_SEL_ADC_Msk                           (0x1UL << AON_RF_RF5_IN_SEL_ADC_Pos)
#define AON_RF_RF5_IN_SEL_ADC                               AON_RF_RF5_IN_SEL_ADC_Msk

#define AON_RF_RF5_TEST_MUX_ADC_SEL_2MHZ_Pos                (23U)
#define AON_RF_RF5_TEST_MUX_ADC_SEL_2MHZ_Len                (1U)
#define AON_RF_RF5_TEST_MUX_ADC_SEL_2MHZ_Msk                (0x1UL << AON_RF_RF5_TEST_MUX_ADC_SEL_2MHZ_Pos)
#define AON_RF_RF5_TEST_MUX_ADC_SEL_2MHZ                    AON_RF_RF5_TEST_MUX_ADC_SEL_2MHZ_Msk


/*******************  Bit definition for AON_RF_RF6 register  *******************/
#define AON_RF_RF6_CPLL_DOUBLER_SEL_Pos                     (0U)
#define AON_RF_RF6_CPLL_DOUBLER_SEL_Len                     (1U)
#define AON_RF_RF6_CPLL_DOUBLER_SEL_Msk                     (0x1UL << AON_RF_RF6_CPLL_DOUBLER_SEL_Pos)
#define AON_RF_RF6_CPLL_DOUBLER_SEL                         AON_RF_RF6_CPLL_DOUBLER_SEL_Msk

#define AON_RF_RF6_CPLL_CP_EN_Pos                           (1U)
#define AON_RF_RF6_CPLL_CP_EN_Len                           (1U)
#define AON_RF_RF6_CPLL_CP_EN_Msk                           (0x1UL << AON_RF_RF6_CPLL_CP_EN_Pos)
#define AON_RF_RF6_CPLL_CP_EN                               AON_RF_RF6_CPLL_CP_EN_Msk

#define AON_RF_RF6_CPLL_VCO_EN_Pos                          (2U)
#define AON_RF_RF6_CPLL_VCO_EN_Len                          (1U)
#define AON_RF_RF6_CPLL_VCO_EN_Msk                          (0x1UL << AON_RF_RF6_CPLL_VCO_EN_Pos)
#define AON_RF_RF6_CPLL_VCO_EN                              AON_RF_RF6_CPLL_VCO_EN_Msk

#define AON_RF_RF6_CPLL_FREQ_EN_Pos                         (3U)
#define AON_RF_RF6_CPLL_FREQ_EN_Len                         (1U)
#define AON_RF_RF6_CPLL_FREQ_EN_Msk                         (0x1UL << AON_RF_RF6_CPLL_FREQ_EN_Pos)
#define AON_RF_RF6_CPLL_FREQ_EN                             AON_RF_RF6_CPLL_FREQ_EN_Msk

#define AON_RF_RF6_CPLL_IBIAS_CP_SEL_Pos                    (4U)
#define AON_RF_RF6_CPLL_IBIAS_CP_SEL_Len                    (1U)
#define AON_RF_RF6_CPLL_IBIAS_CP_SEL_Msk                    (0x1UL << AON_RF_RF6_CPLL_IBIAS_CP_SEL_Pos)
#define AON_RF_RF6_CPLL_IBIAS_CP_SEL                        AON_RF_RF6_CPLL_IBIAS_CP_SEL_Msk

#define AON_RF_RF6_CPLL_IBIAS_VCO_SEL_Pos                   (5U)
#define AON_RF_RF6_CPLL_IBIAS_VCO_SEL_Len                   (1U)
#define AON_RF_RF6_CPLL_IBIAS_VCO_SEL_Msk                   (0x1UL << AON_RF_RF6_CPLL_IBIAS_VCO_SEL_Pos)
#define AON_RF_RF6_CPLL_IBIAS_VCO_SEL                       AON_RF_RF6_CPLL_IBIAS_VCO_SEL_Msk

#define AON_RF_RF6_CPLL_FREQ_DDC_Pos                        (6U)
#define AON_RF_RF6_CPLL_FREQ_DDC_Len                        (2U)
#define AON_RF_RF6_CPLL_FREQ_DDC_Msk                        (0x3UL << AON_RF_RF6_CPLL_FREQ_DDC_Pos)
#define AON_RF_RF6_CPLL_FREQ_DDC                            AON_RF_RF6_CPLL_FREQ_DDC_Msk

#define AON_RF_RF6_CPLL_FILTER_R_CTRL_Pos                   (8U)
#define AON_RF_RF6_CPLL_FILTER_R_CTRL_Len                   (5U)
#define AON_RF_RF6_CPLL_FILTER_R_CTRL_Msk                   (0x1FUL << AON_RF_RF6_CPLL_FILTER_R_CTRL_Pos)
#define AON_RF_RF6_CPLL_FILTER_R_CTRL                       AON_RF_RF6_CPLL_FILTER_R_CTRL_Msk

#define AON_RF_RF6_CPLL_FILTER_C_CTRL_Pos                   (13U)
#define AON_RF_RF6_CPLL_FILTER_C_CTRL_Len                   (5U)
#define AON_RF_RF6_CPLL_FILTER_C_CTRL_Msk                   (0x1FUL << AON_RF_RF6_CPLL_FILTER_C_CTRL_Pos)
#define AON_RF_RF6_CPLL_FILTER_C_CTRL                       AON_RF_RF6_CPLL_FILTER_C_CTRL_Msk

#define AON_RF_RF6_CPLL_FILTER_C2_CTRL_Pos                  (18U)
#define AON_RF_RF6_CPLL_FILTER_C2_CTRL_Len                  (5U)
#define AON_RF_RF6_CPLL_FILTER_C2_CTRL_Msk                  (0x1FUL << AON_RF_RF6_CPLL_FILTER_C2_CTRL_Pos)
#define AON_RF_RF6_CPLL_FILTER_C2_CTRL                      AON_RF_RF6_CPLL_FILTER_C2_CTRL_Msk

#define AON_RF_RF6_CPLL_FILTER_C3_CTRL_Pos                  (23U)
#define AON_RF_RF6_CPLL_FILTER_C3_CTRL_Len                  (5U)
#define AON_RF_RF6_CPLL_FILTER_C3_CTRL_Msk                  (0x1FUL << AON_RF_RF6_CPLL_FILTER_C3_CTRL_Pos)
#define AON_RF_RF6_CPLL_FILTER_C3_CTRL                      AON_RF_RF6_CPLL_FILTER_C3_CTRL_Msk

#define AON_RF_RF6_CPLL_M_DIV_CTRL_Pos                      (28U)
#define AON_RF_RF6_CPLL_M_DIV_CTRL_Len                      (2U)
#define AON_RF_RF6_CPLL_M_DIV_CTRL_Msk                      (0x3UL << AON_RF_RF6_CPLL_M_DIV_CTRL_Pos)
#define AON_RF_RF6_CPLL_M_DIV_CTRL                          AON_RF_RF6_CPLL_M_DIV_CTRL_Msk

#define AON_RF_RF6_PLL_LOCK_DET_EN_Pos                      (31U)
#define AON_RF_RF6_PLL_LOCK_DET_EN_Len                      (1U)
#define AON_RF_RF6_PLL_LOCK_DET_EN_Msk                      (0x1UL << AON_RF_RF6_PLL_LOCK_DET_EN_Pos)
#define AON_RF_RF6_PLL_LOCK_DET_EN                          AON_RF_RF6_PLL_LOCK_DET_EN_Msk


/*******************  Bit definition for AON_RF_RF7 register  *******************/
#define AON_RF_RF7_CPLL_M_FB_DIV_CTRL_Pos                   (0U)
#define AON_RF_RF7_CPLL_M_FB_DIV_CTRL_Len                   (6U)
#define AON_RF_RF7_CPLL_M_FB_DIV_CTRL_Msk                   (0x3FUL << AON_RF_RF7_CPLL_M_FB_DIV_CTRL_Pos)
#define AON_RF_RF7_CPLL_M_FB_DIV_CTRL                       AON_RF_RF7_CPLL_M_FB_DIV_CTRL_Msk

#define AON_RF_RF7_CPLL_KVOC_CTRL_Pos                       (6U)
#define AON_RF_RF7_CPLL_KVOC_CTRL_Len                       (3U)
#define AON_RF_RF7_CPLL_KVOC_CTRL_Msk                       (0x7UL << AON_RF_RF7_CPLL_KVOC_CTRL_Pos)
#define AON_RF_RF7_CPLL_KVOC_CTRL                           AON_RF_RF7_CPLL_KVOC_CTRL_Msk

#define AON_RF_RF7_CPLL_LCP_CODE_Pos                        (9U)
#define AON_RF_RF7_CPLL_LCP_CODE_Len                        (3U)
#define AON_RF_RF7_CPLL_LCP_CODE_Msk                        (0x7UL << AON_RF_RF7_CPLL_LCP_CODE_Pos)
#define AON_RF_RF7_CPLL_LCP_CODE                            AON_RF_RF7_CPLL_LCP_CODE_Msk

#define AON_RF_RF7_CPLL_VCO_FREQ_CTRL_Pos                   (12U)
#define AON_RF_RF7_CPLL_VCO_FREQ_CTRL_Len                   (5U)
#define AON_RF_RF7_CPLL_VCO_FREQ_CTRL_Msk                   (0x1FUL << AON_RF_RF7_CPLL_VCO_FREQ_CTRL_Pos)
#define AON_RF_RF7_CPLL_VCO_FREQ_CTRL                       AON_RF_RF7_CPLL_VCO_FREQ_CTRL_Msk

#define AON_RF_RF7_CPLL_VCO_OVER_CTRL_Pos                   (17U)
#define AON_RF_RF7_CPLL_VCO_OVER_CTRL_Len                   (1U)
#define AON_RF_RF7_CPLL_VCO_OVER_CTRL_Msk                   (0x1UL << AON_RF_RF7_CPLL_VCO_OVER_CTRL_Pos)
#define AON_RF_RF7_CPLL_VCO_OVER_CTRL                       AON_RF_RF7_CPLL_VCO_OVER_CTRL_Msk

#define AON_RF_RF7_CPLL_N_IDEA_COUNT_Pos                    (18U)
#define AON_RF_RF7_CPLL_N_IDEA_COUNT_Len                    (8U)
#define AON_RF_RF7_CPLL_N_IDEA_COUNT_Msk                    (0xFFUL << AON_RF_RF7_CPLL_N_IDEA_COUNT_Pos)
#define AON_RF_RF7_CPLL_N_IDEA_COUNT                        AON_RF_RF7_CPLL_N_IDEA_COUNT_Msk

#define AON_RF_RF7_CPLL_REF_DPLL_DIV_CTRL_Pos               (26U)
#define AON_RF_RF7_CPLL_REF_DPLL_DIV_CTRL_Len               (2U)
#define AON_RF_RF7_CPLL_REF_DPLL_DIV_CTRL_Msk               (0x3UL << AON_RF_RF7_CPLL_REF_DPLL_DIV_CTRL_Pos)
#define AON_RF_RF7_CPLL_REF_DPLL_DIV_CTRL                   AON_RF_RF7_CPLL_REF_DPLL_DIV_CTRL_Msk

#define AON_RF_RF7_L_H_THRESHOLD_Pos                        (28U)
#define AON_RF_RF7_L_H_THRESHOLD_Len                        (4U)
#define AON_RF_RF7_L_H_THRESHOLD_Msk                        (0xFUL << AON_RF_RF7_L_H_THRESHOLD_Pos)
#define AON_RF_RF7_L_H_THRESHOLD                            AON_RF_RF7_L_H_THRESHOLD_Msk

/*******************  Bit definition for AON_RF_RF8 register  *******************/
#define AON_RF_RF8_XO_IBIAS_CTRL_Pos                        (0U)
#define AON_RF_RF8_XO_IBIAS_CTRL_Len                        (5U)
#define AON_RF_RF8_XO_IBIAS_CTRL_Msk                        (0x1FUL << AON_RF_RF8_XO_IBIAS_CTRL_Pos)
#define AON_RF_RF8_XO_IBIAS_CTRL                            AON_RF_RF8_XO_IBIAS_CTRL_Msk

#define AON_RF_RF8_XO_CURRENT_BOOST_Pos                     (5U)
#define AON_RF_RF8_XO_CURRENT_BOOST_Len                     (1U)
#define AON_RF_RF8_XO_CURRENT_BOOST_Msk                     (0x1UL << AON_RF_RF8_XO_CURRENT_BOOST_Pos)
#define AON_RF_RF8_XO_CURRENT_BOOST                         AON_RF_RF8_XO_CURRENT_BOOST_Msk

#define AON_RF_RF8_CK_IDO_LOAD_EN_Pos                       (6U)
#define AON_RF_RF8_CK_IDO_LOAD_EN_Len                       (1U)
#define AON_RF_RF8_CK_IDO_LOAD_EN_Msk                       (0x1UL << AON_RF_RF8_CK_IDO_LOAD_EN_Pos)
#define AON_RF_RF8_CK_IDO_LOAD_EN                           AON_RF_RF8_CK_IDO_LOAD_EN_Msk

#define AON_RF_RF8_CK_IDO_BYPASS_Pos                        (7U)
#define AON_RF_RF8_CK_IDO_BYPASS_Len                        (1U)
#define AON_RF_RF8_CK_IDO_BYPASS_Msk                        (0x1UL << AON_RF_RF8_CK_IDO_BYPASS_Pos)
#define AON_RF_RF8_CK_IDO_BYPASS                            AON_RF_RF8_CK_IDO_BYPASS_Msk

#define AON_RF_RF8_CK_IDO_XO_CTRL_Pos                       (8U)
#define AON_RF_RF8_CK_IDO_XO_CTRL_Len                       (5U)
#define AON_RF_RF8_CK_IDO_XO_CTRL_Msk                       (0x1FUL << AON_RF_RF8_CK_IDO_XO_CTRL_Pos)
#define AON_RF_RF8_CK_IDO_XO_CTRL                           AON_RF_RF8_CK_IDO_XO_CTRL_Msk

#define AON_RF_RF8_SU_EN_Pos                                (13U)
#define AON_RF_RF8_SU_EN_Len                                (1U)
#define AON_RF_RF8_SU_EN_Msk                                (0x1UL << AON_RF_RF8_SU_EN_Pos)
#define AON_RF_RF8_SU_EN                                    AON_RF_RF8_SU_EN_Msk

#define AON_RF_RF8_SU_NEG_Z_EN_Pos                          (14U)
#define AON_RF_RF8_SU_NEG_Z_EN_Len                          (1U)
#define AON_RF_RF8_SU_NEG_Z_EN_Msk                          (0x1UL << AON_RF_RF8_SU_NEG_Z_EN_Pos)
#define AON_RF_RF8_SU_NEG_Z_EN                              AON_RF_RF8_SU_NEG_Z_EN_Msk

#define AON_RF_RF8_SU_NOISE_VCO_EN_Pos                      (15U)
#define AON_RF_RF8_SU_NOISE_VCO_EN_Len                      (1U)
#define AON_RF_RF8_SU_NOISE_VCO_EN_Msk                      (0x1UL << AON_RF_RF8_SU_NOISE_VCO_EN_Pos)
#define AON_RF_RF8_SU_NOISE_VCO_EN                          AON_RF_RF8_SU_NOISE_VCO_EN_Msk

#define AON_RF_RF8_SU_GM_IBOOT_EN_Pos                       (16U)
#define AON_RF_RF8_SU_GM_IBOOT_EN_Len                       (1U)
#define AON_RF_RF8_SU_GM_IBOOT_EN_Msk                       (0x1UL << AON_RF_RF8_SU_GM_IBOOT_EN_Pos)
#define AON_RF_RF8_SU_GM_IBOOT_EN                           AON_RF_RF8_SU_GM_IBOOT_EN_Msk

#define AON_RF_RF8_SU_INJ_RAMP_CTRL_Pos                     (17U)
#define AON_RF_RF8_SU_INJ_RAMP_CTRL_Len                     (3U)
#define AON_RF_RF8_SU_INJ_RAMP_CTRL_Msk                     (0x7UL << AON_RF_RF8_SU_INJ_RAMP_CTRL_Pos)
#define AON_RF_RF8_SU_INJ_RAMP_CTRL                         AON_RF_RF8_SU_INJ_RAMP_CTRL_Msk

#define AON_RF_RF8_SU_KVCO_CTRL_Pos                         (20U)
#define AON_RF_RF8_SU_KVCO_CTRL_Len                         (4U)
#define AON_RF_RF8_SU_KVCO_CTRL_Msk                         (0xFUL << AON_RF_RF8_SU_KVCO_CTRL_Pos)
#define AON_RF_RF8_SU_KVCO_CTRL                             AON_RF_RF8_SU_KVCO_CTRL_Msk

#define AON_RF_RF8_SU_CHIRP_BUFF_Z_PROG_Pos                 (24U)
#define AON_RF_RF8_SU_CHIRP_BUFF_Z_PROG_Len                 (4U)
#define AON_RF_RF8_SU_CHIRP_BUFF_Z_PROG_Msk                 (0xFUL << AON_RF_RF8_SU_CHIRP_BUFF_Z_PROG_Pos)
#define AON_RF_RF8_SU_CHIRP_BUFF_Z_PROG                     AON_RF_RF8_SU_CHIRP_BUFF_Z_PROG_Msk

#define AON_RF_RF8_SU_RAMP_REF_CTRL_Pos                     (28U)
#define AON_RF_RF8_SU_RAMP_REF_CTRL_Len                     (4U)
#define AON_RF_RF8_SU_RAMP_REF_CTRL_Msk                     (0xFUL << AON_RF_RF8_SU_RAMP_REF_CTRL_Pos)
#define AON_RF_RF8_SU_RAMP_REF_CTRL                         AON_RF_RF8_SU_RAMP_REF_CTRL_Msk


/*******************  Bit definition for AON_RF_RF9 register  *******************/
#define AON_RF_RF9_SU_CNTR_CTRL_Pos                         (0U)
#define AON_RF_RF9_SU_CNTR_CTRL_Len                         (5U)
#define AON_RF_RF9_SU_CNTR_CTRL_Msk                         (0x1FUL << AON_RF_RF9_SU_CNTR_CTRL_Pos)
#define AON_RF_RF9_SU_CNTR_CTRL                             AON_RF_RF9_SU_CNTR_CTRL_Msk

#define AON_RF_RF9_SU_CNTR_SETTLE_CTRL_Pos                  (5U)
#define AON_RF_RF9_SU_CNTR_SETTLE_CTRL_Len                  (5U)
#define AON_RF_RF9_SU_CNTR_SETTLE_CTRL_Msk                  (0x1FUL << AON_RF_RF9_SU_CNTR_SETTLE_CTRL_Pos)
#define AON_RF_RF9_SU_CNTR_SETTLE_CTRL                      AON_RF_RF9_SU_CNTR_SETTLE_CTRL_Msk

#define AON_RF_RF9_XO_CAP_CTRL_Pos                          (10U)
#define AON_RF_RF9_XO_CAP_CTRL_Len                          (9U)
#define AON_RF_RF9_XO_CAP_CTRL_Msk                          (0x1FFUL << AON_RF_RF9_XO_CAP_CTRL_Pos)
#define AON_RF_RF9_XO_CAP_CTRL                              AON_RF_RF9_XO_CAP_CTRL_Msk

#define AON_RF_RF9_RC_CAL_OVER_Pos                          (19U)
#define AON_RF_RF9_RC_CAL_OVER_Len                          (1U)
#define AON_RF_RF9_RC_CAL_OVER_Msk                          (0x1UL << AON_RF_RF9_RC_CAL_OVER_Pos)
#define AON_RF_RF9_RC_CAL_OVER                              AON_RF_RF9_RC_CAL_OVER_Msk

#define AON_RF_RF9_RC_CAL_N_IDEAL_COUNT_Pos                 (20U)
#define AON_RF_RF9_RC_CAL_N_IDEAL_COUNT_Len                 (8U)
#define AON_RF_RF9_RC_CAL_N_IDEAL_COUNT_Msk                 (0xFFUL << AON_RF_RF9_RC_CAL_N_IDEAL_COUNT_Pos)
#define AON_RF_RF9_RC_CAL_N_IDEAL_COUNT                     AON_RF_RF9_RC_CAL_N_IDEAL_COUNT_Msk

#define AON_RF_RF9_RC_CAL_PREDIV_Pos                        (28U)
#define AON_RF_RF9_RC_CAL_PREDIV_Len                        (2U)
#define AON_RF_RF9_RC_CAL_PREDIV_Msk                        (0x3UL << AON_RF_RF9_RC_CAL_PREDIV_Pos)
#define AON_RF_RF9_RC_CAL_PREDIV                            AON_RF_RF9_RC_CAL_PREDIV_Msk

#define AON_RF_RF9_RC_CAL_RST_B_Pos                         (30U)
#define AON_RF_RF9_RC_CAL_RST_B_Len                         (1U)
#define AON_RF_RF9_RC_CAL_RST_B_Msk                         (0x1UL << AON_RF_RF9_RC_CAL_RST_B_Pos)
#define AON_RF_RF9_RC_CAL_RST_B                             AON_RF_RF9_RC_CAL_RST_B_Msk

#define AON_RF_RF9_RC_CAL_EN_Pos                            (31U)
#define AON_RF_RF9_RC_CAL_EN_Len                            (1U)
#define AON_RF_RF9_RC_CAL_EN_Msk                            (0x1UL << AON_RF_RF9_RC_CAL_EN_Pos)
#define AON_RF_RF9_RC_CAL_EN                                AON_RF_RF9_RC_CAL_EN_Msk


/*******************  Bit definition for AON_RF_RF_RD_REG_0 register  *******************/
#define AON_RF_RF_RD_REG_0_RF_ID_Pos                        (0U)
#define AON_RF_RF_RD_REG_0_RF_ID_Len                        (8U)
#define AON_RF_RF_RD_REG_0_RF_ID_Msk                        (0xFFUL << AON_RF_RF_RD_REG_0_RF_ID_Pos)
#define AON_RF_RF_RD_REG_0_RF_ID                            AON_RF_RF_RD_REG_0_RF_ID_Msk

#define AON_RF_RF_RD_REG_0_CPLL_CRSCDE_Pos                  (16U)
#define AON_RF_RF_RD_REG_0_CPLL_CRSCDE_Len                  (5U)
#define AON_RF_RF_RD_REG_0_CPLL_CRSCDE_Msk                  (0x1FUL << AON_RF_RF_RD_REG_0_CPLL_CRSCDE_Pos)
#define AON_RF_RF_RD_REG_0_CPLL_CRSCDE                      AON_RF_RF_RD_REG_0_CPLL_CRSCDE_Msk

/*******************  Bit definition for AON_RF_XO_BIAS_VALUE register  *******************/
#define AON_RF_XO_BIAS_HI_Pos                               (0U)
#define AON_RF_XO_BIAS_HI_Len                               (6U)
#define AON_RF_XO_BIAS_HI_Msk                               (0x3FUL << AON_RF_XO_BIAS_HI_Pos)
#define AON_RF_XO_BIAS_HI                                   AON_RF_XO_BIAS_HI_Msk

#define AON_RF_XO_CAP_HI_Pos                                (6U)
#define AON_RF_XO_CAP_HI_Len                                (9U)
#define AON_RF_XO_CAP_HI_Msk                                (0x1FFUL << AON_RF_XO_CAP_HI_Pos)
#define AON_RF_XO_CAP_HI                                    AON_RF_XO_CAP_HI_Msk

#define AON_RF_XO_BIAS_LO_Pos                               (16U)
#define AON_RF_XO_BIAS_LO_Len                               (6U)
#define AON_RF_XO_BIAS_LO_Msk                               (0x3FUL << AON_RF_XO_BIAS_LO_Pos)
#define AON_RF_XO_BIAS_LO                                   AON_RF_XO_BIAS_LO_Msk

#define AON_RF_XO_CAP_LO_Pos                                (22U)
#define AON_RF_XO_CAP_LO_Len                                (9U)
#define AON_RF_XO_CAP_LO_Msk                                (0x1FFUL << AON_RF_XO_CAP_LO_Pos)
#define AON_RF_XO_CAP_LO                                    AON_RF_XO_CAP_LO_Msk

/*******************  Bit definition for AON_RF_RF_INTF_OVR_EN_0 register  *******************/
#define AON_RF_RF_INTF_OVR_EN_0_XO_EN_Pos                   (0U)
#define AON_RF_RF_INTF_OVR_EN_0_XO_EN_Len                   (1U)
#define AON_RF_RF_INTF_OVR_EN_0_XO_EN_Msk                   (0x1UL << AON_RF_RF_INTF_OVR_EN_0_XO_EN_Pos)
#define AON_RF_RF_INTF_OVR_EN_0_XO_EN                       AON_RF_RF_INTF_OVR_EN_0_XO_EN_Msk

#define AON_RF_RF_INTF_OVR_EN_0_TUNE_EN_Pos                 (1U)
#define AON_RF_RF_INTF_OVR_EN_0_TUNE_EN_Len                 (1U)
#define AON_RF_RF_INTF_OVR_EN_0_TUNE_EN_Msk                 (0x1UL << AON_RF_RF_INTF_OVR_EN_0_TUNE_EN_Pos)
#define AON_RF_RF_INTF_OVR_EN_0_TUNE_EN                     AON_RF_RF_INTF_OVR_EN_0_TUNE_EN_Msk

#define AON_RF_RF_INTF_OVR_EN_0_CPLL_EN_Pos                 (2U)
#define AON_RF_RF_INTF_OVR_EN_0_CPLL_EN_Len                 (1U)
#define AON_RF_RF_INTF_OVR_EN_0_CPLL_EN_Msk                 (0x1UL << AON_RF_RF_INTF_OVR_EN_0_CPLL_EN_Pos)
#define AON_RF_RF_INTF_OVR_EN_0_CPLL_EN                     AON_RF_RF_INTF_OVR_EN_0_CPLL_EN_Msk

#define AON_RF_RF_INTF_OVR_EN_0_RST_N_Pos                   (3U)
#define AON_RF_RF_INTF_OVR_EN_0_RST_N_Len                   (1U)
#define AON_RF_RF_INTF_OVR_EN_0_RST_N_Msk                   (0x1UL << AON_RF_RF_INTF_OVR_EN_0_RST_N_Pos)
#define AON_RF_RF_INTF_OVR_EN_0_RST_N                       AON_RF_RF_INTF_OVR_EN_0_RST_N_Msk


/*******************  Bit definition for AON_RF_RF_INTF_OVR_VAL_0 register  *******************/
#define AON_RF_RF_INTF_OVR_VAL_0_XO_EN_Pos                  (0U)
#define AON_RF_RF_INTF_OVR_VAL_0_XO_EN_Len                  (1U)
#define AON_RF_RF_INTF_OVR_VAL_0_XO_EN_Msk                  (0x1UL << AON_RF_RF_INTF_OVR_VAL_0_XO_EN_Pos)
#define AON_RF_RF_INTF_OVR_VAL_0_XO_EN                      AON_RF_RF_INTF_OVR_VAL_0_XO_EN_Msk

#define AON_RF_RF_INTF_OVR_VAL_0_TUNE_EN_Pos                (1U)
#define AON_RF_RF_INTF_OVR_VAL_0_TUNE_EN_Len                (1U)
#define AON_RF_RF_INTF_OVR_VAL_0_TUNE_EN_Msk                (0x1UL << AON_RF_RF_INTF_OVR_VAL_0_TUNE_EN_Pos)
#define AON_RF_RF_INTF_OVR_VAL_0_TUNE_EN                    AON_RF_RF_INTF_OVR_VAL_0_TUNE_EN_Msk

#define AON_RF_RF_INTF_OVR_VAL_0_CPLL_EN_Pos                (2U)
#define AON_RF_RF_INTF_OVR_VAL_0_CPLL_EN_Len                (1U)
#define AON_RF_RF_INTF_OVR_VAL_0_CPLL_EN_Msk                (0x1UL << AON_RF_RF_INTF_OVR_VAL_0_CPLL_EN_Pos)
#define AON_RF_RF_INTF_OVR_VAL_0_CPLL_EN                    AON_RF_RF_INTF_OVR_VAL_0_CPLL_EN_Msk

#define AON_RF_RF_INTF_OVR_VAL_0_RST_N_Pos                  (3U)
#define AON_RF_RF_INTF_OVR_VAL_0_RST_N_Len                  (1U)
#define AON_RF_RF_INTF_OVR_VAL_0_RST_N_Msk                  (0x1UL << AON_RF_RF_INTF_OVR_VAL_0_RST_N_Pos)
#define AON_RF_RF_INTF_OVR_VAL_0_RST_N                      AON_RF_RF_INTF_OVR_VAL_0_RST_N_Msk


/*******************  Bit definition for AON_RF_RF_INTF_OVR_RD_0 register  *******************/
#define AON_RF_RF_INTF_OVR_RD_0_XO_EN_Pos                   (0U)
#define AON_RF_RF_INTF_OVR_RD_0_XO_EN_Len                   (1U)
#define AON_RF_RF_INTF_OVR_RD_0_XO_EN_Msk                   (0x1UL << AON_RF_RF_INTF_OVR_RD_0_XO_EN_Pos)
#define AON_RF_RF_INTF_OVR_RD_0_XO_EN                       AON_RF_RF_INTF_OVR_RD_0_XO_EN_Msk

#define AON_RF_RF_INTF_OVR_RD_0_TUNE_EN_Pos                 (1U)
#define AON_RF_RF_INTF_OVR_RD_0_TUNE_EN_Len                 (1U)
#define AON_RF_RF_INTF_OVR_RD_0_TUNE_EN_Msk                 (0x1UL << AON_RF_RF_INTF_OVR_RD_0_TUNE_EN_Pos)
#define AON_RF_RF_INTF_OVR_RD_0_TUNE_EN                     AON_RF_RF_INTF_OVR_RD_0_TUNE_EN_Msk

#define AON_RF_RF_INTF_OVR_RD_0_CPLL_EN_Pos                 (2U)
#define AON_RF_RF_INTF_OVR_RD_0_CPLL_EN_Len                 (1U)
#define AON_RF_RF_INTF_OVR_RD_0_CPLL_EN_Msk                 (0x1UL << AON_RF_RF_INTF_OVR_RD_0_CPLL_EN_Pos)
#define AON_RF_RF_INTF_OVR_RD_0_CPLL_EN                     AON_RF_RF_INTF_OVR_RD_0_CPLL_EN_Msk

#define AON_RF_RF_INTF_OVR_RD_0_RST_N_Pos                   (3U)
#define AON_RF_RF_INTF_OVR_RD_0_RST_N_Len                   (1U)
#define AON_RF_RF_INTF_OVR_RD_0_RST_N_Msk                   (0x1UL << AON_RF_RF_INTF_OVR_RD_0_RST_N_Pos)
#define AON_RF_RF_INTF_OVR_RD_0_RST_N                       AON_RF_RF_INTF_OVR_RD_0_RST_N_Msk

/* ================================================================================================================= */
/* ================                                        AON_IO                                   ================ */
/* ================================================================================================================= */
/*******************  Bit definition for AON_IO_AON_PAD_CTRL0 register  *******************/
#define AON_IO_AON_PAD_CTRL0_PE_POS                         (0U)
#define AON_IO_AON_PAD_CTRL0_PE_Len                         (8U)
#define AON_IO_AON_PAD_CTRL0_PE_Msk                         (0xFFUL << AON_IO_AON_PAD_CTRL0_PE_POS)
#define AON_IO_AON_PAD_CTRL0_PE                             AON_IO_AON_PAD_CTRL0_PE_Msk

#define AON_IO_AON_PAD_CTRL0_PS_POS                         (8U)
#define AON_IO_AON_PAD_CTRL0_PS_Len                         (8U)
#define AON_IO_AON_PAD_CTRL0_PS_Msk                         (0xFFUL << AON_IO_AON_PAD_CTRL0_PS_POS)
#define AON_IO_AON_PAD_CTRL0_PS                             AON_IO_AON_PAD_CTRL0_PS_Msk

#define AON_IO_AON_PAD_CTRL0_IE_POS                         (16U)
#define AON_IO_AON_PAD_CTRL0_IE_Len                         (8U)
#define AON_IO_AON_PAD_CTRL0_IE_Msk                         (0xFFUL << AON_IO_AON_PAD_CTRL0_IE_POS)
#define AON_IO_AON_PAD_CTRL0_IE                             AON_IO_AON_PAD_CTRL0_IE_Msk

/*******************  Bit definition for AON_IO_AON_PAD_CTRL1 register  *******************/
#define AON_IO_AON_PAD_CTRL1_OE_POS                         (0U)
#define AON_IO_AON_PAD_CTRL1_OE_Len                         (8U)
#define AON_IO_AON_PAD_CTRL1_OE_Msk                         (0xFFUL << AON_IO_AON_PAD_CTRL1_OE_POS)
#define AON_IO_AON_PAD_CTRL1_OE                             AON_IO_AON_PAD_CTRL1_OE_Msk

#define AON_IO_AON_PAD_CTRL1_OUT_VAL_POS                    (8U)
#define AON_IO_AON_PAD_CTRL1_OUT_VAL_Len                    (8U)
#define AON_IO_AON_PAD_CTRL1_OUT_VAL_Msk                    (0xFFUL << AON_IO_AON_PAD_CTRL1_OUT_VAL_POS)
#define AON_IO_AON_PAD_CTRL1_OUT_VAL                        AON_IO_AON_PAD_CTRL1_OUT_VAL_Msk

#define AON_IO_AON_PAD_CTRL1_IN_VAL_POS                     (16U)
#define AON_IO_AON_PAD_CTRL1_IN_VAL_Len                     (8U)
#define AON_IO_AON_PAD_CTRL1_IN_VAL_Msk                     (0xFFUL << AON_IO_AON_PAD_CTRL1_IN_VAL_POS)
#define AON_IO_AON_PAD_CTRL1_IN_VAL                         AON_IO_AON_PAD_CTRL1_IN_VAL_Msk

/*******************  Bit definition for AON_IO_AON_PAD_CTRL2 register  *******************/
#define AON_IO_AON_PAD_CTRL2_IS_POS                         (0U)
#define AON_IO_AON_PAD_CTRL2_IS_Len                         (8U)
#define AON_IO_AON_PAD_CTRL2_IS_Msk                         (0xFFUL << AON_IO_AON_PAD_CTRL2_IS_POS)
#define AON_IO_AON_PAD_CTRL2_IS                             AON_IO_AON_PAD_CTRL2_IS_Msk

#define AON_IO_AON_PAD_CTRL2_SR_POS                         (8U)
#define AON_IO_AON_PAD_CTRL2_SR_Len                         (8U)
#define AON_IO_AON_PAD_CTRL2_SR_Msk                         (0xFFUL << AON_IO_AON_PAD_CTRL2_SR_POS)
#define AON_IO_AON_PAD_CTRL2_SR                             AON_IO_AON_PAD_CTRL2_SR_Msk

#define AON_IO_AON_PAD_CTRL2_POE_POS                        (16U)
#define AON_IO_AON_PAD_CTRL2_POE_Len                        (8U)
#define AON_IO_AON_PAD_CTRL2_POE_Msk                        (0xFFUL << AON_IO_AON_PAD_CTRL1_POE_POS)
#define AON_IO_AON_PAD_CTRL2_POE_VAL                         AON_IO_AON_PAD_CTRL2_POE_Msk

/*******************  Bit definition for AON_IO_AON_PAD_CTRL3 register  *******************/
#define AON_IO_AON_PAD_CTRL3_DS0_POS                         (0U)
#define AON_IO_AON_PAD_CTRL3_DS0_Len                         (8U)
#define AON_IO_AON_PAD_CTRL3_DS0_Msk                         (0xFFUL << AON_IO_AON_PAD_CTRL3_DS0_POS)
#define AON_IO_AON_PAD_CTRL3_DS0                             AON_IO_AON_PAD_CTRL3_DS0_Msk

#define AON_IO_AON_PAD_CTRL3_DS1_POS                         (8U)
#define AON_IO_AON_PAD_CTRL3_DS1_Len                         (8U)
#define AON_IO_AON_PAD_CTRL3_DS1_Msk                         (0xFFUL << AON_IO_AON_PAD_CTRL3_DS1_POS)
#define AON_IO_AON_PAD_CTRL3_DS1                             AON_IO_AON_PAD_CTRL3_DS1_Msk

/*******************  Bit definition for AON_PAD_CLK register  *******************/
#define AON_IO_AON_PAD_CLK_AON_GPIO4_OUT_EN_Pos             (0U)
#define AON_IO_AON_PAD_CLK_AON_GPIO4_OUT_EN_Len             (1U)
#define AON_IO_AON_PAD_CLK_AON_GPIO4_OUT_EN_Msk             (0x1UL << AON_IO_AON_PAD_CLK_AON_GPIO4_OUT_EN_Pos)
#define AON_IO_AON_PAD_CLK_AON_GPIO4_OUT_EN                 AON_IO_AON_PAD_CLK_AON_GPIO4_OUT_EN_Msk

#define AON_IO_AON_PAD_CLK_AON_GPIO4_CLK_SEL_Pos            (2U)
#define AON_IO_AON_PAD_CLK_AON_GPIO4_CLK_SEL_Len            (3U)
#define AON_IO_AON_PAD_CLK_AON_GPIO4_CLK_SEL_Msk            (0x7UL << AON_IO_AON_PAD_CLK_AON_GPIO4_CLK_SEL_Pos)
#define AON_IO_AON_PAD_CLK_AON_GPIO4_CLK_SEL                AON_IO_AON_PAD_CLK_AON_GPIO4_CLK_SEL_Msk

/*******************  Bit definition for AON_IO_AON_MCU_OVR register  *******************/
#define AON_IO_AON_MCU_OVR_OVR_POS                          (16U)
#define AON_IO_AON_MCU_OVR_OVR_Len                          (8U)
#define AON_IO_AON_MCU_OVR_OVR_Msk                          (0xFFUL << AON_IO_AON_MCU_OVR_OVR_POS)
#define AON_IO_AON_MCU_OVR_OVR                              AON_IO_AON_MCU_OVR_OVR_Msk

/*******************  Bit definition for AON_IO_EXT_WAKEUP_CTRL0 register  *******************/
#define AON_IO_EXT_WAKEUP_CTRL0_SRC_EN_POS                  (0U)
#define AON_IO_EXT_WAKEUP_CTRL0_SRC_EN_Len                  (8U)
#define AON_IO_EXT_WAKEUP_CTRL0_SRC_EN_Msk                  (0xFFUL << AON_IO_EXT_WAKEUP_CTRL0_SRC_EN_POS)
#define AON_IO_EXT_WAKEUP_CTRL0_SRC_EN                      AON_IO_EXT_WAKEUP_CTRL0_SRC_EN_Msk

#define AON_IO_EXT_WAKEUP_CTRL0_INVERT_POS                  (8U)
#define AON_IO_EXT_WAKEUP_CTRL0_INVERT_Len                  (8U)
#define AON_IO_EXT_WAKEUP_CTRL0_INVERT_Msk                  (0xFFUL << AON_IO_EXT_WAKEUP_CTRL0_INVERT_POS)
#define AON_IO_EXT_WAKEUP_CTRL0_INVERT                      AON_IO_EXT_WAKEUP_CTRL0_INVERT_Msk

/*******************  Bit definition for AON_IO_EXT_WAKEUP_CTRL1 register  *******************/
#define AON_IO_EXT_WAKEUP_CTRL1_EDGE_EN_POS                 (0U)
#define AON_IO_EXT_WAKEUP_CTRL1_EDGE_EN_Len                 (8U)
#define AON_IO_EXT_WAKEUP_CTRL1_EDGE_EN_Msk                 (0xFFUL << AON_IO_EXT_WAKEUP_CTRL1_EDGE_EN_POS)
#define AON_IO_EXT_WAKEUP_CTRL1_EDGE_EN                     AON_IO_EXT_WAKEUP_CTRL1_EDGE_EN_Msk

#define AON_IO_EXT_WAKEUP_CTRL1_EDGE_TYPE_POS               (8U)
#define AON_IO_EXT_WAKEUP_CTRL1_EDGE_TYPE_Len               (8U)
#define AON_IO_EXT_WAKEUP_CTRL1_EDGE_TYPE_Msk               (0xFFUL << AON_IO_EXT_WAKEUP_CTRL1_EDGE_TYPE_POS)
#define AON_IO_EXT_WAKEUP_CTRL1_EDGE_TYPE                   AON_IO_EXT_WAKEUP_CTRL1_EDGE_TYPE_Msk

#define AON_IO_EXT_WAKEUP_CTRL1_EDGE_BOTH_POS               (16U)
#define AON_IO_EXT_WAKEUP_CTRL1_EDGE_BOTH_Len               (8U)
#define AON_IO_EXT_WAKEUP_CTRL1_EDGE_BOTH_Msk               (0xFFUL << AON_IO_EXT_WAKEUP_CTRL1_EDGE_BOTH_POS)
#define AON_IO_EXT_WAKEUP_CTRL1_EDGE_BOTH                   AON_IO_EXT_WAKEUP_CTRL1_EDGE_BOTH_Msk

/*******************  Bit definition for AON_IO_EXT_WAKEUP_STAT register  *******************/
#define AON_IO_EXT_WAKEUP_STAT_STAT_POS                     (0U)
#define AON_IO_EXT_WAKEUP_STAT_STAT_Len                     (8U)
#define AON_IO_EXT_WAKEUP_STAT_STAT_Msk                     (0xFFUL << AON_IO_EXT_WAKEUP_STAT_STAT_POS)
#define AON_IO_EXT_WAKEUP_STAT_STAT                         AON_IO_EXT_WAKEUP_STAT_STAT_Msk


/* ================================================================================================================= */
/* ================                                        AON_MEM                                  ================ */
/* ================================================================================================================= */
/*******************  Bit definition for AON_MEM_MEM_PWR_SLP0 register  *******************/
#define AON_MEM_MEM_PWR_SLP0_SETTING00_POS                  (0U)
#define AON_MEM_MEM_PWR_SLP0_SETTING00_Len                  (2U)
#define AON_MEM_MEM_PWR_SLP0_SETTING00_Msk                  (0x3UL << AON_MEM_MEM_PWR_SLP0_SETTING00_POS)
#define AON_MEM_MEM_PWR_SLP0_SETTING00                      AON_MEM_MEM_PWR_SLP0_SETTING00_Msk

#define AON_MEM_MEM_PWR_SLP0_SETTING01_POS                  (2U)
#define AON_MEM_MEM_PWR_SLP0_SETTING01_Len                  (2U)
#define AON_MEM_MEM_PWR_SLP0_SETTING01_Msk                  (0x3UL << AON_MEM_MEM_PWR_SLP0_SETTING01_POS)
#define AON_MEM_MEM_PWR_SLP0_SETTING01                      AON_MEM_MEM_PWR_SLP0_SETTING01_Msk

#define AON_MEM_MEM_PWR_SLP0_SETTING02_POS                  (4U)
#define AON_MEM_MEM_PWR_SLP0_SETTING02_Len                  (2U)
#define AON_MEM_MEM_PWR_SLP0_SETTING02_Msk                  (0x3UL << AON_MEM_MEM_PWR_SLP0_SETTING02_POS)
#define AON_MEM_MEM_PWR_SLP0_SETTING02                      AON_MEM_MEM_PWR_SLP0_SETTING02_Msk

#define AON_MEM_MEM_PWR_SLP0_SETTING03_POS                  (6U)
#define AON_MEM_MEM_PWR_SLP0_SETTING03_Len                  (2U)
#define AON_MEM_MEM_PWR_SLP0_SETTING03_Msk                  (0x3UL << AON_MEM_MEM_PWR_SLP0_SETTING03_POS)
#define AON_MEM_MEM_PWR_SLP0_SETTING03                      AON_MEM_MEM_PWR_SLP0_SETTING03_Msk

#define AON_MEM_MEM_PWR_SLP0_SETTING04_POS                  (8U)
#define AON_MEM_MEM_PWR_SLP0_SETTING04_Len                  (2U)
#define AON_MEM_MEM_PWR_SLP0_SETTING04_Msk                  (0x3UL << AON_MEM_MEM_PWR_SLP0_SETTING04_POS)
#define AON_MEM_MEM_PWR_SLP0_SETTING04                      AON_MEM_MEM_PWR_SLP0_SETTING04_Msk

#define AON_MEM_MEM_PWR_SLP0_SETTING05_POS                  (10U)
#define AON_MEM_MEM_PWR_SLP0_SETTING05_Len                  (2U)
#define AON_MEM_MEM_PWR_SLP0_SETTING05_Msk                  (0x3UL << AON_MEM_MEM_PWR_SLP0_SETTING05_POS)
#define AON_MEM_MEM_PWR_SLP0_SETTING05                      AON_MEM_MEM_PWR_SLP0_SETTING05_Msk

#define AON_MEM_MEM_PWR_SLP0_SETTING06_POS                  (12U)
#define AON_MEM_MEM_PWR_SLP0_SETTING06_Len                  (2U)
#define AON_MEM_MEM_PWR_SLP0_SETTING06_Msk                  (0x3UL << AON_MEM_MEM_PWR_SLP0_SETTING06_POS)
#define AON_MEM_MEM_PWR_SLP0_SETTING06                      AON_MEM_MEM_PWR_SLP0_SETTING06_Msk

#define AON_MEM_MEM_PWR_SLP0_SETTING07_POS                  (14U)
#define AON_MEM_MEM_PWR_SLP0_SETTING07_Len                  (2U)
#define AON_MEM_MEM_PWR_SLP0_SETTING07_Msk                  (0x3UL << AON_MEM_MEM_PWR_SLP0_SETTING07_POS)
#define AON_MEM_MEM_PWR_SLP0_SETTING07                      AON_MEM_MEM_PWR_SLP0_SETTING07_Msk

#define AON_MEM_MEM_PWR_SLP0_SETTING08_POS                  (16U)
#define AON_MEM_MEM_PWR_SLP0_SETTING08_Len                  (2U)
#define AON_MEM_MEM_PWR_SLP0_SETTING08_Msk                  (0x3UL << AON_MEM_MEM_PWR_SLP0_SETTING08_POS)
#define AON_MEM_MEM_PWR_SLP0_SETTING08                      AON_MEM_MEM_PWR_SLP0_SETTING08_Msk

#define AON_MEM_MEM_PWR_SLP0_SETTING09_POS                  (18U)
#define AON_MEM_MEM_PWR_SLP0_SETTING09_Len                  (2U)
#define AON_MEM_MEM_PWR_SLP0_SETTING09_Msk                  (0x3UL << AON_MEM_MEM_PWR_SLP0_SETTING09_POS)
#define AON_MEM_MEM_PWR_SLP0_SETTING09                      AON_MEM_MEM_PWR_SLP0_SETTING09_Msk

#define AON_MEM_MEM_PWR_SLP0_SETTING10_POS                  (20U)
#define AON_MEM_MEM_PWR_SLP0_SETTING10_Len                  (2U)
#define AON_MEM_MEM_PWR_SLP0_SETTING10_Msk                  (0x3UL << AON_MEM_MEM_PWR_SLP0_SETTING10_POS)
#define AON_MEM_MEM_PWR_SLP0_SETTING10                      AON_MEM_MEM_PWR_SLP0_SETTING10_Msk

/*******************  Bit definition for AON_MEM_MEM_PWR_SLP1 register  *******************/
#define AON_MEM_MEM_PWR_SLP1_HTM_AM_SETTING_POS             (0U)
#define AON_MEM_MEM_PWR_SLP1_HTM_AM_SETTING_Len             (2U)
#define AON_MEM_MEM_PWR_SLP1_HTM_AM_SETTING_Msk             (0x3UL << AON_MEM_MEM_PWR_SLP1_HTM_AM_SETTING_POS)
#define AON_MEM_MEM_PWR_SLP1_HTM_AM_SETTING                 AON_MEM_MEM_PWR_SLP1_HTM_AM_SETTING_Msk

#define AON_MEM_MEM_PWR_SLP1_HTM_DM_SETTING_POS             (2U)
#define AON_MEM_MEM_PWR_SLP1_HTM_DM_SETTING_Len             (2U)
#define AON_MEM_MEM_PWR_SLP1_HTM_DM_SETTING_Msk             (0x3UL << AON_MEM_MEM_PWR_SLP1_HTM_DM_SETTING_POS)
#define AON_MEM_MEM_PWR_SLP1_HTM_DM_SETTING                 AON_MEM_MEM_PWR_SLP1_HTM_DM_SETTING_Msk

#define AON_MEM_MEM_PWR_SLP1_ICACHE_SETTING_POS             (4U)
#define AON_MEM_MEM_PWR_SLP1_ICACHE_SETTING_Len             (2U)
#define AON_MEM_MEM_PWR_SLP1_ICACHE_SETTING_Msk             (0x3UL << AON_MEM_MEM_PWR_SLP1_ICACHE_SETTING_POS)
#define AON_MEM_MEM_PWR_SLP1_ICACHE_SETTING                 AON_MEM_MEM_PWR_SLP1_ICACHE_SETTING_Msk

#define AON_MEM_MEM_PWR_SLP1_PACKET_SETTING_POS             (6U)
#define AON_MEM_MEM_PWR_SLP1_PACKET_SETTING_Len             (2U)
#define AON_MEM_MEM_PWR_SLP1_PACKET_SETTING_Msk             (0x3UL << AON_MEM_MEM_PWR_SLP1_PACKET_SETTING_POS)
#define AON_MEM_MEM_PWR_SLP1_PACKET_SETTING                 AON_MEM_MEM_PWR_SLP1_PACKET_SETTING_Msk

#define AON_MEM_MEM_PWR_SLP1_KEYRAM_SETTING_POS             (8U)
#define AON_MEM_MEM_PWR_SLP1_KEYRAM_SETTING_Len             (2U)
#define AON_MEM_MEM_PWR_SLP1_KEYRAM_SETTING_Msk             (0x3UL << AON_MEM_MEM_PWR_SLP1_KEYRAM_SETTING_POS)
#define AON_MEM_MEM_PWR_SLP1_KEYRAM_SETTING                 AON_MEM_MEM_PWR_SLP1_KEYRAM_SETTING_Msk

/*******************  Bit definition for AON_MEM_MEM_PWR_WKUP0 register  *******************/
#define AON_MEM_MEM_PWR_WKUP0_SETTING00_POS                 (0U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING00_Len                 (2U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING00_Msk                 (0x3UL << AON_MEM_MEM_PWR_WKUP0_SETTING00_POS)
#define AON_MEM_MEM_PWR_WKUP0_SETTING00                     AON_MEM_MEM_PWR_WKUP0_SETTING00_Msk

#define AON_MEM_MEM_PWR_WKUP0_SETTING01_POS                 (2U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING01_Len                 (2U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING01_Msk                 (0x3UL << AON_MEM_MEM_PWR_WKUP0_SETTING01_POS)
#define AON_MEM_MEM_PWR_WKUP0_SETTING01                     AON_MEM_MEM_PWR_WKUP0_SETTING01_Msk

#define AON_MEM_MEM_PWR_WKUP0_SETTING02_POS                 (4U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING02_Len                 (2U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING02_Msk                 (0x3UL << AON_MEM_MEM_PWR_WKUP0_SETTING02_POS)
#define AON_MEM_MEM_PWR_WKUP0_SETTING02                     AON_MEM_MEM_PWR_WKUP0_SETTING02_Msk

#define AON_MEM_MEM_PWR_WKUP0_SETTING03_POS                 (6U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING03_Len                 (2U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING03_Msk                 (0x3UL << AON_MEM_MEM_PWR_WKUP0_SETTING03_POS)
#define AON_MEM_MEM_PWR_WKUP0_SETTING03                     AON_MEM_MEM_PWR_WKUP0_SETTING03_Msk

#define AON_MEM_MEM_PWR_WKUP0_SETTING04_POS                 (8U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING04_Len                 (2U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING04_Msk                 (0x3UL << AON_MEM_MEM_PWR_WKUP0_SETTING04_POS)
#define AON_MEM_MEM_PWR_WKUP0_SETTING04                     AON_MEM_MEM_PWR_WKUP0_SETTING04_Msk

#define AON_MEM_MEM_PWR_WKUP0_SETTING05_POS                 (10U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING05_Len                 (2U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING05_Msk                 (0x3UL << AON_MEM_MEM_PWR_WKUP0_SETTING05_POS)
#define AON_MEM_MEM_PWR_WKUP0_SETTING05                     AON_MEM_MEM_PWR_WKUP0_SETTING05_Msk

#define AON_MEM_MEM_PWR_WKUP0_SETTING06_POS                 (12U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING06_Len                 (2U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING06_Msk                 (0x3UL << AON_MEM_MEM_PWR_WKUP0_SETTING06_POS)
#define AON_MEM_MEM_PWR_WKUP0_SETTING06                     AON_MEM_MEM_PWR_WKUP0_SETTING06_Msk

#define AON_MEM_MEM_PWR_WKUP0_SETTING07_POS                 (14U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING07_Len                 (2U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING07_Msk                 (0x3UL << AON_MEM_MEM_PWR_WKUP0_SETTING07_POS)
#define AON_MEM_MEM_PWR_WKUP0_SETTING07                     AON_MEM_MEM_PWR_WKUP0_SETTING07_Msk

#define AON_MEM_MEM_PWR_WKUP0_SETTING08_POS                 (16U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING08_Len                 (2U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING08_Msk                 (0x3UL << AON_MEM_MEM_PWR_WKUP0_SETTING08_POS)
#define AON_MEM_MEM_PWR_WKUP0_SETTING08                     AON_MEM_MEM_PWR_WKUP0_SETTING08_Msk

#define AON_MEM_MEM_PWR_WKUP0_SETTING09_POS                 (18U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING09_Len                 (2U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING09_Msk                 (0x3UL << AON_MEM_MEM_PWR_WKUP0_SETTING09_POS)
#define AON_MEM_MEM_PWR_WKUP0_SETTING09                     AON_MEM_MEM_PWR_WKUP0_SETTING09_Msk

#define AON_MEM_MEM_PWR_WKUP0_SETTING10_POS                 (20U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING10_Len                 (2U)
#define AON_MEM_MEM_PWR_WKUP0_SETTING10_Msk                 (0x3UL << AON_MEM_MEM_PWR_WKUP0_SETTING10_POS)
#define AON_MEM_MEM_PWR_WKUP0_SETTING10                     AON_MEM_MEM_PWR_WKUP0_SETTING10_Msk

/*******************  Bit definition for AON_MEM_MEM_PWR_WKUP1 register  *******************/
#define AON_MEM_MEM_PWR_WKUP1_HTM_AM_SETTING_POS            (0U)
#define AON_MEM_MEM_PWR_WKUP1_HTM_AM_SETTING_Len            (2U)
#define AON_MEM_MEM_PWR_WKUP1_HTM_AM_SETTING_Msk            (0x3UL << AON_MEM_MEM_PWR_WKUP1_HTM_AM_SETTING_POS)
#define AON_MEM_MEM_PWR_WKUP1_HTM_AM_SETTING                AON_MEM_MEM_PWR_WKUP1_HTM_AM_SETTING_Msk

#define AON_MEM_MEM_PWR_WKUP1_HTM_DM_SETTING_POS            (2U)
#define AON_MEM_MEM_PWR_WKUP1_HTM_DM_SETTING_Len            (2U)
#define AON_MEM_MEM_PWR_WKUP1_HTM_DM_SETTING_Msk            (0x3UL << AON_MEM_MEM_PWR_WKUP1_HTM_DM_SETTING_POS)
#define AON_MEM_MEM_PWR_WKUP1_HTM_DM_SETTING                AON_MEM_MEM_PWR_WKUP1_HTM_DM_SETTING_Msk

#define AON_MEM_MEM_PWR_WKUP1_ICACHE_SETTING_POS            (4U)
#define AON_MEM_MEM_PWR_WKUP1_ICACHE_SETTING_Len            (2U)
#define AON_MEM_MEM_PWR_WKUP1_ICACHE_SETTING_Msk            (0x3UL << AON_MEM_MEM_PWR_WKUP1_ICACHE_SETTING_POS)
#define AON_MEM_MEM_PWR_WKUP1_ICACHE_SETTING                AON_MEM_MEM_PWR_WKUP1_ICACHE_SETTING_Msk

#define AON_MEM_MEM_PWR_WKUP1_PACKET_SETTING_POS            (6U)
#define AON_MEM_MEM_PWR_WKUP1_PACKET_SETTING_Len            (2U)
#define AON_MEM_MEM_PWR_WKUP1_PACKET_SETTING_Msk            (0x3UL << AON_MEM_MEM_PWR_WKUP1_PACKET_SETTING_POS)
#define AON_MEM_MEM_PWR_WKUP1_PACKET_SETTING                AON_MEM_MEM_PWR_WKUP1_PACKET_SETTING_Msk

#define AON_MEM_MEM_PWR_WKUP1_KEYRAM_SETTING_POS            (8U)
#define AON_MEM_MEM_PWR_WKUP1_KEYRAM_SETTING_Len            (2U)
#define AON_MEM_MEM_PWR_WKUP1_KEYRAM_SETTING_Msk            (0x3UL << AON_MEM_MEM_PWR_WKUP1_KEYRAM_SETTING_POS)
#define AON_MEM_MEM_PWR_WKUP1_KEYRAM_SETTING                AON_MEM_MEM_PWR_WKUP1_KEYRAM_SETTING_Msk

/*******************  Bit definition for AON_MEM_MEM_PWR_APPLY register  *******************/
#define AON_MEM_MEM_PWR_APPLY_APPLY_POS                     (0U)
#define AON_MEM_MEM_PWR_APPLY_APPLY_Len                     (1U)
#define AON_MEM_MEM_PWR_APPLY_APPLY_Msk                     (0x1UL << AON_MEM_MEM_PWR_APPLY_APPLY_POS)
#define AON_MEM_MEM_PWR_APPLY_APPLY                         AON_MEM_MEM_PWR_APPLY_APPLY_Msk

#define AON_MEM_MEM_PWR_APPLY_BUSY_POS                      (16U)
#define AON_MEM_MEM_PWR_APPLY_BUSY_Len                      (1U)
#define AON_MEM_MEM_PWR_APPLY_BUSY_Msk                      (0x1UL << AON_MEM_MEM_PWR_APPLY_BUSY_POS)
#define AON_MEM_MEM_PWR_APPLY_BUSY                          AON_MEM_MEM_PWR_APPLY_BUSY_Msk

/*******************  Bit definition for AON_MEM_MEM_PWR_STAT0 register  *******************/
#define AON_MEM_MEM_PWR_STAT0_SETTING00_POS                 (0U)
#define AON_MEM_MEM_PWR_STAT0_SETTING00_Len                 (2U)
#define AON_MEM_MEM_PWR_STAT0_SETTING00_Msk                 (0x3UL << AON_MEM_MEM_PWR_STAT0_SETTING00_POS)
#define AON_MEM_MEM_PWR_STAT0_SETTING00                     AON_MEM_MEM_PWR_STAT0_SETTING00_Msk

#define AON_MEM_MEM_PWR_STAT0_SETTING01_POS                 (2U)
#define AON_MEM_MEM_PWR_STAT0_SETTING01_Len                 (2U)
#define AON_MEM_MEM_PWR_STAT0_SETTING01_Msk                 (0x3UL << AON_MEM_MEM_PWR_STAT0_SETTING01_POS)
#define AON_MEM_MEM_PWR_STAT0_SETTING01                     AON_MEM_MEM_PWR_STAT0_SETTING01_Msk

#define AON_MEM_MEM_PWR_STAT0_SETTING02_POS                 (4U)
#define AON_MEM_MEM_PWR_STAT0_SETTING02_Len                 (2U)
#define AON_MEM_MEM_PWR_STAT0_SETTING02_Msk                 (0x3UL << AON_MEM_MEM_PWR_STAT0_SETTING02_POS)
#define AON_MEM_MEM_PWR_STAT0_SETTING02                     AON_MEM_MEM_PWR_STAT0_SETTING02_Msk

#define AON_MEM_MEM_PWR_STAT0_SETTING03_POS                 (6U)
#define AON_MEM_MEM_PWR_STAT0_SETTING03_Len                 (2U)
#define AON_MEM_MEM_PWR_STAT0_SETTING03_Msk                 (0x3UL << AON_MEM_MEM_PWR_STAT0_SETTING03_POS)
#define AON_MEM_MEM_PWR_STAT0_SETTING03                     AON_MEM_MEM_PWR_STAT0_SETTING03_Msk

#define AON_MEM_MEM_PWR_STAT0_SETTING04_POS                 (8U)
#define AON_MEM_MEM_PWR_STAT0_SETTING04_Len                 (2U)
#define AON_MEM_MEM_PWR_STAT0_SETTING04_Msk                 (0x3UL << AON_MEM_MEM_PWR_STAT0_SETTING04_POS)
#define AON_MEM_MEM_PWR_STAT0_SETTING04                     AON_MEM_MEM_PWR_STAT0_SETTING04_Msk

#define AON_MEM_MEM_PWR_STAT0_SETTING05_POS                 (10U)
#define AON_MEM_MEM_PWR_STAT0_SETTING05_Len                 (2U)
#define AON_MEM_MEM_PWR_STAT0_SETTING05_Msk                 (0x3UL << AON_MEM_MEM_PWR_STAT0_SETTING05_POS)
#define AON_MEM_MEM_PWR_STAT0_SETTING05                     AON_MEM_MEM_PWR_STAT0_SETTING05_Msk

#define AON_MEM_MEM_PWR_STAT0_SETTING06_POS                 (12U)
#define AON_MEM_MEM_PWR_STAT0_SETTING06_Len                 (2U)
#define AON_MEM_MEM_PWR_STAT0_SETTING06_Msk                 (0x3UL << AON_MEM_MEM_PWR_STAT0_SETTING06_POS)
#define AON_MEM_MEM_PWR_STAT0_SETTING06                     AON_MEM_MEM_PWR_STAT0_SETTING06_Msk

#define AON_MEM_MEM_PWR_STAT0_SETTING07_POS                 (14U)
#define AON_MEM_MEM_PWR_STAT0_SETTING07_Len                 (2U)
#define AON_MEM_MEM_PWR_STAT0_SETTING07_Msk                 (0x3UL << AON_MEM_MEM_PWR_STAT0_SETTING07_POS)
#define AON_MEM_MEM_PWR_STAT0_SETTING07                     AON_MEM_MEM_PWR_STAT0_SETTING07_Msk

#define AON_MEM_MEM_PWR_STAT0_SETTING08_POS                 (16U)
#define AON_MEM_MEM_PWR_STAT0_SETTING08_Len                 (2U)
#define AON_MEM_MEM_PWR_STAT0_SETTING08_Msk                 (0x3UL << AON_MEM_MEM_PWR_STAT0_SETTING08_POS)
#define AON_MEM_MEM_PWR_STAT0_SETTING08                     AON_MEM_MEM_PWR_STAT0_SETTING08_Msk

#define AON_MEM_MEM_PWR_STAT0_SETTING09_POS                 (18U)
#define AON_MEM_MEM_PWR_STAT0_SETTING09_Len                 (2U)
#define AON_MEM_MEM_PWR_STAT0_SETTING09_Msk                 (0x3UL << AON_MEM_MEM_PWR_STAT0_SETTING09_POS)
#define AON_MEM_MEM_PWR_STAT0_SETTING09                     AON_MEM_MEM_PWR_STAT0_SETTING09_Msk

#define AON_MEM_MEM_PWR_STAT0_SETTING10_POS                 (20U)
#define AON_MEM_MEM_PWR_STAT0_SETTING10_Len                 (2U)
#define AON_MEM_MEM_PWR_STAT0_SETTING10_Msk                 (0x3UL << AON_MEM_MEM_PWR_STAT0_SETTING10_POS)
#define AON_MEM_MEM_PWR_STAT0_SETTING10                     AON_MEM_MEM_PWR_STAT0_SETTING10_Msk

/*******************  Bit definition for AON_MEM_MEM_PWR_STAT1 register  *******************/
#define AON_MEM_MEM_PWR_STAT1_HTM_AM_SETTING_POS            (0U)
#define AON_MEM_MEM_PWR_STAT1_HTM_AM_SETTING_Len            (2U)
#define AON_MEM_MEM_PWR_STAT1_HTM_AM_SETTING_Msk            (0x3UL << AON_MEM_MEM_PWR_STAT1_HTM_AM_SETTING_POS)
#define AON_MEM_MEM_PWR_STAT1_HTM_AM_SETTING                AON_MEM_MEM_PWR_STAT1_HTM_AM_SETTING_Msk

#define AON_MEM_MEM_PWR_STAT1_HTM_DM_SETTING_POS            (2U)
#define AON_MEM_MEM_PWR_STAT1_HTM_DM_SETTING_Len            (2U)
#define AON_MEM_MEM_PWR_STAT1_HTM_DM_SETTING_Msk            (0x3UL << AON_MEM_MEM_PWR_STAT1_HTM_DM_SETTING_POS)
#define AON_MEM_MEM_PWR_STAT1_HTM_DM_SETTING                AON_MEM_MEM_PWR_STAT1_HTM_DM_SETTING_Msk

#define AON_MEM_MEM_PWR_STAT1_ICACHE_SETTING_POS            (4U)
#define AON_MEM_MEM_PWR_STAT1_ICACHE_SETTING_Len            (2U)
#define AON_MEM_MEM_PWR_STAT1_ICACHE_SETTING_Msk            (0x3UL << AON_MEM_MEM_PWR_STAT1_ICACHE_SETTING_POS)
#define AON_MEM_MEM_PWR_STAT1_ICACHE_SETTING                AON_MEM_MEM_PWR_STAT1_ICACHE_SETTING_Msk

#define AON_MEM_MEM_PWR_STAT1_PACKET_SETTING_POS            (6U)
#define AON_MEM_MEM_PWR_STAT1_PACKET_SETTING_Len            (2U)
#define AON_MEM_MEM_PWR_STAT1_PACKET_SETTING_Msk            (0x3UL << AON_MEM_MEM_PWR_STAT1_PACKET_SETTING_POS)
#define AON_MEM_MEM_PWR_STAT1_PACKET_SETTING                AON_MEM_MEM_PWR_STAT1_PACKET_SETTING_Msk

#define AON_MEM_MEM_PWR_STAT1_KEYRAM_SETTING_POS            (8U)
#define AON_MEM_MEM_PWR_STAT1_KEYRAM_SETTING_Len            (2U)
#define AON_MEM_MEM_PWR_STAT1_KEYRAM_SETTING_Msk            (0x3UL << AON_MEM_MEM_PWR_STAT1_KEYRAM_SETTING_POS)
#define AON_MEM_MEM_PWR_STAT1_KEYRAM_SETTING                AON_MEM_MEM_PWR_STAT1_KEYRAM_SETTING_Msk

/*******************  Bit definition for AON_MEM_MEM_MARGIN register  *******************/
#define AON_MEM_MEM_MARGIN_CRITICAL_RMM_POS                 (0U)
#define AON_MEM_MEM_MARGIN_CRITICAL_RMM_Len                 (1U)
#define AON_MEM_MEM_MARGIN_CRITICAL_RMM_Msk                 (0x1UL << AON_MEM_MEM_MARGIN_CRITICAL_RMM_POS)
#define AON_MEM_MEM_MARGIN_CRITICAL_RMM                     AON_MEM_MEM_MARGIN_CRITICAL_RMM_Msk

#define AON_MEM_MEM_MARGIN_CRITICAL_WMM_POS                 (1U)
#define AON_MEM_MEM_MARGIN_CRITICAL_WMM_Len                 (1U)
#define AON_MEM_MEM_MARGIN_CRITICAL_WMM_Msk                 (0x1UL << AON_MEM_MEM_MARGIN_CRITICAL_WMM_POS)
#define AON_MEM_MEM_MARGIN_CRITICAL_WMM                     AON_MEM_MEM_MARGIN_CRITICAL_WMM_Msk

#define AON_MEM_MEM_MARGIN_CRITICAL_CMM_POS                 (2U)
#define AON_MEM_MEM_MARGIN_CRITICAL_CMM_Len                 (2U)
#define AON_MEM_MEM_MARGIN_CRITICAL_CMM_Msk                 (0x3UL << AON_MEM_MEM_MARGIN_CRITICAL_CMM_POS)
#define AON_MEM_MEM_MARGIN_CRITICAL_CMM                     AON_MEM_MEM_MARGIN_CRITICAL_CMM_Msk

#define AON_MEM_MEM_MARGIN_NON_CRITICAL_RMM_POS             (4U)
#define AON_MEM_MEM_MARGIN_NON_CRITICAL_RMM_Len             (1U)
#define AON_MEM_MEM_MARGIN_NON_CRITICAL_RMM_Msk             (0x1UL << AON_MEM_MEM_MARGIN_NON_CRITICAL_RMM_POS)
#define AON_MEM_MEM_MARGIN_NON_CRITICAL_RMM                 AON_MEM_MEM_MARGIN_NON_CRITICAL_RMM_Msk

#define AON_MEM_MEM_MARGIN_NON_CRITICAL_WMM_POS             (5U)
#define AON_MEM_MEM_MARGIN_NON_CRITICAL_WMM_Len             (1U)
#define AON_MEM_MEM_MARGIN_NON_CRITICAL_WMM_Msk             (0x1UL << AON_MEM_MEM_MARGIN_NON_CRITICAL_WMM_POS)
#define AON_MEM_MEM_MARGIN_NON_CRITICAL_WMM                 AON_MEM_MEM_MARGIN_NON_CRITICAL_WMM_Msk

#define AON_MEM_MEM_MARGIN_NON_CRITICAL_CMM_POS             (6U)
#define AON_MEM_MEM_MARGIN_NON_CRITICAL_CMM_Len             (2U)
#define AON_MEM_MEM_MARGIN_NON_CRITICAL_CMM_Msk             (0x3UL << AON_MEM_MEM_MARGIN_NON_CRITICAL_CMM_POS)
#define AON_MEM_MEM_MARGIN_NON_CRITICAL_CMM                 AON_MEM_MEM_MARGIN_NON_CRITICAL_CMM_Msk

/*******************  Bit definition for AON_MEM_MEM_PARAM register  *******************/
#define AON_MEM_MEM_PARAM_SRC_BIAS_TRIM_POS                 (0U)
#define AON_MEM_MEM_PARAM_SRC_BIAS_TRIM_Len                 (4U)
#define AON_MEM_MEM_PARAM_SRC_BIAS_TRIM_Msk                 (0xFUL << AON_MEM_MEM_PARAM_SRC_BIAS_TRIM_POS)
#define AON_MEM_MEM_PARAM_SRC_BIAS_TRIM                     AON_MEM_MEM_PARAM_SRC_BIAS_TRIM_Msk


/* ================================================================================================================= */
/* ================                                        AON_MSIO                                 ================ */
/* ================================================================================================================= */
/*******************  Bit definition for AON_MSIO_A_PAD_CFG0 register  *******************/
#define AON_MSIO_A_PAD_CFG0_OUT_VAL_POS                     (0U)
#define AON_MSIO_A_PAD_CFG0_OUT_VAL_Len                     (10U)
#define AON_MSIO_A_PAD_CFG0_OUT_VAL_Msk                     (0x3FFUL << AON_MSIO_A_PAD_CFG0_OUT_VAL_POS)
#define AON_MSIO_A_PAD_CFG0_OUT_VAL                         AON_MSIO_A_PAD_CFG0_OUT_VAL_Msk

#define AON_MSIO_A_PAD_CFG0_OE_POS                          (10U)
#define AON_MSIO_A_PAD_CFG0_OE_Len                          (10U)
#define AON_MSIO_A_PAD_CFG0_OE_Msk                          (0x3FFUL << AON_MSIO_A_PAD_CFG0_OE_POS)
#define AON_MSIO_A_PAD_CFG0_OE                              AON_MSIO_A_PAD_CFG0_OE_Msk

#define AON_MSIO_A_PAD_CFG0_IN_VAL_POS                      (20U)
#define AON_MSIO_A_PAD_CFG0_IN_VAL_Len                      (10U)
#define AON_MSIO_A_PAD_CFG0_IN_VAL_Msk                      (0x3FFUL << AON_MSIO_A_PAD_CFG0_IN_VAL_POS)
#define AON_MSIO_A_PAD_CFG0_IN_VAL                          AON_MSIO_A_PAD_CFG0_IN_VAL_Msk

/*******************  Bit definition for AON_MSIO_A_PAD_CFG1 register  *******************/
#define AON_MSIO_A_PAD_CFG1_PE_POS                          (0U)
#define AON_MSIO_A_PAD_CFG1_PE_Len                          (10U)
#define AON_MSIO_A_PAD_CFG1_PE_Msk                          (0x3FFUL << AON_MSIO_A_PAD_CFG1_PE_POS)
#define AON_MSIO_A_PAD_CFG1_PE                               AON_MSIO_A_PAD_CFG1_PE_Msk

#define AON_MSIO_A_PAD_CFG1_PS_POS                          (10U)
#define AON_MSIO_A_PAD_CFG1_PS_Len                          (10U)
#define AON_MSIO_A_PAD_CFG1_PS_Msk                          (0x3FFUL << AON_MSIO_A_PAD_CFG1_PS_POS)
#define AON_MSIO_A_PAD_CFG1_PS                              AON_MSIO_A_PAD_CFG1_PS_Msk

#define AON_MSIO_A_PAD_CFG1_IE_POS                          (20U)
#define AON_MSIO_A_PAD_CFG1_IE_Len                          (10U)
#define AON_MSIO_A_PAD_CFG1_IE_Msk                          (0x3FFUL << AON_MSIO_A_PAD_CFG1_IE_POS)
#define AON_MSIO_A_PAD_CFG1_IE                              AON_MSIO_A_PAD_CFG1_IE_Msk

/*******************  Bit definition for AON_MSIO_A_PAD_CFG2 register  *******************/
#define AON_MSIO_A_PAD_CFG2_IS_POS                          (0U)
#define AON_MSIO_A_PAD_CFG2_IS_Len                          (10U)
#define AON_MSIO_A_PAD_CFG2_IS_Msk                          (0x3FFUL << AON_MSIO_A_PAD_CFG2_IS_POS)
#define AON_MSIO_A_PAD_CFG2_IS                              AON_MSIO_A_PAD_CFG2_IS_Msk

#define AON_MSIO_A_PAD_CFG2_SR_POS                          (10U)
#define AON_MSIO_A_PAD_CFG2_SR_Len                          (10U)
#define AON_MSIO_A_PAD_CFG2_SR_Msk                          (0x3FFUL << AON_MSIO_A_PAD_CFG2_SR_POS)
#define AON_MSIO_A_PAD_CFG2_SR                              AON_MSIO_A_PAD_CFG2_SR_Msk

#define AON_MSIO_A_PAD_CFG2_POE_POS                         (20U)
#define AON_MSIO_A_PAD_CFG2_POE_Len                         (10U)
#define AON_MSIO_A_PAD_CFG2_POE_Msk                         (0x3FFUL << AON_MSIO_A_PAD_CFG2_POE_POS)
#define AON_MSIO_A_PAD_CFG2_POE                             AON_MSIO_A_PAD_CFG2_POE_Msk

/*******************  Bit definition for AON_MSIO_A_PAD_CFG3 register  *******************/
#define AON_MSIO_A_PAD_CFG3_DS0_POS                         (0U)
#define AON_MSIO_A_PAD_CFG3_DS0_Len                         (10U)
#define AON_MSIO_A_PAD_CFG3_DS0_Msk                         (0x3FFUL << AON_MSIO_A_PAD_CFG3_DS0_POS)
#define AON_MSIO_A_PAD_CFG3_DS0                             AON_MSIO_A_PAD_CFG3_DS0_Msk

#define AON_MSIO_A_PAD_CFG3_DS1_POS                         (10U)
#define AON_MSIO_A_PAD_CFG3_DS1_Len                         (10U)
#define AON_MSIO_A_PAD_CFG3_DS1_Msk                         (0x3FFUL << AON_MSIO_A_PAD_CFG3_DS1_POS)
#define AON_MSIO_A_PAD_CFG3_DS1                             AON_MSIO_A_PAD_CFG3_DS1_Msk

#define AON_MSIO_A_PAD_CFG3_AE_POS                          (20U)
#define AON_MSIO_A_PAD_CFG3_AE_Len                          (10U)
#define AON_MSIO_A_PAD_CFG3_AE_Msk                          (0x3FFUL << AON_MSIO_A_PAD_CFG3_AE_POS)
#define AON_MSIO_A_PAD_CFG3_AE                              AON_MSIO_A_PAD_CFG3_AE_Msk

/*******************  Bit definition for AON_MSIO_MCU_OVR register  *******************/
#define AON_MSIO_MCU_OVR_MSIO_OVR_POS                      (0U)
#define AON_MSIO_MCU_OVR_MSIO_OVR_Len                      (10U)
#define AON_MSIO_MCU_OVR_MSIO_OVR_Msk                      (0x3FFUL << AON_MSIO_MCU_OVR_MSIO_OVR_POS)
#define AON_MSIO_MCU_OVR_MSIO_OVR                          AON_MSIO_MCU_OVR_MSIO_OVR_Msk


/* ================================================================================================================= */
/* ================                                        SLP_TIMER                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for SLP_TIMER_CFG0 register  *******************/
#define SLP_TIMER_CFG0_EN_Pos                               (0U)
#define SLP_TIMER_CFG0_EN_Len                               (1U)
#define SLP_TIMER_CFG0_EN_Msk                               (0x1UL << SLP_TIMER_CFG0_EN_Pos)
#define SLP_TIMER_CFG0_EN                                   SLP_TIMER_CFG0_EN_Msk

#define SLP_TIMER_CFG0_VAL_SET_Pos                          (1U)
#define SLP_TIMER_CFG0_VAL_SET_Len                          (1U)
#define SLP_TIMER_CFG0_VAL_SET_Msk                          (0x1UL << SLP_TIMER_CFG0_VAL_SET_Pos)
#define SLP_TIMER_CFG0_VAL_SET                              SLP_TIMER_CFG0_VAL_SET_Msk

#define SLP_TIMER_CFG0_MODE_Pos                             (2U)
#define SLP_TIMER_CFG0_MODE_Len                             (1U)
#define SLP_TIMER_CFG0_MODE_Msk                             (0x1UL << SLP_TIMER_CFG0_MODE_Pos)
#define SLP_TIMER_CFG0_MODE                                 SLP_TIMER_CFG0_MODE_Msk

#define SLP_TIMER_CFG0_COUNT_MODE_Pos                       (3U)
#define SLP_TIMER_CFG0_COUNT_MODE_Len                       (1U)
#define SLP_TIMER_CFG0_COUNT_MODE_Msk                       (0x1UL << SLP_TIMER_CFG0_COUNT_MODE_Pos)
#define SLP_TIMER_CFG0_COUNT_MODE                           SLP_TIMER_CFG0_COUNT_MODE_Msk

#define SLP_TIMER_CFG0_CFG_Pos                              (24U)
#define SLP_TIMER_CFG0_CFG_Len                              (1U)
#define SLP_TIMER_CFG0_CFG_Msk                              (0x1UL << SLP_TIMER_CFG0_CFG_Pos)
#define SLP_TIMER_CFG0_CFG                                  SLP_TIMER_CFG0_CFG_Msk


/*******************  Bit definition for SLP_TIMER_STAT register  *******************/
#define SLP_TIMER_STAT_STAT_Pos                             (0U)
#define SLP_TIMER_STAT_STAT_Len                             (1U)
#define SLP_TIMER_STAT_STAT_Msk                             (0x1UL << SLP_TIMER_STAT_STAT_Pos)
#define SLP_TIMER_STAT_STAT                                 SLP_TIMER_STAT_STAT_Msk

#define SLP_TIMER_STAT_BUSY_Pos                             (1U)
#define SLP_TIMER_STAT_BUSY_Len                             (1U)
#define SLP_TIMER_STAT_BUSY_Msk                             (0x1UL << SLP_TIMER_STAT_BUSY_Pos)
#define SLP_TIMER_STAT_BUSY                                 SLP_TIMER_STAT_BUSY_Msk


/*******************  Bit definition for SLP_TIMER_CLK register  *******************/
#define SLP_TIMER_CLK_SEL_Pos                               (0U)
#define SLP_TIMER_CLK_SEL_Len                               (2U)
#define SLP_TIMER_CLK_SEL_Msk                               (0x3UL << SLP_TIMER_CLK_SEL_Pos)
#define SLP_TIMER_CLK_SEL                                   SLP_TIMER_CLK_SEL_Msk


/*******************  Bit definition for SLP_TIMER_TIMER_W register  *******************/
#define SLP_TIMER_TIMER_W_VAL_SET_Pos                       (0U)
#define SLP_TIMER_TIMER_W_VAL_SET_Len                       (32U)
#define SLP_TIMER_TIMER_W_VAL_SET_Msk                       (0xFFFFFFFFUL << SLP_TIMER_TIMER_W_VAL_SET_Pos)
#define SLP_TIMER_TIMER_W_VAL_SET                           SLP_TIMER_TIMER_W_VAL_SET_Msk


/*******************  Bit definition for SLP_TIMER_TIMER_R register  *******************/
#define SLP_TIMER_TIMER_R_VAL_READ_Pos                      (0U)
#define SLP_TIMER_TIMER_R_VAL_READ_Len                      (32U)
#define SLP_TIMER_TIMER_R_VAL_READ_Msk                      (0xFFFFFFFFUL << SLP_TIMER_TIMER_R_VAL_READ_Pos)
#define SLP_TIMER_TIMER_R_VAL_READ                          SLP_TIMER_TIMER_R_VAL_READ_Msk


/* ================================================================================================================= */
/* ================                                        RTC                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for RTC_CFG0 register  *******************/
#define RTC_CFG0_EN_Pos                                     (0U)
#define RTC_CFG0_EN_Len                                     (1U)
#define RTC_CFG0_EN_Msk                                     (0x1UL << RTC_CFG0_EN_Pos)
#define RTC_CFG0_EN                                         RTC_CFG0_EN_Msk

#define RTC_CFG0_TIMER_SET_Pos                              (1U)
#define RTC_CFG0_TIMER_SET_Len                              (1U)
#define RTC_CFG0_TIMER_SET_Msk                              (0x1UL << RTC_CFG0_TIMER_SET_Pos)
#define RTC_CFG0_TIMER_SET                                  RTC_CFG0_TIMER_SET_Msk

#define RTC_CFG0_ALARM_EN_Pos                               (2U)
#define RTC_CFG0_ALARM_EN_Len                               (1U)
#define RTC_CFG0_ALARM_EN_Msk                               (0x1UL << RTC_CFG0_ALARM_EN_Pos)
#define RTC_CFG0_ALARM_EN                                   RTC_CFG0_ALARM_EN_Msk

#define RTC_CFG0_ALARM_SET_Pos                              (3U)
#define RTC_CFG0_ALARM_SET_Len                              (1U)
#define RTC_CFG0_ALARM_SET_Msk                              (0x1UL << RTC_CFG0_ALARM_SET_Pos)
#define RTC_CFG0_ALARM_SET                                  RTC_CFG0_ALARM_SET_Msk

#define RTC_CFG0_WRAP_CLR_Pos                               (4U)
#define RTC_CFG0_WRAP_CLR_Len                               (1U)
#define RTC_CFG0_WRAP_CLR_Msk                               (0x1UL << RTC_CFG0_WRAP_CLR_Pos)
#define RTC_CFG0_WRAP_CLR                                   RTC_CFG0_WRAP_CLR_Msk

#define RTC_CFG0_TICK_EN_Pos                                (8U)
#define RTC_CFG0_TICK_EN_Len                                (1U)
#define RTC_CFG0_TICK_EN_Msk                                (0x1UL << RTC_CFG0_TICK_EN_Pos)
#define RTC_CFG0_TICK_EN                                    RTC_CFG0_TICK_EN_Msk

#define RTC_CFG0_TICK_SET_Pos                               (9U)
#define RTC_CFG0_TICK_SET_Len                               (1U)
#define RTC_CFG0_TICK_SET_Msk                               (0x1UL << RTC_CFG0_TICK_SET_Pos)
#define RTC_CFG0_TICK_SET                                   RTC_CFG0_TICK_SET_Msk

#define RTC_CFG0_TICK_MDOE_Pos                              (10U)
#define RTC_CFG0_TICK_MDOE_Len                              (1U)
#define RTC_CFG0_TICK_MDOE_Msk                              (0x1UL << RTC_CFG0_TICK_MDOE_Pos)
#define RTC_CFG0_TICK_MDOE                                  RTC_CFG0_TICK_MDOE_Msk

#define RTC_CFG0_CFG_Pos                                    (24U)
#define RTC_CFG0_CFG_Len                                    (1U)
#define RTC_CFG0_CFG_Msk                                    (0x1UL << RTC_CFG0_CFG_Pos)
#define RTC_CFG0_CFG                                        RTC_CFG0_CFG_Msk


/*******************  Bit definition for RTC_CFG1 register  *******************/
#define RTC_CFG1_DIV_Pos                                    (0U)
#define RTC_CFG1_DIV_Len                                    (3U)
#define RTC_CFG1_DIV_Msk                                    (0x7UL << RTC_CFG1_DIV_Pos)
#define RTC_CFG1_DIV                                        RTC_CFG1_DIV_Msk


/*******************  Bit definition for RTC_INT_EN register  *******************/
#define RTC_INT_EN_ALARM_Pos                                (0U)
#define RTC_INT_EN_ALARM_Len                                (1U)
#define RTC_INT_EN_ALARM_Msk                                (0x1UL << RTC_INT_EN_ALARM_Pos)
#define RTC_INT_EN_ALARM                                    RTC_INT_EN_ALARM_Msk

#define RTC_INT_EN_WRAP_Pos                                 (1U)
#define RTC_INT_EN_WRAP_Len                                 (1U)
#define RTC_INT_EN_WRAP_Msk                                 (0x1UL << RTC_INT_EN_WRAP_Pos)
#define RTC_INT_EN_WRAP                                     RTC_INT_EN_WRAP_Msk

#define RTC_INT_EN_TICK_Pos                                 (2U)
#define RTC_INT_EN_TICK_Len                                 (1U)
#define RTC_INT_EN_TICK_Msk                                 (0x1UL << RTC_INT_EN_TICK_Pos)
#define RTC_INT_EN_TICK                                     RTC_INT_EN_TICK_Msk


/*******************  Bit definition for RTC_INT_STAT register  *******************/
#define RTC_INT_STAT_ALARM_Pos                              (0U)
#define RTC_INT_STAT_ALARM_Len                              (1U)
#define RTC_INT_STAT_ALARM_Msk                              (0x1UL << RTC_INT_STAT_ALARM_Pos)
#define RTC_INT_STAT_ALARM                                  RTC_INT_STAT_ALARM_Msk

#define RTC_INT_STAT_WRAP_Pos                               (1U)
#define RTC_INT_STAT_WRAP_Len                               (1U)
#define RTC_INT_STAT_WRAP_Msk                               (0x1UL << RTC_INT_STAT_WRAP_Pos)
#define RTC_INT_STAT_WRAP                                   RTC_INT_STAT_WRAP_Msk

#define RTC_INT_STAT_TICK_Pos                               (2U)
#define RTC_INT_STAT_TICK_Len                               (1U)
#define RTC_INT_STAT_TICK_Msk                               (0x1UL << RTC_INT_STAT_TICK_Pos)
#define RTC_INT_STAT_TICK                                   RTC_INT_STAT_TICK_Msk


/*******************  Bit definition for RTC_STAT register  *******************/
#define RTC_STAT_STAT_Pos                                   (0U)
#define RTC_STAT_STAT_Len                                   (1U)
#define RTC_STAT_STAT_Msk                                   (0x1UL << RTC_STAT_STAT_Pos)
#define RTC_STAT_STAT                                       RTC_STAT_STAT_Msk

#define RTC_STAT_BUSY_Pos                                   (4U)
#define RTC_STAT_BUSY_Len                                   (1U)
#define RTC_STAT_BUSY_Msk                                   (0x1UL << RTC_STAT_BUSY_Pos)
#define RTC_STAT_BUSY                                       RTC_STAT_BUSY_Msk

#define RTC_STAT_WRAP_CNT_Pos                               (8U)
#define RTC_STAT_WRAP_CNT_Len                               (4U)
#define RTC_STAT_WRAP_CNT_Msk                               (0xFUL << RTC_STAT_WRAP_CNT_Pos)
#define RTC_STAT_WRAP_CNT                                   RTC_STAT_WRAP_CNT_Msk


/*******************  Bit definition for RTC_CLK register  *******************/
#define RTC_CLK_SEL_Pos                                     (0U)
#define RTC_CLK_SEL_Len                                     (2U)
#define RTC_CLK_SEL_Msk                                     (0x3UL << RTC_CLK_SEL_Pos)
#define RTC_CLK_SEL                                         RTC_CLK_SEL_Msk


/*******************  Bit definition for RTC_ALARM_W register  *******************/
#define RTC_ALARM_W_VAL_Pos                                 (0U)
#define RTC_ALARM_W_VAL_Len                                 (32U)
#define RTC_ALARM_W_VAL_Msk                                 (0xFFFFFFFFUL << RTC_ALARM_W_VAL_Pos)
#define RTC_ALARM_W_VAL                                     RTC_ALARM_W_VAL_Msk


/*******************  Bit definition for RTC_TIMER_W register  *******************/
#define RTC_TIMER_W_VAL_Pos                                 (0U)
#define RTC_TIMER_W_VAL_Len                                 (32U)
#define RTC_TIMER_W_VAL_Msk                                 (0xFFFFFFFFUL << RTC_TIMER_W_VAL_Pos)
#define RTC_TIMER_W_VAL                                     RTC_TIMER_W_VAL_Msk


/*******************  Bit definition for RTC_TICK_W register  *******************/
#define RTC_TICK_W_VAL_Pos                                  (0U)
#define RTC_TICK_W_VAL_Len                                  (32U)
#define RTC_TICK_W_VAL_Msk                                  (0xFFFFFFFFUL << RTC_TICK_W_VAL_Pos)
#define RTC_TICK_W_VAL                                      RTC_TICK_W_VAL_Msk


/*******************  Bit definition for RTC_TIMER_R register  *******************/
#define RTC_TIMER_R_VAL_Pos                                 (0U)
#define RTC_TIMER_R_VAL_Len                                 (32U)
#define RTC_TIMER_R_VAL_Msk                                 (0xFFFFFFFFUL << RTC_TIMER_R_VAL_Pos)
#define RTC_TIMER_R_VAL                                     RTC_TIMER_R_VAL_Msk


/*******************  Bit definition for RTC_ALARM_R register  *******************/
#define RTC_ALARM_R_VAL_Pos                                 (0U)
#define RTC_ALARM_R_VAL_Len                                 (32U)
#define RTC_ALARM_R_VAL_Msk                                 (0xFFFFFFFFUL << RTC_ALARM_R_VAL_Pos)
#define RTC_ALARM_R_VAL                                     RTC_ALARM_R_VAL_Msk


/*******************  Bit definition for RTC_TICK_R register  *******************/
#define RTC_TICK_R_VAL_Pos                                  (0U)
#define RTC_TICK_R_VAL_Len                                  (32U)
#define RTC_TICK_R_VAL_Msk                                  (0xFFFFFFFFUL << RTC_TICK_R_VAL_Pos)
#define RTC_TICK_R_VAL                                      RTC_TICK_R_VAL_Msk


/* ================================================================================================================= */
/* ================                                        CLK_CAL                                  ================ */
/* ================================================================================================================= */
/*******************  Bit definition for CLK_CAL_SL_CLK_CTRL register  *******************/
#define CLK_CAL_SL_CLK_CTRL_EN_POS                          (0U)
#define CLK_CAL_SL_CLK_CTRL_EN_Len                          (1U)
#define CLK_CAL_SL_CLK_CTRL_EN_Msk                          (0x1UL << CLK_CAL_SL_CLK_CTRL_EN_POS)
#define CLK_CAL_SL_CLK_CTRL_EN                              CLK_CAL_SL_CLK_CTRL_EN_Msk

/*******************  Bit definition for CLK_CAL_SL_CLK_CNT register  *******************/
#define CLK_CAL_SL_CLK_CNT_COUNT_POS                        (0U)
#define CLK_CAL_SL_CLK_CNT_COUNT_Len                        (12U)
#define CLK_CAL_SL_CLK_CNT_COUNT_Msk                        (0xFFFUL << CLK_CAL_SL_CLK_CNT_COUNT_POS)
#define CLK_CAL_SL_CLK_CNT_COUNT                            CLK_CAL_SL_CLK_CNT_COUNT_Msk

/*******************  Bit definition for CLK_CAL_SL_CLK_STAT register  *******************/
#define CLK_CAL_SL_CLK_STAT_DONE_POS                        (0U)
#define CLK_CAL_SL_CLK_STAT_DONE_Len                        (1U)
#define CLK_CAL_SL_CLK_STAT_DONE_Msk                        (0x1UL << CLK_CAL_SL_CLK_STAT_DONE_POS)
#define CLK_CAL_SL_CLK_STAT_DONE                            CLK_CAL_SL_CLK_STAT_DONE_Msk

#define CLK_CAL_SL_CLK_STAT_OVER_POS                        (8U)
#define CLK_CAL_SL_CLK_STAT_OVER_Len                        (1U)
#define CLK_CAL_SL_CLK_STAT_OVER_Msk                        (0x1UL << CLK_CAL_SL_CLK_STAT_OVER_POS)
#define CLK_CAL_SL_CLK_STAT_OVER                            CLK_CAL_SL_CLK_STAT_OVER_Msk

/*******************  Bit definition for CLK_CAL_SL_CLK_CNT0 register  *******************/
#define CLK_CAL_SL_CLK_CNT0_VAL_POS                         (0U)
#define CLK_CAL_SL_CLK_CNT0_VAL_Len                         (24U)
#define CLK_CAL_SL_CLK_CNT0_VAL_Msk                         (0xFFFFFFUL << CLK_CAL_SL_CLK_CNT0_VAL_POS)
#define CLK_CAL_SL_CLK_CNT0_VAL                             CLK_CAL_SL_CLK_CNT0_VAL_Msk

/*******************  Bit definition for CLK_CAL_SL_CLK_CNT1 register  *******************/
#define CLK_CAL_SL_CLK_CNT1_VAL_POS                         (0U)
#define CLK_CAL_SL_CLK_CNT1_VAL_Len                         (12U)
#define CLK_CAL_SL_CLK_CNT1_VAL_Msk                         (0xFFFUL << CLK_CAL_SL_CLK_CNT1_VAL_POS)
#define CLK_CAL_SL_CLK_CNT1_VAL                             CLK_CAL_SL_CLK_CNT1_VAL_Msk

/*******************  Bit definition for CLK_CAL_SL_CLK_INT_EN register  *******************/
#define CLK_CAL_SL_CLK_INT_EN_DONE_POS                       (0U)
#define CLK_CAL_SL_CLK_INT_EN_DONE_Len                       (1U)
#define CLK_CAL_SL_CLK_INT_EN_DONE_Msk                       (0x1UL << CLK_CAL_SL_CLK_INT_EN_DONE_POS)
#define CLK_CAL_SL_CLK_INT_EN_DONE                           CLK_CAL_SL_CLK_INT_EN_DONE_Msk

#define CLK_CAL_SL_CLK_INT_EN_OVER_POS                       (1U)
#define CLK_CAL_SL_CLK_INT_EN_OVER_Len                       (1U)
#define CLK_CAL_SL_CLK_INT_EN_OVER_Msk                       (0x1UL << CLK_CAL_SL_CLK_INT_EN_OVER_POS)
#define CLK_CAL_SL_CLK_INT_EN_OVER                           CLK_CAL_SL_CLK_INT_EN_OVER_Msk

/*******************  Bit definition for CLK_CAL_SL_CLK_INT_CLR register  *******************/
#define CLK_CAL_SL_CLK_INT_CLR_DONE_POS                      (0U)
#define CLK_CAL_SL_CLK_INT_CLR_DONE_Len                      (1U)
#define CLK_CAL_SL_CLK_INT_CLR_DONE_Msk                      (0x1UL << CLK_CAL_SL_CLK_INT_CLR_DONE_POS)
#define CLK_CAL_SL_CLK_INT_CLR_DONE                          CLK_CAL_SL_CLK_INT_CLR_DONE_Msk

#define CLK_CAL_SL_CLK_INT_CLR_OVER_POS                      (1U)
#define CLK_CAL_SL_CLK_INT_CLR_OVER_Len                      (1U)
#define CLK_CAL_SL_CLK_INT_CLR_OVER_Msk                      (0x1UL << CLK_CAL_SL_CLK_INT_CLR_OVER_POS)
#define CLK_CAL_SL_CLK_INT_CLR_OVER                          CLK_CAL_SL_CLK_INT_CLR_OVER_Msk

/*******************  Bit definition for CLK_CAL_SL_CLK_SEL register  *******************/
#define CLK_CAL_SL_CLK_SEL_VAL_POS                          (0U)
#define CLK_CAL_SL_CLK_SEL_VAL_Len                          (8U)
#define CLK_CAL_SL_CLK_SEL_VAL_Msk                          (0xFFUL << CLK_CAL_SL_CLK_SEL_VAL_POS)
#define CLK_CAL_SL_CLK_SEL_VAL                              CLK_CAL_SL_CLK_SEL_VAL_Msk

/*******************  Bit definition for CLK_CAL_HS_CLK_CTRL register  *******************/
#define CLK_CAL_HS_CLK_CTRL_EN_POS                          (0U)
#define CLK_CAL_HS_CLK_CTRL_EN_Len                          (1U)
#define CLK_CAL_HS_CLK_CTRL_EN_Msk                          (0x1UL << CLK_CAL_HS_CLK_CTRL_EN_POS)
#define CLK_CAL_HS_CLK_CTRL_EN                              CLK_CAL_HS_CLK_CTRL_EN_Msk

/*******************  Bit definition for CLK_CAL_HS_CLK_CNT register  *******************/
#define CLK_CAL_HS_CLK_CNT_COUNT_POS                        (0U)
#define CLK_CAL_HS_CLK_CNT_COUNT_Len                        (12U)
#define CLK_CAL_HS_CLK_CNT_COUNT_Msk                        (0xFFFUL << CLK_CAL_HS_CLK_CNT_COUNT_POS)
#define CLK_CAL_HS_CLK_CNT_COUNT                            CLK_CAL_HS_CLK_CNT_COUNT_Msk

/*******************  Bit definition for CLK_CAL_HS_CLK_STAT register  *******************/
#define CLK_CAL_HS_CLK_STAT_DONE_POS                        (0U)
#define CLK_CAL_HS_CLK_STAT_DONE_Len                        (1U)
#define CLK_CAL_HS_CLK_STAT_DONE_Msk                        (0x1UL << CLK_CAL_HS_CLK_STAT_DONE_POS)
#define CLK_CAL_HS_CLK_STAT_DONE                            CLK_CAL_HS_CLK_STAT_DONE_Msk

#define CLK_CAL_HS_CLK_STAT_OVER_POS                        (8U)
#define CLK_CAL_HS_CLK_STAT_OVER_Len                        (1U)
#define CLK_CAL_HS_CLK_STAT_OVER_Msk                        (0x1UL << CLK_CAL_HS_CLK_STAT_OVER_POS)
#define CLK_CAL_HS_CLK_STAT_OVER                            CLK_CAL_HS_CLK_STAT_OVER_Msk

/*******************  Bit definition for CLK_CAL_HS_CLK_CNT0 register  *******************/
#define CLK_CAL_HS_CLK_CNT0_VAL_POS                         (0U)
#define CLK_CAL_HS_CLK_CNT0_VAL_Len                         (24U)
#define CLK_CAL_HS_CLK_CNT0_VAL_Msk                         (0xFFFFFFUL << CLK_CAL_HS_CLK_CNT0_VAL_POS)
#define CLK_CAL_HS_CLK_CNT0_VAL                             CLK_CAL_HS_CLK_CNT0_VAL_Msk

/*******************  Bit definition for CLK_CAL_HS_CLK_CNT1 register  *******************/
#define CLK_CAL_HS_CLK_CNT1_VAL_POS                         (0U)
#define CLK_CAL_HS_CLK_CNT1_VAL_Len                         (12U)
#define CLK_CAL_HS_CLK_CNT1_VAL_Msk                         (0xFFFUL << CLK_CAL_HS_CLK_CNT1_VAL_POS)
#define CLK_CAL_HS_CLK_CNT1_VAL                             CLK_CAL_HS_CLK_CNT1_VAL_Msk

/*******************  Bit definition for CLK_CAL_HS_CLK_INT_EN register  *******************/
#define CLK_CAL_HS_CLK_INT_EN_DONE_POS                       (0U)
#define CLK_CAL_HS_CLK_INT_EN_DONE_Len                       (1U)
#define CLK_CAL_HS_CLK_INT_EN_DONE_Msk                       (0x1UL << CLK_CAL_HS_CLK_INT_EN_DONE_POS)
#define CLK_CAL_HS_CLK_INT_EN_DONE                           CLK_CAL_HS_CLK_INT_EN_DONE_Msk

#define CLK_CAL_HS_CLK_INT_EN_OVER_POS                       (1U)
#define CLK_CAL_HS_CLK_INT_EN_OVER_Len                       (1U)
#define CLK_CAL_HS_CLK_INT_EN_OVER_Msk                       (0x1UL << CLK_CAL_HS_CLK_INT_EN_OVER_POS)
#define CLK_CAL_HS_CLK_INT_EN_OVER                           CLK_CAL_HS_CLK_INT_EN_OVER_Msk

/*******************  Bit definition for CLK_CAL_HS_CLK_INT_CLR register  *******************/
#define CLK_CAL_HS_CLK_INT_CLR_DONE_POS                      (0U)
#define CLK_CAL_HS_CLK_INT_CLR_DONE_Len                      (1U)
#define CLK_CAL_HS_CLK_INT_CLR_DONE_Msk                      (0x1UL << CLK_CAL_HS_CLK_INT_CLR_DONE_POS)
#define CLK_CAL_HS_CLK_INT_CLR_DONE                          CLK_CAL_HS_CLK_INT_CLR_DONE_Msk

#define CLK_CAL_HS_CLK_INT_CLR_OVER_POS                      (1U)
#define CLK_CAL_HS_CLK_INT_CLR_OVER_Len                      (1U)
#define CLK_CAL_HS_CLK_INT_CLR_OVER_Msk                      (0x1UL << CLK_CAL_HS_CLK_INT_CLR_OVER_POS)
#define CLK_CAL_HS_CLK_INT_CLR_OVER                          CLK_CAL_HS_CLK_INT_CLR_OVER_Msk


/*******************  Bit definition for CLK_CAL_HS_CLK_SEL register  *******************/
#define CLK_CAL_HS_CLK_SEL_VAL_POS                          (0U)
#define CLK_CAL_HS_CLK_SEL_VAL_Len                          (8U)
#define CLK_CAL_HS_CLK_SEL_VAL_Msk                          (0xFFUL << CLK_CAL_HS_CLK_SEL_VAL_POS)
#define CLK_CAL_HS_CLK_SEL_VAL                              CLK_CAL_HS_CLK_SEL_VAL_Msk

/* ================================================================================================================= */
/* ================                                        DDVS_CTRL                                ================ */
/* ================================================================================================================= */
/*******************  Bit definition for DDVS_EN register  ***********************/
#define DDVS_CTRL_CONF_DDVS_EN_POS                           (0U)
#define DDVS_CTRL_CONF_DDVS_EN_Len                           (1U)
#define DDVS_CTRL_CONF_DDVS_EN_Msk                           (0x1UL << DDVS_CTRL_CONF_DDVS_EN_POS)
#define DDVS_CTRL_CONF_DDVS_EN                               DDVS_CTRL_CONF_DDVS_EN_Msk

/*******************  Bit definition for DDVS_CFG_1 register  ********************/
#define DDVS_CFG_1_CONF_THRESHOLD_SLOW_POS                   (4U)
#define DDVS_CFG_1_CONF_THRESHOLD_SLOW_Len                   (12U)
#define DDVS_CFG_1_CONF_THRESHOLD_SLOW_Msk                   (0xFFFUL << DDVS_CFG_1_CONF_THRESHOLD_SLOW_POS)
#define DDVS_CFG_1_CONF_THRESHOLD_SLOW                       DDVS_CFG_1_CONF_THRESHOLD_SLOW_Msk

#define DDVS_CFG_1_CONF_VREF_MANUAL_POS                      (17U)
#define DDVS_CFG_1_CONF_VREF_MANUAL_Len                      (6U)
#define DDVS_CFG_1_CONF_VREF_MANUAL_Msk                      (0x3FUL << DDVS_CFG_1_CONF_VREF_MANUAL_POS)
#define DDVS_CFG_1_CONF_VREF_MANUAL                          DDVS_CFG_1_CONF_VREF_MANUAL_Msk

#define DDVS_CFG_1_ERR_INT_POS                               (23U)
#define DDVS_CFG_1_ERR_INT_Len                               (1U)
#define DDVS_CFG_1_ERR_INT_Msk                               (0x1UL << DDVS_CFG_1_ERR_INT_POS)
#define DDVS_CFG_1_ERR_INT                                   DDVS_CFG_1_ERR_INT_Msk

#define DDVS_CFG_1_CONF_INT_EN_POS                           (24U)
#define DDVS_CFG_1_CONF_INT_EN_Len                           (1U)
#define DDVS_CFG_1_CONF_INT_EN_Msk                           (0x1UL << DDVS_CFG_1_CONF_INT_EN_POS)
#define DDVS_CFG_1_CONF_INT_EN                               DDVS_CFG_1_CONF_INT_EN_Msk

#define DDVS_CFG_1_CONF_RINGO_EN_POS                         (25U)
#define DDVS_CFG_1_CONF_RINGO_EN_Len                         (4U)
#define DDVS_CFG_1_CONF_RINGO_EN_Msk                         (0xFUL << DDVS_CFG_1_CONF_RINGO_EN_POS)
#define DDVS_CFG_1_CONF_RINGO_EN                             DDVS_CFG_1_CONF_RINGO_EN_Msk

#define DDVS_CFG_1_CONF_DIV_FACTOR_POS                       (29U)
#define DDVS_CFG_1_CONF_DIV_FACTOR_Len                       (2U)
#define DDVS_CFG_1_CONF_DIV_FACTOR_Msk                       (0x3UL << DDVS_CFG_1_CONF_DIV_FACTOR_POS)
#define DDVS_CFG_1_CONF_DIV_FACTOR                           DDVS_CFG_1_CONF_DIV_FACTOR_Msk

#define DDVS_CFG_1_CONF_DDVS_MODE_POS                        (31U)
#define DDVS_CFG_1_CONF_DDVS_MODE_Len                        (1U)
#define DDVS_CFG_1_CONF_DDVS_MODE_Msk                        (0x1UL << DDVS_CFG_1_CONF_DDVS_MODE_POS)
#define DDVS_CFG_1_CONF_DDVS_MODE                            DDVS_CFG_1_CONF_DDVS_MODE_Msk

/*******************  Bit definition for DDVS_CFG_2 register  ********************/
#define DDVS_CFG_2_CONF_THRESHOLD_FAST_POS                   (4U)
#define DDVS_CFG_2_CONF_THRESHOLD_FAST_Len                   (0x12U)
#define DDVS_CFG_2_CONF_THRESHOLD_FAST_Msk                   (0xFFFUL << DDVS_CFG_2_CONF_THRESHOLD_FAST_POS)
#define DDVS_CFG_2_CONF_THRESHOLD_FAST                       DDVS_CFG_2_CONF_THRESHOLD_FAST_Msk

#define DDVS_CFG_2_CONF_TARGET_CNT_POS                       (20U)
#define DDVS_CFG_2_CONF_TARGET_CNT_Len                       (12U)
#define DDVS_CFG_2_CONF_TARGET_CNT_Msk                       (0xFFFUL << DDVS_CFG_2_CONF_TARGET_CNT_POS)
#define DDVS_CFG_2_CONF_TARGET_CNT                           DDVS_CFG_2_CONF_TARGET_CNT_Msk

/*******************  Bit definition for DDVS_RINGO_CNT_01 register  *************/
#define DDVS_RINGO_CNT_01_RINGO_1_CNT_POS                    (4U)
#define DDVS_RINGO_CNT_01_RINGO_1_CNT_Len                    (12U)
#define DDVS_RINGO_CNT_01_RINGO_1_CNT_Msk                    (0xFFFUL << DDVS_RINGO_CNT_01_RINGO_1_CNT_POS)
#define DDVS_RINGO_CNT_01_RINGO_1_CNT                        DDVS_RINGO_CNT_01_RINGO_1_CNT_Msk

#define DDVS_RINGO_CNT_01_RINGO_0_CNT_POS                    (20U)
#define DDVS_RINGO_CNT_01_RINGO_0_CNT_Len                    (12U)
#define DDVS_RINGO_CNT_01_RINGO_0_CNT_Msk                    (0xFFFUL << DDVS_RINGO_CNT_01_RINGO_0_CNT_POS)
#define DDVS_RINGO_CNT_01_RINGO_0_CNT                        DDVS_RINGO_CNT_01_RINGO_0_CNT_Msk

/*******************  Bit definition for DDVS_RINGO_CNT_23 register  *************/
#define DDVS_RINGO_CNT_23_RINGO_3_CNT_POS                    (4U)
#define DDVS_RINGO_CNT_23_RINGO_3_CNT_Len                    (12U)
#define DDVS_RINGO_CNT_23_RINGO_3_CNT_Msk                    (0xFFFUL << DDVS_RINGO_CNT_23_RINGO_3_CNT_POS)
#define DDVS_RINGO_CNT_23_RINGO_3_CNT                        DDVS_RINGO_CNT_23_RINGO_3_CNT_Msk

#define DDVS_RINGO_CNT_23_RINGO_2_CNT_POS                    (20U)
#define DDVS_RINGO_CNT_23_RINGO_2_CNT_Len                    (12U)
#define DDVS_RINGO_CNT_23_RINGO_2_CNT_Msk                    (0xFFFUL << DDVS_RINGO_CNT_23_RINGO_2_CNT_POS)
#define DDVS_RINGO_CNT_23_RINGO_2_CNT                        DDVS_RINGO_CNT_23_RINGO_2_CNT_Msk

/*******************  Bit definition for DDVS_FSM register  **********************/
#define DDVS_FSM_STS_FSM_CURR_POS                            (29U)
#define DDVS_FSM_STS_FSM_CURR_Len                            (3U)
#define DDVS_FSM_STS_FSM_CURR_Msk                            (0x7UL << DDVS_FSM_STS_FSM_CURR_POS)
#define DDVS_FSM_STS_FSM_CURR                                DDVS_FSM_STS_FSM_CURR_Msk

/*******************  Bit definition for DDVS_CLK_CTRL register  *****************/
#define DDVS_CLK_CTRL_DDVS_CLK_EN_POS                        (0U)
#define DDVS_CLK_CTRL_DDVS_CLK_EN_Len                        (1U)
#define DDVS_CLK_CTRL_DDVS_CLK_EN_Msk                        (0x1UL << DDVS_CLK_CTRL_DDVS_CLK_EN_POS)
#define DDVS_CLK_CTRL_DDVS_CLK_EN                            DDVS_CLK_CTRL_DDVS_CLK_EN_Msk

#define DDVS_CLK_CTRL_DDVS_CLK_SEL_POS                       (8U)
#define DDVS_CLK_CTRL_DDVS_CLK_SEL_Len                       (2U)
#define DDVS_CLK_CTRL_DDVS_CLK_SEL_Msk                       (0x3UL << DDVS_CLK_CTRL_DDVS_CLK_SEL_POS)
#define DDVS_CLK_CTRL_DDVS_CLK_SEL                           DDVS_CLK_CTRL_DDVS_CLK_SEL_Msk

/*******************  Bit definition for PAD_IE_AUTO_EN register  *****************/
#define MCU_PAD_IE_AUTO_EN_DPAD_POS                         (0U)
#define MCU_PAD_IE_AUTO_EN_DPAD_Len                         (1U)
#define MCU_PAD_IE_AUTO_EN_DPAD_Msk                         (0x1UL << MCU_PAD_IE_AUTO_EN_DPAD_POS)
#define MCU_PAD_IE_AUTO_EN_DPAD                             MCU_PAD_IE_AUTO_EN_DPAD_Msk

#define MCU_PAD_IE_AUTO_EN_AON_POS                          (1U)
#define MCU_PAD_IE_AUTO_EN_AON_Len                          (1U)
#define MCU_PAD_IE_AUTO_EN_AON_Msk                          (0x1UL << MCU_PAD_IE_AUTO_EN_AON_POS)
#define MCU_PAD_IE_AUTO_EN_AON                              MCU_PAD_IE_AUTO_EN_AON_Msk

#define MCU_PAD_IE_AUTO_EN_MSIO_POS                         (1U)
#define MCU_PAD_IE_AUTO_EN_MSIO_Len                         (1U)
#define MCU_PAD_IE_AUTO_EN_MSIO_Msk                         (0x1UL << MCU_PAD_IE_AUTO_EN_MSIO_POS)
#define MCU_PAD_IE_AUTO_EN_MSIO                             MCU_PAD_IE_AUTO_EN_MSIO_Msk

/*******************  Bit definition for DPAD_IE_BUS register  *****************/
#define MCU_PAD_DPAD_IE_POS                                 (0U)
#define MCU_PAD_DPAD_IE_Len                                 (20U)
#define MCU_PAD_DPAD_IE_Msk                                 (0xFFFFUL << MCU_PAD_DPAD_IE_POS)
#define MCU_PAD_DPAD_IE                                     MCU_PAD_DPAD_IE_Msk

/*******************  Bit definition for DPAD_PE_BUS register  *****************/
#define MCU_PAD_DPAD_PE_POS                                 (0U)
#define MCU_PAD_DPAD_PE_Len                                 (20U)
#define MCU_PAD_DPAD_PE_Msk                                 (0xFFFFUL << MCU_PAD_DPAD_PE_POS)
#define MCU_PAD_DPAD_PE                                     MCU_PAD_DPAD_PE_Msk


/*******************  Bit definition for DPAD_PS_BUS register  *****************/
#define MCU_PAD_DPAD_PS_POS                                 (0U)
#define MCU_PAD_DPAD_PS_Len                                 (20U)
#define MCU_PAD_DPAD_PS_Msk                                 (0xFFFFUL << MCU_PAD_DPAD_PS_POS)
#define MCU_PAD_DPAD_PS                                     MCU_PAD_DPAD_PS_Msk

/*******************  Bit definition for DPAD_IS_BUS register  *****************/
#define MCU_PAD_DPAD_IS_POS                                 (0U)
#define MCU_PAD_DPAD_IS_Len                                 (20U)
#define MCU_PAD_DPAD_IS_Msk                                 (0xFFFFUL << MCU_PAD_DPAD_IS_POS)
#define MCU_PAD_DPAD_IS                                     MCU_PAD_DPAD_IS_Msk

/*******************  Bit definition for DPAD_IS_BUS register  *****************/
#define MCU_PAD_DPAD_IS_POS                                 (0U)
#define MCU_PAD_DPAD_IS_Len                                 (20U)
#define MCU_PAD_DPAD_IS_Msk                                 (0xFFFFUL << MCU_PAD_DPAD_IS_POS)
#define MCU_PAD_DPAD_IS                                     MCU_PAD_DPAD_IS_Msk

/*******************  Bit definition for DPAD_SR_BUS register  *****************/
#define MCU_PAD_DPAD_SR_POS                                 (0U)
#define MCU_PAD_DPAD_SR_Len                                 (20U)
#define MCU_PAD_DPAD_SR_Msk                                 (0xFFFFUL << MCU_PAD_DPAD_SR_POS)
#define MCU_PAD_DPAD_SR                                     MCU_PAD_DPAD_SR_Msk

/*******************  Bit definition for DPAD_DS0_BUS register  *****************/
#define MCU_PAD_DPAD_DS0_POS                                 (0U)
#define MCU_PAD_DPAD_DS0_Len                                 (20U)
#define MCU_PAD_DPAD_DS0_Msk                                 (0xFFFFUL << MCU_PAD_DPAD_DS0_POS)
#define MCU_PAD_DPAD_DS0                                     MCU_PAD_DPAD_DS0_Msk

/*******************  Bit definition for DPAD_DS1_BUS register  *****************/
#define MCU_PAD_DPAD_DS1_POS                                 (0U)
#define MCU_PAD_DPAD_DS1_Len                                 (20U)
#define MCU_PAD_DPAD_DS1_Msk                                 (0xFFFFUL << MCU_PAD_DPAD_DS1_POS)
#define MCU_PAD_DPAD_DS1                                     MCU_PAD_DPAD_DS1_Msk

/*******************  Bit definition for DPAD_DS1_POE register  *****************/
#define MCU_PAD_DPAD_POE_POS                                 (0U)
#define MCU_PAD_DPAD_POE_Len                                 (20U)
#define MCU_PAD_DPAD_POE_Msk                                 (0xFFFFUL << MCU_PAD_DPAD_POE_POS)
#define MCU_PAD_DPAD_POE                                     MCU_PAD_DPAD_POE_Msk

/*******************  Bit definition for COMM_HTABLE_AM_SWCNTL_CFG register  *****************/
#define MCOMM_HTABLE_AM_SWCNTL_EN_POS                        (0U)
#define MCOMM_HTABLE_AM_SWCNTL_EN_Len                        (1U)
#define MCOMM_HTABLE_AM_SWCNTL_EN_Msk                        (0x01L << MCOMM_HTABLE_AM_SWCNTL_EN_POS)
#define MCOMM_HTABLE_AM_SWCNTL_EN                            MCOMM_HTABLE_AM_SWCNTL_EN_Msk

#define MCOMM_HTABLE_AM_SWCNTL_REG_NUM_POS                   (7U)
#define MCOMM_HTABLE_AM_SWCNTL_REG_NUM_Len                   (9U)
#define MCOMM_HTABLE_AM_SWCNTL_REG_NUM_Msk                   (0x01FL << MCOMM_HTABLE_AM_SWCNTL_REG_NUM_POS)
#define MCOMM_HTABLE_AM_SWCNTL_REG_NUM                       MCOMM_HTABLE_AM_SWCNTL_REG_NUM_Msk

/*******************  Bit definition for COMM_HTABLE_AM_SWCNTL_ENABLE register  *****************/
#define MCOMM_HTABLE_AM_TRIGGER0_POS                         (0U)
#define MCOMM_HTABLE_AM_TRIGGER0_Len                         (1U)
#define MCOMM_HTABLE_AM_TRIGGER0_Msk                         (0x01L << MCOMM_HTABLE_AM_TRIGGER0_POS)
#define MCOMM_HTABLE_AM_TRIGGER0_EN                          MCOMM_HTABLE_AM_TRIGGER0_Msk

/*******************  Bit definition for COMM_HTABLE_AM_IRQ_MSK register  *****************/
#define MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_MSK_POS          (15U)
#define MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_MSK_Len          (1U)
#define MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_MSK_Msk          (0x01L << MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_MSK_POS)
#define MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_MSK_EN           MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_MSK_Msk

/*******************  Bit definition for COMM_HTABLE_AM_IRQ_ACK register  *****************/
#define MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_ACK_POS          (15U)
#define MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_ACK_Len          (1U)
#define MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_ACK_Msk          (0x01L << MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_ACK_POS)
#define MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_ACK_EN           MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_ACK_Msk

/*******************  Bit definition for COMM_HTABLE_AM_IRQ_VEC register  *****************/
#define MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_VEC_POS          (15U)
#define MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_VEC_Len          (1U)
#define MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_VEC_Msk          (0x01L << MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_VEC_POS)
#define MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_VEC_EN           MCOMM_HTABLE_AM_SWCNTL_CFG_DONE_INT_VEC_Msk

/** @} */

#ifdef __cplusplus
  }
#endif

#endif // __GR552xx_INT_H__

/** @} */ /* End of group GR552xx */

/** @} */ /* End of group CMSIS_Device */

