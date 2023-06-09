// Author: Mateusz Ostaszewski
#pragma once
#include "ShoulderJoint.h"
#include "JointConnector.h"
class RestrictedShoulderJoint :
    public ShoulderJoint
{
private:
    unsigned int max_angle;
public:
    RestrictedShoulderJoint();
    RestrictedShoulderJoint(const JointConnector&, const Coordinates&, const unsigned int);
    float rotate(const int);
    float rotate_one_degree();
    unsigned int get_max_angle()const;
    void set_max_angle(const int);
    void print() const override;
};

