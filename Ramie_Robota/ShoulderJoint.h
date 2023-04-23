//Author: Mateusz Ostaszewski
#pragma once
#include "Joint.h"
class ShoulderJoint :
    public Joint
{
private:
    int alpha;
public:
    ShoulderJoint(const JointConnector&, const Coordinates&);
    float rotate(const int);
    float rotate_one_degree();
};
