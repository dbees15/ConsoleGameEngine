#include <iostream>

#include "Application.h"

using namespace std;

int main()
{
    Application app(100,100);   //default 140, 100
    app.startLoop();

    /*
    Vector3d v1(2,3,4);
    Vector3d v2(5,6,7);

    Vector3d v3 = v1.cross(v2);
    std::cout<<v3.getX()<<" "<<v3.getY()<<" "<<v3.getZ()<<"\n";
    */

    return 0;
}
