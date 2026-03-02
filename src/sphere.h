#pragma once

#include "vec3.h"
#include "Shape.h"
#include <memory>

class shader;

class Sphere : public Shape
{
public:
    Sphere(): center(vec3(0, 0, 0)), radius(1.0), color(vec3(1.0, 1.0, 1.0)), shader(nullptr) {}
    Sphere(vec3 c, float r): center(c), radius(r), color(vec3(1.0, 1.0, 1.0)), shader(nullptr) {}
    Sphere(vec3 c, float r, vec3 col): center(c), radius(r), color(col), shader(nullptr) {}
    Sphere(vec3 c, float r, vec3 col, std::shared_ptr<shader> shd): center(c), radius(r), color(col), shader(shd) {}

    bool intersect(const ray& ray, float t_min, float& t_max, hit_record& rec) const override;
    vec3 getColor() const override;
    std::shared_ptr<shader> getShader() const override;
private:
    vec3 center;
    float radius;
    vec3 color;
    std::shared_ptr<shader> shader;
};