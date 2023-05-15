#pragma once
#include "Joint.h"
#include "ElbowJoint.h"
#include "ShoulderJoint.h"
#include "coordinates.h"
#include "Gripper.h"
class Arm
{
private:
	Coordinates start_coords;
	ShoulderJoint shoulder;
	ElbowJoint elbow;
	JointConnector arm_part;
	JointConnector forearm;
	Gripper gripper;
	float range;
	float lenght;
	float tg;

public:
	Arm();
	Arm(JointConnector&, JointConnector&, Coordinates = Coordinates());
	void uptade();
	bool reach_target(Coordinates&);
	bool if_reachable(double, double, double) const;
	float get_range() const;
	float get_tg() const;
	float cout_end_forearm_x()const;
};
