#include "Lambertian.h"
#include "HitStructure.h"
#include "color.h"

color Lambertian::shade(const hit_record& hit) const {
    vec3 light_dir = normalize(vec3(0.0f, 1.0f, 1.0f));
    float nDotL = std::max(0.0, dot(hit.normal, light_dir));
    return color(nDotL, nDotL, nDotL);
}
