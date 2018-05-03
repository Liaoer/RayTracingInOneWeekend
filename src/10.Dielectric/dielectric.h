
 
#ifndef DIELECTRIC_H  
#define DIELECTRIC_H  
  
#include "material.h"  
#include "metal.h"

class dielectric : public material {
public:
    float ref_idx;
public:
    dielectric(float ri) : ref_idx(ri) {}
    virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const;
};



#endif // DIELECTRIC_H  