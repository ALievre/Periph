#include "Vent.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"

int Activation_Girouette(void){

	return LL_GPIO_ReadInputPort(GPIOA);
	//A FAIRE POLLING IDR REMET COMPTEUR A 0

}

int Direction_Vent(void){

	return LL_TIM_GetCounter(TIM3);

}