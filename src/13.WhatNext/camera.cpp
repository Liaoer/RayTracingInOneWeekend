#include "camera.h"

Camera::Camera(Vec3 lookfrom, Vec3 lookat, Vec3 vup, float vfov, float aspect,float aperture, float focus_dist)
{
    lens_radius = aperture / 2;
    float theta = vfov * M_PI / 180;
    float half_height = tan(theta / 2);
    float half_widgh = aspect * half_height;
    origin = lookfrom;
    w = unit_vector(lookfrom - lookat);
    u = unit_vector(cross(vup, w));
    v = cross(w, u);

    lower_left_corner = origin - half_widgh * focus_dist * u - half_height* focus_dist * v - w * focus_dist;
    horizontal = 2 * half_widgh * focus_dist * u ;
    vertical = 2 * half_height * focus_dist * v ;
}

Vec3 random_in_unit_disk() {  
/*在z=0平面上产生一个“起点在原点，长度小于1，方向随机”的向量。为什么是z=0平面，
这个和相机的倾斜方向有关。（相机的倾斜方向为view up （简称vup，一般设置为（0，1，0）））*/  
    Vec3 p;  
    do {  
        p = 2.0*Vec3((rand()%(100)/(float)(100)), (rand()%(100)/(float)(100)), 0) - Vec3(1,1,0);  
    } while (dot(p,p) >= 1.0);  
    return p;  
}  