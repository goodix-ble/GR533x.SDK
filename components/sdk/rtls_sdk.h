/**
 ****************************************************************************************
 *
 * @file rtls_sdk.h
 *
 * @brief RTLS API
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
#ifndef __RTLS_SDK_H__
#define __RTLS_SDK_H__

#define MAX_ANTENNA_COUNT           (4)
#define MAX_CAL_BUFFER_SIZE         (100)

#define RANGING_LEPSM               (0xFF)

/** @brief antenna element struct. */
typedef struct  
{  
 uint8_t gpio_truth;
 float axis_x; /**< x axis uint cm. */
 float axis_y; /**< y axis uint cm. */
}rtls_antenna_element_t;
  
typedef struct
{
 uint8_t ant_number;
 rtls_antenna_element_t ant_array[MAX_ANTENNA_COUNT];
}rtls_antenna_env_t;


/** @brief connectionless cte transmission parameter struct. */
typedef struct
{
    uint8_t cte_len;                          /**< CTE length (8us unit, range 0x02 to 0x14). */
    uint8_t cte_type;                         /**< CTE type (0: AOA | 1: AOD-1us | 2: AOD-2us). */
    uint8_t cte_count;                        /**< CTE count (number of CTEs to transmit in each periodic advertising interval, range 0x01 to 0x10). */
    // uint8_t pattern_len;                      /**< The number of Antenna IDs in the pattern (range 0x02 to 0x4B). */
    // uint8_t antenna_id[MAX_ANTENNA_COUNT];    /**< List of Antenna IDs in the pattern. */
} rtls_conless_cte_trans_param_t;

/** @brief connectionless cte reception parameter struct. */
typedef struct
{
    uint8_t slot_dur;                         /**< The slot duration for IQ sampling. */
    uint8_t max_smaple_cte;                   /**< The maximum number of CTE to sample and report in each periodic advertising interval (range 0x00 to 0x10).
                                                    0x00: Sample and report all available CTE. */
    // uint8_t pattern_len;                      /**< The number of antenna IDs in the pattern (range 0x02 to 0x4B). */
    // uint8_t antenna_id[MAX_ANTENNA_COUNT];    /**< List of Antenna IDs in the pattern. */
} rtls_conless_cte_rcv_param_t;

/** @brief connectionless iq report event struct. */
typedef struct
{
    uint8_t  channel_idx;                     /**< The index of the channel on which the packet was received, range 0x00 to 0x24. */
    int16_t  rssi;                            /**< RSSI units: 0.1 dBm, range -1270 to +200. */
    uint8_t  rssi_antenna_id;                 /**< RSSI antenna ID. */
    uint8_t  cte_type;                        /**< CTE type (0: CET_AOA | 1: CET_AOD_1US | 2: CET_AOD_2US). */
    uint8_t  slot_dur;                        /**< Slot durations (1: SLOT_1US | 2: SLOT_2US). */
    uint8_t  pkt_status;                      /**< Packet status. */
    uint16_t pa_evt_cnt;                      /**< Periodic advertising event counter. */
    uint8_t  nb_samples;                      /**< Number of samples. 0x00: no samples provided (only permitted if pkt_status is 0xFF),
                                                   0x09 to 0x52: total number of sample pairs. */
    int8_t   i_sample[BLE_GAP_MAX_IQ_SAMPLE_NUM]; /**< The list of i samples for the reported PDU. */
    int8_t   q_sample[BLE_GAP_MAX_IQ_SAMPLE_NUM]; /**< The list of q samples for the reported PDU. */
} rtls_conless_iq_report_t;

/** @brief connection cte transmission parameter struct. */
typedef struct
{
    uint8_t cte_type;                            /**< The type of cte(bit0: 0: CET_AOA | bit1: CET_AOD_1US | bit2: CET_AOD_2US ). */
    // uint8_t pattern_len;                      /**< The number of Antenna IDs in the pattern, range 0x02 to 0x4B. */
    // uint8_t antenna_id[MAX_ANTENNA_COUNT];    /**< List of Antenna IDs in the pattern. */
} rtls_con_cte_trans_param_t;

/** @brief connection cte reception parameter struct. */
typedef struct
{
    bool     sampling_enable;                  /**< Wheter to sample IQ from the CTE. */
    uint8_t  slot_dur;                         /**< The slot for sample IQ from the CTE. */
    // uint8_t  pattern_len;                      /**< The number of Antenna IDs in the pattern, range 0x02 to 0x4B. */
    // uint8_t  antenna_id[MAX_ANTENNA_COUNT];    /**< List of Antenna IDs in the pattern. */
    uint16_t cte_req_interval;                 /**< Defines whether the cte request procedure is initiated only once or periodically.
                                                   0x0000: initiate the Constant Tone Extension Request procedure once.
                                                   0x0001 to 0xFFFF: requested interval for initiating the cte request procedure in number of connection events. */
    uint8_t  req_cte_len;                      /**< Minimum length of the cte being requested in 8us units, range 0x02 to 0x14. */
    uint8_t  req_cte_type;                     /**< The cte type for requested. */
} rtls_con_cte_rcv_param_t;

/** @brief connection iq report event struct. */
typedef struct
{
    uint8_t  rx_phy;                          /**< Rx PHY (0x01: 1M | 0x02: 2M). */
    uint8_t  data_channel_idx;                /**< Data channel index, range 0x00 to 0x24. */
    int16_t  rssi;                            /**< RSSI units: 0.1 dBm, range -1270 to +200. */
    uint8_t  rssi_antenna_id;                 /**< RSSI antenna ID. */
    uint8_t  cte_type;                        /**< CTE type (0: AOA | 1: AOD_1US | 2: AOD_2US). */
    uint8_t  slot_dur;                        /**< Slot durations (1: SLOT_1US | 2: SLOT_2US). */
    uint8_t  pkt_status;                      /**< Packet status. */
    uint16_t con_evt_cnt;                     /**< Connection event counter. */
    uint8_t  nb_samples;                      /**< Number of samples. 0x00: no samples provided (only permitted if pkt_status is 0xFF),
                                                   0x09 to 0x52: total number of sample pairs. */
    int8_t   i_sample[BLE_GAP_MAX_IQ_SAMPLE_NUM]; /**< The list of i samples for the reported PDU. */
    int8_t   q_sample[BLE_GAP_MAX_IQ_SAMPLE_NUM]; /**< The list of q samples for the reported PDU. */
} rtls_con_iq_report_t;

/** @brief angle result event struct. */
typedef struct
{
    uint8_t  channel_idx;                     /**< The index of the channel on which the packet was received, range 0x00 to 0x24. */
    int16_t  rssi;                            /**< RSSI units: 0.1 dBm, range -1270 to +200. */
    uint8_t  rssi_antenna_id;                 /**< RSSI antenna ID. */
    uint8_t  cte_type;                        /**< CTE type (0: CET_AOA | 1: CET_AOD_1US | 2: CET_AOD_2US). */
    uint8_t  slot_dur;                        /**< Slot durations (1: SLOT_1US | 2: SLOT_2US). */
    uint8_t  pkt_status;                      /**< Packet status. */
    uint16_t evt_cnt;                         /**< Event counter. */
    uint8_t  nb_samples;                      /**< Number of samples. 0x00: no samples provided (only permitted if pkt_status is 0xFF),
                                                   0x09 to 0x52: total number of sample pairs. */
    float   angle;                           /**< angle, unit: PI. */
} rtls_angle_result_t;

/** @brief applicaiton rtls function callback struct. */
typedef struct
{
    void (*app_rtls_conless_iq_report_cb)(uint8_t per_sync_idx, const rtls_conless_iq_report_t *iq_report);    /**< connectionless iq report callback. */
    void (*app_rtls_conless_angle_result_cb)(uint8_t per_sync_idx, const rtls_angle_result_t *angle_result);   /**< connectionless angle result callback. */
    void (*app_rtls_con_iq_report_cb)(uint8_t con_idx, const rtls_con_iq_report_t *iq_report);                 /**< connectionless iq report callback. */
    void (*app_rtls_con_angle_result_cb)(uint8_t con_idx, const rtls_angle_result_t *angle_result);            /**< connection angle result callback */
    void (*app_rtls_estimated_angle_cb)(float angle, float elev);                                                          /**< algorithm angle result callback */
} rtls_cb_fun_t;

/** @brief ranging parameter struct. */
typedef struct
{
    /// ranging channel sequence
    uint8_t  ch_seq[BLE_GAP_MAX_GDX_RANGING_CH];
    /// Number of channel to be collected
    uint8_t  ch_num;
    uint8_t  cte_len;
} rtls_ranging_param_t;

typedef struct
{
    /// status
    uint8_t  status;
    /// sample number
    uint16_t nb_sample;
    /// sample
    int8_t   *sample;
} rtls_ranging_sample_report_t;

/** @brief angle result event struct. */
typedef struct
{
    uint8_t  channel_idx;                     /**< The index of the channel on which the packet was received, range 0x00 to 0x24. */
    int16_t  rssi;                            /**< RSSI units: 0.1 dBm, range -1270 to +200. */
    uint16_t evt_cnt;                         /**< Event counter. */
    float    distance;                        /**< distance, unit: centimeter. */
} rtls_distance_result_t;

/** @brief applicaiton rtls function callback struct. */
typedef struct
{
    void (*app_rtls_ranging_ind_cb)(uint8_t con_idx, uint8_t status);    /**< ranging indication callback. */
    void (*app_rtls_ranging_sample_report_cb)(uint8_t con_idx, const rtls_ranging_sample_report_t *sample);                 /**< ranging sample report callback. */
    void (*app_rtls_ranging_cmp_cb)(uint8_t con_idx, uint8_t status);            /**< ranging indication callback. */
    void (*app_rtls_ranging_distance)(uint8_t con_idx, rtls_distance_result_t *distance);
} rtls_ranging_cb_fun_t;


/** @brief rtls cte role. */
enum rtls_cte_role
{
    RTLS_ROLE_UNDEF,                   /**< undefined role. */
    RTLS_ROLE_CONLESS_TRANSMITTER,     /**< connectionless transmitter */
    RTLS_ROLE_CONLESS_RECEIVER,        /**< connectionless receiver */
    RTLS_ROLE_CON_TRANSMITTER,         /**< connection transmitter */
    RTLS_ROLE_CON_RECEIVER,            /**< connection receiver */
};

/**
 ****************************************************************************************
 * @brief set connectionless cte transmission parameters
 *
 * @param[in] per_adv_idx: index of periodic advertise.
 * @param[in] param:       connectionless cte transmission parameters.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_DISALLOWED: Operation disallowed
 * @retval ::SDK_ERR_INVALID_PARAM: Invalid parameter supplied.
 * @retval ::SDK_ERR_INVALID_CONN_IDX: Invalid connection index supplied.
 * @retval ::SDK_ERR_NO_RESOURCES: Not enough resources.
 ****************************************************************************************
 */
uint16_t rtls_set_conless_cte_trans_parameter(uint8_t per_adv_idx, const rtls_conless_cte_trans_param_t *param);

/**
 ****************************************************************************************
 * @brief set connectionless cte reception parameters
 *
 * @param[in] per_sync_idx: index of periodic synchronization.
 * @param[in] param:       connectionless cte reception parameters.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_DISALLOWED: Operation disallowed
 * @retval ::SDK_ERR_INVALID_PARAM: Invalid parameter supplied.
 * @retval ::SDK_ERR_INVALID_CONN_IDX: Invalid connection index supplied.
 * @retval ::SDK_ERR_NO_RESOURCES: Not enough resources.
 ****************************************************************************************
 */
uint16_t rtls_set_conless_cte_rcv_parameter(uint8_t per_sync_idx, const rtls_conless_cte_rcv_param_t *param);

/**
 ****************************************************************************************
 * @brief set connection cte transmission parameters
 *
 * @param[in] con_idx: index of connection.
 * @param[in] param:       connection cte transmission parameters.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_DISALLOWED: Operation disallowed
 * @retval ::SDK_ERR_INVALID_PARAM: Invalid parameter supplied.
 * @retval ::SDK_ERR_INVALID_CONN_IDX: Invalid connection index supplied.
 * @retval ::SDK_ERR_NO_RESOURCES: Not enough resources.
 ****************************************************************************************
 */
uint16_t rtls_set_con_cte_trans_parameter(uint8_t con_idx, const rtls_con_cte_trans_param_t *param);

/**
 ****************************************************************************************
 * @brief set connection cte reception parameters
 *
 * @param[in] con_idx: index of connection.
 * @param[in] param:       connection cte reception parameters.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_DISALLOWED: Operation disallowed
 * @retval ::SDK_ERR_INVALID_PARAM: Invalid parameter supplied.
 * @retval ::SDK_ERR_INVALID_CONN_IDX: Invalid connection index supplied.
 * @retval ::SDK_ERR_NO_RESOURCES: Not enough resources.
 ****************************************************************************************
 */
uint16_t rtls_set_con_cte_rcv_parameter(uint8_t con_idx, const rtls_con_cte_rcv_param_t *param);

/**
 ****************************************************************************************
 * @brief clear cte parameters
 *
 * @param[in] link_idx: index of periodic advertise/periodic synchronization/connection.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_DISALLOWED: Operation disallowed
 * @retval ::SDK_ERR_INVALID_CONN_IDX: Invalid connection index supplied.
 ****************************************************************************************
 */
uint16_t rtls_clear_cte_parameter(uint8_t link_idx);

/**
 ****************************************************************************************
 * @brief initiate rtls module
 *
 * @param[in] cb: applicaiton rtls function callback.
 *
 * @retval ::void.
 ****************************************************************************************
 */
void     rtls_init(rtls_cb_fun_t *cb);

/**
 ****************************************************************************************
 * @brief check if rtls module initialized
 *
 * @param[in] void.
 *
 * @retval ::true:  rtls module is initialized.
 * @retval ::false: rtls module is not initialized.
 ****************************************************************************************
 */
bool     rtls_is_initialized(void);

/**
 ****************************************************************************************
 * @brief check if rtls service related to specific link is running
 *
 * @param[in] link_idx: index of periodic advertise/periodic synchronization/connection.
 *
 * @retval ::true:rtls service is running.
 * @retval ::false:rtls service is not running.
 ****************************************************************************************
 */
bool     rtls_is_running(uint8_t link_idx);

/**
 ****************************************************************************************
 * @brief start direction finding
 *
 * @param[in] link_idx: index of periodic advertise/periodic synchronization/connection.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_DISALLOWED: Operation disallowed
 * @retval ::SDK_ERR_INVALID_HANDLE: Invalid index supplied.
 ****************************************************************************************
 */
uint16_t rtls_direction_start(uint8_t link_idx);

/**
 ****************************************************************************************
 * @brief stop direction finding
 *
 * @param[in] link_idx: index of periodic advertise/periodic synchronization/connection.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_DISALLOWED: Operation disallowed
 * @retval ::SDK_ERR_INVALID_HANDLE: Invalid index supplied.
 ****************************************************************************************
 */
uint16_t rtls_direction_stop(uint8_t link_idx);

/**
 ****************************************************************************************
 * @brief calculate angle using iq sample
 *
 * @param[in] nb_sample: number of sample
 * @param[in] i_sample: i sample data
 * @param[in] q_sample: q sample data
 *
 * @param[out] angle: angle in radian
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_DISALLOWED: Operation disallowed
 * @retval ::SDK_ERR_INVALID_HANDLE: Invalid index supplied.
 * @retval ::SDK_ERR_BUSY: SDK is busy internally.
 ****************************************************************************************
 */
uint16_t rtls_calc_angle(uint8_t nb_sample, const int8_t *i_sample, const int8_t *q_sample, uint8_t channel_index);

/**  
 ****************************************************************************************
 * @brief Set rtls environment including antenna array and calculation buffer
 *
 * @param[in] ant_env: include antenna number and antenna array
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_DISALLOWED: Operation disallowed.
 * @retval ::SDK_ERR_POINTER_NULL:  Invalid pointer supplied.
 * @retval ::SDK_ERR_INVALID_PARAM: Invalid parameter supplied.
 ****************************************************************************************
 */
uint16_t rtls_set_env(const rtls_antenna_env_t* ant_env);

/**
 ****************************************************************************************
 * @brief Get antenna array from rtls module
 *
 * @param[out] ant_number: number of antennas
 * @param[out] ant_array: antenna array pointer
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_DISALLOWED: Operation disallowed
 ****************************************************************************************
 */

uint16_t rtls_get_env(uint8_t* ant_number, rtls_antenna_element_t **ant_array);

/**
 ****************************************************************************************
 * @brief Clear rtls environment configuration
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_DISALLOWED: Operation disallowed
 ****************************************************************************************
 */
uint16_t rtls_clear_env(void);

/**
 ****************************************************************************************
 * @brief Set rtls environment including antenna array and calculation buffer
 *
 * @param[in] algo_window_size_u: counter of cte to get one angle result
 * @param[in] dbscan_eps_u: parameter for dbscan function
 * @param[in] dbscan_min_samp_u: parameter for dbscan function
 *  
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_INVALID_PARAM: Invalid parameter supplied.
 ****************************************************************************************
 */
uint16_t rtls_set_algorithm_param(uint8_t algo_window_size_u, float dbscan_eps_u, uint8_t dbscan_min_samp_u);

/**
 ****************************************************************************************
 * @brief Get antenna array from rtls module
 *
 * @param[out] algo_window_size_u: counter of cte to get one angle result
 * @param[out] dbscan_eps_u: parameter for dbscan function
 * @param[out] dbscan_min_samp_u: parameter for dbscan function
 *
 ****************************************************************************************
 */
void rtls_get_algorithm_param(uint8_t *algo_window_size_u, float *dbscan_eps_u, uint8_t *dbscan_min_samp_u);

/**
 ****************************************************************************************
 * @brief Get estimated angle calculated by algorithm
 *
 * @retval Estimated angle calculated by algorithm
 ****************************************************************************************
 */
float rtls_get_estimated_angle(void);

/**
 ****************************************************************************************
 * @brief Set TX&RX primary antenna
 *
 * @param[in] gpiotruth: GPIO truth value of primary antenna
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_SDK_INTERNAL : Internal SDK error.
 ****************************************************************************************
 */
uint16_t rtls_set_primary_antenna(uint8_t gpiotruth);

/**
 ****************************************************************************************
 * @brief Get TX&RX primary antenna
 *
 * @retval :: GPIO truth value of primary antenna.
 ****************************************************************************************
 */
uint8_t rtls_get_primary_antenna(void);


/**
 ****************************************************************************************
 * @brief initiate rtls ranging module
 *
 * @param[in] cb: applicaiton rtls function callback.
 * @param[in] cte_len: cte length used for ranging.
 * @param[in] client: rtls ranging module act as client role or not
 * @retval ::void.
 ****************************************************************************************
 */
void rtls_ranging_init(rtls_ranging_cb_fun_t *cb, uint8_t cte_len, bool client);
/**
 ****************************************************************************************
 * @brief set ranging parameters
 *
 * @param[in] param: ranging parameters.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_DISALLOWED: Operation disallowed
 * @retval ::SDK_ERR_INVALID_PARAM: Invalid parameter supplied.
 ****************************************************************************************
 */
uint16_t rtls_set_ranging_param(const rtls_ranging_param_t *param);

/**
 ****************************************************************************************
 * @brief set cte length
 *
 * @param[in] cte_len: cte length.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_INVALID_PARAM: Invalid parameter supplied.
 ****************************************************************************************
 */
uint16_t rtls_ranging_set_cte_len(uint8_t cte_len);

/**
 ****************************************************************************************
 * @brief start ranging
 *
 * @param[in] link_idx: connection index.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_DISALLOWED: Operation disallowed
 * @retval ::SDK_ERR_INVALID_HANDLE: Invalid index supplied.
 ****************************************************************************************
 */
uint16_t rtls_ranging_start(uint8_t con_idx);

uint16_t rtls_set_env_array(const rtls_antenna_env_t* ant_env_A, const rtls_antenna_env_t* ant_env_B, const rtls_antenna_env_t* ant_env_C, const rtls_antenna_env_t* ant_env_D, uint8_t ant_array_num);

#endif //__RTLS_SDK_H__
