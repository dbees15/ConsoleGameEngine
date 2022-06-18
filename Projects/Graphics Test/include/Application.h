#ifndef APPLICATION_H
#define APPLICATION_H

#include <vector>
#include <math.h>
#include <string>
#include <ctime>

#include "ConsoleEngine.h"
#include "Vector3d.h"
#include "Object.h"
#include "Camera.h"
#include "Sphere.h"


class Application : public ConsoleEngine
{
    public:
        Application(int window_height, int window_width);
        virtual ~Application();

        void loopMain();
        void loopClear();

    protected:

    private:
        int windowwidth;
        int windowheight;

        Camera m_camera;
        std::vector<Object*> m_objects;

        double traceRay(COLOR *c, Vector3d camera, Vector3d direction, double min, double max);
        Vector2d intersectSphere(Vector3d camera, Vector3d direction, Sphere *s);
        Vector2d intersectTriangle(Vector3d camera, Vector3d direction, Sphere *s);

};

#endif // APPLICATION_H
