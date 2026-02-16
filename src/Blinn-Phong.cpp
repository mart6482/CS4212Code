#include "Blinn-Phong.h"
#include "HitStructure.h"
#include "color.h"

color BlinnPhong::shade(const hit_record& hit) const {
    vec3 light_dir = normalize(vec3(0.0f, 1.0f, 1.0f));
    vec3 view_dir = normalize(-hit.p);

    // Compute Lambertian component
    float nDotL = std::max(0.0, dot(hit.normal, light_dir));
    color LambertianComponent = color(nDotL, nDotL, nDotL);

    // Compute Blinn-Phong component
    vec3 halfVector = normalize(view_dir + light_dir);
    float nDotH = std::max(0.0, dot(hit.normal, halfVector));
    float BlinnPhongExponent = 2.0f;
    color BlinnPhongComponent = color(pow(nDotH, BlinnPhongExponent), pow(nDotH, BlinnPhongExponent), pow(nDotH, BlinnPhongExponent));
    return LambertianComponent + BlinnPhongComponent;

    
}

BlinnPhong::~BlinnPhong() {}


