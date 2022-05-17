#include "X10modtager.h"
#include <avr/io.h>


X10modtager::X10modtager()
{
	currentUseCase_ = stopSim_;
	DDRD = 0;
}


int X10modtager::listenUseCase(int antal_bits, int & modtaget)
{
	if (antal_bits < 4)
	{
		if(!PIND2 == (startBits_ && (1<<(3 - antal_bits))))
		{
			antal_bits = 0;
			return antal_bits;
		} else
		{
			antal_bits++;
			return antal_bits;
		}
	} else if (antal_bits < 10)
	{
		modtaget += (PIND2 << (10-antal_bits));
		antal_bits++;
		return antal_bits;
	}
	else if (antal_bits < 16 )
	{
		if(!PIND2 == 0)
		{
			modtaget = 0;
			antal_bits = 0;
			return antal_bits;
		}
		else
		{
			antal_bits++;
			return antal_bits;
		}
	}
}


int X10modtager::getCurrentUseCase()
{
	return currentUseCase_;
}

void X10modtager::setCurrentUseCase(int UC)
{
	currentUseCase_ = UC;
}
	
int X10modtager::getReceivedUseCase()
{
	return reveivedUseCase_;
}

void X10modtager::setReceivedUseCase(int UC)
{
	reveivedUseCase_ = UC;
}
