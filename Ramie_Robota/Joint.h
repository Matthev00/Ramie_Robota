//Author: Mateusz Ostaszewski
#pragma once
#include "coordinates.h"
#include <iostream>
#include "JointConnector.h"
#include "Wektor.h"

// Only for task4
class JointConnector
{
private:
	Coordinates begin_coordinates;
	Coordinates end_coordinates;
	Wektor direction;
	float tg_angle;

public:
	JointConnector();
	JointConnector(Coordinates, Coordinates, float = 0.0f);


	Coordinates get_begin_coordinates()const;
	void set_begin_coordinates(const Coordinates&);
	Coordinates get_end_coordinates()const;
	void set_end_coordinates(const Coordinates&);
	Wektor get_direction()const;
	void set_direction(const Wektor&);

	void update_directions();

	void update_end_coordinates();
	float get_lenght()const;
	float max_x()const;
	float min_x()const;
	void set_tg_angle(const float);

	friend std::ostream& operator<<(std::ostream&, const JointConnector&);
	friend std::istream& operator>>(std::istream&, JointConnector&);
};
//

class Joint
{
protected:
	float tg_alpha;
	Coordinates coordinates;
	JointConnector my_next_joint_connector;
public:
	Joint();
	Joint(const JointConnector&);
	virtual Coordinates get_coordinates()const;
	virtual void set_coordinates(const Coordinates&);
	virtual void set_tg_alpha(const float);
	virtual float get_tg_alpha()const;
	virtual JointConnector get_my_next_joint_connector()const;
	virtual void set_my_next_joint_connector(const JointConnector&);
	virtual void bend(const int);
	virtual void bend_one_unit();
	virtual void bend_0_1();
	virtual void adjust_coords_of_next_joint_connector(const float);
	virtual void print()const;
	friend std::ostream& operator<<(std::ostream&, const Joint&);
	friend std::istream& operator>>(std::istream&, Joint&);
	virtual void save_to_file(std::string)const;
	virtual void read_from_file(std::string);
};

