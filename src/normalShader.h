#pragma once

#include "Shader.h"
#include "HitStructure.h"
#include "vec3.h"
#include <vector>

class normalShader : public shader
{
public:
    vec3 shade(const hit_record& hit, const ray &r, const std::vector<std::shared_ptr<PointLight>>& lights, const std::vector<std::shared_ptr<Shape>>& shapes, int depth) override;
};