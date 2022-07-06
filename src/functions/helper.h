
#define F_CPU 16000000UL // Defining the CPU Frequency
#define BAUDRATE 9600
#define BAUD_PRESCALLER (((F_CPU / (BAUDRATE * 16UL))) - 1)

#include <avr/io.h>      // Contains all the I/O Register Macros
#include <util/delay.h>  // Generates a Blocking Delay
#include <stdlib.h>
#include <string.h>
#include <avr/interrupt.h>
#include <stdio.h>

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

#define IN1 0
#define IN2 1
#define IN3 2
#define IN4 3

#define	set_bit(y,bit)	(y|=(1<<bit))
#define	clr_bit(y,bit)	(y&=~(1<<bit))
#define cpl_bit(y,bit) 	(y^=(1<<bit))
#define tst_bit(y,bit) 	(y&(1<<bit))

static volatile int pulseEnd = 0;
static volatile int var = 0;

void USART_Init();
void init();
void write_string(char *str);
void write_int(int num);
void write_measurement(char *str,int num);
void delayFunction_Timer0(int a);
void signalPulse();
void fullInit();
void startEngine(int value1, int value2);
void turnRight();
void turnLeft();
void goForward();
void stopEngine();
