#ifndef SPHERE_H  
#define SPHERE_H  
  
#include "hitable.h"  
  
class sphere : public hitable
{//sphere为hitable的子类
public:
    Vec3 center;
    float Radius;
public:
    sphere() {};
    sphere(Vec3 cen, float r) : center(cen), Radius(r) {}
    virtual bool hit(const Ray & r , float tmin , float tmax , hit_record & rec ) const ;
};
 
#endif // SPHERE_H  