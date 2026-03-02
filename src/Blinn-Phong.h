#pragma once
#include "shader.h"
#include <vector>
#include <memory>

class BlinnPhong : public shader {
    public:
        BlinnPhong() {}
        vec3 shade(const hit_record& hit, const ray &r, const std::vector<std::shared_ptr<PointLight>>& lights, const std::vector<std::shared_ptr<Shape>>& shapes, int depth) override;
        void setEyePosition(const vec3& eyePos) { eyePosition = eyePos; }
        vec3 eyePosition = vec3(0.0f, 0.0f, 0.0f);

    private:
        
};