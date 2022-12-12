#include "game.h"
#include "surface.h"
#include <cstdio> //printf

#include "template.h"

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
	static Sprite theSprite(new Surface("assets/ball.png"), 1);
	static int frame = 0;
	int spriteX = 0;
	int spriteY = 100;
	int speed = 1;
	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		spriteY += speed;
		speed += 1;

		const bool hitBottom = spriteY > ScreenHeight - theSprite.GetHeight();
		printf("hitBottom: %i\n", hitBottom);

		if (hitBottom)
		{
			spriteY = ScreenHeight - theSprite.GetHeight();
			speed = -(speed - 2);
			screen->Clear(0xff0000);
		}
		else
		{
			screen->Clear(0);
		}
		theSprite.Draw(screen, spriteX, spriteY);
	}
};