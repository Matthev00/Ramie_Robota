//#include "Joint.h"
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

// Czy jest sens umozliwiac zmiane koncowych/wektora

JointConnector::JointConnector(Coordinates begin = Coordinates(), Coordinates end = Coordinates(), float tg = 0) : BaseJointConnector(begin, end)
{
	tg_angle = tg;
}

float JointConnector::get_angle() const
{
	return tg_angle;
}

void JointConnector::set_angle(float newAngle)
{
	tg_angle = newAngle;
}



float JointConnector::max_x() const
{
	float outcome = 0;
	float direction_squared = get_lenght() * get_lenght();
	float tg_squared = tg_angle * tg_angle;
	outcome = sqrt(direction_squared / (1 + tg_squared));
	return outcome;
}
float JointConnector::min_x() const
{
	float outcome = 0;
	float direction_squared = get_lenght() * get_lenght();
	float tg_squared = tg_angle * tg_angle;
	outcome = sqrt(direction_squared / (1 - tg_squared));
	return outcome;
}

std::ostream& operator<<(std::ostream& out, const JointConnector& toOut)
{
	out << static_cast<const BaseJointConnector>(toOut);
	out << "Angle: " << toOut.get_angle() << std::endl;
	return out;
}

std::istream& operator>>(std::istream& in, JointConnector& toLoad)
{
	// TODO: tu wstawiæ instrukcjê return
	std::string helper;
	float newAngle;
	in >> static_cast<BaseJointConnector&>(toLoad);
	in >> helper >> newAngle;
	if (helper != "Angle:")
		throw std::exception("Invalid input");
	toLoad.set_angle(newAngle);
	return in;
}

