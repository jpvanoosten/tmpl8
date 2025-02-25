#include "game.h"

#include <cassert>

#include "surface.h"

#include "AABB.hpp"
#include "Circle.hpp"

namespace Tmpl8
{
    void Game::Init()
    {
        std::shared_ptr<SpriteSheet> playerShip = std::make_shared<SpriteSheet>("assets/playership.png", 1, 9);
        tileMap = TileMap{ playerShip, 5, 5 };

        int tileIds[] = {
            0, 0, 0, 0, 0,
            1, 1, 1, 1, 1,
            -1, 0, 0, 0, -1,
            2, 2, 2, 2, 2,
            8, 8, 8, 8, 8
        };

        for (int y = 0; y < 5; ++y)
        {
            for (int x = 0; x < 5; ++x)
            {
                tileMap(x, y) = tileIds[y * 5 + x];
            }
        }

        AABB playerAABB{ {-20, -80}, {20, 0} };
        player = Player{ playerAABB, {ScreenWidth / 2, ScreenHeight / 2} };

        // Setup colliders
        colliders = {
            AABB::fromXYWH(300, 475, 197, 36),
            AABB::fromXYWH(534, 383, 102, 36),
            AABB::fromXYWH(656, 311, 112, 36)
        };
    }

    void Game::Shutdown() {}

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);
        player.draw(*screen);

        for (auto& collider : colliders)
        {
            screen->Box(collider, 0xFF0000);
        }
    }
};