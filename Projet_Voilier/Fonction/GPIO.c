#include "GPIO.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"


//Girouette : PA5 IDR
//Moteur cc : PA2

void GPIO_Conf(void){

	//Start clock
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
	
	//Girouette
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_5, LL_GPIO_MODE_FLOATING);

	//Moteur cc
	LL_GPIO_SetPinMode(GPIOA, LL_GPIO_PIN_2, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOA, LL_GPIO_PIN_2, LL_GPIO_OUTPUT_PUSHPULL);

}