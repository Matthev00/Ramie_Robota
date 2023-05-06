#include "JointConnector.h"

JointConnector::JointConnector(Coordinates begin, Coordinates end)
{
	begin_coordinates = begin;
	end_coordinates = end;
	float x_diff = end_coordinates.x - begin_coordinates.x;
	float y_diff = end_coordinates.y - begin_coordinates.y;
	float z_diff = end_coordinates.z - begin_coordinates.z;
	direction = Wektor(x_diff, y_diff, z_diff);
}

float JointConnector::count_length() const
{
	float len = direction.count_distance();
	return len;
}

Coordinates JointConnector::get_begin_coordinates() const
{
	return begin_coordinates;
}

void JointConnector::set_begin_coordinates(const Coordinates newBegin)
{
	begin_coordinates = newBegin;
}

Coordinates JointConnector::get_end_coordinates() const
{
	return end_coordinates;
}

void JointConnector::set_end_coordinates(const Coordinates newEnd)
{
	end_coordinates = newEnd;
}

Wektor JointConnector::get_direction() const
{
	return direction;
}

void JointConnector::set_direction(const Wektor newDirection)
{
	direction = newDirection;
}

void JointConnector::update_directions()
{
	float x_diff = end_coordinates.x - begin_coordinates.x;
	float y_diff = end_coordinates.y - begin_coordinates.y;
	float z_diff = end_coordinates.z - begin_coordinates.z;
	Wektor newDirection = Wektor(x_diff, y_diff, z_diff);
	set_direction(newDirection);
}

float JointConnector::get_lenght() const
{
	return direction.count_distance();
}
