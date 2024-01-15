#include "game.h"

#include <algorithm>

#include "surface.h"
#include <cstdio> //printf
#include <cmath>

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

    // Source: https://en.wikipedia.org/wiki/HSL_and_HSV#HSV_to_RGB
    Pixel HSVtoRGB( float H, float S = 1.0f, float V = 1.0f )
    {
        float C = V * S;
        float m = V - C;
        float H2 = H / 60.0f;
        float X = C * (1.0f - fabsf(fmodf(H2, 2.0f) - 1.0f));

        vec3 RGB;

        switch (static_cast<int>(H2))
        {
        case 0:
            RGB = { C, X, 0 };
            break;
        case 1:
            RGB = { X, C, 0 };
            break;
        case 2:
            RGB = { 0, C, X };
            break;
        case 3:
            RGB = { 0, X, C };
            break;
        case 4:
            RGB = { X, 0, C };
            break;
        case 5:
            RGB = { C, 0, X };
            break;
        }

        RGB += vec3{ m, m, m };

        const Pixel p =
            static_cast<unsigned int>(RGB.x * 255.0f) << 16 |
            static_cast<unsigned int>(RGB.y * 255.0f) << 8 |
            static_cast<unsigned int>(RGB.z * 255.0f);

        return p;
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

        //for (int y = 0; y < 200; ++y)
        //{
        //    for (int x = 0; x < 200; ++x)
        //    {
        //        int i = y * screen->GetWidth() + x;

        //        screen->Plot(x, y, (x + y & 1) == 1 ? 0x0 : 0xffffff);
        //    }
        //}

        //screen->Bar(200, 0, 400, 200, 0x7f7f7f);

        for(int i = 0; i < screen->GetWidth() - 1; ++i)
        {
            float H = (static_cast<float>(i) / static_cast<float>(screen->GetWidth())) * 360.0f;
            Pixel p = HSVtoRGB(H);

            screen->Line(i, 0, i, screen->GetHeight() - 1, p);
        }

    }
};