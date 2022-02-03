#include "game.h"
#include "surface.h"
#include "template.h"

namespace Tmpl8
{
    void Game::Init() {}

    void Game::Shutdown() {}

    Surface* img = new Surface("assets/aagun.tga");
    float dx = 2.0f;
    void Game::Tick(float deltaTime)
    {
        Pixel* dst = screen->GetBuffer();
        Pixel* src = img->GetBuffer();
        int srcWidth = img->GetWidth();
        int srcHeight = img->GetHeight();
        for (int x = 0; x < ScreenWidth; x++)
            for (int y = 0; y < ScreenHeight; y++)
            {
                int readxpos = (int)(dx * x) % srcWidth;
                int readypox = (int)(dx * y) % srcHeight;
                Pixel sample = src[readxpos + readypox * srcWidth];
                dst[x + y * ScreenWidth] = sample;
            }
        dx *= 0.999f;
    }
};