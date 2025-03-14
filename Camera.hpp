#pragma once

#include "AABB.hpp"
#include "template.h"

class Camera
{
public:
    Camera() = default;

    const Tmpl8::vec2& getPos() const
    {
        return pos;
    }

    void setPos(const Tmpl8::vec2& p)
    {
        pos = p;
    }

    Tmpl8::vec2 toScreenSpace(const Tmpl8::vec2& p) const
    {
        return p - pos;
    }

    AABB toScreenSpace(const AABB& aabb) const
    {
        return { toScreenSpace(aabb.min), toScreenSpace(aabb.max) };
    }

private:
    Tmpl8::vec2 pos{0};
};