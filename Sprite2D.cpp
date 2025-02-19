#include "Sprite2D.hpp"

Sprite2D::Sprite2D(std::shared_ptr<Tmpl8::Surface> image, const Rect& rect)
    : image{std::move(image)}
    , rect{rect}
{}

void Sprite2D::draw(Tmpl8::Surface& surface, int tx, int ty) const
{
    Tmpl8::Pixel* dst = surface.GetBuffer();

    for (int y = 0; y < rect.h; ++y)
    {
        for (int x = 0; x < rect.w; ++x)
        {
            Tmpl8::Pixel src = image->GetBuffer()[(rect.y + y) * image->GetPitch() + (rect.x + x)];
            dst[(ty + y) * surface.GetPitch() + (tx + x)] = src;
        }
    }
}
