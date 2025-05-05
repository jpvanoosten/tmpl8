#pragma once

#include "Circle.hpp"
#include "Line.hpp"
#include "template.h"

#include <cfloat>
#include <cmath>
#include <algorithm>
#include <optional>


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

    float width() const
    {
        return max.x - min.x;
    }

    float height() const
    {
        return max.y - min.y;
    }

    float area() const
    {
        return width() * height();
    }

    /// <summary>
    /// Compute the center point of the AABB.
    /// </summary>
    /// <returns>The center point of the AABB.</returns>
    Tmpl8::vec2 center() const
    {
        return (min + max) * 0.5f;
    }

    /// <summary>
    /// Compute the size (diagonal) of the AABB.
    /// </summary>
    /// <returns>Returns the vector from the min to the max point.</returns>
    Tmpl8::vec2 size() const
    {
        return max - min;
    }

    /// <summary>
    /// Compute the extent (1/2 size) of the AABB.
    /// </summary>
    /// <returns>Returns the vector from the min to the center of the AABB.</returns>
    Tmpl8::vec2 extent() const
    {
        return size() * 0.5f;
    }

    /// <summary>
    /// Get a line that spans the top edge of the AABB.
    /// </summary>
    /// <returns>The top edge of the AABB.</returns>
    Line top() const
    {
        return { {min.x, min.y}, {max.x, min.y} };
    }

    /// <summary>
    /// Get a line that spans the bottom edge of the AABB.
    /// </summary>
    /// <returns>The bottom edge of the AABB.</returns>
    Line bottom() const
    {
        return { {min.x, max.y}, {max.x, max.y} };
    }

    /// <summary>
    /// Get a line that spans the left edge of the AABB.
    /// </summary>
    /// <returns>The left edge of the AABB.</returns>
    Line left() const
    {
        return { {min.x, min.y}, {min.x, max.y} };
    }

    /// <summary>
    /// Get a line that spans the right edge of the AABB.
    /// </summary>
    /// <returns>The right edge of the AABB.</returns>
    Line right() const
    {
        return { {max.x, min.y}, {max.x, max.y} };
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


    /// <summary>
    /// Test intersection with a moving AABB.
    /// Source: Real-time collision detection (2005), Christer Ericson. pp. 230-232
    /// </summary>
    /// <param name="aabb">The moving AABB.</param>
    /// <param name="v">The velocity of the AABB.</param>
    /// <param name="t0">(optional) The time of first contact (if any).</param>
    /// <param name="t1">(optional) The time of last contact (if any).</param>
    /// <returns>true if the AABB will intersect. In this case, t0 and t1 will contain the time of intersection.</returns>
    bool intersect(const AABB& aabb, const Tmpl8::vec2& v, float* t0 = nullptr, float* t1 = nullptr)
    {
        // Exit early if AABB's are already overlapping.
        if (intersect(aabb))
        {
            if (t0) *t0 = 0.0f;
            if (t1) *t1 = 0.0f;
            return true;
        }

        float tfirst = 0.0f;
        float tlast = 1.0f;

        // For each axis, determine times of first and last contact, if any.
        for (int i = 0; i < 2; ++i)
        {
            if (v[i] < 0.0f)
            {
                if (aabb.max[i] < min[i]) return false; // Non-intersecting and moving apart.
                if (max[i] < aabb.min[i]) tfirst = std::max((max[i] - aabb.min[i]) / v[i], tfirst);
                if (aabb.max[i] > min[i]) tlast = std::min((min[i] - aabb.max[i]) / v[i], tlast);
            }
            else if (v[i] > 0.0f)
            {
                if (aabb.min[i] > max[i]) return false; // Non-intersecting and moving apart.
                if (aabb.max[i] < min[i]) tfirst = std::max((min[i] - aabb.max[i]) / v[i], tfirst);
                if (max[i] > aabb.min[i]) tlast = std::min((max[i] - aabb.min[i]) / v[i], tlast);
            }

            // No overlap possible if time of first contact occurs after time of last contact.
            if (tfirst > tlast) return false;
        }

        if (t0) *t0 = tfirst;
        if (t1) *t1 = tlast;

        return true;
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

    // Find the closest point on or in this AABB to p.
    // If p is in the AABB, this returns p.
    Tmpl8::vec2 closestPoint(const Tmpl8::vec2& p) const
    {
        return {
            std::max(min.x, std::min(p.x, max.x)),
            std::max(min.y, std::min(p.y, max.y))
        };
    }

    // Test circle/AABB intersection.
    bool intersect(const Circle& circle) const
    {
        // Find the closest point on the AABB to the center of the circle.
        Tmpl8::vec2 c = closestPoint(circle.position);

        // Calculate the distance between the closest point and the center of the circle.
        Tmpl8::vec2 d = circle.position - c;

        // If the distance is less than the radius, the circle is colliding with this AABB.
        return d.sqrLentgh() <= circle.radius * circle.radius;
    }

    /// <summary>
    /// Compute the minimum overlap between a 2D point and this AABB.
    /// </summary>
    /// <param name="p">The point to test for overlap.</param>
    /// <returns>The minimum overlap between the point and this AABB, or a null optional if no overlap occurs.</returns>
    std::optional<Tmpl8::vec2> overlap(const Tmpl8::vec2& p) const noexcept
    {
        if (intersect(p))
        {
            // Compute the min/max overlap in each axis.
            float minX = p.x - min.x;
            float maxX = max.x - p.x;
            float minY = p.y - min.y;
            float maxY = max.y - p.y;

            float xOverlap = std::min(minX, maxX);
            float yOverlap = std::min(minY, maxY);

            Tmpl8::vec2 n{ 0 }; // Collision normal.
            if (xOverlap < yOverlap)
            {
                if (minX < maxX)
                    n = { -1, 0 }; // Point should go left to resolve collision.
                else
                    n = { 1, 0 }; // Point should go right to resolve collision.
            }
            else
            {
                if (minY < maxY)
                    n = { 0, -1 }; // Point should go up to resolve collision.
                else
                    n = { 0, 1 }; // Point should go down to resolve collision.
            }

            return Tmpl8::vec2{ xOverlap, yOverlap } *n;
        }

        return {};
    }

    /// <summary>
    /// Compute the overlap between a circle and this AABB.
    /// </summary>
    /// <param name="circle">The circle to test for overlap.</param>
    /// <returns>The minimum overlap between the circle and this AABB, or a null optional if no overlap occurs.</returns>
    std::optional<Tmpl8::vec2> overlap(const Circle& circle) const noexcept
    {
        Tmpl8::vec2 closestPoint = AABB::closestPoint(circle.position);
        Tmpl8::vec2 d = circle.position - closestPoint;
        float squaredDistance = d.sqrLentgh(); // Squared length between the closest point and the center of the circle.

        if (squaredDistance <= circle.radius * circle.radius)
        {
            Tmpl8::vec2 mtv; // Compute the minimum translation vector.

            // If the circle's center is inside the AABB or almost on the boundary
            if (squaredDistance == 0.0f)
            {
                // Compute the min/max overlap in each axis.
                float minX = circle.position.x - min.x;
                float maxX = max.x - circle.position.x;
                float minY = circle.position.y - min.y;
                float maxY = max.y - circle.position.y;

                float xOverlap = std::min(minX, maxX);
                float yOverlap = std::min(minY, maxY);

                if (xOverlap < yOverlap)
                {
                    if (minX < maxX)
                        mtv = { -circle.radius, 0.0f };
                    else
                        mtv = { circle.radius, 0.0f };
                }
                else
                {
                    if (minY < maxY)
                        mtv = { 0.0f, -circle.radius };
                    else
                        mtv = { 0.0f, circle.radius };
                }
            }
            else
            {
                // The center of the circle is outside the AABB.
                float distance = std::sqrt(squaredDistance);
                if (distance > 0.0f)
                {
                    float penetration = circle.radius - distance + 1.0f; // Penetration depth.
                    mtv = (d / distance) * penetration;
                }
                else
                {
                    mtv = { circle.radius, 0.0f };
                }
            }

            return mtv;
        }

        return {}; // No intersection.
    }

    bool intersect(const Tmpl8::vec2& p0, const Tmpl8::vec2& p1) const
    {
        const Tmpl8::vec2 c = center(); // AABB center point.
        const Tmpl8::vec2 e = extent(); // AABB extent.
        Tmpl8::vec2 m = (p0 + p1) * 0.5f; // Middle point of the line.
        const Tmpl8::vec2 d = p1 - m; // Direction of the line.

        // Translate middle point to the origin.
        m = m - c;

        const float adx = std::abs(d.x);
        if (std::abs(m.x) > e.x + adx)
            return false;

        const float ady = std::abs(d.y);
        if (std::abs(m.y) > e.y + ady)
            return false;

        if (std::abs(m.x * d.y - m.y * d.x) > e.x * ady + e.y * adx)
            return false;

        // No separating axis found, line must be overlapping AABB.
        return true;
    }

    bool intersect(const Line& l) const
    {
        return intersect(l.p0, l.p1);
    }

    static AABB fromXYWH(float x, float y, float w, float h)
    {
        return { {x, y}, {x + w, y + h} };
    }

    Tmpl8::vec2 min{ FLT_MAX };
    Tmpl8::vec2 max{ -FLT_MAX };
};