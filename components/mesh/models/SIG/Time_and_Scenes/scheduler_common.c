/**
 *****************************************************************************************
 *
 * @file time_common.c
 *
 * @brief APP Mesh Time Common API Implementation.
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include "scheduler_message.h"
#include "scheduler_common.h"
#include "mesh_common.h"
#include "app_log.h"
#include "common_utils.h"




/*
 * GLOBAL VARIABLES
 ****************************************************************************************
 */

extern bool is_scene_little_endian;

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */
 uint16_t scheduler_pack_action_status(mesh_scheduler_action_status_msg_pkt_t *msg_pkt, const mesh_scheduler_action_status_params_t * p_params)
{
    uint16_t scene_number = 0;
    if ((NULL == msg_pkt) || (NULL == p_params))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    gx_write16p(&scene_number, p_params->scene_number);

    msg_pkt->scheduler_reg_H64 = (p_params->index&TSCNS_SCHEDULER_REGISTER_INDEX_MASK)
                                                        |(p_params->year&TSCNS_SCHEDULER_REGISTER_YEAR_MASK)<<TSCNS_SCHEDULER_REGISTER_YEAR_OFFSET
                                                        | ((uint64_t)p_params->month&TSCNS_SCHEDULER_REGISTER_MONTH_MASK)<<TSCNS_SCHEDULER_REGISTER_MONTH_OFFSET
                                                        | ((uint64_t)p_params->day&TSCNS_SCHEDULER_REGISTER_DAY_MASK)<<TSCNS_SCHEDULER_REGISTER_DAY_OFFSET
                                                        | ((uint64_t)p_params->hour&TSCNS_SCHEDULER_REGISTER_HOUR_MASK)<<TSCNS_SCHEDULER_REGISTER_HOUR_OFFSET//5 bit
                                                        | ((uint64_t)p_params->minute&TSCNS_SCHEDULER_REGISTER_MINUTE_MASK)<<TSCNS_SCHEDULER_REGISTER_MINUTE_OFFSET//6 bit
                                                        | ((uint64_t)p_params->second&TSCNS_SCHEDULER_REGISTER_SECOND_MASK)<<TSCNS_SCHEDULER_REGISTER_SECOND_OFFSET//6 bit
                                                        | ((uint64_t)p_params->dayofweek&TSCNS_SCHEDULER_REGISTER_DAYWEEK_MASK)<<TSCNS_SCHEDULER_REGISTER_DAYWEEK_OFFSET//7 bit
                                                        | ((uint64_t)p_params->action&TSCNS_SCHEDULER_REGISTER_ACTION_MASK)<<TSCNS_SCHEDULER_REGISTER_ACTION_OFFSET// 4 bit
                                                        | ((uint64_t)p_params->transition_time&TSCNS_SCHEDULER_REGISTER_TRANS_TIME_MASK)<<TSCNS_SCHEDULER_REGISTER_TRANS_TIME_OFFSET;//8 bit

    msg_pkt->scheduler_reg_L12 = scene_number;

    APP_LOG_INFO("%s : idx %d, 2%03d-0x%03x-%02d, %02d:%02d:%02d, action %d", __func__, p_params->index, p_params->year, p_params->month,p_params->day,
                                                                                                                                            p_params->hour, p_params->minute, p_params->second, p_params->action);
    return MESH_ERROR_NO_ERROR;
}

uint16_t scheduler_unpack_action_status(mesh_scheduler_action_set_params_t * p_params, mesh_scheduler_action_set_msg_pkt_t *msg_pkt)
{
    if ((NULL == msg_pkt) || (NULL == p_params))
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }


    p_params->index = msg_pkt->scheduler_reg_H64 & TSCNS_SCHEDULER_REGISTER_INDEX_MASK;
    p_params->year = TSCNS_SCHEDULER_REGISTER_YEAR_MASK & msg_pkt->scheduler_reg_H64>>TSCNS_SCHEDULER_REGISTER_YEAR_OFFSET;
    p_params->month = TSCNS_SCHEDULER_REGISTER_MONTH_MASK & (msg_pkt->scheduler_reg_H64 >>TSCNS_SCHEDULER_REGISTER_MONTH_OFFSET);
    p_params->day = TSCNS_SCHEDULER_REGISTER_DAY_MASK & (msg_pkt->scheduler_reg_H64 >>TSCNS_SCHEDULER_REGISTER_DAY_OFFSET);
    p_params->hour = TSCNS_SCHEDULER_REGISTER_HOUR_MASK & (msg_pkt->scheduler_reg_H64 >>TSCNS_SCHEDULER_REGISTER_HOUR_OFFSET);
    p_params->minute = TSCNS_SCHEDULER_REGISTER_MINUTE_MASK & (msg_pkt->scheduler_reg_H64 >>TSCNS_SCHEDULER_REGISTER_MINUTE_OFFSET);
    p_params->second = TSCNS_SCHEDULER_REGISTER_SECOND_MASK & (msg_pkt->scheduler_reg_H64 >>TSCNS_SCHEDULER_REGISTER_SECOND_OFFSET);
    p_params->dayofweek = TSCNS_SCHEDULER_REGISTER_DAYWEEK_MASK & (msg_pkt->scheduler_reg_H64 >>TSCNS_SCHEDULER_REGISTER_DAYWEEK_OFFSET);
    p_params->action = TSCNS_SCHEDULER_REGISTER_ACTION_MASK & (msg_pkt->scheduler_reg_H64 >>TSCNS_SCHEDULER_REGISTER_ACTION_OFFSET);
    p_params->transition_time = TSCNS_SCHEDULER_REGISTER_TRANS_TIME_MASK & (msg_pkt->scheduler_reg_H64 >>TSCNS_SCHEDULER_REGISTER_TRANS_TIME_OFFSET);
    p_params->scene_number = msg_pkt->scheduler_reg_L12;

    APP_LOG_INFO("%s : idx %d, 2%03d-0x%03x-%02d, %02d:%02d:%02d, action %d", __func__, p_params->index, p_params->year, p_params->month,p_params->day,
                                                                                                                                            p_params->hour, p_params->minute, p_params->second, p_params->action);
    return MESH_ERROR_NO_ERROR;
}

