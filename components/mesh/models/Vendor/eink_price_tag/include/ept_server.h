#ifndef SIMPLE_SPM_LABEL_SERVER_H__
#define SIMPLE_SPM_LABEL_SERVER_H__

#include "ept_common.h"

/** Simple Supermarket-Label Server model ID. */
#define SIMPLE_SPM_LABEL_SERVER_MODEL_ID (0x0008)

typedef struct __supermarket_label_server_t supermarket_label_server_t;

typedef void (*supermarket_label_state_status_cb_t)(const mesh_model_msg_ind_t * p_rx_msg);

typedef struct
{
    supermarket_label_state_status_cb_t battery_level_get_cb;
    supermarket_label_state_status_cb_t product_category_get_cb;
    supermarket_label_state_status_cb_t product_category_set_cb;
    supermarket_label_state_status_cb_t product_category_set_unack_cb;
    supermarket_label_state_status_cb_t product_name_get_cb;
    supermarket_label_state_status_cb_t product_name_set_cb;
    supermarket_label_state_status_cb_t product_name_set_unack_cb;
    supermarket_label_state_status_cb_t original_price_get_cb;
    supermarket_label_state_status_cb_t original_price_set_cb;
    supermarket_label_state_status_cb_t original_price_set_unack_cb;
    supermarket_label_state_status_cb_t discount_get_cb;
    supermarket_label_state_status_cb_t discount_set_cb;
    supermarket_label_state_status_cb_t discount_set_unack_cb;
    supermarket_label_state_status_cb_t vip_discount_get_cb;
    supermarket_label_state_status_cb_t vip_discount_set_cb;
    supermarket_label_state_status_cb_t vip_discount_set_unack_cb;
    supermarket_label_state_status_cb_t description_get_cb;
    supermarket_label_state_status_cb_t description_set_cb;
    supermarket_label_state_status_cb_t description_set_unack_cb;
    supermarket_label_state_status_cb_t bitmap_cfm_cb;
} supermarket_label_server_callbacks_t;

struct __supermarket_label_server_t
{
    mesh_lid_t model_lid;
    const supermarket_label_server_callbacks_t *p_callbacks;
    uint8_t model_instance_index;
};

/**@brief Register simple on off server model, obtain the information of registered model.
 *
 * @return Result of register.
 */ 
uint16_t ept_server_init(supermarket_label_server_t *p_client, uint8_t element_offset);

uint16_t simple_spm_label_server_msg_send(uint8_t opcode, uint8_t tx_hdl, uint16_t len, uint8_t *p_data);

#endif /* SIMPLE_SPM_LABEL_SERVER_H__ */
