/*
 * X10sender.cpp
 *
 * Created: 11-05-2022 13:34:11
 * Author : malle
 */ 

#include <avr/io.h>
#include "X10sender.h"
#define F_CPU 16000000

#define STARTBIT 1110
#define STOPBIT 000000

int oldUseCase = 010101;
int newUseCase = 010101;

void initExtInts();

X10sender X10s;

int main(void)
{
	
	// if (new code != old code)
	// tænd EIMSK |= 0b00000100;
	
    while (1) 
    {
		if (oldUseCase != newUseCase)
		{
			EIMSK |= 0b00000100;
		}
    }
}

ISR (INT1_vect)
{
	X10s.sendUseCase(newUseCase);
	X10s.sendUseCase(newUseCase);
}

void initExtInts()
{
	// ZERO-CROSS detekter, interrupt ved edge-skift. Ben44, PD1 INT0.
	EICRA = 0b00000100;
	// Enable extern interrupts INT1.
	EIMSK |= 0b00000000;
}

