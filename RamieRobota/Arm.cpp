// Author: Mateusz Ostaszewski
#include "Arm.h"
#include "Joint.h"
#include "ElbowJoint.h"
#include <cmath>

float Arm::count_distance(const Coordinates& starting_point, const Coordinates& target)
{
	float target_distance = sqrt(
		pow(target.x - starting_point.x, 2) +
		pow(target.y - starting_point.y, 2) +
		pow(target.z - starting_point.z, 2));
	return target_distance;
}

Arm::Arm()
{
}

Arm::Arm(JointConnector& part_1, JointConnector& part_2, Coordinates coords)
{
	this->arm_part = part_1;
	this->forearm = part_2;
	ShoulderJoint sh(arm_part, coords);
	shoulder = sh;
	ElbowJoint el(arm_part, forearm);
	elbow = el;
	Gripper g(forearm.get_end_coordinates());
	gripper = g;
	/// max lenght of elbow
	tg = 0.0f;
	lenght = arm_part.get_lenght() + forearm.get_lenght();
}

void Arm::uptade_after_shoulder_movement()
{
	elbow.set_coordinates(arm_part.get_end_coordinates());

	float x_end = cout_end_forearm_x();
	float x = x_end - start_coords.x;
	float y = tg * x - start_coords.y;
	float old_z = forearm.get_end_coordinates().z;
	float new_z = sqrt(lenght * lenght - x * x - y * y);
	float begin_z = start_coords.z;
	float z = (begin_z + new_z < old_z) ? begin_z + new_z : begin_z - new_z;
	Coordinates coords(
		x + start_coords.x,
		y + start_coords.y,
		z);
	forearm.set_end_coordinates(coords);

	gripper.set_coordinates(coords);
}

void Arm::uptade_after_elbow_forearm_movement()
{
	gripper.set_coordinates(forearm.get_end_coordinates());
}

bool Arm::reach_target(Coordinates& target)
{
	float target_distance = count_distance(start_coords, target);

	if (target_distance > lenght) {
		return false;
	}

	float elbow_lenght = arm_part.get_lenght();

	if (target_distance > elbow_lenght) {
		// Dostosuj dugo forearm
	}
	/*
	*zegij bark troche
	*rotuj
	*zegnij bark
	*/
	shoulder.bend_one_unit();


	float old_distance = count_distance(elbow.get_coordinates(), target);
	float new_distance = old_distance - 0.000000001;
	while (new_distance < old_distance)
	{
		old_distance = new_distance;
		shoulder.rotate_one_degree();
		new_distance = count_distance(elbow.get_coordinates(), target);
	}
	shoulder.rotate(shoulder.get_alpha() - 1);


	new_distance = old_distance - 0.000000001;
	while (new_distance < old_distance)
	{
		old_distance = new_distance;
		shoulder.bend_0_1();
		new_distance = count_distance(elbow.get_coordinates(), target);
	}
	shoulder.re_bend();


	if (target_distance <= elbow_lenght) {
		/*
		*zegnij okie
		dostosuj dugo
		*/

		new_distance = old_distance - 0.000000001;
		while (new_distance < old_distance)
		{
			old_distance = new_distance;
			elbow.bend_0_1();
			new_distance = count_distance(elbow.get_coordinates(), target);
		}
		shoulder.re_bend();


		// Dostosuj Dugo
	}


	float final_distance = count_distance(gripper.get_coordinates(), target);
	if (final_distance > gripper.get_range()) return false;
	return true;
}

bool Arm::if_reachable(double x, double y, double z) const
{
	double dst = sqrt(x * x + y * y + z * z);
	if (dst <= lenght) {
		return true;
	}
	return false;
}

float Arm::get_range() const
{
	return lenght;
}

float Arm::get_tg() const
{
	return tg;
}

float Arm::cout_end_forearm_x() const
{
	float len = arm_part.get_lenght() + forearm.get_lenght();
	float y = arm_part.get_lenght();
	float x = arm_part.get_end_coordinates().x;
	return len * x / y;
}

void Arm::set_range(const float range)
{
	this->lenght = range;
}
