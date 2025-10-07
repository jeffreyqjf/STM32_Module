/**
 ******************************************************************************
 * @file    PWM.h
 * @brief   TIM2 PWM 初始化函数头文件
 * @note    本模块默认使用 TIM2_CH1 (PA0) 与 TIM2_CH2 (PA1) 输出 PWM 信号。
 * @version 1.0
 * @date    2025-10-07
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * - PWM 频率 = Fclk / (PSC + 1) / (ARR + 1)，Fclk 为定时器时钟（示例为 72MHz）。
 * - 修改 PWM 参数请在对应的实现文件中调整 ARR、PSC 与 CCRx。
 * - 调用前请确保 GPIO 与 TIM 的 RCC 时钟已开启，且引脚配置为复用推挽（AF_PP）。
 ******************************************************************************
 */

#ifndef __PWM_H
#define __PWM_H

#include "stm32f10x.h"  ///< STM32 标准外设库头文件

#ifdef __cplusplus
extern "C" {
#endif

void PWM_Init(void);

#ifdef __cplusplus
}
#endif

#endif /* __PWM_H */
