/**
 *****************************************************************************************
 *
 * @file generic_location_common.h
 *
 * @brief Generic Location Common Define.
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
#ifndef __GENERIC_LOCATION_COMMON_H__
#define __GENERIC_LOCATION_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/** Generic Location Server model max number */
#define GENERIC_LOCATION_SERVER_INSTANCE_COUNT_MAX              (16)
/** Generic Location Client model max number */
#define GENERIC_LOCATION_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for Generic Location Server */
#define GENERIC_LOCATION_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for Generic Location Server publish Status message */
#define GENERIC_LOCATION_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for Generic Location Server response Status message */
#define GENERIC_LOCATION_SERVER_RSP_SEND_TX_HDL                 (0x01)

/** The total number of transmit handle for Generic Location Client */
#define GENERIC_LOCATION_CLIENT_TX_HDL_TOTAL                    (5)
/** The transmit handle for Generic Location Client Get message */
#define GENERIC_LOCATION_CLIENT_GET_SEND_TX_HDL                 (GENERIC_LOCATION_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + GENERIC_LOCATION_SERVER_TX_HDL_TOTAL * GENERIC_LOCATION_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Generic Location Client Set message */
#define GENERIC_LOCATION_CLIENT_SET_LOC_SEND_TX_HDL                 (GENERIC_LOCATION_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for Generic On Off Client Set Unacknowledged message */
#define GENERIC_ONOFF_CLIENT_SET_LOC_UNRELIABLE_SEND_TX_HDL      (GENERIC_LOCATION_CLIENT_SET_LOC_SEND_TX_HDL + 1)
/** The transmit handle for Generic Location Client Set message */
#define GENERIC_LOCATION_CLIENT_SET_GLO_SEND_TX_HDL                 (GENERIC_ONOFF_CLIENT_SET_LOC_UNRELIABLE_SEND_TX_HDL + 1)
/** The transmit handle for Generic On Off Client Set Unacknowledged message */
#define GENERIC_ONOFF_CLIENT_SET_GLO_UNRELIABLE_SEND_TX_HDL      (GENERIC_LOCATION_CLIENT_SET_GLO_SEND_TX_HDL + 1)
/** The reliable message timeout time */
#define GENERIC_LOCATION_RELIABLE_MSG_TIMEOUT_MS                (30000)


/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */
#define LOCATION_LATITUDE_ENCODE(latitude)          (latitude/90*(((int64_t)1<<31)-1))
#define LOCATION_LATITUDE_DECODE(N)                    ((float)N/(((int64_t)1<<31)-1)*90)
#define LOCATION_LONGITUDE_ENCODE(longitude)    (longitude/180*(((int64_t)1<<31)-1))
#define LOCATION_LONGITUDE_DECODE(N)                    ((float)N/(((int64_t)1<<31)-1)*180)
#define LOCATION_FLOOR_NUMBER_ENCODE(floor)                    (floor+20)
#define LOCATION_FLOOR_NUMBER_DECODE(floor)                    (floor-20)

/** Parameters for the Generic location Status message. */
typedef struct
{
    int32_t global_latitude;                     /**< Global Coordinates (Latitude). The Latitude in the range 2^31-1 ~ -2^31+1 */
    int32_t global_longitude;                  /**< Global Coordinates (Longitude). The Longitude in the range 2^31-1 ~ -2^31+1s .*/
    int16_t global_altitude;                 /**<Global Altitude. */
} location_global_status_params_t;

typedef struct
{
    int16_t local_north;                       /**<Local Coordinates (North).*/
    int16_t local_east;                         /**<Local Coordinates (East).*/
    int16_t local_altitude;                   /**<Local Altitude.*/
    uint8_t floor_number;                   /**<Floor Number.*/
    uint16_t uncertainty;                    /**<Uncertainty.*/
} location_local_status_params_t;

#endif /* __GENERIC_LOCATION_COMMON_H__ */

/** @} */

