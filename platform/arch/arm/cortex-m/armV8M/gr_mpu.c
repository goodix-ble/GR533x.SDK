/**
  ******************************************************************************
  * @file    gr_mpu.c
  * @author  BLE Driver Team
  * @brief   CORTEX HAL module driver.
  *          This file provides firmware functions to manage the following
  *          functionalities of the CORTEX:
  *           + Initialization and de-initialization functions
  *           + Peripheral Control functions
  *
  *  @verbatim
  ==============================================================================
                        ##### How to use MPU #####
  ==============================================================================
    A. Configure MPU region, include start address, end address, access permission etc.
       Up to 8 MPU regions can be configured.
       The size of an MPU region can be any size in the granularity of 32 bytes.
       The starting address of an MPU region can now also be in any address which is a multiple of 32 bytes.
       Does not allow MPU regions to be overlapped.
    B. Enable MPU.

Example usage:
#include "gr_mpu.h"
void mpu_setup(void)
{
    mpu_region_init_t mpu_region;
    memset((void *)&mpu_region, 0 ,sizeof(mpu_region));
    mpu_region.enable = MPU_REGION_ENABLE;

    // Set address [0, 0x20000000] to read-only. Code region Writing is prohibited
    mpu_region.number = MPU_REGION_NUMBER7;
    mpu_region.base_address = 0;
    mpu_region.limit_address = 0x20000000;
    mpu_region.access_permission = MPU_REGION_ALL_RO;
    hal_mpu_config_region(&mpu_region);

    hal_mpu_enable(MPU_PRIVILEGED_DEFAULT);

    // Add stack limit checking(check stack overflow)
#if defined ( __CC_ARM ) || defined(__ARMCC_VERSION)
    extern uint32_t Image$$ARM_LIB_STACK$$ZI$$Base;
    uint32_t msp_min_addr = (uint32_t )&Image$$ARM_LIB_STACK$$ZI$$Base;
#elif defined ( __ICCARM__ )
    uint32_t msp_min_addr = (uint32_t )&__section_begin("CSTACK");
#elif defined ( __GNUC__ )
    extern char* __StackLimit;
    uint32_t msp_min_addr = (uint32_t)&__StackLimit;
#else
   #error "Not Support Other Compiler"
#endif
    SCB->CCR |= SCB_CCR_STKOFHFNMIGN_Msk; // Allows HardFault and NMI handlers to bypass stack limit checks
    __set_MSPLIM(msp_min_addr);
}
  @endverbatim
  */

/* Includes ------------------------------------------------------------------*/

#include "gr5x.h"
#include "gr_common.h"
#include "gr_mpu.h"
#include "custom_config.h"
#if (CFG_APP_DRIVER_SUPPORT == 1)
#include "app_pwr_mgmt.h"
#endif

/** @addtogroup HAL_DRIVER
  * @{
  */

#ifdef HAL_MPU_V8

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Exported functions ---------------------------------------------------------*/

/** @defgroup CORTEX_Exported_Functions CORTEX Exported Functions
  * @{
  */


/** @defgroup CORTEX_Exported_Functions_Group1 Initialization and de-initialization functions
  * @{
  */

//__WEAK void hal_nvic_set_priority_grouping(uint32_t priority_group)
//{
//    /* Check the parameters */
//    gr_assert_param(IS_NVIC_PRIORITY_GROUP(priority_group));

//    /* Set the PRIGROUP[10:8] bits according to the PriorityGroup parameter value */
//    NVIC_SetPriorityGrouping(priority_group);
//}

//__WEAK void hal_nvic_set_priority(IRQn_Type IRQn, uint32_t preempt_priority, uint32_t sub_priority)
//{
//    uint32_t prioritygroup = 0x00U;

//    /* Check the parameters */
//    gr_assert_param(IS_NVIC_SUB_PRIORITY(sub_priority));
//    gr_assert_param(IS_NVIC_PREEMPTION_PRIORITY(preempt_priority));

//    prioritygroup = NVIC_GetPriorityGrouping();

//    NVIC_SetPriority(IRQn, NVIC_EncodePriority(prioritygroup, preempt_priority, sub_priority));
//}

//__WEAK void hal_nvic_enable_irq(IRQn_Type IRQn)
//{
//    /* Check the parameters */
//    gr_assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

//    /* Enable interrupt */
//    NVIC_EnableIRQ(IRQn);
//}

//__WEAK void hal_nvic_disable_irq(IRQn_Type IRQn)
//{
//    /* Check the parameters */
//    gr_assert_param(IS_NVIC_DEVICE_IRQ(IRQn));

//    /* Disable interrupt */
//    NVIC_DisableIRQ(IRQn);
//}

//__WEAK void hal_nvic_system_reset(void)
//{
//    __set_PRIMASK(1); //Disable Global Interrupt.

//    //Power on memory
//    WRITE_REG(AON_MEM->MEM_PWR_WKUP0,   0x002AAAAAU);
//    WRITE_REG(AON_MEM->MEM_PWR_WKUP1, 0x000002AAU);
//    /* Write 1 to apply the memory settings in MEM_PWR_WKUP manually. */
//    WRITE_REG(AON_MEM->MEM_PWR_APPLY, AON_MEM_MEM_PWR_APPLY_APPLY);
//    /* during the bit being 1, writing mem_pwr_apply would not take any effect. */
//    while(READ_BITS(AON_MEM->MEM_PWR_APPLY, AON_MEM_MEM_PWR_APPLY_BUSY) == AON_MEM_MEM_PWR_APPLY_BUSY);

//    /* Disable isp check during cold start. */
//    //*(uint32_t *)(GR54XX_ALIAS_ADDRESS + 0x7FF0) = 0x676f6f64;

//    /* Clear the flag of cold boot. */
//    WRITE_REG(AON_CTRL->SW_REG0, 0x00U);

//    /* System Reset */
//    NVIC_SystemReset();
//}

/*
 * Note that the following operation only turns on timer, but does not turn on interrupt,
 * because RTOS compatible running environment
*/
__WEAK uint32_t hal_systick_config(uint32_t ticks)
{
    if ((ticks - 1UL) > SysTick_LOAD_RELOAD_Msk)
    {
       return (1UL);                                                  /* Reload value impossible */
    }

    SysTick->LOAD  = (uint32_t)(ticks - 1UL);                         /* set reload register */
    NVIC_SetPriority (SysTick_IRQn, (1UL << __NVIC_PRIO_BITS) - 1UL); /* set Priority for Systick Interrupt */
    SysTick->VAL   = 0UL;                                             /* Load the SysTick Counter Value */
    SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk |
                     SysTick_CTRL_TICKINT_Msk   |
                     SysTick_CTRL_ENABLE_Msk;                         /* Enable SysTick IRQ and SysTick Timer */
    return (0UL);
}
/** @} */

/** @defgroup CORTEX_Exported_Functions_Group2 Peripheral Control functions
  * @{
  */

#if (__MPU_PRESENT == 1U)

#define MPU_REGION_NUM   8U

/**
  * @brief MPU retention region register definition
  */
typedef struct
{
    uint32_t RBAR;     /*!< Region Base Address Register value */
    uint32_t RLAR;     /*!< Region Limit Address Register value */
} mpu_region_reg_t;

/**
  * @brief MPU retention register definition
  */
typedef struct
{
    uint32_t ctrl;                         /* MPU Control Register value */
    mpu_region_reg_t reg[MPU_REGION_NUM];  /* MPU Region Register value */
    uint32_t mair0;                        /* MPU Memory Attribute Indirection Register 0 */
    uint32_t mair1;                        /* MPU Memory Attribute Indirection Register 1 */
} mpu_retention_t;

static mpu_retention_t s_mpu_retention;

#if (CFG_APP_DRIVER_SUPPORT == 1)
static bool mpu_is_allow_sleep(void)
{
    hal_mpu_suspend_reg();
    return true;
}

static const app_sleep_callbacks_t s_mpu_sleep_cb =
{
    .app_prepare_for_sleep = mpu_is_allow_sleep,
    .app_wake_up_ind       = hal_mpu_resume_reg,
};
#endif

__WEAK void hal_mpu_suspend_reg(void)
{
    s_mpu_retention.ctrl = MPU->CTRL;
    s_mpu_retention.mair0 = MPU->MAIR0;
    s_mpu_retention.mair1 = MPU->MAIR1;
    for (uint32_t i = 0; i < MPU_REGION_NUM; i++)
    {
        MPU->RNR = i;
        s_mpu_retention.reg[i].RBAR = MPU->RBAR;
        s_mpu_retention.reg[i].RLAR = MPU->RLAR;
    }
}

__WEAK void hal_mpu_resume_reg(void)
{
    for (uint32_t i = 0; i < MPU_REGION_NUM; i++)
    {
        MPU->RNR = i;
        MPU->RBAR = s_mpu_retention.reg[i].RBAR;
        MPU->RLAR = s_mpu_retention.reg[i].RLAR;
    }
    MPU->MAIR0 = s_mpu_retention.mair0;
    MPU->MAIR1 = s_mpu_retention.mair1;
    MPU->CTRL  = s_mpu_retention.ctrl;
}

#ifdef HAL_PM_ENABLE
__WEAK hal_pm_status_t hal_pm_mpu_suspend(void)
{
    hal_mpu_suspend_reg();
    return HAL_PM_SLEEP;
}

__WEAK void hal_pm_mpu_resume(void)
{
    hal_mpu_resume_reg();
}
#endif /* HAL_PM_ENABLE */

__WEAK void hal_mpu_enable(uint32_t mpu_control)
{
    __DMB(); /* Data Memory Barrier operation to force any outstanding writes to memory before enabling the MPU */

    /* Enable the MPU */
    MPU->CTRL   = mpu_control | MPU_CTRL_ENABLE_Msk;

    __DSB(); /* Ensure that the subsequent instruction is executed only after the write to memory */
    __ISB(); /* Flush and refill pipeline with updated MPU configuration settings */

    /* MPU support sleep */
#if (CFG_APP_DRIVER_SUPPORT == 1)
    pwr_register_sleep_cb(&s_mpu_sleep_cb, WAKEUP_PRIORITY_LOW, MPU_PWR_ID);
#else
    /* Call hal_pm_mpu_resume/suspend in hal_pm_resume/suspend_user */
#endif
}

__WEAK void hal_mpu_disable(void)
{
    __DMB(); /* Force any outstanding transfers to complete before disabling MPU */

    /* Disable the MPU */
    MPU->CTRL  &= ~MPU_CTRL_ENABLE_Msk;

    __DSB(); /* Ensure that the subsequent instruction is executed only after the write to memory */
    __ISB(); /* Flush and refill pipeline with updated MPU configuration settings */

#if (CFG_APP_DRIVER_SUPPORT == 1)
    pwr_unregister_sleep_cb(MPU_PWR_ID);
#endif
}

__WEAK void hal_mpu_config_region(mpu_region_init_t *p_mpu_region_init)
{
    /* Check the parameters */
    gr_assert_param(IS_MPU_REGION_NUMBER(p_mpu_region_init->number));
    gr_assert_param(IS_MPU_REGION_ENABLE(p_mpu_region_init->enable));

    /* Follow ARM recommendation with Data Memory Barrier prior to MPU configuration */
    __DMB();

    /* Set the Region number */
    MPU->RNR = p_mpu_region_init->number;

    if (p_mpu_region_init->enable != MPU_REGION_DISABLE)
    {
        /* Check the parameters */
        gr_assert_param(IS_MPU_INSTRUCTION_ACCESS(p_mpu_region_init->disable_exec));
        gr_assert_param(IS_MPU_REGION_PERMISSION_ATTRIBUTE(p_mpu_region_init->access_permission));
        gr_assert_param(IS_MPU_ACCESS_SHAREABLE(p_mpu_region_init->is_shareable));

        MPU->RBAR = (((uint32_t)p_mpu_region_init->base_address               & 0xFFFFFFE0UL)  |
                     ((uint32_t)p_mpu_region_init->is_shareable           << MPU_RBAR_SH_Pos)  |
                     ((uint32_t)p_mpu_region_init->access_permission      << MPU_RBAR_AP_Pos)  |
                     ((uint32_t)p_mpu_region_init->disable_exec           << MPU_RBAR_XN_Pos));

        MPU->RLAR = (((uint32_t)p_mpu_region_init->limit_address                    & 0xFFFFFFE0UL) |
                     ((uint32_t)p_mpu_region_init->attributes_index       << MPU_RLAR_AttrIndx_Pos) |
                     ((uint32_t)p_mpu_region_init->enable                 << MPU_RLAR_EN_Pos));
    }
    else
    {
        MPU->RLAR = 0U;
        MPU->RBAR = 0U;
    }
}

__WEAK void hal_mpu_config_memory_attributes(mpu_attributes_init_t *p_mpu_attributes_init)
{
    __IO uint32_t *p_mair;
    uint32_t      attr_values;
    uint32_t      attr_number;

    /* Check the parameters */
    gr_assert_param(IS_MPU_ATTRIBUTES_NUMBER(p_mpu_attributes_init->number));
    /* No need to check Attributes value as all 0x0..0xFF possible */

    /* Follow ARM recommendation with Data Memory Barrier prior to MPU configuration */
    __DMB();

    if (p_mpu_attributes_init->number < MPU_ATTRIBUTES_NUMBER4)
    {
        /* Program MPU_MAIR0 */
        p_mair = &(MPU->MAIR0);
        attr_number = p_mpu_attributes_init->number;
    }
    else
    {
        /* Program MPU_MAIR1 */
        p_mair = &(MPU->MAIR1);
        attr_number = (uint32_t)p_mpu_attributes_init->number - 4U;
    }

    attr_values = *(p_mair);
    attr_values &=  ~(0xFFUL << (attr_number * 8U));
    *(p_mair) = attr_values | ((uint32_t)p_mpu_attributes_init->attributes << (attr_number * 8U));
}

#endif /* __MPU_PRESENT */

//__WEAK uint32_t hal_nvic_get_priority_grouping(void)
//{
//    /* Get the PRIGROUP[10:8] field value */
//    return NVIC_GetPriorityGrouping();
//}

//__WEAK void hal_nvic_get_priority(IRQn_Type IRQn, uint32_t priority_group, uint32_t *p_preempt_priority, uint32_t *p_sub_priority)
//{
//    /* Check the parameters */
//    gr_assert_param(IS_NVIC_PRIORITY_GROUP(priority_group));
//    /* Get priority for Cortex-M system or device specific interrupts */
//    NVIC_DecodePriority(NVIC_GetPriority(IRQn), priority_group, p_preempt_priority, p_sub_priority);
//}

//__WEAK void hal_nvic_set_pending_irq(IRQn_Type IRQn)
//{
//    /* Set interrupt pending */
//    NVIC_SetPendingIRQ(IRQn);
//}

//__WEAK uint32_t hal_nvic_get_pending_irq(IRQn_Type IRQn)
//{
//    /* Return 1 if pending else 0U */
//    return NVIC_GetPendingIRQ(IRQn);
//}

//__WEAK void hal_nvic_clear_pending_irq(IRQn_Type IRQn)
//{
//    /* Clear pending interrupt */
//    NVIC_ClearPendingIRQ(IRQn);
//}

//__WEAK uint32_t hal_nvic_get_active(IRQn_Type IRQn)
//{
//    /* Return 1 if active else 0U */
//    return NVIC_GetActive(IRQn);
//}


/** @} */

/** @} */

#endif /* HAL_CORTEX_MODULE_ENABLED */
/** @} */

/** @} */

