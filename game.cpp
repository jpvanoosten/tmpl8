#include "game.h"
#include "surface.h"
#include <cstdio> //printf
#include <format>
#include <iostream>

namespace Tmpl8
{
    constexpr Pixel RED = 0xff0000;
    constexpr Pixel GREEN = 0xff00;
    constexpr Pixel BLUE = 0xff;

    // -----------------------------------------------------------
    // Initialize the application
    // -----------------------------------------------------------
    void Game::Init()
    {
        player = Player{ "assets/ball.png", 1, {0, ScreenHeight - 50} };

        // Please create a level class...
        colliders.emplace_back(AABB{ {100, 350}, {140, 370} });
        colliders.emplace_back(AABB{ {150, 300}, {190, 320} });
        colliders.emplace_back(AABB{ {200, 350}, {240, 370} });

        // Ground collider...
        colliders.emplace_back(AABB{ {-100, ScreenHeight}, {ScreenWidth + 100, ScreenHeight + 100} });
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

        player.update(deltaTime);

        checkCollisions();

        // clear the graphics window
        screen->Clear(0);

        // Draw a cross-hair for the mouse.
        {
            screen->Line(currentMousePos.x, 0.0f, currentMousePos.x, ScreenHeight - 1, RED);
            screen->Line(0.0f, currentMousePos.y, ScreenWidth - 1, currentMousePos.y, RED);
        }

        for (auto& collider : colliders)
        {
            screen->Bar(collider, RED);
        }

        player.draw(screen);
        // screen->Bar(player.getAABB(), BLUE);

        std::string text = std::format("Player velocity: {}, {}", player.getVelocity().x, player.getVelocity().y);
        screen->Print(text.c_str(), 10, 10, 0xffffff);
    }

    void Game::checkCollisions()
    {
        auto aabb = player.getAABB();
        auto vel = player.getVelocity();

        // Check if the player is colliding with any of the colliders.
        for (auto& collider : colliders)
        {
            if (!aabb.intersect(collider)) continue; // Optimize collisions.

            if (fabs(vel.x) > fabs(vel.y))
            {
                checkHorizontalCollisions(collider, aabb, vel);
                checkVerticalCollisions(collider, aabb, vel);
            }
            else
            {
                checkVerticalCollisions(collider, aabb, vel);
                checkHorizontalCollisions(collider, aabb, vel);
            }

        }

        player.setAABB(aabb);
        player.setVelocity(vel);
    }

    bool Game::checkVerticalCollisions(const AABB& collider, AABB& aabb, Tmpl8::vec2& vel)
    {
        if (vel.y > 0) // Moving down...
        {
            if (aabb.intersect(collider.topEdge().shrink(3)))
            {
                // Compute intersection.
                const float overlap = collider.min.y - aabb.max.y;
                aabb += vec2{ 0, overlap };

                vel.y = 0.0f;

                player.hitGround(); // This should be a state...
                return true;
            }
        }
        else if (vel.y < 0) // Moving up
        {
            if (aabb.intersect(collider.bottomEdge().shrink(3)))
            {
                // Compute intersection.
                const float overlap = collider.max.y - aabb.min.y;
                aabb += vec2{ 0, overlap };

                vel.y = 0.0f;
                return true;
            }
        }

        return false;
    }

    bool Game::checkHorizontalCollisions(const AABB& collider, AABB& aabb, Tmpl8::vec2& vel)
    {
        if (vel.x > 0) // Moving Right...
        {
            if (aabb.intersect(collider.leftEdge().shrink(3)))
            {
                // Compute intersection.
                const float overlap = collider.min.x - aabb.max.x;
                aabb += vec2{ overlap, 0 };

                vel.x = 0.0f;
                return true;
            }
        }
        else if (vel.x < 0) // Moving left...
        {
            if (aabb.intersect(collider.rightEdge().shrink(3)))
            {
                // Compute intersection.
                const float overlap = collider.max.x - aabb.min.x;
                aabb += vec2{ overlap, 0 };

                vel.x = 0.0f;
                return true;
            }
        }

        return false;
    }
};