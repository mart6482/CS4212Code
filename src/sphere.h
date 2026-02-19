#pragma once
#include "shape.h"
#include "HitStructure.h"

class sphere : public shape{

    public:
        sphere(vec3 c, float r): center(c), radius(r) {}
        sphere() : center(vec3(0.0f, 0.0f, 0.0f)), radius(1.0f) {}
        bool intersect(const ray& r, float t_min, float t_max, hit_record& rec) const override{
            vec3 oc = r.getOrigin() - center;
            float a = dot(r.getDirection(), r.getDirection());
            float b = 2.0f * dot(oc, r.getDirection());
            float c = dot(oc, oc) - radius*radius;
            float discriminant = b*b - 4*a*c;
            if (discriminant < 0) {
                return false;
            }
            float sqrt_disc = std::sqrt(discriminant);
            float root = (-b - sqrt_disc) / (2.0f * a);
            if (root < t_min || root > t_max) {
                root = (-b + sqrt_disc) / (2.0f * a);
                if (root < t_min || root > t_max) {
                    return false;
                }
            }
            rec.t = root;
            rec.p = r.at(rec.t);
            rec.normal = (rec.p - center) / radius;
        

                return true;
            }

    private:
        vec3 center;
        float radius;
};