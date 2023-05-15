#pragma once
#include "JointConnector.h"
#include "Joint.h"


class ElbowJoint :
    public Joint
{
private:
    JointConnector my_previous_joint_connector;
public:
    ElbowJoint();
    ElbowJoint(const JointConnector&, const JointConnector&);
    JointConnector get_previous_joint_connector()const;
    void set_previous_joint_connector(const JointConnector&);
    void print() const override;
};

