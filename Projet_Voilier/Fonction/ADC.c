#include "ADC.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_rcc.h"


//Roulis : PC0 et PC1 et Batterie : PC2, IN10/11/12

void ADC_Conf(void){

	//Start la clock
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);
	
	//PC0 : X et PC1 : Y
	//Div la freq de la clock d'ADC par 6
	LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_6);

}

void ADC_Start(void){

	//Enable les ADC
	LL_ADC_Enable(ADC1);
	LL_ADC_Enable(ADC2);

}

void ADC_Stop(void){

	//Enable les ADC
	LL_ADC_Disable(ADC1);
	LL_ADC_Disable(ADC2);

}