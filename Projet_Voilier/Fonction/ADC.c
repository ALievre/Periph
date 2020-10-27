#include "ADC.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_rcc.h"




void ADC_Conf(ADC_TypeDef *ADC){

	//Start la clock
	if (ADC==ADC1) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
	else if (ADC==ADC2) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);
	
	//PC0 : X et PC1 : Y
	//Config PC0 et PC1 en analog input
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_0, LL_GPIO_MODE_ANALOG);
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_1, LL_GPIO_MODE_ANALOG);

	//Div la freq de la clock d'ADC par 6
	LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_6);

}