#pragma once
#include "ray.h"
#include "HitStructure.h"

class shape {
    public:
        shape() {}
        virtual ~shape() {}
        virtual bool intersect(const ray& ray, float t_min, float t_max, hit_record& rec) const = 0;
        
};