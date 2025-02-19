#include "game.h"
#include "surface.h"

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
    }

    void Game::Shutdown() {}


    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);

        tileMap.draw(*screen, 100, 100);
    }
};