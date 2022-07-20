#include "functions/helper.h"

int main() {
	fullInit();
	int marker = true;
	while (1){

		signalPulse();
		_delay_ms(500);
		// write_measurement("PulseEnd", (pulseEnd*50)/58);
		if(pulseEnd < 50 && marker) {
			stop();
			turnLeftCustom(1);
			marker = false;
		} else if(pulseEnd > 50 && !marker) {
			stop();
			turnRightCustom(1);
			marker = true;
		}
		else { goForward(); }
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

