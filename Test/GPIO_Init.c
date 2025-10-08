#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "GPIO_Init.h"
#include "OLED.h"
#include "EXTI_Init.h"
#include "Timer.h"
#include "PWM.h"
#include "MyAD.h"
#include "MyRTC.h"


/*GPIO_Init test*/
int main(void)
{
	Indicator_Light_Init();
}
