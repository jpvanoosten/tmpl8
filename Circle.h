#pragma once

#include "template.h"

struct Circle
{
    Tmpl8::vec2 center{0};
    float radius{0.0f};

    bool Collides(const Circle& circle) const;
};
