#include "helper.h"

void USART_Init() {
	// Set Baud Rate
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;
	// Set Frame Format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}


//initialise values
void init() {

	TCCR2A |= (1<<WGM21);
	OCR2A = 100;
	TIMSK2 = (1<<OCIE2A);
	TCCR2B |= (1<<CS21);

	DDRC = 0xFF;	//all pins as output
	PORTC = 0x00;	//set the pins to low initially, prevent floating

	DDRB = 0xFF;	//all pins as output
	PORTB = 0x00;	//set the pins to low initially, prevent floating

	DDRD = 0xFF;	//all pins as output
	DDRD &= ~(1<<echoPin);	//echoPin is input
	PORTD = 0x00;	//set pins to low

	EIMSK |= (1<<INT0);		//interrupt INT0 enabled
	EICRA |= (1<<ISC00); // interrupt on rising edge and falling edge

}

void fullInit() {
    USART_Init();
    init();
    _delay_ms(50);
    sei();
}