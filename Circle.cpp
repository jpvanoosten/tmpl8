#include "Circle.hpp"

#include <cmath>

Circle::Circle(const Tmpl8::vec2& p, float r)
    : position{ p }
    , radius{ r }
{
}

float Circle::distance(const Circle& c) const
{
    auto delta = c.position - position;
    return std::sqrt(delta.x * delta.x + delta.y * delta.y);
}

std::optional<float> Circle::intersect(const Circle& c) const
{
    float m = distance(c);
    float rr = radius + c.radius;
    if (m < rr)
    {
        // The penetration depth.
        return m - rr;
    }

    return {}; // Empty disengaged optional.
}

void Circle::draw(Tmpl8::Surface& s, Tmpl8::Pixel c) const
{
    for (int i = 0; i < 64; i++)
    {
        float r1 = static_cast<float>(i) * Tmpl8::PI / 32;
        float r2 = static_cast<float>(i + 1) * Tmpl8::PI / 32;

        s.Line(
            position.x - radius * std::sin(r1), position.y - radius * std::cos(r1),
            position.x - radius * std::sin(r2), position.y - radius * std::cos(r2), c);
    }
}
