#pragma once

#include "Sprite2D.hpp"

#include "surface.h"

#include <vector>
#include <filesystem>
#include <memory>

class SpriteSheet
{
public:
    SpriteSheet() = default;
    SpriteSheet(const std::filesystem::path& filePath, int rows, int columns);

    // Get a sprite at x, y coords in the spritesheet.
    const Sprite2D& getSprite(int x, int y);
    // Get a sprite at the 1D index in the spritesheet array.
    const Sprite2D& getSprite(int i);

private:
    int rows = 0;
    int columns = 0;
    std::shared_ptr<Tmpl8::Surface> image;
    std::vector<Sprite2D> sprites;
};
