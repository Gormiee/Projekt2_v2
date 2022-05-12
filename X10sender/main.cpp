/*
 * X10sender.cpp
 *
 * Created: 11-05-2022 13:34:11
 * Author : malle
 */ 

#include <avr/io.h>
#include "X10sender.h"
#define F_CPU 16000000

int main(void)
{
	X10sender X10s;
    /* Replace with your application code */
    while (1) 
    {
			X10s.sendUseCase(010101);
			_delay_ms(10000);
			X10s.sendUseCase(101001);
			_delay_ms(10000);	
    }
}

