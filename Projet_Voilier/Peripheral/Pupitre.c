#include "Pupitre.h"
#include "stm32f1xx_ll_usart.h"
#include <stdlib.h>

//Batterie = "tension" V
//Angle limite de roulis détecté
//Angle Voiles = "valeur" degrés

void Transmission_Data(int Tension_Batterie, int Angle_Limite, int Angle_Voiles){

	//Convertit les valeurs en hexa et les sépare entre dizaine et unité
	uint8_t Tension_Diz = (Tension_Batterie/10) + 0x30;
	uint8_t Tension_Unit = (Tension_Batterie%10) + 0x30;
	
	//Convertit les valeurs en hexa et les sépare entre dizaine et unité
	int Angle_Voiles_new = abs(Angle_Voiles);
	uint8_t Angles_Voiles_Diz = (Angle_Voiles_new/10) + 0x30;
	uint8_t Angles_Voiles_Unit = (Angle_Voiles_new%10) + 0x30;
	
	//Tableau message batterie
	uint8_t tab_batt[17] = {'B', 'a', 't', 't', 'e', 'r', 'i', 'e', ' ', '=', ' ', 
														Tension_Diz, Tension_Unit, ' ', 'V', 0x0A, 0x0D};
	
	//Tableau message roulis
	uint8_t tab_roulis[32] = {0x41, 0x6E, 0x67, 0x6C, 0x65, 0x20, 0x6C, 0x69, 0x6D, 0x69, 0x74, 
														0x65, 0x20, 0x64, 0x65, 0x20, 0x72, 0x6F, 0x75, 0x6C, 0x69, 0x73, 
														0x20, 0x64, 0x65, 0x74, 0x65, 0x63, 0x74, 0x65, 0x0A,0x0D};
	
	//Tableau message voiles
	uint8_t tab_voiles[26] = {0x41, 0x6E, 0x67, 0x6C, 0x65, 0x20, 0x76, 0x6F, 0x69, 0x6C, 0x65,
														0x73, 0x20, 0x3D, 0x20, Angles_Voiles_Diz, Angles_Voiles_Unit,
														0x20, 0x64, 0x65, 0x67, 0x72, 0x65, 0x73, 0x0A, 0x0D};
	
	//Transmission message batterie
	for(int i=0; i<18; i++){
		if(LL_USART_IsActiveFlag_TXE(USART1)){
		LL_USART_TransmitData8(USART1, tab_batt[i]);
		}
	}
	/*
	//Transmission message roulis si angle limite détecté
	if(Angle_Limite){
		for(int j=0; j<32; j++){
			if(LL_USART_IsActiveFlag_TXE(USART1)){
				LL_USART_TransmitData8(USART1, tab_roulis[j]);
			}
		}
	}
	
	//Transmission message voiles
	for(int k=0; k<26; k++){
		if(LL_USART_IsActiveFlag_TXE(USART1)){
		LL_USART_TransmitData8(USART1, tab_voiles[k]);
		}
	}
	*/
}
