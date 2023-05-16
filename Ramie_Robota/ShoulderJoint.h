//Author: Mateusz Ostaszewski
#pragma once
#include "Joint.h"
#include "JointConnector.h"
class ShoulderJoint :
    public Joint
{
protected:
    int alpha;
public:
    ShoulderJoint();
    ShoulderJoint(const JointConnector&, const Coordinates&);
    double rotate(const int);
    double rotate_one_degree();
    int get_alpha()const;
    void set_alpha(const int);
    void print() const override;
};

