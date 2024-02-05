#pragma once

#include "AABB.hpp"

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
	Surface* screen;

	Tmpl8::vec2 mousePos;
	AABB aabb1;
};

}; // namespace Tmpl8