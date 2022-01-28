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
		WATER_TILE, PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE, WATER_TILE,
		WATER_TILE, PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE, WATER_TILE,
		WATER_TILE, PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE,  PATH_TILE, WATER_TILE,
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
		Bounds playerBounds = { {-17, -15}, {19, 18} };
		playerEntity = new Entity(playerTexture, 16, playerBounds, { ScreenWidth / 2, ScreenHeight / 2 });
		playerController = new PlayerController(playerEntity, &tileMap);
	}

	Game::~Game()
	{
		delete playerTexture;
		delete playerController;
		delete playerEntity;
	}

	void Game::Init() {
	}

	void Game::KeyDown(int key)
	{
		switch (key)
		{
		case SDL_SCANCODE_LEFT:
			playerController->MoveLeft(true);
			break;
		case SDL_SCANCODE_RIGHT:
			playerController->MoveRight(true);
			break;
		case SDL_SCANCODE_UP:
			playerController->MoveUp(true);
			break;
		case SDL_SCANCODE_DOWN:
			playerController->MoveDown(true);
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
			playerController->MoveLeft(false);
			break;
		case SDL_SCANCODE_RIGHT:
			playerController->MoveRight(false);
			break;
		case SDL_SCANCODE_UP:
			playerController->MoveUp(false);
			break;
		case SDL_SCANCODE_DOWN:
			playerController->MoveDown(false);
			break;
		default:
			break;
		}
	}

	void Game::Shutdown() {}

	void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f;

		playerController->Update(deltaTime);

		screen->Clear(0);

		tileMap.Draw(*screen);
		playerEntity->Draw(*screen);

		Bounds b = playerEntity->GetBounds();
		//screen->Box(b.min.x, b.min.y, b.max.x, b.max.y, 0xff0000);

	}
};