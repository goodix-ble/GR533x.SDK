/**
 ****************************************************************************************
 *
 * @file simple_supermarket_label_client.c
 *
 * @brief Simple Supermarket-Label Client Model.
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

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
 
#include "ept_client.h"
#include <string.h>
#include "app_log.h"

#define APP_DEFAULT_TTL     11
#define APP_PERIOD          0
#define APP_PUB_RETX_CNT    1 // Retransmit count
#define APP_PUB_RETX_STEP   1 // Retransmit Step. Unit in 50ms

/*
 * GLOBAL FUNCTION DECLARATION
 *******************************************************************************
 */
//extern void app_dump_bind_info(void);
extern uint16_t app_get_appkey_index(mesh_lid_t model_lid, uint16_t *appkey_index);

static const uint16_t ept_client_opcode_list[] =
{
    DEVICE_ID_OPCODE_STATUS,
    BATTERY_LEVEL_OPCODE_STATUS,
    PRODUCT_CATEGORY_OPCODE_STATUS,
    PRODUCT_NAME_OPCODE_STATUS,
    PRODUCT_ORIGINAL_PRICE_OPCODE_STATUS,
    PRODUCT_DISCOUNT_OPCODE_STATUS,
    PRODUCT_VIP_DISCOUNT_OPCODE_STATUS,
    PRODUCT_DESCRIPTION_OPCODE_STATUS,
    MSG_BITMAP_STATUS,
};

static void handle_device_id_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_battery_level_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_category_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_name_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_original_price_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_discount_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_vip_discount_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_description_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_msg_bitmap_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);

static const mesh_opcode_handler_t ept_opcode_handlers[] =
{
    {DEVICE_ID_OPCODE_GET,                          NULL                                           },
    {DEVICE_ID_OPCODE_STATUS,                       handle_device_id_status_cb                     },
    {BATTERY_LEVEL_OPCODE_GET,                      NULL                                           },
    {BATTERY_LEVEL_OPCODE_STATUS,                   handle_battery_level_status_cb                 },
    {PRODUCT_CATEGORY_OPCODE_GET,                   NULL                                           },
    {PRODUCT_CATEGORY_OPCODE_SET,                   NULL                                           },
    {PRODUCT_CATEGORY_OPCODE_SET_UNRELIABLE,        NULL                                           },
    {PRODUCT_CATEGORY_OPCODE_STATUS,                handle_product_category_status_cb              },
    {PRODUCT_NAME_OPCODE_GET,                       NULL                                           },
    {PRODUCT_NAME_OPCODE_SET,                       NULL                                           },
    {PRODUCT_NAME_OPCODE_SET_UNRELIABLE,            NULL                                           },
    {PRODUCT_NAME_OPCODE_STATUS,                    handle_product_name_status_cb                  },
    {PRODUCT_ORIGINAL_PRICE_OPCODE_GET,             NULL                                           },
    {PRODUCT_ORIGINAL_PRICE_OPCODE_SET,             NULL                                           },
    {PRODUCT_ORIGINAL_PRICE_OPCODE_SET_UNRELIABLE,  NULL                                           },
    {PRODUCT_ORIGINAL_PRICE_OPCODE_STATUS,          handle_product_original_price_status_cb        },
    {PRODUCT_DISCOUNT_OPCODE_GET,                   NULL                                           },
    {PRODUCT_DISCOUNT_OPCODE_SET,                   NULL                                           },
    {PRODUCT_DISCOUNT_OPCODE_SET_UNRELIABLE,        NULL                                           },
    {PRODUCT_DISCOUNT_OPCODE_STATUS,                handle_product_discount_status_cb              },
    {PRODUCT_VIP_DISCOUNT_OPCODE_GET,               NULL                                           },
    {PRODUCT_VIP_DISCOUNT_OPCODE_SET,               NULL                                           },
    {PRODUCT_VIP_DISCOUNT_OPCODE_SET_UNRELIABLE,    NULL                                           },
    {PRODUCT_VIP_DISCOUNT_OPCODE_STATUS,            handle_product_vip_discount_status_cb          },
    {PRODUCT_DESCRIPTION_OPCODE_GET,                NULL                                           },
    {PRODUCT_DESCRIPTION_OPCODE_SET,                NULL                                           },
    {PRODUCT_DESCRIPTION_OPCODE_SET_UNRELIABLE,     NULL                                           },
    {PRODUCT_DESCRIPTION_OPCODE_STATUS,             handle_product_description_status_cb           },
    {MSG_BITMAP_STATUS,                             handle_product_msg_bitmap_status_cb            },
};

static void mesh_msg_model_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void mesh_msg_model_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args);
static void mesh_msg_model_publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args);

static const mesh_model_cb_t mesh_model_msg_cb = {
    .cb_rx             = mesh_msg_model_rx_cb,
    .cb_sent           = mesh_msg_model_sent_cb,
    .cb_publish_period = mesh_msg_model_publish_period_cb,
};

// transport id
//static uint8_t global_tid = 0;

//static bool trans_active[0x20] = {false};
// use for respond
static mesh_model_send_info_t send_info;

static uint8_t global_tx_hdl = 0;

/*****************************************************************************
 * Simple Supermarket-Label client model info / send message info
 *****************************************************************************/
 
static mesh_model_register_info_t supermarket_label_client_register_info = 
{
    .model_id = MESH_MODEL_VENDOR(SIMPLE_SPM_LABEL_CLIENT_MODEL_ID, SIMPLE_SPM_LABEL_COMPANY_ID),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)ept_client_opcode_list,
    .num_opcodes = sizeof(ept_client_opcode_list) / sizeof(uint16_t),
    .p_cb = &mesh_model_msg_cb,
    .p_args = NULL,
};


/*****************************************************************************
 * Simple Supermarket-Label client model register
 *****************************************************************************/

/**@brief Register simple on off client model, obtain the information of registered model.
 *
 * @return Result of register.
 */ 
uint16_t ept_client_init(supermarket_label_client_t *p_client, uint8_t element_offset)
{
    if (NULL == p_client
        || NULL == p_client->p_callbacks
        || NULL == p_client->p_callbacks->discount_status_cb
        || NULL == p_client->p_callbacks->original_price_status_cb
        || NULL == p_client->p_callbacks->product_name_status_cb
        || SPM_LABEL_CLIENT_INSTANCE_COUNT_MAX <= p_client->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }
   
    supermarket_label_client_register_info.p_args         = p_client;
    supermarket_label_client_register_info.element_offset = element_offset;

    return mesh_model_register(&supermarket_label_client_register_info, &p_client->model_lid);
}

/*****************************************************************************
 * Simple Supermarket-Label client model opcode handler callbacks
 *****************************************************************************/
//extern void gus_msg_send(mesh_model_send_info_t *p_rsp_info);

static void handle_device_id_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(device_id_msg_t))
    {
        device_id_msg_t msg = *((device_id_msg_t *)&p_rx_msg->msg[0]);
        APP_LOG_INFO("Receive message, device id is %d!!!\r\n", msg.device_id);
    }
}

static void handle_battery_level_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(battery_level_msg_t))
    {
        supermarket_label_client_t * p_client = (supermarket_label_client_t *) p_args;
        p_client->p_callbacks->battery_level_status_cb(p_rx_msg);
    }
}

static void handle_product_category_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_category_msg_t))
    {
        supermarket_label_client_t * p_client = (supermarket_label_client_t *) p_args;
        p_client->p_callbacks->product_category_status_cb(p_rx_msg);
    }
}

static void handle_product_name_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len >= 2 && p_rx_msg->msg_len <= sizeof(product_name_msg_t))
    {
        supermarket_label_client_t * p_client = (supermarket_label_client_t *) p_args;
        p_client->p_callbacks->product_name_status_cb(p_rx_msg);
    }
}

static void handle_product_original_price_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_original_price_msg_t))
    {
        supermarket_label_client_t * p_client = (supermarket_label_client_t *) p_args;
        p_client->p_callbacks->original_price_status_cb(p_rx_msg);
    }
}

static void handle_product_discount_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_discount_msg_t))
    {
        supermarket_label_client_t * p_client = (supermarket_label_client_t *) p_args;
        p_client->p_callbacks->discount_status_cb(p_rx_msg);
    }
}

static void handle_product_vip_discount_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_vip_discount_msg_t))
    {
        supermarket_label_client_t * p_client = (supermarket_label_client_t *) p_args;
        p_client->p_callbacks->vip_discount_status_cb(p_rx_msg);
    }
}

static void handle_product_description_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_description_msg_t))
    {
        supermarket_label_client_t * p_client = (supermarket_label_client_t *) p_args;
        p_client->p_callbacks->description_status_cb(p_rx_msg);
    }
}

static void handle_product_msg_bitmap_status_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(lpn_bitmap_msg_t))
    {
        supermarket_label_client_t * p_client = (supermarket_label_client_t *) p_args;
        p_client->p_callbacks->msg_bitmap_status_cb(p_rx_msg);
    }
}

/*****************************************************************************
 * Simple Supermarket-Label client model handler callbacks
 *****************************************************************************/
static void mesh_msg_model_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{
    mesh_opcode_handler_cb_t handler = ept_opcode_handlers[p_model_msg->opcode.company_opcode - DEVICE_ID_OPCODE_GET].handler;

    if (NULL != handler)
    {
        send_info.model_lid = p_model_msg->model_lid;
        send_info.opcode.company_id = p_model_msg->opcode.company_id;
        send_info.appkey_index = p_model_msg->appkey_index;
        handler(p_model_msg, p_args);
    }
}

static void mesh_msg_model_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args)
{
    if (p_sent->status == MESH_ERROR_NO_ERROR)
    {
        APP_LOG_INFO("Sent message. model_lid: %d, tx_hdl: %d\n", p_sent->model_lid, p_sent->tx_hdl);
    }
    else
    {
        APP_LOG_INFO("Failed to Send message. model_lid: %d, tx_hdl: %d, status: %04X\n", p_sent->model_lid, p_sent->tx_hdl, p_sent->status);
    }
}

static void mesh_msg_model_publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args)
{
    APP_LOG_INFO("model_publish_period_cb\n");
}

/**
 * @brief Send simple supermarket-label client message(set/get/set_unreliable).
 *
 * @param[in] p_spm_label_client     The source the msg send.
 * @param[in] company_opcode         The vendor specific opcode.
 * @param[in] len                    The data length of the sending message.
 * @param[in] p_data                 Point to the data of the sending message.
 *
 */
uint16_t simple_spm_label_client_msg_send(supermarket_label_client_t* p_spm_label_client, uint8_t company_opcode, uint16_t dst, uint16_t len, uint8_t *p_data)
{
    bool input_valid_flag = false;
    uint16_t status = MESH_ERROR_NO_ERROR;

    switch (company_opcode)
    {
        case DEVICE_ID_OPCODE_GET:
        case BATTERY_LEVEL_OPCODE_GET:
        case PRODUCT_CATEGORY_OPCODE_GET:
        case PRODUCT_NAME_OPCODE_GET:
        case PRODUCT_ORIGINAL_PRICE_OPCODE_GET:
        case PRODUCT_DISCOUNT_OPCODE_GET:
        case PRODUCT_VIP_DISCOUNT_OPCODE_GET:
        case PRODUCT_DESCRIPTION_OPCODE_GET:
        {
            if (len == 0)
                input_valid_flag = true;
            break;
        }
        case PRODUCT_CATEGORY_OPCODE_SET:
        case PRODUCT_CATEGORY_OPCODE_SET_UNRELIABLE:
        {
            if (len == sizeof(product_category_msg_t))
                input_valid_flag = true; 
            break;
        }
        case PRODUCT_NAME_OPCODE_SET:
        case PRODUCT_NAME_OPCODE_SET_UNRELIABLE:
        {
            if (len >= 2 && len <= sizeof(product_name_msg_t))
                input_valid_flag = true; 
            break;
        }
        case PRODUCT_ORIGINAL_PRICE_OPCODE_SET:
        case PRODUCT_ORIGINAL_PRICE_OPCODE_SET_UNRELIABLE:
        {
            if (len == sizeof(product_original_price_msg_t))
                input_valid_flag = true; 
            break;
        }
        case PRODUCT_DISCOUNT_OPCODE_SET:
        case PRODUCT_DISCOUNT_OPCODE_SET_UNRELIABLE:
        {
            if (len == sizeof(product_discount_msg_t))
                input_valid_flag = true; 
            break;
        }
        case PRODUCT_VIP_DISCOUNT_OPCODE_SET:
        case PRODUCT_VIP_DISCOUNT_OPCODE_SET_UNRELIABLE:
        {
            if (len == sizeof(product_vip_discount_msg_t))
                input_valid_flag = true; 
            break;
        }
        case PRODUCT_DESCRIPTION_OPCODE_SET:
        case PRODUCT_DESCRIPTION_OPCODE_SET_UNRELIABLE:
        {
            if (len == sizeof(product_description_msg_t))
                input_valid_flag = true; 
            break;
        }
        default:
            break;
    }

    if (true == input_valid_flag && 0xFF != p_spm_label_client->model_lid)
    {
        uint16_t appkey_index;
        mesh_model_pdu_send_info_t st_send_info;
        //app_dump_bind_info();
        status = app_get_appkey_index(p_spm_label_client->model_lid, &appkey_index); 
        if(MESH_ERROR_NO_ERROR == status)
        {
            // Configure model message for transmission
            st_send_info.model_lid             = p_spm_label_client->model_lid;;
            st_send_info.opcode.company_opcode = company_opcode;
            st_send_info.opcode.company_id     = SIMPLE_SPM_LABEL_COMPANY_ID;
            st_send_info.dst                   = dst;
            st_send_info.period                = APP_PERIOD;
            st_send_info.appkey_index          = appkey_index;
            st_send_info.friendship_credential = false;
            st_send_info.ttl                   = APP_DEFAULT_TTL;
            st_send_info.retx_param            = (APP_PUB_RETX_STEP << 3 | APP_PUB_RETX_CNT);
            st_send_info.tx_hdl                = global_tx_hdl++;
            st_send_info.p_data_send           = p_data;
            st_send_info.data_send_len         = len;

            status = mesh_model_pdu_send(&st_send_info, NULL);
            if(MESH_ERROR_NO_ERROR == status)
            {
                APP_LOG_INFO("Ready to publish msg to [0x%X], msg_id = %d",dst, st_send_info.tx_hdl);
            }
            else
            {
                APP_LOG_INFO("Not ready to publish msg to [0x%X], msg_id = %d",dst, st_send_info.tx_hdl);
            }
        }
    }
    else
    {
        APP_LOG_INFO("INVALID INPUT PARAMETERS");
        status = MESH_ERROR_INVALID_PARAM;
    }
    return status;
}

/**
 * @brief Send simple supermarket-label client message(set/get/set_unreliable) to a address.
 *
 * @param[in] dst_address     The destination of message.
 * @param[in] company_opcode  The vendor specific opcode.
 * @param[in] len             The data length of the sending message.
 * @param[in] p_data          Point to the data of the sending message.
 *
 */
uint16_t simple_spm_label_client_msg_user_send(uint16_t dst, uint8_t company_opcode, uint16_t len, uint8_t *p_data)
{
    send_info.opcode.company_opcode = company_opcode;
    send_info.tx_hdl = global_tx_hdl++;
    send_info.p_data_send = p_data;
    send_info.data_send_len = len;
    send_info.dst = dst;

    return mesh_model_rsp_send(&send_info);
}
