#include "game.h"
#include "surface.h"
#include "template.h"
#include <cstdio> //printf

struct TGAHeader
{
    TGAHeader(unsigned short width, unsigned short height)
        : ID(0)
        , colmapt(0)
        , type(2)
        , colmap{ 0 }
        , xorigin(0)
        , yorigin(0)
        , width(width)
        , height(height)
        , bpp(32)
        , idesc(0)
    {}

    unsigned char ID, colmapt;       // set both to 0
    unsigned char type;              // set to 2
    unsigned char colmap[5];         // set all elements to 0
    unsigned short xorigin, yorigin; // set to 0
    unsigned short width, height;    // put image size here
    unsigned char bpp;               // set to 32
    unsigned char idesc;             // set to 0
};

namespace Tmpl8
{
    float x = 200.0f, y = 0.0f, vx = 0.1f, vy = 0.0f;
    void Game::Init()
    {
        FILE* f = fopen("bindat.bin", "wb");
        fwrite(&x, sizeof(x), 1, f);
        fwrite(&y, sizeof(y), 1, f);
        fclose(f);
    }
    void Game::Shutdown() { }

    static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);
    static int frame = 0;

    void Game::Tick(float deltaTime)
    {
        screen->Clear(0);
        FILE* f = fopen("positions.hada", "wb");
        fprintf(f, "X-position: %f\nY-position: %f\n", x, y);
        fclose(f);
        screen->Box(x, y, x + 5, y + 5, 0xffffff);
        if ((vy += 0.02f, y += vy) > ScreenHeight) vy = -vy;
        if ((x += vx < 0) || (x >= ScreenWidth)) vx = -vx;
    }
};