/**
 *****************************************************************************************
 *
 * @file light_HSL_common.h
 *
 * @brief Light HSL Common Define.
 *
 *****************************************************************************************
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
 *****************************************************************************************
 */

 /**
 * @addtogroup MESH
 * @{
 */
#ifndef __LIGHT_HSL_COMMON_H__
#define __LIGHT_HSL_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** Light HSL Server model max number */
#define LIGHT_HSL_SERVER_INSTANCE_COUNT_MAX              (16)
/** Light HSL Client model max number */
#define LIGHT_HSL_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for Light HSL Server */
#define LIGHT_HSL_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for Light HSL Server publish Status message */
#define LIGHT_HSL_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for Light HSL Server response Status message */
#define LIGHT_HSL_SERVER_RSP_SEND_TX_HDL                 (0x01)

/** The total number of transmit handle for Light HSL Client */
#define LIGHT_HSL_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for Light HSL Client Get message */
#define LIGHT_HSL_CLIENT_GET_SEND_TX_HDL                 (LIGHT_HSL_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + LIGHT_HSL_SERVER_TX_HDL_TOTAL * LIGHT_HSL_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Light HSL Client Set message */
#define LIGHT_HSL_CLIENT_SET_SEND_TX_HDL                 (LIGHT_HSL_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for Light HSL Client Set Unacknowledged message */
#define LIGHT_HSL_CLIENT_SET_UNRELIABLE_SEND_TX_HDL      (LIGHT_HSL_CLIENT_SET_SEND_TX_HDL + 1)

/** The reliable message timeout time */
#define LIGHT_HSL_RELIABLE_MSG_TIMEOUT_MS                (30000)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Permanet parameters for the Light HSL Set message. */
typedef struct
{
    uint16_t HSL_hue;                                          /**< Hue State to set */
    uint16_t HSL_stt;                                          /**< Saturation State to set */
    uint16_t HSL_ln;                                           /**< Lightness State to set */
    uint8_t tid;                                               /**< Transaction number for application */
} light_HSL_set_params_t;

typedef struct
{
    uint16_t hue;                                           /**< Hue State to set */
    uint8_t tid;                                            /**< Transaction number for application */
} light_HSL_hue_set_params_t;

typedef struct
{
    uint16_t stt;                                           /**< Saturation State to set */
    uint8_t tid;                                            /**< Transaction number for application */
} light_HSL_stt_set_params_t;


/** Permanet parameters for the Light HSL Default Set message. */
typedef struct
{
    uint16_t hue;                                         /**<Hue State to set */
    uint16_t stt;                                         /**<Saturation State to set */
    uint16_t ln;                                          /**<Lightness State to set */
} light_HSL_set_dft_params_t;

/** Permanet parameters for the Light HSL Range Set message. */
typedef struct
{
    uint16_t min_hue;                                         /**< Hue Rang Min to set */
    uint16_t max_hue;                                         /**< Hue Rang Max State to set */
    uint16_t min_stt;                                         /**< Saturation Rang Min State to set */
    uint16_t max_stt;                                         /**< Hue Rang Max State to set */
} light_HSL_set_range_params_t;


typedef union
{
    struct 
    {
        uint16_t min_hue;                                         
        uint16_t max_hue;                                     
        uint16_t min_stt;                                       
        uint16_t max_stt;                                        
    }range;
    struct
    {
        uint16_t hue;                                        
        uint16_t stt;                                        
        uint16_t ln;                                      
    }dft;
} light_HSL_setup_params_t;

/** Parameters for the Light HSL Status message. */
typedef struct
{
    uint16_t HSL_hue;                                 /**< The present value of the Light HSL Hue state */
    uint16_t HSL_stt;                                 /**< The present value of the Light HSL Saturation state */
    uint16_t HSL_ln;                                  /**< The present value of the Light HSL Lightness state */
    uint32_t remaining_time_ms;                                 /**< Encoded remaining time */
} light_HSL_status_params_t;

typedef struct
{
    uint16_t HSL_hue;                                 /**< The target value of the Light HSL Hue state */
    uint16_t HSL_stt;                                 /**< The target value of the Light HSL Saturation state */
    uint16_t HSL_ln;                                  /**< The target value of the Light HSL Lightness state */
    uint32_t remaining_time_ms;                                 /**< Encoded remaining time */
} light_HSL_target_status_params_t;

/** Message format for the Light HSL Hue Status message. */
typedef struct
{
    uint16_t present_hue;                                  /**< The present value of the Light HSL Hue state */
    uint16_t target_hue;                                 /**< The target value of the Light HSL Hue state */
    uint32_t remaining_time_ms;                                 /**< Encoded remaining time */
} light_HSL_hue_status_params_t;

/** Message format for the Light HSL Saturation Status message. */
typedef struct
{
    uint16_t present_stt;                                  /**< The present value of the Light HSL Saturation state */
    uint16_t target_stt;                                 /**< The target value of the Light HSL Saturation state */
    uint32_t remaining_time_ms;                             /**< Encoded remaining time */
} light_HSL_stt_status_params_t;


typedef struct
{
    uint16_t hue;                                         /**<Hue Default State */
    uint16_t stt;                                         /**<Saturation Default State*/
    uint16_t ln;                                          /**<Lightness Default State*/    
} light_HSL_dft_status_params_t;


typedef struct
{
    uint8_t status_code;
    uint16_t min_hue;                                 /**< The Hue Rang Min value of the Light HSL Hue state */
    uint16_t max_hue;                                 /**< The Hue Rang Max value of the Light HSL Hue state */
    uint16_t min_stt;                                 /**< The Saturation Rang Min value of the Light HSL Saturation state */
    uint16_t max_stt;                                 /**< The Saturation Rang Max value of the Light HSL Saturation state */
} light_HSL_range_status_params_t;

typedef union
{
    light_HSL_status_params_t HSL;
    light_HSL_target_status_params_t HSL_target;
    light_HSL_hue_status_params_t HSL_hue;
    light_HSL_stt_status_params_t HSL_stt;
    light_HSL_dft_status_params_t HSL_dft;
    light_HSL_range_status_params_t HSL_range;
}light_HSL_status_params_u;

#endif /* __LIGHT_HSL_COMMON_H__ */

/** @} */

