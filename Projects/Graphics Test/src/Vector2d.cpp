#include "Vector2d.h"

Vector2d::Vector2d()
:m_x(0.0),m_y(0.0)
{
}

Vector2d::Vector2d(float x=0,float y=0)
:m_x(x),m_y(y)
{
}

Vector2d::Vector2d(const Vector2d &other)
:m_x(other.m_x),m_y(other.m_y)
{
}

Vector2d::~Vector2d()
{
}

void Vector2d::Clear()
{
    m_x = 0.0;
    m_y = 0.0;
}

void Vector2d::SetX(float x)
{
    m_x = x;
}
void Vector2d::SetY(float y)
{
    m_y = y;
}
void Vector2d::setComponents(float x, float y)
{
    m_x=x;
    m_y=y;
}

void Vector2d::setMagnitude(float m)
{
    Vector2d unitvector(this->unit());
    m_x = unitvector.m_x*m;
    m_y = unitvector.m_y*m;
}

void Vector2d::setAngle(double a)
{
    double m = getMagnitude();
    m_x = m*cos(a);
    m_y = m*sin(a);
}

float Vector2d::getX() const
{
    return m_x;
}

float Vector2d::getY() const
{
    return m_y;
}

float Vector2d::getMagnitude() const
{
    return sqrt(pow(m_x,2)+pow(m_y,2));
}

float Vector2d::getAngle() const
{
    if(m_x==0&&m_y<0)
    {
        return PI*(3/2);
    }
    else if(m_x==0&&m_y>0)
    {
        return PI/2;
    }
    else if(m_x==0&&m_y==0)
    {
        return 0;
    }
    return atan(m_y/m_x);
}

Vector2d Vector2d::unit() const
{
    float magnitude = getMagnitude();
    return Vector2d(m_x/magnitude,m_y/magnitude);
}

Vector2d& Vector2d::operator=(const Vector2d other)
{
    m_x = other.m_x;
    m_y = other.m_y;
    return *this;
}

Vector2d Vector2d::operator+(const Vector2d &other) const
{
    return Vector2d(m_x+other.m_x,m_y+other.m_y);
}

float Vector2d::operator*(const Vector2d &other) const
{
    return m_x*other.m_x + m_y*other.m_y;
}

Vector2d& Vector2d::operator+=(Vector2d &other)
{
    m_x += other.m_x;
    m_y += other.m_y;
    return *this;
}

bool Vector2d::operator==(const Vector2d &other) const
{
    return (m_x==other.m_x)&&(m_y==other.m_y);
}

void Vector2d::debug_printComponents() const
{
    std::cout<<"(x,y) = ("<<m_x<<","<<m_y<<")\n";
}

void Vector2d::debug_PrintPolar() const
{
    std::cout<<"(r,theta) = ("<<getMagnitude()<<","<<getAngle()<<")\n";
}
