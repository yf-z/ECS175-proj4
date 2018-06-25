#include "vertex.h"

Vertex::Vertex() {
    x = 0;
    y = 0;
    z = 0;
}

Vertex::Vertex(float x, float y, float z) {
    this->x = x;
    this->y = y;
    this->z = z;
}

Vertex Vertex::operator=(const Vertex pt)
{
    x = pt.x;
    y = pt.y;
    z = pt.z;
    return *this;
}
Vertex Vertex::operator+(const Vertex pt) const
{
    Vertex temp;
    temp.x = x + pt.x;
    temp.y = y + pt.y;
    temp.z = z + pt.z;
    return temp;
}
Vertex Vertex::operator*(float m) const
{
    Vertex temp;
    temp.x = x*m;
    temp.y = y*m;
    temp.z = z*m;
    return temp;
}
Vertex Vertex::operator/(float m) const
{
    Vertex temp;
    temp.x = x/m;
    temp.y = y/m;
    temp.z = z/m;
    return temp;
}


Connection::Connection() {
    x = 0;
    y = 0;
}

Connection::Connection(int x, int y) {
    this->x = x;
    this->y = y;
}