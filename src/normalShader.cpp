#include "normalShader.h"

vec3 normalShader::shade(const hit_record& hit, const std::vector<std::shared_ptr<PointLight>>& lights)
{
    vec3 normalizedNormal = (hit.normal + vec3(1.0, 1.0, 1.0)) * 0.5;
    return normalizedNormal;
}