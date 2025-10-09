/**
 ******************************************************************************
 * @file    Key.c
 * @brief   按键输入模块：实现按键初始化、检测与定时扫描
 * @version 1.0
 * @date    2025-10-09
 * @author  Jeffrey
 ******************************************************************************
 * @attention
 * 本模块使用 TIM1 定时器实现周期性按键扫描与防抖处理。
 * 按键默认连接至 GPIOA 引脚 (PA2, PA3)，采用上拉输入模式。
 *
 * 若要扩展更多按键，可在 Key_GetState() 中增加引脚检测逻辑。
 ******************************************************************************
 */

#include "stm32f10x.h"                  // Device header
#include "GPIO_Init.h"


/** 
 * @brief  当前检测到的按键编号
 * @note   该变量在 Key_Tick() 内部设置，在 Key_GetNum() 中读取并清零。
 */
uint8_t Key_Num = 0;


/**
 * @brief  按键初始化函数
 * @note   初始化 GPIOA (PA2, PA3) 为上拉输入，并配置 TIM1 定时中断。
 * @retval 无
 */
void Key_Init(void){
	
	// GPIO Init
	GPIOA_Init(GPIO_Mode_IPU, GPIO_Pin_2 | GPIO_Pin_3);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	
	// switch Clock
	TIM_InternalClockConfig(TIM1);
	
	// TIM(Timer) init
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInitStructure;
	TIM_TimeBaseInitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TIM_TimeBaseInitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TIM_TimeBaseInitStructure.TIM_Period = 1000 - 1; // ARR
	TIM_TimeBaseInitStructure.TIM_Prescaler = 72 - 1; // PSC
	TIM_TimeBaseInitStructure.TIM_RepetitionCounter = 0x00; // not use 
	TIM_TimeBaseInit(TIM1, &TIM_TimeBaseInitStructure);
	
	TIM_ITConfig(TIM1, TIM_IT_Update, ENABLE); // TIM_IT_Update: 溢出中断
	
	// NVIC init
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM1_UP_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	// Turn up TIM1
	TIM_Cmd(TIM1,ENABLE);
}


/**
 * @brief  获取按键编号
 * @retval 若有新按键事件返回按键号 (1, 2, ...)，否则返回 0。
 * @note   每次调用后 Key_Num 会被清零。
 */
uint8_t Key_GetNum(void){
	uint8_t Tmp = 0;
	if(Key_Num){
		Tmp = Key_Num;
		Key_Num = 0;
		return Tmp;
	}
	return 0;
}


/**
 * @brief  获取当前按键状态
 * @retval 当前按下的按键编号：
 *         - 1：PA2 被按下  
 *         - 2：PA3 被按下  
 *         - 0：无按键按下
 */
uint8_t Key_GetState(void){
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_2) == 0){ // could in define
		return 1;
	}
	if(GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_3) == 0){ // could in define
		return 2;
	}
	return 0;
}


/**
 * @brief  定时扫描函数
 * @note   应在 TIM1 中断或定时任务中周期调用。
 *         每约 20 次计数检测一次按键状态，用于消抖与事件识别。
 */
void Key_Tick(void){
	static uint8_t Count = 0;
	static uint8_t CurrentState, PrevState;
	
	if(Count >= 20){
		Count = 0;
		
		PrevState = CurrentState;
		CurrentState = Key_GetState();
		if(PrevState != 0 && CurrentState == 0){
			Key_Num = PrevState;
		}
	}
	Count ++;
}


///**
// * @brief  TIM1 更新中断服务函数（若使用软件扫描可启用）
// */
//void TIM1_IRQHandler(void){
//	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET){
//		
//		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
//	}
//}
