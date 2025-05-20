#include "user_app.h"
#include "app_log.h"
#include "board_SK.h"
#include "mesh_common.h"

void mesh_uart_cmd_handler(uint8_t *buf, uint8_t len)
{
    if (buf[0] == 0xbb)
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
