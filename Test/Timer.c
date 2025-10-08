#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "GPIO_Init.h"
#include "OLED.h"
#include "EXTI_Init.h"
#include "Timer.h"
#include "PWM.h"
#include "MyAD.h"
#include "MyRTC.h"


/*Timer test*/
int Count = 0;
int main(void)
{
	OLED_Init();
	Timer_Init();
	while(1)
	{
		OLED_ShowNum(0, 0, Count, 3, OLED_8X16);
		OLED_Update();
	}
}

void TIM2_IRQHandler(void){
	if(TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
		Count ++;
		TIM_ClearITPendingBit(TIM2, TIM_IT_Update);
	}
}
