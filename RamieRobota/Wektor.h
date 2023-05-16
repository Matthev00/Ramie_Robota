#pragma once
#include <math.h>
#include <iostream>
#include "coordinates.h"
class Wektor
{
public:
	float x, y, z;
	Wektor();
	Wektor(const float, const float, const float);
	Wektor(const Coordinates&, const Coordinates&);
	float count_distance()const;
	void operator*= (const float);
	Wektor operator*(float)const;
	bool operator==(const Wektor&);
	void extend_by_len(const float);
	Wektor mult_by_float(const float)const;
	Wektor extend_by_len_whithout_changing(const float)const;
	friend std::ostream& operator<<(std::ostream&, const Wektor&);
	friend std::istream& operator>> (std::istream&, Wektor&);
};
