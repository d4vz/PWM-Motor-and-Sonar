
#define F_CPU 16000000UL // Defining the CPU Frequency
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

#include <avr/io.h>      // Contains all the I/O Register Macros
#include <util/delay.h>  // Generates a Blocking Delay
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>

#define USART_BAUDRATE 9600 // Desired Baud Rate
#define BAUD_PRESCALER (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

#define ASYNCHRONOUS (0<<UMSEL00) // USART Mode Selection

#define DISABLED    (0<<UPM00)
#define EVEN_PARITY (2<<UPM00)
#define ODD_PARITY  (3<<UPM00)
#define PARITY_MODE  DISABLED // USART Parity Bit Selection

#define ONE_BIT (0<<USBS0)
#define TWO_BIT (1<<USBS0)
#define STOP_BIT ONE_BIT      // USART Stop Bit Selection

#define FIVE_BIT  (0<<UCSZ00)
#define SIX_BIT   (1<<UCSZ00)
#define SEVEN_BIT (2<<UCSZ00)
#define EIGHT_BIT (3<<UCSZ00)
#define DATA_BIT   EIGHT_BIT  // USART Data Bit Selection

#define trigPin 3
#define echoPin 2

volatile unsigned int var = 0;
volatile unsigned int pulseEnd = 0;

#define tst_bit(y,bit) 	(y&(1<<bit))	//retorna 0 ou 1 conforme leitura do bit


void USART_Init()
{
	// Set Baud Rate
	UBRR0H = BAUD_PRESCALER >> 8;
	UBRR0L = BAUD_PRESCALER;
	// Set Frame Format
	UCSR0C = ASYNCHRONOUS | PARITY_MODE | STOP_BIT | DATA_BIT;
	// Enable Receiver and Transmitter
	UCSR0B = (1<<RXEN0) | (1<<TXEN0);
}

void USART_TransmitPolling(uint8_t DataByte)
{
	while (( UCSR0A & (1<<UDRE0)) == 0) {}; // Do nothing until UDR is ready
	UDR0 = DataByte;
}

//initialise values
void init()
{

	TCCR2A |= (1<<WGM21);
	OCR2A = 100;
	TIMSK2 = (1<<OCIE2A);
	TCCR2B |= (1<<CS21);

	DDRB = 0xFF;	//all pins as output
	PORTB = 0x00;	//set the pins to low initially, prevent floating
	DDRD = 0xFF;	//all pins as output
	DDRD &= ~(1<<echoPin);	//echoPin is input
	PORTD = 0x00;	//set pins to low
	EIMSK |= (1<<INT0);		//interrupt INT0 enabled
	EICRA |= (1<<ISC00); // interrupt on rising edge and falling edge

}

void write_string(char *str)
{
	while (*str)
	{
		USART_TransmitPolling(*str);
		str++;
	}
}

void write_int(int num)
{
	char str[10];
	itoa(num, str, 10);
	write_string(str);
}

void write_measurement(char *str,int num)
{
  write_string(str);
  write_int(num);
  write_string("\n");
}

//delay function using timer0
void delayFunction_Timer0(int a)	//8 bit timer
{
	OCR0A = a;	//counter limit
	TCNT0 = 0x00;		//initialise Timer0 bits
	TCCR0A |= (1<<WGM01);		//Timer0, set to CTC mode
	TCCR0B |= (1<<CS00);		//Timer0, CS00 = no pre-scaler
	while ((TIFR0 & (1 << OCF0A)) == 0) {	//count up to OCF0 value
	}
	TCCR0B = 0x00;		//stop clock when OCF1 value is reached
	TIFR0 = (1 << OCF0A);		//set flag to 1
}

//pulse 10uSecs to trigger input, this starts the ranging process
void signalPulse()
{
	PORTB |= (1<<trigPin);	//set trigPin high
	delayFunction_Timer0(0x9F);	//0x9F = 159 = 10 uSecs
	PORTB &= ~(1<<trigPin);		//set trigPin low again
}