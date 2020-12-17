#ifndef Voiles_h
#define Voiles_h

//Renvoie l'angle des voiles
int Direction_Voiles(int Angle_Girouette);

//Crée le PWM qui contrôlera le servo-moteur
void Controle_Servomoteur(int Angle_Servo, int Angle_Limite);

#endif
