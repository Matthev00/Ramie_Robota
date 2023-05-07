#include "CppUnitTest.h"
#include "../Ramie_Robota/Joint.h"
#include "../Ramie_Robota/coordinates.h"
#include "../Ramie_Robota/Joint.cpp"
#include "../Ramie_Robota/coordinates.cpp"
#include "../Ramie_Robota/ElbowJoint.h"
#include "../Ramie_Robota/ElbowJoint.cpp"
#include "../Ramie_Robota/ShoulderJoint.h"
#include "../Ramie_Robota/ShoulderJoint.cpp"
#include "../Ramie_Robota/RestrictedShoulderJoint.h"
#include "../Ramie_Robota/RestrictedShoulderJoint.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace JointTest
{
	TEST_CLASS(JointTest)
	{
	public:

		TEST_METHOD(constructor_for_joints_classes)
		{
			Joint j;
			ElbowJoint ej;
			ShoulderJoint sj;
			RestrictedShoulderJoint rsj;
			Coordinates c;
			Assert::AreEqual(true, c==j.get_coordinates());
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_begin_coordinates());
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());

			Assert::AreEqual(true, c == ej.get_coordinates());
			Assert::AreEqual(true, c == ej.get_my_next_joint_connector().get_begin_coordinates());
			Assert::AreEqual(true, c == ej.get_my_next_joint_connector().get_end_coordinates());
			
			Assert::AreEqual(true, c == sj.get_coordinates());
			Assert::AreEqual(true, c == sj.get_my_next_joint_connector().get_begin_coordinates());
			Assert::AreEqual(true, c == sj.get_my_next_joint_connector().get_end_coordinates());
			Assert::AreEqual(0, sj.get_alpha());

			Assert::AreEqual(true, c == rsj.get_coordinates());
			Assert::AreEqual(true, c == rsj.get_my_next_joint_connector().get_begin_coordinates());
			Assert::AreEqual(true, c == rsj.get_my_next_joint_connector().get_end_coordinates());
			Assert::AreEqual(0, rsj.get_alpha());
			Assert::AreEqual(unsigned int(90), rsj.get_max_angle());

		}

		TEST_METHOD(coors_setters_for_joints_classes)
		{
			Coordinates c(1, 1, 1);
			Joint j;
			j.set_coordinates(c);
			ElbowJoint ej;
			ej.set_coordinates(c);
			ShoulderJoint sj;
			sj.set_coordinates(c);
			RestrictedShoulderJoint rsj;
			rsj.set_coordinates(c);
			Coordinates c2(2, 3, 4);
			

			Assert::AreEqual(true, c == j.get_coordinates());
			j.set_x_coordinate(2);
			j.set_y_coordinate(3);
			j.set_z_coordinate(4);
			Assert::AreEqual(true, c2 == j.get_coordinates());

			Assert::AreEqual(true, c == ej.get_coordinates());
			ej.set_x_coordinate(2);
			ej.set_y_coordinate(3);
			ej.set_z_coordinate(4);
			Assert::AreEqual(true, c2 == ej.get_coordinates());

			Assert::AreEqual(true, c == sj.get_coordinates());
			sj.set_x_coordinate(2);
			sj.set_y_coordinate(3);
			sj.set_z_coordinate(4);
			Assert::AreEqual(true, c2 == sj.get_coordinates());
			
			Assert::AreEqual(true, c == rsj.get_coordinates());
			rsj.set_x_coordinate(2);
			rsj.set_y_coordinate(3);
			rsj.set_z_coordinate(4);
			Assert::AreEqual(true, c2 == rsj.get_coordinates());

		}
	};
}
