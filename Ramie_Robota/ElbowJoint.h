
#include "Joint.h"
class ElbowJoint :
    public Joint
{
private:
    JointConnector my_previous_joint_connector;
public:
    ElbowJoint(const JointConnector&, const JointConnector&);
};
