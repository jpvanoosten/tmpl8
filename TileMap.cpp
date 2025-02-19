#include "TileMap.h"

#include <cassert>

TileMap::TileMap(std::shared_ptr<SpriteSheet> spriteSheet, int rows, int columns)
    : spriteSheet{ std::move(spriteSheet) }
    , rows{ rows }
    , columns{ columns }
    , tiles( static_cast<size_t>(rows * columns), -1 )
{}

int& TileMap::operator()(int x, int y)
{
    assert(x >= 0 && x < columns);
    assert(y >= 0 && y < rows);
    return tiles[y * columns + x];
}

int TileMap::operator()(int x, int y) const
{
    assert(x >= 0 && x < columns);
    assert(y >= 0 && y < rows);
    return tiles[y * columns + x];
}

void TileMap::draw(Tmpl8::Surface& surface, int x, int y) const
{
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            int tileId = tiles[i * columns + j];
            if (tileId >= 0)
            {
                auto& sprite = spriteSheet->getSprite(tileId);
                int tileX = j * sprite.getWidth();
                int tileY = i * sprite.getHeight();

                sprite.draw(surface, tileX + x, tileY + y);
            }
        }
    }
}
