#include "game.h"

#include <array>
#include <vector>

#include "surface.h"
#include "template.h"

namespace Tmpl8
{
    // Single dot on the screen.
    struct Dot
    {
        float x = 0.0f, y = 0.0f;
    };

    std::array<Dot, 1024> dots; // Also stores the size.

    void Game::Init()
    {
        for (Dot& dot : dots)
        {
            dot.x = static_cast<float>(IRand(ScreenWidth - 1));
            dot.y = static_cast<float>(IRand(ScreenHeight - 1));
        }
    }

    void Game::Shutdown() {}

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);
        screen->Line(mousex, 0, mousex, screen->GetHeight() - 1, 0xff0000);
        screen->Line(0, mousey, screen->GetWidth() - 1, mousey, 0xff0000);

        //float dx = x - mousex, dy = y - mousey;
        //float dist = sqrtf(dx * dx + dy * dy);
        //if (dist < 50)
        //    x += dx / dist, y += dy / dist;

        for (Dot& dot : dots)
        {
            float dx = dot.x - mousex;
            float dy = dot.y - mousey;
            float dist = sqrtf(dx * dx + dy * dy);

            if( dist < 50.0f)
            {
                dot.x += dx / dist;
                dot.y += dy / dist;
            }

            screen->Plot(dot.x, dot.y, 0xffffff);
        }
    }
};