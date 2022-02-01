#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <iostream>

#define _WIN32_LEAN_AND_MEAN
#include <Windows.h>

#include "SDL_keycode.h"

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
	int x[8] = { 5, 6, 7, 8, 9, 10, 11, 12 };
	int y[8] = { 8, 8, 8, 8, 8, 8, 8, 8 };
	int heading = 0;
	const int delta[8] = { 1, 0, 0, 1, -1, 0, 0, -1 };
	int head = 7, tail = 0;

	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		for (int i = 0; i < 8; i++)
			screen->Box(x[i] * 8, y[i] * 8, x[i] * 8 + 6, y[i] * 8 + 6, 0xffffff);
		int headx = x[head] + delta[heading * 2];
		int heady = y[head] + delta[heading * 2 + 1];
		tail = (tail + 1) % 8;
		head = (head + 1) % 8;
		x[head] = headx;
		y[head] = heady;
		//if (GetAsyncKeyState(VK_LEFT)) heading = (heading + 3) % 4;
		//if (GetAsyncKeyState(VK_RIGHT)) heading = (heading + 1) % 4;
		Sleep(100);
	}

	void Game::KeyDown(int key)
	{
		switch (key)
		{
		case SDL_SCANCODE_LEFT:
			heading = (heading + 3) % 4;
			break;
		case SDL_SCANCODE_RIGHT:
			heading = (heading + 1) % 4;
			break;
		default:
			break;
		}
	}


};