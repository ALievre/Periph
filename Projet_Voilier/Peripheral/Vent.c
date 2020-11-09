#include "Vent.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"

//Polling de l'IDR, à faire en background
void Index_Girouette(void){
	
	if(LL_GPIO_ReadInputPort(GPIOA)){
	
			LL_TIM_SetCounter(TIM3, 0);
		
	}
}

int Direction_Vent(void){

	return LL_TIM_GetCounter(TIM3);

}