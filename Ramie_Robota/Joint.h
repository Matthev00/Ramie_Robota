#pragma once
#include "coordinates.h"

class JointConnector
{
private:
	Coordinates begin_coordinates;
	Coordinates end_coordinates;
public:
	Coordinates get_begin_coordinates()const;
	Coordinates get_end_coordinates()const;
	int get_lenght()const;
	void set_coordinates(Coordinates);
	float max_x()const;
};

class Joint
{
private:
	Coordinates coordinates;
	JointConnector my_next_joint_connector;
public:
	Joint(Coordinates&, JointConnector&);
	float get_x_coordinate()const;
	float get_y_coordinate()const;
	float get_z_coordinate()const;
	Coordinates get_coordinates()const;
	void set_x_coordinate(const float);
	void set_y_coordinate(const float);
	void set_z_coordinate(const float);
	void set_coordinates(const Coordinates&);
	void bend(const int);
	void bend_one_unit();
	void bend_0_1();
	Coordinates operator++();
	void adjust_coords_of_next_joint_connector(const float);
};

