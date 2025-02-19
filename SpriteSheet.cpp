#include "SpriteSheet.hpp"

#include <cassert>

SpriteSheet::SpriteSheet(const std::filesystem::path& filePath, int rows, int columns)
    : rows{ rows }
    , columns{ columns }
{
    image = std::make_shared<Tmpl8::Surface>(filePath.string().c_str());
    int w = image->GetWidth() / columns;
    int h = image->GetHeight() / rows;

    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            sprites.emplace_back(image, Rect{ j * w, i * h * image->GetPitch(), w, h } );
        }
    }

}

const Sprite2D& SpriteSheet::getSprite(int x, int y)
{
    return getSprite(y * columns + x);
}

const Sprite2D& SpriteSheet::getSprite(int i)
{
    assert(i >= 0 && i < sprites.size());
    return sprites[i];
}
