#include "game.h"
#include "surface.h"
#include "template.h"

namespace Tmpl8
{
    float x = ScreenWidth / 2.0f, y = ScreenHeight / 2.0f;

    void Game::Init() {}

    void Game::Shutdown() {}

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);
        screen->Line(mousex, 0, mousex, screen->GetHeight() - 1, 0xff0000);
        screen->Line(0, mousey, screen->GetWidth() - 1, mousey, 0xff0000);

        float dx = x - mousex, dy = y - mousey;
        float dist = sqrtf(dx * dx + dy * dy);
        if (dist < 10)
            x += dx / dist, y += dy / dist;
        screen->Plot(x, y, 0xffffff);
    }
};