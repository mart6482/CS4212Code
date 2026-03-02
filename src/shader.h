#pragma once
#include "HitStructure.h"
#include "color.h"
#include "Light.h"

class shader {
    public:
        shader() {}
        virtual ~shader() {}
        virtual color shade(const hit_record& hit, const std::vector<std::shared_ptr<PointLight>>& lights) = 0;

};