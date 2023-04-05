// Ramie_Robota.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include "Arm.h"
#include <iostream>


int main()
{
    Arm arm;
    arm.set_range(10.1);
    std::cout << arm.if_reachable(1, 1, 1) << "\n";

}
