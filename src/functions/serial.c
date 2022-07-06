#include "helper.h"

void USART_TransmitPolling(uint8_t DataByte) {
	while (( UCSR0A & (1<<UDRE0)) == 0); // Do nothing until UDR is ready
	UDR0 = DataByte;
}

void write_string(char *str) {
	while (*str)
	{
		USART_TransmitPolling(*str);
		str++;
	}
}

void write_int(int num) {
	char str[10];
	itoa(num, str, 10);
	write_string(str);
}

void write_measurement(char *str,int num) {
  write_string(str);
  write_string(": ");
  write_int(num);
  write_string("\n");
}