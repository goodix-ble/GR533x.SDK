/**
 *****************************************************************************************
 *
 * @file model_common.c
 *
 * @brief Model Common API Implementation.
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
#include "model_common.h"

/*
 * DEFINES
 ****************************************************************************************
 */



/* As defined in Mesh Model Specification v1.0 */
#define TID_VALIDATION_INTERVAL_MS              (6000)

/* Generic Default Transition Time state pointer array number */
#define GENERIC_DTT_ARR_COUNT       0x10
/*
 * STRUCTURES
 ****************************************************************************************
 */
 


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

uint8_t *app_generic_dtt_ptr_arr[GENERIC_DTT_ARR_COUNT] = {NULL, };


/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void model_tid_timer_cb(void * p_context)
{
    tid_tracker_t * p_item = (tid_tracker_t *) p_context;
    p_item->tid_expiry_timer.callback = NULL;
}

/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

bool model_tid_validate(tid_tracker_t * p_tid_tracker, const mesh_model_msg_ind_t * p_rx_msg,
                        uint32_t message_id, uint8_t tid)
{
    if (p_tid_tracker->src != p_rx_msg->src||
        //p_tid_tracker->dst != p_meta->dst.value ||
        p_tid_tracker->old_tid != tid ||
        p_tid_tracker->message_id != message_id ||
        p_tid_tracker->tid_expiry_timer.callback == NULL)
    {
        p_tid_tracker->src = p_rx_msg->src;
        //p_tid_tracker->dst = p_meta->dst.value;
        p_tid_tracker->message_id = message_id;
        p_tid_tracker->old_tid = tid;

        // if the timer isn't in list, no error occurs.
        mesh_timer_clear(&p_tid_tracker->tid_expiry_timer.timer_id);
        
        p_tid_tracker->tid_expiry_timer.callback = model_tid_timer_cb;
        p_tid_tracker->tid_expiry_timer.p_args = p_tid_tracker;
        p_tid_tracker->tid_expiry_timer.delay_ms = TID_VALIDATION_INTERVAL_MS;
        mesh_timer_set(&p_tid_tracker->tid_expiry_timer);

        p_tid_tracker->new_transaction = true;
    }
    else
    {
        p_tid_tracker->new_transaction = false;
    }

    return p_tid_tracker->new_transaction;
}

bool model_transaction_is_new(tid_tracker_t * p_tid_tracker)
{
    return p_tid_tracker->new_transaction;
}

uint32_t model_transition_time_decode(uint8_t enc_transition_time)
{
    uint32_t time = 0;

    if ((enc_transition_time & ~TRANSITION_TIME_STEP_MASK) == TRANSITION_TIME_UNKNOWN)
    {
        return 0;
    }

    switch(enc_transition_time & TRANSITION_TIME_STEP_MASK)
    {
        case TRANSITION_TIME_STEP_RESOLUTION_100MS:
        {
            time = (enc_transition_time & ~TRANSITION_TIME_STEP_MASK) * TRANSITION_TIME_STEP_100MS_FACTOR;
            break;
        }

        case TRANSITION_TIME_STEP_RESOLUTION_1S:
        {
            time = (enc_transition_time & ~TRANSITION_TIME_STEP_MASK) * TRANSITION_TIME_STEP_1S_FACTOR;
            break;
        }

        case TRANSITION_TIME_STEP_RESOLUTION_10S:
        {
            time = (enc_transition_time & ~TRANSITION_TIME_STEP_MASK) * TRANSITION_TIME_STEP_10S_FACTOR;
            break;
        }

        case TRANSITION_TIME_STEP_RESOLUTION_10M:
        {
            time = (enc_transition_time & ~TRANSITION_TIME_STEP_MASK) * TRANSITION_TIME_STEP_10M_FACTOR;
            break;
        }

        default:
        {
            break;
        }
    }

    return time;
}

uint8_t model_transition_time_encode(uint32_t transition_time)
{
    uint8_t enc_time = TRANSITION_TIME_UNKNOWN;

    if (transition_time <= TRANSITION_TIME_STEP_100MS_MAX)
    {
        enc_time = (transition_time / TRANSITION_TIME_STEP_100MS_FACTOR) | TRANSITION_TIME_STEP_RESOLUTION_100MS;
    }
    else if (transition_time <= TRANSITION_TIME_STEP_1S_MAX)
    {
        enc_time = (transition_time / TRANSITION_TIME_STEP_1S_FACTOR) | TRANSITION_TIME_STEP_RESOLUTION_1S;
    }
    else if (transition_time <= TRANSITION_TIME_STEP_10S_MAX)
    {
        enc_time = (transition_time / TRANSITION_TIME_STEP_10S_FACTOR) | TRANSITION_TIME_STEP_RESOLUTION_10S;
    }
    else if (transition_time <= TRANSITION_TIME_STEP_10M_MAX)
    {
        enc_time = (transition_time / TRANSITION_TIME_STEP_10M_FACTOR) | TRANSITION_TIME_STEP_RESOLUTION_10M;
    }

    return enc_time;
}

bool model_transition_time_is_valid(uint8_t enc_transition_time)
{
    return ((enc_transition_time & ~TRANSITION_TIME_STEP_MASK) != TRANSITION_TIME_UNKNOWN);
}

uint32_t model_delay_decode(uint8_t enc_delay)
{
    return (enc_delay * DELAY_TIME_STEP_FACTOR_MS);
}

uint8_t model_delay_encode(uint32_t delay)
{
    if (delay > (DELAY_TIME_STEP_MAX*DELAY_TIME_STEP_FACTOR_MS))
    {
        return DELAY_TIME_STEP_MAX;
    }
    else
    {
        return (delay/DELAY_TIME_STEP_FACTOR_MS);
    }
}

uint16_t model_register_dtt_ptr(uint8_t element_offset, uint8_t *dtt_value_ptr)
{
    if(element_offset < GENERIC_DTT_ARR_COUNT)
    {
        app_generic_dtt_ptr_arr[element_offset] = dtt_value_ptr;

        return MESH_ERROR_NO_ERROR;
    }

    return MESH_ERROR_SDK_INVALID_PARAM;
}

uint16_t model_update_dtt_ptr(uint8_t **rst_dtt_ptr)
{
    uint8_t * ptr = NULL;

    if(NULL == ptr)
    {
        int16_t i = 0;
        for( ; i < GENERIC_DTT_ARR_COUNT; i++)
        {
            if (NULL != app_generic_dtt_ptr_arr[i])
            {
                ptr = app_generic_dtt_ptr_arr[i];
                break;
            }
        }
    }

    if(NULL != ptr)
    {
        *rst_dtt_ptr = ptr;
        return MESH_ERROR_NO_ERROR;
    }

    return MESH_ERROR_NOT_SUPPORTED;
}

