/**
 ******************************************************************************
 * @file    EXIT_GPIO_Init.h
 * @brief   STM32F10x 外部中断 GPIO 初始化函数头文件
 * @note    声明 GPIOA、GPIOB、GPIOC 外部中断输入初始化函数接口。
 * @version 1.0
 * @date    2025-10-07
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * - 本头文件需与 EXIT_GPIO_Init.c 搭配使用；
 * - 在调用函数前，请确保 RCC 时钟与 NVIC 中断优先级组已正确配置；
 * - 需包含标准外设库头文件 "stm32f10x.h"。
 ******************************************************************************
 */

#ifndef __EXIT_INIT_H
#define __EXIT_INIT_H

#include "stm32f10x.h"  ///< STM32 标准外设库头文件

#ifdef __cplusplus
extern "C" {
#endif


void EXIT_GPIOA_Init(uint16_t x);
void EXIT_GPIOB_Init(uint16_t x);
void EXIT_GPIOC_Init(uint16_t x);

#ifdef __cplusplus
}
#endif

#endif /* __EXIT_INIT_H */
