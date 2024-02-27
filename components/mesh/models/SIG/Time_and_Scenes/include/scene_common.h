/**
 *****************************************************************************************
 *
 * @file scene_common.h
 *
 * @brief  Mesh Scene Common Define.
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
#ifndef __TSCNS_SCENE_COMMON_H__
#define __TSCNS_SCENE_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */

/**   mesh scene Server model max number */
#define TSCNS_SCENE_SERVER_INSTANCE_COUNT_MAX              (16)
/**   mesh scene Client model max number */
#define TSCNS_SCENE_CLIENT_INSTANCE_COUNT_MAX              (16)

/** The total number of transmit handle for   mesh scene Server */
#define TSCNS_SCENE_SERVER_TX_HDL_TOTAL                    (2)
/** The transmit handle for   mesh scene Server publish Status message */
#define TSCNS_SCENE_SERVER_PUBLISH_SEND_TX_HDL             (0x00)
/** The transmit handle for   mesh scene Server response Status message */
#define TSCNS_SCENE_SERVER_RSP_SEND_TX_HDL                 (0x01)

/** The total number of transmit handle for   mesh scene Client */
#define TSCNS_SCENE_CLIENT_TX_HDL_TOTAL                    (3)
/** The transmit handle for   mesh scene Client Get message */
#define TSCNS_SCENE_CLIENT_GET_SEND_TX_HDL                 (TSCNS_SCENE_SERVER_PUBLISH_SEND_TX_HDL \
                                                              + TSCNS_SCENE_SERVER_TX_HDL_TOTAL * TSCNS_SCENE_SERVER_INSTANCE_COUNT_MAX)
/** The transmit handle for   mesh scene Client Set message */
#define TSCNS_SCENE_CLIENT_SET_SEND_TX_HDL                 (TSCNS_SCENE_CLIENT_GET_SEND_TX_HDL + 1)
/** The transmit handle for   mesh scene Client Set Unacknowledged message */
#define TSCNS_SCENE_CLIENT_SET_UNRELIABLE_SEND_TX_HDL      (TSCNS_SCENE_CLIENT_SET_SEND_TX_HDL + 1)

/** The reliable message sceneout scene */
#define TSCNS_SCENE_RELIABLE_MSG_TIMEOUT_MS                (30000)

#define TSCNS_SCENE_REGISTER_SCENE_NUMBER_CNT_MAX   16
/*
 * ENUMERATIONS
 ****************************************************************************************
 */


/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Permanet parameters for the   mesh scene Set message. */
typedef struct
{
    uint16_t scene_number;                          /**< The number of the scene to be stored  . */
} mesh_scene_store_params_t;

typedef struct
{
    uint16_t scene_number;                          /**< The number of the scene to be recalled. */
    uint8_t tid;                                               /**< Transaction number for application */
}mesh_scene_recall_params_t;

typedef struct
{
    uint16_t scene_number;                         /**< The number of the scene to be deleted  . */
}mesh_scene_delete_params_t;

/** Parameters for the scene Status message. */
typedef struct
{
    uint8_t status_code;                                 /**<The Status Code field identifies the status code for the last operation */
    uint16_t current_scene;                           /**< Scene Number of a current scene. */
    uint16_t target_scene;                             /**< Scene Number of a target scene.  */
    uint32_t remaining_time_ms;                  /**< Remaining time value in milliseconds */
} mesh_scene_status_params_t;

typedef struct
{
    uint8_t status_code;                               /**<The Status Code field identifies the status code for the previous operation.*/
    uint16_t current_scene;                          /**< Scene Number of a current scene.*/
    uint16_t scene_cnt;                                 /**< Scene Number count of scenes list . */
    uint16_t scene[TSCNS_SCENE_REGISTER_SCENE_NUMBER_CNT_MAX];                                     /**< A list of scenes stored within an element. */
}mesh_scene_register_status_params_t;

typedef struct
{
    uint8_t status_code;                               /**<The Status Code field identifies the status code for the previous operation.*/
    uint16_t current_scene;                          /**< Scene Number of a current scene.*/
    uint16_t scene_cnt;                                 /**< Scene Number count of scenes list . */
    uint16_t scene[];                                     /**< A list of scenes stored within an element. */
}mesh_scene_recv_register_status_params_t;

#endif /* __TSCNS_SCENE_COMMON_H__ */

/** @} */

