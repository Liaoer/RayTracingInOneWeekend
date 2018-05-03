#ifndef MATERIAL_H  
#define MATERIAL_H  

#include "hitable.h"

class material {
    public:
        virtual bool scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const = 0;
};
  
#endif // MATERIAL_H 