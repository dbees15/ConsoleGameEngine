#include "Object.h"

Object::Object()
: m_position(0,0,0), m_orientation(0,0,0), m_type("")
{
}

Object::Object(const Object& other)
: m_position(other.m_position), m_orientation(other.m_orientation), m_type(other.m_type)
{
}

Object::Object(const Vector3d position, const Vector3d orientation, const std::string type)
: m_position(position), m_orientation(orientation), m_type(type)
{
}

void Object::setOrientation(const Vector3d v)
{
    m_orientation = v;
}

Object& Object::operator=(const Object& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    m_position = rhs.m_position;
    m_orientation = rhs.m_orientation;
    return *this;
}

Vector3d Object::getPosition()
{
    return m_position;
}

Vector3d Object::getOrientation()
{
    return m_orientation;
}

std::string Object::getType()
{
    return m_type;
}
