#pragma once

#include "SpriteSheet.hpp"
#include "Camera.hpp"

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

    const Tmpl8::vec2& getOrigin() const;
    void setOrigin(const Tmpl8::vec2& origin);

    /// <summary>
    /// Draw the tile map to the surface.
    /// </summary>
    /// <param name="surface">The surface to draw to.</param>
    /// <param name="camera">The camera to offset the tilemap into screen space.</param>
    void draw(Tmpl8::Surface& surface, const Camera& camera) const;

private:
    std::shared_ptr<SpriteSheet> spriteSheet;
    int rows = 0;
    int columns = 0;
    std::vector<int> tiles;

    // The tilemap origin.
    Tmpl8::vec2 origin{0};
};
