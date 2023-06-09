//Author: Mateusz Ostaszewski

#include <math.h>
#include <cmath>
#include "CppUnitTest.h"
#include "../RamieRobota/Joint.h"
#include "../RamieRobota/coordinates.h"
#include "../RamieRobota/Joint.cpp"
#include "../RamieRobota/JointConnector.h"
#include "../RamieRobota/JointConnector.cpp"
#include "../RamieRobota/coordinates.cpp"
#include "../RamieRobota/ElbowJoint.h"
#include "../RamieRobota/ElbowJoint.cpp"
#include "../RamieRobota/ShoulderJoint.h"
#include "../RamieRobota/ShoulderJoint.cpp"
#include "../RamieRobota/RestrictedShoulderJoint.h"
#include "../RamieRobota/RestrictedShoulderJoint.cpp"
#include "../RamieRobota/Gripper.h"
#include "../RamieRobota/Gripper.cpp"
#include "../RamieRobota/BaseJointConnector.h"
#include "../RamieRobota/BaseJointConnector.cpp"
#include "../RamieRobota/ExtandebleJointConnector.h"
#include "../RamieRobota/ExtandebleJointConnector.cpp"
#include "../RamieRobota/Wektor.h"
#include "../RamieRobota/Wektor.cpp"
#include "../RamieRobota/Arm.h"
#include "../RamieRobota/Arm.cpp"
// #include "../Ramie_Robota/JointConnector.h"
// #include "../Ramie_Robota/JointConnector.cpp"

const float EPSILON = 0.0001f;

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace JointTest
{
	TEST_CLASS(JointTest)
	{
	public:

		TEST_METHOD(empty_constructor_for_joints_classes)
		{
			Joint j;
			ElbowJoint ej;
			ShoulderJoint sj;
			RestrictedShoulderJoint rsj;
			Coordinates c;
			Assert::AreEqual(true, c == j.get_coordinates());
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

		TEST_METHOD(constructor_for_joints_classes)
		{
			Coordinates end1(1, 1, 1);
			Coordinates end2(2, 2, 2);
			JointConnector con1(Coordinates(), end1, 0);
			JointConnector con2(end1, end2, 0);
			Joint j(con1);
			ElbowJoint ej(con1, con2);
			ShoulderJoint sj(con1, Coordinates());
			RestrictedShoulderJoint rsj(con1, Coordinates(), 120);
			Coordinates c;

			Assert::AreEqual(true, end1 == j.get_my_next_joint_connector().get_end_coordinates());

			Assert::AreEqual(true, end2 == ej.get_my_next_joint_connector().get_end_coordinates());
			Assert::AreEqual(true, end1 == ej.get_previous_joint_connector().get_end_coordinates());
			Assert::AreEqual(true, c == ej.get_previous_joint_connector().get_begin_coordinates());
			Assert::AreEqual(true, end1 == ej.get_coordinates());

			Assert::AreEqual(true, end1 == sj.get_my_next_joint_connector().get_end_coordinates());
			Assert::AreEqual(true, c == sj.get_coordinates());
			Assert::AreEqual(0, sj.get_alpha());

			Assert::AreEqual(true, end1 == rsj.get_my_next_joint_connector().get_end_coordinates());
			Assert::AreEqual(true, c == rsj.get_coordinates());
			Assert::AreEqual(0, rsj.get_alpha());
			Assert::AreEqual(unsigned int(120), rsj.get_max_angle());
		}
		TEST_METHOD(coords_setters_for_joints_classes)
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
			j.set_coordinates(c2);
			Assert::AreEqual(true, c2 == j.get_coordinates());

			Assert::AreEqual(true, c == ej.get_coordinates());
			ej.set_coordinates(c2);
			Assert::AreEqual(true, c2 == ej.get_coordinates());

			Assert::AreEqual(true, c == sj.get_coordinates());
			sj.set_coordinates(c2);
			Assert::AreEqual(true, c2 == sj.get_coordinates());

			Assert::AreEqual(true, c == rsj.get_coordinates());
			rsj.set_coordinates(c2);
			Assert::AreEqual(true, c2 == rsj.get_coordinates());

		}

		TEST_METHOD(getter_setter_my_next_joint_conn)
		{
			Coordinates end1(1, 1, 1);
			Coordinates end2(2, 2, 2);
			JointConnector con1(Coordinates(), end1, 0);
			JointConnector con2(end1, end2, 0);
			Joint j(con1);
			ElbowJoint ej(con1, con2);
			ShoulderJoint sj(con1, Coordinates());
			RestrictedShoulderJoint rsj(con1, Coordinates());
			Coordinates c;

			j.set_my_next_joint_connector(con2);
			Assert::AreEqual(true, end2 == j.get_my_next_joint_connector().get_end_coordinates());

			ej.set_my_next_joint_connector(con1);
			ej.set_previous_joint_connector(con2);
			Assert::AreEqual(true, end1 == ej.get_my_next_joint_connector().get_end_coordinates());
			Assert::AreEqual(true, end2 == ej.get_previous_joint_connector().get_end_coordinates());
			Assert::AreEqual(true, end1 == ej.get_previous_joint_connector().get_begin_coordinates());
			Assert::AreEqual(true, end2 == ej.get_coordinates());

			sj.set_my_next_joint_connector(con2);
			Assert::AreEqual(true, end2 == sj.get_my_next_joint_connector().get_end_coordinates());
			Assert::AreEqual(true, c == sj.get_coordinates());
			Assert::AreEqual(0, sj.get_alpha());

			rsj.set_my_next_joint_connector(con2);
			Assert::AreEqual(true, end2 == rsj.get_my_next_joint_connector().get_end_coordinates());
			Assert::AreEqual(true, c == rsj.get_coordinates());
			Assert::AreEqual(0, rsj.get_alpha());
			Assert::AreEqual(unsigned int(90), rsj.get_max_angle());

		}

		TEST_METHOD(adjust_coords_of_next_joint_connector_typical)
		{
			Coordinates end1(2, 2, 2);
			JointConnector con1(Coordinates(), end1, 0);

			Joint j(con1);

			Coordinates c(1.0, 1.0, -sqrt(10));
			j.set_tg_alpha(1);
			j.adjust_coords_of_next_joint_connector(1.0);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(adjust_coords_of_next_joint_connector_1_q)
		{
			Coordinates end1(1.0, 1.0, sqrt(10));
			JointConnector con1(Coordinates(), end1, 0);

			Joint j(con1);

			Coordinates c(2, 2, 2);
			j.set_tg_alpha(1);
			j.adjust_coords_of_next_joint_connector(2.0);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(adjust_coords_of_next_joint_connector_2_q)
		{
			Coordinates end1(-1.0, 1.0, sqrt(10));
			JointConnector con1(Coordinates(), end1, 0);

			Joint j(con1);

			Coordinates c(-2, 2, 2);
			j.set_tg_alpha(-1);
			j.adjust_coords_of_next_joint_connector(-2.0);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(adjust_coords_of_next_joint_connector_2_q_b)
		{
			Coordinates end1(-2, 2, 2);
			JointConnector con1(Coordinates(), end1, 0);

			Joint j(con1);

			Coordinates c(-1.0, 1.0, -sqrt(10));
			j.set_tg_alpha(-1);
			j.adjust_coords_of_next_joint_connector(-1.0);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(adjust_coords_of_next_joint_connector_3_q)
		{
			Coordinates end1(-1.0, -1.0, sqrt(10));
			JointConnector con1(Coordinates(), end1, 0);

			Joint j(con1);

			Coordinates c(-2, -2, 2);
			j.set_tg_alpha(1);
			j.adjust_coords_of_next_joint_connector(-2.0);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(adjust_coords_of_next_joint_connector_3_q_b)
		{
			Coordinates end1(-2, -2, 2);
			JointConnector con1(Coordinates(), end1, 0);

			Joint j(con1);

			Coordinates c(-1.0, -1.0, -sqrt(10));
			j.set_tg_alpha(1);
			j.adjust_coords_of_next_joint_connector(-1.0);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(adjust_coords_of_next_joint_connector_4_q)
		{
			Coordinates end1(1.0, -1.0, sqrt(10));
			JointConnector con1(Coordinates(), end1, 0);

			Joint j(con1);

			Coordinates c(2, -2, 2);
			j.set_tg_alpha(-1);
			j.adjust_coords_of_next_joint_connector(2.0);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(adjust_coords_of_next_joint_connector_4_q_b)
		{
			Coordinates end1(2, -2, 2);
			JointConnector con1(Coordinates(), end1, 0);

			Joint j(con1);

			Coordinates c(1.0, -1.0, -sqrt(10));
			j.set_tg_alpha(-1);
			j.adjust_coords_of_next_joint_connector(1.0);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}
		TEST_METHOD(get_set_tg_alpha)
		{
			Coordinates end1(2, -2, 2);
			JointConnector con1(Coordinates(), end1, 0);

			Joint j(con1);
			float eps = 0.001;
			Assert::AreEqual(true, abs(0 - j.get_tg_alpha()) < eps);
			j.set_tg_alpha(1);
			Assert::AreEqual(true, abs(1 - j.get_tg_alpha()) < eps);
		}

		TEST_METHOD(bend_typical_1_q)
		{
			Coordinates end1(10, 10, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Joint j(con1);

			Coordinates c(12, 12, sqrt(12));
			j.set_tg_alpha(1);
			j.bend(2);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(bend_sj_1_q)
		{
			Coordinates end1(10, 10, 10);
			JointConnector con1(Coordinates(), end1, 1);

			ShoulderJoint j(con1);

			Coordinates c(12, 12, sqrt(12));
			j.set_tg_alpha(1);
			j.bend(2);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(bend_zero_1_q)
		{
			Coordinates end1(10, 10, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Joint j(con1);

			Coordinates c(con1.max_x(), con1.max_x(), 0);
			j.set_tg_alpha(1);
			j.bend(3);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(bend_neg_1_q)
		{
			Coordinates end1(10, 10, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Joint j(con1);
			float z = sqrt(3 * 10 * 10 - 2 * (con1.max_x() - 1) * (con1.max_x() - 1));
			Coordinates c(con1.max_x() - 1, con1.max_x() - 1, -z);
			j.set_tg_alpha(1);
			j.bend(4);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}
		TEST_METHOD(bend_typical_2_q)
		{
			Coordinates end1(-10, 10, 10);
			JointConnector con1(Coordinates(), end1, -1);

			Joint j(con1);

			Coordinates c(-12, 12, sqrt(12));
			j.set_tg_alpha(-1);
			j.bend(2);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}
		TEST_METHOD(bend_zero_2_q)
		{
			Coordinates end1(-10, 10, 10);
			JointConnector con1(Coordinates(), end1, -1);

			Joint j(con1);

			Coordinates c(-con1.max_x(), con1.max_x(), 0);
			j.set_tg_alpha(-1);
			j.bend(3);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(bend_neg_2_q)
		{
			Coordinates end1(-10, 10, 10);
			JointConnector con1(Coordinates(), end1, -1);

			Joint j(con1);
			float z = sqrt(3 * 10 * 10 - 2 * (con1.max_x() - 1) * (con1.max_x() - 1));
			Coordinates c(-(con1.max_x() - 1), con1.max_x() - 1, -z);
			j.set_tg_alpha(-1);
			j.bend(4);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}
		TEST_METHOD(bend_typical_3_q)
		{
			Coordinates end1(-10, -10, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Joint j(con1);

			Coordinates c(-12, -12, sqrt(12));
			j.set_tg_alpha(1);
			j.bend(2);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}
		TEST_METHOD(bend_zero_3_q)
		{
			Coordinates end1(-10, -10, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Joint j(con1);

			Coordinates c(-con1.max_x(), -con1.max_x(), 0);
			j.set_tg_alpha(1);
			j.bend(3);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(bend_neg_3_q)
		{
			Coordinates end1(-10, -10, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Joint j(con1);
			float z = sqrt(3 * 10 * 10 - 2 * (con1.max_x() - 1) * (con1.max_x() - 1));
			Coordinates c(-(con1.max_x() - 1), -(con1.max_x() - 1), -z);
			j.set_tg_alpha(1);
			j.bend(4);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(bend_typical_4_q)
		{
			Coordinates end1(10, -10, 10);
			JointConnector con1(Coordinates(), end1, -1);

			Joint j(con1);

			Coordinates c(12, -12, sqrt(12));
			j.set_tg_alpha(-1);
			j.bend(2);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}
		TEST_METHOD(bend_zero_4_q)
		{
			Coordinates end1(10, -10, 10);
			JointConnector con1(Coordinates(), end1, -1);

			Joint j(con1);

			Coordinates c(con1.max_x(), -con1.max_x(), 0);
			j.set_tg_alpha(-1);
			j.bend(3);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(bend_neg_4_q)
		{
			Coordinates end1(10, -10, 10);
			JointConnector con1(Coordinates(), end1, -1);

			Joint j(con1);
			float z = sqrt(3 * 10 * 10 - 2 * (con1.max_x() - 1) * (con1.max_x() - 1));
			Coordinates c((con1.max_x() - 1), -(con1.max_x() - 1), -z);
			j.set_tg_alpha(-1);
			j.bend(4);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(bend_one_unit_typical)
		{
			Coordinates end1(10, 10, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Joint j(con1);

			Coordinates c(11, 11, sqrt(58));
			j.set_tg_alpha(1);
			j.bend_one_unit();
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(bend_01)
		{
			Coordinates end1(10, 10, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Joint j(con1);

			Coordinates c(10.1, 10.1, sqrt(96));
			j.set_tg_alpha(1);
			j.bend_0_1();
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(rotate_typical_1q)
		{
			Coordinates end1(sqrt(200), 0, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Coordinates c(10, 10, 10);

			ShoulderJoint j(con1);

			j.rotate(45);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(rotate_typical_2_q)
		{
			Coordinates end1(sqrt(200), 0, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Coordinates c(-10, 10, 10);

			ShoulderJoint j(con1);

			j.rotate(135);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(rotate_typical_3_q)
		{
			Coordinates end1(sqrt(200), 0, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Coordinates c(-10, -10, 10);

			ShoulderJoint j(con1);

			j.rotate(225);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(rotate_typical_4_q)
		{
			Coordinates end1(sqrt(200), 0, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Coordinates c(10, -10, 10);

			ShoulderJoint j(con1);

			j.rotate(315);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(rotate_negative_4_q)
		{
			Coordinates end1(sqrt(200), 0, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Coordinates c(10, -10, 10);

			ShoulderJoint j(con1);

			j.rotate(-45);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(rotate_modulo_1q)
		{
			Coordinates end1(sqrt(200), 0, 10);
			JointConnector con1(Coordinates(), end1, 1);

			Coordinates c(10, 10, 10);

			ShoulderJoint j(con1);

			j.rotate(765);
			Assert::AreEqual(true, c == j.get_my_next_joint_connector().get_end_coordinates());
		}

		TEST_METHOD(rotate_90)
		{
			Coordinates end1(sqrt(200), 0, 10);
			JointConnector con1(Coordinates(), end1, 1);
			double pi = 4.0 * std::atan(1.0);

			ShoulderJoint j(con1);

			double tg = j.rotate(90);
			Assert::AreEqual(tan((91) * pi / 180), tg);
		}
		TEST_METHOD(rotate_270)
		{
			Coordinates end1(sqrt(200), 0, 10);
			JointConnector con1(Coordinates(), end1, 1);
			double pi = 4.0 * std::atan(1.0);

			ShoulderJoint j(con1);

			double tg = j.rotate(270);
			Assert::AreEqual(tan((271) * pi / 180), tg);
		}
		TEST_METHOD(rotate_90_module)
		{
			Coordinates end1(sqrt(200), 0, 10);
			JointConnector con1(Coordinates(), end1, 1);
			double pi = 4.0 * std::atan(1.0);

			ShoulderJoint j(con1);

			double tg = j.rotate(450);
			Assert::AreEqual(tan((91) * pi / 180), tg);
		}

		TEST_METHOD(RestrictedShoulderJoint_rortate_over_limit)
		{
			Coordinates end1(sqrt(200), 0, 10);
			JointConnector con1(Coordinates(), end1, 1);

			RestrictedShoulderJoint j(con1);
			Assert::AreEqual(unsigned int(90), j.get_max_angle());
			j.set_max_angle(120);
			try {
				j.rotate(121);
			}
			catch (const char* x) {
				Assert::AreEqual(x, "Angle is beyond range.");
			}
		}

		TEST_METHOD(RestrictedShoulderJoint_rotate_negative)
		{
			Coordinates end1(sqrt(200), 0, 10);
			JointConnector con1(Coordinates(), end1, 1);

			RestrictedShoulderJoint j(con1);
			Assert::AreEqual(unsigned int(90), j.get_max_angle());
			j.set_max_angle(120);
			try {
				j.rotate(-1);
			}
			catch (const char* x) {
				Assert::AreEqual(x, "Angle is beyond range.");
			}
		}

		TEST_METHOD(RestrictedShoulderJoint_rotate_one_degree)
		{
			Coordinates end1(sqrt(200), 0, 10);
			JointConnector con1(Coordinates(), end1, 1);

			RestrictedShoulderJoint j(con1);
			Assert::AreEqual(unsigned int(90), j.get_max_angle());
			j.set_max_angle(120);
			j.rotate(120);
			try {
				j.rotate_one_degree();
			}
			catch (const char* x) {
				Assert::AreEqual(x, "Angle is beyond range.");
			}
		}


	};

	TEST_CLASS(TestBasicJointConnector)
	{
	public:

		TEST_METHOD(testConstructor)
		{
			Coordinates a(0, 0, 0), b(2, 3, 0);
			BaseJointConnector Joint(a, b);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
		}
		TEST_METHOD(testLenght)
		{
			Coordinates a(0, 0, 0), b(4, 3, 0);
			BaseJointConnector Joint(a, b);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_lenght(), 5.0f);
		}
	};
	TEST_CLASS(TestJointConnector)
	{
	public:

		TEST_METHOD(testConstructor)
		{
			Coordinates a(0, 0, 0), b(2, 3, 0);
			float angle = 0.53f;
			JointConnector Joint(a, b, angle);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_angle(), 1.5f);
		}
		TEST_METHOD(testLenght)
		{
			Coordinates a(0, 0, 0), b(4, 3, 0);
			float angle = 0.5f;
			JointConnector Joint(a, b, angle);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_angle(), 0.75f);
			Assert::AreEqual(Joint.get_lenght(), 5.0f);
		}
		TEST_METHOD(testMaxX)
		{
			Coordinates a(0, 0, 0), b(4, 3, 0);
			float angle = 0.5f;
			JointConnector Joint(a, b, angle);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_angle(), 0.75f);
			Assert::AreEqual(Joint.get_lenght(), 5.0f);
			Assert::AreEqual(Joint.max_x(), float(sqrt(16)), EPSILON);
		}
		TEST_METHOD(testMaxX_negAngle)
		{
			Coordinates a(0, 0, 0), b(4, 3, 0);
			float angle = -0.5f;
			JointConnector Joint(a, b, angle);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_angle(), 0.75f);
			Assert::AreEqual(Joint.get_lenght(), 5.0f);
			Assert::AreEqual(Joint.max_x(), float(sqrt(16)), EPSILON);
		}
		TEST_METHOD(testMinX)
		{
			Coordinates a(0, 0, 0), b(4, 3, 0);
			float angle = 0.5f;
			JointConnector Joint(a, b, angle);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_angle(), 0.75f);
			Assert::AreEqual(Joint.get_lenght(), 5.0f);
			Assert::AreEqual(Joint.min_x(), float(-sqrt(16)), EPSILON);
		}
		TEST_METHOD(testMinX_negAngle)
		{
			Coordinates a(0, 0, 0), b(4, 3, 0);
			float angle = -0.5f;
			JointConnector Joint(a, b, angle);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_angle(), 0.75f);
			Assert::AreEqual(Joint.get_lenght(), 5.0f);
			Assert::AreEqual(Joint.min_x(), float(-sqrt(16)), EPSILON);
		}
	};
	TEST_CLASS(TestJExtandebleointConnector)
	{
	public:

		TEST_METHOD(testConstructor)
		{
			Coordinates a(0, 0, 0), b(4, 3, 0);
			Wektor wek(4, 3, 0);
			ExtandebleJointConnector Joint(a, b);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_lenght(), 5.0f, EPSILON);
			Assert::AreEqual(Joint.get_direction() == wek, true);
		}
		TEST_METHOD(testSetDirectionAndUpdateEnd)
		{
			Coordinates a(0, 0, 0), b(4, 3, 0);
			Wektor wek(4, 3, 0);
			ExtandebleJointConnector Joint(a, b);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_lenght(), 5.0f, EPSILON);
			Assert::AreEqual(Joint.get_direction() == wek, true);
			wek = Wektor(12, 5, 0);
			b = Coordinates(12, 5, 0);
			Joint.set_directions_and_update_end(wek);
			Assert::AreEqual(Joint.get_direction() == wek, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_lenght(), 13.0f, EPSILON);
		}
		TEST_METHOD(testSetEndAndUpdateDirection)
		{
			Coordinates a(0, 0, 0), b(4, 3, 0);
			Wektor wek(4, 3, 0);
			ExtandebleJointConnector Joint(a, b);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_lenght(), 5.0f, EPSILON);
			Assert::AreEqual(Joint.get_direction() == wek, true);
			wek = Wektor(12, 5, 0);
			b = Coordinates(12, 5, 0);
			Joint.set_end_and_update_directions(b);
			Assert::AreEqual(Joint.get_direction() == wek, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_lenght(), 13.0f, EPSILON);
		}
		TEST_METHOD(testExtend)
		{
			Coordinates a(0, 0, 0), b(4, 3, 0);
			Wektor wek(4, 3, 0);
			ExtandebleJointConnector Joint(a, b);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_lenght(), 5.0f, EPSILON);
			Assert::AreEqual(Joint.get_direction() == wek, true);
			Joint.extend(2.0f);
			wek = Wektor(8, 6, 0);
			Assert::AreEqual(Joint.get_direction() == wek, true);
		}
		TEST_METHOD(testExtendFloat)
		{
			Coordinates a(0, 0, 0), b(4, 3, 0);
			Wektor wek(4, 3, 0);
			ExtandebleJointConnector Joint(a, b);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_lenght(), 5.0f, EPSILON);
			Assert::AreEqual(Joint.get_direction() == wek, true);
			Joint.extend(1.5f);
			wek = Wektor(6, 4.5, 0);
			Assert::AreEqual(Joint.get_direction() == wek, true);
		}
		TEST_METHOD(testExtendByVal)
		{
			Coordinates a(0, 0, 0), b(4, 3, 0);
			Wektor wek(4, 3, 0);
			ExtandebleJointConnector Joint(a, b);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_lenght(), 5.0f, EPSILON);
			Assert::AreEqual(Joint.get_direction() == wek, true);
			Joint.extend_by_len(8.0f);
			Assert::AreEqual(Joint.get_lenght(), 13.0f, EPSILON);
			Assert::AreEqual(Joint.get_end_coordinates().x, 10.4f, EPSILON);
			Assert::AreEqual(Joint.get_end_coordinates().y, 7.8f, EPSILON);
			Assert::AreEqual(Joint.get_end_coordinates().z, 0.0f, EPSILON);
		}
		TEST_METHOD(testExtendByVal_NonZeroZ)
		{
			Coordinates a(0, 0, 0), b(4, 3, 5);
			Wektor wek(4, 3, 5);
			ExtandebleJointConnector Joint(a, b);
			Assert::AreEqual(Joint.get_begin_coordinates() == a, true);
			Assert::AreEqual(Joint.get_end_coordinates() == b, true);
			Assert::AreEqual(Joint.get_lenght(), float(sqrt(50)), EPSILON);
			Assert::AreEqual(Joint.get_direction() == wek, true);
			Joint.extend_by_len(8.0f);
			Assert::AreEqual(Joint.get_lenght(), 15.071f, EPSILON); // 2.13137
			Assert::AreEqual(Joint.get_end_coordinates().x, 8.52548f, EPSILON);
			Assert::AreEqual(Joint.get_end_coordinates().y, 6.3941099f, EPSILON);
			Assert::AreEqual(Joint.get_end_coordinates().z, 10.65684994f, EPSILON);
		}
	};
	TEST_CLASS(TestGripper)
	{
	public:
		TEST_METHOD(Gripper_constructor)
		{
			Gripper gripper;
			Assert::AreEqual(true, gripper.get_coordinates() == Coordinates());
			Assert::AreEqual(gripper.get_range(), 1.0f, 0.01f);
			Assert::AreEqual(gripper.is_closed(), false);
			Gripper gripper2(Coordinates(1, 2, 3), 2.0f);
			Assert::AreEqual(true, gripper2.get_coordinates() == Coordinates(1, 2, 3));
			Assert::AreEqual(gripper2.get_range(), 2.0f, 0.01f);
			Assert::AreEqual(gripper2.is_closed(), false);
		}
		TEST_METHOD(set_coordinates)
		{
			Gripper gripper;
			Assert::AreEqual(true, gripper.get_coordinates() == Coordinates());
			gripper.set_coordinates(Coordinates(1, 2, 3));
			Assert::AreEqual(true, gripper.get_coordinates() == Coordinates(1, 2, 3));
		}
		TEST_METHOD(close_open)
		{
			Gripper gripper;
			gripper.close();
			Assert::AreEqual(gripper.is_closed(), true);
			gripper.open();
			Assert::AreEqual(gripper.is_closed(), false);
		}

		TEST_METHOD(set_range)
		{
			Gripper gripper;
			gripper.set_range(2);
			Assert::AreEqual(gripper.get_range(), 2.0f);
		}
	};
	TEST_CLASS(TestArm)
	{
	public:
		TEST_METHOD(if_reachable)
		{
			JointConnector arm_part(Coordinates(0, 0, 0), Coordinates(0, 0, 10));
			ExtandebleJointConnector forearm(Coordinates(0, 0, 10), Coordinates(0, 0, 20));
			Arm arm(arm_part, forearm, Coordinates(0, 0, 20));
			Assert::AreEqual(true, arm.if_reachable(Coordinates(2, 2, 2)));
			Assert::AreEqual(false, arm.if_reachable(Coordinates(15, 15, 10)));
			Assert::AreEqual(true, arm.if_reachable(Coordinates(0, 0, 20)));
		}
		TEST_METHOD(get_range)
		{
			JointConnector arm_part(Coordinates(0, 0, 0), Coordinates(0, 0, 10));
			ExtandebleJointConnector forearm(Coordinates(0, 0, 10), Coordinates(0, 0, 20));
			Arm arm(arm_part, forearm, Coordinates(0, 0, 20));
			Assert::AreEqual(20.0f, arm.get_range(), 0.01f);
		}
		TEST_METHOD(get_tg_0)
		{
			JointConnector arm_part(Coordinates(0, 0, 0), Coordinates(0, 0, 10));
			ExtandebleJointConnector forearm(Coordinates(0, 0, 10), Coordinates(0, 0, 20));
			Arm arm(arm_part, forearm, Coordinates(0, 0, 20));
			Assert::AreEqual(0.0f, arm.get_tg(), 0.01f);
		}
		TEST_METHOD(get_tg_45)
		{
			JointConnector arm_part(Coordinates(0, 0, 0), Coordinates(5, 5, 5));
			ExtandebleJointConnector forearm(Coordinates(5, 5, 5), Coordinates(10, 10, 10));
			Arm arm(arm_part, forearm, Coordinates(10, 10, 10));
			Assert::AreEqual(1.0f, arm.get_tg(), 0.01f);
		}
		TEST_METHOD(uptadete_tg)
		{
			JointConnector arm_part(Coordinates(0, 0, 0), Coordinates(5, 5, 5));
			ExtandebleJointConnector forearm(Coordinates(5, 5, 5), Coordinates(10, 10, 10));
			Arm arm(arm_part, forearm, Coordinates(10, 10, 10));
			arm.update_tg(3);

			Assert::AreEqual(3.0f, arm.get_tg(), 0.01f);
			Assert::AreEqual(3.0f, arm.get_elbow().get_tg_alpha(), 0.01f);
			Assert::AreEqual(3.0f, arm.get_shoulder().get_tg_alpha(), 0.01f);
			Assert::AreEqual(3.0f, arm.get_arm_part().get_angle(), 0.01f);
			Assert::AreEqual(3.0f, arm.get_forearm().get_angle(), 0.01f);
		}

		TEST_METHOD(catch_object)
		{
			JointConnector arm_part(Coordinates(0, 0, 0), Coordinates(5, 5, 5));
			ExtandebleJointConnector forearm(Coordinates(5, 5, 5), Coordinates(10, 10, 10));
			Arm arm(arm_part, forearm, Coordinates(0, 0, 0));

			Assert::AreEqual(true, arm.catch_object(Coordinates(10, 10, 10)));
			Assert::AreEqual(true, arm.get_gripper().is_closed());

		}

		TEST_METHOD(released)
		{
			JointConnector arm_part(Coordinates(0, 0, 0), Coordinates(5, 5, 5));
			ExtandebleJointConnector forearm(Coordinates(5, 5, 5), Coordinates(10, 10, 10));
			Arm arm(arm_part, forearm, Coordinates(0, 0, 0));

			Assert::AreEqual(true, arm.catch_object(Coordinates(10, 10, 10)));
			Assert::AreEqual(true, arm.get_gripper().is_closed());
			arm.release();
			Assert::AreEqual(false, arm.get_gripper().is_closed());

		}
	};

}

