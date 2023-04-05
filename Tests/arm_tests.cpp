#include "CppUnitTest.h"
#include "../Ramie_Robota/Arm.h"
#include "../Ramie_Robota/Arm.cpp"

using namespace Microsoft::VisualStudio::CppUnitTestFramework;

namespace arm_tests
{
	TEST_CLASS(arm_tests)
	{
	public:
		
		TEST_METHOD(if_reachable_positive)
		{
			Arm arm;
			arm.set_range(10);
			Assert::AreEqual(true, arm.if_reachable(1, 1, 1));
		}

		TEST_METHOD(if_reachable_negative)
		{
			Arm arm;
			arm.set_range(10);
			Assert::AreEqual(false, arm.if_reachable(10, 10, 10));
		}
		TEST_METHOD(if_reachable_borderline_case)
		{
			Arm arm;
			arm.set_range(10);
			Assert::AreEqual(true, arm.if_reachable(6, 4, 0));
		}
		TEST_METHOD(set_range_tpical)
		{
			Arm arm;
			arm.set_range(10);
			Assert::AreEqual(10.0, arm.get_range());
		}
		TEST_METHOD(set_range_negative_range)
		{
			Arm arm;
			try {
				arm.set_range(-10);
			}
			catch (const char* x) {
				Assert::AreEqual(x, "Range can not be negative.");
			}
			
		}
	};
}
