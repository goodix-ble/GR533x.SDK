#ifndef __BLE_EM_MAP__
#define __BLE_EM_MAP__

#define BLE_EM_TOTAL_SIZE                   (0x4000)    //From BLE Stack Rom
#define BLE_EM_COMMON_FIX_OFFSET            (0x3350)    // <= 0x4000 - 0xC88(total fix EM buffer size)

#define BLE_EM_CUST_CONFIG_SIZE_MAX         (0x235B)
#define BLE_EM_ACTIVITY_BLOCK_SIZE          (0x120)

#define BLE_ACTIVITY_CUST                   (CFG_MAX_CONNECTIONS + 2 * CFG_MAX_ADVS + CFG_MAX_SCAN + DTM_TEST_ENABLE)

#if (BLE_ACTIVITY_CUST > 12)   // controller support max number of activity is 12
#error "custom configuration activity overflow, (CONNECTIONS+2*ADVS+SCAN) should not exceed the limit 12!!!"
#endif

#if (CFG_MAX_BOND_DEVS == 0)   // minimum number is 1
#error "custom configuration error, minimum number of CFG_MAX_BOND_DEVS is 1"
#endif

#if (CFG_MAX_BOND_DEVS > 10)
#define BLE_RAL_CUST                        10
#else
#define BLE_RAL_CUST                        (CFG_MAX_BOND_DEVS)
#endif

// <h> BLE EM buffer configuration
// <o> Support maximum number of BLE adv data buffer Number <0-9>
// <i> Range: 0-9
#if (CFG_MAX_ADVS)
#ifndef BLE_ADV_BUF_NB_CUST
#define BLE_ADV_BUF_NB_CUST                 (2 * CFG_MAX_ADVS)
#endif
#else
#ifndef BLE_ADV_BUF_NB_CUST
#define BLE_ADV_BUF_NB_CUST                 0
#endif
#endif

// <o> Support maximum number of BLE adv data fragments number <1-5>
// <i> Range: 1-5
#ifndef BLE_ADV_FRAG_NB_CUST
#define BLE_ADV_FRAG_NB_CUST                1
#endif

#if (BLE_EM_CUST_CONFIG_SIZE_MAX< \
    (BLE_ACTIVITY_CUST * BLE_EM_ACTIVITY_BLOCK_SIZE)+ \
    (BLE_ADV_BUF_NB_CUST*BLE_ADV_FRAG_NB_CUST*254 + BLE_ADV_FRAG_NB_CUST*BLE_ACTIVITY_CUST*16 + 6*BLE_ADV_FRAG_NB_CUST*BLE_ACTIVITY_CUST)+\
    BLE_EM_FREE_ZONE)
#error "custom configuration buffer overflow, please reduce the stack or advertising buffer configuration!!!"
#endif

#ifndef CO_ALIGN4_HI
#define CO_ALIGN4_HI(val)                   (((val)+3)&~3)
#endif

/*************************************************************************************************************
*                                Do not modify these paragraph at all costs: Begin                            *
*************************************************************************************************************/
/**
* Item 1: Control Structures area definition
 *
 * - LINK   (N)
 * - SCAN/INIT
 */
#define BLE_EM_BLE_CS_OFFSET                (0)
#define BLE_EM_BLE_CS_NB                    (BLE_ACTIVITY_CUST + 4)//(BLE_OBSERVER*3) + BLE_CENTRAL
#define BLE_EM_BLE_CS_END                   (BLE_EM_BLE_CS_OFFSET + BLE_EM_BLE_CS_NB * 148)//REG_EM_BLE_CS_SIZE


#if ((REG_EM_BLE_CS_SIZE % 4) != 0)
#error "CS Pointers must be 32 bits aligned"
#endif // ((REG_EM_BLE_CS_SIZE % 4) != 0)

/*
 * Item 2: WHITE LIST
 ****************************************************************************************
 */

/// White list area definition
#define BLE_EM_BLE_WPAL_OFFSET              (BLE_EM_BLE_CS_END)
#define BLE_EM_BLE_WPAL_SIZE                (10 * 12)//BLE_WHITELIST_MAX * REG_EM_BLE_WPAL_SIZE
#define BLE_EM_BLE_WPAL_END                 (BLE_EM_BLE_WPAL_OFFSET + BLE_EM_BLE_WPAL_SIZE)


#if ((REG_EM_BLE_WPAL_SIZE % 4) != 0)
#error "WPAL Pointers must be 32 bits aligned"
#endif // ((REG_EM_BLE_WPAL_SIZE % 4) != 0)

/*
 * Item 3: RESOLVING LIST
 ****************************************************************************************
 */

/// Resolving list area definition
#define BLE_EM_BLE_RAL_OFFSET               (BLE_EM_BLE_WPAL_END)
#define BLE_EM_BLE_RAL_SIZE                 (BLE_RAL_CUST * 56)//REG_EM_BLE_RAL_SIZE
#define BLE_EM_BLE_RAL_END                  (BLE_EM_BLE_RAL_OFFSET + BLE_EM_BLE_RAL_SIZE)

#if ((REG_EM_BLE_RAL_SIZE % 4) != 0)
#error "RAL Pointers must be 32 bits aligned"
#endif // ((REG_EM_BLE_RAL_SIZE % 4) != 0)

/*
 * TX DESCRIPTORS
 ****************************************************************************************
 */

/**
 * Item 4: TX Descriptors area definition
 *
 * - N per connection
 * - 1 per advertising data buffer
 */
#define BLE_EM_BLE_TX_DESC_OFFSET           (BLE_EM_BLE_RAL_END)
#define BLE_EM_BLE_TX_DESC_NB               ((BLE_ADV_FRAG_NB_CUST+2) * BLE_ACTIVITY_CUST)
#define BLE_EM_BLE_TX_DESC_END              (BLE_EM_BLE_TX_DESC_OFFSET + BLE_EM_BLE_TX_DESC_NB * 16)//REG_EM_BLE_TX_DESC_SIZE

#if ((REG_EM_BLE_TX_DESC_SIZE % 4) != 0)
#error "TX Descriptors must be 32 bits aligned"
#endif // ((REG_EM_BLE_TX_DESC_SIZE % 4) != 0)

/*
 * Item 5: LLCP TX BUFFERS
 ****************************************************************************************
 */

/// LLCP TX buffers area definition
#define BLE_EM_BLE_LLCPTXBUF_OFFSET         (BLE_EM_BLE_TX_DESC_END)
#define BLE_EM_BLE_LLCPTXBUF_NB             (2*BLE_ACTIVITY_CUST)
#define BLE_EM_BLE_LLCPTXBUF_SIZE           36//CO_ALIGN4_HI(LL_PDU_LENGTH_MAX) // ensure that LLCP buffer is 32bits aligned
#define BLE_EM_BLE_LLCPTXBUF_END            (BLE_EM_BLE_LLCPTXBUF_OFFSET + BLE_EM_BLE_LLCPTXBUF_NB * BLE_EM_BLE_LLCPTXBUF_SIZE)


/*
 * Item 6: ADV EXTENDED HEADERS TX BUFFER
 ****************************************************************************************
 */

/// Advertising TX buffer area definition
#define BLE_EM_BLE_ADVEXTHDRTXBUF_OFFSET    (BLE_EM_BLE_LLCPTXBUF_END)
#define BLE_EM_BLE_ADVEXTHDRTXBUF_NB        (BLE_ACTIVITY_CUST)
#define BLE_EM_BLE_ADVEXTHDRTXBUF_SIZE      (39 + 6*(BLE_ADV_FRAG_NB_CUST - 1))
#define BLE_EM_BLE_ADVEXTHDRTXBUF_END       (BLE_EM_BLE_ADVEXTHDRTXBUF_OFFSET + BLE_EM_BLE_ADVEXTHDRTXBUF_NB * BLE_EM_BLE_ADVEXTHDRTXBUF_SIZE)

/*
  * Item 7: ADVERTISING DATA TX BUFFERS
  ****************************************************************************************
  */

/// Advertising data TX buffers area definition
#define BLE_EM_BLE_ADVDATATXBUF_OFFSET      (BLE_EM_BLE_ADVEXTHDRTXBUF_END)
#define BLE_EM_BLE_ADVDATATXBUF_NB          (BLE_ADV_BUF_NB_CUST)
#define BLE_EM_BLE_ADVDATATXBUF_SIZE        (BLE_ADV_FRAG_NB_CUST*254)
#define BLE_EM_BLE_ADVDATATXBUF_END         (BLE_EM_BLE_ADVDATATXBUF_OFFSET + BLE_EM_BLE_ADVDATATXBUF_NB * BLE_EM_BLE_ADVDATATXBUF_SIZE)

/*
 * Item 8: ACL TX BUFFERS
 ****************************************************************************************
 */

/// ACL TX buffers area definition
#define BLE_EM_BLE_ACLTXBUF_OFFSET          (BLE_EM_BLE_ADVDATATXBUF_END)
#define BLE_EM_BLE_ACLTXBUF_NB              (12)
#define BLE_EM_BLE_ACLTXBUF_SIZE            (256)
#define BLE_EM_BLE_ACLTXBUF_END             (BLE_EM_BLE_ACLTXBUF_OFFSET + BLE_EM_BLE_ACLTXBUF_NB * BLE_EM_BLE_ACLTXBUF_SIZE)

/*************************************************************************************************************
*                                Do not modify these paragraph at all costs: End                             *
*************************************************************************************************************/

#define _EM_MIN_SAVE_MARGIN                 38// do not modify to less than item*3+7

#define _EM_BLE_END                         (BLE_EM_BLE_ACLTXBUF_END)

#define _EM_COMMON_OFFSET                   ((BLE_EM_COMMON_FIX_OFFSET - _EM_BLE_END - _EM_MIN_SAVE_MARGIN)/8*8)

#define BLE_EM_FREE_SIZE                    _EM_COMMON_OFFSET
#define BLE_EM_USED_SIZE                    (BLE_EM_TOTAL_SIZE - BLE_EM_FREE_SIZE)
#endif
