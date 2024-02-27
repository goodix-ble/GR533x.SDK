#ifndef TMALL_COMMON_H__
#define TMALL_COMMON_H__

#include <stdint.h>
#include "mesh_common.h"
#include "mesh_model.h"
#include "dbg_define.h"
#include "stdlib.h"
#include "grx_hal.h"

/** Vendor specific company ID for tmall model */
#define TMALL_COMPANY_ID    (0x01A8)

/** Tmall Server model ID. */
#define TMALL_SERVER_MODEL_ID (0x0000)


/** Tmall opcodes. */
typedef enum
{
    TMALL_OPCODE_ATTR_GET           = 0xD0,           /**< Tmall Attr Get. */
    TMALL_OPCODE_ATTR_SET           = 0xD1,           /**< Tmall Attr Set. */
    TMALL_OPCODE_ATTR_SET_UNACK     = 0xD2,           /**< Tmall Attr Set Unacknowledged. */
    TMALL_OPCODE_ATTR_STATUS        = 0xD3,           /**< Tmall Attr Status. */
    TMALL_OPCODE_ATTR_INDICATION    = 0xD4,           /**< Tmall Attr Indication. */
    TMALL_OPCODE_ATTR_CONFIRMATION  = 0xD5,           /**< Tmall Attr Confirmation. */
    TMALL_OPCODE_TRANSPARENT        = 0xCF,           /**< Tmall Attr Transparent msg. */
} tmall_opcode_t;

/** Message Struct for each Tmall message Attr.
*/
typedef struct
{
    uint16_t attr_type;         /**< attr type to be read. */
    uint16_t attr_param_len;    /**< attr param_len. */
    uint8_t attr_param[2];      /**< pointer to attr param. */
} tmall_attr_ind_t;

/** Message list for the Tmall message Attr.
*/
typedef struct
{
    tmall_attr_ind_t fan_attr[15];
} tmall_model_fan_attr_t;

typedef struct
{
    mesh_model_register_info_t register_info;
    mesh_lid_t                 model_lid;
    uint8_t                    current_msg;
    tmall_model_fan_attr_t     tmall_fan;
} tmall_model_info_t;

#endif /* TMALL_COMMON_H__ */
