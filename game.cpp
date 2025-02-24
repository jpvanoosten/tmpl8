#include "game.h"

#include <cassert>

#include "surface.h"

#include "AABB.hpp"
#include "Circle.hpp"

namespace Tmpl8
{
    void Game::Init()
    {
        // Test Circle-Circle collision.
        {
            Circle a{ {0, 0}, 5 };
            Circle b{ {10, 0}, 5 };
            assert(!a.intersect(b));
        }
        {
            Circle a{ {0, 0}, 5 };
            Circle b{ {9.9f, 0}, 5 };
            assert(a.intersect(b));
        }
        {
            AABB a{ {0, 0}, {10, 10} };
            AABB b{ {10, 10}, {20, 20} };
            assert(a.intersect(b));
        }
        {
            AABB a{ {0, 0}, {10, 10} };
            AABB b{ {11, 11}, {20, 20} };
            assert(!a.intersect(b));
        }
        {
            Circle a{ {0, 0}, 10 };
            AABB aabb{ {-5, -5}, {5, 5} };
            assert(aabb.intersect(a));
        }
        {
            Circle a{ {0, 0}, 10 };
            AABB aabb{ {10, 0}, {20, 10} };
            assert(aabb.intersect(a));
        }


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
    }

    void Game::Shutdown() {}


    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);

        tileMap.draw(*screen, 100, 100);
    }
};