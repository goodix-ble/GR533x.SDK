#ifndef __GR_COMMON_H
#define __GR_COMMON_H

#include "cmsis_compiler.h"

/* Exported macro ------------------------------------------------------------*/
#ifdef  USE_FULL_ASSERT
/**
  * @brief  The gr_assert_param macro is used for function's parameters check.
  * @param  expr If expr is false, it calls assert_failed function
  *         which reports the name of the source file and the source
  *         line number of the call that failed.
  *         If expr is true, it returns no value.
  * @retval None
  */
#define gr_assert_param(expr) ((expr) ? (void)0U : assert_failed((char *)__FILE__, __LINE__))
/* Exported functions ------------------------------------------------------- */
__STATIC_INLINE void assert_failed(char *file, uint32_t line)
{

}
#else
#define gr_assert_param(expr) ((void)0U)
#endif /* USE_FULL_ASSERT */



/** @brief Disable interrupts globally in the system(apart from the NMI).
 *  This macro must be used in conjunction with the @ref GLOBAL_EXCEPTION_ENABLE macro
 *  since this last one will close the brace that the current macro opens.  This means
 *  that both macros must be located at the same scope level.
 */
#define GLOBAL_EXCEPTION_DISABLE()                         \
do {                                                       \
    uint32_t __l_irq_rest = __get_PRIMASK();               \
    __set_PRIMASK(1)


/** @brief Restore interrupts from the previous global disable(apart from the NMI).
 *  @sa GLOBAL_EXCEPTION_ENABLE
 */
#define GLOBAL_EXCEPTION_ENABLE()                          \
    if(__l_irq_rest == 0)                                  \
    {                                                      \
        __set_PRIMASK(0);                                  \
    }                                                      \
    else                                                   \
    {                                                      \
        __set_PRIMASK(1);                                  \
    }                                                      \
} while(0)

/** @brief Disable interrupts globally in the system.
 * This macro must be used in conjunction with the @ref GLOBAL_INT_RESTORE macro.
 */
#define GLOBAL_INT_DISABLE()                               \
do {                                                       \
    extern uint32_t global_int_disable(void);              \
    uint32_t __res_mask = global_int_disable()

/** @brief Restore global interrupt.
 *  @sa GLOBAL_INT_RESTORE
 */
#define GLOBAL_INT_RESTORE()                               \
    extern void global_int_enable(uint32_t mask);          \
    global_int_enable(__res_mask);                         \
} while(0)

/** @brief Disable external interrupts with a priority lower than IRQn_Type in the system.
 * This macro must be used in conjunction with the @ref LOCAL_INT_RESTORE macro
 * since this last one will close the brace that the current macro opens. This
 * means that both macros must be located at the same scope level.
 */
#define LOCAL_INT_DISABLE(IRQn_Type)                         \
do {                                                         \
    uint32_t __l_irq_rest = __get_BASEPRI();                 \
    __set_BASEPRI(NVIC_GetPriority(IRQn_Type) +              \
                 (1 << (NVIC_GetPriorityGrouping() + 1)));   \

/** @brief Restore external interrupts(apart from the BLE) from the previous disable.
 *  @sa EXP_BLE_INT_RESTORE
 */
#define LOCAL_INT_RESTORE()                                  \
    __set_BASEPRI(__l_irq_rest);                             \
} while(0)


/**
  * @brief  HAL Status structures definition
  */
typedef enum
{
    HAL_OK       = 0x00U,    /**< Operation is OK. */
    HAL_ERROR    = 0x01U,    /**< Parameter error or operation is not supported. */
    HAL_BUSY     = 0x02U,    /**< Driver is busy. */
    HAL_TIMEOUT  = 0x03      /**< Timeout occurred. */
} hal_status_t;


#endif
