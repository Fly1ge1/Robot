#include "IHM.h"      

IHM ihm; 

DigitalOut Led0(PB_3);
PwmOut Mot_Gauche(PB_5); 
PwmOut Mot_droit(PB_4); 


AnalogIn AnaIn (PB_1);
BusOut Mux (PA_8, PF_1, PF_0);


int main()
{
	   ihm.LCD_clear();
    ihm.LCD_printf("TP IHM NBOARD");
	Mux=0x7;
	Mot_Gauche.period_us(10);
	Mot_droit.period_us(10);
	   
    while(1) 
		{
			Mot_Gauche.write(AnaIn.read());
			Mot_droit.write(AnaIn.read());
		 			
       
    }
}


