#ifndef LED_MATRIX_CLIENT_H__
#define LED_MATRIX_CLIENT_H__

#include "led_matrix_common.h"
#define LED_MATRIX_CLIENT_COUNT (16)

/**@brief Register led matrix client model, obtain the information of registered model.
 *
 * @return Result of register.
 */ 
uint16_t led_matrix_client_init(void);
void led_matrix_client_msg_send(uint8_t index, uint16_t opcode);
void led_matrix_client_msg_all_send(uint8_t opcode);
void led_matrix_client_serverice_send(uint32_t len, uint8_t* p_data);


#endif /* LED_MATRIX_CLIENT_H__ */

