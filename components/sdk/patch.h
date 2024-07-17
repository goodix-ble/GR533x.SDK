#ifndef __PATCH_H_
#define __PATCH_H_

/**
 ****************************************************************************************
 *
 * @file patch.h
 *
 * @brief offer the interface for the patch function based on the FPB of the cortex arm-m4;
 *
 * Copyright(C) 2016-2018, Shenzhen Goodix Technology Co., Ltd
 * All Rights Reserved
 *
 ****************************************************************************************
 */

/**
  * @brief  Register the path function to the hardware patch.
  * @param  patch_index  the patch index.
  * @param  func_addr    the address of the patch function.
  *
  * @retval None
  */
void fpb_register_patch_function(int patch_index, uint32_t func_addr);

#endif  // __PATCH_H_
