#pragma once
#include "ray.h"
#include "HitStructure.h"
#include "shader.h"

class shape {
    public:
        shape() {}
        virtual ~shape() {}
        virtual bool intersect(const ray& ray, float t_min, float t_max, hit_record& rec) const = 0;
        virtual vec3 getColor() const = 0;
        virtual std::shared_ptr<shader> getShader() const = 0;
        
};