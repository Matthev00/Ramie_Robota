#include "JointConnector.h"
/*
JointConnector::JointConnector()
{
}

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

void JointConnector::update_end_coordinates()
{
}

float JointConnector::get_lenght() const
{
	return direction.count_distance();
}

float JointConnector::max_x() const
{
	return 0.0f;
}

float JointConnector::min_x() const
{
	return 0.0f;
}

std::ostream& operator<<(std::ostream& out, const JointConnector&)
{
	return out;
}

std::istream& operator>>(std::istream& in, JointConnector&)
{
	return in;
}*/
