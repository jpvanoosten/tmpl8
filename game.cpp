#include "game.h"
#include "surface.h"
#include "template.h"
#include <cstdio> //printf
#include <iostream>
#include <tuple>

namespace Tmpl8
{
    float x = 200.0f, y = 0.0f, vx = 0.1f, vy = 0.0f;

    void Game::Init()
    {
        FILE* f = fopen("bindat.bin", "wb");
        fwrite(&x, 4, 1, f);
        fwrite(&y, 4, 1, f);
        fclose(f);
    }

    void Game::Shutdown() { }

    static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);
    static int frame = 0;

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);
        FILE* f = fopen("positions.txt", "a");
        fprintf(f, "X-position: %f\nY-position: %f\n", x, y);
        fclose(f);
        screen->Box(x, y, x + 5, y + 5, 0xffffff);
        if ((vy += 0.02f, y += vy) > ScreenHeight) vy = -vy;
        if ((x += vx < 0) || (x >= ScreenWidth)) vx = -vx;
    }
};