#pragma once

#include "template.h"
#include "surface.h"

#include <optional>
#include <windows.h>

struct Circle
{
    explicit Circle(const Tmpl8::vec2& p = Tmpl8::vec2{0}, float r = 0.0f);

    float distance(const Circle& c) const;

    // If an intersection occurs, then this function returns the penetration depth.
    // Otherwise, a disengaged optional value is returned.
    std::optional<float> intersect(const Circle& c) const;

    void draw(Tmpl8::Surface& screen, Tmpl8::Pixel color) const;

    Tmpl8::vec2 position{ 0 };
    float radius;
};
