#pragma once
#include "shader.h"
#include <vector>
#include <memory>

class BlinnPhong : public shader {
    public:
        BlinnPhong() {}
        vec3 shade(const hit_record& hit, const std::vector<std::shared_ptr<PointLight>>& lights) override;
        void setEyePosition(const vec3& eyePos) { eyePosition = eyePos; }
        vec3 eyePosition = vec3(0.0f, 0.0f, 0.0f);

    private:
        
};