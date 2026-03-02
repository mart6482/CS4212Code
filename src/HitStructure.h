#ifndef HITTABLE_H
#define HITTABLE_H

#include "ray.h"

class hit_record {
  public:
    point3 p;
    vec3 normal;
    double t;
    const shape* shape;

    hit_record() : p(point3(0,0,0)), normal(vec3(0,0,0)), t(0){}
    
};

class hittable {
  public:
    virtual ~hittable() = default;
    hittable() {}

    virtual bool hit(const ray& r, double ray_tmin, double ray_tmax, hit_record& rec) const = 0;
};

#endif