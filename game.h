#pragma once

#include "AABB.hpp"
#include "Player.hpp"

#include <vector>

namespace Tmpl8 {

class Surface;
class Game
{
public:
	void SetTarget( Surface* surface ) { screen = surface; }
	void Init();
	void Shutdown();
	void Tick( float deltaTime );
	void MouseUp( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseDown( int button ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove(int x, int y)
	{
	    mousePos.x = static_cast<float>( x );
		mousePos.y = static_cast<float>( y );
	}
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown( int key ) { /* implement if you want to handle keys */ }

private:
	void checkCollisions();

	Surface* screen;

	Tmpl8::vec2 mousePos;

	std::vector<AABB> colliders; // All the platforms in the level.
	Player player;
};

}; // namespace Tmpl8