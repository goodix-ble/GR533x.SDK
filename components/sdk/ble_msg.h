/**
 ****************************************************************************************
 *
 * @file ble_msg.h
 *
 * @brief declare the message handler function
 *
 ****************************************************************************************
 * @attention
  #####Copyright (c) 2019 GOODIX
  All rights reserved.

    Redistribution and use in source and binary forms, with or without
    modification, are permitted provided that the following conditions are met:
  * Redistributions of source code must retain the above copyright
    notice, this list of conditions and the following disclaimer.
  * Redistributions in binary form must reproduce the above copyright
    notice, this list of conditions and the following disclaimer in the
    documentation and/or other materials provided with the distribution.
  * Neither the name of GOODIX nor the names of its contributors may be used
    to endorse or promote products derived from this software without
    specific prior written permission.

  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
  ARE DISCLAIMED. IN NO EVENT SHALL COPYRIGHT HOLDERS AND CONTRIBUTORS BE
  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
  POSSIBILITY OF SUCH DAMAGE.
 *****************************************************************************************
 */

 /**
 * @addtogroup BLE
 * @{
 */

  /**
 * @addtogroup BLE_MSG
 * @{
 * @brief Message handler function extern.
 */

#ifndef __BLE_MSG_H__
#define __BLE_MSG_H__

#include <stdint.h>

/** @addtogroup BLE_MSG_DEFINES Defines
 * @{ */

/// Get the number of elements within an array, give also number of rows in a 2-D array
#define ARRAY_LEN(array)   (sizeof((array))/sizeof((array)[0]))

/// Message Identifier. The number of messages is limited to 0xFFFF.
/// The message ID is divided in two parts:
/// bits[15~8]: task index (no more than 255 tasks support)
/// bits[7~0]: message index(no more than 255 messages per task)
typedef uint16_t ke_msg_id_t;

/// Task Identifier. Composed by the task type and the task index.
typedef uint16_t ke_task_id_t;

/**@} */

/** @addtogroup BLE_MSG_HANDLER Functions
 * @{ */

// declare for GAPM_TASK
int hci_le_cmd_cmp_evt_adv_handler(uint16_t opcode, void const *p_event);

int hci_basic_cmd_cmp_evt_cfg_handler(uint16_t opcode, void const *event);

int hci_le_cmd_cmp_evt_list_handler(uint16_t opcode, void const *p_event);

int hci_le_cmd_cmp_evt_scan_handler(uint16_t opcode, void const *event);

int hci_le_cmd_cmp_evt_addr_handler(uint16_t opcode, void const *p_event);

int hci_basic_cmd_cmp_evt_rl_cfg_handler(uint16_t opcode, void const *event);

int hci_le_cmd_cmp_evt_init_handler(uint16_t opcode, void const *event);

int hci_le_ext_adv_report_evt_handler(uint16_t opcode, void *p_event);

int hci_le_scan_timeout_evt_handler(uint16_t opcode, void const *p_event);

int hci_le_enh_con_cmp_evt_handler(uint16_t opcode, void const *p_event);

int hci_le_rd_local_p256_public_key_cmp_evt_handler(uint16_t opcode, void const *p_event);

int hci_le_adv_set_term_evt_handler(uint16_t opcode, void const *p_event);

int hci_le_cmd_cmp_evt_per_sync_handler(uint16_t opcode, void const *p_event);

int hci_le_set_per_adv_rec_en_cmp_evt_handler(uint16_t opcode, void const *p_event);

int hci_le_set_conless_cte_tx_param_cmd_cmp_handler(uint16_t opcode, void const *p_event);

int hci_le_set_conless_cte_tx_en_cmd_cmp_handler(uint16_t opcode, void const *p_event);

int hci_le_set_conless_iq_sampl_en_cmd_cmp_evt_list_handler(uint16_t opcode, void const *p_event);

int hci_le_gen_dhkey_v2_stat_evt_handler(uint16_t opcode, void const *p_event);

int hci_le_per_adv_sync_est_evt_handler(uint16_t opcode, void const *p_event);

int hci_le_per_adv_sync_lost_evt_handler(uint16_t opcode, void const *p_event);

int hci_le_conless_iq_report_evt_handler(uint16_t opcode, void const *p_event);

int hci_le_gen_dhkey_cmp_evt_handler(uint16_t opcode, void const *p_event);

int hci_le_per_adv_report_evt_handler(uint16_t opcode, void const *p_event);

int gapm_cmp_evt_handler(ke_msg_id_t const msgid, void const *cmp_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_reset_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_set_dev_config_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_set_channel_map_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_get_dev_info_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_profile_task_add_cmd_handler(ke_msg_id_t const msgid, void const * param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_public_addr_set_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_list_set_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_activity_create_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_activity_start_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_activity_stop_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_activity_delete_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_addr_renew_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_addr_renew_to_ind_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_dev_bdaddr_ind_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_set_adv_data_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_per_adv_cte_tx_ctl_cmd_handler(ke_msg_id_t const msgid, void const *p_cmd,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_per_adv_cte_tx_param_set_handler(ke_msg_id_t const msgid, void const *p_cmd,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_auto_conn_to_ind_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_cmp_evt_handler(ke_msg_id_t const msgid, void const *cmp_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_resolv_addr_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_gen_rand_addr_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_gen_dh_key_cmd_handler(ke_msg_id_t const msgid, void const * param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_get_pub_key_cmd_handler(ke_msg_id_t const msgid, void const * param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_per_adv_report_ctrl_cmd_handler(ke_msg_id_t const msgid, void const* p_cmd,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_per_sync_iq_sampling_ctrl_cmd_handler(ke_msg_id_t const msgid, void const* p_cmd,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_set_gdx_ranging_param_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_lepsm_register_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_lepsm_unregister_cmd_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_unknown_task_msg_handler(ke_msg_id_t const msgid, void * param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_hci_handler(ke_msg_id_t const msgid, void const* event,
    ke_task_id_t dest_id, ke_task_id_t opcode);

int gapm_default_msg_handler(ke_msg_id_t const msgid, void *event,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

// declare for GAPC_TASK
int hci_rd_rssi_cmd_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_rd_chnl_map_cmd_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_le_set_data_len_cmd_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_le_rd_phy_cmd_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_le_rd_rem_feats_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_le_con_update_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_le_rem_con_param_req_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_le_data_len_chg_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_le_phy_upd_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_le_ch_sel_algo_evt_handler(uint16_t opcode, void const *p_evt);

int hci_le_ltk_request_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_cte_cmd_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_le_ranging_ind_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_le_ranging_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_le_ranging_sample_report_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_l2cc_cmp_evt_handler(ke_msg_id_t const msgid, void *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_hci_handler(ke_msg_id_t const msgid, void const* p_evt,
    ke_task_id_t dest_id, ke_task_id_t src_id);

int gapc_hci_handler(ke_msg_id_t const msgid, void const* p_evt,
    ke_task_id_t dest_id, ke_task_id_t src_id);

int gapc_default_msg_handler(ke_msg_id_t const msgid, void *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_le_con_iq_report_evt_handler(ke_msg_id_t const msgid, void const *p_evt,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_l2cc_pdu_recv_ind_handler(ke_msg_id_t const msgid, void *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_gattc_read_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_gattc_write_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_gattc_att_info_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapm_smpc_pub_key_ind_handler(ke_msg_id_t const msgid, void *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_gen_dh_key_ind_handler(ke_msg_id_t const msgid, void *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_smp_gapm_cmp_evt_handler(ke_msg_id_t const msgid, void *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_connection_cfm_handler(ke_msg_id_t const msgid, void *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_disconnect_cmd_handler(ke_msg_id_t const msgid, void *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_get_info_cmd_handler(ke_msg_id_t const msgid, void *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_get_dev_info_cfm_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_set_dev_info_cfm_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_param_update_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_param_update_cfm_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_bond_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_bond_cfm_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_encrypt_cfm_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_encrypt_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_security_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_set_phy_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_per_adv_sync_trans_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_cte_tx_cfg_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_cte_rx_cfg_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_cte_req_ctrl_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_cte_rsp_ctrl_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_ranging_start_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_update_conn_param_to_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_smp_timeout_timer_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_smp_rep_attempts_timer_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gapc_set_le_pkt_size_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

// declare for GATTC_TASK
int gattc_l2cc_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_l2cc_pdu_recv_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_exc_mtu_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_disc_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_disc_svc_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_disc_svc_incl_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_disc_char_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_disc_char_desc_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_sdp_svc_disc_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_timeout_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_read_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_write_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_read_cfm_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_write_cfm_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_execute_write_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_event_cfm_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_reg_to_peer_evt_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_send_evt_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_send_svc_changed_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_read_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_default_msg_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_write_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_att_info_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_att_info_cfm_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gattc_timeout_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

// declare for L2CC_TASK
int l2cc_lecb_sdu_send_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cc_lecb_connect_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cc_lecb_connect_cfm_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cc_lecb_disconnect_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cc_signaling_trans_to_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cc_lecb_add_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cc_pdu_send_cmd_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cc_pdu_recv_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int hci_nb_cmp_pkts_evt_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cc_hci_acl_data_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cc_default_msg_handler(ke_msg_id_t const msgid, void *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

// declare for SDK_TASK
int gapm_op_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_activity_created_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_activity_stopped_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_add_profile_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_ext_adv_report_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_sync_established_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_dev_bdaddr_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_rslv_addr_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_connless_iq_report_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);


int gap_connection_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_disconnect_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_param_update_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_param_update_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_le_phy_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_con_rssi_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_le_pkt_size_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_con_channel_map_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_con_peer_version_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_con_peer_features_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_get_dev_info_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_set_dev_info_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_conn_iq_report_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_ranging_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_ranging_sample_report_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int gap_ranging_cmp_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int sec_rcv_sec_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int sec_rcv_bond_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int sec_rcv_bond_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int sec_rcv_sign_counter_update_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int sec_rcv_encrypt_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int sec_rcv_encrypt_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cap_lecb_rcv_conn_req_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cap_lecb_rcv_conn_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cap_lecb_rcv_disconn_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cap_lecb_rcv_sdu_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cap_lecb_rcv_cmp_evt_handler(ke_msg_id_t const msgid,  void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int l2cap_lecb_rcv_add_credits_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int ble_sdk_gatts_svc_changed_cfg_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int ble_sdk_gattc_sdp_srvc_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int ble_sdk_gattc_event_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int ble_gattc_read_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int ble_sdk_gattc_disc_char_desc_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int ble_sdk_gattc_disc_char_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int ble_sdk_gattc_disc_svc_inc_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int ble_sdk_gattc_disc_srvc_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int ble_sdk_gatt_mtu_changed_ind_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int ble_sdk_gatt_cmp_evt_handler(ke_msg_id_t const msgid, void const *p_param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

int ble_sdk_common_timeout_handler(ke_msg_id_t const msgid, void const *param,
    ke_task_id_t const dest_id, ke_task_id_t const src_id);

/** @} */
#endif
/** @} */
/** @} */

