/*
 * Pjt2LysV3.cpp
 *
 * Created: 11-05-2022 09:46:32
 * Author : malle
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include "LEDX10.h"
#include "X10modtagerLys.h"
#define	F_CPU = 8000000

//Prototyper
void initExtInts();
void initTimer0();

// Global variabel, der tæller antal Timer0 overflows (bemærk: SKAL erklæres volatile)
volatile unsigned int antal_overflows = 0;
volatile unsigned int antal_bits = 0;
volatile unsigned int setPoint = 10;

X10modtagerLys X10stue(15);

int main(void)
{
	initExtInts();
	initLEDport();
	initTimer0();
	sei();
	setPoint = X10stue.getSetPoint(); //ændres til getSetpoint måkse
	
    /* Replace with your application code */
    while (1)
    {
		while(X10stue.getCurrentUseCase() == X10stue.getReceivedUseCase())
		{
		}
		X10stue.setCurrentUseCase(X10stue.getReceivedUseCase());
		if (X10stue.getCurrentUseCase() == X10stue.lysOgLys_ || X10stue.getCurrentUseCase() == X10stue.kunLys_)
		{
			antal_overflows = 0;
			TIMSK0 |= 0b00000001;
		}
		else
		{
			TIMSK0 |= 0b00000000;
			antal_overflows = 0;
		}
    }
}

// Interrupt service rutine for Timer0 overflow
ISR(TIMER0_OVF_vect)
{
  // LED6 toggles, når der har vaeret 62500 interrupts
  // = hvert sekund, da 8000000/1/256 = 1
  antal_overflows++;
  if (antal_overflows == 31250*setPoint)  //*setpoint og toggle ved setpoint*30 eller indtast to setpoints. Husk vi bruger en anden clock 8/4 MHz
  {
    turnOnLED(1);
  }
  else if (antal_overflows == 31250*setPoint*30)
  {
	turnOffLED(1);
  }
  else if (antal_overflows == 31250*180)
  {
	  antal_overflows = 0;
  }
}


ISR (INT1_vect)
{
	static int firstUseCase = 0;
	static int secondUseCase = 0;
	static int modtagetFirst = 0;
	if (!modtagetFirst)
	{
		antal_bits = X10stue.listenUseCase(antal_bits, &firstUseCase);
		if (!antal_bits == 15)
		{
			return;
		}
		else
		{
			modtagetFirst = 1;
			antal_bits = 0;
			return;
		}
	}
	else
	{
		antal_bits = X10stue.listenUseCase(antal_bits, &secondUseCase);
		
		if (!antal_bits)
		{
			static int firstUseCase = 0;
			static int secondUseCase = 0;
			static int modtagetFirst = 0;
			return;
		} else if (antal_bits < 32)
		{
			return;
		}
		else if (secondUseCase == firstUseCase)
		{
			X10stue.setReceivedUseCase(firstUseCase);
			static int firstUseCase = 0;
			static int secondUseCase = 0;
			static int modtagetFirst = 0;
		}
		else
		{
			static int firstUseCase = 0;
			static int secondUseCase = 0;
			static int modtagetFirst = 0;
		}
	}
}

void initExtInts()
{
	// ZERO-CROSS detekter, interrupt ved edge-skift. Ben44, PD1 INT0.
	EICRA = 0b00000100;
	// Enable extern interrupts INT1.
	EIMSK |= 0b00000010;
}

void initTimer0()
{
	// Timer0: Normal mode, PS = 1 (= "No prescaling")
	TCCR0A = 0b00000000;
	TCCR0B = 0b00000001;
	// Enable Timer0 overflow interrupt
	TIMSK0 |= 0b00000000;
}