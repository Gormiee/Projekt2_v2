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

// Global variabel, der tæller antal Timer0 overflows (bemærk: SKAL erklæres volatile)
volatile unsigned int antal_overflows = 0;
volatile unsigned int setPoint = 10;

int main(void)
{
	initLEDport()
	initTimer0();
	
	X10modtagerLys X10stue();
	setPoint = X10stue.getsetPoint(); //ændres til getSetpoint måkse
	
    /* Replace with your application code */
    while (1) 
    {			
		while (!PIND(1) == 1)
		{
		}
		
		if (X10stue.listenStart())
		{
			X10stue.setUseCase(X10stue.listenUseCase());
		}		
    }
}

// Interrupt service rutine for Timer0 overflow
ISR(TIMER0_OVF_vect)
{
  // LED6 toggles, når der har vaeret 62500 interrupts
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

void initExtInts()
{
	// INT2:Falling edge, INT3:Rising edge
	EICRA = 0b11100000;
	// Enable extern interrupts INT2 og INT3
	EIMSK |= 0b00001100;
}

void initTimer0()
{
	// Timer0: Normal mode, PS = 1 (= "No prescaling")
	TCCR0A = 0b00000000;
	TCCR0B = 0b00000001;
	// Enable Timer0 overflow interrupt
	TIMSK0 |= 0b00000001;
}