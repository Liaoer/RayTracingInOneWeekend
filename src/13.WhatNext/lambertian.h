//lambertian漫反射类
#ifndef LAMBERTIAN_H  
#define LAMBERTIAN_H

#include "material.h"  

Vec3 random_in_unit_sphere();

class lambertian : public material  
{  
    public:  
        lambertian(const Vec3& a): albedo(a) {}  
        virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const;/*scatter()获取反射光线和衰减系数*/  
        Vec3 albedo;/*保存衰减系数*/  
};

#endif // LAMBERTIAN_H  