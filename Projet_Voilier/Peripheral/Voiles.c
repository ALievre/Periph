#include "Voiles.h"
#include "stm32f1xx_ll_tim.h"


int Direction_Voiles(int Angle_Girouette){

	int Angle_Voiles;
	
	if ((315 < Angle_Girouette) || (Angle_Girouette < 45)) Angle_Voiles = 0;
	else if ((Angle_Girouette >= 45) && (Angle_Girouette <180)) Angle_Voiles = (Angle_Girouette - 45)*1.5;
	else if ((Angle_Girouette > 181) && (Angle_Girouette <= 315)) Angle_Voiles = -((360 - Angle_Girouette)*1.5);
	else if (Angle_Girouette == 181) Angle_Voiles = -89;
	else if (Angle_Girouette == 180) Angle_Voiles = 90;
	
	return Angle_Voiles;
	
}

void Controle_Servomoteur(int Angle_Voiles, int Angle_Limite){

	int Angle_Servo, ARR_new;
	if (Angle_Limite){
		LL_TIM_SetAutoReload(TIM1, 89);
	} else {
		if (Angle_Voiles == 0) LL_TIM_SetAutoReload(TIM1, 134);
		else if (Angle_Voiles == 90) LL_TIM_SetAutoReload(TIM1, 89);
		else if (Angle_Voiles == -89) LL_TIM_SetAutoReload(TIM1, 179);
		else{
			
			Angle_Servo = 90 - Angle_Voiles;
			ARR_new = ((0.02*(0.05+(Angle_Servo*0.000281))*9000000)/100) - 1;
			LL_TIM_SetAutoReload(TIM1, ARR_new);
		
		} 	
	}

}