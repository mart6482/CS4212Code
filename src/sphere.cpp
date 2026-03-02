#include "Sphere.h"

bool Sphere::intersect(const ray& r, float t_min, float& t_max, hit_record& hit) const
{
    vec3 oc = r.getOrigin() - center;

    float a = dot(r.getDirection(), r.getDirection());
    float b = 2.0f * dot(oc, r.getDirection());
    float c = dot(oc, oc) - radius*radius;

    float discriminant = b*b - 4*a*c;

    if (discriminant < 0) {
        return false;
    }

    float sqrt_disc = std::sqrt(discriminant);

    float t1 = (-b - sqrt_disc) / (2.0f * a);
    float t2 = (-b + sqrt_disc) / (2.0f * a);

    if (t1 > t_min && t1 < t_max) {
        t_max = t1;
        hit.t = t1;
        hit.p = r.at(t1);
        hit.shape = this;
        hit.normal = normalize(hit.p - center);
        return true;
    }

    if (t2 > t_min && t2 < t_max) {
        t_max = t2;
        hit.t = t2;
        hit.p = r.at(t2);
        hit.shape = this;
        hit.normal = normalize(hit.p - center);
        return true;
    }

    return false;
}

vec3 Sphere::getColor() const
{
    return color;
}

std::shared_ptr<shader> Sphere::getShader() const
{
    return shader;
}