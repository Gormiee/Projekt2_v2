#include "X10sender.h"

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

X10sender::X10sender()
{
	UC_ = 0b101001;
	DDRB = 0xFF;
	DDRD = 0;
	TCCR0B = TCCR0B & 0b11111001; //prescaler på 1 ingen ingen
	TCCR0A = TCCR0A | 0b11000000;
	OCR0A = 0;
}

void X10sender::sendBit(int bit)    //sender bit på OCR0A. Dette er ben B7/nr:26.
{
	if (!bit)
	{
		return;
	}
	else {
		OCR0A  = 66;
		_delay_ms(1);
		OCR0A  = 0;
		return;
	}
}

