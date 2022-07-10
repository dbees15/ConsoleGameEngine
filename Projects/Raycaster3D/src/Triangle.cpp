#include "Triangle.h"

Triangle::Triangle()
{
    //ctor
}

Triangle::Triangle(const Triangle& other)
{
    //copy ctor
}

Triangle(const Vector3d root, const Vector3d vertex_a, const Vector3d vertex_b)
: Object()
{
}

Triangle& Triangle::operator=(const Triangle& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    //assignment operator
    return *this;
}


Triangle::~Triangle()
{
    //dtor
}


