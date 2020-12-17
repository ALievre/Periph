#ifndef Timer_h
#define Timer_h
#include "stm32f103xb.h" 

/**
	* @brief  Active l'horloge et règle l'ARR et le PSC du timer visé
  * @note   Fonction à lancer avant toute autre. Le timer n'est pas encore lancé (voir MyTimerStart)
	* @param  TIM_TypeDef Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
	* 				int Arr   : valeur à placer dans ARR
	*					int Psc   : valeur à placer dans PSC
  * @retval None
  */
void Timer_Conf(void);

void Timer_Start(TIM_TypeDef * Timer);

void Timer_Stop(TIM_TypeDef * Timer);

#endif
