#include "helper.h"

//motor1
// set_bit(PORTC, IN1);
// clr_bit(PORTC, IN2);

// clr_bit(PORTC, IN1);
// set_bit(PORTC, IN2);

// //motor2
// set_bit(PORTC, IN3);
// clr_bit(PORTC, IN4);

// clr_bit(PORTC, IN3);
// set_bit(PORTC, IN4);

void turnRight() {
  set_bit(PORTC, IN1);
	clr_bit(PORTC, IN2);

	clr_bit(PORTC, IN3);
  set_bit(PORTC, IN4);
}

void turnLeft() {
	clr_bit(PORTC, IN1);
  set_bit(PORTC, IN2);

  set_bit(PORTC, IN3);
	clr_bit(PORTC, IN4);
}

void goForward() {
  startEngine(IN1, IN2);
  startEngine(IN3, IN4);
}

void startEngine(int value1, int value2) {
		set_bit(PORTC, value1);
		clr_bit(PORTC, value2);
}

void stopEngine(int value1, int value2) {
    clr_bit(PORTC, value1);
    clr_bit(PORTC, value2);
}