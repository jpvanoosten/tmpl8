#pragma once

#include "template.h"

struct Circle
{
    Circle() = default;
    Circle(const Tmpl8::vec2& pos, float radius)
        : position{pos}
        , radius{radius}
    {}

    bool intersect(const Circle& c) const
    {
        // Circles are intersecting if the distance between them is less
        // than the sum of the radii.
        Tmpl8::vec2 d = position - c.position;
        float l2 = d.sqrLentgh();
        float r = radius + c.radius;

        return l2 < r * r;
    }

    Tmpl8::vec2 position{0, 0};
    float radius = 0.0f;
};