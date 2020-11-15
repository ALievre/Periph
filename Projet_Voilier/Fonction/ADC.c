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
	//PC2
	//Div la freq de la clock d'ADC par 6
	LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_6);
	
	//conversion voie par voie
	
	//trigger externe sur SW
	LL_ADC_REG_SetTriggerSource(ADC1,LL_ADC_REG_TRIG_SOFTWARE);
	LL_ADC_REG_StartConversionExtTrig(ADC1,LL_ADC_REG_TRIG_EXT_RISING);
	
}

void Conversion_start(void){
	
	LL_ADC_REG_StartConversionSWStart(ADC1);
}

void Conversion_stop(void){
	LL_ADC_REG_StopConversionExtTrig(ADC1);
}
void ADC_Start(void){

	//Enable les ADC (bit ADON à 1)
	LL_ADC_Enable(ADC1);
	LL_ADC_Enable(ADC2);

}

void ADC_Stop(void){

	//Enable les ADC
	LL_ADC_Disable(ADC1);
	LL_ADC_Disable(ADC2);

}