/**
 ****************************************************************************************
 *
 * @file ble_lcp.h
 *
 * @brief LCP SDK API
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
 * @brief Definitions and prototypes for the BLE SDK interface.
 */
 
  /**
 * @addtogroup BLE_LCP Light Communication Protocol (LCP)
 * @{
 * @brief Definitions and prototypes for the LCP interface.
 */

#ifndef _LCP_SDK_H_
#define _LCP_SDK_H_

/**@addtogroup BLE_LCP_TYPEDEFS Typedefs
 * @{ 
 */
/**@brief RX handler callback function. */
typedef uint16_t (*rx_handler_cb_t) (uint8_t header, uint8_t length, uint8_t *p_payload);
typedef void (*rx_done_cb_t) (uint8_t type);
typedef void (*tx_done_cb_t) (void);
/** @} */

/**@addtogroup BLE_LCP_ENUMERATIONS Enumerations
 * @{ 
 */
enum LCP_RATE
{
    LCP_RATE_1MBPS = 0,
    LCP_RATE_2MBPS,
};

/**@brief Protocol Mode. */
enum PROTOCOL_MODE
{
    BLE_ADV = 0,       /**< BLE ADV mode. */
    BLE_SCAN = 1,      /**< BLE SCAN mode. */
    LCP_TRX_MODE_SW_TX = 2,     /*TX by software, just once */
    LCP_TRX_MODE_SW_RX = 3,           /*RX by software, just once */
    LCP_TRX_MODE_TIMER_TX = 4,     /*TX by timer with specified period, will stop when the timer stop */
    LCP_TRX_MODE_TIMER_RX = 5,       /*TX by timer with specified period, will stop when the timer stop */
};
/** @} */

/**@addtogroup BLE_LCP_STRUCTURES Structures
 * @{ */
/**@brief LCP Parameter. */
typedef struct
{
    uint8_t   trx_mode;                         /**< Set protocol mode, see @ref PROTOCOL_MODE. */
    int8_t    txpwr_dbm;                    /**< The value of the tx power(range: -20-7), uint: dBm. */
    uint32_t  freq_mhz;                         /**< The value of the frequency(range: 2360-2520), uint: MHz. */
    uint32_t  access_address;               /**< The value of the access address. */
    uint32_t  crc_init;                     /**< The initial value of the crc. */
    uint32_t  rx_window_size_us;   
    uint8_t     rate; // LCP_RATE_1MBPS or LCP_RATE_2MBPS

    bool     whiten_en;
    bool     b_disable_rx_oneshot_mode;     /**< should be false in timer trigger mode, support oneshot mode only*/

    uint32_t trx_timer_period_us; // while trx_mode=TRX_MODE_TIMER_TX/RX only
    uint32_t trx_timer_trigger_trx_time_us; // while trx_mode=TRX_MODE_TIMER_TX/RX only, should < trx_timer_period_us
    tx_done_cb_t tx_done_cb;   // xxx api
    rx_done_cb_t rx_done_cb;
    rx_handler_cb_t rx_handler_cb;          /**< The callback function of rx. */
} gdx_lcp_config_t;
/** @} */

/** @addtogroup BLE_LCP_FUNCTIONS Functions
 * @{ 
 */
/**
 ****************************************************************************************
 * @brief Initialize LCP.
 *
 * @param[in] gdx_lcp_config: Configure the parameter of LCP, @ref gdx_lcp_config_t.
 *
 * @retval ::SDK_SUCCESS: The LCP parameter is successfully configured.
 * @retval ::SDK_ERR_POINTER_NULL: Invalid pointer supplied.
 * @retval ::SDK_ERR_INVALID_PARAM: Invalid parameter supplied.
 ****************************************************************************************
 */
uint16_t gdx_lcp_init(gdx_lcp_config_t *gdx_lcp_config);

/**
 ****************************************************************************************
 * @brief Deinitialize LCP.
 *
 * @retval ::SDK_SUCCESS: The LCP is successfully Deinitialized.
 ****************************************************************************************
 */
void gdx_lcp_deinit(void);
void gdx_lcp_timer_binding(bool b_dual_timer, uint8_t timer_id);

/**
 ****************************************************************************************
 * @brief Set the tx power of LCP.
 *
 * @param[in] txpwr_dbm: The value of the tx power, Range: -20dbm to 7dbm.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_INVALID_PARAM: Invalid parameter supplied.
 ****************************************************************************************
 */
uint16_t gdx_lcp_tx_power_set(int8_t txpwr_dbm);

/**
 ****************************************************************************************
 * @brief Get the tx power of LCP.
 *
 * @param[in] txpwr_dbm: The value of the tx power, Range: -20dbm to 7dbm.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_POINTER_NULL: Invalid pointer supplied.
 ****************************************************************************************
 */
uint16_t gdx_lcp_tx_power_get(int8_t *txpwr_dbm);

/**
 ****************************************************************************************
 * @brief Set the channel of LCP.
 *
 * @param[in] freq_mhz: The value of the frequency, Range: 2360MHz to 2520MHz. 2M per step
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_INVALID_PARAM: Invalid parameter supplied.
 ****************************************************************************************
 */
uint16_t gdx_lcp_channel_set(uint32_t freq_mhz);

/**
 ****************************************************************************************
 * @brief Get the channel of LCP.
 *
 * @param[in] freq_mhz: The value of the frequency, Range: 2360MHz to 2520MHz.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_POINTER_NULL: Invalid pointer supplied.
 ****************************************************************************************
 */
uint16_t gdx_lcp_channel_get(uint32_t *freq_mhz);

/**
 ****************************************************************************************
 * @brief Set lcp access address
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 ****************************************************************************************
 */
uint16_t gdx_lcp_access_address_set(uint32_t access_address);

/**
 ****************************************************************************************
 * @brief Get lcp rssi
 *
 * @return Rssi value.
 ****************************************************************************************
 */
int8_t gdx_lcp_rssi_get(void);

/**
 ****************************************************************************************
 * @brief Set LCP rx windows size.
 *
 * @param[in] time_us: the windows size of rx.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 ****************************************************************************************
 */
void gdx_lcp_rx_window_size_set(uint32_t time_us);


/**
 ****************************************************************************************
 * @brief Rx oneshot mode enable or disable.
 *
 * @param[in] enable: enable oneshot or disable oneshot.
 ****************************************************************************************
 */
void gdx_lcp_rx_oneshot_mode_set(bool enable);

/**
 ****************************************************************************************
 * @brief Auto TXRX mode enable or disable.
 *
 * @param[in] enable: enable auto txrx or disable txrx to sw tx rx.
 ****************************************************************************************
 */
void gdx_lcp_auto_txrx_mode_set(bool enable);

/**
 ****************************************************************************************
 * @brief Transmmit a packet.
 *
 * @param[in] header: The header of the packet.
 * @param[in] length: The length of the packet payload.
 * @param[in] p_payload: The pointer of the packet payload.
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 * @retval ::SDK_ERR_INVALID_PARAM: Invalid parameter supplied.
 ****************************************************************************************
 */
uint16_t gdx_lcp_data_tx(uint8_t header, uint8_t length, uint8_t *p_payload);

/**
 ****************************************************************************************
 * @brief Start receiving packets
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 ****************************************************************************************
 */
uint16_t gdx_lcp_rx_start(void);
uint16_t gdx_lcp_whitening_seed_set(uint8_t whitening_seed);

/**
 ****************************************************************************************
 * @brief Stop receiving packets
 *
 * @retval ::SDK_SUCCESS: Operation is Success.
 ****************************************************************************************
 */
uint16_t gdx_lcp_rx_stop(void);

void gdx_lcp_t2r_turn_around_time_adjust(uint8_t added_us);
void gdx_lcp_r2t_turn_around_time_adjust(uint8_t added_us);

/** @} */

#endif

/** @} */
/** @} */
