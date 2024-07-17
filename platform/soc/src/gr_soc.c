#include "gr_soc.h"
#include "grx_hal.h"

#ifndef DRIVER_TEST
#include "gr_includes.h"
#endif

#include "platform_sdk.h"
#include "custom_config.h"
#include "hal_flash.h"
#include "pmu_calibration.h"
#include "app_pwr_mgmt.h"

#define PUYA_FLASH_HP_CMD               (0xA3)
#define PUYA_FLASH_HP_END_DUMMY         (2)

#define FALSH_HP_MODE                   LL_XQSPI_HP_MODE_EN
#define FLASH_HP_CMD                    PUYA_FLASH_HP_CMD
#define FLASH_HP_END_DUMMY              PUYA_FLASH_HP_END_DUMMY

#define SOFTWARE_REG1_ULTRA_DEEP_SLEEP_FLAG_POS       (29)

#define SDK_VER_MAJOR                   1
#define SDK_VER_MINOR                   0
#define SDK_VER_BUILD                   6
#define COMMIT_ID                       0x74461bed

static const sdk_version_t sdk_version = {SDK_VER_MAJOR,
                                          SDK_VER_MINOR,
                                          SDK_VER_BUILD,
                                          COMMIT_ID,};//sdk version

void sys_sdk_verison_get(sdk_version_t *p_version)
{
    memcpy(p_version, &sdk_version, sizeof(sdk_version_t));
}

#if (BLE_SUPPORT == 1)
#ifndef DRIVER_TEST
static mesh_config_dev_num_t mesh_config_dev_mun =
{
    .mesh_net_key_list_num = 0,
    .mesh_app_key_list_num = 0,
    .mesh_piblic_subscr_list_num = 0,
    .mesh_friend_num = 0,
    .mesh_LPN_num = 0
};
#endif
#endif

__ALIGNED(0x100) FuncVector_t FuncVector_table[MAX_NUMS_IRQn + NVIC_USER_IRQ_OFFSET] = {
    0,
    Reset_Handler,
    NMI_Handler,
    HardFault_Handler,
    MemManage_Handler,
    BusFault_Handler,
    UsageFault_Handler,
    0,
    0,
    0,
    0,
    SVC_Handler,
    DebugMon_Handler,
    0,
    PendSV_Handler,
    SysTick_Handler,
};

void soc_register_nvic(IRQn_Type indx, uint32_t func)
{
    FuncVector_table[indx + NVIC_USER_IRQ_OFFSET] = (FuncVector_t)func;
}

static fun_t svc_user_func = NULL;

void svc_func_register(uint8_t svc_num, uint32_t user_func)
{
    svc_user_func = (fun_t)user_func;
}

void svc_user_handler(uint8_t svc_num)
{
    if (svc_user_func)
        svc_user_func();
}

#if (BLE_SUPPORT == 1)
__WEAK void nvds_init_error_handler(uint8_t err_code)
{
#ifdef NVDS_START_ADDR
    nvds_deinit(NVDS_START_ADDR, NVDS_NUM_SECTOR);
    nvds_init(NVDS_START_ADDR, NVDS_NUM_SECTOR);
#else
    /* nvds_deinit will erase the flash area and old data will be lost */
    nvds_deinit(0, NVDS_NUM_SECTOR);
    nvds_init(0, NVDS_NUM_SECTOR);
#endif
}

static void nvds_setup(void)
{
#ifndef DRIVER_TEST
    nvds_retention_size(CFG_MAX_BOND_DEVS, mesh_config_dev_mun);
#endif

#ifdef NVDS_START_ADDR
    uint8_t err_code = nvds_init(NVDS_START_ADDR, NVDS_NUM_SECTOR);
#else
    uint8_t err_code = nvds_init(0, NVDS_NUM_SECTOR);
#endif
    uint8_t init_err_code = nvds_get_init_error_info();

    switch(err_code)
    {
        case NVDS_SUCCESS:
            break;
        default:
            /* Nvds initialization other errors.
             * For more information, please see NVDS_INIT_ERR_CODE. */
            nvds_init_error_handler(err_code);
            break;
    }
}
#endif

uint8_t sys_device_reset_reason(void)
{
   uint8_t reset_season = AON_CTL->DBG_REG_RST_SRC & 0x3FUL;

   AON_CTL->DBG_REG_RST_SRC = AON_CTL->DBG_REG_RST_SRC | reset_season;
   if(SYS_RESET_REASON_AONWDT & reset_season)
   {
       return SYS_RESET_REASON_AONWDT;
   }
   else
   {
       return SYS_RESET_REASON_NONE;
   }
}

void first_class_task(void)
{
    ll_xqspi_hp_init_t hp_init;

    platform_exflash_env_init();

    hp_init.xqspi_hp_enable    = FALSH_HP_MODE;
    hp_init.xqspi_hp_cmd       = FLASH_HP_CMD;
    hp_init.xqspi_hp_end_dummy = FLASH_HP_END_DUMMY;
    hal_exflash_enable_quad(hp_init);

#if (BLE_SUPPORT == 1)
    /* set sram power state. */
    mem_pwr_mgmt_mode_set(MEM_POWER_AUTO_MODE);

    /* nvds module init process. */
    nvds_setup();

    /* platform init process. */
    platform_sdk_init();
#endif
}

extern bool clock_calibration_is_done(void);
static bool wait_for_clock_calibration_done(uint32_t timeout)//unit:us
{
    bool ret = true;
    uint32_t wait_time = 0;

    while(!clock_calibration_is_done())
    {
        delay_us(1);
        if(++wait_time >= timeout)
        {
            ret = false;
            break;
        }
    }

    return ret;
}

void second_class_task(void)
{
#if (BLE_SUPPORT == 1)
    /* To choose the System clock source and set the accuracy of OSC. */
#if CFG_LPCLK_INTERNAL_EN
    platform_clock_init((mcu_clock_type_t)SYSTEM_CLOCK, RC_OSC_CLK, CFG_LF_ACCURACY_PPM, 0);
#else
    platform_clock_init((mcu_clock_type_t)SYSTEM_CLOCK, RTC_OSC_CLK, CFG_LF_ACCURACY_PPM, 0);
#endif

#if PMU_CALIBRATION_ENABLE && !defined(DRIVER_TEST)
    /* Enable auto pmu calibration function. */
    if(!CHECK_IS_ON_FPGA())
    {
        system_pmu_calibration_init(30000);
    }
#endif
    system_pmu_init((mcu_clock_type_t)SYSTEM_CLOCK);
#endif

    // pmu shall be init before clock set
    system_power_mode((sys_power_t)SYSTEM_POWER_MODE);
    SetSerialClock(SERIAL_S64M_CLK);
    SystemCoreSetClock((mcu_clock_type_t)SYSTEM_CLOCK);

#if (BLE_SUPPORT == 1)
    // recover the default setting by temperature, should be called in the end
    if(!CHECK_IS_ON_FPGA())
    {
        pmu_calibration_handler(NULL);
    }
    /* Init peripheral sleep management */
    app_pwr_mgmt_init();
    if(!CHECK_IS_ON_FPGA())
    {
        wait_for_clock_calibration_done(1000000);
    }
#endif
}

void otp_trim_init(void)
{
#if (BLE_SUPPORT == 1)
    if(SDK_SUCCESS != sys_trim_info_sync())
    {
        if(!CHECK_IS_ON_FPGA())
        {
            /* do nothing for not calibrated chips */
            while(1);
        }
    }
#endif
}

void platform_init(void)
{
    gr5xx_fpb_init(FPB_MODE_PATCH_AND_DEBUG);
    otp_trim_init();
    first_class_task();
    second_class_task();
}

void vector_table_init(void)
{
    __DMB(); // Data Memory Barrier
    FuncVector_table[0] = *(FuncVector_t *)(SCB->VTOR);
    SCB->VTOR = (uint32_t)FuncVector_table; // Set VTOR to the new vector table location
    __DSB(); // Data Synchronization Barrier to ensure all
}

void warm_boot_process(void)
{
#if (BLE_SUPPORT == 1)
    vector_table_init();
    pwr_mgmt_warm_boot();
#endif
}

/**
 ****************************************************************************************
 * @brief  Check whether the system wakes up from ultra deep sleep. If it wakes up from ultra
 *         deep sleep, reset the entire system. If not, do nothing.
 * @retval: void
 ****************************************************************************************
 */
static void ultra_deep_sleep_wakeup_handle(void)
{
    if (AON_CTL->SOFTWARE_REG1 & (1 << SOFTWARE_REG1_ULTRA_DEEP_SLEEP_FLAG_POS))
    {
        hal_nvic_system_reset();
        while (true)
            ;
    }
}

void soc_init(void)
{
    ultra_deep_sleep_wakeup_handle();
#if !defined(WDT_RUN_ENABLE) || (!WDT_RUN_ENABLE)
    /* Disable WDT */
    ll_aon_wdt_unlock();
    ll_aon_wdt_disable();
    while(ll_aon_wdt_is_busy());
    ll_aon_wdt_lock();
#endif

    platform_init();
}

__WEAK void sdk_init(void){};
