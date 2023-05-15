#include "Gripper.h"

Gripper::Gripper()
{
}

Gripper::Gripper(const Coordinates& coords, const float range)
{
	this->coords = coords;
	this->range = range;
	closed = false;
}

Coordinates Gripper::get_coordinates() const
{
	return coords;
}

void Gripper::set_coordinates(const Coordinates& coords)
{
	this->coords = coords;
}

bool Gripper::if_closed() const
{
	return closed;
}

void Gripper::close()
{
	closed = true;
}

void Gripper::open()
{
	closed = false;
}

float Gripper::get_range() const
{
	return range;
}

void Gripper::set_range(const float range)
{
	this->range = range;
}
