
#include "helper.h"

int main()
{

	// set tnct2 to output
	DDRB |= (1<<TCNT2);

	USART_Init();
	init();
	_delay_ms(50);
	sei();
	int16_t pulseRange = 0;
	char pulseString[5];
	while (1)
	{
		signalPulse();
		pulseRange = pulseEnd;
		itoa(pulseRange, pulseString, 10);
		// write_string("Distance: ");
		// write_string(pulseString);
		// USART_TransmitPolling('\n');
		_delay_ms(500);
	}
	return 0;
}


ISR(INT0_vect)
{
	//if the flag is 0, start timer2 with 1024 pre-scaler
	if(echoFlag == 0) {
		TCCR2B |= (1<<CS22) | (1<<CS21) | (1<<CS20);	//1024 pre-scaler
		echoFlag = 1;	//set flag to 1
	}
	else if(echoFlag == 1){
		pulseEnd = TCNT2;	//pulse takes values of counter
		write_int(pulseEnd);
		TCNT2 = 0;		//reset counter
		TCCR2B = 0;	//stop timer	
		echoFlag = 0;		//reset flag
	}
}

//this interrupt will reset Timer 2 if overflow occurs. 
//However, because the timer is 8 bit, it is limited to showing only values up to 275cm.
//Therefore, the Timer will never count beyond the range of the sensor, 400cm.
//Thus, overflow will never occur. This is simply here to increase robustness of the system.

ISR(TIMER2_OVF_vect){
	TCCR2B = 0;	//stop timer
	TCNT2 = 0;	//reset counter
	echoFlag = 0;	//reset flag
}
