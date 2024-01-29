#include "game.h"
#include "surface.h"
#include "template.h"
#include "windows.h"

namespace Tmpl8
{
    void Game::Init() {}

    void Game::Shutdown() {}

    Ball ball1{ {300, 0}, 16 };
    Ball ball2{ {320, ScreenHeight - 50}, 49 };

    const vec2 GRAVITY{ 0.0f, 200.0f }; // Force due to gravity in pixels/second.

    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f; // Convert to seconds.

        // Apply gravity.
        {
            vec2 vel = ball1.getVel();

            vel += GRAVITY * deltaTime;

            // Other velocity...
            ball1.setVelocity(vel);
        }

        // Update
        ball1.update(deltaTime);
        ball2.update(deltaTime);

        // Apply constraints.
        // Ground constraint
        {
            vec2 pos = ball1.getPos();
            vec2 vel = ball1.getVel();
            const float r = ball1.getRadius();

            // Test collision with the bottom of the screen.
            if(pos.y >= ScreenHeight - r)
            {
                pos.y = ScreenHeight - r - 1;
                vel.y *= -0.50f;
            }
            // Test collision with the right side of the screen.
            if(pos.x < r)
            {
                pos.x = r;
            }
            else if(pos.x >= ScreenWidth - r)
            {
                pos.x = ScreenWidth - r - 1;
            }

            // Update ball.
            ball1.setPos(pos);
            ball1.setVelocity(vel);
        }
        // Ball collision.
        if (ball1.checkCollision(ball2))
        {
            // Hit!
            int i = 3;
            // Assignment: Finish this function!
        }

        // Draw
        screen->Clear(0);

        ball1.draw(screen);
        ball2.draw(screen);
    }
};