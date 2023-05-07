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
    float rotate(const int);
    float rotate_one_degree();
    int get_alpha()const;
    void set_alpha(const int);
    friend std::ostream& operator<<(std::ostream&, const ShoulderJoint&);
    friend std::istream& operator>>(std::istream&, ShoulderJoint&);
};
