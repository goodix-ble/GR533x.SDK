/**
 ****************************************************************************************
 *
 * @file    gr533x_ll_bod.h
 * @author  BLE Driver Team
 * @brief   Header file containing functions prototypes of CALENDAR LL library.
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

/** @defgroup LL_BOD BOD Module Driver
  * @brief BOD LL module driver.
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR55XX_LL_BOD_H_
#define __GR55XX_LL_BOD_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gr533x.h"

/** @defgroup BOD_LL_STRUCTURES Structures
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup BOD_LL_ES_INIT BOD Exported init structures
  * @{
  */

/**
  * @brief LL BOD init Structure definition
  */
typedef struct _ll_bod_init
{
    uint8_t bod_en;      /**< Specifies the bod enable.
                                 This parameter can be any value of @ref BOD_LL_ENABLE.
                                 This parament can be modified afterwards using unitary function @ref ll_bod_bod_enable() and  ll_bod_bod_disable(). */

    uint8_t bod2_en;     /**< Specifies the bod2 enable.
                                 This parameter can be any value of @ref BOD2_LL_ENABLE.
                                 This parament can be modified afterwards using unitary function @ref ll_bod_bod2_enable() and  ll_bod_bod2_disable().. */

    uint8_t bod2_lvl;    /**< Specifies the bod2 level.
                                 This parameter can be a value of @ref BOD2_LL_LEVEL.
                                 This parament can be modified afterwards using unitary function @ref ll_bod_bod2_lvl_ctrl_lv_set(). */
    uint8_t bod_static_en;  /**< Specifies the bod static enbale.
                                 This parameter can be a value of @ref BOD_LL_STATIC_ENABLE.
                                 This parament can be modified afterwards using unitary function @ref ll_bod_static_enable() and ll_bod_static_disable(). */

    uint8_t bod2_auto_power_bypass_en; /**< Specifies the bod bod2 auto power bypass.
                                 This parameter can be a value of @ref BOD_LL_BOD2_AUTO_POWER_BYPASS.
                                 This parament can be modified afterwards using unitary function @ref ll_bod_bod2_auto_power_bypass_enable()
                                    and ll_bod_bod2_auto_power_bypass_disable(). */
} ll_bod_init_t;

/** @} */

/** @} */

/**
  * @defgroup  BOD_LL_MACRO Defines
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup BOD_LL_Exported_Constants BOD Exported Constants
  * @{
  */

/** @defgroup BOD_LL_ENABLE BOD ENABLE
  * @{
  */
#define LL_BOD_BOD_ENABLE               (0x1)   /**< BOD enable  */
#define LL_BOD_BOD_DISABLE              (0x0)   /**< BOD disable  */
/** @} */

/** @defgroup BOD2_LL_ENABLE BOD2 ENABLE
  * @{
  */
#define LL_BOD_BOD2_ENABLE               (0x1)   /**< BOD2 enable  */
#define LL_BOD_BOD2_DISABLE              (0x0)  /**< BOD2 disable  */
/** @} */

/** @defgroup BOD_LL_STATIC_ENABLE BOD STATIC ENABLE
  * @{
  */
#define LL_BOD_STATIC_ENABLE               (0x1)   /**< BOD STATIC enable  */
#define LL_BOD_STATIC_DISABLE              (0x0)   /**< BOD STATIC disable  */
/** @} */

/** @defgroup BOD_LL_BOD2_AUTO_POWER_BYPASS BOD2 AUTO POWER BYPASS
  * @{
  */
#define LL_BOD_BOD2_AUTO_POWER_BYPASS_ENABLE               (0x1)   /**< BOD STATIC enable  */
#define LL_BOD_BOD2_AUTO_POWER_BYPASS_DISABLE              (0x0)   /**< BOD STATIC disable  */
/** @} */

/** @defgroup BOD2_LL_LEVEL BOD2 LVEVL
  * @{
  */
#define LL_BOD_BOD2_LEVEL_0              (0x0)   /**< BOD2 Level 0  */
#define LL_BOD_BOD2_LEVEL_1              (0x1)   /**< BOD2 Level 1  */
#define LL_BOD_BOD2_LEVEL_2              (0x2)   /**< BOD2 Level 2  */
#define LL_BOD_BOD2_LEVEL_3              (0x3)   /**< BOD2 Level 3  */
#define LL_BOD_BOD2_LEVEL_4              (0x4)   /**< BOD2 Level 4  */
#define LL_BOD_BOD2_LEVEL_5              (0x5)   /**< BOD2 Level 5  */
#define LL_BOD_BOD2_LEVEL_6              (0x6)   /**< BOD2 Level 6  */
#define LL_BOD_BOD2_LEVEL_7              (0x7)   /**< BOD2 Level 7  */
/** @} */

/** @} */

/** @} */

/** @defgroup BOD_LL_DRIVER_FUNCTIONS Functions
  * @{
  */
/**
  * @brief  Enable the bod
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | bod_en_lv
  *
  */
__STATIC_INLINE void ll_bod_bod_enable(void)
{
#if defined(BIT_BAND_SUPPORT)
    BIT_ADDR((uint32_t)&AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD_EN_Pos) = 1;
#else
    SET_BITS(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD_EN);
#endif
}

/**
  * @brief  Disable the bod
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | bod_en_lv
  *
  */
__STATIC_INLINE void ll_bod_bod_disable(void)
{
#if defined(BIT_BAND_SUPPORT)
    BIT_ADDR((uint32_t)&AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD_EN_Pos) = 0;
#else
    CLEAR_BITS(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD_EN);
#endif
}

/**
  * @brief  Enable the bod2
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | bod2_en_lv
  *
  */
__STATIC_INLINE void ll_bod_bod2_enable(void)
{
#if defined(BIT_BAND_SUPPORT)
    BIT_ADDR((uint32_t)&AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_EN_Pos) = 1;
#else
    SET_BITS(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_EN);
#endif
}

/**
  * @brief  Disable the bod2
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | bod2_en_lv
  *
  */
__STATIC_INLINE void ll_bod_bod2_disable(void)
{
#if defined(BIT_BAND_SUPPORT)
    BIT_ADDR((uint32_t)&AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_EN_Pos) = 0;
#else
    CLEAR_BITS(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_EN);
#endif
}

/**
  * @brief  Set bod control level
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | bod_lvl_ctrl_lv_3_0
  * @param  lvl_ctrl_lv: 0x0 ~ 0xF
  */
__STATIC_INLINE void ll_bod_bod2_lvl_ctrl_lv_set(uint8_t lvl_ctrl_lv)
{
#if defined(BIT_BAND_SUPPORT)
    BIT_ADDR((uint32_t)&AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_LVL_CTRL_LV_Pos) = (lvl_ctrl_lv & 0x01);
    BIT_ADDR((uint32_t)&AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_LVL_CTRL_LV_Pos+1) = ((lvl_ctrl_lv>>1) & 0x01);
    BIT_ADDR((uint32_t)&AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_LVL_CTRL_LV_Pos+2) = ((lvl_ctrl_lv>>2) & 0x01);
#else
    MODIFY_REG(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_LVL_CTRL_LV, (lvl_ctrl_lv << AON_PMU_RF_REG_3_BOD2_LVL_CTRL_LV_Pos));
#endif
}

/**
  * @brief  enable bod static lv
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | bod_static_lv
  */
__STATIC_INLINE void ll_bod_static_enable(void)
{
#if defined(BIT_BAND_SUPPORT)
    BIT_ADDR((uint32_t)&AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD_STATIC_Pos) = 1;
#else
    SET_BITS(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD_STATIC_EN);
#endif
}

/**
  * @brief  disable bod static lv
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | bod_static_lv
  */
__STATIC_INLINE void ll_bod_static_disable(void)
{
#if defined(BIT_BAND_SUPPORT)
    BIT_ADDR((uint32_t)&AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD_STATIC_Pos) = 0;
#else
    CLEAR_BITS(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD_STATIC_EN);
#endif
}

/**
  * @brief  Enable the bod2 auto power bypass
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | bod2_auto_power_bypass_enable
  *
  */
__STATIC_INLINE void ll_bod_bod2_auto_power_bypass_enable(void)
{
#if defined(BIT_BAND_SUPPORT)
    BIT_ADDR((uint32_t)&AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_BYPASS_Pos) = 1;
#else
    SET_BITS(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_BYPASS);
#endif
}

/**
  * @brief  Disable the bod2 auto power bypass
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | bod2_auto_power_bypass_enable
  *
  */
__STATIC_INLINE void ll_bod_bod2_auto_power_bypass_disable(void)
{
#if defined(BIT_BAND_SUPPORT)
    BIT_ADDR((uint32_t)&AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_BYPASS_Pos) = 0;
#else
    CLEAR_BITS(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_BYPASS);
#endif
}

/**
  * @brief  Indicate if the BOD Power Flag is set or not.
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | pmu_bod_ok
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_bod_bod2_is_active_flag_bod_ok(void)
{
    return (uint32_t)(READ_BITS(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_OK) == AON_PMU_RF_REG_3_BOD2_OK);
}

/**
  * @brief  Indicate if the BOD2 Power Flag is set or not.
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | bod2_pwr_ctrl_post
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_bod_bod2_is_active_flag_bod2_pwr_ctrl_post(void)
{
    return (uint32_t)(READ_BITS(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_PWR_CTRL_POST) == AON_PMU_RF_REG_3_BOD2_PWR_CTRL_POST);
}

/**
  * @brief  Indicate if the BOD INTR Flag is set or not.
  *
  *  Register|BitsName
  *  --------|--------
  *  RF_REG_3 | pmu_bod_intr
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_bod_bod2_is_active_flag_pmu_bod_intr(void)
{
    return (uint32_t)(READ_BITS(AON_PMU->RF_REG_3, AON_PMU_RF_REG_3_BOD2_INT) == AON_PMU_RF_REG_3_BOD2_INT);
}


/**
  * @brief  enable BOD FEDGE Event.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_IRQ | AON_CTL_AON_IRQ_EN_PMU_BOD_FALL
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void ll_bod_bod2_enable_fedge(void)
{
    SET_BITS(AON_CTL->AON_IRQ_EN, AON_CTL_AON_IRQ_EN_PMU_BOD_FALL);
}

/**
  * @brief  disable BOD FEDGE Event.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_IRQ | AON_CTL_AON_IRQ_EN_PMU_BOD_FALL
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void ll_bod_bod2_disable_fedge(void)
{
    CLEAR_BITS(AON_CTL->AON_IRQ_EN, AON_CTL_AON_IRQ_EN_PMU_BOD_FALL);
}

/**
  * @brief  enable BOD REDGE Event.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_IRQ | AON_CTL_AON_IRQ_EN_PMU_BOD_RISE
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void ll_bod_bod2_enable_redge(void)
{
    SET_BITS(AON_CTL->AON_IRQ_EN, AON_CTL_AON_IRQ_EN_PMU_BOD_RISE);
}

/**
  * @brief  disable BOD REDGE Event.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_IRQ | AON_CTL_AON_IRQ_EN_PMU_BOD_RISE
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE void ll_bod_bod2_disable_redge(void)
{
    CLEAR_BITS(AON_CTL->AON_IRQ_EN, AON_CTL_AON_IRQ_EN_PMU_BOD_RISE);
}

/**
  * @brief  Indicate if the BOD FEDGE Event Flag is set or not.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_IRQ | AON_CTL_AON_IRQ_PMU_BOD_FALL
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_bod_bod2_is_active_flag_fedge(void)
{
    return (uint32_t)(READ_BITS(AON_CTL->AON_IRQ, AON_CTL_AON_IRQ_PMU_BOD_FALL) == AON_CTL_AON_IRQ_PMU_BOD_FALL);
}

/**
  * @brief  Clear Interrupt Status flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_IRQ| AON_CTL_AON_IRQ_PMU_BOD_FALL
  *
  * @retval None
  */
__STATIC_INLINE void ll_bod_bod2_clear_flag_fedge(void)
{
    WRITE_REG(AON_CTL->AON_IRQ, ~AON_CTL_AON_IRQ_PMU_BOD_FALL);
}

/**
  * @brief  Indicate if the BOD REDGE Event Flag is set or not.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_IRQ | AON_CTL_AON_IRQ_PMU_BOD_RISE
  *
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_bod_bod2_is_active_flag_redge(void)
{
    return (uint32_t)(READ_BITS(AON_CTL->AON_IRQ, AON_CTL_AON_IRQ_PMU_BOD_RISE) == AON_CTL_AON_IRQ_PMU_BOD_RISE);
}

/**
  * @brief  Clear Interrupt Status flag.
  *
  *  Register|BitsName
  *  --------|--------
  *  AON_IRQ| AON_CTL_AON_IRQ_PMU_BOD_RISE
  *
  * @retval None
  */
__STATIC_INLINE void ll_bod_bod2_clear_flag_redge(void)
{
    WRITE_REG(AON_CTL->AON_IRQ, ~AON_CTL_AON_IRQ_PMU_BOD_RISE);
}

/**
  * @brief  De-initialize the BOD registers to their default reset values.
  * @retval An error_status_t enumeration value:
  *          - SUCCESS: PDM registers are de-initialized
  *          - ERROR: PDM registers are not de-initialized
  */
error_status_t ll_bod_deinit(void);

/**
  * @brief  Initialize the BOD registers according to the specified parameters in p_bod_init.
  * @param  p_bod_init pointer to a @ref ll_bod_init_t structure.
  * @retval An error_status_t enumeration value:
  *          - SUCCESS: BOD registers are initialized
  *          - ERROR: Not applicable
  */
error_status_t ll_bod_init(ll_bod_init_t *p_bod_init);

/**
  * @brief Set each field of a p_bod_init type structure to default value.
  * @param p_bod_init  Pointer to a @ref ll_bod_init_t structure
  *                        whose fields will be set to default values.
  * @retval None
  */
void ll_bod_struct_init(ll_bod_init_t *p_bod_init);
/** @} */

#ifdef __cplusplus
}
#endif

#endif
/** @} */

/** @} */

/** @} */
