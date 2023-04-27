#pragma once
#include "ShoulderJoint.h"
class RestrictedShoulderJoint :
    public ShoulderJoint
{
private:
    unsigned int max_angle;
public:
    RestrictedShoulderJoint(const JointConnector&, const Coordinates&, const unsigned int);
    float rotate(const int);
    float rotate_one_degree();
    unsigned int get_max_angle()const;
    void set_max_angle(const int);
};

