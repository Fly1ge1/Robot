#include "IHM.h"      

IHM ihm; 

PwmOut Mot_Gauche(PB_5); 
PwmOut Mot_droit(PB_4); 
AnalogIn AnaIn(PB_1);
BusOut BusSelectMux (PA_8, PF_1, PF_0);

float decalage;

int main()
{
	ihm.LCD_clear();
	ihm.LCD_printf("TP VIRAGE DROIT");
	Mot_Gauche.period_us(50);
	Mot_droit.period_us(50);
	BusSelectMux =7;
	
	while(1) 
	{
		decalage = AnaIn.read();
		Mot_droit.write(0.5-decalage); //+-0.12      Si 0.3 +-0.07
		Mot_Gauche.write(0.5+decalage);
		ihm.LCD_gotoxy(1,0);
		ihm.LCD_printf("val = %4.2f", decalage);
		wait_ms(10);
	}
}

