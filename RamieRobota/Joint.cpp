//Author: Mateusz Ostaszewski
#include "Joint.h"
#include <math.h>
#include <fstream>


Joint::Joint()
{
    this->coordinates = Coordinates();
    tg_alpha = 0;
}

Joint::Joint(const JointConnector& my_next_joint_connector)
{
    this->coordinates = Coordinates();
    this->my_next_joint_connector = my_next_joint_connector;
    tg_alpha = 0;
}

Coordinates Joint::get_coordinates() const
{
    return coordinates;
}

void Joint::set_coordinates(const Coordinates& coordinates)
{
    this->coordinates = coordinates;
    my_next_joint_connector.set_begin_coordinates(coordinates);
}

void Joint::set_tg_alpha(const float tg)
{
    this->tg_alpha = tg;
}

float Joint::get_tg_alpha() const
{
    return tg_alpha;
}

JointConnector& Joint::get_my_next_joint_connector()
{
    return my_next_joint_connector;
}

void Joint::set_my_next_joint_connector(const JointConnector& new_jc)
{
    my_next_joint_connector = new_jc;
}

void Joint::bend(const int incrment)
{
    float x = my_next_joint_connector.get_end_coordinates().x;
    if (x >= 0) {
        for (int i = 1; i <= incrment; i++)
        {
            if (x + 1 <= my_next_joint_connector.max_x() && !over) {
                x += 1;
            }
            else if (x - 1 >= my_next_joint_connector.min_x()) {
                if (!over) {
                    x = my_next_joint_connector.max_x();
                    over = true;
                }
                else x -= 1;
            }
            else {
                break;
            }
            adjust_coords_of_next_joint_connector(x);
        }
    }
    else {
        for (int i = 1; i <= incrment; i++)
        {
            if (x - 1 >= my_next_joint_connector.min_x() && !over) {
                x -= 1;
            }
            else if (x + 1 <= my_next_joint_connector.max_x()) {
                if (!over) {
                    x = my_next_joint_connector.min_x();
                    over = true;
                }
                else x += 1;
            }
            else {
                break;
            }
            adjust_coords_of_next_joint_connector(x);
        }
    }
}

void Joint::bend_one_unit()
{
    bend(1);
}

void Joint::bend_0_1()
{
    float x = my_next_joint_connector.get_end_coordinates().x;
    if (x >= 0) {
        if (x + 0.1 <= my_next_joint_connector.max_x() && !over) {
            x += 0.1;
        }
        else if (x - 0.1 >= my_next_joint_connector.min_x()) {
            if (!over) {
                x = my_next_joint_connector.max_x();
                over = true;
            }
            else x -= 0.1;
        }
    }
    else {
        if (x - 0.1 >= my_next_joint_connector.min_x() && !over) {
            x -= 0.1;
        }
        else if (x + 0.1 <= my_next_joint_connector.max_x()) {
            if (!over) {
                x = my_next_joint_connector.min_x();
                over = true;
            }
            else x += 0.1;
        }
    }
    adjust_coords_of_next_joint_connector(x);
}

void Joint::re_bend()
{
    float x = my_next_joint_connector.get_end_coordinates().x;
    if (x >= 0) {
        if (x - 0.1 >= my_next_joint_connector.min_x() && !over) {
            x -= 0.1;
        }
        else if (x + 0.1 <= my_next_joint_connector.max_x()) {
            if (!over) {
                x = my_next_joint_connector.min_x();
                over = true;
            }
            else x += 0.1;
        }
    }
    else {
        if (x + 0.1 <= my_next_joint_connector.max_x() && !over) {
            x += 0.1;
        }
        else if (x - 0.1 >= my_next_joint_connector.min_x()) {
            if (!over) {
                x = my_next_joint_connector.max_x();
                over = true;
            }
            else x -= 0.1;
        }
    }
    adjust_coords_of_next_joint_connector_re_bend(x);
}

void Joint::adjust_coords_of_next_joint_connector(const float x_end)
{
    float x = x_end - my_next_joint_connector.get_begin_coordinates().x;
    float y = tg_alpha * x;
    float old_z = my_next_joint_connector.get_end_coordinates().z;
    float lenght = my_next_joint_connector.get_lenght();
    float help = lenght * lenght - x * x - y * y;
    if (help < 0) {
        help = 0;
    }
    float new_z = sqrt(help);
    float begin_z = my_next_joint_connector.get_begin_coordinates().z;
    float z = (begin_z + new_z < old_z) ? begin_z + new_z : begin_z - new_z;
    Coordinates coords(
        x + my_next_joint_connector.get_begin_coordinates().x,
        y + coordinates.y,
        z);
    my_next_joint_connector.set_end_coordinates(coords);
}

void Joint::adjust_coords_of_next_joint_connector_re_bend(const float x_end)
{
    float x = x_end - my_next_joint_connector.get_begin_coordinates().x;
    float y = tg_alpha * x;
    float old_z = my_next_joint_connector.get_end_coordinates().z;
    float lenght = my_next_joint_connector.get_lenght();
    float help = lenght * lenght - x * x - y * y;
    if (help < 0) {
        help = 0;
    }
    float new_z = sqrt(help);
    float begin_z = my_next_joint_connector.get_begin_coordinates().z;
    float z = begin_z + new_z;
    if (coordinates.z > old_z) {
        z = begin_z - new_z;
    }
    
    Coordinates coords(
        x + my_next_joint_connector.get_begin_coordinates().x,
        y + coordinates.y,
        z);
    my_next_joint_connector.set_end_coordinates(coords);
}

void Joint::print() const
{
    std::cout << coordinates << my_next_joint_connector;
}

void Joint::save_to_file(std::string file_name) const
{
    std::fstream out;
    try {
        out.open(file_name, std::ios::out);
    }
    catch (std::ifstream::failure x) {
        std::cout << x.what() << std::endl;
    }
    std::streambuf* oss = std::cout.rdbuf();
    std::cout.rdbuf(out.rdbuf());
    out << *this;
    std::cout.rdbuf(oss);
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

std::ostream& operator<<(std::ostream& out, const Joint& j)
{
    j.print();
    return out;
}

std::istream& operator>>(std::istream& in, Joint& j)
{
    Coordinates coords;
    in >> coords >> j.my_next_joint_connector;
    return in;
}
