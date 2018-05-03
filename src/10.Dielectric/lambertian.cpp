#include "lambertian.h" 


Vec3 random_in_unit_sphere()
{  
    /*漫射材料章节中有介绍过这个函数。这个函数产生一个“起点在原点，长度小于1，方向随机”的向量，该向量和交点处单位法向量相加就得到交点处反射光线随机的方向向量*/  
   Vec3 p;
    do
    {
        p = 2.0 * Vec3(drand48(), drand48(), drand48()) - Vec3(1,1,1);

    } while (p.squared_length() >= 1.0 );
    return p;  
}  

bool lambertian::scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const
{  
    /*这里具体实现lambertian::scatter()。做两件事情：获取漫反射的反射光线；获取材料的衰减系数。 */  
    Vec3 target = rec.p + rec.normal + random_in_unit_sphere();  
    scattered = Ray(rec.p, target-rec.p);  
    attenuation = albedo;  
    return true;  
}