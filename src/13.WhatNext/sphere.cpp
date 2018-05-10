#include "sphere.h"

inline bool sphere::hit(const Ray & r, float tmin, float tmax, hit_record & rec) const
{
    Vec3 oc = r.Origin() - center;
    float a = dot(r.Direction(), r.Direction());
    float b = dot(oc, r.Direction());
    float c = dot(oc, oc) - Radius * Radius;
    float discriminant  = b * b - a * c;

    if (discriminant > 0)
    {
        float temp = (-b - sqrt(b*b - a*c)) / (a) ;
        if (temp < tmax && temp > tmin)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / Radius;
            rec.mat_ptr = ma;
            return true;
        }
        temp = (-b + sqrt(b*b - a*c)) / ( a);
        if (temp < tmax && temp > tmin)
        {
            rec.t = temp;
            rec.p = r.point_at_parameter(rec.t);
            rec.normal = (rec.p - center) / Radius;
            rec.mat_ptr = ma;
            return true;
        }
    }
    return false;
}