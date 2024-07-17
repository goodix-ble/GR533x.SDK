/**
 ****************************************************************************************
 *
 * @file    gr533x_ll_advs.h
 * @author  BLE RD
 * @brief   Header file containing functions prototypes of advs LL library.
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

/** @defgroup LL_ADVS ADVS
  * @brief ADVS LL module driver.
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __GR533X_LL_advs_H_
#define __GR533X_LL_advs_H_

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "gr533x_hal.h"

/**
  * @defgroup  ADVS_LL_MACRO Defines
  * @{
  */
/** @defgroup LL_ADVS_VTBIAS_ENABLE Scaling vtbias enable state defines
  * @{
  */
#define LL_ADVS_VTBIAS_DIS                                             (0U)  /**< VTBIAS Disable(default) */
#define LL_ADVS_VTBIAS_EN                                              (1U)  /**< VTBIAS Enable */
/** @} */

/** @defgroup LL_ADVS_BLK_ENABLE Scaling blk enable state defines
  * @{
  */
#define LL_ADVS_BLK_DIS                                                (0U)  /**< BLK Disable(default) */
#define LL_ADVS_BLK_EN                                                 (1U)  /**< BLK Enable */
/** @} */

/** @defgroup LL_ADVS_TYPE Scaling slop control type defines
  * @{
  */
#define LL_ADVS_SLOP_LOWER_TYPE                                        (0U)  /**< Lower Slop Type(default) */
#define LL_ADVS_SLOP_HIGHER_TYPE                                       (1U)  /**< Higher Slop Type */
/** @} */

/** @defgroup LL_ADVS_LIMIT_ENABLE Scaling limiter enable defines
  * @{
  */
#define LL_ADVS_LIMIT_DIS                                              (0U)  /**< Scaling Limit Disable(default) */
#define LL_ADVS_LIMIT_EN                                               (1U)  /**< Scaling Limit Enable */
/** @} */

/** @} */

/** @defgroup ADVS_LL_DRIVER_FUNCTIONS Functions
  * @{
  */
/**
  * @brief  The ADVS_DCDC vtbias enable set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DCDC | EN_VTBIAS
  */
__STATIC_INLINE void ll_advs_dcdc_vtbias_enable_set(uint8_t enable)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_DCDC_EN_VTBIAS, (enable << AON_PMU_ADVS_DCDC_EN_VTBIAS_Pos));
}

/**
  * @brief  The ADVS_DCDC vtbias enable get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DCDC | EN_VTBIAS
  */
__STATIC_INLINE uint8_t ll_advs_dcdc_vtbias_enable_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_DCDC_EN_VTBIAS)) >> AON_PMU_ADVS_DCDC_EN_VTBIAS_Pos);
}

/**
  * @brief  The ADVS_DCDC blk enable set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DCDC | EN_BLK
  */
__STATIC_INLINE void ll_advs_dcdc_blk_enable_set(uint8_t enable)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_DCDC_EN_BLK, (enable << AON_PMU_ADVS_DCDC_EN_BLK_Pos));
}

/**
  * @brief  The ADVS_DCDC blk enable get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DCDC | EN_BLK
  */
__STATIC_INLINE uint8_t ll_advs_dcdc_blk_enable_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_DCDC_EN_BLK)) >> AON_PMU_ADVS_DCDC_EN_BLK_Pos);
}

/**
  * @brief  The ADVS_DCDC's Slop Control type set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DCDC | VTBIAS_SLOPE_CTRL
  */
__STATIC_INLINE void ll_advs_dcdc_vtbias_slop_ctrl_set(uint8_t type)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_DCDC_VTBIAS_SLOPE_CTRL, (type << AON_PMU_ADVS_DCDC_VTBIAS_SLOPE_CTRL_Pos));
}

/**
  * @brief  The ADVS_DCDC's Slop Control type get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DCDC | VTBIAS_SLOPE_CTRL
  */
__STATIC_INLINE uint8_t ll_advs_dcdc_vtbias_slop_ctrl_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_DCDC_VTBIAS_SLOPE_CTRL)) >> AON_PMU_ADVS_DCDC_VTBIAS_SLOPE_CTRL_Pos);
}

/**
  * @brief  The ADVS_DCDC's Lower Limit Control enable set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DCDC | EN_LIMITER
  */
__STATIC_INLINE void ll_advs_dcdc_limiter_enable_set(uint8_t enable)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_DCDC_EN_LIMITER, (enable << AON_PMU_ADVS_DCDC_EN_LIMITER_Pos));
}

/**
  * @brief The ADVS_DCDC's Lower Limit Control enable get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DCDC | EN_LIMITER
  */
__STATIC_INLINE uint8_t ll_advs_dcdc_limiter_enable_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_DCDC_EN_LIMITER)) >> AON_PMU_ADVS_DCDC_EN_LIMITER_Pos);
}

/**
  * @brief  The ADVS_DCDC's default level value of the VT bias set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DCDC | VTBIAS_CTRL_VT_2_0
  */
__STATIC_INLINE void ll_advs_dcdc_vtbias_ctrl_vt_set(uint8_t vt)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_LPD_VTBIAS_CTRL, (vt << AON_PMU_ADVS_DCDC_VTBIAS_CTRL_VT_2_0_Pos));
}

/**
  * @brief The ADVS_DCDC's default level value of the VT bias get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DCDC | VTBIAS_CTRL_VT_2_0
  */
__STATIC_INLINE uint8_t ll_advs_dcdc_vtbias_ctrl_vt_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_DCDC_VTBIAS_CTRL_VT_2_0)) >> AON_PMU_ADVS_DCDC_VTBIAS_CTRL_VT_2_0_Pos);
}

/**
  * @brief  The ADVS_DCDC's lower limit for the output voltage set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DCDC | VTBIAS_CTRL_VT_2_0
  */
__STATIC_INLINE void ll_advs_dcdc_vtbias_ctrl_lower_limit_set(uint8_t limit)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_DCDC_VTBIAS_CTRL_LIMIT_2_0, (limit << AON_PMU_ADVS_DCDC_VTBIAS_CTRL_LIMIT_2_0_Pos));
}

/**
  * @brief The ADVS_DCDC's lower limit for the output voltage get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DCDC | VTBIAS_CTRL_VT_2_0
  */
__STATIC_INLINE uint8_t ll_advs_dcdc_vtbias_ctrl_lower_limit_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_DCDC_VTBIAS_CTRL_LIMIT_2_0)) >> AON_PMU_ADVS_DCDC_VTBIAS_CTRL_LIMIT_2_0_Pos);
}

/**
  * @brief  The ADVS_LPD vtbias enable set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_LPD | EN_VTBIAS
  */
__STATIC_INLINE void ll_advs_lpd_vtbias_enable_set(uint8_t enable)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_LPD_VTBIAS_EN, (enable << AON_PMU_ADVS_LPD_VTBIAS_EN_Pos));
}

/**
  * @brief  The ADVS_LPD vtbias enable get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_LPD | EN_VTBIAS
  */
__STATIC_INLINE uint8_t ll_advs_lpd_vtbias_enable_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_LPD_VTBIAS_EN)) >> AON_PMU_ADVS_LPD_VTBIAS_EN_Pos);
}

/**
  * @brief  The ADVS_LPD's default level value of the VT bias set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_LPD | VTBIAS_CTRL_VT
  */
__STATIC_INLINE void ll_advs_lpd_vtbias_ctrl_vt_set(uint8_t vt)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_LPD_VTBIAS_CTRL, (vt << AON_PMU_ADVS_LPD_VTBIAS_CTRL_Pos));
}

/**
  * @brief The ADVS_LPD's default level value of the VT bias get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_LPD | VTBIAS_CTRL_VT
  */
__STATIC_INLINE uint8_t ll_advs_lpd_vtbias_ctrl_vt_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_0, AON_PMU_ADVS_LPD_VTBIAS_CTRL)) >> AON_PMU_ADVS_LPD_VTBIAS_CTRL_Pos);
}

/**
  * @brief  The ADVS_DIGCORE vtbias enable set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DIGCORE | EN_VTBIAS
  */
__STATIC_INLINE void ll_advs_digcore_vtbias_enable_set(uint8_t enable)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_1, AON_PMU_ADVS_DIGCORE_EN_VTBIAS, (enable << AON_PMU_ADVS_DIGCORE_EN_VTBIAS_Pos));
}

/**
  * @brief  The ADVS_DIGCORE vtbias enable get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DIGCORE | EN_VTBIAS
  */
__STATIC_INLINE uint8_t ll_advs_digcore_vtbias_enable_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_1, AON_PMU_ADVS_DIGCORE_EN_VTBIAS)) >> AON_PMU_ADVS_DIGCORE_EN_VTBIAS_Pos);
}

/**
  * @brief  The ADVS_DIGCORE blk enable set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DIGCORE | EN_BLK
  */
__STATIC_INLINE void ll_advs_digcore_blk_enable_set(uint8_t enable)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_1, AON_PMU_ADVS_DIGCORE_EN_BLK, (enable << AON_PMU_ADVS_DIGCORE_EN_BLK_Pos));
}

/**
  * @brief  The ADVS_DIGCORE blk enable get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DIGCORE | EN_BLK
  */
__STATIC_INLINE uint8_t ll_advs_digcore_blk_enable_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_1, AON_PMU_ADVS_DIGCORE_EN_BLK)) >> AON_PMU_ADVS_DIGCORE_EN_BLK_Pos);
}

/**
  * @brief  The ADVS_DIGCORE's Slop Control type set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DIGCORE | VTBIAS_SLOPE_CTRL
  */
__STATIC_INLINE void ll_advs_digcore_vtbias_slop_ctrl_set(uint8_t type)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_1, AON_PMU_ADVS_DIGCORE_VTBIAS_SLOPE_CTRL, (type << AON_PMU_ADVS_DIGCORE_VTBIAS_SLOPE_CTRL_Pos));
}

/**
  * @brief  The ADVS_DIGCORE's Slop Control type get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DIGCORE | VTBIAS_SLOPE_CTRL
  */
__STATIC_INLINE uint8_t ll_advs_digcore_vtbias_slop_ctrl_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_1, AON_PMU_ADVS_DIGCORE_VTBIAS_SLOPE_CTRL)) >> AON_PMU_ADVS_DIGCORE_VTBIAS_SLOPE_CTRL_Pos);
}

/**
  * @brief  The ADVS_DIGCORE's Lower Limit Control enable set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DIGCORE | EN_LIMITER
  */
__STATIC_INLINE void ll_advs_digcore_limiter_enable_set(uint8_t enable)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_1, AON_PMU_ADVS_DIGCORE_EN_LIMITER, (enable << AON_PMU_ADVS_DIGCORE_EN_LIMITER_Pos));
}

/**
  * @brief The ADVS_DIGCORE's Lower Limit Control enable get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DIGCORE | EN_LIMITER
  */
__STATIC_INLINE uint8_t ll_advs_digcore_limiter_enable_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_1, AON_PMU_ADVS_DIGCORE_EN_LIMITER)) >> AON_PMU_ADVS_DIGCORE_EN_LIMITER_Pos);
}

/**
  * @brief  The ADVS_DIGCORE's default level value of the VT bias set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DIGCORE | VTBIAS_CTRL_VT_2_0
  */
__STATIC_INLINE void ll_advs_digcore_vtbias_ctrl_vt_set(uint8_t vt)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_1, AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_VT_2_0, (vt << AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_VT_2_0_Pos));
}

/**
  * @brief The ADVS_DIGCORE's default level value of the VT bias get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DIGCORE | VTBIAS_CTRL_VT_2_0
  */
__STATIC_INLINE uint8_t ll_advs_digcore_vtbias_ctrl_vt_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_1, AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_VT_2_0)) >> AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_VT_2_0_Pos);
}

/**
  * @brief  The ADVS_DIGCORE's lower limit for the output voltage set
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DIGCORE | VTBIAS_CTRL_VT_2_0
  */
__STATIC_INLINE void ll_advs_digcore_vtbias_ctrl_lower_limit_set(uint8_t limit)
{
    MODIFY_REG(AON_PMU->PMU_ADVS_CFG_1, AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_LIMIT_2_0, (limit << AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_LIMIT_2_0_Pos));
}

/**
  * @brief The ADVS_DIGCORE's lower limit for the output voltage get
  *
  *  Register|BitsName
  *  --------|--------
  *  ADVS_DIGCORE | VTBIAS_CTRL_VT_2_0
  */
__STATIC_INLINE uint8_t ll_advs_digcore_vtbias_ctrl_lower_limit_get(void)
{
    return ((READ_BITS(AON_PMU->PMU_ADVS_CFG_1, AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_LIMIT_2_0)) >> AON_PMU_ADVS_DIGCORE_VTBIAS_CTRL_LIMIT_2_0_Pos);
}

/** @} */
#ifdef __cplusplus
}
#endif

#endif
/** @} */

/** @} */

/** @} */
