#pragma once

#include "Entity.h"
#include "PlayerController.h"
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
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp(int key);
	void KeyDown(int key);
private:
	Surface* screen = nullptr;
	TileMap* tileMap = nullptr;

	Surface* playerTexture = nullptr;
	Entity* playerEntity = nullptr;
	PlayerController* playerController = nullptr;
};

}; // namespace Tmpl8