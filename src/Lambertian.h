#include "shader.h"
#include "color.h"

class Lambertian : public shader {
    public:
        Lambertian() {}
         ~Lambertian() {}
        color shade(const hit_record& hit, const std::vector<std::shared_ptr<PointLight>>& lights) override;
        
};