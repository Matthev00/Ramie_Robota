// Author: Mateusz Ostaszewski
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
	float lenght;
	float tg;
	float count_distance(const Coordinates&, const Coordinates&);
public:
	Arm();
	Arm(JointConnector&, JointConnector&, Coordinates = Coordinates());
	void uptade_after_shoulder_movement();
	void uptade_after_elbow_forearm_movement();
	bool reach_target(Coordinates&);
	bool if_reachable(double, double, double) const;
	// do usuniêcia
	float get_range() const;
	void set_range(const float);
	//

	float get_tg() const;
	float cout_end_forearm_x()const;
};
