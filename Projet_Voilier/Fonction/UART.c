#include "UART.h"
#include "stm32f1xx_ll_bus.h"
#include "stm32f1xx_ll_usart.h"
#include "stm32f1xx_ll_gpio.h"



//Data in : PA9 USART1 Tx, Tx enable : PA11 USART1 CTS

void USART_Conf(void){
	
	//Start clock
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_USART1);
	
	LL_APB2_GRP1_EnableClock(LL_APB2_GRP1_PERIPH_GPIOA);
		
	
	//Initialise Tx enable à 0
	LL_USART_DisableCTSHWFlowCtrl(USART1);
	
	//Initialise les config
	LL_USART_InitTypeDef USART_InitConf;
	
	LL_USART_StructInit(&USART_InitConf);
	USART_InitConf.BaudRate = 9600; //9600
	USART_InitConf.DataWidth = LL_USART_DATAWIDTH_8B;
	USART_InitConf.Parity = LL_USART_PARITY_NONE;
	USART_InitConf.StopBits = LL_USART_STOPBITS_1;
	USART_InitConf.TransferDirection = LL_USART_DIRECTION_TX;
	
	//Config
	LL_USART_Init(USART1, &USART_InitConf);
	
	//Enable
	LL_USART_Enable(USART1);
	LL_USART_EnableDirectionTx(USART1);

}