#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <iterator>

#include "template.h"

namespace Tmpl8
{
	constexpr Pixel RED = 0xff0000;
	constexpr Pixel GREEN = 0x00ff00;
	constexpr Pixel BLUE = 0x0000ff;
	constexpr Pixel YELLOW = 0xffff00;

	struct Point
	{
		int x, y;
		Pixel color;
	};

	constexpr Point points[] = {
		{0, 0, RED },
		{ScreenWidth-1, ScreenHeight-1, RED},
		{ScreenWidth-1, 0, RED },
		{0, ScreenHeight-1, BLUE },
		{ScreenWidth-1, ScreenHeight-1, BLUE},
	};

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
		screen->Clear(0);

		for(int i = 1; i < std::size(points); ++i )
		{
			auto p0 = points[i - 1];
			auto p1 = points[i];

			screen->Line(p0.x, p0.y, p1.x, p1.y, p0.color);
		}
	}
};