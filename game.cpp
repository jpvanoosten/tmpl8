#include "game.h"
#include "surface.h"
#include <cstdio> //printf

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

    void Game::DrawI(int x, int y)
    {
        screen->Line(100 + x, 50 + y, 200 + x, 50 + y, 0xffffff);
        screen->Line(150 + x, 50 + y, 150 + x, 300 + y, 0xffffff);
        screen->Line(100 + x, 300 + y, 200 + x, 300 + y, 0xffffff);
    }

    void Game::DrawFatI(int x, int y, int thickness)
    {
        for(int i = 0; i <= thickness; ++i)
        {
            for(int j = 0; j <= thickness; ++j)
            {
                DrawI(x + i, y + j);
            }
        }
    }

    // -----------------------------------------------------------
    // Main application tick function
    // -----------------------------------------------------------
    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f;

        // clear the graphics window
        screen->Clear(0);

        const float speed = 10.0f;

        DrawFatI(static_cast<int>(x), static_cast<int>(y), 1);

        x += deltaTime * speed;
    }
};