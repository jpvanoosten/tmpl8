#include "game.h"
#include "surface.h"
#include <cstdio> //printf

namespace Tmpl8
{
	static Sprite rotatingGun(new Surface("assets/aagun.tga"), 36);
	static int frame = 0;

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

    // -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		// clear the graphics window
		screen->Clear(0x064E27);
		// print something in the graphics window
		screen->Print("hello world", 100, 20, 0x00ff00);
		// print something to the text window
		printf("this goes to the console window.\n");
		// draw a sprite
		rotatingGun.SetFrame(frame); rotatingGun.Draw(screen, 100, 100);
		if (++frame == 36) frame = 0;
	}
};