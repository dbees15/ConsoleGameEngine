#include "Application.h"

Application::Application(int window_height, int window_width)
: ConsoleEngine(window_height,window_width), m_camera(Vector3d(0,0,0),Vector3d(0,0,1),Vector3d(1.4,1,1))
{
    m_objects.push_back(new Sphere(Vector3d(0,-1,6),Vector3d(0,0,0),1,COLOR::LIGHTGREEN));
    m_objects.push_back(new Sphere(Vector3d(0,1,7),Vector3d(0,0,0),1,COLOR::BLUE));
    m_objects.push_back(new Sphere(Vector3d(0,2,6),Vector3d(0,0,0),2.2,COLOR::LIGHTYELLOW));
    m_objects.push_back(new Sphere(Vector3d(2,0,4),Vector3d(0,0,0),1,COLOR::CYAN));
    m_objects.push_back(new Sphere(Vector3d(-2,0,5),Vector3d(0,0,0),1.2,COLOR::RED));
}

Application::~Application()
{
    //dtor
}

void Application::loopMain()
{
    clock_t t = clock();    //get time at beginning of loop

    //handle movement inputs

    if(m_keystates[87]) //W
    {
        m_camera.setPosition(Vector3d(m_camera.getPosition().getX(),
                                      m_camera.getPosition().getY(),
                                      m_camera.getPosition().getZ()+0.01));
    }

    if(m_keystates[83]) //S
    {
        m_camera.setPosition(Vector3d(m_camera.getPosition().getX(),
                                      m_camera.getPosition().getY(),
                                      m_camera.getPosition().getZ()-0.01));
    }
    if(m_keystates[65]) //A
    {
        m_camera.setPosition(Vector3d(m_camera.getPosition().getX()-0.01,
                                      m_camera.getPosition().getY(),
                                      m_camera.getPosition().getZ()));
    }

    if(m_keystates[68]) //D
    {
        m_camera.setPosition(Vector3d(m_camera.getPosition().getX()+0.01,
                                      m_camera.getPosition().getY(),
                                      m_camera.getPosition().getZ()));
    }

    if(m_keystates[32]) //space
    {
        m_camera.setPosition(Vector3d(m_camera.getPosition().getX(),
                                      m_camera.getPosition().getY()+0.01,
                                      m_camera.getPosition().getZ()));
    }

    if(m_keystates[160]) //L-shift
    {
        m_camera.setPosition(Vector3d(m_camera.getPosition().getX(),
                                      m_camera.getPosition().getY()-0.01,
                                      m_camera.getPosition().getZ()));
    }


    //Handle orientation input

    if(m_keystates[70]) //L-arrow
    {
        m_camera.setOrientation(Vector3d(m_camera.getOrientation().getX()-0.01,
                                      m_camera.getOrientation().getY(),
                                      m_camera.getOrientation().getZ()));
    }
    if(m_keystates[39]) //R-arrow
    {
        m_camera.setOrientation(Vector3d(m_camera.getOrientation().getX()-0.01,
                                      m_camera.getOrientation().getY(),
                                      m_camera.getOrientation().getZ()));
    }


    for(int y=0;y<c_screenHeight;y++)    //iterate through screen pixels
    {
        for(int x=0;x<c_screenWidth;x++)
        {
            Vector2d canvasCoordinates(x-(int)c_screenWidth/2,(int)c_screenHeight/2-y); //convert from screen to canvas coordinates
            //find direction of ray in scene
            Vector3d rayDirection(m_camera.getViewportPoint(Vector2d(canvasCoordinates.getX(),canvasCoordinates.getY()),
                                                            Vector2d(c_screenWidth,c_screenHeight)));

            COLOR col = COLOR::WHITE;
            double pixeldata = traceRay(&col,m_camera.getPosition(),rayDirection,0,10000);   //trace ray, get color information
            if(pixeldata>0) //draw nothing if ray does not hit a valid object
            {


                if(pixeldata<3)
                    fillPixel('#',TEXT_COLOR(col),x,y);
                else if(pixeldata<3.4)
                    fillPixel('&',TEXT_COLOR(col),x,y);
                else if(pixeldata<3.8)
                    fillPixel('*',TEXT_COLOR(col),x,y);
                else if(pixeldata<4.2)
                    fillPixel('%',TEXT_COLOR(col),x,y);
                else
                    fillPixel('+',TEXT_COLOR(col),x,y);
            }
        }
    }

    t = clock() - t;   //get time at end of loop iteration
    drawText("CPU Time: "+std::to_string((double)t/1000.0f) + " seconds",TEXT_COLOR(COLOR::WHITE),0,0);   //display time
}

void Application::loopClear()
{
    fill(' ', TEXT_COLOR(COLOR::BLACK,COLOR::BLACK));
}



double Application::traceRay(COLOR *c, Vector3d camera, Vector3d direction, double min, double max)
{
    long double closest_t = -1;
    Object* closest_object = NULL;

    for(int j=0;j<m_objects.size();j++) //iterate through scene objects
    {

        Vector2d intersection = intersectSphere(camera,direction,(Sphere*)m_objects[j]);
        if((intersection.getX()<=max && intersection.getX()>=min && intersection.getX() < closest_t) || closest_t==-1)
        {
            closest_t = intersection.getX();
            closest_object = m_objects[j];
        }
        if((intersection.getY()<=max && intersection.getY()>=min && intersection.getY() < closest_t) || closest_t==-1)
        {
            closest_t = intersection.getY();
            closest_object = m_objects[j];
        }
    }

    if(closest_object==NULL)
    {
        *c = COLOR::BLACK;
        return -1;
    }
    else
    {
        *c = static_cast<Sphere*>(closest_object)->getColor();
        return closest_t;
    }


}

Vector2d Application::intersectSphere(Vector3d camera, Vector3d direction, Sphere *s) //calculates intersection point (currently only for spheres)
{
    Vector3d co = camera - s->getPosition();

    long double a = direction.dot(direction);
    long double b = co.dot(direction) * 2;
    long double c = co.dot(co) - (s->getRadius() * s->getRadius());

    long double discriminant = b * b - 4 * a * c;
    if(discriminant<0)  //no solutions exist
    {
        return Vector2d(-1,-1);
    }

    //two solutions exist
    long double t1 = (-b + sqrt(discriminant)) / (2*a);
    long double t2 = (-b - sqrt(discriminant)) / (2*a);

    return Vector2d(t1,t2);
}
