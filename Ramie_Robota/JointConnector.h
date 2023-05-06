#pragma once
//Author: Krzysztof Gólcz
#include "coordinates.h"
#include <math.h>
#include "Wektor.h"

class JointConnector
{
private:
	Coordinates begin_coordinates;
	Coordinates end_coordinates;
	Wektor direction;
	float tg_angle;
public:
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

};