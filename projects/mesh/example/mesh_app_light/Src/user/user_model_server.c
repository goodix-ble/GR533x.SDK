#include "user_app.h"
#include "app_log.h"
#include "mesh_common.h"
#include "mesh_model.h"
#include "user_model_server.h"
#include "board_SK.h"

/*
 * GLOBLE VARIABLE DEFINITIONS
 *****************************************************************************************
 */
mesh_lid_t g_app_model_server_local_id = 0;
uint32_t s_rcv_msg_count = 0;

/*
 * LOCAL FUNCTION DEFINITIONS
 *****************************************************************************************
 */
static void app_model_server_rx_cb(mesh_model_msg_ind_t *p_model_msg, void *p_args)
{
    uint16_t company_opcode = p_model_msg->opcode.company_opcode;

    if (APP_MODEL_OPCODE_CLIENT_SEND_DATA == company_opcode)
    {
        APP_LOG_INFO("server rcv msg, model_lid = %d, src_addr = %d, msg_len = %d\n",
            p_model_msg->model_lid, p_model_msg->src, p_model_msg->msg_len);

        s_rcv_msg_count++;
        APP_LOG_INFO("s_rcv_msg_count = %d", s_rcv_msg_count);

        if (p_model_msg->msg[0] == 0xAA)
        {
            switch (p_model_msg->msg[01])
            {
                case APP_CMD_CLOSE_LIGHT:
                {
                    APP_LOG_INFO("close light");
                    bsp_led_close(BSP_LED_NUM_0);
                    break;
                }

                case APP_CMD_OPEN_LIGHT:
                {
                    APP_LOG_INFO("open light");
                    bsp_led_open(BSP_LED_NUM_0);
                    break;
                }

                case APP_CMD_START_AUTO_SEND_MSG:
                {
                    APP_LOG_INFO("gateway start auto send msg");
                    s_rcv_msg_count = 0;
                    break;
                }

                case APP_CMD_STOP_AUTO_SEND_MSG:
                {
                    APP_LOG_INFO("gateway stop auto send msg");
                    s_rcv_msg_count = 0;
                    break;
                }

                case APP_CMD_SET_NET_TX_COUNT:
                {
                    APP_LOG_INFO("set net/relay tx count: %d", p_model_msg->msg[2]);
                    mesh_net_tx_param_set(p_model_msg->msg[2], 2);
                    mesh_relay_tx_param_set(p_model_msg->msg[2], 2);
                    break;
                }

                default:
                    break;
            }
        }
        else
        {
            APP_LOG_ERROR("first byte rcv err: 0x%x", p_model_msg->msg[0]);
        }

        #if (MESH_AUTO_PERFORMANCE_TEST)
        extern void app_restart_timer(void);
        app_restart_timer();
        #endif
    }
    else
    {
        APP_LOG_ERROR("rcv invalid opcode, opcode = 0x%x", company_opcode);
    }
}

static void app_model_server_sent_cb(mesh_model_msg_sent_ind_t *p_sent, void *p_args, void *p_buf)
{
    APP_LOG_INFO("message sent, model_lid = %d, status = 0x%x", p_sent->model_lid, p_sent->status);
}

/*
 * LOCAL VARIABLE DEFINITIONS
 *****************************************************************************************
 */
static const uint16_t app_model_server_opcode_list[] =
{
    APP_MODEL_OPCODE_CLIENT_SEND_DATA,
};

static const mesh_model_cb_t simple_on_off_server_msg_cb = {
    .cb_rx             = app_model_server_rx_cb,
    .cb_sent           = app_model_server_sent_cb,
    .cb_publish_period = NULL,
};

static mesh_model_register_info_t app_model_server_info =
{
    .model_id = MESH_MODEL_VENDOR(APP_MODEL_SERVER_ID, APP_MODEL_COMPANY_ID),
    .element_offset = 0,
    .publish = true,
    .p_opcodes = (uint16_t *)app_model_server_opcode_list,
    .num_opcodes = sizeof(app_model_server_opcode_list) / sizeof(uint16_t),
    .p_cb = &simple_on_off_server_msg_cb,
    .p_args = NULL,
};

/*
 * GLOBLE VARIABLE DEFINITIONS
 *****************************************************************************************
 */
uint16_t app_model_server_init(void)
{
    return (uint16_t)mesh_model_register(&app_model_server_info, &g_app_model_server_local_id);
}
