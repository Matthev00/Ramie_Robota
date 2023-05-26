// Author: Krzysztof Golcz

#pragma once
#include <iostream>
#include "Wektor.h"
#include "JointConnector.h"
class ExtandebleJointConnector :
	public JointConnector
{
protected:
	Wektor direction;
	float inital_length;

	void update_directions();

	void update_end_coordinates();
public:
	ExtandebleJointConnector();
	ExtandebleJointConnector(Coordinates, Coordinates, float=0.0f);

	Wektor get_direction() const;

	void set_direction(const Wektor& newDirection);

	float get_initial_length()const;

	void set_directions_and_update_end(const Wektor& direct);

	void set_end_and_update_directions(const Coordinates& newCoords);

	float get_lenght() const;

	void extend(const float);

	void extend_by_len(const float);


	friend std::ostream& operator<<(std::ostream&, const ExtandebleJointConnector&);
	friend std::istream& operator>> (std::istream&, ExtandebleJointConnector&);
};
