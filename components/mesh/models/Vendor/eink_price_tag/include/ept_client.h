#ifndef SIMPLE_SPM_LABEL_CLIENT_H__
#define SIMPLE_SPM_LABEL_CLIENT_H__

#include "ept_common.h"

/** Simple Supermarket-Label Client model ID. */
#define SIMPLE_SPM_LABEL_CLIENT_MODEL_ID (0x0009)

typedef struct __supermarket_label_client_t supermarket_label_client_t;

typedef void (*supermarket_label_state_status_cb_t)(const mesh_model_msg_ind_t * p_rx_msg);

typedef struct
{
    supermarket_label_state_status_cb_t battery_level_status_cb;
    supermarket_label_state_status_cb_t product_category_status_cb;
    supermarket_label_state_status_cb_t product_name_status_cb;
    supermarket_label_state_status_cb_t original_price_status_cb;
    supermarket_label_state_status_cb_t discount_status_cb;
    supermarket_label_state_status_cb_t vip_discount_status_cb;
    supermarket_label_state_status_cb_t description_status_cb;
    supermarket_label_state_status_cb_t msg_bitmap_status_cb;
} supermarket_label_client_callbacks_t;

struct __supermarket_label_client_t
{
    mesh_lid_t model_lid;
    const supermarket_label_client_callbacks_t *p_callbacks;
    uint8_t model_instance_index;
};

/**@brief Register simple on off client model, obtain the information of registered model.
 *
 * @return Result of register.
 */ 
uint16_t ept_client_init(supermarket_label_client_t *p_client, uint8_t element_offset);

/**
 * @brief Send simple supermarket-label client message(set/get/set_unreliable).
 *
 * @param[in] p_spm_label_client     The source the msg send.
 * @param[in] company_opcode         The vendor specific opcode.
 * @param[in] len                    The data length of the sending message.
 * @param[in] p_data                 Point to the data of the sending message.
 *
 */
uint16_t simple_spm_label_client_msg_send(supermarket_label_client_t* p_spm_label_client, uint8_t company_opcode, uint16_t dst, uint16_t len, uint8_t *p_data);

/**
 * @brief Send simple supermarket-label client message(set/get/set_unreliable) to a address.
 *
 * @param[in] dst_address     The destination of message.
 * @param[in] company_opcode  The vendor specific opcode.
 * @param[in] len             The data length of the sending message.
 * @param[in] p_data          Point to the data of the sending message.
 *
 */
uint16_t simple_spm_label_client_msg_user_send(uint16_t dst, uint8_t company_opcode, uint16_t len, uint8_t *p_data);

#endif /* SIMPLE_SPM_LABEL_CLIENT_H__ */

