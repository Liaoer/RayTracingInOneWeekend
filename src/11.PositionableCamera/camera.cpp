#include "camera.h"

Camera::Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect)
{
    Vec3 u, v, w;
    float theta = vfov * M_PI / 180;
    float half_height = tan(theta / 2);
    float half_widgh = aspect * half_height;
    origin = lookfrom;
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    lower_left_corner = origin - half_widgh * u - half_height * v - w;
    horizontal = 2 * half_widgh * u ;
    vertical = 2 * half_height * v ;
}