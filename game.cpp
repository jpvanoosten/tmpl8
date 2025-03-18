#include "game.h"
#include "surface.h"
#include "template.h"

namespace Tmpl8
{
    void Game::Init()
    {
        balls.emplace_back(vec2{ 300, 0 }, 16.0f, 16.0f);
        balls.emplace_back(vec2{ 320, ScreenHeight - 50 }, 49.0f, 49.0f);
    }

    void Game::Shutdown() {}

    const vec2 GRAVITY{ 0.0f, 400.0f }; // Force due to gravity in pixels/second.

    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f; // Convert to seconds.

        for (auto& ball : balls)
        {
            // Apply gravity.
            ball.addAcceleration(GRAVITY);

            // Update
            ball.update(deltaTime);

            // Check collisions
            vec2 p = ball.getPosition();
            vec2 v = ball.getVelocity();
            float r = ball.getRadius();

            // Test collision with the bottom of the screen.
            if (p.y + r >= ScreenHeight)
            {
                p.y = ScreenHeight - r;
                v.x *= 0.95f;
                v.y *= -0.95f;
            }

            // Test collision with the left side of the screen.
            if (p.x - r <= 0)
            {
                p.x = r;
                v.x *= -0.95f;
            }

            // Test collision with the right side of the screen.
            if (p.x + r >= ScreenWidth)
            {
                p.x = ScreenWidth - r;
                v.x *= -0.5f;
            }

            ball.setPosition(p);
            ball.setVelocity(v);
            ball.setAcceleration({ 0 });
        }

        for (size_t i = 0; i < balls.size(); i++)
        {
            for (size_t j = i + 1; j < balls.size(); j++)
            {
                if (auto hit = balls[i].checkCollision(balls[j]))
                {
                    if (hit->depth > 0)
                    {
                        // Correct the positions so the balls are no longer colliding.
                        vec2 correction = hit->normal * hit->depth * 0.5f;
                        balls[i].setPosition(balls[i].getPosition() - correction);
                        balls[j].setPosition(balls[j].getPosition() + correction);
                    }

                    // Compute relative velocity along the normal.
                    vec2 relVel = balls[j].getVelocity() - balls[i].getVelocity();
                    float velAlongNormal = relVel.dot(hit->normal);

                    // Do not resolve if balls are moving away from each other.
                    if (velAlongNormal > 0) continue;

                    // Compute restitution.
                    float e = 0.95f; // 1 is perfectly elastic, 0 is perfectly inelastic.
                    float impulse = -(1.0f + e) * velAlongNormal;
                    impulse /= 1.0f / balls[i].getMass() + 1.0f / balls[j].getMass();

                    // Apply impulse along normal
                    vec2 impulseVector = hit->normal * impulse;
                    balls[i].setVelocity(balls[i].getVelocity() - impulseVector * (1.0f / balls[i].getMass()));
                    balls[j].setVelocity(balls[j].getVelocity() + impulseVector * (1.0f / balls[j].getMass()));
                }
            }
        }


        // Draw
        screen->Clear(0);

        for (auto& ball : balls)
        {
            ball.draw(screen);
        }
    }

    void Game::MouseUp(const SDL_MouseButtonEvent& button)
    {
        switch (button.button)
        {
        case 1:
            balls.emplace_back(vec2{ static_cast<float>(button.x), static_cast<float>(button.y) }, 16.0f, 16.0f);
            break;
        case 3:
            balls.emplace_back(vec2{ static_cast<float>(button.x), static_cast<float>(button.y) }, 49.0f, 49.0f);
            break;
        default:
            break;
        }
    }

    void Game::KeyUp(const SDL_KeyboardEvent& event)
    {
        switch (event.keysym.scancode)
        {
        case SDL_SCANCODE_R:
            balls.clear();
            break;
        default:
            break;
        }
    }
};