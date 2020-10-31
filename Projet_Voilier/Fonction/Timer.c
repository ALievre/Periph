#include "Timer.h"
#include "stm32f1xx_ll_bus.h" // Pour l'activation des horloges
#include "stm32f1xx_ll_tim.h"
#include "stm32f1xx_ll_gpio.h"


//Servo moteur : PA8 TIM1CH1, (PB8 TIM4CH3)
//Codeur increment : A=PA6 TIM3CH1, B=PA7 TIM3CH2
//Moteur cc : PA1 TIM2CH2
//Telécommande : PB6 TIM4CH1 PB7 TIM4CH2

void Timer_Conf(void)
{
	LL_TIM_InitTypeDef My_LL_Tim_Init_Struct;
	LL_TIM_BDTR_InitTypeDef My_TIM_BDTRInitStruct;
	
	// Validation horloge locale
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_TIM1);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM2);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM3);
	LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_TIM4);
	
	//TIM1CH1 en PWM Output
			//Conf de l'ARR et du PSC
	My_LL_Tim_Init_Struct.Autoreload=1799;
	My_LL_Tim_Init_Struct.Prescaler=99;
	My_LL_Tim_Init_Struct.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	My_LL_Tim_Init_Struct.CounterMode=LL_TIM_COUNTERMODE_UP;
	My_LL_Tim_Init_Struct.RepetitionCounter=0;
	LL_TIM_Init(TIM1,&My_LL_Tim_Init_Struct);
			//Conf du CCR1
	LL_TIM_OC_SetCompareCH1(TIM1, 89);
			//Mode PWM1
	LL_TIM_OC_SetMode(TIM1, LL_TIM_CHANNEL_CH1, LL_TIM_OCMODE_PWM1);
			//Activation bit MOE
	LL_TIM_EnableAllOutputs(TIM1);	
	
	//TIM2 en PWM Output
			//Conf de l'ARR et du PSC
	My_LL_Tim_Init_Struct.Autoreload=179;
	My_LL_Tim_Init_Struct.Prescaler=9;
	My_LL_Tim_Init_Struct.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	My_LL_Tim_Init_Struct.CounterMode=LL_TIM_COUNTERMODE_UP;
	My_LL_Tim_Init_Struct.RepetitionCounter=0;
	LL_TIM_Init(TIM2,&My_LL_Tim_Init_Struct);
			//Conf du CCR1
	LL_TIM_OC_SetCompareCH2(TIM2, 1);
			//Mode PWM1
	LL_TIM_OC_SetMode(TIM2, LL_TIM_CHANNEL_CH2, LL_TIM_OCMODE_PWM1);	
	
	//TIM3 en mode Encoder Interface
	LL_TIM_SetEncoderMode(TIM3, LL_TIM_ENCODERMODE_X4_TI12);
			//Conf de l'ARR et du PSC
	My_LL_Tim_Init_Struct.Autoreload=1799;
	My_LL_Tim_Init_Struct.Prescaler=99;
	My_LL_Tim_Init_Struct.ClockDivision=LL_TIM_CLOCKDIVISION_DIV1;
	My_LL_Tim_Init_Struct.CounterMode=LL_TIM_COUNTERMODE_UP;
	My_LL_Tim_Init_Struct.RepetitionCounter=0;
	LL_TIM_Init(TIM3,&My_LL_Tim_Init_Struct);
	
	//TIM4 en PWM Input

	
}

void Timer_Start(TIM_TypeDef * Timer){

	LL_TIM_EnableCounter(Timer);
	
}

void Timer_Stop(TIM_TypeDef * Timer){

	LL_TIM_DisableCounter(Timer);
	
}