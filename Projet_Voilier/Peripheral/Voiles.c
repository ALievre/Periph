#include "Voiles.h"
#include "stm32f1xx_ll_tim.h"

//Convertit l'angle de girouette en angle de voiles voulu
int Direction_Voiles(int Angle_Girouette){

	int Angle_Voiles;
	
	if ((315 < Angle_Girouette) || (Angle_Girouette < 45)) Angle_Voiles = 0;
	else if ((Angle_Girouette >= 45) && (Angle_Girouette <180)) Angle_Voiles = 45;
	else if ((Angle_Girouette > 181) && (Angle_Girouette <= 315)) Angle_Voiles = -45;
	else if (Angle_Girouette == 181) Angle_Voiles = -89;
	else if (Angle_Girouette == 180) Angle_Voiles = 90;
	
	return Angle_Voiles;
	
}

//Controle le servomoteur selon l'angle de voiles voulu
void Controle_Servomoteur(int Angle_Voiles, int Angle_Lim){
	
	int Angle_Servo, duty_cycle;
	
	//Si on est à l'angle limite, on ferme les voiles
	if (Angle_Lim==1){
		LL_TIM_OC_SetCompareCH1(TIM1, 1500);
	} else {
		if (Angle_Voiles == 0) LL_TIM_OC_SetCompareCH1(TIM1, 1110);
		else if (Angle_Voiles == 90) LL_TIM_OC_SetCompareCH1(TIM1, 720);
		else if (Angle_Voiles == -89) LL_TIM_OC_SetCompareCH1(TIM1, 1500);
		else if (Angle_Voiles == -45) LL_TIM_OC_SetCompareCH1(TIM1, 1305); 
		else if (Angle_Voiles == 45) LL_TIM_OC_SetCompareCH1(TIM1, 915);
		/*else{
			
			Angle_Servo = 90 - Angle_Voiles;
			duty_cycle = ((0.02*(0.05+(Angle_Servo*0.000281))*9000000)/100) - 1;
			LL_TIM_OC_SetCompareCH1(TIM1, duty_cycle);
		
		} 	*/
	}

}