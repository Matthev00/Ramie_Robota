#include "Arm.h"
#include "Joint.h"
#include "ElbowJoint.h"
#include <cmath>

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
	range = arm_part.get_lenght() + forearm.get_lenght() + gripper.get_range();
	tg = 0.0f;
	lenght = arm_part.get_lenght() + forearm.get_lenght();
}

void Arm::uptade()
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

bool Arm::reach_target(Coordinates& target)
{
	float target_distance = sqrt(
		pow(target.x - start_coords.x, 2) +
		pow(target.y - start_coords.y, 2) +
		pow(target.z - start_coords.z, 2));

	if (target_distance > range) {
		return false;
	}

	float elbow_lenght = arm_part.get_lenght();

	if (target_distance > elbow_lenght) {
		/*
		Dostosuj d³ugoœæ forearm
		zegij bark troche
		rotuj
		zegnij bark
		chwyæ
		*/
	}
	else {
		/*
		zegij bark troche
		rotuj
		zegnij bark
		zegnij ³okieæ
		dostosuj d³ugoœæ
		chwyæ
		*/
	}



	return false;
}

bool Arm::if_reachable(double x, double y, double z) const
{
	double dst = sqrt(x * x + y * y + z * z);
	if (dst <= range) {
		return true;
	}
	return false;
}

float Arm::get_range() const
{
	return range;
}

float Arm::cout_end_forearm_x() const
{
	float len = arm_part.get_lenght() + forearm.get_lenght();
	float y = arm_part.get_lenght();
	float x = arm_part.get_end_coordinates().x;
	return len * x / y;
}
