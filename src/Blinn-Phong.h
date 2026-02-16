#pragma once
#include "shader.h"

class BlinnPhong : public shader {
    public:
        BlinnPhong() {}
        virtual ~BlinnPhong();
        virtual color shade(const hit_record& hit) const override;
};