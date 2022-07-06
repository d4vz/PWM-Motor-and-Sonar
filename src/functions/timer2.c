#include "helper.h"
//TIMER
void delayFunction_Timer0(int a) { //8 bit timer
	OCR0A = a;	//counter limit
	TCNT0 = 0x00;		//initialise Timer0 bits
	TCCR0A |= (1<<WGM01);		//Timer0, set to CTC mode
	TCCR0B |= (1<<CS00);		//Timer0, CS00 = no pre-scaler
	while ((TIFR0 & (1 << OCF0A)) == 0) {	//count up to OCF0 value
	}
	TCCR0B = 0x00;		//stop clock when OCF1 value is reached
	TIFR0 = (1 << OCF0A);		//set flag to 1
}