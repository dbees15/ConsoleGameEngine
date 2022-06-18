#include "Camera.h"

Camera::Camera()
: Object(Vector3d(0,0,0),Vector3d(0,0,0),"camera"), m_viewport(0,0,0)
{
}

Camera::Camera(const Vector3d position, const Vector3d orientation, const Vector3d viewport)
: Object(position,orientation,"camera"), m_viewport(viewport.getX(),viewport.getY(),viewport.getZ())
{
}

Camera::~Camera()
{
}

Camera::Camera(const Camera& other)
: Object(other), m_viewport(other.m_viewport.getX(),other.m_viewport.getY(),other.m_viewport.getZ())
{
}

Camera& Camera::operator=(const Camera& rhs)
{
    if (this == &rhs) return *this; // handle self assignment
    m_orientation = rhs.m_orientation;
    m_position = rhs.m_position;
    return *this;
}

void Camera::setPosition(const Vector3d v)
{
    m_position = v;
}

Vector3d Camera::getViewportPoint(Vector2d cp,Vector2d cd)    //pass canvas pixel location and canvas dimensions
{
    return Vector3d(cp.getX()*m_viewport.getX() / cd.getX(),
                    cp.getY()*m_viewport.getY() / cd.getY(),
                    m_viewport.getZ());
}
