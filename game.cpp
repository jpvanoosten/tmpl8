#include "Bounds.h"
#include "game.h"
#include "surface.h"
#include "template.h"
#include <SDL_scancode.h>
#include <cassert>

namespace Tmpl8
{
	float px = ScreenWidth / 2, py = ScreenHeight / 2;

	Surface tiles("assets/nc2tiles.png");
	Sprite tank(new Surface("assets/ctankbase.tga"), 16);

	static const Tile WATER_TILE = { true, 10, 2, 32, 32 };
	static const Tile PATH_TILE = { false, 5, 1, 32, 32 };
	static const Tile WATER_BORDER = { true, 11, 2, 32, 32 };

	//char map[5][31] = {
	//     "kcXkcXkcXkcXkcXkcXkcXkcXkcXkcX",
	//     "kcXfb fb fb kc kc kc kc kc kc ",
	//     "kcXfb fb fb fb fb kc kc kc kc ",
	//     "kcXlcXlc fb fb fb kc kc kc kc ",
	//     "kcXkcXkcXlcXlcXlcXkcXkcXkc kc "
	//};

	std::vector<Tile> map = {
		WATER_TILE, WATER_TILE, WATER_TILE, WATER_TILE, WATER_TILE, WATER_TILE,WATER_TILE, WATER_TILE, WATER_TILE, WATER_TILE,
		WATER_TILE, PATH_TILE,  PATH_TILE,  PATH_TILE,  WATER_TILE, WATER_TILE,WATER_TILE, WATER_TILE, WATER_TILE, WATER_TILE,
		WATER_TILE, PATH_TILE,  PATH_TILE,  PATH_TILE,  WATER_TILE, WATER_TILE,WATER_TILE, WATER_TILE, WATER_TILE, WATER_TILE,
		WATER_TILE, PATH_TILE,  PATH_TILE,  PATH_TILE,  WATER_TILE, WATER_TILE,WATER_TILE, WATER_TILE, WATER_TILE, WATER_TILE,
		WATER_TILE, WATER_TILE, WATER_TILE, WATER_TILE, WATER_TILE, WATER_TILE,WATER_TILE, WATER_TILE, WATER_TILE, WATER_TILE,
	};

	Game::Game()
		: screen(nullptr)
		, tileMap("assets/nc2tiles.png")
	{
		tileMap.SetTiles(map, 10);
		vec2 tileMapSize = tileMap.GetSizeInPixels();
		tileMap.SetOffset({ (ScreenWidth - tileMapSize.x) / 2.0f, (ScreenHeight - tileMapSize.y) / 2.0f });

		// Player
		playerTexture = new Surface("assets/ctankbase.tga");
		Bounds playerBounds = { {0, 0}, {static_cast<float>(playerTexture->GetWidth()),static_cast<float>(playerTexture->GetHeight()) } };
		playerEntity = new Entity(playerTexture, 16, playerBounds, { ScreenWidth / 2, ScreenHeight / 2 });
		playerController = new PlayerController(playerEntity);
	}

	Game::~Game()
	{
		delete playerTexture;
		delete playerController;
		delete playerEntity;
	}

	void Game::Init() {
		Bounds a1{ {0, 0}, {1, 1} };
		Bounds a2{ {2, 2}, {3, 3} };
		Bounds a3{ {0.25, 0.25}, {0.75, 0.75} };
		Bounds a4{ {0, 1}, {1, 2} };

		assert(a1.Collides(a2) == false);
		assert(a1.Collides(a3) == true);
		assert(a3.Collides(a1) == true);
		assert(a3.Collides(a2) == false);
		assert(a1.Collides(a4) == false);
		assert(a4.Collides(a1) == false);
	}

	void Game::KeyDown(int key)
	{
		switch (key)
		{
		case SDL_SCANCODE_LEFT:
			m_Left = 1.0f;
			break;
		case SDL_SCANCODE_RIGHT:
			m_Right = 1.0f;
			break;
		case SDL_SCANCODE_UP:
			m_Up = 1.0f;
			break;
		case SDL_SCANCODE_DOWN:
			m_Down = 1.0f;
			break;
		default:
			break;
		}
	}

	void Game::KeyUp(int key)
	{
		switch (key)
		{
		case SDL_SCANCODE_LEFT:
			m_Left = 0.0f;
			break;
		case SDL_SCANCODE_RIGHT:
			m_Right = 0.0f;
			break;
		case SDL_SCANCODE_UP:
			m_Up = 0.0f;
			break;
		case SDL_SCANCODE_DOWN:
			m_Down = 0.0f;
			break;
		default:
			break;
		}
	}

	void Game::Shutdown() {}

	void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f;

		static float totalTime = 0.0f;
		totalTime += deltaTime;

		screen->Clear(0);

		vec2 tileMapSize = tileMap.GetSizeInPixels();
		int screenWidth = screen->GetWidth();
		int screenHeight = screen->GetHeight();

		float tx = 0;
		float ty = 0;

		if (m_Left) tx -= 50.0f * deltaTime;
		if (m_Right) tx += 50.0f * deltaTime;
		if (m_Up) ty -= 50.0f * deltaTime;
		if (m_Down) ty += 50.0f * deltaTime;

		tileMap.Translate({ -tx, -ty });
		tileMap.Draw(*screen);

		playerController->Update(deltaTime);
		playerEntity->Draw(*screen);

		//for (auto& entity : entities)
		//{
		//	entity.Draw(*screen);
		//}
	}
};