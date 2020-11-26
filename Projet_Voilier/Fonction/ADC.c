#include "ADC.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_adc.h"
#include "stm32f1xx_ll_rcc.h"


//Roulis : PC0 et PC1 et Batterie : PC2, IN10/11/12

//Config des ADC
void ADC_Conf(void){

    //Start la clock
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC1);
    LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_ADC2);
    //PC0 : X et PC1 : Y
    //PC2
    //Div la freq de la clock d'ADC par 6
    LL_RCC_SetADCClockSource(LL_RCC_ADC_CLKSRC_PCLK2_DIV_6);

    //conversion voie par voie

    //champ L à 0: 1 seule conversion
    LL_ADC_REG_SetSequencerLength(ADC1,LL_ADC_REG_SEQ_SCAN_DISABLE);
    //trigger externe sur SW
    LL_ADC_REG_SetTriggerSource(ADC1,LL_ADC_REG_TRIG_SOFTWARE);
    LL_ADC_REG_StartConversionExtTrig(ADC1,LL_ADC_REG_TRIG_EXT_RISING);

		ADC_Start();
}

void Conversion_Start(void){

    LL_ADC_REG_StartConversionSWStart(ADC1);
}

void Conversion_Stop(void){
    LL_ADC_REG_StopConversionExtTrig(ADC1);
}

//Fait les conversions
int * Conversion(int num_channel){

	static int tab[3];
	int * ptab = tab;
	
    if (num_channel==0){
        LL_ADC_REG_SetSequencerRanks(ADC1,LL_ADC_REG_RANK_1,LL_ADC_CHANNEL_10);
				Conversion_Start();
				tab[0] = LL_ADC_REG_ReadConversionData12(ADC1);
    }
    else if (num_channel==1){
					LL_ADC_REG_SetSequencerRanks(ADC1,LL_ADC_REG_RANK_1,LL_ADC_CHANNEL_11);
					Conversion_Start();
					tab[1] = LL_ADC_REG_ReadConversionData12(ADC1);
		}
		else if (num_channel==2){
				LL_ADC_REG_SetSequencerRanks(ADC1,LL_ADC_REG_RANK_1,LL_ADC_CHANNEL_12);
				Conversion_Start();
				tab[2] = LL_ADC_REG_ReadConversionData12(ADC1);
		}
			
    return ptab;

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
