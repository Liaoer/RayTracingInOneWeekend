#ifndef METAL_H  
#define METAL_H  
  
#include "material.h"

class metal : public material  
{  
    public:  
        metal(const Vec3& a,float f) : albedo(a),fuzz(f) {}  
        virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const;  
        Vec3 albedo;
        float fuzz; //镜面模糊参数
};


#endif // METAL_H  