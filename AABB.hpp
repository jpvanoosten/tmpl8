#pragma once

#include "template.h"

#include <algorithm> // std::min & std::max
#include <limits>    // std::numeric_limits<float>

#include "surface.h"

#include "Line.hpp"

namespace Tmpl8
{
    class Surface;
}

struct AABB
{
    // Construct AABB from 2 points.
    AABB(const Tmpl8::vec2& a, const Tmpl8::vec2& b) noexcept
        : min{ std::min(a.x, b.x), std::min(a.y, b.y) }
        , max{ std::max(a.x, b.x), std::max(a.y, b.y) }
    {}

    // Translate AABB.
    AABB operator+(const Tmpl8::vec2& rhs) const noexcept
    {
        return { min + rhs, max + rhs };
    }

    // Translate AABB.
    AABB& operator+=(const Tmpl8::vec2& rhs) noexcept
    {
        min += rhs;
        max += rhs;

        return *this;
    }

    // Translate AABB.
    AABB operator-(const Tmpl8::vec2& rhs) const noexcept
    {
        return { min - rhs, max - rhs };
    }

    // Translate AABB.
    AABB& operator-=(const Tmpl8::vec2& rhs) noexcept
    {
        min -= rhs;
        max -= rhs;

        return *this;
    }

    // Return the left-most point of the AABB.
    float left() const noexcept
    {
        return min.x;
    }

    // Return the right-most point of the AABB.
    float right() const noexcept
    {
        return max.x;
    }

    // Return the top-most point of the AABB.
    float top() const noexcept
    {
        return min.y;
    }

    // Return the bottom-most point of the AABB.
    float bottom() const noexcept
    {
        return max.y;
    }

    Line leftEdge() const noexcept
    {
        return { {min.x, min.y}, {min.x, max.y} };
    }

    Line rightEdge() const noexcept
    {
        return { {max.x, min.y}, {max.x, max.y} };
    }

    Line topEdge() const noexcept
    {
        return { {min.x, min.y}, {max.x, min.y} };
    }

    Line bottomEdge() const noexcept
    {
        return { {min.x, max.y}, {max.x, max.y} };
    }

    // Compute the center point of the AABB.
    Tmpl8::vec2 center() const noexcept
    {
        return (min + max) * 0.5f;
    }

    // Get the width of the AABB.
    float width() const noexcept
    {
        return max.x - min.x;
    }

    // Get the height of the AABB.
    float height() const noexcept
    {
        return max.y - min.y;
    }

    // Get the area of the AABB.
    float area() const noexcept
    {
        return width() * height();
    }

    // Get the size (the diagonal from min -> max) of the AABB.
    Tmpl8::vec2 size() const noexcept
    {
        return max - min;
    }

    // The extent of the AABB is 1/2 of the size of the AABB.
    Tmpl8::vec2 extent() const noexcept
    {
        return size() * 0.5f;
    }

    // Check if a point is inside the AABB.
    bool contains(const Tmpl8::vec2& point) const noexcept
    {
        return (point.x >= min.x && point.x <= max.x) &&
            (point.y >= min.y && point.y <= max.y);
    }

    // Check if another AABB is intersecting with this one.
    bool intersect(const AABB& other) const noexcept
    {
        return (min.x <= other.max.x && min.y <= other.max.y) &&
            (max.x >= other.min.x && max.y >= other.min.y);
    }

    // Check to see if the line {p0, p1} intersects the AABB
    bool intersect(const Tmpl8::vec2& p0, const Tmpl8::vec2& p1) const
    {
        // Find min and max X for the segment
        float minX = p0.x;
        float maxX = p1.x;

        if (p0.x > p1.x)
        {
            minX = p1.x;
            maxX = p0.x;
        }

        // Find the intersection of the segment's and rectangle's x-projections
        if (maxX > max.x)
        {
            maxX = max.x;
        }

        if (minX < min.x)
        {
            minX = min.x;
        }

        if (minX > maxX) // If their projections do not intersect return false
        {
            return false;
        }

        // Find corresponding min and max Y for min and max X we found before
        float minY = p0.y;
        float maxY = p1.y;

        float dx = p1.x - p0.x;

        if (std::abs(dx) > 0.0000001f)
        {
            float a = (p1.y - p0.y) / dx;
            float b = p0.y - a * p0.x;
            minY = a * minX + b;
            maxY = a * maxX + b;
        }

        if (minY > maxY)
        {
            std::swap(minY, maxY);
        }

        // Find the intersection of the segment's and rectangle's y-projections
        if (maxY > max.y)
        {
            maxY = max.y;
        }

        if (minY < min.y)
        {
            minY = min.y;
        }

        if (minY > maxY) // If Y-projections do not intersect return false
        {
            return false;
        }

        return true;
    }

    bool intersect(const Line& l) const
    {
        return intersect(l.p0, l.p1);
    }

    // Draw the AABB to the screen.
    void draw(Tmpl8::Surface& screen, Tmpl8::Pixel color) const;

    AABB() noexcept = default;
    AABB(const AABB&) noexcept = default;
    AABB(AABB&&) noexcept = default;
    ~AABB() noexcept = default;
    AABB& operator=(const AABB&) noexcept = default;
    AABB& operator=(AABB&&) noexcept = default;

    Tmpl8::vec2 min{ std::numeric_limits<float>::max() };
    Tmpl8::vec2 max{ std::numeric_limits<float>::lowest() };
};