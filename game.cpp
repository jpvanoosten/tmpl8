#include "Bounds.h"
#include "game.h"
#include "PlayerComponent.h"
#include "surface.h"
#include "template.h"
#include "Timer.h"
#include "TransformComponent.h"

#include <SDL_scancode.h>
#include <cstddef>
#include <cassert>


namespace Tmpl8
{
	Game* Game::theGame = nullptr;

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
	{
		assert(theGame == nullptr);

		theGame = this;

		tileMap = new TileMap("assets/nc2tiles.png");
		tileMap->SetTiles(map, 10);
		vec2 tileMapSize = tileMap->GetSizeInPixels();
		tileMap->SetOffset({ (ScreenWidth - tileMapSize.x) / 2.0f, (ScreenHeight - tileMapSize.y) / 2.0f });

		// Player
		Entity player;

		player.AddComponent<PlayerComponent>();
		player.AddComponent<TransformComponent>();
		player.AddComponent<PlayerComponent>();

		entities.push_back(std::move(player));

		//playerTexture = new Surface("assets/ctankbase.tga");
		//playerEntity = new Entity(playerTexture, 16, { {-17, -15}, {19, 18} }, { ScreenWidth / 2, ScreenHeight / 2 });
		//playerController = new PlayerController(playerEntity, tileMap);
	}

	Game::~Game()
	{
		//delete playerController;
		//delete playerEntity;
		//delete playerTexture;
		if(tileMap != nullptr)
			delete tileMap;

		theGame = nullptr;
	}

	Game& Game::Get()
	{
		assert(theGame != nullptr);
		return *theGame;
	}

	void Game::Init()
	{}

	void Game::KeyDown(SDL_Scancode key)
	{
		for (auto& e : entities)
		{
			e.KeyDown(key);
		}
	}

	void Game::KeyUp(SDL_Scancode key)
	{
		for (auto& e : entities)
		{
			e.KeyUp(key);
		}
	}

	void Game::Shutdown() {}

	void Game::Tick(float)
	{
		Timer::Get().Tick();

		screen->Clear(0);

		for (auto& e : entities)
		{
			e.Update();
		}

		tileMap->Draw(*screen);

		for (auto& e : entities)
		{
			e.Render(*screen);
		}

		//Bounds b = playerEntity->GetBounds();
		//screen->Box(b.min.x, b.min.y, b.max.x, b.max.y, 0xff0000);
	}

	void Game::MouseUp(int button)
	{
		for (auto& e : entities)
		{
			e.MouseUp(button);
		}
	}

	void Game::MouseDown(int button)
	{
		for (auto& e : entities)
		{
			e.MouseDown(button);
		}
	}

	void Game::MouseMove(int x, int y)
	{
		for (auto& e : entities)
		{
			e.MouseMove(x, y);
		}
	}
};