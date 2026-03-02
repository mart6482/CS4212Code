#pragma once
#include "shader.h"

class BlinnPhong : public shader {
    public:
        BlinnPhong() {}
        virtual ~BlinnPhong();
        virtual color shade(const hit_record& hit, const std::vector<std::shared_ptr<PointLight>>& lights) override;
        void setEyePosition(const vec3& eyePos) { eyePosition = eyePos; }

    private:
        vec3 eyePosition = vec3(0.0f, 0.0f, 0.0f);
};