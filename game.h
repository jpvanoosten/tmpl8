#pragma once

#include <SDL_scancode.h>
#include "Entity.h"
#include "TileMap.h"

namespace Tmpl8 {

class Surface;
class Game
{
public:
	Game();

	~Game();

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

};

}; // namespace Tmpl8