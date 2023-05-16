#pragma once
#include <math.h>
#include <iostream>
#include <stdexcept>
#include "coordinates.h"


class BaseJointConnector
{
protected:
	Coordinates begin_coordinates;
	Coordinates end_coordinates;

public:
	BaseJointConnector() {};
	BaseJointConnector(Coordinates, Coordinates);

	Coordinates get_begin_coordinates()const;
	void set_begin_coordinates(const Coordinates&);
	Coordinates get_end_coordinates()const;
	void set_end_coordinates(const Coordinates&);

	float get_lenght()const;
	// virtualne funkcje zeby wektor z referecjami dzialal
	friend std::ostream& operator<<(std::ostream&, const BaseJointConnector&);
	friend std::istream& operator>>(std::istream&, BaseJointConnector&);
};

