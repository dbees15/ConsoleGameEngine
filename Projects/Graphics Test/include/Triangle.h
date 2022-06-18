#ifndef TRIANGLE_H
#define TRIANGLE_H

#include "Object.h"

class Triangle
{
    public:
        Triangle();
        Triangle(const Triangle& other);
        Triangle& operator=(const Triangle& other);
        Triangle(const Vector3d root, const Vector3d vertex_a, const Vector3d vertex_b);

        virtual ~Triangle();


        Vector3d getVertexA_local() const;  //clone of Object::getPosition()
        Vector3d getVertexB_local() const;
        Vector3d getVertexC_local() const;

        Vector3d getVertexA_global() const;  //clone of Object::getPosition()
        Vector3d getVertexB_global() const;
        Vector3d getVertexC_global() const;


    private:
        Vector3d m_a;   //root of triangle
        Vector3d m_b;   //global position of b
        Vector3d m_c;   //global position of c

        Vector3d m_b_local; //local position of b
        Vector3d m_c_local; //local position of c

};

#endif // TRIANGLE_H
