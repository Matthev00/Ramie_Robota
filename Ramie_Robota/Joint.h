//Author: Mateusz Ostaszewski
#pragma once
#include "coordinates.h"
#include <iostream>
#include "Wektor.h"

class JointConnector
{
private:
	Coordinates begin_coordinates;
	Coordinates end_coordinates;
	Wektor direction;
	float tg_angle;

public:
	JointConnector();
	JointConnector(Coordinates, Coordinates, float);


	Coordinates get_begin_coordinates()const;
	void set_begin_coordinates(const Coordinates);
	Coordinates get_end_coordinates()const;
	void set_end_coordinates(const Coordinates);
	Wektor get_direction()const;
	void set_direction(const Wektor);

	void update_directions();

	void update_end_coordinates();
	float get_lenght()const;
	float max_x()const;
	float min_x()const;
	void set_tg_angle(const float);

	friend std::ostream& operator<<(std::ostream&, const JointConnector&);
	friend std::istream& operator>>(std::istream&, JointConnector&);
};


class Joint
{
protected:
	float tg_alpha;
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
	void set_tg_alpha(const float);
	float get_tg_alpha();
	JointConnector get_my_next_joint_connector()const;
	void set_my_next_joint_connector(const JointConnector&);
	void bend(const int);
	void bend_one_unit();
	void bend_0_1();
	void adjust_coords_of_next_joint_connector(const float);
	friend std::ostream& operator<<(std::ostream&, const Joint&);
	friend std::istream& operator>>(std::istream&, Joint&);
	void save_to_file(std::string);
	void read_from_file(std::string);
};

