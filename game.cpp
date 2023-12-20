#include "game.h"

#include <algorithm>

#include "surface.h"
#include <cstdio> //printf

#include "template.h"

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

    Surface jadeFlower("assets/jade-plant.jpg");

    struct Colour
    {
        Colour() = default;
        Colour(Pixel p)
            : p{p}
        {}

        operator Pixel() const
        {
            return p;
        }

        union
        {
            Pixel p;
            struct
            {
                uint8_t b;
                uint8_t g;
                uint8_t r;
                uint8_t a;
            };
            uint8_t v[4];
        };
    };

    float fade = 1.0f;
    float fadeDuration = 5.0f; // Fade out in n seconds.

    //Pixel Fade(Pixel p)
    //{
    //    uint8_t b = static_cast<uint8_t>(p & 0xff);
    //    uint8_t g = static_cast<uint8_t>((p & 0xff00) >> 8);
    //    uint8_t r = static_cast<uint8_t>((p & 0xff0000) >> 16);

    //    b = static_cast<uint8_t>(static_cast<float>(b) * fade);
    //    g = static_cast<uint8_t>(static_cast<float>(g) * fade);
    //    r = static_cast<uint8_t>(static_cast<float>(r) * fade);

    //    return static_cast<Pixel>(r << 16 | g << 8 | b);
    //}
    Pixel Fade(Colour p)
    {
        const int f = static_cast<int>(fade * 256.0f);

        Colour c;

        c.b = static_cast<uint8_t>((p.b * f) >> 8); // Same as x / 256.
        c.g = static_cast<uint8_t>((p.g * f) >> 8);
        c.r = static_cast<uint8_t>((p.r * f) >> 8);
        c.a = 255u;

        return c;
    }

    Pixel Fade(Pixel p)
    {
        const int f = static_cast<int>(fade * 256.0f);

        uint8_t b = static_cast<uint8_t>(p & 0xff);
        uint8_t g = static_cast<uint8_t>((p & 0xff00) >> 8);
        uint8_t r = static_cast<uint8_t>((p & 0xff0000) >> 16);

        b = static_cast<uint8_t>((b * f) >> 8); // Same as x / 256.
        g = static_cast<uint8_t>((g * f) >> 8);
        r = static_cast<uint8_t>((r * f) >> 8);

        return static_cast<Pixel>(r << 16 | g << 8 | b);
    }

    // -----------------------------------------------------------
    // Main application tick function
    // -----------------------------------------------------------
    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f;

        fade = std::max(fade - deltaTime / fadeDuration, 0.0f);

        // clear the graphics window
        screen->Clear(0);

        for (int y = 0; y < 201; ++y)
        {
            for (int x = 0; x < 201; ++x)
            {
                int i = y * screen->GetWidth() + x;

                Pixel c = i % 2 == 0 ? 0xffffff : 0;
                screen->Plot(x, y, c);
            }
        }

        screen->Bar(200, 0, 400, 200, 0x7f7f7f);
    }
};