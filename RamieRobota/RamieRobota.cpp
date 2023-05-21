// RamieRobota.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include "Arm.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <cmath>



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
    GLFWwindow* window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(1280, 1280, "Simulation", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    gluLookAt(0, 0, 0, 40, 40, 20, 0, 0, 1);

    while (!glfwWindowShouldClose(window))
    {

        glClear(GL_COLOR_BUFFER_BIT);


        /*glBegin(GL_POINTS);
        for (int i = -10; i <= 10; i++)
        {
            glVertex3f(i/10.f, i/10.0f, 0.0f);
        }
        glEnd();*/
        glColor3f(0, 1, 0);
        glBegin(GL_LINES);
        glVertex3f(0.0f, 10, 0.0f);
        glVertex3f(0.0f, -10, 0.0f);

        glColor3f(1, 0, 0);
        glVertex3f(10.0f, 0.0f, 0.0f);
        glVertex3f(-10.0f, 0.0f, 0.0f);

        glColor3f(0, 0, 1);
        glVertex3f(0.0f, 0.0f, 10.0f);
        glVertex3f(0.0f, 0.0f, -10.0f);
        glEnd();



        // czemu punkt znika gdy z > 1
        // jak obrocic punkt patrzenia
        glColor3f(1, 1, 1);

        glBegin(GL_LINES);
        glVertex3d(0, 0, 0);
        glVertex3d(0.75f, -0.5f, 0.25f);
        glVertex3d(0.75f, -0.5f, 0.25f);
        glVertex3d(-0.2, 0.3, 0.5);
        glEnd();

        // punkt
        glPointSize(20);
        glColor3f(0.5, 0, 0.5);
        glBegin(GL_POINTS);
        glVertex3d(0.75, -0.5, 0.25);
        glVertex3d(-0.2, 0.3, 0.5);
        glEnd();

        /*glBegin(GL_POINTS);

        glVertex3f(1.0f, 1.0f, 1.0f);

        glEnd();

        glBegin(GL_LINES);
        glVertex3f(0.0f, 0.0f, 0.0f);
        glVertex3f(3.0f, 3.0f, 3.0f);
        glEnd();

        glBegin(GL_TRIANGLES);

        glVertex3f(0.0f, 0.5f, 0.5f);
        glVertex3f(1.0f, 0.5f, 0.5f);
        glVertex3f(0.0f, -0.5f, 0.5f);

        glEnd();
        */
        glfwSwapBuffers(window);


        glfwPollEvents();
    }

    glfwTerminate();
    return 0;

}
