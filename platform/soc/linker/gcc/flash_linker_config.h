/**
 ****************************************************************************************
 *
 * @file flash_linker_config.h
 *
 * @brief Common link script definition file.
 *
 *
 ****************************************************************************************
 */

#ifndef __FLASH_LINKER_CONFIG_H__
#define __FLASH_LINKER_CONFIG_H__

#include "custom_config.h"
#if BLE_SUPPORT
#include "ble_em_map.h"
#endif

/*****************************************************************
 * if CSTACK_HEAP_SIZE is not defined in custom_config.h,
 * keep default setting to 32KB
 */
#ifndef CSTACK_HEAP_SIZE
    #define CSTACK_HEAP_SIZE      0x8000
#endif

#define FLASH_START_ADDR         0x00200000
#define FLASH_SIZE               0x00080000 //512KB


#define RAM_START_ADDR            0x00100000
#define HIGH_RAM_OFFSET           0x1FF00000
#define FPB_DATA_SPACE_SIZE       0x50
#define RAM_CODE_SPACE_SIZE       (0x1000 - FPB_DATA_SPACE_SIZE)

/* size of ROM reserved RAM in retention cell */
#ifndef ROM_RTN_RAM_SIZE
#define ROM_RTN_RAM_SIZE          0x1E00
#endif

/*****************************************************************
 * Warning: User App developer never change the six macros below
 */
#define RAM_CODE_SPACE_START      (RAM_START_ADDR + ROM_RTN_RAM_SIZE)
#define FPB_DATA_SPACE_START      (RAM_START_ADDR + ROM_RTN_RAM_SIZE + RAM_CODE_SPACE_SIZE + HIGH_RAM_OFFSET)

#define RAM_SIZE              0x00018000 //96KB


#if BLE_SUPPORT
    #define RAM_END_ADDR              (RAM_START_ADDR + HIGH_RAM_OFFSET + RAM_SIZE - BLE_EM_USED_SIZE)
#else
    #define RAM_END_ADDR              (RAM_START_ADDR + HIGH_RAM_OFFSET + RAM_SIZE)
#endif

#define FERP_SIZE                 0x8000     //32K
#define CRITICAL_CODE_MAX_SIZE    0x10000    // maximum size of critical code reserved

#ifdef CFG_FERP
    #define STACK_END_ADDR        (RAM_END_ADDR-FERP_SIZE)
#else
    #define STACK_END_ADDR        (RAM_END_ADDR)
#endif

#if ((APP_CODE_RUN_ADDR == APP_CODE_LOAD_ADDR) && \
        (APP_CODE_RUN_ADDR >= FLASH_START_ADDR) && \
        (APP_CODE_RUN_ADDR < FLASH_START_ADDR + FLASH_SIZE))
    #define XIP_MODE
#endif

#if ((APP_CODE_RUN_ADDR > (RAM_START_ADDR + HIGH_RAM_OFFSET)) && \
        (APP_CODE_RUN_ADDR < (RAM_START_ADDR + HIGH_RAM_OFFSET + RAM_SIZE)))
    #define HMIRROR_MODE
#endif

#define APP_MAX_CODE_SIZE         FLASH_SIZE
#define APP_RAM_SIZE              RAM_SIZE

#endif // __FLASH_LINKER_CONFIG_H__

