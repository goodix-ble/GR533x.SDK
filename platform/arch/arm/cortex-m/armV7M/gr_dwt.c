
#include "gr5x.h"
#include "gr_common.h"

__IO uint32_t dwt_counter = 0x00;

void hal_dwt_enable(uint32_t _demcr_initial, uint32_t _dwt_ctrl_initial)
{
    GLOBAL_EXCEPTION_DISABLE();
    dwt_counter ++;
    CoreDebug->DEMCR = _demcr_initial | CoreDebug_DEMCR_TRCENA_Msk;
    DWT->CTRL = _dwt_ctrl_initial | DWT_CTRL_CYCCNTENA_Msk;
    GLOBAL_EXCEPTION_ENABLE();
    return ;
}

void hal_dwt_disable(uint32_t _demcr_initial, uint32_t _dwt_ctrl_initial)
{
    GLOBAL_EXCEPTION_DISABLE();
    dwt_counter --;
    if (dwt_counter == 0x0)
    {
        DWT->CTRL = _dwt_ctrl_initial;
        CoreDebug->DEMCR = _demcr_initial;
    }
    GLOBAL_EXCEPTION_ENABLE();
    return ;
}
