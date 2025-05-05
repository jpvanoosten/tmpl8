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

const Tmpl8::vec2& TileMap::getOrigin() const
{
    return origin;
}

void TileMap::setOrigin(const Tmpl8::vec2& o)
{
    origin = o;
}

void TileMap::draw(Tmpl8::Surface& surface, const Camera& camera) const
{
    auto c = camera.getPos();
    for (int i = 0; i < rows; ++i)
    {
        for (int j = 0; j < columns; ++j)
        {
            int tileId = tiles[i * columns + j];
            if (tileId >= 0)
            {
                auto& sprite = spriteSheet->getSprite(tileId);

                int tileX = static_cast<int>( origin.x - c.x ) + j * sprite.getWidth();
                int tileY = static_cast<int>( origin.y - c.y ) + i * sprite.getHeight();

                sprite.draw(surface, tileX, tileY);
            }
        }
    }
}
