#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <iostream>

namespace Tmpl8
{
    constexpr Pixel RED = 0xff0000;
    constexpr Pixel GREEN = 0xff00;
    constexpr Pixel BLUE = 0xff;

    // -----------------------------------------------------------
    // Initialize the application
    // -----------------------------------------------------------
    void Game::Init()
    {
        constexpr float w = 150.0f;
        constexpr float h = 100.0f;
        constexpr float x = (ScreenWidth - w) / 2.0f;
        constexpr float y = (ScreenHeight - h) / 2.0f;

        aabb1 = AABB{ {x, y}, {x + w, y + h} };
    }

    // -----------------------------------------------------------
    // Close down application
    // -----------------------------------------------------------
    void Game::Shutdown()
    {
    }

    // -----------------------------------------------------------
    // Main application tick function
    // -----------------------------------------------------------
    void Game::Tick(float deltaTime)
    {
        // clear the graphics window
        screen->Clear(0);
        constexpr float w = 25.0f;
        AABB aabb{ {mousePos.x - w, mousePos.y - w},{mousePos.x + w, mousePos.y + w} };

        // Draw a cross-hair for the mouse.
        {
            screen->Line(mousePos.x, 0.0f, mousePos.x, ScreenHeight - 1, RED);
            screen->Line(0.0f, mousePos.y, ScreenWidth - 1, mousePos.y, RED);
            // screen->Box(aabb.min.x, aabb.min.y, aabb.max.x, aabb.max.y, GREEN);
            aabb.draw(*screen, GREEN);
        }

        if (aabb.intersect(aabb1.topEdge()))
        {
            aabb1.draw(*screen, RED);
        }
        else
        {
            aabb1.draw(*screen, GREEN);
        }

    }
};