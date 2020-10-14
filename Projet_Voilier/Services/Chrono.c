// A COMPLETER

/*
Service permettant de chornométrer jusqu'à 59mn 59s 99 1/100
Utilise un timer au choix (TIMER1 à TIMER4).
Utilise la lib MyTimers.h /.c
*/



#include "Chrono.h"
#include "MyTimer.h"
#include "stm32f1xx_ll_gpio.h"
#include "stm32f1xx_ll_rcc.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_usart.h"

// variable privée de type Time qui mémorise la durée mesurée
static Time Chrono_Time; // rem : static rend la visibilité de la variable Chrono_Time limitée à ce fichier 

// variable privée qui mémorise pour le module le timer utilisé par le module
static TIM_TypeDef * Chrono_Timer=TIM1; // init par défaut au cas où l'utilisateur ne lance pas Chrono_Conf avant toute autre fct.

static int Etat_LED = 0;

static int Flag_Emission = 0;

// déclaration callback appelé toute les 10ms
void Chrono_Task_10ms(void);

void Usarts_Conf(USART_TypeDef* USARTn){

	//Start clock
	if (USARTn == USART1) LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
	else if (USARTn == USART2) LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART2);
	else LL_APB1_GRP1_EnableClock(LL_APB1_GRP1_PERIPH_USART3);
	
	//Initialise les config
	LL_USART_InitTypeDef USART_InitConf;
	
	LL_USART_StructInit(&USART_InitConf);
	USART_InitConf.BaudRate = 9600; //9600
	USART_InitConf.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitConf.Parity = LL_USART_PARITY_NONE;
	USART_InitConf.StopBits = LL_USART_STOPBITS_1;
	USART_InitConf.TransferDirection = LL_USART_DIRECTION_TX_RX;
	
	//Config
	LL_USART_Init(USARTn, &USART_InitConf);
	
	//Enable
	//LL_USART_SR_TXE;
	LL_USART_Enable(USARTn);
	LL_USART_EnableDirectionTx(USARTn);
	LL_USART_EnableDirectionRx(USARTn);
	
	
}

/**
	* @brief  incrémente la variable privée Chron_Time modulo 60mn 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Task_10ms(void)
{ 
	Flag_Emission = 1;
	
	Chrono_Time.Hund++;
	if (Chrono_Time.Hund==100)
	{
		Chrono_Time.Sec++;
		Chrono_Time.Hund=0;
	}
	if (Chrono_Time.Sec==60)
	{
		Chrono_Time.Min++;
		Chrono_Time.Sec=0;
	}
	if (Chrono_Time.Min==60)
	{
		Chrono_Time.Hund=0;
	}
	
	static int Count_Chrono = 0;
	Count_Chrono++;
	
	if (Count_Chrono == 101){
		if (Etat_LED == 0){
			LL_GPIO_SetOutputPin(GPIOC, LL_GPIO_PIN_10);
			Etat_LED = 1;
		}
		else if (Etat_LED == 1){
			LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_10);
			Etat_LED = 0;
		}
		Count_Chrono = 0;
	}
	
	
	//Allume la LED
	//GPIOC->ODR |= GPIO_ODR_ODR10;
	
	//Eteint la LED
	//GPIOC->ODR &= ~GPIO_ODR_ODR10;
	
}


/**
	* @brief  polle les 3 entrées et gènère les actions à faire
  * @note   Fct à lancer en tâche de fond (non bloquante)
	* @param  None 
  * @retval None
  */
		
void Chrono_Background(void){
	
	//BP Start/Stop
	static int Etat_Chrono; //0 = chrono éteint, 1 = chrono allumé
	static int Etat_BP; 		//0 = BP relaché, 1 = BP appuyé
	
	if(((LL_GPIO_ReadInputPort(GPIOC) & (1<<8)) != (1<<8)) && (Etat_BP == 0)){
		Etat_BP = 1;
		if (Etat_Chrono == 0){
			Etat_Chrono = 1;
			Chrono_Start();
		}
		else if (Etat_Chrono == 1){
			Etat_Chrono = 0;
			Chrono_Stop();
		}
	}
	
	
	//BP Reset
	if((LL_GPIO_ReadInputPort(GPIOC) & (1<<13)) != (1<<13)){
	Chrono_Reset();
	Etat_Chrono = 0;
		if (Etat_LED == 1){
			LL_GPIO_ResetOutputPin(GPIOC, LL_GPIO_PIN_10);
			Etat_LED = 0;
		}
	}
	
	if((LL_GPIO_ReadInputPort(GPIOC) & (1<<8)) == (1<<8)){
		Etat_BP = 0;
	}
	
	if(Flag_Emission == 1){
		Chrono_Affichage(USART2) ;
		Flag_Emission = 0;
	}
	
}

static void Chrono_Conf_io(void){

	//Allumer la clock
	//RCC->APB2ENR |= RCC_APB2ENR_IOPCEN;
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOC);
	
	//Start conf en floating input
	//GPIOC->CRH &= ~GPIO_CRH_MODE8;
	//GPIOC->CRH |= GPIO_CRH_CNF8_0;
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_8, LL_GPIO_MODE_FLOATING);
	
	//BP bleu conf en floating input PC13
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_13, LL_GPIO_MODE_FLOATING);
	
	//LED conf en output pushpull
	//GPIOC->CRH |= GPIO_CRH_MODE10_0;
	//GPIOC->CRH &= ~GPIO_CRH_CNF10;
	LL_GPIO_SetPinMode(GPIOC, LL_GPIO_PIN_10, LL_GPIO_MODE_OUTPUT);
	LL_GPIO_SetPinOutputType(GPIOC, LL_GPIO_PIN_10, LL_GPIO_OUTPUT_PUSHPULL);
	
	//LED conf en output open drain
	//GPIOC->CRH |= GPIO_CRH_MODE10_0;
	//GPIOC->CRH |= GPIO_CRH_CNF10_0;
	
}

/**
	* @brief  Configure le chronomètre. 
  * @note   A lancer avant toute autre fonction.
	* @param  Timer : indique le timer à utiliser par le chronomètre, TIM1, TIM2, TIM3 ou TIM4
  * @retval None
  */
void Chrono_Conf(TIM_TypeDef * Timer)
{
	// Reset Time
	Chrono_Time.Hund=0;
	Chrono_Time.Sec=0;
	Chrono_Time.Min=0;
	
	// Fixation du Timer
	Chrono_Timer=Timer;

	// Réglage Timer pour un débordement à 10ms
	MyTimer_Conf(Chrono_Timer,999, 719);
	
	// Réglage interruption du Timer avec callback : Chrono_Task_10ms()
	MyTimer_IT_Conf(Chrono_Timer, Chrono_Task_10ms,3);
	
	// Validation IT
	MyTimer_IT_Enable(Chrono_Timer);
	
	//Appel Chrono Conf IO
	Chrono_Conf_io();
	
}


/**
	* @brief  Démarre le chronomètre. 
  * @note   si la durée dépasse 59mn 59sec 99 Hund, elle est remise à zéro et repart
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Start(void)
{
	MyTimer_Start(Chrono_Timer);
}


/**
	* @brief  Arrête le chronomètre. 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Stop(void)
{
	MyTimer_Stop(Chrono_Timer);
}


/**
	* @brief  Remet le chronomètre à 0 
  * @note   
	* @param  Aucun
  * @retval Aucun
  */
void Chrono_Reset(void)
{
  // Arrêt Chrono
	MyTimer_Stop(Chrono_Timer);

	// Reset Time
	Chrono_Time.Hund=0;
	Chrono_Time.Sec=0;
	Chrono_Time.Min=0;
}


/**
	* @brief  Renvoie l'adresse de la variable Time privée gérée dans le module Chrono.c
  * @note   
	* @param  Aucun
  * @retval adresse de la variable Time
  */
Time * Chrono_Read(void)
{
	return &Chrono_Time;
}



void Chrono_Affichage(USART_TypeDef* USARTn){

	uint8_t Diz_M, Unit_M, Diz_S, Unit_S, Diz_C, Unit_C;
	
	Diz_M = (Chrono_Time.Min/10) +0x30;
	Unit_M = (Chrono_Time.Min%10) +0x30;
	
	Diz_S = (Chrono_Time.Sec/10) +0x30;
	Unit_S = (Chrono_Time.Sec%10) +0x30;
	
	Diz_C = (Chrono_Time.Hund/10) +0x30;
	Unit_C = (Chrono_Time.Hund%10) +0x30;
	
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, Diz_M);	//dizaine min
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, Unit_M);	//unite min
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, 0x3A);	//:
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, Diz_S);	//dizaine sec
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, Unit_S);	//unite sec
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, 0x3A);	//:
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, Diz_C);	//dizaine cent
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, Unit_C);	//unite cent
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, 0x3A);	//:
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, 0x3C);	//<
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, 0x30);	//0
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, 0x78);	//x
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, 0x30);	//0
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, 0x44);	//D
	}
	if(LL_USART_IsActiveFlag_TXE(USARTn)){
		LL_USART_TransmitData8(USARTn, 0x3E);	//>
	}
}
