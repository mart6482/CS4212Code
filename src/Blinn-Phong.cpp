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
    float BlinnPhongExponent = 32.0f;
    color BlinnPhongComponent = color(pow(nDotH, BlinnPhongExponent), pow(nDotH, BlinnPhongExponent), pow(nDotH, BlinnPhongExponent));
    color result = LambertianComponent + BlinnPhongComponent;

    //clamp the result to [0, 1]
    if (result.x() > 1.0f) result[0] = 1.0f;
    if (result.y() > 1.0f) result[1] = 1.0f;
    if (result.z() > 1.0f) result[2] = 1.0f;
    if (result.x() < 0.0f) result[0] = 0.0f;
    if (result.y() < 0.0f) result[1] = 0.0f;
    if (result.z() < 0.0f) result[2] = 0.0f;
    return result;

    
}

BlinnPhong::~BlinnPhong() {}


