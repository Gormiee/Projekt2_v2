#pragma once

#include "X10modtager.h"


class X10modtagerLys : public X10modtager
{
	public:
	X10modtagerLys(int setPoint);
	int getSetPoint();
	private:
	int setPoint_;
};