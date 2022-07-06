
//#include "helper.h"
#include "functions/helper.h"

/*
ESTADOS			IN1 IN2
HORARIO 		 1 - 0
ANTI-HORARIO	 0 - 1
PONTO MORTO 	 0 - 0
FREIO 		 	 1 - 1

ESTADOS			IN4 IN3
HORARIO 		 1 - 0
ANTI-HORARIO	 0 - 1
PONTO MORTO 	 0 - 0
FREIO 		 	 1 - 1
*/



// [1,0,0,1]




int main() {
	fullInit();

	while (1){

		// signalPulse();
		// _delay_ms(500);
		// write_measurement("PulseEnd", (pulseEnd*50)/58);

		clr_bit(PORTC, IN1);
	  	set_bit(PORTC, IN2);
		// clr_bit(PORTC, IN3);
	  	// set_bit(PORTC, IN4);

		}
	return 0;
}


ISR(TIMER2_COMPA_vect) {
	var++;
}


ISR(INT0_vect) {
	if(tst_bit(PIND,PD2)){
		var = 0;
	}
	else{
		if(var >= 0){pulseEnd = var;}
		else { pulseEnd = 0; }
	}
}

