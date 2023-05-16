// Author: Mateusz Ostaszewski
#include <fstream>
#include "ElbowJoint.h"

ElbowJoint::ElbowJoint() :Joint()
{
}

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
	coordinates = previous_joint_connector.get_end_coordinates();
}

void ElbowJoint::print() const
{
	std::cout << coordinates << my_previous_joint_connector << my_next_joint_connector;
}

void ElbowJoint::set_coordinates(const Coordinates& coords)
{
	Joint::set_coordinates(coords);
	my_previous_joint_connector.set_end_coordinates(coords);
}

