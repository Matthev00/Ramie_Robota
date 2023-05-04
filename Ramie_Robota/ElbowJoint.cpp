
#include "ElbowJoint.h"

ElbowJoint::ElbowJoint(const JointConnector& previous_joint_connector, const JointConnector& next_joint_connector) : Joint(next_joint_connector)
{
	this->my_previous_joint_connector = previous_joint_connector;
	coordinates = previous_joint_connector.get_end_coordinates();
}

JointConnector ElbowJoint::get_previous_joint_connector() const
{
	return my_previous_joint_connector;
}

void ElbowJoint::set_previous_joint_connector(const JointConnector& previous_joint_connector)
{
	my_previous_joint_connector = previous_joint_connector;
}

std::ostream& operator<<(std::ostream& out, const ElbowJoint& ej)
{
	out << static_cast<const Joint&>(ej);
	out << ej.my_previous_joint_connector;
	return out;
}

std::istream& operator>>(std::istream& in, ElbowJoint& ej)
{
	in >> static_cast<Joint&>(ej);
	in >> ej.my_next_joint_connector;
	return in;
}
