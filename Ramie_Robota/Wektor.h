#pragma once
#include <math.h>
class Wektor
{
public:
	float x, y, z;
	Wektor(){}
	Wektor(const float x, const float y, const float z)
	{
		this->x = x;
		this->y = y;
		this->z = z;
	}
	float count_distance()const
	{
		return sqrt(x * x + y * y + z * z);
	}
};

