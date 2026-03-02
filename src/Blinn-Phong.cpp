#include "Blinn-Phong.h"
#include "HitStructure.h"
#include "vec3.h"
#include "shape.h"
#include <vector>

vec3 BlinnPhong::shade(const hit_record& hit, const std::vector<std::shared_ptr<PointLight>>& lights){
    vec3 materialColor = hit.shape->getColor();
    vec3 color = vec3(0.0f, 0.0f, 0.0f);

    float kd = 1.0f;
    float ks = 0.6f;
    float p = 32.0f;
    
    vec3 view_dir = normalize(eyePosition - hit.p);

    for(const auto& light: lights){
        vec3 light_dir = normalize(light->getPosition() - hit.p);
        vec3 half_vector = normalize(light_dir + view_dir);

        float diff = std::max(0.0, dot(hit.normal, light_dir));
        vec3 diffuse = kd * diff * light->getColor() * light->getIntensity();
        

        float spec = std::pow(std::max(0.0, dot(hit.normal, half_vector)), p);
        vec3 specular = ks * spec * light->getColor() * light->getIntensity();

        color += diffuse * materialColor + specular;
    }

    color = vec3(std::min(color.x(), 1.0), std::min(color.y(), 1.0), std::min(color.z(), 1.0));
    return color;
}



