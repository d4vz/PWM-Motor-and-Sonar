#include "functions/helper.h"

int main() {
	fullInit();
	while (1){

		signalPulse();
		int distance = (pulseEnd*50)/58;
		_delay_ms(500);
		write_measurement("Distance", distance);
		if(distance < 60) {
			turnLeftCustom(1);
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

