#ifndef GR_SOC_H
#define GR_SOC_H

#include "grx_sys.h"

extern void Reset_Handler(void);
extern void NMI_Handler(void);
extern void HardFault_Handler(void);
extern void MemManage_Handler(void);
extern void BusFault_Handler(void);
extern void UsageFault_Handler(void);
extern void SVC_Handler(void);
extern void DebugMon_Handler(void);
extern void PendSV_Handler(void);
extern void SysTick_Handler(void);

extern void platform_exflash_env_init(void);
extern void vector_table_init(void);
extern void soc_init(void);
extern void warm_boot_process(void);
extern void platform_init(void);
extern void soc_register_nvic(IRQn_Type indx, uint32_t func);
extern uint32_t get_wakeup_flag(void);

extern uint32_t nvds_get_start_addr(void);
extern uint8_t  nvds_get_init_error_info(void);
extern uint16_t sys_trim_info_sync(void);

typedef void (*FuncVector_t)(void);

#endif

