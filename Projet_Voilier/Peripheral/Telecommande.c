#include "Telecommande.h"
#include "stm32f1xx_ll_tim.h"


float DV_telecom(void){
	
	float direction;
	float duty_cycle;
	
	//duty cycle= CCR1/CCR2
	duty_cycle=LL_TIM_IC_GetCaptureCH1(TIM4)/LL_TIM_IC_GetCaptureCH2(TIM4);
	
	direction=((duty_cycle-0.05)*0.2/0.01);

	return direction;
}


