#pragma once

#include "vec3.h"
#include "shape.h"
#include "HitStructure.h"

class Triangle : public shape {
    public:
        Triangle() : vertex_a(vec3(0.0,0.0,0.0)), vertex_b(vec3(1.0, 0.0, 0.0)), vertex_c(vec3(0.0, 1.0, 0.0)) { }
        Triangle(const vec3& vertex_a, const vec3& vertex_b, const vec3 &vertex_c)
            : vertex_a(vertex_a), vertex_b(vertex_b), vertex_c(vertex_c) { }

        bool intersect(const ray& r, float t_min, float t_max, hit_record& rec) const override;
        
    private:
        vec3 vertex_a;
        vec3 vertex_b;
        vec3 vertex_c;
};
