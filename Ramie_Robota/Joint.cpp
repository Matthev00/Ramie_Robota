//Author: Mateusz Ostaszewski
#include "Joint.h"
#include <math.h>

Joint::Joint(const JointConnector& my_next_joint_connector, const Coordinates& coordinates = Coordinates(0, 0, 0))
{
    this->coordinates = coordinates;
    this->my_next_joint_connector = my_next_joint_connector;
}

float Joint::get_x_coordinate() const
{
    return coordinates.x;
}

float Joint::get_y_coordinate() const
{
    return coordinates.y;
}

float Joint::get_z_coordinate() const
{
    return coordinates.z;
}

Coordinates Joint::get_coordinates() const
{
    return coordinates;
}

void Joint::set_x_coordinate(const float x)
{
    coordinates.x = x;
}

void Joint::set_y_coordinate(const float y)
{
    coordinates.y = y;
}

void Joint::set_z_coordinate(const float z)
{
    if (z < 0) {
        throw "Value has to be non-negative!";
    }
    coordinates.z = z;
}

void Joint::set_coordinates(const Coordinates& coordinates)
{
    this->coordinates = coordinates;
}

void Joint::bend(const int incrment)
{
    float x = my_next_joint_connector.get_end_coordinates().x;
    for (int i = 1; i <= incrment; i++)
    {
        if (x + 1 <= my_next_joint_connector.max_x()) {
            x += 1;
        }
        else {
            x -= 1;
        }
    }
    adjust_coords_of_next_joint_connector(x);
}

void Joint::bend_one_unit()
{
    float x = my_next_joint_connector.get_end_coordinates().x;
    if (x + 1 <= my_next_joint_connector.max_x()) {
        x += 1;
    }
    else {
        x -= 1;
    }
    adjust_coords_of_next_joint_connector(x);
}

void Joint::bend_0_1()
{
    float x = my_next_joint_connector.get_end_coordinates().x;
    if (x + 0.1 <= my_next_joint_connector.max_x()) {
        x += 0.1;
    }
    else {
        x -= 0.1;
    }
    adjust_coords_of_next_joint_connector(x);
}

Coordinates Joint::operator++()
{
    float x = my_next_joint_connector.get_end_coordinates().x;
    if (x + 1 <= my_next_joint_connector.max_x()) {
        x += 1;
    }
    else {
        x -= 1;
    }
    adjust_coords_of_next_joint_connector(x);
    return my_next_joint_connector.get_end_coordinates();
}

void Joint::adjust_coords_of_next_joint_connector(const float x_end)
{
    float x = x_end - my_next_joint_connector.get_begin_coordinates().x;
    // Testing ver
    float tg_alpha = sqrt(2) / 2;
    //
 
    // Final
    // float tg_alpha = Arm.get_tg_alpha();
    //
    float y = tg_alpha * x - my_next_joint_connector.get_begin_coordinates().y;
    float old_z = my_next_joint_connector.get_end_coordinates().z;
    int lenght = my_next_joint_connector.get_lenght();
    float new_z = sqrt(lenght * lenght - x * x - y * y);
    float begin_z = my_next_joint_connector.get_begin_coordinates().z;
    float z = (begin_z + new_z < old_z)? begin_z + new_z : begin_z - new_z;
    Coordinates coords(
        x + my_next_joint_connector.get_begin_coordinates().x,
        y + my_next_joint_connector.get_begin_coordinates().y,
        z);
    my_next_joint_connector.set_coordinates(coords);
}
