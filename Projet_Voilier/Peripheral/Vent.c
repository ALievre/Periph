#include "Vent.h"
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"

//Polling de l'IDR, � faire en background
void Index_Girouette(void){
	
	//Si l'index passe � 1, on remet le compteur � 0
	if(LL_GPIO_ReadInputPort(GPIOA)){
			LL_TIM_SetCounter(TIM3, 0);
	}
}

int Direction_Vent(void){

	//On r�cup�re la valeur du compteur (= angle de girouette)
	return LL_TIM_GetCounter(TIM3);

}