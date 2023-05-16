// Author: Mateusz Ostaszewski
#pragma once
#include <istream>
struct Coordinates
{
	float x;
	float y;
	float z;
	Coordinates(float x = 0.0f, float y = 0.0f, float z = 0.0f) {
		this->x = x;
		this->y = y;
		this->z = z;
	}
	bool operator==(Coordinates);
	friend std::ostream& operator<<(std::ostream& out, const Coordinates& c);
	friend std::istream& operator>>(std::istream& in, Coordinates& c);
};
