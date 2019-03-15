//#define F_CPU 16000000
#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>

int main(void) {
	DDRB = 0xFF;      // configure Port B dir register pins for output
	PORTB = 0x00;
	_delay_ms(500);

	DDRD = 0x00;
	PORTD = 0xFF;

	while (1) { // loop forever
		if (!(PIND & 0x02)) {
			for (int i = 0; i < 8; i++) {
				PORTB = 0x01 << i;
				_delay_ms(100);
			}
		}
		if(!(PIND & 0x01)) PORTB = 0x00;
	}
}
