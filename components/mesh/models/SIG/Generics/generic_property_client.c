/**
 ****************************************************************************************
 *
 * @file generic_property_client.c
 *
 * @brief Generic Property Client API Implementation.
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
#include "app_log.h"
#include "generic_property_message.h"
#include "generic_property_client.h"
#include "grx_sys.h"
#include "common_utils.h"
#include "mesh_property.h"

/*
 * LOCAL FUNCTIONS DECLARATION
 ****************************************************************************************
 */
static void property_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void properties_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static void generic_property_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void generic_property_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args);


/*
 * LOCAL VARIABLES
 ****************************************************************************************
 */

static const uint16_t generic_property_client_opcode_list[] =
{
    GENERIC_PROPERTIES_OPCODE_MFR_STATUS,
    GENERIC_PROPERTY_OPCODE_MFR_STATUS,
    GENERIC_PROPERTIES_OPCODE_ADMIN_STATUS,
    GENERIC_PROPERTY_OPCODE_ADMIN_STATUS,
    GENERIC_PROPERTIES_OPCODE_USER_STATUS,
    GENERIC_PROPERTY_OPCODE_USER_STATUS,
    GENERIC_PROPERTIES_OPCODE_CLIENT_STATUS,
};

static const mesh_opcode_handler_t m_opcode_handlers[] =
{
    {GENERIC_PROPERTIES_OPCODE_MFR_STATUS, properties_status_handle},
    {GENERIC_PROPERTY_OPCODE_MFR_STATUS, property_status_handle},
    {GENERIC_PROPERTIES_OPCODE_ADMIN_STATUS, properties_status_handle},
    {GENERIC_PROPERTY_OPCODE_ADMIN_STATUS, property_status_handle},
    {GENERIC_PROPERTIES_OPCODE_USER_STATUS, properties_status_handle},
    {GENERIC_PROPERTY_OPCODE_USER_STATUS, property_status_handle},
    {GENERIC_PROPERTIES_OPCODE_CLIENT_STATUS, properties_status_handle},
};

static const mesh_model_cb_t generic_property_client_msg_cb = {
    .cb_rx             = generic_property_client_rx_cb,
    .cb_sent           = generic_property_client_sent_cb,
    .cb_publish_period = NULL,
};


static mesh_model_register_info_t generic_property_client_register_info = 
{
    .model_id = MESH_MODEL_SIG(MODEL_ID_GENC_PROP),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)generic_property_client_opcode_list,
    .num_opcodes = sizeof(generic_property_client_opcode_list) / sizeof(uint16_t),
    .p_cb = &generic_property_client_msg_cb,
    .p_args = NULL,
};

/*
 * LOCAL FUNCTIONS
 ****************************************************************************************
 */

static void property_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    generic_property_client_t * p_client = (generic_property_client_t *) p_args;
    generic_property_uam_status_params_t in_data = {0,};

    if (p_rx_msg->msg_len >= GENERIC_PROPERTY_UAM_STATUS_MINLEN)
    {
        if (p_rx_msg->msg_len == GENERIC_PROPERTY_UAM_STATUS_MINLEN)
        {
            in_data.property_id = ((uint16_t)p_rx_msg->msg[0]) | ((uint16_t)(p_rx_msg->msg[1])<<8);
        }
        else if(p_rx_msg->msg_len == GENERIC_PROPERTY_UAM_STATUS_MINLEN + 1)
        {
            in_data.property_id = ((uint16_t)p_rx_msg->msg[0]) | ((uint16_t)(p_rx_msg->msg[1])<<8);
            in_data.access = p_rx_msg->msg[2];
        }
        else
        {
            in_data.property_id = ((uint16_t)p_rx_msg->msg[0]) | ((uint16_t)(p_rx_msg->msg[1])<<8);
            in_data.access = p_rx_msg->msg[2];
            in_data.value_length = p_rx_msg->msg_len - GENERIC_PROPERTY_UAM_STATUS_MINLEN - 1;
            in_data.property_value = sys_malloc(in_data.value_length * sizeof(uint8_t));
            memcpy(in_data.property_value, p_rx_msg->msg + 3, in_data.value_length);
            //in_data.property_value = (uint8_t*)p_rx_msg->msg + 3;
        }
        
        if(p_rx_msg->opcode.company_opcode == GENERIC_PROPERTY_OPCODE_MFR_STATUS)
        {
            p_client->settings.p_callbacks->property_mfr_status_cb(p_client, p_rx_msg, &in_data);
        }
        else if(p_rx_msg->opcode.company_opcode == GENERIC_PROPERTY_OPCODE_ADMIN_STATUS)
        {
            p_client->settings.p_callbacks->property_admin_status_cb(p_client, p_rx_msg, &in_data);
        }
        else if(p_rx_msg->opcode.company_opcode == GENERIC_PROPERTY_OPCODE_USER_STATUS)
        {
            p_client->settings.p_callbacks->property_user_status_cb(p_client, p_rx_msg, &in_data);
        }
    }
    if (in_data.property_value != NULL)
    {
        sys_free(in_data.property_value);
        in_data.property_value = NULL;
    }
}

static void properties_status_handle(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    generic_property_client_t * p_client = (generic_property_client_t *) p_args;
    generic_properties_uamc_status_params_t in_data = {0};

    if (p_rx_msg->msg_len % 2 == 0)
    {
        uint16_t id_num = p_rx_msg->msg_len / 2;
        uint8_t* msg = (uint8_t*)p_rx_msg->msg;
        uint16_t* p_buffer = sys_malloc(sizeof(uint16_t) * id_num);
        memcpy(p_buffer, msg, p_rx_msg->msg_len);
        in_data.id_number = id_num;
        in_data.property_id = p_buffer;
        
        if(p_rx_msg->opcode.company_opcode == GENERIC_PROPERTIES_OPCODE_MFR_STATUS)
        {
            p_client->settings.p_callbacks->properties_mfr_status_cb(p_client, p_rx_msg, &in_data);
        }
        else if(p_rx_msg->opcode.company_opcode == GENERIC_PROPERTIES_OPCODE_ADMIN_STATUS)
        {
            p_client->settings.p_callbacks->properties_admin_status_cb(p_client, p_rx_msg, &in_data);
        }
        else if(p_rx_msg->opcode.company_opcode == GENERIC_PROPERTIES_OPCODE_USER_STATUS)
        {
            p_client->settings.p_callbacks->properties_user_status_cb(p_client, p_rx_msg, &in_data);
        }
        else if(p_rx_msg->opcode.company_opcode == GENERIC_PROPERTIES_OPCODE_CLIENT_STATUS)
        {
            p_client->settings.p_callbacks->properties_client_status_cb(p_client, p_rx_msg, &in_data);
        }
        
        sys_free(p_buffer);
    }
}

#ifdef MESH_MODEL_BQB_TEST
static void message_send_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, uint8_t * p_buffer, uint16_t length)
{
    mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_SIG(company_opcode);

    // fill publish data by tx_hdl
    p_msg_tx->model_lid        = model_lid;
    p_msg_tx->opcode           = opcode;
    p_msg_tx->tx_hdl           = tx_hdl;
    p_msg_tx->p_data_send      = p_buffer;
    p_msg_tx->data_send_len    = length;
    p_msg_tx->dst              = MESH_INVALID_ADDR;
    p_msg_tx->appkey_index     = MESH_INVALID_KEY_INDEX;
}

static void user_set_message_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, const generic_property_user_set_params_t * p_params, uint8_t* *p_buffer)
{
    uint16_t length = 0;
    if(p_params->value_length == 0 && p_params->property_value == NULL)
    {
        length = GENERIC_PROPERTY_USER_SET_MINLEN;
        *p_buffer = sys_malloc(sizeof(uint8_t) * length);
        gx_write16p(*p_buffer, p_params->property_id);
    }
    else
    {
        length = GENERIC_PROPERTY_USER_SET_MINLEN + p_params->value_length;
        *p_buffer = sys_malloc(sizeof(uint8_t) * length);
        gx_write16p(*p_buffer, p_params->property_id);
        memcpy((*p_buffer)+2, p_params->property_value, p_params->value_length);
    }
    message_send_create(p_msg_tx, model_lid, company_opcode, tx_hdl, *p_buffer, length);
}

static void admin_set_message_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, const generic_property_admin_set_params_t * p_params, uint8_t** p_buffer)
{
    uint16_t length = 0;
    if(p_params->value_length == 0 && p_params->property_value == NULL)
    {
        length = GENERIC_PROPERTY_ADMIN_SET_MINLEN;
        *p_buffer = sys_malloc(sizeof(uint8_t) * length);
        gx_write16p(*p_buffer, p_params->property_id);
        gx_write8((*p_buffer)+2, p_params->access);
    }
    else
    {
        length = GENERIC_PROPERTY_ADMIN_SET_MINLEN + p_params->value_length;
        *p_buffer = sys_malloc(sizeof(uint8_t) * length);
        gx_write16p(*p_buffer, p_params->property_id);
        gx_write8((*p_buffer)+2, p_params->access);
        memcpy(*p_buffer+3, p_params->property_value, p_params->value_length);
    }
    message_send_create(p_msg_tx, model_lid, company_opcode, tx_hdl, *p_buffer, length);
}

static void mfr_set_message_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, const generic_property_mfr_set_params_t * p_params, uint8_t** p_buffer)
{
    uint16_t length = GENERIC_PROPERTY_MFR_SET_LEN;
    *p_buffer = sys_malloc(sizeof(uint8_t) * length);
    gx_write16p(*p_buffer, p_params->property_id);
    gx_write8((*p_buffer)+2, p_params->access);

    message_send_create(p_msg_tx, model_lid, company_opcode, tx_hdl, *p_buffer, length);
}

static void uam_get_message_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, const generic_property_uam_get_params_t * p_params)
{
    uint16_t length = GENERIC_PROPERTY_UAM_GET_LEN;
    message_send_create(p_msg_tx, model_lid, company_opcode, tx_hdl, (uint8_t*)&(p_params->property_id), length);
}

static uint16_t model_send_unicast_dev(generic_property_client_t *p_client, mesh_model_send_info_t * p_msg_tx)
{
    p_msg_tx->dst = 0x01;
    p_msg_tx->appkey_index = 0x00;

    return mesh_model_pdu_send(p_msg_tx);
}
#else
static void inline message_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, mesh_access_opcode_t opcode,
                                   uint8_t tx_hdl, uint8_t* p_buffer, uint16_t length)
{
    // fill publish data by tx_hdl
    p_msg_tx->model_lid              = model_lid;
    p_msg_tx->opcode                = opcode;
    p_msg_tx->tx_hdl                = tx_hdl;   
    p_msg_tx->p_data_send           = p_buffer;
    p_msg_tx->data_send_len         = length;
    p_msg_tx->dst                   = MESH_INVALID_ADDR;
    p_msg_tx->appkey_index         = MESH_INVALID_KEY_INDEX;
}

static void user_set_message_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, const generic_property_user_set_params_t * p_params, uint8_t* *p_buffer)
{
    mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_SIG(company_opcode);
    uint16_t length = 0;
    if(p_params->value_length == 0 && p_params->property_value == NULL)
    {
        length = GENERIC_PROPERTY_USER_SET_MINLEN;
        *p_buffer = sys_malloc(sizeof(uint8_t) * length);
        gx_write16p(*p_buffer, p_params->property_id);
    }
    else
    {
        length = GENERIC_PROPERTY_USER_SET_MINLEN + p_params->value_length;
        *p_buffer = sys_malloc(sizeof(uint8_t) * length);
        gx_write16p(*p_buffer, p_params->property_id);
        memcpy((*p_buffer)+2, p_params->property_value, p_params->value_length);
    }
    message_create(p_msg_tx, model_lid, opcode, tx_hdl, *p_buffer, length);
}

static void admin_set_message_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, const generic_property_admin_set_params_t * p_params, uint8_t** p_buffer)
{
    mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_SIG(company_opcode);
    uint16_t length = 0;
    if(p_params->value_length == 0 && p_params->property_value == NULL)
    {
        length = GENERIC_PROPERTY_ADMIN_SET_MINLEN;
        *p_buffer = sys_malloc(sizeof(uint8_t) * length);
        gx_write16p(*p_buffer, p_params->property_id);
        gx_write8((*p_buffer)+2, p_params->access);
    }
    else
    {
        length = GENERIC_PROPERTY_ADMIN_SET_MINLEN + p_params->value_length;
        *p_buffer = sys_malloc(sizeof(uint8_t) * length);
        gx_write16p(*p_buffer, p_params->property_id);
        gx_write8((*p_buffer)+2, p_params->access);
        memcpy(*p_buffer+3, p_params->property_value, p_params->value_length);
    }
    message_create(p_msg_tx, model_lid, opcode, tx_hdl, *p_buffer, length);
}

static void mfr_set_message_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, const generic_property_mfr_set_params_t * p_params, uint8_t** p_buffer)
{
    mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_SIG(company_opcode);
    uint16_t length = GENERIC_PROPERTY_MFR_SET_LEN;
    *p_buffer = sys_malloc(sizeof(uint8_t) * length);
    gx_write16p(*p_buffer, p_params->property_id);
    gx_write8((*p_buffer)+2, p_params->access);

    message_create(p_msg_tx, model_lid, opcode, tx_hdl, *p_buffer, length);
}

static void uam_get_message_create(mesh_model_send_info_t * p_msg_tx, mesh_lid_t model_lid, uint16_t company_opcode,
                                   uint8_t tx_hdl, const generic_property_uam_get_params_t * p_params)
{
    mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_SIG(company_opcode);
    uint16_t length = GENERIC_PROPERTY_UAM_GET_LEN;
    message_create(p_msg_tx, model_lid, opcode, tx_hdl, (uint8_t*)&(p_params->property_id), length);
}
#endif

static void generic_property_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{  
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;
    uint8_t index = 0;
    switch(company_opcode)
    {
        case GENERIC_PROPERTIES_OPCODE_MFR_STATUS:
            index = 0;
            break;
        case GENERIC_PROPERTY_OPCODE_MFR_STATUS:
            index = 1;
            break;
        case GENERIC_PROPERTIES_OPCODE_ADMIN_STATUS:
            index = 2;
            break;
        case GENERIC_PROPERTY_OPCODE_ADMIN_STATUS:
            index = 3;
            break;
        case GENERIC_PROPERTIES_OPCODE_USER_STATUS:
            index = 4;
            break;
        case GENERIC_PROPERTY_OPCODE_USER_STATUS:
            index = 5;
            break;
        case GENERIC_PROPERTIES_OPCODE_CLIENT_STATUS:
            index = 6;
            break;
    }

    mesh_opcode_handler_cb_t handler = m_opcode_handlers[index].handler;

    if (NULL != handler)
    {
        handler(p_model_msg, p_args);
    }
}

static void generic_property_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args)
{
    generic_property_client_t * p_client = (generic_property_client_t *) p_args;
    
    switch(p_sent->tx_hdl - p_client->model_instance_index * GENERIC_PROPERTY_CLIENT_TX_HDL_TOTAL)
    {
        case GENERIC_PROPERTY_CLIENT_GET_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent get message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send get message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case GENERIC_PROPERTY_CLIENT_SET_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent set message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send set message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        case GENERIC_PROPERTY_CLIENT_SET_UNRELIABLE_SEND_TX_HDL:
            if(MESH_ERROR_NO_ERROR == p_sent->status)
            {
                APP_LOG_INFO("CLIENT[%d] -- Sent set(unreliable) message!!!", p_client->model_instance_index);
            }
            else
            {
                APP_LOG_INFO("CLIENT[%d] -- Failed to send set(unreliable) message, status = %x!!!", p_client->model_instance_index, p_sent->status);
            }
            break;
        default:
            APP_LOG_INFO("msg has been sent!!!");
            break;
    }   
}



/*
 * GLOBAL FUNCTIONS
 ****************************************************************************************
 */

uint16_t generic_property_client_init(generic_property_client_t *p_client, uint8_t element_offset)
{
    if (NULL == p_client
        || NULL == p_client->settings.p_callbacks
        || NULL == p_client->settings.p_callbacks->property_user_status_cb
        || NULL == p_client->settings.p_callbacks->properties_user_status_cb
        || NULL == p_client->settings.p_callbacks->property_admin_status_cb
        || NULL == p_client->settings.p_callbacks->properties_admin_status_cb
        || NULL == p_client->settings.p_callbacks->property_mfr_status_cb
        || NULL == p_client->settings.p_callbacks->properties_mfr_status_cb
        || NULL == p_client->settings.p_callbacks->properties_client_status_cb
        || NULL == p_client->settings.p_callbacks->ack_transaction_status_cb
        || GENERIC_PROPERTY_CLIENT_INSTANCE_COUNT_MAX <= p_client->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    
    generic_property_client_register_info.p_args         = p_client;
    generic_property_client_register_info.element_offset = element_offset;
    
    return mesh_model_register(&generic_property_client_register_info, &p_client->model_lid);
}


uint16_t generic_property_client_user_set(generic_property_client_t * p_client, const generic_property_user_set_params_t * p_params)
{
    if (!is_property_msg_length_valid(p_params->property_id, p_params->value_length))
    {
        APP_LOG_INFO("Input message length is invalid.");
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    uint8_t* p_buffer = NULL;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = GENERIC_PROPERTY_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * GENERIC_PROPERTY_CLIENT_TX_HDL_TOTAL;
    mesh_model_send_info_t model_msg_send;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(GENERIC_PROPERTY_OPCODE_USER_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif    

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            user_set_message_create(&model_msg_send, p_client->model_lid, GENERIC_PROPERTY_OPCODE_USER_SET, tx_hdl, p_params, &p_buffer);
#ifdef MESH_MODEL_BQB_TEST
            uint16_t status = model_send_unicast_dev(p_client, &model_msg_send);
            sys_free(p_buffer);
            p_buffer = NULL;
            return status;
#else
            uint16_t status = mesh_model_publish(&model_msg_send, &reliable_info);
            sys_free(p_buffer);
            p_buffer = NULL;
            return status;
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }    
}

uint16_t generic_property_client_user_set_unack(generic_property_client_t * p_client, const generic_property_user_set_params_t * p_params)
{
    if (!is_property_msg_length_valid(p_params->property_id, p_params->value_length))
    {
        APP_LOG_INFO("Input message length is invalid.");
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    uint8_t* p_buffer = NULL;
    uint8_t tx_hdl = GENERIC_PROPERTY_CLIENT_SET_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * GENERIC_PROPERTY_CLIENT_TX_HDL_TOTAL;    

    mesh_model_send_info_t model_msg_send;

    if (p_client == NULL || p_params == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    
    user_set_message_create(&model_msg_send, p_client->model_lid, GENERIC_PROPERTY_OPCODE_USER_SET_UNACKNOWLEDGED, tx_hdl, p_params, &p_buffer);
#ifdef MESH_MODEL_BQB_TEST
    uint16_t status = model_send_unicast_dev(p_client, &model_msg_send);
    sys_free(p_buffer);
    p_buffer = NULL;
    return status;
#else
    uint16_t status = mesh_model_publish(&model_msg_send, NULL);
    sys_free(p_buffer);
    p_buffer = NULL;
    return status;
#endif
}

uint16_t generic_property_client_admin_set(generic_property_client_t * p_client, const generic_property_admin_set_params_t * p_params)
{
    if (!is_property_msg_length_valid(p_params->property_id, p_params->value_length))
    {
        APP_LOG_INFO("Input message length is invalid.");
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    uint8_t* p_buffer = NULL;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = GENERIC_PROPERTY_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * GENERIC_PROPERTY_CLIENT_TX_HDL_TOTAL;
    mesh_model_send_info_t model_msg_send;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(GENERIC_PROPERTY_OPCODE_ADMIN_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif    

    if (p_client == NULL || p_params == NULL || p_params->access > is_user_property_read_write)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            admin_set_message_create(&model_msg_send, p_client->model_lid, GENERIC_PROPERTY_OPCODE_ADMIN_SET, tx_hdl, p_params, &p_buffer);
#ifdef MESH_MODEL_BQB_TEST
            uint16_t status = model_send_unicast_dev(p_client, &model_msg_send);
            sys_free(p_buffer);
            p_buffer = NULL;
            return status;
#else
            uint16_t status = mesh_model_publish(&model_msg_send, &reliable_info);
            sys_free(p_buffer);
            p_buffer = NULL;
            return status;
#endif
        } 
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    } 
    
}


uint16_t generic_property_client_admin_set_unack(generic_property_client_t * p_client, const generic_property_admin_set_params_t * p_params)
{
    if (!is_property_msg_length_valid(p_params->property_id, p_params->value_length))
    {
        APP_LOG_INFO("Input message length is invalid.");
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    uint8_t* p_buffer = NULL;
    uint8_t tx_hdl = GENERIC_PROPERTY_CLIENT_SET_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * GENERIC_PROPERTY_CLIENT_TX_HDL_TOTAL;         

    mesh_model_send_info_t model_msg_send;

    if (p_client == NULL || p_params == NULL || p_params->access > is_user_property_read_write)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
    admin_set_message_create(&model_msg_send, p_client->model_lid, GENERIC_PROPERTY_OPCODE_ADMIN_SET_UNACKNOWLEDGED, tx_hdl, p_params, &p_buffer);
#ifdef MESH_MODEL_BQB_TEST
    uint16_t status = model_send_unicast_dev(p_client, &model_msg_send);
    sys_free(p_buffer);
    p_buffer = NULL;
    return status;
#else
    uint16_t status = mesh_model_publish(&model_msg_send, NULL);
    sys_free(p_buffer);
    p_buffer = NULL;
    return status;
#endif
}

uint16_t generic_property_client_mfr_set(generic_property_client_t * p_client, const generic_property_mfr_set_params_t * p_params)
{
    uint8_t* p_buffer = NULL;
    bool reliable_trans_state = false;
    uint8_t tx_hdl = GENERIC_PROPERTY_CLIENT_SET_SEND_TX_HDL + p_client->model_instance_index * GENERIC_PROPERTY_CLIENT_TX_HDL_TOTAL;
    mesh_model_send_info_t model_msg_send;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(GENERIC_PROPERTY_OPCODE_MFR_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif    

    if (p_client == NULL || p_params == NULL || p_params->access > is_user_property_read)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            mfr_set_message_create(&model_msg_send, p_client->model_lid, GENERIC_PROPERTY_OPCODE_MFR_SET, tx_hdl, p_params, &p_buffer);

#ifdef MESH_MODEL_BQB_TEST
            uint16_t status = model_send_unicast_dev(p_client, &model_msg_send);
            sys_free(p_buffer);
            p_buffer = NULL;
            return status;
#else
            uint16_t status = mesh_model_publish(&model_msg_send, &reliable_info);
            sys_free(p_buffer);
            p_buffer = NULL;
            return status;
#endif
        }
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    } 
    
}

uint16_t generic_property_client_mfr_set_unack(generic_property_client_t * p_client, const generic_property_mfr_set_params_t * p_params)
{
    uint8_t* p_buffer = NULL;
    uint8_t tx_hdl = GENERIC_PROPERTY_CLIENT_SET_UNRELIABLE_SEND_TX_HDL + p_client->model_instance_index * GENERIC_PROPERTY_CLIENT_TX_HDL_TOTAL;

    mesh_model_send_info_t model_msg_send;

    if (p_client == NULL || p_params == NULL || p_params->access > is_user_property_read)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    mfr_set_message_create(&model_msg_send, p_client->model_lid, GENERIC_PROPERTY_OPCODE_MFR_SET_UNACKNOWLEDGED, tx_hdl, p_params, &p_buffer);
#ifdef MESH_MODEL_BQB_TEST
    uint16_t status = model_send_unicast_dev(p_client, &model_msg_send);
    sys_free(p_buffer);
    p_buffer = NULL;
    return status;
#else
    uint16_t status = mesh_model_publish(&model_msg_send, NULL);
    sys_free(p_buffer);
    p_buffer = NULL;
    return status;
#endif
}
  
uint16_t generic_property_client_uam_get(generic_property_client_t * p_client, const generic_property_uam_get_params_t * p_params, property_cmd_type_t cmd_type)
{
    APP_LOG_INFO("[%s] property_id: %04x", __func__,p_params->property_id);
    uint16_t send_opcode;
    
    if (USER == cmd_type)
    {
        send_opcode = GENERIC_PROPERTY_OPCODE_USER_GET;
    }
    else if (ADMIN == cmd_type)
    {
        send_opcode = GENERIC_PROPERTY_OPCODE_ADMIN_GET;
    }
    else if (MFR == cmd_type)
    {
        send_opcode = GENERIC_PROPERTY_OPCODE_MFR_GET;
    }
    
    bool reliable_trans_state = false;
    uint8_t tx_hdl = GENERIC_PROPERTY_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * GENERIC_PROPERTY_CLIENT_TX_HDL_TOTAL;
    mesh_model_send_info_t model_msg_send;
#ifndef MESH_MODEL_BQB_TEST
    uint16_t company_opcode;
    if (USER == cmd_type)
    {
        company_opcode = GENERIC_PROPERTY_OPCODE_USER_STATUS;
    }
    else if (ADMIN == cmd_type)
    {
        company_opcode = GENERIC_PROPERTY_OPCODE_ADMIN_STATUS;
    }
    else if (MFR == cmd_type)
    {
        company_opcode = GENERIC_PROPERTY_OPCODE_MFR_STATUS;
    }

    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(company_opcode),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif    

    if (p_client == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            uam_get_message_create(&model_msg_send, p_client->model_lid, send_opcode, tx_hdl, p_params);
#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, &model_msg_send);
#else
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t generic_properties_client_uam_get(generic_property_client_t * p_client,  property_cmd_type_t cmd_type)
{
    uint16_t send_opcode;
    
    if (USER == cmd_type)
    {
        send_opcode = GENERIC_PROPERTIES_OPCODE_USER_GET;
    }
    else if (ADMIN == cmd_type)
    {
        send_opcode = GENERIC_PROPERTIES_OPCODE_ADMIN_GET;
    }
    else if (MFR == cmd_type)
    {
        send_opcode = GENERIC_PROPERTIES_OPCODE_MFR_GET;
    }
    
    bool reliable_trans_state = false;
    uint8_t tx_hdl = GENERIC_PROPERTY_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * GENERIC_PROPERTY_CLIENT_TX_HDL_TOTAL;
    mesh_model_send_info_t model_msg_send;
#ifndef MESH_MODEL_BQB_TEST
    uint16_t company_opcode;
    
    if (USER == cmd_type)
    {
        company_opcode = GENERIC_PROPERTIES_OPCODE_USER_STATUS;
    }
    else if (ADMIN == cmd_type)
    {
        company_opcode = GENERIC_PROPERTIES_OPCODE_ADMIN_STATUS;
    }
    else if (MFR == cmd_type)
    {
        company_opcode = GENERIC_PROPERTIES_OPCODE_MFR_STATUS;
    }

    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(company_opcode),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif    

    if (p_client == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
#ifdef MESH_MODEL_BQB_TEST
            message_send_create(&model_msg_send, p_client->model_lid, send_opcode, tx_hdl, NULL, 0);
            return model_send_unicast_dev(p_client, &model_msg_send);
#else
            mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_SIG(send_opcode);
            message_create(&model_msg_send, p_client->model_lid, opcode, tx_hdl, NULL, 0);
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}

uint16_t generic_properties_client_get(generic_property_client_t * p_client, const generic_properties_client_get_params_t * p_params)
{
    bool reliable_trans_state = false;
    uint8_t tx_hdl = GENERIC_PROPERTY_CLIENT_GET_SEND_TX_HDL + p_client->model_instance_index * GENERIC_PROPERTY_CLIENT_TX_HDL_TOTAL;
    mesh_model_send_info_t model_msg_send;
#ifndef MESH_MODEL_BQB_TEST
    mesh_model_reliable_info_t reliable_info =
    {
        .reply_opcode = MESH_ACCESS_OPCODE_SIG(GENERIC_PROPERTIES_OPCODE_CLIENT_STATUS),
        .status_cb = p_client->settings.p_callbacks->ack_transaction_status_cb,
        .timeout_ms = p_client->settings.timeout_ms,
    };
#endif    
    
    if (p_client == NULL)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    if (MESH_ERROR_NO_ERROR == mesh_model_reliable_trans_is_on(p_client->model_lid, &reliable_trans_state))
    {
        if (reliable_trans_state)
        {
            return MESH_ERROR_SDK_RELIABLE_TRANS_ON;
        }
        else
        {
            /**The Properties Client Get message create is same with the Property User/Admin/Manufacture Get */
            uam_get_message_create(&model_msg_send, p_client->model_lid, GENERIC_PROPERTIES_OPCODE_CLIENT_GET, 
                                   tx_hdl, (generic_property_uam_get_params_t *)p_params);
#ifdef MESH_MODEL_BQB_TEST
            return model_send_unicast_dev(p_client, &model_msg_send);
#else
            return mesh_model_publish(&model_msg_send, &reliable_info);
#endif
        }        
    }
    else
    {
        return MESH_ERROR_SDK_INVALID_PARAM; 
    }
}
