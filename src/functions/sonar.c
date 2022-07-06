#include "helper.h"

void signalPulse() {
	PORTB |= (1<<trigPin);	//set trigPin high
	delayFunction_Timer0(0x9F);	//0x9F = 159 = 10 uSecs
	PORTB &= ~(1<<trigPin);		//set trigPin low again
}