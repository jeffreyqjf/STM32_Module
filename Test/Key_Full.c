#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "GPIO_Init.h"
#include "OLED.h"
#include "EXTI_Init.h"
#include "Timer.h"
#include "PWM.h"
#include "MyAD.h"
#include "MyRTC.h"
#include "Key_Full.h"


int main(void){
	Key_Init();
	OLED_Init();
	Indicator_Light_Init();
	GPIO_SetBits(GPIOC, GPIO_Pin_13);
	/* HOLD test */
//	while(1){
//		if(Key_Check(KEY_HOLD)){
//			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//		}else{
//			GPIO_SetBits(GPIOC, GPIO_Pin_13);
//		}
//	}
	
	/* DOWM test */
//	while(1){
//		if(Key_Check(KEY_DOWN)){
//			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//			Delay_ms(500);
//		}else{
//			GPIO_SetBits(GPIOC, GPIO_Pin_13);
//		}
//	}

	/* UP test */
//	while(1){
//		if(Key_Check(KEY_UP)){
//			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//			Delay_ms(500);
//		}else{
//			GPIO_SetBits(GPIOC, GPIO_Pin_13);
//		}
//	}

  	/* SINGLE test */
//	while(1){
//		if(Key_Check(KEY_SINGLE)){
//			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//			Delay_ms(500);
//		}else{
//			GPIO_SetBits(GPIOC, GPIO_Pin_13);
//		}
//	}

  	/* DOUBLE test */
//	while(1){
//		if(Key_Check(KEY_DOUBLE)){
//			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//			Delay_ms(500);
//		}else{
//			GPIO_SetBits(GPIOC, GPIO_Pin_13);
//		}
//	}

	/* LONG test */
//	while(1){
//		if(Key_Check(KEY_LONG)){
//			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//			Delay_ms(500);
//		}else{
//			GPIO_SetBits(GPIOC, GPIO_Pin_13);
//		}
//	}

	/* REPEAT test */
//	while(1){
//		if(Key_Check(KEY_REPEAT)){
//			GPIO_ResetBits(GPIOC, GPIO_Pin_13);
//			Delay_ms(1);
//		}else{
//			GPIO_SetBits(GPIOC, GPIO_Pin_13);
//		}
//	}

}


void TIM1_UP_IRQHandler(void){
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET){
		Key_Tick();
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}
