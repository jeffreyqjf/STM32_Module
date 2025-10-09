/**
 ******************************************************************************
 * @file    Key.h
 * @brief   按键输入模块函数声明
 * @version 1.0
 * @date    2025-10-09
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * 本模块使用 GPIOA (PA2、PA3) 作为输入引脚，并支持定时扫描防抖。
 * 若启用定时中断，请确保在主循环或定时器中周期调用 Key_Tick()。
 *
 * 依赖：
 * - stm32f10x.h
 * - GPIO_Init.h
 ******************************************************************************
 */

#ifndef __KEY_H
#define __KEY_H

#ifdef __cplusplus
extern "C" {
#endif


void Key_Init(void);
uint8_t Key_GetNum(void);
uint8_t Key_GetState(void);
void Key_Tick(void);

#ifdef __cplusplus
}
#endif

#endif /* __KEY_H */
