#include "X10sender.h"

#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

X10sender::X10sender()
{
	UC_ = 101001;
	DDRB = 0xFF;
	TCCR0B = TCCR0B & 1111.1001; //prescaler på 1 ingen ingen
	TCCR0A = TCCR0A | 1100.0000;
	OCR0A = 0;
}

void X10sender::sendUseCase(int UC)
{

	OCR0A  = 66;
	_delay_ms(3);
	OCR0A  = 0;
	_delay_ms(1);

	for (int i = 0; i < 6; i++)
	{
		if (!(UC && (1 << 6 - i)))
		{
			_delay_ms(1);
		}
		else
		{
			OCR0A = 66;
			_delay_ms(1);
			OCR0A = 0; //eller 255 eller sluk for timer. men ved ikke hvordan
		}
	}

	_delay_ms(6);

}
