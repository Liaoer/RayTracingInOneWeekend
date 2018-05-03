#ifndef CAMERA_H  
#define CAMERA_H  
  
#include "ray.h"

class Camera
{
    public:
        Vec3 origin;
        Vec3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
    public:
        Camera();
        Ray getRay(float u,float v);
};

inline Ray Camera::getRay(float u, float v)
{
    return Ray(origin , lower_left_corner + u*horizontal + v * vertical - origin );
}


#endif // CAMERA_H 