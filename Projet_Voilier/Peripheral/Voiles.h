#ifndef Voiles_h
#define Voiles_h

//Renvoie l'angle des voiles
int Direction_Voiles(int Angle_Girouette);

//Cr�e le PWM qui contr�lera le servo-moteur
void Controle_Servomoteur(int Angle_Servo, int Angle_Limite);

#endif
