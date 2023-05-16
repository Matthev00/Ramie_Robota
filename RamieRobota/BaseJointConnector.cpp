#include "BaseJointConnector.h"

// Czy jest sens umozliwiac zmiane koncowych/wektora

BaseJointConnector::BaseJointConnector()
{
	begin_coordinates = Coordinates();
	end_coordinates = Coordinates();
}

BaseJointConnector::BaseJointConnector(Coordinates begin, Coordinates end)
{
	begin_coordinates = begin;
	end_coordinates = end;
}

Coordinates BaseJointConnector::get_begin_coordinates() const
{
	return begin_coordinates;
}

void BaseJointConnector::set_begin_coordinates(const Coordinates& newBegin)
{
	begin_coordinates = newBegin;
}

Coordinates BaseJointConnector::get_end_coordinates() const
{
	return end_coordinates;
}

void BaseJointConnector::set_end_coordinates(const Coordinates& newEnd)
{
	end_coordinates = newEnd;
}


float BaseJointConnector::get_lenght() const
{
	float x_diff = end_coordinates.x - begin_coordinates.x;
	float y_diff = end_coordinates.y - begin_coordinates.y;
	float z_diff = end_coordinates.z - begin_coordinates.z;
	float output = sqrt((x_diff * x_diff) + (y_diff * y_diff) + (z_diff * z_diff));
	return output;

}

std::ostream& operator<<(std::ostream& out, const BaseJointConnector& toOut)
{
	
	out << "Begin: " << toOut.begin_coordinates << "End: " << toOut.end_coordinates;
	return out;
}

std::istream& operator>>(std::istream& in, BaseJointConnector& toLoad)
{
	
	std::string helper;
	in >> helper;
	if (helper != "Begin:")
		throw std::exception("Incorect input");
	Coordinates temp;
	in >> temp >> helper;
	toLoad.set_begin_coordinates(temp);
	if (helper != "End:")
		throw std::exception("Incorect input");
	in >> temp;
	toLoad.set_end_coordinates(temp);
	return in;
}

