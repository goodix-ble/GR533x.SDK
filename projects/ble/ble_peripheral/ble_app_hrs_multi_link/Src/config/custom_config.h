/**
 ****************************************************************************************
 *
 * @file custom_config.h
 *
 * @brief Custom configuration file for applications.
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

/*
 * DEFINES
 *****************************************************************************************
 */
#ifndef __CUSTOM_CONFIG_H__
#define __CUSTOM_CONFIG_H__

// <<< Use Configuration Wizard in Context Menu >>>

// <h> Basic configuration

// <o> Chip version
#ifndef SOC_GR533X
#define SOC_GR533X
#endif

// <o> Select chip type
// <0=> GR5330AENI
// <1=> GR5331AENI
// <2=> GR5331CENI
// <3=> GR5332AENE
// <4=> GR5332CENE
#ifndef CHIP_TYPE
#define CHIP_TYPE                        4
#endif

// <o> Enable system fault trace module
// <0=> DISABLE
// <1=> ENABLE
#ifndef SYS_FAULT_TRACE_ENABLE
#define SYS_FAULT_TRACE_ENABLE           1
#endif

// <o> Enable callstack backtrace function
// <i> Default: 0
#ifndef ENABLE_BACKTRACE_FEA
#define ENABLE_BACKTRACE_FEA             0
#endif

// <o> Eanble APP log module
// <0=> DISABLE
// <1=> ENABLE
#ifndef APP_LOG_ENABLE
#define APP_LOG_ENABLE                   1
#endif

// <o> Eanble APP log store module
// <0=> DISABLE
// <1=> ENABLE
#ifndef APP_LOG_STORE_ENABLE
#define APP_LOG_STORE_ENABLE             0
#endif

// <o> Eanble APP Log via RTT module
// <0=> DISABLE
// <1=> ENABLE
#ifndef APP_LOG_PORT
#define APP_LOG_PORT                     0
#endif


// <o> Enable Platform Initialize
// <0=> DISABLE
// <1=> ENABLE
#ifndef PLATFORM_SDK_INIT_ENABLE
#define PLATFORM_SDK_INIT_ENABLE         1
#endif

// <o> Enable PMU Calibration
// <0=> DISABLE
// <1=> ENABLE
#ifndef PMU_CALIBRATION_ENABLE
#define PMU_CALIBRATION_ENABLE           1
#endif

// <o> The Number of sectors for NVDS
// <i> Default:  1
#ifndef NVDS_NUM_SECTOR
#define NVDS_NUM_SECTOR                  1
#endif

// <o> Call Stack Size
// <i> Default: 0x2000
#ifndef SYSTEM_STACK_SIZE
#if (CHIP_TYPE == 0)
#define SYSTEM_STACK_SIZE                0x1000
#else
#define SYSTEM_STACK_SIZE                0x2000
#endif
#endif

// <o> Call Heap Size
// <i> Default: 0x0000
#ifndef SYSTEM_HEAP_SIZE
#define SYSTEM_HEAP_SIZE                 0x0000
#endif

// </h>

// <h> Boot info configuration

// <o> Chip version
// <i> Default: 0x00
#ifndef CHIP_VER
#define CHIP_VER                         0x5332
#endif

// <o> Code load address
// <0x00202000=> Flash address
// <i> Default:  0x00202000(Flash)
#ifndef APP_CODE_LOAD_ADDR
#define APP_CODE_LOAD_ADDR               0x00202000
#endif

// <o> Code run address
// <0x20002000=> SRAM address
// <0x00202000=> Flash address
// <i> Default:  0x00202000(Flash XIP)
#ifndef APP_CODE_RUN_ADDR
#define APP_CODE_RUN_ADDR                0x00202000
#endif

// <ol.0..5> System clock
// <0=> 64MHZ
// <1=> 32MHZ
// <2=> 16MHZ-XO
// <3=> 16MHZ
// <4=> 8MHZ
// <5=> 2MHZ
#ifndef SYSTEM_CLOCK
#define SYSTEM_CLOCK                     0
#endif

// <ol.0..2> System power mode
// <0=> DCDC MODE
// <1=> SYSLDO MODE
#ifndef SYSTEM_POWER_MODE
#define SYSTEM_POWER_MODE                0
#endif

// <o> External clock accuracy used in the LL to compute timing  <1-500>
// <i> Range: 1-500
#ifndef CFG_LF_ACCURACY_PPM
#define CFG_LF_ACCURACY_PPM              500
#endif

// <o> Enable internal osc as low power clock
// <0=> Default: Disable internal osc as low power clock
// <1=> Enable internal osc as low power clock and force CFG_LF_ACCURACY_PPM to 500ppm
#ifndef CFG_LPCLK_INTERNAL_EN
#define CFG_LPCLK_INTERNAL_EN            0
#endif

// <o> Delay time for Boot startup
// <0=> Not Delay
// <1=> Delay 1s
#ifndef BOOT_LONG_TIME
#define BOOT_LONG_TIME                   1
#endif

// <o> In xip mode, check image during cold boot startup
// <0=> Not check
// <1=> Check image
#ifndef BOOT_CHECK_IMAGE
#define BOOT_CHECK_IMAGE                 0
#endif

// <o>  Support BLE
// <0=> MCU only, without BLE
// <1=> Support BLE
#ifndef BLE_SUPPORT
#define BLE_SUPPORT                   1
#endif

// <o>  Support BT-BR/EDR
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_BT_BREDR
#define CFG_BT_BREDR                     0
#endif

// <o> Enable DTM test support
// <0=> DISABLE
// <1=> ENABLE
#ifndef DTM_TEST_ENABLE
#define DTM_TEST_ENABLE                  0
#endif

// <o> RF TX PA select
// <1=> BLE_RF_TX_MODE_SPA_MODE  (-20~6 dBm TX power for GR5331/GR5330, -20~5 dBm TX power for GR5332)
// <2=> BLE_RF_TX_MODE_UPA_MODE  (-15~2 dBm TX power for GR5331/GR5330)
// <3=> BLE_RF_TX_MODE_HPA_MODE  (-10~15 dBm TX power for GR5332)
#ifndef RF_TX_PA_SELECT
#define RF_TX_PA_SELECT                  1
#endif

// <o>  matching circuit configuration
// <0=> 5th order matching circuit
// <1=> 3rd order matching circuit
#ifndef CFG_MATCHING_CIRCUIT
#define CFG_MATCHING_CIRCUIT             0
#endif

// <o> Enable patch
// <0=> DISABLE
// <1=> ENABLE
#ifndef CFG_PATCH_ENABLE
#define CFG_PATCH_ENABLE                 0
#endif

// </h>

// <h> BLE resource configuration
// <i> Note: The total number of BLE Activities(CONNECTIONS+ADVS+SCAN) should not exceed the limit 12.

// <o> Support maximum number of BLE profiles <1-64>
// <i> Range: 1-64
#ifndef CFG_MAX_PRFS
#define CFG_MAX_PRFS                     10
#endif

// <o> Support maximum number of bonded devices
#ifndef CFG_MAX_BOND_DEVS
#define CFG_MAX_BOND_DEVS                4
#endif

// <o> Support maximum number of BLE Links <1-10>
// <i> Range: 1-10
#ifndef CFG_MAX_CONNECTIONS
#define CFG_MAX_CONNECTIONS              5
#endif

// <o> Support maximum number of BLE Legacy/Extended Advertisings <0-5>
// <i> Range: 0-5
// <i> Note: The total number of BLE Legacy/Extended/Periodic Advertisings should not exceed the limit 5.
#ifndef CFG_MAX_ADVS
#define CFG_MAX_ADVS                     1
#endif

// <o> Support maximum number of BLE Scan <0-1>
// <i> Range: 0-1
#ifndef CFG_MAX_SCAN
#define CFG_MAX_SCAN                     0
#endif

// <o>  Support multiple link with the same device, this feature can't use for GR5330
// <0=> NOT SUPPORT
// <1=> SUPPORT
#if (CHIP_TYPE != 0)
#ifndef CFG_MUL_LINK_WITH_SAME_DEV
#define CFG_MUL_LINK_WITH_SAME_DEV       0
#endif
#endif

// <o>  Support car key needs
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_CAR_KEY_SUPPORT
#define CFG_CAR_KEY_SUPPORT              0
#endif

// <o> BLE controller only(use for extern host or HCI uart transport)
// <0=> Support BLE controller and host
// <1=> Support BLE controller only
#ifndef CFG_CONTROLLER_ONLY
#define CFG_CONTROLLER_ONLY              0
#endif

// <o>  Support master
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_MASTER_SUPPORT
#define CFG_MASTER_SUPPORT               1
#endif

// <o>  Support slave
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_SLAVE_SUPPORT
#define CFG_SLAVE_SUPPORT                1
#endif

// <o>  Support legacy pair
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_LEGACY_PAIR_SUPPORT
#define CFG_LEGACY_PAIR_SUPPORT          1
#endif

// <o>  Support sc pair
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_SC_PAIR_SUPPORT
#define CFG_SC_PAIR_SUPPORT              1
#endif

// <o>  Support coc
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_COC_SUPPORT
#define CFG_COC_SUPPORT                  1
#endif

// <o>  Support gatt server
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_GATTS_SUPPORT
#define CFG_GATTS_SUPPORT                1
#endif

// <o>  Support gatt client
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_GATTC_SUPPORT
#define CFG_GATTC_SUPPORT                1
#endif

// <o>  Support connection aoa/aod
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_CONN_AOA_AOD_SUPPORT
#define CFG_CONN_AOA_AOD_SUPPORT         0
#endif

// <o>  Support connectionless aoa/aod
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_CONNLESS_AOA_AOD_SUPPORT
#define CFG_CONNLESS_AOA_AOD_SUPPORT     0
#endif

// <o>  Support ranging
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_RANGING_SUPPORT
#define CFG_RANGING_SUPPORT              0
#endif

// </h>

// <h> MESH support configuration
// <o>  Support MESH
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_MESH_SUPPORT
#define CFG_MESH_SUPPORT                 0
#endif
// </h>

// <h> sniffer support configuration
// <o>  Support sniffer
// <0=> NOT SUPPORT
// <1=> SUPPORT
#ifndef CFG_SNIFFER_SUPPORT
#define CFG_SNIFFER_SUPPORT              0
#endif
// </h>

// <h> sniffer mng way configuration
// <o>  sniffer mng way
// <0=>  mng sniffer by ble link
// <1=>  mng sniffer by uart
#ifndef CFG_SNIFFER_MNG_BY_UART
#define CFG_SNIFFER_MNG_BY_UART              0
#endif
// </h>

// <h> Security configuration
// <o> algorithm security level
// <0=> Enable algorithm level one
// <1=> Enable algorithm level two
#ifndef SECURITY_CFG_VAL
#define SECURITY_CFG_VAL                 0
#endif
// </h>

// <h> WDT function configuration
// <o> mode select
// <0=> Disable WDT run in background
// <1=> Enable WDT run in background
#ifndef WDT_RUN_ENABLE
#define WDT_RUN_ENABLE                 0
#endif
// </h>

// <<< end of configuration section >>>
#endif //__CUSTOM_CONFIG_H__
