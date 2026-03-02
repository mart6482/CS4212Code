#include "RayTracer.h"
#include "shader.h"
#include "HitStructure.h"
#include "color.h"



class DiffuseShader : public shader {
    public:
        DiffuseShader() {}
        DiffuseShader (vec3 col) : diffuseReflectanceColor(col) {}
         ~DiffuseShader() {}
        vec3 random_in_unit_sphere() const;
        vec3 shade(const hit_record& hit, const ray &r, const std::vector<std::shared_ptr<PointLight>>& lights, const std::vector<std::shared_ptr<Shape>>& shapes, int depth) override;
    
    private:
        vec3 diffuseReflectanceColor;
};