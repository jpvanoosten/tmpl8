#include "Sprite2D.hpp"

Sprite2D::Sprite2D(std::shared_ptr<Tmpl8::Surface> image, const Rect& rect)
    : image{ std::move(image) }
    , rect{ rect }
{}

void Sprite2D::draw(Tmpl8::Surface& surface, int spriteX, int spriteY) const
{
    // Sprite dimensions
    int spriteWidth = rect.w;
    int spriteHeight = rect.h;

    // Surface dimensions.
    int screenWidth = surface.GetWidth();
    int screenHeight = surface.GetHeight();

    // Check if sprite is fully outside the screen.
    if (spriteX + spriteWidth < 0 || spriteX >= screenWidth ||
        spriteY + spriteHeight < 0 || spriteY >= screenHeight )
        return;

    Rect clipRect;
    clipRect.x = std::max(spriteX, 0);
    clipRect.y = std::max(spriteY, 0);
    clipRect.w = std::min(spriteX + spriteWidth, screenWidth - 1) - clipRect.x;
    clipRect.h = std::min(spriteY + spriteHeight, screenHeight - 1) - clipRect.y;

    if (clipRect.w > 0 && clipRect.h > 0)
    {
        // Adjust sprite texture coordinates.
        int u = clipRect.x - spriteX + rect.x;
        int v = clipRect.y - spriteY + rect.y;

        // Source image.
        Tmpl8::Pixel* src = image->GetBuffer();
        int imageWidth = image->GetWidth();

        // Destination buffer.
        Tmpl8::Pixel* dst = surface.GetBuffer();

        // Draw the clipped sprite.
        for (int y = 0; y < clipRect.h; ++y)
        {
            int dstY = clipRect.y + y;
            int srcY = v + y;

            for (int x = 0; x < clipRect.w; ++x)
            {
                int dstX = clipRect.x + x;
                int srcX = u + x;

                Tmpl8::Pixel p = src[srcY * imageWidth + srcX];
                // Don't draw transparent pixels.
                if ( (p >> 24) > 127 )
                {
                    dst[dstY * screenWidth + dstX] = p;
                }
            }
        }
    }
}
