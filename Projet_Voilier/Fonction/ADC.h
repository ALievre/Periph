#include "stm32f1xx_ll_bus.h"

void ADC_Conf(void);
void Conversion_Start(void);
void Conversion_Stop(void);
int * Conversion(int num_channel);
void ADC_Start(void);
void ADC_Stop(void);