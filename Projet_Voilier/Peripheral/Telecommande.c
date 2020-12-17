#include "Telecommande.h"
#include "stm32f1xx_ll_tim.h"

//On récupère la direction indiquée par la télécommande
float Get_Direction(void){
	
	float direction;
	float duty_cycle;
	
	//duty cycle= CCR1/CCR2
	duty_cycle= (float) LL_TIM_IC_GetCaptureCH2(TIM4)/ (float) LL_TIM_IC_GetCaptureCH1(TIM4);
	
	//conversion du duty cycle en direction
//	direction=((duty_cycle-0.05)*0.2/0.01);
	direction = duty_cycle ;
	return direction;
}


