#include "Arm.h"
#include <cmath>

Arm::Arm()
{
}

bool Arm::if_reachable(double x, double y, double z) const
{
	double dst = sqrt(x * x + y * y + z * z);
	if (dst <= range) {
		return true;
	}
	return false;
}

double Arm::get_range() const
{
	return range;
}

void Arm::set_range(double new_range)
{
	if (new_range < 0) {
		throw "Range can not be negative.";
	}
	range = new_range;
}
