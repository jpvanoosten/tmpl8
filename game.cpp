#include "game.h"
#include "surface.h"
#include <cstdio> //printf

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
	int gx = 400, gy = 0;
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		noise.CopyTo(screen, 0, 0);

		Pixel address = *(screen->GetBuffer() + (screen->GetWidth() * (gy + 1)) + gx);
		if ((address & 0x00ffffff) == 0) // Mask the alpha channel before you check for black.
		{
			++gy;
		}
		else if (gy % 2 == 0)
		{
			++gx;
		}
		else
		{
			--gx;
		}

		gy %= screen->GetHeight();

		// Use bar to draw a 2x2 green dot.
		screen->Bar(gx-1, gy-1, gx+1, gy+1, 0x00ff00);
	}
};