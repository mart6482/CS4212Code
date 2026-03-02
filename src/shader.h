#pragma once
#include "HitStructure.h"
#include "vec3.h"
#include "Light.h"
#include <vector>
#include <memory>

class PointLight;

class shader {
    public:
        shader() {}
        virtual ~shader() {}
        virtual vec3 shade(const hit_record& hit, const std::vector<std::shared_ptr<PointLight>>& lights) = 0;

};