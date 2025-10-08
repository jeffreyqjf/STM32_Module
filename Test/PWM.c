#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "GPIO_Init.h"
#include "OLED.h"
#include "EXTI_Init.h"
#include "Timer.h"
#include "PWM.h"
#include "MyAD.h"
#include "MyRTC.h"


/*PWM test*/
int main(void)
{
	PWM_Init();
	while(1)
	{
		for(int i = 0; i<= 10; i++){
			TIM_SetCompare1(TIM2, i * 10);
			Delay_ms(50);
		}
		for(int i = 0; i <= 10; i++){
			TIM_SetCompare1(TIM2, 100 - i * 10);
			Delay_ms(50);
		}
	}
}