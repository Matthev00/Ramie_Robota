#include "RestrictedShoulderJoint.h"
#include <fstream>

RestrictedShoulderJoint::RestrictedShoulderJoint() : ShoulderJoint()
{
	max_angle = 90;
}

RestrictedShoulderJoint::RestrictedShoulderJoint(const JointConnector& next_joint_connector,
	const Coordinates& coords = Coordinates(),
	const unsigned int max_angle = 90) :
	ShoulderJoint(next_joint_connector, coords)
{
	this->max_angle = max_angle % 360;
}

float RestrictedShoulderJoint::rotate(const int angle)
{
	if (angle<0 || angle>max_angle) {
		throw "Angle is beyond range.";
	}
	return ShoulderJoint::rotate(angle);
}

float RestrictedShoulderJoint::rotate_one_degree()
{
	if (alpha + 1 > max_angle) {
		throw "Angle is beyond range.";
	}
	return ShoulderJoint::rotate_one_degree();
}

unsigned int RestrictedShoulderJoint::get_max_angle() const
{
	return max_angle;
}

void RestrictedShoulderJoint::set_max_angle(const int max_angle)
{
	this->max_angle = max_angle % 360;
}

void RestrictedShoulderJoint::print() const
{
	ShoulderJoint::print();
	std::cout << "Max angle: " << max_angle << std::endl;
}
