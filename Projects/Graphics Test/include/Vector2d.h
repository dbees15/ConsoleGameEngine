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
        Vector2d &operator+=(Vector2d &other);              //addition assignment, returns calling object
        bool operator==(const Vector2d &other) const;       //vector equality

        void debug_printComponents() const; //cout components of vector
        void debug_PrintPolar() const;      //cout polar coordinates of vector

    private:
        float m_x,m_y;


};


#endif // VECTOR2D_H
