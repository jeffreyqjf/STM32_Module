#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "GPIO_Init.h"
#include "OLED.h"
#include "EXTI_Init.h"
#include "Timer.h"
#include "PWM.h"
#include "MyAD.h"
#include "MyRTC.h"


/*MyAD test*/
int main(void)
{
	OLED_Init();
	MyAD_Init();
	int AD_Value = 0;
	while(1)
	{
		AD_Value = MyAD_GetVaule();
		OLED_ShowNum(0, 0, AD_Value, 4, OLED_8X16);
		OLED_Update();
		Delay_ms(500);
	}
}