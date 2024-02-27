/**
 *****************************************************************************************
 *
 * @file model_common.h
 *
 * @brief Model Common API.
 *
 *****************************************************************************************
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
 * @addtogroup MESH
 * @{
 */
#ifndef __MODEL_COMMON_H__
#define __MODEL_COMMON_H__


/*
 * INCLUDE FILES
 ****************************************************************************************
 */
#include <stdint.h>
#include <stddef.h>
#include "mesh_common.h"
#include "mesh_model.h"


/*
 * DEFINES
 ****************************************************************************************
 */
 
#define TRANSITION_TIME_STEP_RESOLUTION_100MS   (0x00)
#define TRANSITION_TIME_STEP_RESOLUTION_1S      (0x40)
#define TRANSITION_TIME_STEP_RESOLUTION_10S     (0x80)
#define TRANSITION_TIME_STEP_RESOLUTION_10M     (0xC0)

#define TRANSITION_TIME_STEP_MASK               (0xC0)
#define TRANSITION_TIME_STEP_100MS_FACTOR       (100)
#define TRANSITION_TIME_STEP_1S_FACTOR          (1000)
#define TRANSITION_TIME_STEP_10S_FACTOR         (10*1000)
#define TRANSITION_TIME_STEP_10M_FACTOR         (10*60*1000)

#define STATUS_CODES_SUCCESS 0x00   //Success
#define STATUS_CODES_ERR_MIN 0x01   //Cannot Set Range Min
#define STATUS_CODES_ERR_MAX 0x02   //Cannot Set Range Max

/**
 * Get pointer to the start of a structure given a pointer to one of the structure's fields.
 *
 * @param[in] STRUCT_TYPE   Type of structure.
 * @param[in] FIELD_NAME    Name of field.
 * @param[in] FIELD_POINTER Pointer to field inside the structure.
 *
 * @return Pointer to start of structure.
 */
#define PARENT_BY_FIELD_GET(STRUCT_TYPE, FIELD_NAME, FIELD_POINTER) \
    ((STRUCT_TYPE *) (((uint8_t *)FIELD_POINTER) - offsetof(STRUCT_TYPE, FIELD_NAME)))


/** Maximum value of transition time (in ms) possible in steps of 100 ms */
#define TRANSITION_TIME_STEP_100MS_MAX          (6200ul)
/** Maximum value of transition time (in ms) possible in steps of 1 s */
#define TRANSITION_TIME_STEP_1S_MAX             (62000ul)
/** Maximum value of transition time (in ms) possible in steps of 10 s */
#define TRANSITION_TIME_STEP_10S_MAX            (620000ul)
/** Maximum value of transition time (in ms) possible in steps of 10 min */
#define TRANSITION_TIME_STEP_10M_MAX            (620000ul * 60)
/** Max value of encoded transition time step value */
#define TRANSITION_TIME_MAX                     (0x3E)
/** Unknown encoded transition time value */
#define TRANSITION_TIME_UNKNOWN                 (0x3F)
/** Maximum permissible transition time in milliseconds */
#define TRANSITION_TIME_MAX_MS                  (TRANSITION_TIME_STEP_10M_MAX)

/** Delay field step factor in milliseconds */
#define DELAY_TIME_STEP_FACTOR_MS               (5)
/** Maximum encoded value of the delay field */
#define DELAY_TIME_STEP_MAX                     (0xFF)
/** Maximum permisible delay time in milliseconds */
#define DELAY_TIME_MAX_MS                       (DELAY_TIME_STEP_MAX * DELAY_TIME_STEP_FACTOR_MS)

/* ************************** Model IDs for Generic Models ***************************** */

/** Generic Server - OnOff model ID */
#define MODEL_ID_GENS_OO           (0x1000)
/** Generic Server - Level model ID */
#define MODEL_ID_GENS_LVL          (0x1002)
/** Generic Server - Default Transition Time model ID */
#define MODEL_ID_GENS_DTT          (0x1004)
/** Generic Server - Power OnOff model ID */
#define MODEL_ID_GENS_POO          (0x1006)
/** Generic Server - Power OnOff Setup model ID */
#define MODEL_ID_GENS_POOS         (0x1007)
/** Generic Server - Power Level model ID */
#define MODEL_ID_GENS_PLVL         (0x1009)
/** Generic Server - Power Level Setup model ID */
#define MODEL_ID_GENS_PLVLS        (0x100A)
/** Generic Server - Battery model ID */
#define MODEL_ID_GENS_BAT          (0x100C)
/** Generic Server - Location model ID */
#define MODEL_ID_GENS_LOC          (0x100E)
/** Generic Server - Location Setup model ID */
#define MODEL_ID_GENS_LOCS         (0x100F)
/** Generic Server - User Property model ID */
#define MODEL_ID_GENS_UPROP        (0x1013)
/** Generic Server - Admin Property model ID */
#define MODEL_ID_GENS_APROP        (0x1011)
/** Generic Server - Manufacturer Property model ID */
#define MODEL_ID_GENS_MPROP        (0x1012)
/** Generic Server - Client Property model ID */
#define MODEL_ID_GENS_CPROP        (0x1014)

/** Generic Client - OnOff model ID */
#define MODEL_ID_GENC_OO           (0x1001)
/** Generic Client - Level model ID */
#define MODEL_ID_GENC_LVL          (0x1003)
/** Generic Client - Default Transition Time model ID */
#define MODEL_ID_GENC_DTT          (0x1005)
/** Generic Client - Power OnOff model ID */
#define MODEL_ID_GENC_POO          (0x1008)
/** Generic Client - Power Level model ID */
#define MODEL_ID_GENC_PLVL         (0x100B)
/** Generic Client - Location model ID */
#define MODEL_ID_GENC_LOC          (0x1010)
/** Generic Client - Battery model ID */
#define MODEL_ID_GENC_BAT          (0x100D)
/** Generic Client - Property model ID */
#define MODEL_ID_GENC_PROP         (0x1015)

/// ************************** Model IDs for Sensors Models *****************************

/** Sensors Server - Sensor model ID */
#define MODEL_ID_SENS_SEN          (0x1100)
/** Sensors Server - Sensor Setup model ID */
#define MODEL_ID_SENS_SENS         (0x1101)

/** Sensors Client - Sensor model ID */
#define MODEL_ID_SENC_SEN          (0x1102)

/// ********************** Model IDs for Time and Scenes Models *************************

/** Time and Scene Server - Time model ID */
#define MODEL_ID_TSCNS_TIM         (0x1200)
/** Time and Scene Server - Time Setup model ID */
#define MODEL_ID_TSCNS_TIMS        (0x1201)
/** Time and Scene Server - Scene model ID */
#define MODEL_ID_TSCNS_SCN         (0x1203)
/** Time and Scene Server - Scene Setup model ID */
#define MODEL_ID_TSCNS_SCNS        (0x1204)
/** Time and Scene Server - Scheduler model ID */
#define MODEL_ID_TSCNS_SCH         (0x1206)
/** Time and Scene Server - Scheduler Setup model ID */
#define MODEL_ID_TSCNS_SCHS        (0x1207)

/** Time and Scene Client - Time model ID */
#define MODEL_ID_TSCNC_TIM         (0x1202)
/** Time and Scene Client - Scene model ID */
#define MODEL_ID_TSCNC_SCN         (0x1205)
/** Time and Scene Client - Scheduler model ID */
#define MODEL_ID_TSCNC_SCH         (0x1208)

/// ************************** Model IDs for Lighting Models ****************************

/** Lighting Server - Light Lightness model ID */
#define MODEL_ID_LIGHTS_LN         (0x1300)
/** Lighting Server - Light Lightness Setup model ID */
#define MODEL_ID_LIGHTS_LNS        (0x1301)
/** Lighting Server - Light CTL model ID */
#define MODEL_ID_LIGHTS_CTL        (0x1303)
/** Lighting Server - Light CTL Temperature model ID */
#define MODEL_ID_LIGHTS_CTLT       (0x1306)
/** Lighting Server - Light CTL Setup model ID */
#define MODEL_ID_LIGHTS_CTLS       (0x1304)
/** Lighting Server - Light HSL model ID */
#define MODEL_ID_LIGHTS_HSL        (0x1307)
/** Lighting Server - Light HSL Hue model ID */
#define MODEL_ID_LIGHTS_HSLH       (0x130A)
/** Lighting Server - Light HSL Saturation model ID */
#define MODEL_ID_LIGHTS_HSLSAT     (0x130B)
/** Lighting Server - Light HSL Setup model ID */
#define MODEL_ID_LIGHTS_HSLS       (0x1308)
/** Lighting Server - Light xyL model ID */
#define MODEL_ID_LIGHTS_XYL        (0x130C)
/** Lighting Server - Light xyL Setup model ID */
#define MODEL_ID_LIGHTS_XYLS       (0x130D)
/** Lighting Server - Light LC model ID */
#define MODEL_ID_LIGHTS_LC         (0x130F)
/** Lighting Server - Light LC Setup model ID */
#define MODEL_ID_LIGHTS_LCS        (0x1310)

/** Lighting Client - Light Lightness model ID */
#define MODEL_ID_LIGHTC_LN         (0x1302)
/** Lighting Client - Light CTL model ID */
#define MODEL_ID_LIGHTC_CTL        (0x1305)
/** Lighting Client - Light HSL model ID */
#define MODEL_ID_LIGHTC_HSL        (0x1309)
/** Lighting Client - Light xyL model ID */
#define MODEL_ID_LIGHTC_XYL        (0x130E)
/** Lighting Client - Light LC model ID */
#define MODEL_ID_LIGHTC_LC         (0x1311)

/*
 * ENUMERATIONS
 ****************************************************************************************
 */

/*
/// List of opcodes for the mesh generic model
enum mesh_generic_model_opcodes
{
    // generic on off model
    GENERIC_OPCODE_ON_OFF_GET                           = 0x8201,
    GENERIC_OPCODE_ON_OFF_SET,
    GENERIC_OPCODE_ON_OFF_SET_UNACK,
    GENERIC_OPCODE_ON_OFF_STATUS,
    // generic level model
    GENERIC_OPCODE_LEVEL_GET                            = 0x8205,
    GENERIC_OPCODE_LEVEL_SET,
    GENERIC_OPCODE_LEVEL_SET_UNACK,
    GENERIC_OPCODE_LEVEL_STATUS,
    GENERIC_OPCODE_DELTA_SET,
    GENERIC_OPCODE_DELTA_SET_UNACK,
    GENERIC_OPCODE_MOVE_SET,
    GENERIC_OPCODE_MOVE_SET_UNACK,
    // generic default transition time model
    GENERIC_OPCODE_DEFAULT_TRANS_TIME_GET               = 0x820D,
    GENERIC_OPCODE_DEFAULT_TRANS_TIME_SET,
    GENERIC_OPCODE_DEFAULT_TRANS_TIME_SET_UNACK,
    GENERIC_OPCODE_DEFAULT_TRANS_TIME_STATUS,
    // generic power on off model
    GENERIC_OPCODE_ON_POWER_UP_GET                      = 0x8211,
    GENERIC_OPCODE_ON_POWER_UP_STATUS,
    // generic power on off setup model
    GENERIC_OPCODE_ON_POWER_UP_SET                      = 0x8213,
    GENERIC_OPCODE_ON_POWER_UP_SET_UNACK,
    // generic power level model
    GENERIC_OPCODE_POWER_LEVEL_GET                      = 0x8215,
    GENERIC_OPCODE_POWER_LEVEL_SET,
    GENERIC_OPCODE_POWER_LEVEL_SET_UNACK,
    GENERIC_OPCODE_POWER_LEVEL_STATUS,
    GENERIC_OPCODE_POWER_LAST_GET,
    GENERIC_OPCODE_POWER_LAST_STATUS,
    GENERIC_OPCODE_POWER_DEFAULT_GET,
    GENERIC_OPCODE_POWER_DEFAULT_STATUS,
    GENERIC_OPCODE_POWER_RANGE_GET,
    GENERIC_OPCODE_POWER_RANGE_STATUS,
    // generic power level setup model
    GENERIC_OPCODE_POWER_DEFAULT_SET                    = 0x821F,
    GENERIC_OPCODE_POWER_DEFAULT_SET_UNACK,
    GENERIC_OPCODE_POWER_RANGE_SET,
    GENERIC_OPCODE_POWER_RANGE_SET_UNACK,
    // generic battery model
    GENERIC_OPCODE_BATTERY_GET                          = 0x8223,
    GENERIC_OPCODE_BATTERY_STATUS,
    // generic location model
    GENERIC_OPCODE_LOCATION_GLOBAL_GET                  = 0x8225,
    GENERIC_OPCODE_LOCATION_GLOBAL_STATUS               = 0x40,
    GENERIC_OPCODE_LOCATION_LOCAL_GET                   = 0x8226,
    GENERIC_OPCODE_LOCATION_LOCAL_STATUS,
    // generic location setup model
    GENERIC_OPCODE_LOCATION_GLOBAL_SET                  = 0x41,
    GENERIC_OPCODE_LOCATION_GLOBAL_SET_UNACK,
    GENERIC_OPCODE_LOCATION_LOCAL_SET                   = 0x8228,
    GENERIC_OPCODE_LOCATION_LOCAL_SET_UNACK,
    // generic manufacturer property model
    GENERIC_OPCODE_MANU_PROPERTIES_GET                  = 0x822A,
    GENERIC_OPCODE_MANU_PROPERTIES_STATUS               = 0x43,
    GENERIC_OPCODE_MANU_PROPERTY_GET                    = 0x822B,
    GENERIC_OPCODE_MANU_PROPERTY_SET                    = 0x44,
    GENERIC_OPCODE_MANU_PROPERTY_SET_UNACK,
    GENERIC_OPCODE_MANU_PROPERTY_STATUS,
    // generic admin property model
    GENERIC_OPCODE_ADMIN_PROPERTIES_GET                  = 0x822C,
    GENERIC_OPCODE_ADMIN_PROPERTIES_STATUS               = 0x47,
    GENERIC_OPCODE_ADMIN_PROPERTY_GET                    = 0x822D,
    GENERIC_OPCODE_ADMIN_PROPERTY_SET                    = 0x48,
    GENERIC_OPCODE_ADMIN_PROPERTY_SET_UNACK,
    GENERIC_OPCODE_ADMIN_PROPERTY_STATUS,
    // generic user property model
    GENERIC_OPCODE_USER_PROPERTIES_GET                   = 0x822E,
    GENERIC_OPCODE_USER_PROPERTIES_STATUS                = 0x4B,
    GENERIC_OPCODE_USER_PROPERTY_GET                     = 0x822F,
    GENERIC_OPCODE_USER_PROPERTY_SET                     = 0x4C,
    GENERIC_OPCODE_USER_PROPERTY_SET_UNACK,
    GENERIC_OPCODE_USER_PROPERTY_STATUS,
    // generic client property model
    GENERIC_OPCODE_CLIENT_PROPERTIES_GET                 = 0x4F,
    GENERIC_OPCODE_CLIENT_PROPERTIES_STATUS,
};
*/

/*
 * TYPE DEFINITIONS
 ****************************************************************************************
 */

/** Generic Transition parameters for the model messages. */
typedef struct
{
    uint32_t transition_time_ms;                            /**< Transition time value in milliseconds */
    uint32_t delay_ms;                                      /**< Message execution delay in milliseconds */
} model_transition_t;

/** Structure for tracking TID expiry for the models */
typedef struct
{
    uint16_t src;                       /**< Source address */
    uint32_t message_id;                /**< Previously received Opcode */
    uint8_t old_tid;                    /**< Previously received TID */
    bool new_transaction;               /**< New transaction indicator flag */
    mesh_timer_t tid_expiry_timer;      /**< Expiration timer instance */
} tid_tracker_t;

/*
 * FUNCTIONS
 ****************************************************************************************
 */

/**
 * Gets the decoded value of the transition time in milliseconds.
 *
 * @param[in] enc_transition_time Encoded value of the transition time as specified in the Mesh
 *                                Model Specification.
 *
 * @returns Transition time in milliseconds.
 */
uint32_t model_transition_time_decode(uint8_t enc_transition_time);

/**
 * Gets the encoded value of the transition time as specified in the Mesh Model Specification.
 * Note that the provided value will be rounded down to the nearest possible representation.
 *
 * @param[in] transition_time Transition time in milliseconds.
 *
 * @returns Encoded value of the transition time as specified in the Mesh Model Specification.
 */
uint8_t model_transition_time_encode(uint32_t transition_time);

/**
 * Validates the given transition time value.
 *
 * @param[in]  enc_transition_time  Encoded transition time value
 *
 * @retval True                     If encoded transition time is a valid value for the models.
 * @retval False                    If encoded transition time is invalid for the models and cannot be set.
 *
 */
bool model_transition_time_is_valid(uint8_t enc_transition_time);

/**
 * Gets the decoded value of the delay time in milliseconds
 *
 * @param[in] enc_delay Encoded value of the delay time as specified in the Mesh
 *                      Model Specification.
 *
 * @returns delay time in milliseconds.
 */
uint32_t model_delay_decode(uint8_t enc_delay);

/**
 * Gets the encoded value of the delay time as specified in the Mesh Model Specification.
 * Note that the provided value will be rounded down to the nearest possible representation.
 *
 * @param[in] delay Delay time in milliseconds.
 *
 * @returns Encoded value of the delay time as specified in the Mesh Model Specification.
 */
uint8_t model_delay_encode(uint32_t delay);

/** Checks if the given message parameters represents a new transaction.
 *
 * The transaction is considered either new or same as previous in the context of
 * a given message ID, TID, source address and timeout of 6 seconds as specified by the Mesh Model Specification 1.0.
 * This API is used by the model interfaces to reject duplicate transactions.
 *
 * @param[in] p_tid_tracker     Pointer to the tid tracker structure.
 * @param[in] p_rx_msg          Access message metadata containing source and destination addresses.
 * @param[in] message_id        Any kind of unique identifier (e.g opcode) for a given type of message.
 * @param[in] tid               Received TID value.
 *
 * @retval    True              If transaction is new.
 * @retval    False             If transaction is same as the previous transaction.
 */
bool model_tid_validate(tid_tracker_t * p_tid_tracker, const mesh_model_msg_ind_t * p_rx_msg,
                        uint32_t message_id, uint8_t tid);

/**
 * Checks if given TID tracker instance has recorded a new transaction.
 *
 * This API can be used by the user application to determine if the received message callback
 * represents a new transaction.
 *
 * @param[in] p_tid_tracker     Pointer to the tid tracker structure.
 *
 * @retval    True              If transaction is new.
 * @retval    False             If transaction is same as the previous transaction.
 */
bool model_transaction_is_new(tid_tracker_t * p_tid_tracker);

/**
 * Register default transition time value pointer.
 *
 *
 * @param[in] element_offset           Element address offset from primary element address.
 * @param[in] dtt_value_ptr       Pointer to default transition time value.
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_SDK_INVALID_PARAM       Invalid parameter.
 */
uint16_t model_register_dtt_ptr(uint8_t element_offset, uint8_t *dtt_value_ptr);

/**
 * Checks if default transition time has registed.
 *
 *
 * @param[out] rst_dtt_ptr     Return default transiton time pointer if success .
 *
 * @retval ::MESH_ERROR_NO_ERROR                Operation is Success.
 * @retval ::MESH_ERROR_NOT_SUPPORTED       Not support the operation.
 */
uint16_t model_update_dtt_ptr(uint8_t **rst_dtt_ptr);


#endif /* __MODEL_COMMON_H__ */

/** @} */

