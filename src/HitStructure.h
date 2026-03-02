#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"
//#include "shape.h"
#include "vec3.h"
#include <memory>

class Shape;

class hit_record {
  public:
    point3 p;
    vec3 normal;
    double t;
    const Shape* shape;

    hit_record() : p(point3(0,0,0)), normal(vec3(0,0,0)), t(0), shape(nullptr){}
    
};

class hittable {
  public:
    virtual ~hittable() = default;
    hittable() {}

    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif