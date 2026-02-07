#include "shape.h"

class sphere : public shape{

    public:
        sphere(vec3 c, float r): center(c), radius(r) {}
        bool intersect(const ray& r) const override{
            vec3 oc = r.getOrigin() - center;
            float a = dot(r.getDirection(), r.getDirection());
            float b = 2.0f * dot(oc, r.getDirection());
            float c = dot(oc, oc) - radius * radius;
            float discriminant = b * b - 4 * a * c;
            if(discriminant < 0) {
                return false;
            }
            float sqrt_disc = std::sqrt(discriminant);
            float t1 = (-b - sqrt_disc) / (2.0f * a);
            float t2 = (-b + sqrt_disc) / (2.0f * a);
            return (t1 >= 0) || (t2 >= 0);
        }

    private:
        vec3 center;
        float radius;
};