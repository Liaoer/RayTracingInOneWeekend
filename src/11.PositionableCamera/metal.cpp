#include "metal.h"
#include "lambertian.h"

Vec3 reflect(const Vec3& v, const Vec3& n)
{  
    /*获取镜面反射的反射光线的方向向量。具体计算，后面解释*/  
    return v - 2 * dot(v, n)*n;
}  
  
bool metal::scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const 
{  
    /*这里具体实现metal::scatter()。做两件事情：获取镜面反射的反射光线；获取材料的衰减系数。 */  
    Vec3 reflected = reflect(unit_vector(r_in.Direction()), rec.normal);
    scattered = Ray(rec.p, reflected + fuzz * random_in_unit_sphere());
    attenuation = albedo;
    return (dot(scattered.Direction(), rec.normal) > 0);
} 