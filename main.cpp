#include "IHM.h"      // contient mbed.h

IHM ihm;  // définition de l'objet ihm (de classe IHM pour la NBOARD)

DigitalOut Led0(PB_3);
DigitalOut Led1(PA_7);
DigitalOut Led2(PA_6);
DigitalOut Led3(PA_5);
DigitalOut Led4(PA_3);

BusOut Bus8Led(PB_3, PA_7, PA_6, PA_5, PA_3, PA_1, PA_0, PA_2);

DigitalIn BP0(PA_9, PullUp);
DigitalIn BP1(PA_10, PullUp);
DigitalIn BP2(PB_0, PullUp);
DigitalIn BP3(PB_7, PullUp);

BusOut BusSelectMux(PA_8, PF_1, PF_0);

AnalogIn AnaIn(PB_1);
//--------------------------------- main -----------------------------------------------------
int main()
{
		float capteur_raccourci;
    float capteur_extreme_gauche;
    float capteur_gauche;
    float capteur_droite;
    float capteur_extreme_droite;
	
    while(true)
    {
        BusSelectMux = 0;
        wait_us(20);
        capteur_droite=AnaIn;

        BusSelectMux = 1;
        wait_us(20);
        capteur_raccourci=AnaIn;

        BusSelectMux = 2;
        wait_us(20);
        capteur_extreme_gauche=AnaIn;

        BusSelectMux = 3;
        wait_us(20);
        capteur_gauche=AnaIn;

        BusSelectMux = 4;
        wait_us(20);
        capteur_extreme_droite=AnaIn;


        if (capteur_raccourci > 0.5)
        {
            Led0=1;
        }
        else
        {
            Led0=0;
        }

        if (capteur_extreme_gauche>0.5)
        {
            Led1=1;
        }
        else
        {
            Led1=0;
        }

        if (capteur_gauche>0.5)
        {
            Led2=1;
        }
        else
        {
            Led2=0;
        }
        if (capteur_droite>0.5)
        {
            Led3=1;
        }
        else
        {
            Led3=0;
        }

        if (capteur_extreme_droite>0.5)
        {
            Led4=1;
        }
        else
        {
            Led4=0;
        }
        ihm.LCD_gotoxy(0,0);
        ihm.LCD_printf("cap %4.2f",capteur_droite);

}
}
