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

	//Surface noise("assets/noise.png");
	Sprite noise(new Surface("assets/noise.png"), 1);
	int gx = 400, gy = 0;
	void Game::Tick(float deltaTime)
	{
//		screen->Clear(0); // This might not be necessary...
		//noise.CopyTo(screen, 0, 0);
		noise.Draw(screen, 0, 0);

		Pixel address = *(screen->GetBuffer() + (screen->GetWidth() * (gy + 1)) + gx);
		if ((address & 0x00ffffff) == 0) // Mask the alpha channel before you check for black.
		{
			// Keep y in screen bounds.
		    gy = (gy + 1 ) % screen->GetHeight(); 
		}
		else if (gy % 2 == 0)
		{
			++gx;
		}
		else
		{
			--gx;
		}

		// Use bar to draw a 2x2 green dot.
		screen->Bar(gx-20, gy-20, gx+20, gy+20, 0x00ff00);
	}
};