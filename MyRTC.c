/**
 ******************************************************************************
 * @file    MyRTC.c
 * @brief   提供 STM32F10x RTC 初始化函数
 * @version 1.0
 * @date    2025-10-07
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * 本文件依赖 STM32 标准外设库 (stm32f10x_stdperiph_lib)。
 * 默认使用外部低速晶振 (LSE, 32.768kHz) 作为 RTC 时钟源。
 * 若需使用 LSI 或 HSE，请修改 `RCC_RTCCLKConfig()` 相关配置。
 ******************************************************************************
 */

#include "stm32f10x.h"   ///< STM32 标准外设库头文件

/**
 * @brief  初始化实时时钟 (RTC)
 * @note   该函数启用 LSE 作为时钟源，并设置分频系数以产生 1Hz 时基。
 *         初始化完成后 RTC 计数器从 0 开始计时。
 * @retval 无
 */
void MyRTC_Init(void)
{
    /* 使能电源与备份寄存器时钟 */
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_PWR, ENABLE);
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_BKP, ENABLE);
    
    /* 允许访问备份域 */
    PWR_BackupAccessCmd(ENABLE);
    
    /* 启动外部低速晶振 LSE 并等待稳定 */
    RCC_LSEConfig(RCC_LSE_ON);
    while (RCC_GetFlagStatus(RCC_FLAG_LSERDY) != SET);
    
    /* 选择 LSE 作为 RTC 时钟源并启用 RTC */
    RCC_RTCCLKConfig(RCC_RTCCLKSource_LSE);
    RCC_RTCCLKCmd(ENABLE);
    
    /* 同步与等待上一次任务完成 */
    RTC_WaitForSynchro();
    RTC_WaitForLastTask();
    
    /* 设置分频系数：32768Hz / 32768 = 1Hz */
    RTC_SetPrescaler(32768 - 1);
    RTC_WaitForLastTask();
    
    /* 清零计数器 */
    RTC_SetCounter(0);
    RTC_WaitForLastTask();
}
