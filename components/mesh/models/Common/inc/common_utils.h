/**
 ****************************************************************************************
 *
 * @file common_utils.h
 *
 * @brief Header file for Common Utils Module
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
 * @addtogroup MESH
 * @{
 */
#ifndef _COMMON_UTILS_H_
#define _COMMON_UTILS_H_

/*
 * INCLUDE FILES
 ****************************************************************************************
 */
 
#include <stdint.h>

/*
 * FUNCTION DECLARATIONS
 ****************************************************************************************
 */

/**
 ****************************************************************************************
 * @brief Read an aligned 32 bit word.
 * @param[in] ptr32 The address of the first byte of the 32 bit word.
 * @return The 32 bit value.
 ****************************************************************************************
 */
static inline uint32_t gx_read32(void const *ptr32)
{
    return *((uint32_t*)ptr32);
}

/**
 ****************************************************************************************
 * @brief Read an aligned 16 bits word.
 * @param[in] ptr16 The address of the first byte of the 16 bits word.
 * @return The 16 bits value.
 ****************************************************************************************
 */
static inline uint16_t gx_read16(void const *ptr16)
{
    return *((uint16_t*)ptr16);
}

/**
 ****************************************************************************************
 * @brief Write an aligned 32 bits word.
 * @param[in] ptr32 The address of the first byte of the 32 bits word.
 * @param[in] value The value to write.
 ****************************************************************************************
 */
static inline void gx_write32(void const *ptr32, uint32_t value)
{
    *(uint32_t*)ptr32 = value;
}

/**
 ****************************************************************************************
 * @brief Write an aligned 16 bits word.
 * @param[in] ptr16 The address of the first byte of the 16 bits word.
 * @param[in] value The value to write.
 ****************************************************************************************
 */
static inline void gx_write16(void const *ptr16, uint32_t value)
{
    *(uint16_t*)ptr16 = value;
}

/**
 ****************************************************************************************
 * @brief Write a 8 bits word.
 * @param[in] ptr8 The address of the first byte of the 8 bits word.
 * @param[in] value The value to write.
 ****************************************************************************************
 */
static inline void gx_write8(void const *ptr8, uint32_t value)
{
    *(uint8_t*)ptr8 = value;
}

/**
 ****************************************************************************************
 * @brief Read a packed 16 bits word.
 * @param[in] ptr16 The address of the first byte of the 16 bits word.
 * @return The 16 bits value.
 ****************************************************************************************
 */
static inline uint16_t gx_read16p(void const *ptr16)
{
    uint16_t value = ((uint8_t *)ptr16)[0] | ((uint8_t *)ptr16)[1] << 8;
    return value;
}

/**
 ****************************************************************************************
 * @brief Read a packed 24 bits word.
 * @param[in] ptr24 The address of the first byte of the 24 bits word.
 * @return The 24 bits value.
 ****************************************************************************************
 */
static inline uint32_t gx_read24p(void const *ptr24)
{
    uint16_t addr_l, addr_h;
    addr_l = gx_read16p(ptr24);
    addr_h = *((uint8_t *)ptr24 + 2) & 0x00FF;
    return ((uint32_t)addr_l | (uint32_t)addr_h << 16);
}

/**
 ****************************************************************************************
 * @brief Write a packed 24 bits word.
 * @param[in] ptr24 The address of the first byte of the 24 bits word.
 * @param[in] value The value to write.
 ****************************************************************************************
 */
static inline void gx_write24p(void const *ptr24, uint32_t value)
{
    uint8_t *ptr=(uint8_t*)ptr24;

    *ptr++ = (uint8_t)(value&0xff);
    *ptr++ = (uint8_t)((value&0xff00)>>8);
    *ptr++ = (uint8_t)((value&0xff0000)>>16);
}

/**
 ****************************************************************************************
 * @brief Read a packed 32 bits word.
 * @param[in] ptr32 The address of the first byte of the 32 bits word.
 * @return The 32 bits value.
 ****************************************************************************************
 */
static inline uint32_t gx_read32p(void const *ptr32)
{
    uint16_t addr_l, addr_h;
    addr_l = gx_read16p(ptr32);
    addr_h = gx_read16p((uint8_t *)ptr32 + 2);
    return ((uint32_t)addr_l | (uint32_t)addr_h << 16);
}

/**
 ****************************************************************************************
 * @brief Read a packed 40 bits word.
 * @param[in] ptr40 The address of the first byte of the 40 bits word.
 * @return The 40 bits value.
 ****************************************************************************************
 */
static inline uint64_t gx_read40p(void const *ptr40)
{
    uint32_t addr_l, addr_h;
    addr_l = gx_read32p(ptr40);
    addr_h = *((uint8_t *)ptr40 + 4) & 0x00FF;
    return ((uint64_t)addr_l | (uint64_t)addr_h << 32);
}

/**
 ****************************************************************************************
 * @brief Read a packed 64 bits word.
 * @param[in] ptr64 The address of the first byte of the 64 bits word.
 * @return The 64 bits value.
 ****************************************************************************************
 */
static inline uint64_t gx_read64p(void const *ptr64)
{
    uint32_t addr_l, addr_h;
    addr_l = gx_read32p(ptr64);
    addr_h = gx_read32p((uint8_t *)ptr64 + 4);
    return ((uint64_t)addr_l | (uint64_t)addr_h << 32);
}

/**
 ****************************************************************************************
 * @brief Write a packed 32 bits word.
 * @param[in] ptr32 The address of the first byte of the 32 bits word.
 * @param[in] value The value to write.
 ****************************************************************************************
 */
static inline void gx_write32p(void const *ptr32, uint32_t value)
{
    uint8_t *ptr=(uint8_t*)ptr32;

    *ptr++ = (uint8_t)(value&0xff);
    *ptr++ = (uint8_t)((value&0xff00)>>8);
    *ptr++ = (uint8_t)((value&0xff0000)>>16);
    *ptr = (uint8_t)((value&0xff000000)>>24);
}

/**
 ****************************************************************************************
 * @brief Write a packed 40 bits word.
 * @param[in] ptr64 The address of the first byte of the 40 bits word.
 * @param[in] value The value to write.
 ****************************************************************************************
 */
static inline void gx_write40p(void const *ptr40, uint64_t value)
{
    uint8_t *ptr=(uint8_t*)ptr40;

    *ptr++ = (uint8_t)(value&0xff);
    *ptr++ = (uint8_t)((value&0xff00)>>8);
    *ptr++ = (uint8_t)((value&0xff0000)>>16);
    *ptr++ = (uint8_t)((value&0xff000000)>>24);
    *ptr = (uint8_t)((value&0xff00000000)>>32);
}

/**
 ****************************************************************************************
 * @brief Write a packed 64 bits word.
 * @param[in] ptr64 The address of the first byte of the 64 bits word.
 * @param[in] value The value to write.
 ****************************************************************************************
 */
static inline void gx_write64p(void const *ptr64, uint64_t value)
{
    void *ptr32_0=(void*)ptr64;
    void *ptr32_1=(uint8_t*)ptr64+4;

    gx_write32p((void const *)ptr32_0, value);
    gx_write32p((void const *)ptr32_1, value>>32);
}

/**
 ****************************************************************************************
 * @brief Write a packed 16 bits word.
 * @param[in] ptr16 The address of the first byte of the 16 bits word.
 * @param[in] value The value to write.
 ****************************************************************************************
 */
static inline void gx_write16p(void const *ptr16, uint16_t value)
{
    uint8_t *ptr=(uint8_t*)ptr16;

    *ptr++ = value&0xff;
    *ptr = (value&0xff00)>>8;
}


#endif /* _COMMON_UTILS_H_ */

/** @} */

