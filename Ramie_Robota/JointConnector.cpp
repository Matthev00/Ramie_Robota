#include "JointConnector.h"
/*
JointConnector::JointConnector()
{
}

JointConnector::JointConnector(Coordinates begin, Coordinates end, float tg = 0)
{
	begin_coordinates = begin;
	end_coordinates = end;
	tg_angle = tg;
	const float x_diff = end_coordinates.x - begin_coordinates.x;
	const float y_diff = end_coordinates.y - begin_coordinates.y;
	const float z_diff = end_coordinates.z - begin_coordinates.z;
	direction = Wektor(x_diff, y_diff, z_diff);
}

Coordinates JointConnector::get_begin_coordinates() const
{
	return begin_coordinates;
}

void JointConnector::set_begin_coordinates(const Coordinates newBegin)
{
	begin_coordinates = newBegin;
	update_directions();
}

Coordinates JointConnector::get_end_coordinates() const
{
	return end_coordinates;
}

void JointConnector::set_end_coordinates(const Coordinates newEnd)
{
	end_coordinates = newEnd;
	update_directions();
}

Wektor JointConnector::get_direction() const
{
	return direction;
}

void JointConnector::set_direction(const Wektor newDirection)
{
	direction = newDirection;
	update_end_coordinates();
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
	float newx = begin_coordinates.x + direction.x;
	float newy = begin_coordinates.y + direction.y;
	float newz = begin_coordinates.z + direction.z;
	set_end_coordinates(Coordinates(newx, newy, newz));
}

float JointConnector::get_lenght() const
{
	return direction.count_distance();
}

float JointConnector::max_x() const
{
	float outcome = 0;
	float direction_squared = direction.count_distance() * direction.count_distance();
	float tg_squared = tg_angle * tg_angle;
	outcome = sqrt(direction_squared / (1 + tg_squared));
	return outcome;
}
float JointConnector::min_x() const
{
	float outcome = 0;
	float direction_squared = direction.count_distance() * direction.count_distance();
	float tg_squared = tg_angle * tg_angle;
	outcome = sqrt(direction_squared / (1 - tg_squared));
	return outcome;
}

std::ostream& operator<<(std::ostream& out, const JointConnector&)
{
	return out;
}

std::istream& operator>>(std::istream& in, JointConnector&)
{
	return in;
}
*/
