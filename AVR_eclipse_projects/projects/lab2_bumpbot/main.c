/*
 This code will cause a Bot connected to the AVR board to
 move forward and when it touches an obstacle, it will reverse
 and turn away from the obstacle and resume forward motion.

 PORT MAP
 Port B, Pin 4 -> Output -> Right Motor Enable
 Port B, Pin 5 -> Output -> Right Motor Direction
 Port B, Pin 7 -> Output -> Left Motor Enable
 Port B, Pin 6 -> Output -> Left Motor Direction
 Port D, Pin 1 -> Input -> Left Whisker
 Port D, Pin 0 -> Input -> Right Whisker
 */

#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void) {
	while (1) // loop forever
	{
		DDRB = 0b11110000;      // configure Port B pins for Output | Input
		PORTB = 0b01100000;     // set initial value for Port B outputs

		DDRD = 0x00;		// Set Port D Data Direction Register for input
		//PORTD = 0b11111111;	    //Initialize Port D Data Register

		if (! (PIND & 0x02)) {	//if left
			PORTB = 0x00;
			_delay_ms(1000);
			PORTB = 0b00010000;
			_delay_ms(1000);
			PORTB = 0b00100000;
			_delay_ms(500);
		} else if (! (PIND & 0x01)) {	//if right
			PORTB = 0x00;
			_delay_ms(1000);
			PORTB = 0b10000000;
			_delay_ms(1000);
			PORTB = 0b01000000;
			_delay_ms(500);
		}

	}
}
