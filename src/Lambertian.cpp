#include "Lambertian.h"
#include "HitStructure.h"
#include "color.h"
#include <vector>

color Lambertian::shade(const hit_record& hit, const std::vector<std::shared_ptr<PointLight>>& lights){
    vec3 materialColor = hit.shape->getcolor();
    vec3 color = vec3(0.0f, 0.0f, 0.0f);

    for(const auto& light : lights){
        vec3 light_dir = normalize(light->getPosition() - hit.p);
        float diff = std::max(0.0, dot(hit.normal, light_dir));
        color += diff * light->getColor() * light->getIntensity();
    }

    vec3 result = materialColor * color;

    result = vec3(std::min(result.x(), 1.0), std::min(result.y(), 1.0), std::min(result.z(), 1.0));

    return result;
}
