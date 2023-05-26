// Author: Krzysztof Golcz

#include "Wektor.h"

Wektor::Wektor()
{
	x = 0;
	y = 0;
	z = 0;
}

Wektor::Wektor(const float x, const float y, const float z)
{
	this->x = x;
	this->y = y;
	this->z = z;
}

Wektor::Wektor(const Coordinates& begin, const Coordinates& end)
{
	x = end.x - begin.x;
	y = end.y - begin.y;
	z = end.z - begin.z;
}

float Wektor::count_distance() const
{
	return sqrt(x * x + y * y + z * z);
}

void Wektor::operator*=(const float multiplyer)
{
	x *= multiplyer;
	y *= multiplyer;
	z *= multiplyer;
}

Wektor Wektor::operator*(const float mult)const
{
	return Wektor(x * mult, y * mult, z * mult);
}

bool Wektor::operator==(const Wektor& another)
{
	return x == another.x && y == another.y && z == another.z;
}

void Wektor::extend_by_len(const float len_to_extand)
{
	float goal_len = count_distance() + len_to_extand;
	float multiplyer = goal_len / count_distance();
	*this *= multiplyer;
}

Wektor Wektor::mult_by_float(const float mult) const
{
	return Wektor(x * mult, y * mult, z * mult);
}

Wektor Wektor::extend_by_len_whithout_changing(const float len_to_extand) const
{
	float goal_len = count_distance() + len_to_extand;
	float multiplyer = goal_len / count_distance();
	return this->mult_by_float(multiplyer);
}

std::ostream& operator<<(std::ostream& out, const Wektor& toOut)
{
	// TODO: tu wstawi instrukcj return
	out << toOut.x << ' ' << toOut.y << ' ' << toOut.z << '\n';
	return out;
}

std::istream& operator>>(std::istream& in, Wektor& toLoad)
{
	// TODO: tu wstawi instrukcj return
	float xx, yy, zz;
	in >> xx >> yy >> zz;
	toLoad.x = xx;
	toLoad.y = yy;
	toLoad.z = zz;
	return in;
}
