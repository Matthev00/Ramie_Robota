//Author: Mateusz Ostaszewski
#include "ShoulderJoint.h"
#include <math.h>
#include <cmath>
#include <fstream>

ShoulderJoint::ShoulderJoint() : Joint()
{
	coordinates = Coordinates();
	alpha = 0;
}

ShoulderJoint::ShoulderJoint(const JointConnector& next_joint_connector, const Coordinates& coords) : Joint(next_joint_connector)
{
	coordinates = coords;
	alpha = 0;
}

double ShoulderJoint::rotate(const int alp)
{
	int alpha = alp % 360;

	if (alpha == 90 || alpha == 270)
		alpha = alpha + 1;
	Coordinates coords_of_next_joint = my_next_joint_connector.get_end_coordinates();
	float new_x = 0.0f, new_y = 0.0f;
	double pi = 4.0 * std::atan(1.0);
	double tg_alpha = tan(alpha * pi / 180);
	double cos_alpha = cos(alpha * pi / 180);
	double sin_alpha = sin(alpha * pi / 180);
	double two_D_distance_from_O = sqrt(pow(coords_of_next_joint.x, 2) + pow(coords_of_next_joint.y, 2));

	new_x = coordinates.x + cos_alpha * two_D_distance_from_O;
	new_y = coordinates.y + sin_alpha * two_D_distance_from_O;

	Coordinates new_coords(new_x, new_y, coords_of_next_joint.z);
	my_next_joint_connector.set_end_coordinates(new_coords);
	this->alpha = alpha;
	this->tg_alpha = tg_alpha;
	return tg_alpha;
}

double ShoulderJoint::rotate_one_degree()
{
	return rotate(alpha + 1);
}

int ShoulderJoint::get_alpha() const
{
	return alpha;
}

void ShoulderJoint::set_alpha(const int alpha)
{
	rotate(alpha);
}

void ShoulderJoint::print() const
{
	Joint::print();
	std::cout << "Alpha: " << alpha << std::endl;
}
