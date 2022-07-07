
#include "functions/helper.h"

int main() {
	fullInit();

	while (1){

		// signalPulse();
		// _delay_ms(500);
		// write_measurement("PulseEnd", (pulseEnd*50)/58);

		// clr_bit(PORTC, IN1);
	  	// set_bit(PORTC, IN2);
		while (1) {
			goForward();
			_delay_ms(5000);
			turnRight();
			_delay_ms(5000);
			turnLeft();
			_delay_ms(5000);
			fullStop();
			_delay_ms(10000);
		}
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

