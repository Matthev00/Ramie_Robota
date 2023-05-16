#include "JointConnector.h"

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
	return -max_x();
}

std::ostream& operator<<(std::ostream & out, const JointConnector & toOut)
{
	out << static_cast<const BaseJointConnector>(toOut);
	out << "Angle: " << toOut.get_angle() << std::endl;
	return out;
}

std::istream& operator>>(std::istream & in, JointConnector & toLoad)
{
	// TODO: tu wstawi instrukcj return
	std::string helper;
	float newAngle;
	in >> static_cast<BaseJointConnector&>(toLoad);
	in >> helper >> newAngle;
	if (helper != "Angle:")
		throw std::exception("Invalid input");
	toLoad.set_angle(newAngle);
	return in;
}
