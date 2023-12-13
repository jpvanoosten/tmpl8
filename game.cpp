#include "game.h"
#include "surface.h"
#include "SpriteAnim.h"
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

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	static Sprite theSprite(new Surface("assets/ctankbase.tga"), 16);
	static SpriteAnim animatedGun(&theSprite, 10.0f);

    void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f;

		animatedGun.Update(deltaTime);

		screen->Clear(0);

		for(int j = 0; j < 10; ++j )
		{
		    for( int i = 0; i < 16; ++i )
		    {
				animatedGun.Draw(screen, i * 50, j * 50);
		    }
		}
	}
};