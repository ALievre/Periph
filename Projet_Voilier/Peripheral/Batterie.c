#include "Batterie.h"
#include "stm32f1xx_ll_adc.h"

//Fonction qui d�tecte un seuil de tension de la batterie
int Seuil_Batterie(int * ptension){
	
	int tension = *ptension; 
	
	if (tension<=6){
		return 1;
	}
}

