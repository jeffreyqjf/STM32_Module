#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "GPIO_Init.h"
#include "OLED.h"
#include "EXTI_Init.h"
#include "Timer.h"
#include "PWM.h"
#include "MyAD.h"
#include "MyRTC.h"


/*EXTI_Init test*/
int Count = 0;
int main(void)
{
	OLED_Init();
	EXTI_GPIOA_Init(3);
	while(1)
	{
		OLED_ShowNum(0, 0, Count, 3, OLED_8X16);
		OLED_Update();
	}
}


void EXTI3_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line3) == SET){
		Count ++;
		EXTI_ClearFlag(EXTI_Line3);
	}
}
