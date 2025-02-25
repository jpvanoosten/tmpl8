#pragma once

#include "Circle.hpp"
#include "template.h"

#include <cfloat>
#include <algorithm>


inline Tmpl8::vec2 min(const Tmpl8::vec2& a, const Tmpl8::vec2& b)
{
    return { std::min(a.x, b.x), std::min(a.y, b.y) };
}

inline Tmpl8::vec2 max(const Tmpl8::vec2& a, const Tmpl8::vec2& b)
{
    return { std::max(a.x, b.x), std::max(a.y, b.y) };
}

// Axis-Aligned bounding box.
struct AABB
{
    AABB() = default;

    AABB(const Tmpl8::vec2& p0, const Tmpl8::vec2& p1)
    {
        min = ::min(p0, p1);
        max = ::max(p0, p1);
    }

    /// <summary>
    /// Get this AABB translated by some offset.
    /// </summary>
    /// <param name="rhs">The distance to offset.</param>
    /// <returns>This AABB translated by p.</returns>
    AABB operator+(const Tmpl8::vec2& rhs) const
    {
        return { min + rhs, max + rhs };
    }

    /// <summary>
    /// Get this AABB translated by some offset.
    /// </summary>
    /// <param name="rhs">The distance to translate.</param>
    /// <returns>This AABB translated by p.</returns>
    AABB operator-(const Tmpl8::vec2& rhs) const
    {
        return { min - rhs, max - rhs };
    }

    /// <summary>
    /// Get this AABB at a particular position.
    /// </summary>
    /// <param name="p">The offset to translate the AABB.</param>
    /// <returns></returns>
    AABB at(const Tmpl8::vec2& p) const
    {
        return operator+(p);
    }

    // Test AABB-AABB intersection.
    bool intersect(const AABB& aabb) const
    {
        return
            min.x <= aabb.max.x &&
            min.y <= aabb.max.y &&
            max.x >= aabb.min.x &&
            max.y >= aabb.min.y;
    }

    // Test point-AABB intersection.
    bool intersect(const Tmpl8::vec2& p) const
    {
        return
            p.x >= min.x &&
            p.y >= min.y &&
            p.x <= max.x &&
            p.y <= max.y;
    }

    // Test circle/AABB intersection.
    bool intersect(const Circle& circle) const
    {
        AABB aabb{ min - Tmpl8::vec2{circle.radius}, max + Tmpl8::vec2{circle.radius} };
        return aabb.intersect(circle.position);
    }

    static AABB fromXYWH(float x, float y, float w, float h)
    {
        return { {x, y}, {x + w, y + h} };
    }

    Tmpl8::vec2 min{ FLT_MAX };
    Tmpl8::vec2 max{ -FLT_MAX };
};