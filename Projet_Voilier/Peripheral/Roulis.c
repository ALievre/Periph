#include "Roulis.h"

int Angle_Limite(int * proulis){

	int x = *(proulis + 1);
	int y = *(proulis + 2);
	
	static int indicateur = 0; //0 : angle de roulis < 45°
	
	if (x == y){
	
		if (indicateur == 0){
			indicateur = 1;
			return 1;
		} else if (indicateur == 1){
			indicateur = 0;
			return 0;
		}
		
	}

}