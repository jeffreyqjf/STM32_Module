/**
 ******************************************************************************
 * @file    GPIO_Init.h
 * @brief   STM32F10x GPIO 初始化函数头文件
 * @note    提供 GPIOA、GPIOB、GPIOC 以及板载指示灯初始化函数接口，
 *          通过简化函数实现快速端口配置。
 * @version 1.0
 * @date    2025-10-07
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * - 本头文件需与 GPIO_Init.c 配套使用；
 * - 在调用前请确保 RCC 时钟已开启；
 * - 默认输出速率为 50MHz；
 * - 本模块依赖 STM32 标准外设库 (stm32f10x_stdperiph_lib)。
 ******************************************************************************
 */

#ifndef __GPIO_INIT_H
#define __GPIO_INIT_H

#include "stm32f10x.h"  ///< STM32 标准外设库头文件

#ifdef __cplusplus
extern "C" {
#endif


void GPIOA_Init(GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin_x);
void GPIOB_Init(GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin_x);
void GPIOC_Init(GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin_x);
void Indicator_Light_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __GPIO_INIT_H */
