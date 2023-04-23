//Author: Mateusz Ostaszewski
#include "ShoulderJoint.h"
#include <math.h>
#include <cmath>

ShoulderJoint::ShoulderJoint(const JointConnector& next_joint_connector, const Coordinates& coords = Coordinates()) : Joint(next_joint_connector, coords)
{
	alpha = 0;
}

float ShoulderJoint::rotate(const int alpha)
{
	Coordinates coords_of_next_joint = my_next_joint_connector.get_end_coordinates();
	float new_x = 0.0f, new_y = 0.0f;
	double pi = 4.0 * std::atan(1.0);
	float tg_alpha = tan(alpha * pi / 180);
	float cos_alpha = cos(alpha * pi / 180);
	float sin_alpha = sin(alpha * pi / 180);
	float two_D_distance_from_O = sqrt(pow(coords_of_next_joint.x, 2) + pow(coords_of_next_joint.y, 2));
	if (alpha > -90 and alpha < 90) {
		float new_x = coords_of_next_joint.x + cos_alpha * two_D_distance_from_O;
	}
	else {
		float new_x = coords_of_next_joint.x - cos_alpha * two_D_distance_from_O;
	}
	if (alpha > 0 and alpha < 180) {
		float new_y = coords_of_next_joint.y + sin_alpha * two_D_distance_from_O;
	}
	else {
		float new_y = coords_of_next_joint.y - sin_alpha * two_D_distance_from_O;
	}
	Coordinates new_coords(new_x, new_y, coords_of_next_joint.z);
	my_next_joint_connector.set_coordinates(new_coords);
	this->alpha = alpha;
	return tg_alpha;
}

float ShoulderJoint::rotate_one_degree()
{
	return rotate(alpha + 1);
}
