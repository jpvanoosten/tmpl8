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
};
