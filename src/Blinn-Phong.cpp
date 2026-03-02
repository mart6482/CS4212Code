#include "Blinn-Phong.h"
#include "HitStructure.h"
#include "vec3.h"
#include "shape.h"
#include <vector>

vec3 BlinnPhong::shade(const hit_record& hit, const ray &r, const std::vector<std::shared_ptr<PointLight>>& lights, const std::vector<std::shared_ptr<Shape>>& shapes, int depth){
    vec3 materialColor = hit.shape->getColor();
    vec3 color = vec3(0.0f, 0.0f, 0.0f);

    float kd = 1.0f;
    float ks = 0.6f;
    float p = 32.0f;
    
    vec3 view_dir = normalize(eyePosition - hit.p);

    for(const auto& light: lights){
        vec3 light_dir = normalize(light->getPosition() - hit.p);
        vec3 light_pos = normalize(light->getPosition());
        vec3 half_vector = normalize(light_dir + view_dir);
        bool inShadow = false;
        ray shadowRay(hit.p, light_dir);
        float distanceToLight = (light_pos - hit.p).length();

        for(const auto& shape : shapes){
            hit_record shadowHit;
            if(shape->intersect(shadowRay, 0.001f, distanceToLight, shadowHit)){
                inShadow = true;
                break;
            }
        }

        if(!inShadow){
            float diff = std::max(0.0, dot(hit.normal, light_dir));
            vec3 diffuse = kd * diff * light->getColor() * light->getIntensity();
            

            float spec = std::pow(std::max(0.0, dot(hit.normal, half_vector)), p);
            vec3 specular = ks * spec * light->getColor() * light->getIntensity();

            color += diffuse * materialColor + specular;
        }
    }

    color = vec3(std::min(color.x(), 1.0), std::min(color.y(), 1.0), std::min(color.z(), 1.0));
    return color;
}



