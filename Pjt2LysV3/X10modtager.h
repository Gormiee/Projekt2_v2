#pragma once

#include <iostream>

class X10modtager
{
	public:
	X10modtager(); //m�ske setpoint
	bool listenStart();
	int listenUseCase();
	void initX10Modtager();
	void setUseCase(int useCase);
	int getUseCase();
	protected:
	int useCase_;
	private:

};

