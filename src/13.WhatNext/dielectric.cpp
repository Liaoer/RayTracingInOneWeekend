#include "dielectric.h"
#include "metal.h"

// 折射 
bool refract(const Vec3& v, const Vec3& n, float ni_over_nt, Vec3& refracted) {
    Vec3 uv = unit_vector(v);
    float dt = dot(uv, n);
    float discriminant = 1.0 - ni_over_nt*ni_over_nt*(1 - dt*dt);
    if (discriminant > 0) {
        refracted = ni_over_nt*(uv - n*dt) - n*sqrt(discriminant);
        return true;
    }
    else
        return false;
}

float schlick(float cosine, float ref_idx) {
    float r0 = (1 - ref_idx) / (1 + ref_idx);
    r0 = r0*r0;
    return r0 + (1 - r0)*pow((1 - cosine), 5);
}


bool dielectric::scatter(const Ray& r_in, const hit_record& rec, Vec3& attenuation, Ray& scattered) const 
{
    Vec3 outward_normal;
    Vec3 reflected = reflect(r_in.Direction(), rec.normal);
    float ni_over_nt;
    attenuation = Vec3(1.0, 1.0, 1.0);
    Vec3 refracted;
    float reflect_prob;
    float cosine;
    if (dot(r_in.Direction(), rec.normal) > 0) {
        outward_normal = -rec.normal;
        ni_over_nt = ref_idx;
        cosine = dot(r_in.Direction(), rec.normal) / r_in.Direction().length();
        cosine = sqrt(1 - ref_idx*ref_idx*(1 - cosine*cosine));
    }
    else {
        outward_normal = rec.normal;
        ni_over_nt = 1.0 / ref_idx;
        cosine = -dot(r_in.Direction(), rec.normal) / r_in.Direction().length();
    }
    if (refract(r_in.Direction(), outward_normal, ni_over_nt, refracted))
        reflect_prob = schlick(cosine, ref_idx);
    else
        reflect_prob = 1.0;
    if (drand48() < reflect_prob)
        scattered = Ray(rec.p, reflected);
    else
        scattered = Ray(rec.p, refracted);
    return true;
}
