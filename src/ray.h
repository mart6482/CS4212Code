#ifndef RAY_H
#define RAY_H

#include "vec3.h"

class ray{
    public:
        //default constructor
        ray(): origin(point3(0,0,0)), direction(vec3(0,0,0)) {}
        //parameterized constructor
        ray(const point3& origin, const vec3& direction)
            : origin(origin), direction(direction)
            {}

        //getters
        const point3& getOrigin() const { return origin; }
        const vec3& getDirection() const { return direction; }

        //compute point along ray at parameter t
        point3 at(double t) const {
            return origin + t*direction;
        }

    private:
        //variables
        point3 origin;
        vec3 direction;
};

#endif