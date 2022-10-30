#pragma once

#include <SDL_events.h>

#include "TransparentSprite.h"

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
	void MouseMove(const SDL_MouseMotionEvent& e) { m_MouseX = e.x; m_MouseY = e.y; }
	void KeyUp(int key);
	void KeyDown(int key);
private:
	
	Surface* screen;
	int m_MouseX = 0;
	int m_MouseY = 0;

	TransparentSprite m_player;

	bool m_Up = false;
	bool m_Down = false;
	bool m_Left = false;
	bool m_Right = false;
};

}; // namespace Tmpl8