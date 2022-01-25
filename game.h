#pragma once

#include "TileMap.h"

namespace Tmpl8 {

class Surface;
class Game
{
public:
	Game();

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
	Surface* screen;

	float m_Up = 0.0f;
	float m_Left = 0.0f;
	float m_Right = 0.0f;
	float m_Down = 0.0f;
	TileMap tileMap;
};

}; // namespace Tmpl8