/**
 *****************************************************************************************
 *
 * @file light_xyl_common.h
 *
 * @brief Light xyL Common Define.
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
#ifndef __LIGHT_XYL_COMMON_H__
#define __LIGHT_XYL_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** Light xyL Server model max number */
#define LIGHT_XYL_SERVER_INSTANCE_COUNT_MAX              (16)
/** Light xyL Client model max number */
#define LIGHT_XYL_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for Light xyL Server */
#define LIGHT_XYL_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for Light xyL Server publish Status message */
#define LIGHT_XYL_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for Light xyL Server response Status message */
#define LIGHT_XYL_SERVER_RSP_SEND_TX_HDL                 (0x01)

/** The total number of transmit handle for Light xyL Client */
#define LIGHT_XYL_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for Light xyL Client Get message */
#define LIGHT_XYL_CLIENT_GET_SEND_TX_HDL                 (LIGHT_XYL_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + LIGHT_XYL_SERVER_TX_HDL_TOTAL * LIGHT_XYL_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Light xyL Client Set message */
#define LIGHT_XYL_CLIENT_SET_SEND_TX_HDL                 (LIGHT_XYL_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for Light xyL Client Set Unacknowledged message */
#define LIGHT_XYL_CLIENT_SET_UNRELIABLE_SEND_TX_HDL      (LIGHT_XYL_CLIENT_SET_SEND_TX_HDL + 1)

/** The reliable message timeout time */
#define LIGHT_XYL_RELIABLE_MSG_TIMEOUT_MS                (30000)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Permanet parameters for the Light xyL Set message. */
typedef struct
{
    uint16_t xyl_ln;                                         /**< The target value of the Light xyL Lightness state */
    uint16_t xyl_x;                                          /**< The target value of the Light xyL x state */
    uint16_t xyl_y;                                          /**< The target value of the Light xyL y state */
    uint8_t tid;                                                /**< Transaction number for application */
} light_xyl_set_params_t;

typedef struct
{
    uint16_t ln;                                         /**< The value of the Light Lightness Default state */
    uint16_t x;                                          /**< The value of the Light xyL x Default state */
    uint16_t y;                                          /**< The value of the Light xyL y Default state */
} light_xyl_dft_set_params_t;

typedef struct
{
    uint16_t range_min_x;                                         /**< The value of the x Range Min field of the Light xyL Range state */
    uint16_t range_max_x;                                         /**< The value of the x Range Max field of the Light xyL Range state */
    uint16_t range_min_y;                                         /**< The value of the y Range Min field of the Light xyL Range state */
    uint16_t range_max_y;                                         /**< The value of the y Range Max field of the Light xyL Range state */
} light_xyl_set_range_params_t;

/** Message format for the Light xyL Status message. */
typedef struct
{
    uint16_t present_xyl_ln;                                 /**< The present value of the Light xyL Lightness state */
    uint16_t present_xyl_x;                                 /**< The present value of the Light xyL x state */
    uint16_t present_xyl_y;                                 /**< The present value of the Light xyL y state */
    uint32_t remaining_time_ms;                        /**< Remaining time value in milliseconds */
} light_xyl_status_params_t;

typedef struct
{
    uint16_t target_xyl_ln;                                 /**< The present value of the Light xyL Lightness state */
    uint16_t target_xyl_x;                                  /**< The present value of the Light xyL x state */
    uint16_t target_xyl_y;                                  /**< The present value of the Light xyL y state */
    uint32_t remaining_time_ms;                       /**< Remaining time value in milliseconds */
} light_xyl_target_status_params_t;

typedef struct
{
    uint16_t ln;                                         /**< The value of the Light Lightness Default state */
    uint16_t x;                                          /**< The value of the Light xyL x Default state */
    int16_t y;                                           /**< The value of the Light xyL y Default state */
} light_xyl_dft_status_params_t;

typedef struct
{
    uint8_t status_code;                                            /**<Status Code for the requesting message */
    uint16_t range_min_x;                                         /**< The value of the x Range Min field of the Light xyL Range state */
    uint16_t range_max_x;                                         /**< The value of the x Range Max field of the Light xyL Range state */
    uint16_t range_min_y;                                         /**< The value of the y Range Min field of the Light xyL Range state */
    uint16_t range_max_y;                                         /**< The value of the y Range Max field of the Light xyL Range state */
} light_xyl_range_status_params_t;

#endif /* __LIGHT_XYL_COMMON_H__ */

/** @} */

