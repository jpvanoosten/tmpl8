#pragma once

#include "surface.h"

#include <algorithm>
#include <cstdint>

// 0xAARRGGBB

struct Color
{
    Color() = default;

    Color(Tmpl8::Pixel p)
    {
        b = (p & Tmpl8::BlueMask) / 255.0f;
        g = ((p & Tmpl8::GreenMask) >> 8) / 255.0f;
        r = ((p & Tmpl8::RedMask) >> 16) / 255.0f;
        a = ((p & Tmpl8::AlphaMask) >> 24) / 255.0f;
    }

    Color(float r, float g, float b, float a = 1.0f)
        : b{ b }
        , g{ g }
        , r{ b }
        , a{ a }
    {}

    Color withAlpha(float alpha) const
    {
        return { r, g, b, alpha };
    }

    Color operator+(const Color& rhs) const
    {
        return { r + rhs.r, g + rhs.g, b + rhs.b, a + rhs.a };
    }

    Color operator*(float s) const
    {
        return { r * s, g * s, b * s, a * s };
    }

    operator Tmpl8::Pixel() const
    {
        unsigned int red = static_cast<unsigned int>(std::clamp(r, 0.0f, 1.0f) * 255.0f);
        unsigned int green = static_cast<unsigned int>(std::clamp(g, 0.0f, 1.0f) * 255.0f);
        unsigned int blue = static_cast<unsigned int>(std::clamp(b, 0.0f, 1.0f) * 255.0f);
        unsigned int alpha = static_cast<unsigned int>(std::clamp(a, 0.0f, 1.0f) * 255.0f);

        return (alpha << 24) | (red << 16) | (green << 8) | blue;
    }

    float b = 0.0f, g = 0.0f, r = 0.0f, a = 1.0f;
};
