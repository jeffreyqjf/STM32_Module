/**
 ******************************************************************************
 * @file    Timer.h
 * @brief   定时器初始化函数头文件
 * @version 1.0
 * @date    2025-10-07
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * - 默认配置 TIM2 为内部时钟源；
 * - 修改定时参数请在 TIMER.c 中调整预分频器和自动重装值；
 * - 使用前请确保 RCC 时钟和 NVIC 已初始化；
 ******************************************************************************
 */

#ifndef __TIMER_H
#define __TIMER_H

#include "stm32f10x.h"  ///< STM32 标准外设库头文件

#ifdef __cplusplus
extern "C" {
#endif

void Timer_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __TIMER_H */
