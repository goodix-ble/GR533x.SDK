#include "user_app.h"
#include "app_log.h"
#include "board_SK.h"
#include "mesh_common.h"
#include "mesh_model.h"
#include "user_model_client.h"

uint8_t msg_data[29] = {0x00};
uint8_t g_send_data_len = 2;

extern uint32_t s_auto_send_msg_cnt;

void test_send_message(void)
{
    mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_VENDOR(APP_MODEL_OPCODE_CLIENT_SEND_DATA, APP_MODEL_COMPANY_ID);

    // build message
    mesh_model_send_info_t msg;
    msg.model_lid = g_app_model_client_local_id;
    msg.opcode = opcode;
    msg.tx_hdl = 0;
    msg.dst = 0xffff;
    msg.appkey_index = 0;
    msg_data[0] = 0xAA;
    msg_data[1] = (s_auto_send_msg_cnt % 2) ? APP_CMD_OPEN_LIGHT : APP_CMD_CLOSE_LIGHT;
    msg.p_data_send = msg_data;
    msg.data_send_len = g_send_data_len;
    // send message
    uint16_t status = mesh_model_msg_send(&msg);

    if (status != MESH_ERROR_NO_ERROR)
    {
        APP_LOG_INFO("send message err, status = 0x%x.", status);
    }
}

static bool check_data_valid(uint8_t *p_data, uint8_t data_len)
{
    // AA(token) + node_id + cmd_id + param data, cmd_id define as bellow:
    // aa + node id + 0x00: light off
    // aa + node id + 0x01: light on
    // aa + node id + 0x02: start auto send message, node_id must be 0xff
    // aa + node id + 0x03: stop auto send message, node_id must be 0xff
    // aa + node id + 0x04 + net tx count: set net/relay tx count, node_id must be 0xff
    // aa + node id + 0x05 + msg_len: set auto send message length, node_id must be 0xff
    bool valid_flag = false;

    if (data_len != 3 && data_len != 4)
    {
        APP_LOG_ERROR("data len err");
        return valid_flag;
    }

    if (p_data[0] != 0xAA)
    {
        APP_LOG_ERROR("first byte must be 0xAA");
        return valid_flag;
    }

    switch (p_data[2])
    {
        case APP_CMD_CLOSE_LIGHT:
        case APP_CMD_OPEN_LIGHT:
        {
            if (data_len != 3)
            {
                APP_LOG_ERROR("set close/open light err");
            }
            else
            {
                valid_flag = true;
            }
            break;
        }

        case APP_CMD_START_AUTO_SEND_MSG:
        case APP_CMD_STOP_AUTO_SEND_MSG:
        {
            if (data_len != 3 || p_data[1] != 0xff)
            {
                APP_LOG_ERROR("set start/stop auto send msg err");
                break;
            }
            else
            {
                valid_flag = true;
            }
            break;
        }
        
        case APP_CMD_SET_NET_TX_COUNT:
        {
            if ((data_len != 4) || (p_data[1] != 0xff) || (p_data[3] == 0 || p_data[3] > 8))
            {
                APP_LOG_ERROR("set net tx count err");
            }
            else
            {
                valid_flag = true;
            }
            break;
        }

        case APP_CMD_SET_AUTO_SEND_MSG_LEN:
        {
            if ((data_len != 4) || (p_data[1] != 0xff) || (p_data[3] < 5 || p_data[3] > 32))
            {
                APP_LOG_ERROR("set auto send msg len err");
            }
            else
            {
                valid_flag = true;
            }
            break;
        }

        default:
        {
            APP_LOG_ERROR("invalid cmd id");
            break;
        }
    }

    return valid_flag;
}

void handle_rcv_temp_data(uint8_t *p_data, uint8_t data_len)
{
    if (check_data_valid(p_data, data_len))
    {
        if (p_data[2] != APP_CMD_SET_AUTO_SEND_MSG_LEN)
        {
            s_auto_send_msg_cnt++;
            APP_LOG_INFO("send_msg_cnt = %d\n", s_auto_send_msg_cnt);
        }

        mesh_access_opcode_t opcode = MESH_ACCESS_OPCODE_VENDOR(APP_MODEL_OPCODE_CLIENT_SEND_DATA, APP_MODEL_COMPANY_ID);

        // build message
        mesh_model_send_info_t msg;
        msg.model_lid = g_app_model_client_local_id;
        msg.opcode = opcode;
        msg.tx_hdl = 0;
        msg.appkey_index = 0;
        msg.p_data_send = msg_data;
        msg.data_send_len = 0;
        // set dest addr
        if (p_data[1] == 0xFF)
        {
            msg.dst = (0x00FF << 8) | p_data[1];
        }
        else
        {
            msg.dst = p_data[1];
        }

        switch (p_data[2])
        {
            case APP_CMD_CLOSE_LIGHT:
            case APP_CMD_OPEN_LIGHT:
            {
                msg_data[0] = 0xaa;
                msg_data[1] = p_data[2];
                msg.data_send_len = 2;
                break;
            }

            case APP_CMD_START_AUTO_SEND_MSG:
            {
                msg_data[0] = 0xaa;
                msg_data[1] = p_data[2];
                msg.data_send_len = 2;
                extern void app_start_auto_send_msg(void);
                app_start_auto_send_msg();
                break;
            }

            case APP_CMD_STOP_AUTO_SEND_MSG:
            {
                msg_data[0] = 0xaa;
                msg_data[1] = p_data[2];
                msg.data_send_len = 2;
                extern void app_stop_auto_send_msg(void);
                app_stop_auto_send_msg();
                break;
            }

            case APP_CMD_SET_NET_TX_COUNT:
            {
                msg_data[0] = 0xaa;
                msg_data[1] = p_data[2];
                msg_data[2] = p_data[3];
                msg.data_send_len = 3;
                APP_LOG_INFO("set net tx count: %d", p_data[3]);
                mesh_net_tx_param_set(p_data[3], 2);
                break;
            }

            case APP_CMD_SET_AUTO_SEND_MSG_LEN:
            {
                APP_LOG_INFO("set auto send msg len: %d", p_data[3]);
                extern uint8_t g_send_data_len;
                g_send_data_len = p_data[3] - 3;
                break;
            }

            default:
                break;
        }

        if (p_data[2] != APP_CMD_SET_AUTO_SEND_MSG_LEN)
        {
            // send message
            uint16_t status = mesh_model_msg_send(&msg);

            if (status != MESH_ERROR_NO_ERROR)
            {
                APP_LOG_INFO("send message err, status = 0x%x.", status);
            }
        }
    }
}

void mesh_uart_cmd_handler(uint8_t *buf, uint8_t len)
{
    if (buf[0] == 0xAA)
    {
        handle_rcv_temp_data(buf, len);
    }
    else if (buf[0] == 0xbb)
    {
        if (buf[1] == 0x00 && buf[2] == 2)
        {
            APP_LOG_INFO("update unicast addr");
            uint16_t unicast_addr = buf[4] << 8 | buf[3];
            mesh_auto_prov_info_t prov_info_upd;
            prov_info_upd.unicast_addr = unicast_addr;
            mesh_prov_info_update(&prov_info_upd, MESH_PROV_INFO_UPD_TYPE_ADDR);
        }
        else if (buf[1] == 0x01 && buf[2] == 16)
        {
            APP_LOG_INFO("update dev key");
            mesh_auto_prov_info_t prov_info_upd;
            memcpy(prov_info_upd.dev_key, &(buf[3]), 16);
            mesh_prov_info_update(&prov_info_upd, MESH_PROV_INFO_UPD_TYPE_DEV_KEY);
        }
        else if (buf[1] == 0x02 && buf[2] == 16)
        {
            APP_LOG_INFO("update net key");
            mesh_auto_prov_info_t prov_info_upd;
            memcpy(prov_info_upd.net_key, &(buf[3]), 16);
            mesh_prov_info_update(&prov_info_upd, MESH_PROV_INFO_UPD_TYPE_NET_KEY);
        }
        else if (buf[1] == 0x03 && buf[2] == 16)
        {
            APP_LOG_INFO("update app key");
            mesh_auto_prov_info_t prov_info_upd;
            memcpy(prov_info_upd.app_key, &(buf[3]), 16);
            mesh_prov_info_update(&prov_info_upd, MESH_PROV_INFO_UPD_TYPE_APP_KEY);
        }
    }
}
