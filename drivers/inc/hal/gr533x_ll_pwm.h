/**
 ****************************************************************************************
 *
 * @file    gr533x_ll_pwm.h
 * @author  BLE Driver Team
 * @brief   Header file containing functions prototypes of PWM LL library.
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

/** @defgroup LL_PWM PWM
  * @brief PWM LL module driver.
  * @{
  */

#ifndef __GR533X_LL_PWM_H__
#define __GR533X_LL_PWM_H__

#ifdef __cplusplus
extern "C" {
#endif

#include "gr533x.h"

#if defined (PWM0) || defined (PWM1)

/* Exported types ------------------------------------------------------------*/
/** @addtogroup LL_PWM_ENUMERATIONS Enumerations
  * @{
  */

/**
  * @brief LL PWM Mode definition
  */
typedef enum
{
    LL_PWM_FLICKER_MODE = 0x00,    /**< Choose PWM Flicker Mode */
    LL_PWM_BREATH_MODE,            /**< Choose PWM Breath Mode  */
    LL_PWM_CODING_MODE,            /**< Choose PWM Coding Mode  */
} ll_pwm_mode_t;

/** @} */

/** @defgroup PWM_LL_STRUCTURES Structures
  * @{
  */

/* Exported types ------------------------------------------------------------*/
/** @defgroup PWM_LL_ES_INIT PWM Exported init structures
  * @{
  */

/**
  * @brief  LL PWM Output Channel init Structure definition.
  */
typedef struct _ll_pwm_none_coding_channel_init_t
{
    uint8_t duty;               /**< Specifies the duty in PWM output mode.
                                     This parameter must be a number ranges between Min_Data=0 and Max_Data=100.*/

    uint8_t drive_polarity;      /**< Specifies the drive polarity in PWM output mode.
                                        This parameter can be a value of @ref PWM_LL_EC_DRIVEPOLARITY.

                                        This feature can be modified afterwards using unitary function ll_pwm_enable_positive_drive_channel_x()
                                        and ll_pwm_disable_positive_drive_channel_x() where X can be (A, B, C).*/

     uint32_t flickerstop_lvl;   /**< Specifies the IO level when channel flicker stop.
                                     This parameter can be a value of @ref PWM_LL_STOP_LVL.*/
} ll_pwm_none_coding_channel_init_t;

/**
  * @brief  LL PWM Output Channel init Structure definition.
  */
typedef struct _ll_pwm_coding_channel_init_t
{
    uint32_t ll_comp0;                 /**< Specifies current channel first compare value
                                        This parameter must be a number ranges between Min_Data=0 and Max_Data=period.*/

    uint32_t ll_comp1;                 /**< Specifies current channel second compare value
                                        This parameter must be a number ranges between Min_Data=0 and Max_Data=period.*/

    uint8_t ll_drive_polarity;      /**< Specifies the drive polarity in PWM output mode.
                                            This parameter can be a value of @ref PWM_LL_EC_DRIVEPOLARITY.
                                            This feature can be modified afterwards using unitary function ll_pwm_enable_positive_drive_channel_x()
                                            and ll_pwm_disable_positive_drive_channel_x() where X can be (A, B, C).*/

    uint8_t ll_waiting_time_lvl;       /**< Specifies the waiting time level in coding mode.
                                        This parameter can be a value of @ref PWM_LL_WAITING_TIME_LVL.*/

} ll_pwm_coding_channel_init_t;

/**
  * @brief  LL PWM none coding mode Structure definition.
  */
typedef struct _ll_pwm_none_coding_mode_init_t
{
	uint32_t align;             /**< Specifies the PWM alignment pulses.
                                     This parameter can be a value of @ref PWM_LL_EC_ALIGN.*/

    uint32_t prescaler;         /**< Specifies the prescaler value which will be used configure PWM output frequency.
                                     This parameter must be a number ranges between Min_Data = 0 and Max_Data = 0xFFFFFFFF.
                                     This parameter should be larger than 128.

                                     This feature can be modified afterwards using unitary function @ref ll_pwm_set_prescaler().*/

    uint32_t bprescaler;        /**< Specifies the required prescaler that the duty changes from 0% to 100% in breath mode.
                                     This parameter must be a number ranges between Min_Data=0 and Max_Data=0xFFFFFFFF.
                                     This parameter is recommended to be larger than 128*prescaler to guarantee an ideal breath effect.

                                     This feature can be modified afterwards using unitary function @ref ll_pwm_set_breath_prescaler().*/

    uint32_t hprescaler;        /**< Specifies the required prescaler in breath hold state.
                                     This parameter must be a number ranges between Min_Data=0 and Max_Data=0xFFFFFF.

                                     This feature can be modified afterwards using unitary function @ref ll_pwm_set_hold_prescaler().*/

    uint32_t breathstop_lvl;    /**< Specifies the IO level when breath stop.
                                     This parameter can be a value of @ref PWM_LL_STOP_LVL.*/

    ll_pwm_none_coding_channel_init_t channel_a;    /**< Specifies the configuration of channelA.
                                                 This parameter can be a value of @ref ll_pwm_none_coding_channel_init_t.*/

    ll_pwm_none_coding_channel_init_t channel_b;    /**< Specifies the configuration of channelB.
                                                 This parameter can be a value of @ref ll_pwm_none_coding_channel_init_t.*/

    ll_pwm_none_coding_channel_init_t channel_c;    /**< Specifies the configuration of channelC.
                                                 This parameter can be a value of @ref ll_pwm_none_coding_channel_init_t.*/
} ll_pwm_none_coding_mode_init_t;

/**
  * @brief  LL PWM coding mode Structure definition.
  */
typedef struct _ll_pwm_coding_mode_init_t
{
    uint32_t ll_period;                     /**< Specifies the period value which will be used configure PWM output frequency in coding mode.
                                                This parameter must be a number ranges between Min_Data = 0 and Max_Data = SysCoreCLK.*/

    uint32_t ll_waiting_time;               /**< Specifies the waiting time before PWM waveform generation in coding mode.
                                                This parameter control PWM waiting time count in the coding mode.*/

    uint8_t ll_data_width_valid;            /**< Specifies the coding data valid width in Coding mode.
                                                This parameter control coding data valid width = DATA_WIDTH_VALID + 1,
                                                DATA_WIDTH_VALID value ranges between Min_Data = 0x0 and Max_Data = 0x1F.*/

    uint8_t ll_coding_channel_select;       /**< Specifies the coding channel select all 3 channels or only channel A.
                                                This parameter can be a value of @ref PWM_LL_CODING_CHANNEL*/

    ll_pwm_coding_channel_init_t ll_channel_a;     /**< Specifies the configuration of channelA in coding mode.
                                                 This parameter can be a value of @ref ll_pwm_coding_channel_init_t.*/

    ll_pwm_coding_channel_init_t ll_channel_b;     /**< Specifies the configuration of channelB in coding mode.
                                                 This parameter can be a value of @ref ll_pwm_coding_channel_init_t.*/

    ll_pwm_coding_channel_init_t ll_channel_c;     /**< Specifies the configuration of channelC in coding mode.
                                                 This parameter can be a value of @ref ll_pwm_coding_channel_init_t.*/
} ll_pwm_coding_mode_init_t;

/**
  * @brief  LL PWM  init Structure definition.
  */
typedef struct _ll_pwm_init_t
{
    ll_pwm_mode_t ll_mode;         /**< Specifies the PWM output mode.
                                     This parameter can be a value of PWM_LL_EC_MODE.

                                     This feature can be modified afterwards using unitary function @ref ll_pwm_set_mode().*/

    uint32_t ll_prd_cycles;                 /**< Specifies the number of period cycle in Flicker mode or Coding mode.
                                                This parameter control the number of period cycles, when set to 0 will continuously generate waveform.*/

    ll_pwm_none_coding_mode_init_t none_coding_mode_cfg;    /**< Specifies the none coding mode config.
                                                                This parameter can be a value of @ref ll_pwm_none_coding_mode_init_t.*/

    ll_pwm_coding_mode_init_t coding_mode_cfg;              /**< Specifies the coding mode config.
                                                                This parameter can be a value of @ref ll_pwm_coding_mode_init_t.*/

} ll_pwm_init_t;

/** @} */

/** @} */

/**
  * @defgroup  PWM_LL_MACRO Defines
  * @{
  */

/* Exported constants --------------------------------------------------------*/
/** @defgroup PWM_LL_Exported_Constants PWM Exported Constants
  * @{
  */

/** @defgroup PWM_LL_EC_ALIGN PWM alignment pulses
  * @{
  */
#define LL_PWM_EDGE_ALIGNED                 (0x00000000U)       /**< PWM edge-aligned */
#define LL_PWM_CENTER_ALIGNED               (0x00000001U)       /**< PWM center-aligned  */
/** @} */

/** @defgroup PWM_LL_STOP_LVL PWM stop io level
  * @{
  */
#define LL_PWM_STOP_LVL_LOW                 (0x00000000U)       /**< PWM stop in low io level */
#define LL_PWM_STOP_LVL_HIGH                (0x00000001U)       /**< PWM stop in high io level  */
/** @} */

/** @defgroup PWM_LL_WAITING_TIME_LVL PWM waiting time io level
  * @{
  */
#define LL_PWM_WAITING_TIME_LVL_LOW         (0x00000000U)       /**< PWM waiting time io level low */
#define LL_PWM_WAITING_TIME_LVL_HIGH        (0x00000001U)       /**< PWM waiting time io level high */
/** @} */

/** @defgroup PWM_LL_CODING_CHANNEL PWM coding channel select in coding mode
  * @{
  */
#define LL_PWM_CODING_CHANNEL_ALL           (0x00000000U)       /**< Select all channels operation in coding mode */
#define LL_PWM_CODING_CHANNEL_A             (0x00000001U)       /**< Select channle A operation in coding mode */
/** @} */

/** @defgroup PWM_LL_EC_DRIVEPOLARITY PWM drive polarity
  * @{
  */
#define LL_PWM_DRIVEPOLARITY_NEGATIVE       (0x00000000U)       /**< PWM led-negative-drive mode */
#define LL_PWM_DRIVEPOLARITY_POSITIVE       (0x00000001U)       /**< PWM led-positive-drive mode */
/** @} */

/** @defgroup PWM_LL_EC_ACTIONEVENT PWM action event
  * @{
  */
#define LL_PWM_ACTIONEVENT_NONE             (0x00000000U)       /**< No action event      */
#define LL_PWM_ACTIONEVENT_CLEAR            (0x00000001U)       /**< Action event CLEAR   */
#define LL_PWM_ACTIONEVENT_SET              (0x00000002U)       /**< Action event SET     */
#define LL_PWM_ACTIONEVENT_TOGGLE           (0x00000003U)       /**< Action event TOGGLE  */
/** @} */

/** @defgroup PWM_LL_EC_PERIOD_UNIT PWM period unit default configuretion
  * @{
  */
#define LL_PWM_PRESCALER_UNIT               (128)               /**< The unit of prescaler is 128 */
#define LL_PWM_BREATH_PRESCALER_UNIT        (128)               /**< The unit of breath prescaler is 128 */
#define LL_PWM_HOLD_PRESCALER_UNIT          (10)                /**< The unit of hold prescaler is 10 */
/** @} */

/** @defgroup PWM_LL_EC_DEFAULT_CONFIG InitStrcut default configuartion
  * @{
  */

/**
  * @brief LL PWM None Coding Channel InitStrcut default configuartion
  */
#define LL_PWM_NONE_CODING_CHANNEL_DEFAULT_CONFIG                   \
{                                                                   \
    .duty          = 50,                                            \
    .drive_polarity = LL_PWM_DRIVEPOLARITY_POSITIVE,                \
    .flickerstop_lvl = LL_PWM_STOP_LVL_LOW,                         \
}

/**
  * @brief LL PWM Coding Channel InitStrcut default configuartion
  */
#define LL_PWM_CODING_CHANNEL_DEFAULT_CONFIG                        \
{                                                                   \
    .ll_comp0                 = 0,                                  \
    .ll_comp1                 = 640,                                \
    .ll_drive_polarity        = LL_PWM_DRIVEPOLARITY_POSITIVE,      \
    .ll_waiting_time_lvl      = LL_PWM_WAITING_TIME_LVL_LOW,        \
}

/**
  * @brief LL PWM None Coding InitStrcut default configuartion
  */
#define LL_PWM_NONE_CODING_DEFAULT_CONFIG                           \
{                                                       \
    .align          = LL_PWM_EDGE_ALIGNED,              \
    .prescaler      = 10 * LL_PWM_PRESCALER_UNIT,       \
    .bprescaler     = 10 * LL_PWM_BREATH_PRESCALER_UNIT * 10 * LL_PWM_PRESCALER_UNIT,  \
    .hprescaler     = 10 * LL_PWM_HOLD_PRESCALER_UNIT * 10 * LL_PWM_PRESCALER_UNIT,    \
    .breathstop_lvl = LL_PWM_STOP_LVL_LOW,              \
    .channel_a      = LL_PWM_NONE_CODING_CHANNEL_DEFAULT_CONFIG,    \
    .channel_b      = LL_PWM_NONE_CODING_CHANNEL_DEFAULT_CONFIG,    \
    .channel_c      = LL_PWM_NONE_CODING_CHANNEL_DEFAULT_CONFIG,    \
}

/**
  * @brief LL PWM Coding InitStrcut default configuartion
  */
#define LL_PWM_CODING_DEFAULT_CONFIG                                     \
{                                                                        \
    .ll_period                = 640,                                     \
    .ll_waiting_time          = 640,                                     \
    .ll_data_width_valid      = 0x1F,                                    \
    .ll_coding_channel_select = LL_PWM_CODING_CHANNEL_ALL,               \
    .ll_channel_a             = LL_PWM_CODING_CHANNEL_DEFAULT_CONFIG,    \
    .ll_channel_b             = LL_PWM_CODING_CHANNEL_DEFAULT_CONFIG,    \
    .ll_channel_c             = LL_PWM_CODING_CHANNEL_DEFAULT_CONFIG,    \
}

/**
  * @brief LL PWM InitStrcut default configuartion
  */
#define LL_PWM_DEFAULT_CONFIG                                            \
{                                                                        \
    .ll_mode                  = LL_PWM_FLICKER_MODE,                     \
    .ll_prd_cycles            = 0x0,                                     \
    .none_coding_mode_cfg     = LL_PWM_NONE_CODING_DEFAULT_CONFIG,       \
    .coding_mode_cfg          = LL_PWM_CODING_DEFAULT_CONFIG,            \
}

/** @} */

/** @} */

/* Exported macro ------------------------------------------------------------*/
/** @defgroup PWM_LL_Exported_Macros PWM Exported Macros
  * @{
  */

/** @defgroup PWM_LL_EM_WRITE_READ Common Write and read registers Macros
  * @{
  */

/**
  * @brief  Write a value in PWM register
  * @param  __instance__ PWM instance
  * @param  __REG__ Register to be written
  * @param  __VALUE__ Value to be written in the register
  * @retval None
  */
#define LL_PWM_WriteReg(__instance__, __REG__, __VALUE__)  WRITE_REG(__instance__->__REG__, (__VALUE__))

/**
  * @brief  Read a value in PWM register
  * @param  __instance__ PWM instance
  * @param  __REG__ Register to be read
  * @retval Register value
  */
#define LL_PWM_ReadReg(__instance__, __REG__)              READ_REG(__instance__->__REG__)

/** @} */

/** @} */

/** @} */

/* Exported functions --------------------------------------------------------*/
/** @defgroup PWM_LL_DRIVER_FUNCTIONS Functions
  * @{
  */

/** @defgroup PWM_LL_EF_Configuration Configuration functions
  * @{
  */

/**
  * @brief  Enable PWM.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | EN
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->MODE, PWM_MODE_EN);
}

/**
  * @brief  Disable PWM.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | EN
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->MODE, PWM_MODE_EN);
}

/**
  * @brief  Indicate whether the PWM is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | EN
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_EN) == (PWM_MODE_EN));
}

/**
  * @brief  Enable PWM pause.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | PAUSE
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_pause(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->MODE, PWM_MODE_PAUSE);
}

/**
  * @brief  Disable PWM pause.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | PAUSE
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_pause(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->MODE, PWM_MODE_PAUSE);
}

/**
  * @brief  Indicate whether the PWM pause is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | PAUSE
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_pause(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_PAUSE) == (PWM_MODE_PAUSE));
}

/**
  * @brief  Set PWM mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | BREATHEN and CODINGEN
  *
  * @param  PWMx PWM instance
  * @param  mode This parameter can be one of the following values:
  *         @arg @ref LL_PWM_FLICKER_MODE
  *         @arg @ref LL_PWM_BREATH_MODE
  *         @arg @ref LL_PWM_CODING_MODE
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_mode(pwm_regs_t *PWMx, ll_pwm_mode_t mode)
{
    if(mode == LL_PWM_CODING_MODE) {
        if(PWMx == PWM0) {
            MODIFY_REG(PWMx->MODE, PWM_MODE_CODINGEN, 0x1 << PWM_MODE_CODINGEN_Pos);
        }
    } else {
        CLEAR_BITS(PWMx->MODE, PWM_MODE_CODINGEN);
        MODIFY_REG(PWMx->MODE, PWM_MODE_BREATHEN, (mode == LL_PWM_BREATH_MODE) ?
                    (0x1 << PWM_MODE_BREATHEN_Pos) : (0x0 << PWM_MODE_BREATHEN_Pos));
    }
}

/**
  * @brief  Get PWM mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | BREATHEN and CODINGEN
  *
  * @param  PWMx PWM instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_PWM_FLICKER_MODE
  *         @arg @ref LL_PWM_BREATH_MODE
  * 		@arg @ref LL_PWM_CODING_MODE
  */
__STATIC_INLINE ll_pwm_mode_t ll_pwm_get_mode(pwm_regs_t *PWMx)
{
	if(READ_BITS(PWMx->MODE, PWM_MODE_CODINGEN) == PWM_MODE_CODINGEN) {
		return LL_PWM_CODING_MODE;
	} else {
		return ((READ_BITS(PWMx->MODE, PWM_MODE_BREATHEN) == PWM_MODE_BREATHEN) ? LL_PWM_BREATH_MODE : LL_PWM_FLICKER_MODE);
	}
}

/**
  * @brief  Enable positive drive mode in channelA.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | DPENA
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_positive_drive_channel_a(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->MODE, PWM_MODE_DPENA);
}

/**
  * @brief  Disable positive drive mode in channelA.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | DPENA
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_positive_drive_channel_a(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->MODE, PWM_MODE_DPENA);
}

/**
  * @brief  Indicate whether the positive drive mode in channelA is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | DPENA
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_positive_drive_channel_a(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_DPENA) == (PWM_MODE_DPENA));
}

/**
  * @brief  Enable positive drive mode in channelB.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | DPENB
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_positive_drive_channel_b(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->MODE, PWM_MODE_DPENB);
}

/**
  * @brief  Disable positive drive mode in channelB.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | DPENB
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_positive_drive_channel_b(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->MODE, PWM_MODE_DPENB);
}

/**
  * @brief  Indicate whether the positive drive mode in channelB is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | DPENB
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_positive_drive_channel_b(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_DPENB) == (PWM_MODE_DPENB));
}

/**
  * @brief  Enable positive drive mode in channelC.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | DPENC
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_positive_drive_channel_c(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->MODE, PWM_MODE_DPENC);
}

/**
  * @brief  Disable positive drive mode in channelC.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | DPENC
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_positive_drive_channel_c(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->MODE, PWM_MODE_DPENC);
}

/**
  * @brief  Indicate whether the positive drive mode in channelC is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | DPENC
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_positive_drive_channel_c(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_DPENC) == (PWM_MODE_DPENC));
}

/**
  * @brief  Set the channel_a stop level in flicker mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | FLICKER_PAUSE_LEVEL_A
  *
  * @param  PWMx PWM flicker stop level
  * @param  flickerstop_lvl This parameter can be set with 0 or 1.
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_flicker_stop_level_a(pwm_regs_t *PWMx,uint32_t flickerstop_lvl)
{
    MODIFY_REG(PWMx->MODE, PWM_MODE_FLICKER_PAUSE_LEVEL_A, flickerstop_lvl << PWM_MODE_FLICKER_PAUSE_LEVEL_A_Pos);
}

/**
  * @brief  Get the channel_a stop level in flicker mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | FLICKER_PAUSE_LEVEL_A
  *
  * @param  PWMx
  * @retval Return value of 0 or 1.
  */
__STATIC_INLINE uint32_t ll_pwm_get_flicker_stop_level_a(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_FLICKER_PAUSE_LEVEL_A));
}

/**
  * @brief  Set the channel_b stop level in flicker mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | FLICKER_PAUSE_LEVEL_B
  *
  * @param  PWMx PWM flicker stop level
  * @param  flickerstop_lvl This parameter can be set with 0 or 1.
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_flicker_stop_level_b(pwm_regs_t *PWMx,uint32_t flickerstop_lvl)
{
    MODIFY_REG(PWMx->MODE, PWM_MODE_FLICKER_PAUSE_LEVEL_B, flickerstop_lvl << PWM_MODE_FLICKER_PAUSE_LEVEL_B_Pos);
}

/**
  * @brief  Get the channel_b stop level in flicker mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | FLICKER_PAUSE_LEVEL_B
  *
  * @param  PWMx
  * @retval Return value of 0 or 1.
  */
__STATIC_INLINE uint32_t ll_pwm_get_flicker_stop_level_b(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_FLICKER_PAUSE_LEVEL_B));
}

/**
  * @brief  Set the channel_c stop level in flicker mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | FLICKER_PAUSE_LEVEL_C
  *
  * @param  PWMx PWM flicker stop level
  * @param  flickerstop_lvl This parameter can be set with 0 or 1.
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_flicker_stop_level_c(pwm_regs_t *PWMx,uint32_t flickerstop_lvl)
{
    MODIFY_REG(PWMx->MODE, PWM_MODE_FLICKER_PAUSE_LEVEL_C, flickerstop_lvl << PWM_MODE_FLICKER_PAUSE_LEVEL_C_Pos);
}

/**
  * @brief  Get the channel_c stop level in flicker mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | FLICKER_PAUSE_LEVEL_C
  *
  * @param  PWMx
  * @retval Return value of 0 or 1.
  */
__STATIC_INLINE uint32_t ll_pwm_get_flicker_stop_level_c(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_FLICKER_PAUSE_LEVEL_C));
}

/**
  * @brief  Set the channel_a waiting time level in coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | WAITING_TIME_LEVEL_A
  *
  * @param  PWMx
  * @param  waiting_time_lvl This parameter can be set with LL_PWM_WAITING_TIME_LVL_LOW or LL_PWM_WAITING_TIME_LVL_HIGH.
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_waiting_time_level_a(pwm_regs_t *PWMx, uint8_t waiting_time_lvl)
{
    MODIFY_REG(PWMx->MODE, PWM_MODE_WAITING_TIME_LEVEL_A, waiting_time_lvl << PWM_MODE_WAITING_TIME_LEVEL_A_Pos);
}

/**
  * @brief  Get the channel_a waiting time level in coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | WAITING_TIME_LEVEL_A
  *
  * @param  PWMx
  * @retval Return value of 0 or 1.
  */
__STATIC_INLINE uint8_t ll_pwm_get_waiting_time_level_a(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_WAITING_TIME_LEVEL_A) == (PWM_MODE_WAITING_TIME_LEVEL_A));
}

/**
  * @brief  Set the channel_b waiting time level in coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | WAITING_TIME_LEVEL_B
  *
  * @param  PWMx
  * @param  waiting_time_lvl This parameter can be set with LL_PWM_WAITING_TIME_LVL_LOW or LL_PWM_WAITING_TIME_LVL_HIGH.
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_waiting_time_level_b(pwm_regs_t *PWMx, uint8_t waiting_time_lvl)
{
    MODIFY_REG(PWMx->MODE, PWM_MODE_WAITING_TIME_LEVEL_B, waiting_time_lvl << PWM_MODE_WAITING_TIME_LEVEL_B_Pos);
}

/**
  * @brief  Get the channel_b waiting time level in coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | WAITING_TIME_LEVEL_B
  *
  * @param  PWMx
  * @retval Return value of 0 or 1.
  */
__STATIC_INLINE uint8_t ll_pwm_get_waiting_time_level_b(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_WAITING_TIME_LEVEL_B) == (PWM_MODE_WAITING_TIME_LEVEL_B));
}

/**
  * @brief  Set the channel_c waiting time level in coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | WAITING_TIME_LEVEL_C
  *
  * @param  PWMx
  * @param  waiting_time_lvl This parameter can be set with LL_PWM_WAITING_TIME_LVL_LOW or LL_PWM_WAITING_TIME_LVL_HIGH.
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_waiting_time_level_c(pwm_regs_t *PWMx, uint8_t waiting_time_lvl)
{
    MODIFY_REG(PWMx->MODE, PWM_MODE_WAITING_TIME_LEVEL_C, waiting_time_lvl << PWM_MODE_WAITING_TIME_LEVEL_C_Pos);
}

/**
  * @brief  Get the channel_c waiting time level in coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | WAITING_TIME_LEVEL_C
  *
  * @param  PWMx
  * @retval Return value of 0 or 1.
  */
__STATIC_INLINE uint8_t ll_pwm_get_waiting_time_level_c(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_WAITING_TIME_LEVEL_C) == (PWM_MODE_WAITING_TIME_LEVEL_C));
}

/**
  * @brief  Set DMA enable in coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | DMA_EN
  *
  * @param  PWMx
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_dma_enable(pwm_regs_t *PWMx)
{
    MODIFY_REG(PWMx->MODE, PWM_MODE_DMA_EN, 0x1 << PWM_MODE_DMA_EN_Pos);
}

/**
  * @brief  Set DMA disable in coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | DMA_EN
  *
  * @param  PWMx
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_dma_disable(pwm_regs_t *PWMx)
{
    MODIFY_REG(PWMx->MODE, PWM_MODE_DMA_EN, 0x0 << PWM_MODE_DMA_EN_Pos);
}

/**
  * @brief  Get DMA enable or disable.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | DMA_EN
  *
  * @param  PWMx
  * @retval Return value of 0 or 1.
  */
__STATIC_INLINE uint8_t ll_pwm_get_dma_en(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_DMA_EN) == (PWM_MODE_DMA_EN));
}

/**
  * @brief  Choose 3 channels operation in coding mode or only choose channel A operation in coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | CODING_CHANNEL_SELECT
  *
  * @param  PWMx
  * @param  coding_channel This parameter can be set with LL_PWM_CODING_CHANNEL_ALL or LL_PWM_CODING_CHANNEL_A.
  * @retval None
  */
__STATIC_INLINE void ll_pwm_coding_channel_select(pwm_regs_t *PWMx, uint8_t coding_channel)
{
    MODIFY_REG(PWMx->MODE, PWM_MODE_CODING_CHANNEL_SELECT, coding_channel << PWM_MODE_CODING_CHANNEL_SELECT_Pos);
}

/**
  * @brief  Get PWM coding channel.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | CODING_CHANNEL_SELECT
  *
  * @param  PWMx
  * @retval Return value of 0 or 1, 0 represents LL_PWM_CODING_CHANNEL_ALL, 1 represents LL_PWM_CODING_CHANNEL_A
  */
__STATIC_INLINE uint8_t ll_pwm_get_coding_channel(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_CODING_CHANNEL_SELECT) == (PWM_MODE_CODING_CHANNEL_SELECT));
}

/**
  * @brief  Check update active flag
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SAG
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_active_flag_update_all(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->UPDATE, PWM_UPDATE_SAG) == (PWM_UPDATE_SAG));
}

/**
  * @brief  Enable update all parameters.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SA
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_update_all(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->UPDATE, PWM_UPDATE_SA);
}

/**
  * @brief  Disable update all parameters.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SA
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_update_all(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->UPDATE, PWM_UPDATE_SA);
}

/**
  * @brief  Indicate whether the update all parameters is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SA
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_update_all(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->UPDATE, PWM_UPDATE_SA) == (PWM_UPDATE_SA));
}

/**
  * @brief  Enable update period.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSPRD
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_update_period(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->UPDATE, PWM_UPDATE_SSPRD);
}

/**
  * @brief  Disable update period.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSPRD
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_update_period(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->UPDATE, PWM_UPDATE_SSPRD);
}

/**
  * @brief  Indicate whether the update period is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSPRD
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_update_period(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->UPDATE, PWM_UPDATE_SSPRD) == (PWM_UPDATE_SSPRD));
}

/**
  * @brief  Enable update compareA0.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPA0
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_update_compare_a0(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPA0);
}

/**
  * @brief  Disable update compareA0.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPA0
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_update_compare_a0(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPA0);
}

/**
  * @brief  Indicate whether the update compareA0 is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPA0
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_update_compare_a0(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPA0) == (PWM_UPDATE_SSCMPA0));
}

/**
  * @brief  Enable update compareA1.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPA1
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_update_compare_a1(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPA1);
}

/**
  * @brief  Disable update compareA1.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPA1
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_update_compare_a1(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPA1);
}

/**
  * @brief  Indicate whether the update compareA1 is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPA1
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_update_compare_a1(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPA1) == (PWM_UPDATE_SSCMPA1));
}

/**
  * @brief  Enable update compareB0.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPB0
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_update_compare_b0(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPB0);
}

/**
  * @brief  Disable update compareB0.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPB0
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_update_compare_b0(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPB0);
}

/**
  * @brief  Indicate whether the update compareB0 is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPB0
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_update_compare_b0(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPB0) == (PWM_UPDATE_SSCMPB0));
}

/**
  * @brief  Enable update compareB1.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPB1
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_update_compare_b1(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPB1);
}

/**
  * @brief  Disable update compareB1.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPB1
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_update_compare_b1(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPB1);
}

/**
  * @brief  Indicate whether the update compareB1 is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPB1
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_update_compare_b1(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPB1) == (PWM_UPDATE_SSCMPB1));
}

/**
  * @brief  Enable update compareC0.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPC0
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_update_compare_c0(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPC0);
}

/**
  * @brief  Disable update compareC0.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPC0
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_update_compare_c0(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPC0);
}

/**
  * @brief  Indicate whether the update compareC0 is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPC0
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_update_compare_c0(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPC0) == (PWM_UPDATE_SSCMPC0));
}

/**
  * @brief  Enable update compareC1.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPC1
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_update_compare_c1(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPC1);
}

/**
  * @brief  Disable update compareC1.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPC1
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_update_compare_c1(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPC1);
}

/**
  * @brief  Indicate whether the update compareC1 is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSCMPC1
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_update_compare_c1(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->UPDATE, PWM_UPDATE_SSCMPC1) == (PWM_UPDATE_SSCMPC1));
}

/**
  * @brief  Enable update breath period.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSBRPRD
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_update_breath_period(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->UPDATE, PWM_UPDATE_SSBRPRD);
}

/**
  * @brief  Disable update breath period.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSBRPRD
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_update_breath_period(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->UPDATE, PWM_UPDATE_SSBRPRD);
}

/**
  * @brief  Indicate whether the update breath period is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSBRPRD
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_update_breath_period(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->UPDATE, PWM_UPDATE_SSBRPRD) == (PWM_UPDATE_SSBRPRD));
}

/**
  * @brief  Enable update hold period.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSHOLD
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_update_hold_period(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->UPDATE, PWM_UPDATE_SSHOLD);
}

/**
  * @brief  Disable update hold period.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSHOLD
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_update_hold_period(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->UPDATE, PWM_UPDATE_SSHOLD);
}

/**
  * @brief  Indicate whether the update hold period is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSHOLD
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_update_hold_period(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->UPDATE, PWM_UPDATE_SSHOLD) == (PWM_UPDATE_SSHOLD));
}

/**
  * @brief  Enable update active event.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSAQCTRL
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_enable_update_active_event(pwm_regs_t *PWMx)
{
    SET_BITS(PWMx->UPDATE, PWM_UPDATE_SSAQCTRL);
}

/**
  * @brief  Disable update active event.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSAQCTRL
  *
  * @param  PWMx PWM instance
  * @retval None
  */
__STATIC_INLINE void ll_pwm_disable_update_active_event(pwm_regs_t *PWMx)
{
    CLEAR_BITS(PWMx->UPDATE, PWM_UPDATE_SSAQCTRL);
}

/**
  * @brief  Indicate whether the update active event is enabled.
  *
  *  Register|BitsName
  *  --------|--------
  *  UPDATE | SSAQCTRL
  *
  * @param  PWMx PWM instance
  * @retval State of bit (1 or 0).
  */
__STATIC_INLINE uint32_t ll_pwm_is_enabled_update_active_event(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->UPDATE, PWM_UPDATE_SSAQCTRL) == (PWM_UPDATE_SSAQCTRL));
}

/**
  * @brief  Set the PWM prescaler.
  *
  *  Register|BitsName
  *  --------|--------
  *  PRD | PRD
  *
  * @param  PWMx PWM instance
  * @param  prescaler This parameter ranges between Min_Data=1 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_prescaler(pwm_regs_t *PWMx, uint32_t prescaler)
{
    WRITE_REG(PWMx->PRD, prescaler);
}

/**
  * @brief  Get the PWM prescaler.
  *
  *  Register|BitsName
  *  --------|--------
  *  PRD | PRD
  *
  * @param  PWMx PWM instance
  * @retval Return value ranges between Min_Data=1 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_pwm_get_prescaler(pwm_regs_t *PWMx)
{
    return (READ_REG(PWMx->PRD));
}

/**
  * @brief  Set the PWM compare counter A0.
  *
  *  Register|BitsName
  *  --------|--------
  *  CMPA0 | CMPA0
  *
  * @param  PWMx PWM instance
  * @param  compare This parameter ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_compare_a0(pwm_regs_t *PWMx, uint32_t compare)
{
    WRITE_REG(PWMx->CMPA0, compare);
}

/**
  * @brief  Get the PWM compare counter A0.
  *
  *  Register|BitsName
  *  --------|--------
  *  CMPA0 | CMPA0
  *
  * @param  PWMx PWM instance
  * @retval Return value ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_pwm_get_compare_a0(pwm_regs_t *PWMx)
{
    return (READ_REG(PWMx->CMPA0));
}

/**
  * @brief  Set the PWM compare counter A1.
  *
  *  Register|BitsName
  *  --------|--------
  *  CMPA1 | CMPA1
  *
  * @param  PWMx PWM instance
  * @param  compare This parameter ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_compare_a1(pwm_regs_t *PWMx, uint32_t compare)
{
    WRITE_REG(PWMx->CMPA1, compare);
}

/**
  * @brief  Get the PWM compare counter A1.
  *
  *  Register|BitsName
  *  --------|--------
  *  CMPA1 | CMPA1
  *
  * @param  PWMx PWM instance
  * @retval Return value ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_pwm_get_compare_a1(pwm_regs_t *PWMx)
{
    return (READ_REG(PWMx->CMPA1));
}

/**
  * @brief  Set the PWM compare counter B0.
  *
  *  Register|BitsName
  *  --------|--------
  *  CMPB0 | CMPB0
  *
  * @param  PWMx PWM instance
  * @param  compare This parameter ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_compare_b0(pwm_regs_t *PWMx, uint32_t compare)
{
    WRITE_REG(PWMx->CMPB0, compare);
}

/**
  * @brief  Get the PWM compare counter B0.
  *
  *  Register|BitsName
  *  --------|--------
  *  CMPB0 | CMPB0
  *
  * @param  PWMx PWM instance
  * @retval Return value ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_pwm_get_compare_b0(pwm_regs_t *PWMx)
{
    return (READ_REG(PWMx->CMPB0));
}

/**
  * @brief  Set the PWM compare counter B1.
  *
  *  Register|BitsName
  *  --------|--------
  *  CMPB1 | CMPB1
  *
  * @param  PWMx PWM instance
  * @param  compare This parameter ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_compare_b1(pwm_regs_t *PWMx, uint32_t compare)
{
    WRITE_REG(PWMx->CMPB1, compare);
}

/**
  * @brief  Get the PWM compare counter B1.
  *
  *  Register|BitsName
  *  --------|--------
  *  CMPB1 | CMPB1
  *
  * @param  PWMx PWM instance
  * @retval Return value ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_pwm_get_compare_b1(pwm_regs_t *PWMx)
{
    return (READ_REG(PWMx->CMPB1));
}

/**
  * @brief  Set the PWM compare counter C0.
  *
  *  Register|BitsName
  *  --------|--------
  *  CMPC0 | CMPC0
  *
  * @param  PWMx PWM instance
  * @param  compare This parameter ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_compare_c0(pwm_regs_t *PWMx, uint32_t compare)
{
    WRITE_REG(PWMx->CMPC0, compare);
}

/**
  * @brief  Get the PWM compare counter C0.
  *
  *  Register|BitsName
  *  --------|--------
  *  CMPC0 | CMPC0
  *
  * @param  PWMx PWM instance
  * @retval Return value ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_pwm_get_compare_c0(pwm_regs_t *PWMx)
{
    return (READ_REG(PWMx->CMPC0));
}

/**
  * @brief  Set the PWM compare counter C1.
  *
  *  Register|BitsName
  *  --------|--------
  *  CMPC1 | CMPC1
  *
  * @param  PWMx PWM instance
  * @param  compare This parameter ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_compare_c1(pwm_regs_t *PWMx, uint32_t compare)
{
    WRITE_REG(PWMx->CMPC1, compare);
}

/**
  * @brief  Get the PWM compare counter C1.
  *
  *  Register|BitsName
  *  --------|--------
  *  CMPC1 | CMPC1
  *
  * @param  PWMx PWM instance
  * @retval Return value ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_pwm_get_compare_c1(pwm_regs_t *PWMx)
{
    return (READ_REG(PWMx->CMPC1));
}

/**
  * @brief  Set the channel A0 action event when PWM counter value reaches compare counter A0.
  *
  *  Register|BitsName
  *  --------|--------
  *  AQCTRL | A0
  *
  * @param  PWMx PWM instance
  * @param  action_event This parameter can be one of the following values:
  *         @arg @ref LL_PWM_ACTIONEVENT_NONE
  *         @arg @ref LL_PWM_ACTIONEVENT_CLEAR
  *         @arg @ref LL_PWM_ACTIONEVENT_SET
  *         @arg @ref LL_PWM_ACTIONEVENT_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_action_event_cmp_a0(pwm_regs_t *PWMx, uint32_t action_event)
{
    MODIFY_REG(PWMx->AQCTRL, PWM_AQCTRL_A0, action_event << PWM_AQCTRL_A0_Pos);
}

/**
  * @brief  Get the channel A0 action event when PWM counter value reaches compare counter A0.
  *
  *  Register|BitsName
  *  --------|--------
  *  AQCTRL | A0
  *
  * @param  PWMx PWM instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_PWM_ACTIONEVENT_NONE
  *         @arg @ref LL_PWM_ACTIONEVENT_CLEAR
  *         @arg @ref LL_PWM_ACTIONEVENT_SET
  *         @arg @ref LL_PWM_ACTIONEVENT_TOGGLE
  */
__STATIC_INLINE uint32_t ll_pwm_get_action_event_cmp_a0(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->AQCTRL, PWM_AQCTRL_A0) >> PWM_AQCTRL_A0_Pos);
}

/**
  * @brief  Set the channel A1 action event when PWM counter value reaches compare counter A1.
  *
  *  Register|BitsName
  *  --------|--------
  *  AQCTRL | A1
  *
  * @param  PWMx PWM instance
  * @param  action_event This parameter can be one of the following values:
  *         @arg @ref LL_PWM_ACTIONEVENT_NONE
  *         @arg @ref LL_PWM_ACTIONEVENT_CLEAR
  *         @arg @ref LL_PWM_ACTIONEVENT_SET
  *         @arg @ref LL_PWM_ACTIONEVENT_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_action_event_cmp_a1(pwm_regs_t *PWMx, uint32_t action_event)
{
    MODIFY_REG(PWMx->AQCTRL, PWM_AQCTRL_A1, action_event << PWM_AQCTRL_A1_Pos);
}

/**
  * @brief  Get the channel A1 action event when PWM counter value reaches compare counter A1.
  *
  *  Register|BitsName
  *  --------|--------
  *  AQCTRL | A1
  *
  * @param  PWMx PWM instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_PWM_ACTIONEVENT_NONE
  *         @arg @ref LL_PWM_ACTIONEVENT_CLEAR
  *         @arg @ref LL_PWM_ACTIONEVENT_SET
  *         @arg @ref LL_PWM_ACTIONEVENT_TOGGLE
  */
__STATIC_INLINE uint32_t ll_pwm_get_action_event_cmp_a1(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->AQCTRL, PWM_AQCTRL_A1) >> PWM_AQCTRL_A1_Pos);
}

/**
  * @brief  Set the channel B0 action event when PWM counter value reaches compare counter B0.
  *
  *  Register|BitsName
  *  --------|--------
  *  AQCTRL | B0
  *
  * @param  PWMx PWM instance
  * @param  action_event This parameter can be one of the following values:
  *         @arg @ref LL_PWM_ACTIONEVENT_NONE
  *         @arg @ref LL_PWM_ACTIONEVENT_CLEAR
  *         @arg @ref LL_PWM_ACTIONEVENT_SET
  *         @arg @ref LL_PWM_ACTIONEVENT_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_action_event_cmp_b0(pwm_regs_t *PWMx, uint32_t action_event)
{
    MODIFY_REG(PWMx->AQCTRL, PWM_AQCTRL_B0, action_event << PWM_AQCTRL_B0_Pos);
}

/**
  * @brief  Get the channel B0 action event when PWM counter value reaches compare counter B0.
  *
  *  Register|BitsName
  *  --------|--------
  *  AQCTRL | B0
  *
  * @param  PWMx PWM instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_PWM_ACTIONEVENT_NONE
  *         @arg @ref LL_PWM_ACTIONEVENT_CLEAR
  *         @arg @ref LL_PWM_ACTIONEVENT_SET
  *         @arg @ref LL_PWM_ACTIONEVENT_TOGGLE
  */
__STATIC_INLINE uint32_t ll_pwm_get_action_event_cmp_b0(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->AQCTRL, PWM_AQCTRL_B0) >> PWM_AQCTRL_B0_Pos);
}

/**
  * @brief  Set the channel B1 action event when PWM counter value reaches compare counter B1.
  *
  *  Register|BitsName
  *  --------|--------
  *  AQCTRL | B1
  *
  * @param  PWMx PWM instance
  * @param  action_event This parameter can be one of the following values:
  *         @arg @ref LL_PWM_ACTIONEVENT_NONE
  *         @arg @ref LL_PWM_ACTIONEVENT_CLEAR
  *         @arg @ref LL_PWM_ACTIONEVENT_SET
  *         @arg @ref LL_PWM_ACTIONEVENT_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_action_event_cmp_b1(pwm_regs_t *PWMx, uint32_t action_event)
{
    MODIFY_REG(PWMx->AQCTRL, PWM_AQCTRL_B1, action_event << PWM_AQCTRL_B1_Pos);
}

/**
  * @brief  Get the channel B1 action event when PWM counter value reaches compare counter B1.
  *
  *  Register|BitsName
  *  --------|--------
  *  AQCTRL | B1
  *
  * @param  PWMx PWM instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_PWM_ACTIONEVENT_NONE
  *         @arg @ref LL_PWM_ACTIONEVENT_CLEAR
  *         @arg @ref LL_PWM_ACTIONEVENT_SET
  *         @arg @ref LL_PWM_ACTIONEVENT_TOGGLE
  */
__STATIC_INLINE uint32_t ll_pwm_get_action_event_cmp_b1(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->AQCTRL, PWM_AQCTRL_B1) >> PWM_AQCTRL_B1_Pos);
}

/**
  * @brief  Set the channel C0 action event when PWM counter value reaches compare counter C0.
  *
  *  Register|BitsName
  *  --------|--------
  *  AQCTRL | C0
  *
  * @param  PWMx PWM instance
  * @param  action_event This parameter can be one of the following values:
  *         @arg @ref LL_PWM_ACTIONEVENT_NONE
  *         @arg @ref LL_PWM_ACTIONEVENT_CLEAR
  *         @arg @ref LL_PWM_ACTIONEVENT_SET
  *         @arg @ref LL_PWM_ACTIONEVENT_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_action_event_cmp_c0(pwm_regs_t *PWMx, uint32_t action_event)
{
    MODIFY_REG(PWMx->AQCTRL, PWM_AQCTRL_C0, action_event << PWM_AQCTRL_C0_Pos);
}

/**
  * @brief  Get the channel C0 action event when PWM counter value reaches compare counter C0.
  *
  *  Register|BitsName
  *  --------|--------
  *  AQCTRL | C0
  *
  * @param  PWMx PWM instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_PWM_ACTIONEVENT_NONE
  *         @arg @ref LL_PWM_ACTIONEVENT_CLEAR
  *         @arg @ref LL_PWM_ACTIONEVENT_SET
  *         @arg @ref LL_PWM_ACTIONEVENT_TOGGLE
  */
__STATIC_INLINE uint32_t ll_pwm_get_action_event_cmp_c0(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->AQCTRL, PWM_AQCTRL_C0) >> PWM_AQCTRL_C0_Pos);
}

/**
  * @brief  Set the channel C1 action event when PWM counter value reaches compare counter C1.
  *
  *  Register|BitsName
  *  --------|--------
  *  AQCTRL | C1
  *
  * @param  PWMx PWM instance
  * @param  action_event This parameter can be one of the following values:
  *         @arg @ref LL_PWM_ACTIONEVENT_NONE
  *         @arg @ref LL_PWM_ACTIONEVENT_CLEAR
  *         @arg @ref LL_PWM_ACTIONEVENT_SET
  *         @arg @ref LL_PWM_ACTIONEVENT_TOGGLE
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_action_event_cmp_c1(pwm_regs_t *PWMx, uint32_t action_event)
{
    MODIFY_REG(PWMx->AQCTRL, PWM_AQCTRL_C1, action_event << PWM_AQCTRL_C1_Pos);
}

/**
  * @brief  Get the channel C1 action event when PWM counter value reaches compare counter C1.
  *
  *  Register|BitsName
  *  --------|--------
  *  AQCTRL | C1
  *
  * @param  PWMx PWM instance
  * @retval Return value can be one of the following values:
  *         @arg @ref LL_PWM_ACTIONEVENT_NONE
  *         @arg @ref LL_PWM_ACTIONEVENT_CLEAR
  *         @arg @ref LL_PWM_ACTIONEVENT_SET
  *         @arg @ref LL_PWM_ACTIONEVENT_TOGGLE
  */
__STATIC_INLINE uint32_t ll_pwm_get_action_event_cmp_c1(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->AQCTRL, PWM_AQCTRL_C1) >> PWM_AQCTRL_C1_Pos);
}

/**
  * @brief  Set the breath prescaler in breath mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  BRPRD | BRPRD
  *
  * @param  PWMx PWM instance
  * @param  bprescaler This parameter ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_breath_prescaler(pwm_regs_t *PWMx, uint32_t bprescaler)
{
    MODIFY_REG(PWMx->BRPRD, PWM_BRPRD_BRPRD, bprescaler);
}

/**
  * @brief  Get the breath prescaler in breath mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  BRPRD | BRPRD
  *
  * @param  PWMx PWM instance
  * @retval Return value ranges between Min_Data=0 and Max_Data=0xFFFFFFFF
  */
__STATIC_INLINE uint32_t ll_pwm_get_breath_prescaler(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->BRPRD, PWM_BRPRD_BRPRD));
}

/**
  * @brief  Set the hold prescaler in breath mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  HOLD | HOLD
  *
  * @param  PWMx PWM instance
  * @param  hprescaler This parameter ranges between Min_Data=0 and Max_Data=0xFFFFFF
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_hold_prescaler(pwm_regs_t *PWMx, uint32_t hprescaler)
{
    MODIFY_REG(PWMx->HOLD, PWM_HOLD_HOLD, hprescaler);
}

/**
  * @brief  Get the hold prescaler in breath mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  HOLD | HOLD
  *
  * @param  PWMx PWM instance
  * @retval Return value ranges between Min_Data=0 and Max_Data=0xFFFFFF
  */
__STATIC_INLINE uint32_t ll_pwm_get_hold_prescaler(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->HOLD, PWM_HOLD_HOLD));
}

/**
  * @brief  Set the stop level in breath mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | BREATH_PAUSE_LEVEL
  *
  * @param  PWMx PWM breath stop level
  * @param  breathstop_lvl This parameter can be set with 0 or 1.
  * @retval None
  */
__STATIC_INLINE void ll_pwm_set_breath_stop_level(pwm_regs_t *PWMx, uint32_t breathstop_lvl)
{
    MODIFY_REG(PWMx->MODE, PWM_MODE_BREATH_PAUSE_LEVEL, breathstop_lvl << PWM_MODE_BREATH_PAUSE_LEVEL_Pos);
}

/**
  * @brief  Get the stop level in breath mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | BREATH_PAUSE_LEVEL
  *
  * @param  PWMx PWM breath stop level
  * @retval Return value of 0 or 1.
  */
__STATIC_INLINE uint32_t ll_pwm_get_breath_stop_level(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->MODE, PWM_MODE_BREATH_PAUSE_LEVEL));
}

/**
  * @brief  Set the number of PWM period cycle in flicker mode or coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  PRD_CYCLES | PRD_CYCLES
  *
  * @param  PWMx
  * @param  prd_cycles This parameter control the number of period cycles, when set to 0 will continuously generate waveform.
  * @retval None.
  */
__STATIC_INLINE void ll_pwm_set_prd_cycles(pwm_regs_t *PWMx, uint32_t prd_cycles)
{
    WRITE_REG(PWMx->PRD_CYCLES, prd_cycles);
}

/**
  * @brief  Get the number of PWM period cycle.
  *
  *  Register|BitsName
  *  --------|--------
  *  PRD_CYCLES | PRD_CYCLES
  *
  * @param  PWMx
  * @retval Return value ranges between Min_Data=0 and Max_Data=0xFFFFFFFF.
  */
__STATIC_INLINE uint32_t ll_pwm_get_prd_cycles(pwm_regs_t *PWMx)
{
    return (READ_REG(PWMx->PRD_CYCLES));
}

/**
  * @brief  Set the waiting time count in coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  WAIT_TIME | WAIT_TIME
  *
  * @param  PWMx
  * @param  waiting_time This parameter control PWM waiting time in the coding mode.
  * @retval None.
  */
__STATIC_INLINE void ll_pwm_set_waiting_time(pwm_regs_t *PWMx, uint32_t waiting_time)
{
    WRITE_REG(PWMx->WAIT_TIME, waiting_time);
}

/**
  * @brief  Get the waiting time count.
  *
  *  Register|BitsName
  *  --------|--------
  *  WAIT_TIME | WAIT_TIME
  *
  * @param  PWMx
  * @retval Return count value ranges between Min_Data=0 and Max_Data=0xFFFFFFFF.
  */
__STATIC_INLINE uint32_t ll_pwm_get_waiting_time(pwm_regs_t *PWMx)
{
    return (READ_REG(PWMx->WAIT_TIME));
}

/**
  * @brief  Set the valid coding data width in coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  DATA_WIDTH_VALID | DATA_WIDTH_VALID
  *
  * @param  PWMx
  * @param  data_valid_width This parameter control coding data valid width = DATA_WIDTH_VALID + 1,
  * 		DATA_WIDTH_VALID value ranges between Min_Data = 0x0 and Max_Data = 0x1F.
  * @retval None.
  */
__STATIC_INLINE void ll_pwm_set_data_width_valid(pwm_regs_t *PWMx, uint8_t data_valid_width)
{
    MODIFY_REG(PWMx->DATA_WIDTH_VALID, PWM_DATA_WIDTH_VALID, data_valid_width << PWM_DATA_WIDTH_VALID_Pos);
}

/**
  * @brief  Get the valid coding data width.
  *
  *  Register|BitsName
  *  --------|--------
  *  DATA_WIDTH_VALID | DATA_WIDTH_VALID
  *
  * @param  PWMx
  * @retval Return the valid data width in coding mode
  */
__STATIC_INLINE uint8_t ll_pwm_get_data_width_valid(pwm_regs_t *PWMx)
{
    return (uint8_t)(READ_REG(PWMx->DATA_WIDTH_VALID) & PWM_DATA_WIDTH_VALID);
}

/**
  * @brief  Set the PWM coding data in coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  CODING_DATA | CODING_DATA
  *
  * @param  PWMx
  * @param  coding_data This parameter control PWM generate waveform by coding data.
  * @retval None.
  */
__STATIC_INLINE void ll_pwm_set_coding_data(pwm_regs_t *PWMx, uint32_t coding_data)
{
    WRITE_REG(PWMx->CODING_DATA, coding_data);
}

/**
  * @brief  Get the PWM coding data in coding mode.
  *
  *  Register|BitsName
  *  --------|--------
  *  CODING_DATA | CODING_DATA
  *
  * @param  PWMx
  * @retval Return the coding_data value in coding mode.
  */
__STATIC_INLINE uint32_t ll_pwm_get_coding_data(pwm_regs_t *PWMx)
{
    return (READ_REG(PWMx->CODING_DATA));
}

/**
  * @brief  Get pwm coding status
  *
  *  Register|BitsName
  *  --------|--------
  *  CODING_STATUS | CODING_STATUS
  *
  * @param  PWMx
  * @retval Return the pwm coding status
  */
__STATIC_INLINE uint32_t ll_pwm_get_coding_status(pwm_regs_t *PWMx)
{
    return (READ_REG(PWMx->CODING_STATUS));
}

/**
  * @brief  Clear pwma coding error status.
  *
  *  Register|BitsName
  *  --------|--------
  *  CLR_CODING_STATUS | CODING_A_ERROR_CLR
  *
  * @param  PWMx
  * @retval None.
  */
__STATIC_INLINE void ll_pwm_clr_coding_a_error_status(pwm_regs_t *PWMx)
{
    MODIFY_REG(PWMx->CLR_CODING_STATUS, PWM_CODING_STATUS_CODING_A_ERROR_CLR, 0x1 << PWM_CODING_STATUS_CODING_A_ERROR_CLR_Pos);
}

/**
  * @brief  Get pwma coding error status
  *
  *  Register|BitsName
  *  --------|--------
  *  CODING_STATUS | CODING_A_ERROR
  *
  * @param  PWMx
  * @retval Return the pwma coding error status
  */
__STATIC_INLINE uint8_t ll_pwm_get_coding_a_error_status(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->CODING_STATUS, PWM_CODING_STATUS_CODING_A_ERROR) == (PWM_CODING_STATUS_CODING_A_ERROR));
}

/**
  * @brief  Clear pwmb coding error status.
  *
  *  Register|BitsName
  *  --------|--------
  *  CLR_CODING_STATUS | CODING_B_ERROR_CLR
  *
  * @param  PWMx
  * @retval None.
  */
__STATIC_INLINE void ll_pwm_clr_coding_b_error_status(pwm_regs_t *PWMx)
{
    MODIFY_REG(PWMx->CLR_CODING_STATUS, PWM_CODING_STATUS_CODING_B_ERROR_CLR, 0x1 << PWM_CODING_STATUS_CODING_B_ERROR_CLR_Pos);
}

/**
  * @brief  Get pwmb coding error status
  *
  *  Register|BitsName
  *  --------|--------
  *  CODING_STATUS | CODING_B_ERROR
  *
  * @param  PWMx
  * @retval Return the pwmb coding error status
  */
__STATIC_INLINE uint8_t ll_pwm_get_coding_b_error_status(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->CODING_STATUS, PWM_CODING_STATUS_CODING_B_ERROR) == (PWM_CODING_STATUS_CODING_B_ERROR));
}

/**
  * @brief  Clear pwmc coding error status.
  *
  *  Register|BitsName
  *  --------|--------
  *  CLR_CODING_STATUS | CODING_C_ERROR_CLR
  *
  * @param  PWMx
  * @retval None.
  */
__STATIC_INLINE void ll_pwm_clr_coding_c_error_status(pwm_regs_t *PWMx)
{
    MODIFY_REG(PWMx->CLR_CODING_STATUS, PWM_CODING_STATUS_CODING_C_ERROR_CLR, 0x1 << PWM_CODING_STATUS_CODING_C_ERROR_CLR_Pos);
}

/**
  * @brief  Get pwmc coding error status
  *
  *  Register|BitsName
  *  --------|--------
  *  CODING_STATUS | CODING_C_ERROR
  *
  * @param  PWMx
  * @retval Return the pwmc coding error status
  */
__STATIC_INLINE uint8_t ll_pwm_get_coding_c_error_status(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->CODING_STATUS, PWM_CODING_STATUS_CODING_C_ERROR) == (PWM_CODING_STATUS_CODING_C_ERROR));
}

/**
  * @brief  Clear coding done status.
  *
  *  Register|BitsName
  *  --------|--------
  *  CLR_CODING_STATUS | CODING_DONE_CLR
  *
  * @param  PWMx
  * @retval None.
  */
__STATIC_INLINE void ll_pwm_clr_coding_done_status(pwm_regs_t *PWMx)
{
    MODIFY_REG(PWMx->CLR_CODING_STATUS, PWM_CODING_STATUS_CODING_DONE_CLR, 0x1 << PWM_CODING_STATUS_CODING_DONE_CLR_Pos);
}

/**
  * @brief  Get PWM conding done status
  *
  *  Register|BitsName
  *  --------|--------
  *  CODING_STATUS | CODING_DONE
  *
  * @param  PWMx
  * @retval Return the coding done interrupt status
  */
__STATIC_INLINE uint8_t ll_pwm_get_coding_done_status(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->CODING_STATUS, PWM_CODING_STATUS_CODING_DONE) == (PWM_CODING_STATUS_CODING_DONE));
}

/**
  * @brief  Clear coding load status.
  *
  *  Register|BitsName
  *  --------|--------
  *  CLR_CODING_STATUS | CODING_LAOD_CLR
  *
  * @param  PWMx
  * @retval None.
  */
__STATIC_INLINE void ll_pwm_clr_coding_load_status(pwm_regs_t *PWMx)
{
    MODIFY_REG(PWMx->CLR_CODING_STATUS, PWM_CODING_STATUS_CODING_LOAD_CLR, 0x1 << PWM_CODING_STATUS_CODING_LOAD_CLR_Pos);
}

/**
  * @brief  Get PWM conding load status
  *
  *  Register|BitsName
  *  --------|--------
  *  CODING_STATUS | CODING_LOAD
  *
  * @param  PWMx
  * @retval Return the coding load interrupt status
  */
__STATIC_INLINE uint8_t ll_pwm_get_coding_load_status(pwm_regs_t *PWMx)
{
    return (READ_BITS(PWMx->CODING_STATUS, PWM_CODING_STATUS_CODING_LOAD) == (PWM_CODING_STATUS_CODING_LOAD));
}

/**
  * @brief  Get the coding data register address used for DMA transfer
  *
  *  Register|BitsName
  *  --------|--------
  *  MODE | CODING_DATA
  *
  * @param  PWMx
  * @retval Address of coding data register
  */
__STATIC_INLINE uint32_t ll_pwm_dma_get_register_address(pwm_regs_t *PWMx)
{
    return ((uint32_t) &(PWMx->CODING_DATA));
}

/** @} */

/** @defgroup PWM_LL_EF_Init Initialization and de-initialization functions
  * @{
  */

/**
  * @brief  De-initialize PWM registers (Registers restored to their default values).
  * @param  PWMx PWM instance
  * @retval An error_status_t enumeration value:
  *          - SUCCESS: PWM registers are de-initialized
  *          - ERROR: PWM registers are not de-initialized
  */
error_status_t ll_pwm_deinit(pwm_regs_t *PWMx);

/**
  * @brief  Initialize PWM registers according to the specified
  *         parameters in PWM_InitStruct.
  * @param  PWMx PWM instance
  * @param  p_pwm_init Pointer to a ll_pwm_init_t structure that contains the configuration
  *                         information for the specified PWM peripheral.
  * @retval An error_status_t enumeration value:
  *          - SUCCESS: PWM registers are initialized according to p_pwm_init content
  *          - ERROR: Problem occurred during PWM Registers initialization
  */
error_status_t ll_pwm_init(pwm_regs_t *PWMx, ll_pwm_init_t *p_pwm_init);

/**
  * @brief Set each field of a @ref ll_pwm_init_t type structure to default value.
  * @param p_pwm_init  Pointer to a @ref ll_pwm_init_t structure
  *                         whose fields will be set to default values.
  * @retval None
  */
void ll_pwm_struct_init(ll_pwm_init_t *p_pwm_init);

/** @} */

/** @} */

#endif /* PWM0 || PWM1 */

#ifdef __cplusplus
}
#endif

#endif /* __GR533X_LL_PWM_H__ */

/** @} */

/** @} */

/** @} */
