#pragma once

#include "TileMap.h"
#include "template.h"
#include "Player.hpp"

namespace Tmpl8 {

	class Surface;
	class Game
	{
	public:
		void SetTarget(Surface* surface) { screen = surface; }
		void Init();
		void Shutdown();
		void Tick(float deltaTime);
		void MouseUp(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseDown(int button) { /* implement if you want to detect mouse button presses */ }
		void MouseMove(int x, int y) { /* implement if you want to detect mouse movement */ }
		void KeyUp(int key) { /* implement if you want to handle keys */ }
		void KeyDown(int key) {}
	private:
		Surface* screen;
		TileMap tileMap;
		Player player;
		std::vector<AABB> colliders;
	};

}; // namespace Tmpl8