/*
 * X10sender.cpp
 *
 * Created: 11-05-2022 13:34:11
 * Author : malle
 */ 

#include <avr/io.h>
#include "X10sender.h"
#define F_CPU 16000000
#include <util/delay.h>
#include <avr/interrupt.h>


#define STARTBIT 0b1110
#define STOPBIT 0b000000

int oldUseCase = 0b010101;
int newUseCase = 0b010101;

void initExtInts();

X10sender X10s;

int main(void)
{
	sei();	
	// if (new code != old code)
	// tænd EIMSK |= 0b00000100;
	
    while (1) 
    {
		if (oldUseCase != newUseCase)
		{
			EIMSK |= 0b00000010;   //sætter INT1 til any edge interrupt.
		}
    }
}

ISR (INT1_vect)
{
	static int antal_bits = 0;
	static int casesSend = 0;
	if (casesSend < 2)
	{
		X10s.sendBit(antal_bits);
		antal_bits++;
	}
	if(!(antal_bits == 16))
	{
		return;
	}
	else
	{
		casesSend++;
		antal_bits = 0;
		return;
	}
		
	if (casesSend == 2)
	{
		EIMSK |= 0b00000000;
	}
	
}

void initExtInts()
{
	// ZERO-CROSS detekter, interrupt ved edge-skift. Ben44, PD1 INT0.
	EICRA = 0b00000100;
	// Enable extern interrupts INT1.
	EIMSK |= 0b00000000;
}

