#ifndef VECTOR3D_H
#define VECTOR3D_H

#include <math.h>

class Vector3d
{
    public:
        ///Public methods

        //Constructors and Destructor
        Vector3d(long double x, long double y, long double z);
        Vector3d(const Vector3d &other);
        virtual ~Vector3d();

        //Accessors
        long double getX() const;
        long double getY() const;
        long double getZ() const;

        //Mutators
        void setX(long double x);
        void setY(long double y);
        void setZ(long double z);

        //Operators
        Vector3d operator+ (const Vector3d &v1) const;  //add two vectors and return the new vector
        Vector3d operator- (const Vector3d &v1) const;  //subtract two vectors and return the new vector
        Vector3d operator* (int i) const;  //Scalar multiplication

        //Other operations
        long double magnitude() const;    //returns magnitude of vector
        long double dot(const Vector3d &other) const;  //returns dot product
        long double angle(const Vector3d &other) const; //returns angle in radians between this vector and other
        Vector3d cross(const Vector3d &other) const;    //returns cross product of this and other

    private:
        ///Private members
        long double m_x;
        long double m_y;
        long double m_z;
};

#endif // VECTOR3D_H
