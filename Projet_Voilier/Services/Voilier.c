#include "Voilier.h"
#include "ADC.h"
#include "GPIO.h"
#include "Timer.h"
#include "UART.h"
#include "Batterie.h"
#include "Plateau.h"
#include "Pupitre.h"
#include "Roulis.h"
#include "Vent.h"
#include "Voiles.h"
#include "Telecommande.h"
#include "stm32f1xx_ll_adc.h"

void Voilier_Conf(void){

	ADC_Conf();
	GPIO_Conf();
	Timer_Conf();
	USART_Conf();
	
}

void Controle_Voiles(void){

	int Angle_Limite_Roulis;
	int Etat_Conversion = 3;
	int Tension;
	int Voiles = Direction_Voiles(Direction_Vent());
	
//	Index_Girouette();
	
	//Conversions des channels 10, 11, 12
	if(Etat_Conversion == 3){
		Tension = *Conversion(0);
		Etat_Conversion = 1;
	}
	while(!(LL_ADC_IsActiveFlag_EOS(ADC1))){	}
	if ((LL_ADC_IsActiveFlag_EOS(ADC1)) && (Etat_Conversion == 1)){
		Angle_Limite_Roulis = Angle_Limite(Conversion(Etat_Conversion));
		Etat_Conversion = 2;
	}
	while(!(LL_ADC_IsActiveFlag_EOS(ADC1))){	}
	if ((LL_ADC_IsActiveFlag_EOS(ADC1)) && (Etat_Conversion == 2)){
		Angle_Limite_Roulis = Angle_Limite(Conversion(Etat_Conversion));
		Etat_Conversion = 0;
	}
	while(!(LL_ADC_IsActiveFlag_EOS(ADC1))){	}
	if ((LL_ADC_IsActiveFlag_EOS(ADC1)) && (Etat_Conversion == 0)){
		Tension = *Conversion(0);
		Etat_Conversion = 1;
	}
	
	//Servomoteur et voiles
	Controle_Servomoteur(Voiles, Angle_Limite_Roulis);
	
	//Transmission de données vers le pupitre
	Transmission_Data(Tension, Angle_Limite_Roulis, Voiles);
}

void Controle_Plateau(void){

	Controle_Moteur_cc(Get_Direction());
	
}