/**
 ******************************************************************************
 * @file    Timer.c
 * @brief   提供 STM32F10x 定时器（TIM2）初始化封装函数
 * @note    该模块封装了 TIM2 定时中断的初始化与中断服务函数，
 *          默认配置为内部时钟、向上计数、周期性更新中断。
 * @version 1.0
 * @date    2025-10-07
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * - 本文件依赖 STM32 标准外设库 (stm32f10x_stdperiph_lib)；
 * - 本示例使用 TIM2，如需更换其他定时器，请修改对应寄存器；
 * - 默认中断周期约为 1 秒（基于 72MHz 主频，PSC=7200，ARR=10000）。
 ******************************************************************************
 */

#include "stm32f10x.h"  ///< STM32 标准外设库头文件

/**
 * @brief  初始化 TIM2 为定时中断模式
 * @retval 无
 * @note
 * - 自动开启 TIM2 时钟；
 * - 使用内部时钟源；
 * - 计数模式为向上计数；
 * - 触发“更新中断 (TIM_IT_Update)”；
 * - 中断优先级组为 NVIC_PriorityGroup_2。
 *
 * @par TIM_IT_Update 说明：
 * TIM_IT_Update 表示“更新中断源”，当计数器溢出（CNT 从 ARR 回到 0）时触发。
 * 通常用于周期性任务，如 LED 闪烁、计时、任务调度等。
 */
void Timer_Init(void)
{
    /*-------------------- 开启 TIM2 时钟 --------------------*/
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);

    /*-------------------- 选择内部时钟 --------------------*/
    TIM_InternalClockConfig(TIM2);

    /*-------------------- 定时器基础配置 --------------------*/
    TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
    TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;       // 不分频
    TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;   // 向上计数
    TIM_TimeBaseInitStructure.TIM_Period = 10000 - 1;                 // 自动重装载值 ARR
    TIM_TimeBaseInitStructure.TIM_Prescaler = 7200 - 1;               // 预分频值 PSC
    TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0x00;           // 不使用重复计数
    TIM_TimeBaseInit(TIM2, &TIM_TimeBaseInitStructure);

    /*-------------------- 使能更新中断 --------------------*/
    TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);  // 计数溢出时触发中断

    /*-------------------- NVIC 中断优先级配置 --------------------*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
    NVIC_Init(&NVIC_InitStructure);

    /*-------------------- 启动定时器 --------------------*/
    TIM_Cmd(TIM2, ENABLE);
}

/**
 * @brief  TIM2 中断服务函数
 * @retval 无
 * @note
 * - 当 TIM2 溢出产生“更新中断”时调用；
 * - 用户可在中断中加入周期性任务；
 * - 清除中断标志位是必要操作，否则中断会重复触发。
 */
void TIM2_IRQHandler(void)
{
    if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET)
    {
        /*-------------------- 用户代码区 --------------------*/
        // 示例：周期性执行任务
        // TODO: 用户可在此添加中断逻辑
        /*----------------------------------------------------*/

        /* 清除中断标志位，防止重复进入 */
        TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
    }
}
