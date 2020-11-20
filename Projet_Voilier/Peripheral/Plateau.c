#include "Plateau.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_tim.h"
#include "math.h"

void Controle_Moteur_cc(float Direction){

	float Vitesse, Direction_Gauche;
	int duty_cycle;
	
	//Droite : 0, gauche : 1
	if(Direction > 0.55){ //on va vers la droite
		LL_GPIO_ResetOutputPin(GPIOA, LL_GPIO_PIN_2); //on met le pin à 0
		Vitesse = (Direction - 0.55)*2.22; //on calcule la vitesse
		duty_cycle = (0.002*Vitesse*36000000)/10; //on convertit en duty cycle
		LL_TIM_OC_SetCompareCH1(TIM4, duty_cycle);
	}
	else if (Direction < 0.45){ //on va vers la gauche
		LL_GPIO_SetOutputPin(GPIOA, LL_GPIO_PIN_2); //on met le pin à 1
		Direction_Gauche = fabsf(Direction - 0.45);
		Vitesse = Direction_Gauche * 2.22;
		duty_cycle = (0.002*Vitesse*36000000)/10;
		LL_TIM_OC_SetCompareCH1(TIM4, duty_cycle);		
	}
	else if ((Direction >= 0.45 ) && (Direction <= 0.55)){ //zone neutre
		LL_TIM_SetAutoReload(TIM4, 8);
		LL_TIM_SetPrescaler(TIM4, 1);
	}
	
}