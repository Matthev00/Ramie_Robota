
#include "Joint.h"
class ElbowJoint :
    public Joint
{
private:
    JointConnector my_previous_joint_connector;
public:
    ElbowJoint(const JointConnector&, const JointConnector&);
    JointConnector get_previous_joint_connector()const;
    void set_previous_joint_connector(const JointConnector&);
    friend std::ostream& operator<<(std::ostream&, const ElbowJoint&);
    friend std::istream& operator>>(std::istream&, const ElbowJoint&);
};
