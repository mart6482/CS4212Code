#pragma once
#include "HitStructure.h"
#include "vec3.h"
#include "Light.h"
#include "shape.h"
#include "ray.h"
#include <vector>
#include <memory>

class PointLight;

class shader {
    public:
        shader() {}
        virtual ~shader() {}
        virtual vec3 shade(
            const hit_record& hit, 
            const ray &r, 
            const std::vector<std::shared_ptr<PointLight>>& lights, 
            const std::vector<std::shared_ptr<Shape>>& shapes,
            int depth) = 0;

};