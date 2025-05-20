#include "custom_config.h"
#include "ble.h"
#include "ble_id.h"
#include "ble_msg.h"
#include "ble_event.h"
#include "patch_tab.h"

extern void adv_func_init(void);
extern void scan_func_init(void);
extern void master_func_init(void);
extern void slave_func_init(void);
extern void legacy_pair_func_init(void);
extern void sc_pair_func_init(void);
extern void coc_func_init(void);
extern void gatts_func_init(void);
extern void gattc_func_init(void);
extern void conn_aoa_aod_func_init(void);
extern void connless_aoa_aod_func_init(void);
extern void ranging_func_init(void);
extern void mesh_func_init(void);
extern void sniffer_func_init(void);

extern void ble_common_env_init(void);
extern void ble_mul_link_env_init(void);
extern void ble_con_env_init(void);
extern void ble_car_key_env_init(void);
extern void ble_bt_bredr_env_init(void);
extern void ble_test_evn_init(void);
extern void ble_test_private_cmd_init(void);
extern void ble_adv_env_init(void);
extern void ble_scan_env_init(void);
extern void ble_gatts_env_init(void);

extern void reg_msg_patch_tab(msg_tab_item_t *msg_tab, uint16_t msg_cnt);
extern void reg_gapm_hci_evt_patch_tab(gapm_hci_evt_tab_item_t *gapm_hci_evt_tab, uint16_t gapm_hci_evt_cnt);
extern void reg_llm_hci_cmd_patch_tab(llm_hci_cmd_tab_item_t *hci_cmd_tab, uint16_t hci_cmd_cnt);

extern void ble_stack_enable(ble_evt_handler_t evt_handler, stack_heaps_table_t *p_heaps_table);
extern void ble_stack_controller_enable(stack_heaps_table_t *p_heaps_table);

void ble_sdk_patch_env_init(void)
{
    // register the msg handler for patch
    uint16_t msg_cnt = sizeof(msg_tab) / sizeof(msg_tab_item_t);
    reg_msg_patch_tab(msg_tab, msg_cnt);

    // register the llm hci cmd handler for patch
    uint16_t llm_hci_cmd_cnt = sizeof(llm_hci_cmd_tab) / sizeof(llm_hci_cmd_tab_item_t);
    reg_llm_hci_cmd_patch_tab(llm_hci_cmd_tab, llm_hci_cmd_cnt);

    // register the gapm hci evt handler for patch
    uint16_t gapm_hci_evt_cnt = sizeof(gapm_hci_evt_tab) / sizeof(gapm_hci_evt_tab_item_t);
    reg_gapm_hci_evt_patch_tab(gapm_hci_evt_tab, gapm_hci_evt_cnt);

    ble_common_env_init();
}

/**************************************************************************************
 **************                       TASK GAPM TAB                    ****************
 **************************************************************************************/

extern gapm_hci_evt_handler_tab_info_t gapm_hci_cmd_handler_tab_info[3];

/// The message handlers for HCI command complete events
static const struct gapm_hci_evt_handler gapm_hci_cmd_cmp_event_handler_tab[] =
{
    /* Advertising procedure (startup part) */
    { HCI_LE_SET_EXT_ADV_EN_CMD_OPCODE,                (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_adv_handler },
    { HCI_LE_SET_EXT_ADV_PARAM_CMD_OPCODE,             (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_adv_handler },
    { HCI_LE_SET_EXT_ADV_DATA_CMD_OPCODE,              (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_adv_handler },
    /* Advertising procedure */
    { HCI_LE_SET_EXT_SCAN_RSP_DATA_CMD_OPCODE,         (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_adv_handler },
    { HCI_LE_SET_PER_ADV_PARAM_CMD_OPCODE,             (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_adv_handler },
    { HCI_LE_SET_PER_ADV_DATA_CMD_OPCODE,              (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_adv_handler },
    { HCI_LE_SET_PER_ADV_EN_CMD_OPCODE,                (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_adv_handler },
    { HCI_LE_RMV_ADV_SET_CMD_OPCODE,                   (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_adv_handler },

    { HCI_RESET_CMD_OPCODE,                            (gapm_hci_evt_hdl_func_t) hci_basic_cmd_cmp_evt_cfg_handler },
    { HCI_SET_EVT_MASK_CMD_OPCODE,                     (gapm_hci_evt_hdl_func_t) hci_basic_cmd_cmp_evt_cfg_handler },
    { HCI_LE_SET_EVT_MASK_CMD_OPCODE,                  (gapm_hci_evt_hdl_func_t) hci_basic_cmd_cmp_evt_cfg_handler },
    { HCI_LE_SET_HOST_CH_CLASS_CMD_OPCODE,             (gapm_hci_evt_hdl_func_t) hci_basic_cmd_cmp_evt_cfg_handler },

    { HCI_LE_WR_SUGGTED_DFT_DATA_LEN_CMD_OPCODE,       (gapm_hci_evt_hdl_func_t) hci_basic_cmd_cmp_evt_cfg_handler },
    { HCI_LE_WR_RF_PATH_COMP_CMD_OPCODE,               (gapm_hci_evt_hdl_func_t) hci_basic_cmd_cmp_evt_cfg_handler },
    { HCI_LE_SET_DFT_PHY_CMD_OPCODE,                   (gapm_hci_evt_hdl_func_t) hci_basic_cmd_cmp_evt_cfg_handler },

    /* White list management */
    { HCI_LE_ADD_DEV_TO_WLST_CMD_OPCODE,               (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_list_handler },
    { HCI_LE_CLEAR_WLST_CMD_OPCODE,                    (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_list_handler },

    /* Scan procedure */
    { HCI_LE_SET_EXT_SCAN_PARAM_CMD_OPCODE,            (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_scan_handler },
    { HCI_LE_SET_EXT_SCAN_EN_CMD_OPCODE,               (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_scan_handler },

    /* Connection procedure */
    { HCI_LE_CREATE_CON_CANCEL_CMD_OPCODE,             (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_init_handler },

    /* Address Management */
    { HCI_LE_SET_RAND_ADDR_CMD_OPCODE,                 (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_addr_handler },
    { HCI_LE_SET_ADV_SET_RAND_ADDR_CMD_OPCODE,         (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_addr_handler },

    /* Resolving List Management */
    { HCI_LE_SET_ADDR_RESOL_EN_CMD_OPCODE,             (gapm_hci_evt_hdl_func_t) hci_basic_cmd_cmp_evt_rl_cfg_handler },
    { HCI_LE_SET_RSLV_PRIV_ADDR_TO_CMD_OPCODE,         (gapm_hci_evt_hdl_func_t) hci_basic_cmd_cmp_evt_rl_cfg_handler },
    { HCI_LE_ADD_DEV_TO_RSLV_LIST_CMD_OPCODE,          (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_list_handler },
    { HCI_LE_CLEAR_RSLV_LIST_CMD_OPCODE,               (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_list_handler },
    { HCI_LE_SET_PRIV_MODE_CMD_OPCODE,                 (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_list_handler },

    /* Periodic advertiser list management */
    { HCI_LE_ADD_DEV_TO_PER_ADV_LIST_CMD_OPCODE,       (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_list_handler },
    { HCI_LE_CLEAR_PER_ADV_LIST_CMD_OPCODE,            (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_list_handler },
    //{ HCI_LE_RD_PER_ADV_LIST_SIZE_CMD_OPCODE,          (gapm_hci_evt_hdl_func_t) hci_le_rd_pal_size_cmd_cmp_evt_handler },

    /* Periodic synchronization procedure */
    { HCI_LE_PER_ADV_CREATE_SYNC_CANCEL_CMD_OPCODE,    (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_per_sync_handler },
    { HCI_LE_PER_ADV_TERM_SYNC_CMD_OPCODE,             (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_per_sync_handler },
    { HCI_LE_SET_PER_ADV_REC_EN_CMD_OPCODE,            (gapm_hci_evt_hdl_func_t) hci_le_set_per_adv_rec_en_cmp_evt_handler },

    { HCI_LE_SET_CONLESS_CTE_TX_PARAM_CMD_OPCODE,      (gapm_hci_evt_hdl_func_t) hci_le_set_conless_cte_tx_param_cmd_cmp_handler },
    { HCI_LE_SET_CONLESS_CTE_TX_EN_CMD_OPCODE,         (gapm_hci_evt_hdl_func_t) hci_le_set_conless_cte_tx_en_cmd_cmp_handler },
    { HCI_LE_SET_CONLESS_IQ_SAMPL_EN_CMD_OPCODE,       (gapm_hci_evt_hdl_func_t) hci_le_set_conless_iq_sampl_en_cmd_cmp_evt_list_handler },
};

/// The message handlers for HCI status event
static const struct gapm_hci_evt_handler  gapm_hci_cmd_stat_event_handler_tab[] =
{
    { HCI_LE_EXT_CREATE_CON_CMD_OPCODE,          (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_init_handler },
    { HCI_LE_PER_ADV_CREATE_SYNC_CMD_OPCODE,     (gapm_hci_evt_hdl_func_t) hci_le_cmd_cmp_evt_per_sync_handler },
    { HCI_LE_GEN_DHKEY_V2_CMD_OPCODE,            (gapm_hci_evt_hdl_func_t) hci_le_gen_dhkey_v2_stat_evt_handler },

};

/// The message handlers for HCI LE events
static const struct gapm_hci_evt_handler gapm_hci_le_event_handler_tab[] =
{
    /* Scan procedure */
    { HCI_LE_EXT_ADV_REPORT_EVT_SUBCODE,            (gapm_hci_evt_hdl_func_t) hci_le_ext_adv_report_evt_handler },
    { HCI_LE_SCAN_TIMEOUT_EVT_SUBCODE,              (gapm_hci_evt_hdl_func_t) hci_le_scan_timeout_evt_handler },

    #if (CFG_CONNLESS_AOA_AOD_SUPPORT)
    /* Periodic synchronization procedure */
    { HCI_LE_PER_ADV_SYNC_EST_EVT_SUBCODE,          (gapm_hci_evt_hdl_func_t) hci_le_per_adv_sync_est_evt_handler },
    { HCI_LE_PER_ADV_REPORT_EVT_SUBCODE,            (gapm_hci_evt_hdl_func_t) hci_le_per_adv_report_evt_handler },
    { HCI_LE_PER_ADV_SYNC_LOST_EVT_SUBCODE,         (gapm_hci_evt_hdl_func_t) hci_le_per_adv_sync_lost_evt_handler },
    { HCI_LE_CONLESS_IQ_REPORT_EVT_SUBCODE,         (gapm_hci_evt_hdl_func_t) hci_le_conless_iq_report_evt_handler },
    #endif

    { HCI_LE_ENH_CON_CMP_EVT_SUBCODE,               (gapm_hci_evt_hdl_func_t) hci_le_enh_con_cmp_evt_handler },

    #if (CFG_SC_PAIR_SUPPORT || CFG_MESH_SUPPORT)
    { HCI_LE_RD_LOC_P256_PUB_KEY_CMP_EVT_SUBCODE,   (gapm_hci_evt_hdl_func_t) hci_le_rd_local_p256_public_key_cmp_evt_handler },
    { HCI_LE_GEN_DHKEY_CMP_EVT_SUBCODE,             (gapm_hci_evt_hdl_func_t) hci_le_gen_dhkey_cmp_evt_handler },
    #endif

    /* Advertising procedure */
    { HCI_LE_ADV_SET_TERMINATED_EVT_SUBCODE,        (gapm_hci_evt_hdl_func_t) hci_le_adv_set_term_evt_handler },
};

/// The default message handlers
static const struct ke_msg_handler gapm_msg_handler_tab[] =
{
    // Note: all messages must be sorted in ID ascending order

    { GAPM_CMP_EVT,                           (ke_msg_func_t) gapm_cmp_evt_handler },
    /* Reset command */
    { GAPM_RESET_CMD,                         (ke_msg_func_t) gapm_reset_cmd_handler },
    /* Device get configuration */
    { GAPM_GET_DEV_INFO_CMD ,                 (ke_msg_func_t) gapm_get_dev_info_cmd_handler },
    /* Device set configuration */
    { GAPM_SET_DEV_CONFIG_CMD,                (ke_msg_func_t) gapm_set_dev_config_cmd_handler },
    { GAPM_DEV_BDADDR_IND,                    (ke_msg_func_t) gapm_dev_bdaddr_ind_handler },
    /* Address resolution */
    { GAPM_RESOLV_ADDR_CMD,                   (ke_msg_func_t) gapm_resolv_addr_cmd_handler },
    { GAPM_GEN_RAND_ADDR_CMD,                 (ke_msg_func_t) gapm_gen_rand_addr_cmd_handler },
    /* Profile Management */
    { GAPM_PROFILE_TASK_ADD_CMD,              (ke_msg_func_t) gapm_profile_task_add_cmd_handler },

    #if (CFG_COC_SUPPORT)
    /* LE Credit Based Channel Management */
    { GAPM_LEPSM_REGISTER_CMD,                (ke_msg_func_t) gapm_lepsm_register_cmd_handler },
    { GAPM_LEPSM_UNREGISTER_CMD,              (ke_msg_func_t) gapm_lepsm_unregister_cmd_handler },
    #endif

    #if (CFG_SC_PAIR_SUPPORT || CFG_MESH_SUPPORT)
    /* Address resolution */
    { GAPM_GEN_DH_KEY_CMD,                    (ke_msg_func_t) gapm_gen_dh_key_cmd_handler },
    { GAPM_GET_PUB_KEY_CMD,                   (ke_msg_func_t) gapm_get_pub_key_cmd_handler },
    #endif

    /* List Management */
    { GAPM_LIST_SET_CMD,                      (ke_msg_func_t) gapm_list_set_cmd_handler },
    /* Extended Air Operations */
    { GAPM_ACTIVITY_CREATE_CMD,               (ke_msg_func_t) gapm_activity_create_cmd_handler },
    { GAPM_ACTIVITY_START_CMD,                (ke_msg_func_t) gapm_activity_start_cmd_handler },
    { GAPM_ACTIVITY_STOP_CMD,                 (ke_msg_func_t) gapm_activity_stop_cmd_handler },
    { GAPM_ACTIVITY_DELETE_CMD,               (ke_msg_func_t) gapm_activity_delete_cmd_handler },
    { GAPM_SET_ADV_DATA_CMD,                  (ke_msg_func_t) gapm_set_adv_data_cmd_handler },

    #if (CFG_CONNLESS_AOA_AOD_SUPPORT)
    { GAPM_PER_ADV_REPORT_CTRL_CMD,           (ke_msg_func_t) gapm_per_adv_report_ctrl_cmd_handler },
    { GAPM_PER_SYNC_IQ_SAMPLING_CTRL_CMD,     (ke_msg_func_t) gapm_per_sync_iq_sampling_ctrl_cmd_handler },
    /* Extended Air Operations */
    { GAPM_PER_ADV_CTE_TX_CTL_CMD,            (ke_msg_func_t) gapm_per_adv_cte_tx_ctl_cmd_handler },
    { GAPM_PER_ADV_CTE_TX_PARAM_SET_CMD,      (ke_msg_func_t) gapm_per_adv_cte_tx_param_set_handler },
    #endif

    { GAPM_UNKNOWN_TASK_MSG,                  (ke_msg_func_t) gapm_unknown_task_msg_handler },
    /* Address Management (Internal) */
    { GAPM_ADDR_RENEW_TO_IND,                 (ke_msg_func_t) gapm_addr_renew_to_ind_handler },
    { GAPM_AUTO_CONN_TO_IND,                  (ke_msg_func_t) gapm_auto_conn_to_ind_handler },
    { GAPM_ADDR_RENEW_CMD,                    (ke_msg_func_t) gapm_addr_renew_cmd_handler },
    { GAPM_PUBLIC_ADDR_SET_CMD,               (ke_msg_func_t) gapm_public_addr_set_cmd_handler },
    { GAPM_SET_GDX_RANGING_PARAM_CMD,         (ke_msg_func_t) gapm_set_gdx_ranging_param_cmd_handler },
    { GAPC_CMP_EVT,                           (ke_msg_func_t) gapc_cmp_evt_handler },
    /* HCI management */
    { HCI_CMD_CMP_EVENT,                      (ke_msg_func_t) gapm_hci_handler },
    { HCI_CMD_STAT_EVENT,                     (ke_msg_func_t) gapm_hci_handler },
    { HCI_LE_EVENT,                           (ke_msg_func_t) gapm_hci_handler },
    { KE_MSG_DEFAULT_HANDLER,                 (ke_msg_func_t) gapm_default_msg_handler },
};

/**************************************************************************************
 **************                       TASK GAPC TAB                    ****************
 **************************************************************************************/

extern hci_cmd_handler_tab_info_t hci_cmd_handler_tab_info[4];

/// The message handlers for HCI command complete events
static const struct ke_msg_handler hci_cmd_cmp_event_handler_tab[] =
{
    { HCI_RD_RSSI_CMD_OPCODE,                        (ke_msg_func_t) hci_rd_rssi_cmd_cmp_evt_handler },
    { HCI_LE_RD_CHNL_MAP_CMD_OPCODE,                 (ke_msg_func_t) hci_rd_chnl_map_cmd_cmp_evt_handler },
    { HCI_LE_SET_DATA_LEN_CMD_OPCODE,                (ke_msg_func_t) hci_le_set_data_len_cmd_cmp_evt_handler },
    { HCI_LE_RD_PHY_CMD_OPCODE,                      (ke_msg_func_t) hci_le_rd_phy_cmd_cmp_evt_handler },

    #if (CFG_CONN_AOA_AOD_SUPPORT)
    { HCI_LE_SET_CON_CTE_TX_PARAM_CMD_OPCODE,        (ke_msg_func_t) hci_cte_cmd_cmp_evt_handler },
    { HCI_LE_SET_CON_CTE_RX_PARAM_CMD_OPCODE,        (ke_msg_func_t) hci_cte_cmd_cmp_evt_handler },
    { HCI_LE_CON_CTE_REQ_EN_CMD_OPCODE,              (ke_msg_func_t) hci_cte_cmd_cmp_evt_handler },
    { HCI_LE_CON_CTE_RSP_EN_CMD_OPCODE,              (ke_msg_func_t) hci_cte_cmd_cmp_evt_handler },
    #endif

    #if (CFG_RANGING_SUPPORT)
    { HCI_LE_START_RANGING_CMD_OPCODE,               (ke_msg_func_t) hci_cte_cmd_cmp_evt_handler },
    #endif
};

/// The message handlers for HCI LE events
static const struct ke_msg_handler hci_le_event_handler_tab[] =
{
    { HCI_LE_RD_REM_FEATS_CMP_EVT_SUBCODE,           (ke_msg_func_t) hci_le_rd_rem_feats_cmp_evt_handler },
    { HCI_LE_CON_UPDATE_CMP_EVT_SUBCODE,             (ke_msg_func_t) hci_le_con_update_cmp_evt_handler },
    { HCI_LE_REM_CON_PARAM_REQ_EVT_SUBCODE,          (ke_msg_func_t) hci_le_rem_con_param_req_evt_handler },
    { HCI_LE_DATA_LEN_CHG_EVT_SUBCODE,               (ke_msg_func_t) hci_le_data_len_chg_evt_handler },
    { HCI_LE_PHY_UPD_CMP_EVT_SUBCODE,                (ke_msg_func_t) hci_le_phy_upd_cmp_evt_handler },
    { HCI_LE_CH_SEL_ALGO_EVT_SUBCODE,                (ke_msg_func_t) hci_le_ch_sel_algo_evt_handler },
    { HCI_LE_LTK_REQUEST_EVT_SUBCODE,                (ke_msg_func_t) hci_le_ltk_request_evt_handler },

    #if (CFG_CONN_AOA_AOD_SUPPORT)
    { HCI_LE_CON_IQ_REPORT_EVT_SUBCODE,              (ke_msg_func_t) hci_le_con_iq_report_evt_handler },
    #endif

    #if (CFG_RANGING_SUPPORT)
    { HCI_LE_RANGING_IND_EVT_SUBCODE,                (ke_msg_func_t) hci_le_ranging_ind_evt_handler },
    { HCI_LE_RANGING_SAMPLE_REPORT_EVT_SUBCODE,      (ke_msg_func_t) hci_le_ranging_sample_report_evt_handler },
    { HCI_LE_RANGING_CMP_EVT_SUBCODE,                (ke_msg_func_t) hci_le_ranging_cmp_evt_handler },
    #endif
};

/// The default message handlers
static const struct ke_msg_handler gapc_msg_handler_tab[] =
{
    // Note: all messages must be sorted in ID ascending order

    { L2CC_CMP_EVT,                                (ke_msg_func_t) gapc_l2cc_cmp_evt_handler               },
    { L2CC_PDU_RECV_IND,                           (ke_msg_func_t) gapc_l2cc_pdu_recv_ind_handler          },

    /* Generic Access DB Management */
    { GATTC_READ_REQ_IND,                          (ke_msg_func_t) gapc_gattc_read_req_ind_handler         },
    { GATTC_WRITE_REQ_IND,                         (ke_msg_func_t) gapc_gattc_write_req_ind_handler        },
    { GATTC_ATT_INFO_REQ_IND,                      (ke_msg_func_t) gapc_gattc_att_info_req_ind_handler     },
    /* Generic Access DB Management */
    { GAPC_GET_DEV_INFO_CFM,                       (ke_msg_func_t) gapc_get_dev_info_cfm_handler           },
    { GAPC_SET_DEV_INFO_CFM,                       (ke_msg_func_t) gapc_set_dev_info_cfm_handler           },

    { GAPM_CMP_EVT,                                (ke_msg_func_t) gapc_smp_gapm_cmp_evt_handler           },

    #if (CFG_SC_PAIR_SUPPORT)
    { GAPM_GEN_DH_KEY_IND,                         (ke_msg_func_t) gapc_gen_dh_key_ind_handler             },
    { GAPM_PUB_KEY_IND,                            (ke_msg_func_t) gapm_smpc_pub_key_ind_handler           },
    #endif

    /* Set Bonding information */
    { GAPC_CONNECTION_CFM,                         (ke_msg_func_t) gapc_connection_cfm_handler             },

    /* Link management command */
    { GAPC_DISCONNECT_CMD,                         (ke_msg_func_t) gapc_disconnect_cmd_handler             },

    /* Peer device info */
    { GAPC_GET_INFO_CMD,                           (ke_msg_func_t) gapc_get_info_cmd_handler               },

    // Update connection parameters
    { GAPC_PARAM_UPDATE_CMD,                       (ke_msg_func_t) gapc_param_update_cmd_handler           },
    { GAPC_PARAM_UPDATE_CFM,                       (ke_msg_func_t) gapc_param_update_cfm_handler           },
    // Bonding procedure
    { GAPC_BOND_CMD,                               (ke_msg_func_t) gapc_bond_cmd_handler                   },
    { GAPC_BOND_CFM,                               (ke_msg_func_t) gapc_bond_cfm_handler                   },

    // Encryption procedure
    { GAPC_ENCRYPT_CMD,                            (ke_msg_func_t) gapc_encrypt_cmd_handler                },
    { GAPC_ENCRYPT_CFM,                            (ke_msg_func_t) gapc_encrypt_cfm_handler                },
    // Security Request procedure
    { GAPC_SECURITY_CMD,                           (ke_msg_func_t) gapc_security_cmd_handler               },

    // LE Data Length Extension
    { GAPC_SET_LE_PKT_SIZE_CMD,                    (ke_msg_func_t) gapc_set_le_pkt_size_handler            },

    // LE Phy configuration
    { GAPC_SET_PHY_CMD,                            (ke_msg_func_t) gapc_set_phy_cmd_handler                },

    #if (CFG_CONN_AOA_AOD_SUPPORT)
    // Constant Tone Extension
    { GAPC_CTE_TX_CFG_CMD,                         (ke_msg_func_t) gapc_cte_tx_cfg_cmd_handler             },
    { GAPC_CTE_RX_CFG_CMD,                         (ke_msg_func_t) gapc_cte_rx_cfg_cmd_handler             },
    { GAPC_CTE_REQ_CTRL_CMD,                       (ke_msg_func_t) gapc_cte_req_ctrl_cmd_handler           },
    { GAPC_CTE_RSP_CTRL_CMD,                       (ke_msg_func_t) gapc_cte_rsp_ctrl_cmd_handler           },
    #endif

    #if (CFG_RANGING_SUPPORT)
    { GAPC_RANGING_START_CMD,                      (ke_msg_func_t) gapc_ranging_start_cmd_handler          },
    #endif

    { GAPC_PARAM_UPDATE_TO_IND,                    (ke_msg_func_t) gapc_update_conn_param_to_ind_handler   },

    // Pairing timers handler
    { GAPC_SMP_TIMEOUT_TIMER_IND,                  (ke_msg_func_t) gapc_smp_timeout_timer_ind_handler      },
    { GAPC_SMP_REP_ATTEMPTS_TIMER_IND,             (ke_msg_func_t) gapc_smp_rep_attempts_timer_handler     },

    { HCI_CMD_CMP_EVENT,                           (ke_msg_func_t) gapc_hci_handler                        },
    { HCI_CMD_STAT_EVENT,                          (ke_msg_func_t) gapc_hci_handler                        },
    { HCI_EVENT,                                   (ke_msg_func_t) gapc_hci_handler                        },
    { HCI_LE_EVENT,                                (ke_msg_func_t) gapc_hci_handler                        },

    { KE_MSG_DEFAULT_HANDLER,                      (ke_msg_func_t) gapc_default_msg_handler                },
};

/**************************************************************************************
 **************                       TASK GATTC TAB                   ****************
 **************************************************************************************/
static const struct ke_msg_handler gattc_msg_handler_tab[] =
{
    // Note: all messages must be sorted in ID ascending order
    { L2CC_CMP_EVT,                  (ke_msg_func_t) gattc_l2cc_cmp_evt_handler },
    { L2CC_PDU_RECV_IND,             (ke_msg_func_t) gattc_l2cc_pdu_recv_ind_handler },

    #if (CFG_GATTC_SUPPORT)
    { GATTC_CMP_EVT,                 (ke_msg_func_t) gattc_cmp_evt_handler },
    { GATTC_EXC_MTU_CMD,             (ke_msg_func_t) gattc_exc_mtu_cmd_handler },
    { GATTC_DISC_CMD,                (ke_msg_func_t) gattc_disc_cmd_handler },
    { GATTC_DISC_SVC_IND,            (ke_msg_func_t) gattc_disc_svc_ind_handler },
    { GATTC_DISC_SVC_INCL_IND,       (ke_msg_func_t) gattc_disc_svc_incl_ind_handler },
    { GATTC_DISC_CHAR_IND,           (ke_msg_func_t) gattc_disc_char_ind_handler },
    { GATTC_DISC_CHAR_DESC_IND,      (ke_msg_func_t) gattc_disc_char_desc_ind_handler },
    { GATTC_SDP_SVC_DISC_CMD,        (ke_msg_func_t) gattc_sdp_svc_disc_cmd_handler },
    { GATTC_CLIENT_RTX_IND,          (ke_msg_func_t) gattc_timeout_handler },
    { GATTC_READ_CMD,                (ke_msg_func_t) gattc_read_cmd_handler },
    { GATTC_WRITE_CMD,               (ke_msg_func_t) gattc_write_cmd_handler },
    { GATTC_EXECUTE_WRITE_CMD,       (ke_msg_func_t) gattc_execute_write_cmd_handler },
    { GATTC_EVENT_CFM,               (ke_msg_func_t) gattc_event_cfm_handler },
    { GATTC_REG_TO_PEER_EVT_CMD,     (ke_msg_func_t) gattc_reg_to_peer_evt_cmd_handler },
    #endif

    #if (CFG_GATTS_SUPPORT)
    { GATTC_SEND_EVT_CMD,            (ke_msg_func_t) gattc_send_evt_cmd_handler },
    { GATTC_SEND_SVC_CHANGED_CMD,    (ke_msg_func_t) gattc_send_svc_changed_cmd_handler },
    { GATTC_READ_REQ_IND,            (ke_msg_func_t) gattc_read_req_ind_handler },
    { GATTC_READ_CFM,                (ke_msg_func_t) gattc_read_cfm_handler },
    { GATTC_WRITE_REQ_IND,           (ke_msg_func_t) gattc_write_req_ind_handler },
    { GATTC_WRITE_CFM,               (ke_msg_func_t) gattc_write_cfm_handler },
    { GATTC_ATT_INFO_REQ_IND,        (ke_msg_func_t) gattc_att_info_req_ind_handler },
    { GATTC_ATT_INFO_CFM,            (ke_msg_func_t) gattc_att_info_cfm_handler },
    { GATTC_SERVER_RTX_IND,          (ke_msg_func_t) gattc_timeout_handler},
    #endif

    { KE_MSG_DEFAULT_HANDLER,        (ke_msg_func_t) gattc_default_msg_handler },
};

/**************************************************************************************
 **************                       TASK GATTC TAB                   ****************
 **************************************************************************************/
static const struct ke_msg_handler l2cc_msg_handler_tab[] =
{
    #if (CFG_COC_SUPPORT)
    { L2CC_LECB_CONNECT_CMD,            (ke_msg_func_t) l2cc_lecb_connect_cmd_handler },
    { L2CC_LECB_CONNECT_CFM,            (ke_msg_func_t) l2cc_lecb_connect_cfm_handler },
    { L2CC_LECB_DISCONNECT_CMD,         (ke_msg_func_t) l2cc_lecb_disconnect_cmd_handler },
    { L2CC_LECB_ADD_CMD,                (ke_msg_func_t) l2cc_lecb_add_cmd_handler },
    { L2CC_LECB_SDU_SEND_CMD,           (ke_msg_func_t) l2cc_lecb_sdu_send_cmd_handler },
    { L2CC_SIGNALING_TRANS_TO_IND,      (ke_msg_func_t) l2cc_signaling_trans_to_ind_handler },
    #endif

    { L2CC_PDU_SEND_CMD,                (ke_msg_func_t) l2cc_pdu_send_cmd_handler },
    { L2CC_PDU_RECV_IND,                (ke_msg_func_t) l2cc_pdu_recv_ind_handler },

    { HCI_EVENT,                        (ke_msg_func_t) hci_nb_cmp_pkts_evt_handler },
    { HCI_ACL_DATA,                     (ke_msg_func_t) l2cc_hci_acl_data_handler },

    { KE_MSG_DEFAULT_HANDLER,           (ke_msg_func_t) l2cc_default_msg_handler },
};

/**************************************************************************************
 **************                       TASK SDK TAB                     ****************
 **************************************************************************************/
static const struct ke_msg_handler sdk_msg_handler_tab[] =
{
    /******************************* sdk gapm module ***************************************/
    {GAPM_CMP_EVT,                      (ke_msg_func_t)gapm_op_cmp_evt_handler },
    {GAPM_DEV_BDADDR_IND,               (ke_msg_func_t)gap_dev_bdaddr_ind_handler },
    {GAPM_ADDR_SOLVED_IND,              (ke_msg_func_t)gap_rslv_addr_ind_handler },
    {GAPM_PROFILE_ADDED_IND,            (ke_msg_func_t)gap_add_profile_ind_handler },
    {GAPM_ACTIVITY_CREATED_IND,         (ke_msg_func_t)gap_activity_created_ind_handler },
    {GAPM_ACTIVITY_STOPPED_IND,         (ke_msg_func_t)gap_activity_stopped_ind_handler },

    #if (CFG_MAX_SCAN)
    {GAPM_EXT_ADV_REPORT_IND,           (ke_msg_func_t)gap_ext_adv_report_ind_handler },
    #endif

    #if (CFG_CONNLESS_AOA_AOD_SUPPORT)
    {GAPM_SYNC_ESTABLISHED_IND,         (ke_msg_func_t)gap_sync_established_ind_handler },
    {GAPM_PER_ADV_IQ_REPORT_IND,        (ke_msg_func_t)gap_connless_iq_report_ind_handler },
    #endif

    /******************************* sdk gapc module ***************************************/
    #if (CFG_MASTER_SUPPORT || CFG_SLAVE_SUPPORT)
    {GAPC_CMP_EVT,                      (ke_msg_func_t)gap_cmp_evt_handler },
    {GAPC_CONNECTION_REQ_IND,           (ke_msg_func_t)gap_connection_req_ind_handler },
    {GAPC_DISCONNECT_IND,               (ke_msg_func_t)gap_disconnect_ind_handler },
    {GAPC_PEER_VERSION_IND,             (ke_msg_func_t)gap_con_peer_version_ind_handler },
    {GAPC_PEER_FEATURES_IND,            (ke_msg_func_t)gap_con_peer_features_ind_handler },
    {GAPC_CON_RSSI_IND,                 (ke_msg_func_t)gap_con_rssi_ind_handler },
    {GAPC_GET_DEV_INFO_REQ_IND,         (ke_msg_func_t)gap_get_dev_info_req_ind_handler },
    {GAPC_SET_DEV_INFO_REQ_IND,         (ke_msg_func_t)gap_set_dev_info_req_ind_handler },
    {GAPC_PARAM_UPDATE_REQ_IND,         (ke_msg_func_t)gap_param_update_req_ind_handler },
    {GAPC_PARAM_UPDATED_IND,            (ke_msg_func_t)gap_param_update_ind_handler },
    {GAPC_CON_CHANNEL_MAP_IND,          (ke_msg_func_t)gap_con_channel_map_ind_handler },
    {GAPC_LE_PKT_SIZE_IND,              (ke_msg_func_t)gap_le_pkt_size_ind_handler },
    {GAPC_LE_PHY_IND,                   (ke_msg_func_t)gap_le_phy_ind_handler },
    #endif

    #if (CFG_CONN_AOA_AOD_SUPPORT)
    {GAPC_CTE_IQ_REPORT_IND,            (ke_msg_func_t)gap_conn_iq_report_ind_handler },
    #endif

    #if (CFG_RANGING_SUPPORT)
    {GAPC_RANGING_IND,                  (ke_msg_func_t)gap_ranging_ind_handler },
    {GAPC_RANGING_SAMPLE_REPORT_IND,    (ke_msg_func_t)gap_ranging_sample_report_ind_handler },
    {GAPC_RANGING_CMP_IND,              (ke_msg_func_t)gap_ranging_cmp_ind_handler },
    #endif

    /******************************* sdk sec module ***************************************/
    #if (CFG_LEGACY_PAIR_SUPPORT || CFG_SC_PAIR_SUPPORT)
    {GAPC_BOND_REQ_IND,                 (ke_msg_func_t)sec_rcv_bond_req_ind_handler },
    {GAPC_BOND_IND,                     (ke_msg_func_t)sec_rcv_bond_ind_handler },
    {GAPC_ENCRYPT_REQ_IND,              (ke_msg_func_t)sec_rcv_encrypt_req_ind_handler },
    {GAPC_ENCRYPT_IND,                  (ke_msg_func_t)sec_rcv_encrypt_ind_handler },
    {GAPC_SECURITY_IND,                 (ke_msg_func_t)sec_rcv_sec_req_ind_handler },
    {GAPC_SIGN_COUNTER_IND,             (ke_msg_func_t)sec_rcv_sign_counter_update_ind_handler },
    {GAPC_SEC_REQ_TIMEOUT_IND,          (ke_msg_func_t)sec_rcv_sec_req_timeout_ind_handler },

    #endif

    /******************************* sdk l2cap module ***************************************/
    #if (CFG_COC_SUPPORT)
    {L2CC_CMP_EVT,                      (ke_msg_func_t)l2cap_lecb_rcv_cmp_evt_handler },
    {L2CC_LECB_CONNECT_REQ_IND,         (ke_msg_func_t)l2cap_lecb_rcv_conn_req_ind_handler },
    {L2CC_LECB_CONNECT_IND,             (ke_msg_func_t)l2cap_lecb_rcv_conn_ind_handler },
    {L2CC_LECB_DISCONNECT_IND,          (ke_msg_func_t)l2cap_lecb_rcv_disconn_ind_handler },
    {L2CC_LECB_ADD_IND,                 (ke_msg_func_t)l2cap_lecb_rcv_add_credits_ind_handler },
    {L2CC_LECB_SDU_RECV_IND,            (ke_msg_func_t)l2cap_lecb_rcv_sdu_ind_handler },
    #endif

    /******************************* sdk gatt module ***************************************/
    #if (CFG_GATTS_SUPPORT || CFG_GATTC_SUPPORT)
    {GATTC_CMP_EVT,                     (ke_msg_func_t)ble_sdk_gatt_cmp_evt_handler },
    {GATTC_MTU_CHANGED_IND,             (ke_msg_func_t)ble_sdk_gatt_mtu_changed_ind_handler },
    #endif

    #if (CFG_GATTS_SUPPORT)
    {GATTC_SVC_CHANGED_CFG_IND,         (ke_msg_func_t)ble_sdk_gatts_svc_changed_cfg_ind_handler },
    #endif

    #if (CFG_GATTC_SUPPORT)
    {GATTC_DISC_SVC_IND,                (ke_msg_func_t)ble_sdk_gattc_disc_srvc_ind_handler },
    {GATTC_DISC_SVC_INCL_IND,           (ke_msg_func_t)ble_sdk_gattc_disc_svc_inc_ind_handler },
    {GATTC_DISC_CHAR_IND,               (ke_msg_func_t)ble_sdk_gattc_disc_char_ind_handler },
    {GATTC_DISC_CHAR_DESC_IND,          (ke_msg_func_t)ble_sdk_gattc_disc_char_desc_ind_handler },
    {GATTC_READ_IND,                    (ke_msg_func_t)ble_gattc_read_ind_handler },
    {GATTC_EVENT_IND,                   (ke_msg_func_t)ble_sdk_gattc_event_ind_handler }, //notify
    {GATTC_EVENT_REQ_IND,               (ke_msg_func_t)ble_sdk_gattc_event_ind_handler }, //indicate
    {GATTC_SDP_SVC_IND,                 (ke_msg_func_t)ble_sdk_gattc_sdp_srvc_ind_handler },
    #endif

    {KE_MSG_DEFAULT_HANDLER,            (ke_msg_func_t)ble_sdk_common_timeout_handler },
};

extern void gapm_task_tab_init(const struct ke_msg_handler* tab, uint16_t size);
extern void gapc_task_tab_init(const struct ke_msg_handler* tab, uint16_t size);
extern void gattc_task_tab_init(const struct ke_msg_handler* tab, uint16_t size);
extern void l2cc_task_tab_init(const struct ke_msg_handler* tab, uint16_t size);
extern void sdk_task_tab_init(const struct ke_msg_handler* tab, uint16_t size);

static void ble_gapm_task_tab_init(void)
{
    gapm_hci_cmd_handler_tab_info[0].gapm_hci_evt_handler_p = (struct gapm_hci_evt_handler *)gapm_hci_cmd_cmp_event_handler_tab;
    gapm_hci_cmd_handler_tab_info[0].tab_size               = ARRAY_LEN(gapm_hci_cmd_cmp_event_handler_tab);
    gapm_hci_cmd_handler_tab_info[1].gapm_hci_evt_handler_p = (struct gapm_hci_evt_handler *)gapm_hci_cmd_stat_event_handler_tab;
    gapm_hci_cmd_handler_tab_info[1].tab_size               = ARRAY_LEN(gapm_hci_cmd_stat_event_handler_tab);
    gapm_hci_cmd_handler_tab_info[2].gapm_hci_evt_handler_p = (struct gapm_hci_evt_handler *)gapm_hci_le_event_handler_tab;
    gapm_hci_cmd_handler_tab_info[2].tab_size               = ARRAY_LEN(gapm_hci_le_event_handler_tab);

    gapm_task_tab_init(gapm_msg_handler_tab, ARRAY_LEN(gapm_msg_handler_tab));
}

static void ble_gapc_task_tab_init(void)
{
    hci_cmd_handler_tab_info[0].hci_handler_tab_p = (struct ke_msg_handler * )hci_cmd_cmp_event_handler_tab;
    hci_cmd_handler_tab_info[0].tab_size          = ARRAY_LEN(hci_cmd_cmp_event_handler_tab);
    hci_cmd_handler_tab_info[3].hci_handler_tab_p = (struct ke_msg_handler * )hci_le_event_handler_tab;
    hci_cmd_handler_tab_info[3].tab_size          = ARRAY_LEN(hci_le_event_handler_tab);

    gapc_task_tab_init(gapc_msg_handler_tab, ARRAY_LEN(gapc_msg_handler_tab));
}

static void ble_gatt_task_tab_init(void)
{
    gattc_task_tab_init(gattc_msg_handler_tab, ARRAY_LEN(gattc_msg_handler_tab));
}

static void ble_l2cc_task_tab_init(void)
{
    l2cc_task_tab_init(l2cc_msg_handler_tab, ARRAY_LEN(l2cc_msg_handler_tab));
}

static void ble_sdk_task_tab_init(void)
{
    sdk_task_tab_init(sdk_msg_handler_tab, ARRAY_LEN(sdk_msg_handler_tab));
}

static void ble_task_tab_init(void)
{
    ble_gapm_task_tab_init();
    ble_gapc_task_tab_init();
    ble_l2cc_task_tab_init();
    ble_gatt_task_tab_init();
    ble_sdk_task_tab_init();
}

static void ble_feature_init(void)
{
    #if (CFG_MAX_ADVS)
    adv_func_init();
    ble_adv_env_init();
    #endif

    #if (CFG_MAX_SCAN)
    scan_func_init();
    ble_scan_env_init();
    #endif

    #if (CFG_MASTER_SUPPORT)
    master_func_init();
    #endif

    #if (CFG_SLAVE_SUPPORT)
    slave_func_init();
    #endif

    #if (CFG_LEGACY_PAIR_SUPPORT)
    legacy_pair_func_init();
    #endif

    #if (CFG_SC_PAIR_SUPPORT)
    sc_pair_func_init();
    #endif

    #if (CFG_COC_SUPPORT)
    coc_func_init();
    #endif

    #if (CFG_GATTS_SUPPORT)
    gatts_func_init();
    ble_gatts_env_init();
    #endif

    #if (CFG_GATTC_SUPPORT)
    gattc_func_init();
    #endif

    #if (CFG_CONN_AOA_AOD_SUPPORT)
    conn_aoa_aod_func_init();
    #endif

    #if (CFG_CONNLESS_AOA_AOD_SUPPORT)
    connless_aoa_aod_func_init();
    #endif

    #if (CFG_RANGING_SUPPORT)
    ranging_func_init();
    #endif

    #if (CFG_MESH_SUPPORT)
    mesh_func_init();
    #endif

    #if (CFG_MAX_CONNECTIONS)
    ble_con_env_init();
    #endif

    #if (DTM_TEST_ENABLE)
    ble_test_evn_init();
    #ifndef DTM_ATE_ENABLE
    //no need to support private cmd in ate to save code resource
    ble_test_private_cmd_init();
    #endif
    #endif

    #if (CHIP_TYPE != 0) && (CFG_MUL_LINK_WITH_SAME_DEV)
    ble_mul_link_env_init();
    #endif

    #if (CFG_CAR_KEY_SUPPORT)
    ble_car_key_env_init();
    #endif

    #if (CFG_BT_BREDR)
    ble_bt_bredr_env_init();
    #endif

    // should call it after ble_con_env_init, for it need to over-write some content in
    #if (CFG_SNIFFER_SUPPORT)
    sniffer_func_init();
    #endif

    #if (RF_TX_PA_SELECT)
    ble_rf_tx_mode_set((ble_rf_tx_mode_t)RF_TX_PA_SELECT);
    #endif

    #if (CFG_MATCHING_CIRCUIT)
    ble_rf_match_circuit_set((ble_rf_match_circuit_t)CFG_MATCHING_CIRCUIT);
    #endif
}

void ble_stack_init(ble_evt_handler_t evt_handler, stack_heaps_table_t *p_heaps_table)
{
    ble_feature_init();
    ble_task_tab_init();
    ble_sdk_patch_env_init();
    ble_stack_enable(evt_handler, p_heaps_table);
}

void ble_stack_controller_init(stack_heaps_table_t *p_heaps_table)
{
    #if (RF_TX_PA_SELECT)
    ble_rf_tx_mode_set((ble_rf_tx_mode_t)RF_TX_PA_SELECT);
    #endif

    #if (CFG_MATCHING_CIRCUIT)
    ble_rf_match_circuit_set((ble_rf_match_circuit_t)CFG_MATCHING_CIRCUIT);
    #endif

    #if DTM_TEST_ENABLE
    ble_test_evn_init();
    #ifndef DTM_ATE_ENABLE
    //no need to support private cmd in ate to save code resource
    ble_test_private_cmd_init();
    #endif
    #endif

    ble_stack_controller_enable(p_heaps_table);
}

