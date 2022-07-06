
#include "helper.h"

int main()
{
	USART_Init();
	init();
	_delay_ms(50);
	sei();
	while (1)
	{
		signalPulse();
		_delay_ms(500);
	}
	return 0;
}


ISR(TIMER2_COMPA_vect){
	var++;
}


ISR(INT0_vect)
{
	if(tst_bit(PIND,PD2)){
		var = 0;	
	}
	else{
		pulseEnd = var;	//pulse takes values of counter
	}
}

