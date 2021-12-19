#pragma once

#include "Ball.h"

const size_t NUM_BALLS = 50;

namespace tmpl8 {

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
	void MouseMove( int x, int y ) { /* implement if you want to detect mouse movement */ }
	void KeyUp( int key ) { /* implement if you want to handle keys */ }
	void KeyDown(int key);
private:
	Surface* screen;
	Ball balls[NUM_BALLS];

	float totalTime = 0.0f;
	float fps = 0.0f;
	unsigned int numFrames = 0;

	bool pause = false;
};

}; // namespace Tmpl8