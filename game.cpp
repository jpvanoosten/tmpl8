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

	static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);
	static int frame = 0;

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	Sprite theSprite(new Surface("assets/ctankbase.tga"), 16);
	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		for (int i = 0; i < 16; i++)
		{
			theSprite.SetFrame(i);
			theSprite.Draw(screen, i * 50, 0);
		}
	}
};