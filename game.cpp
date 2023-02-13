#include "game.h"
#include "surface.h"
#include <cstdio> //printf

namespace Tmpl8
{
	// -----------------------------------------------------------
	// Initialize the application
	// -----------------------------------------------------------
	void Game::Init()
	{
		ball.setPosition({ ScreenWidth / 2.0f, ScreenHeight / 2.0f });
		ball.setVelocity(vec2{ 1, -1 } * 100.0f );
	}
	
	// -----------------------------------------------------------
	// Close down application
	// -----------------------------------------------------------
	void Game::Shutdown()
	{
	}

	// -----------------------------------------------------------
	// Main application tick function
	// -----------------------------------------------------------
	void Game::Tick(float deltaTime)
	{
		deltaTime /= 1000.0f;

		// Update
		ball.Update(deltaTime);
		// Make it bounce...
		vec2 vel = ball.getVelocity();
		Circle circle = ball.getCircle();
		// Hit right side of screen.
		if(circle.center.x - circle.radius <= 0.0f )
		{
			circle.center.x = circle.radius;
			vel.x = -vel.x;
		}
		else if( circle.center.x + circle.radius >= ScreenWidth)
		{
			circle.center.x = ScreenWidth - circle.radius;
			vel.x = -vel.x;
		}
		if(circle.center.y - circle.radius <= 0.0f )
		{
			circle.center.y = circle.radius;
			vel.y = -vel.y;
		}
		else if( circle.center.y + circle.radius >= ScreenHeight)
		{
			circle.center.y = ScreenHeight - circle.radius;
			vel.y = -vel.y;
		}
		ball.setPosition(circle.center);
		ball.setVelocity(vel);
		
		// clear the graphics window
		screen->Clear(0);

		ball.Draw(*screen);
	}
};