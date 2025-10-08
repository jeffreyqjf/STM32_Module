/**
 ******************************************************************************
 * @file    MyRTC.h
 * @brief   实时时钟 (RTC) 初始化函数声明
 * @version 1.0
 * @date    2025-10-07
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * 本文件依赖 STM32F10x 标准外设库 (stm32f10x.h)。
 * 默认使用外部低速晶振 (LSE, 32.768 kHz) 作为 RTC 时钟源。
 * 若需使用其他时钟源，请修改 MyRTC.c 中的 RCC_RTCCLKConfig()。
 ******************************************************************************
 */

#ifndef __MYRTC_H
#define __MYRTC_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"   ///< 依赖 STM32 标准外设库

/**
 * @brief  初始化实时时钟模块 (RTC)
 * @note   初始化后，RTC 计数器从 0 开始，以 1Hz 递增。
 */
void MyRTC_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __MYRTC_H */
