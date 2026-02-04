#include "ray.h"

class shape {
    public:
        shape() {}
        virtual ~shape() {}
        virtual bool intersect(const ray& ray) const = 0;
        
};