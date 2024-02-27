/**
 ****************************************************************************************
 *
 * @file simple_supermarket_label_server.c
 *
 * @brief Simple Supermarket-Label Server Model.
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
 
#include "ept_server.h"
#include <string.h>
#include "app_log.h"

// define tx_hdl for publish or rsp
#define SPM_PUBLISH_SEND_TX_HDL             (0x00)   //tx_hdl used for send publish message
#define SPM_RSP_SEND_TX_HDL                 (0x01)   //tx_hdl used for send rsp message

static const uint16_t ept_server_opcode_list[] =
{
    DEVICE_ID_OPCODE_GET,
    BATTERY_LEVEL_OPCODE_GET,
    PRODUCT_CATEGORY_OPCODE_GET,
    PRODUCT_CATEGORY_OPCODE_SET,
    PRODUCT_CATEGORY_OPCODE_SET_UNRELIABLE,
    PRODUCT_NAME_OPCODE_GET,
    PRODUCT_NAME_OPCODE_SET,
    PRODUCT_NAME_OPCODE_SET_UNRELIABLE,
    PRODUCT_ORIGINAL_PRICE_OPCODE_GET,
    PRODUCT_ORIGINAL_PRICE_OPCODE_SET,
    PRODUCT_ORIGINAL_PRICE_OPCODE_SET_UNRELIABLE,
    PRODUCT_DISCOUNT_OPCODE_GET,
    PRODUCT_DISCOUNT_OPCODE_SET,
    PRODUCT_DISCOUNT_OPCODE_SET_UNRELIABLE,
    PRODUCT_VIP_DISCOUNT_OPCODE_GET,
    PRODUCT_VIP_DISCOUNT_OPCODE_SET,
    PRODUCT_VIP_DISCOUNT_OPCODE_SET_UNRELIABLE,
    PRODUCT_DESCRIPTION_OPCODE_GET,
    PRODUCT_DESCRIPTION_OPCODE_SET,
    PRODUCT_DESCRIPTION_OPCODE_SET_UNRELIABLE,
    MSG_BITMAP_CFM,
};

static void handle_device_id_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_battery_level_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_category_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_category_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_category_set_unreliable_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_name_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_name_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_name_set_unreliable_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_original_price_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_original_price_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_original_price_set_unreliable_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_discount_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_discount_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_discount_set_unreliable_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_vip_discount_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_vip_discount_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_vip_discount_set_unreliable_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_description_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_description_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_product_description_set_unreliable_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);
static void handle_msg_bitmap_cfm_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args);


static const mesh_opcode_handler_t ept_opcode_handlers[] =
{
    {DEVICE_ID_OPCODE_GET,                          handle_device_id_get_cb                        },
    {DEVICE_ID_OPCODE_STATUS,                       NULL                                           },
    {BATTERY_LEVEL_OPCODE_GET,                      handle_battery_level_get_cb                    },
    {BATTERY_LEVEL_OPCODE_STATUS,                   NULL                                           },
    {PRODUCT_CATEGORY_OPCODE_GET,                   handle_product_category_get_cb                 },
    {PRODUCT_CATEGORY_OPCODE_SET,                   handle_product_category_set_cb                 },
    {PRODUCT_CATEGORY_OPCODE_SET_UNRELIABLE,        handle_product_category_set_unreliable_cb      },
    {PRODUCT_CATEGORY_OPCODE_STATUS,                NULL                                           },
    {PRODUCT_NAME_OPCODE_GET,                       handle_product_name_get_cb                     },
    {PRODUCT_NAME_OPCODE_SET,                       handle_product_name_set_cb                     },
    {PRODUCT_NAME_OPCODE_SET_UNRELIABLE,            handle_product_name_set_unreliable_cb          },
    {PRODUCT_NAME_OPCODE_STATUS,                    NULL                                           },
    {PRODUCT_ORIGINAL_PRICE_OPCODE_GET,             handle_product_original_price_get_cb           },
    {PRODUCT_ORIGINAL_PRICE_OPCODE_SET,             handle_product_original_price_set_cb           },
    {PRODUCT_ORIGINAL_PRICE_OPCODE_SET_UNRELIABLE,  handle_product_original_price_set_unreliable_cb},
    {PRODUCT_ORIGINAL_PRICE_OPCODE_STATUS,          NULL                                           },
    {PRODUCT_DISCOUNT_OPCODE_GET,                   handle_product_discount_get_cb                 },
    {PRODUCT_DISCOUNT_OPCODE_SET,                   handle_product_discount_set_cb                 },
    {PRODUCT_DISCOUNT_OPCODE_SET_UNRELIABLE,        handle_product_discount_set_unreliable_cb      },
    {PRODUCT_DISCOUNT_OPCODE_STATUS,                NULL                                           },
    {PRODUCT_VIP_DISCOUNT_OPCODE_GET,               handle_product_vip_discount_get_cb             },
    {PRODUCT_VIP_DISCOUNT_OPCODE_SET,               handle_product_vip_discount_set_cb             },
    {PRODUCT_VIP_DISCOUNT_OPCODE_SET_UNRELIABLE,    handle_product_vip_discount_set_unreliable_cb  },
    {PRODUCT_VIP_DISCOUNT_OPCODE_STATUS,            NULL                                           },
    {PRODUCT_DESCRIPTION_OPCODE_GET,                handle_product_description_get_cb              },
    {PRODUCT_DESCRIPTION_OPCODE_SET,                handle_product_description_set_cb              },
    {PRODUCT_DESCRIPTION_OPCODE_SET_UNRELIABLE,     handle_product_description_set_unreliable_cb   },
    {PRODUCT_DESCRIPTION_OPCODE_STATUS,             NULL                                           },
    {MSG_BITMAP_STATUS,                             NULL                                           },
    {MSG_BITMAP_CFM,                                handle_msg_bitmap_cfm_cb                       },
};


static void mesh_msg_model_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args);
static void mesh_msg_model_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf);
static void mesh_msg_model_publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args);

static const mesh_model_cb_t mesh_model_msg_cb = {
    .cb_rx             = mesh_msg_model_rx_cb,
    .cb_sent           = mesh_msg_model_sent_cb,
    .cb_publish_period = mesh_msg_model_publish_period_cb,
};

static mesh_model_send_info_t server_send_info;


/*****************************************************************************
 * Simple Supermarket-Label server model info
 *****************************************************************************/

static mesh_model_register_info_t supermarket_label_server_register_info = 
{
    .model_id = MESH_MODEL_VENDOR(SIMPLE_SPM_LABEL_SERVER_MODEL_ID, SIMPLE_SPM_LABEL_COMPANY_ID),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)ept_server_opcode_list,
    .num_opcodes = sizeof(ept_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &mesh_model_msg_cb,
    .p_args = NULL,
};

/*****************************************************************************
 * Simple Supermarket-Label server model register
 *****************************************************************************/

/**@brief Register simple on off server model, obtain the information of registered model.
 *
 * @return Result of register.
 */
uint16_t ept_server_init(supermarket_label_server_t *p_server, uint8_t element_offset)
{
    if (NULL == p_server
        || NULL == p_server->p_callbacks
        || NULL == p_server->p_callbacks->battery_level_get_cb
        || NULL == p_server->p_callbacks->product_name_set_cb
        || NULL == p_server->p_callbacks->original_price_set_cb
        || NULL == p_server->p_callbacks->discount_set_cb
        || SPM_LABEL_CLIENT_INSTANCE_COUNT_MAX <= p_server->model_instance_index)
    {
        return MESH_ERROR_SDK_INVALID_PARAM;
    }

    server_send_info.dst = 0x0001;
    server_send_info.appkey_index = 0;
    server_send_info.model_lid = 2;

    supermarket_label_server_register_info.p_args         = p_server;
    supermarket_label_server_register_info.element_offset = element_offset;

    return mesh_model_register(&supermarket_label_server_register_info, &p_server->model_lid);
}


uint16_t simple_spm_label_server_msg_send(uint8_t opcode, uint8_t tx_hdl, uint16_t len, uint8_t *p_data)
{
    uint16_t status = MESH_ERROR_NO_ERROR;
    server_send_info.opcode.company_opcode = opcode;
    server_send_info.opcode.company_id = SIMPLE_SPM_LABEL_COMPANY_ID;
    server_send_info.tx_hdl = tx_hdl;
    server_send_info.data_send_len = len;
    server_send_info.p_data_send = p_data;
    bool is_rsp = (tx_hdl == SPM_RSP_SEND_TX_HDL);

    //uint8_t *p_data_send = (uint8_t *)malloc(p_rsp_info->data_send_len + 1);
    //p_data_send[0] = global_tid++;
    //memcpy(&p_data_send[1], p_rsp_info->p_data_send, p_rsp_info->data_send_len);
    //p_rsp_info->p_data_send = p_data_send;
    //p_rsp_info->data_send_len = p_rsp_info->data_send_len + 1;
    //p_rsp_info->p_data_send = p_rsp_info->data_send_len;
    //p_rsp_info->data_send_len = p_rsp_info->data_send_len;

    /*printf("[%s][%d]len: %d\n", __func__, __LINE__, p_rsp_info->data_send_len);
    for(int i = 0; i < p_rsp_info->data_send_len; i++)
        printf("%X ", p_rsp_info->p_data_send[i]);
    printf("\n");*/

    // rsp or publish
    if (is_rsp)
    {
        status = mesh_model_rsp_send(&server_send_info);
        if (MESH_ERROR_NO_ERROR == status)
        {
            APP_LOG_INFO("Ready to response!!!\r\n");
        }
        else
        {
            APP_LOG_INFO("Not Ready to response!!!\r\n");
        }
    }
    else
    {
        status = mesh_model_publish(&server_send_info, NULL);
        if (MESH_ERROR_NO_ERROR == status)
        {
            APP_LOG_INFO("Ready to publish!!!\r\n");
        }
        else
        {
            APP_LOG_INFO("Not Ready to publish!!!\r\n");
        }
    }

    //free(p_data_send);

    return status;
}

/*****************************************************************************
 * Simple Supermarket-Label server model opcode handler callbacks
 *****************************************************************************/

static void handle_device_id_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    
}

static void handle_battery_level_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == 0x00)
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->battery_level_get_cb(p_rx_msg);
    }
}

static void handle_product_category_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == 0x00)
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->product_category_get_cb(p_rx_msg);
    }
}

static void handle_product_category_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_category_msg_t))
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->product_category_set_cb(p_rx_msg);
    }
}

static void handle_product_category_set_unreliable_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_category_msg_t))
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->product_category_set_unack_cb(p_rx_msg);
    }
}

static void handle_product_name_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == 0x00)
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->product_name_get_cb(p_rx_msg);
    }
}

static void handle_product_name_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len <= sizeof(product_name_msg_t))
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->product_name_set_cb(p_rx_msg);
    }
}

static void handle_product_name_set_unreliable_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len <= sizeof(product_name_msg_t))
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->product_name_set_unack_cb(p_rx_msg);
    }
}

static void handle_product_original_price_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == 0x00)
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->original_price_get_cb(p_rx_msg);
    }
}

static void handle_product_original_price_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_original_price_msg_t))
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->original_price_set_cb(p_rx_msg);
    }
}

static void handle_product_original_price_set_unreliable_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_original_price_msg_t))
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->original_price_set_unack_cb(p_rx_msg);
    }
}

static void handle_product_discount_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == 0x00)
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->discount_get_cb(p_rx_msg);
    }
}

static void handle_product_discount_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_discount_msg_t))
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->discount_set_cb(p_rx_msg);
    }
}

static void handle_product_discount_set_unreliable_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_discount_msg_t))
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->discount_set_unack_cb(p_rx_msg);
    }
}

static void handle_product_vip_discount_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == 0x00)
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->vip_discount_get_cb(p_rx_msg);
    }
}

static void handle_product_vip_discount_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_vip_discount_msg_t))
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->vip_discount_set_cb(p_rx_msg);
    }
}

static void handle_product_vip_discount_set_unreliable_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_vip_discount_msg_t))
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->vip_discount_set_unack_cb(p_rx_msg);
    }
}

static void handle_product_description_get_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == 0x00)
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->description_get_cb(p_rx_msg);
    }
}

static void handle_product_description_set_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_description_msg_t))
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->description_set_cb(p_rx_msg);
    }
}

static void handle_product_description_set_unreliable_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    if (p_rx_msg->msg_len == sizeof(product_description_msg_t))
    {
        supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
        p_server->p_callbacks->description_set_unack_cb(p_rx_msg);
    }
}

static void handle_msg_bitmap_cfm_cb(const mesh_model_msg_ind_t *p_rx_msg,  void *p_args)
{
    supermarket_label_server_t * p_server = (supermarket_label_server_t *) p_args;
    p_server->p_callbacks->bitmap_cfm_cb(p_rx_msg);
}

/*****************************************************************************
 * Simple Supermarket-Label server model handler callbacks
 *****************************************************************************/
static void mesh_msg_model_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{
    server_send_info.dst = p_model_msg->src;
    server_send_info.appkey_index = p_model_msg->appkey_index;
    server_send_info.model_lid = p_model_msg->model_lid;

    mesh_opcode_handler_cb_t handler = ept_opcode_handlers[p_model_msg->opcode.company_opcode - DEVICE_ID_OPCODE_GET].handler;

    if (NULL != handler)
    {
        handler(p_model_msg, p_args);
    }
}


static void mesh_msg_model_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    switch(p_sent->tx_hdl)
    {
        case SPM_RSP_SEND_TX_HDL:
            if (MESH_ERROR_NO_ERROR == p_sent->status)
                APP_LOG_INFO("Responsed get or set message!!!\r\n");
            else
                APP_LOG_INFO("Failed to responsed get or set message, status = %x!!!\r\n", p_sent->status);
            break;
        case SPM_PUBLISH_SEND_TX_HDL:
            if (MESH_ERROR_NO_ERROR == p_sent->status)
                APP_LOG_INFO("Published message!!!\r\n");
            else
                APP_LOG_INFO("Failed to published message, status = %x!!!\r\n", p_sent->status);
            break;
        default:
            APP_LOG_INFO("Never here!!!\r\n");
            break;
    }
}

static void mesh_msg_model_publish_period_cb(mesh_model_publish_period_ind_t *p_ind, void *p_args)
{
    
}

