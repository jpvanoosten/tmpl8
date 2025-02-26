#pragma once

#include "template.h"

struct Line
{
    Line() = default;
    Line(const Tmpl8::vec2& p0, const Tmpl8::vec2& p1)
        : p0{ p0 }
        , p1{ p1 }
    {}

    /// <summary>
    /// Get the length of the line.
    /// </summary>
    /// <returns>The length of the line.</returns>
    float length() const
    {
        return (p1 - p0).length();
    }

    Line shrink(float amount)
    {
        Tmpl8::vec2 d = (p1 - p0).normalized() * amount;
        return { p0 + d, p1 - d };
    }

    Tmpl8::vec2 p0{ 0 };
    Tmpl8::vec2 p1{ 0 };
};