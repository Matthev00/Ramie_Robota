﻿// RamieRobota.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//
#include "Arm.h"
#include <iostream>
#include <GLFW/glfw3.h>
#include <GL/glut.h>
#include <cmath>
#include <Windows.h>


float cameraX = 1.0f;
float cameraY = 1.0f;
float cameraZ = 5.0f;
std::vector < std::vector<Coordinates>>result;
Coordinates target(2, 5, 5);
int i;
const int SCALE = 10.0f;


void display() {
    
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    // Set the camera position

    gluPerspective(45, 1.0, 0.001f, 10000.0f);

    gluLookAt(cameraX, cameraY, cameraZ, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 1.0f);

    // Draw 3D Axies

    glColor3f(0, 1, 0);
    glLineWidth(1.0f);

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


    // the arm itself
    glColor3f(1, 1, 1);
    glLineWidth(2.0f);


    glBegin(GL_LINES);
    glVertex3d(result[0][i].x / SCALE, result[0][i].y / SCALE, result[0][i].z / SCALE);
    glVertex3d(result[1][i].x / SCALE, result[1][i].y / SCALE, result[1][i].z / SCALE);
    glVertex3d(result[1][i].x / SCALE, result[1][i].y / SCALE, result[1][i].z / SCALE);
    glVertex3d(result[2][i].x / SCALE, result[2][i].y / SCALE, result[2][i].z / SCALE);
    glEnd();

    // punkt
    glPointSize(20);
    glColor3f(0.5, 0, 0.5);
    glBegin(GL_POINTS);
    glVertex3d(result[1][i].x / SCALE, result[1][i].y / SCALE, result[1][i].z / SCALE);
    glVertex3d(result[2][i].x / SCALE, result[2][i].y / SCALE, result[2][i].z / SCALE);

    glColor3f(0.0f, 0.2f, 1.0f);
    glVertex3d(target.x / SCALE, target.y / SCALE, target.z / SCALE);

    glEnd();

    glFlush();
}

void specialKeys(int key, int x, int y) {
    float cameraSpeed = 0.1f; 

    switch (key) {
    case GLUT_KEY_UP:
        cameraZ -= cameraSpeed;
        break;
    case GLUT_KEY_DOWN:
        cameraZ += cameraSpeed;
        break;
    case GLUT_KEY_LEFT:
        cameraX -= cameraSpeed;
        break;
    case GLUT_KEY_RIGHT:
        cameraX += cameraSpeed;
        break;
    case GLUT_KEY_F1:
        cameraY += cameraSpeed;
        break;
    case GLUT_KEY_F2:
        cameraY -= cameraSpeed;
        break;
    case GLUT_KEY_F6:
        if (i > 0)
            i--;
        break;
    case GLUT_KEY_F7:
        if (i < result[0].size() - 1)
            i++;
        break;
    }

    glutPostRedisplay();
}





int main(int argc, char** argv) {
    JointConnector arm_part(Coordinates(0, 0, 0), Coordinates(0, 0, 10));
    ExtandebleJointConnector forearm(Coordinates(0, 0, 10), Coordinates(0, 0, 20));
    Arm arm(arm_part, forearm);
    std::cout << "What point do you want to reach (x, y, z)" << std::endl;
    std::cin >> target;

    
    result = arm.reach_target(target);
    i = result[1].size() - 1;

    for (int j = 0; j < result[0].size();j++) {
        // i-ty koordynat barku
        std::cout << result[0][j];
        // i-ty koordynat łokcia
        std::cout << result[1][j];
        // i-ty koordynat chwytaka
        std::cout << result[2][j] <<  std::endl;
    }

    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("Outcome window");

    glEnable(GL_DEPTH_TEST);

    glutDisplayFunc(display);
    glutSpecialFunc(specialKeys);

    glutMainLoop();
    
    
    return 0;

}
