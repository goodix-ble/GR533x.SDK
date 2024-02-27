/**************************************************************************//**
 * @file     gr53xx.h
 * @brief    CMSIS Cortex-M# Core Peripheral Access Layer Header File for
 *           Device gr53xx
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

/** @addtogroup GR54xx
  * @{
  */

#ifndef __GR53xx_H__
#define __GR53xx_H__

#ifdef __cplusplus
extern "C" {
#endif

/** @addtogroup Peripheral_interrupt_number_definition
  * @{
  */



/**
 * @brief GR533x Interrupt Number Definition, according to the selected device
 *        in @ref Library_configuration_section
 */

/* ================================================================================================================= */
/* ================                           Interrupt Number Definition                           ================ */
/* ================================================================================================================= */
typedef enum IRQn
{
/* ==================================  ARM Cortex-M# Specific Interrupt Numbers  =================================== */

    NonMaskableInt_IRQn       = -14,  /**< -14  Non maskable Interrupt, cannot be stopped or preempted               */
    HardFault_IRQn            = -13,  /**< -13  Hard Fault, all classes of Fault                                     */
    MemoryManagement_IRQn     = -12,  /**< -12  Memory Management, MPU mismatch, including Access Violation
                                                and No Match                                                         */
    BusFault_IRQn             = -11,  /**< -11  Bus Fault, Pre-Fetch-, Memory Access Fault, other address/memory
                                                related Fault                                                        */
    UsageFault_IRQn           = -10,  /**< -10  Usage Fault, i.e. Undef Instruction, Illegal State Transition        */
    SVCall_IRQn               =  -5,  /**< -5 System Service Call via SVC instruction                                */
    DebugMonitor_IRQn         =  -4,  /**< -4 Debug Monitor                                                          */
    PendSV_IRQn               =  -2,  /**< -2 Pendable request for system service                                    */
    SysTick_IRQn              =  -1,  /**< -1 System Tick Timer                                                      */

/* ======================================  <Device> Specific Interrupt Numbers  ==================================== */
    WDT_IRQn                  =   0,  /**< Watchdog Timer Interrupt                                                  */
    BLE_DFE_IRQn              =   1,  /**< BLE_DEF Interrupt                                                         */
    BLE_IRQn                  =   2,  /**< BLE Interrupt                                                             */
    DMA0_IRQn                 =   3,  /**< DMA0 Interrupt                                                            */
    SPI_M_IRQn                =   4,  /**< SPI_M Interrupt                                                           */
    SPI_S_IRQn                =   5,  /**< SPI_S Interrupt                                                           */
    EXT0_IRQn                 =   6,  /**< External 0 Interrupt                                                      */
    EXT1_IRQn                 =   7,  /**< External 1 Interrupt                                                      */
    TIMER0_IRQn               =   8,  /**< Timer0 Interrupt                                                          */
    TIMER1_IRQn               =   9,  /**< Timer1 Interrupt                                                          */
    DUAL_TIMER_IRQn           =  10,  /**< Dual_Timer Interrupt                                                      */
    DDVS_ERR_IRQn             =  11,  /**< DDVS ERR Interrupt                                                         */
    UART0_IRQn                =  12,  /**< UART0 Interrupt                                                           */
    UART1_IRQn                =  13,  /**< UART1 Interrupt                                                           */
    I2C0_IRQn                 =  14,  /**< I2C0 Interrupt                                                            */
    I2C1_IRQn                 =  15,  /**< I2C1 Interrupt                                                            */
    RNG_IRQn                  =  16,  /**< RNG Interrupt                                                             */
    BOD_ASSERT_IRQn           =  17,  /**< BOD UP Interrupt                                                          */
    BLE_SDK_IRQn              =  18,  /**< BLE_SDK_SCHEDULE Interrupt                                                */
    BLESLP_IRQn               =  19,  /**< SMC-OSC Interrupt                                                         */
    SLPTIMER_IRQn             =  20,  /**< SLEEP TIMER Interrupt                                                     */
    AON_EXT_IRQn              =  21,  /**< EXT-EVT Interrupt                                                         */
    AON_WDT_IRQn              =  22,  /**< Always on Watchdog Interrupt                                              */
    CALENDAR_IRQn             =  23,  /**< RTC Interrupt                                                             */
    COMM_CORE_IRQn            =  24,  /**< COMM CORE Interrupt                                                       */
    SLP_FAIL_IRQn             =  25,  /**< DEEP SLEEP FAIL Interrupt                                                 */
    CTE_FULL_IRQn             =  26,  /**< CTE_FULL Interrupt                                                        */
    BOD_DEASSERT_IRQn         =  27,  /**< BOD DOWN Interrupt                                                        */
    COMP_IRQn                 =  28,  /**< Comparator Interrupt                                                      */
    CPLL_DRIFT_IRQn           =  29,  /**< CPLL DRIFT Interrupt                                                      */
    CLK_CALIB_IRQn            =  30,  /**< CLOCK Calibration Done Interrupt                                          */
    BLE_PWR_ON_IRQn           =  31,  /**< AON BLE sequencer power on done Interrupt                                 */
    BLE_PWR_DN_IRQn           =  32,  /**< AON BLE sequencer power down done Interrupt                               */
    PLL_STATE_IRQn            =  33,  /**< PLL STATE Interrupt                                                       */
    PWM0_IRQn                 =  34,  /**< PWM0 Interrupt                                                            */
    MAX_NUMS_IRQn             =  35,  /**< Last Interrupt                                                            */
} IRQn_Type;

/** @} */ /* End of group Peripheral     _interrupt_number_definition */

/**
  * @brief IO_MUX define
  */
/* Sliver 1.1 */
#define IO_MUX_GPIO                 ((uint32_t)  0U)
#define IO_MUX_I2C0_SCL             ((uint32_t)  1U)
#define IO_MUX_I2C0_SDA             ((uint32_t)  2U)
#define IO_MUX_I2C1_SCL             ((uint32_t)  3U)
#define IO_MUX_I2C1_SDA             ((uint32_t)  4U)
#define IO_MUX_UART0_CTS            ((uint32_t)  5U)
#define IO_MUX_UART0_RTS            ((uint32_t)  6U)
#define IO_MUX_UART0_TX             ((uint32_t)  7U)
#define IO_MUX_UART0_RX             ((uint32_t)  8U)
#define IO_MUX_UART1_CTS            ((uint32_t)  9U)
#define IO_MUX_UART1_RTS            ((uint32_t) 10U)
#define IO_MUX_UART1_TX             ((uint32_t) 11U)
#define IO_MUX_UART1_RX             ((uint32_t) 12U)
#define IO_MUX_PWM0                 ((uint32_t) 13U)
#define IO_MUX_PWM1                 ((uint32_t) 14U)
#define IO_MUX_PWM2                 ((uint32_t) 15U)
#define IO_MUX_PWM3                 ((uint32_t) 16U)
#define IO_MUX_PWM4                 ((uint32_t) 17U)
#define IO_MUX_PWM5                 ((uint32_t) 18U)
#define IO_MUX_df_ant_sw_0          ((uint32_t) 19U)
#define IO_MUX_df_ant_sw_1          ((uint32_t) 20U)
#define IO_MUX_df_ant_sw_2          ((uint32_t) 21U)
#define IO_MUX_df_ant_sw_3          ((uint32_t) 22U)
#define IO_MUX_df_ant_sw_4          ((uint32_t) 23U)
#define IO_MUX_df_ant_sw_5          ((uint32_t) 24U)
#define IO_MUX_df_ant_sw_6          ((uint32_t) 25U)
#define IO_MUX_ferp_gpio_trig_0     ((uint32_t) 26U)
#define IO_MUX_SWO                  ((uint32_t) 27U)
#define IO_MUX_coex_ble_rx          ((uint32_t) 28U)
#define IO_MUX_coex_ble_tx          ((uint32_t) 29U)
#define IO_MUX_coex_wlan_rx         ((uint32_t) 30U)
#define IO_MUX_coex_wlan_tx         ((uint32_t) 31U)
#define IO_MUX_coex_ble_in_process  ((uint32_t) 32U)
#define IO_MUX_SWD_CLK              ((uint32_t) 33U)
#define IO_MUX_SWD_DATA             ((uint32_t) 34U)
#define IO_MUX_reserve3             ((uint32_t) 35U)
#define IO_MUX_reserve4             ((uint32_t) 36U)
#define IO_MUX_reserve5             ((uint32_t) 37U)
#define IO_MUX_SPI_S_MOSI           ((uint32_t) 38U)
#define IO_MUX_SPI_S_CS_N           ((uint32_t) 39U)
#define IO_MUX_SPI_S_CLK            ((uint32_t) 40U)
#define IO_MUX_SPI_S_MISO           ((uint32_t) 41U)
#define IO_MUX_SPI_M_CLK            ((uint32_t) 42U)
#define IO_MUX_SPI_M_CS0_N          ((uint32_t) 43U)
#define IO_MUX_SPI_M_CS1_N          ((uint32_t) 44U)
#define IO_MUX_SPI_M_MISO           ((uint32_t) 45U)
#define IO_MUX_SPI_M_MOSI           ((uint32_t) 46U)
#define IO_MUX_DUAL_TIMER0_A        ((uint32_t) 49U)
#define IO_MUX_DUAL_TIMER0_B        ((uint32_t) 50U)
#define IO_MUX_DUAL_TIMER0_C        ((uint32_t) 51U)
#define IO_MUX_DUAL_TIMER1_A        ((uint32_t) 52U)
#define IO_MUX_DUAL_TIMER1_B        ((uint32_t) 53U)
#define IO_MUX_DUAL_TIMER1_C        ((uint32_t) 54U)
#define IO_MUX_BIT_MASK             ((uint32_t) 0xFFU)

/* ================================================================================================================= */
/* ================                        Processor and Core Peripheral Section                    ================ */
/* ================================================================================================================= */

/* ===================================  Start of section using anonymous unions  =================================== */

/* ======================  Configuration of the ARM Cortex-M4 Processor and Core Peripherals  ====================== */
#define __CM4_REV                 0x0001U   /* Core revision r0p1 */
#define __MPU_PRESENT             1         /* MPU present */
#define __VTOR_PRESENT            1         /* VTOR present */
#define __NVIC_PRIO_BITS          8         /* Number of Bits used for Priority Levels */
#define __Vendor_SysTickConfig    0         /* Set to 1 if different SysTick Config is used */
#define __FPU_PRESENT             1         /* FPU present */

#include "core_cm4.h"             /*      Cortex-M4 processor and core peripherals */
#include "system_gr533x.h"        /*      System Header */
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
  * @brief DMA
  */
#define DMA_REG(name)                   __IOM uint32_t name; __IOM uint32_t __pad_##name
/* DMA/Channel_x_Registers Registers */
typedef struct
{
    DMA_REG(SAR);                       /**< Source Address,                Address offset: 0x00 */
    DMA_REG(DAR);                       /**< Destination Address,           Address offset: 0x08 */
    __IOM uint32_t RESERVED0[2];        /**< Reserved,                      Address offset: 0x10 */
    __IOM uint32_t CTL_LO;              /**< Control Register Low,          Address offset: 0x18 */
    __IOM uint32_t CTL_HI;              /**< Control Register High,         Address offset: 0x1C */
    __IOM uint32_t RESERVED1[8];        /**< Reserved,                      Address offset: 0x20 */
    __IOM uint32_t CFG_LO;              /**< Configuration Register Low,    Address offset: 0x40 */
    __IOM uint32_t CFG_HI;              /**< Configuration Register High,   Address offset: 0x44 */
    __IOM uint32_t RESERVED2[4];        /**< Reserved,                      Address offset: 0x48 */
} DMA_CH_REGS;

/* DMA/Interrupt_Registers Registers */
typedef struct
{
    __IO uint32_t RAW_CH_EVT[10];       /**< Raw channel event,             Address offset: 0x00 */
    __I  uint32_t STATUS_CH_EVT[10];    /**< Status channel event,          Address offset: 0x28 */
    __IO uint32_t MASK_CH_EVT[10];      /**< Mask channel event,            Address offset: 0x50 */
    __O  uint32_t CLEAR_CH_EVT[10];     /**< Clear channel event,           Address offset: 0x78 */
    DMA_REG(STATUS_EVT);                /**< Status event,                  Address offset: 0xA0 */
} DMA_INT_REGS;

/* DMA/Software_Handshake_Registers Registers */
typedef struct
{
    DMA_REG(REQ_SRC);                   /**< Source Transaction Request,            Address offset: 0x00 */
    DMA_REG(REQ_DST);                   /**< Destination Transaction Request,       Address offset: 0x08 */
    DMA_REG(SGL_RQ_SRC);                /**< Source Single Transaction Request,     Address offset: 0x10 */
    DMA_REG(SGL_RQ_DST);                /**< Destination Single Transaction Request,Address offset: 0x18 */
    DMA_REG(LST_SRC);                   /**< Source Last Transaction Request,       Address offset: 0x20 */
    DMA_REG(LST_DST);                   /**< Destination Last Transaction Request,  Address offset: 0x28 */
} DMA_HS_REGS;

/* DMA/Miscellaneous_Registers Registers */
typedef struct
{
    DMA_REG(CFG);                       /**< DMA Configuration,             Address offset: 0x00 */
    DMA_REG(CH_EN);                     /**< DMA Channel Enable,            Address offset: 0x08 */
    DMA_REG(ID);                        /**< DMA ID,                        Address offset: 0x10 */
    DMA_REG(TEST);                      /**< DMA Test,                      Address offset: 0x18 */
    DMA_REG(LP_TIMEOUT);                /**< DMA Low Power Timeout,         Address offset: 0x20 */
} DMA_MISC_REGS;

typedef struct _dma_regs
{
    DMA_CH_REGS         CHANNEL[5];     /**< DMA_REG_CH register,           Address offset: 0x000 */
    __IOM uint32_t      RESERVED0[66];  /**< Reserved,                      Address offset: 0x1B8 */
    DMA_INT_REGS        EVENT;          /**< DMA_REG_INT register,          Address offset: 0x2C0 */
    DMA_HS_REGS         HANDSHAKE;      /**< DMA_REG_HS register,           Address offset: 0x368 */
    DMA_MISC_REGS       MISCELLANEOU;   /**< DMA_REG_MISC register,         Address offset: 0x398 */
} dma_regs_t;

/**
  * @brief DUAL_TIM
  */
typedef struct _dual_timer_regs
{
    __IOM uint32_t RELOAD;          /**< DUAL_TIM auto-reload register,                       Address offset: 0x00 */
    __IM  uint32_t VALUE;           /**< DUAL_TIM counter value register,                     Address offset: 0x04 */
    __IOM uint32_t CTRL;            /**< DUAL_TIM control register,                           Address offset: 0x08 */
    __OM  uint32_t INTCLR;          /**< DUAL_TIM interrupt status clear register,            Address offset: 0x0C */
    __IM  uint32_t RAW_INTSTAT;     /**< DUAL_TIM raw interrupt status register,              Address offset: 0x10 */
    __IM  uint32_t INTSTAT;         /**< DUAL_TIM interrupt status register,                  Address offset: 0x14 */
    __IOM uint32_t BG_LOAD;         /**< DUAL_TIM background-reload register,                 Address offset: 0x18 */
    __IOM uint32_t COUNT_A1IO;      /**< DUAL_TIM gpio A count 1 register,                    Address offset: 0x1C */
    __IOM uint32_t COUNT_A2IO;      /**< DUAL_TIM gpio A count 2 register,                    Address offset: 0x20 */
    __IOM uint32_t COUNT_B1IO;      /**< DUAL_TIM gpio B count 1 register,                    Address offset: 0x24 */
    __IOM uint32_t COUNT_B2IO;      /**< DUAL_TIM gpio B count 2 register,                    Address offset: 0x28 */
    __IOM uint32_t COUNT_C1IO;      /**< DUAL_TIM gpio C count 1 register,                    Address offset: 0x2C */
    __IOM uint32_t COUNT_C2IO;      /**< DUAL_TIM gpio C count 2 register,                    Address offset: 0x30 */
    __IOM uint32_t IO_ACT_CTRL;     /**< DUAL_TIM IO action control register,                 Address offset: 0x34 */
    __IOM uint32_t IO_INIT_SET;     /**< DUAL_TIM IO initial value register,                  Address offset: 0x38 */
    __IOM uint32_t TP_LOAD;         /**< DUAL_TIM one-time reload register,                   Address offset: 0x3C */
    __IOM uint32_t BLE_COUNT1;      /**< DUAL_TIM BLE conut value 1 register,                 Address offset: 0x40 */
    __IOM uint32_t BLE_COUNT2;      /**< DUAL_TIM BLE conut value 2 register,                 Address offset: 0x44 */
    __IOM uint32_t BLE_PULSEWIDTH;  /**< DUAL_TIM BLE pulse width register,                   Address offset: 0x48 */
    __IOM uint32_t PERIOD_COUNT;    /**< DUAL_TIM period count register,                      Address offset: 0x4C */
    __OM  uint32_t IO_BLE_INTCLR;   /**< DUAL_TIM IO and BLE interrupt status clear register, Address offset: 0x50 */
} dual_timer_regs_t;

/**
  * @brief GPIO
  */
typedef struct _gpio_regs
{
    __IOM uint32_t DATA;                /**< GPIO_REG_DATA register,            Address offset: 0x000 */
    __IOM uint32_t DATAOUT;             /**< GPIO_REG_DATAOUT register,         Address offset: 0x004 */
    __IM  uint32_t RESERVED0[2];        /**< GPIO_REG_RESERVED register,        Address offset: 0x008 */
    __IOM uint32_t OUTENSET;            /**< GPIO_REG_OUTENSET register,        Address offset: 0x010 */
    __IOM uint32_t OUTENCLR;            /**< GPIO_REG_OUTENCLR register,        Address offset: 0x014 */
    __IOM uint32_t ALTFUNCSET;          /**< GPIO_REG_ALTFUNCSET register,      Address offset: 0x018 */
    __IOM uint32_t ALTFUNCCLR;          /**< GPIO_REG_ALTFUNCCLR register,      Address offset: 0x01C */
    __IOM uint32_t INTENSET;            /**< GPIO_REG_INTENSET register,        Address offset: 0x020 */
    __IOM uint32_t INTENCLR;            /**< GPIO_REG_INTENCLR register,        Address offset: 0x024 */
    __IOM uint32_t INTTYPESET;          /**< GPIO_REG_INTTYPESET register,      Address offset: 0x028 */
    __IOM uint32_t INTTYPECLR;          /**< GPIO_REG_INTTYPECLR register,      Address offset: 0x02C */
    __IOM uint32_t INTPOLSET;           /**< GPIO_REG_INTPOLSET register,       Address offset: 0x030 */
    __IOM uint32_t INTPOLCLR;           /**< GPIO_REG_INTPOLCLR register,       Address offset: 0x034 */
    __IOM uint32_t INTSTAT;             /**< GPIO_REG_INTSTAT register,         Address offset: 0x038 */
    __IM  uint32_t RESERVED1;           /**< GPIO_REG_RESERVED register,        Address offset: 0x03C */
    __IOM uint32_t INTDBESET;           /**< GPIO_REG_INTDBESET register,       Address offset: 0x040 */
    __IOM uint32_t INTDBECLR;           /**< GPIO_REG_INTDBECLR register,       Address offset: 0x044 */
    __IM  uint32_t RESERVED2[238];      /**< GPIO_REG_RESERVED register,        Address offset: 0x048 */
    __IOM uint32_t MASKLOWBYTE[256];    /**< GPIO_REG_MASKLOWBYTE register,     Address offset: 0x400 */
    __IOM uint32_t MASKHIGHBYTE[256];   /**< GPIO_REG_MASKHIGHBYTE register,    Address offset: 0x500 */
} gpio_regs_t;

/**
  * @brief I2C
  */
typedef struct _i2c_regs
{
    __IOM uint32_t CTRL;                      /**< I2C Control Register,                                                 Address offset: 0x0000 */
    __IOM uint32_t TARGET_ADDR;               /**< I2C Target Address Register,                                          Address offset: 0x0004 */
    __IOM uint32_t S_ADDR;                    /**< I2C Slave Address Register,                                           Address offset: 0x0008 */
    __IOM uint32_t M_HS_ADDR;                 /**< I2C High-Speed Master Mode Code Address Register,                     Address offset: 0x000C */
    __IOM uint32_t DATA_CMD;                  /**< I2C RX/TX Data Buffer and Command Register,                           Address offset: 0x0010 */
    __IOM uint32_t SS_CLK_HCOUNT;             /**< Standard Speed I2C Clock SCL High Count Register,                     Address offset: 0x0014 */
    __IOM uint32_t SS_CLK_LCOUNT;             /**< Standard Speed I2C Clock SCL Low Count Register,                      Address offset: 0x0018 */
    __IOM uint32_t FS_CLK_HCOUNT;             /**< Fast Mode or Fast Mode Plus I2C Clock SCL High Count Register,        Address offset: 0x001C */
    __IOM uint32_t FS_CLK_LCOUNT;             /**< Fast Mode or Fast Mode Plus I2C Clock SCL Low Count Register,         Address offset: 0x0020 */
    __IOM uint32_t HS_CLK_HCOUNT;             /**< High Speed I2C Clock SCL High Count Register,                         Address offset: 0x0024 */
    __IOM uint32_t HS_CLK_LCOUNT;             /**< High Speed I2C Clock SCL Low Count Register,                          Address offset: 0x0028 */
    __IOM uint32_t INT_STAT;                  /**< I2C Interrupt Status Register,                                        Address offset: 0x002C */
    __IOM uint32_t INT_MASK;                  /**< I2C Interrupt Mask Register,                                          Address offset: 0x0030 */
    __IOM uint32_t RAW_INT_STAT;              /**< I2C Raw Interrupt Status Register,                                    Address offset: 0x0034 */
    __IOM uint32_t RX_FIFO_THD;               /**< I2C Receive FIFO Threshold Register,                                  Address offset: 0x0038 */
    __IOM uint32_t TX_FIFO_THD;               /**< I2C Transmit FIFO Threshold Register,                                 Address offset: 0x003C */
    __IOM uint32_t CLR_INT;                   /**< Clear Combined and Individual Interrupt Register,                     Address offset: 0x0040 */
    __IOM uint32_t CLR_RX_UNDER;              /**< Clear RX_UNDER Interrupt Register,                                    Address offset: 0x0044 */
    __IOM uint32_t CLR_RX_OVER;               /**< Clear RX_OVER Interrupt Register,                                     Address offset: 0x0048 */
    __IOM uint32_t CLR_TX_OVER;               /**< Clear TX_OVER Interrupt Register,                                     Address offset: 0x004C */
    __IOM uint32_t CLR_RD_REQ;                /**< Clear RD_REQ Interrupt Register,                                      Address offset: 0x0050 */
    __IOM uint32_t CLR_TX_ABORT;              /**< Clear TX_ABORT Interrupt Register,                                    Address offset: 0x0054 */
    __IOM uint32_t CLR_RX_DONE;               /**< Clear RX_DONE Interrupt Register,                                     Address offset: 0x0058 */
    __IOM uint32_t CLR_ACTIVITY;              /**< Clear ACTIVITY Interrupt Register,                                    Address offset: 0x005C */
    __IOM uint32_t CLR_STOP_DET;              /**< Clear STOP_DET Interrupt Register,                                    Address offset: 0x0060 */
    __IOM uint32_t CLR_START_DET;             /**< Clear START_DET Interrupt Register,                                   Address offset: 0x0064 */
    __IOM uint32_t CLR_GEN_CALL;              /**< Clear GEN_CALL Interrupt Register,                                    Address offset: 0x0068 */
    __IOM uint32_t EN;                        /**< I2C ENABLE Register,                                                  Address offset: 0x006C */
    __IOM uint32_t STAT;                      /**< I2C STATUS Register,                                                  Address offset: 0x0070 */
    __IOM uint32_t TX_FIFO_LEVEL;             /**< I2C Transmit FIFO Level Register,                                     Address offset: 0x0074 */
    __IOM uint32_t RX_FIFO_LEVEL;             /**< I2C Receive FIFO Level Register,                                      Address offset: 0x0078 */
    __IOM uint32_t SDA_HOLD;                  /**< I2C SDA Hold Time Length Register,                                    Address offset: 0x007C */
    __IOM uint32_t TX_ABORT_SRC;              /**< I2C SDA Hold Time Length Register,                                    Address offset: 0x0080 */
    __IOM uint32_t RESERVED0[1];              /**< RESERVED,                                                             Address offset: 0x0084 */
    __IOM uint32_t DMA_CTRL;                  /**< DMA Control Register,                                                 Address offset: 0x0088 */
    __IOM uint32_t DMA_TX_LEVEL;              /**< DMA Transmit Data Level Register,                                     Address offset: 0x008C */
    __IOM uint32_t DMA_RX_LEVEL;              /**< DMA Receive Data Level Register,                                      Address offset: 0x0090 */
    __IOM uint32_t SDA_SETUP;                 /**< I2C SDA Setup Register,                                               Address offset: 0x0094 */
    __IOM uint32_t ACK_GEN_CALL;              /**< I2C ACK General Call Register,                                        Address offset: 0x0098 */
    __IOM uint32_t EN_STAT;                   /**< I2C Enable Status Register,                                           Address offset: 0x009C */
    __IOM uint32_t FS_SPKLEN;                 /**< I2C SS, FS or FM+ spike suppression limit,                            Address offset: 0x00A0 */
    __IOM uint32_t HS_SPKLEN;                 /**< I2C HS spike suppression limit Register,                              Address offset: 0x00A4 */
    __IOM uint32_t RESERVED1[1];              /**< RESERVED,                                                             Address offset: 0x00A8 */
    __IOM uint32_t SCL_STUCK_TIMEOUT;         /**< I2C SCL Stuck at Low Timeout Register,                                Address offset: 0x00AC */
    __IOM uint32_t SDA_STUCK_TIMEOUT;         /**< I2C SDA Stuck at Low Timeout Register,                                Address offset: 0x00B0 */
    __IOM uint32_t CLR_SCL_STUCK_DET;         /**< Clear SCL Stuck at Low Detect interrupt Register,                     Address offset: 0x00B4 */
} i2c_regs_t;

/**
  * @brief MCU_SUB
  */
typedef struct _mcu_sub_regs
{
    __IOM uint32_t SENSE_ADC_FIFO;            /**< Sense ADC Read FIFO Register,                                         Address offset: 0x0000 */
    __IOM uint32_t SENSE_FF_THRESH;           /**< Sense ADC FIFO Threshold Register,                                    Address offset: 0x0004 */
    __IOM uint32_t SENSE_ADC_STAT;            /**< Sense ADC Status Register,                                            Address offset: 0x0008 */
    __IOM uint32_t SENSE_ADC_CLK;             /**< Sense ADC Clock Register,                                             Address offset: 0x000C */
    __IOM uint32_t RESERVED0[1];              /**< RESERVED,                                                             Address offset: 0x0010 */
    __IOM uint32_t SENSE_ADC_GET_TKN_HW;      /**< Sense ADC get token for Hardware Register,                            Address offset: 0x0014 */
    __IOM uint32_t SENSE_ADC_GET_TKN_SW;      /**< Sense ADC get token for software Register,                            Address offset: 0x0018 */
    __IOM uint32_t SENSE_ADC_RET_TKN_HW;      /**< Sense ADC release the HW token Register,                              Address offset: 0x001C */
    __OM  uint32_t SENSE_ADC_RET_TKN_SW;      /**< Sense ADC release the SW token Register,                              Address offset: 0x0020 */
    __IOM uint32_t SENSE_ADC_TKN_STS;         /**< Sense ADC Token Status Register,                                      Address offset: 0x0024 */
    __IOM uint32_t RESERVED1[6];              /**< RESERVED,                                                             Address offset: 0x0028 */
    __IOM uint32_t CTE_FIFO_DATA;             /**< CTE FIFO data Register,                                               Address offset: 0x0040 */
    __IOM uint32_t CTE_FIFO_THRESH;           /**< CTE FIFO threshold Register,                                          Address offset: 0x0044 */
    __IOM uint32_t CTE_FIFO_STAT;             /**< CTE FIFO status Register,                                             Address offset: 0x0048 */
    __IOM uint32_t CTE_CFG;                   /**< CTE Configure Register,                                               Address offset: 0x004C */
    __IOM uint32_t RESERVED2[117];            /**< RESERVED,                                                             Address offset: 0x0050 */
    __IOM uint32_t BLE_FERP_CTL;              /**< BLE ferp control register,                                            Address offset: 0x0224 */
    __IOM uint32_t RESERVED3[1];              /**< RESERVED,                                                             Address offset: 0x0228 */
    __IOM uint32_t SECURITY_RESET;            /**< Sercurity block reset control register,                               Address offset: 0x022C */
    __IOM uint32_t PMU_ID;                    /**< analog timing control Register ,                                      Address offset: 0x0230 */
    __IOM uint32_t PWR_AVG_CTL_REG0;          /**< power average block control registers,                                Address offset: 0x0234 */
    __IOM uint32_t TIMER2BLE_PLUSE_CTRL;      /**< RESERVED,                                                             Address offset: 0x0238 */
    __IOM uint32_t RESERVED4[6];              /**< RESERVED,                                                             Address offset: 0x023C */
    __IOM uint32_t EFUSE_PWR_DELTA_0;         /**< Efuse timing pararmeter register 0.,                                  Address offset: 0x0254 */
    __IOM uint32_t EFUSE_PWR_DELTA_1;         /**< Efuse timing pararmeter register 1.,                                  Address offset: 0x0258 */
    __IOM uint32_t RESERVED5[1];              /**< RESERVED,                                                             Address offset: 0x025C */
    __IOM uint32_t EFUSE_PWR_CTRL_0;          /**< Efuse power controller register 0,                                    Address offset: 0x0260 */
    __IOM uint32_t EFUSE_PWR_CTRL_1;          /**< Efuse power controller register 1,                                    Address offset: 0x0264 */
    __IOM uint32_t RESERVED6[5];              /**< RESERVED,                                                             Address offset: 0x0268 */
    __IOM uint32_t MCU_BOOT_DBG;              /**< MCU BOOT DBG register,                                                Address offset: 0x027C */
    __IOM uint32_t MCU_SUB_REG;               /**< MCU SUB register,                                                     Address offset: 0x0280 */
    __IOM uint32_t MCU_NMI_CFG;               /**< MCU NMI configure register,                                           Address offset: 0x0284 */
    __IOM uint32_t CPLL_IRQ_CFG;              /**< CPLL DRIFT IRQ configure register,                                    Address offset: 0x0288 */
    __IOM uint32_t AON_SW_RST;                /**< AON domain reset register,                                            Address offset: 0x028C */
    __IOM uint32_t RESERVED7[12];             /**< RESERVED,                                                             Address offset: 0x0290 */
    __IOM uint32_t MCU_SUBSYS_CG_CTRL[3];     /**< Automatic Turn off clock during WFI register ,                        Address offset: 0x02C0 */
    __IOM uint32_t MCU_PERIPH_PCLK_OFF;       /**< Force clock OFF register ,                                            Address offset: 0x02CC */
    __IOM uint32_t MCU_PERIPH_CG_LP_EN;       /**< Low Power feature control register ,                                  Address offset: 0x02D0 */
    __IOM uint32_t MCU_PERIPH_CLK_SLP_OFF;    /**< Turn the peripherals off during WFI/WFE register ,                    Address offset: 0x02D4 */
    __IOM uint32_t SECU_CLK_CTRL;             /**< Security block clock control  register,                               Address offset: 0x02D8 */
    __IOM uint32_t RESERVED8[3];              /**< RESERVED,                                                             Address offset: 0x02DC */
    __IOM uint32_t MCU_MISC_CLK;              /**< MCU MISC register,                                                    Address offset: 0x02E8 */
    __IOM uint32_t RESERVED9[2];              /**< RESERVED,                                                             Address offset: 0x02EC */
    __IOM uint32_t HFOSC_CLK_EN;              /**< PLL HFOSC CLK EN register,                                            Address offset: 0x02F4 */
    __IOM uint32_t RESERVED10[18];            /**< RESERVED,                                                             Address offset: 0x02F8 */
    __IOM uint32_t APB_TIMER_DBG;             /**< MCU APB Timer debug register,                                         Address offset: 0x0340 */
    __IOM uint32_t APB_MON_DBG;               /**< bypass the bus monitor in AHB-APB bridge register,                    Address offset: 0x0344 */
    __IOM uint32_t RESERVED11[14];            /**< RESERVED,                                                             Address offset: 0x0348 */
    __IOM uint32_t MCU_RELEASE;               /**< MCU release register,                                                 Address offset: 0x0380 */
    __IOM uint32_t FPGA_CTRL;                 /**< FPGA control register,                                                Address offset: 0x0384 */
    __IOM uint32_t ST_CALIB;                  /**< ST_CALIB register,                                                    Address offset: 0x0388 */
} mcu_sub_regs_t;

/**
  * @brief PWM
  */
typedef struct _pwm_regs
{
    __IOM uint32_t MODE;                   /**< PWM_REG_MODE,                                      Address, offset: 0x00 */
    __IOM uint32_t UPDATE;                 /**< PWM_REG_UPDATE,                                    Address, offset: 0x04 */
    __IOM uint32_t PRD;                    /**< PWM_REG_PRD,                                       Address, offset: 0x08 */
    __IOM uint32_t CMPA0;                  /**< PWM_REG_CMPA0,                                     Address, offset: 0x0C */
    __IOM uint32_t CMPA1;                  /**< PWM_REG_CMPA1,                                     Address, offset: 0x10 */
    __IOM uint32_t CMPB0;                  /**< PWM_REG_CMPB0,                                     Address, offset: 0x14 */
    __IOM uint32_t CMPB1;                  /**< PWM_REG_CMPB1,                                     Address, offset: 0x18 */
    __IOM uint32_t CMPC0;                  /**< PWM_REG_CMPC0,                                     Address, offset: 0x1C */
    __IOM uint32_t CMPC1;                  /**< PWM_REG_CMPC1,                                     Address, offset: 0x20 */
    __IOM uint32_t AQCTRL;                 /**< PWM_REG_AQCTRL,                                    Address, offset: 0x24 */
    __IOM uint32_t BRPRD;                  /**< PWM_REG_BRPRD,                                     Address, offset: 0x28 */
    __IOM uint32_t HOLD;                   /**< PWM_REG_HOLD,                                      Address, offset: 0x2C */
    __IOM uint32_t PRD_CYCLES;             /**< PWM_REG_PRD_CYCLES,                                Address, offset: 0x30 */
    __IOM uint32_t WAIT_TIME;              /**< PWM_REG_WAIT_TIME, only PWM0 can access,           Address, offset: 0x34 */
    __IOM uint32_t DATA_WIDTH_VALID;       /**< PWM_REG_DATA_WIDTH_VALID, only PWM0 can access,    Address, offset: 0x38 */
	__IOM uint32_t CODING_DATA;            /**< PWM_REG_CODING_DATA, only PWM0 can access,         Address, offset: 0x3C */
	__IM  uint32_t CODING_STATUS;          /**< PWM_REG_CODING_STATUS, only PWM0 can access,       Address, offset: 0x40 */
	__OM  uint32_t CLR_CODING_STATUS;      /**< PWM_REG_CLR_CODING_STATUS, only PWM0 can access,   Address, offset: 0x44 */
} pwm_regs_t;

/**
  * @brief SPI
  */
typedef struct _spi_regs
{
    __IOM uint32_t CTRL0;                     /**< SPI Control Register 0 ,                                              Address offset: 0x0000 */
    __IOM uint32_t CTRL1;                     /**< SPI Control Register 1,                                               Address offset: 0x0004 */
    __IOM uint32_t SSI_EN;                    /**< SSI Enable Register,                                                  Address offset: 0x0008 */
    __IOM uint32_t MW_CTRL;                   /**< Microwire Control Register,                                           Address offset: 0x000C */
    __IOM uint32_t S_EN;                      /**< Slave Enable Register,                                                Address offset: 0x0010 */
    __IOM uint32_t BAUD;                      /**< Baud Rate Register,                                                   Address offset: 0x0014 */
    __IOM uint32_t TX_FIFO_TL;                /**< Transmit FIFO Threshold Level Register,                               Address offset: 0x0018 */
    __IOM uint32_t RX_FIFO_TL;                /**< Receive FIFO Threshold Level,                                         Address offset: 0x001C */
    __IOM uint32_t TX_FIFO_LEVEL;             /**< Transmit FIFO Level Register,                                         Address offset: 0x0020 */
    __IOM uint32_t RX_FIFO_LEVEL;             /**< Receive FIFO Level Register ,                                         Address offset: 0x0024 */
    __IOM uint32_t STAT;                      /**< Status Register,                                                      Address offset: 0x0028 */
    __IOM uint32_t INT_MASK;                  /**< Interrupt Mask Register,                                              Address offset: 0x002C */
    __IOM uint32_t INT_STAT;                  /**< Interrupt Status Register ,                                           Address offset: 0x0030 */
    __IOM uint32_t RAW_INT_STAT;              /**< Raw Interrupt Status Register,                                        Address offset: 0x0034 */
    __IOM uint32_t TX_FIFO_OIC;               /**< Transmit FIFO Overflow Interrupt Clear Register,                      Address offset: 0x0038 */
    __IOM uint32_t RX_FIFO_OIC;               /**< Receive FIFO Overflow Interrupt Clear Register ,                      Address offset: 0x003C */
    __IOM uint32_t RX_FIFO_UIC;               /**< Receive FIFO Underflow Interrupt Clear Register ,                     Address offset: 0x0040 */
    __IOM uint32_t MULTI_M_IC;                /**< Multi-Master Interrupt Clear Register,                                Address offset: 0x0044 */
    __IOM uint32_t INT_CLR;                   /**< Interrupt Clear Register ,                                            Address offset: 0x0048 */
    __IOM uint32_t DMA_CTRL;                  /**< DMA Control Register ,                                                Address offset: 0x004C */
    __IOM uint32_t DMA_TX_DL;                 /**< DMA Transmit Data Level Register,                                     Address offset: 0x0050 */
    __IOM uint32_t DMA_RX_DL;                 /**< DMA Receive Data Level Register,                                      Address offset: 0x0054 */
    __IOM uint32_t RESERVED0[2];              /**< RESERVED,                                                             Address offset: 0x0058 */
    __IOM uint32_t DATA;                      /**< Data Register,                                                        Address offset: 0x0060 */
    __IM  uint32_t REVERSED[35];              /**< DATA Registers REVERSED,                                              Address offset: 0x0064 */
    __IOM uint32_t RX_SAMPLE_DLY;             /**< RX sample delay Register,                                             Address offset: 0x00F0 */
} spi_regs_t;

/**
  * @brief TIMER
  */
typedef struct _timer_regs
{
    __IOM uint32_t CTRL;            /**< TIM control register,                        Address offset: 0x00  */
    __IOM uint32_t VALUE;           /**< TIM counter value register,                  Address offset: 0x04  */
    __IOM uint32_t RELOAD;          /**< TIM auto-reload register,                    Address offset: 0x08  */
    __IOM uint32_t INTEN;           /**< TIM interrupt enable register,               Address offset: 0x0C  */
    __IOM uint32_t INTSTAT;         /**< TIM interrupt status register,               Address offset: 0x010 */
    __IOM uint32_t CHANNEL0_VAL;    /**< TIM channel0 capture value register,         Address offset: 0x014 */
    __IOM uint32_t CHANNEL1_VAL;    /**< TIM channel1 capture value register,         Address offset: 0x018 */
    __IOM uint32_t CHANNEL2_VAL;    /**< TIM channel2 capture value register,         Address offset: 0x01C */
    __IOM uint32_t CHANNEL3_VAL;    /**< TIM channel3 capture value register,         Address offset: 0x020 */
    __IOM uint32_t BLE_COUNTVAL1;   /**< TIM BLE count value1 register,               Address offset: 0x024 */
    __IOM uint32_t BLE_COUNTVAL2;   /**< TIM BLE count value2 register,               Address offset: 0x028 */
    __IOM uint32_t BLE_PULSEWIDTH;  /**< TIM BLE pulse width register,                Address offset: 0x02C */
} timer_regs_t;

/**
  * @brief UART
  */
typedef struct _uart_regs
{
    union
    {
        __IOM uint32_t RBR;
        __IOM uint32_t DLL;
        __IOM uint32_t THR;
    } RBR_DLL_THR;                  /**< UART_REG_RBR_DLL_THR,  Address offset: 0x00 */
    union
    {
        __IOM uint32_t DLH;
        __IOM uint32_t IER;
    } DLH_IER;                      /**< UART_REG_DLH_IER,      Address offset: 0x04 */
    union
    {
        __IOM uint32_t FCR;
        __IOM uint32_t IIR;
    } FCR_IIR;                      /**< UART_REG_FCR_IIR,      Address offset: 0x08 */
    __IOM uint32_t LCR;             /**< UART_REG_LCR,          Address offset: 0x0C */
    __IOM uint32_t MCR;             /**< UART_REG_MCR,          Address offset: 0x10 */
    __IOM uint32_t LSR;             /**< UART_REG_LSR,          Address offset: 0x14 */
    __IOM uint32_t MSR;             /**< UART_REG_MSR,          Address offset: 0x18 */
    __IOM uint32_t SCRATCHPAD;      /**< UART_REG_SCRATCHPAD,   Address offset: 0x1C */
    __IOM uint32_t LPDLL;           /**< UART_REG_LPDLL,        Address offset: 0x20 */
    __IOM uint32_t LPDLH;           /**< UART_REG_LPDLH,        Address offset: 0x24 */
    __IOM uint32_t REVERSED0[2];    /**< REVERSED,              Address offset: 0x28 */
    union
    {
        __IOM uint32_t SRBR[16];
        __IOM uint32_t STHR[16];
    } SRBR_STHR;                    /**< UART_REG_SRBR_STHR,    Address offset: 0x30 */
    __IOM uint32_t FAR;             /**< UART_REG_FAR,          Address offset: 0x70 */
    __IOM uint32_t TFR;             /**< UART_REG_TFR,          Address offset: 0x74 */
    __IOM uint32_t TFW;             /**< UART_REG_TFW,          Address offset: 0x78 */
    __IOM uint32_t USR;             /**< UART_REG_USR,          Address offset: 0x7C */
    __IOM uint32_t TFL;             /**< UART_REG_TFL,          Address offset: 0x80 */
    __IOM uint32_t RFL;             /**< UART_REG_RFL,          Address offset: 0x84 */
    __IOM uint32_t SRR;             /**< UART_REG_SRR,          Address offset: 0x88 */
    __IOM uint32_t SRTS;            /**< UART_REG_SRTS,         Address offset: 0x8C */
    __IOM uint32_t SBCR;            /**< UART_REG_SBCR,         Address offset: 0x90 */
    __IOM uint32_t SDMAM;           /**< UART_REG_SDMAM,        Address offset: 0x94 */
    __IOM uint32_t SFE;             /**< UART_REG_SFE,          Address offset: 0x98 */
    __IOM uint32_t SRT;             /**< UART_REG_SRT,          Address offset: 0x9C */
    __IOM uint32_t STET;            /**< UART_REG_STET,         Address offset: 0xA0 */
    __IOM uint32_t HTX;             /**< UART_REG_HTX,          Address offset: 0xA4 */
    __IOM uint32_t DMASA;           /**< UART_REG_DMASA,        Address offset: 0xA8 */
    __IOM uint32_t TCR;             /**< UART_REG_TCR,          Address offset: 0xAC */
    __IOM uint32_t DE_EN;           /**< UART_REG_DE_EN,        Address offset: 0xB0 */
    __IOM uint32_t RE_EN;           /**< UART_REG_RE_EN,        Address offset: 0xB4 */
    __IOM uint32_t DET;             /**< UART_REG_DET,          Address offset: 0xB8 */
    __IOM uint32_t TAT;             /**< UART_REG_TAT,          Address offset: 0xBC */
    __IOM uint32_t DLF;             /**< UART_REG_DLF,          Address offset: 0xC0 */
    __IOM uint32_t RAR;             /**< UART_REG_RAR,          Address offset: 0xC4 */
    __IOM uint32_t TAR;             /**< UART_REG_TAR,          Address offset: 0xC8 */
    __IOM uint32_t LCR_EXT;         /**< UART_REG_LCR_EXT,      Address offset: 0xCC */
    __IOM uint32_t REVERSED1[9];    /**< REVERSED,              Address offset: 0xD0 */
    __IOM uint32_t CPR;             /**< UART_REG_CPR,          Address offset: 0xF4 */
    __IOM uint32_t UCV;             /**< UART_REG_UCV,          Address offset: 0xF8 */
    __IOM uint32_t CTR;             /**< UART_REG_CTR,          Address offset: 0xFC */
} uart_regs_t;

/**
  * @brief WDT
  */
typedef struct _wdt_regs
{
    __IOM uint32_t LOAD;            /**< WDT_REG_LOAD,          Address offset: 0x000 */
    __IOM uint32_t VALUE;           /**< WDT_REG_VALUE,         Address offset: 0x004 */
    __IOM uint32_t CTRL;            /**< WDT_REG_CONTROL,       Address offset: 0x008 */
    __IOM uint32_t INTCLR;          /**< WDT_REG_INTCLR,        Address offset: 0x00C */
    __IOM uint32_t RIS;             /**< WDT_REG_RIS,           Address offset: 0x010 */
    __IOM uint32_t MIS;             /**< WDT_REG_MIS,           Address offset: 0x014 */
    __IOM uint32_t REVERSED[762];   /**< REVERSED,              Address offset: 0x018 */
    __IOM uint32_t LOCK;            /**< WDT_REG_LOCK,          Address offset: 0xC00 */
} wdt_regs_t;

/**
  * @brief XQSPI
  */
/* XQSPI/Cache Registers */
typedef struct
{
    __IOM uint32_t CTRL0;               /**< Cache Control 0 Register,  Address offset: 0x00 */
    __IOM uint32_t CTRL1;               /**< Cache Control 1 Register,  Address offset: 0x04 */
    __IM  uint32_t HIT_COUNT;           /**< Cache hits count,          Address offset: 0x08 */
    __IM  uint32_t MISS_COUNT;          /**< Cache miss count,          Address offset: 0x0C */
    __IM  uint32_t STAT;                /**< Status Register,           Address offset: 0x10 */
    __IOM uint32_t BUF_FIRST_ADDR;      /**< Preload start address,     Address offset: 0x14 */
    __IOM uint32_t BUF_LAST_ADDR;       /**< Preload last address,      Address offset: 0x18 */
} CACHE_REGS;

/* XQSPI/QSPI Registers */
typedef struct
{
    __OM  uint32_t TX_DATA;             /**< Serial Data Transmit,         Address offset: 0x00 */
    __IM  uint32_t RX_DATA;             /**< Serial Data Receive,          Address offset: 0x04 */
    __IM  uint32_t RESERVED0;           /**< RESERVED,                     Address offset: 0x08 */
    __IOM uint32_t CTRL;                /**< Control,                      Address offset: 0x0C */
    __IOM uint32_t AUX_CTRL;            /**< Auxiliary Control,            Address offset: 0x10 */
    __IM  uint32_t STAT;                /**< Status Control,               Address offset: 0x14 */
    __IOM uint32_t SLAVE_SEL;           /**< Slave Select,                 Address offset: 0x18 */
    __IOM uint32_t SLAVE_SEL_POL;       /**< Slave Select Polarity,        Address offset: 0x1C */
    __IOM uint32_t INTEN;               /**< Interrupt Enable,             Address offset: 0x20 */
    __IM  uint32_t INTSTAT;             /**< Interrupt Status,             Address offset: 0x24 */
    __OM  uint32_t INTCLR;              /**< Interrupt Clear,              Address offset: 0x28 */
    __IM  uint32_t TX_FIFO_LVL;         /**< TX FIFO Level,                Address offset: 0x2C */
    __IM  uint32_t RX_FIFO_LVL;         /**< RX FIFO Level,                Address offset: 0x30 */
    __IM  uint32_t RESERVED1;           /**< RESERVED,                     Address offset: 0x34 */
    __IOM uint32_t MSTR_IT_DELAY;       /**< Master Inter-transfer Delay,  Address offset: 0x38 */
    __IOM uint32_t SPIEN;               /**< SPI Enable,                   Address offset: 0x3C */
    __IOM uint32_t SPI_GP_SET;          /**< GPO Set / GPO State,          Address offset: 0x40 */
    __IOM uint32_t SPI_GP_CLEAR;        /**< GPO Clear / GPI State,        Address offset: 0x44 */
    __IM  uint32_t RX_DATA0_31;         /**< 32-bit LSB word(0~31),        Address offset: 0x48 */
    __IM  uint32_t RX_DATA32_63;        /**< 32-bit LSB word(32~63),       Address offset: 0x4C */
    __IM  uint32_t RX_DATA64_95;        /**< 32-bit LSB word(64~95),       Address offset: 0x50 */
    __IM  uint32_t RX_DATA96_127;       /**< 32-bit MSB word(96~127),      Address offset: 0x54 */
    __OM  uint32_t P_IV;                /**< 32-BIT IV Key,                Address offset: 0x58 */
    __IOM uint32_t FLASH_WRITE;         /**< use for flash write,          Address offset: 0x5C */
    __IM  uint32_t RESERVED2[6];
    __IOM uint32_t CS_IDLE_UNVLD_EN;    /**< enable cs idle invalid,       Address offset: 0x78 */
} QSPI_REGS;

/* XQSPI/XIP Registers */
typedef struct
{
    __IOM uint32_t CTRL0;               /**< XIP Control 0 Register,       Address offset: 0x00 */
    __IOM uint32_t CTRL1;               /**< XIP Control 1 Register,       Address offset: 0x04 */
    __IOM uint32_t CTRL2;               /**< XIP Control 2 Register,       Address offset: 0x08 */
    __IOM uint32_t CTRL3;               /**< XIP Enable Request,           Address offset: 0x0C */
    __IOM uint32_t STAT;                /**< XIP Enable Output (Stat0),    Address offset: 0x10 */
    __IM  uint32_t INTEN;               /**< Interrupt Enable  (Intr0),    Address offset: 0x14 */
    __IM  uint32_t INTSTAT;             /**< Interrupt Status  (Intr1),    Address offset: 0x18 */
    __IM  uint32_t INTREQ;              /**< Interrupt Status  (Intr2),    Address offset: 0x1C */
    __OM  uint32_t INTSET;              /**< Interrupt Set     (Intr3),    Address offset: 0x20 */
    __OM  uint32_t INTCLR;              /**< Interrupt Clear   (Intr4),    Address offset: 0x24 */
    __IOM uint32_t SOFT_RST;            /**< XIP Control Software Reset,   Address offset: 0x28 */
} XIP_REGS;

typedef struct _xqspi_regs
{
    CACHE_REGS      CACHE;              /**< CACHE Registers,              Address offset: 0x000 */
    __IM  uint32_t  RESERVED0[249];
    QSPI_REGS       QSPI;               /**< QSPI Registers,               Address offset: 0x400 */
    __IM  uint32_t  RESERVED1[481];
    XIP_REGS        XIP;                /**< XIP Registers,                Address offset: 0xC00 */
} xqspi_regs_t;

/**
  * @brief EFUSE
  */
typedef struct _efuse_regs
{
    __IOM uint32_t TPGM;                /**< EFUSE_TPGM,                   Address offset: 0x000 */
    __IOM uint32_t PGENB;               /**< EFUSE_PGENB,                  Address offset: 0x004 */
    __OM  uint32_t OPERATION;           /**< EFUSE_OPERATION,              Address offset: 0x008 */
    __IM  uint32_t STAT;                /**< EFUSE_STATUS,                 Address offset: 0x00C */
} efuse_regs_t;

/**
  * @brief RNG
  */
typedef struct _rng_regs
{
    __IOM uint32_t CTRL;                /**< RNG_CTRL,                     Address offset: 0x000 */
    __IOM uint32_t STATUS;              /**< RNG_STATUS,                   Address offset: 0x004 */
    __IM  uint32_t DATA;                /**< RNG_DATA,                     Address offset: 0x008 */
    __IOM uint32_t RESERVED;            /**< RESERVED,                     Address offset: 0x00C */
    __IM  uint32_t LR_STATUS;           /**< RNG_LR_STATUS,                Address offset: 0x010 */
    __IOM uint32_t CONFIG;              /**< RNG_CONFIG,                   Address offset: 0x014 */
    __IOM uint32_t TSCON;               /**< RNG_TSCON,                    Address offset: 0x018 */
    __IOM uint32_t FROCFG;              /**< RNG_FROCFG,                   Address offset: 0x01C */
    __OM  uint32_t USER_SEED;           /**< RNG_USER_SEED,                Address offset: 0x020 */
    __IOM uint32_t LRCON;               /**< RNG_LRCON,                    Address offset: 0x024 */
} rng_regs_t;

/**
  * @brief SADC
  */
typedef struct _sadc_regs
{
    __IM  uint32_t FIFO_RD;                   /**< Sense ADC Read FIFO Register,                                         Address offset: 0x0000 */
    __IOM uint32_t FIFO_THD;                  /**< Sense ADC FIFO Threshold Register,                                    Address offset: 0x0004 */
    __IOM uint32_t FIFO_STAT;                 /**< Sense ADC Status Register,                                            Address offset: 0x0008 */
    __IOM uint32_t CLK;                       /**< Sense ADC Clock Register,                                             Address offset: 0x000C */
    __IOM uint32_t RESERVED0[1];              /**< RESERVED,                                                             Address offset: 0x0010 */
    __IOM uint32_t GET_TKN_HW;                /**< Sense ADC get token for Hardware Register,                            Address offset: 0x0014 */
    __IOM uint32_t GET_TKN_SW;                /**< Sense ADC get token for software Register,                            Address offset: 0x0018 */
    __IOM uint32_t RET_TKN_HW;                /**< Sense ADC release the HW token Register,                              Address offset: 0x001C */
    __OM  uint32_t RET_TKN_SW;                /**< Sense ADC release the SW token Register,                              Address offset: 0x0020 */
    __IOM uint32_t TKN_STAT;                  /**< Sense ADC Token Status Register,                                      Address offset: 0x0024 */
} sadc_regs_t;

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

#define ROM_BASE                ((uint32_t)0x00000000UL)
#define FLASH_BASE              ((uint32_t)0x00200000UL)
#define SRAM_BASE               ((uint32_t)0x20000000UL)
#define PERIPH_BASE             ((uint32_t)0x40000000UL)
#define PERIPH_QSPI_XIP_BASE    ((uint32_t)0xA0000000UL)

#define TIMER0_BASE             (PERIPH_BASE + 0x00000000UL)
#define TIMER1_BASE             (PERIPH_BASE + 0x00001000UL)
#define DUAL_TIM0_BASE          (PERIPH_BASE + 0x00002000UL)
#define DUAL_TIM1_BASE          (PERIPH_BASE + 0x00002080UL)
#define WDT_BASE                (PERIPH_BASE + 0x00008000UL)
#define SPIM_BASE               (PERIPH_BASE + 0x0000C000UL)
#define SPIS_BASE               (PERIPH_BASE + 0x0000C100UL)
#define I2C0_BASE               (PERIPH_BASE + 0x0000C300UL)
#define I2C1_BASE               (PERIPH_BASE + 0x0000C400UL)
#define UART0_BASE              (PERIPH_BASE + 0x0000C500UL)
#define UART1_BASE              (PERIPH_BASE + 0x0000C600UL)
#define PWM0_BASE               (PERIPH_BASE + 0x0000CB00UL)
#define PWM1_BASE               (PERIPH_BASE + 0x0000CC00UL)
#define XQSPI_BASE              (PERIPH_BASE + 0x0000D000UL)
#define GPIO0_BASE              (PERIPH_BASE + 0x00010000UL)
#define GPIO1_BASE              (PERIPH_BASE + 0x00011000UL)
#define GPIO2_BASE              (PERIPH_BASE + 0x00012000UL)
#define DMA0_BASE               (PERIPH_BASE + 0x00014000UL)

#define EFUSE_BASE              (PERIPH_BASE + 0x00018400UL)
#define RNG_BASE                (PERIPH_BASE + 0x00019000UL)

#define QSPI0_XIP_BASE          (PERIPH_QSPI_XIP_BASE + 0x0C000000UL)
#define QSPI1_XIP_BASE          (PERIPH_QSPI_XIP_BASE + 0x08000000UL)
#define QSPI2_XIP_BASE          (PERIPH_QSPI_XIP_BASE + 0x04000000UL)

#define KRAM_BASE               (PERIPH_BASE + 0x00017000UL)
#define EFUSE_STORAGE_BASE      (PERIPH_BASE + 0x00018000UL)
//#define GPADC_BASE              (PERIPH_BASE + 0x0000F800UL)
#define SADC_BASE               (PERIPH_BASE + 0x0000E000UL)

/** @} */ /* End of group Peripheral_memory_map */


/* ================================================================================================================= */
/* ================                             Peripheral declaration                              ================ */
/* ================================================================================================================= */

/** @addtogroup Peripheral_declaration
  * @{
  */

#define TIMER0                  ((timer_regs_t *)TIMER0_BASE)
#define TIMER1                  ((timer_regs_t *)TIMER1_BASE)
#define DUAL_TIMER0             ((dual_timer_regs_t *)DUAL_TIM0_BASE)
#define DUAL_TIMER1             ((dual_timer_regs_t *)DUAL_TIM1_BASE)
#define WDT                     ((wdt_regs_t *)WDT_BASE)
#define SPIM                    ((spi_regs_t *)SPIM_BASE)
#define SPIS                    ((spi_regs_t *)SPIS_BASE)
#define I2C0                    ((i2c_regs_t *)I2C0_BASE)
#define I2C1                    ((i2c_regs_t *)I2C1_BASE)
#define UART0                   ((uart_regs_t *)UART0_BASE)
#define UART1                   ((uart_regs_t *)UART1_BASE)
#define PWM0                    ((pwm_regs_t *)PWM0_BASE)
#define PWM1                    ((pwm_regs_t *)PWM1_BASE)
#define XQSPI                   ((xqspi_regs_t *)XQSPI_BASE)
#define GPIO0                   ((gpio_regs_t *)GPIO0_BASE)
#define GPIO1                   ((gpio_regs_t *)GPIO1_BASE)
#define GPIO2                   ((gpio_regs_t *)GPIO2_BASE)
#define DMA0                    ((dma_regs_t *)DMA0_BASE)
#define EFUSE                   ((efuse_regs_t *)EFUSE_BASE)
#define RNG                     ((rng_regs_t *)RNG_BASE)

/** @} */ /* End of group Peripheral_declaration */

/** @addtogroup Peripheral_Registers_Bits_Definition
  * @{
  */

/* ================================================================================================================= */
/* ================                                        AES                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for AES_CTRL register  *******************/
#define AES_CTRL_MODULE_EN_POS                              (0U)
#define AES_CTRL_MODULE_EN_Len                              (1U)
#define AES_CTRL_MODULE_EN_Msk                              (0x1UL << AES_CTRL_MODULE_EN_POS)
#define AES_CTRL_MODULE_EN                                  AES_CTRL_MODULE_EN_Msk

#define AES_CTRL_MCU_MODE_EN_POS                            (1U)
#define AES_CTRL_MCU_MODE_EN_Len                            (1U)
#define AES_CTRL_MCU_MODE_EN_Msk                            (0x1UL << AES_CTRL_MCU_MODE_EN_POS)
#define AES_CTRL_MCU_MODE_EN                                AES_CTRL_MCU_MODE_EN_Msk

#define AES_CTRL_DMA_MODE_EN_POS                            (2U)
#define AES_CTRL_DMA_MODE_EN_Len                            (1U)
#define AES_CTRL_DMA_MODE_EN_Msk                            (0x1UL << AES_CTRL_DMA_MODE_EN_POS)
#define AES_CTRL_DMA_MODE_EN                                AES_CTRL_DMA_MODE_EN_Msk

#define AES_CTRL_FKEY_EN_POS                                (3U)
#define AES_CTRL_FKEY_EN_Len                                (1U)
#define AES_CTRL_FKEY_EN_Msk                                (0x1UL << AES_CTRL_FKEY_EN_POS)
#define AES_CTRL_FKEY_EN                                    AES_CTRL_FKEY_EN_Msk

/*******************  Bit definition for AES_CFG register  *******************/
#define AES_CFG_KEY_MODE_POS                                (0U)
#define AES_CFG_KEY_MODE_Len                                (2U)
#define AES_CFG_KEY_MODE_Msk                                (0x3UL << AES_CFG_KEY_MODE_POS)
#define AES_CFG_KEY_MODE                                    AES_CFG_KEY_MODE_Msk

#define AES_CFG_FULL_MASK_EN_POS                            (3U)
#define AES_CFG_FULL_MASK_EN_Len                            (1U)
#define AES_CFG_FULL_MASK_EN_Msk                            (0x1UL << AES_CFG_FULL_MASK_EN_POS)
#define AES_CFG_FULL_MASK_EN                                AES_CFG_FULL_MASK_EN_Msk

#define AES_CFG_DEC_ENC_SEL_POS                             (4U)
#define AES_CFG_DEC_ENC_SEL_Len                             (1U)
#define AES_CFG_DEC_ENC_SEL_Msk                             (0x1UL << AES_CFG_DEC_ENC_SEL_POS)
#define AES_CFG_DEC_ENC_SEL                                 AES_CFG_DEC_ENC_SEL_Msk

#define AES_CFG_LOAD_SEED_POS                               (5U)
#define AES_CFG_LOAD_SEED_Len                               (1U)
#define AES_CFG_LOAD_SEED_Msk                               (0x1UL << AES_CFG_LOAD_SEED_POS)
#define AES_CFG_LOAD_SEED                                   AES_CFG_LOAD_SEED_Msk

#define AES_CFG_FIRST_BLK_POS                               (6U)
#define AES_CFG_FIRST_BLK_Len                               (1U)
#define AES_CFG_FIRST_BLK_Msk                               (0x1UL << AES_CFG_FIRST_BLK_POS)
#define AES_CFG_FIRST_BLK                                   AES_CFG_FIRST_BLK_Msk

#define AES_CFG_ENDIAN_POS                                  (7U)
#define AES_CFG_ENDIAN_Len                                  (1U)
#define AES_CFG_ENDIAN_Msk                                  (0x1UL << AES_CFG_ENDIAN_POS)
#define AES_CFG_ENDIAN                                      AES_CFG_ENDIAN_Msk

#define AES_CFG_OPT_MODE_POS                                (8U)
#define AES_CFG_OPT_MODE_Len                                (3U)
#define AES_CFG_OPT_MODE_Msk                                (0x7UL << AES_CFG_OPT_MODE_POS)
#define AES_CFG_OPT_MODE                                    AES_CFG_OPT_MODE_Msk

#define AES_CFG_KEY_TYPE_POS                                (11U)
#define AES_CFG_KEY_TYPE_Len                                (2U)
#define AES_CFG_KEY_TYPE_Msk                                (0x3UL << AES_CFG_KEY_TYPE_POS)
#define AES_CFG_KEY_TYPE                                    AES_CFG_KEY_TYPE_Msk

/*******************  Bit definition for AES_STAT register  *******************/
#define AES_STAT_READY_POS                                  (0U)
#define AES_STAT_READY_Len                                  (1U)
#define AES_STAT_READY_Msk                                  (0x1UL << AES_STAT_READY_POS)
#define AES_STAT_READY                                      AES_STAT_READY_Msk

#define AES_STAT_DMA_XFE_CPLT_POS                           (1U)
#define AES_STAT_DMA_XFE_CPLT_Len                           (1U)
#define AES_STAT_DMA_XFE_CPLT_Msk                           (0x1UL << AES_STAT_DMA_XFE_CPLT_POS)
#define AES_STAT_DMA_XFE_CPLT                               AES_STAT_DMA_XFE_CPLT_Msk

#define AES_STAT_DMA_XFE_ERR_POS                            (2U)
#define AES_STAT_DMA_XFE_ERR_Len                            (1U)
#define AES_STAT_DMA_XFE_ERR_Msk                            (0x1UL << AES_STAT_DMA_XFE_ERR_POS)
#define AES_STAT_DMA_XFE_ERR                                AES_STAT_DMA_XFE_ERR_Msk

#define AES_STAT_KEY_STAT_POS                               (3U)
#define AES_STAT_KEY_STAT_Len                               (1U)
#define AES_STAT_KEY_STAT_Msk                               (0x1UL << AES_STAT_KEY_STAT_POS)
#define AES_STAT_KEY_STAT                                   AES_STAT_KEY_STAT_Msk

/*******************  Bit definition for AES_INT register  *******************/
#define AES_INT_CPLT_INT_FLAG_POS                           (0U)
#define AES_INT_CPLT_INT_FLAG_Len                           (1U)
#define AES_INT_CPLT_INT_FLAG_Msk                           (0x1UL << AES_INT_CPLT_INT_FLAG_POS)
#define AES_INT_CPLT_INT_FLAG                               AES_INT_CPLT_INT_FLAG_Msk

#define AES_INT_CPLT_INT_EN_POS                             (1U)
#define AES_INT_CPLT_INT_EN_Len                             (1U)
#define AES_INT_CPLT_INT_EN_Msk                             (0x1UL << AES_INT_CPLT_INT_EN_POS)
#define AES_INT_CPLT_INT_EN                                 AES_INT_CPLT_INT_EN_Msk

/*******************  Bit definition for AES_XFE_SIZE register  *******************/
#define AES_XFE_SIZE_SIZE_POS                               (0U)
#define AES_XFE_SIZE_SIZE_Len                               (15U)
#define AES_XFE_SIZE_SIZE_Msk                               (0x7FFFUL << AES_XFE_SIZE_SIZE_POS)
#define AES_XFE_SIZE_SIZE                                   AES_XFE_SIZE_SIZE_Msk

/*******************  Bit definition for AES_RD_START_ADDR register  *******************/
#define AES_RD_START_ADDR_ADDR_POS                          (0U)
#define AES_RD_START_ADDR_ADDR_Len                          (32U)
#define AES_RD_START_ADDR_ADDR_Msk                          (0xFFFFFFFFUL << AES_RD_START_ADDR_ADDR_POS)
#define AES_RD_START_ADDR_ADDR                              AES_RD_START_ADDR_ADDR_Msk

/*******************  Bit definition for AES_WR_START_ADDR register  *******************/
#define AES_WR_START_ADDR_ADDR_POS                          (0U)
#define AES_WR_START_ADDR_ADDR_Len                          (32U)
#define AES_WR_START_ADDR_ADDR_Msk                          (0xFFFFFFFFUL << AES_WR_START_ADDR_ADDR_POS)
#define AES_WR_START_ADDR_ADDR                              AES_WR_START_ADDR_ADDR_Msk

/*******************  Bit definition for AES_KEY_ADDR register  *******************/
#define AES_KEY_ADDR_ADDR_POS                               (0U)
#define AES_KEY_ADDR_ADDR_Len                               (32U)
#define AES_KEY_ADDR_ADDR_Msk                               (0xFFFFFFFFUL << AES_KEY_ADDR_ADDR_POS)
#define AES_KEY_ADDR_ADDR                                   AES_KEY_ADDR_ADDR_Msk

/*******************  Bit definition for AES_DATA_OUT0 register  *******************/
#define AES_DATA_OUT0_DATA_OUT0_POS                         (0U)
#define AES_DATA_OUT0_DATA_OUT0_Len                         (32U)
#define AES_DATA_OUT0_DATA_OUT0_Msk                         (0xFFFFFFFFUL << AES_DATA_OUT0_DATA_OUT0_POS)
#define AES_DATA_OUT0_DATA_OUT0                             AES_DATA_OUT0_DATA_OUT0_Msk

/*******************  Bit definition for AES_DATA_OUT1 register  *******************/
#define AES_DATA_OUT1_DATA_OUT1_POS                         (0U)
#define AES_DATA_OUT1_DATA_OUT1_Len                         (32U)
#define AES_DATA_OUT1_DATA_OUT1_Msk                         (0xFFFFFFFFUL << AES_DATA_OUT1_DATA_OUT1_POS)
#define AES_DATA_OUT1_DATA_OUT1                             AES_DATA_OUT1_DATA_OUT1_Msk

/*******************  Bit definition for AES_DATA_OUT2 register  *******************/
#define AES_DATA_OUT2_DATA_OUT2_POS                         (0U)
#define AES_DATA_OUT2_DATA_OUT2_Len                         (32U)
#define AES_DATA_OUT2_DATA_OUT2_Msk                         (0xFFFFFFFFUL << AES_DATA_OUT2_DATA_OUT2_POS)
#define AES_DATA_OUT2_DATA_OUT2                             AES_DATA_OUT2_DATA_OUT2_Msk

/*******************  Bit definition for AES_DATA_OUT3 register  *******************/
#define AES_DATA_OUT3_DATA_OUT3_POS                         (0U)
#define AES_DATA_OUT3_DATA_OUT3_Len                         (32U)
#define AES_DATA_OUT3_DATA_OUT3_Msk                         (0xFFFFFFFFUL << AES_DATA_OUT3_DATA_OUT3_POS)
#define AES_DATA_OUT3_DATA_OUT3                             AES_DATA_OUT3_DATA_OUT3_Msk

/*******************  Bit definition for AES_KEY0 register  *******************/
#define AES_KEY0_KEY0_POS                                   (0U)
#define AES_KEY0_KEY0_Len                                   (32U)
#define AES_KEY0_KEY0_Msk                                   (0xFFFFFFFFUL << AES_KEY0_KEY0_POS)
#define AES_KEY0_KEY0                                       AES_KEY0_KEY0_Msk

/*******************  Bit definition for AES_KEY1 register  *******************/
#define AES_KEY1_KEY1_POS                                   (0U)
#define AES_KEY1_KEY1_Len                                   (32U)
#define AES_KEY1_KEY1_Msk                                   (0xFFFFFFFFUL << AES_KEY1_KEY1_POS)
#define AES_KEY1_KEY1                                       AES_KEY1_KEY1_Msk

/*******************  Bit definition for AES_KEY2 register  *******************/
#define AES_KEY2_KEY2_POS                                   (0U)
#define AES_KEY2_KEY2_Len                                   (32U)
#define AES_KEY2_KEY2_Msk                                   (0xFFFFFFFFUL << AES_KEY2_KEY2_POS)
#define AES_KEY2_KEY2                                       AES_KEY2_KEY2_Msk

/*******************  Bit definition for AES_KEY3 register  *******************/
#define AES_KEY3_KEY3_POS                                   (0U)
#define AES_KEY3_KEY3_Len                                   (32U)
#define AES_KEY3_KEY3_Msk                                   (0xFFFFFFFFUL << AES_KEY3_KEY3_POS)
#define AES_KEY3_KEY3                                       AES_KEY3_KEY3_Msk

/*******************  Bit definition for AES_KEY4 register  *******************/
#define AES_KEY4_KEY4_POS                                   (0U)
#define AES_KEY4_KEY4_Len                                   (32U)
#define AES_KEY4_KEY4_Msk                                   (0xFFFFFFFFUL << AES_KEY4_KEY4_POS)
#define AES_KEY4_KEY4                                       AES_KEY4_KEY4_Msk

/*******************  Bit definition for AES_KEY5 register  *******************/
#define AES_KEY5_KEY5_POS                                   (0U)
#define AES_KEY5_KEY5_Len                                   (32U)
#define AES_KEY5_KEY5_Msk                                   (0xFFFFFFFFUL << AES_KEY5_KEY5_POS)
#define AES_KEY5_KEY5                                       AES_KEY5_KEY5_Msk

/*******************  Bit definition for AES_KEY6 register  *******************/
#define AES_KEY6_KEY6_POS                                   (0U)
#define AES_KEY6_KEY6_Len                                   (32U)
#define AES_KEY6_KEY6_Msk                                   (0xFFFFFFFFUL << AES_KEY6_KEY6_POS)
#define AES_KEY6_KEY6                                       AES_KEY6_KEY6_Msk

/*******************  Bit definition for AES_KEY7 register  *******************/
#define AES_KEY7_KEY7_POS                                   (0U)
#define AES_KEY7_KEY7_Len                                   (32U)
#define AES_KEY7_KEY7_Msk                                   (0xFFFFFFFFUL << AES_KEY7_KEY7_POS)
#define AES_KEY7_KEY7                                       AES_KEY7_KEY7_Msk

/*******************  Bit definition for AES_INIT_SSI register  *******************/
#define AES_INIT_SSI_SEED_POS                               (0U)
#define AES_INIT_SSI_SEED_Len                               (32U)
#define AES_INIT_SSI_SEED_Msk                               (0xFFFFFFFFUL << AES_INIT_SSI_SEED_POS)
#define AES_INIT_SSI_SEED                                   AES_INIT_SSI_SEED_Msk

/*******************  Bit definition for AES_INIT_SSO register  *******************/
#define AES_INIT_SSO_SEED_POS                               (0U)
#define AES_INIT_SSO_SEED_Len                               (32U)
#define AES_INIT_SSO_SEED_Msk                               (0xFFFFFFFFUL << AES_INIT_SSO_SEED_POS)
#define AES_INIT_SSO_SEED                                   AES_INIT_SSO_SEED_Msk

/*******************  Bit definition for AES_MASK_SSI register  *******************/
#define AES_MASK_SSI_MASK_POS                               (0U)
#define AES_MASK_SSI_MASK_Len                               (32U)
#define AES_MASK_SSI_MASK_Msk                               (0xFFFFFFFFUL << AES_MASK_SSI_MASK_POS)
#define AES_MASK_SSI_MASK                                   AES_MASK_SSI_MASK_Msk

/*******************  Bit definition for AES_MASK_SSO register  *******************/
#define AES_MASK_SSO_MASK_POS                               (0U)
#define AES_MASK_SSO_MASK_Len                               (32U)
#define AES_MASK_SSO_MASK_Msk                               (0xFFFFFFFFUL << AES_MASK_SSO_MASK_POS)
#define AES_MASK_SSO_MASK                                   AES_MASK_SSO_MASK_Msk

/*******************  Bit definition for AES_INIT_V0 register  *******************/
#define AES_INIT_V0_VECTOR_POS                              (0U)
#define AES_INIT_V0_VECTOR_Len                              (32U)
#define AES_INIT_V0_VECTOR_Msk                              (0xFFFFFFFFUL << AES_INIT_V0_VECTOR_POS)
#define AES_INIT_V0_VECTOR                                  AES_INIT_V0_VECTOR_Msk

/*******************  Bit definition for AES_INIT_V1 register  *******************/
#define AES_INIT_V1_VECTOR_POS                              (0U)
#define AES_INIT_V1_VECTOR_Len                              (32U)
#define AES_INIT_V1_VECTOR_Msk                              (0xFFFFFFFFUL << AES_INIT_V1_VECTOR_POS)
#define AES_INIT_V1_VECTOR                                  AES_INIT_V1_VECTOR_Msk

/*******************  Bit definition for AES_INIT_V2 register  *******************/
#define AES_INIT_V2_VECTOR_POS                              (0U)
#define AES_INIT_V2_VECTOR_Len                              (32U)
#define AES_INIT_V2_VECTOR_Msk                              (0xFFFFFFFFUL << AES_INIT_V2_VECTOR_POS)
#define AES_INIT_V2_VECTOR                                  AES_INIT_V2_VECTOR_Msk

/*******************  Bit definition for AES_INIT_V3 register  *******************/
#define AES_INIT_V3_VECTOR_POS                              (0U)
#define AES_INIT_V3_VECTOR_Len                              (32U)
#define AES_INIT_V3_VECTOR_Msk                              (0xFFFFFFFFUL << AES_INIT_V3_VECTOR_POS)
#define AES_INIT_V3_VECTOR                                  AES_INIT_V3_VECTOR_Msk

/*******************  Bit definition for AES_DATA_IN0 register  *******************/
#define AES_DATA_IN0_DATA_IN0_POS                           (0U)
#define AES_DATA_IN0_DATA_IN0_Len                           (32U)
#define AES_DATA_IN0_DATA_IN0_Msk                           (0xFFFFFFFFUL << AES_DATA_IN0_DATA_IN0_POS)
#define AES_DATA_IN0_DATA_IN0                               AES_DATA_IN0_DATA_IN0_Msk

/*******************  Bit definition for AES_DATA_IN1 register  *******************/
#define AES_DATA_IN1_DATA_IN1_POS                           (0U)
#define AES_DATA_IN1_DATA_IN1_Len                           (32U)
#define AES_DATA_IN1_DATA_IN1_Msk                           (0xFFFFFFFFUL << AES_DATA_IN1_DATA_IN1_POS)
#define AES_DATA_IN1_DATA_IN1                               AES_DATA_IN1_DATA_IN1_Msk

/*******************  Bit definition for AES_DATA_IN2 register  *******************/
#define AES_DATA_IN2_DATA_IN2_POS                           (0U)
#define AES_DATA_IN2_DATA_IN2_Len                           (32U)
#define AES_DATA_IN2_DATA_IN2_Msk                           (0xFFFFFFFFUL << AES_DATA_IN2_DATA_IN2_POS)
#define AES_DATA_IN2_DATA_IN2                               AES_DATA_IN2_DATA_IN2_Msk

/*******************  Bit definition for AES_DATA_IN3 register  *******************/
#define AES_DATA_IN3_DATA_IN3_POS                           (0U)
#define AES_DATA_IN3_DATA_IN3_Len                           (32U)
#define AES_DATA_IN3_DATA_IN3_Msk                           (0xFFFFFFFFUL << AES_DATA_IN3_DATA_IN3_POS)
#define AES_DATA_IN3_DATA_IN3                               AES_DATA_IN3_DATA_IN3_Msk

/*******************  Bit definition for AES_KEYPORT_MASK register  *******************/
#define AES_KEYPORT_MASK_MASK_POS                           (0U)
#define AES_KEYPORT_MASK_MASK_Len                           (32U)
#define AES_KEYPORT_MASK_MASK_Msk                           (0xFFFFFFFFUL << AES_KEYPORT_MASK_MASK_POS)
#define AES_KEYPORT_MASK_MASK                               AES_KEYPORT_MASK_MASK_Msk

/* ================================================================================================================= */
/* ================                                        COMP                                     ================ */
/* ================================================================================================================= */

/*******************  Bit definition for COMP_REG_0 register  **********/

#define AON_PMU_COMP_REG_0_POSITIVE_HYS_EN_Pos                   (0U)
#define AON_PMU_COMP_REG_0_POSITIVE_HYS_EN_Len                   (1U)
#define AON_PMU_COMP_REG_0_POSITIVE_HYS_EN_Msk                   (0x1U << AON_PMU_COMP_REG_0_POSITIVE_HYS_EN_Pos)
#define AON_PMU_COMP_REG_0_POSITIVE_HYS_EN                       AON_PMU_COMP_REG_0_POSITIVE_HYS_EN_Msk

#define AON_PMU_COMP_REG_0_NEGATIVE_HYS_EN_Pos                   (1U)
#define AON_PMU_COMP_REG_0_NEGATIVE_HYS_EN_Len                   (1U)
#define AON_PMU_COMP_REG_0_NEGATIVE_HYS_EN_Msk                   (0x1U << AON_PMU_COMP_REG_0_NEGATIVE_HYS_EN_Pos)
#define AON_PMU_COMP_REG_0_NEGATIVE_HYS_EN                       AON_PMU_COMP_REG_0_NEGATIVE_HYS_EN_Msk

#define AON_PMU_COMP_REG_0_CASCRES_HALF_CTRL_Pos                 (6U)
#define AON_PMU_COMP_REG_0_CASCRES_HALF_CTRL_Len                 (1U)
#define AON_PMU_COMP_REG_0_CASCRES_HALF_CTRL_Msk                 (0x1U << AON_PMU_COMP_REG_0_CASCRES_HALF_CTRL_Pos)
#define AON_PMU_COMP_REG_0_CASCRES_HALF_CTRL                     AON_PMU_COMP_REG_0_CASCRES_HALF_CTRL_Msk

#define AON_PMU_COMP_REG_0_WAKE_COMP_EN_Pos                      (7U)
#define AON_PMU_COMP_REG_0_WAKE_COMP_EN_Len                      (1U)
#define AON_PMU_COMP_REG_0_WAKE_COMP_EN_Msk                      (0x1U << AON_PMU_COMP_REG_0_WAKE_COMP_EN_Pos)
#define AON_PMU_COMP_REG_0_WAKE_COMP_EN                          AON_PMU_COMP_REG_0_WAKE_COMP_EN_Msk

#define AON_PMU_COMP_REG_0_ICOMP_CTRL_Pos                        (8U)
#define AON_PMU_COMP_REG_0_ICOMP_CTRL_Len                        (4U)
#define AON_PMU_COMP_REG_0_ICOMP_CTRL_Msk                        (0xFU << AON_PMU_COMP_REG_0_ICOMP_CTRL_Pos)
#define AON_PMU_COMP_REG_0_ICOMP_CTRL                            AON_PMU_COMP_REG_0_ICOMP_CTRL_Msk

#define AON_PMU_COMP_REG_0_COMP_BATT_LVL_CTRL_Pos                (12U)
#define AON_PMU_COMP_REG_0_COMP_BATT_LVL_CTRL_Len                (3U)
#define AON_PMU_COMP_REG_0_COMP_BATT_LVL_CTRL_Msk                (0x7U << AON_PMU_COMP_REG_0_COMP_BATT_LVL_CTRL_Pos)
#define AON_PMU_COMP_REG_0_COMP_BATT_LVL_CTRL                    AON_PMU_COMP_REG_0_COMP_BATT_LVL_CTRL_Msk

#define AON_PMU_COMP_REG_0_CHANNEL_SEL_P_Pos                     (16U)
#define AON_PMU_COMP_REG_0_CHANNEL_SEL_P_Len                     (4U)
#define AON_PMU_COMP_REG_0_CHANNEL_SEL_P_Msk                     (0xFU << AON_PMU_COMP_REG_0_CHANNEL_SEL_P_Pos)
#define AON_PMU_COMP_REG_0_CHANNEL_SEL_P                         AON_PMU_COMP_REG_0_CHANNEL_SEL_P_Msk

#define AON_PMU_COMP_REG_0_CHANNEL_SEL_N_Pos                     (20U)
#define AON_PMU_COMP_REG_0_CHANNEL_SEL_N_Len                     (4U)
#define AON_PMU_COMP_REG_0_CHANNEL_SEL_N_Msk                     (0xFU << AON_PMU_COMP_REG_0_CHANNEL_SEL_N_Pos)
#define AON_PMU_COMP_REG_0_CHANNEL_SEL_N                         AON_PMU_COMP_REG_0_CHANNEL_SEL_N_Msk

/*******************  Bit definition for COMP_REG_1 register  **********/

#define AON_PMU_COMP_REG_1_CHANNEL_POSITIVE_RES_DEGENERATION_Pos          (0U)
#define AON_PMU_COMP_REG_1_CHANNEL_POSITIVE_RES_DEGENERATION_Len          (4U)
#define AON_PMU_COMP_REG_1_CHANNEL_POSITIVE_RES_DEGENERATION_Msk          (0xFU << AON_PMU_COMP_REG_1_CHANNEL_POSITIVE_RES_DEGENERATION_Pos)
#define AON_PMU_COMP_REG_1_CHANNEL_POSITIVE_RES_DEGENERATION              AON_PMU_COMP_REG_1_CHANNEL_POSITIVE_RES_DEGENERATION_Msk

#define AON_PMU_COMP_REG_1_CHANNEL_NEGATIVE_RES_DEGENERATION_Pos          (4U)
#define AON_PMU_COMP_REG_1_CHANNEL_NEGATIVE_RES_DEGENERATION_Len          (4U)
#define AON_PMU_COMP_REG_1_CHANNEL_NEGATIVE_RES_DEGENERATION_Msk          (0xFU << AON_PMU_COMP_REG_1_CHANNEL_NEGATIVE_RES_DEGENERATION_Pos)
#define AON_PMU_COMP_REG_1_CHANNEL_NEGATIVE_RES_DEGENERATION              AON_PMU_COMP_REG_1_CHANNEL_NEGATIVE_RES_DEGENERATION_Msk

#define AON_PMU_COMP_REG_1_COMP_REF_CTRL_Pos                              (8U)
#define AON_PMU_COMP_REG_1_COMP_REF_CTRL_Len                              (8U)
#define AON_PMU_COMP_REG_1_COMP_REF_CTRL_Msk                              (0xFFU << AON_PMU_COMP_REG_1_COMP_REF_CTRL_Pos)
#define AON_PMU_COMP_REG_1_COMP_REF_CTRL                                  AON_PMU_COMP_REG_1_COMP_REF_CTRL_Msk

/* ================================================================================================================= */
/* ================                                        DMA                                      ================ */
/* ================================================================================================================= */

/*******************  Bit definition for DMA_SAR register  ********************/
#define DMA_SAR_CSA_Pos                                     (0U)
#define DMA_SAR_CSA_Len                                     (32U)
#define DMA_SAR_CSA_Msk                                     (0xFFFFFFFFU)
#define DMA_SAR_CSA                                         DMA_SAR_CSA_Msk

/*******************  Bit definition for DMA_DAR register  ********************/
#define DMA_DAR_CDA_Pos                                     (0U)
#define DMA_DAR_CDA_Len                                     (32U)
#define DMA_DAR_CDA_Msk                                     (0xFFFFFFFFU)
#define DMA_DAR_CDA                                         DMA_DAR_CDA_Msk

/*******************  Bit definition for DMA_CTLL register  *******************/
#define DMA_CTLL_TT_FC_Pos                                  (20U)
#define DMA_CTLL_TT_FC_Len                                  (2U)
#define DMA_CTLL_TT_FC_Msk                                  (0x3U << DMA_CTLL_TT_FC_Pos)
#define DMA_CTLL_TT_FC                                      DMA_CTLL_TT_FC_Msk
#define DMA_CTLL_TT_FC_M2M                                  (0x0U << DMA_CTLL_TT_FC_Pos)
#define DMA_CTLL_TT_FC_M2P                                  (0x1U << DMA_CTLL_TT_FC_Pos)
#define DMA_CTLL_TT_FC_P2M                                  (0x2U << DMA_CTLL_TT_FC_Pos)
#define DMA_CTLL_TT_FC_P2P                                  (0x3U << DMA_CTLL_TT_FC_Pos)

#define DMA_CTLL_SRC_MSIZE_Pos                              (14U)
#define DMA_CTLL_SRC_MSIZE_Len                              (3U)
#define DMA_CTLL_SRC_MSIZE_Msk                              (0x7U << DMA_CTLL_SRC_MSIZE_Pos)
#define DMA_CTLL_SRC_MSIZE                                  DMA_CTLL_SRC_MSIZE_Msk
#define DMA_CTLL_SRC_MSIZE_1                                (0x0U << DMA_CTLL_SRC_MSIZE_Pos)
#define DMA_CTLL_SRC_MSIZE_4                                (0x1U << DMA_CTLL_SRC_MSIZE_Pos)
#define DMA_CTLL_SRC_MSIZE_8                                (0x2U << DMA_CTLL_SRC_MSIZE_Pos)
#define DMA_CTLL_SRC_MSIZE_16                               (0x3U << DMA_CTLL_SRC_MSIZE_Pos)
#define DMA_CTLL_SRC_MSIZE_32                               (0x4U << DMA_CTLL_SRC_MSIZE_Pos)
#define DMA_CTLL_SRC_MSIZE_64                               (0x5U << DMA_CTLL_SRC_MSIZE_Pos)
#define DMA_CTLL_SRC_MSIZE_128                              (0x6U << DMA_CTLL_SRC_MSIZE_Pos)
#define DMA_CTLL_SRC_MSIZE_256                              (0x7U << DMA_CTLL_SRC_MSIZE_Pos)

#define DMA_CTLL_DST_MSIZE_Pos                              (11U)
#define DMA_CTLL_DST_MSIZE_Len                              (3U)
#define DMA_CTLL_DST_MSIZE_Msk                              (0x7U << DMA_CTLL_DST_MSIZE_Pos)
#define DMA_CTLL_DST_MSIZE                                  DMA_CTLL_DST_MSIZE_Msk
#define DMA_CTLL_DST_MSIZE_1                                (0x0U << DMA_CTLL_DST_MSIZE_Pos)
#define DMA_CTLL_DST_MSIZE_4                                (0x1U << DMA_CTLL_DST_MSIZE_Pos)
#define DMA_CTLL_DST_MSIZE_8                                (0x2U << DMA_CTLL_DST_MSIZE_Pos)
#define DMA_CTLL_DST_MSIZE_16                               (0x3U << DMA_CTLL_DST_MSIZE_Pos)
#define DMA_CTLL_DST_MSIZE_32                               (0x4U << DMA_CTLL_DST_MSIZE_Pos)
#define DMA_CTLL_DST_MSIZE_64                               (0x5U << DMA_CTLL_DST_MSIZE_Pos)
#define DMA_CTLL_DST_MSIZE_128                              (0x6U << DMA_CTLL_DST_MSIZE_Pos)
#define DMA_CTLL_DST_MSIZE_256                              (0x7U << DMA_CTLL_DST_MSIZE_Pos)

#define DMA_CTLL_SINC_Pos                                   (9U)
#define DMA_CTLL_SINC_Len                                   (2U)
#define DMA_CTLL_SINC_Msk                                   (0x3U << DMA_CTLL_SINC_Pos)
#define DMA_CTLL_SINC                                       DMA_CTLL_SINC_Msk
#define DMA_CTLL_SINC_INC                                   (0x0U << DMA_CTLL_SINC_Pos)
#define DMA_CTLL_SINC_DEC                                   (0x1U << DMA_CTLL_SINC_Pos)
#define DMA_CTLL_SINC_NO                                    (0x2U << DMA_CTLL_SINC_Pos)

#define DMA_CTLL_DINC_Pos                                   (7U)
#define DMA_CTLL_DINC_Len                                   (2U)
#define DMA_CTLL_DINC_Msk                                   (0x3U << DMA_CTLL_DINC_Pos)
#define DMA_CTLL_DINC                                       DMA_CTLL_DINC_Msk
#define DMA_CTLL_DINC_INC                                   (0x0U << DMA_CTLL_DINC_Pos)
#define DMA_CTLL_DINC_DEC                                   (0x1U << DMA_CTLL_DINC_Pos)
#define DMA_CTLL_DINC_NO                                    (0x2U << DMA_CTLL_DINC_Pos)

#define DMA_CTLL_SRC_TR_WIDTH_Pos                           (4U)
#define DMA_CTLL_SRC_TR_WIDTH_Len                           (2U)
#define DMA_CTLL_SRC_TR_WIDTH_Msk                           (0x3U << DMA_CTLL_SRC_TR_WIDTH_Pos)
#define DMA_CTLL_SRC_TR_WIDTH                               DMA_CTLL_SRC_TR_WIDTH_Msk
#define DMA_CTLL_SRC_TR_WIDTH_8                             (0x0U << DMA_CTLL_SRC_TR_WIDTH_Pos)
#define DMA_CTLL_SRC_TR_WIDTH_16                            (0x1U << DMA_CTLL_SRC_TR_WIDTH_Pos)
#define DMA_CTLL_SRC_TR_WIDTH_32                            (0x2U << DMA_CTLL_SRC_TR_WIDTH_Pos)

#define DMA_CTLL_DST_TR_WIDTH_Pos                           (1U)
#define DMA_CTLL_DST_TR_WIDTH_Len                           (2U)
#define DMA_CTLL_DST_TR_WIDTH_Msk                           (0x3U << DMA_CTLL_DST_TR_WIDTH_Pos)
#define DMA_CTLL_DST_TR_WIDTH                               DMA_CTLL_DST_TR_WIDTH_Msk
#define DMA_CTLL_DST_TR_WIDTH_8                             (0x0U << DMA_CTLL_DST_TR_WIDTH_Pos)
#define DMA_CTLL_DST_TR_WIDTH_16                            (0x1U << DMA_CTLL_DST_TR_WIDTH_Pos)
#define DMA_CTLL_DST_TR_WIDTH_32                            (0x2U << DMA_CTLL_DST_TR_WIDTH_Pos)

#define DMA_CTLL_INT_EN_Pos                                 (0U)
#define DMA_CTLL_INT_EN_Len                                 (1U)
#define DMA_CTLL_INT_EN_Msk                                 (0x1U << DMA_CTLL_INT_EN_Pos)
#define DMA_CTLL_INI_EN                                     DMA_CTLL_INT_EN_Msk

/*******************  Bit definition for DMA_CTLH register  *******************/
#define DMA_CTLH_BLOCK_TS_Pos                               (0U)
#define DMA_CTLH_BLOCK_TS_Len                               (12U)
#define DMA_CTLH_BLOCK_TS_Msk                               (0xFFFU << DMA_CTLH_BLOCK_TS_Pos)
#define DMA_CTLH_BLOCK_TS                                   DMA_CTLH_BLOCK_TS_Msk

/*******************  Bit definition for DMA_CFGL register  *******************/
#define DMA_CFGL_SRC_HS_POL_Pos                             (19U)
#define DMA_CFGL_SRC_HS_POL_Len                             (1U)
#define DMA_CFGL_SRC_HS_POL_Msk                             (0x1U << DMA_CFGL_SRC_HS_POL_Pos)
#define DMA_CFGL_SRC_HS_POL                                 DMA_CFGL_SRC_HS_POL_Msk

#define DMA_CFGL_DST_HS_POL_Pos                             (18U)
#define DMA_CFGL_DST_HS_POL_Len                             (1U)
#define DMA_CFGL_DST_HS_POL_Msk                             (0x1U << DMA_CFGL_DST_HS_POL_Pos)
#define DMA_CFGL_DST_HS_POL                                 DMA_CFGL_DST_HS_POL_Msk

#define DMA_CFGL_LOCK_B_Pos                                 (17U)
#define DMA_CFGL_LOCK_B_Len                                 (1U)
#define DMA_CFGL_LOCK_B_Msk                                 (0x1U << DMA_CFGL_LOCK_B_Pos)
#define DMA_CFGL_LOCK_B                                     DMA_CFGL_LOCK_B_Msk
#define DMA_CFGL_LOCK_B_ENABLE                              (0x1U << DMA_CFGL_LOCK_B_Pos)
#define DMA_CFGL_LOCK_B_DISABLE                             (0x0U << DMA_CFGL_LOCK_B_Pos)

#define DMA_CFGL_LOCK_CH_Pos                                (16U)
#define DMA_CFGL_LOCK_CH_Len                                (1U)
#define DMA_CFGL_LOCK_CH_Msk                                (0x1U << DMA_CFGL_LOCK_CH_Pos)
#define DMA_CFGL_LOCK_CH                                    DMA_CFGL_LOCK_CH_Msk
#define DMA_CFGL_LOCK_CH_ENABLE                             (0x1U << DMA_CFGL_LOCK_CH_Pos)
#define DMA_CFGL_LOCK_CH_DISABLE                            (0x0U << DMA_CFGL_LOCK_CH_Pos)

#define DMA_CFGL_LOCK_B_L_Pos                               (14U)
#define DMA_CFGL_LOCK_B_L_Len                               (2U)
#define DMA_CFGL_LOCK_B_L_Msk                               (0x3U << DMA_CFGL_LOCK_B_L_Pos)
#define DMA_CFGL_LOCK_B_L                                   DMA_CFGL_LOCK_B_L_Msk
#define DMA_CFGL_LOCK_B_L_TFR                               (0x0U << DMA_CFGL_LOCK_B_L_Pos)
#define DMA_CFGL_LOCK_B_L_BLK                               (0x1U << DMA_CFGL_LOCK_B_L_Pos)
#define DMA_CFGL_LOCK_B_L_TRANS                             (0x2U << DMA_CFGL_LOCK_B_L_Pos)

#define DMA_CFGL_LOCK_CH_L_Pos                              (12U)
#define DMA_CFGL_LOCK_CH_L_Len                              (2U)
#define DMA_CFGL_LOCK_CH_L_Msk                              (0x3U << DMA_CFGL_LOCK_CH_L_Pos)
#define DMA_CFGL_LOCK_CH_L                                  DMA_CFGL_LOCK_CH_L_Msk
#define DMA_CFGL_LOCK_CH_L_TFR                              (0x0U << DMA_CFGL_LOCK_CH_L_Pos)
#define DMA_CFGL_LOCK_CH_L_BLK                              (0x1U << DMA_CFGL_LOCK_CH_L_Pos)
#define DMA_CFGL_LOCK_CH_L_TRANS                            (0x2U << DMA_CFGL_LOCK_CH_L_Pos)

#define DMA_CFGL_HS_SEL_SRC_Pos                             (11U)
#define DMA_CFGL_HS_SEL_SRC_Len                             (1U)
#define DMA_CFGL_HS_SEL_SRC_Msk                             (0x1U << DMA_CFGL_HS_SEL_SRC_Pos)
#define DMA_CFGL_HS_SEL_SRC                                 DMA_CFGL_HS_SEL_SRC_Msk

#define DMA_CFGL_HS_SEL_DST_Pos                             (10U)
#define DMA_CFGL_HS_SEL_DST_Len                             (1U)
#define DMA_CFGL_HS_SEL_DST_Msk                             (0x1U << DMA_CFGL_HS_SEL_DST_Pos)
#define DMA_CFGL_HS_SEL_DST                                 DMA_CFGL_HS_SEL_DST_Msk

#define DMA_CFGL_FIFO_EMPTY_Pos                             (9U)
#define DMA_CFGL_FIFO_EMPTY_Len                             (1U)
#define DMA_CFGL_FIFO_EMPTY_Msk                             (0x1U << DMA_CFGL_FIFO_EMPTY_Pos)
#define DMA_CFGL_FIFO_EMPTY                                 DMA_CFGL_FIFO_EMPTY_Msk

#define DMA_CFGL_CH_SUSP_Pos                                (8U)
#define DMA_CFGL_CH_SUSP_Len                                (1U)
#define DMA_CFGL_CH_SUSP_Msk                                (0x1U << DMA_CFGL_CH_SUSP_Pos)
#define DMA_CFGL_CH_SUSP                                    DMA_CFGL_CH_SUSP_Msk

#define DMA_CFGL_CH_PRIOR_Pos                               (5U)
#define DMA_CFGL_CH_PRIOR_Len                               (3U)
#define DMA_CFGL_CH_PRIOR_Msk                               (0x7U << DMA_CFGL_CH_PRIOR_Pos)
#define DMA_CFGL_CH_PRIOR                                   DMA_CFGL_CH_PRIOR_Msk
#define DMA_CFGL_CH_PRIOR_0                                 (0x0U << DMA_CFGL_CH_PRIOR_Pos)
#define DMA_CFGL_CH_PRIOR_1                                 (0x1U << DMA_CFGL_CH_PRIOR_Pos)
#define DMA_CFGL_CH_PRIOR_2                                 (0x2U << DMA_CFGL_CH_PRIOR_Pos)
#define DMA_CFGL_CH_PRIOR_3                                 (0x3U << DMA_CFGL_CH_PRIOR_Pos)
#define DMA_CFGL_CH_PRIOR_4                                 (0x4U << DMA_CFGL_CH_PRIOR_Pos)
#define DMA_CFGL_CH_PRIOR_5                                 (0x5U << DMA_CFGL_CH_PRIOR_Pos)
#define DMA_CFGL_CH_PRIOR_6                                 (0x6U << DMA_CFGL_CH_PRIOR_Pos)
#define DMA_CFGL_CH_PRIOR_7                                 (0x7U << DMA_CFGL_CH_PRIOR_Pos)

/*******************  Bit definition for DMA_CFGH register  ********************/
#define DMA_CFGL_MAX_ABRST_Pos                              (20U)
#define DMA_CFGL_MAX_ABRST_Len                              (10U)
#define DMA_CFGL_MAX_ABRST_Msk                              (0x3FFU << DMA_CFGL_MAX_ABRST_Pos)
#define DMA_CFGL_MAX_ABRST                                  DMA_CFGL_MAX_ABRST_Msk

#define DMA_CFGH_DST_PER_Pos                                (11U)
#define DMA_CFGH_DST_PER_Len                                (4U)
#define DMA_CFGH_DST_PER_Msk                                (0xFU << DMA_CFGH_DST_PER_Pos)
#define DMA_CFGH_DST_PER                                    DMA_CFGH_DST_PER_Msk

#define DMA_CFGH_SRC_PER_Pos                                (7U)
#define DMA_CFGH_SRC_PER_Len                                (4U)
#define DMA_CFGH_SRC_PER_Msk                                (0xFU << DMA_CFGH_SRC_PER_Pos)
#define DMA_CFGH_SRC_PER                                    DMA_CFGH_SRC_PER_Msk

#define DMA_CFGH_PROTCTL_Pos                                (2U)
#define DMA_CFGH_PROTCTL_Len                                (3U)
#define DMA_CFGH_PROTCTL_Msk                                (0x7U << DMA_CFGH_PROTCTL_Pos)
#define DMA_CFGH_PROTCTL                                    DMA_CFGH_PROTCTL_Msk

#define DMA_CFGH_FIFO_MODE_Pos                              (1U)
#define DMA_CFGH_FIFO_MODE_Len                              (1U)
#define DMA_CFGH_FIFO_MODE_Msk                              (0x1U << DMA_CFGH_FIFO_MODE_Pos)
#define DMA_CFGH_FIFO_MODE                                  DMA_CFGH_FIFO_MODE_Msk

#define DMA_CFGH_FCMODE_Pos                                 (0U)
#define DMA_CFGH_FCMODE_Len                                 (1U)
#define DMA_CFGH_FCMODE_Msk                                 (0x1U << DMA_CFGH_FCMODE_Pos)
#define DMA_CFGH_FCMODE                                     DMA_CFGH_FCMODE_Msk

/*******************  Bit definition for DMA_RAW_TFR register  *****************/
#define DMA_RAW_TFR_Pos                                     (0U)
#define DMA_RAW_TFR_Len                                     (5U)
#define DMA_RAW_TFR_Msk                                     (0x1FU << DMA_RAW_TFR_Pos)
#define DMA_RAW_TFR                                         DMA_RAW_TFR_Msk

/*******************  Bit definition for DMA_RAW_BLK register  *****************/
#define DMA_RAW_BLK_Pos                                     (0U)
#define DMA_RAW_BLK_Len                                     (5U)
#define DMA_RAW_BLK_Msk                                     (0x1FU << DMA_RAW_BLK_Pos)
#define DMA_RAW_BLK                                         DMA_RAW_BLK_Msk

/*******************  Bit definition for DMA_RAW_SRC_TRN register  *************/
#define DMA_RAW_SRC_TRN_Pos                                 (0U)
#define DMA_RAW_SRC_TRN_Len                                 (5U)
#define DMA_RAW_SRC_TRN_Msk                                 (0x1FU << DMA_RAW_SRC_TRN_Pos)
#define DMA_RAW_SRC_TRN                                     DMA_RAW_SRC_TRN_Msk

/*******************  Bit definition for DMA_RAW_DST_TRN register  *************/
#define DMA_RAW_DST_TRN_Pos                                 (0U)
#define DMA_RAW_DST_TRN_Len                                 (5U)
#define DMA_RAW_DST_TRN_Msk                                 (0x1FU << DMA_RAW_DST_TRN_Pos)
#define DMA_RAW_DST_TRN                                     DMA_RAW_DST_TRN_Msk

/*******************  Bit definition for DMA_RAW_ERR register  *****************/
#define DMA_RAW_ERR_Pos                                     (0U)
#define DMA_RAW_ERR_Len                                     (5U)
#define DMA_RAW_ERR_Msk                                     (0x1FU << DMA_RAW_ERR_Pos)
#define DMA_RAW_ERR                                         DMA_RAW_ERR_Msk

/*******************  Bit definition for DMA_STAT_TFR register  ****************/
#define DMA_STAT_TFR_Pos                                    (0U)
#define DMA_STAT_TFR_Len                                    (5U)
#define DMA_STAT_TFR_Msk                                    (0x1FUL << DMA_STAT_TFR_Pos)
#define DMA_STAT_TFR                                        DMA_STAT_TFR_Msk

/*******************  Bit definition for DMA_STAT_BLK register  ****************/
#define DMA_STAT_BLK_Pos                                    (0U)
#define DMA_STAT_BLK_Len                                    (5U)
#define DMA_STAT_BLK_Msk                                    (0x1FU << DMA_STAT_BLK_Pos)
#define DMA_STAT_BLK                                        DMA_STAT_BLK_Msk

/*******************  Bit definition for DMA_STAT_SRC_TRN register  ************/
#define DMA_STAT_SRC_TRN_Pos                                (0U)
#define DMA_STAT_SRC_TRN_Len                                (5U)
#define DMA_STAT_SRC_TRN_Msk                                (0x1FU << DMA_STAT_SRC_TRN_Pos)
#define DMA_STAT_SRC_TRN                                    DMA_STAT_SRC_TRN_Msk

/*******************  Bit definition for DMA_STAT_DST_TRN register  ************/
#define DMA_STAT_DST_TRN_Pos                                (0U)
#define DMA_STAT_DST_TRN_Len                                (5U)
#define DMA_STAT_DST_TRN_Msk                                (0x1FU << DMA_STAT_DST_TRN_Pos)
#define DMA_STAT_DST_TRN                                    DMA_STAT_DST_TRN_Msk

/*******************  Bit definition for DMA_STAT_ERR register  ****************/
#define DMA_STAT_ERR_Pos                                    (0U)
#define DMA_STAT_ERR_Len                                    (5U)
#define DMA_STAT_ERR_Msk                                    (0x1FU << DMA_STAT_ERR_Pos)
#define DMA_STAT_ERR                                        DMA_STAT_ERR_Msk

/*******************  Bit definition for DMA_MASK_TFR register  ****************/
#define DMA_MASK_TFR_WE_Pos                                 (8U)
#define DMA_MASK_TFR_WE_Len                                 (5U)
#define DMA_MASK_TFR_WE_Msk                                 (0x1FU << DMA_MASK_TFR_WE_Pos)
#define DMA_MASK_TFR_WE                                     DMA_MASK_TFR_WE_Msk

#define DMA_MASK_TFR_Pos                                    (0U)
#define DMA_MASK_TFR_Len                                    (5U)
#define DMA_MASK_TFR_Msk                                    (0x1FU << DMA_MASK_TFR_Pos)
#define DMA_MASK_TFR                                        DMA_MASK_TFR_Msk

/*******************  Bit definition for DMA_MASK_BLK register  ****************/
#define DMA_MASK_BLK_WE_Pos                                 (8U)
#define DMA_MASK_BLK_WE_Len                                 (5U)
#define DMA_MASK_BLK_WE_Msk                                 (0x1FU << DMA_MASK_BLK_WE_Pos)
#define DMA_MASK_BLK_WE                                     DMA_MASK_BLK_WE_Msk

#define DMA_MASK_BLK_Pos                                    (0U)
#define DMA_MASK_BLK_Len                                    (5U)
#define DMA_MASK_BLK_Msk                                    (0x1FU << DMA_MASK_BLK_Pos)
#define DMA_MASK_BLK                                        DMA_MASK_BLK_Msk

/*******************  Bit definition for DMA_MASK_SRC_TRN register  ************/
#define DMA_MASK_SRC_TRN_WE_Pos                             (8U)
#define DMA_MASK_SRC_TRN_WE_Len                             (5U)
#define DMA_MASK_SRC_TRN_WE_Msk                             (0x1FU << DMA_MASK_SRC_TRN_WE_Pos)
#define DMA_MASK_SRC_TRN_WE                                 DMA_MASK_SRC_TRN_WE_Msk

#define DMA_MASK_SRC_TRN_Pos                                (0U)
#define DMA_MASK_SRC_TRN_Len                                (5U)
#define DMA_MASK_SRC_TRN_Msk                                (0x1FU << DMA_MASK_SRC_TRN_Pos)
#define DMA_MASK_SRC_TRN                                    DMA_MASK_SRC_TRN_Msk

/*******************  Bit definition for DMA_MASK_DST_TRN register  ************/
#define DMA_MASK_DST_TRN_WE_Pos                             (8U)
#define DMA_MASK_DST_TRN_WE_Len                             (5U)
#define DMA_MASK_DST_TRN_WE_Msk                             (0x1FU << DMA_MASK_DST_TRN_WE_Pos)
#define DMA_MASK_DST_TRN_WE                                 DMA_MASK_DST_TRN_WE_Msk

#define DMA_MASK_DST_TRN_Pos                                (0U)
#define DMA_MASK_DST_TRN_Len                                (5U)
#define DMA_MASK_DST_TRN_Msk                                (0x1FU << DMA_MASK_DST_TRN_Pos)
#define DMA_MASK_DST_TRN                                    DMA_MASK_DST_TRN_Msk

/*******************  Bit definition for DMA_MASK_ERR register  ****************/
#define DMA_MASK_ERR_WE_Pos                                 (8U)
#define DMA_MASK_ERR_WE_Len                                 (5U)
#define DMA_MASK_ERR_WE_Msk                                 (0x1FU << DMA_MASK_ERR_WE_Pos)
#define DMA_MASK_ERR_WE                                     DMA_MASK_ERR_WE_Msk

#define DMA_MASK_ERR_Pos                                    (0U)
#define DMA_MASK_ERR_Len                                    (5U)
#define DMA_MASK_ERR_Msk                                    (0x1FU << DMA_MASK_ERR_Pos)
#define DMA_MASK_ERR                                        DMA_MASK_ERR_Msk

/*******************  Bit definition for DMA_CLR_TFR register  *****************/
#define DMA_CLR_TFR_Pos                                     (0U)
#define DMA_CLR_TFR_Len                                     (5U)
#define DMA_CLR_TFR_Msk                                     (0x1FU << DMA_CLR_TFR_Pos)
#define DMA_CLR_TFR                                         DMA_CLR_TFR_Msk

/*******************  Bit definition for DMA_CLR_BLK register  *****************/
#define DMA_CLR_BLK_Pos                                     (0U)
#define DMA_CLR_BLK_Len                                     (5U)
#define DMA_CLR_BLK_Msk                                     (0x1FU << DMA_CLR_BLK_Pos)
#define DMA_CLR_BLK                                         DMA_CLR_BLK_Msk

/*******************  Bit definition for DMA_CLR_SRC_TRN register  *************/
#define DMA_CLR_SRC_TRN_Pos                                 (0U)
#define DMA_CLR_SRC_TRN_Len                                 (5U)
#define DMA_CLR_SRC_TRN_Msk                                 (0x1FU << DMA_CLR_SRC_TRN_Pos)
#define DMA_CLR_SRC_TRN                                     DMA_CLR_SRC_TRN_Msk

/*******************  Bit definition for DMA_CLR_DST_TRN register  *************/
#define DMA_CLR_DST_TRN_Pos                                 (0U)
#define DMA_CLR_DST_TRN_Len                                 (5U)
#define DMA_CLR_DST_TRN_Msk                                 (0x1FU << DMA_CLR_DST_TRN_Pos)
#define DMA_CLR_DST_TRN                                     DMA_CLR_DST_TRN_Msk

/*******************  Bit definition for DMA_CLR_ERR register  *****************/
#define DMA_CLR_ERR_Pos                                     (0U)
#define DMA_CLR_ERR_Len                                     (5U)
#define DMA_CLR_ERR_Msk                                     (0x1FU << DMA_CLR_ERR_Pos)
#define DMA_CLR_ERR                                         DMA_CLR_ERR_Msk

/*******************  Bit definition for DMA_STATUS_INT register  **************/
#define DMA_STAT_INT_ERR_Pos                                (4U)
#define DMA_STAT_INT_ERR_Len                                (1U)
#define DMA_STAT_INT_ERR_Msk                                (0x1U << DMA_STAT_INT_ERR_Pos)
#define DMA_STAT_INT_ERR                                    DMA_STAT_INT_ERR_Msk

#define DMA_STAT_INT_DST_Pos                                (3U)
#define DMA_STAT_INT_DST_Len                                (1U)
#define DMA_STAT_INT_DST_Msk                                (0x1U << DMA_STAT_INT_DST_Pos)
#define DMA_STAT_INT_DST                                    DMA_STAT_INT_DST_Msk

#define DMA_STAT_INT_SRC_Pos                                (2U)
#define DMA_STAT_INT_SRC_Len                                (1U)
#define DMA_STAT_INT_SRC_Msk                                (0x1U << DMA_STAT_INT_SRC_Pos)
#define DMA_STAT_INT_SRC                                    DMA_STAT_INT_SRC_Msk

#define DMA_STAT_INT_BLK_Pos                                (1U)
#define DMA_STAT_INT_BLK_Len                                (1U)
#define DMA_STAT_INT_BLK_Msk                                (0x1U << DMA_STAT_INT_BLK_Pos)
#define DMA_STAT_INT_BLK                                    DMA_STAT_INT_BLK_Msk

#define DMA_STAT_INT_TFR_Pos                                (0U)
#define DMA_STAT_INT_TFR_Len                                (1U)
#define DMA_STAT_INT_TFR_Msk                                (0x1U << DMA_STAT_INT_TFR_Pos)
#define DMA_STAT_INT_TFR                                    DMA_STAT_INT_TFR_Msk

/*******************  Bit definition for DMA_REQ_SRC_REG register  *************/
#define DMA_REQ_SRC_WE_Pos                                  (8U)
#define DMA_REQ_SRC_WE_Len                                  (5U)
#define DMA_REQ_SRC_WE_Msk                                  (0x1FU << DMA_REQ_SRC_WE_Pos)
#define DMA_REQ_SRC_WE                                      DMA_REQ_SRC_WE_Msk

#define DMA_REQ_SRC_Pos                                     (0U)
#define DMA_REQ_SRC_Len                                     (5U)
#define DMA_REQ_SRC_Msk                                     (0x1FU << DMA_REQ_SRC_Pos)
#define DMA_REQ_SRC                                         DMA_REQ_SRC_Msk

/*******************  Bit definition for DMA_REQ_DST_REG register  *************/
#define DMA_REQ_DST_WE_Pos                                  (8U)
#define DMA_REQ_DST_WE_Len                                  (5U)
#define DMA_REQ_DST_WE_Msk                                  (0x1FU << DMA_REQ_DST_WE_Pos)
#define DMA_REQ_DST_WE                                      DMA_REQ_DST_WE_Msk

#define DMA_REQ_DST_Pos                                     (0U)
#define DMA_REQ_DST_Len                                     (5U)
#define DMA_REQ_DST_Msk                                     (0x1FU << DMA_REQ_DST_Pos)
#define DMA_REQ_DST                                         DMA_REQ_DST_Msk

/*******************  Bit definition for DMA_SGL_REQ_SRC_REG register  *********/
#define DMA_SGL_REQ_SRC_WE_Pos                              (8U)
#define DMA_SGL_REQ_SRC_WE_Len                              (5U)
#define DMA_SGL_REQ_SRC_WE_Msk                              (0x1FU << DMA_SGL_REQ_SRC_WE_Pos)
#define DMA_SGL_REQ_SRC_WE                                  DMA_SGL_REQ_SRC_WE_Msk

#define DMA_SGL_REQ_SRC_Pos                                 (0U)
#define DMA_SGL_REQ_SRC_Len                                 (5U)
#define DMA_SGL_REQ_SRC_Msk                                 (0x1FU << DMA_SGL_REQ_SRC_Pos)
#define DMA_SGL_REQ_SRC                                     DMA_SGL_REQ_SRC_Msk

/*******************  Bit definition for DMA_SGL_REQ_DST_REG register  *********/
#define DMA_SGL_REQ_DST_WE_Pos                              (8U)
#define DMA_SGL_REQ_DST_WE_Len                              (5U)
#define DMA_SGL_REQ_DST_WE_Msk                              (0x1FU << DMA_SGL_REQ_DST_WE_Pos)
#define DMA_SGL_REQ_DST_WE                                  DMA_SGL_REQ_DST_WE_Msk

#define DMA_SGL_REQ_DST_Pos                                 (0U)
#define DMA_SGL_REQ_DST_Len                                 (5U)
#define DMA_SGL_REQ_DST_Msk                                 (0x1FU << DMA_SGL_REQ_DST_Pos)
#define DMA_SGL_REQ_DST                                     DMA_SGL_REQ_DST_Msk

/*******************  Bit definition for DMA_LST_SRC_REG register  *********/
#define DMA_LST_SRC_WE_Pos                                  (8U)
#define DMA_LST_SRC_WE_Len                                  (5U)
#define DMA_LST_SRC_WE_Msk                                  (0x1FU << DMA_LST_SRC_WE_Pos)
#define DMA_LST_SRC_WE                                      DMA_LST_SRC_WE_Msk

#define DMA_LST_SRC_Pos                                     (0U)
#define DMA_LST_SRC_Len                                     (5U)
#define DMA_LST_SRC_Msk                                     (0x1FU << DMA_LST_SRC_Pos)
#define DMA_LST_SRC                                         DMA_LST_SRC_Msk

/*******************  Bit definition for DMA_LST_DST_REG register  *********/
#define DMA_LST_DST_WE_Pos                                  (8U)
#define DMA_LST_DST_WE_Len                                  (5U)
#define DMA_LST_DST_WE_Msk                                  (0x1FU << DMA_LST_DST_WE_Pos)
#define DMA_LST_DST_WE                                      DMA_LST_DST_WE_Msk

#define DMA_LST_DST_Pos                                     (0U)
#define DMA_LST_DST_Len                                     (5U)
#define DMA_LST_DST_Msk                                     (0x1FU << DMA_LST_DST_Pos)
#define DMA_LST_DST                                         DMA_LST_DST_Msk

/*******************  Bit definition for DMA_CFG_REG register  ****************/
#define DMA_MODULE_CFG_EN_Pos                               (0U)
#define DMA_MODULE_CFG_EN_Len                               (1U)
#define DMA_MODULE_CFG_EN_Msk                               (0x1U << DMA_MODULE_CFG_EN_Pos)
#define DMA_MODULE_CFG_EN                                   DMA_MODULE_CFG_EN_Msk

/*******************  Bit definition for DMA_CH_EN_REG register  **************/
#define DMA_CH_WE_EN_Pos                                    (8U)
#define DMA_CH_WE_EN_Len                                    (5U)
#define DMA_CH_WE_EN_Msk                                    (0x1FU << DMA_CH_WE_EN_Pos)
#define DMA_CH_WE_EN                                        DMA_CH_WE_EN_Msk

#define DMA_CH_EN_Pos                                       (0U)
#define DMA_CH_EN_Len                                       (5U)
#define DMA_CH_EN_Msk                                       (0x1FU << DMA_CH_EN_Pos)
#define DMA_CH_EN                                           DMA_CH_EN_Msk

/*******************  Bit definition for DMA_ID_REG register  **************/
#define DMA_ID_Pos                                          (0U)
#define DMA_ID_Len                                          (32U)
#define DMA_ID_Msk                                          (0xFFFFFFFFU << DMA_ID_Pos)
#define DMA_ID                                              DMA_ID_Msk

/*******************  Bit definition for DMA_TEST_REG register  **************/
#define DMA_TEST_Pos                                        (0U)
#define DMA_TEST_Len                                        (1U)
#define DMA_TEST_Msk                                        (0x1U << DMA_TEST_Pos)
#define DMA_TEST                                            DMA_TEST_Msk

/*******************  Bit definition for DMA_LP_TIMEOUT_REG register  **************/
#define DMA_LP_TIMEOUT_Pos                                  (0U)
#define DMA_LP_TIMEOUT_Len                                  (8U)
#define DMA_LP_TIMEOUT_Msk                                  (0xFFU << DMA_LP_TIMEOUT_Pos)
#define DMA_LP_TIMEOUT                                      DMA_LP_TIMEOUT_Msk


/* ================================================================================================================= */
/* ================                                     DUAL_TIMER                                    ================ */
/* ================================================================================================================= */

/*******************  Bit definition for DUAL_TIMER_RELOAD register  ************/
#define DUAL_TIMER_RELOAD_RELOAD_Pos                          (0U)
#define DUAL_TIMER_RELOAD_RELOAD_Len                          (32U)
#define DUAL_TIMER_RELOAD_RELOAD_Msk                          (0xFFFFFFFFU)
#define DUAL_TIMER_RELOAD_RELOAD                              DUAL_TIMER_RELOAD_RELOAD_Msk

/*******************  Bit definition for DUAL_TIMER_VALUE register  *************/
#define DUAL_TIMER_VALUE_VALUE_Pos                            (0U)
#define DUAL_TIMER_VALUE_VALUE_Len                            (32U)
#define DUAL_TIMER_VALUE_VALUE_Msk                            (0xFFFFFFFFU)
#define DUAL_TIMER_VALUE_VALUE                                DUAL_TIMER_VALUE_VALUE_Msk

/*******************  Bit definition for DUAL_TIMER_CTRL register  **************/
#define DUAL_TIMER_CTRL_BLEPULSE2_INTEN_Pos                   (22U)
#define DUAL_TIMER_CTRL_BLEPULSE2_INTEN_Len                   (1U)
#define DUAL_TIMER_CTRL_BLEPULSE2_INTEN_Msk                   (0x1U << DUAL_TIMER_CTRL_BLEPULSE2_INTEN_Pos)
#define DUAL_TIMER_CTRL_BLEPULSE2_INTEN                       DUAL_TIMER_CTRL_BLEPULSE2_INTEN_Msk

#define DUAL_TIMER_CTRL_BLEPULSE1_INTEN_Pos                   (21U)
#define DUAL_TIMER_CTRL_BLEPULSE1_INTEN_Len                   (1U)
#define DUAL_TIMER_CTRL_BLEPULSE1_INTEN_Msk                   (0x1U << DUAL_TIMER_CTRL_BLEPULSE1_INTEN_Pos)
#define DUAL_TIMER_CTRL_BLEPULSE1_INTEN                       DUAL_TIMER_CTRL_BLEPULSE1_INTEN_Msk

#define DUAL_TIMER_CTRL_IOC_ACT_C2_INTEN_Pos                  (20U)
#define DUAL_TIMER_CTRL_IOC_ACT_C2_INTEN_Len                  (1U)
#define DUAL_TIMER_CTRL_IOC_ACT_C2_INTEN_Msk                  (0x1U << DUAL_TIMER_CTRL_IOC_ACT_C2_INTEN_Pos)
#define DUAL_TIMER_CTRL_IOC_ACT_C2_INTEN                      DUAL_TIMER_CTRL_IOC_ACT_C2_INTEN_Msk

#define DUAL_TIMER_CTRL_IOC_ACT_C1_INTEN_Pos                  (19U)
#define DUAL_TIMER_CTRL_IOC_ACT_C1_INTEN_Len                  (1U)
#define DUAL_TIMER_CTRL_IOC_ACT_C1_INTEN_Msk                  (0x1U << DUAL_TIMER_CTRL_IOC_ACT_C1_INTEN_Pos)
#define DUAL_TIMER_CTRL_IOC_ACT_C1_INTEN                      DUAL_TIMER_CTRL_IOC_ACT_C1_INTEN_Msk

#define DUAL_TIMER_CTRL_IOB_ACT_C2_INTEN_Pos                  (18U)
#define DUAL_TIMER_CTRL_IOB_ACT_C2_INTEN_Len                  (1U)
#define DUAL_TIMER_CTRL_IOB_ACT_C2_INTEN_Msk                  (0x1U << DUAL_TIMER_CTRL_IOB_ACT_C2_INTEN_Pos)
#define DUAL_TIMER_CTRL_IOB_ACT_C2_INTEN                      DUAL_TIMER_CTRL_IOB_ACT_C2_INTEN_Msk

#define DUAL_TIMER_CTRL_IOB_ACT_C1_INTEN_Pos                  (17U)
#define DUAL_TIMER_CTRL_IOB_ACT_C1_INTEN_Len                  (1U)
#define DUAL_TIMER_CTRL_IOB_ACT_C1_INTEN_Msk                  (0x1U << DUAL_TIMER_CTRL_IOB_ACT_C1_INTEN_Pos)
#define DUAL_TIMER_CTRL_IOB_ACT_C1_INTEN                      DUAL_TIMER_CTRL_IOB_ACT_C1_INTEN_Msk

#define DUAL_TIMER_CTRL_ACT_STOP_INTEN_Pos                    (16U)
#define DUAL_TIMER_CTRL_ACT_STOP_INTEN_Len                    (1U)
#define DUAL_TIMER_CTRL_ACT_STOP_INTEN_Msk                    (0x1U << DUAL_TIMER_CTRL_ACT_STOP_INTEN_Pos)
#define DUAL_TIMER_CTRL_ACT_STOP_INTEN                        DUAL_TIMER_CTRL_ACT_STOP_INTEN_Msk

#define DUAL_TIMER_CTRL_ACT_PERIOD_INTEN_Pos                  (15U)
#define DUAL_TIMER_CTRL_ACT_PERIOD_INTEN_Len                  (1U)
#define DUAL_TIMER_CTRL_ACT_PERIOD_INTEN_Msk                  (0x1U << DUAL_TIMER_CTRL_ACT_PERIOD_INTEN_Pos)
#define DUAL_TIMER_CTRL_ACT_PERIOD_INTEN                      DUAL_TIMER_CTRL_ACT_PERIOD_INTEN_Msk

#define DUAL_TIMER_CTRL_IOA_ACT_C2_INTEN_Pos                  (14U)
#define DUAL_TIMER_CTRL_IOA_ACT_C2_INTEN_Len                  (1U)
#define DUAL_TIMER_CTRL_IOA_ACT_C2_INTEN_Msk                  (0x1U << DUAL_TIMER_CTRL_IOA_ACT_C2_INTEN_Pos)
#define DUAL_TIMER_CTRL_IOA_ACT_C2_INTEN                      DUAL_TIMER_CTRL_IOA_ACT_C2_INTEN_Msk

#define DUAL_TIMER_CTRL_IOA_ACT_C1_INTEN_Pos                  (13U)
#define DUAL_TIMER_CTRL_IOA_ACT_C1_INTEN_Len                  (1U)
#define DUAL_TIMER_CTRL_IOA_ACT_C1_INTEN_Msk                  (0x1U << DUAL_TIMER_CTRL_IOA_ACT_C1_INTEN_Pos)
#define DUAL_TIMER_CTRL_IOA_ACT_C1_INTEN                      DUAL_TIMER_CTRL_IOA_ACT_C1_INTEN_Msk

#define DUAL_TIMER_CTRL_ACT_START_INTEN_Pos                   (12U)
#define DUAL_TIMER_CTRL_ACT_START_INTEN_Len                   (1U)
#define DUAL_TIMER_CTRL_ACT_START_INTEN_Msk                   (0x1U << DUAL_TIMER_CTRL_ACT_START_INTEN_Pos)
#define DUAL_TIMER_CTRL_ACT_START_INTEN                       DUAL_TIMER_CTRL_ACT_START_INTEN_Msk

#define DUAL_TIMER_CTRL_BLE_Pos                               (11U)
#define DUAL_TIMER_CTRL_BLE_Len                               (1U)
#define DUAL_TIMER_CTRL_BLE_Msk                               (0x1U << DUAL_TIMER_CTRL_BLE_Pos)
#define DUAL_TIMER_CTRL_BLE                                   DUAL_TIMER_CTRL_BLE_Msk

#define DUAL_TIMER_CTRL_IOC_Pos                               (10U)
#define DUAL_TIMER_CTRL_IOC_Len                               (1U)
#define DUAL_TIMER_CTRL_IOC_Msk                               (0x1U << DUAL_TIMER_CTRL_IOC_Pos)
#define DUAL_TIMER_CTRL_IOC                                   DUAL_TIMER_CTRL_IOC_Msk

#define DUAL_TIMER_CTRL_IOB_Pos                               (9U)
#define DUAL_TIMER_CTRL_IOB_Len                               (1U)
#define DUAL_TIMER_CTRL_IOB_Msk                               (0x1U << DUAL_TIMER_CTRL_IOB_Pos)
#define DUAL_TIMER_CTRL_IOB                                   DUAL_TIMER_CTRL_IOB_Msk

#define DUAL_TIMER_CTRL_IOA_Pos                               (8U)
#define DUAL_TIMER_CTRL_IOA_Len                               (1U)
#define DUAL_TIMER_CTRL_IOA_Msk                               (0x1U << DUAL_TIMER_CTRL_IOA_Pos)
#define DUAL_TIMER_CTRL_IOA                                   DUAL_TIMER_CTRL_IOA_Msk

#define DUAL_TIMER_CTRL_EN_Pos                                (7U)
#define DUAL_TIMER_CTRL_EN_Len                                (1U)
#define DUAL_TIMER_CTRL_EN_Msk                                (0x1U << DUAL_TIMER_CTRL_EN_Pos)
#define DUAL_TIMER_CTRL_EN                                    DUAL_TIMER_CTRL_EN_Msk

#define DUAL_TIMER_CTRL_MODE_Pos                              (6U)
#define DUAL_TIMER_CTRL_MODE_Len                              (1U)
#define DUAL_TIMER_CTRL_MODE_Msk                              (0x1U << DUAL_TIMER_CTRL_MODE_Pos)
#define DUAL_TIMER_CTRL_MODE                                  DUAL_TIMER_CTRL_MODE_Msk

#define DUAL_TIMER_CTRL_INTEN_Pos                             (5U)
#define DUAL_TIMER_CTRL_INTEN_Len                             (1U)
#define DUAL_TIMER_CTRL_INTEN_Msk                             (0x1U << DUAL_TIMER_CTRL_INTEN_Pos)
#define DUAL_TIMER_CTRL_INTEN                                 DUAL_TIMER_CTRL_INTEN_Msk

#define DUAL_TIMER_CTRL_PRE_Pos                               (2U)
#define DUAL_TIMER_CTRL_PRE_Len                               (2U)
#define DUAL_TIMER_CTRL_PRE_Msk                               (0x3U << DUAL_TIMER_CTRL_PRE_Pos)
#define DUAL_TIMER_CTRL_PRE                                   DUAL_TIMER_CTRL_PRE_Msk

#define DUAL_TIMER_CTRL_SIZE_Pos                              (1U)
#define DUAL_TIMER_CTRL_SIZE_Len                              (1U)
#define DUAL_TIMER_CTRL_SIZE_Msk                              (0x1U << DUAL_TIMER_CTRL_SIZE_Pos)
#define DUAL_TIMER_CTRL_SIZE                                  DUAL_TIMER_CTRL_SIZE_Msk

#define DUAL_TIMER_CTRL_ONESHOT_Pos                           (0U)
#define DUAL_TIMER_CTRL_ONESHOT_Len                           (1U)
#define DUAL_TIMER_CTRL_ONESHOT_Msk                           (0x1U << DUAL_TIMER_CTRL_ONESHOT_Pos)
#define DUAL_TIMER_CTRL_ONESHOT                               DUAL_TIMER_CTRL_ONESHOT_Msk

/*******************  Bit definition for DUAL_TIMER_INT_CLR register  ***********/
#define DUAL_TIMER_INT_CLR_Pos                                (0U)
#define DUAL_TIMER_INT_CLR_Len                                (32U)
#define DUAL_TIMER_INT_CLR_Msk                                (0xFFFFFFFFU)
#define DUAL_TIMER_INT_CLR                                    DUAL_TIMER_INT_CLR_Msk

/*******************  Bit definition for DUAL_TIMER_RAW_INT_STAT register  ******/
#define DUAL_TIMER_RIS_RTI_Pos                                (0U)
#define DUAL_TIMER_RIS_RTI_Len                                (1U)
#define DUAL_TIMER_RIS_RTI_Msk                                (0x1U << DUAL_TIMER_RIS_RTI_Pos)
#define DUAL_TIMER_RIS_RTI                                    DUAL_TIMER_RIS_RTI_Msk

/*******************  Bit definition for DUAL_TIMER_INT_STAT register  **********/
#define DUAL_TIMER_INT_BLEPULSE2_Pos                          (11U)
#define DUAL_TIMER_INT_BLEPULSE2_Len                          (1U)
#define DUAL_TIMER_INT_BLEPULSE2_Msk                          (0x1U << DUAL_TIMER_INT_BLEPULSE2_Pos)
#define DUAL_TIMER_INT_BLEPULSE2                              DUAL_TIMER_INT_BLEPULSE2_Msk

#define DUAL_TIMER_INT_BLEPULSE1_Pos                          (10U)
#define DUAL_TIMER_INT_BLEPULSE1_Len                          (1U)
#define DUAL_TIMER_INT_BLEPULSE1_Msk                          (0x1U << DUAL_TIMER_INT_BLEPULSE1_Pos)
#define DUAL_TIMER_INT_BLEPULSE1                              DUAL_TIMER_INT_BLEPULSE1_Msk

#define DUAL_TIMER_INT_IOC_ACT_C2_Pos                         (9U)
#define DUAL_TIMER_INT_IOC_ACT_C2_Len                         (1U)
#define DUAL_TIMER_INT_IOC_ACT_C2_Msk                         (0x1U << DUAL_TIMER_INT_IOC_ACT_C2_Pos)
#define DUAL_TIMER_INT_IOC_ACT_C2                             DUAL_TIMER_INT_IOC_ACT_C2_Msk

#define DUAL_TIMER_INT_IOC_ACT_C1_Pos                         (8U)
#define DUAL_TIMER_INT_IOC_ACT_C1_Len                         (1U)
#define DUAL_TIMER_INT_IOC_ACT_C1_Msk                         (0x1U << DUAL_TIMER_INT_IOC_ACT_C1_Pos)
#define DUAL_TIMER_INT_IOC_ACT_C1                             DUAL_TIMER_INT_IOC_ACT_C1_Msk

#define DUAL_TIMER_INT_IOB_ACT_C2_Pos                         (7U)
#define DUAL_TIMER_INT_IOB_ACT_C2_Len                         (1U)
#define DUAL_TIMER_INT_IOB_ACT_C2_Msk                         (0x1U << DUAL_TIMER_INT_IOB_ACT_C2_Pos)
#define DUAL_TIMER_INT_IOB_ACT_C2                             DUAL_TIMER_INT_IOB_ACT_C2_Msk

#define DUAL_TIMER_INT_IOB_ACT_C1_Pos                         (6U)
#define DUAL_TIMER_INT_IOB_ACT_C1_Len                         (1U)
#define DUAL_TIMER_INT_IOB_ACT_C1_Msk                         (0x1U << DUAL_TIMER_INT_IOB_ACT_C1_Pos)
#define DUAL_TIMER_INT_IOB_ACT_C1                             DUAL_TIMER_INT_IOB_ACT_C1_Msk

#define DUAL_TIMER_INT_ACT_STOP_Pos                           (5U)
#define DUAL_TIMER_INT_ACT_STOP_Len                           (1U)
#define DUAL_TIMER_INT_ACT_STOP_Msk                           (0x1U << DUAL_TIMER_INT_ACT_STOP_Pos)
#define DUAL_TIMER_INT_ACT_STOP                               DUAL_TIMER_INT_ACT_STOP_Msk

#define DUAL_TIMER_INT_ACT_PERIOD_Pos                         (4U)
#define DUAL_TIMER_INT_ACT_PERIOD_Len                         (1U)
#define DUAL_TIMER_INT_ACT_PERIOD_Msk                         (0x1U << DUAL_TIMER_INT_ACT_PERIOD_Pos)
#define DUAL_TIMER_INT_ACT_PERIOD                             DUAL_TIMER_INT_ACT_PERIOD_Msk

#define DUAL_TIMER_INT_IOA_ACT_C2_Pos                         (3U)
#define DUAL_TIMER_INT_IOA_ACT_C2_Len                         (1U)
#define DUAL_TIMER_INT_IOA_ACT_C2_Msk                         (0x1U << DUAL_TIMER_INT_IOA_ACT_C2_Pos)
#define DUAL_TIMER_INT_IOA_ACT_C2                             DUAL_TIMER_INT_IOA_ACT_C2_Msk

#define DUAL_TIMER_INT_IOA_ACT_C1_Pos                         (2U)
#define DUAL_TIMER_INT_IOA_ACT_C1_Len                         (1U)
#define DUAL_TIMER_INT_IOA_ACT_C1_Msk                         (0x1U << DUAL_TIMER_INT_IOA_ACT_C1_Pos)
#define DUAL_TIMER_INT_IOA_ACT_C1                             DUAL_TIMER_INT_IOA_ACT_C1_Msk

#define DUAL_TIMER_INT_ACT_START_Pos                          (1U)
#define DUAL_TIMER_INT_ACT_START_Len                          (1U)
#define DUAL_TIMER_INT_ACT_START_Msk                          (0x1U << DUAL_TIMER_INT_ACT_START_Pos)
#define DUAL_TIMER_INT_ACT_START                              DUAL_TIMER_INT_ACT_START_Msk

#define DUAL_TIMER_ISR_TI_Pos                                 (0U)
#define DUAL_TIMER_ISR_TI_Len                                 (1U)
#define DUAL_TIMER_ISR_TI_Msk                                 (0x1U << DUAL_TIMER_ISR_TI_Pos)
#define DUAL_TIMER_ISR_TI                                     DUAL_TIMER_ISR_TI_Msk

#define DUAL_TIMER_INT_STAT_Pos                               (0U)
#define DUAL_TIMER_INT_STAT_Len                               (12U)
#define DUAL_TIMER_INT_STAT_Msk                               (0xFFFU << DUAL_TIMER_INT_STAT_Pos)
#define DUAL_TIMER_INT_STAT                                   DUAL_TIMER_INT_STAT_Msk

/*******************  Bit definition for DUAL_TIMER_BGLOAD register  ************/
#define DUAL_TIMER_BLR_BL_Pos                                 (0U)
#define DUAL_TIMER_BLR_BL_Len                                 (32U)
#define DUAL_TIMER_BLR_BL_Msk                                 (0xFFFFFFFFU)
#define DUAL_TIMER_BLR_BL                                     DUAL_TIMER_BLR_BL_Msk

/*******************  Bit definition for DUAL_TIMER_COUNT_A1IO register  ********/
#define DUAL_TIMER_COUNT_A1IO_Pos                             (0U)
#define DUAL_TIMER_COUNT_A1IO_Len                             (32U)
#define DUAL_TIMER_COUNT_A1IO_Msk                             (0xFFFFFFFFU)
#define DUAL_TIMER_COUNT_A1IO                                 DUAL_TIMER_COUNT_A1IO_Msk

/*******************  Bit definition for DUAL_TIMER_COUNT_A2IO register  ********/
#define DUAL_TIMER_COUNT_A2IO_Pos                             (0U)
#define DUAL_TIMER_COUNT_A2IO_Len                             (32U)
#define DUAL_TIMER_COUNT_A2IO_Msk                             (0xFFFFFFFFU)
#define DUAL_TIMER_COUNT_A2IO                                 DUAL_TIMER_COUNT_A2IO_Msk

/*******************  Bit definition for DUAL_TIMER_COUNT_B1IO register  ********/
#define DUAL_TIMER_COUNT_B1IO_Pos                             (0U)
#define DUAL_TIMER_COUNT_B1IO_Len                             (32U)
#define DUAL_TIMER_COUNT_B1IO_Msk                             (0xFFFFFFFFU)
#define DUAL_TIMER_COUNT_B1IO                                 DUAL_TIMER_COUNT_B1IO_Msk

/*******************  Bit definition for DUAL_TIMER_COUNT_B2IO register  ********/
#define DUAL_TIMER_COUNT_B2IO_Pos                             (0U)
#define DUAL_TIMER_COUNT_B2IO_Len                             (32U)
#define DUAL_TIMER_COUNT_B2IO_Msk                             (0xFFFFFFFFU)
#define DUAL_TIMER_COUNT_B2IO                                 DUAL_TIMER_COUNT_B2IO_Msk

/*******************  Bit definition for DUAL_TIMER_COUNT_C1IO register  ********/
#define DUAL_TIMER_COUNT_C1IO_Pos                             (0U)
#define DUAL_TIMER_COUNT_C1IO_Len                             (32U)
#define DUAL_TIMER_COUNT_C1IO_Msk                             (0xFFFFFFFFU)
#define DUAL_TIMER_COUNT_C1IO                                 DUAL_TIMER_COUNT_C1IO_Msk

/*******************  Bit definition for DUAL_TIMER_COUNT_C2IO register  ********/
#define DUAL_TIMER_COUNT_C2IO_Pos                             (0U)
#define DUAL_TIMER_COUNT_C2IO_Len                             (32U)
#define DUAL_TIMER_COUNT_C2IO_Msk                             (0xFFFFFFFFU)
#define DUAL_TIMER_COUNT_C2IO                                 DUAL_TIMER_COUNT_C2IO_Msk

/*******************  Bit definition for DUAL_TIMER_IO_ACT_CTRL register  *******/
#define DUAL_TIMER_IOC_ACT_CTRL_STOP_Pos                      (28U)
#define DUAL_TIMER_IOC_ACT_CTRL_STOP_Len                      (2U)
#define DUAL_TIMER_IOC_ACT_CTRL_STOP_Msk                      (0x3U << DUAL_TIMER_IOC_ACT_CTRL_STOP_Pos)
#define DUAL_TIMER_IOC_ACT_CTRL_STOP                          DUAL_TIMER_IOC_ACT_CTRL_STOP_Msk

#define DUAL_TIMER_IOC_ACT_CTRL_PERIOD_Pos                    (26U)
#define DUAL_TIMER_IOC_ACT_CTRL_PERIOD_Len                    (2U)
#define DUAL_TIMER_IOC_ACT_CTRL_PERIOD_Msk                    (0x3U << DUAL_TIMER_IOC_ACT_CTRL_PERIOD_Pos)
#define DUAL_TIMER_IOC_ACT_CTRL_PERIOD                        DUAL_TIMER_IOC_ACT_CTRL_PERIOD_Msk

#define DUAL_TIMER_IOC_ACT_CTRL_C2_Pos                        (24U)
#define DUAL_TIMER_IOC_ACT_CTRL_C2_Len                        (2U)
#define DUAL_TIMER_IOC_ACT_CTRL_C2_Msk                        (0x3U << DUAL_TIMER_IOC_ACT_CTRL_C2_Pos)
#define DUAL_TIMER_IOC_ACT_CTRL_C2                            DUAL_TIMER_IOC_ACT_CTRL_C2_Msk

#define DUAL_TIMER_IOC_ACT_CTRL_C1_Pos                        (22U)
#define DUAL_TIMER_IOC_ACT_CTRL_C1_Len                        (2U)
#define DUAL_TIMER_IOC_ACT_CTRL_C1_Msk                        (0x3U << DUAL_TIMER_IOC_ACT_CTRL_C1_Pos)
#define DUAL_TIMER_IOC_ACT_CTRL_C1                            DUAL_TIMER_IOC_ACT_CTRL_C1_Msk

#define DUAL_TIMER_IOC_ACT_CTRL_START_Pos                     (20U)
#define DUAL_TIMER_IOC_ACT_CTRL_START_Len                     (2U)
#define DUAL_TIMER_IOC_ACT_CTRL_START_Msk                     (0x3U << DUAL_TIMER_IOC_ACT_CTRL_START_Pos)
#define DUAL_TIMER_IOC_ACT_CTRL_START                         DUAL_TIMER_IOC_ACT_CTRL_START_Msk

#define DUAL_TIMER_IOB_ACT_CTRL_STOP_Pos                      (18U)
#define DUAL_TIMER_IOB_ACT_CTRL_STOP_Len                      (2U)
#define DUAL_TIMER_IOB_ACT_CTRL_STOP_Msk                      (0x3U << DUAL_TIMER_IOB_ACT_CTRL_STOP_Pos)
#define DUAL_TIMER_IOB_ACT_CTRL_STOP                          DUAL_TIMER_IOB_ACT_CTRL_STOP_Msk

#define DUAL_TIMER_IOB_ACT_CTRL_PERIOD_Pos                    (16U)
#define DUAL_TIMER_IOB_ACT_CTRL_PERIOD_Len                    (2U)
#define DUAL_TIMER_IOB_ACT_CTRL_PERIOD_Msk                    (0x3U << DUAL_TIMER_IOB_ACT_CTRL_PERIOD_Pos)
#define DUAL_TIMER_IOB_ACT_CTRL_PERIOD                        DUAL_TIMER_IOB_ACT_CTRL_PERIOD_Msk

#define DUAL_TIMER_IOB_ACT_CTRL_C2_Pos                        (14U)
#define DUAL_TIMER_IOB_ACT_CTRL_C2_Len                        (2U)
#define DUAL_TIMER_IOB_ACT_CTRL_C2_Msk                        (0x3U << DUAL_TIMER_IOB_ACT_CTRL_C2_Pos)
#define DUAL_TIMER_IOB_ACT_CTRL_C2                            DUAL_TIMER_IOB_ACT_CTRL_C2_Msk

#define DUAL_TIMER_IOB_ACT_CTRL_C1_Pos                        (12U)
#define DUAL_TIMER_IOB_ACT_CTRL_C1_Len                        (2U)
#define DUAL_TIMER_IOB_ACT_CTRL_C1_Msk                        (0x3U << DUAL_TIMER_IOB_ACT_CTRL_C1_Pos)
#define DUAL_TIMER_IOB_ACT_CTRL_C1                            DUAL_TIMER_IOB_ACT_CTRL_C1_Msk

#define DUAL_TIMER_IOB_ACT_CTRL_START_Pos                     (10U)
#define DUAL_TIMER_IOB_ACT_CTRL_START_Len                     (2U)
#define DUAL_TIMER_IOB_ACT_CTRL_START_Msk                     (0x3U << DUAL_TIMER_IOB_ACT_CTRL_START_Pos)
#define DUAL_TIMER_IOB_ACT_CTRL_START                         DUAL_TIMER_IOB_ACT_CTRL_START_Msk

#define DUAL_TIMER_IOA_ACT_CTRL_STOP_Pos                      (8U)
#define DUAL_TIMER_IOA_ACT_CTRL_STOP_Len                      (2U)
#define DUAL_TIMER_IOA_ACT_CTRL_STOP_Msk                      (0x3U << DUAL_TIMER_IOA_ACT_CTRL_STOP_Pos)
#define DUAL_TIMER_IOA_ACT_CTRL_STOP                          DUAL_TIMER_IOA_ACT_CTRL_STOP_Msk

#define DUAL_TIMER_IOA_ACT_CTRL_PERIOD_Pos                    (6U)
#define DUAL_TIMER_IOA_ACT_CTRL_PERIOD_Len                    (2U)
#define DUAL_TIMER_IOA_ACT_CTRL_PERIOD_Msk                    (0x3U << DUAL_TIMER_IOA_ACT_CTRL_PERIOD_Pos)
#define DUAL_TIMER_IOA_ACT_CTRL_PERIOD                        DUAL_TIMER_IOA_ACT_CTRL_PERIOD_Msk

#define DUAL_TIMER_IOA_ACT_CTRL_C2_Pos                        (4U)
#define DUAL_TIMER_IOA_ACT_CTRL_C2_Len                        (2U)
#define DUAL_TIMER_IOA_ACT_CTRL_C2_Msk                        (0x3U << DUAL_TIMER_IOA_ACT_CTRL_C2_Pos)
#define DUAL_TIMER_IOA_ACT_CTRL_C2                            DUAL_TIMER_IOA_ACT_CTRL_C2_Msk

#define DUAL_TIMER_IOA_ACT_CTRL_C1_Pos                        (2U)
#define DUAL_TIMER_IOA_ACT_CTRL_C1_Len                        (2U)
#define DUAL_TIMER_IOA_ACT_CTRL_C1_Msk                        (0x3U << DUAL_TIMER_IOA_ACT_CTRL_C1_Pos)
#define DUAL_TIMER_IOA_ACT_CTRL_C1                            DUAL_TIMER_IOA_ACT_CTRL_C1_Msk

#define DUAL_TIMER_IOA_ACT_CTRL_START_Pos                     (0U)
#define DUAL_TIMER_IOA_ACT_CTRL_START_Len                     (2U)
#define DUAL_TIMER_IOA_ACT_CTRL_START_Msk                     (0x3U << DUAL_TIMER_IOA_ACT_CTRL_START_Pos)
#define DUAL_TIMER_IOA_ACT_CTRL_START                         DUAL_TIMER_IOA_ACT_CTRL_START_Msk

/*******************  Bit definition for DUAL_TIMER_IO_INIT_SET register  *******/
#define DUAL_TIMER_IOC_ACT_INIT_Pos                           (2U)
#define DUAL_TIMER_IOC_ACT_INIT_Len                           (1U)
#define DUAL_TIMER_IOC_ACT_INIT_Msk                           (0x1U << DUAL_TIMER_IOC_ACT_INIT_Pos)
#define DUAL_TIMER_IOC_ACT_INIT                               DUAL_TIMER_IOC_ACT_INIT_Msk

#define DUAL_TIMER_IOB_ACT_INIT_Pos                           (1U)
#define DUAL_TIMER_IOB_ACT_INIT_Len                           (1U)
#define DUAL_TIMER_IOB_ACT_INIT_Msk                           (0x1U << DUAL_TIMER_IOB_ACT_INIT_Pos)
#define DUAL_TIMER_IOB_ACT_INIT                               DUAL_TIMER_IOB_ACT_INIT_Msk

#define DUAL_TIMER_IOA_ACT_INIT_Pos                           (0U)
#define DUAL_TIMER_IOA_ACT_INIT_Len                           (1U)
#define DUAL_TIMER_IOA_ACT_INIT_Msk                           (0x1U << DUAL_TIMER_IOA_ACT_INIT_Pos)
#define DUAL_TIMER_IOA_ACT_INIT                               DUAL_TIMER_IOA_ACT_INIT_Msk

/*******************  Bit definition for DUAL_TIMER_TP_LOAD register  ***********/
#define DUAL_TIMER_TP_LOAD_Pos                                (0U)
#define DUAL_TIMER_TP_LOAD_Len                                (32U)
#define DUAL_TIMER_TP_LOAD_Msk                                (0xFFFFFFFFU)
#define DUAL_TIMER_TP_LOAD                                    DUAL_TIMER_TP_LOAD_Msk

/*******************  Bit definition for DUAL_TIMER_BLE_COUNT1 register  ********/
#define DUAL_TIMER_BLE_COUNT1_Pos                             (0U)
#define DUAL_TIMER_BLE_COUNT1_Len                             (32U)
#define DUAL_TIMER_BLE_COUNT1_Msk                             (0xFFFFFFFFU)
#define DUAL_TIMER_BLE_COUNT1                                 DUAL_TIMER_BLE_COUNT1_Msk

/*******************  Bit definition for DUAL_TIMER_BLE_COUNT2 register  ********/
#define DUAL_TIMER_BLE_COUNT2_Pos                             (0U)
#define DUAL_TIMER_BLE_COUNT2_Len                             (32U)
#define DUAL_TIMER_BLE_COUNT2_Msk                             (0xFFFFFFFFU)
#define DUAL_TIMER_BLE_COUNT2                                 DUAL_TIMER_BLE_COUNT2_Msk

/*******************  Bit definition for DUAL_TIMER_BLE_PULSEWIDTH register  ****/
#define DUAL_TIMER_BLE_PULSEWIDTH_Pos                         (0U)
#define DUAL_TIMER_BLE_PULSEWIDTH_Len                         (6U)
#define DUAL_TIMER_BLE_PULSEWIDTH_Msk                         (0x3FU << DUAL_TIMER_BLE_PULSEWIDTH_Pos)
#define DUAL_TIMER_BLE_PULSEWIDTH                             DUAL_TIMER_BLE_PULSEWIDTH_Msk

/*******************  Bit definition for DUAL_TIMER_PERIOD_COUNT register  ***********/
#define DUAL_TIMER_PERIOD_COUNT_Pos                           (0U)
#define DUAL_TIMER_PERIOD_COUNT_Len                           (16U)
#define DUAL_TIMER_PERIOD_COUNT_Msk                           (0xFFFFU << DUAL_TIMER_PERIOD_COUNT_Pos)
#define DUAL_TIMER_PERIOD_COUNT                               DUAL_TIMER_PERIOD_COUNT_Msk

/*******************  Bit definition for DUAL_TIMER_IO_BLE_INTCLR register  *******/
#define DUAL_TIMER_IO_ACT_ALL_INTCLR_Pos                      (11U)
#define DUAL_TIMER_IO_ACT_ALL_INTCLR_Len                      (1U)
#define DUAL_TIMER_IO_ACT_ALL_INTCLR_Msk                      (0x1U << DUAL_TIMER_IO_ACT_ALL_INTCLR_Pos)
#define DUAL_TIMER_IO_ACT_ALL_INTCLR                          DUAL_TIMER_IO_ACT_ALL_INTCLR_Msk

#define DUAL_TIMER_BLEPULSE2_INTCLR_Pos                       (10U)
#define DUAL_TIMER_BLEPULSE2_INTCLR_Len                       (1U)
#define DUAL_TIMER_BLEPULSE2_INTCLR_Msk                       (0x1U << DUAL_TIMER_BLEPULSE2_INTCLR_Pos)
#define DUAL_TIMER_BLEPULSE2_INTCLR                           DUAL_TIMER_BLEPULSE2_INTCLR_Msk

#define DUAL_TIMER_BLEPULSE1_INTCLR_Pos                       (9U)
#define DUAL_TIMER_BLEPULSE1_INTCLR_Len                       (1U)
#define DUAL_TIMER_BLEPULSE1_INTCLR_Msk                       (0x1U << DUAL_TIMER_BLEPULSE1_INTCLR_Pos)
#define DUAL_TIMER_BLEPULSE1_INTCLR                           DUAL_TIMER_BLEPULSE1_INTCLR_Msk

#define DUAL_TIMER_IOC_ACT_C2_INTCLR_Pos                      (8U)
#define DUAL_TIMER_IOC_ACT_C2_INTCLR_Len                      (1U)
#define DUAL_TIMER_IOC_ACT_C2_INTCLR_Msk                      (0x1U << DUAL_TIMER_IOC_ACT_C2_INTCLR_Pos)
#define DUAL_TIMER_IOC_ACT_C2_INTCLR                          DUAL_TIMER_IOC_ACT_C2_INTCLR_Msk

#define DUAL_TIMER_IOC_ACT_C1_INTCLR_Pos                      (7U)
#define DUAL_TIMER_IOC_ACT_C1_INTCLR_Len                      (1U)
#define DUAL_TIMER_IOC_ACT_C1_INTCLR_Msk                      (0x1U << DUAL_TIMER_IOC_ACT_C1_INTCLR_Pos)
#define DUAL_TIMER_IOC_ACT_C1_INTCLR                          DUAL_TIMER_IOC_ACT_C1_INTCLR_Msk

#define DUAL_TIMER_IOB_ACT_C2_INTCLR_Pos                      (6U)
#define DUAL_TIMER_IOB_ACT_C2_INTCLR_Len                      (1U)
#define DUAL_TIMER_IOB_ACT_C2_INTCLR_Msk                      (0x1U << DUAL_TIMER_IOB_ACT_C2_INTCLR_Pos)
#define DUAL_TIMER_IOB_ACT_C2_INTCLR                          DUAL_TIMER_IOB_ACT_C2_INTCLR_Msk

#define DUAL_TIMER_IOB_ACT_C1_INTCLR_Pos                      (5U)
#define DUAL_TIMER_IOB_ACT_C1_INTCLR_Len                      (1U)
#define DUAL_TIMER_IOB_ACT_C1_INTCLR_Msk                      (0x1U << DUAL_TIMER_IOB_ACT_C1_INTCLR_Pos)
#define DUAL_TIMER_IOB_ACT_C1_INTCLR                          DUAL_TIMER_IOB_ACT_C1_INTCLR_Msk

#define DUAL_TIMER_ACT_STOP_INTCLR_Pos                        (4U)
#define DUAL_TIMER_ACT_STOP_INTCLR_Len                        (1U)
#define DUAL_TIMER_ACT_STOP_INTCLR_Msk                        (0x1U << DUAL_TIMER_ACT_STOP_INTCLR_Pos)
#define DUAL_TIMER_ACT_STOP_INTCLR                            DUAL_TIMER_ACT_STOP_INTCLR_Msk

#define DUAL_TIMER_ACT_PERIOD_INTCLR_Pos                      (3U)
#define DUAL_TIMER_ACT_PERIOD_INTCLR_Len                      (1U)
#define DUAL_TIMER_ACT_PERIOD_INTCLR_Msk                      (0x1U << DUAL_TIMER_ACT_PERIOD_INTCLR_Pos)
#define DUAL_TIMER_ACT_PERIOD_INTCLR                          DUAL_TIMER_ACT_PERIOD_INTCLR_Msk

#define DUAL_TIMER_IOA_ACT_C2_INTCLR_Pos                      (2U)
#define DUAL_TIMER_IOA_ACT_C2_INTCLR_Len                      (1U)
#define DUAL_TIMER_IOA_ACT_C2_INTCLR_Msk                      (0x1U << DUAL_TIMER_IOA_ACT_C2_INTCLR_Pos)
#define DUAL_TIMER_IOA_ACT_C2_INTCLR                          DUAL_TIMER_IOA_ACT_C2_INTCLR_Msk

#define DUAL_TIMER_IOA_ACT_C1_INTCLR_Pos                      (1U)
#define DUAL_TIMER_IOA_ACT_C1_INTCLR_Len                      (1U)
#define DUAL_TIMER_IOA_ACT_C1_INTCLR_Msk                      (0x1U << DUAL_TIMER_IOA_ACT_C1_INTCLR_Pos)
#define DUAL_TIMER_IOA_ACT_C1_INTCLR                          DUAL_TIMER_IOA_ACT_C1_INTCLR_Msk

#define DUAL_TIMER_ACT_START_INTCLR_Pos                       (0U)
#define DUAL_TIMER_ACT_START_INTCLR_Len                       (1U)
#define DUAL_TIMER_ACT_START_INTCLR_Msk                       (0x1U << DUAL_TIMER_ACT_START_INTCLR_Pos)
#define DUAL_TIMER_ACT_START_INTCLR                           DUAL_TIMER_ACT_START_INTCLR_Msk


/* ================================================================================================================= */
/* ================                                        GPIO                                     ================ */
/* ================================================================================================================= */

/*******************  Bit definition for GPIO_DATA register  ******************/
#define GPIO_DATA_Pos                                       (0U)
#define GPIO_DATA_Len                                       (16U)
#define GPIO_DATA_Msk                                       (0xFFFFU << GPIO_DATA_Pos)
#define GPIO_DATA                                           GPIO_DATA_Msk          /**< Data */

/*******************  Bit definition for GPIO_DATAOUT register  ***************/
#define GPIO_DATAOUT_Pos                                    (0U)
#define GPIO_DATAOUT_Len                                    (16U)
#define GPIO_DATAOUT_Msk                                    (0xFFFFU << GPIO_DATAOUT_Pos)
#define GPIO_DATAOUT                                        GPIO_DATAOUT_Msk    /**< Data Output */

/*******************  Bit definition for GPIO_OUTENSET register  ***************/
#define GPIO_OUTENSET_Pos                                   (0U)
#define GPIO_OUTENSET_Len                                   (16U)
#define GPIO_OUTENSET_Msk                                   (0xFFFFU << GPIO_OUTENSET_Pos)
#define GPIO_OUTENSET                                       GPIO_OUTENSET_Msk    /**< Data Output Enable Set*/

/*******************  Bit definition for GPIO_OUTENCLR register  ***************/
#define GPIO_OUTENCLR_Pos                                   (0U)
#define GPIO_OUTENCLR_Len                                   (16U)
#define GPIO_OUTENCLR_Msk                                   (0xFFFFU << GPIO_OUTENCLR_Pos)
#define GPIO_OUTENCLR                                       GPIO_OUTENCLR_Msk    /**< Data Output Enable Clear */

/*******************  Bit definition for GPIO_INTENSET register  ***************/
#define GPIO_INTENSET_Pos                                   (0U)
#define GPIO_INTENSET_Len                                   (16U)
#define GPIO_INTENSET_Msk                                   (0xFFFFU << GPIO_INTENSET_Pos)
#define GPIO_INTENSET                                       GPIO_INTENSET_Msk    /**< Interrupt Enable Set */

/*******************  Bit definition for GPIO_INTENCLR register  ***************/
#define GPIO_INTENCLR_Pos                                   (0U)
#define GPIO_INTENCLR_Len                                   (16U)
#define GPIO_INTENCLR_Msk                                   (0xFFFFU << GPIO_INTENCLR_Pos)
#define GPIO_INTENCLR                                       GPIO_INTENCLR_Msk    /**< Interrupt Enable clear */

/*******************  Bit definition for GPIO_INTTYPESET register  ***************/
#define GPIO_INTTYPESET_Pos                                 (0U)
#define GPIO_INTTYPESET_Len                                 (16U)
#define GPIO_INTTYPESET_Msk                                 (0xFFFFU << GPIO_INTTYPESET_Pos)
#define GPIO_INTTYPESET                                     GPIO_INTTYPESET_Msk    /**< Interrupt Type Set */

/*******************  Bit definition for GPIO_INTTYPECLR register  ***************/
#define GPIO_INTTYPECLR_Pos                                 (0U)
#define GPIO_INTTYPECLR_Len                                 (16U)
#define GPIO_INTTYPECLR_Msk                                 (0xFFFFU << GPIO_INTTYPECLR_Pos)
#define GPIO_INTTYPECLR                                     GPIO_INTTYPECLR_Msk    /**< Interrupt Type Clear */

/*******************  Bit definition for GPIO_INTPOLSET register  ***************/
#define GPIO_INTPOLSET_Pos                                  (0U)
#define GPIO_INTPOLSET_Len                                  (16U)
#define GPIO_INTPOLSET_Msk                                  (0xFFFFU << GPIO_INTPOLSET_Pos)
#define GPIO_INTPOLSET                                      GPIO_INTPOLSET_Msk    /**< Interrupt Polarity-level Set */

/*******************  Bit definition for GPIO_INTPOLCLR register  ***************/
#define GPIO_INTPOLCLR_Pos                                  (0U)
#define GPIO_INTPOLCLR_Len                                  (16U)
#define GPIO_INTPOLCLR_Msk                                  (0xFFFFU << GPIO_INTPOLCLR_Pos)
#define GPIO_INTPOLCLR                                      GPIO_INTPOLCLR_Msk    /**< Interrupt Polarity-level Clear */

/*******************  Bit definition for GPIO_INTSTAT register  ***************/
#define GPIO_INTSTAT_Pos                                    (0U)
#define GPIO_INTSTAT_Len                                    (16U)
#define GPIO_INTSTAT_Msk                                    (0xFFFFU << GPIO_INTSTAT_Pos)
#define GPIO_INTSTAT                                        GPIO_INTSTAT_Msk    /**< Interrupt Status */

/*******************  Bit definition for GPIO_MASKLOWBYTE register  ***********/
#define GPIO_MASKLOWBYTE_DATA_Pos                           (0U)
#define GPIO_MASKLOWBYTE_DATA_Len                           (8U)
#define GPIO_MASKLOWBYTE_DATA_Msk                           (0xFFU << GPIO_MASKLOWBYTE_DATA_Pos)
#define GPIO_MASKLOWBYTE_DATA                               GPIO_MASKLOWBYTE_DATA_Msk   /**< Lower eight bits masked access */

/*******************  Bit definition for GPIO_MASKLOWBYTE register  ***********/
#define GPIO_MASKHIGHBYTE_DATA_Pos                          (8U)
#define GPIO_MASKHIGHBYTE_DATA_Len                          (8U)
#define GPIO_MASKHIGHBYTE_DATA_Msk                          (0xFFU << GPIO_MASKHIGHBYTE_DATA_Pos)
#define GPIO_MASKHIGHBYTE_DATA                              GPIO_MASKHIGHBYTE_DATA   /**< Higher eight bits masked access */


/* ================================================================================================================= */
/* ================                                       HMAC                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for HMAC_CTRL register  *******************/
#define HMAC_CTRL_EN_POS                                    (0U)
#define HMAC_CTRL_EN_Len                                    (1U)
#define HMAC_CTRL_EN_Msk                                    (0x1UL << HMAC_CTRL_EN_POS)
#define HMAC_CTRL_EN                                        HMAC_CTRL_EN_Msk

#define HMAC_CTRL_DMA_START_POS                             (1U)
#define HMAC_CTRL_DMA_START_Len                             (1U)
#define HMAC_CTRL_DMA_START_Msk                             (0x1UL << HMAC_CTRL_DMA_START_POS)
#define HMAC_CTRL_DMA_START                                 HMAC_CTRL_DMA_START_Msk

#define HMAC_CTRL_KEY_EN_POS                                (2U)
#define HMAC_CTRL_KEY_EN_Len                                (1U)
#define HMAC_CTRL_KEY_EN_Msk                                (0x1UL << HMAC_CTRL_KEY_EN_POS)
#define HMAC_CTRL_KEY_EN                                    HMAC_CTRL_KEY_EN_Msk

#define HMAC_CTRL_LST_TX_POS                                (3U)
#define HMAC_CTRL_LST_TX_Len                                (1U)
#define HMAC_CTRL_LST_TX_Msk                                (0x1UL << HMAC_CTRL_LST_TX_POS)
#define HMAC_CTRL_LST_TX                                    HMAC_CTRL_LST_TX_Msk

/*******************  Bit definition for HMAC_CFG register  *******************/
#define HMAC_CFG_HASH_POS                                   (0U)
#define HMAC_CFG_HASH_Len                                   (1U)
#define HMAC_CFG_HASH_Msk                                   (0x1UL << HMAC_CFG_HASH_POS)
#define HMAC_CFG_HASH                                       HMAC_CFG_HASH_Msk

#define HMAC_CFG_ENDIAN_POS                                 (1U)
#define HMAC_CFG_ENDIAN_Len                                 (1U)
#define HMAC_CFG_ENDIAN_Msk                                 (0x1UL << HMAC_CFG_ENDIAN_POS)
#define HMAC_CFG_ENDIAN                                     HMAC_CFG_ENDIAN_Msk

#define HMAC_CFG_KEY_TYPE_POS                               (2U)
#define HMAC_CFG_KEY_TYPE_Len                               (2U)
#define HMAC_CFG_KEY_TYPE_Msk                               (0x3UL << HMAC_CFG_KEY_TYPE_POS)
#define HMAC_CFG_KEY_TYPE                                   HMAC_CFG_KEY_TYPE_Msk

#define HMAC_CFG_CALC_TYPE_POS                              (4U)
#define HMAC_CFG_CALC_TYPE_Len                              (1U)
#define HMAC_CFG_CALC_TYPE_Msk                              (0x1UL << HMAC_CFG_CALC_TYPE_POS)
#define HMAC_CFG_CALC_TYPE                                  HMAC_CFG_CALC_TYPE_Msk

#define HMAC_CFG_PRIVT_MODE_POS                             (5U)
#define HMAC_CFG_PRIVT_MODE_Len                             (1U)
#define HMAC_CFG_PRIVT_MODE_Msk                             (0x1UL << HMAC_CFG_PRIVT_MODE_POS)
#define HMAC_CFG_PRIVT_MODE                                 HMAC_CFG_PRIVT_MODE_Msk

/*******************  Bit definition for HMAC_STAT register  *******************/
#define HMAC_STAT_HASH_READY_POS                            (0U)
#define HMAC_STAT_HASH_READY_Len                            (1U)
#define HMAC_STAT_HASH_READY_Msk                            (0x1UL << HMAC_STAT_HASH_READY_POS)
#define HMAC_STAT_HASH_READY                                HMAC_STAT_HASH_READY_Msk

#define HMAC_STAT_DMA_MSG_DONE_POS                          (1U)
#define HMAC_STAT_DMA_MSG_DONE_Len                          (1U)
#define HMAC_STAT_DMA_MSG_DONE_Msk                          (0x1UL << HMAC_STAT_DMA_MSG_DONE_POS)
#define HMAC_STAT_DMA_MSG_DONE                              HMAC_STAT_DMA_MSG_DONE_Msk

#define HMAC_STAT_DMA_TX_ERR_POS                            (2U)
#define HMAC_STAT_DMA_TX_ERR_Len                            (1U)
#define HMAC_STAT_DMA_TX_ERR_Msk                            (0x1UL << HMAC_STAT_DMA_TX_ERR_POS)
#define HMAC_STAT_DMA_TX_ERR                                HMAC_STAT_DMA_TX_ERR_Msk

#define HMAC_STAT_KEY_VALID_POS                             (3U)
#define HMAC_STAT_KEY_VALID_Len                             (1U)
#define HMAC_STAT_KEY_VALID_Msk                             (0x1UL << HMAC_STAT_KEY_VALID_POS)
#define HMAC_STAT_KEY_VALID                                 HMAC_STAT_KEY_VALID_Msk

#define HMAC_STAT_HMAC_READY_POS                            (4U)
#define HMAC_STAT_HMAC_READY_Len                            (1U)
#define HMAC_STAT_HMAC_READY_Msk                            (0x1UL << HMAC_STAT_HMAC_READY_POS)
#define HMAC_STAT_HMAC_READY                                HMAC_STAT_HMAC_READY_Msk

#define HMAC_STAT_DMA_TX_DONE_POS                           (5U)
#define HMAC_STAT_DMA_TX_DONE_Len                           (1U)
#define HMAC_STAT_DMA_TX_DONE_Msk                           (0x1UL << HMAC_STAT_DMA_TX_DONE_POS)
#define HMAC_STAT_DMA_TX_DONE                               HMAC_STAT_DMA_TX_DONE_Msk

/*******************  Bit definition for HMAC_XFE_SIZE register  *******************/
#define HMAC_XFE_SIZE_SIZE_POS                              (0U)
#define HMAC_XFE_SIZE_SIZE_Len                              (15U)
#define HMAC_XFE_SIZE_SIZE_Msk                              (0x7FFFUL << HMAC_XFE_SIZE_SIZE_POS)
#define HMAC_XFE_SIZE_SIZE                                  HMAC_XFE_SIZE_SIZE_Msk

/*******************  Bit definition for HMAC_INT register  *******************/
#define HMAC_INT_DONE_POS                                   (0U)
#define HMAC_INT_DONE_Len                                   (1U)
#define HMAC_INT_DONE_Msk                                   (0x1UL << HMAC_INT_DONE_POS)
#define HMAC_INT_DONE                                       HMAC_INT_DONE_Msk

#define HMAC_INT_EN_POS                                     (1U)
#define HMAC_INT_EN_Len                                     (1U)
#define HMAC_INT_EN_Msk                                     (0x1UL << HMAC_INT_EN_POS)
#define HMAC_INT_EN                                         HMAC_INT_EN_Msk

/*******************  Bit definition for HMAC_RD_START_ADDR register  *******************/
#define HMAC_RD_START_ADDR_ADDR_POS                         (0U)
#define HMAC_RD_START_ADDR_ADDR_Len                         (32U)
#define HMAC_RD_START_ADDR_ADDR_Msk                         (0xFFFFFFFFUL << HMAC_RD_START_ADDR_ADDR_POS)
#define HMAC_RD_START_ADDR_ADDR                             HMAC_RD_START_ADDR_ADDR_Msk

/*******************  Bit definition for HMAC_WR_START_ADDR register  *******************/
#define HMAC_WR_START_ADDR_ADDR_POS                         (0U)
#define HMAC_WR_START_ADDR_ADDR_Len                         (32U)
#define HMAC_WR_START_ADDR_ADDR_Msk                         (0xFFFFFFFFUL << HMAC_WR_START_ADDR_ADDR_POS)
#define HMAC_WR_START_ADDR_ADDR                             HMAC_WR_START_ADDR_ADDR_Msk

/*******************  Bit definition for HMAC_USER_HASH_0 register  *******************/
#define HMAC_USER_HASH_0_HASH_0_POS                         (0U)
#define HMAC_USER_HASH_0_HASH_0_Len                         (32U)
#define HMAC_USER_HASH_0_HASH_0_Msk                         (0xFFFFFFFFUL << HMAC_USER_HASH_0_HASH_0_POS)
#define HMAC_USER_HASH_0_HASH_0                             HMAC_USER_HASH_0_HASH_0_Msk

/*******************  Bit definition for HMAC_USER_HASH_1 register  *******************/
#define HMAC_USER_HASH_1_HASH_1_POS                         (0U)
#define HMAC_USER_HASH_1_HASH_1_Len                         (32U)
#define HMAC_USER_HASH_1_HASH_1_Msk                         (0xFFFFFFFFUL << HMAC_USER_HASH_1_HASH_1_POS)
#define HMAC_USER_HASH_1_HASH_1                             HMAC_USER_HASH_1_HASH_1_Msk

/*******************  Bit definition for HMAC_USER_HASH_2 register  *******************/
#define HMAC_USER_HASH_2_HASH_2_POS                         (0U)
#define HMAC_USER_HASH_2_HASH_2_Len                         (32U)
#define HMAC_USER_HASH_2_HASH_2_Msk                         (0xFFFFFFFFUL << HMAC_USER_HASH_2_HASH_2_POS)
#define HMAC_USER_HASH_2_HASH_2                             HMAC_USER_HASH_2_HASH_2_Msk

/*******************  Bit definition for HMAC_USER_HASH_3 register  *******************/
#define HMAC_USER_HASH_3_HASH_3_POS                         (0U)
#define HMAC_USER_HASH_3_HASH_3_Len                         (32U)
#define HMAC_USER_HASH_3_HASH_3_Msk                         (0xFFFFFFFFUL << HMAC_USER_HASH_3_HASH_3_POS)
#define HMAC_USER_HASH_3_HASH_3                             HMAC_USER_HASH_3_HASH_3_Msk

/*******************  Bit definition for HMAC_USER_HASH_4 register  *******************/
#define HMAC_USER_HASH_4_HASH_4_POS                         (0U)
#define HMAC_USER_HASH_4_HASH_4_Len                         (32U)
#define HMAC_USER_HASH_4_HASH_4_Msk                         (0xFFFFFFFFUL << HMAC_USER_HASH_4_HASH_4_POS)
#define HMAC_USER_HASH_4_HASH_4                             HMAC_USER_HASH_4_HASH_4_Msk

/*******************  Bit definition for HMAC_USER_HASH_5 register  *******************/
#define HMAC_USER_HASH_5_HASH_5_POS                         (0U)
#define HMAC_USER_HASH_5_HASH_5_Len                         (32U)
#define HMAC_USER_HASH_5_HASH_5_Msk                         (0xFFFFFFFFUL << HMAC_USER_HASH_5_HASH_5_POS)
#define HMAC_USER_HASH_5_HASH_5                             HMAC_USER_HASH_5_HASH_5_Msk

/*******************  Bit definition for HMAC_USER_HASH_6 register  *******************/
#define HMAC_USER_HASH_6_HASH_6_POS                         (0U)
#define HMAC_USER_HASH_6_HASH_6_Len                         (32U)
#define HMAC_USER_HASH_6_HASH_6_Msk                         (0xFFFFFFFFUL << HMAC_USER_HASH_6_HASH_6_POS)
#define HMAC_USER_HASH_6_HASH_6                             HMAC_USER_HASH_6_HASH_6_Msk

/*******************  Bit definition for HMAC_USER_HASH_7 register  *******************/
#define HMAC_USER_HASH_7_HASH_7_POS                         (0U)
#define HMAC_USER_HASH_7_HASH_7_Len                         (32U)
#define HMAC_USER_HASH_7_HASH_7_Msk                         (0xFFFFFFFFUL << HMAC_USER_HASH_7_HASH_7_POS)
#define HMAC_USER_HASH_7_HASH_7                             HMAC_USER_HASH_7_HASH_7_Msk

/*******************  Bit definition for HMAC_DATA_OUT register  *******************/
#define HMAC_DATA_OUT_DATA_POS                              (0U)
#define HMAC_DATA_OUT_DATA_Len                              (32U)
#define HMAC_DATA_OUT_DATA_Msk                              (0xFFFFFFFFUL << HMAC_DATA_OUT_DATA_POS)
#define HMAC_DATA_OUT_DATA                                  HMAC_DATA_OUT_DATA_Msk

/*******************  Bit definition for HMAC_DATA_IN register  *******************/
#define HMAC_DATA_IN_DATA_POS                               (0U)
#define HMAC_DATA_IN_DATA_Len                               (32U)
#define HMAC_DATA_IN_DATA_Msk                               (0xFFFFFFFFUL << HMAC_DATA_IN_DATA_POS)
#define HMAC_DATA_IN_DATA                                   HMAC_DATA_IN_DATA_Msk

/*******************  Bit definition for HMAC_KEY0 register  *******************/
#define HMAC_KEY0_KEY0_POS                                  (0U)
#define HMAC_KEY0_KEY0_Len                                  (32U)
#define HMAC_KEY0_KEY0_Msk                                  (0xFFFFFFFFUL << HMAC_KEY0_KEY0_POS)
#define HMAC_KEY0_KEY0                                      HMAC_KEY0_KEY0_Msk

/*******************  Bit definition for HMAC_KEY1 register  *******************/
#define HMAC_KEY1_KEY1_POS                                  (0U)
#define HMAC_KEY1_KEY1_Len                                  (32U)
#define HMAC_KEY1_KEY1_Msk                                  (0xFFFFFFFFUL << HMAC_KEY1_KEY1_POS)
#define HMAC_KEY1_KEY1                                      HMAC_KEY1_KEY1_Msk

/*******************  Bit definition for HMAC_KEY2 register  *******************/
#define HMAC_KEY2_KEY2_POS                                  (0U)
#define HMAC_KEY2_KEY2_Len                                  (32U)
#define HMAC_KEY2_KEY2_Msk                                  (0xFFFFFFFFUL << HMAC_KEY2_KEY2_POS)
#define HMAC_KEY2_KEY2                                      HMAC_KEY2_KEY2_Msk

/*******************  Bit definition for HMAC_KEY3 register  *******************/
#define HMAC_KEY3_KEY3_POS                                  (0U)
#define HMAC_KEY3_KEY3_Len                                  (32U)
#define HMAC_KEY3_KEY3_Msk                                  (0xFFFFFFFFUL << HMAC_KEY3_KEY3_POS)
#define HMAC_KEY3_KEY3                                      HMAC_KEY3_KEY3_Msk

/*******************  Bit definition for HMAC_KEY4 register  *******************/
#define HMAC_KEY4_KEY4_POS                                  (0U)
#define HMAC_KEY4_KEY4_Len                                  (32U)
#define HMAC_KEY4_KEY4_Msk                                  (0xFFFFFFFFUL << HMAC_KEY4_KEY4_POS)
#define HMAC_KEY4_KEY4                                      HMAC_KEY4_KEY4_Msk

/*******************  Bit definition for HMAC_KEY5 register  *******************/
#define HMAC_KEY5_KEY5_POS                                  (0U)
#define HMAC_KEY5_KEY5_Len                                  (32U)
#define HMAC_KEY5_KEY5_Msk                                  (0xFFFFFFFFUL << HMAC_KEY5_KEY5_POS)
#define HMAC_KEY5_KEY5                                      HMAC_KEY5_KEY5_Msk

/*******************  Bit definition for HMAC_KEY6 register  *******************/
#define HMAC_KEY6_KEY6_POS                                  (0U)
#define HMAC_KEY6_KEY6_Len                                  (32U)
#define HMAC_KEY6_KEY6_Msk                                  (0xFFFFFFFFUL << HMAC_KEY6_KEY6_POS)
#define HMAC_KEY6_KEY6                                      HMAC_KEY6_KEY6_Msk

/*******************  Bit definition for HMAC_KEY7 register  *******************/
#define HMAC_KEY7_KEY7_POS                                  (0U)
#define HMAC_KEY7_KEY7_Len                                  (32U)
#define HMAC_KEY7_KEY7_Msk                                  (0xFFFFFFFFUL << HMAC_KEY7_KEY7_POS)
#define HMAC_KEY7_KEY7                                      HMAC_KEY7_KEY7_Msk

/*******************  Bit definition for HMAC_KEY_ADDR register  *******************/
#define HMAC_KEY_ADDR_KEY_ADDR_POS                          (0U)
#define HMAC_KEY_ADDR_KEY_ADDR_Len                          (32U)
#define HMAC_KEY_ADDR_KEY_ADDR_Msk                          (0xFFFFFFFFUL << HMAC_KEY_ADDR_KEY_ADDR_POS)
#define HMAC_KEY_ADDR_KEY_ADDR                              HMAC_KEY_ADDR_KEY_ADDR_Msk

/*******************  Bit definition for HMAC_KEYPORT_MASK register  *******************/
#define HMAC_KEYPORT_MASK_MASK_POS                          (0U)
#define HMAC_KEYPORT_MASK_MASK_Len                          (32U)
#define HMAC_KEYPORT_MASK_MASK_Msk                          (0xFFFFFFFFUL << HMAC_KEYPORT_MASK_MASK_POS)
#define HMAC_KEYPORT_MASK_MASK                              HMAC_KEYPORT_MASK_MASK_Msk

/* ================================================================================================================= */
/* ================                                        I2C                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for I2C_CTRL register  *******************/
#define I2C_CTRL_M_MODE_POS                                 (0U)
#define I2C_CTRL_M_MODE_Len                                 (1U)
#define I2C_CTRL_M_MODE_Msk                                 (0x1UL << I2C_CTRL_M_MODE_POS)
#define I2C_CTRL_M_MODE                                     I2C_CTRL_M_MODE_Msk

#define I2C_CTRL_SPEED_POS                                  (1U)
#define I2C_CTRL_SPEED_Len                                  (2U)
#define I2C_CTRL_SPEED_Msk                                  (0x3UL << I2C_CTRL_SPEED_POS)
#define I2C_CTRL_SPEED                                      I2C_CTRL_SPEED_Msk

#define I2C_CTRL_ADDR_BIT_S_POS                             (3U)
#define I2C_CTRL_ADDR_BIT_S_Len                             (1U)
#define I2C_CTRL_ADDR_BIT_S_Msk                             (0x1UL << I2C_CTRL_ADDR_BIT_S_POS)
#define I2C_CTRL_ADDR_BIT_S                                 I2C_CTRL_ADDR_BIT_S_Msk

#define I2C_CTRL_ADDR_BIT_M_POS                             (4U)
#define I2C_CTRL_ADDR_BIT_M_Len                             (1U)
#define I2C_CTRL_ADDR_BIT_M_Msk                             (0x1UL << I2C_CTRL_ADDR_BIT_M_POS)
#define I2C_CTRL_ADDR_BIT_M                                 I2C_CTRL_ADDR_BIT_M_Msk

#define I2C_CTRL_RESTART_EN_POS                             (5U)
#define I2C_CTRL_RESTART_EN_Len                             (1U)
#define I2C_CTRL_RESTART_EN_Msk                             (0x1UL << I2C_CTRL_RESTART_EN_POS)
#define I2C_CTRL_RESTART_EN                                 I2C_CTRL_RESTART_EN_Msk

#define I2C_CTRL_S_DIS_POS                                  (6U)
#define I2C_CTRL_S_DIS_Len                                  (1U)
#define I2C_CTRL_S_DIS_Msk                                  (0x1UL << I2C_CTRL_S_DIS_POS)
#define I2C_CTRL_S_DIS                                      I2C_CTRL_S_DIS_Msk

#define I2C_CTRL_STOP_DET_INT_POS                           (7U)
#define I2C_CTRL_STOP_DET_INT_Len                           (1U)
#define I2C_CTRL_STOP_DET_INT_Msk                           (0x1UL << I2C_CTRL_STOP_DET_INT_POS)
#define I2C_CTRL_STOP_DET_INT                               I2C_CTRL_STOP_DET_INT_Msk

#define I2C_CTRL_TX_EMPTY_CTRL_POS                          (8U)
#define I2C_CTRL_TX_EMPTY_CTRL_Len                          (1U)
#define I2C_CTRL_TX_EMPTY_CTRL_Msk                          (0x1UL << I2C_CTRL_TX_EMPTY_CTRL_POS)
#define I2C_CTRL_TX_EMPTY_CTRL                              I2C_CTRL_TX_EMPTY_CTRL_Msk

#define I2C_CTRL_RXFIFO_FULL_HLD_POS                        (9U)
#define I2C_CTRL_RXFIFO_FULL_HLD_Len                        (1U)
#define I2C_CTRL_RXFIFO_FULL_HLD_Msk                        (0x1UL << I2C_CTRL_RXFIFO_FULL_HLD_POS)
#define I2C_CTRL_RXFIFO_FULL_HLD                            I2C_CTRL_RXFIFO_FULL_HLD_Msk

#define I2C_CTRL_STOP_DET_M_ACTIVE_POS                      (10U)
#define I2C_CTRL_STOP_DET_M_ACTIVE_Len                      (1U)
#define I2C_CTRL_STOP_DET_M_ACTIVE_Msk                      (0x1UL << I2C_CTRL_STOP_DET_M_ACTIVE_POS)
#define I2C_CTRL_STOP_DET_M_ACTIVE                          I2C_CTRL_STOP_DET_M_ACTIVE_Msk

#define I2C_CTRL_BUS_CLR_FEATURE_POS                        (11U)
#define I2C_CTRL_BUS_CLR_FEATURE_Len                        (1U)
#define I2C_CTRL_BUS_CLR_FEATURE_Msk                        (0x1UL << I2C_CTRL_BUS_CLR_FEATURE_POS)
#define I2C_CTRL_BUS_CLR_FEATURE                            I2C_CTRL_BUS_CLR_FEATURE_Msk

/*******************  Bit definition for I2C_TARGET_ADDR register  *******************/
#define I2C_TARGET_ADDR_TARGET_POS                          (0U)
#define I2C_TARGET_ADDR_TARGET_Len                          (10U)
#define I2C_TARGET_ADDR_TARGET_Msk                          (0x3FFUL << I2C_TARGET_ADDR_TARGET_POS)
#define I2C_TARGET_ADDR_TARGET                              I2C_TARGET_ADDR_TARGET_Msk

#define I2C_TARGET_ADDR_TX_CTRL_POS                         (10U)
#define I2C_TARGET_ADDR_TX_CTRL_Len                         (1U)
#define I2C_TARGET_ADDR_TX_CTRL_Msk                         (0x1UL << I2C_TARGET_ADDR_TX_CTRL_POS)
#define I2C_TARGET_ADDR_TX_CTRL                             I2C_TARGET_ADDR_TX_CTRL_Msk

#define I2C_TARGET_ADDR_SPECIAL_POS                         (11U)
#define I2C_TARGET_ADDR_SPECIAL_Len                         (1U)
#define I2C_TARGET_ADDR_SPECIAL_Msk                         (0x1UL << I2C_TARGET_ADDR_SPECIAL_POS)
#define I2C_TARGET_ADDR_SPECIAL                             I2C_TARGET_ADDR_SPECIAL_Msk

/*******************  Bit definition for I2C_S_ADDR register  *******************/
#define I2C_S_ADDR_S_ADDR_POS                               (0U)
#define I2C_S_ADDR_S_ADDR_Len                               (10U)
#define I2C_S_ADDR_S_ADDR_Msk                               (0x3FFUL << I2C_S_ADDR_S_ADDR_POS)
#define I2C_S_ADDR_S_ADDR                                   I2C_S_ADDR_S_ADDR_Msk

/*******************  Bit definition for I2C_M_HS_ADDR register  *******************/
#define I2C_M_HS_ADDR_HS_ADDR_POS                           (0U)
#define I2C_M_HS_ADDR_HS_ADDR_Len                           (3U)
#define I2C_M_HS_ADDR_HS_ADDR_Msk                           (0x7UL << I2C_M_HS_ADDR_HS_ADDR_POS)
#define I2C_M_HS_ADDR_HS_ADDR                               I2C_M_HS_ADDR_HS_ADDR_Msk

/*******************  Bit definition for I2C_DATA_CMD register  *******************/
#define I2C_DATA_CMD_DATA_POS                               (0U)
#define I2C_DATA_CMD_DATA_Len                               (8U)
#define I2C_DATA_CMD_DATA_Msk                               (0xFFUL << I2C_DATA_CMD_DATA_POS)
#define I2C_DATA_CMD_DATA                                   I2C_DATA_CMD_DATA_Msk

#define I2C_DATA_CMD_CMD_POS                                (8U)
#define I2C_DATA_CMD_CMD_Len                                (1U)
#define I2C_DATA_CMD_CMD_Msk                                (0x1UL << I2C_DATA_CMD_CMD_POS)
#define I2C_DATA_CMD_CMD                                    I2C_DATA_CMD_CMD_Msk

#define I2C_DATA_CMD_STOP_POS                               (9U)
#define I2C_DATA_CMD_STOP_Len                               (1U)
#define I2C_DATA_CMD_STOP_Msk                               (0x1UL << I2C_DATA_CMD_STOP_POS)
#define I2C_DATA_CMD_STOP                                   I2C_DATA_CMD_STOP_Msk

#define I2C_DATA_CMD_RESTART_POS                            (10U)
#define I2C_DATA_CMD_RESTART_Len                            (1U)
#define I2C_DATA_CMD_RESTART_Msk                            (0x1UL << I2C_DATA_CMD_RESTART_POS)
#define I2C_DATA_CMD_RESTART                                I2C_DATA_CMD_RESTART_Msk

/*******************  Bit definition for I2C_SS_CLK_HCOUNT register  *******************/
#define I2C_SS_CLK_HCOUNT_COUNT_POS                         (0U)
#define I2C_SS_CLK_HCOUNT_COUNT_Len                         (16U)
#define I2C_SS_CLK_HCOUNT_COUNT_Msk                         (0xFFFFUL << I2C_SS_CLK_HCOUNT_COUNT_POS)
#define I2C_SS_CLK_HCOUNT_COUNT                             I2C_SS_CLK_HCOUNT_COUNT_Msk

/*******************  Bit definition for I2C_SS_CLK_LCOUNT register  *******************/
#define I2C_SS_CLK_LCOUNT_COUNT_POS                         (0U)
#define I2C_SS_CLK_LCOUNT_COUNT_Len                         (16U)
#define I2C_SS_CLK_LCOUNT_COUNT_Msk                         (0xFFFFUL << I2C_SS_CLK_LCOUNT_COUNT_POS)
#define I2C_SS_CLK_LCOUNT_COUNT                             I2C_SS_CLK_LCOUNT_COUNT_Msk

/*******************  Bit definition for I2C_FS_CLK_HCOUNT register  *******************/
#define I2C_FS_CLK_HCOUNT_COUNT_POS                         (0U)
#define I2C_FS_CLK_HCOUNT_COUNT_Len                         (16U)
#define I2C_FS_CLK_HCOUNT_COUNT_Msk                         (0xFFFFUL << I2C_FS_CLK_HCOUNT_COUNT_POS)
#define I2C_FS_CLK_HCOUNT_COUNT                             I2C_FS_CLK_HCOUNT_COUNT_Msk

/*******************  Bit definition for I2C_FS_CLK_LCOUNT register  *******************/
#define I2C_FS_CLK_LCOUNT_COUNT_POS                         (0U)
#define I2C_FS_CLK_LCOUNT_COUNT_Len                         (16U)
#define I2C_FS_CLK_LCOUNT_COUNT_Msk                         (0xFFFFUL << I2C_FS_CLK_LCOUNT_COUNT_POS)
#define I2C_FS_CLK_LCOUNT_COUNT                             I2C_FS_CLK_LCOUNT_COUNT_Msk

/*******************  Bit definition for I2C_HS_CLK_HCOUNT register  *******************/
#define I2C_HS_CLK_HCOUNT_COUNT_POS                         (0U)
#define I2C_HS_CLK_HCOUNT_COUNT_Len                         (16U)
#define I2C_HS_CLK_HCOUNT_COUNT_Msk                         (0xFFFFUL << I2C_HS_CLK_HCOUNT_COUNT_POS)
#define I2C_HS_CLK_HCOUNT_COUNT                             I2C_HS_CLK_HCOUNT_COUNT_Msk

/*******************  Bit definition for I2C_HS_CLK_LCOUNT register  *******************/
#define I2C_HS_CLK_LCOUNT_COUNT_POS                         (0U)
#define I2C_HS_CLK_LCOUNT_COUNT_Len                         (16U)
#define I2C_HS_CLK_LCOUNT_COUNT_Msk                         (0xFFFFUL << I2C_HS_CLK_LCOUNT_COUNT_POS)
#define I2C_HS_CLK_LCOUNT_COUNT                             I2C_HS_CLK_LCOUNT_COUNT_Msk

/*******************  Bit definition for I2C_INT_STAT register  *******************/
#define I2C_INT_STAT_RAW_RX_UNDER_POS                       (0U)
#define I2C_INT_STAT_RAW_RX_UNDER_Len                       (1U)
#define I2C_INT_STAT_RAW_RX_UNDER_Msk                       (0x1UL << I2C_INT_STAT_RAW_RX_UNDER_POS)
#define I2C_INT_STAT_RAW_RX_UNDER                           I2C_INT_STAT_RAW_RX_UNDER_Msk

#define I2C_INT_STAT_RAW_RX_OVER_POS                        (1U)
#define I2C_INT_STAT_RAW_RX_OVER_Len                        (1U)
#define I2C_INT_STAT_RAW_RX_OVER_Msk                        (0x1UL << I2C_INT_STAT_RAW_RX_OVER_POS)
#define I2C_INT_STAT_RAW_RX_OVER                            I2C_INT_STAT_RAW_RX_OVER_Msk

#define I2C_INT_STAT_RAW_RX_FULL_POS                        (2U)
#define I2C_INT_STAT_RAW_RX_FULL_Len                        (1U)
#define I2C_INT_STAT_RAW_RX_FULL_Msk                        (0x1UL << I2C_INT_STAT_RAW_RX_FULL_POS)
#define I2C_INT_STAT_RAW_RX_FULL                            I2C_INT_STAT_RAW_RX_FULL_Msk

#define I2C_INT_STAT_RAW_TX_OVER_POS                        (3U)
#define I2C_INT_STAT_RAW_TX_OVER_Len                        (1U)
#define I2C_INT_STAT_RAW_TX_OVER_Msk                        (0x1UL << I2C_INT_STAT_RAW_TX_OVER_POS)
#define I2C_INT_STAT_RAW_TX_OVER                            I2C_INT_STAT_RAW_TX_OVER_Msk

#define I2C_INT_STAT_RAW_TX_EMPTY_POS                       (4U)
#define I2C_INT_STAT_RAW_TX_EMPTY_Len                       (1U)
#define I2C_INT_STAT_RAW_TX_EMPTY_Msk                       (0x1UL << I2C_INT_STAT_RAW_TX_EMPTY_POS)
#define I2C_INT_STAT_RAW_TX_EMPTY                           I2C_INT_STAT_RAW_TX_EMPTY_Msk

#define I2C_INT_STAT_RAW_RD_REQ_POS                         (5U)
#define I2C_INT_STAT_RAW_RD_REQ_Len                         (1U)
#define I2C_INT_STAT_RAW_RD_REQ_Msk                         (0x1UL << I2C_INT_STAT_RAW_RD_REQ_POS)
#define I2C_INT_STAT_RAW_RD_REQ                             I2C_INT_STAT_RAW_RD_REQ_Msk

#define I2C_INT_STAT_RAW_TX_ABORT_POS                       (6U)
#define I2C_INT_STAT_RAW_TX_ABORT_Len                       (1U)
#define I2C_INT_STAT_RAW_TX_ABORT_Msk                       (0x1UL << I2C_INT_STAT_RAW_TX_ABORT_POS)
#define I2C_INT_STAT_RAW_TX_ABORT                           I2C_INT_STAT_RAW_TX_ABORT_Msk

#define I2C_INT_STAT_RAW_RX_DONE_POS                        (7U)
#define I2C_INT_STAT_RAW_RX_DONE_Len                        (1U)
#define I2C_INT_STAT_RAW_RX_DONE_Msk                        (0x1UL << I2C_INT_STAT_RAW_RX_DONE_POS)
#define I2C_INT_STAT_RAW_RX_DONE                            I2C_INT_STAT_RAW_RX_DONE_Msk

#define I2C_INT_STAT_RAW_ACTIVITY_POS                       (8U)
#define I2C_INT_STAT_RAW_ACTIVITY_Len                       (1U)
#define I2C_INT_STAT_RAW_ACTIVITY_Msk                       (0x1UL << I2C_INT_STAT_RAW_ACTIVITY_POS)
#define I2C_INT_STAT_RAW_ACTIVITY                           I2C_INT_STAT_RAW_ACTIVITY_Msk

#define I2C_INT_STAT_RAW_STOP_DET_POS                       (9U)
#define I2C_INT_STAT_RAW_STOP_DET_Len                       (1U)
#define I2C_INT_STAT_RAW_STOP_DET_Msk                       (0x1UL << I2C_INT_STAT_RAW_STOP_DET_POS)
#define I2C_INT_STAT_RAW_STOP_DET                           I2C_INT_STAT_RAW_STOP_DET_Msk

#define I2C_INT_STAT_RAW_START_DET_POS                      (10U)
#define I2C_INT_STAT_RAW_START_DET_Len                      (1U)
#define I2C_INT_STAT_RAW_START_DET_Msk                      (0x1UL << I2C_INT_STAT_RAW_START_DET_POS)
#define I2C_INT_STAT_RAW_START_DET                          I2C_INT_STAT_RAW_START_DET_Msk

#define I2C_INT_STAT_RAW_GEN_CALL_POS                       (11U)
#define I2C_INT_STAT_RAW_GEN_CALL_Len                       (1U)
#define I2C_INT_STAT_RAW_GEN_CALL_Msk                       (0x1UL << I2C_INT_STAT_RAW_GEN_CALL_POS)
#define I2C_INT_STAT_RAW_GEN_CALL                           I2C_INT_STAT_RAW_GEN_CALL_Msk

#define I2C_INT_STAT_RAW_RESTART_DET_POS                    (12U)
#define I2C_INT_STAT_RAW_RESTART_DET_Len                    (1U)
#define I2C_INT_STAT_RAW_RESTART_DET_Msk                    (0x1UL << I2C_INT_STAT_RAW_RESTART_DET_POS)
#define I2C_INT_STAT_RAW_RESTART_DET                        I2C_INT_STAT_RAW_RESTART_DET_Msk

#define I2C_INT_STAT_RAW_M_HOLD_POS                         (13U)
#define I2C_INT_STAT_RAW_M_HOLD_Len                         (1U)
#define I2C_INT_STAT_RAW_M_HOLD_Msk                         (0x1UL << I2C_INT_STAT_RAW_M_HOLD_POS)
#define I2C_INT_STAT_RAW_M_HOLD                             I2C_INT_STAT_RAW_M_HOLD_Msk

#define I2C_INT_STAT_RAW_SCL_STUCKLOW_POS                   (14U)
#define I2C_INT_STAT_RAW_SCL_STUCKLOW_Len                   (1U)
#define I2C_INT_STAT_RAW_SCL_STUCKLOW_Msk                   (0x1UL << I2C_INT_STAT_RAW_SCL_STUCKLOW_POS)
#define I2C_INT_STAT_RAW_SCL_STUCKLOW                       I2C_INT_STAT_RAW_SCL_STUCKLOW_Msk

/*******************  Bit definition for I2C_INT_MASK register  *******************/
#define I2C_INT_MASK_MASK_RX_UNDER_POS                      (0U)
#define I2C_INT_MASK_MASK_RX_UNDER_Len                      (1U)
#define I2C_INT_MASK_MASK_RX_UNDER_Msk                      (0x1UL << I2C_INT_MASK_MASK_RX_UNDER_POS)
#define I2C_INT_MASK_MASK_RX_UNDER                          I2C_INT_MASK_MASK_RX_UNDER_Msk

#define I2C_INT_MASK_MASK_RX_OVER_POS                       (1U)
#define I2C_INT_MASK_MASK_RX_OVER_Len                       (1U)
#define I2C_INT_MASK_MASK_RX_OVER_Msk                       (0x1UL << I2C_INT_MASK_MASK_RX_OVER_POS)
#define I2C_INT_MASK_MASK_RX_OVER                           I2C_INT_MASK_MASK_RX_OVER_Msk

#define I2C_INT_MASK_MASK_RX_FULL_POS                       (2U)
#define I2C_INT_MASK_MASK_RX_FULL_Len                       (1U)
#define I2C_INT_MASK_MASK_RX_FULL_Msk                       (0x1UL << I2C_INT_MASK_MASK_RX_FULL_POS)
#define I2C_INT_MASK_MASK_RX_FULL                           I2C_INT_MASK_MASK_RX_FULL_Msk

#define I2C_INT_MASK_MASK_TX_OVER_POS                       (3U)
#define I2C_INT_MASK_MASK_TX_OVER_Len                       (1U)
#define I2C_INT_MASK_MASK_TX_OVER_Msk                       (0x1UL << I2C_INT_MASK_MASK_TX_OVER_POS)
#define I2C_INT_MASK_MASK_TX_OVER                           I2C_INT_MASK_MASK_TX_OVER_Msk

#define I2C_INT_MASK_MASK_TX_EMPTY_POS                      (4U)
#define I2C_INT_MASK_MASK_TX_EMPTY_Len                      (1U)
#define I2C_INT_MASK_MASK_TX_EMPTY_Msk                      (0x1UL << I2C_INT_MASK_MASK_TX_EMPTY_POS)
#define I2C_INT_MASK_MASK_TX_EMPTY                          I2C_INT_MASK_MASK_TX_EMPTY_Msk

#define I2C_INT_MASK_MASK_RD_REQ_POS                        (5U)
#define I2C_INT_MASK_MASK_RD_REQ_Len                        (1U)
#define I2C_INT_MASK_MASK_RD_REQ_Msk                        (0x1UL << I2C_INT_MASK_MASK_RD_REQ_POS)
#define I2C_INT_MASK_MASK_RD_REQ                            I2C_INT_MASK_MASK_RD_REQ_Msk

#define I2C_INT_MASK_MASK_TX_ABORT_POS                      (6U)
#define I2C_INT_MASK_MASK_TX_ABORT_Len                      (1U)
#define I2C_INT_MASK_MASK_TX_ABORT_Msk                      (0x1UL << I2C_INT_MASK_MASK_TX_ABORT_POS)
#define I2C_INT_MASK_MASK_TX_ABORT                          I2C_INT_MASK_MASK_TX_ABORT_Msk

#define I2C_INT_MASK_MASK_RX_DONE_POS                       (7U)
#define I2C_INT_MASK_MASK_RX_DONE_Len                       (1U)
#define I2C_INT_MASK_MASK_RX_DONE_Msk                       (0x1UL << I2C_INT_MASK_MASK_RX_DONE_POS)
#define I2C_INT_MASK_MASK_RX_DONE                           I2C_INT_MASK_MASK_RX_DONE_Msk

#define I2C_INT_MASK_MASK_ACTIVITY_POS                      (8U)
#define I2C_INT_MASK_MASK_ACTIVITY_Len                      (1U)
#define I2C_INT_MASK_MASK_ACTIVITY_Msk                      (0x1UL << I2C_INT_MASK_MASK_ACTIVITY_POS)
#define I2C_INT_MASK_MASK_ACTIVITY                          I2C_INT_MASK_MASK_ACTIVITY_Msk

#define I2C_INT_MASK_MASK_STOP_DET_POS                      (9U)
#define I2C_INT_MASK_MASK_STOP_DET_Len                      (1U)
#define I2C_INT_MASK_MASK_STOP_DET_Msk                      (0x1UL << I2C_INT_MASK_MASK_STOP_DET_POS)
#define I2C_INT_MASK_MASK_STOP_DET                          I2C_INT_MASK_MASK_STOP_DET_Msk

#define I2C_INT_MASK_MASK_START_DET_POS                     (10U)
#define I2C_INT_MASK_MASK_START_DET_Len                     (1U)
#define I2C_INT_MASK_MASK_START_DET_Msk                     (0x1UL << I2C_INT_MASK_MASK_START_DET_POS)
#define I2C_INT_MASK_MASK_START_DET                         I2C_INT_MASK_MASK_START_DET_Msk

#define I2C_INT_MASK_MASK_GEN_CALL_POS                      (11U)
#define I2C_INT_MASK_MASK_GEN_CALL_Len                      (1U)
#define I2C_INT_MASK_MASK_GEN_CALL_Msk                      (0x1UL << I2C_INT_MASK_MASK_GEN_CALL_POS)
#define I2C_INT_MASK_MASK_GEN_CALL                          I2C_INT_MASK_MASK_GEN_CALL_Msk

#define I2C_INT_MASK_MASK_RESTART_DET_POS                   (12U)
#define I2C_INT_MASK_MASK_RESTART_DET_Len                   (1U)
#define I2C_INT_MASK_MASK_RESTART_DET_Msk                   (0x1UL << I2C_INT_MASK_MASK_RESTART_DET_POS)
#define I2C_INT_MASK_MASK_RESTART_DET                       I2C_INT_MASK_MASK_RESTART_DET_Msk

#define I2C_INT_MASK_MASK_M_HOLD_POS                        (13U)
#define I2C_INT_MASK_MASK_M_HOLD_Len                        (1U)
#define I2C_INT_MASK_MASK_M_HOLD_Msk                        (0x1UL << I2C_INT_MASK_MASK_M_HOLD_POS)
#define I2C_INT_MASK_MASK_M_HOLD                            I2C_INT_MASK_MASK_M_HOLD_Msk

#define I2C_INT_MASK_MASK_SCL_STUCKLOW_POS                  (14U)
#define I2C_INT_MASK_MASK_SCL_STUCKLOW_Len                  (1U)
#define I2C_INT_MASK_MASK_SCL_STUCKLOW_Msk                  (0x1UL << I2C_INT_MASK_MASK_SCL_STUCKLOW_POS)
#define I2C_INT_MASK_MASK_SCL_STUCKLOW                      I2C_INT_MASK_MASK_SCL_STUCKLOW_Msk

/*******************  Bit definition for I2C_RAW_INT_STAT register  *******************/
#define I2C_RAW_INT_STAT_RX_UNDER_POS                       (0U)
#define I2C_RAW_INT_STAT_RX_UNDER_Len                       (1U)
#define I2C_RAW_INT_STAT_RX_UNDER_Msk                       (0x1UL << I2C_RAW_INT_STAT_RX_UNDER_POS)
#define I2C_RAW_INT_STAT_RX_UNDER                           I2C_RAW_INT_STAT_RX_UNDER_Msk

#define I2C_RAW_INT_STAT_RX_OVER_POS                        (1U)
#define I2C_RAW_INT_STAT_RX_OVER_Len                        (1U)
#define I2C_RAW_INT_STAT_RX_OVER_Msk                        (0x1UL << I2C_RAW_INT_STAT_RX_OVER_POS)
#define I2C_RAW_INT_STAT_RX_OVER                            I2C_RAW_INT_STAT_RX_OVER_Msk

#define I2C_RAW_INT_STAT_RX_FULL_POS                        (2U)
#define I2C_RAW_INT_STAT_RX_FULL_Len                        (1U)
#define I2C_RAW_INT_STAT_RX_FULL_Msk                        (0x1UL << I2C_RAW_INT_STAT_RX_FULL_POS)
#define I2C_RAW_INT_STAT_RX_FULL                            I2C_RAW_INT_STAT_RX_FULL_Msk

#define I2C_RAW_INT_STAT_TX_OVER_POS                        (3U)
#define I2C_RAW_INT_STAT_TX_OVER_Len                        (1U)
#define I2C_RAW_INT_STAT_TX_OVER_Msk                        (0x1UL << I2C_RAW_INT_STAT_TX_OVER_POS)
#define I2C_RAW_INT_STAT_TX_OVER                            I2C_RAW_INT_STAT_TX_OVER_Msk

#define I2C_RAW_INT_STAT_TX_EMPTY_POS                       (4U)
#define I2C_RAW_INT_STAT_TX_EMPTY_Len                       (1U)
#define I2C_RAW_INT_STAT_TX_EMPTY_Msk                       (0x1UL << I2C_RAW_INT_STAT_TX_EMPTY_POS)
#define I2C_RAW_INT_STAT_TX_EMPTY                           I2C_RAW_INT_STAT_TX_EMPTY_Msk

#define I2C_RAW_INT_STAT_RD_REQ_POS                         (5U)
#define I2C_RAW_INT_STAT_RD_REQ_Len                         (1U)
#define I2C_RAW_INT_STAT_RD_REQ_Msk                         (0x1UL << I2C_RAW_INT_STAT_RD_REQ_POS)
#define I2C_RAW_INT_STAT_RD_REQ                             I2C_RAW_INT_STAT_RD_REQ_Msk

#define I2C_RAW_INT_STAT_TX_ABORT_POS                       (6U)
#define I2C_RAW_INT_STAT_TX_ABORT_Len                       (1U)
#define I2C_RAW_INT_STAT_TX_ABORT_Msk                       (0x1UL << I2C_RAW_INT_STAT_TX_ABORT_POS)
#define I2C_RAW_INT_STAT_TX_ABORT                           I2C_RAW_INT_STAT_TX_ABORT_Msk

#define I2C_RAW_INT_STAT_RX_DONE_POS                        (7U)
#define I2C_RAW_INT_STAT_RX_DONE_Len                        (1U)
#define I2C_RAW_INT_STAT_RX_DONE_Msk                        (0x1UL << I2C_RAW_INT_STAT_RX_DONE_POS)
#define I2C_RAW_INT_STAT_RX_DONE                            I2C_RAW_INT_STAT_RX_DONE_Msk

#define I2C_RAW_INT_STAT_ACTIVITY_POS                       (8U)
#define I2C_RAW_INT_STAT_ACTIVITY_Len                       (1U)
#define I2C_RAW_INT_STAT_ACTIVITY_Msk                       (0x1UL << I2C_RAW_INT_STAT_ACTIVITY_POS)
#define I2C_RAW_INT_STAT_ACTIVITY                           I2C_RAW_INT_STAT_ACTIVITY_Msk

#define I2C_RAW_INT_STAT_STOP_DET_POS                       (9U)
#define I2C_RAW_INT_STAT_STOP_DET_Len                       (1U)
#define I2C_RAW_INT_STAT_STOP_DET_Msk                       (0x1UL << I2C_RAW_INT_STAT_STOP_DET_POS)
#define I2C_RAW_INT_STAT_STOP_DET                           I2C_RAW_INT_STAT_STOP_DET_Msk

#define I2C_RAW_INT_STAT_START_DET_POS                      (10U)
#define I2C_RAW_INT_STAT_START_DET_Len                      (1U)
#define I2C_RAW_INT_STAT_START_DET_Msk                      (0x1UL << I2C_RAW_INT_STAT_START_DET_POS)
#define I2C_RAW_INT_STAT_START_DET                          I2C_RAW_INT_STAT_START_DET_Msk

#define I2C_RAW_INT_STAT_GEN_CALL_POS                       (11U)
#define I2C_RAW_INT_STAT_GEN_CALL_Len                       (1U)
#define I2C_RAW_INT_STAT_GEN_CALL_Msk                       (0x1UL << I2C_RAW_INT_STAT_GEN_CALL_POS)
#define I2C_RAW_INT_STAT_GEN_CALL                           I2C_RAW_INT_STAT_GEN_CALL_Msk

#define I2C_RAW_INT_STAT_RESTART_DET_POS                    (12U)
#define I2C_RAW_INT_STAT_RESTART_DET_Len                    (1U)
#define I2C_RAW_INT_STAT_RESTART_DET_Msk                    (0x1UL << I2C_RAW_INT_STAT_RESTART_DET_POS)
#define I2C_RAW_INT_STAT_RESTART_DET                        I2C_RAW_INT_STAT_RESTART_DET_Msk

#define I2C_RAW_INT_STAT_M_HOLD_POS                         (13U)
#define I2C_RAW_INT_STAT_M_HOLD_Len                         (1U)
#define I2C_RAW_INT_STAT_M_HOLD_Msk                         (0x1UL << I2C_RAW_INT_STAT_M_HOLD_POS)
#define I2C_RAW_INT_STAT_M_HOLD                             I2C_RAW_INT_STAT_M_HOLD_Msk

#define I2C_RAW_INT_STAT_SCL_STUCKLOW_POS                   (14U)
#define I2C_RAW_INT_STAT_SCL_STUCKLOW_Len                   (1U)
#define I2C_RAW_INT_STAT_SCL_STUCKLOW_Msk                   (0x1UL << I2C_RAW_INT_STAT_SCL_STUCKLOW_POS)
#define I2C_RAW_INT_STAT_SCL_STUCKLOW                       I2C_RAW_INT_STAT_SCL_STUCKLOW_Msk

/*******************  Bit definition for I2C_RX_FIFO_THD register  *******************/
#define I2C_RX_FIFO_THD_THD_POS                             (0U)
#define I2C_RX_FIFO_THD_THD_Len                             (8U)
#define I2C_RX_FIFO_THD_THD_Msk                             (0xFFUL << I2C_RX_FIFO_THD_THD_POS)
#define I2C_RX_FIFO_THD_THD                                 I2C_RX_FIFO_THD_THD_Msk

/*******************  Bit definition for I2C_TX_FIFO_THD register  *******************/
#define I2C_TX_FIFO_THD_THD_POS                             (0U)
#define I2C_TX_FIFO_THD_THD_Len                             (8U)
#define I2C_TX_FIFO_THD_THD_Msk                             (0xFFUL << I2C_TX_FIFO_THD_THD_POS)
#define I2C_TX_FIFO_THD_THD                                 I2C_TX_FIFO_THD_THD_Msk

/*******************  Bit definition for I2C_CLR_INT register  *******************/
#define I2C_CLR_INT_CLR_INT_POS                             (0U)
#define I2C_CLR_INT_CLR_INT_Len                             (1U)
#define I2C_CLR_INT_CLR_INT_Msk                             (0x1UL << I2C_CLR_INT_CLR_INT_POS)
#define I2C_CLR_INT_CLR_INT                                 I2C_CLR_INT_CLR_INT_Msk

/*******************  Bit definition for I2C_CLR_RX_UNDER register  *******************/
#define I2C_CLR_RX_UNDER_CLR_RX_UNDER_POS                   (0U)
#define I2C_CLR_RX_UNDER_CLR_RX_UNDER_Len                   (1U)
#define I2C_CLR_RX_UNDER_CLR_RX_UNDER_Msk                   (0x1UL << I2C_CLR_RX_UNDER_CLR_RX_UNDER_POS)
#define I2C_CLR_RX_UNDER_CLR_RX_UNDER                       I2C_CLR_RX_UNDER_CLR_RX_UNDER_Msk

/*******************  Bit definition for I2C_CLR_RX_OVER register  *******************/
#define I2C_CLR_RX_OVER_CLR_RX_OVER_POS                     (0U)
#define I2C_CLR_RX_OVER_CLR_RX_OVER_Len                     (1U)
#define I2C_CLR_RX_OVER_CLR_RX_OVER_Msk                     (0x1UL << I2C_CLR_RX_OVER_CLR_RX_OVER_POS)
#define I2C_CLR_RX_OVER_CLR_RX_OVER                         I2C_CLR_RX_OVER_CLR_RX_OVER_Msk

/*******************  Bit definition for I2C_CLR_TX_OVER register  *******************/
#define I2C_CLR_TX_OVER_CLR_TX_OVER_POS                     (0U)
#define I2C_CLR_TX_OVER_CLR_TX_OVER_Len                     (1U)
#define I2C_CLR_TX_OVER_CLR_TX_OVER_Msk                     (0x1UL << I2C_CLR_TX_OVER_CLR_TX_OVER_POS)
#define I2C_CLR_TX_OVER_CLR_TX_OVER                         I2C_CLR_TX_OVER_CLR_TX_OVER_Msk

/*******************  Bit definition for I2C_CLR_RD_REQ register  *******************/
#define I2C_CLR_RD_REQ_CLR_RD_REQ_POS                       (0U)
#define I2C_CLR_RD_REQ_CLR_RD_REQ_Len                       (1U)
#define I2C_CLR_RD_REQ_CLR_RD_REQ_Msk                       (0x1UL << I2C_CLR_RD_REQ_CLR_RD_REQ_POS)
#define I2C_CLR_RD_REQ_CLR_RD_REQ                           I2C_CLR_RD_REQ_CLR_RD_REQ_Msk

/*******************  Bit definition for I2C_CLR_TX_ABORT register  *******************/
#define I2C_CLR_TX_ABORT_CLR_TX_ABORT_POS                   (0U)
#define I2C_CLR_TX_ABORT_CLR_TX_ABORT_Len                   (1U)
#define I2C_CLR_TX_ABORT_CLR_TX_ABORT_Msk                   (0x1UL << I2C_CLR_TX_ABORT_CLR_TX_ABORT_POS)
#define I2C_CLR_TX_ABORT_CLR_TX_ABORT                       I2C_CLR_TX_ABORT_CLR_TX_ABORT_Msk

/*******************  Bit definition for I2C_CLR_RX_DONE register  *******************/
#define I2C_CLR_RX_DONE_CLR_RX_DONE_POS                     (0U)
#define I2C_CLR_RX_DONE_CLR_RX_DONE_Len                     (1U)
#define I2C_CLR_RX_DONE_CLR_RX_DONE_Msk                     (0x1UL << I2C_CLR_RX_DONE_CLR_RX_DONE_POS)
#define I2C_CLR_RX_DONE_CLR_RX_DONE                         I2C_CLR_RX_DONE_CLR_RX_DONE_Msk

/*******************  Bit definition for I2C_CLR_ACTIVITY register  *******************/
#define I2C_CLR_ACTIVITY_CLR_ACTIVITY_POS                   (0U)
#define I2C_CLR_ACTIVITY_CLR_ACTIVITY_Len                   (1U)
#define I2C_CLR_ACTIVITY_CLR_ACTIVITY_Msk                   (0x1UL << I2C_CLR_ACTIVITY_CLR_ACTIVITY_POS)
#define I2C_CLR_ACTIVITY_CLR_ACTIVITY                       I2C_CLR_ACTIVITY_CLR_ACTIVITY_Msk

/*******************  Bit definition for I2C_CLR_STOP_DET register  *******************/
#define I2C_CLR_STOP_DET_CLR_STOP_DET_POS                   (0U)
#define I2C_CLR_STOP_DET_CLR_STOP_DET_Len                   (1U)
#define I2C_CLR_STOP_DET_CLR_STOP_DET_Msk                   (0x1UL << I2C_CLR_STOP_DET_CLR_STOP_DET_POS)
#define I2C_CLR_STOP_DET_CLR_STOP_DET                       I2C_CLR_STOP_DET_CLR_STOP_DET_Msk

/*******************  Bit definition for I2C_CLR_START_DET register  *******************/
#define I2C_CLR_START_DET_CLR_START_DET_POS                 (0U)
#define I2C_CLR_START_DET_CLR_START_DET_Len                 (1U)
#define I2C_CLR_START_DET_CLR_START_DET_Msk                 (0x1UL << I2C_CLR_START_DET_CLR_START_DET_POS)
#define I2C_CLR_START_DET_CLR_START_DET                     I2C_CLR_START_DET_CLR_START_DET_Msk

/*******************  Bit definition for I2C_CLR_GEN_CALL register  *******************/
#define I2C_CLR_GEN_CALL_CLR_GEN_CALL_POS                   (0U)
#define I2C_CLR_GEN_CALL_CLR_GEN_CALL_Len                   (1U)
#define I2C_CLR_GEN_CALL_CLR_GEN_CALL_Msk                   (0x1UL << I2C_CLR_GEN_CALL_CLR_GEN_CALL_POS)
#define I2C_CLR_GEN_CALL_CLR_GEN_CALL                       I2C_CLR_GEN_CALL_CLR_GEN_CALL_Msk

/*******************  Bit definition for I2C_EN register  *******************/
#define I2C_EN_ACTIVITY_POS                                 (0U)
#define I2C_EN_ACTIVITY_Len                                 (1U)
#define I2C_EN_ACTIVITY_Msk                                 (0x1UL << I2C_EN_ACTIVITY_POS)
#define I2C_EN_ACTIVITY                                     I2C_EN_ACTIVITY_Msk

#define I2C_EN_ABORT_POS                                    (1U)
#define I2C_EN_ABORT_Len                                    (1U)
#define I2C_EN_ABORT_Msk                                    (0x1UL << I2C_EN_ABORT_POS)
#define I2C_EN_ABORT                                        I2C_EN_ABORT_Msk

#define I2C_EN_TX_CMD_BLOCK_POS                             (2U)
#define I2C_EN_TX_CMD_BLOCK_Len                             (1U)
#define I2C_EN_TX_CMD_BLOCK_Msk                             (0x1UL << I2C_EN_TX_CMD_BLOCK_POS)
#define I2C_EN_TX_CMD_BLOCK                                 I2C_EN_TX_CMD_BLOCK_Msk

#define I2C_EN_SDA_STUCK_RECOVERY_POS                       (3U)
#define I2C_EN_SDA_STUCK_RECOVERY_Len                       (1U)
#define I2C_EN_SDA_STUCK_RECOVERY_Msk                       (0x1UL << I2C_EN_SDA_STUCK_RECOVERY_POS)
#define I2C_EN_SDA_STUCK_RECOVERY                           I2C_EN_SDA_STUCK_RECOVERY_Msk

/*******************  Bit definition for I2C_STAT register  *******************/
#define I2C_STAT_ACTIVITY_POS                               (0U)
#define I2C_STAT_ACTIVITY_Len                               (1U)
#define I2C_STAT_ACTIVITY_Msk                               (0x1UL << I2C_STAT_ACTIVITY_POS)
#define I2C_STAT_ACTIVITY                                   I2C_STAT_ACTIVITY_Msk

#define I2C_STAT_TX_FIFO_NF_POS                             (1U)
#define I2C_STAT_TX_FIFO_NF_Len                             (1U)
#define I2C_STAT_TX_FIFO_NF_Msk                             (0x1UL << I2C_STAT_TX_FIFO_NF_POS)
#define I2C_STAT_TX_FIFO_NF                                 I2C_STAT_TX_FIFO_NF_Msk

#define I2C_STAT_TX_FIFO_CE_POS                             (2U)
#define I2C_STAT_TX_FIFO_CE_Len                             (1U)
#define I2C_STAT_TX_FIFO_CE_Msk                             (0x1UL << I2C_STAT_TX_FIFO_CE_POS)
#define I2C_STAT_TX_FIFO_CE                                 I2C_STAT_TX_FIFO_CE_Msk

#define I2C_STAT_RX_FIFO_NE_POS                             (3U)
#define I2C_STAT_RX_FIFO_NE_Len                             (1U)
#define I2C_STAT_RX_FIFO_NE_Msk                             (0x1UL << I2C_STAT_RX_FIFO_NE_POS)
#define I2C_STAT_RX_FIFO_NE                                 I2C_STAT_RX_FIFO_NE_Msk

#define I2C_STAT_RX_FIFO_CF_POS                             (4U)
#define I2C_STAT_RX_FIFO_CF_Len                             (1U)
#define I2C_STAT_RX_FIFO_CF_Msk                             (0x1UL << I2C_STAT_RX_FIFO_CF_POS)
#define I2C_STAT_RX_FIFO_CF                                 I2C_STAT_RX_FIFO_CF_Msk

#define I2C_STAT_M_ACTIVITY_POS                             (5U)
#define I2C_STAT_M_ACTIVITY_Len                             (1U)
#define I2C_STAT_M_ACTIVITY_Msk                             (0x1UL << I2C_STAT_M_ACTIVITY_POS)
#define I2C_STAT_M_ACTIVITY                                 I2C_STAT_M_ACTIVITY_Msk

#define I2C_STAT_S_ACTIVITY_POS                             (6U)
#define I2C_STAT_S_ACTIVITY_Len                             (1U)
#define I2C_STAT_S_ACTIVITY_Msk                             (0x1UL << I2C_STAT_S_ACTIVITY_POS)
#define I2C_STAT_S_ACTIVITY                                 I2C_STAT_S_ACTIVITY_Msk

#define I2C_STAT_SDA_STUCK_RCVR_POS                         (11U)
#define I2C_STAT_SDA_STUCK_RCVR_Len                         (1U)
#define I2C_STAT_SDA_STUCK_RCVR_Msk                         (0x1UL << I2C_STAT_SDA_STUCK_RCVR_POS)
#define I2C_STAT_SDA_STUCK_RCVR                             I2C_STAT_SDA_STUCK_RCVR_Msk

/*******************  Bit definition for I2C_TX_FIFO_LEVEL register  *******************/
#define I2C_TX_FIFO_LEVEL_LEVEL_POS                         (0U)
#define I2C_TX_FIFO_LEVEL_LEVEL_Len                         (8U)
#define I2C_TX_FIFO_LEVEL_LEVEL_Msk                         (0xFFUL << I2C_TX_FIFO_LEVEL_LEVEL_POS)
#define I2C_TX_FIFO_LEVEL_LEVEL                             I2C_TX_FIFO_LEVEL_LEVEL_Msk

/*******************  Bit definition for I2C_RX_FIFO_LEVEL register  *******************/
#define I2C_RX_FIFO_LEVEL_LEVEL_POS                         (0U)
#define I2C_RX_FIFO_LEVEL_LEVEL_Len                         (8U)
#define I2C_RX_FIFO_LEVEL_LEVEL_Msk                         (0xFFUL << I2C_RX_FIFO_LEVEL_LEVEL_POS)
#define I2C_RX_FIFO_LEVEL_LEVEL                             I2C_RX_FIFO_LEVEL_LEVEL_Msk

/*******************  Bit definition for I2C_SDA_HOLD register  *******************/
#define I2C_SDA_HOLD_TX_HOLD_POS                            (0U)
#define I2C_SDA_HOLD_TX_HOLD_Len                            (16U)
#define I2C_SDA_HOLD_TX_HOLD_Msk                            (0xFFFFUL << I2C_SDA_HOLD_TX_HOLD_POS)
#define I2C_SDA_HOLD_TX_HOLD                                I2C_SDA_HOLD_TX_HOLD_Msk

#define I2C_SDA_HOLD_RX_HOLD_POS                            (16U)
#define I2C_SDA_HOLD_RX_HOLD_Len                            (8U)
#define I2C_SDA_HOLD_RX_HOLD_Msk                            (0xFFUL << I2C_SDA_HOLD_RX_HOLD_POS)
#define I2C_SDA_HOLD_RX_HOLD                                I2C_SDA_HOLD_RX_HOLD_Msk

/*******************  Bit definition for I2C_TX_ABORT_SRC register  *******************/
#define I2C_TX_ABORT_SRC_ABORT_7B_NOACK_POS                 (0U)
#define I2C_TX_ABORT_SRC_ABORT_7B_NOACK_Len                 (1U)
#define I2C_TX_ABORT_SRC_ABORT_7B_NOACK_Msk                 (0x1UL << I2C_TX_ABORT_SRC_ABORT_7B_NOACK_POS)
#define I2C_TX_ABORT_SRC_ABORT_7B_NOACK                     I2C_TX_ABORT_SRC_ABORT_7B_NOACK_Msk

#define I2C_TX_ABORT_SRC_ABORT_10B1_NOACK_POS               (1U)
#define I2C_TX_ABORT_SRC_ABORT_10B1_NOACK_Len               (1U)
#define I2C_TX_ABORT_SRC_ABORT_10B1_NOACK_Msk               (0x1UL << I2C_TX_ABORT_SRC_ABORT_10B1_NOACK_POS)
#define I2C_TX_ABORT_SRC_ABORT_10B1_NOACK                   I2C_TX_ABORT_SRC_ABORT_10B1_NOACK_Msk

#define I2C_TX_ABORT_SRC_ABORT_10B2_NOACK_POS               (2U)
#define I2C_TX_ABORT_SRC_ABORT_10B2_NOACK_Len               (1U)
#define I2C_TX_ABORT_SRC_ABORT_10B2_NOACK_Msk               (0x1UL << I2C_TX_ABORT_SRC_ABORT_10B2_NOACK_POS)
#define I2C_TX_ABORT_SRC_ABORT_10B2_NOACK                   I2C_TX_ABORT_SRC_ABORT_10B2_NOACK_Msk

#define I2C_TX_ABORT_SRC_ABORT_TX_NOACK_POS                 (3U)
#define I2C_TX_ABORT_SRC_ABORT_TX_NOACK_Len                 (1U)
#define I2C_TX_ABORT_SRC_ABORT_TX_NOACK_Msk                 (0x1UL << I2C_TX_ABORT_SRC_ABORT_TX_NOACK_POS)
#define I2C_TX_ABORT_SRC_ABORT_TX_NOACK                     I2C_TX_ABORT_SRC_ABORT_TX_NOACK_Msk

#define I2C_TX_ABORT_SRC_ABORT_GCALL_NOACK_POS              (4U)
#define I2C_TX_ABORT_SRC_ABORT_GCALL_NOACK_Len              (1U)
#define I2C_TX_ABORT_SRC_ABORT_GCALL_NOACK_Msk              (0x1UL << I2C_TX_ABORT_SRC_ABORT_GCALL_NOACK_POS)
#define I2C_TX_ABORT_SRC_ABORT_GCALL_NOACK                  I2C_TX_ABORT_SRC_ABORT_GCALL_NOACK_Msk

#define I2C_TX_ABORT_SRC_ABORT_GCALL_RD_POS                 (5U)
#define I2C_TX_ABORT_SRC_ABORT_GCALL_RD_Len                 (1U)
#define I2C_TX_ABORT_SRC_ABORT_GCALL_RD_Msk                 (0x1UL << I2C_TX_ABORT_SRC_ABORT_GCALL_RD_POS)
#define I2C_TX_ABORT_SRC_ABORT_GCALL_RD                     I2C_TX_ABORT_SRC_ABORT_GCALL_RD_Msk

#define I2C_TX_ABORT_SRC_ABORT_HS_ACKDET_POS                (6U)
#define I2C_TX_ABORT_SRC_ABORT_HS_ACKDET_Len                (1U)
#define I2C_TX_ABORT_SRC_ABORT_HS_ACKDET_Msk                (0x1UL << I2C_TX_ABORT_SRC_ABORT_HS_ACKDET_POS)
#define I2C_TX_ABORT_SRC_ABORT_HS_ACKDET                    I2C_TX_ABORT_SRC_ABORT_HS_ACKDET_Msk

#define I2C_TX_ABORT_SRC_ABORT_SBYTE_ACKDET_POS             (7U)
#define I2C_TX_ABORT_SRC_ABORT_SBYTE_ACKDET_Len             (1U)
#define I2C_TX_ABORT_SRC_ABORT_SBYTE_ACKDET_Msk             (0x1UL << I2C_TX_ABORT_SRC_ABORT_SBYTE_ACKDET_POS)
#define I2C_TX_ABORT_SRC_ABORT_SBYTE_ACKDET                 I2C_TX_ABORT_SRC_ABORT_SBYTE_ACKDET_Msk

#define I2C_TX_ABORT_SRC_ABORT_HS_NORSTRT_POS               (8U)
#define I2C_TX_ABORT_SRC_ABORT_HS_NORSTRT_Len               (1U)
#define I2C_TX_ABORT_SRC_ABORT_HS_NORSTRT_Msk               (0x1UL << I2C_TX_ABORT_SRC_ABORT_HS_NORSTRT_POS)
#define I2C_TX_ABORT_SRC_ABORT_HS_NORSTRT                   I2C_TX_ABORT_SRC_ABORT_HS_NORSTRT_Msk

#define I2C_TX_ABORT_SRC_ABORT_SBYTE_NORSTRT_POS            (9U)
#define I2C_TX_ABORT_SRC_ABORT_SBYTE_NORSTRT_Len            (1U)
#define I2C_TX_ABORT_SRC_ABORT_SBYTE_NORSTRT_Msk            (0x1UL << I2C_TX_ABORT_SRC_ABORT_SBYTE_NORSTRT_POS)
#define I2C_TX_ABORT_SRC_ABORT_SBYTE_NORSTRT                I2C_TX_ABORT_SRC_ABORT_SBYTE_NORSTRT_Msk

#define I2C_TX_ABORT_SRC_ABORT_10B_RD_NORSTR_POS            (10U)
#define I2C_TX_ABORT_SRC_ABORT_10B_RD_NORSTR_Len            (1U)
#define I2C_TX_ABORT_SRC_ABORT_10B_RD_NORSTR_Msk            (0x1UL << I2C_TX_ABORT_SRC_ABORT_10B_RD_NORSTR_POS)
#define I2C_TX_ABORT_SRC_ABORT_10B_RD_NORSTR                I2C_TX_ABORT_SRC_ABORT_10B_RD_NORSTR_Msk

#define I2C_TX_ABORT_SRC_ABORT_MASTER_DIS_POS               (11U)
#define I2C_TX_ABORT_SRC_ABORT_MASTER_DIS_Len               (1U)
#define I2C_TX_ABORT_SRC_ABORT_MASTER_DIS_Msk               (0x1UL << I2C_TX_ABORT_SRC_ABORT_MASTER_DIS_POS)
#define I2C_TX_ABORT_SRC_ABORT_MASTER_DIS                   I2C_TX_ABORT_SRC_ABORT_MASTER_DIS_Msk

#define I2C_TX_ABORT_SRC_ABORT_LOST_POS                     (12U)
#define I2C_TX_ABORT_SRC_ABORT_LOST_Len                     (1U)
#define I2C_TX_ABORT_SRC_ABORT_LOST_Msk                     (0x1UL << I2C_TX_ABORT_SRC_ABORT_LOST_POS)
#define I2C_TX_ABORT_SRC_ABORT_LOST                         I2C_TX_ABORT_SRC_ABORT_LOST_Msk

#define I2C_TX_ABORT_SRC_ABORT_SLVFLUSH_TXFIFO_POS          (13U)
#define I2C_TX_ABORT_SRC_ABORT_SLVFLUSH_TXFIFO_Len          (1U)
#define I2C_TX_ABORT_SRC_ABORT_SLVFLUSH_TXFIFO_Msk          (0x1UL << I2C_TX_ABORT_SRC_ABORT_SLVFLUSH_TXFIFO_POS)
#define I2C_TX_ABORT_SRC_ABORT_SLVFLUSH_TXFIFO              I2C_TX_ABORT_SRC_ABORT_SLVFLUSH_TXFIFO_Msk

#define I2C_TX_ABORT_SRC_ABORT_S_ARBLOST_POS                (14U)
#define I2C_TX_ABORT_SRC_ABORT_S_ARBLOST_Len                (1U)
#define I2C_TX_ABORT_SRC_ABORT_S_ARBLOST_Msk                (0x1UL << I2C_TX_ABORT_SRC_ABORT_S_ARBLOST_POS)
#define I2C_TX_ABORT_SRC_ABORT_S_ARBLOST                    I2C_TX_ABORT_SRC_ABORT_S_ARBLOST_Msk

#define I2C_TX_ABORT_SRC_ABORT_SLVRD_INTX_POS               (15U)
#define I2C_TX_ABORT_SRC_ABORT_SLVRD_INTX_Len               (1U)
#define I2C_TX_ABORT_SRC_ABORT_SLVRD_INTX_Msk               (0x1UL << I2C_TX_ABORT_SRC_ABORT_SLVRD_INTX_POS)
#define I2C_TX_ABORT_SRC_ABORT_SLVRD_INTX                   I2C_TX_ABORT_SRC_ABORT_SLVRD_INTX_Msk

#define I2C_TX_ABORT_SRC_ABORT_USER_ABORT_POS               (16U)
#define I2C_TX_ABORT_SRC_ABORT_USER_ABORT_Len               (1U)
#define I2C_TX_ABORT_SRC_ABORT_USER_ABORT_Msk               (0x1UL << I2C_TX_ABORT_SRC_ABORT_USER_ABORT_POS)
#define I2C_TX_ABORT_SRC_ABORT_USER_ABORT                   I2C_TX_ABORT_SRC_ABORT_USER_ABORT_Msk

#define I2C_TX_ABORT_SRC_ABORT_SDA_STUCK_POS                (17U)
#define I2C_TX_ABORT_SRC_ABORT_SDA_STUCK_Len                (1U)
#define I2C_TX_ABORT_SRC_ABORT_SDA_STUCK_Msk                (0x1UL << I2C_TX_ABORT_SRC_ABORT_SDA_STUCK_POS)
#define I2C_TX_ABORT_SRC_ABORT_SDA_STUCK                    I2C_TX_ABORT_SRC_ABORT_SDA_STUCK_Msk

#define I2C_TX_ABORT_SRC_TX_FLUSH_CNT_POS                   (23U)
#define I2C_TX_ABORT_SRC_TX_FLUSH_CNT_Len                   (9U)
#define I2C_TX_ABORT_SRC_TX_FLUSH_CNT_Msk                   (0x1FFUL << I2C_TX_ABORT_SRC_TX_FLUSH_CNT_POS)
#define I2C_TX_ABORT_SRC_TX_FLUSH_CNT                       I2C_TX_ABORT_SRC_TX_FLUSH_CNT_Msk

/*******************  Bit definition for I2C_DMA_CTRL register  *******************/
#define I2C_DMA_CTRL_RX_EN_POS                              (0U)
#define I2C_DMA_CTRL_RX_EN_Len                              (1U)
#define I2C_DMA_CTRL_RX_EN_Msk                              (0x1UL << I2C_DMA_CTRL_RX_EN_POS)
#define I2C_DMA_CTRL_RX_EN                                  I2C_DMA_CTRL_RX_EN_Msk

#define I2C_DMA_CTRL_TX_EN_POS                              (1U)
#define I2C_DMA_CTRL_TX_EN_Len                              (1U)
#define I2C_DMA_CTRL_TX_EN_Msk                              (0x1UL << I2C_DMA_CTRL_TX_EN_POS)
#define I2C_DMA_CTRL_TX_EN                                  I2C_DMA_CTRL_TX_EN_Msk

/*******************  Bit definition for I2C_DMA_TX_LEVEL register  *******************/
#define I2C_DMA_TX_LEVEL_LEVEL_POS                          (0U)
#define I2C_DMA_TX_LEVEL_LEVEL_Len                          (5U)
#define I2C_DMA_TX_LEVEL_LEVEL_Msk                          (0x1FUL << I2C_DMA_TX_LEVEL_LEVEL_POS)
#define I2C_DMA_TX_LEVEL_LEVEL                              I2C_DMA_TX_LEVEL_LEVEL_Msk

/*******************  Bit definition for I2C_DMA_RX_LEVEL register  *******************/
#define I2C_DMA_RX_LEVEL_LEVEL_POS                          (0U)
#define I2C_DMA_RX_LEVEL_LEVEL_Len                          (5U)
#define I2C_DMA_RX_LEVEL_LEVEL_Msk                          (0x1FUL << I2C_DMA_RX_LEVEL_LEVEL_POS)
#define I2C_DMA_RX_LEVEL_LEVEL                              I2C_DMA_RX_LEVEL_LEVEL_Msk

/*******************  Bit definition for I2C_SDA_SETUP register  *******************/
#define I2C_SDA_SETUP_SETUP_POS                             (0U)
#define I2C_SDA_SETUP_SETUP_Len                             (8U)
#define I2C_SDA_SETUP_SETUP_Msk                             (0xFFUL << I2C_SDA_SETUP_SETUP_POS)
#define I2C_SDA_SETUP_SETUP                                 I2C_SDA_SETUP_SETUP_Msk

/*******************  Bit definition for I2C_ACK_GEN_CALL register  *******************/
#define I2C_ACK_GEN_CALL_ACK_GEN_CALL_POS                   (0U)
#define I2C_ACK_GEN_CALL_ACK_GEN_CALL_Len                   (1U)
#define I2C_ACK_GEN_CALL_ACK_GEN_CALL_Msk                   (0x1UL << I2C_ACK_GEN_CALL_ACK_GEN_CALL_POS)
#define I2C_ACK_GEN_CALL_ACK_GEN_CALL                       I2C_ACK_GEN_CALL_ACK_GEN_CALL_Msk

/*******************  Bit definition for I2C_EN_STAT register  *******************/
#define I2C_EN_STAT_EN_POS                                  (0U)
#define I2C_EN_STAT_EN_Len                                  (1U)
#define I2C_EN_STAT_EN_Msk                                  (0x1UL << I2C_EN_STAT_EN_POS)
#define I2C_EN_STAT_EN                                      I2C_EN_STAT_EN_Msk

#define I2C_EN_STAT_S_DIS_BUSY_POS                          (1U)
#define I2C_EN_STAT_S_DIS_BUSY_Len                          (1U)
#define I2C_EN_STAT_S_DIS_BUSY_Msk                          (0x1UL << I2C_EN_STAT_S_DIS_BUSY_POS)
#define I2C_EN_STAT_S_DIS_BUSY                              I2C_EN_STAT_S_DIS_BUSY_Msk

#define I2C_EN_STAT_S_RX_DATA_LOST_POS                      (2U)
#define I2C_EN_STAT_S_RX_DATA_LOST_Len                      (1U)
#define I2C_EN_STAT_S_RX_DATA_LOST_Msk                      (0x1UL << I2C_EN_STAT_S_RX_DATA_LOST_POS)
#define I2C_EN_STAT_S_RX_DATA_LOST                          I2C_EN_STAT_S_RX_DATA_LOST_Msk

/*******************  Bit definition for I2C_FS_SPKLEN register  *******************/
#define I2C_FS_SPKLEN_FS_SPKLEN_POS                         (0U)
#define I2C_FS_SPKLEN_FS_SPKLEN_Len                         (8U)
#define I2C_FS_SPKLEN_FS_SPKLEN_Msk                         (0xFFUL << I2C_FS_SPKLEN_FS_SPKLEN_POS)
#define I2C_FS_SPKLEN_FS_SPKLEN                             I2C_FS_SPKLEN_FS_SPKLEN_Msk

/*******************  Bit definition for I2C_HS_SPKLEN register  *******************/
#define I2C_HS_SPKLEN_HS_SPKLEN_POS                         (0U)
#define I2C_HS_SPKLEN_HS_SPKLEN_Len                         (8U)
#define I2C_HS_SPKLEN_HS_SPKLEN_Msk                         (0xFFUL << I2C_HS_SPKLEN_HS_SPKLEN_POS)
#define I2C_HS_SPKLEN_HS_SPKLEN                             I2C_HS_SPKLEN_HS_SPKLEN_Msk

/* ================================================================================================================= */
/* ================                                        I2S                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for I2S_EN register  *******************/
#define I2S_EN_I2S_EN_POS                                   (0U)
#define I2S_EN_I2S_EN_Len                                   (1U)
#define I2S_EN_I2S_EN_Msk                                   (0x1UL << I2S_EN_I2S_EN_POS)
#define I2S_EN_I2S_EN                                       I2S_EN_I2S_EN_Msk

/*******************  Bit definition for I2S_RX_EN register  *******************/
#define I2S_RX_EN_RX_EN_POS                                 (0U)
#define I2S_RX_EN_RX_EN_Len                                 (1U)
#define I2S_RX_EN_RX_EN_Msk                                 (0x1UL << I2S_RX_EN_RX_EN_POS)
#define I2S_RX_EN_RX_EN                                     I2S_RX_EN_RX_EN_Msk

/*******************  Bit definition for I2S_TX_EN register  *******************/
#define I2S_TX_EN_TX_EN_POS                                 (0U)
#define I2S_TX_EN_TX_EN_Len                                 (1U)
#define I2S_TX_EN_TX_EN_Msk                                 (0x1UL << I2S_TX_EN_TX_EN_POS)
#define I2S_TX_EN_TX_EN                                     I2S_TX_EN_TX_EN_Msk

/*******************  Bit definition for I2S_CLK_EN register  *******************/
#define I2S_CLK_EN_CLK_EN_POS                               (0U)
#define I2S_CLK_EN_CLK_EN_Len                               (1U)
#define I2S_CLK_EN_CLK_EN_Msk                               (0x1UL << I2S_CLK_EN_CLK_EN_POS)
#define I2S_CLK_EN_CLK_EN                                   I2S_CLK_EN_CLK_EN_Msk

/*******************  Bit definition for I2S_SCLK_CFG register  *******************/
#define I2S_SCLK_CFG_SCLK_GAT_POS                           (0U)
#define I2S_SCLK_CFG_SCLK_GAT_Len                           (3U)
#define I2S_SCLK_CFG_SCLK_GAT_Msk                           (0x7UL << I2S_SCLK_CFG_SCLK_GAT_POS)
#define I2S_SCLK_CFG_SCLK_GAT                               I2S_SCLK_CFG_SCLK_GAT_Msk

#define I2S_SCLK_CFG_WS_SCLK_POS                            (3U)
#define I2S_SCLK_CFG_WS_SCLK_Len                            (2U)
#define I2S_SCLK_CFG_WS_SCLK_Msk                            (0x3UL << I2S_SCLK_CFG_WS_SCLK_POS)
#define I2S_SCLK_CFG_WS_SCLK                                I2S_SCLK_CFG_WS_SCLK_Msk

/*******************  Bit definition for I2S_RX_FIFO_RST register  *******************/
#define I2S_RX_FIFO_RST_RX_FIFO_RST_POS                     (0U)
#define I2S_RX_FIFO_RST_RX_FIFO_RST_Len                     (1U)
#define I2S_RX_FIFO_RST_RX_FIFO_RST_Msk                     (0x1UL << I2S_RX_FIFO_RST_RX_FIFO_RST_POS)
#define I2S_RX_FIFO_RST_RX_FIFO_RST                         I2S_RX_FIFO_RST_RX_FIFO_RST_Msk

/*******************  Bit definition for I2S_TX_FIFO_RST register  *******************/
#define I2S_TX_FIFO_RST_TX_FIFO_RST_POS                     (0U)
#define I2S_TX_FIFO_RST_TX_FIFO_RST_Len                     (1U)
#define I2S_TX_FIFO_RST_TX_FIFO_RST_Msk                     (0x1UL << I2S_TX_FIFO_RST_TX_FIFO_RST_POS)
#define I2S_TX_FIFO_RST_TX_FIFO_RST                         I2S_TX_FIFO_RST_TX_FIFO_RST_Msk

/*******************  Bit definition for I2S_LEFT_RX_BUF register  *******************/
#define I2S_LEFT_BUF_LEFT_BUF_POS                            (0U)
#define I2S_LEFT_BUF_LEFT_BUF_Len                            (32U)
#define I2S_LEFT_BUF_LEFT_BUF_Msk                            (0xFFFFFFFFUL << I2S_LEFT_BUF_LEFT_BUF_POS)
#define I2S_LEFT_BUF_LEFT_BUF                                 I2S_LEFT_BUF_LEFT_BUF_Msk

/*******************  Bit definition for I2S_RIGHT_RX_BUF register  *******************/
#define I2S_RIGHT_BUF_RIGHT_BUF_POS                          (0U)
#define I2S_RIGHT_BUF_RIGHT_BUF_Len                          (32U)
#define I2S_RIGHT_BUF_RIGHT_BUF_Msk                          (0xFFFFFFFFUL << I2S_RIGHT_BUF_RIGHT_BUF_POS)
#define I2S_RIGHT_BUF_RIGHT_BUF                               I2S_RIGHT_BUF_RIGHT_BUF_Msk

/*******************  Bit definition for I2S_RX_CH_EN register  *******************/
#define I2S_RX_CH_EN_RX_CH_EN_POS                           (0U)
#define I2S_RX_CH_EN_RX_CH_EN_Len                           (1U)
#define I2S_RX_CH_EN_RX_CH_EN_Msk                           (0x1UL << I2S_RX_CH_EN_RX_CH_EN_POS)
#define I2S_RX_CH_EN_RX_CH_EN                               I2S_RX_CH_EN_RX_CH_EN_Msk

/*******************  Bit definition for I2S_TX_CH_EN register  *******************/
#define I2S_TX_CH_EN_TX_CH_EN_POS                           (0U)
#define I2S_TX_CH_EN_TX_CH_EN_Len                           (1U)
#define I2S_TX_CH_EN_TX_CH_EN_Msk                           (0x1UL << I2S_TX_CH_EN_TX_CH_EN_POS)
#define I2S_TX_CH_EN_TX_CH_EN                               I2S_TX_CH_EN_TX_CH_EN_Msk

/*******************  Bit definition for I2S_RX_CFG register  *******************/
#define I2S_RX_CFG_WORD_LEN_POS                             (0U)
#define I2S_RX_CFG_WORD_LEN_Len                             (3U)
#define I2S_RX_CFG_WORD_LEN_Msk                             (0x7UL << I2S_RX_CFG_WORD_LEN_POS)
#define I2S_RX_CFG_WORD_LEN                                 I2S_RX_CFG_WORD_LEN_Msk

/*******************  Bit definition for I2S_TX_CFG register  *******************/
#define I2S_TX_CFG_WORD_LEN_POS                             (0U)
#define I2S_TX_CFG_WORD_LEN_Len                             (3U)
#define I2S_TX_CFG_WORD_LEN_Msk                             (0x7UL << I2S_TX_CFG_WORD_LEN_POS)
#define I2S_TX_CFG_WORD_LEN                                 I2S_TX_CFG_WORD_LEN_Msk

/*******************  Bit definition for I2S_INT_STAT register  *******************/
#define I2S_INT_STAT_RX_DATA_AVL_POS                        (0U)
#define I2S_INT_STAT_RX_DATA_AVL_Len                        (1U)
#define I2S_INT_STAT_RX_DATA_AVL_Msk                        (0x1UL << I2S_INT_STAT_RX_DATA_AVL_POS)
#define I2S_INT_STAT_RX_DATA_AVL                            I2S_INT_STAT_RX_DATA_AVL_Msk

#define I2S_INT_STAT_RX_FIFO_OVER_POS                       (1U)
#define I2S_INT_STAT_RX_FIFO_OVER_Len                       (1U)
#define I2S_INT_STAT_RX_FIFO_OVER_Msk                       (0x1UL << I2S_INT_STAT_RX_FIFO_OVER_POS)
#define I2S_INT_STAT_RX_FIFO_OVER                           I2S_INT_STAT_RX_FIFO_OVER_Msk

#define I2S_INT_STAT_TX_FIFO_EMPTY_POS                      (4U)
#define I2S_INT_STAT_TX_FIFO_EMPTY_Len                      (1U)
#define I2S_INT_STAT_TX_FIFO_EMPTY_Msk                      (0x1UL << I2S_INT_STAT_TX_FIFO_EMPTY_POS)
#define I2S_INT_STAT_TX_FIFO_EMPTY                          I2S_INT_STAT_TX_FIFO_EMPTY_Msk

#define I2S_INT_STAT_TX_FIFO_OVER_POS                       (5U)
#define I2S_INT_STAT_TX_FIFO_OVER_Len                       (1U)
#define I2S_INT_STAT_TX_FIFO_OVER_Msk                       (0x1UL << I2S_INT_STAT_TX_FIFO_OVER_POS)
#define I2S_INT_STAT_TX_FIFO_OVER                           I2S_INT_STAT_TX_FIFO_OVER_Msk

/*******************  Bit definition for I2S_INT_MASK register  *******************/
#define I2S_INT_MASK_RX_DAM_POS                             (0U)
#define I2S_INT_MASK_RX_DAM_Len                             (1U)
#define I2S_INT_MASK_RX_DAM_Msk                             (0x1UL << I2S_INT_MASK_RX_DAM_POS)
#define I2S_INT_MASK_RX_DAM                                 I2S_INT_MASK_RX_DAM_Msk

#define I2S_INT_MASK_RX_FOM_POS                             (1U)
#define I2S_INT_MASK_RX_FOM_Len                             (1U)
#define I2S_INT_MASK_RX_FOM_Msk                             (0x1UL << I2S_INT_MASK_RX_FOM_POS)
#define I2S_INT_MASK_RX_FOM                                 I2S_INT_MASK_RX_FOM_Msk

#define I2S_INT_MASK_TX_FEM_POS                             (4U)
#define I2S_INT_MASK_TX_FEM_Len                             (1U)
#define I2S_INT_MASK_TX_FEM_Msk                             (0x1UL << I2S_INT_MASK_TX_FEM_POS)
#define I2S_INT_MASK_TX_FEM                                 I2S_INT_MASK_TX_FEM_Msk

#define I2S_INT_MASK_TX_FOM_POS                             (5U)
#define I2S_INT_MASK_TX_FOM_Len                             (1U)
#define I2S_INT_MASK_TX_FOM_Msk                             (0x1UL << I2S_INT_MASK_TX_FOM_POS)
#define I2S_INT_MASK_TX_FOM                                 I2S_INT_MASK_TX_FOM_Msk

/*******************  Bit definition for I2S_RX_OVER register  *******************/
#define I2S_RX_OVER_RX_CLR_FDO_POS                          (0U)
#define I2S_RX_OVER_RX_CLR_FDO_Len                          (1U)
#define I2S_RX_OVER_RX_CLR_FDO_Msk                          (0x1UL << I2S_RX_OVER_RX_CLR_FDO_POS)
#define I2S_RX_OVER_RX_CLR_FDO                              I2S_RX_OVER_RX_CLR_FDO_Msk

/*******************  Bit definition for I2S_TX_OVER register  *******************/
#define I2S_TX_OVER_TX_CLR_FDO_POS                          (0U)
#define I2S_TX_OVER_TX_CLR_FDO_Len                          (1U)
#define I2S_TX_OVER_TX_CLR_FDO_Msk                          (0x1UL << I2S_TX_OVER_TX_CLR_FDO_POS)
#define I2S_TX_OVER_TX_CLR_FDO                              I2S_TX_OVER_TX_CLR_FDO_Msk

/*******************  Bit definition for I2S_RX_FIFO_CFG register  *******************/
#define I2S_RX_FIFO_CFG_RX_FIFO_TL_POS                      (0U)
#define I2S_RX_FIFO_CFG_RX_FIFO_TL_Len                      (4U)
#define I2S_RX_FIFO_CFG_RX_FIFO_TL_Msk                      (0xFUL << I2S_RX_FIFO_CFG_RX_FIFO_TL_POS)
#define I2S_RX_FIFO_CFG_RX_FIFO_TL                          I2S_RX_FIFO_CFG_RX_FIFO_TL_Msk

/*******************  Bit definition for I2S_TX_FIFO_CFG register  *******************/
#define I2S_TX_FIFO_CFG_TX_FIFO_TL_POS                      (0U)
#define I2S_TX_FIFO_CFG_TX_FIFO_TL_Len                      (4U)
#define I2S_TX_FIFO_CFG_TX_FIFO_TL_Msk                      (0xFUL << I2S_TX_FIFO_CFG_TX_FIFO_TL_POS)
#define I2S_TX_FIFO_CFG_TX_FIFO_TL                          I2S_TX_FIFO_CFG_TX_FIFO_TL_Msk

/*******************  Bit definition for I2S_RX_FIFO_FLUSH register  *******************/
#define I2S_RX_FIFO_FLUSH_RX_FIFO_RST_POS                   (0U)
#define I2S_RX_FIFO_FLUSH_RX_FIFO_RST_Len                   (1U)
#define I2S_RX_FIFO_FLUSH_RX_FIFO_RST_Msk                   (0x1UL << I2S_RX_FIFO_FLUSH_RX_FIFO_RST_POS)
#define I2S_RX_FIFO_FLUSH_RX_FIFO_RST                       I2S_RX_FIFO_FLUSH_RX_FIFO_RST_Msk

/*******************  Bit definition for I2S_TX_FIFO_FLUSH register  *******************/
#define I2S_TX_FIFO_FLUSH_TX_FIFO_RST_POS                   (0U)
#define I2S_TX_FIFO_FLUSH_TX_FIFO_RST_Len                   (1U)
#define I2S_TX_FIFO_FLUSH_TX_FIFO_RST_Msk                   (0x1UL << I2S_TX_FIFO_FLUSH_TX_FIFO_RST_POS)
#define I2S_TX_FIFO_FLUSH_TX_FIFO_RST                       I2S_TX_FIFO_FLUSH_TX_FIFO_RST_Msk

/*******************  Bit definition for I2S_RX_DMA register  *******************/
#define I2S_RX_DMA_RX_DMA_POS                               (0U)
#define I2S_RX_DMA_RX_DMA_Len                               (1U)
#define I2S_RX_DMA_RX_DMA_Msk                               (0x1UL << I2S_RX_DMA_RX_DMA_POS)
#define I2S_RX_DMA_RX_DMA                                   I2S_RX_DMA_RX_DMA_Msk

/*******************  Bit definition for I2S_RST_RX_DMA register  *******************/
#define I2S_RST_RX_DMA_RST_RX_DMA_POS                       (0U)
#define I2S_RST_RX_DMA_RST_RX_DMA_Len                       (1U)
#define I2S_RST_RX_DMA_RST_RX_DMA_Msk                       (0x1UL << I2S_RST_RX_DMA_RST_RX_DMA_POS)
#define I2S_RST_RX_DMA_RST_RX_DMA                           I2S_RST_RX_DMA_RST_RX_DMA_Msk

/*******************  Bit definition for I2S_TX_DMA register  *******************/
#define I2S_TX_DMA_TX_DMA_POS                               (0U)
#define I2S_TX_DMA_TX_DMA_Len                               (1U)
#define I2S_TX_DMA_TX_DMA_Msk                               (0x1UL << I2S_TX_DMA_TX_DMA_POS)
#define I2S_TX_DMA_TX_DMA                                   I2S_TX_DMA_TX_DMA_Msk

/*******************  Bit definition for I2S_RST_TX_DMA register  *******************/
#define I2S_RST_TX_DMA_RST_TX_DMA_POS                       (0U)
#define I2S_RST_TX_DMA_RST_TX_DMA_Len                       (1U)
#define I2S_RST_TX_DMA_RST_TX_DMA_Msk                       (0x1UL << I2S_RST_TX_DMA_RST_TX_DMA_POS)
#define I2S_RST_TX_DMA_RST_TX_DMA                           I2S_RST_TX_DMA_RST_TX_DMA_Msk


/* ================================================================================================================= */
/* ================                                        ISO7816                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for ISO7816_CTRL register  *******************/
#define ISO7816_CTRL_ACTION_POS                             (0U)
#define ISO7816_CTRL_ACTION_Len                             (3U)
#define ISO7816_CTRL_ACTION_Msk                             (0x7UL << ISO7816_CTRL_ACTION_POS)
#define ISO7816_CTRL_ACTION                                 ISO7816_CTRL_ACTION_Msk

#define ISO7816_CTRL_RX_RETYR_MC_POS                        (8U)
#define ISO7816_CTRL_RX_RETYR_MC_Len                        (1U)
#define ISO7816_CTRL_RX_RETYR_MC_Msk                        (0x1UL << ISO7816_CTRL_RX_RETYR_MC_POS)
#define ISO7816_CTRL_RX_RETYR_MC                            ISO7816_CTRL_RX_RETYR_MC_Msk

#define ISO7816_CTRL_TX_RETYR_MC_POS                        (12U)
#define ISO7816_CTRL_TX_RETYR_MC_Len                        (1U)
#define ISO7816_CTRL_TX_RETYR_MC_Msk                        (0x1UL << ISO7816_CTRL_TX_RETYR_MC_POS)
#define ISO7816_CTRL_TX_RETYR_MC                            ISO7816_CTRL_TX_RETYR_MC_Msk

#define ISO7816_CTRL_IRQ_DONE_CLR_POS                       (20U)
#define ISO7816_CTRL_IRQ_DONE_CLR_Len                       (1U)
#define ISO7816_CTRL_IRQ_DONE_CLR_Msk                       (0x1UL << ISO7816_CTRL_IRQ_DONE_CLR_POS)
#define ISO7816_CTRL_IRQ_DONE_CLR                           ISO7816_CTRL_IRQ_DONE_CLR_Msk

#define ISO7816_CTRL_IRQ_RX_EC_POS                          (21U)
#define ISO7816_CTRL_IRQ_RX_EC_Len                          (1U)
#define ISO7816_CTRL_IRQ_RX_EC_Msk                          (0x1UL << ISO7816_CTRL_IRQ_RX_EC_POS)
#define ISO7816_CTRL_IRQ_RX_EC                              ISO7816_CTRL_IRQ_RX_EC_Msk

#define ISO7816_CTRL_IRQ_RETYR_EC_POS                       (22U)
#define ISO7816_CTRL_IRQ_RETYR_EC_Len                       (1U)
#define ISO7816_CTRL_IRQ_RETYR_EC_Msk                       (0x1UL << ISO7816_CTRL_IRQ_RETYR_EC_POS)
#define ISO7816_CTRL_IRQ_RETYR_EC                           ISO7816_CTRL_IRQ_RETYR_EC_Msk

#define ISO7816_CTRL_IRQ_DMA_EC_POS                         (23U)
#define ISO7816_CTRL_IRQ_DMA_EC_Len                         (1U)
#define ISO7816_CTRL_IRQ_DMA_EC_Msk                         (0x1UL << ISO7816_CTRL_IRQ_DMA_EC_POS)
#define ISO7816_CTRL_IRQ_DMA_EC                             ISO7816_CTRL_IRQ_DMA_EC_Msk

#define ISO7816_CTRL_IRQ_STAT_EC_POS                        (24U)
#define ISO7816_CTRL_IRQ_STAT_EC_Len                        (1U)
#define ISO7816_CTRL_IRQ_STAT_EC_Msk                        (0x1UL << ISO7816_CTRL_IRQ_STAT_EC_POS)
#define ISO7816_CTRL_IRQ_STAT_EC                            ISO7816_CTRL_IRQ_STAT_EC_Msk

#define ISO7816_CTRL_IRQ_PRESENCE_CLR_POS                   (25U)
#define ISO7816_CTRL_IRQ_PRESENCE_CLR_Len                   (1U)
#define ISO7816_CTRL_IRQ_PRESENCE_CLR_Msk                   (0x1UL << ISO7816_CTRL_IRQ_PRESENCE_CLR_POS)
#define ISO7816_CTRL_IRQ_PRESENCE_CLR                       ISO7816_CTRL_IRQ_PRESENCE_CLR_Msk

#define ISO7816_CTRL_IRQ_TEST_CLR_POS                       (30U)
#define ISO7816_CTRL_IRQ_TEST_CLR_Len                       (1U)
#define ISO7816_CTRL_IRQ_TEST_CLR_Msk                       (0x1UL << ISO7816_CTRL_IRQ_TEST_CLR_POS)
#define ISO7816_CTRL_IRQ_TEST_CLR                           ISO7816_CTRL_IRQ_TEST_CLR_Msk

#define ISO7816_CTRL_IRQ_TEST_SET_POS                       (31U)
#define ISO7816_CTRL_IRQ_TEST_SET_Len                       (1U)
#define ISO7816_CTRL_IRQ_TEST_SET_Msk                       (0x1UL << ISO7816_CTRL_IRQ_TEST_SET_POS)
#define ISO7816_CTRL_IRQ_TEST_SET                           ISO7816_CTRL_IRQ_TEST_SET_Msk

/*******************  Bit definition for ISO7816_STAT register  *******************/
#define ISO7816_INTR_ALL                                       (0x43F00000)

#define ISO7816_STAT_PWR_STAT_POS                           (0U)
#define ISO7816_STAT_PWR_STAT_Len                           (4U)
#define ISO7816_STAT_PWR_STAT_Msk                           (0xFUL << ISO7816_STAT_PWR_STAT_POS)
#define ISO7816_STAT_PWR_STAT                               ISO7816_STAT_PWR_STAT_Msk

#define ISO7816_STAT_IO_STAT_POS                            (4U)
#define ISO7816_STAT_IO_STAT_Len                            (3U)
#define ISO7816_STAT_IO_STAT_Msk                            (0x7UL << ISO7816_STAT_IO_STAT_POS)
#define ISO7816_STAT_IO_STAT                                ISO7816_STAT_IO_STAT_Msk

#define ISO7816_STAT_RX_RETRY_MAX_POS                       (8U)
#define ISO7816_STAT_RX_RETRY_MAX_Len                       (3U)
#define ISO7816_STAT_RX_RETRY_MAX_Msk                       (0x7UL << ISO7816_STAT_RX_RETRY_MAX_POS)
#define ISO7816_STAT_RX_RETRY_MAX                           ISO7816_STAT_RX_RETRY_MAX_Msk

#define ISO7816_STAT_TX_RETRY_MAX_POS                       (12U)
#define ISO7816_STAT_TX_RETRY_MAX_Len                       (3U)
#define ISO7816_STAT_TX_RETRY_MAX_Msk                       (0x7UL << ISO7816_STAT_TX_RETRY_MAX_POS)
#define ISO7816_STAT_TX_RETRY_MAX                           ISO7816_STAT_TX_RETRY_MAX_Msk

#define ISO7816_STAT_BUSY_POS                               (16U)
#define ISO7816_STAT_BUSY_Len                               (1U)
#define ISO7816_STAT_BUSY_Msk                               (0x1UL << ISO7816_STAT_BUSY_POS)
#define ISO7816_STAT_BUSY                                   ISO7816_STAT_BUSY_Msk

#define ISO7816_STAT_PRESENCE_STAT_POS                      (17U)
#define ISO7816_STAT_PRESENCE_STAT_Len                      (1U)
#define ISO7816_STAT_PRESENCE_STAT_Msk                      (0x1UL << ISO7816_STAT_PRESENCE_STAT_POS)
#define ISO7816_STAT_PRESENCE_STAT                          ISO7816_STAT_PRESENCE_STAT_Msk

#define ISO7816_STAT_IRQ_DONE_POS                           (20U)
#define ISO7816_STAT_IRQ_DONE_Len                           (1U)
#define ISO7816_STAT_IRQ_DONE_Msk                           (0x1UL << ISO7816_STAT_IRQ_DONE_POS)
#define ISO7816_STAT_IRQ_DONE                               ISO7816_STAT_IRQ_DONE_Msk

#define ISO7816_STAT_IRQ_RX_ERR_POS                         (21U)
#define ISO7816_STAT_IRQ_RX_ERR_Len                         (1U)
#define ISO7816_STAT_IRQ_RX_ERR_Msk                         (0x1UL << ISO7816_STAT_IRQ_RX_ERR_POS)
#define ISO7816_STAT_IRQ_RX_ERR                             ISO7816_STAT_IRQ_RX_ERR_Msk

#define ISO7816_STAT_IRQ_RETRY_ERR_POS                      (22U)
#define ISO7816_STAT_IRQ_RETRY_ERR_Len                      (1U)
#define ISO7816_STAT_IRQ_RETRY_ERR_Msk                      (0x1UL << ISO7816_STAT_IRQ_RETRY_ERR_POS)
#define ISO7816_STAT_IRQ_RETRY_ERR                          ISO7816_STAT_IRQ_RETRY_ERR_Msk

#define ISO7816_STAT_IRQ_DMA_ERR_POS                        (23U)
#define ISO7816_STAT_IRQ_DMA_ERR_Len                        (1U)
#define ISO7816_STAT_IRQ_DMA_ERR_Msk                        (0x1UL << ISO7816_STAT_IRQ_DMA_ERR_POS)
#define ISO7816_STAT_IRQ_DMA_ERR                            ISO7816_STAT_IRQ_DMA_ERR_Msk

#define ISO7816_STAT_IRQ_STAT_ERR_POS                       (24U)
#define ISO7816_STAT_IRQ_STAT_ERR_Len                       (1U)
#define ISO7816_STAT_IRQ_STAT_ERR_Msk                       (0x1UL << ISO7816_STAT_IRQ_STAT_ERR_POS)
#define ISO7816_STAT_IRQ_STAT_ERR                           ISO7816_STAT_IRQ_STAT_ERR_Msk

#define ISO7816_STAT_IRQ_PRESENCE_POS                       (25U)
#define ISO7816_STAT_IRQ_PRESENCE_Len                       (1U)
#define ISO7816_STAT_IRQ_PRESENCE_Msk                       (0x1UL << ISO7816_STAT_IRQ_PRESENCE_POS)
#define ISO7816_STAT_IRQ_PRESENCE                           ISO7816_STAT_IRQ_PRESENCE_Msk

#define ISO7816_STAT_IRQ_TEST_POS                           (30U)
#define ISO7816_STAT_IRQ_TEST_Len                           (1U)
#define ISO7816_STAT_IRQ_TEST_Msk                           (0x1UL << ISO7816_STAT_IRQ_TEST_POS)
#define ISO7816_STAT_IRQ_TEST                               ISO7816_STAT_IRQ_TEST_Msk

/*******************  Bit definition for ISO7816_CLK_CFG register  *******************/
#define ISO7816_CLK_CFG_ETU_DIV_POS                         (0U)
#define ISO7816_CLK_CFG_ETU_DIV_Len                         (10U)
#define ISO7816_CLK_CFG_ETU_DIV_Msk                         (0x3FFUL << ISO7816_CLK_CFG_ETU_DIV_POS)
#define ISO7816_CLK_CFG_ETU_DIV                             ISO7816_CLK_CFG_ETU_DIV_Msk

#define ISO7816_CLK_CFG_CLK_DIV_POS                         (16U)
#define ISO7816_CLK_CFG_CLK_DIV_Len                         (8U)
#define ISO7816_CLK_CFG_CLK_DIV_Msk                         (0xFFUL << ISO7816_CLK_CFG_CLK_DIV_POS)
#define ISO7816_CLK_CFG_CLK_DIV                             ISO7816_CLK_CFG_CLK_DIV_Msk

#define ISO7816_CLK_CFG_CLK_STOP_SEL_POS                    (31U)
#define ISO7816_CLK_CFG_CLK_STOP_SEL_Len                    (1U)
#define ISO7816_CLK_CFG_CLK_STOP_SEL_Msk                    (0x1UL << ISO7816_CLK_CFG_CLK_STOP_SEL_POS)
#define ISO7816_CLK_CFG_CLK_STOP_SEL                        ISO7816_CLK_CFG_CLK_STOP_SEL_Msk

/*******************  Bit definition for ISO7816_TIMES_CFG register  *******************/
#define ISO7816_TIMES_CFG_GUARD_TIME_POS                    (0U)
#define ISO7816_TIMES_CFG_GUARD_TIME_Len                    (10U)
#define ISO7816_TIMES_CFG_GUARD_TIME_Msk                    (0x3FFUL << ISO7816_TIMES_CFG_GUARD_TIME_POS)
#define ISO7816_TIMES_CFG_GUARD_TIME                        ISO7816_TIMES_CFG_GUARD_TIME_Msk

#define ISO7816_TIMES_CFG_WAIT_TIME_POS                     (12U)
#define ISO7816_TIMES_CFG_WAIT_TIME_Len                     (18U)
#define ISO7816_TIMES_CFG_WAIT_TIME_Msk                     (0x3FFFFUL << ISO7816_TIMES_CFG_WAIT_TIME_POS)
#define ISO7816_TIMES_CFG_WAIT_TIME                         ISO7816_TIMES_CFG_WAIT_TIME_Msk

/*******************  Bit definition for ISO7816_DATA_CFG register  *******************/
#define ISO7816_DATA_CFG_CODING_POS                         (0U)
#define ISO7816_DATA_CFG_CODING_Len                         (1U)
#define ISO7816_DATA_CFG_CODING_Msk                         (0x1UL << ISO7816_DATA_CFG_CODING_POS)
#define ISO7816_DATA_CFG_CODING                             ISO7816_DATA_CFG_CODING_Msk

#define ISO7816_DATA_CFG_DETECT_CODING_POS                  (1U)
#define ISO7816_DATA_CFG_DETECT_CODING_Len                  (1U)
#define ISO7816_DATA_CFG_DETECT_CODING_Msk                  (0x1UL << ISO7816_DATA_CFG_DETECT_CODING_POS)
#define ISO7816_DATA_CFG_DETECT_CODING                      ISO7816_DATA_CFG_DETECT_CODING_Msk

#define ISO7816_DATA_CFG_RETRY_LIMIT_POS                    (4U)
#define ISO7816_DATA_CFG_RETRY_LIMIT_Len                    (3U)
#define ISO7816_DATA_CFG_RETRY_LIMIT_Msk                    (0x7UL << ISO7816_DATA_CFG_RETRY_LIMIT_POS)
#define ISO7816_DATA_CFG_RETRY_LIMIT                        ISO7816_DATA_CFG_RETRY_LIMIT_Msk

/*******************  Bit definition for ISO7816_ADDR register  *******************/
#define ISO7816_ADDR_ADDR_FRAC_POS                          (0U)
#define ISO7816_ADDR_ADDR_FRAC_Len                          (2U)
#define ISO7816_ADDR_ADDR_FRAC_Msk                          (0x3UL << ISO7816_ADDR_ADDR_FRAC_POS)
#define ISO7816_ADDR_ADDR_FRAC                              ISO7816_ADDR_ADDR_FRAC_Msk

#define ISO7816_ADDR_ADDR_POS                               (2U)
#define ISO7816_ADDR_ADDR_Len                               (18U)
#define ISO7816_ADDR_ADDR_Msk                               (0x3FFFFUL << ISO7816_ADDR_ADDR_POS)
#define ISO7816_ADDR_ADDR                                   ISO7816_ADDR_ADDR_Msk

/*******************  Bit definition for ISO7816_START_ADDR register  *******************/
#define ISO7816_START_ADDR_START_ADDR_POS                   (2U)
#define ISO7816_START_ADDR_START_ADDR_Len                   (18U)
#define ISO7816_START_ADDR_START_ADDR_Msk                   (0x3FFFFUL << ISO7816_START_ADDR_START_ADDR_POS)
#define ISO7816_START_ADDR_START_ADDR                       ISO7816_START_ADDR_START_ADDR_Msk

#define ISO7816_START_ADDR_BASE_ADDR_POS                    (20U)
#define ISO7816_START_ADDR_BASE_ADDR_Len                    (12U)
#define ISO7816_START_ADDR_BASE_ADDR_Msk                    (0xFFFUL << ISO7816_START_ADDR_BASE_ADDR_POS)
#define ISO7816_START_ADDR_BASE_ADDR                        ISO7816_START_ADDR_BASE_ADDR_Msk

/*******************  Bit definition for ISO7816_RX_END_ADDR register  *******************/
#define ISO7816_RX_END_ADDR_RX_END_AF_POS                   (0U)
#define ISO7816_RX_END_ADDR_RX_END_AF_Len                   (2U)
#define ISO7816_RX_END_ADDR_RX_END_AF_Msk                   (0x3UL << ISO7816_RX_END_ADDR_RX_END_AF_POS)
#define ISO7816_RX_END_ADDR_RX_END_AF                       ISO7816_RX_END_ADDR_RX_END_AF_Msk

#define ISO7816_RX_END_ADDR_RX_END_ADDR_POS                 (2U)
#define ISO7816_RX_END_ADDR_RX_END_ADDR_Len                 (18U)
#define ISO7816_RX_END_ADDR_RX_END_ADDR_Msk                 (0x3FFFFUL << ISO7816_RX_END_ADDR_RX_END_ADDR_POS)
#define ISO7816_RX_END_ADDR_RX_END_ADDR                     ISO7816_RX_END_ADDR_RX_END_ADDR_Msk

/*******************  Bit definition for ISO7816_TX_END_ADDR register  *******************/
#define ISO7816_TX_END_ADDR_TX_END_AF_POS                   (0U)
#define ISO7816_TX_END_ADDR_TX_END_AF_Len                   (2U)
#define ISO7816_TX_END_ADDR_TX_END_AF_Msk                   (0x3UL << ISO7816_TX_END_ADDR_TX_END_AF_POS)
#define ISO7816_TX_END_ADDR_TX_END_AF                       ISO7816_TX_END_ADDR_TX_END_AF_Msk

#define ISO7816_TX_END_ADDR_TX_END_ADDR_POS                 (2U)
#define ISO7816_TX_END_ADDR_TX_END_ADDR_Len                 (18U)
#define ISO7816_TX_END_ADDR_TX_END_ADDR_Msk                 (0x3FFFFUL << ISO7816_TX_END_ADDR_TX_END_ADDR_POS)
#define ISO7816_TX_END_ADDR_TX_END_ADDR                     ISO7816_TX_END_ADDR_TX_END_ADDR_Msk

/* ================================================================================================================= */
/* ================                                      MCU_SUB                                    ================ */
/* ================================================================================================================= */
/*******************  Bit definition for SENSE_ADC_FIFO register  ********************/
#define MCU_SUB_SNSADC_FF_DATA_Pos                          (0U)
#define MCU_SUB_SNSADC_FF_DATA_Len                          (32U)
#define MCU_SUB_SNSADC_FF_DATA_Msk                          (0xFFFFFFFFU)
#define MCU_SUB_SNSADC_FF_DATA                              MCU_SUB_SNSADC_FF_DATA_Msk

/*******************  Bit definition for SENSE_FF_THRESH register  ********************/
#define MCU_SUB_SNSADC_FF_THRESH_Pos                        (0U)
#define MCU_SUB_SNSADC_FF_THRESH_Len                        (6U)
#define MCU_SUB_SNSADC_FF_THRESH_Msk                        (0x3FU << MCU_SUB_SNSADC_FF_THRESH_Pos)
#define MCU_SUB_SNSADC_FF_THRESH                            MCU_SUB_SNSADC_FF_THRESH_Msk

#define MCU_SUB_SNSADC_FF_DMA_EN_Pos                        (16U)
#define MCU_SUB_SNSADC_FF_DMA_EN_Len                        (1U)
#define MCU_SUB_SNSADC_FF_DMA_EN_Msk                        (0x1UL << MCU_SUB_SNSADC_FF_DMA_EN_Pos)
#define MCU_SUB_SNSADC_FF_DMA_EN                            MCU_SUB_SNSADC_FF_DMA_EN_Msk

/*******************  Bit definition for SENSE_ADC_STAT register  *****/
#define MCU_SUB_SNSADC_STAT_FLUSH_Pos                       (16U)
#define MCU_SUB_SNSADC_STAT_FLUSH_Len                       (1U)
#define MCU_SUB_SNSADC_STAT_FLUSH_Msk                       (0x1U << MCU_SUB_SNSADC_STAT_FLUSH_Pos)
#define MCU_SUB_SNSADC_STAT_FLUSH                            MCU_SUB_SNSADC_STAT_FLUSH_Msk

#define MCU_SUB_SNSADC_STAT_VAL_Pos                         (8U)
#define MCU_SUB_SNSADC_STAT_VAL_Len                         (1U)
#define MCU_SUB_SNSADC_STAT_VAL_Msk                         (0x1U << MCU_SUB_SNSADC_STAT_VAL_Pos)
#define MCU_SUB_SNSADC_STAT_VAL                             MCU_SUB_SNSADC_STAT_VAL_Msk

#define MCU_SUB_SNSADC_STAT_FF_COUNT_Pos                    (0U)
#define MCU_SUB_SNSADC_STAT_FF_COUNT_Len                    (7U)
#define MCU_SUB_SNSADC_STAT_FF_COUNT_Msk                    (0x7FU << MCU_SUB_SNSADC_STAT_FF_COUNT_Pos)
#define MCU_SUB_SNSADC_STAT_FF_COUNT                        MCU_SUB_SNSADC_STAT_FF_COUNT_Msk

/*******************  Bit definition for SENSE_ADC_CLK register  *****/
#define MCU_SUB_SNSADC_CLK_RD_Pos                           (16U)
#define MCU_SUB_SNSADC_CLK_RD_Len                           (3U)
#define MCU_SUB_SNSADC_CLK_RD_Msk                           (0x7U << MCU_SUB_SNSADC_CLK_RD_Pos)
#define MCU_SUB_SNSADC_CLK_RD                               MCU_SUB_SNSADC_CLK_RD_Msk

#define MCU_SUB_SNSADC_CLK_WR_Pos                           (0U)
#define MCU_SUB_SNSADC_CLK_WR_Len                           (3U)
#define MCU_SUB_SNSADC_CLK_WR_Msk                           (0x7U << MCU_SUB_SNSADC_CLK_WR_Pos)
#define MCU_SUB_SNSADC_CLK_WR                               MCU_SUB_SNSADC_CLK_WR_Msk
#define MCU_SUB_SNSADC_CLK_NONE                             (0x0U << MCU_SUB_SNSADC_CLK_WR_Pos)
#define MCU_SUB_SNSADC_CLK_16K                              (0x1U << MCU_SUB_SNSADC_CLK_WR_Pos)
#define MCU_SUB_SNSADC_CLK_8K                               (0x2U << MCU_SUB_SNSADC_CLK_WR_Pos)
#define MCU_SUB_SNSADC_CLK_1K                               (0x3U << MCU_SUB_SNSADC_CLK_WR_Pos)
#define MCU_SUB_SNSADC_CLK_16M                              (0x4U << MCU_SUB_SNSADC_CLK_WR_Pos)
#define MCU_SUB_SNSADC_CLK_8M                               (0x5U << MCU_SUB_SNSADC_CLK_WR_Pos)
#define MCU_SUB_SNSADC_CLK_1M                               (0x6U << MCU_SUB_SNSADC_CLK_WR_Pos)
#define MCU_SUB_SNSADC_CLK_250K                             (0x7U << MCU_SUB_SNSADC_CLK_WR_Pos)

/*******************  Bit definition for SADC_GET_TKN_HW register  *******************/
#define MCU_SUB_SNSADC_GET_TKN_HW_LOCKED_POS                (0U)
#define MCU_SUB_SNSADC_GET_TKN_HW_LOCKED_Len                (1U)
#define MCU_SUB_SNSADC_GET_TKN_HW_LOCKED_Msk                ((0x1UL) << MCU_SUB_SNSADC_GET_TKN_HW_LOCKED_POS)
#define MCU_SUB_SNSADC_GET_TKN_HW_LOCKED                    MCU_SUB_SNSADC_GET_TKN_HW_LOCKED_Msk

/*******************  Bit definition for SADC_GET_TKN_SW register  *******************/
#define MCU_SUB_SNSADC_GET_TKN_SW_LOCKED_POS                (0U)
#define MCU_SUB_SNSADC_GET_TKN_SW_LOCKED_Len                (1U)
#define MCU_SUB_SNSADC_GET_TKN_SW_LOCKED_Msk                ((0x1UL) << MCU_SUB_SNSADC_GET_TKN_SW_LOCKED_POS)
#define MCU_SUB_SNSADC_GET_TKN_SW_LOCKED                    MCU_SUB_SNSADC_GET_TKN_SW_LOCKED_Msk

#define MCU_SUB_SNSADC_GET_TKN_SW_OWNER_POS                 (8U)
#define MCU_SUB_SNSADC_GET_TKN_SW_OWNER_Len                 (1U)
#define MCU_SUB_SNSADC_GET_TKN_SW_OWNER_Msk                 ((0x1UL) << MCU_SUB_SNSADC_GET_TKN_SW_OWNER_POS)
#define MCU_SUB_SNSADC_GET_TKN_SW_OWNER                     MCU_SUB_SNSADC_GET_TKN_SW_OWNER_Msk

#define MCU_SUB_SNSADC_TKN_LOCKED_SW                        (0x00000101UL)
#define MCU_SUB_SNSADC_TKN_LOCKED_HW                        (0x00000001UL)

/*******************  Bit definition for SADC_RET_TKN_HW register  *******************/
#define MCU_SUB_SNSADC_RET_TKN_HW_RELEASE_POS               (0U)
#define MCU_SUB_SNSADC_RET_TKN_HW_RELEASE_Len               (1U)
#define MCU_SUB_SNSADC_RET_TKN_HW_RELEASE_Msk               ((0x1UL) << MCU_SUB_SNSADC_RET_TKN_HW_RELEASE_POS)
#define MCU_SUB_SNSADC_RET_TKN_HW_RELEASE                   MCU_SUB_SNSADC_RET_TKN_HW_RELEASE_Msk

/*******************  Bit definition for SADC_RET_TKN_SW register  *******************/
#define MCU_SUB_SNSADC_RET_TKN_SW_RELEASE_POS               (0U)
#define MCU_SUB_SNSADC_RET_TKN_SW_RELEASE_Len               (1U)
#define MCU_SUB_SNSADC_RET_TKN_SW_RELEASE_Msk               ((0x1UL) << MCU_SUB_SNSADC_RET_TKN_SW_RELEASE_POS)
#define MCU_SUB_SNSADC_RET_TKN_SW_RELEASE                   MCU_SUB_SNSADC_RET_TKN_SW_RELEASE_Msk

/*******************  Bit definition for SADC_TKN_STAT register  *******************/
#define MCU_SUB_SNSADC_TKN_STAT_LOCKED_POS                  (0U)
#define MCU_SUB_SNSADC_TKN_STAT_LOCKED_Len                  (1U)
#define MCU_SUB_SNSADC_TKN_STAT_LOCKED_Msk                  ((0x1UL) << MCU_SUB_SNSADC_TKN_STAT_LOCKED_POS)
#define MCU_SUB_SNSADC_TKN_STAT_LOCKED                      MCU_SUB_SNSADC_TKN_STAT_LOCKED_Msk

#define MCU_SUB_SNSADC_TKN_STAT_OWNER_POS                   (8U)
#define MCU_SUB_SNSADC_TKN_STAT_OWNER_Len                   (1U)
#define MCU_SUB_SNSADC_TKN_STAT_OWNER_Msk                   ((0x1UL) << MCU_SUB_SNSADC_TKN_STAT_OWNER_POS)
#define MCU_SUB_SNSADC_TKN_STAT_OWNER                       MCU_SUB_SNSADC_TKN_STAT_OWNER_Msk

/***************  Bit definition for BLE_FERP_CTL register  ********/
#define MUC_SUB_BLE_FERP_CTL_TESTBUS_SEL_Pos                (4U)
#define MUC_SUB_BLE_FERP_CTL_TESTBUS_SEL_Len                (3U)
#define MUC_SUB_BLE_FERP_CTL_TESTBUS_SEL_Msk                (0x7U << MUC_SUB_BLE_FERP_CTL_TESTBUS_SEL_Pos)
#define MUC_SUB_BLE_FERP_CTL_TESTBUS_SEL                    MUC_SUB_BLE_FERP_CTL_TESTBUS_SEL_Msk

#define MCU_SUB_BLE_FERP_CTL_FERP_EN_Pos                    (0U)
#define MCU_SUB_BLE_FERP_CTL_FERP_EN_Len                    (1U)
#define MCU_SUB_BLE_FERP_CTL_FERP_EN_Msk                    (0x1U << MCU_SUB_BLE_FERP_CTL_FERP_EN_Pos)
#define MCU_SUB_BLE_FERP_CTL_FERP_EN                        MCU_SUB_BLE_FERP_CTL_FERP_EN_Msk

/***************  Bit definition for SECURITY_RESET register  ********/
#define MCU_SUB_SECURITY_RESET_TRNG_Pos                     (5U)
#define MCU_SUB_SECURITY_RESET_TRNG_Len                     (1U)
#define MCU_SUB_SECURITY_RESET_TRNG_Msk                     (0x1U << MCU_SUB_SECURITY_RESET_TRNG_Pos)
#define MCU_SUB_SECURITY_RESET_TRNG                         MCU_SUB_SECURITY_RESET_TRNG_Msk

#define MCU_SUB_SECURITY_RESET_EFUSE_Pos                    (3U)
#define MCU_SUB_SECURITY_RESET_EFUSE_Len                    (1U)
#define MCU_SUB_SECURITY_RESET_EFUSE_Msk                    (0x1U << MCU_SUB_SECURITY_RESET_EFUSE_Pos)
#define MCU_SUB_SECURITY_RESET_EFUSE                        MCU_SUB_SECURITY_RESET_EFUSE_Msk

/***************  Bit definition for PMU_ID register  ********/
#define MCU_SUB_PMU_ID_Pos                                  (0U)
#define MCU_SUB_PMU_ID_Len                                  (8U)
#define MCU_SUB_PMU_ID_Msk                                  (0xFFU << MCU_SUB_PMU_ID_Pos)
#define MCU_SUB_PMU_ID                                      MCU_SUB_PMU_ID_Msk

/***************  Bit definition for PWR_AVG_CTL_REG0 register  ********/
#define MCU_SUB_PWR_AVG_CTL0_TPA_ADC_OUT_Pos                (24U)
#define MCU_SUB_PWR_AVG_CTL0_TPA_ADC_OUT_Len                (8U)
#define MCU_SUB_PWR_AVG_CTL0_TPA_ADC_OUT_Msk                (0xFFU << MCU_SUB_PWR_AVG_CTL0_TPA_ADC_OUT_Pos)
#define MCU_SUB_PWR_AVG_CTL0_TPA_ADC_OUT                    MCU_SUB_PWR_AVG_CTL0_TPA_ADC_OUT_Msk

#define MCU_SUB_PWR_AVG_CTL0_AVG_PWR_ERR_Pos                (18U)
#define MCU_SUB_PWR_AVG_CTL0_AVG_PWR_ERR_Len                (1U)
#define MCU_SUB_PWR_AVG_CTL0_AVG_PWR_ERR_Msk                (0x1U << MCU_SUB_PWR_AVG_CTL0_AVG_PWR_ERR_Pos)
#define MCU_SUB_PWR_AVG_CTL0_AVG_PWR_ERR                    MCU_SUB_PWR_AVG_CTL0_AVG_PWR_ERR_Msk

#define MCU_SUB_PWR_AVG_CTL0_AVG_PWR_RDY_Pos                (16U)
#define MCU_SUB_PWR_AVG_CTL0_AVG_PWR_RDY_Len                (1U)
#define MCU_SUB_PWR_AVG_CTL0_AVG_PWR_RDY_Msk                (0x1U << MCU_SUB_PWR_AVG_CTL0_AVG_PWR_RDY_Pos)
#define MCU_SUB_PWR_AVG_CTL0_AVG_PWR_RDY                    MCU_SUB_PWR_AVG_CTL0_AVG_PWR_RDY_Msk

#define MCU_SUB_PWR_AVG_CTL0_AVG_PWR_Pos                    (8U)
#define MCU_SUB_PWR_AVG_CTL0_AVG_PWR_Len                    (8U)
#define MCU_SUB_PWR_AVG_CTL0_AVG_PWR_Msk                    (0xFFU << MCU_SUB_PWR_AVG_CTL0_AVG_PWR_Pos)
#define MCU_SUB_PWR_AVG_CTL0_AVG_PWR                        MCU_SUB_PWR_AVG_CTL0_AVG_PWR_Msk

#define MCU_SUB_PWR_AVG_CTL0_SAMPL_PWR_Pos                  (4U)
#define MCU_SUB_PWR_AVG_CTL0_SAMPL_PWR_Len                  (4U)
#define MCU_SUB_PWR_AVG_CTL0_SAMPL_PWR_Msk                  (0xFU << MCU_SUB_PWR_AVG_CTL0_SAMPL_PWR_Pos)
#define MCU_SUB_PWR_AVG_CTL0_SAMPL_PWR                      MCU_SUB_PWR_AVG_CTL0_SAMPL_PWR_Msk

#define MCU_SUB_PWR_AVG_CTL0_BLE_F_TX_EN_Pos                (3U)
#define MCU_SUB_PWR_AVG_CTL0_BLE_F_TX_EN_Len                (1U)
#define MCU_SUB_PWR_AVG_CTL0_BLE_F_TX_EN_Msk                (0x1 << MCU_SUB_PWR_AVG_CTL0_BLE_F_TX_EN_Pos)
#define MCU_SUB_PWR_AVG_CTL0_BLE_F_TX_EN                    MCU_SUB_PWR_AVG_CTL0_BLE_F_TX_EN_Msk

#define MCU_SUB_PWR_AVG_CTL0_ONESHOT_EN_Pos                 (2U)
#define MCU_SUB_PWR_AVG_CTL0_ONESHOT_EN_Len                 (1U)
#define MCU_SUB_PWR_AVG_CTL0_ONESHOT_EN_Msk                 (0x1 << MCU_SUB_PWR_AVG_CTL0_ONESHOT_EN_Pos)
#define MCU_SUB_PWR_AVG_CTL0_ONESHOT_EN                     MCU_SUB_PWR_AVG_CTL0_ONESHOT_EN_Msk

#define MCU_SUB_PWR_AVG_CTL0_PWR_AVG_EN_Pos                 (0U)
#define MCU_SUB_PWR_AVG_CTL0_PWR_AVG_EN_Len                 (1U)
#define MCU_SUB_PWR_AVG_CTL0_PWR_AVG_EN_Msk                 (0x1 << MCU_SUB_PWR_AVG_CTL0_PWR_AVG_EN_Pos)
#define MCU_SUB_PWR_AVG_CTL0_PWR_AVG_EN                     MCU_SUB_PWR_AVG_CTL0_PWR_AVG_EN_Msk

/***************  Bit definition for TIMER2BLE_PLUSE_CTRL register  ********/
#define MCU_SUB_TIMER2BLE_PLUSE_CTRL_Pos                    (0U)
#define MCU_SUB_TIMER2BLE_PLUSE_CTRL_Len                    (2U)
#define MCU_SUB_TIMER2BLE_PLUSE_CTRL_Msk                    (0x3U << MCU_SUB_TIMER2BLE_PLUSE_CTRL_Pos)
#define MCU_SUB_TIMER2BLE_PLUSE_CTRL                        MCU_SUB_TIMER2BLE_PLUSE_CTRL_Msk
#define MCU_SUB_TIMER2BLE_PLUSE_CTRL_TIMER0                 (0x0U << MCU_SUB_TIMER2BLE_PLUSE_CTRL_Pos)
#define MCU_SUB_TIMER2BLE_PLUSE_CTRL_TIMER1                 (0x1U << MCU_SUB_TIMER2BLE_PLUSE_CTRL_Pos)
#define MCU_SUB_TIMER2BLE_PLUSE_CTRL_DUALTIMER0             (0x2U << MCU_SUB_TIMER2BLE_PLUSE_CTRL_Pos)
#define MCU_SUB_TIMER2BLE_PLUSE_CTRL_DUALTIMER1             (0x3U << MCU_SUB_TIMER2BLE_PLUSE_CTRL_Pos)

/***************  Bit definition for EFUSE_PWR_DELTA_0 register  ********/
#define MCU_SUB_EFUSE_PWR_DELTA1_Pos                        (16U)
#define MCU_SUB_EFUSE_PWR_DELTA1_Len                        (16U)
#define MCU_SUB_EFUSE_PWR_DELTA1_Msk                        (0xFFFFU << MCU_SUB_EFUSE_PWR_DELTA1_Pos)
#define MCU_SUB_EFUSE_PWR_DELTA1                            MCU_SUB_EFUSE_PWR_DELTA1_Msk

#define MCU_SUB_EFUSE_PWR_DELTA0_Pos                        (0U)
#define MCU_SUB_EFUSE_PWR_DELTA0_Len                        (16U)
#define MCU_SUB_EFUSE_PWR_DELTA0_Msk                        (0xFFFFU << MCU_SUB_EFUSE_PWR_DELTA0_Pos)
#define MCU_SUB_EFUSE_PWR_DELTA0                            MCU_SUB_EFUSE_PWR_DELTA0_Msk

/***************  Bit definition for EFUSE_PWR_DELTA_1 register  ********/
#define MCU_SUB_EFUSE_PWR_DELTA2_Pos                        (0U)
#define MCU_SUB_EFUSE_PWR_DELTA2_Len                        (16U)
#define MCU_SUB_EFUSE_PWR_DELTA2_Msk                        (0xFFFFU << MCU_SUB_EFUSE_PWR_DELTA2_Pos)
#define MCU_SUB_EFUSE_PWR_DELTA2                            MCU_SUB_EFUSE_PWR_DELTA2_Msk

/***************  Bit definition for EFUSE_PWR_CTRL_0 register  ********/
#define MCU_SUB_EFUSE_PWR_CTL0_STP_Pos                      (4U)
#define MCU_SUB_EFUSE_PWR_CTL0_STP_Len                      (1U)
#define MCU_SUB_EFUSE_PWR_CTL0_STP_Msk                      (0x1U << MCU_SUB_EFUSE_PWR_CTL0_STP_Pos)
#define MCU_SUB_EFUSE_PWR_CTL0_STP                          MCU_SUB_EFUSE_PWR_CTL0_STP_Msk

#define MCU_SUB_EFUSE_PWR_CTL0_BGN_Pos                      (2U)
#define MCU_SUB_EFUSE_PWR_CTL0_BGN_Len                      (1U)
#define MCU_SUB_EFUSE_PWR_CTL0_BGN_Msk                      (0x1U << MCU_SUB_EFUSE_PWR_CTL0_BGN_Pos)
#define MCU_SUB_EFUSE_PWR_CTL0_BGN                          MCU_SUB_EFUSE_PWR_CTL0_BGN_Msk

#define MCU_SUB_EFUSE_PWR_CTL0_EN_Pos                       (0U)
#define MCU_SUB_EFUSE_PWR_CTL0_EN_Len                       (1U)
#define MCU_SUB_EFUSE_PWR_CTL0_EN_Msk                       (0x1U << MCU_SUB_EFUSE_PWR_CTL0_EN_Pos)
#define MCU_SUB_EFUSE_PWR_CTL0_EN                           MCU_SUB_EFUSE_PWR_CTL0_EN_Msk

/***************  Bit definition for EFUSE_PWR_CTRL_1 register  ********/
#define MCU_SUB_EFUSE_PWR_CTL0_DIS_DONE_Pos                 (4U)
#define MCU_SUB_EFUSE_PWR_CTL0_DIS_DONE_Len                 (1U)
#define MCU_SUB_EFUSE_PWR_CTL0_DIS_DONE_Msk                 (0x1U << MCU_SUB_EFUSE_PWR_CTL0_DIS_DONE_Pos)
#define MCU_SUB_EFUSE_PWR_CTL0_DIS_DONE                     MCU_SUB_EFUSE_PWR_CTL0_DIS_DONE_Msk

#define MCU_SUB_EFUSE_PWR_CTL0_EN_DONE_Pos                  (0U)
#define MCU_SUB_EFUSE_PWR_CTL0_EN_DONE_Len                  (1U)
#define MCU_SUB_EFUSE_PWR_CTL0_EN_DONE_Msk                  (0x1U << MCU_SUB_EFUSE_PWR_CTL0_EN_DONE_Pos)
#define MCU_SUB_EFUSE_PWR_CTL0_EN_DONE                      MCU_SUB_EFUSE_PWR_CTL0_EN_DONE_Msk

/***************  Bit definition for MCU_SUB_REG0 register  ********/
#define MCU_SUB_MCU_SUB_REG0_GDX_REG_WAIT_STATE_Pos         (12U)
#define MCU_SUB_MCU_SUB_REG0_GDX_REG_WAIT_STATE_Len         (2U)
#define MCU_SUB_MCU_SUB_REG0_GDX_REG_WAIT_STATE_Msk         (0x3U << MCU_SUB_MCU_SUB_REG0_GDX_REG_WAIT_STATE_Pos)
#define MCU_SUB_MCU_SUB_REG0_GDX_REG_WAIT_STATE             MCU_SUB_MCU_SUB_REG0_GDX_REG_WAIT_STATE_Msk

#define MCU_SUB_MCU_SUB_REG0_MEM_BOND_OPT_Pos               (4U)
#define MCU_SUB_MCU_SUB_REG0_MEM_BOND_OPT_Len               (2U)
#define MCU_SUB_MCU_SUB_REG0_MEM_BOND_OPT_Msk               (0x3U << MCU_SUB_MCU_SUB_REG0_MEM_BOND_OPT_Pos)
#define MCU_SUB_MCU_SUB_REG0_MEM_BOND_OPT                    MCU_SUB_MCU_SUB_REG0_MEM_BOND_OPT_Msk
#define MCU_SUB_MCU_SUB_REG0_MEM_BOND_OPT_64K               (0x00 << MCU_SUB_MCU_SUB_REG0_MEM_BOND_OPT_Pos)
#define MCU_SUB_MCU_SUB_REG0_MEM_BOND_OPT_128K              (0x01 << MCU_SUB_MCU_SUB_REG0_MEM_BOND_OPT_Pos)
#define MCU_SUB_MCU_SUB_REG0_MEM_BOND_OPT_256K              (0x03 << MCU_SUB_MCU_SUB_REG0_MEM_BOND_OPT_Pos)

/*******************  Bit definition for MCU_SUB_MCU_NMI_CFG register  *******************/
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Pos                 (0U)
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Len                 (10U)
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Msk                 (0x3FFUL << MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Pos)
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL                     MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Msk
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_IRQNUM6             (0x00 << MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Pos)
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_IRQNUM7             (0x01 << MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Pos)
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_IRQNUM2             (0x02 << MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Pos)
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_IRQNUM20            (0x04 << MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Pos)
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_IRQNUM25            (0x08 << MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Pos)
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_IRQNUM28            (0x10 << MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Pos)
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_IRQNUM48            (0x20 << MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Pos)
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_IRQNUM8             (0x40 << MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Pos)
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_IRQNUM56            (0x80 << MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Pos)
#define MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_IRQNUM57            (0x100 << MCU_SUB_MCU_NMI_CFG_MCU_NMI_SEL_Pos)

/*******************  Bit definition for MCU_SUB_CPLL_IRQ_CFG register  *******************/
#define MCU_SUB_CPLL_IRQ_CFG_DRIFT_IRQ_EN_Pos               (0U)
#define MCU_SUB_CPLL_IRQ_CFG_DRIFT_IRQ_EN_Len               (1U)
#define MCU_SUB_CPLL_IRQ_CFG_DRIFT_IRQ_EN_Msk               (0x1UL << MCU_SUB_CPLL_IRQ_CFG_DRIFT_IRQ_EN_Pos)
#define MCU_SUB_CPLL_IRQ_CFG_DRIFT_IRQ_EN                   MCU_SUB_CPLL_IRQ_CFG_DRIFT_IRQ_EN_Msk

/*******************  Bit definition for MCU_SUB_AON_SW_RST register  *******************/
#define MCU_SUB_AON_SW_RST_PARTIAL_Pos                      (0U)
#define MCU_SUB_AON_SW_RST_PARTIAL_Len                      (1U)
#define MCU_SUB_AON_SW_RST_PARTIAL_Msk                      (0x1UL << MCU_SUB_AON_SW_RST_PARTIAL_Pos)
#define MCU_SUB_AON_SW_RST_PARTIAL                          MCU_SUB_AON_SW_RST_PARTIAL_Msk

#define MCU_SUB_AON_SW_RST_FULL_Pos                         (8U)
#define MCU_SUB_AON_SW_RST_FULL_Len                         (1U)
#define MCU_SUB_AON_SW_RST_FULL_Msk                         (0x1UL << MCU_SUB_AON_SW_RST_FULL_Pos)
#define MCU_SUB_AON_SW_RST_FULL                             MCU_SUB_AON_SW_RST_FULL_Msk

#define MCU_SUB_AON_SW_RST_SET_Pos                          (16U)
#define MCU_SUB_AON_SW_RST_SET_Len                          (16U)
#define MCU_SUB_AON_SW_RST_SET_Msk                          (0xFFFFUL << MCU_SUB_AON_SW_RST_SET_Pos)
#define MCU_SUB_AON_SW_RST_SET                              MCU_SUB_AON_SW_RST_SET_Msk

/***************  Bit definition for MCU_SUBSYS_CG_CTRL_0 register  ********/
#define MCU_SUB_WFI_SERIAL_HCLK_Pos                         (10U)
#define MCU_SUB_WFI_SERIAL_HCLK_Len                         (1U)
#define MCU_SUB_WFI_SERIAL_HCLK_Msk                         (0x01 << MCU_SUB_WFI_SERIAL_HCLK_Pos)
#define MCU_SUB_WFI_SERIAL_HCLK                             MCU_SUB_WFI_SERIAL_HCLK_Msk

#define MCU_SUB_WFI_APB_SUB_HCLK_Pos                        (9U)
#define MCU_SUB_WFI_APB_SUB_HCLK_Len                        (1U)
#define MCU_SUB_WFI_APB_SUB_HCLK_Msk                        (0x01 << MCU_SUB_WFI_APB_SUB_HCLK_Pos)
#define MCU_SUB_WFI_APB_SUB_HCLK                            MCU_SUB_WFI_APB_SUB_HCLK_Msk

#define MCU_SUB_WFI_BLE_BRG_HCLK_Pos                        (8U)
#define MCU_SUB_WFI_BLE_BRG_HCLK_Len                        (1U)
#define MCU_SUB_WFI_BLE_BRG_HCLK_Msk                        (0x01 << MCU_SUB_WFI_BLE_BRG_HCLK_Pos)
#define MCU_SUB_WFI_BLE_BRG_HCLK                            MCU_SUB_WFI_BLE_BRG_HCLK_Msk

#define MCU_SUB_WFI_GPIO_HCLK_Pos                           (6U)
#define MCU_SUB_WFI_GPIO_HCLK_Len                           (1U)
#define MCU_SUB_WFI_GPIO_HCLK_Msk                           (0x01 << MCU_SUB_WFI_GPIO_HCLK_Pos)
#define MCU_SUB_WFI_GPIO_HCLK                               MCU_SUB_WFI_GPIO_HCLK_Msk

#define MCU_SUB_WFI_SNSADC_HCLK_Pos                         (5U)
#define MCU_SUB_WFI_SNSADC_HCLK_Len                         (1U)
#define MCU_SUB_WFI_SNSADC_HCLK_Msk                         (0x01 << MCU_SUB_WFI_SNSADC_HCLK_Pos)
#define MCU_SUB_WFI_SNSADC_HCLK                             MCU_SUB_WFI_SNSADC_HCLK_Msk

#define MCU_SUB_WFI_ROM_HCLK_Pos                            (4U)
#define MCU_SUB_WFI_ROM_HCLK_Len                            (1U)
#define MCU_SUB_WFI_ROM_HCLK_Msk                            (0x01 << MCU_SUB_WFI_ROM_HCLK_Pos)
#define MCU_SUB_WFI_ROM_HCLK                                MCU_SUB_WFI_ROM_HCLK_Msk

#define MCU_SUB_WFI_HTB_HCLK_Pos                            (2U)
#define MCU_SUB_WFI_HTB_HCLK_Len                            (1U)
#define MCU_SUB_WFI_HTB_HCLK_Msk                            (0x01 << MCU_SUB_WFI_HTB_HCLK_Pos)
#define MCU_SUB_WFI_HTB_HCLK                                MCU_SUB_WFI_HTB_HCLK_Msk

#define MCU_SUB_WFI_SECU_HCLK_Pos                           (0U)
#define MCU_SUB_WFI_SECU_HCLK_Len                           (1U)
#define MCU_SUB_WFI_SECU_HCLK_Msk                           (0x01 << MCU_SUB_WFI_SECU_HCLK_Pos)
#define MCU_SUB_WFI_SECU_HCLK                               MCU_SUB_WFI_SECU_HCLK_Msk

/***************  Bit definition for MCU_SUBSYS_CG_CTRL_1 register  ********/
#define MCU_SUB_FORCE_SERIAL_HCLK_Pos                       (10U)
#define MCU_SUB_FORCE_SERIAL_HCLK_Len                       (1U)
#define MCU_SUB_FORCE_SERIAL_HCLK_Msk                       (0x01 << MCU_SUB_FORCE_SERIAL_HCLK_Pos)
#define MCU_SUB_FORCE_SERIAL_HCLK                           MCU_SUB_FORCE_SERIAL_HCLK_Msk

#define MCU_SUB_FORCE_APB_SUB_HCLK_Pos                      (9U)
#define MCU_SUB_FORCE_APB_SUB_HCLK_Len                      (1U)
#define MCU_SUB_FORCE_APB_SUB_HCLK_Msk                      (0x01 << MCU_SUB_FORCE_APB_SUB_HCLK_Pos)
#define MCU_SUB_FORCE_APB_SUB_HCLK                          MCU_SUB_FORCE_APB_SUB_HCLK_Msk

#define MCU_SUB_FORCE_BLE_BRG_HCLK_Pos                      (8U)
#define MCU_SUB_FORCE_BLE_BRG_HCLK_Len                      (1U)
#define MCU_SUB_FORCE_BLE_BRG_HCLK_Msk                      (0x01 << MCU_SUB_FORCE_BLE_BRG_HCLK_Pos)
#define MCU_SUB_FORCE_BLE_BRG_HCLK                          MCU_SUB_FORCE_BLE_BRG_HCLK_Msk

#define MCU_SUB_FORCE_GPIO_HCLK_Pos                         (6U)
#define MCU_SUB_FORCE_GPIO_HCLK_Len                         (1U)
#define MCU_SUB_FORCE_GPIO_HCLK_Msk                         (0x01 << MCU_SUB_FORCE_GPIO_HCLK_Pos)
#define MCU_SUB_FORCE_GPIO_HCLK                             MCU_SUB_FORCE_GPIO_HCLK_Msk

#define MCU_SUB_FORCE_SNSADC_HCLK_Pos                       (5U)
#define MCU_SUB_FORCE_SNSADC_HCLK_Len                       (1U)
#define MCU_SUB_FORCE_SNSADC_HCLK_Msk                       (0x01 << MCU_SUB_FORCE_SNSADC_HCLK_Pos)
#define MCU_SUB_FORCE_SNSADC_HCLK                           MCU_SUB_FORCE_SNSADC_HCLK_Msk

#define MCU_SUB_FORCE_ROM_HCLK_Pos                          (4U)
#define MCU_SUB_FORCE_ROM_HCLK_Len                          (1U)
#define MCU_SUB_FORCE_ROM_HCLK_Msk                          (0x01 << MCU_SUB_FORCE_ROM_HCLK_Pos)
#define MCU_SUB_FORCE_ROM_HCLK                              MCU_SUB_FORCE_ROM_HCLK_Msk

#define MCU_SUB_FORCE_HTB_HCLK_Pos                          (2U)
#define MCU_SUB_FORCE_HTB_HCLK_Len                          (1U)
#define MCU_SUB_FORCE_HTB_HCLK_Msk                          (0x01 << MCU_SUB_FORCE_HTB_HCLK_Pos)
#define MCU_SUB_FORCE_HTB_HCLK                              MCU_SUB_FORCE_HTB_HCLK_Msk

#define MCU_SUB_FORCE_SECU_HCLK_Pos                         (0U)
#define MCU_SUB_FORCE_SECU_HCLK_Len                         (1U)
#define MCU_SUB_FORCE_SECU_HCLK_Msk                         (0x01 << MCU_SUB_FORCE_SECU_HCLK_Pos)
#define MCU_SUB_FORCE_SECU_HCLK                             MCU_SUB_FORCE_SECU_HCLK_Msk

/***************  Bit definition for MCU_SUBSYS_CG_CTRL_2 register  ********/
#define MCU_SUB_FORCE_SRAM_HCLK_Pos                         (18U)
#define MCU_SUB_FORCE_SRAM_HCLK_Len                         (1U)
#define MCU_SUB_FORCE_SRAM_HCLK_Msk                         (0x1UL << MCU_SUB_FORCE_SRAM_HCLK_Pos)
#define MCU_SUB_FORCE_SRAM_HCLK                             MCU_SUB_FORCE_SRAM_HCLK_Msk

#define MCU_SUB_FORCE_XF_XQSPI_HCLK_Pos                     (17U)
#define MCU_SUB_FORCE_XF_XQSPI_HCLK_Len                     (1U)
#define MCU_SUB_FORCE_XF_XQSPI_HCLK_Msk                     (0x1UL << MCU_SUB_FORCE_XF_XQSPI_HCLK_Pos)
#define MCU_SUB_FORCE_XF_XQSPI_HCLK                         MCU_SUB_FORCE_XF_XQSPI_HCLK_Msk

#define MCU_SUB_WFI_SRAM_HCLK_Pos                           (2U)
#define MCU_SUB_WFI_SRAM_HCLK_Len                           (1U)
#define MCU_SUB_WFI_SRAM_HCLK_Msk                           (0x1UL << MCU_SUB_WFI_SRAM_HCLK_Pos)
#define MCU_SUB_WFI_SRAM_HCLK                               MCU_SUB_WFI_SRAM_HCLK_Msk

#define MCU_SUB_WFI_XF_XQSPI_HCLK_Pos                       (1U)
#define MCU_SUB_WFI_XF_XQSPI_HCLK_Len                       (1U)
#define MCU_SUB_WFI_XF_XQSPI_HCLK_Msk                       (0x1UL << MCU_SUB_WFI_XF_XQSPI_HCLK_Pos)
#define MCU_SUB_WFI_XF_XQSPI_HCLK                           MCU_SUB_WFI_XF_XQSPI_HCLK_Msk

#define MCU_SUB_WFI_AON_MCUSUB_HCLK_Pos                     (0U)
#define MCU_SUB_WFI_AON_MCUSUB_HCLK_Len                     (1U)
#define MCU_SUB_WFI_AON_MCUSUB_HCLK_Msk                     (0x1UL << MCU_SUB_WFI_AON_MCUSUB_HCLK_Pos)
#define MCU_SUB_WFI_AON_MCUSUB_HCLK                         MCU_SUB_WFI_AON_MCUSUB_HCLK_Msk

/***************  Bit definition for MCU_PERIPH_PCLK_OFF register  ********/
#define MCU_SUB_FORCE_PWM_1_PCLK_Pos                        (29U)
#define MCU_SUB_FORCE_PWM_1_PCLK_Len                        (1U)
#define MCU_SUB_FORCE_PWM_1_PCLK_Msk                        (0x1UL << MCU_SUB_FORCE_PWM_1_PCLK_Pos)
#define MCU_SUB_FORCE_PWM_1_PCLK                            MCU_SUB_FORCE_PWM_1_PCLK_Msk

#define MCU_SUB_FORCE_PWM_0_PCLK_Pos                        (28U)
#define MCU_SUB_FORCE_PWM_0_PCLK_Len                        (1U)
#define MCU_SUB_FORCE_PWM_0_PCLK_Msk                        (0x1UL << MCU_SUB_FORCE_PWM_0_PCLK_Pos)
#define MCU_SUB_FORCE_PWM_0_PCLK                            MCU_SUB_FORCE_PWM_0_PCLK_Msk

#define MCU_SUB_FORCE_SPI_S_PCLK_Pos                        (18U)
#define MCU_SUB_FORCE_SPI_S_PCLK_Len                        (1U)
#define MCU_SUB_FORCE_SPI_S_PCLK_Msk                        (0x1UL << MCU_SUB_FORCE_SPI_S_PCLK_Pos)
#define MCU_SUB_FORCE_SPI_S_PCLK                            MCU_SUB_FORCE_SPI_S_PCLK_Msk

#define MCU_SUB_FORCE_SPI_M_PCLK_Pos                        (17U)
#define MCU_SUB_FORCE_SPI_M_PCLK_Len                        (1U)
#define MCU_SUB_FORCE_SPI_M_PCLK_Msk                        (0x1UL << MCU_SUB_FORCE_SPI_M_PCLK_Pos)
#define MCU_SUB_FORCE_SPI_M_PCLK                            MCU_SUB_FORCE_SPI_M_PCLK_Msk

#define MCU_SUB_FORCE_I2C1_PCLK_Pos                         (13U)
#define MCU_SUB_FORCE_I2C1_PCLK_Len                         (1U)
#define MCU_SUB_FORCE_I2C1_PCLK_Msk                         (0x1UL << MCU_SUB_FORCE_I2C1_PCLK_Pos)
#define MCU_SUB_FORCE_I2C1_PCLK                             MCU_SUB_FORCE_I2C1_PCLK_Msk

#define MCU_SUB_FORCE_I2C0_PCLK_Pos                         (12U)
#define MCU_SUB_FORCE_I2C0_PCLK_Len                         (1U)
#define MCU_SUB_FORCE_I2C0_PCLK_Msk                         (0x1UL << MCU_SUB_FORCE_I2C0_PCLK_Pos)
#define MCU_SUB_FORCE_I2C0_PCLK                             MCU_SUB_FORCE_I2C0_PCLK_Msk

#define MCU_SUB_FORCE_UART1_PCLK_Pos                        (2U)
#define MCU_SUB_FORCE_UART1_PCLK_Len                        (1U)
#define MCU_SUB_FORCE_UART1_PCLK_Msk                        (0x1UL << MCU_SUB_FORCE_UART1_PCLK_Pos)
#define MCU_SUB_FORCE_UART1_PCLK                            MCU_SUB_FORCE_UART1_PCLK_Msk

#define MCU_SUB_FORCE_UART0_PCLK_Pos                        (0U)
#define MCU_SUB_FORCE_UART0_PCLK_Len                        (1U)
#define MCU_SUB_FORCE_UART0_PCLK_Msk                        (0x1UL << MCU_SUB_FORCE_UART0_PCLK_Pos)
#define MCU_SUB_FORCE_UART0_PCLK                            MCU_SUB_FORCE_UART0_PCLK_Msk

/***************  Bit definition for MCU_PERIPH_CG_LP_EN register  ********/
#define MCU_SUB_PERIPH_CG_LP_AHB2APB_ASYNC_EN_Pos           (11U)
#define MCU_SUB_PERIPH_CG_LP_AHB2APB_ASYNC_EN_Len           (1U)
#define MCU_SUB_PERIPH_CG_LP_AHB2APB_ASYNC_EN_Msk           (0x1UL << MCU_SUB_PERIPH_CG_LP_AHB2APB_ASYNC_EN_Pos)
#define MCU_SUB_PERIPH_CG_LP_AHB2APB_ASYNC_EN               MCU_SUB_PERIPH_CG_LP_AHB2APB_ASYNC_EN_Msk

#define MCU_SUB_PERIPH_CG_LP_AHB2APB_SYNC_EN_Pos            (10U)
#define MCU_SUB_PERIPH_CG_LP_AHB2APB_SYNC_EN_Len            (1U)
#define MCU_SUB_PERIPH_CG_LP_AHB2APB_SYNC_EN_Msk            (0x1UL << MCU_SUB_PERIPH_CG_LP_AHB2APB_SYNC_EN_Pos)
#define MCU_SUB_PERIPH_CG_LP_AHB2APB_SYNC_EN                MCU_SUB_PERIPH_CG_LP_AHB2APB_SYNC_EN_Msk

#define MCU_SUB_PERIPH_CG_LP_EN_AHB_BUS_LP_EN_Pos           (8U)
#define MCU_SUB_PERIPH_CG_LP_EN_AHB_BUS_LP_EN_Len           (1U)
#define MCU_SUB_PERIPH_CG_LP_EN_AHB_BUS_LP_EN_Msk           (0x1UL << MCU_SUB_PERIPH_CG_LP_EN_AHB_BUS_LP_EN_Pos)
#define MCU_SUB_PERIPH_CG_LP_EN_AHB_BUS_LP_EN               MCU_SUB_PERIPH_CG_LP_EN_AHB_BUS_LP_EN_Msk

#define MCU_SUB_PERIPH_CG_LP_EN_I2C_LP_SCLK_EN_Pos          (5U)
#define MCU_SUB_PERIPH_CG_LP_EN_I2C_LP_SCLK_EN_Len          (1U)
#define MCU_SUB_PERIPH_CG_LP_EN_I2C_LP_SCLK_EN_Msk          (0x1UL << MCU_SUB_PERIPH_CG_LP_EN_I2C_LP_SCLK_EN_Pos)
#define MCU_SUB_PERIPH_CG_LP_EN_I2C_LP_SCLK_EN              MCU_SUB_PERIPH_CG_LP_EN_I2C_LP_SCLK_EN_Msk

#define MCU_SUB_PERIPH_CG_LP_EN_SPIS_LP_SCLK_EN_Pos         (4U)
#define MCU_SUB_PERIPH_CG_LP_EN_SPIS_LP_SCLK_EN_Len         (1U)
#define MCU_SUB_PERIPH_CG_LP_EN_SPIS_LP_SCLK_EN_Msk         (0x1UL << MCU_SUB_PERIPH_CG_LP_EN_SPIS_LP_SCLK_EN_Pos)
#define MCU_SUB_PERIPH_CG_LP_EN_SPIS_LP_SCLK_EN             MCU_SUB_PERIPH_CG_LP_EN_SPIS_LP_SCLK_EN_Msk

#define MCU_SUB_PERIPH_CG_LP_EN_SPIM_LP_SCLK_EN_Pos         (3U)
#define MCU_SUB_PERIPH_CG_LP_EN_SPIM_LP_SCLK_EN_Len         (1U)
#define MCU_SUB_PERIPH_CG_LP_EN_SPIM_LP_SCLK_EN_Msk         (0x1UL << MCU_SUB_PERIPH_CG_LP_EN_SPIM_LP_SCLK_EN_Pos)
#define MCU_SUB_PERIPH_CG_LP_EN_SPIM_LP_SCLK_EN             MCU_SUB_PERIPH_CG_LP_EN_SPIM_LP_SCLK_EN_Msk

#define MCU_SUB_PERIPH_CG_LP_EN_UART_LP_PCLK_EN_Pos         (1U)
#define MCU_SUB_PERIPH_CG_LP_EN_UART_LP_PCLK_EN_Len         (1U)
#define MCU_SUB_PERIPH_CG_LP_EN_UART_LP_PCLK_EN_Msk         (0x1UL << MCU_SUB_PERIPH_CG_LP_EN_UART_LP_PCLK_EN_Pos)
#define MCU_SUB_PERIPH_CG_LP_EN_UART_LP_PCLK_EN             MCU_SUB_PERIPH_CG_LP_EN_UART_LP_PCLK_EN_Msk

#define MCU_SUB_PERIPH_CG_LP_EN_UART_LP_SCLK_EN_Pos         (0U)
#define MCU_SUB_PERIPH_CG_LP_EN_UART_LP_SCLK_EN_Len         (1U)
#define MCU_SUB_PERIPH_CG_LP_EN_UART_LP_SCLK_EN_Msk         (0x1UL << MCU_SUB_PERIPH_CG_LP_EN_UART_LP_SCLK_EN_Pos)
#define MCU_SUB_PERIPH_CG_LP_EN_UART_LP_SCLK_EN             MCU_SUB_PERIPH_CG_LP_EN_UART_LP_SCLK_EN_Msk

/***************  Bit definition for MCU_SUB_MCU_PERIPH_CLK_SLP_OFF register  *******************/
#define MCU_SUB_PERIPH_CLK_SLP_OFF_UART0_Pos                (0U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_UART0_Len                (1U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_UART0_Msk                (0x1UL << MCU_SUB_PERIPH_CLK_SLP_OFF_UART0_Pos)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_UART0                    MCU_SUB_PERIPH_CLK_SLP_OFF_UART0_Msk

#define MCU_SUB_PERIPH_CLK_SLP_OFF_UART1_Pos                (1U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_UART1_Len                (1U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_UART1_Msk                (0x1UL << MCU_SUB_PERIPH_CLK_SLP_OFF_UART1_Pos)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_UART1                    MCU_SUB_PERIPH_CLK_SLP_OFF_UART1_Msk

#define MCU_SUB_PERIPH_CLK_SLP_OFF_I2C0_Pos                 (6U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_I2C0_Len                 (1U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_I2C0_Msk                 (0x1UL << MCU_SUB_PERIPH_CLK_SLP_OFF_I2C0_Pos)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_I2C0                     MCU_SUB_PERIPH_CLK_SLP_OFF_I2C0_Msk

#define MCU_SUB_PERIPH_CLK_SLP_OFF_I2C1_Pos                 (7U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_I2C1_Len                 (1U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_I2C1_Msk                 (0x1UL << MCU_SUB_PERIPH_CLK_SLP_OFF_I2C1_Pos)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_I2C1                     MCU_SUB_PERIPH_CLK_SLP_OFF_I2C1_Msk

#define MCU_SUB_PERIPH_CLK_SLP_OFF_SPIM_Pos                 (10U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_SPIM_Len                 (1U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_SPIM_Msk                 (0x1UL << MCU_SUB_PERIPH_CLK_SLP_OFF_SPIM_Pos)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_SPIM                     MCU_SUB_PERIPH_CLK_SLP_OFF_SPIM_Msk

#define MCU_SUB_PERIPH_CLK_SLP_OFF_SPIS_Pos                 (11U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_SPIS_Len                 (1U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_SPIS_Msk                 (0x1UL << MCU_SUB_PERIPH_CLK_SLP_OFF_SPIS_Pos)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_SPIS                     MCU_SUB_PERIPH_CLK_SLP_OFF_SPIS_Msk

#define MCU_SUB_PERIPH_CLK_SLP_OFF_PWM0_Pos                 (12U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_PWM0_Len                 (1U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_PWM0_Msk                 (0x1UL << MCU_SUB_PERIPH_CLK_SLP_OFF_PWM0_Pos)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_PWM0                     MCU_SUB_PERIPH_CLK_SLP_OFF_PWM0_Msk

#define MCU_SUB_PERIPH_CLK_SLP_OFF_PWM1_Pos                 (13U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_PWM1_Len                 (1U)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_PWM1_Msk                 (0x1UL << MCU_SUB_PERIPH_CLK_SLP_OFF_PWM1_Pos)
#define MCU_SUB_PERIPH_CLK_SLP_OFF_PWM1                     MCU_SUB_PERIPH_CLK_SLP_OFF_PWM1_Msk

/*******************  Bit definition for MCU_SUB_SECU_CLK_CTRL register  *******************/
#define MCU_SUB_SECU_CLK_CTRL_RNG_HCLK_FORCE_OFF_Pos        (10U)
#define MCU_SUB_SECU_CLK_CTRL_RNG_HCLK_FORCE_OFF_Len        (1U)
#define MCU_SUB_SECU_CLK_CTRL_RNG_HCLK_FORCE_OFF_Msk        (0x1UL << MCU_SUB_SECU_CLK_CTRL_RNG_HCLK_FORCE_OFF_Pos)
#define MCU_SUB_SECU_CLK_CTRL_RNG_HCLK_FORCE_OFF            MCU_SUB_SECU_CLK_CTRL_RNG_HCLK_FORCE_OFF_Msk

#define MCU_SUB_SECU_CLK_CTRL_RNG_HCLK_SLP_OFF_Pos          (11U)
#define MCU_SUB_SECU_CLK_CTRL_RNG_HCLK_SLP_OFF_Len          (1U)
#define MCU_SUB_SECU_CLK_CTRL_RNG_HCLK_SLP_OFF_Msk          (0x1UL << MCU_SUB_SECU_CLK_CTRL_RNG_HCLK_SLP_OFF_Pos)
#define MCU_SUB_SECU_CLK_CTRL_RNG_HCLK_SLP_OFF              MCU_SUB_SECU_CLK_CTRL_RNG_HCLK_SLP_OFF_Msk

#define MCU_SUB_SECU_CLK_CTRL_EFUSE_HCLK_FORCE_OFF_Pos      (12U)
#define MCU_SUB_SECU_CLK_CTRL_EFUSE_HCLK_FORCE_OFF_Len      (1U)
#define MCU_SUB_SECU_CLK_CTRL_EFUSE_HCLK_FORCE_OFF_Msk      (0x1UL << MCU_SUB_SECU_CLK_CTRL_EFUSE_HCLK_FORCE_OFF_Pos)
#define MCU_SUB_SECU_CLK_CTRL_EFUSE_HCLK_FORCE_OFF          MCU_SUB_SECU_CLK_CTRL_EFUSE_HCLK_FORCE_OFF_Msk

#define MCU_SUB_SECU_CLK_CTRL_EFUSE_HCLK_SLP_OFF_Pos        (13U)
#define MCU_SUB_SECU_CLK_CTRL_EFUSE_HCLK_SLP_OFF_Len        (1U)
#define MCU_SUB_SECU_CLK_CTRL_EFUSE_HCLK_SLP_OFF_Msk        (0x1UL << MCU_SUB_SECU_CLK_CTRL_EFUSE_HCLK_SLP_OFF_Pos)
#define MCU_SUB_SECU_CLK_CTRL_EFUSE_HCLK_SLP_OFF            MCU_SUB_SECU_CLK_CTRL_EFUSE_HCLK_SLP_OFF_Msk

/*****************  Bit definition for MCU_SUB_MCU_MISC_CLK_DBG register  ******************/
#define MCU_SUB_CLK_CTRL_XQSPI_SCK_OFF_Pos                  (2U)
#define MCU_SUB_CLK_CTRL_XQSPI_SCK_OFF_Len                  (1U)
#define MCU_SUB_CLK_CTRL_XQSPI_SCK_OFF_Msk                  (0x1UL << MCU_SUB_CLK_CTRL_XQSPI_SCK_OFF_Pos)
#define MCU_SUB_CLK_CTRL_XQSPI_SCK_OFF                      MCU_SUB_CLK_CTRL_XQSPI_SCK_OFF_Msk

#define MCU_SUB_CLK_CTRL_DMA0_HCLK_OFF_Pos                  (3U)
#define MCU_SUB_CLK_CTRL_DMA0_HCLK_OFF_Len                  (1U)
#define MCU_SUB_CLK_CTRL_DMA0_HCLK_OFF_Msk                  (0x1UL << MCU_SUB_CLK_CTRL_DMA0_HCLK_OFF_Pos)
#define MCU_SUB_CLK_CTRL_DMA0_HCLK_OFF                      MCU_SUB_CLK_CTRL_DMA0_HCLK_OFF_Msk

/*****************  Bit definition for MCU_SUB_HFOSC_CLK_EN register  ******************/
#define MCU_SUB_HFOSC_CLK_EN_Pos                            (0U)
#define MCU_SUB_HFOSC_CLK_EN_Len                            (1U)
#define MCU_SUB_HFOSC_CLK_EN_Msk                            (0x1UL << MCU_SUB_HFOSC_CLK_EN_Pos)
#define MCU_SUB_HFOSC_CLK_EN                                MCU_SUB_HFOSC_CLK_EN_Msk

/*******************  Bit definition for MCU_SUB_APB_TIMER_DBG register  *******************/
#define MCU_SUB_APB_TIMER_DBG_TIMER0_POS                    (0U)
#define MCU_SUB_APB_TIMER_DBG_TIMER0_Len                    (1U)
#define MCU_SUB_APB_TIMER_DBG_TIMER0_Msk                    (0x1UL << MCU_SUB_APB_TIMER_DBG_TIMER0_POS)
#define MCU_SUB_APB_TIMER_DBG_TIMER0                        MCU_SUB_APB_TIMER_DBG_TIMER0_Msk

#define MCU_SUB_APB_TIMER_DBG_TIMER1_POS                    (1U)
#define MCU_SUB_APB_TIMER_DBG_TIMER1_Len                    (1U)
#define MCU_SUB_APB_TIMER_DBG_TIMER1_Msk                    (0x1U << MCU_SUB_APB_TIMER_DBG_TIMER1_POS)
#define MCU_SUB_APB_TIMER_DBG_TIMER1                        MCU_SUB_APB_TIMER_DBG_TIMER1_Msk

#define MCU_SUB_APB_TIMER_DBG_DUAL_TIMER_POS                (2U)
#define MCU_SUB_APB_TIMER_DBG_DUAL_TIMER_Len                (1U)
#define MCU_SUB_APB_TIMER_DBG_DUAL_TIMER_Msk                (0x1U << MCU_SUB_APB_TIMER_DBG_DUAL_TIMER_POS)
#define MCU_SUB_APB_TIMER_DBG_DUAL_TIMER                    MCU_SUB_APB_TIMER_DBG_DUAL_TIMER_Msk

#define MCU_SUB_APB_TIMER_DBG_WDT_POS                       (3U)
#define MCU_SUB_APB_TIMER_DBG_WDT_Len                       (1U)
#define MCU_SUB_APB_TIMER_DBG_WDT_Msk                       (0x1UL << MCU_SUB_APB_TIMER_DBG_WDT_POS)
#define MCU_SUB_APB_TIMER_DBG_WDT                           MCU_SUB_APB_TIMER_DBG_WDT_Msk

/***************  Bit definition for MCU_APB_MON_DBG register  ********/
#define MCU_SUB_MCU_APB_MON_BYPASS_POS                      (0U)
#define MCU_SUB_MCU_APB_MON_BYPASS_Len                      (1U)
#define MCU_SUB_MCU_APB_MON_BYPASS_Msk                      (0x1UL << MCU_SUB_MCU_APB_MON_BYPASS_POS)
#define MCU_SUB_MCU_APB_MON_BYPASS                          MCU_SUB_MCU_APB_MON_BYPASS_Msk

/***************  Bit definition for MCU_RELEASE register  ********/
#define MCU_SUB_MCU_RELEASE_Pos                             (0U)
#define MCU_SUB_MCU_RELEASE_Len                             (32U)
#define MCU_SUB_MCU_RELEASE_Msk                             (0xFFFFFFFFU)
#define MCU_SUB_MCU_RELEASE                                 MCU_SUB_MCU_RELEASE_Msk

/***************  Bit definition for FPGA_CTRL_REG register  ********/
#define MCU_SUB_FPGA_CTRL_REG_EXIST_Pos                     (4U)
#define MCU_SUB_FPGA_CTRL_REG_EXIST_Len                     (1U)
#define MCU_SUB_FPGA_CTRL_REG_EXIST_Msk                     (0x1U << MCU_SUB_FPGA_CTRL_REG_EXIST_Pos)
#define MCU_SUB_FPGA_CTRL_REG_EXIST                         MCU_SUB_FPGA_CTRL_REG_EXIST_Msk

#define MCU_SUB_FPGA_CTRL_REG_MUX_SEL_Pos                   (0U)
#define MCU_SUB_FPGA_CTRL_REG_MUX_SEL_Len                   (2U)
#define MCU_SUB_FPGA_CTRL_REG_MUX_SEL_Msk                   (0x3U << MCU_SUB_FPGA_CTRL_REG_MUX_SEL_Pos)
#define MCU_SUB_FPGA_CTRL_REG_MUX_SEL                       MCU_SUB_FPGA_CTRL_REG_MUX_SEL_Msk

/**********************  Bit definition for ST_CALIB_REG register  ***********************************/
#define MCU_SUB_ST_CALIB_REG_STCALIB_CLK_Pos                (28U)
#define MCU_SUB_ST_CALIB_REG_STCALIB_CLK_Len                (1U)
#define MCU_SUB_ST_CALIB_REG_STCALIB_CLK_Msk                (0x1U <<  MCU_SUB_ST_CALIB_REG_STCALIB_CLK_Pos)
#define MCU_SUB_ST_CALIB_REG_STCALIB_CLK                    MCU_SUB_ST_CALIB_REG_STCALIB_CLK_Msk

#define MCU_SUB_ST_CALIB_REG_STCALIB_Pos                    (0U)
#define MCU_SUB_ST_CALIB_REG_STCALIB_Len                    (26U)
#define MCU_SUB_ST_CALIB_REG_STCALIB_Msk                    (0x3FFFFFFU <<  MCU_SUB_ST_CALIB_REG_STCALIB_Pos)
#define MCU_SUB_ST_CALIB_REG_STCALIB                        MCU_SUB_ST_CALIB_REG_STCALIB_Msk


/* ================================================================================================================= */
/* ================                                        PWM                                      ================ */
/* ================================================================================================================= */

/*******************  Bit definition for PWM_MODE register  *******************/
#define PWM_MODE_EN_Pos                                     (0U)
#define PWM_MODE_EN_Len                                     (1U)
#define PWM_MODE_EN_Msk                                     (0x1U << PWM_MODE_EN_Pos)
#define PWM_MODE_EN                                         PWM_MODE_EN_Msk

#define PWM_MODE_PAUSE_Pos                                  (1U)
#define PWM_MODE_PAUSE_Len                                  (1U)
#define PWM_MODE_PAUSE_Msk                                  (0x1U << PWM_MODE_PAUSE_Pos)
#define PWM_MODE_PAUSE                                      PWM_MODE_PAUSE_Msk

#define PWM_MODE_BREATHEN_Pos                               (2U)
#define PWM_MODE_BREATHEN_Len                               (1U)
#define PWM_MODE_BREATHEN_Msk                               (0x1U << PWM_MODE_BREATHEN_Pos)
#define PWM_MODE_BREATHEN                                   PWM_MODE_BREATHEN_Msk

#define PWM_MODE_DPENA_Pos                                  (3U)
#define PWM_MODE_DPENA_Len                                  (1U)
#define PWM_MODE_DPENA_Msk                                  (0x1U << PWM_MODE_DPENA_Pos)
#define PWM_MODE_DPENA                                      PWM_MODE_DPENA_Msk

#define PWM_MODE_DPENB_Pos                                  (4U)
#define PWM_MODE_DPENB_Len                                  (1U)
#define PWM_MODE_DPENB_Msk                                  (0x1U << PWM_MODE_DPENB_Pos)
#define PWM_MODE_DPENB                                      PWM_MODE_DPENB_Msk

#define PWM_MODE_DPENC_Pos                                  (5U)
#define PWM_MODE_DPENC_Len                                  (1U)
#define PWM_MODE_DPENC_Msk                                  (0x1U << PWM_MODE_DPENC_Pos)
#define PWM_MODE_DPENC                                      PWM_MODE_DPENC_Msk

#define PWM_MODE_FLICKER_PAUSE_LEVEL_A_Pos                  (6U)
#define PWM_MODE_FLICKER_PAUSE_LEVEL_A_Len                  (1U)
#define PWM_MODE_FLICKER_PAUSE_LEVEL_A_Msk                  (0x1U << PWM_MODE_FLICKER_PAUSE_LEVEL_A_Pos)
#define PWM_MODE_FLICKER_PAUSE_LEVEL_A                      PWM_MODE_FLICKER_PAUSE_LEVEL_A_Msk

#define PWM_MODE_FLICKER_PAUSE_LEVEL_B_Pos                  (7U)
#define PWM_MODE_FLICKER_PAUSE_LEVEL_B_Len                  (1U)
#define PWM_MODE_FLICKER_PAUSE_LEVEL_B_Msk                  (0x1U << PWM_MODE_FLICKER_PAUSE_LEVEL_B_Pos)
#define PWM_MODE_FLICKER_PAUSE_LEVEL_B                      PWM_MODE_FLICKER_PAUSE_LEVEL_B_Msk

#define PWM_MODE_FLICKER_PAUSE_LEVEL_C_Pos                  (8U)
#define PWM_MODE_FLICKER_PAUSE_LEVEL_C_Len                  (1U)
#define PWM_MODE_FLICKER_PAUSE_LEVEL_C_Msk                  (0x1U << PWM_MODE_FLICKER_PAUSE_LEVEL_C_Pos)
#define PWM_MODE_FLICKER_PAUSE_LEVEL_C                      PWM_MODE_FLICKER_PAUSE_LEVEL_C_Msk

#define PWM_MODE_BREATH_PAUSE_LEVEL_Pos                     (9U)
#define PWM_MODE_BREATH_PAUSE_LEVEL_Len                     (1U)
#define PWM_MODE_BREATH_PAUSE_LEVEL_Msk                     (0x1U << PWM_MODE_BREATH_PAUSE_LEVEL_Pos)
#define PWM_MODE_BREATH_PAUSE_LEVEL                         PWM_MODE_BREATH_PAUSE_LEVEL_Msk

#define PWM_MODE_CODINGEN_Pos                               (10U)
#define PWM_MODE_CODINGEN_Len                               (1U)
#define PWM_MODE_CODINGEN_Msk                               (0x1U << PWM_MODE_CODINGEN_Pos)
#define PWM_MODE_CODINGEN                                   PWM_MODE_CODINGEN_Msk

#define PWM_MODE_WAITING_TIME_LEVEL_A_Pos                   (11U)
#define PWM_MODE_WAITING_TIME_LEVEL_A_Len                   (1U)
#define PWM_MODE_WAITING_TIME_LEVEL_A_Msk                   (0x1U << PWM_MODE_WAITING_TIME_LEVEL_A_Pos)
#define PWM_MODE_WAITING_TIME_LEVEL_A                       PWM_MODE_WAITING_TIME_LEVEL_A_Msk

#define PWM_MODE_WAITING_TIME_LEVEL_B_Pos                   (12U)
#define PWM_MODE_WAITING_TIME_LEVEL_B_Len                   (1U)
#define PWM_MODE_WAITING_TIME_LEVEL_B_Msk                   (0x1U << PWM_MODE_WAITING_TIME_LEVEL_B_Pos)
#define PWM_MODE_WAITING_TIME_LEVEL_B                       PWM_MODE_WAITING_TIME_LEVEL_B_Msk

#define PWM_MODE_WAITING_TIME_LEVEL_C_Pos                   (13U)
#define PWM_MODE_WAITING_TIME_LEVEL_C_Len                   (1U)
#define PWM_MODE_WAITING_TIME_LEVEL_C_Msk                   (0x1U << PWM_MODE_WAITING_TIME_LEVEL_C_Pos)
#define PWM_MODE_WAITING_TIME_LEVEL_C                       PWM_MODE_WAITING_TIME_LEVEL_C_Msk

#define PWM_MODE_DMA_EN_Pos                                 (14U)
#define PWM_MODE_DMA_EN_Len                                 (1U)
#define PWM_MODE_DMA_EN_Msk                                 (0x1U << PWM_MODE_DMA_EN_Pos)
#define PWM_MODE_DMA_EN                                     PWM_MODE_DMA_EN_Msk

#define PWM_MODE_CODING_CHANNEL_SELECT_Pos                  (15U)
#define PWM_MODE_CODING_CHANNEL_SELECT_Len                  (1U)
#define PWM_MODE_CODING_CHANNEL_SELECT_Msk                  (0x1U << PWM_MODE_CODING_CHANNEL_SELECT_Pos)
#define PWM_MODE_CODING_CHANNEL_SELECT                      PWM_MODE_CODING_CHANNEL_SELECT_Msk

/*******************  Bit definition for PWM_UPDATE register  *****************/
#define PWM_UPDATE_SAG_Pos                                  (0U)
#define PWM_UPDATE_SAG_Len                                  (1U)
#define PWM_UPDATE_SAG_Msk                                  (0x1U << PWM_UPDATE_SAG_Pos)
#define PWM_UPDATE_SAG                                      PWM_UPDATE_SAG_Msk

#define PWM_UPDATE_SA_Pos                                   (1U)
#define PWM_UPDATE_SA_Len                                   (1U)
#define PWM_UPDATE_SA_Msk                                   (0x1U << PWM_UPDATE_SA_Pos)
#define PWM_UPDATE_SA                                       PWM_UPDATE_SA_Msk

#define PWM_UPDATE_SSPRD_Pos                                (8U)
#define PWM_UPDATE_SSPRD_Len                                (1U)
#define PWM_UPDATE_SSPRD_Msk                                (0x1U << PWM_UPDATE_SSPRD_Pos)
#define PWM_UPDATE_SSPRD                                    PWM_UPDATE_SSPRD_Msk

#define PWM_UPDATE_SSCMPA0_Pos                              (9U)
#define PWM_UPDATE_SSCMPA0_Len                              (1U)
#define PWM_UPDATE_SSCMPA0_Msk                              (0x1U << PWM_UPDATE_SSCMPA0_Pos)
#define PWM_UPDATE_SSCMPA0                                  PWM_UPDATE_SSCMPA0_Msk

#define PWM_UPDATE_SSCMPA1_Pos                              (10U)
#define PWM_UPDATE_SSCMPA1_Len                              (1U)
#define PWM_UPDATE_SSCMPA1_Msk                              (0x1U << PWM_UPDATE_SSCMPA1_Pos)
#define PWM_UPDATE_SSCMPA1                                  PWM_UPDATE_SSCMPA1_Msk

#define PWM_UPDATE_SSCMPB0_Pos                              (11U)
#define PWM_UPDATE_SSCMPB0_Len                              (1U)
#define PWM_UPDATE_SSCMPB0_Msk                              (0x1U << PWM_UPDATE_SSCMPB0_Pos)
#define PWM_UPDATE_SSCMPB0                                  PWM_UPDATE_SSCMPB0_Msk

#define PWM_UPDATE_SSCMPB1_Pos                              (12U)
#define PWM_UPDATE_SSCMPB1_Len                              (1U)
#define PWM_UPDATE_SSCMPB1_Msk                              (0x1U << PWM_UPDATE_SSCMPB1_Pos)
#define PWM_UPDATE_SSCMPB1                                  PWM_UPDATE_SSCMPB1_Msk

#define PWM_UPDATE_SSCMPC0_Pos                              (13U)
#define PWM_UPDATE_SSCMPC0_Len                              (1U)
#define PWM_UPDATE_SSCMPC0_Msk                              (0x1U << PWM_UPDATE_SSCMPC0_Pos)
#define PWM_UPDATE_SSCMPC0                                  PWM_UPDATE_SSCMPC0_Msk

#define PWM_UPDATE_SSCMPC1_Pos                              (14U)
#define PWM_UPDATE_SSCMPC1_Len                              (1U)
#define PWM_UPDATE_SSCMPC1_Msk                              (0x1U << PWM_UPDATE_SSCMPC1_Pos)
#define PWM_UPDATE_SSCMPC1                                  PWM_UPDATE_SSCMPC1_Msk

#define PWM_UPDATE_SSBRPRD_Pos                              (15U)
#define PWM_UPDATE_SSBRPRD_Len                              (1U)
#define PWM_UPDATE_SSBRPRD_Msk                              (0x1U << PWM_UPDATE_SSBRPRD_Pos)
#define PWM_UPDATE_SSBRPRD                                  PWM_UPDATE_SSBRPRD_Msk

#define PWM_UPDATE_SSHOLD_Pos                               (16U)
#define PWM_UPDATE_SSHOLD_Len                               (1U)
#define PWM_UPDATE_SSHOLD_Msk                               (0x1U << PWM_UPDATE_SSHOLD_Pos)
#define PWM_UPDATE_SSHOLD                                   PWM_UPDATE_SSHOLD_Msk

#define PWM_UPDATE_SSAQCTRL_Pos                             (17U)
#define PWM_UPDATE_SSAQCTRL_Len                             (1U)
#define PWM_UPDATE_SSAQCTRL_Msk                             (0x1U << PWM_UPDATE_SSAQCTRL_Pos)
#define PWM_UPDATE_SSAQCTRL                                 PWM_UPDATE_SSAQCTRL_Msk

/*******************  Bit definition for PWM_PRD register  ********************/
#define PWM_PRD_PRD_Pos                                     (0U)
#define PWM_PRD_PRD_Len                                     (32U)
#define PWM_PRD_PRD_Msk                                     (0xFFFFFFFFU)
#define PWM_PRD_PRD                                         PWM_PRD_PRD_Msk

/*******************  Bit definition for PWM_CMPA0 register  ******************/
#define PWM_CMPA0_CMPA0_Pos                                 (0U)
#define PWM_CMPA0_CMPA0_Len                                 (32U)
#define PWM_CMPA0_CMPA0_Msk                                 (0xFFFFFFFFU)
#define PWM_CMPA0_CMPA0                                     PWM_CMPA0_CMPA0_Msk

/*******************  Bit definition for PWM_CMPA1 register  ******************/
#define PWM_CMPA1_CMPA1_Pos                                 (0U)
#define PWM_CMPA1_CMPA1_Len                                 (32U)
#define PWM_CMPA1_CMPA1_Msk                                 (0xFFFFFFFFU)
#define PWM_CMPA1_CMPA1                                     PWM_CMPA1_CMPA1_Msk

/*******************  Bit definition for PWM_CMPB0 register  ******************/
#define PWM_CMPB0_CMPB0_Pos                                 (0U)
#define PWM_CMPB0_CMPB0_Len                                 (32U)
#define PWM_CMPB0_CMPB0_Msk                                 (0xFFFFFFFFU)
#define PWM_CMPB0_CMPB0                                     PWM_CMPB0_CMPB0_Msk

/*******************  Bit definition for PWM_CMPB1 register  ******************/
#define PWM_CMPB1_CMPB1_Pos                                 (0U)
#define PWM_CMPB1_CMPB1_Len                                 (32U)
#define PWM_CMPB1_CMPB1_Msk                                 (0xFFFFFFFFU)
#define PWM_CMPB1_CMPB1                                     PWM_CMPB1_CMPB1_Msk

/*******************  Bit definition for PWM_CMPC0 register  ******************/
#define PWM_CMPC0_CMPC0_Pos                                 (0U)
#define PWM_CMPC0_CMPC0_Len                                 (32U)
#define PWM_CMPC0_CMPC0_Msk                                 (0xFFFFFFFFU)
#define PWM_CMPC0_CMPC0                                     PWM_CMPC0_CMPC0_Msk

/*******************  Bit definition for PWM_CMPC1 register  ******************/
#define PWM_CMPC1_CMPC1_Pos                                 (0U)
#define PWM_CMPC1_CMPC1_Len                                 (32U)
#define PWM_CMPC1_CMPC1_Msk                                 (0xFFFFFFFFU)
#define PWM_CMPC1_CMPC1                                     PWM_CMPC1_CMPC1_Msk

/*******************  Bit definition for PWM_AQCTRL register  *****************/
#define PWM_AQCTRL_A0_Pos                                   (0U)
#define PWM_AQCTRL_A0_Len                                   (2U)
#define PWM_AQCTRL_A0_Msk                                   (0x3U << PWM_AQCTRL_A0_Pos)
#define PWM_AQCTRL_A0                                       PWM_AQCTRL_A0_Msk

#define PWM_AQCTRL_A1_Pos                                   (2U)
#define PWM_AQCTRL_A1_Len                                   (2U)
#define PWM_AQCTRL_A1_Msk                                   (0x3U << PWM_AQCTRL_A1_Pos)
#define PWM_AQCTRL_A1                                       PWM_AQCTRL_A1_Msk

#define PWM_AQCTRL_B0_Pos                                   (4U)
#define PWM_AQCTRL_B0_Len                                   (2U)
#define PWM_AQCTRL_B0_Msk                                   (0x3U << PWM_AQCTRL_B0_Pos)
#define PWM_AQCTRL_B0                                       PWM_AQCTRL_B0_Msk

#define PWM_AQCTRL_B1_Pos                                   (6U)
#define PWM_AQCTRL_B1_Len                                   (2U)
#define PWM_AQCTRL_B1_Msk                                   (0x3U << PWM_AQCTRL_B1_Pos)
#define PWM_AQCTRL_B1                                       PWM_AQCTRL_B1_Msk

#define PWM_AQCTRL_C0_Pos                                   (8U)
#define PWM_AQCTRL_C0_Len                                   (2U)
#define PWM_AQCTRL_C0_Msk                                   (0x3U << PWM_AQCTRL_C0_Pos)
#define PWM_AQCTRL_C0                                       PWM_AQCTRL_C0_Msk

#define PWM_AQCTRL_C1_Pos                                   (10U)
#define PWM_AQCTRL_C1_Len                                   (2U)
#define PWM_AQCTRL_C1_Msk                                   (0x3U << PWM_AQCTRL_C1_Pos)
#define PWM_AQCTRL_C1                                       PWM_AQCTRL_C1_Msk

/*******************  Bit definition for PWM_BRPRD register  ******************/
#define PWM_BRPRD_BRPRD_Pos                                 (0U)
#define PWM_BRPRD_BRPRD_Len                                 (32U)
#define PWM_BRPRD_BRPRD_Msk                                 (0xFFFFFFFFU)
#define PWM_BRPRD_BRPRD                                     PWM_BRPRD_BRPRD_Msk

/*******************  Bit definition for PWM_HOLD register  *******************/
#define PWM_HOLD_HOLD_Pos                                   (0U)
#define PWM_HOLD_HOLD_Len                                   (24U)
#define PWM_HOLD_HOLD_Msk                                   (0x00FFFFFFU)
#define PWM_HOLD_HOLD                                       PWM_HOLD_HOLD_Msk

/*******************  Bit definition for PWM_PRD_CYCLES register  *******************/
#define PWM_PRD_CYCLES_Pos                                  (0U)
#define PWM_PRD_CYCLES_Len                                  (32U)
#define PWM_PRD_CYCLES_Msk                                  (0xFFFFFFFFU)
#define PWM_PRD_CYCLES                                      PWM_PRD_CYCLES_Msk

/*******************  Bit definition for PWM_WAIT_TIME register  *******************/
#define PWM_WAIT_TIME_Pos                                   (0U)
#define PWM_WAIT_TIME_Len                                   (32U)
#define PWM_WAIT_TIME_Msk                                   (0xFFFFFFFFU)
#define PWM_WAIT_TIME                                       PWM_WAIT_TIME_Msk

/*******************  Bit definition for PWM_DATA_WIDTH_VALID register  *******************/
#define PWM_DATA_WIDTH_VALID_Pos                            (0U)
#define PWM_DATA_WIDTH_VALID_Len                            (5U)
#define PWM_DATA_WIDTH_VALID_Msk                            (0x1FU << PWM_DATA_WIDTH_VALID_Pos)
#define PWM_DATA_WIDTH_VALID                                PWM_DATA_WIDTH_VALID_Msk

/*******************  Bit definition for PWM_CODING_DATA register  *******************/
#define PWM_CODING_DATA_Pos                                 (0U)
#define PWM_CODING_DATA_Len                                 (32U)
#define PWM_CODING_DATA_Msk                                 (0xFFFFFFFFU)
#define PWM_CODING_DATA                                     PWM_CODING_DATA_Msk

/*******************  Bit definition for PWM_CODING_STATUS register  *******************/\
#define PWM_CODING_STATUS_CODING_A_ERROR_Pos                (0U)
#define PWM_CODING_STATUS_CODING_A_ERROR_Len                (1U)
#define PWM_CODING_STATUS_CODING_A_ERROR_Msk                (0x1U << PWM_CODING_STATUS_CODING_A_ERROR_Pos)
#define PWM_CODING_STATUS_CODING_A_ERROR                    PWM_CODING_STATUS_CODING_A_ERROR_Msk

#define PWM_CODING_STATUS_CODING_B_ERROR_Pos                (1U)
#define PWM_CODING_STATUS_CODING_B_ERROR_Len                (1U)
#define PWM_CODING_STATUS_CODING_B_ERROR_Msk                (0x1U << PWM_CODING_STATUS_CODING_B_ERROR_Pos)
#define PWM_CODING_STATUS_CODING_B_ERROR                    PWM_CODING_STATUS_CODING_B_ERROR_Msk

#define PWM_CODING_STATUS_CODING_C_ERROR_Pos                (2U)
#define PWM_CODING_STATUS_CODING_C_ERROR_Len                (1U)
#define PWM_CODING_STATUS_CODING_C_ERROR_Msk                (0x1U << PWM_CODING_STATUS_CODING_C_ERROR_Pos)
#define PWM_CODING_STATUS_CODING_C_ERROR                    PWM_CODING_STATUS_CODING_C_ERROR_Msk

#define PWM_CODING_STATUS_CODING_DONE_Pos                   (3U)
#define PWM_CODING_STATUS_CODING_DONE_Len                   (1U)
#define PWM_CODING_STATUS_CODING_DONE_Msk                   (0x1U << PWM_CODING_STATUS_CODING_DONE_Pos)
#define PWM_CODING_STATUS_CODING_DONE                       PWM_CODING_STATUS_CODING_DONE_Msk

#define PWM_CODING_STATUS_CODING_LOAD_Pos                   (4U)
#define PWM_CODING_STATUS_CODING_LOAD_Len                   (1U)
#define PWM_CODING_STATUS_CODING_LOAD_Msk                   (0x1U << PWM_CODING_STATUS_CODING_LOAD_Pos)
#define PWM_CODING_STATUS_CODING_LOAD                       PWM_CODING_STATUS_CODING_LOAD_Msk

/*******************  Bit definition for PWM_CLR_CODING_STATUS register  *******************/\
#define PWM_CODING_STATUS_CODING_A_ERROR_CLR_Pos            (0U)
#define PWM_CODING_STATUS_CODING_A_ERROR_CLR_Len            (1U)
#define PWM_CODING_STATUS_CODING_A_ERROR_CLR_Msk            (0x1U << PWM_CODING_STATUS_CODING_A_ERROR_CLR_Pos)
#define PWM_CODING_STATUS_CODING_A_ERROR_CLR                PWM_CODING_STATUS_CODING_A_ERROR_CLR_Msk

#define PWM_CODING_STATUS_CODING_B_ERROR_CLR_Pos            (1U)
#define PWM_CODING_STATUS_CODING_B_ERROR_CLR_Len            (1U)
#define PWM_CODING_STATUS_CODING_B_ERROR_CLR_Msk            (0x1U << PWM_CODING_STATUS_CODING_B_ERROR_CLR_Pos)
#define PWM_CODING_STATUS_CODING_B_ERROR_CLR                PWM_CODING_STATUS_CODING_B_ERROR_CLR_Msk

#define PWM_CODING_STATUS_CODING_C_ERROR_CLR_Pos            (2U)
#define PWM_CODING_STATUS_CODING_C_ERROR_CLR_Len            (1U)
#define PWM_CODING_STATUS_CODING_C_ERROR_CLR_Msk            (0x1U << PWM_CODING_STATUS_CODING_C_ERROR_CLR_Pos)
#define PWM_CODING_STATUS_CODING_C_ERROR_CLR                PWM_CODING_STATUS_CODING_C_ERROR_CLR_Msk

#define PWM_CODING_STATUS_CODING_DONE_CLR_Pos               (3U)
#define PWM_CODING_STATUS_CODING_DONE_CLR_Len               (1U)
#define PWM_CODING_STATUS_CODING_DONE_CLR_Msk               (0x1U << PWM_CODING_STATUS_CODING_DONE_CLR_Pos)
#define PWM_CODING_STATUS_CODING_DONE_CLR                   PWM_CODING_STATUS_CODING_DONE_CLR_Msk

#define PWM_CODING_STATUS_CODING_LOAD_CLR_Pos               (4U)
#define PWM_CODING_STATUS_CODING_LOAD_CLR_Len               (1U)
#define PWM_CODING_STATUS_CODING_LOAD_CLR_Msk               (0x1U << PWM_CODING_STATUS_CODING_LOAD_CLR_Pos)
#define PWM_CODING_STATUS_CODING_LOAD_CLR                   PWM_CODING_STATUS_CODING_LOAD_Msk

/* ================================================================================================================= */
/* ================                                        SPI                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for SPI_CTRL0 register  *******************/
#define SPI_CTRL0_FRAME_FORMAT_POS                          (4U)
#define SPI_CTRL0_FRAME_FORMAT_Len                          (2U)
#define SPI_CTRL0_FRAME_FORMAT_Msk                          (0x3UL << SPI_CTRL0_FRAME_FORMAT_POS)
#define SPI_CTRL0_FRAME_FORMAT                              SPI_CTRL0_FRAME_FORMAT_Msk

#define SPI_CTRL0_SERIAL_CLK_PHASE_POS                      (6U)
#define SPI_CTRL0_SERIAL_CLK_PHASE_Len                      (1U)
#define SPI_CTRL0_SERIAL_CLK_PHASE_Msk                      (0x1UL << SPI_CTRL0_SERIAL_CLK_PHASE_POS)
#define SPI_CTRL0_SERIAL_CLK_PHASE                          SPI_CTRL0_SERIAL_CLK_PHASE_Msk

#define SPI_CTRL0_SERIAL_CLK_POL_POS                        (7U)
#define SPI_CTRL0_SERIAL_CLK_POL_Len                        (1U)
#define SPI_CTRL0_SERIAL_CLK_POL_Msk                        (0x1UL << SPI_CTRL0_SERIAL_CLK_POL_POS)
#define SPI_CTRL0_SERIAL_CLK_POL                            SPI_CTRL0_SERIAL_CLK_POL_Msk

#define SPI_CTRL0_XFE_MODE_POS                              (8U)
#define SPI_CTRL0_XFE_MODE_Len                              (2U)
#define SPI_CTRL0_XFE_MODE_Msk                              (0x3UL << SPI_CTRL0_XFE_MODE_POS)
#define SPI_CTRL0_XFE_MODE                                  SPI_CTRL0_XFE_MODE_Msk

#define SPI_CTRL0_S_OUT_EN_POS                              (10U)
#define SPI_CTRL0_S_OUT_EN_Len                              (1U)
#define SPI_CTRL0_S_OUT_EN_Msk                              (0x1UL << SPI_CTRL0_S_OUT_EN_POS)
#define SPI_CTRL0_S_OUT_EN                                  SPI_CTRL0_S_OUT_EN_Msk

#define SPI_CTRL0_SHIFT_REG_LOOP_POS                        (11U)
#define SPI_CTRL0_SHIFT_REG_LOOP_Len                        (1U)
#define SPI_CTRL0_SHIFT_REG_LOOP_Msk                        (0x1UL << SPI_CTRL0_SHIFT_REG_LOOP_POS)
#define SPI_CTRL0_SHIFT_REG_LOOP                            SPI_CTRL0_SHIFT_REG_LOOP_Msk

#define SPI_CTRL0_CTRL_FRAME_SIZE_POS                       (12U)
#define SPI_CTRL0_CTRL_FRAME_SIZE_Len                       (4U)
#define SPI_CTRL0_CTRL_FRAME_SIZE_Msk                       (0xFUL << SPI_CTRL0_CTRL_FRAME_SIZE_POS)
#define SPI_CTRL0_CTRL_FRAME_SIZE                           SPI_CTRL0_CTRL_FRAME_SIZE_Msk

#define SPI_CTRL0_DATA_FRAME_SIZE_POS                       (16U)
#define SPI_CTRL0_DATA_FRAME_SIZE_Len                       (5U)
#define SPI_CTRL0_DATA_FRAME_SIZE_Msk                       (0x1FUL << SPI_CTRL0_DATA_FRAME_SIZE_POS)
#define SPI_CTRL0_DATA_FRAME_SIZE                           SPI_CTRL0_DATA_FRAME_SIZE_Msk

#define SPI_CTRL0_S_ST_EN_POS                               (24U)
#define SPI_CTRL0_S_ST_EN_Len                               (1U)
#define SPI_CTRL0_S_ST_EN_Msk                               (0x1UL << SPI_CTRL0_S_ST_EN_POS)
#define SPI_CTRL0_S_ST_EN                                   SPI_CTRL0_S_ST_EN_Msk

/*******************  Bit definition for SPI_CTRL1 register  *******************/
#define SPI_CTRL1_NUM_DATA_FRAME_POS                        (0U)
#define SPI_CTRL1_NUM_DATA_FRAME_Len                        (16U)
#define SPI_CTRL1_NUM_DATA_FRAME_Msk                        (0xFFFFUL << SPI_CTRL1_NUM_DATA_FRAME_POS)
#define SPI_CTRL1_NUM_DATA_FRAME                            SPI_CTRL1_NUM_DATA_FRAME_Msk

/*******************  Bit definition for SPI_SSI_EN register  *******************/
#define SPI_SSI_EN_POS                                      (0U)
#define SPI_SSI_EN_Len                                      (1U)
#define SPI_SSI_EN_Msk                                      (0x1UL << SPI_SSI_EN_POS)
#define SPI_SSI_EN                                          SPI_SSI_EN_Msk

/*******************  Bit definition for SPI_MW_CTRL register  *******************/
#define SPI_MW_CTRL_MW_XFE_MODE_POS                         (0U)
#define SPI_MW_CTRL_MW_XFE_MODE_Len                         (1U)
#define SPI_MW_CTRL_MW_XFE_MODE_Msk                         (0x1UL << SPI_MW_CTRL_MW_XFE_MODE_POS)
#define SPI_MW_CTRL_MW_XFE_MODE                             SPI_MW_CTRL_MW_XFE_MODE_Msk

#define SPI_MW_CTRL_MW_DIR_DW_POS                           (1U)
#define SPI_MW_CTRL_MW_DIR_DW_Len                           (1U)
#define SPI_MW_CTRL_MW_DIR_DW_Msk                           (0x1UL << SPI_MW_CTRL_MW_DIR_DW_POS)
#define SPI_MW_CTRL_MW_DIR_DW                               SPI_MW_CTRL_MW_DIR_DW_Msk

#define SPI_MW_CTRL_MW_HSG_POS                              (2U)
#define SPI_MW_CTRL_MW_HSG_Len                              (1U)
#define SPI_MW_CTRL_MW_HSG_Msk                              (0x1UL << SPI_MW_CTRL_MW_HSG_POS)
#define SPI_MW_CTRL_MW_HSG                                  SPI_MW_CTRL_MW_HSG_Msk

/*******************  Bit definition for SPI_S_EN register  *******************/
#define SPI_SLA_S0_SEL_EN_POS                               (0U)
#define SPI_SLA_S0_SEL_EN_Len                               (1U)
#define SPI_SLA_S0_SEL_EN_Msk                               (0x1UL << SPI_SLA_S0_SEL_EN_POS)
#define SPI_SLA_S0_SEL_EN                                   SPI_SLA_S0_SEL_EN_Msk

#define SPI_SLA_S1_SEL_EN_POS                               (1U)
#define SPI_SLA_S1_SEL_EN_Len                               (1U)
#define SPI_SLA_S1_SEL_EN_Msk                               (0x1UL << SPI_SLA_S1_SEL_EN_POS)
#define SPI_SLA_S1_SEL_EN                                   SPI_SLA_S1_SEL_EN_Msk

/*******************  Bit definition for SPI_BAUD register  *******************/
#define SPI_BAUD_CLK_DIV_POS                                (0U)
#define SPI_BAUD_CLK_DIV_Len                                (16U)
#define SPI_BAUD_CLK_DIV_Msk                                (0xFFFFUL << SPI_BAUD_CLK_DIV_POS)
#define SPI_BAUD_CLK_DIV                                    SPI_BAUD_CLK_DIV_Msk

/*******************  Bit definition for SPI_TX_FIFO_TL register  *******************/
#define SPI_TX_FIFO_TL_TX_FIFO_THD_POS                      (0U)
#define SPI_TX_FIFO_TL_TX_FIFO_THD_Len                      (4U)
#define SPI_TX_FIFO_TL_TX_FIFO_THD_Msk                      (0xFUL << SPI_TX_FIFO_TL_TX_FIFO_THD_POS)
#define SPI_TX_FIFO_TL_TX_FIFO_THD                          SPI_TX_FIFO_TL_TX_FIFO_THD_Msk

/*******************  Bit definition for SPI_RX_FIFO_TL register  *******************/
#define SPI_RX_FIFO_TL_RX_FIFO_THD_POS                      (0U)
#define SPI_RX_FIFO_TL_RX_FIFO_THD_Len                      (4U)
#define SPI_RX_FIFO_TL_RX_FIFO_THD_Msk                      (0xFUL << SPI_RX_FIFO_TL_RX_FIFO_THD_POS)
#define SPI_RX_FIFO_TL_RX_FIFO_THD                          SPI_RX_FIFO_TL_RX_FIFO_THD_Msk

/*******************  Bit definition for SPI_TX_FIFO_LEVEL register  *******************/
#define SPI_TX_FIFO_LEVEL_TX_FIFO_LEVEL_POS                 (0U)
#define SPI_TX_FIFO_LEVEL_TX_FIFO_LEVEL_Len                 (5U)
#define SPI_TX_FIFO_LEVEL_TX_FIFO_LEVEL_Msk                 (0x1FUL << SPI_TX_FIFO_LEVEL_TX_FIFO_LEVEL_POS)
#define SPI_TX_FIFO_LEVEL_TX_FIFO_LEVEL                     SPI_TX_FIFO_LEVEL_TX_FIFO_LEVEL_Msk

/*******************  Bit definition for SPI_RX_FIFO_LEVEL register  *******************/
#define SPI_RX_FIFO_LEVEL_RX_FIFO_LEVEL_POS                 (0U)
#define SPI_RX_FIFO_LEVEL_RX_FIFO_LEVEL_Len                 (5U)
#define SPI_RX_FIFO_LEVEL_RX_FIFO_LEVEL_Msk                 (0x1FUL << SPI_RX_FIFO_LEVEL_RX_FIFO_LEVEL_POS)
#define SPI_RX_FIFO_LEVEL_RX_FIFO_LEVEL                     SPI_RX_FIFO_LEVEL_RX_FIFO_LEVEL_Msk

/*******************  Bit definition for SPI_STAT register  *******************/
#define SPI_STAT_SSI_BUSY_POS                               (0U)
#define SPI_STAT_SSI_BUSY_Len                               (1U)
#define SPI_STAT_SSI_BUSY_Msk                               (0x1UL << SPI_STAT_SSI_BUSY_POS)
#define SPI_STAT_SSI_BUSY                                   SPI_STAT_SSI_BUSY_Msk

#define SPI_STAT_TX_FIFO_NF_POS                             (1U)
#define SPI_STAT_TX_FIFO_NF_Len                             (1U)
#define SPI_STAT_TX_FIFO_NF_Msk                             (0x1UL << SPI_STAT_TX_FIFO_NF_POS)
#define SPI_STAT_TX_FIFO_NF                                 SPI_STAT_TX_FIFO_NF_Msk

#define SPI_STAT_TX_FIFO_EMPTY_POS                          (2U)
#define SPI_STAT_TX_FIFO_EMPTY_Len                          (1U)
#define SPI_STAT_TX_FIFO_EMPTY_Msk                          (0x1UL << SPI_STAT_TX_FIFO_EMPTY_POS)
#define SPI_STAT_TX_FIFO_EMPTY                              SPI_STAT_TX_FIFO_EMPTY_Msk

#define SPI_STAT_RX_FIFO_NE_POS                             (3U)
#define SPI_STAT_RX_FIFO_NE_Len                             (1U)
#define SPI_STAT_RX_FIFO_NE_Msk                             (0x1UL << SPI_STAT_RX_FIFO_NE_POS)
#define SPI_STAT_RX_FIFO_NE                                 SPI_STAT_RX_FIFO_NE_Msk

#define SPI_STAT_RX_FIFO_FULL_POS                           (4U)
#define SPI_STAT_RX_FIFO_FULL_Len                           (1U)
#define SPI_STAT_RX_FIFO_FULL_Msk                           (0x1UL << SPI_STAT_RX_FIFO_FULL_POS)
#define SPI_STAT_RX_FIFO_FULL                               SPI_STAT_RX_FIFO_FULL_Msk

#define SPI_STAT_TX_ERR_POS                                 (5U)
#define SPI_STAT_TX_ERR_Len                                 (1U)
#define SPI_STAT_TX_ERR_Msk                                 (0x1UL << SPI_STAT_TX_ERR_POS)
#define SPI_STAT_TX_ERR                                     SPI_STAT_TX_ERR_Msk

#define SPI_STAT_DATA_COLN_ERR_POS                          (6U)
#define SPI_STAT_DATA_COLN_ERR_Len                          (1U)
#define SPI_STAT_DATA_COLN_ERR_Msk                          (0x1UL << SPI_STAT_DATA_COLN_ERR_POS)
#define SPI_STAT_DATA_COLN_ERR                              SPI_STAT_DATA_COLN_ERR_Msk

/*******************  Bit definition for SPI_INT_MASK register  *******************/
#define SPI_INT_MASK_TX_FIFO_EIM_POS                        (0U)
#define SPI_INT_MASK_TX_FIFO_EIM_Len                        (1U)
#define SPI_INT_MASK_TX_FIFO_EIM_Msk                        (0x1UL << SPI_INT_MASK_TX_FIFO_EIM_POS)
#define SPI_INT_MASK_TX_FIFO_EIM                            SPI_INT_MASK_TX_FIFO_EIM_Msk

#define SPI_INT_MASK_TX_FIFO_OIM_POS                        (1U)
#define SPI_INT_MASK_TX_FIFO_OIM_Len                        (1U)
#define SPI_INT_MASK_TX_FIFO_OIM_Msk                        (0x1UL << SPI_INT_MASK_TX_FIFO_OIM_POS)
#define SPI_INT_MASK_TX_FIFO_OIM                            SPI_INT_MASK_TX_FIFO_OIM_Msk

#define SPI_INT_MASK_RX_FIFO_UIM_POS                        (2U)
#define SPI_INT_MASK_RX_FIFO_UIM_Len                        (1U)
#define SPI_INT_MASK_RX_FIFO_UIM_Msk                        (0x1UL << SPI_INT_MASK_RX_FIFO_UIM_POS)
#define SPI_INT_MASK_RX_FIFO_UIM                            SPI_INT_MASK_RX_FIFO_UIM_Msk

#define SPI_INT_MASK_RX_FIFO_OIM_POS                        (3U)
#define SPI_INT_MASK_RX_FIFO_OIM_Len                        (1U)
#define SPI_INT_MASK_RX_FIFO_OIM_Msk                        (0x1UL << SPI_INT_MASK_RX_FIFO_OIM_POS)
#define SPI_INT_MASK_RX_FIFO_OIM                            SPI_INT_MASK_RX_FIFO_OIM_Msk

#define SPI_INT_MASK_RX_FIFO_FIM_POS                        (4U)
#define SPI_INT_MASK_RX_FIFO_FIM_Len                        (1U)
#define SPI_INT_MASK_RX_FIFO_FIM_Msk                        (0x1UL << SPI_INT_MASK_RX_FIFO_FIM_POS)
#define SPI_INT_MASK_RX_FIFO_FIM                            SPI_INT_MASK_RX_FIFO_FIM_Msk

#define SPI_INT_MASK_MULTI_M_CIM_POS                        (5U)
#define SPI_INT_MASK_MULTI_M_CIM_Len                        (1U)
#define SPI_INT_MASK_MULTI_M_CIM_Msk                        (0x1UL << SPI_INT_MASK_MULTI_M_CIM_POS)
#define SPI_INT_MASK_MULTI_M_CIM                            SPI_INT_MASK_MULTI_M_CIM_Msk

/*******************  Bit definition for SPI_INT_STAT register  *******************/
#define SPI_INT_STAT_TX_FIFO_EIS_POS                        (0U)
#define SPI_INT_STAT_TX_FIFO_EIS_Len                        (1U)
#define SPI_INT_STAT_TX_FIFO_EIS_Msk                        (0x1UL << SPI_INT_STAT_TX_FIFO_EIS_POS)
#define SPI_INT_STAT_TX_FIFO_EIS                            SPI_INT_STAT_TX_FIFO_EIS_Msk

#define SPI_INT_STAT_TX_FIFO_OIS_POS                        (1U)
#define SPI_INT_STAT_TX_FIFO_OIS_Len                        (1U)
#define SPI_INT_STAT_TX_FIFO_OIS_Msk                        (0x1UL << SPI_INT_STAT_TX_FIFO_OIS_POS)
#define SPI_INT_STAT_TX_FIFO_OIS                            SPI_INT_STAT_TX_FIFO_OIS_Msk

#define SPI_INT_STAT_RX_FIFO_UIS_POS                        (2U)
#define SPI_INT_STAT_RX_FIFO_UIS_Len                        (1U)
#define SPI_INT_STAT_RX_FIFO_UIS_Msk                        (0x1UL << SPI_INT_STAT_RX_FIFO_UIS_POS)
#define SPI_INT_STAT_RX_FIFO_UIS                            SPI_INT_STAT_RX_FIFO_UIS_Msk

#define SPI_INT_STAT_RX_FIFO_OIS_POS                        (3U)
#define SPI_INT_STAT_RX_FIFO_OIS_Len                        (1U)
#define SPI_INT_STAT_RX_FIFO_OIS_Msk                        (0x1UL << SPI_INT_STAT_RX_FIFO_OIS_POS)
#define SPI_INT_STAT_RX_FIFO_OIS                            SPI_INT_STAT_RX_FIFO_OIS_Msk

#define SPI_INT_STAT_RX_FIFO_FIS_POS                        (4U)
#define SPI_INT_STAT_RX_FIFO_FIS_Len                        (1U)
#define SPI_INT_STAT_RX_FIFO_FIS_Msk                        (0x1UL << SPI_INT_STAT_RX_FIFO_FIS_POS)
#define SPI_INT_STAT_RX_FIFO_FIS                            SPI_INT_STAT_RX_FIFO_FIS_Msk

#define SPI_INT_STAT_MULTI_M_CIS_POS                        (5U)
#define SPI_INT_STAT_MULTI_M_CIS_Len                        (1U)
#define SPI_INT_STAT_MULTI_M_CIS_Msk                        (0x1UL << SPI_INT_STAT_MULTI_M_CIS_POS)
#define SPI_INT_STAT_MULTI_M_CIS                            SPI_INT_STAT_MULTI_M_CIS_Msk

/*******************  Bit definition for SPI_RAW_INT_STAT register  *******************/
#define SPI_RAW_INT_STAT_TX_FIFO_ERIS_POS                   (0U)
#define SPI_RAW_INT_STAT_TX_FIFO_ERIS_Len                   (1U)
#define SPI_RAW_INT_STAT_TX_FIFO_ERIS_Msk                   (0x1UL << SPI_RAW_INT_STAT_TX_FIFO_ERIS_POS)
#define SPI_RAW_INT_STAT_TX_FIFO_ERIS                       SPI_RAW_INT_STAT_TX_FIFO_ERIS_Msk

#define SPI_RAW_INT_STAT_TX_FIFO_ORIS_POS                   (1U)
#define SPI_RAW_INT_STAT_TX_FIFO_ORIS_Len                   (1U)
#define SPI_RAW_INT_STAT_TX_FIFO_ORIS_Msk                   (0x1UL << SPI_RAW_INT_STAT_TX_FIFO_ORIS_POS)
#define SPI_RAW_INT_STAT_TX_FIFO_ORIS                       SPI_RAW_INT_STAT_TX_FIFO_ORIS_Msk

#define SPI_RAW_INT_STAT_RX_FIFO_URIS_POS                   (2U)
#define SPI_RAW_INT_STAT_RX_FIFO_URIS_Len                   (1U)
#define SPI_RAW_INT_STAT_RX_FIFO_URIS_Msk                   (0x1UL << SPI_RAW_INT_STAT_RX_FIFO_URIS_POS)
#define SPI_RAW_INT_STAT_RX_FIFO_URIS                       SPI_RAW_INT_STAT_RX_FIFO_URIS_Msk

#define SPI_RAW_INT_STAT_RX_FIFO_ORIS_POS                   (3U)
#define SPI_RAW_INT_STAT_RX_FIFO_ORIS_Len                   (1U)
#define SPI_RAW_INT_STAT_RX_FIFO_ORIS_Msk                   (0x1UL << SPI_RAW_INT_STAT_RX_FIFO_ORIS_POS)
#define SPI_RAW_INT_STAT_RX_FIFO_ORIS                       SPI_RAW_INT_STAT_RX_FIFO_ORIS_Msk

#define SPI_RAW_INT_STAT_RX_FIFO_FRIS_POS                   (4U)
#define SPI_RAW_INT_STAT_RX_FIFO_FRIS_Len                   (1U)
#define SPI_RAW_INT_STAT_RX_FIFO_FRIS_Msk                   (0x1UL << SPI_RAW_INT_STAT_RX_FIFO_FRIS_POS)
#define SPI_RAW_INT_STAT_RX_FIFO_FRIS                       SPI_RAW_INT_STAT_RX_FIFO_FRIS_Msk

#define SPI_RAW_INT_STAT_MULTI_M_CRIS_POS                   (5U)
#define SPI_RAW_INT_STAT_MULTI_M_CRIS_Len                   (1U)
#define SPI_RAW_INT_STAT_MULTI_M_CRIS_Msk                   (0x1UL << SPI_RAW_INT_STAT_MULTI_M_CRIS_POS)
#define SPI_RAW_INT_STAT_MULTI_M_CRIS                       SPI_RAW_INT_STAT_MULTI_M_CRIS_Msk

/*******************  Bit definition for SPI_TX_FIFO_OIC register  *******************/
#define SPI_TX_FIFO_OIC_TX_FIFO_OIC_POS                     (0U)
#define SPI_TX_FIFO_OIC_TX_FIFO_OIC_Len                     (1U)
#define SPI_TX_FIFO_OIC_TX_FIFO_OIC_Msk                     (0x1UL << SPI_TX_FIFO_OIC_TX_FIFO_OIC_POS)
#define SPI_TX_FIFO_OIC_TX_FIFO_OIC                         SPI_TX_FIFO_OIC_TX_FIFO_OIC_Msk

/*******************  Bit definition for SPI_RX_FIFO_OIC register  *******************/
#define SPI_RX_FIFO_OIC_RX_FIFO_OIC_POS                     (0U)
#define SPI_RX_FIFO_OIC_RX_FIFO_OIC_Len                     (1U)
#define SPI_RX_FIFO_OIC_RX_FIFO_OIC_Msk                     (0x1UL << SPI_RX_FIFO_OIC_RX_FIFO_OIC_POS)
#define SPI_RX_FIFO_OIC_RX_FIFO_OIC                         SPI_RX_FIFO_OIC_RX_FIFO_OIC_Msk

/*******************  Bit definition for SPI_RX_FIFO_UIC register  *******************/
#define SPI_RX_FIFO_UIC_RX_FIFO_UIC_POS                     (0U)
#define SPI_RX_FIFO_UIC_RX_FIFO_UIC_Len                     (1U)
#define SPI_RX_FIFO_UIC_RX_FIFO_UIC_Msk                     (0x1UL << SPI_RX_FIFO_UIC_RX_FIFO_UIC_POS)
#define SPI_RX_FIFO_UIC_RX_FIFO_UIC                         SPI_RX_FIFO_UIC_RX_FIFO_UIC_Msk

/*******************  Bit definition for SPI_MULTI_M_IC register  *******************/
#define SPI_MULTI_M_IC_MULTI_M_IC_POS                       (0U)
#define SPI_MULTI_M_IC_MULTI_M_IC_Len                       (1U)
#define SPI_MULTI_M_IC_MULTI_M_IC_Msk                       (0x1UL << SPI_MULTI_M_IC_MULTI_M_IC_POS)
#define SPI_MULTI_M_IC_MULTI_M_IC                           SPI_MULTI_M_IC_MULTI_M_IC_Msk

/*******************  Bit definition for SPI_INT_CLR register  *******************/
#define SPI_INT_CLR_INT_CLR_POS                             (0U)
#define SPI_INT_CLR_INT_CLR_Len                             (1U)
#define SPI_INT_CLR_INT_CLR_Msk                             (0x1UL << SPI_INT_CLR_INT_CLR_POS)
#define SPI_INT_CLR_INT_CLR                                 SPI_INT_CLR_INT_CLR_Msk

/*******************  Bit definition for SPI_DMA_CTRL register  *******************/
#define SPI_DMA_CTRL_RX_DMA_EN_POS                          (0U)
#define SPI_DMA_CTRL_RX_DMA_EN_Len                          (1U)
#define SPI_DMA_CTRL_RX_DMA_EN_Msk                          (0x1UL << SPI_DMA_CTRL_RX_DMA_EN_POS)
#define SPI_DMA_CTRL_RX_DMA_EN                              SPI_DMA_CTRL_RX_DMA_EN_Msk

#define SPI_DMA_CTRL_TX_DMA_EN_POS                          (1U)
#define SPI_DMA_CTRL_TX_DMA_EN_Len                          (1U)
#define SPI_DMA_CTRL_TX_DMA_EN_Msk                          (0x1UL << SPI_DMA_CTRL_TX_DMA_EN_POS)
#define SPI_DMA_CTRL_TX_DMA_EN                              SPI_DMA_CTRL_TX_DMA_EN_Msk

/*******************  Bit definition for SPI_DMA_TX_DL register  *******************/
#define SPI_DMA_TX_DL_DMA_TX_DL_POS                         (0U)
#define SPI_DMA_TX_DL_DMA_TX_DL_Len                         (4U)
#define SPI_DMA_TX_DL_DMA_TX_DL_Msk                         (0xFUL << SPI_DMA_TX_DL_DMA_TX_DL_POS)
#define SPI_DMA_TX_DL_DMA_TX_DL                             SPI_DMA_TX_DL_DMA_TX_DL_Msk

/*******************  Bit definition for SPI_DMA_RX_DL register  *******************/
#define SPI_DMA_RX_DL_DMA_RX_DL_POS                         (0U)
#define SPI_DMA_RX_DL_DMA_RX_DL_Len                         (4U)
#define SPI_DMA_RX_DL_DMA_RX_DL_Msk                         (0xFUL << SPI_DMA_RX_DL_DMA_RX_DL_POS)
#define SPI_DMA_RX_DL_DMA_RX_DL                             SPI_DMA_RX_DL_DMA_RX_DL_Msk

/*******************  Bit definition for SPI_DATA register  *******************/
#define SPI_DATA_DATA_POS                                   (0U)
#define SPI_DATA_DATA_Len                                   (32U)
#define SPI_DATA_DATA_Msk                                   (0xFFFFFFFFUL << SPI_DATA_DATA_POS)
#define SPI_DATA_DATA                                       SPI_DATA_DATA_Msk

/*******************  Bit definition for SPI_RX_SAMPLEDLY register  *******************/
#define SPI_RX_SAMPLEDLY_POS                                (0U)
#define SPI_RX_SAMPLEDLY_Len                                (3U)
#define SPI_RX_SAMPLEDLY_Msk                                (0x07UL << SPI_RX_SAMPLEDLY_POS)
#define SPI_RX_SAMPLEDLY                                    SPI_RX_SAMPLEDLY_Msk


/* ================================================================================================================= */
/* ================                                       TIMER                                     ================ */
/* ================================================================================================================= */
/*******************  Bit definition for TIMER_CTRL register  *******************/
#define TIMER_CTRL_EN_Pos                                   (0U)
#define TIMER_CTRL_EN_Len                                   (1U)
#define TIMER_CTRL_EN_Msk                                   (0x1U << TIMER_CTRL_EN_Pos)
#define TIMER_CTRL_EN                                       TIMER_CTRL_EN_Msk

#define TIMER_CH0_EDGE_DET_Pos                              (1U)
#define TIMER_CH0_EDGE_DET_Len                              (2U)
#define TIMER_CH0_EDGE_DET_Msk                              (0x3U << TIMER_CH0_EDGE_DET_Pos)
#define TIMER_CH0_EDGE_DET                                  TIMER_CH0_EDGE_DET_Msk

#define TIMER_CH1_EDGE_DET_Pos                              (3U)
#define TIMER_CH1_EDGE_DET_Len                              (2U)
#define TIMER_CH1_EDGE_DET_Msk                              (0x3U << TIMER_CH1_EDGE_DET_Pos)
#define TIMER_CH1_EDGE_DET                                  TIMER_CH1_EDGE_DET_Msk

#define TIMER_CH2_EDGE_DET_Pos                              (5U)
#define TIMER_CH2_EDGE_DET_Len                              (2U)
#define TIMER_CH2_EDGE_DET_Msk                              (0x3U << TIMER_CH2_EDGE_DET_Pos)
#define TIMER_CH2_EDGE_DET                                  TIMER_CH2_EDGE_DET_Msk

#define TIMER_CH3_EDGE_DET_Pos                              (7U)
#define TIMER_CH3_EDGE_DET_Len                              (2U)
#define TIMER_CH3_EDGE_DET_Msk                              (0x3U << TIMER_CH3_EDGE_DET_Pos)
#define TIMER_CH3_EDGE_DET                                  TIMER_CH3_EDGE_DET_Msk

#define TIMER_CH0_PIN_SELECT_Pos                            (9U)
#define TIMER_CH0_PIN_SELECT_Len                            (5U)
#define TIMER_CH0_PIN_SELECT_Msk                            (0x1FU << TIMER_CH0_PIN_SELECT_Pos)
#define TIMER_CH0_PIN_SELECT                                TIMER_CH0_PIN_SELECT_Msk

#define TIMER_CH1_PIN_SELECT_Pos                            (14U)
#define TIMER_CH1_PIN_SELECT_Len                            (5U)
#define TIMER_CH1_PIN_SELECT_Msk                            (0x1FU << TIMER_CH1_PIN_SELECT_Pos)
#define TIMER_CH1_PIN_SELECT                                TIMER_CH1_PIN_SELECT_Msk

#define TIMER_CH2_PIN_SELECT_Pos                            (19U)
#define TIMER_CH2_PIN_SELECT_Len                            (5U)
#define TIMER_CH2_PIN_SELECT_Msk                            (0x1FU << TIMER_CH2_PIN_SELECT_Pos)
#define TIMER_CH2_PIN_SELECT                                TIMER_CH2_PIN_SELECT_Msk

#define TIMER_CH3_PIN_SELECT_Pos                            (24U)
#define TIMER_CH3_PIN_SELECT_Len                            (5U)
#define TIMER_CH3_PIN_SELECT_Msk                            (0x1FU << TIMER_CH3_PIN_SELECT_Pos)
#define TIMER_CH3_PIN_SELECT                                TIMER_CH3_PIN_SELECT_Msk

#define TIMER_BLE_PULSE_CTRL_Pos                            (29U)
#define TIMER_BLE_PULSE_CTRL_Len                            (1U)
#define TIMER_BLE_PULSE_CTRL_Msk                            (0x1U << TIMER_BLE_PULSE_CTRL_Pos)
#define TIMER_BLE_PULSE_CTRL                                TIMER_BLE_PULSE_CTRL_Msk

/*******************  Bit definition for TIMER_VALUE register  ******************/
#define TIMER_VALUE_VALUE_Pos                               (0U)
#define TIMER_VALUE_VALUE_Len                               (32U)
#define TIMER_VALUE_VALUE_Msk                               (0xFFFFFFFFU)
#define TIMER_VALUE_VALUE                                   TIMER_VALUE_VALUE_Msk

/*******************  Bit definition for TIMER_RELOAD register  *****************/
#define TIMER_RELOAD_RELOAD_Pos                             (0U)
#define TIMER_RELOAD_RELOAD_Len                             (32U)
#define TIMER_RELOAD_RELOAD_Msk                             (0xFFFFFFFFU)
#define TIMER_RELOAD_RELOAD                                 TIMER_RELOAD_RELOAD_Msk

/*******************  Bit definition for TIMER_INT_EN register  *****************/
#define TIMER_COUNTDONE_INT_EN_Pos                          (0U)
#define TIMER_COUNTDONE_INT_EN_Len                          (1U)
#define TIMER_COUNTDONE_INT_EN_Msk                          (0x1U << TIMER_COUNTDONE_INT_EN_Pos)
#define TIMER_COUNTDONE_INT_EN                              TIMER_COUNTDONE_INT_EN_Msk

#define TIMER_CH0_INT_EN_Pos                                (1U)
#define TIMER_CH0_INT_EN_Len                                (1U)
#define TIMER_CH0_INT_EN_Msk                                (0x1U << TIMER_CH0_INT_EN_Pos)
#define TIMER_CH0_INT_EN                                    TIMER_CH0_INT_EN_Msk

#define TIMER_CH1_INT_EN_Pos                                (2U)
#define TIMER_CH1_INT_EN_Len                                (1U)
#define TIMER_CH1_INT_EN_Msk                                (0x1U << TIMER_CH1_INT_EN_Pos)
#define TIMER_CH1_INT_EN                                    TIMER_CH1_INT_EN_Msk

#define TIMER_CH2_INT_EN_Pos                                (3U)
#define TIMER_CH2_INT_EN_Len                                (1U)
#define TIMER_CH2_INT_EN_Msk                                (0x1U << TIMER_CH2_INT_EN_Pos)
#define TIMER_CH2_INT_EN                                    TIMER_CH2_INT_EN_Msk

#define TIMER_CH3_INT_EN_Pos                                (4U)
#define TIMER_CH3_INT_EN_Len                                (1U)
#define TIMER_CH3_INT_EN_Msk                                (0x1U << TIMER_CH3_INT_EN_Pos)
#define TIMER_CH3_INT_EN                                    TIMER_CH3_INT_EN_Msk

#define TIMER_BLEPULSE1_INT_EN_Pos                          (5U)
#define TIMER_BLEPULSE1_INT_EN_Len                          (1U)
#define TIMER_BLEPULSE1_INT_EN_Msk                          (0x1U << TIMER_BLEPULSE1_INT_EN_Pos)
#define TIMER_BLEPULSE1_INT_EN                              TIMER_BLEPULSE1_INT_EN_Msk

#define TIMER_BLEPULSE2_INT_EN_Pos                          (6U)
#define TIMER_BLEPULSE2_INT_EN_Len                          (1U)
#define TIMER_BLEPULSE2_INT_EN_Msk                          (0x1U << TIMER_BLEPULSE2_INT_EN_Pos)
#define TIMER_BLEPULSE2_INT_EN                              TIMER_BLEPULSE2_INT_EN_Msk

/*******************  Bit definition for TIMER_INT_STAT register  *****************/
#define TIMER_COUNTDONE_INT_STAT_Pos                        (0U)
#define TIMER_COUNTDONE_INT_STAT_Len                        (1U)
#define TIMER_COUNTDONE_INT_STAT_Msk                        (0x1U << TIMER_COUNTDONE_INT_STAT_Pos)
#define TIMER_COUNTDONE_INT_STAT                            TIMER_COUNTDONE_INT_STAT_Msk

#define TIMER_CH0_INT_STAT_Pos                              (1U)
#define TIMER_CH0_INT_STAT_Len                              (1U)
#define TIMER_CH0_INT_STAT_Msk                              (0x1U << TIMER_CH0_INT_STAT_Pos)
#define TIMER_CH0_INT_STAT                                  TIMER_CH0_INT_STAT_Msk

#define TIMER_CH1_INT_STAT_Pos                              (2U)
#define TIMER_CH1_INT_STAT_Len                              (1U)
#define TIMER_CH1_INT_STAT_Msk                              (0x1U << TIMER_CH1_INT_STAT_Pos)
#define TIMER_CH1_INT_STAT                                  TIMER_CH1_INT_STAT_Msk

#define TIMER_CH2_INT_STAT_Pos                              (3U)
#define TIMER_CH2_INT_STAT_Len                              (1U)
#define TIMER_CH2_INT_STAT_Msk                              (0x1U << TIMER_CH2_INT_STAT_Pos)
#define TIMER_CH2_INT_STAT                                  TIMER_CH2_INT_STAT_Msk

#define TIMER_CH3_INT_STAT_Pos                              (4U)
#define TIMER_CH3_INT_STAT_Len                              (1U)
#define TIMER_CH3_INT_STAT_Msk                              (0x1U << TIMER_CH3_INT_STAT_Pos)
#define TIMER_CH3_INT_STAT                                  TIMER_CH3_INT_STAT_Msk

#define TIMER_BLEPULSE1_INT_STAT_Pos                        (5U)
#define TIMER_BLEPULSE1_INT_STAT_Len                        (1U)
#define TIMER_BLEPULSE1_INT_STAT_Msk                        (0x1U << TIMER_BLEPULSE1_INT_STAT_Pos)
#define TIMER_BLEPULSE1_INT_STAT                            TIMER_BLEPULSE1_INT_STAT_Msk

#define TIMER_BLEPULSE2_INT_STAT_Pos                        (6U)
#define TIMER_BLEPULSE2_INT_STAT_Len                        (1U)
#define TIMER_BLEPULSE2_INT_STAT_Msk                        (0x1U << TIMER_BLEPULSE2_INT_STAT_Pos)
#define TIMER_BLEPULSE2_INT_STAT                            TIMER_BLEPULSE2_INT_STAT_Msk

#define TIMER_INT_STAT_Pos                                  (0U)
#define TIMER_INT_STAT_Len                                  (7U)
#define TIMER_INT_STAT_Msk                                  (0x7FU << TIMER_INT_STAT_Pos)
#define TIMER_INT_STAT                                      TIMER_INT_STAT_Msk

/*******************  Bit definition for TIMER_CHANNEL0_VAL register  *****************/
#define TIMER_CH0_VAL_Pos                                   (0U)
#define TIMER_CH0_VAL_Len                                   (32U)
#define TIMER_CH0_VAL_Msk                                   (0xFFFFFFFFU << TIMER_CH0_VAL_Pos)
#define TIMER_CH0_VAL                                       TIMER_CH0_VAL_Msk

/*******************  Bit definition for TIMER_CHANNEL1_VAL register  *****************/
#define TIMER_CH1_VAL_Pos                                   (0U)
#define TIMER_CH1_VAL_Len                                   (32U)
#define TIMER_CH1_VAL_Msk                                   (0xFFFFFFFFU << TIMER_CH1_VAL_Pos)
#define TIMER_CH1_VAL                                       TIMER_CH1_VAL_Msk

/*******************  Bit definition for TIMER_CHANNEL2_VAL register  *****************/
#define TIMER_CH2_VAL_Pos                                   (0U)
#define TIMER_CH2_VAL_Len                                   (32U)
#define TIMER_CH2_VAL_Msk                                   (0xFFFFFFFFU << TIMER_CH2_VAL_Pos)
#define TIMER_CH2_VAL                                       TIMER_CH2_VAL_Msk

/*******************  Bit definition for TIMER_CHANNEL3_VAL register  *****************/
#define TIMER_CH3_VAL_Pos                                   (0U)
#define TIMER_CH3_VAL_Len                                   (32U)
#define TIMER_CH3_VAL_Msk                                   (0xFFFFFFFFU << TIMER_CH3_VAL_Pos)
#define TIMER_CH3_VAL                                       TIMER_CH3_VAL_Msk

/*******************  Bit definition for TIMER_BLE_COUNTVAL1 register  *****************/
#define TIMER_BLE_VAL1_Pos                                  (0U)
#define TIMER_BLE_VAL1_Len                                  (32U)
#define TIMER_BLE_VAL1_Msk                                  (0xFFFFFFFFU << TIMER_BLE_VAL1_Pos)
#define TIMER_BLE_VAL1                                      TIMER_BLE_VAL1_Msk

/*******************  Bit definition for TIMER_BLE_COUNTVAL2 register  *****************/
#define TIMER_BLE_VAL2_Pos                                  (0U)
#define TIMER_BLE_VAL2_Len                                  (32U)
#define TIMER_BLE_VAL2_Msk                                  (0xFFFFFFFFU << TIMER_BLE_VAL2_Pos)
#define TIMER_BLE_VAL2                                      TIMER_BLE_VAL2_Msk

/*******************  Bit definition for TIMER_BLE_PULSEWIDTH register  *****************/
#define TIMER_BLE_PLS_Pos                                   (0U)
#define TIMER_BLE_PLS_Len                                   (6U)
#define TIMER_BLE_PLS_Msk                                   (0x3FU << TIMER_BLE_PLS_Pos)
#define TIMER_BLE_PLS                                       TIMER_BLE_PLS_Msk


/* ================================================================================================================= */
/* ================                                       UART                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for UART_RBR register  *******************/
#define UART_RBR_RBR_Pos                                    (0U)
#define UART_RBR_RBR_Len                                    (8U)
#define UART_RBR_RBR_Msk                                    (0xFFU << UART_RBR_RBR_Pos)
#define UART_RBR_RBR                                        UART_RBR_RBR_Msk  /**< Receive Buffer Register */

/*******************  Bit definition for UART_DLL register  *******************/
#define UART_DLL_DLL_Pos                                    (0U)
#define UART_DLL_DLL_Len                                    (8U)
#define UART_DLL_DLL_Msk                                    (0xFFU << UART_DLL_DLL_Pos)
#define UART_DLL_DLL                                        UART_DLL_DLL_Msk  /**< Divisor Latch (Low) */

/*******************  Bit definition for UART_THR register  *******************/
#define UART_THR_THR_Pos                                    (0U)
#define UART_THR_THR_Len                                    (8U)
#define UART_THR_THR_Msk                                    (0xFFU << UART_THR_THR_Pos)
#define UART_THR_THR                                        UART_THR_THR_Msk  /**< Transmit Holding Register */

/*******************  Bit definition for UART_DLH register  *******************/
#define UART_DLH_DLH_Pos                                    (0U)
#define UART_DLH_DLH_Len                                    (8U)
#define UART_DLH_DLH_Msk                                    (0xFFU << UART_DLH_DLH_Pos)
#define UART_DLH_DLH                                        UART_DLH_DLH_Msk  /**< Divisor Latch (High) */

/*******************  Bit definition for UART_IER register  *******************/
#define UART_IER_PTIME_Pos                                  (7U)
#define UART_IER_PTIME_Len                                  (1U)
#define UART_IER_PTIME_Msk                                  (0x1U << UART_IER_PTIME_Pos)
#define UART_IER_PTIME                                      UART_IER_PTIME_Msk  /**< Programmable THRE Interrupt Mode Enable */

#define UART_IER_ELCOLR_Pos                                 (4U)
#define UART_IER_ELCOLR_Len                                 (1U)
#define UART_IER_ELCOLR_Msk                                 (0x1U << UART_IER_ELCOLR_Pos)
#define UART_IER_ELCOLR                                     UART_IER_ELCOLR_Msk /**< Enable Auto Clear LSR Register by read RBR/LSR, read only */

#define UART_IER_EDSSI_Pos                                  (3U)
#define UART_IER_EDSSI_Len                                  (1U)
#define UART_IER_EDSSI_Msk                                  (0x1U << UART_IER_EDSSI_Pos)
#define UART_IER_EDSSI                                      UART_IER_EDSSI_Msk  /**< Enable Modem Status Interrupt */

#define UART_IER_ERLS_Pos                                   (2U)
#define UART_IER_ERLS_Len                                   (1U)
#define UART_IER_ERLS_Msk                                   (0x1U << UART_IER_ERLS_Pos)
#define UART_IER_ERLS                                       UART_IER_ERLS_Msk   /**< Enable Receiver Line Status Interrupt */

#define UART_IER_ETBEI_Pos                                  (1U)
#define UART_IER_ETBEI_Len                                  (1U)
#define UART_IER_ETBEI_Msk                                  (0x1U << UART_IER_ETBEI_Pos)
#define UART_IER_ETBEI                                      UART_IER_ETBEI_Msk  /**< Enable Transmit Holding Register Empty Interrupt */

#define UART_IER_ERBFI_Pos                                  (0U)
#define UART_IER_ERBFI_Len                                  (1U)
#define UART_IER_ERBFI_Msk                                  (0x1U << UART_IER_ERBFI_Pos)
#define UART_IER_ERBFI                                      UART_IER_ERBFI_Msk  /**< Enable Received Data Available Interrupt */

/*******************  Bit definition for UART_FCR register  *******************/
#define UART_FCR_RT_Pos                                     (6U)
#define UART_FCR_RT_Len                                     (2U)
#define UART_FCR_RT_Msk                                     (0x3U << UART_FCR_RT_Pos)
#define UART_FCR_RT                                         UART_FCR_RT_Msk             /**< RCVR Trigger */
#define UART_FCR_RT_CHAR_1                                  (0x0U << UART_FCR_RT_Pos)  /**< RX FIFO 1 Char */
#define UART_FCR_RT_QUARTER_FULL                            (0x1U << UART_FCR_RT_Pos)  /**< RX FIFO Quater Full*/
#define UART_FCR_RT_HALF_FULL                               (0x2U << UART_FCR_RT_Pos)  /**< RX FIFO Half Full */
#define UART_FCR_RT_FULL_2                                  (0x3U << UART_FCR_RT_Pos)  /**< RX FIFO 2 less than Full */

#define UART_FCR_TET_Pos                                    (4U)
#define UART_FCR_TET_Len                                    (2U)
#define UART_FCR_TET_Msk                                    (0x3U << UART_FCR_TET_Pos)
#define UART_FCR_TET                                        UART_FCR_TET_Msk            /**< TX Empty Trigger */
#define UART_FCR_TET_EMPTY                                  (0x0U << UART_FCR_TET_Pos)   /**< TX FIFO Empty */
#define UART_FCR_TET_CHAR_2                                 (0x1U << UART_FCR_TET_Pos)   /**< TX FIFO 2 chars */
#define UART_FCR_TET_QUARTER_FULL                           (0x2U << UART_FCR_TET_Pos)   /**< TX FIFO Quater Full */
#define UART_FCR_TET_HALF_FULL                              (0x3U << UART_FCR_TET_Pos)   /**< TX FIFO Half Full */

#define UART_FCR_XFIFOR_Pos                                 (2U)
#define UART_FCR_XFIFOR_Len                                 (1U)
#define UART_FCR_XFIFOR_Msk                                 (0x1U << UART_FCR_XFIFOR_Pos)
#define UART_FCR_XFIFOR                                     UART_FCR_XFIFOR_Msk /**< XMIT FIFO Reset */

#define UART_FCR_RFIFOR_Pos                                 (1U)
#define UART_FCR_RFIFOR_Len                                 (1U)
#define UART_FCR_RFIFOR_Msk                                 (0x1U << UART_FCR_RFIFOR_Pos)
#define UART_FCR_RFIFOR                                     UART_FCR_RFIFOR_Msk /**< RCVR FIFO Reset */

#define UART_FCR_FIFOE_Pos                                  (0U)
#define UART_FCR_FIFOE_Len                                  (1U)
#define UART_FCR_FIFOE_Msk                                  (0x1U << UART_FCR_FIFOE_Pos)
#define UART_FCR_FIFOE                                      UART_FCR_FIFOE_Msk  /**< FIFO Enable */

/*******************  Bit definition for UART_IIR register  *******************/
#define UART_IIR_IID_Pos                                    (0U)
#define UART_IIR_IID_Len                                    (4U)
#define UART_IIR_IID_Msk                                    (0xFU << UART_IIR_IID_Pos)
#define UART_IIR_IID                                        UART_IIR_IID_Msk            /**< Interrupt ID */
#define UART_IIR_IID_MS                                     (0x0U << UART_IIR_IID_Pos)  /**< Modem Status */
#define UART_IIR_IID_NIP                                    (0x1U << UART_IIR_IID_Pos)  /**< No Interrupt Pending */
#define UART_IIR_IID_THRE                                   (0x2U << UART_IIR_IID_Pos)  /**< THR Empty */
#define UART_IIR_IID_RDA                                    (0x4U << UART_IIR_IID_Pos)  /**< Received Data Available */
#define UART_IIR_IID_RLS                                    (0x6U << UART_IIR_IID_Pos)  /**< Receiver Line Status */
#define UART_IIR_IID_CTO                                    (0xCU << UART_IIR_IID_Pos)  /**< Character Timeout */

/*******************  Bit definition for UART_LCR register  *******************/
#define UART_LCR_DLAB_Pos                                   (7U)
#define UART_LCR_DLAB_Len                                   (1U)
#define UART_LCR_DLAB_Msk                                   (0x1U << UART_LCR_DLAB_Pos)
#define UART_LCR_DLAB                                       UART_LCR_DLAB_Msk           /**< Divisor Latch Access */

#define UART_LCR_BC_Pos                                     (6U)
#define UART_LCR_BC_Len                                     (1U)
#define UART_LCR_BC_Msk                                     (0x1U << UART_LCR_BC_Pos)
#define UART_LCR_BC                                         UART_LCR_BC_Msk             /**< Break Control */

#define UART_LCR_PARITY_Pos                                 (3U)
#define UART_LCR_PARITY_Len                                 (3U)
#define UART_LCR_PARITY_Msk                                 (0x7U << UART_LCR_PARITY_Pos)
#define UART_LCR_PARITY                                     UART_LCR_PARITY_Msk             /**< Parity, SP,EPS,PEN bits */
#define UART_LCR_PARITY_NONE                                (0x0U << UART_LCR_PARITY_Pos)   /**< Parity none */
#define UART_LCR_PARITY_ODD                                 (0x1U << UART_LCR_PARITY_Pos)   /**< Parity odd */
#define UART_LCR_PARITY_EVEN                                (0x3U << UART_LCR_PARITY_Pos)   /**< Parity even */
#define UART_LCR_PARITY_SP0                                 (0x5U << UART_LCR_PARITY_Pos)   /**< Parity stick 0 */
#define UART_LCR_PARITY_SP1                                 (0x7U << UART_LCR_PARITY_Pos)   /**< Parity stick 1 */

#define UART_LCR_STOP_Pos                                   (2U)
#define UART_LCR_STOP_Msk                                   (0x1U << UART_LCR_STOP_Pos)
#define UART_LCR_STOP                                       UART_LCR_STOP_Msk               /**< Stop bit */
#define UART_LCR_STOP_1                                     (0x0U << UART_LCR_STOP_Pos)     /**< Stop bit 1 */
#define UART_LCR_STOP_1_5                                   (0x1U << UART_LCR_STOP_Pos)     /**< Stop bit 1.5 (DLS = 0) */
#define UART_LCR_STOP_2                                     (0x1U << UART_LCR_STOP_Pos)     /**< Stop bit 2 (DLS != 0) */

#define UART_LCR_DLS_Pos                                    (0U)
#define UART_LCR_DLS_Msk                                    (0x3U << UART_LCR_DLS_Pos)
#define UART_LCR_DLS                                        UART_LCR_DLS_Msk                /**< Data Length Select */
#define UART_LCR_DLS_5                                      (0x0U << UART_LCR_DLS_Pos)      /**< Data bits 5 */
#define UART_LCR_DLS_6                                      (0x1U << UART_LCR_DLS_Pos)      /**< Data bits 6 */
#define UART_LCR_DLS_7                                      (0x2U << UART_LCR_DLS_Pos)      /**< Data bits 7 */
#define UART_LCR_DLS_8                                      (0x3U << UART_LCR_DLS_Pos)      /**< Data bits 8 */

/*******************  Bit definition for UART_MCR register  *******************/
#define UART_MCR_SIRE_Pos                                   (6U)
#define UART_MCR_SIRE_Len                                   (1U)
#define UART_MCR_SIRE_Msk                                   (0x1 << UART_MCR_SIRE_Pos)
#define UART_MCR_SIRE                                       UART_MCR_SIRE_Msk      /**< SIR mode enable */

#define UART_MCR_AFCE_Pos                                   (5U)
#define UART_MCR_AFCE_Len                                   (1U)
#define UART_MCR_AFCE_Msk                                   (0x1U << UART_MCR_AFCE_Pos)
#define UART_MCR_AFCE                                       UART_MCR_AFCE_Msk       /**< Auto flow contrl enable */

#define UART_MCR_LOOPBACK_Pos                               (4U)
#define UART_MCR_LOOPBACK_Len                               (1U)
#define UART_MCR_LOOPBACK_Msk                               (0x1U << UART_MCR_LOOPBACK_Pos)
#define UART_MCR_LOOPBACK                                   UART_MCR_LOOPBACK_Msk   /**< LoopBack */

#define UART_MCR_RTS_Pos                                    (1U)
#define UART_MCR_RTS_Len                                    (1U)
#define UART_MCR_RTS_Msk                                    (0x1U << UART_MCR_RTS_Pos)
#define UART_MCR_RTS                                        UART_MCR_RTS_Msk        /**< Request To Send */

/*******************  Bit definition for UART_LSR register  *******************/
#define UART_LSR_RFE_Pos                                    (7U)
#define UART_LSR_RFE_Len                                    (1U)
#define UART_LSR_RFE_Msk                                    (0x1U << UART_LSR_RFE_Pos)
#define UART_LSR_RFE                                        UART_LSR_RFE_Msk    /**< Receiver FIFO Error */

#define UART_LSR_TEMT_Pos                                   (6U)
#define UART_LSR_TEMT_Len                                   (1U)
#define UART_LSR_TEMT_Msk                                   (0x1U << UART_LSR_TEMT_Pos)
#define UART_LSR_TEMT                                       UART_LSR_TEMT_Msk   /**< Transmitter Empty */

#define UART_LSR_THRE_Pos                                   (5U)
#define UART_LSR_THRE_Len                                   (1U)
#define UART_LSR_THRE_Msk                                   (0x1U << UART_LSR_THRE_Pos)
#define UART_LSR_THRE                                       UART_LSR_THRE_Msk   /**< Transmit Holding Register Empty */

#define UART_LSR_BI_Pos                                     (4U)
#define UART_LSR_BI_Len                                     (1U)
#define UART_LSR_BI_Msk                                     (0x1U << UART_LSR_BI_Pos)
#define UART_LSR_BI                                         UART_LSR_BI_Msk     /**< Break Interrupt */

#define UART_LSR_FE_Pos                                     (3U)
#define UART_LSR_FE_Len                                     (1U)
#define UART_LSR_FE_Msk                                     (0x1U << UART_LSR_FE_Pos)
#define UART_LSR_FE                                         UART_LSR_FE_Msk     /**< Framing Error */

#define UART_LSR_PE_Pos                                     (2U)
#define UART_LSR_PE_Len                                     (1U)
#define UART_LSR_PE_Msk                                     (0x1U << UART_LSR_PE_Pos)
#define UART_LSR_PE                                         UART_LSR_PE_Msk     /**< Parity Error */

#define UART_LSR_OE_Pos                                     (1U)
#define UART_LSR_OE_Len                                     (1U)
#define UART_LSR_OE_Msk                                     (0x1U << UART_LSR_OE_Pos)
#define UART_LSR_OE                                         UART_LSR_OE_Msk     /**< Overrun error */

#define UART_LSR_DR_Pos                                     (0U)
#define UART_LSR_DR_Msk                                     (0x1U << UART_LSR_DR_Pos)
#define UART_LSR_DR                                         UART_LSR_DR_Msk     /**< Data Ready */

/*******************  Bit definition for UART_MSR register  *******************/
#define UART_MSR_CTS_Pos                                    (4U)
#define UART_MSR_CTS_Len                                    (1U)
#define UART_MSR_CTS_Msk                                    (0x1U << UART_MSR_CTS_Pos)
#define UART_MSR_CTS                                        UART_MSR_CTS_Msk    /**< Clear To Send */

#define UART_MSR_DCTS_Pos                                   (0U)
#define UART_MSR_DCTS_Len                                   (1U)
#define UART_MSR_DCTS_Msk                                   (0x1U << UART_MSR_DCTS_Pos)
#define UART_MSR_DCTS                                       UART_MSR_DCTS_Msk   /**< Delta Clear To Send */

/*******************  Bit definition for UART_USR register  *******************/
#define UART_USR_RFF_Pos                                    (4U)
#define UART_USR_RFF_Len                                    (1U)
#define UART_USR_RFF_Msk                                    (0x1U << UART_USR_RFF_Pos)
#define UART_USR_RFF                                        UART_USR_RFF_Msk    /**< Receive FIFO Full */

#define UART_USR_RFNE_Pos                                   (3U)
#define UART_USR_RFNE_Len                                   (1U)
#define UART_USR_RFNE_Msk                                   (0x1U << UART_USR_RFNE_Pos)
#define UART_USR_RFNE                                       UART_USR_RFNE_Msk   /**< Receive FIFO Not Empty */

#define UART_USR_TFE_Pos                                    (2U)
#define UART_USR_TFE_Len                                    (1U)
#define UART_USR_TFE_Msk                                    (0x1U << UART_USR_TFE_Pos)
#define UART_USR_TFE                                        UART_USR_TFE_Msk    /**< Transmit FIFO Empty */

#define UART_USR_TFNF_Pos                                   (1U)
#define UART_USR_TFNF_Len                                   (1U)
#define UART_USR_TFNF_Msk                                   (0x1U << UART_USR_TFNF_Pos)
#define UART_USR_TFNF                                       UART_USR_TFNF_Msk   /**< Transmit FIFO Not Full */

/*******************  Bit definition for UART_TFL register  *******************/
/* Transmit FIFO Level bits */
#define UART_TFL_TFL_Pos                                    (0U)
#define UART_TFL_TFL_Len                                    (7U)
#define UART_TFL_TFL_Msk                                    (0x7FU << UART_TFL_TFL_Pos)
#define UART_TFL_TFL                                        UART_TFL_TFL_Msk    /**< Transmit FIFO Level */

/*******************  Bit definition for UART_RFL register  *******************/
/* Receive FIFO Level bits */
#define UART_RFL_RFL_Pos                                    (0U)
#define UART_RFL_RFL_Len                                    (7U)
#define UART_RFL_RFL_Msk                                    (0x7FU << UART_RFL_RFL_Pos)
#define UART_RFL_RFL                                        UART_RFL_RFL_Msk    /**< Receive FIFO Level */

/*******************  Bit definition for UART_SRR register  *******************/
/* XMIT FIFO Reset bit */
#define UART_SRR_XFR_Pos                                    (2U)
#define UART_SRR_XFR_Len                                    (1U)
#define UART_SRR_XFR_Msk                                    (0x1U << UART_SRR_XFR_Pos)
#define UART_SRR_XFR                                        UART_SRR_XFR_Msk    /**< XMIT FIFO Reset */

/* RCVR FIFO Reset bit */
#define UART_SRR_RFR_Pos                                    (1U)
#define UART_SRR_RFR_Len                                    (1U)
#define UART_SRR_RFR_Msk                                    (0x1U << UART_SRR_RFR_Pos)
#define UART_SRR_RFR                                        UART_SRR_RFR_Msk    /**< RCVR FIFO Reset */

/* UART Reset Enable bit */
#define UART_SRR_UR_Pos                                     (0U)
#define UART_SRR_UR_Len                                     (1U)
#define UART_SRR_UR_Msk                                     (0x1U << UART_SRR_UR_Pos)
#define UART_SRR_UR                                         UART_SRR_UR_Msk     /**< UART Reset */

/*******************  Bit definition for UART_SRTS register  *******************/
#define UART_SRTS_SRTS_Pos                                  (0U)
#define UART_SRTS_SRTS_Len                                  (1U)
#define UART_SRTS_SRTS_Msk                                  (0x1U << UART_SRTS_SRTS_Pos)
#define UART_SRTS_SRTS                                      UART_SRTS_SRTS_Msk  /**< Shadow Request to Send */

/*******************  Bit definition for UART_SBCR register  *******************/
#define UART_SBCR_SBCR_Pos                                  (0U)
#define UART_SBCR_SBCR_Len                                  (1U)
#define UART_SBCR_SBCR_Msk                                  (0x1U << UART_SBCR_SBCR_Pos)
#define UART_SBCR_SBCR                                      UART_SBCR_SBCR_Msk  /**< Shadow Break Control */

/*******************  Bit definition for UART_SFE register  *******************/
#define UART_SFE_SFE_Pos                                    (0U)
#define UART_SFE_SFE_Len                                    (1U)
#define UART_SFE_SFE_Msk                                    (0x1U << UART_SFE_SFE_Pos)
#define UART_SFE_SFE                                        UART_SFE_SFE_Msk    /**< Shadow FIFO Enable */

/*******************  Bit definition for UART_SRT register  *******************/
#define UART_SRT_SRT_Pos                                    (0U)
#define UART_SRT_SRT_Len                                    (2U)
#define UART_SRT_SRT_Msk                                    (0x3U << UART_SRT_SRT_Pos)
#define UART_SRT_SRT                                        UART_SRT_SRT_Msk
#define UART_SRT_SRT_CHAR_1                                 (0x0U << UART_SRT_SRT_Pos)  /**< RX FIFO 1 Char */
#define UART_SRT_SRT_QUARTER_FULL                           (0x1U << UART_SRT_SRT_Pos)  /**< RX FIFO Quater Full*/
#define UART_SRT_SRT_HALF_FULL                              (0x2U << UART_SRT_SRT_Pos)  /**< RX FIFO Half Full */
#define UART_SRT_SRT_FULL_2                                 (0x3U << UART_SRT_SRT_Pos)  /**< RX FIFO 2 less than Full */

/*******************  Bit definition for UART_STET register  *******************/
#define UART_STET_STET_Pos                                  (0U)
#define UART_STET_STET_Len                                  (2U)
#define UART_STET_STET_Msk                                  (0x3U << UART_STET_STET_Pos)
#define UART_STET_STET                                      UART_STET_STET_Msk
#define UART_STET_STET_EMPTY                                (0x0U << UART_STET_STET_Pos)    /**< TX FIFO Empty */
#define UART_STET_STET_CHAR_2                               (0x1U << UART_STET_STET_Pos)    /**< TX FIFO 2 chars */
#define UART_STET_STET_QUARTER_FULL                         (0x2U << UART_STET_STET_Pos)    /**< TX FIFO Quater Full */
#define UART_STET_STET_HALF_FULL                            (0x3U << UART_STET_STET_Pos)    /**< TX FIFO Half Full */

/*******************  Bit definition for UART_HTX register  *******************/
#define UART_HTX_HTX_Pos                                    (0U)
#define UART_HTX_HTX_Len                                    (1U)
#define UART_HTX_HTX_Msk                                    (0x1U << UART_HTX_HTX_Pos)
#define UART_HTX_HTX                                        UART_HTX_HTX_Msk    /**< Halt TX */

/*******************  Bit definition for UART_DLF register  *******************/
#define UART_DLF_DLF_Pos                                    (0U)
#define UART_DLF_DLF_Len                                    (1U)
#define UART_DLF_DLF_Msk                                    (0x1U << UART_DLF_DLF_Pos)
#define UART_DLF_DLF                                        UART_DLF_DLF_Msk    /**< Fractional part of divisor */


/* ================================================================================================================= */
/* ================                                        WDT                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for WDT_CTRL register  ********************/
#define WDT_CTRL_INTEN_Pos                                  (0U)
#define WDT_CTRL_INTEN_Len                                  (1U)
#define WDT_CTRL_INTEN_Msk                                  (0x1U << WDT_CTRL_INTEN_Pos)
#define WDT_CTRL_INTEN                                      WDT_CTRL_INTEN_Msk      /**< Interrupt Enable */

#define WDT_CTRL_RSTEN_Pos                                  (1U)
#define WDT_CTRL_RSTEN_Len                                  (1U)
#define WDT_CTRL_RSTEN_Msk                                  (0x1U << WDT_CTRL_RSTEN_Pos)
#define WDT_CTRL_RSTEN                                      WDT_CTRL_RSTEN_Msk      /**< Reset Enable */

/*******************  Bit definition for WDT_INTCLR register  ********************/
#define WDT_INTCLR_Pos                                      (0U)
#define WDT_INTCLR_Len                                      (1U)
#define WDT_INTCLR_Msk                                      (0x1U << WDT_INTCLR_Pos)
#define WDT_INTCLR                                          WDT_INTCLR_Msk   /**< Interrupt status clear */

/*******************  Bit definition for WDT_MIS register  ********************/
#define WDT_MIS_INTSTAT_Pos                                 (0U)
#define WDT_MIS_INTSTAT_Len                                 (1U)
#define WDT_MIS_INTSTAT_Msk                                 (0x1U << WDT_MIS_INTSTAT_Pos)
#define WDT_MIS_INTSTAT                                     WDT_MIS_INTSTAT_Msk     /**< Interrupt status */


/* ================================================================================================================= */
/* ================                                       XQSPI                                     ================ */
/* ================================================================================================================= */
/*******************  Bit definition for XQSPI_CACHE_CTRL0 register  **********/
#define XQSPI_CACHE_CTRL0_DIRECT_MAP_EN_Pos                 (11U)
#define XQSPI_CACHE_CTRL0_DIRECT_MAP_EN_Len                 (1U)
#define XQSPI_CACHE_CTRL0_DIRECT_MAP_EN_Msk                 (0x1U << XQSPI_CACHE_CTRL0_DIRECT_MAP_EN_Pos)
#define XQSPI_CACHE_CTRL0_DIRECT_MAP_EN                     XQSPI_CACHE_CTRL0_DIRECT_MAP_EN_Msk

#define XQSPI_CACHE_CTRL0_CLK_FORCE_EN_Pos                  (7U)
#define XQSPI_CACHE_CTRL0_CLK_FORCE_EN_Len                  (4U)
#define XQSPI_CACHE_CTRL0_CLK_FORCE_EN_Msk                  (0xFU << XQSPI_CACHE_CTRL0_CLK_FORCE_EN_Pos)
#define XQSPI_CACHE_CTRL0_CLK_FORCE_EN                      XQSPI_CACHE_CTRL0_CLK_FORCE_EN_Msk

#define XQSPI_CACHE_CTRL0_BUF_DIS_Pos                       (6U)
#define XQSPI_CACHE_CTRL0_BUF_DIS_Len                       (1U)
#define XQSPI_CACHE_CTRL0_BUF_DIS_Msk                       (0x1U << XQSPI_CACHE_CTRL0_BUF_DIS_Pos)
#define XQSPI_CACHE_CTRL0_BUF_DIS                           XQSPI_CACHE_CTRL0_BUF_DIS_Msk

#define XQSPI_CACHE_CTRL0_DIS_SEQ_Pos                       (5U)
#define XQSPI_CACHE_CTRL0_DIS_SEQ_Len                       (1U)
#define XQSPI_CACHE_CTRL0_DIS_SEQ_Msk                       (0x1U << XQSPI_CACHE_CTRL0_DIS_SEQ_Pos)
#define XQSPI_CACHE_CTRL0_DIS_SEQ                           XQSPI_CACHE_CTRL0_DIS_SEQ_Msk

#define XQSPI_CACHE_CTRL0_HITMISS_Pos                       (4U)
#define XQSPI_CACHE_CTRL0_HITMISS_Len                       (1U)
#define XQSPI_CACHE_CTRL0_HITMISS_Msk                       (0x1U << XQSPI_CACHE_CTRL0_HITMISS_Pos)
#define XQSPI_CACHE_CTRL0_HITMISS                           XQSPI_CACHE_CTRL0_HITMISS_Msk

#define XQSPI_CACHE_CTRL0_FIFO_Pos                          (3U)
#define XQSPI_CACHE_CTRL0_FIFO_Len                          (1U)
#define XQSPI_CACHE_CTRL0_FIFO_Msk                          (0x1U << XQSPI_CACHE_CTRL0_FIFO_Pos)
#define XQSPI_CACHE_CTRL0_FIFO                              XQSPI_CACHE_CTRL0_FIFO_Msk

#define XQSPI_CACHE_CTRL0_FLUSH_Pos                         (1U)
#define XQSPI_CACHE_CTRL0_FLUSH_Len                         (1U)
#define XQSPI_CACHE_CTRL0_FLUSH_Msk                         (0x1U << XQSPI_CACHE_CTRL0_FLUSH_Pos)
#define XQSPI_CACHE_CTRL0_FLUSH                             XQSPI_CACHE_CTRL0_FLUSH_Msk

#define XQSPI_CACHE_CTRL0_DIS_Pos                           (0U)
#define XQSPI_CACHE_CTRL0_DIS_Len                           (1U)
#define XQSPI_CACHE_CTRL0_DIS_Msk                           (0x1U << XQSPI_CACHE_CTRL0_DIS_Pos)
#define XQSPI_CACHE_CTRL0_DIS                               XQSPI_CACHE_CTRL0_DIS_Msk

/*******************  Bit definition for XQSPI_CACHE_CTRL1 register  **********/
#define XQSPI_CACHE_CTRL1_DBGMUX_EN_Pos                     (4U)
#define XQSPI_CACHE_CTRL1_DBGMUX_EN_Len                     (1U)
#define XQSPI_CACHE_CTRL1_DBGMUX_EN_Msk                     (0x1U << XQSPI_CACHE_CTRL1_DBGMUX_EN_Pos)
#define XQSPI_CACHE_CTRL1_DBGMUX_EN                         XQSPI_CACHE_CTRL1_DBGMUX_EN_Msk

#define XQSPI_CACHE_CTRL1_DBGBUS_SEL_Pos                    (0U)
#define XQSPI_CACHE_CTRL1_DBGBUS_SEL_Len                    (4U)
#define XQSPI_CACHE_CTRL1_DBGBUS_SEL_Msk                    (0xFU << XQSPI_CACHE_CTRL1_DBGBUS_SEL_Pos)
#define XQSPI_CACHE_CTRL1_DBGBUS_SEL                        XQSPI_CACHE_CTRL1_DBGBUS_SEL_Msk

/*******************  Bit definition for XQSPI_CACHE_HITCOUNT register  *******/
#define XQSPI_CACHE_HITCOUNT_Pos                            (0U)
#define XQSPI_CACHE_HITCOUNT_Len                            (32U)
#define XQSPI_CACHE_HITCOUNT_Msk                            (0xFFFFFFFFU)
#define XQSPI_CACHE_HITCOUNT                                XQSPI_CACHE_HITCOUNT_Msk

/*******************  Bit definition for XQSPI_CACHE_MISSCOUNT register  ******/
#define XQSPI_CACHE_MISSCOUNT_Pos                           (0U)
#define XQSPI_CACHE_MISSCOUNT_Len                           (32U)
#define XQSPI_CACHE_MISSCOUNT_Msk                           (0xFFFFFFFFU)
#define XQSPI_CACHE_MISSCOUNT                               XQSPI_CACHE_MISSCOUNT_Msk

/*******************  Bit definition for XQSPI_CACHE_STAT register  ***********/
#define XQSPI_CACHE_BUF_BUSY_Pos                            (2U)
#define XQSPI_CACHE_BUF_BUSY_Len                            (1U)
#define XQSPI_CACHE_BUF_BUSY_Msk                            (0x1U << XQSPI_CACHE_BUF_BUSY_Pos)
#define XQSPI_CACHE_BUF_BUSY                                XQSPI_CACHE_BUF_BUSY_Msk

#define XQSPI_CACHE_BUF_ADDR_REACHED_Pos                    (1U)
#define XQSPI_CACHE_BUF_ADDR_REACHED_Len                    (1U)
#define XQSPI_CACHE_BUF_ADDR_REACHED_Msk                    (0x1U << XQSPI_CACHE_BUF_ADDR_REACHED_Pos)
#define XQSPI_CACHE_BUF_ADDR_REACHED                        XQSPI_CACHE_BUF_ADDR_REACHED_Msk

#define XQSPI_CACHE_STAT_Pos                                (0U)
#define XQSPI_CACHE_STAT_Len                                (1U)
#define XQSPI_CACHE_STAT_Msk                                (0x1U << XQSPI_CACHE_STAT_Pos)
#define XQSPI_CACHE_STAT                                    XQSPI_CACHE_STAT_Msk

/*******************  Bit definition for XQSPI_CACHE_BUF_FIRST_ADDR register  ***********/
#define XQSPI_CACHE_BUF_FISRT_ADDR_Pos                      (0U)
#define XQSPI_CACHE_BUF_FISRT_ADDR_Len                      (32U)
#define XQSPI_CACHE_BUF_FISRT_ADDR_Msk                      (0xFFFFFFFFU)
#define XQSPI_CACHE_BUF_FISRT_ADDR                          XQSPI_CACHE_BUF_FISRT_ADDR_Msk

/*******************  Bit definition for XQSPI_CACHE_BUF_LAST_ADDR register  ***********/
#define XQSPI_CACHE_BUF_LAST_ADDR_Pos                       (0U)
#define XQSPI_CACHE_BUF_LAST_ADDR_Len                       (32U)
#define XQSPI_CACHE_BUF_LAST_ADDR_Msk                       (0xFFFFFFFFU)
#define XQSPI_CACHE_BUF_LAST_ADDR                           XQSPI_CACHE_BUF_LAST_ADDR_Msk

/*******************  Bit definition for XQSPI_XIP_CFG register  **************/
#define XQSPI_XIP_CFG_CMD_Pos                               (0U)
#define XQSPI_XIP_CFG_CMD_Len                               (8U)
#define XQSPI_XIP_CFG_CMD_Msk                               (0xFFU << XQSPI_XIP_CFG_CMD_Pos)
#define XQSPI_XIP_CFG_CMD                                   XQSPI_XIP_CFG_CMD_Msk

#define XQSPI_XIP_CFG_LE32_Pos                              (8U)
#define XQSPI_XIP_CFG_LE32_Len                              (1U)
#define XQSPI_XIP_CFG_LE32_Msk                              (0x1U << XQSPI_XIP_CFG_LE32_Pos)
#define XQSPI_XIP_CFG_LE32                                  XQSPI_XIP_CFG_LE32_Msk

#define XQSPI_XIP_CFG_ADDR4_Pos                             (7U)
#define XQSPI_XIP_CFG_ADDR4_Len                             (1U)
#define XQSPI_XIP_CFG_ADDR4_Msk                             (0x1U << XQSPI_XIP_CFG_ADDR4_Pos)
#define XQSPI_XIP_CFG_ADDR4                                 XQSPI_XIP_CFG_ADDR4_Msk

#define XQSPI_XIP_CFG_CPOL_Pos                              (6U)
#define XQSPI_XIP_CFG_CPOL_Len                              (1U)
#define XQSPI_XIP_CFG_CPOL_Msk                              (0x1U << XQSPI_XIP_CFG_CPOL_Pos)
#define XQSPI_XIP_CFG_CPOL                                  XQSPI_XIP_CFG_CPOL_Msk

#define XQSPI_XIP_CFG_CPHA_Pos                              (5U)
#define XQSPI_XIP_CFG_CPHA_Len                              (1U)
#define XQSPI_XIP_CFG_CPHA_Msk                              (0x1U << XQSPI_XIP_CFG_CPHA_Pos)
#define XQSPI_XIP_CFG_CPHA                                  XQSPI_XIP_CFG_CPHA_Msk

#define XQSPI_XIP_CFG_SS_Pos                                (1U)
#define XQSPI_XIP_CFG_SS_Len                                (4U)
#define XQSPI_XIP_CFG_SS_Msk                                (0xFU << XQSPI_XIP_CFG_SS_Pos)
#define XQSPI_XIP_CFG_SS                                    XQSPI_XIP_CFG_SS_Msk

#define XQSPI_XIP_CFG_HPEN_Pos                              (0U)
#define XQSPI_XIP_CFG_HPEN_Len                              (1U)
#define XQSPI_XIP_CFG_HPEN_Msk                              (0x1U << XQSPI_XIP_CFG_HPEN_Pos)
#define XQSPI_XIP_CFG_HPEN                                  XQSPI_XIP_CFG_HPEN_Msk

#define XQSPI_XIP_CFG_ENDDUMMY_Pos                          (12U)
#define XQSPI_XIP_CFG_ENDDUMMY_Len                          (2U)
#define XQSPI_XIP_CFG_ENDDUMMY_Msk                          (0x3U << XQSPI_XIP_CFG_ENDDUMMY_Pos)
#define XQSPI_XIP_CFG_ENDDUMMY                              XQSPI_XIP_CFG_ENDDUMMY_Msk

#define XQSPI_XIP_CFG_DUMMYCYCLES_Pos                       (8U)
#define XQSPI_XIP_CFG_DUMMYCYCLES_Len                       (4U)
#define XQSPI_XIP_CFG_DUMMYCYCLES_Msk                       (0xFU << XQSPI_XIP_CFG_DUMMYCYCLES_Pos)
#define XQSPI_XIP_CFG_DUMMYCYCLES                           XQSPI_XIP_CFG_DUMMYCYCLES_Msk

#define XQSPI_XIP_CFG_HPMODE_Pos                            (0U)
#define XQSPI_XIP_CFG_HPMODE_Len                            (8U)
#define XQSPI_XIP_CFG_HPMODE_Msk                            (0xFFUL << XQSPI_XIP_CFG_HPMODE_Pos)
#define XQSPI_XIP_CFG_HPMODE                                XQSPI_XIP_CFG_HPMODE_Msk

/*******************  Bit definition for XQSPI_XIP_EN register  ***************/
#define XQSPI_XIP_EN_REQ_Pos                                (0U)
#define XQSPI_XIP_EN_REQ_Len                                (1U)
#define XQSPI_XIP_EN_REQ_Msk                                (0x1U << XQSPI_XIP_EN_REQ_Pos)
#define XQSPI_XIP_EN_REQ                                    XQSPI_XIP_EN_REQ_Msk

#define XQSPI_XIP_EN_OUT_Pos                                (0U)
#define XQSPI_XIP_EN_OUT_Len                                (1U)
#define XQSPI_XIP_EN_OUT_Msk                                (0x1U << XQSPI_XIP_EN_OUT_Pos)
#define XQSPI_XIP_EN_OUT                                    XQSPI_XIP_EN_OUT_Msk

/*******************  Bit definition for XQSPI_XIP_INT0 register  *************/
#define XQSPI_XIP_INT_EN_Pos                                (0U)
#define XQSPI_XIP_INT_EN_Len                                (1U)
#define XQSPI_XIP_INT_EN_Msk                                (0x1U << XQSPI_XIP_INT_EN_Pos)
#define XQSPI_XIP_INT_EN                                    XQSPI_XIP_INT_EN_Msk

/*******************  Bit definition for XQSPI_XIP_INT1 register  *************/
#define XQSPI_XIP_INT_STAT_Pos                              (0U)
#define XQSPI_XIP_INT_STAT_Len                              (1U)
#define XQSPI_XIP_INT_STAT_Msk                              (0x1U << XQSPI_XIP_INT_STAT_Pos)
#define XQSPI_XIP_INT_STAT                                  XQSPI_XIP_INT_STAT_Msk

/*******************  Bit definition for XQSPI_XIP_INT2 register  *************/
#define XQSPI_XIP_INT_REQ_Pos                               (0U)
#define XQSPI_XIP_INT_REQ_Len                               (1U)
#define XQSPI_XIP_INT_REQ_Msk                               (0x1U << XQSPI_XIP_INT_REQ_Pos)
#define XQSPI_XIP_INT_REQ                                   XQSPI_XIP_INT_REQ_Msk

/*******************  Bit definition for XQSPI_XIP_INT3 register  *************/
#define XQSPI_XIP_INT_SET_Pos                               (0U)
#define XQSPI_XIP_INT_SET_Len                               (1U)
#define XQSPI_XIP_INT_SET_Msk                               (0x1U << XQSPI_XIP_INT_SET_Pos)
#define XQSPI_XIP_INT_SET                                   XQSPI_XIP_INT_SET_Msk

/*******************  Bit definition for XQSPI_XIP_INT4 register  *************/
#define XQSPI_XIP_INT_CLR_Pos                               (0U)
#define XQSPI_XIP_INT_CLR_Len                               (1U)
#define XQSPI_XIP_INT_CLR_Msk                               (0x1U << XQSPI_XIP_INT_CLR_Pos)
#define XQSPI_XIP_INT_CLR                                   XQSPI_XIP_INT_CLR_Msk

/*******************  Bit definition for XQSPI_XIP_SOFT_RST register  *************/
#define XQSPI_XIP_SOFT_RST_Pos                              (0U)
#define XQSPI_XIP_SOFT_RST_Len                              (1U)
#define XQSPI_XIP_SOFT_RST_Msk                              (0x1U << XQSPI_XIP_SOFT_RST_Pos)
#define XQSPI_XIP_SOFT_RST                                  XQSPI_XIP_SOFT_RST_Msk

/*******************  Bit definition for XQSPI_QSPI_STAT register  ************/
#define XQSPI_QSPI_STAT_RXFULL_Pos                          (7U)
#define XQSPI_QSPI_STAT_RXFULL_Len                          (1U)
#define XQSPI_QSPI_STAT_RXFULL_Msk                          (0x1U << XQSPI_QSPI_STAT_RXFULL_Pos)
#define XQSPI_QSPI_STAT_RXFULL                              XQSPI_QSPI_STAT_RXFULL_Msk

#define XQSPI_QSPI_STAT_RXWMARK_Pos                         (6U)
#define XQSPI_QSPI_STAT_RXWMARK_Len                         (1U)
#define XQSPI_QSPI_STAT_RXWMARK_Msk                         (0x1U << XQSPI_QSPI_STAT_RXWMARK_Pos)
#define XQSPI_QSPI_STAT_RXWMARK                             XQSPI_QSPI_STAT_RXWMARK_Msk

#define XQSPI_QSPI_STAT_RXEMPTY_Pos                         (5U)
#define XQSPI_QSPI_STAT_RXEMPTY_Len                         (1U)
#define XQSPI_QSPI_STAT_RXEMPTY_Msk                         (0x1U << XQSPI_QSPI_STAT_RXEMPTY_Pos)
#define XQSPI_QSPI_STAT_RXEMPTY                             XQSPI_QSPI_STAT_RXEMPTY_Msk

#define XQSPI_QSPI_STAT_TXFULL_Pos                          (4U)
#define XQSPI_QSPI_STAT_TXFULL_Len                          (1U)
#define XQSPI_QSPI_STAT_TXFULL_Msk                          (0x1U << XQSPI_QSPI_STAT_TXFULL_Pos)
#define XQSPI_QSPI_STAT_TXFULL                              XQSPI_QSPI_STAT_TXFULL_Msk

#define XQSPI_QSPI_STAT_TXWMARK_Pos                         (3U)
#define XQSPI_QSPI_STAT_TXWMARK_Len                         (1U)
#define XQSPI_QSPI_STAT_TXWMARK_Msk                         (0x1U << XQSPI_QSPI_STAT_TXWMARK_Pos)
#define XQSPI_QSPI_STAT_TXWMARK                             XQSPI_QSPI_STAT_TXWMARK_Msk

#define XQSPI_QSPI_STAT_TXEMPTY_Pos                         (2U)
#define XQSPI_QSPI_STAT_TXEMPTY_Len                         (1U)
#define XQSPI_QSPI_STAT_TXEMPTY_Msk                         (0x1U << XQSPI_QSPI_STAT_TXEMPTY_Pos)
#define XQSPI_QSPI_STAT_TXEMPTY                             XQSPI_QSPI_STAT_TXEMPTY_Msk

#define XQSPI_QSPI_STAT_XFERIP_Pos                          (0U)
#define XQSPI_QSPI_STAT_XFERIP_Len                          (1U)
#define XQSPI_QSPI_STAT_XFERIP_Msk                          (0x1U << XQSPI_QSPI_STAT_XFERIP_Pos)
#define XQSPI_QSPI_STAT_XFERIP                              XQSPI_QSPI_STAT_XFERIP_Msk

/*******************  Bit definition for XQSPI_QSPI_FIFO register  ************/
#define XQSPI_QSPI_FIFO_TX_Pos                              (0U)
#define XQSPI_QSPI_FIFO_TX_Len                              (32U)
#define XQSPI_QSPI_FIFO_TX_Msk                              (0xFFFFFFFFU)
#define XQSPI_QSPI_FIFO_TX                                  XQSPI_QSPI_FIFO_TX_Msk

#define XQSPI_QSPI_FIFO_RX_Pos                              (0U)
#define XQSPI_QSPI_FIFO_RX_Len                              (32U)
#define XQSPI_QSPI_FIFO_RX_Msk                              (0xFFFFFFFFU)
#define XQSPI_QSPI_FIFO_RX                                  XQSPI_QSPI_FIFO_RX_Msk

/*******************  Bit definition for XQSPI_QSPI_CTRL register  ************/
#define XQSPI_QSPI_CTRL_TXWMARK_Pos                         (14U)
#define XQSPI_QSPI_CTRL_TXWMARK_Len                         (2U)
#define XQSPI_QSPI_CTRL_TXWMARK_Msk                         (0x3U << XQSPI_QSPI_CTRL_TXWMARK_Pos)
#define XQSPI_QSPI_CTRL_TXWMARK                             XQSPI_QSPI_CTRL_TXWMARK_Msk

#define XQSPI_QSPI_CTRL_RXWMARK_Pos                         (12U)
#define XQSPI_QSPI_CTRL_RXWMARK_Len                         (2U)
#define XQSPI_QSPI_CTRL_RXWMARK_Msk                         (0x3U << XQSPI_QSPI_CTRL_RXWMARK_Pos)
#define XQSPI_QSPI_CTRL_RXWMARK                             XQSPI_QSPI_CTRL_RXWMARK_Msk

#define XQSPI_QSPI_CTRL_MWAITEN_Pos                         (11U)
#define XQSPI_QSPI_CTRL_MWAITEN_Len                         (1U)
#define XQSPI_QSPI_CTRL_MWAITEN_Msk                         (0x1U << XQSPI_QSPI_CTRL_MWAITEN_Pos)
#define XQSPI_QSPI_CTRL_MWAITEN                             XQSPI_QSPI_CTRL_MWAITEN_Msk

#define XQSPI_QSPI_CTRL_DMA_Pos                             (10U)
#define XQSPI_QSPI_CTRL_DMA_Len                             (1U)
#define XQSPI_QSPI_CTRL_DMA_Msk                             (0x1U << XQSPI_QSPI_CTRL_DMA_Pos)
#define XQSPI_QSPI_CTRL_DMA                                 XQSPI_QSPI_CTRL_DMA_Msk

#define XQSPI_QSPI_CTRL_MASTER_Pos                          (5U)
#define XQSPI_QSPI_CTRL_MASTER_Len                          (1U)
#define XQSPI_QSPI_CTRL_MASTER_Msk                          (0x1U << XQSPI_QSPI_CTRL_MASTER_Pos)
#define XQSPI_QSPI_CTRL_MASTER                              XQSPI_QSPI_CTRL_MASTER_Msk

#define XQSPI_QSPI_CTRL_CPOL_Pos                            (4U)
#define XQSPI_QSPI_CTRL_CPOL_Len                            (1U)
#define XQSPI_QSPI_CTRL_CPOL_Msk                            (0x1U << XQSPI_QSPI_CTRL_CPOL_Pos)
#define XQSPI_QSPI_CTRL_CPOL                                XQSPI_QSPI_CTRL_CPOL_Msk

#define XQSPI_QSPI_CTRL_CPHA_Pos                            (3U)
#define XQSPI_QSPI_CTRL_CPHA_Len                            (1U)
#define XQSPI_QSPI_CTRL_CPHA_Msk                            (0x1U << XQSPI_QSPI_CTRL_CPHA_Pos)
#define XQSPI_QSPI_CTRL_CPHA                                XQSPI_QSPI_CTRL_CPHA_Msk

#define XQSPI_QSPI_CTRL_MSB1ST_Pos                          (2U)
#define XQSPI_QSPI_CTRL_MSB1ST_Len                          (1U)
#define XQSPI_QSPI_CTRL_MSB1ST_Msk                          (0x1U << XQSPI_QSPI_CTRL_MSB1ST_Pos)
#define XQSPI_QSPI_CTRL_MSB1ST                              XQSPI_QSPI_CTRL_MSB1ST_Msk

#define XQSPI_QSPI_CTRL_CONTXFER_Pos                        (0U)
#define XQSPI_QSPI_CTRL_CONTXFER_Len                        (1U)
#define XQSPI_QSPI_CTRL_CONTXFER_Msk                        (0x1U << XQSPI_QSPI_CTRL_CONTXFER_Pos)
#define XQSPI_QSPI_CTRL_CONTXFER                            XQSPI_QSPI_CTRL_CONTXFER_Msk

/*******************  Bit definition for XQSPI_QSPI_AUXCTRL register  *********/
#define XQSPI_QSPI_AUXCTRL_CONTXFERX_Pos                    (7U)
#define XQSPI_QSPI_AUXCTRL_CONTXFERX_Len                    (1U)
#define XQSPI_QSPI_AUXCTRL_CONTXFERX_Msk                    (0x1U << XQSPI_QSPI_AUXCTRL_CONTXFERX_Pos)
#define XQSPI_QSPI_AUXCTRL_CONTXFERX                        XQSPI_QSPI_AUXCTRL_CONTXFERX_Msk

#define XQSPI_QSPI_AUXCTRL_BITSIZE_Pos                      (4U)
#define XQSPI_QSPI_AUXCTRL_BITSIZE_Len                      (3U)
#define XQSPI_QSPI_AUXCTRL_BITSIZE_Msk                      (0x7U << XQSPI_QSPI_AUXCTRL_BITSIZE_Pos)
#define XQSPI_QSPI_AUXCTRL_BITSIZE                          XQSPI_QSPI_AUXCTRL_BITSIZE_Msk

#define XQSPI_QSPI_AUXCTRL_INHIBITDIN_Pos                   (3U)
#define XQSPI_QSPI_AUXCTRL_INHIBITDIN_Len                   (1U)
#define XQSPI_QSPI_AUXCTRL_INHIBITDIN_Msk                   (0x1U << XQSPI_QSPI_AUXCTRL_INHIBITDIN_Pos)
#define XQSPI_QSPI_AUXCTRL_INHIBITDIN                       XQSPI_QSPI_AUXCTRL_INHIBITDIN_Msk

#define XQSPI_QSPI_AUXCTRL_INHIBITDOUT_Pos                  (2U)
#define XQSPI_QSPI_AUXCTRL_INHIBITDOUT_Len                  (1U)
#define XQSPI_QSPI_AUXCTRL_INHIBITDOUT_Msk                  (0x1U << XQSPI_QSPI_AUXCTRL_INHIBITDOUT_Pos)
#define XQSPI_QSPI_AUXCTRL_INHIBITDOUT                      XQSPI_QSPI_AUXCTRL_INHIBITDOUT_Msk

#define XQSPI_QSPI_AUXCTRL_QMODE_Pos                        (0U)
#define XQSPI_QSPI_AUXCTRL_QMODE_Len                        (2U)
#define XQSPI_QSPI_AUXCTRL_QMODE_Msk                        (0x3U << XQSPI_QSPI_AUXCTRL_QMODE_Pos)
#define XQSPI_QSPI_AUXCTRL_QMODE                            XQSPI_QSPI_AUXCTRL_QMODE_Msk

/*******************  Bit definition for XQSPI_QSPI_SS register  **************/
#define XQSPI_QSPI_SS_OUT3_Pos                              (3U)
#define XQSPI_QSPI_SS_OUT3_Len                              (1U)
#define XQSPI_QSPI_SS_OUT3_Msk                              (0x1U << XQSPI_QSPI_SS_OUT3_Pos)
#define XQSPI_QSPI_SS_OUT3                                  XQSPI_QSPI_SS_OUT3_Msk

#define XQSPI_QSPI_SS_OUT2_Pos                              (2U)
#define XQSPI_QSPI_SS_OUT2_Len                              (1U)
#define XQSPI_QSPI_SS_OUT2_Msk                              (0x1U << XQSPI_QSPI_SS_OUT2_Pos)
#define XQSPI_QSPI_SS_OUT2                                  XQSPI_QSPI_SS_OUT2_Msk

#define XQSPI_QSPI_SS_OUT1_Pos                              (1U)
#define XQSPI_QSPI_SS_OUT1_Len                              (1U)
#define XQSPI_QSPI_SS_OUT1_Msk                              (0x1U << XQSPI_QSPI_SS_OUT1_Pos)
#define XQSPI_QSPI_SS_OUT1                                  XQSPI_QSPI_SS_OUT1_Msk

#define XQSPI_QSPI_SS_OUT0_Pos                              (0U)
#define XQSPI_QSPI_SS_OUT0_Len                              (1U)
#define XQSPI_QSPI_SS_OUT0_Msk                              (0x1U << XQSPI_QSPI_SS_OUT0_Pos)
#define XQSPI_QSPI_SS_OUT0                                  XQSPI_QSPI_SS_OUT0_Msk

/*******************  Bit definition for XQSPI_QSPI_SS_POL register  **********/
#define XQSPI_QSPI_SS_POL3_Pos                              (3U)
#define XQSPI_QSPI_SS_POL3_Len                              (1U)
#define XQSPI_QSPI_SS_POL3_Msk                              (0x1U << XQSPI_QSPI_SS_POL3_Pos)
#define XQSPI_QSPI_SS_POL3                                  XQSPI_QSPI_SS_POL3_Msk

#define XQSPI_QSPI_SS_POL2_Pos                              (2U)
#define XQSPI_QSPI_SS_POL2_Len                              (1U)
#define XQSPI_QSPI_SS_POL2_Msk                              (0x1U << XQSPI_QSPI_SS_POL2_Pos)
#define XQSPI_QSPI_SS_POL2                                  XQSPI_QSPI_SS_POL2_Msk

#define XQSPI_QSPI_SS_POL1_Pos                              (1U)
#define XQSPI_QSPI_SS_POL1_Len                              (1U)
#define XQSPI_QSPI_SS_POL1_Msk                              (0x1U << XQSPI_QSPI_SS_POL1_Pos)
#define XQSPI_QSPI_SS_POL1                                  XQSPI_QSPI_SS_POL1_Msk

#define XQSPI_QSPI_SS_POL0_Pos                              (0U)
#define XQSPI_QSPI_SS_POL0_Len                              (1U)
#define XQSPI_QSPI_SS_POL0_Msk                              (0x1U << XQSPI_QSPI_SS_POL0_Pos)
#define XQSPI_QSPI_SS_POL0                                  XQSPI_QSPI_SS_POL0_Msk

/*******************  Bit definition for XQSPI_QSPI_INT_EN register  **********/
#define XQSPI_QSPI_INT_EN_Pos                               (0U)
#define XQSPI_QSPI_INT_EN_Len                               (7U)
#define XQSPI_QSPI_INT_EN_Msk                               (0x7FUL << XQSPI_QSPI_INT_EN_Pos)
#define XQSPI_QSPI_INT_EN                                   XQSPI_QSPI_INT_EN_Msk

/*******************  Bit definition for XQSPI_QSPI_INT_STAT register  ********/
#define XQSPI_QSPI_INT_STAT_Pos                             (0U)
#define XQSPI_QSPI_INT_STAT_Len                             (7U)
#define XQSPI_QSPI_INT_STAT_Msk                             (0x7FUL << XQSPI_QSPI_INT_STAT_Pos)
#define XQSPI_QSPI_INT_STAT                                 XQSPI_QSPI_INT_STAT_Msk

/*******************  Bit definition for XQSPI_QSPI_INT_CLR register  *********/
#define XQSPI_QSPI_INT_CLR_Pos                              (0U)
#define XQSPI_QSPI_INT_CLR_Len                              (7U)
#define XQSPI_QSPI_INT_CLR_Msk                              (0x7FUL << XQSPI_QSPI_INT_CLR_Pos)
#define XQSPI_QSPI_INT_CLR                                  XQSPI_QSPI_INT_CLR_Msk

/*******************  Bit definition for XQSPI Interrupt Bit Mapping  *********/
#define XQSPI_QSPI_GPI_HI_PULSE1_Pos                        (6U)
#define XQSPI_QSPI_GPI_HI_PULSE1_Len                        (1U)
#define XQSPI_QSPI_GPI_HI_PULSE1_Msk                        (0x1U << XQSPI_QSPI_GPI_HI_PULSE1_Pos)
#define XQSPI_QSPI_GPI_HI_PULSE0_Pos                        (5U)
#define XQSPI_QSPI_GPI_HI_PULSE0_Len                        (1U)
#define XQSPI_QSPI_GPI_HI_PULSE0_Msk                        (0x1U << XQSPI_QSPI_GPI_HI_PULSE0_Pos)
#define XQSPI_QSPI_XFER_DPULSE_Pos                          (4U)
#define XQSPI_QSPI_XFER_DPULSE_Len                          (1U)
#define XQSPI_QSPI_XFER_DPULSE_Msk                          (0x1U << XQSPI_QSPI_XFER_DPULSE_Pos)
#define XQSPI_QSPI_RX_FPULSE_Pos                            (3U)
#define XQSPI_QSPI_RX_FPULSE_Len                            (1U)
#define XQSPI_QSPI_RX_FPULSE_Msk                            (0x1U << XQSPI_QSPI_RX_FPULSE_Pos)
#define XQSPI_QSPI_RX_WPULSE_Pos                            (2U)
#define XQSPI_QSPI_RX_WPULSE_Len                            (1U)
#define XQSPI_QSPI_RX_WPULSE_Msk                            (0x1U << XQSPI_QSPI_RX_WPULSE_Pos)
#define XQSPI_QSPI_TX_WPULSE_Pos                            (1U)
#define XQSPI_QSPI_TX_WPULSE_Len                            (1U)
#define XQSPI_QSPI_TX_WPULSE_Msk                            (0x1U << XQSPI_QSPI_TX_WPULSE_Pos)
#define XQSPI_QSPI_TX_EPULSE_Pos                            (0U)
#define XQSPI_QSPI_TX_EPULSE_Len                            (1U)
#define XQSPI_QSPI_TX_EPULSE_Msk                            (0x1U << XQSPI_QSPI_TX_EPULSE_Pos)

/*******************  Bit definition for XQSPI_QSPI_TXFIFOLVL register  *******/
#define XQSPI_QSPI_TXFIFOLVL_Pos                            (0U)
#define XQSPI_QSPI_TXFIFOLVL_Len                            (7U)
#define XQSPI_QSPI_TXFIFOLVL_Msk                            (0x7FUL << XQSPI_QSPI_TXFIFOLVL_Pos)
#define XQSPI_QSPI_TXFIFOLVL                                XQSPI_QSPI_TXFIFOLVL_Msk

/*******************  Bit definition for XQSPI_QSPI_RXFIFOLVL register  *******/
#define XQSPI_QSPI_RXFIFOLVL_Pos                            (0U)
#define XQSPI_QSPI_RXFIFOLVL_Len                            (7U)
#define XQSPI_QSPI_RXFIFOLVL_Msk                            (0x7FUL << XQSPI_QSPI_RXFIFOLVL_Pos)
#define XQSPI_QSPI_RXFIFOLVL                                XQSPI_QSPI_RXFIFOLVL_Msk

/*******************  Bit definition for XQSPI_QSPI_MWAIT register  ***********/
#define XQSPI_QSPI_MWAIT_MWAIT_Pos                          (0U)
#define XQSPI_QSPI_MWAIT_MWAIT_Len                          (8U)
#define XQSPI_QSPI_MWAIT_MWAIT_Msk                          (0xFFUL << XQSPI_QSPI_MWAIT_MWAIT_Pos)
#define XQSPI_QSPI_MWAIT_MWAIT                              XQSPI_QSPI_MWAIT_MWAIT_Msk

/*******************  Bit definition for XQSPI_QSPI_EN register  **************/
#define XQSPI_QSPI_EN_EN_Pos                                (0U)
#define XQSPI_QSPI_EN_EN_Len                                (1U)
#define XQSPI_QSPI_EN_EN_Msk                                (0x1U << XQSPI_QSPI_EN_EN_Pos)
#define XQSPI_QSPI_EN_EN                                    XQSPI_QSPI_EN_EN_Msk

/*******************  Bit definition for XQSPI_QSPI_GPOSET_GPOSET register  ***/
#define XQSPI_QSPI_GPOSET_GPOSET_Pos                        (0U)
#define XQSPI_QSPI_GPOSET_GPOSET_Len                        (8U)
#define XQSPI_QSPI_GPOSET_GPOSET_Msk                        (0xFFUL << XQSPI_QSPI_GPOSET_GPOSET_Pos)
#define XQSPI_QSPI_GPOSET_GPOSET                            XQSPI_QSPI_GPOSET_GPOSET_Msk

/*******************  Bit definition for XQSPI_QSPI_GPOCLR_GPOCLR register  ***/
#define XQSPI_QSPI_GPOCLR_GPOCLR_Pos                        (0U)
#define XQSPI_QSPI_GPOCLR_GPOCLR_Len                        (8U)
#define XQSPI_QSPI_GPOCLR_GPOCLR_Msk                        (0xFFUL << XQSPI_QSPI_GPOCLR_GPOCLR_Pos)
#define XQSPI_QSPI_GPOCLR_GPOCLR                            XQSPI_QSPI_GPOCLR_GPOCLR_Msk

/*******************  Bit definition for XQSPI_QSPI_FLASH_WRITE register  ***/
#define XQSPI_QSPI_FLASH_WRITE_Pos                          (0U)
#define XQSPI_QSPI_FLASH_WRITE_Len                          (1U)
#define XQSPI_QSPI_FLASH_WRITE_Msk                          (0xFFUL << XQSPI_QSPI_FLASH_WRITE_Pos)
#define XQSPI_QSPI_FLASH_WRITE                              XQSPI_QSPI_FLASH_WRITE_Msk

/*******************  Bit definition for XQSPI_QSPI_CS_IDLE_UNVLD_EN register  ***/
#define XQSPI_QSPI_CS_IDLE_UNVLD_EN_Pos                       (0U)
#define XQSPI_QSPI_CS_IDLE_UNVLD_EN_Len                       (1U)
#define XQSPI_QSPI_CS_IDLE_UNVLD_EN_Msk                       (0x1U << XQSPI_QSPI_CS_IDLE_UNVLD_EN_Pos)
#define XQSPI_QSPI_CS_IDLE_UNVLD_EN                            XQSPI_QSPI_CS_IDLE_UNVLD_EN_Msk

#define XQSPI_QSPI_1ST_PRETETCH_DIS_Pos                       (1U)
#define XQSPI_QSPI_1ST_PRETETCH_DIS_Len                       (1U)
#define XQSPI_QSPI_1ST_PRETETCH_DIS_Msk                       (0x1U << XQSPI_QSPI_1ST_PRETETCH_DIS_Pos)
#define XQSPI_QSPI_1ST_PRETETCH_DIS                            XQSPI_QSPI_1ST_PRETETCH_DIS_Msk

#define XQSPI_QSPI_KEY_PULSE_DIS_Pos                          (2U)
#define XQSPI_QSPI_KEY_PULSE_DIS_Len                          (1U)
#define XQSPI_QSPI_KEY_PULSE_DIS_Msk                          (0x1U << XQSPI_QSPI_KEY_PULSE_DIS_Pos)
#define XQSPI_QSPI_KEY_PULSE_DIS                               XQSPI_QSPI_KEY_PULSE_DIS_Msk

/* =============================================================================================================== */
/* ================                                       EFUSE                                   ================ */
/* =============================================================================================================== */
/*******************  Bit definition for EFUSE_TPGM register  **********/
#define EFUSE_TPGM_TIME_Pos                                 (0U)
#define EFUSE_TPGM_TIME_Len                                 (12U)
#define EFUSE_TPGM_TIME_Msk                                 (0xFFFUL << EFUSE_TPGM_TIME_Pos)
#define EFUSE_TPGM_TIME                                     EFUSE_TPGM_TIME_Msk

#define EFUSE_TPGM_WRITE_INTERVAL_Pos                       (12U)
#define EFUSE_TPGM_WRITE_INTERVAL_Len                       (8U)
#define EFUSE_TPGM_WRITE_INTERVAL_Msk                       (0xFFUL << EFUSE_TPGM_WRITE_INTERVAL_Pos)
#define EFUSE_TPGM_WRITE_INTERVAL                           EFUSE_TPGM_WRITE_INTERVAL_Msk

/*******************  Bit definition for EFUSE_PGENB register  **********/
#define EFUSE_PGENB_SIG_Pos                                 (0U)
#define EFUSE_PGENB_SIG_Len                                 (1U)
#define EFUSE_PGENB_SIG_Msk                                 (0x1UL << EFUSE_PGENB_SIG_Pos)
#define EFUSE_PGENB_SIG                                     EFUSE_PGENB_SIG_Msk

/*******************  Bit definition for EFUSE_OPERATION register  **********/
#define EFUSE_OPER_INIT_CHECK_Pos                           (0U)
#define EFUSE_OPER_INIT_CHECK_Len                           (1U)
#define EFUSE_OPER_INIT_CHECK_Msk                           (0x1UL << EFUSE_OPER_INIT_CHECK_Pos)
#define EFUSE_OPER_INIT_CHECK                               EFUSE_OPER_INIT_CHECK_Msk

/*******************  Bit definition for EFUSE_STATUS register  **********/
#define EFUSE_STATUS_INIT_DONE_Pos                          (0U)
#define EFUSE_STATUS_INIT_DONE_Len                          (1U)
#define EFUSE_STATUS_INIT_DONE_Msk                          (0x1UL << EFUSE_STATUS_INIT_DONE_Pos)
#define EFUSE_STATUS_INIT_DONE                              EFUSE_STATUS_INIT_DONE_Msk

#define EFUSE_STATUS_INIT_SUCCESS_Pos                       (1U)
#define EFUSE_STATUS_INIT_SUCCESS_Len                       (1U)
#define EFUSE_STATUS_INIT_SUCCESS_Msk                       (0x1UL << EFUSE_STATUS_INIT_SUCCESS_Pos)
#define EFUSE_STATUS_INIT_SUCCESS                           EFUSE_STATUS_INIT_SUCCESS_Msk

#define EFUSE_STATUS_WRITE_DONE_Pos                         (2U)
#define EFUSE_STATUS_WRITE_DONE_Len                         (1U)
#define EFUSE_STATUS_WRITE_DONE_Msk                         (0x1UL << EFUSE_STATUS_WRITE_DONE_Pos)
#define EFUSE_STATUS_WRITE_DONE                             EFUSE_STATUS_WRITE_DONE_Msk

/* =============================================================================================================== */
/* ================                                      RNG                                      ================ */
/* =============================================================================================================== */
/*******************  Bit definition for RNG_CTRL register  **********/
#define RNG_CTRL_RUN_EN_Pos                                 (0U)
#define RNG_CTRL_RUN_EN_Len                                 (1U)
#define RNG_CTRL_RUN_EN_Msk                                 (0x1UL << RNG_CTRL_RUN_EN_Pos)
#define RNG_CTRL_RUN_EN                                     RNG_CTRL_RUN_EN_Msk

/*******************  Bit definition for RNG_STATUS register  **********/
#define RNG_STATUS_READY_Pos                                (0U)
#define RNG_STATUS_READY_Len                                (1U)
#define RNG_STATUS_READY_Msk                                (0x1UL << RNG_STATUS_READY_Pos)
#define RNG_STATUS_READY                                    RNG_STATUS_READY_Msk

/*******************  Bit definition for RNG_DATA register  **********/
#define RNG_DATA_VALUE_Pos                                  (0U)
#define RNG_DATA_VALUE_Len                                  (32U)
#define RNG_DATA_VALUE_Msk                                  (0xFFFFFFFF)
#define RNG_DATA_VALUE                                      RNG_DATA_VALUE_Msk

/*******************  Bit definition for RNG_LR_STATUS register  *********/
#define RNG_LR_STATUS_FLAG_Pos                              (0U)
#define RNG_LR_STATUS_FLAG_Len                              (1U)
#define RNG_LR_STATUS_FLAG_Msk                              (0x1UL << RNG_LR_STATUS_FLAG_Pos)
#define RNG_LR_STATUS_FLAG                                  RNG_LR_STATUS_FLAG_Msk
#define RNG_LR_STATUS_CNT_Pos                               (1U)
#define RNG_LR_STATUS_CNT_Len                               (8U)
#define RNG_LR_STATUS_CNT_Msk                               (0xFFUL << RNG_LR_STATUS_CNT_Pos)
#define RNG_LR_STATUS_CNT                                   RNG_LR_STATUS_CNT_Msk

/*******************  Bit definition for RNG_CONFIG register  ************/
#define RNG_CONFIG_OUT_MODE_Pos                             (0U)
#define RNG_CONFIG_OUT_MODE_Len                             (4U)
#define RNG_CONFIG_OUT_MODE_Msk                             (0xFUL << RNG_CONFIG_OUT_MODE_Pos)
#define RNG_CONFIG_OUT_MODE                                 RNG_CONFIG_OUT_MODE_Msk
#define RNG_CONFIG_LFSR_XOR_SEL_Pos                         (4U)
#define RNG_CONFIG_LFSR_XOR_SEL_Len                         (3U)
#define RNG_CONFIG_LFSR_XOR_SEL_Msk                         (0x7UL << RNG_CONFIG_LFSR_XOR_SEL_Pos)
#define RNG_CONFIG_LFSR_XOR_SEL                             RNG_CONFIG_LFSR_XOR_SEL_Msk
#define RNG_CONFIG_POST_MODE_Pos                            (7U)
#define RNG_CONFIG_POST_MODE_Len                            (2U)
#define RNG_CONFIG_POST_MODE_Msk                            (0x3UL << RNG_CONFIG_POST_MODE_Pos)
#define RNG_CONFIG_POST_MODE                                RNG_CONFIG_POST_MODE_Msk
#define RNG_CONFIG_LFSR_MODE_Pos                            (9U)
#define RNG_CONFIG_LFSR_MODE_Len                            (1U)
#define RNG_CONFIG_LFSR_MODE_Msk                            (0x1UL << RNG_CONFIG_LFSR_MODE_Pos)
#define RNG_CONFIG_LFSR_MODE                                RNG_CONFIG_LFSR_MODE_Msk
#define RNG_CONFIG_LFSR_SEED_SEL_Pos                        (10U)
#define RNG_CONFIG_LFSR_SEED_SEL_Len                        (3U)
#define RNG_CONFIG_LFSR_SEED_SEL_Msk                        (0x7UL << RNG_CONFIG_LFSR_SEED_SEL_Pos)
#define RNG_CONFIG_LFSR_SEED_SEL                            RNG_CONFIG_LFSR_SEED_SEL_Msk
#define RNG_CONFIG_IRQ_EN_Pos                               (13U)
#define RNG_CONFIG_IRQ_EN_Len                               (1U)
#define RNG_CONFIG_IRQ_EN_Msk                               (0x1UL << RNG_CONFIG_IRQ_EN_Pos)
#define RNG_CONFIG_IRQ_EN                                   RNG_CONFIG_IRQ_EN_Msk
#define RNG_CONFIG_FRO_EN_Pos                               (15U)
#define RNG_CONFIG_FRO_EN_Len                               (1U)
#define RNG_CONFIG_FRO_EN_Msk                               (0x1UL << RNG_CONFIG_FRO_EN_Pos)
#define RNG_CONFIG_FRO_EN                                   RNG_CONFIG_FRO_EN_Msk

/*******************  Bit definition for RNG_TSCON register  *************/
#define RNG_TSCON_TRDY_TIME_Pos                             (0U)
#define RNG_TSCON_TRDY_TIME_Len                             (8U)
#define RNG_TSCON_TRDY_TIME_Msk                             (0xFUL << RNG_TSCON_TRDY_TIME_Pos)
#define RNG_TSCON_TRDY_TIME                                 RNG_TSCON_TRDY_TIME_Msk
#define RNG_TSCON_FRO_CHAIN_Pos                             (11U)
#define RNG_TSCON_FRO_CHAIN_Len                             (4U)
#define RNG_TSCON_FRO_CHAIN_Msk                             (0xFUL << RNG_TSCON_FRO_CHAIN_Pos)
#define RNG_TSCON_FRO_CHAIN                                 RNG_TSCON_FRO_CHAIN_Msk

/*******************  Bit definition for RNG_FROCFG register  *************/
#define RNG_FROCFG_CHAINE_EN_Pos                            (0U)
#define RNG_FROCFG_CHAINE_EN_Len                            (8U)
#define RNG_FROCFG_CHAINE_EN_Msk                            (0xFFUL << RNG_FROCFG_CHAINE_EN_Pos)
#define RNG_FROCFG_CHAINE_EN                                RNG_FROCFG_CHAINE_EN_Msk
#define RNG_FROCFG_TEST_IN_Pos                              (8U)
#define RNG_FROCFG_TEST_IN_Len                              (8U)
#define RNG_FROCFG_TEST_IN_Msk                              (0xFFUL << RNG_FROCFG_TEST_IN_Pos)
#define RNG_FROCFG_TEST_IN                                  RNG_FROCFG_TEST_IN_Msk

/*******************  Bit definition for RNG_USER_SEED register  *************/
#define RNG_USER_SEED_Pos                                   (0U)
#define RNG_USER_SEED_Len                                   (16U)
#define RNG_USER_SEED_Msk                                   (0xFFUL << RNG_USER_SEED_Pos)
#define RNG_USER_SEED                                       RNG_USER_SEED_Msk

/*******************  Bit definition for RNG_LRCON register  *****************/
#define RNG_LRCON_TEST_EN_Pos                               (0U)
#define RNG_LRCON_TEST_EN_Len                               (1U)
#define RNG_LRCON_TEST_EN_Msk                               (0x1UL << RNG_LRCON_TEST_EN_Pos)
#define RNG_LRCON_TEST_EN                                   RNG_LRCON_TEST_EN_Msk
#define RNG_LRCON_TEST_LIMIT_Pos                            (1U)
#define RNG_LRCON_TEST_LIMIT_Len                            (5U)
#define RNG_LRCON_TEST_LIMIT_Msk                            (0x1FUL << RNG_LRCON_TEST_LIMIT_Pos)
#define RNG_LRCON_TEST_LIMIT                                RNG_LRCON_TEST_LIMIT_Msk


/* ================================================================================================================= */
/* ================                                        SADC                                     ================ */
/* ================================================================================================================= */
/*******************  Bit definition for SADC_FIFO_RD register  *******************/
#define SADC_FIFO_RD_DATA_POS                               (0U)
#define SADC_FIFO_RD_DATA_Len                               (32U)
#define SADC_FIFO_RD_DATA_Msk                               (0xFFFFFFFFUL << SADC_FIFO_RD_DATA_POS)
#define SADC_FIFO_RD_DATA                                   SADC_FIFO_RD_DATA_Msk

/*******************  Bit definition for SADC_FIFO_THD register  *******************/
#define SADC_FIFO_THD_FIFO_THD_POS                          (0U)
#define SADC_FIFO_THD_FIFO_THD_Len                          (6U)
#define SADC_FIFO_THD_FIFO_THD_Msk                          (0x3FUL << SADC_FIFO_THD_FIFO_THD_POS)
#define SADC_FIFO_THD_FIFO_THD                              SADC_FIFO_THD_FIFO_THD_Msk

/*******************  Bit definition for SADC_FIFO_STAT register  *******************/
#define SADC_FIFO_STAT_COUNT_POS                            (0U)
#define SADC_FIFO_STAT_COUNT_Len                            (7U)
#define SADC_FIFO_STAT_COUNT_Msk                            (0x7FUL << SADC_FIFO_STAT_COUNT_POS)
#define SADC_FIFO_STAT_COUNT                                SADC_FIFO_STAT_COUNT_Msk

#define SADC_FIFO_STAT_VALID_POS                            (8U)
#define SADC_FIFO_STAT_VALID_Len                            (1U)
#define SADC_FIFO_STAT_VALID_Msk                            (0x1UL << SADC_FIFO_STAT_VALID_POS)
#define SADC_FIFO_STAT_VALID                                SADC_FIFO_STAT_VALID_Msk

#define SADC_FIFO_STAT_FLUSH_POS                            (16U)
#define SADC_FIFO_STAT_FLUSH_Len                            (1U)
#define SADC_FIFO_STAT_FLUSH_Msk                            (0x1UL << SADC_FIFO_STAT_FLUSH_POS)
#define SADC_FIFO_STAT_FLUSH                                SADC_FIFO_STAT_FLUSH_Msk

/*******************  Bit definition for SADC_CLK register  *******************/
#define SADC_CLK_CLK_SEL_POS                                (0U)
#define SADC_CLK_CLK_SEL_Len                                (3U)
#define SADC_CLK_CLK_SEL_Msk                                (0x7UL << SADC_CLK_CLK_SEL_POS)
#define SADC_CLK_CLK_SEL                                    SADC_CLK_CLK_SEL_Msk

#define SADC_CLK_CLK_RD_POS                                 (16U)
#define SADC_CLK_CLK_RD_Len                                 (3U)
#define SADC_CLK_CLK_RD_Msk                                 (0x7UL << SADC_CLK_CLK_RD_POS)
#define SADC_CLK_CLK_RD                                     SADC_CLK_CLK_RD_Msk

#define SADC_CLK_None_POS                                   (19U)
#define SADC_CLK_None_Len                                   (13U)
#define SADC_CLK_None_Msk                                   (0x1FFFUL << SADC_CLK_None_POS)
#define SADC_CLK_None                                       SADC_CLK_None_Msk

/*******************  Bit definition for SADC_GET_TKN_HW register  *******************/
#define SADC_GET_TKN_HW_LOCKED_POS                          (0U)
#define SADC_GET_TKN_HW_LOCKED_Len                          (1U)
#define SADC_GET_TKN_HW_LOCKED_Msk                          (0x1UL << SADC_GET_TKN_HW_LOCKED_POS)
#define SADC_GET_TKN_HW_LOCKED                              SADC_GET_TKN_HW_LOCKED_Msk

#define SADC_GET_TKN_HW_OWNER_POS                           (8U)
#define SADC_GET_TKN_HW_OWNER_Len                           (1U)
#define SADC_GET_TKN_HW_OWNER_Msk                           (0x1UL << SADC_GET_TKN_HW_OWNER_POS)
#define SADC_GET_TKN_HW_OWNER                               SADC_GET_TKN_HW_OWNER_Msk

/*******************  Bit definition for SADC_GET_TKN_SW register  *******************/
#define SADC_GET_TKN_SW_LOCKED_POS                          (0U)
#define SADC_GET_TKN_SW_LOCKED_Len                          (1U)
#define SADC_GET_TKN_SW_LOCKED_Msk                          (0x1UL << SADC_GET_TKN_SW_LOCKED_POS)
#define SADC_GET_TKN_SW_LOCKED                              SADC_GET_TKN_SW_LOCKED_Msk

#define SADC_GET_TKN_SW_OWNER_POS                           (8U)
#define SADC_GET_TKN_SW_OWNER_Len                           (1U)
#define SADC_GET_TKN_SW_OWNER_Msk                           (0x1UL << SADC_GET_TKN_SW_OWNER_POS)
#define SADC_GET_TKN_SW_OWNER                               SADC_GET_TKN_SW_OWNER_Msk

/*******************  Bit definition for SADC_RET_TKN_HW register  *******************/
#define SADC_RET_TKN_HW_RELEASE_POS                         (0U)
#define SADC_RET_TKN_HW_RELEASE_Len                         (1U)
#define SADC_RET_TKN_HW_RELEASE_Msk                         (0x1UL << SADC_RET_TKN_HW_RELEASE_POS)
#define SADC_RET_TKN_HW_RELEASE                             SADC_RET_TKN_HW_RELEASE_Msk

/*******************  Bit definition for SADC_RET_TKN_SW register  *******************/
#define SADC_RET_TKN_SW_RELEASE_POS                         (0U)
#define SADC_RET_TKN_SW_RELEASE_Len                         (1U)
#define SADC_RET_TKN_SW_RELEASE_Msk                         (0x1UL << SADC_RET_TKN_SW_RELEASE_POS)
#define SADC_RET_TKN_SW_RELEASE                             SADC_RET_TKN_SW_RELEASE_Msk

/*******************  Bit definition for SADC_TKN_STAT register  *******************/
#define SADC_TKN_STAT_LOCKED_POS                            (0U)
#define SADC_TKN_STAT_LOCKED_Len                            (1U)
#define SADC_TKN_STAT_LOCKED_Msk                            (0x1UL << SADC_TKN_STAT_LOCKED_POS)
#define SADC_TKN_STAT_LOCKED                                SADC_TKN_STAT_LOCKED_Msk

#define SADC_TKN_STAT_OWNER_POS                             (8U)
#define SADC_TKN_STAT_OWNER_Len                             (1U)
#define SADC_TKN_STAT_OWNER_Msk                             (0x1UL << SADC_TKN_STAT_OWNER_POS)
#define SADC_TKN_STAT_OWNER                                 SADC_TKN_STAT_OWNER_Msk

/* ================================================================================================================= */
/* ================                                        SADC                                      ================ */
/* ================================================================================================================= */
/*******************  Bit definition for SADC_FIFO_RD register  *******************/
#define SADC_FIFO_RD_DATA_POS                               (0U)
#define SADC_FIFO_RD_DATA_Len                               (32U)
#define SADC_FIFO_RD_DATA_Msk                               (0xFFFFFFFFUL << SADC_FIFO_RD_DATA_POS)
#define SADC_FIFO_RD_DATA                                   SADC_FIFO_RD_DATA_Msk

/*******************  Bit definition for SADC_FIFO_THD register  *******************/
#define SADC_FIFO_THD_FIFO_THD_POS                          (0U)
#define SADC_FIFO_THD_FIFO_THD_Len                          (6U)
#define SADC_FIFO_THD_FIFO_THD_Msk                          (0x3FUL << SADC_FIFO_THD_FIFO_THD_POS)
#define SADC_FIFO_THD_FIFO_THD                              SADC_FIFO_THD_FIFO_THD_Msk

/*******************  Bit definition for SADC_FIFO_STAT register  *******************/
#define SADC_FIFO_STAT_COUNT_POS                            (0U)
#define SADC_FIFO_STAT_COUNT_Len                            (7U)
#define SADC_FIFO_STAT_COUNT_Msk                            (0x7FUL << SADC_FIFO_STAT_COUNT_POS)
#define SADC_FIFO_STAT_COUNT                                SADC_FIFO_STAT_COUNT_Msk

#define SADC_FIFO_STAT_VALID_POS                            (8U)
#define SADC_FIFO_STAT_VALID_Len                            (1U)
#define SADC_FIFO_STAT_VALID_Msk                            (0x1UL << SADC_FIFO_STAT_VALID_POS)
#define SADC_FIFO_STAT_VALID                                SADC_FIFO_STAT_VALID_Msk

#define SADC_FIFO_STAT_FLUSH_POS                            (16U)
#define SADC_FIFO_STAT_FLUSH_Len                            (1U)
#define SADC_FIFO_STAT_FLUSH_Msk                            (0x1UL << SADC_FIFO_STAT_FLUSH_POS)
#define SADC_FIFO_STAT_FLUSH                                SADC_FIFO_STAT_FLUSH_Msk

/*******************  Bit definition for SADC_CLK register  *******************/
#define SADC_CLK_CLK_SEL_POS                                (0U)
#define SADC_CLK_CLK_SEL_Len                                (3U)
#define SADC_CLK_CLK_SEL_Msk                                (0x7UL << SADC_CLK_CLK_SEL_POS)
#define SADC_CLK_CLK_SEL                                    SADC_CLK_CLK_SEL_Msk

#define SADC_CLK_CLK_RD_POS                                 (16U)
#define SADC_CLK_CLK_RD_Len                                 (3U)
#define SADC_CLK_CLK_RD_Msk                                 (0x7UL << SADC_CLK_CLK_RD_POS)
#define SADC_CLK_CLK_RD                                     SADC_CLK_CLK_RD_Msk

/*******************  Bit definition for SADC_GET_TKN_HW register  *******************/
#define SADC_GET_TKN_HW_LOCKED_POS                          (0U)
#define SADC_GET_TKN_HW_LOCKED_Len                          (1U)
#define SADC_GET_TKN_HW_LOCKED_Msk                          (0x1UL << SADC_GET_TKN_HW_LOCKED_POS)
#define SADC_GET_TKN_HW_LOCKED                              SADC_GET_TKN_HW_LOCKED_Msk

#define SADC_GET_TKN_HW_OWNER_POS                           (8U)
#define SADC_GET_TKN_HW_OWNER_Len                           (1U)
#define SADC_GET_TKN_HW_OWNER_Msk                           (0x1UL << SADC_GET_TKN_HW_OWNER_POS)
#define SADC_GET_TKN_HW_OWNER                               SADC_GET_TKN_HW_OWNER_Msk

/*******************  Bit definition for SADC_GET_TKN_SW register  *******************/
#define SADC_GET_TKN_SW_LOCKED_POS                          (0U)
#define SADC_GET_TKN_SW_LOCKED_Len                          (1U)
#define SADC_GET_TKN_SW_LOCKED_Msk                          (0x1UL << SADC_GET_TKN_SW_LOCKED_POS)
#define SADC_GET_TKN_SW_LOCKED                              SADC_GET_TKN_SW_LOCKED_Msk

#define SADC_GET_TKN_SW_OWNER_POS                           (8U)
#define SADC_GET_TKN_SW_OWNER_Len                           (1U)
#define SADC_GET_TKN_SW_OWNER_Msk                           (0x1UL << SADC_GET_TKN_SW_OWNER_POS)
#define SADC_GET_TKN_SW_OWNER                               SADC_GET_TKN_SW_OWNER_Msk

/*******************  Bit definition for SADC_RET_TKN_HW register  *******************/
#define SADC_RET_TKN_HW_RELEASE_POS                         (0U)
#define SADC_RET_TKN_HW_RELEASE_Len                         (1U)
#define SADC_RET_TKN_HW_RELEASE_Msk                         (0x1UL << SADC_RET_TKN_HW_RELEASE_POS)
#define SADC_RET_TKN_HW_RELEASE                             SADC_RET_TKN_HW_RELEASE_Msk

/*******************  Bit definition for SADC_RET_TKN_SW register  *******************/
#define SADC_RET_TKN_SW_RELEASE_POS                         (0U)
#define SADC_RET_TKN_SW_RELEASE_Len                         (1U)
#define SADC_RET_TKN_SW_RELEASE_Msk                         (0x1UL << SADC_RET_TKN_SW_RELEASE_POS)
#define SADC_RET_TKN_SW_RELEASE                             SADC_RET_TKN_SW_RELEASE_Msk

/*******************  Bit definition for SADC_TKN_STAT register  *******************/
#define SADC_TKN_STAT_LOCKED_POS                            (0U)
#define SADC_TKN_STAT_LOCKED_Len                            (1U)
#define SADC_TKN_STAT_LOCKED_Msk                            (0x1UL << SADC_TKN_STAT_LOCKED_POS)
#define SADC_TKN_STAT_LOCKED                                SADC_TKN_STAT_LOCKED_Msk

#define SADC_TKN_STAT_OWNER_POS                             (8U)
#define SADC_TKN_STAT_OWNER_Len                             (1U)
#define SADC_TKN_STAT_OWNER_Msk                             (0x1UL << SADC_TKN_STAT_OWNER_POS)
#define SADC_TKN_STAT_OWNER                                 SADC_TKN_STAT_OWNER_Msk

/** @} */ /* End of group Peripheral_Registers_Bits_Definition */

/** @addtogroup Exported_macros
  * @{
  */
/****************************** GPIO instances ********************************/
#define IS_GPIO_ALL_INSTANCE(__INSTANCE__)      (((__INSTANCE__) == GPIO0) || \
                                                 ((__INSTANCE__) == GPIO1))

/****************************** I2C instances *********************************/
#define IS_I2C_ALL_INSTANCE(__INSTANCE__)       (((__INSTANCE__) == I2C0) || \
                                                 ((__INSTANCE__) == I2C1))

/****************************** UART instances ********************************/
#define IS_UART_ALL_INSTANCE(__INSTANCE__)      (((__INSTANCE__) == UART0) || \
                                                 ((__INSTANCE__) == UART1))

/****************************** TIM instances *********************************/
#define IS_TIMER_ALL_INSTANCE(__INSTANCE__)     (((__INSTANCE__) == TIMER0) || \
                                                 ((__INSTANCE__) == TIMER1))

/****************************** DUAL TIM instances ****************************/
#define IS_DUAL_TIM_ALL_INSTANCE(__INSTANCE__)  (((__INSTANCE__) == DUAL_TIMER0) || \
                                                 ((__INSTANCE__) == DUAL_TIMER1))

/****************************** PWM instances *********************************/
#define IS_PWM_ALL_INSTANCE(__INSTANCE__)       (((__INSTANCE__) == PWM0) || \
                                                 ((__INSTANCE__) == PWM1))

/****************************** WDT instances *********************************/
#define IS_WDT_ALL_INSTANCE(__INSTANCE__)       (((__INSTANCE__) == WDT))

/****************************** SPI instances *********************************/
#define IS_SPI_ALL_INSTANCE(__INSTANCE__)       (((__INSTANCE__) == SPIM) || \
                                                 ((__INSTANCE__) == SPIS))

/****************************** AES Instances *********************************/
#define IS_AES_ALL_INSTANCE(__INSTANCE__)       (((__INSTANCE__) == AES))

/****************************** XQSPI Instances *******************************/
#define IS_XQSPI_ALL_INSTANCE(__INSTANCE__)     (((__INSTANCE__) == XQSPI))

/****************************** EFUSE Instances *******************************/
#define IS_EFUSE_ALL_INSTANCE(__INSTANCE__)     (((__INSTANCE__) == EFUSE))

/****************************** RNG Instances *******************************/
#define IS_RNG_ALL_INSTANCE(__INSTANCE__)       (((__INSTANCE__) == RNG))

/** @} */ /* End of group Exported_macros */


#ifdef __cplusplus
}
#endif

#endif /* __GR552xx_H__ */

/** @} */ /* End of group GR54xx */

/** @} */ /* End of group CMSIS_Device */
