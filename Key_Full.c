/**
 ******************************************************************************
 * @file    Key_Full.c
 * @brief   多功能按键处理模块（支持单击、双击、长按、连击等）
 * @version 1.0
 * @date    2025-10-09
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * 本文件实现基于 STM32F10x 的多功能按键扫描逻辑，支持：
 * - 单击（SINGLE）
 * - 双击（DOUBLE）
 * - 长按（LONG）
 * - 连续按下（REPEAT）
 * - 按下（DOWN）
 * - 松开（UP）
 * - 按住状态（HOLD）
 *
 * 默认使用 GPIOA 的 PA2、PA3 引脚作为输入按键，
 * 采用定时器 TIM1 进行周期扫描与防抖。
 *
 * 建议在 TIM1 定时中断或主循环中周期调用 `Key_Tick()`。
 *
 * 依赖：
 * - stm32f10x.h
 * - GPIO_Init.h
 * - Key_Full.h
 ******************************************************************************
 */

#include "stm32f10x.h"                  // Device header
#include "GPIO_Init.h"
#include "Key_Full.h"

/* 定义按键状态常量 */
#define KEY_PRESSED       1     /**< 按键按下状态 */
#define KEY_UNPRESSED     0     /**< 按键未按下状态 */

/* 定义各种按键时间参数（单位：ms） */
#define KEY_TIME_LONG     2000  /**< 长按判定时间 */
#define KEY_TIME_DOUBLE   200   /**< 双击间隔时间 */
#define KEY_TIME_REPEAT   100   /**< 长按连击间隔时间 */

/* 按键标志变量（位标志寄存） */
uint8_t Key_Flag = 0;

/**
 * @brief  初始化按键与定时器
 * @note
 * - 配置 PA2 和 PA3 为上拉输入模式；
 * - 初始化 TIM1 产生周期中断；
 * - 启用 NVIC 对 TIM1 的中断响应；
 * - 开启定时器计数。
 */
void Key_Init(void){
	
	// GPIO 初始化
	GPIOA_Init(GPIO_Mode_IPU, GPIO_Pin_2 | GPIO_Pin_3);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	// 切换时钟源
	TIM_InternalClockConfig(TIM1);
	
	// TIM 基本定时配置
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1; // ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1; // PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0x00; 
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
	// 允许更新中断（溢出中断）
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE);
	
	// NVIC 中断优先级配置
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	// 启动 TIM1
	TIM_Cmd(TIM1, ENABLE);
}

/**
 * @brief  获取当前按键状态
 * @retval KEY_PRESSED：按键按下
 * @retval KEY_UNPRESSED：按键未按下
 */
uint8_t Key_GetState(void){
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0){
		return KEY_PRESSED;
	}
	return KEY_UNPRESSED;
}

/**
 * @brief  检查特定按键事件是否发生
 * @param  Flag 事件标志（如 KEY_DOWN、KEY_UP、KEY_SINGLE 等）
 * @retval 1：事件发生
 * @retval 0：事件未发生
 * @note 对于非持续状态事件（如 DOWN/UP/SINGLE/DOUBLE），调用后标志会自动清除。
 */
uint8_t Key_Check(uint8_t Flag){
	if(Key_Flag & Flag){
		if(Flag != KEY_HOLD){
			Key_Flag &= ~Flag;
		}
		return 1;
	}
	return 0;
}

/**
 * @brief  按键状态扫描与事件判定
 * @note
 * - 建议每 20ms 调用一次；
 * - 内部实现多态状态机，判断单击、双击、长按、连击；
 * - 各事件通过 `Key_Flag` 设置标志位，由 `Key_Check()` 读取。
 */
void Key_Tick(void){
	static uint8_t Count = 0;
	static uint8_t CurrentState, PrevState;
	static uint8_t State = 0;
	static int16_t Time = 0;
	
	if(Time > 0){
		Time--;
	}
	
	if(Count >= 20){
		Count = 0;
		
		PrevState = CurrentState;
		CurrentState = Key_GetState();
		
		// HOLD 检测
		if(CurrentState == KEY_PRESSED){
			Key_Flag |= KEY_HOLD;
		}else{
			Key_Flag &= ~KEY_HOLD;
		}
		
		// 边沿检测：按下/松开
		if(CurrentState == KEY_PRESSED && PrevState == KEY_UNPRESSED){
			Key_Flag |= KEY_DOWN;
		}
		if(CurrentState == KEY_UNPRESSED && PrevState == KEY_PRESSED){
			Key_Flag |= KEY_UP;
		}
		
		// 状态机逻辑
		switch(State){
			case 0:
				if(CurrentState == KEY_PRESSED){
					State = 1;
					Time = KEY_TIME_LONG;
				}
				break;
				
			case 1:
				if(CurrentState == KEY_UNPRESSED){
					Time = KEY_TIME_DOUBLE; // 等待双击
					State = 2; 
				}else if(Time == 0){
					Key_Flag |= KEY_LONG; // 长按事件
					Time = KEY_TIME_REPEAT;
					State = 4; // 进入连击状态
				}
				break;
				
			case 2:
				if(CurrentState == KEY_PRESSED){
					Key_Flag |= KEY_DOUBLE; // 双击
					State = 3;
				}else if(Time == 0){
					Key_Flag |= KEY_SINGLE; // 单击
					State = 0;
				}
				break;
				
			case 3:
				if(CurrentState == KEY_UNPRESSED){
					State = 0;
				}
				break;
			
			case 4:
				if(CurrentState == KEY_UNPRESSED){
					State = 0;
				}else if(Time == 0){
					Key_Flag |= KEY_REPEAT; // 长按重复
					Time = KEY_TIME_REPEAT;
					State = 4;
				}
				break;
		}
	}
	Count++;
}

// void TIM1_IRQHandler(void){
// 	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET){
// 		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
// 	}
// }
