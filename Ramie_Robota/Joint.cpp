//Author: Mateusz Ostaszewski
#include "Joint.h"
#include <math.h>
#include <fstream>


Joint::Joint()
{
    this->coordinates = Coordinates();
}

Joint::Joint(const JointConnector& my_next_joint_connector)
{
    this->coordinates = Coordinates();
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
        else if (x - 1 >= my_next_joint_connector.min_x()) {
            x -= 1;
        }
        else {
            break;
        }
    }
    adjust_coords_of_next_joint_connector(x);
}

void Joint::bend_one_unit()
{
    bend(1);
}

void Joint::bend_0_1()
{
    float x = my_next_joint_connector.get_end_coordinates().x;
    if (x + 0.1 <= my_next_joint_connector.max_x()) {
        x += 0.1;
    }
    else if (x - 0.1 >= my_next_joint_connector.min_x()) {
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
    my_next_joint_connector.set_end_coordinates(coords);
}

void Joint::save_to_file(std::string file_name)
{
    std::fstream out;
    try {
        out.open(file_name, std::ios::out);
    }
    catch (std::ifstream::failure x) {
        std::cout << x.what() << std::endl;
    }
    out << *this;
    out.close();
}

void Joint::read_from_file(std::string file_name)
{
    std::fstream in;
    try {
        in.open(file_name, std::ios::in);
    }
    catch (std::ifstream::failure x) {
        std::cout << x.what() << std::endl;
    }
    in >> *this;
    in.close();
}
/*
std::ostream& operator<<(std::ostream& os, const JointConnector&)
{
    return os;
}

std::istream& operator>>(std::istream& in, const JointConnector&)
{
    return in;
}
*/
std::ostream& operator<<(std::ostream& out, const Joint& j)
{
    out << j.coordinates;
    out << j.my_next_joint_connector;
    return out;
}

std::istream& operator>>(std::istream& in, Joint& j)
{
    Coordinates coords;
    JointConnector next;
    in >> coords >> next;
    return in;
}
/*
Coordinates JointConnector::get_begin_coordinates() const
{
    return Coordinates();
}

Coordinates JointConnector::get_end_coordinates() const
{
    return Coordinates();
}

int JointConnector::get_lenght() const
{
    return 0;
}

void JointConnector::set_coordinates(Coordinates)
{
}

float JointConnector::max_x() const
{
    return 0.0f;
}

float JointConnector::min_x() const
{
    return 0.0f;
}
*/
