#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "GPIO_Init.h"
#include "OLED.h"
#include "EXTI_Init.h"
#include "Timer.h"
#include "PWM.h"
#include "MyAD.h"
#include "MyRTC.h"


/*MyRTC test*/
int main(void)
{
	OLED_Init();
	MyRTC_Init();
	int GetNum = 0;
	while(1)
	{
		GetNum = RTC_GetCounter();
		OLED_ShowNum(0, 0, GetNum, 3, OLED_8X16);
		OLED_Update();
	}
}