//Author: Mateusz Ostaszewski
#pragma once
#include "coordinates.h"
#include <iostream>
#include "JointConnector.h"
#include "Wektor.h"


class Joint
{
protected:
	bool over = false;
	bool over2 = false;
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
	virtual JointConnector& get_my_next_joint_connector();
	virtual void set_my_next_joint_connector(const JointConnector&);
	virtual void bend(const int);
	virtual void bend_one_unit();
	virtual void bend_0_1();
	virtual void re_bend();
	virtual void adjust_coords_of_next_joint_connector(const float);
	virtual void adjust_coords_of_next_joint_connector_re_bend(const float);
	virtual void print()const;
	friend std::ostream& operator<<(std::ostream&, const Joint&);
	friend std::istream& operator>>(std::istream&, Joint&);
	virtual void save_to_file(std::string)const;
	virtual void read_from_file(std::string);
};
