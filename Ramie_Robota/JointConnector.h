#pragma once
//Author: Krzysztof G�lcz
#include "coordinates.h"
#include "Joint.h"
#include <math.h>
#include "Wektor.h"

class JointConnector
{
private:
	Coordinates begin_coordinates;
	Coordinates end_coordinates;
	Wektor direction;
	
public:
	JointConnector(Coordinates, Coordinates);
	
	float count_length()const;

	
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

};