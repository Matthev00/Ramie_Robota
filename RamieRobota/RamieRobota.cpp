// RamieRobota.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include "Arm.h"
#include <iostream>



int main() {
    JointConnector arm_part(Coordinates(0, 0, 0), Coordinates(0, 0, 10));
    ExtandebleJointConnector forearm(Coordinates(0, 0, 10), Coordinates(0, 0, 20));
    Arm arm(arm_part, forearm);
    Coordinates target(1, 10, 10);
    std::vector < std::vector<Coordinates>>result = arm.reach_target(target);


    for (int i = 0; i < result[0].size();i++) {
        // i-ty koordynat barku
        std::cout << result[0][i];
        // i-ty koordynat łokcia
        std::cout << result[1][i];
        // i-ty koordynat chwytaka
        std::cout << result[2][i] <<  std::endl;
    }

    result = arm.back_to_starting_pos();

    for (int i = 0; i < result[0].size(); i++) {
        // i-ty koordynat barku
        std::cout << result[0][i];
        // i-ty koordynat łokcia
        std::cout << result[1][i];
        // i-ty koordynat chwytaka
        std::cout << result[2][i] << std::endl;
    }

}
