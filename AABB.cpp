#include "AABB.hpp"

#include "surface.h"

void AABB::draw(Tmpl8::Surface& screen, Tmpl8::Pixel color) const
{
    screen.Box(
        static_cast<int>(min.x), static_cast<int>(min.y), 
        static_cast<int>(max.x), static_cast<int>(max.y), 
        color
    );
}