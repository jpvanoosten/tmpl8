#include "game.h"
#include "surface.h"
#include <cstdio> //printf
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

	Surface noise("assets/noise.png");

	int x = 400;
	int y = 0;
    constexpr int dotSize = 4;

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		Pixel c = noise.GetPixel(x, y);
		if((c & 0xff) < 127) // Black!
		{
			y = (y + 1) % noise.GetHeight();
		}
		else
		{
		    if (y % 2 == 0) // even.
		    {
				x = (x + 1) % noise.GetWidth();
		    }
			else
			{
				x = (x + noise.GetWidth() - 1) % noise.GetWidth();
			}
		}

		// clear the graphics window
		screen->Clear(0);
		noise.CopyTo(screen, 0, 0);

		// Draw dot.
		screen->Bar(x - dotSize, y - dotSize, x + dotSize, y + dotSize, 0x00ff00);
	}
};