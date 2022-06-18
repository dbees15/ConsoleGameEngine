#ifndef OBJECT_H
#define OBJECT_H

#include "Vector3d.h"
#include "ConsoleEngine.h"
#include <string>

class Object
{
    public:
        Object();
        Object(const Object& other);
        Object(const Vector3d position, const Vector3d orientation, const std::string type);
        Object& operator=(const Object& other);

        virtual void setPosition(const Vector3d v) = 0;
        virtual void setOrientation(const Vector3d v);

        virtual Vector3d getPosition();
        virtual Vector3d getOrientation();
        virtual std::string getType();

    protected:
        Vector3d m_position;
        Vector3d m_orientation;
        const std::string m_type;
};

#endif // OBJECT_H
