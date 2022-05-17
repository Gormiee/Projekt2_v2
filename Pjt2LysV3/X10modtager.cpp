#include "X10modtager.h"
#include <deque>
#include <util/delay.h>
#include <math.h>


X10modtager::X10modtager()
{
	useCase_ = 101001;
}



bool X10modtager::listenStart()
{
	int modtaget[4] = { 0 };

	for (int i = 0; i < 4; i++)
	{
		modtaget[i] = PIND2;
		_delay_ms(1);
	}

	if (modtaget[0] == 1 && modtaget[1] == 1 && modtaget[2] == 1 && modtaget[3] == 0)
	{
		return true;
	}
	else
	{
		return false;
	}
}

int X10modtager::listenUseCase()
{
	int UseCase1[12];
	int UseCase2[12];
	int vUseCase;  //validaret useCase.
	
	for (int i = 0; i < 12; i++)
	{
		UseCase1[i] = PIND2;
		_delay_ms(1);
	}
	
	if (!listenStart())	
	{
		return useCase_;
	}
	
	for (int i = 0; i < 12; i++)
	{
		UseCase2[i] = PIND2
	}
	
	for (int i = 0; i < 12; i++)
	{
		if(!UseCase1[i] == UseCase2[i])
		{
			return useCase_;
		}
		else
		{
			for (int i = 0; i < 6; i++)
			{
				vUseCase += (UseCase1[i]*pow(2,6-i));
			}
			return vUseCase;
		}
	}
	
}

void X10modtager::initX10Modtager()
{
	DDRD = 0;
}


int X10modtager::getUseCase()
{
	return useCase_;
}

int X10modtager::setUseCase(int UC)
{
	useCase_= UC;
}
	

