#pragma once

#include "surface.h"
#include "Rect.hpp"

#include <memory>

class Sprite2D
{
public:
    Sprite2D() = default; // Compiler will generate the constructor for us!

    // A sprite is just a tile in an image.
    Sprite2D(std::shared_ptr<Tmpl8::Surface> image, const Rect& rect);

    void draw(Tmpl8::Surface& surface, int x, int y) const;

    int getWidth() const { return rect.w;  }
    int getHeight() const { return rect.h; }

private:
    std::shared_ptr<Tmpl8::Surface> image;
    Rect rect;
};