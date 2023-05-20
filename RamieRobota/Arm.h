// Author: Mateusz Ostaszewski
#pragma once
#include "Joint.h"
#include "ElbowJoint.h"
#include "ShoulderJoint.h"
#include "coordinates.h"
#include "Gripper.h"
#include "ExtandebleJointConnector.h"
#include <vector>
class Arm
{
private:
	Coordinates start_coords;
	ShoulderJoint shoulder;
	ElbowJoint elbow;
	JointConnector arm_part;
	ExtandebleJointConnector forearm;
	Gripper gripper;
	float lenght;
	float tg;
	float count_distance(const Coordinates&, const Coordinates&) const;
	bool same_quarter(const Coordinates&, const Coordinates&)const;
public:
	Arm();
	Arm(JointConnector&, ExtandebleJointConnector&, Coordinates = Coordinates());
	void update_after_shoulder_movement(std::vector<std::vector<Coordinates>>&, bool = false);
	void update_after_shoulder_re_bend(std::vector<std::vector<Coordinates>>&, bool = false);
	void update_after_elbow_forearm_movement(std::vector<std::vector<Coordinates>>&);
	void update_tg(const float);
	std::vector<std::vector<Coordinates>> reach_target(Coordinates&);
	std::vector<std::vector<Coordinates>> back_to_starting_pos();
	bool if_reachable(const Coordinates&) const;
	float get_range() const;

	float get_tg() const;
	float count_end_forearm_x()const;

	bool catch_object(const Coordinates&);
	void release();
};
