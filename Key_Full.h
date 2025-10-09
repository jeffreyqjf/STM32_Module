/**
 ******************************************************************************
 * @file    Key_Full.h
 * @brief   STM32F10x 按键输入处理模块头文件
 * @note    声明按键初始化、状态检测与扫描处理函数接口。
 * @version 1.0
 * @date    2025-10-09
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * - 本头文件需与 Key_Full.c 搭配使用；
 * - 调用前请确保 GPIO 和定时器时钟已正确初始化；
 * - 推荐在 SysTick 或定时器中周期性调用 Key_Tick() 函数实现去抖与状态检测。
 ******************************************************************************
 */

#ifndef __KEY_FULL_H
#define __KEY_FULL_H

#include "stm32f10x.h"  ///< STM32 标准外设库头文件

#ifdef __cplusplus
extern "C" {
#endif

/* 按键状态标志定义 ---------------------------------------------------------*/
#define KEY_HOLD     0x01  ///< 按键持续按下状态
#define KEY_DOWN     0x02  ///< 按键按下瞬间
#define KEY_UP       0x04  ///< 按键释放瞬间
#define KEY_SINGLE   0x08  ///< 单击
#define KEY_DOUBLE   0x10  ///< 双击
#define KEY_LONG     0x20  ///< 长按
#define KEY_REPEAT   0x40  ///< 连续按压（重复触发）

/* 函数声明 -----------------------------------------------------------------*/
void Key_Init(void);
uint8_t Key_GetState(void);
uint8_t Key_Check(uint8_t Flag);
void Key_Tick(void);

#ifdef __cplusplus
}
#endif

#endif /* __KEY_FULL_H */
