#pragma once

#include "template.h"

struct Line
{
    Line(const Tmpl8::vec2& p0, const Tmpl8::vec2& p1)
        : p0{ p0 }
        , p1{ p1 }
    {}

    Tmpl8::vec2 p0{ 0.0f };
    Tmpl8::vec2 p1{ 0.0f };

    // Shrink the both points of the line towards the center of the line.
    Line shrink(float size) const
    {
        const Tmpl8::vec2 dir = (p1 - p0).normalized();
        return { p0 + dir * size, p1 - dir * size };
    }
};
