//Author: Mateusz Ostaszewski
#pragma once
#include "coordinates.h"
#include <iostream>

class JointConnector
{
private:
	Coordinates begin_coordinates;
	Coordinates end_coordinates;
public:
	Coordinates get_begin_coordinates()const;
	Coordinates get_end_coordinates()const;
	int get_lenght()const;
	void set_end_coordinates(Coordinates);
	float max_x()const;
	float min_x()const;
	friend std::ostream& operator<<(std::ostream&, const JointConnector&);
	friend std::istream& operator>>(std::istream&, const JointConnector&);
};


class Joint
{
protected:
	Coordinates coordinates;
	JointConnector my_next_joint_connector;
public:
	Joint();
	Joint(const JointConnector&);
	float get_x_coordinate()const;
	float get_y_coordinate()const;
	float get_z_coordinate()const;
	Coordinates get_coordinates()const;
	void set_x_coordinate(const float);
	void set_y_coordinate(const float);
	void set_z_coordinate(const float);
	void set_coordinates(const Coordinates&);
	JointConnector get_my_next_joint_connector()const;
	void set_my_next_joint_connector(const JointConnector&);
	void bend(const int);
	void bend_one_unit();
	void bend_0_1();
	Coordinates operator++();
	void adjust_coords_of_next_joint_connector(const float);
	friend std::ostream& operator<<(std::ostream&, const Joint&);
	friend std::istream& operator>>(std::istream&, Joint&);
	void save_to_file(std::string);
	void read_from_file(std::string);
};

