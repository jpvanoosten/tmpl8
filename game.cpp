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
		food = { 20, 15 };
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
	int x[1024] = { 5, 6, 7, 8, 9, 10, 11, 12 };
	int y[1024] = { 8, 8, 8, 8, 8, 8, 8, 8 };
	int heading = 0;
	const int delta[8] = { 1, 0, 0, 1, -1, 0, 0, -1 };
	int head = 7, tail = 0;

	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);

		for (int i = 0; i < snakeSize; i++)
			screen->Box(x[i] * 8, y[i] * 8, x[i] * 8 + 6, y[i] * 8 + 6, 0xffffff);
		int headx = (x[head] + delta[heading * 2] + (ScreenWidth/8)) % (ScreenWidth / 8);
		int heady = (y[head] + delta[heading * 2 + 1] + (ScreenHeight/8)) % (ScreenHeight / 8);
		tail = (tail + 1) % snakeSize;
		head = (head + 1) % snakeSize;
		x[head] = headx;
		y[head] = heady;

		if (!isFoodEaten)
		{
			screen->Box(food.x * 8, food.y * 8, food.x * 8 + 6, food.y * 8 + 6, 0x0000ff);
		}

		for (int i = 0; i < snakeSize; ++i)
		{
			if (i == head) continue;
			if (x[i] == headx && y[i] == heady)
			{
				std::cout << "Ouch!" << std::endl;
				snakeSize = Max(1, snakeSize - 1);
			}
		}

		if (headx == (int)food.x && heady == (int)food.y)
		{
			x[snakeSize] = (int)food.x;
			y[snakeSize] = (int)food.y;

			snakeSize = Min(snakeSize + 1, 1024);
			++foodEaten;

			food = { static_cast<float>(IRand(ScreenWidth/8)), static_cast<float>(IRand(ScreenHeight/8)) };
		}

		//if (GetAsyncKeyState(VK_LEFT)) heading = (heading + 3) % 4;
		//if (GetAsyncKeyState(VK_RIGHT)) heading = (heading + 1) % 4;

		char buffer[256];
		snprintf(buffer, 256, "Food eaten: %i", foodEaten);
		screen->Print(buffer, 10, 10, 0xffffff);

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