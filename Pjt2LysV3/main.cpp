/*
 * Pjt2LysV3.cpp
 *
 * Created: 11-05-2022 09:46:32
 * Author : malle
 */ 

#include <avr/io.h>
#define	F_CPU = 8000000
#include <avr/interrupt.h>
#include <util/delay.h>
#include "led.h"
#include "X10modtagerLys.h"

//Prototyper
void initExtInts();
void initTimer0();

// Global variabel, der t�ller antal Timer0 overflows (bem�rk: SKAL erkl�res volatile)
volatile unsigned int antal_overflows = 0;
volatile unsigned int antal_bits = 0;
volatile unsigned int setPoint = 10;

X10modtagerLys X10stue(15);

int main(void)
{
	initLEDport()
	initTimer0();
	sei();
	setPoint = X10stue.getSetPoint(); //�ndres til getSetpoint m�kse
	
    /* Replace with your application code */
    while (1)
    {
		while(newUseCase_ == oldUseCase_)
		{			
		}
		newUseCase_ = oldUseCase_;
		}
		if (X10stue.getUseCase() == 101010 || X10stue.getUseCase()=010101)
		{
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
  // LED6 toggles, n�r der har vaeret 62500 interrupts
  // = hvert sekund, da 8000000/1/256 = 1
  antal_overflows++;
  if (antal_overflows == 31250*SETPOINT)  //*setpoint og toggle ved setpoint*30 eller indtast to setpoints. Husk vi bruger en anden clock 8/4 MHz
  {
    turnOnLED(1);
  }
  else if (antal_overflows == 31250*SETPOINT*30)
  {
	turnOffLED(1);
  }
  else if (antal_overflows == 31250*180)
  {
	  antal_overflows = 0;
  }
}

// Interrupt service ZERO-Cross. INT1
ISR (INT1_vect)
{
	if (PIND2 == 1)
	{
		if (X10stue.listenStart())
		{
			X10stue.setUseCase(X10stue.listenUseCase());
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