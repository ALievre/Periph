#include "Roulis.h"

int Angle_Limite(int * proulis){

	//On récupère les valeurs de x et y 
	int x = *(proulis + 1);
	int y = *(proulis + 2);
	
	static int indicateur = 0; //0 : angle de roulis < 45°
	static int resultat = 42 ;
	
	//Si x = y, alors on a attenit l'angle limite
	if (x == y){
		
		//On était < 45°, on passe l'angle limite !
		if (indicateur == 0){
			indicateur = 1;
			resultat = 1;
		} else if (indicateur == 1){ //On était > 45° donc on revient aux angles normaux
			indicateur = 0;
				resultat = 0;
		}
		
	}
 return resultat;
}