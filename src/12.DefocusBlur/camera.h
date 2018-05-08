#ifndef CAMERA_H  
#define CAMERA_H  
  
#include "ray.h"

Vec3 random_in_unit_disk();

class Camera
{
    public:
        Vec3 origin;
        Vec3 lower_left_corner;
        Vec3 horizontal;
        Vec3 vertical;
        Vec3 u, v, w;
        float lens_radius;
    public:
        Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect, float aperture, float focus_dist);
        Ray getRay(float u,float v);
};

inline Ray Camera::getRay(float s, float t)
{
    Vec3 rd = lens_radius*random_in_unit_disk();
    Vec3 offset = u * rd.x() + v * rd.y();
    return Ray(origin+offset , lower_left_corner + s*horizontal + t * vertical - origin - offset );
}


#endif // CAMERA_H 