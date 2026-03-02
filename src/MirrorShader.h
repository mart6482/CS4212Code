#include "shader.h"
#include "HitStructure.h"

class MirrorShader : public shader {
    public:
        MirrorShader() {}
        vec3 shade(const hit_record& hit, const ray &r, const std::vector<std::shared_ptr<PointLight>>& lights, const std::vector<std::shared_ptr<Shape>>& shapes, int depth) override;
        
};