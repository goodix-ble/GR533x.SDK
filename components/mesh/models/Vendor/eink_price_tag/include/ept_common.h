#ifndef SIMPLE_SPM_LABEL_COMMON_H__
#define SIMPLE_SPM_LABEL_COMMON_H__

#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "stdlib.h"

/*lint -align_max(push) -align_max(1) */
/** Company ID value for Shenzhen Goodix Technology Co., Ltd. */
#define ACCESS_COMPANY_ID_GOODIX (0x04F7)
/** Vendor specific company ID for Simple Supermarket-Label model */
#define SIMPLE_SPM_LABEL_COMPANY_ID    (ACCESS_COMPANY_ID_GOODIX)

#define SPM_LABEL_CLIENT_INSTANCE_COUNT_MAX              (16)
#define SPM_LABEL_SERVER_INSTANCE_COUNT_MAX              (16)

/** Simple Supermarket-Label opcodes. */
typedef enum
{
    // Device ID
    DEVICE_ID_OPCODE_GET                           = 0xC1,
    DEVICE_ID_OPCODE_STATUS                        = 0xC2,
    // Battery level
    BATTERY_LEVEL_OPCODE_GET                       = 0xC3,
    BATTERY_LEVEL_OPCODE_STATUS                    = 0xC4,
    // Product category
    PRODUCT_CATEGORY_OPCODE_GET                    = 0xC5,
    PRODUCT_CATEGORY_OPCODE_SET                    = 0xC6,
    PRODUCT_CATEGORY_OPCODE_SET_UNRELIABLE         = 0xC7,
    PRODUCT_CATEGORY_OPCODE_STATUS                 = 0xC8,
    // Product name
    PRODUCT_NAME_OPCODE_GET                        = 0xC9,
    PRODUCT_NAME_OPCODE_SET                        = 0xCA,
    PRODUCT_NAME_OPCODE_SET_UNRELIABLE             = 0xCB,
    PRODUCT_NAME_OPCODE_STATUS                     = 0xCC,
    // Product original price
    PRODUCT_ORIGINAL_PRICE_OPCODE_GET              = 0xCD,
    PRODUCT_ORIGINAL_PRICE_OPCODE_SET              = 0xCE,
    PRODUCT_ORIGINAL_PRICE_OPCODE_SET_UNRELIABLE   = 0xCF,
    PRODUCT_ORIGINAL_PRICE_OPCODE_STATUS           = 0xD0,
    // Product discount
    PRODUCT_DISCOUNT_OPCODE_GET                    = 0xD1,
    PRODUCT_DISCOUNT_OPCODE_SET                    = 0xD2,
    PRODUCT_DISCOUNT_OPCODE_SET_UNRELIABLE         = 0xD3,
    PRODUCT_DISCOUNT_OPCODE_STATUS                 = 0xD4,
    // Product VIP discount
    PRODUCT_VIP_DISCOUNT_OPCODE_GET                = 0xD5,
    PRODUCT_VIP_DISCOUNT_OPCODE_SET                = 0xD6,
    PRODUCT_VIP_DISCOUNT_OPCODE_SET_UNRELIABLE     = 0xD7,
    PRODUCT_VIP_DISCOUNT_OPCODE_STATUS             = 0xD8,
    // Product description
    PRODUCT_DESCRIPTION_OPCODE_GET                 = 0xD9,
    PRODUCT_DESCRIPTION_OPCODE_SET                 = 0xDA,
    PRODUCT_DESCRIPTION_OPCODE_SET_UNRELIABLE      = 0xDB,
    PRODUCT_DESCRIPTION_OPCODE_STATUS              = 0xDC,
    // Msg bitmap for lpn
    MSG_BITMAP_STATUS                              = 0xDD,
    MSG_BITMAP_CFM                                 = 0xDE,
} simple_spm_label_opcode_t;

/** Device ID. */
/** Message format for the Simple Supermarket-Label: Device ID. */
typedef struct __attribute((packed))
{
    uint16_t device_id;
} device_id_msg_t;

/** Battery level. */
/** Message format for the Simple Supermarket-Label: Battery level. */
typedef struct __attribute((packed))
{
    uint8_t battery_level;
} battery_level_msg_t;

/** Product category. */
/** Message format for the Simple Supermarket-Label: Product category. */
typedef struct __attribute((packed))
{
    uint8_t product_category;
} product_category_msg_t;

/** Product name. */
/** Message format for the Simple Supermarket-Label: Product name. */
typedef struct __attribute((packed))
{
    uint8_t name_len;
    uint8_t product_name[20];
} product_name_msg_t;

/** Product original price. */
/** Message format for the Simple Supermarket-Label: Product original price. */
typedef struct __attribute((packed))
{
    uint32_t product_original_price;
} product_original_price_msg_t;

/** Product discount. */
/** Message format for the Simple Supermarket-Label: Product discount. */
typedef struct __attribute((packed))
{
    uint8_t product_discount;
} product_discount_msg_t;

/** Product VIP discount. */
/** Message format for the Simple Supermarket-Label: Product VIP discount. */
typedef struct __attribute((packed))
{
    uint8_t product_vip_discount;
} product_vip_discount_msg_t;

/** Product description. */
/** Message format for the Simple Supermarket-Label: Product description. */
typedef struct __attribute((packed))
{
    uint8_t product_factory;
    uint8_t product_uint;
    uint32_t product_weight;
} product_description_msg_t;

/** Msg bit map. */
/** Message format for the Simple Supermarket-Label: Msg bit map. */
typedef struct __attribute((packed))
{
    uint8_t msg_bit;
} lpn_bitmap_msg_t;

typedef struct
{
    mesh_model_send_info_t publish_info;
    uint8_t opcode;
    uint8_t timer_id;
    uint8_t count;
    uint8_t retrans_count;
    uint32_t retrans_interval;
    bool trans_active_state;
} spm_send_message_info_t;

typedef struct
{
    mesh_model_register_info_t register_info;
    mesh_lid_t                 model_lid;
} spm_model_info_t;

typedef struct
{
    // Device ID
    device_id_msg_t              device_id;
    // Battery_level
    battery_level_msg_t          battery_level;
    // Product category
    product_category_msg_t       product_category;
    // Product name
    product_name_msg_t           product_name;
    // Product original price
    product_original_price_msg_t product_original_price;
    // Product discount
    product_discount_msg_t       product_discount;
    // Product VIP discount
    product_vip_discount_msg_t   product_vip_discount;
    // Product description
    product_description_msg_t    product_description;
} spm_model_data_t;


#endif /* SIMPLE_SPM_LABEL_COMMON_H__ */
