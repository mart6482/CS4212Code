#include "shader.h"
#include "color.h"
#include "shape.h"
#include "HitStructure.h"
#include <vector>
#include <memory>

class Lambertian : public shader {
    public:
        Lambertian() {}
         ~Lambertian() {}
        vec3 shade(const hit_record& hit, const ray &r, const std::vector<std::shared_ptr<PointLight>>& lights, const std::vector<std::shared_ptr<Shape>>& shapes, int depth) override;
        
};