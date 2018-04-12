xdata at 0x8000 unsigned char U12;	/* umiejscowienie klawiatury (bufora) */

sbit at 0xB5 T1;

#define BUZZER T1							/* definicja glosniczka	*/
#define SW2 0x01
#define SW3 0x02
#define SW4 0x04
#define SW5 0x08
#define PRESSED(x) ((U12 & x)==0)	/* czy wcisnieto klawisz */

void main (void){
	unsigned char i,r=0,t=70,s=0;
	for(;;){
		if((s & 0x01)!=0){
			if((r & 0x01)==0) 			/*sprawdzanie za pomocy maski wartosci ostatniego bitu, czy jest parzysty i dalej generujemy fale dzwiekowa*/
				BUZZER=1;
			else
				BUZZER=0;
			r++;
		}
		if(PRESSED(SW2))
			t+=70;
		if(PRESSED(SW3))
			if(t>70)
				t=-70;
		if(PRESSED(SW4))
			s++;
		for(i=0; i<t; i++);				/* drobne opoznienie  */
	}
}
