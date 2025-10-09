#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "GPIO_Init.h"
#include "OLED.h"
#include "EXTI_Init.h"
#include "Timer.h"
#include "PWM.h"
#include "MyAD.h"
#include "MyRTC.h"
#include "Key.h"

uint16_t i = 0;
int main(void){
	Key_Init();
	OLED_Init();
	
	uint8_t Count = 0;
	uint8_t Key_Num = 0;

	while(1){
		Key_Num = Key_GetNum();
		if(Key_Num == 1){
			Count += 1;
		}else if(Key_Num == 2){
			Count += 10;
		}
		OLED_ShowNum(0, 0, Count, 3, OLED_8X16);
		OLED_ShowNum(0, 20, i++, 5, OLED_8X16);
		OLED_Update();
	}
}


void TIM1_UP_IRQHandler(void){
	if(TIM_GetITStatus(TIM1, TIM_IT_Update) == SET){
		Key_Tick();
		TIM_ClearITPendingBit(TIM1, TIM_IT_Update);
	}
}


