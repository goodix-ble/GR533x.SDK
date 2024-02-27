/**
 ****************************************************************************************
 *
 * @file generic_power_onoff_common.h
 *
 * @brief Generic Power OnOff Common Define.
 *
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
 *****************************************************************************************
 */


#ifndef __GENERIC_POWER_ONOFF_COMMON_H__
#define __GENERIC_POWER_ONOFF_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */
 
/** Generic Power OnOff Server model max number */
#define GENERIC_POWER_ONOFF_SERVER_INSTANCE_COUNT_MAX                   (16)
/** Generic Power OnOff Client model max number */
#define GENERIC_POWER_ONOFF_CLIENT_INSTANCE_COUNT_MAX                   (16)

/** The total number of transmit handle for Generic Power OnOff Server */
#define GENERIC_POWER_ONOFF_SERVER_TX_HDL_TOTAL                         (2)
/** The transmit handle for Generic Power OnOff Server publish Status message */
#define GENERIC_POWER_ONOFF_SERVER_PUBLISH_SEND_TX_HDL                  (0x00)
/** The transmit handle for Generic Power OnOff Server response Status message */
#define GENERIC_POWER_ONOFF_SERVER_RSP_SEND_TX_HDL                      (0x01) 


/** The total number of transmit handle for Generic Power OnOff Client */
#define GENERIC_POWER_ONOFF_CLIENT_TX_HDL_TOTAL                         (3)
/** The transmit handle for Generic Power OnOff Client Get message */
#define GENERIC_POWER_ONOFF_CLIENT_GET_SEND_TX_HDL                      (GENERIC_POWER_ONOFF_SERVER_PUBLISH_SEND_TX_HDL \
                                                                    + GENERIC_POWER_ONOFF_SERVER_TX_HDL_TOTAL * GENERIC_POWER_ONOFF_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for Generic Power OnOff Client Set message */                                                                                                          //tx_hdl used for send GET message
#define GENERIC_POWER_ONOFF_CLIENT_SET_SEND_TX_HDL                      (GENERIC_POWER_ONOFF_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for Generic Power OnOff Client Set Unacknowledged message */
#define GENERIC_POWER_ONOFF_CLIENT_SET_UNRELIABLE_SEND_TX_HDL           (GENERIC_POWER_ONOFF_CLIENT_SET_SEND_TX_HDL + 1) 

/** The reliable message timeout time */
#define GENERIC_POWER_ONOFF_RELIABLE_MSG_TIMEOUT_MS                     (30000)

/* Model Company ID */
#define GENERIC_POWER_ONOFF_COMPANY_ID 0xFFFF

/* Maximum value of the ON_POWER_UP state, as defined in the Mesh Model Specification v1.0 */
#define GENERIC_ON_POWER_UP_MAX        (0x02)


/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
 * Unpacked message structure typedefs are used for API interfaces and for implementing model code.
 */

/* Parameters for the Generic Power OnOff Set message. */
typedef struct
{                                   
    uint8_t on_power_up;                  /**< Value of the on_power_up state */
} generic_power_onoff_set_params_t;


/* Parameters for the Generic Power OnOff Status message. */
typedef struct
{                                   
    uint8_t on_power_up;                  /**< Value of the on_power_up state */
} generic_power_onoff_status_params_t;                       

#endif /* __GENERIC_POWER_ONOFF_COMMON_H__ */

