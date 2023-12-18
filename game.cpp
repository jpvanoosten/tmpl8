#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <cassert>
#include <algorithm>

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

	static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);
	static int frame = 0;

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
    Surface image("assets/santa.png");
    // -----------------------------------------------------------
    // Main application tick function
    // -----------------------------------------------------------
    void Game::Tick(float deltaTime)
    {
        // clear the graphics window
        screen->Clear(0);

        float widthRatio = static_cast<float>(image.GetWidth()) / static_cast<float>(screen->GetWidth());
        float heightRatio = static_cast<float>(image.GetHeight()) / static_cast<float>(screen->GetHeight());
        int ledWidth = std::max( static_cast<int>(1.0f / widthRatio), 1);
        int ledHeight = std::max(static_cast<int>(1.0f / heightRatio / 3.0f), 1);

        Pixel* src = image.GetBuffer();
        Pixel* dst = screen->GetBuffer();
        int sw = screen->GetWidth();
        int iw = image.GetWidth();

        for (int y = 0; y < screen->GetHeight(); y += ledHeight * 3 )
        {
            int ty = static_cast<int>(y * heightRatio);
            for (int x = 0; x < screen->GetWidth(); x += ledWidth)
            {
                int tx = static_cast<int>(x * widthRatio);
                Pixel p = src[ty * iw + tx];
                int red = p & 0xff0000;
                int green = p & 0x00ff00;
                int blue = p & 0x0000ff;
                screen->Bar(x, y, x + ledWidth, y + ledHeight, red);
                screen->Bar(x, y + ledHeight, x + ledWidth, y + ledHeight * 2, green);
                screen->Bar(x, y + ledHeight * 2, x + ledWidth, y + ledHeight * 3, blue);
            }
        }
    }
};