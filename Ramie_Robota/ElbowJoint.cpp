
#include "ElbowJoint.h"

ElbowJoint::ElbowJoint(const JointConnector& previous_joint_connector, const JointConnector& next_joint_connector) : Joint(next_joint_connector)
{
	this->my_previous_joint_connector = previous_joint_connector;
	coordinates = previous_joint_connector.get_end_coordinates();
}
