// Author: Mateusz Ostaszewski
#include "Arm.h"
#include "Joint.h"
#include "ElbowJoint.h"
#include <vector>
#include <cmath>

float Arm::count_distance(const Coordinates& starting_point, const Coordinates& target) const
{
	float target_distance = sqrt(
		pow(target.x - starting_point.x, 2) +
		pow(target.y - starting_point.y, 2) +
		pow(target.z - starting_point.z, 2));
	return target_distance;
}

bool Arm::same_quarter(const Coordinates& c1, const Coordinates& c2) const
{
	if ((c1.x > 0 && c2.x > 0) || (c1.x <= 0 && c2.x <= 0)){
		if ((c1.y > 0 && c2.y > 0) || (c1.y <= 0 && c2.y <= 0)) {
			return true;
		}
	}
	return false;
}

Arm::Arm()
{
	this->lenght = 0;
	this->tg = 0;
}

Arm::Arm(JointConnector& part_1, ExtandebleJointConnector& part_2, Coordinates coords)
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
	tg = part_1.get_angle();
	lenght = arm_part.get_lenght() + forearm.get_lenght();
}

void Arm::update_after_shoulder_movement(std::vector<std::vector<Coordinates>>& arr, bool bend)
{
	elbow.set_coordinates(shoulder.get_my_next_joint_connector().get_end_coordinates());
	arm_part.set_end_coordinates(shoulder.get_my_next_joint_connector().get_end_coordinates());
	forearm.set_begin_coordinates(shoulder.get_my_next_joint_connector().get_end_coordinates());
	float x_end = count_end_forearm_x();
	float x = x_end - start_coords.x;
	float y = tg * x - start_coords.y;
	float old_z = forearm.get_end_coordinates().z;
	float z = old_z;
	if (bend) {
		float new_z = sqrt(lenght * lenght - x * x - y * y);
		float begin_z = start_coords.z;
		z = (begin_z + new_z < old_z) ? begin_z + new_z : begin_z - new_z;
	}
	
	Coordinates coords(
		x + start_coords.x,
		y + start_coords.y,
		z);
	////
	forearm.set_begin_coordinates(shoulder.get_my_next_joint_connector().get_end_coordinates());
	forearm.set_end_coordinates(coords);
	elbow.get_my_next_joint_connector().set_begin_coordinates(forearm.get_begin_coordinates());
	elbow.get_my_next_joint_connector().set_end_coordinates(forearm.get_end_coordinates());

	gripper.set_coordinates(coords);
	arr[0].push_back(shoulder.get_coordinates());
	arr[1].push_back(elbow.get_coordinates());
	arr[2].push_back(gripper.get_coordinates());
}

void Arm::update_after_shoulder_re_bend(std::vector<std::vector<Coordinates>>& arr, bool bend)
{
	elbow.set_coordinates(shoulder.get_my_next_joint_connector().get_end_coordinates());
	arm_part.set_end_coordinates(shoulder.get_my_next_joint_connector().get_end_coordinates());
	forearm.set_begin_coordinates(shoulder.get_my_next_joint_connector().get_end_coordinates());
	float x_end = count_end_forearm_x();
	float x = x_end - start_coords.x;
	float y = tg * x - start_coords.y;
	float old_z = forearm.get_end_coordinates().z;
	float z = old_z;
	if (bend) {
		float new_z = sqrt(lenght * lenght - x * x - y * y);
		float begin_z = start_coords.z;
		z = (begin_z + new_z > old_z) ? begin_z + new_z : begin_z - new_z;
	}

	Coordinates coords(
		x + start_coords.x,
		y + start_coords.y,
		z);
	////
	forearm.set_begin_coordinates(shoulder.get_my_next_joint_connector().get_end_coordinates());
	forearm.set_end_coordinates(coords);
	elbow.get_my_next_joint_connector().set_begin_coordinates(forearm.get_begin_coordinates());
	elbow.get_my_next_joint_connector().set_end_coordinates(forearm.get_end_coordinates());

	gripper.set_coordinates(coords);
	arr[0].push_back(shoulder.get_coordinates());
	arr[1].push_back(elbow.get_coordinates());
	arr[2].push_back(gripper.get_coordinates());
}

void Arm::update_after_elbow_forearm_movement(std::vector<std::vector<Coordinates>>& arr)
{
	forearm.set_end_coordinates(elbow.get_my_next_joint_connector().get_end_coordinates());
	gripper.set_coordinates(forearm.get_end_coordinates());
	arr[0].push_back(shoulder.get_coordinates());
	arr[1].push_back(elbow.get_coordinates());
	arr[2].push_back(gripper.get_coordinates());
}

void Arm::update_tg(const float tg)
{
	arm_part.set_angle(tg);
	elbow.set_tg_alpha(tg);
	elbow.get_my_next_joint_connector().set_angle(tg);
	forearm.set_angle(tg);
}

std::vector<std::vector<Coordinates>> Arm::reach_target(Coordinates& target)
{
	// coords arr
	std::vector<std::vector<Coordinates>> coords_arr(4);


	float target_distance = count_distance(start_coords, target);

	if (!if_reachable(target)) {
		throw "Target out of range!";
	}
	float eps = 0.01;
	float elbow_lenght = arm_part.get_lenght();

	if (target_distance > elbow_lenght) {
		// Dostosuj dugo forearm
		while (abs(lenght - target_distance) >= eps) {
			forearm.extend(0.97f);
			lenght = arm_part.get_lenght() + forearm.get_lenght();
			update_after_elbow_forearm_movement(coords_arr);
		}
	}
	/*
	*zegij bark troche
	*rotuj
	*zegnij bark
	*/
	shoulder.bend_one_unit();
	update_after_shoulder_movement(coords_arr, true);

	////// Do poprawy
	float old_distance = count_distance(elbow.get_coordinates(), target);
	float new_distance = old_distance - 0.00001;
	while (new_distance < old_distance || !same_quarter(target, elbow.get_coordinates()))
	{
		old_distance = new_distance;
		tg = shoulder.rotate_one_degree();
		update_after_shoulder_movement(coords_arr);
		update_tg(tg);
		new_distance = count_distance(elbow.get_coordinates(), target);
	}
	tg=shoulder.rotate(shoulder.get_alpha() - 1);
	update_after_shoulder_movement(coords_arr);
	update_tg(tg);


	new_distance = old_distance - 0.00001;
	while (new_distance < old_distance)
	{
		old_distance = new_distance;
		shoulder.bend_0_1();
		update_after_shoulder_movement(coords_arr, true);
		new_distance = count_distance(elbow.get_coordinates(), target);
	}
	shoulder.re_bend();
	update_after_shoulder_re_bend(coords_arr, true);


	if (target_distance <= elbow_lenght) {
		
		shoulder.re_bend();
		update_after_shoulder_re_bend(coords_arr, true);
		shoulder.re_bend();
		update_after_shoulder_re_bend(coords_arr, true);

		new_distance = count_distance(target, elbow.get_coordinates());
		Coordinates begin_coordinates = elbow.get_coordinates();
		Coordinates end_coordinates = gripper.get_coordinates();
		float x_diff = end_coordinates.x - begin_coordinates.x;
		float y_diff = end_coordinates.y - begin_coordinates.y;
		float z_diff = end_coordinates.z - begin_coordinates.z;
		Wektor newDirection = Wektor(x_diff, y_diff, z_diff);
		forearm.set_direction(newDirection);

		while (elbow.get_my_next_joint_connector().get_lenght() > new_distance)
		{
			forearm.extend(0.98f);
			elbow.get_my_next_joint_connector().set_begin_coordinates(forearm.get_begin_coordinates());
			elbow.get_my_next_joint_connector().set_end_coordinates(forearm.get_end_coordinates());
			update_after_elbow_forearm_movement(coords_arr);
		}
		forearm.extend(100.0f / 98.0f);
		update_after_elbow_forearm_movement(coords_arr);
		/*
		*zegnij okie
		*/
		

		new_distance = count_distance(target, gripper.get_coordinates());
		old_distance = new_distance + 1;
		while (new_distance < old_distance)
		{
			old_distance = new_distance;
			elbow.bend_0_1();
			update_after_elbow_forearm_movement(coords_arr);
			new_distance = count_distance(gripper.get_coordinates(), target);
		}
		elbow.re_bend();
		update_after_elbow_forearm_movement(coords_arr);

	}


	float final_distance = count_distance(gripper.get_coordinates(), target);
	return coords_arr;
}

std::vector<std::vector<Coordinates>> Arm::back_to_starting_pos()
{
	std::vector<std::vector<Coordinates>> coords_arr(4);
	float eps = 0.01f;
	while (shoulder.get_alpha() != 0) {
		shoulder.rotate_one_degree();
		update_after_shoulder_movement(coords_arr);
	}
	while (abs(arm_part.get_end_coordinates().x)<eps)
	{
		shoulder.re_bend();
		update_after_shoulder_re_bend(coords_arr, true);
	}
	while (abs(forearm.get_end_coordinates().x) < eps)
	{
		elbow.re_bend();
		update_after_elbow_forearm_movement(coords_arr);
	}
	// Wróciæ do d³ugoœci pocz¹tkowej forearm
	return coords_arr;
}

bool Arm::if_reachable(const Coordinates& coords) const
{
	double dst = count_distance(start_coords, coords);
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

float Arm::count_end_forearm_x() const
{
	float len = arm_part.get_lenght() + forearm.get_lenght();
	float y = arm_part.get_lenght();
	float x = arm_part.get_end_coordinates().x;
	return len * x / y;
}


