#pragma once

#include <SDL_events.h>

#include "Ball.hpp"

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
	void MouseUp(const SDL_MouseButtonEvent& event);
	void MouseDown( const SDL_MouseButtonEvent& event ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp(const SDL_KeyboardEvent& event);
	void KeyDown(const SDL_KeyboardEvent& event) { /* implement if you want to handle keys */ }
private:
	Surface* screen;
    std::vector<Ball> balls;
};

}; // namespace Tmpl8