#pragma once

#include "SpriteSheet.hpp"

class TileMap
{
public:
    TileMap(std::shared_ptr<SpriteSheet> spriteSheet, int rows, int columns);

    // Rule of 5.
    TileMap() = default;
    TileMap(const TileMap& copy) = default;
    TileMap(TileMap&&) = default;
    TileMap& operator=(const TileMap& rhs) = default;
    TileMap& operator=(TileMap&&) = default;
    ~TileMap() = default;


    int& operator()(int x, int y);
    int operator()(int x, int y) const;

    /// <summary>
    /// Draw the tile map with an offset of x, y.
    /// </summary>
    /// <param name="surface">The surface to draw to.</param>
    /// <param name="x">The x offset of the tilemap.</param>
    /// <param name="y">The y offset of the tilemap.</param>
    void draw(Tmpl8::Surface& surface, int x, int y) const;

private:
    std::shared_ptr<SpriteSheet> spriteSheet;
    int rows = 0;
    int columns = 0;
    std::vector<int> tiles;
};
