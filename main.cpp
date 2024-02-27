#include "IHM.h"      

IHM ihm; 
#define AN0 0
#define AN1 1
#define AN2 2
#define AN3 3 
#define AN4 4

DigitalIn jack(PB_6, PullUp);
DigitalIn bp(PB_7, PullUp);
PwmOut MD(PB_5);
PwmOut MG(PB_4);
DigitalIn BP0(PA_9, PullUp);
DigitalIn BP1(PA_10, PullUp);
DigitalIn BP2(PB_0,PullUp);
DigitalIn BP3(PB_7, PullUp);
BusOut Mux(PA_8,PF_1,PF_0);
AnalogIn AnaIn (PB_1);
int CD;
int CG;


void automate(void);

int main()
{
  //float capteur_raccourci;
	//float capteur_extreme_gauche;
	float capteur_gauche;
	float capteur_droit;
	//float capteur_extreme_droit;	
	
   while(1) 
		{
			Mux=AN0;
			wait_us(20);
			capteur_droit=AnaIn;
			if (capteur_droit<0.2)
			{
				CD=0;
			}
			else 
			{
				CD=1;
			}
			//Mux=AN1;
			//wait_us(20);
			//capteur_raccourci=AnaIn;
			
			//Mux=AN2;
			//wait_us(20);
			//capteur_extreme_gauche=AnaIn;
			
			Mux=AN3;
			wait_us(20);
			capteur_gauche=AnaIn;	
			if (capteur_gauche<0.2)
			{
				CG=0;
			}
			else 
			{
				CG=1;
			}							
			
			//Mux=AN4;
			//wait_us(20);
			//capteur_extreme_droite=AnaIn;		
			automate();
			wait_ms(10);
	  }
}
void automate()
{
	typedef enum {debut, avancer_tout_droit, virage_droit, virage_gauche} type_etat;
	static type_etat etat_futur = debut;
	type_etat etat_courant;
	etat_courant = etat_futur;

  switch(etat_courant)
	{
		case debut:
			if (jack==0)
			{
				etat_futur=avancer_tout_droit;
			}
			break;
			
	  case avancer_tout_droit:
			if(CG==1 && CD==0)
			{
     	 etat_futur=virage_droit;
	    }	
			else if(CG==0 && CD==1)
			{
				etat_futur=virage_gauche;
			}
			 break;
		case virage_gauche:
			if (CG==1 && CD==0)
			{
				etat_futur=avancer_tout_droit;  		 
	    }	
				break;
		case virage_droit:
			if (CG==0 && CD==1)
			{
				etat_futur=avancer_tout_droit; 		 
	    }	
				break;			
	 }
	
	 
	 switch(etat_courant)
	{
		case debut:
			MG=0;
			MD=0;
			break;
	  case avancer_tout_droit:
			MG=0.3;
			MD=0.3;
		 break;
		case virage_gauche:
			MG=0.3-0.07;
			MD=0.3+0.07;
			break;
		case virage_droit:
			MG=0.3+0.07;
			MD=0.3-0.07;
			break;			
	 }
 }


