#include "user_app.h"
#include "app_log.h"
#include "mesh_common.h"
#include "mesh_model.h"
#include "user_model_client.h"

/*
 * GLOBLE VARIABLE DEFINITIONS
 *****************************************************************************************
 */
mesh_lid_t g_app_model_client_local_id = 0;

/*
 * LOCAL FUNCTION DEFINITIONS
 *****************************************************************************************
 */
static void app_model_client_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    if (APP_MODEL_OPCODE_SERVER_SEND_DATA == company_opcode)
    {
        APP_LOG_INFO("client rcv msg, model_lid = %d, src_addr = %d, msg_len = %d\n",
            p_model_msg->model_lid, p_model_msg->src, p_model_msg->msg_len);
    }
    else
    {
        APP_LOG_ERROR("rcv invalid opcode, opcode = 0x%x", company_opcode);
    }
}

static void app_model_client_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    APP_LOG_INFO("message sent, model_lid = %d, status = 0x%x", p_sent->model_lid, p_sent->status);
}

/*
 * LOCAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
static const uint16_t app_model_client_opcode_list[] =
{
    APP_MODEL_OPCODE_SERVER_SEND_DATA,
};

static const mesh_model_cb_t simple_on_off_client_msg_cb = {
    .cb_rx             = app_model_client_rx_cb,
    .cb_sent           = app_model_client_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t app_model_client_info =
{
    .model_id = MESH_MODEL_VENDOR(APP_MODEL_CLIENT_ID, APP_MODEL_COMPANY_ID),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)app_model_client_opcode_list,
    .num_opcodes = sizeof(app_model_client_opcode_list) / sizeof(uint16_t),
    .p_cb = &simple_on_off_client_msg_cb,
    .p_args = NULL,
};

/*
 * GLOBLE VARIABLE DEFINITIONS
 *****************************************************************************************
 */
uint16_t app_model_client_init(void)
{
    return (uint16_t)mesh_model_register(&app_model_client_info, &g_app_model_client_local_id);
}
