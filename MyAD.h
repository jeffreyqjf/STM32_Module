/**
 ******************************************************************************
 * @file    MyAD.h
 * @brief   提供 STM32F10x ADC 初始化与采样函数声明
 * @version 1.0
 * @date    2025-10-07
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * 本文件依赖 STM32 标准外设库 (stm32f10x_stdperiph_lib)。
 * 默认使用 ADC1 通道2（PA2）作为模拟输入引脚。
 * 若需更改通道或引脚，请修改对应的 GPIO 与通道配置。
 *
 * 本头文件适用于 C/C++ 环境，可直接被 C++ 工程引用。
 ******************************************************************************
 */

#ifndef __MYAD_H
#define __MYAD_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"   ///< STM32 标准外设库头文件

void MyADC_Init(void);
uint16_t Get_AD_Vaule(void);

#ifdef __cplusplus
}
#endif

#endif /* __MYAD_H */
