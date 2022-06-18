#ifndef VECTOR2D_H
#define VECTOR2D_H
#include <math.h>
#include <iostream>
#define PI 3.14159

class Vector2d
{
    public:
        Vector2d();
        Vector2d(float x,float y);
        Vector2d(const Vector2d &other);
        ~Vector2d();

        void SetX(float x);
        void SetY(float y);
        void setComponents(float x, float y);

        float getX() const;
        float getY() const;
        void setMagnitude(float m);
        float getMagnitude() const;

        void setAngle(double a);        //set angle in radians
        float getAngle() const;         //returns angle in radians
        void Clear();                  //sets object to zero vector

        Vector2d unit() const;        //returns unit vector in calling object's direction


        Vector2d &operator=(const Vector2d other);               //simple assignment
        Vector2d operator+(const Vector2d &other) const;    //vector addition, returns new object
        float operator*(const Vector2d &other) const;       //dot product
        Vector2d &operator+=(const Vector2d &other);              //addition assignment, returns calling object
        bool operator==(const Vector2d &other) const;       //vector equality

        void debug_printComponents() const; //cout components of vector
        void debug_PrintPolar() const;      //cout polar coordinates of vector

    private:
        float m_x,m_y;


};

///*******************************IMPLEMENTATION**************************************************

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

Vector2d& Vector2d::operator+=(const Vector2d &other)
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


#endif // VECTOR2D_H
