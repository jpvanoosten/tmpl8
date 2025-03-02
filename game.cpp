#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <cassert>
#include <algorithm>
#include <windows.h>

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

    // -----------------------------------------------------------
    // Main application tick function
    // -----------------------------------------------------------
    Surface image("assets/ball.png");
    Surface RGB_Led("assets/VRGB_Led.png");

    union Color
    {
        Color() = default;
        Color(Pixel p)
            : p{p}
        {}

        Pixel p;
        struct
        {
            unsigned char b, g, r, a;
        };

        Color operator*(Color rhs) const
        {
            Color res;

            res.b = b * rhs.b / 255;
            res.g = g * rhs.g / 255;
            res.r = r * rhs.r / 255;
            res.a = a * rhs.a / 255;

            return res;
        }

        operator Pixel() const
        {
            return p;
        }
    };

    // -----------------------------------------------------------
    // Main application tick function
    // -----------------------------------------------------------
    void Game::Tick(float deltaTime)
    {
        // clear the graphics window
        screen->Clear(0);

        float sw = static_cast<float>(screen->GetWidth());
        float sh = static_cast<float>(screen->GetHeight());

        for (int y = 0; y < screen->GetHeight(); y += RGB_Led.GetHeight())
        {
            for (int x = 0; x < screen->GetWidth(); x += RGB_Led.GetWidth())
            {
                float u = x / sw;
                float v = y / sh;

                Color p = image.Sample(u, v);
                for (int i = 0; i < RGB_Led.GetHeight(); ++i)
                {
                    for (int j = 0; j < RGB_Led.GetWidth(); ++j)
                    {
                        Color led = RGB_Led.Sample(j, i);
                        screen->Plot(x + j, y + i, p * led);
                    }
                }

            }
        }
    }
};