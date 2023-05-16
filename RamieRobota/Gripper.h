// Author: Mateusz Ostaszewski
#pragma once
#include "coordinates.h"

class Gripper
{
private:
	Coordinates coords;
	bool closed;
	float range;
public:
	Gripper();
	Gripper(const Coordinates&, const float = 1.0f);
	Coordinates get_coordinates()const;
	void set_coordinates(const Coordinates&);
	bool if_closed()const;
	void close();
	void open();
	float get_range()const;
	void set_range(const float);
};


