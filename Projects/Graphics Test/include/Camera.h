#ifndef CAMERA_H
#define CAMERA_H

#include "Object.h"
#include "Vector3d.h"
#include "Vector2d.h"

class Camera : public Object
{
    public:
        Camera();
        Camera(const Vector3d position, const Vector3d orientation, const Vector3d viewport);
        virtual ~Camera();
        Camera(const Camera& other);
        Camera& operator=(const Camera& other);

        void setPosition(const Vector3d v);
        Vector3d getViewportPoint(Vector2d cp,Vector2d cd);    //pass canvas pixel location and canvas dimensions

    private:
        Vector3d m_viewport;    //dimenstions of viewport
};

#endif // CAMERA_H
