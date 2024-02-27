#ifndef LED_MATRIX_COMMON_H__
#define LED_MATRIX_COMMON_H__

#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "dbg_define.h"
#include "stdlib.h"
#include "grx_hal.h" 

/** Vendor specific company ID for Led Matrix model */
#define LED_MATRIX_COMPANY_ID    (0x04F7)

/** Led Matrix Server model ID. */
#define LED_MATRIX_SERVER_MODEL_ID (0x000A)

/** Led Matrix Client model ID. */
#define LED_MATRIX_CLIENT_MODEL_ID (0x000B)

/** Led Matrix Client msg len. */
#define LED_MATRIX_PIC_MSG_LEN (8)
/** Led Matrix Client msg len. */
#define LED_MATRIX_BAC_MSG_LEN (2)
/** Led Matrix Client msg len. */
#define LED_MATRIX_RSP_MSG_LEN (2)
/** Led Matrix Client msg len. */
#define LED_MATRIX_CPIC_MSG_LEN (136)
/** Led Matrix Client msg len. */
#define LED_MATRIX_FPIC_MSG_LEN (128)


/** Led Matrix opcodes. */
typedef enum
{
    OPCODE_FIRST = 0xC0,
    LED_MATRIX_OPCODE_PIC_SET = 0xC0,            /**< Led Matrix Picture Set. */
    LED_MATRIX_OPCODE_BAC_SET = 0xC1,            /**< Led Matrix Brightness and Chromaticity Set. */
    LED_MATRIX_OPCODE_STATUS  = 0xC2,            /**< Led Matrix Status. */
    LED_MATRIX_OPCODE_CPIC_SET = 0xC3,           /**< Led Matrix Colorful Picture Set. */
    LED_MATRIX_OPCODE_FPIC_SET = 0xC4,           /**< Led Matrix Full Picture Set. */
} led_matrix_opcode_t;


/** Message format for the led matrix picture message.
* | led bit map |
*/
typedef struct
{
    uint8_t msg[LED_MATRIX_PIC_MSG_LEN];    /**< msg to send. */
} led_matrix_pic_msg_t;

/** Message format for the led matrix brightness and chromaticity message.
* | chromaticity |
*/
typedef struct
{
    uint8_t msg[LED_MATRIX_BAC_MSG_LEN];    /**< msg to send. */
} led_matrix_bac_msg_t;


/** Message format for the led matrix color pic message.
* | bitmap | chromaticity |
*/
typedef struct
{
    uint8_t msg[LED_MATRIX_CPIC_MSG_LEN];    /**< msg to rsp. */
} led_matrix_cpic_msg_t;

/** Message format for the led matrix full pic message.
* | bitmap |
*/
typedef struct
{
    uint8_t msg[LED_MATRIX_FPIC_MSG_LEN];    /**< msg to rsp. */
} led_matrix_fpic_msg_t;


/** Message format for the led matrix rsp message.
* | server_id| opcode |
*/
typedef struct
{
    uint8_t msg[LED_MATRIX_RSP_MSG_LEN];    /**< msg to rsp. */
} led_matrix_rsp_msg_t;


typedef struct
{
    mesh_model_register_info_t register_info;
    mesh_lid_t                 model_lid;
    uint8_t                    current_msg;
    led_matrix_pic_msg_t       lm_pic_msg;
    led_matrix_bac_msg_t       lm_bac_msg;
    led_matrix_rsp_msg_t       lm_rsp_msg;
    led_matrix_cpic_msg_t      lm_cpic_msg;
    led_matrix_fpic_msg_t      lm_fpic_msg;
} lm_model_info_t;

#endif /* LED_MATRIX_COMMON_H__ */
