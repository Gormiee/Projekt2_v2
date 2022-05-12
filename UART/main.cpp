/***********************************************
* MSYS, LAB 12, Del 2                          *
* Software UART sender.                        *
*                                              *
* Henning Hargaard 20/11 2015                  *
************************************************/
#include <avr/io.h>
#define F_CPU 16000000
#include <util/delay.h>

#define DDR   DDRE
#define PORT PORTE
#define PINNR 1
#define BAUD  9600

#define NO_us 1000000/BAUD

// 8 data bit, no parity, 1 stop bit
void SendCharSW(char Tegn)
{
	unsigned char i;
	unsigned char x = Tegn;
	// Start bit
	PORT &= ~(1<<PINNR);
	_delay_us(NO_us);
	// 8 data bits (LSB first)
	for (i = 0; i<8; i++)
	{
		if(x & 0b00000001)
		PORT |= (1<<PINNR);
		else
		PORT &= ~(1<<PINNR);
		_delay_us(NO_us);
		x = x>>1;
	}
	PORT |= (1<<PINNR);
	_delay_us(NO_us);
}

int main(void)
{
	UCSR0B = 0;
	DDR |= (1<<PINNR);
	
		SendCharSW('A');
		SendCharSW('B');
		SendCharSW('C');
	
}

