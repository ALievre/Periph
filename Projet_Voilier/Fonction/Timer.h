#ifndef Timer_h
#define Timer_h
#include "stm32f103xb.h" 

/**
	* @brief  Active l'horloge et r�gle l'ARR et le PSC du timer vis�
  * @note   Fonction � lancer avant toute autre. Le timer n'est pas encore lanc� (voir MyTimerStart)
	* @param  TIM_TypeDef Timer : indique le timer � utiliser par le chronom�tre, TIM1, TIM2, TIM3 ou TIM4
	* 				int Arr   : valeur � placer dans ARR
	*					int Psc   : valeur � placer dans PSC
  * @retval None
  */
void Timer_Conf(void);

void Timer_Start(TIM_TypeDef * Timer);

void Timer_Stop(TIM_TypeDef * Timer);

#endif
