#include "Plateau.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h"
#include "math.h"

void Controle_Moteur_cc(float Direction){

	float Vitesse, Direction_Gauche;
	int ARR_new;
	
	//Droite : 0, gauche : 1
	if(Direction > 0.55){ 
		LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2);
		Vitesse = (Direction - 0.55)*2.22;
		ARR_new = (0.002*Vitesse*36000000)/10;
		LL_TIM_SetAutoReload(TIM4, ARR_new);
	}
	else if (Direction < 0.45){ 
		LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_2);
		Direction_Gauche = fabsf(Direction - 0.45);
		Vitesse = Direction_Gauche * 2.22;
		ARR_new = (0.002*Vitesse*36000000)/10;
		LL_TIM_SetAutoReload(TIM4, ARR_new);		
	}
	else if ((Direction >= 0.45 ) && (Direction <= 0.55)){
		LL_TIM_SetAutoReload(TIM4, 8);
		LL_TIM_SetPrescaler(TIM4, 1);
	}
	
}