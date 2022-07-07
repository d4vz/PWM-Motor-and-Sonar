#include "helper.h"

/*
-> Motor Esquerdo <-
ESTADOS		  	IN1 IN2
HORARIO 		   1 - 0
ANTI-HORARIO	 0 - 1
PONTO MORTO 	 0 - 0
FREIO 		 	   1 - 1

-> Motor direito <-
ESTADOS			  IN4 IN3
HORARIO 		   1 - 0
ANTI-HORARIO	 0 - 1
PONTO MORTO 	 0 - 0
FREIO 		 	   1 - 1
*/


void startEngine(int set, int clr) {
    set_bit(PORTC, set);
    clr_bit(PORTC, clr);
}

void stopEngine(int value1, int value2) {
    clr_bit(PORTC, value1);
    clr_bit(PORTC, value2);
}

void turnRight() {
  startEngine(IN1, IN2);
  startEngine(IN4, IN3);
}

void turnLeft() {
  startEngine(IN2, IN1);
  startEngine(IN3, IN4);
}

void goForward() {
  startEngine(IN1, IN2);
  startEngine(IN3, IN4);
}
