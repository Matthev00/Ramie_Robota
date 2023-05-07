#include "coordinates.h"

std::ostream& operator<<(std::ostream& out, const Coordinates& c)
{
    out << c.x << " " << c.y << " " << c.z << "\n";
    return out;
}

std::istream& operator>>(std::istream& in,Coordinates& c)
{
    float x, y, z;
    in >> x >> y >> z;
    c.x = x;
    c.y = y;
    c.z = z;
    return in;
}

bool Coordinates::operator==(Coordinates other)
{
    if (x == other.x &&
        y == other.y &&
        z == other.z) {
        return true;
    }
    return false;
}
