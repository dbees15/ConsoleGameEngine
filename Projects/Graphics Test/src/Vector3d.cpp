#include "Vector3d.h"

Vector3d::Vector3d(long double x, long double y, long double z)
: m_x(x), m_y(y), m_z(z)
{}

Vector3d::Vector3d(const Vector3d &other)
: m_x(other.m_x), m_y(other.m_y), m_z(other.m_z)
{

}

Vector3d::~Vector3d()
{
    //dtor
}



long double Vector3d::getX() const
{
    return m_x;
}

long double Vector3d::getY() const
{
    return m_y;
}

long double Vector3d::getZ() const
{
    return m_z;
}

void Vector3d::setX(long double x)
{
    m_x = x;
}

void Vector3d::setY(long double y)
{
    m_y = y;
}

void Vector3d::setZ(long double z)
{
    m_z = z;
}

Vector3d Vector3d::operator+ (const Vector3d &v1) const //add two vectors and return the new vector
{
    return Vector3d(m_x+v1.m_x,m_y+v1.m_y,m_z+v1.m_z);
}

Vector3d Vector3d::operator- (const Vector3d &v1) const //subtract two vectors and return the new vector
{
    return Vector3d(m_x-v1.m_x,m_y-v1.m_y,m_z-v1.m_z);
}

Vector3d Vector3d::operator* (int i) const  //Scalar multiplication
{
    return Vector3d(m_x*i,m_y*i,m_z*i);
}

long double Vector3d::magnitude() const
{
    return sqrt(pow(m_x,2)+pow(m_y,2)+pow(m_z,2));
}

long double Vector3d::dot(const Vector3d &other) const  //returns dot product
{
    return m_x*other.m_x + m_y*other.m_y + m_z*other.m_z;
}

long double Vector3d::angle(const Vector3d &other) const  //returns angle in radians between this vector and other
{
    return acos(dot(other) / (magnitude() * other.magnitude()));  //dot product over product of magnitudes
}

Vector3d Vector3d::cross(const Vector3d &other) const   //returns cross product of this and other
{
    long double x = m_y*other.m_z - m_z*other.m_y;
    long double y = m_z*other.m_x - m_x*other.m_z;
    long double z = m_x*other.m_y - m_y*other.m_x;
    return Vector3d(x,y,z);
}
