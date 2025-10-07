/**
 ******************************************************************************
 * @file    MyAD.c
 * @brief   提供 STM32F10x ADC 初始化与采样函数
 * @version 1.0
 * @date    2025-10-07
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * 本文件依赖 STM32 标准外设库 (stm32f10x_stdperiph_lib)。
 * 默认使用 ADC1 通道2（PA2）进行单次采样。
 * 如需修改通道，请调整 GPIO 与 ADC_RegularChannelConfig 参数。
 ******************************************************************************
 */

#include "stm32f10x.h"                  ///< STM32 标准外设库头文件
#include "GPIO_Init.h"                  ///< GPIO 初始化头文件

/**
 * @brief  初始化 ADC1 模块与输入引脚
 * @note   默认配置为 PA2（ADC1 通道2），单次转换模式。
 * @retval 无
 */
void MyADC_Init(void)
{
    // GPIO 初始化
    GPIOA_Init(GPIO_Mode_AIN, GPIO_Pin_2);
    
    // ADC 时钟配置 (PCLK2/6)
    RCC_ADCCLKConfig(RCC_PCLK2_Div6);
    
    // ADC 通道配置
    ADC_RegularChannelConfig(ADC1, ADC_Channel_0, 1, ADC_SampleTime_55Cycles5);
    
    // ADC 初始化结构体
    ADC_InitTypeDef ADC_InitStructure;
    ADC_InitStructure.ADC_Mode = ADC_Mode_Independent;
    ADC_InitStructure.ADC_ScanConvMode = DISABLE;
    ADC_InitStructure.ADC_ContinuousConvMode = DISABLE;
    ADC_InitStructure.ADC_DataAlign = ADC_DataAlign_Right;
    ADC_InitStructure.ADC_ExternalTrigConv = ADC_ExternalTrigConv_None;
    ADC_InitStructure.ADC_NbrOfChannel = 1;
    ADC_Init(ADC1, &ADC_InitStructure);
    
    ADC_Cmd(ADC1, ENABLE);
    // ADC 不需要 NVIC 初始化，因为本例未启用 ADC 中断
    
    // 校准 ADC
    ADC_ResetCalibration(ADC1);
    while (ADC_GetResetCalibrationStatus(ADC1));
    ADC_StartCalibration(ADC1);
    while (ADC_GetCalibrationStatus(ADC1));
}

/**
 * @brief  获取 ADC 单次转换的结果
 * @retval 16位 ADC 转换结果 (0~4095)
 * @note   本函数使用软件触发方式启动转换。
 */
uint16_t Get_AD_Vaule(void)
{
    ADC_SoftwareStartConvCmd(ADC1, ENABLE);
    while (ADC_GetFlagStatus(ADC1, ADC_FLAG_EOC) == RESET);
    // while( ADC_GetSoftwareStartConvStatus(ADC1) == SET);
    // OLED_ShowNum(1, 1, ADC_GetConversionValue(ADC1), 6);
    return ADC_GetConversionValue(ADC1);
}
