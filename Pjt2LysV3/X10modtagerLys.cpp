#include "X10modtagerLys.h"

X10modtagerLys::X10modtagerLys(int setLys): X10modtager();
{
	setPoint_ = (setLys > 0 && setLys < 180) ? setLys : 10;
}

int X10modtagerLys::getSetPoint()
{
	return setPoint_;
}
