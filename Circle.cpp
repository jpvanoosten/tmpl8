#include "Circle.h"

bool Circle::Collides(const Circle& circle) const
{
    const float r = radius + circle.radius;
    const Tmpl8::vec2 dist = center - circle.center;

    return (r * r) < dist.sqrLentgh(); // Super fast!
}
