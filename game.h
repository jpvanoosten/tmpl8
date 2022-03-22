#pragma once

#include <SDL_scancode.h>
#include "Entity.h"
#include "template.h"

class TileMap;

namespace Tmpl8 {

class Surface;

class Game
{
public:
	Game();
	~Game();

	Game(const Game& copy) = delete;
	Game& operator=(const Game& copy) = delete;

	Game(Game&& copy) = default;
	Game& operator=(Game&& copy) = default;

	static Game& Get();

	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp(int button);
	void MouseDown(int button);
	void MouseMove(int x, int y);
	void KeyUp(SDL_Scancode key);
	void KeyDown(SDL_Scancode key);

private:
	Surface* screen = nullptr;
	TileMap* tileMap = nullptr;

	//Surface* playerTexture = nullptr;
	//Entity* playerEntity = nullptr;
	std::vector<Entity> entities;

	static Game* theGame;

	vec2 worldPos;
	vec2 cameraPos;
};

}; // namespace Tmpl8