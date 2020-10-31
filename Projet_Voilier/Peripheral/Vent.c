#include "Vent.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"

int Activation_Girouette(void){

	return LL_GPIO_ReadInputPort(GPIOA);

}

int Direction_Vent(void){

	return LL_TIM_GetCounter(TIM3);

}