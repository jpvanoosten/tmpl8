#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <cassert>
#include <algorithm>

namespace Tmpl8
{
    // -----------------------------------------------------------
    // Initialize the application
    // -----------------------------------------------------------
    void Game::Init()
    {
    }

    // -----------------------------------------------------------
    // Close down application
    // -----------------------------------------------------------
    void Game::Shutdown()
    {
    }

    static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);
    static int frame = 0;

    // -----------------------------------------------------------
    // Main application tick function
    // -----------------------------------------------------------
    Surface image("assets/ball.png");

    // -----------------------------------------------------------
    // Main application tick function
    // -----------------------------------------------------------
    void Game::Tick(float deltaTime)
    {
        // clear the graphics window
        screen->Clear(0);

        float sw = static_cast<float>(screen->GetWidth());
        float sh = static_cast<float>(screen->GetHeight());

        for (int y = 0; y < screen->GetHeight(); ++y)
        {
            for (int x = 0; x < screen->GetWidth(); ++x)
            {
                float u = x / sw;
                float v = y / sh;
                Pixel p = image.Sample(u, v);

                switch (y % 11)
                {
                default:
                case 0:
                case 1:
                case 2:
                    p = p & 0xff0000;
                    break;
                case 3:
                    p = 0;
                    break;
                case 4:
                case 5:
                case 6:
                    p = p & 0x00ff00;
                    break;
                case 7:
                    p = 0;
                    break;
                case 8:
                case 9:
                case 10:
                    p = p & 0x0000ff;
                    break;
                }

                screen->Plot(x, y, p);
            }
        }
    }
};