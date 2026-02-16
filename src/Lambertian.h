#include "shader.h"

class Lambertian : public shader {
    public:
        Lambertian() {}
         ~Lambertian() {}
        color shade(const hit_record& hit) const override;
};