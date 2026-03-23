#include "Lambertian.h"
#include "HitStructure.h"
#include "color.h"
#include "shape.h"
#include <vector>

vec3 Lambertian::shade(const hit_record& hit, const ray &r, const std::vector<std::shared_ptr<PointLight>>& lights, const std::vector<std::shared_ptr<Shape>>& shapes, int depth)
{
    //refactor later
    vec3 materialColor = hit.shape->getColor();
    vec3 color(0.0, 0.0, 0.0);
    
    for (const auto& light : lights) {
        vec3 lightPos = light->getPosition();
        vec3 lightDir = unit_vector(light->getPosition() - hit.p);

        bool inShadow = false;
        ray shadowRay(hit.p, lightDir);
        float distanceToLight = (lightPos - hit.p).length();

        for (const auto& shape : shapes){
            hit_record shadowHit;
            if(shape->intersect(shadowRay, 0.001f, distanceToLight, shadowHit)){
                inShadow = true;
                break;
            }

        }
        if(!inShadow){
        float diff = std::max(dot(hit.normal, lightDir), 0.0);
        color += diff * light->getColor() * light->getIntensity();
        }
    }

    vec3 result = materialColor * color;
        // Clamp to [0, 1]
        result = vec3(
            std::min(result.x(), 1.0),
            std::min(result.y(), 1.0),
            std::min(result.z(), 1.0)
        );
        
        return result;
    
    
}
