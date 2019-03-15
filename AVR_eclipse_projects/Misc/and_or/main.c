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
#include <lcd.h>



int main(void) {
	lcd_init(0);
	lcd_clrscr();
	lcd_puts("hello");

	while (1) // loop forever
	{
		//output port B
		DDRB = 0xFF;
		PORTB = 0x00;

		//input port D
		DDRD = 0x00;
		PORTD = 0xFF; //Initialize Port D Data Register so all Port D inputs are Tri-State

		if(!(PIND & 0x01)){
			PORTB |= 0x01;
			_delay_ms(500);
		}
		else{
			PORTB &= 0xFE;	//
		}

	}
}
