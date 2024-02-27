/**
 *****************************************************************************************
 *
 * @file gx_list.h
 *
 * @brief Gx List API.
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
#ifndef _GX_LIST_H_
#define _GX_LIST_H_

/**
 *****************************************************************************************
 * @defgroup GX_LIST List management
 * @ingroup COMMON
 *
 * @brief  List management.
 *
 * This module contains the list structures and handling functions.
 * @{
 *****************************************************************************************
 */

/*
 * INCLUDE FILES
 ****************************************************************************************
 */

#include "grx_sys.h"
#include <stdbool.h>
#include <stdint.h>

/*
 * DEFINES
 ****************************************************************************************
 */


#define GX_LIST_DEFAULT_MAX_CNT 0x10
/// structure of a list element header
/*@TRACE*/
struct gx_list_hdr
{
    void *ptr;
    struct gx_list_hdr *prev;
    /// Pointer to next gx_list_hdr
    struct gx_list_hdr *next;
};

/// simplify type name of list element header
typedef struct gx_list_hdr gx_list_hdr_t;

/// structure of a list
struct gx_list
{
    /// pointer to first element of the list
    struct gx_list_hdr *first;
    /// pointer to the last element
    struct gx_list_hdr *last;

    /// number of element in the list
    uint16_t cnt;
    /// max number of element in the list
    uint16_t maxcnt;
};

/// simplify type name of list
typedef struct gx_list gx_list_t;

/*
 * MACROS
 ****************************************************************************************
 */

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */
/**
 ****************************************************************************************
 * @brief Initialize a list to defaults values.
 *
 * @param list           Pointer to the list structure.
 * @max_cnt             list structure max nodes.
 *
 ****************************************************************************************
 */
void gx_list_init(struct gx_list *list, uint16_t max_cnt);

/**
 ****************************************************************************************
 * @brief Add an element as last on the list.
 *
 * @param list           Pointer to the list structure
 * @param list_hdr       Pointer to the header to add at the end of the list
 * @return true if the list adds successful, false else otherwise.
 *
 ****************************************************************************************
 */
bool gx_list_push_back(struct gx_list *list, struct gx_list_hdr *list_hdr);

/**
 ****************************************************************************************
 * @brief Add an element as first on the list.
 *
 * @param list           Pointer to the list structure
 * @param list_hdr       Pointer to the header to add at the beginning of the list
 * @return true if the list adds successful, false else otherwise.
 ****************************************************************************************
 */
bool gx_list_push_front(struct gx_list *list, struct gx_list_hdr *list_hdr);

/**
 ****************************************************************************************
 * @brief Extract the first element of the list.
 * @param list           Pointer to the list structure
 * @return The pointer to the element extracted, and NULL if the list is empty.
 ****************************************************************************************
 */
struct gx_list_hdr *gx_list_pop_front(struct gx_list *list);

/**
 ****************************************************************************************
 * @brief Extract the last element of the list.
 * @param list           Pointer to the list structure
 * @return The pointer to the element extracted, and NULL if the list is empty.
 ****************************************************************************************
 */
struct gx_list_hdr *gx_list_pop_back(struct gx_list *list);

/**
****************************************************************************************
* @brief Search for a given element in the list, and extract it if found.
*
* @param list           Pointer to the list structure
* @param list_hdr       Element to extract
*
* @return true if the element is found in the list, false otherwise
****************************************************************************************
 */
 bool gx_list_extract(struct gx_list *list, struct gx_list_hdr *list_hdr);

/**
 ****************************************************************************************
 * @brief Count number of elements present in the list
 *
 * @param list           Pointer to the list structure
 *
 * @return Number of elements present in the list
 ****************************************************************************************
 */
__STATIC_INLINE uint16_t gx_list_size(struct gx_list *list)
{
    return list->cnt;
}

/**
 ****************************************************************************************
 * @brief Test if the list is empty.
 * @param list           Pointer to the list structure.
 * @return true if the list is empty, false else otherwise.
 ****************************************************************************************
 */
__STATIC_INLINE bool gx_list_is_empty(const struct gx_list *const list)
{
    bool listempty;
    listempty = (list->first == NULL);
    return (listempty);
}

/**
 ****************************************************************************************
 * @brief Pick the first element from the list without removing it.
 *
 * @param list           Pointer to the list structure.
 *
 * @return First element address. Returns NULL pointer if the list is empty.
 ****************************************************************************************
 */
__STATIC_INLINE struct gx_list_hdr *gx_list_pick_front(const struct gx_list *const list)
{
    return(list->first);
}

/**
 ****************************************************************************************
 * @brief Pick the last element from the list without removing it.
 *
 * @param list           Pointer to the list structure.
 *
 * @return Last element address. Returns NULL pointer if the list is empty.
 ****************************************************************************************
 */
__STATIC_INLINE struct gx_list_hdr *gx_list_pick_back(const struct gx_list *const list)
{
    return(list->last);
}

/**
 ****************************************************************************************
 * @brief Return following element of a list element.
 *
 * @param list_hdr     Pointer to the list element.
 *
 * @return The pointer to the next element.
 ****************************************************************************************
 */
__STATIC_INLINE struct gx_list_hdr *gx_list_next(const struct gx_list_hdr *const list_hdr)
{
    return(list_hdr->next);
}

/**
 ****************************************************************************************
 * @brief Return front element of a list element.
 *
 * @param list_hdr     Pointer to the list element.
 *
 * @return The pointer to the next element.
 ****************************************************************************************
 */
__STATIC_INLINE struct gx_list_hdr *gx_list_prev(const struct gx_list_hdr *const list_hdr)
{
    return(list_hdr->prev);
}

#endif /* _GX_LIST_H_ */

/** @} */
