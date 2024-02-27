/**
 ****************************************************************************************
 *
 * @file mesh_stack_config.h
 *
 * @brief Mesh stack configuration.
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

/*
 * DEFINES
 *****************************************************************************************
 */

#ifndef __MESH_STACK_CONFIG_H__
#define __MESH_STACK_CONFIG_H__

#include "custom_config.h"

#if (CFG_MESH_SUPPORT != 1)
    #error "If use mesh, should set CFG_MESH_SUPPORT (in file custom_config.h) to 1."
#endif

/*
 * @brief Align val on the multiple of 4 equal or nearest higher.
 */
#define CO_ALIGN4_HI(val) (((val)+3)&~3)

// <<< Use Configuration Wizard in Context Menu >>>

// <h> composition data

// <o> 16-bit company identifier assigned by the Bluetooth SIG
/*
 *  This parameter specifies Company ID.
 *
 */
#define MESH_DEVICE_COMPANY_ID                          (0x04F7)

// <o> 16-bit vendor-assigned product identifier
/*
 *  This parameter specifies a 16-bit vendor-assigned product identifier.
 */
#define MESH_DEVICE_PRODUCT_ID                          (0x0000)

// <o> 16-bit vendor-assigned product version identifier
/*
 *  This parameter specifies a 16-bit vendor-assigned product version identifier.
 */
#define MESH_DEVICE_VERSION_ID                          (0x0000)

// <h> device features
// <o> relay feature supported
//                                                      <0=> NOT SUPPORT
//                                                      <1=> SUPPORT
#define FEATURE_RELAY_SUPPORT                           (1)
#if (FEATURE_RELAY_SUPPORT != 0 && FEATURE_RELAY_SUPPORT != 1)
    #error "FEATURE_RELAY_SUPPORT is over the limit."
#endif
// <o> proxy feature supported
//                                                      <0=> NOT SUPPORT
//                                                      <1=> SUPPORT
#define FEATURE_PROXY_SUPPORT                           (1)
#if (FEATURE_PROXY_SUPPORT != 0 && FEATURE_PROXY_SUPPORT != 1)
    #error "FEATURE_PROXY_SUPPORT is over the limit."
#endif
// <o> friend feature supported
//                                                      <0=> NOT SUPPORT
//                                                      <1=> SUPPORT
#define FEATURE_FRIEND_SUPPORT                          (0)
#if (FEATURE_FRIEND_SUPPORT != 0 && FEATURE_FRIEND_SUPPORT != 1)
    #error "FEATURE_FRIEND_SUPPORT is over the limit."
#endif
// <o> low power feature supported
//                                                      <0=> NOT SUPPORT
//                                                      <1=> SUPPORT
#define FEATURE_LOW_POWER_SUPPORT                       (0)
#if (FEATURE_LOW_POWER_SUPPORT != 0 && FEATURE_LOW_POWER_SUPPORT != 1)
    #error "FEATURE_LOW_POWER_SUPPORT is over the limit."
#endif

#if (FEATURE_FRIEND_SUPPORT == 1 && FEATURE_LOW_POWER_SUPPORT == 1)
    #error "can not support both FEATURE_FRIEND_SUPPORT and FEATURE_LOW_POWER_SUPPORT."
#endif
// </h>

/*
 *  This parameter specifies the supported device feature.
 */
#define MESH_DEVICE_FEATURES                            ((FEATURE_RELAY_SUPPORT << 0) | (FEATURE_PROXY_SUPPORT << 1)    \
                                                         | (FEATURE_FRIEND_SUPPORT << 2) | (FEATURE_LOW_POWER_SUPPORT << 3))
// </h>

// <h> device name

// <s> device name
/*
 *  This parameter specifies the device name.
 */
#define MESH_DEVICE_NAME                                "Goodix_LLNS"
// </h>

// <h> mesh resource configuration

// <o> support maximum size of network message cache  
// <i> maximum size of network message cache
// <i> network message cache size shouldn't be less than 2
/*
 *  This parameter specifies the size of the network message cache.
 */
#define MESH_NET_CACHE_SIZE                             (10)
#if (MESH_NET_CACHE_SIZE < 2)
    #error "MESH_NET_CACHE_SIZE is over the limit."
#endif

// <o> the distance between the network sequence numbers
// <i> the distance between the network sequence numbers, for every persistent storage write.
// <i> If the device is powered cycled, it will resume transmission using the sequence number
// <i> from start of next block.
// <i> the distance shouldn't be less than 10
/*
 *  The distance between the network sequence numbers, for every persistent
 *  storage write. If the device is powered cycled, it will resume transmission
 *  using the sequence number from start of next block.
 */
#define MESH_NET_SEQ_NUMBER_BLOCK_SIZE                  (500)
#if (MESH_NET_SEQ_NUMBER_BLOCK_SIZE < 10)
    #error "MESH_NET_SEQ_NUMBER_BLOCK_SIZE is over the limit."
#endif

// <o> the sequence number value that triggers the start of an IV Update procedure if the node is a member of a primary subnet
// <i> the node must enter into IV Update state at least 96 hours before the sequence number wraps.
// <i> example: due to maximum allowed sequence number is 0xFFFFFF, we allow transmission of 3 packets per second
// <i>          during 96 hours by setting this value to 0xF00000.
// <i> the value should less than 0xFFFFFF, should be set reasonably according to usage scenarios.
/*  The sequence number value that triggers the start of an IV Update procedure if the node is a member of a primary subnet. 
 *  This value should be set so that there are enough sequence numbers left for running the IV update procedure
 */
#define MESH_NET_SEQ_NUMBER_THRESHOLD_IVUPDATE          (0xF00000)
#if (MESH_NET_SEQ_NUMBER_THRESHOLD_IVUPDATE >= 0xFFFFFF)
    #error "MESH_NET_SEQ_NUMBER_THRESHOLD_IVUPDATE is over the limit."
#endif

// <o> support maximum size of replay protection list
// <i> replay protection list is required to protect against relay attacks
// <i> replay protection list size shouldn't be less than 1
/*
 *  Replay Protection list is required to protect against relay attacks.
 *  This parameter specifies the size of the Replay Protection list.
 */
#define MESH_NET_REPLAY_LIST_SIZE                       (15)
#if (MESH_NET_REPLAY_LIST_SIZE < 1)
    #error "MESH_NET_REPLAY_LIST_SIZE is over the limit."
#endif

// <o> support maximum number of models <2-25>
// <i> maximum number of models the device supports
// <i> maximum number of models should be 2-25.
/*
 *  Maximum number of models the device supports.
 */
#define MESH_MODEL_NUM_MAX                              (25)
#if (MESH_MODEL_NUM_MAX < 2 || MESH_MODEL_NUM_MAX > 25)
    #error "MESH_MODEL_NB_MAX is over the limit."
#endif

// <o> support maximum size of subscription list for a model instance <1-10>
// <i> maximum subscription list size for a model instance the device supports.
// <i> maximum subscription list size for a model instance should be 1-10.
/*
 *  Maximum subscription list size for a model instance.
 */
#define MESH_SUBS_LIST_SIZE_MAX_PER_MODEL               (10)
#if (MESH_SUBS_LIST_SIZE_MAX_PER_MODEL < 1 || MESH_SUBS_LIST_SIZE_MAX_PER_MODEL > 10)
    #error "MESH_SUBS_LIST_SIZE_MAX_PER_MODEL is over the limit."
#endif

// <o> support maximum size of virtual addresses list <1-5>
// <i> It is the total number of virtual addresses the device supports
// <i> maximum virtual addresses list size should be 1-5.
/*
 *  Maximum virtual addresses list size the device supported.
 */
#define MESH_VIRT_ADDR_LIST_SIZE_MAX                    (5)
#if (MESH_VIRT_ADDR_LIST_SIZE_MAX < 1 || MESH_VIRT_ADDR_LIST_SIZE_MAX > 5)
    #error "MESH_VIRT_ADDR_LIST_SIZE_MAX is over the limit."
#endif

// <o> support maximum number of bind between application key and model <2-30>
// <i> maximum number of bind between application key and model the device supports
// <i> maximum number of bind between application key and model should be 2-30.
/*
 *  Maximum number of bind between application key and model.
 */
#define MESH_APPKEY_MODEL_BIND_NUM_MAX                  (30)
#if (MESH_APPKEY_MODEL_BIND_NUM_MAX < 2 || MESH_APPKEY_MODEL_BIND_NUM_MAX > 30)
    #error "MESH_APPKEY_MODEL_BIND_NB_MAX is over the limit."
#endif

// <h> optional configuration
// <h> when friend feature supported, this configuration is valid.
/*
 *  Friend feature supported.
 */
#if (FEATURE_FRIEND_SUPPORT)

// <o> receive window <1-255>
// <i> Receive window in milliseconds when Friend feature is supported
// <i> The value range is 1-255.
/*
 *  Receive window in milliseconds when Friend feature is supported.
 *  The value range is 0x01 - 0xFF.
 */
#define MESH_FRIEND_RX_WINDOW                           (255)

// <o> Queue size
// <i> Queue size when Friend feature is supported
// <i> The value shouldn't be less than 2.
/*
 *  Queue size when Friend feature is supported.
 */
#define MESH_FRIEND_QUEUE_SIZE                          (16)

// <o> Subscription list siz    <1-10>
// <i> Subscription list size when Friend feature is supported.
// <i> The value range is 1-10.
/*
 *  Subscription list size when Friend feature is supported.
 *  The value range is 0x01 - 0x0A.
 */
#define MESH_FRIEND_SUB_LIST_SIZE                       (10)

// <o> support maximum number of friendships the friend node can support <1-5>
// <i> maximum number of friendships the friend node can support.
// <i> The value range is 1-5.
/*
 *  Maximum number of Friendships the Friend node can support.
 */
#define MESH_FRIEND_FRIENDSHIP_NUM_MAX                  (5)


#if (MESH_FRIEND_RX_WINDOW < 1 || MESH_FRIEND_RX_WINDOW > 255)
    #error "MESH_FRIEND_RX_WINDOW is over the limit."
#endif
#if (MESH_FRIEND_QUEUE_SIZE < 2)
    #error "MESH_FRIEND_QUEUE_SIZE is over the limit."
#endif
#if (MESH_FRIEND_SUB_LIST_SIZE < 1 || MESH_FRIEND_SUB_LIST_SIZE > 10)
    #error "MESH_FRIEND_SUB_LIST_SIZE is over the limit."
#endif
#if (MESH_FRIEND_FRIENDSHIP_NUM_MAX < 1 || MESH_FRIEND_FRIENDSHIP_NUM_MAX > 5)
    #error "MESH_FRIEND_FRIENDSHIP_NUM_MAX is over the limit."
#endif

#define MEM_MESH_FRIEND                  (CO_ALIGN4_HI(MESH_FRIEND_FRIENDSHIP_NUM_MAX * 2)  \
                                          + MESH_FRIEND_FRIENDSHIP_NUM_MAX *8  \
                                          + MESH_FRIEND_FRIENDSHIP_NUM_MAX * (MESH_FRIEND_QUEUE_SIZE * 80 + 132 + 32))
#else
#define MEM_MESH_FRIEND                  (0)
#endif
// </h>

// <h> when proxy feature supported, this configuration is valid.
/*
 *  Proxy feature supported.
 */
#if (FEATURE_PROXY_SUPPORT)

// <o> support maximum size of the proxy filter list for an active connection <5-30>
// <i> maximum size of the proxy filter list for an active connection.
// <i> The value range is 5-30.
/*
 *  Maximum size of the Proxy filter list for an active connection.
 */
#define MESH_PROXY_FILTER_LIST_SIZE_MAX_PER_CONN        (30)

#if (MESH_PROXY_FILTER_LIST_SIZE_MAX_PER_CONN < 5 || MESH_PROXY_FILTER_LIST_SIZE_MAX_PER_CONN > 30)
    #error "MESH_PROXY_FILTER_LIST_SIZE is over the limit."
#endif

#if (CFG_MAX_CONNECTIONS < 1 || CFG_MAX_CONNECTIONS > 10)
    #error "CFG_MAX_CONNECTIONS is over the limit."
#endif

#define MEM_MESH_PROXY_FILTER                           (CFG_MAX_CONNECTIONS * (MESH_PROXY_FILTER_LIST_SIZE_MAX_PER_CONN * 2 + 8))
#else
#define MEM_MESH_PROXY_FILTER                           (0)
#endif
// </h>

// </h>

// <<< end of configuration section >>>

#define MEM_MESH_STATIC                             (8192)

#define MEM_MESH_NET_CACHE                          (MESH_NET_CACHE_SIZE * 8)
#define MEM_MESH_NET_REPLAY                         (MESH_NET_REPLAY_LIST_SIZE * 12)
#define MEM_MESH_MODEL_SUBS                         (CO_ALIGN4_HI(MESH_MODEL_NUM_MAX * 32) \
                                                     + CO_ALIGN4_HI(MESH_MODEL_NUM_MAX * MESH_SUBS_LIST_SIZE_MAX_PER_MODEL * 2)    \
                                                     + CO_ALIGN4_HI(MESH_MODEL_NUM_MAX * 6)    \
                                                     + (MESH_MODEL_NUM_MAX - 2) * (4 + 8 + 4 + 36))
#define MEM_MESH_APPKEY_MODEL_BIND                  (MESH_APPKEY_MODEL_BIND_NUM_MAX * 2)
#define MEM_MESH_VIRT_ADDR                          (MESH_VIRT_ADDR_LIST_SIZE_MAX * 20)

#define MESH_HEAP_SIZE_ADD  \
        (MEM_MESH_STATIC + MEM_MESH_NET_CACHE + MEM_MESH_NET_REPLAY + MEM_MESH_MODEL_SUBS \
         + MEM_MESH_APPKEY_MODEL_BIND + MEM_MESH_VIRT_ADDR + MEM_MESH_FRIEND + MEM_MESH_PROXY_FILTER)

#endif /* __MESH_STACK_CONFIG_H__ */

