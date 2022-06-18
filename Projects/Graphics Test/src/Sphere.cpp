#include "Sphere.h"

Sphere::Sphere()
: Object(Vector3d(0,0,0),Vector3d(0,0,0),"sphere"), m_radius(0), m_color(COLOR::WHITE)
{
}

Sphere::Sphere(const Sphere &other)
: Object(other), m_radius(other.m_radius), m_color(other.m_color)
{
}

Sphere::Sphere(const Vector3d position, const Vector3d orientation, double radius, COLOR color)
: Object(position,orientation,"sphere"), m_radius(radius), m_color(color)
{
}

Sphere::~Sphere()
{
    //dtor
}

Sphere& Sphere::operator= (const Sphere &other)
{
    if (this == &other) return *this; // handle self assignment
    m_position = other.m_position;
    m_orientation = other.m_orientation;
    m_radius = other.m_radius;
    m_color = other.m_color;
    return *this;
}

void Sphere::setRadius(double r)
{
    m_radius = r;
}

void Sphere::setPosition(const Vector3d v)
{
    m_position = v;
}

double Sphere::getRadius()
{
    return m_radius;
}

COLOR Sphere::getColor()
{
    return m_color;
}
