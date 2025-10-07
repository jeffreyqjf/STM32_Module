/**
 ******************************************************************************
 * @file    EXIT_Init.c
 * @brief   提供 STM32F10x 外部中断 GPIO 初始化函数封装
 * @note    支持 GPIOA、GPIOB、GPIOC 引脚快速配置为外部中断输入模式，
 *          根据引脚编号自动映射 EXTI 线路与 NVIC 通道。
 * @version 1.0
 * @date    2025-10-07
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * - 本文件依赖 STM32 标准外设库 (stm32f10x_stdperiph_lib)。
 * - 在使用前请确保系统时钟、RCC 与 AFIO 已正确配置。
 * - 默认中断触发方式为下降沿触发 (Falling edge)。
 ******************************************************************************
 */

#include "stm32f10x.h"  ///< STM32 标准外设库头文件

/**
 * @brief  初始化 GPIOA 指定引脚为外部中断输入模式
 * @param  x: 引脚编号 (0~15)
 * @retval 无
 * @note
 * - 自动开启 GPIOA 与 AFIO 时钟；
 * - 默认上拉输入模式；
 * - 默认下降沿触发；
 * - 自动判断对应的 NVIC 通道。
 */
void EXIT_GPIOA_Init(uint16_t x)
{
    uint16_t pin = (1 << x);
    uint32_t EXTIx_IRQn = 0;

    /*-------------------- 确定中断通道 --------------------*/
    if (x <= 4)
        EXTIx_IRQn = EXTI0_IRQn + x;
    else if (x <= 9)
        EXTIx_IRQn = EXTI9_5_IRQn;
    else
        EXTIx_IRQn = EXTI15_10_IRQn;

    /*-------------------- 时钟开启 --------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO, ENABLE);

    /*-------------------- GPIO 初始化 --------------------*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;         // 上拉输入
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    /*-------------------- EXTI 线路配置 --------------------*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOA, x);

    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = (1 << x);
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling; // 下降沿触发
    EXTI_Init(&EXTI_InitStructure);

    /*-------------------- NVIC 配置 --------------------*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTIx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief  初始化 GPIOB 指定引脚为外部中断输入模式
 * @param  x: 引脚编号 (0~15)
 * @retval 无
 * @note
 * - 自动开启 GPIOB 与 AFIO 时钟；
 * - 默认上拉输入模式；
 * - 默认下降沿触发；
 * - 自动判断对应的 NVIC 通道。
 */
void EXIT_GPIOB_Init(uint16_t x)
{
    uint16_t pin = (1 << x);
    uint32_t EXTIx_IRQn = 0;

    /*-------------------- 确定中断通道 --------------------*/
    if (x <= 4)
        EXTIx_IRQn = EXTI0_IRQn + x;
    else if (x <= 9)
        EXTIx_IRQn = EXTI9_5_IRQn;
    else
        EXTIx_IRQn = EXTI15_10_IRQn;

    /*-------------------- 时钟开启 --------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB | RCC_APB2Periph_AFIO, ENABLE);

    /*-------------------- GPIO 初始化 --------------------*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*-------------------- EXTI 线路配置 --------------------*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, x);

    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = (1 << x);
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);

    /*-------------------- NVIC 配置 --------------------*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTIx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief  初始化 GPIOC 指定引脚为外部中断输入模式
 * @param  x: 引脚编号 (0~15)
 * @retval 无
 * @note
 * - 自动开启 GPIOC 与 AFIO 时钟；
 * - 默认上拉输入模式；
 * - 默认下降沿触发；
 * - 自动判断对应的 NVIC 通道。
 */
void EXIT_GPIOC_Init(uint16_t x)
{
    uint16_t pin = (1 << x);
    uint32_t EXTIx_IRQn = 0;

    /*-------------------- 确定中断通道 --------------------*/
    if (x <= 4)
        EXTIx_IRQn = EXTI0_IRQn + x;
    else if (x <= 9)
        EXTIx_IRQn = EXTI9_5_IRQn;
    else
        EXTIx_IRQn = EXTI15_10_IRQn;

    /*-------------------- 时钟开启 --------------------*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC | RCC_APB2Periph_AFIO, ENABLE);

    /*-------------------- GPIO 初始化 --------------------*/
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Pin = pin;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IPU;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);

    /*-------------------- EXTI 线路配置 --------------------*/
    GPIO_EXTILineConfig(GPIO_PortSourceGPIOC, x);

    EXTI_InitTypeDef EXTI_InitStructure;
    EXTI_InitStructure.EXTI_Line = (1 << x);
    EXTI_InitStructure.EXTI_LineCmd = ENABLE;
    EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
    EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
    EXTI_Init(&EXTI_InitStructure);

    /*-------------------- NVIC 配置 --------------------*/
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);

    NVIC_InitTypeDef NVIC_InitStructure;
    NVIC_InitStructure.NVIC_IRQChannel = EXTIx_IRQn;
    NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
    NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
    NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
    NVIC_Init(&NVIC_InitStructure);
}

/**
 * @brief  EXTI9_5 中断服务函数示例
 * @retval 无
 * @note
 * - 本函数示例演示如何处理中断事件；
 * - 用户可在其中加入自定义逻辑。
 */
void EXTI9_5_IRQHandler(void)
{
    if (EXTI_GetITStatus(EXTI_Line5) == SET)
    {
        /*-------------------- 用户代码区 --------------------*/
        // 示例：中断响应处理逻辑
        // TODO: 用户可根据实际需要修改
        /*----------------------------------------------------*/

        EXTI_ClearITPendingBit(EXTI_Line5); // 清除中断标志位
    }
}
