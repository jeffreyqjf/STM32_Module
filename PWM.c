/**
 ******************************************************************************
 * @file    PWM.c
 * @brief   TIM2 PWM 输出初始化函数实现文件
 * @version 1.0
 * @date    2025-10-07
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * - 本文件默认使用 TIM2_CH1 (PA0) 与 TIM2_CH2 (PA1) 输出 PWM 信号；
 * - PWM 频率 = 72MHz / (PSC + 1) / (ARR + 1)；
 * - 可通过修改 ARR 和 CCRx 调整周期与占空比；
 * - 在调用前请确保 GPIOA 和 TIM2 的 RCC 已正确配置。
 ******************************************************************************
 */

#include "stm32f10x.h"  ///< STM32 标准外设库头文件

/**
 * @brief  TIM2 PWM 输出初始化函数
 * @note   默认使用 PA0 -> CH1，PA1 -> CH2
 * @retval 无
 */
void PWM_Init(void)
{
    /* 打开时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);

    /* GPIO 配置 */
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode  = GPIO_Mode_AF_PP;   // 复用推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0;          // TIM2_CH1
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_1;          // TIM2_CH2
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /* 选择内部时钟 */
    TIM_InternalClockConfig(TIM2);

    /* 定时器基本配置 */
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision      = TIM_CKD_DIV1;
    TIM_TimeBaseInitStructure.TIM_CounterMode        = TIM_CounterMode_Up;
    TIM_TimeBaseInitStructure.TIM_Period             = 100 - 1;   // ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler          = 720 - 1;   // PSC -> 100kHz 计数频率
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter  = 0x00;
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    /* 输出比较初始化（PWM 模式） */
    TIM_OCInitTypeDef TIM_OCInitStructure;
    TIM_OCStructInit(&TIM_OCInitStructure);
    TIM_OCInitStructure.TIM_OCMode      = TIM_OCMode_PWM1;
    TIM_OCInitStructure.TIM_OCPolarity  = TIM_OCPolarity_High;
    TIM_OCInitStructure.TIM_OutputState = TIM_OutputState_Enable;

    TIM_OCInitStructure.TIM_Pulse = 0;  // 初始占空比 0%
    TIM_OC1Init(TIM2, &TIM_OCInitStructure);

    TIM_OCInitStructure.TIM_Pulse = 0;
    TIM_OC2Init(TIM2, &TIM_OCInitStructure);

    /* 使能定时器 */
    TIM_Cmd(TIM2, ENABLE);
}
