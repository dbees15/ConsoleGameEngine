#ifndef SPHERE_H
#define SPHERE_H

#include "Vector3d.h"
#include "Object.h"

class Sphere : public Object
{
    public:
        Sphere();
        Sphere(const Sphere &other);
        Sphere(const Vector3d position, const Vector3d orientation, double radius, COLOR color);
        Sphere& operator= (const Sphere &other);
        virtual ~Sphere();

        void setRadius(double r);
        void setPosition(const Vector3d v);

        double getRadius();
        COLOR getColor();

    private:
        double m_radius;
        COLOR m_color;
};

#endif // SPHERE_H
