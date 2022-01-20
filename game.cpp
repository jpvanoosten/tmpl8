#include "game.h"
#include "surface.h"
#include "template.h"

namespace Tmpl8
{
	void Game::Init() 
	{
		for (auto& d : dots)
		{
			d.x = IRand(ScreenWidth);
			d.y = IRand(ScreenHeight);
		}
	}

	void Game::Shutdown() {}

	void Game::Tick(float deltaTime)
	{
		screen->Clear(0);
		screen->Line(mousex, 0, mousex, screen->GetHeight() - 1, 0xff0000);
		screen->Line(0, mousey, screen->GetWidth() - 1, mousey, 0xff0000);

		for (auto& d : dots)
		{
			float dx = d.x - mousex, dy = d.y - mousey;
			float dist = sqrtf(dx * dx + dy * dy);
			if (dist < 50)
			{
				d.x += dx / dist;
				d.y += dy / dist;
			}
			screen->Plot(d.x, d.y, 0xffffff);
		}
	}
};