/**
 ******************************************************************************
 * @file    GPIO_Init.c
 * @brief   提供 STM32F10x GPIO 初始化简化函数
 * @note    本文件封装了 GPIOA、GPIOB、GPIOC 的初始化函数，
 *          通过传入引脚号与模式参数即可快速配置对应端口。
 * @version 1.0
 * @date    2025-10-07
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * 本文件依赖 STM32 标准外设库 (stm32f10x_stdperiph_lib)。
 * 在使用前请确保 RCC 与 GPIO 模块已正确配置。
 ******************************************************************************
 */

#include "stm32f10x.h"  ///< STM32 标准外设库头文件

/**
 * @brief  初始化 GPIOA 端口的指定引脚
 * @param  GPIO_Mode: GPIO 模式选择（如 GPIO_Mode_Out_PP、GPIO_Mode_IPU 等）
 * @param  GPIO_Pin_x: 引脚号（如 GPIO_Pin_0、GPIO_Pin_1、GPIO_Pin_13 等）
 * @retval 无
 * @note   自动开启 GPIOA 时钟，并将引脚速率设置为 50MHz。
 */
void GPIOA_Init(GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin_x) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
}

/**
 * @brief  初始化 GPIOB 端口的指定引脚
 * @param  GPIO_Mode: GPIO 模式选择（如 GPIO_Mode_Out_PP、GPIO_Mode_IPU 等）
 * @param  GPIO_Pin_x: 引脚号（如 GPIO_Pin_0、GPIO_Pin_1、GPIO_Pin_13 等）
 * @retval 无
 * @note   自动开启 GPIOB 时钟，并将引脚速率设置为 50MHz。
 */
void GPIOB_Init(GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin_x) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOB, &GPIO_InitStructure);
}

/**
 * @brief  初始化 GPIOC 端口的指定引脚
 * @param  GPIO_Mode: GPIO 模式选择（如 GPIO_Mode_Out_PP、GPIO_Mode_IPU 等）
 * @param  GPIO_Pin_x: 引脚号（如 GPIO_Pin_13、GPIO_Pin_14 等）
 * @retval 无
 * @note   自动开启 GPIOC 时钟，并将引脚速率设置为 50MHz。
 */
void GPIOC_Init(GPIOMode_TypeDef GPIO_Mode, uint16_t GPIO_Pin_x) {
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);
    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_x;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOC, &GPIO_InitStructure);
}

/**
 * @brief  初始化板载指示灯对应的 GPIO 引脚
 * @retval 无
 * @note   默认为 PC13 推挽输出模式，适用于大多数 STM32 最小系统板上的 LED。
 * @see    GPIOC_Init()
 */
void Indicator_Light_Init(void) {
    GPIOC_Init(GPIO_Mode_Out_PP, GPIO_Pin_13);
}
