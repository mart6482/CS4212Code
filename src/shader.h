#pragma once
#include "HitStructure.h"
#include "color.h"

class shader {
    public:
        shader() {}
        virtual ~shader() {}
        virtual color shade(const hit_record& hit) const = 0;
};