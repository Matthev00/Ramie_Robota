#pragma once
#include <iostream>
#include "Wektor.h"
#include "BaseJointConnector.h"
class ExtandebleJointConnector :
	public BaseJointConnector
{
protected:
	Wektor direction;

	void update_directions();

	void update_end_coordinates();
public:
	ExtandebleJointConnector(Coordinates, Coordinates);

	Wektor get_direction() const;

	void set_direction(const Wektor& newDirection);

	void set_directions_and_update_end(const Wektor& direct);

	void set_end_and_update_directions(const Coordinates& newCoords);

	float get_lenght() const;

	void extend(const float);

	void extend_by_len(const float);

	friend std::ostream& operator<<(std::ostream&, const ExtandebleJointConnector&);
	friend std::istream& operator>> (std::istream&, ExtandebleJointConnector&);
};
