//Author: Krzysztof Golcz
#pragma once
#include <math.h>
#include "BaseJointConnector.h"
#include "Wektor.h"
#include "coordinates.h"


class JointConnector :
	public BaseJointConnector
{
protected:
	float tg_angle;

public:
	JointConnector(Coordinates=Coordinates(), Coordinates = Coordinates(), float=0.0f);
	float get_angle()const;
	void set_angle(float);

	float max_x()const;
	float min_x()const;

	friend std::ostream& operator<<(std::ostream&, const JointConnector&);
	friend std::istream& operator>> (std::istream&, JointConnector&);
};
