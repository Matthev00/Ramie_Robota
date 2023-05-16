#include "ExtandebleJointConnector.h"

ExtandebleJointConnector::ExtandebleJointConnector(Coordinates begin, Coordinates end) : BaseJointConnector(begin, end)
{
	float x_diff = end_coordinates.x - begin_coordinates.x;
	float y_diff = end_coordinates.y - begin_coordinates.y;
	float z_diff = end_coordinates.z - begin_coordinates.z;
	direction = Wektor(x_diff, y_diff, z_diff);
}

Wektor ExtandebleJointConnector::get_direction()const
{
	return direction;
}

void ExtandebleJointConnector::set_direction(const Wektor& newDirection)
{
	direction = newDirection;
}


void ExtandebleJointConnector::update_directions()
{
	float x_diff = end_coordinates.x - begin_coordinates.x;
	float y_diff = end_coordinates.y - begin_coordinates.y;
	float z_diff = end_coordinates.z - begin_coordinates.z;
	Wektor newDirection = Wektor(x_diff, y_diff, z_diff);
	set_direction(newDirection);
}

void ExtandebleJointConnector::update_end_coordinates()
{
	float newx = begin_coordinates.x + direction.x;
	float newy = begin_coordinates.y + direction.y;
	float newz = begin_coordinates.z + direction.z;
	set_end_coordinates(Coordinates(newx, newy, newz));
}

void ExtandebleJointConnector::set_directions_and_update_end(const Wektor& direct)
{
	set_direction(direct);
	update_end_coordinates();
}

void ExtandebleJointConnector::set_end_and_update_directions(const Coordinates& newCoords)
{
	set_end_coordinates(newCoords);
	update_directions();
}

float ExtandebleJointConnector::get_lenght() const
{
	return direction.count_distance();
}

void ExtandebleJointConnector::extend(const float len_multiplyer)
{
	direction *= len_multiplyer;
	update_end_coordinates();
}

void ExtandebleJointConnector::extend_by_len(const float lenToAdd)
{
	direction.extend_by_len(lenToAdd);
	update_end_coordinates();
}

std::ostream& operator<<(std::ostream& out, const ExtandebleJointConnector& toOut)
{
	out << static_cast<const BaseJointConnector&>(toOut);
	out << "Direction: " << toOut.direction;
	return out;
}

std::istream& operator>>(std::istream& in, ExtandebleJointConnector& toLoad)
{
	// TODO: tu wstawiæ instrukcjê return
	std::string checker;
	Wektor wek;
	in >> static_cast<BaseJointConnector&>(toLoad);
	in >> checker;
	if (checker != "Direction:")
		throw std::exception("Wrong input");
	in >> wek;
	toLoad.set_directions_and_update_end(wek);
}
