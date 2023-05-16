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
// #include "../Ramie_Robota/JointConnector.h"
// #include "../Ramie_Robota/JointConnector.cpp"

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


}

