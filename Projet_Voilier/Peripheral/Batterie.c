
#include "Batterie.h"
#include "stm32f1xx_ll_adc.h"


int Seuil_batterie(int tension){
	
	if (tension<=6){
		return 1;
	}
}

