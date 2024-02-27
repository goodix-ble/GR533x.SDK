/**
 ****************************************************************************************
 *
 * @file    gr533x_ll_aon_pmu.h
 * @author  BLE Driver Team
 * @brief   Header file containing functions prototypes of PMU LL library.
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
 ****************************************************************************************
 */

/** @addtogroup PERIPHERAL Peripheral Driver
  * @{
  */

/** @addtogroup LL_DRIVER LL Driver
  * @{
  */

/** @defgroup LL_PMU PMU LL Module Driver
  * @brief PMU LL module driver.
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR533X_LL_PMU_H_
#define __GR533X_LL_PMU_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gr533x_hal.h"

/** @defgroup AON_PMU_LL_DRIVER_FUNCTIONS Functions
  * @{
  */
/**
  * @brief  Enable the RTC
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_0 | RTC_EN
  *
  * @retval None
  *
  */
__STATIC_INLINE void ll_aon_pmu_enable_rtc(void)
{
    SET_BITS(AON_PMU->RF_REG_0, AON_PMU_RF_REG_0_RTC_EN);
}

/**
  * @brief  Disable the RTC
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_0 | RTC_EN
  *
  */
__STATIC_INLINE void ll_aon_pmu_disable_rtc(void)
{
    CLEAR_BITS(AON_PMU->RF_REG_0, AON_PMU_RF_REG_0_RTC_EN);
}

/**
  * @brief  Set RTC GM
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_0 | EN
  *
  * @param value: The rtc gm value.
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_rtc_gm(uint32_t value)
{
    MODIFY_REG(AON_PMU->RF_REG_0, AON_PMU_RF_REG_0_RTC_GM, (value << AON_PMU_RF_REG_0_RTC_GM_Pos));
}

/**
  * @brief  Set lv,default is set to 1.8V,LSB = 8.5mv
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_0 | EN
  *
  * @param value: The io ldo vout value.
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_io_ldo_vout(uint32_t value)
{
    MODIFY_REG(AON_PMU->RF_REG_0, AON_PMU_RF_REG_0_IO_LDO_REG1, (value << AON_PMU_RF_REG_0_IO_LDO_REG1_Pos));
}

/**
  * @brief  Set retention level
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_0 | ctrl_ret
  *
  * @param value: The retention level value.
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_retention_level(uint32_t value)
{
    MODIFY_REG(AON_PMU->RF_REG_0, AON_PMU_RF_REG_0_RET_LDO, (value << AON_PMU_RF_REG_0_RET_LDO_Pos));
}

/**
  * @brief  Set aon ldo value
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_0 | TON
  *
  * @param value: The dcdc ton value.
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_aon_ldo(uint32_t value)
{
    MODIFY_REG(AON_PMU->RF_REG_0, AON_PMU_RF_REG_0_AON_LDO, (value << AON_PMU_RF_REG_0_AON_LDO_Pos));
}

/**
  * @brief  Get aon ldo value
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_0 | TON
  *
  * @retval The dcdc ton value.
  *
  */
__STATIC_INLINE uint32_t ll_aon_pmu_get_aon_ldo(void)
{
    return (READ_BITS(AON_PMU->RF_REG_0, AON_PMU_RF_REG_0_AON_LDO) >> AON_PMU_RF_REG_0_AON_LDO_Pos);
}

/**
  * @brief  Set dcdc ref_cntrl_b_lv_3_0,vreg defaulted to 1.1V.
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_1 | DCDC_VREG
  *
  * @param value: the dcdc vreg value.
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_dcdc_vreg(uint32_t value)
{
    MODIFY_REG(AON_PMU->RF_REG_1, AON_PMU_RF_REG_1_DCDC_VREG, (value << AON_PMU_RF_REG_1_DCDC_VREG_Pos));
}

/**
  * @brief  Get dcdc ref_cntrl_b_lv_3_0,vreg defaulted to 1.1V.
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_1 | DCDC_VREG
  *
  * @retval: the dcdc vreg value.
  *
  */
__STATIC_INLINE uint32_t ll_aon_pmu_get_dcdc_vreg(void)
{
    return (READ_BITS(AON_PMU->RF_REG_1, AON_PMU_RF_REG_1_DCDC_VREG) >> AON_PMU_RF_REG_1_DCDC_VREG_Pos);
}

/**
  * @brief  Set dcdc voltage step for 18mV.
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_1 | DCDC_VREG
  *
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_dcdc_step_18mV(void)
{
    CLEAR_BITS(AON_PMU->RF_REG_1, AON_PMU_RF_REG_1_DCDC_VOLT_STEP);
}

/**
  * @brief  Set dcdc voltage step for 25mV.
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_1 | DCDC_VREG
  *
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_dcdc_step_25mV(void)
{
    SET_BITS(AON_PMU->RF_REG_1, AON_PMU_RF_REG_1_DCDC_VOLT_STEP);
}

/**
  * @brief  Set sysldo rg_sysldo_ctrl_vref, vreg defaulted to 1.1V.
  *
  *  Register|BitsName
  *  --------|--------
  *  FS_REG_1 | RG_SYSLDO_CTRL_VREF
  *
  * @param value: the sysldo vreg value.
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_sysldo_vreg(uint32_t value)
{
	MODIFY_REG(AON_PMU->FS_REG_1, AON_PMU_FS_REG_1_SYSLDO_CODE, (value << AON_PMU_FS_REG_1_SYSLDO_CODE_Pos));
}

/**
  * @brief  Get sysldo rg_sysldo_ctrl_vref, vreg defaulted to 1.1V.
  *
  *  Register|BitsName
  *  --------|--------
  *  FS_REG_1 | RG_SYSLDO_CTRL_VREF
  *
  * @retval: the sysldo vreg value.
  *
  */
__STATIC_INLINE uint32_t ll_aon_pmu_get_sysldo_vreg(void)
{
    return (READ_BITS(AON_PMU->FS_REG_1, AON_PMU_FS_REG_1_SYSLDO_CODE) >> AON_PMU_FS_REG_1_SYSLDO_CODE_Pos);
}

/**
  * @brief  Enable the io ldo bypass
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | BYPASS_EN
  *
  */
__STATIC_INLINE void ll_aon_pmu_enable_io_ldo_bypass(void)
{
    SET_BITS(AON_PMU->RF_REG_0, AON_PMU_RF_REG_0_IO_LDO_BYPASS);
}

/**
  * @brief  Disable the io ldo bypass
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | BYPASS_EN
  *
  */
__STATIC_INLINE void ll_aon_pmu_disable_io_ldo_bypass(void)
{
    CLEAR_BITS(AON_PMU->RF_REG_0, AON_PMU_RF_REG_0_IO_LDO_BYPASS);
}

/**
  * @brief  Enable the dig ldo bleed
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_4 | EN
  *
  */
__STATIC_INLINE void ll_aon_pmu_enable_bleed(void)
{
    SET_BITS(AON_PMU->RF_REG_4, AON_PMU_RF_REG_4_DIG_LDO_BLEED_EN);
}

/**
  * @brief  Disable the dig ldo bleed
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_4 | EN
  *
  */
__STATIC_INLINE void ll_aon_pmu_disable_bleed(void)
{
    CLEAR_BITS(AON_PMU->RF_REG_4, AON_PMU_RF_REG_4_DIG_LDO_BLEED_EN);
}

/**
  * @brief  Set the dig ldo bypass
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_4 | BYPASS_EN
  *
  *  @param enable: enable pmu set dig lod bypass.
  * 
  */
__STATIC_INLINE void ll_aon_pmu_set_dig_ldo_bypass(bool enable)
{
    MODIFY_REG(AON_PMU->RF_REG_4, AON_PMU_RF_REG_4_DIG_LDO_BYPASS_EN, (enable << AON_PMU_RF_REG_4_DIG_LDO_BYPASS_EN_Pos));
}

/**
  * @brief  Get the dig ldo bypass
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_4 | BYPASS_EN
  *
  * @retval The dig ldo bypass enable value.
  *
  */
__STATIC_INLINE uint32_t ll_aon_pmu_get_dig_ldo_bypass(void)
{
    return (READ_BITS(AON_PMU->RF_REG_4, AON_PMU_RF_REG_4_DIG_LDO_BYPASS_EN) >> AON_PMU_RF_REG_4_DIG_LDO_BYPASS_EN_Pos);
}

/**
  * @brief  Set dig ldo out coarse tune
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_4 | AON_PMU_RF_REG_4_DIG_LDO_COARSE_TUNE
  *
  * @param value: The dig ldo out value.
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_dig_ldo_out_coarse_tune(uint32_t value)
{
    MODIFY_REG(AON_PMU->RF_REG_4, AON_PMU_RF_REG_4_DIG_LDO_COARSE_TUNE, (value << AON_PMU_RF_REG_4_DIG_LDO_COARSE_TUNE_Pos));
}

/**
  * @brief  Get dig ldo out coarse tune
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_4 | AON_PMU_RF_REG_4_DIG_LDO_COARSE_TUNE
  *
  * @retval: The dig ldo out value.
  *
  */
__STATIC_INLINE uint32_t ll_aon_pmu_get_dig_ldo_out_coarse_tune(void)
{
    return (READ_BITS(AON_PMU->RF_REG_4, AON_PMU_RF_REG_4_DIG_LDO_COARSE_TUNE) >> AON_PMU_RF_REG_4_DIG_LDO_COARSE_TUNE_Pos);
}

/**
  * @brief  Set dig ldo out fine tune
  *
  *  Register|BitsName
  *  --------|--------
  *  PMU_INTF_OVR_VAL_0 | DDVS_CTL_REF
  *
  * @param value: The dig ldo out value.
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_dig_ldo_out_fine_tune(uint32_t value)
{
    MODIFY_REG(AON_PMU->PMU_INTF_OVR_VAL_0, AON_PMU_VAL_AVS_CTL_REF, (value << AON_PMU_VAL_AVS_CTL_REF_Pos) );
    SET_BITS(AON_PMU->PMU_INTF_OVR_EN_0, AON_PMU_AVS_CTL_REF_EN);
}

/**
  * @brief  Get dig ldo out fine tune
  *
  *  Register|BitsName
  *  --------|--------
  *  PMU_INTF_OVR_RD0 | DDVS_CTL_REF
  *
  * @retval: The dig ldo out value.
  *
  */
__STATIC_INLINE uint32_t ll_aon_pmu_get_dig_ldo_out_fine_tune(void)
{
    return ((AON_PMU->PMU_INTF_OVR_RD0 & AON_PMU_RD_AVS_CTL_REF_Msk) >> AON_PMU_RD_AVS_CTL_REF_Pos);
}

/**
  * @brief  Set clk period
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_4 | CLK_PERIOD
  *
  * @param value: The period of clk.
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_clk_period(uint32_t value)
{
    MODIFY_REG(AON_PMU->RF_REG_1, AON_PMU_RF_REG_1_BUCK_CLK_TRIM, (value << AON_PMU_RF_REG_1_BUCK_CLK_TRIM_Pos));
}

/**
  * @brief Enables clock injection from XO to ring oscillator.
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_1 | EN_INJ_ON
  *
  *
  */
__STATIC_INLINE void ll_aon_pmu_enable_clk_inject(void)
{
    SET_BITS(AON_PMU->RF_REG_1, AON_PMU_RF_REG_1_DCDC_CLK);
}

/**
  * @brief Disables clock injection from XO to ring oscillator.
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_1 | EN_INJ_ON
  *
  *
  */
__STATIC_INLINE void ll_aon_pmu_disable_clk_inject(void)
{
    CLEAR_BITS(AON_PMU->RF_REG_1, AON_PMU_RF_REG_1_DCDC_CLK);
}

/**
  * @brief  Set the nunber of BUCK`s PMOS driver
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_1 | rg_buck_pmmosnum_sel<1:0>
  *
  * @param value: The nunber of buck pmos driver
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_buck_pmmosnum_sel(uint32_t value)
{
    MODIFY_REG(AON_PMU->RF_REG_1, AON_PMU_RF_REG_1_BUCK_PMMOSNUM_SEL, (value << AON_PMU_RF_REG_1_BUCK_PMMOSNUM_SEL_Pos));
}

/**
  * @brief  Set the length of driver`s deadtime
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_1 | rg_buck_pmmosnum_sel<1:0>
  *
  * @param value: The length of driver's deadtime
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_buck_deadtime_sel(uint32_t value)
{
    MODIFY_REG(AON_PMU->RF_REG_1, AON_PMU_RF_REG_1_BUCK_DEADTIME_SEL, (value << AON_PMU_RF_REG_1_BUCK_DEADTIME_SEL_Pos));
}

/**
  * @brief  Set the rtc cur cap
  *
  *  Register|BitsName
  *  --------|--------
  *  RC_RTC_REG_0 | RTC_CAP
  *
  * @param value: The rtc current cap value.
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_rtc_cs(uint32_t value)
{
    MODIFY_REG(AON_PMU->RC_RTC_REG_0, AON_PMU_RC_RTC_REG0_RTC_CS, (value << AON_PMU_RC_RTC_REG0_RTC_CS_Pos));
}

/**
  * @brief  Set the rtc cur cap
  *
  *  Register|BitsName
  *  --------|--------
  *  RC_RTC_REG_0 | RTC_CAP
  *
  * @param value: The rtc current cap value.
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_rtc_cap(uint32_t value)
{
    MODIFY_REG(AON_PMU->RC_RTC_REG_0, AON_PMU_RC_RTC_REG0_RTC_CAP, (value << AON_PMU_RC_RTC_REG0_RTC_CAP_Pos));
}

/**
  * @brief  Get the rtc cur cap
  *
  *  Register|BitsName
  *  --------|--------
  *  RC_RTC_REG_0 | RTC_CAP
  *
  * @retval The rtc current cap value.
  *
  */
__STATIC_INLINE uint32_t ll_aon_pmu_get_rtc_cap(void)
{
    return (READ_BITS(AON_PMU->RC_RTC_REG_0, AON_PMU_RC_RTC_REG0_RTC_CAP) >> AON_PMU_RC_RTC_REG0_RTC_CAP_Pos);
}

/**
  * @brief  Enable the RCOSC
  *
  *  Register|BitsName
  *  --------|--------
  *  RC_RTC_REG_0 | RCOSC
  *
  */
__STATIC_INLINE void ll_aon_pmu_enable_rcosc(void)
{
    SET_BITS(AON_PMU->RC_RTC_REG_0, AON_PMU_RC_RTC_REG0_RCOSC);
}

/**
  * @brief  Disable the RCOSC
  *
  *  Register|BitsName
  *  --------|--------
  *  RC_RTC_REG_0 | RCOSC
  *
  */
__STATIC_INLINE void ll_aon_pmu_disable_rcosc(void)
{
    CLEAR_BITS(AON_PMU->RC_RTC_REG_0, AON_PMU_RC_RTC_REG0_RCOSC);
}
/**
  * @brief  modify ton on
  *
  *  Register|BitsName
  *  --------|--------
  *  PMU_TON_CFG | AON_PMU_TON_CTRL_ON
  *
  *  @param value: The value of tx ton.
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_tx_ton_val(uint32_t value)
{
    MODIFY_REG(AON_PMU->PMU_TON_CFG, AON_PMU_TON_CTRL_ON, (value << AON_PMU_TON_CTRL_ON_Pos));
}
/**
  * @brief  modify ton off
  *
  *  Register|BitsName
  *  --------|--------
  *  PMU_TON_CFG | AON_PMU_TON_CTRL_OFF
  *
  *  @param value: The value of non tx ton.
  *
  */
__STATIC_INLINE void ll_aon_pmu_set_non_tx_ton_val(uint32_t value)
{
    MODIFY_REG(AON_PMU->PMU_TON_CFG, AON_PMU_TON_CTRL_OFF, (value << AON_PMU_TON_CTRL_OFF_Pos));
}
/** @} */

/**
  * @brief  Enable BOD auto power off in deepsleep and power on wakeup
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_0 | BOD
  *
  */
__STATIC_INLINE void ll_aon_pmu_enable_bod_auto_power(void)
{
    CLEAR_BITS(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_BYPASS);
}

/**
  * @brief  Disable BOD auto power off in deepsleep and power on wakeup
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_0 | BOD
  *
  */
__STATIC_INLINE void ll_aon_pmu_disable_bod_auto_power(void)
{
    SET_BITS(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_BYPASS);
}

/**
  * @brief  Enable DCDC power
  *
  *  Register|BitsName
  *  --------|--------
  *  PMU_INTF | DCDC
  */
__STATIC_INLINE void ll_aon_pmu_enable_dcdc(void)
{
    WRITE_REG(AON_PWR->PWR_SET, AON_PWR_PWR_SET_DCDC_SET);
}

/**
  * @brief  Disble DCDC power
  *
  *  Register|BitsName
  *  --------|--------
  *  PMU_INTF | DCDC
  */
__STATIC_INLINE void ll_aon_pmu_disable_dcdc(void)
{
    WRITE_REG(AON_PWR->PWR_CLR, AON_PWR_PWR_CLR_DCDC_CLR);
}

/**
  * @brief  Get the DCDC enable status
  *
  *  Register|BitsName
  *  --------|--------
  *  PWR_STS | sts_dcdc_avl
  *
  * @retval The dcdc available status, 1: available, 0: not available
  *
  */
__STATIC_INLINE uint32_t ll_aon_pmu_get_dcdc_available_status(void)
{
    return (READ_BITS(AON_PWR->PWR_STAT, AON_PWR_PWR_STAT_DCDC_AVL) >> AON_PWR_PWR_STAT_DCDC_AVL_Pos);
}


/**
  * @brief  Enable SYSLDO power
  *
  *  Register|BitsName
  *  --------|--------
  *  PMU_INTF | SYSLDO
  */
__STATIC_INLINE void ll_aon_pmu_enable_sysldo(void)
{
    WRITE_REG(AON_PWR->PWR_SET, AON_PWR_PWR_SET_FAST_LDO_SET);
}

/**
  * @brief  Disable SYSLDO power
  *
  *  Register|BitsName
  *  --------|--------
  *  PMU_INTF | DCDC
  */
__STATIC_INLINE void ll_aon_pmu_disable_sysldo(void)
{
    WRITE_REG(AON_PWR->PWR_CLR, AON_PWR_PWR_CLR_FAST_LDO_CLR);
}

/**
  * @brief  Get the SYSLDO enable status
  *
  *  Register|BitsName
  *  --------|--------
  *  PWR_STS | sts_dig_ldo_avl
  *
  * @retval The sysldo available status, 1: available, 0: not available
  *
  */
__STATIC_INLINE uint32_t ll_aon_pmu_get_sysldo_available_status(void)
{
    return (READ_BITS(AON_PWR->PWR_STAT, AON_PWR_PWR_STAT_FAST_LDO_AVL) >> AON_PWR_PWR_STAT_FAST_LDO_AVL_Pos);
}

#endif

/** @} */

/** @} */

/** @} */
