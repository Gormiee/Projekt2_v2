/*************************************************
* "LED.C"                                        *
* Implementation file for "Mega2560 LED driver"  *
* Henning Hargaard, 22/9 2015                    *
**************************************************/
#include "LEDX10.h"
#include <avr/io.h>
#define MAX_LED_NR 7

void initLEDport()
{
	// S�t alle PORTB's ben til at v�re udgange
	DDRB = 0xFF;
	// Sluk alle lysdioderne
	PORTB = 0;
}

void writeAllLEDs(unsigned char pattern)
{
	// Hent parameteren og skriv til lysdioderne
	PORTB = pattern;
}

void turnOnLED(unsigned char led_nr)
{
	// Lokal variabel
	unsigned char mask;
	// Vi skal kun lave noget, hvis led_nr < 8
	if (led_nr <= MAX_LED_NR)
	{
		// Dan maske p� basis af parameteren (led_nr)
		mask = 0b00000001 << led_nr;
		// T�nd den aktuelle lysdiode (de andre �ndres ikke)
		PORTB = PINB | mask;
	}
}

void turnOffLED(unsigned char led_nr)
{
	// Lokal variabel
	unsigned char mask;
	// Vi skal kun lave noget, hvis led_nr < 8
	if (led_nr <= MAX_LED_NR)
	{
		// Dan (inverteret) maske p� basis af parameteren (led_nr)
		mask = ~(0b00000001 << led_nr);
		// Sluk den aktuelle lysdiode (de andre �ndres ikke)
		PORTB = PINB & mask;
	}
}

void toggleLED(unsigned char led_nr)
{
	// Lokal variabel
	unsigned char mask;
	// Vi skal kun lave noget, hvis led_nr < 8
	if (led_nr <= MAX_LED_NR)
	{
		// Dan maske p� basis af parameteren (led_nr)
		mask = 0b00000001 << led_nr;
		// Toggle den aktuelle lysdiode (de andre �ndres ikke)
		PORTB = PINB ^ mask;
	}
}
