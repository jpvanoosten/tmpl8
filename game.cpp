#include "game.h"

#include <cassert>

#include "surface.h"

#include "AABB.hpp"
#include "Circle.hpp"

namespace Tmpl8
{
    void Game::Init()
    {
        std::shared_ptr<SpriteSheet> playerShip = std::make_shared<SpriteSheet>("assets/playership.png", 1, 9);
        tileMap = TileMap{ playerShip, 5, 5 };

        int tileIds[] = {
            0, 0, 0, 0, 0,
            1, 1, 1, 1, 1,
            -1, 0, 0, 0, -1,
            2, 2, 2, 2, 2,
            8, 8, 8, 8, 8
        };

        for (int y = 0; y < 5; ++y)
        {
            for (int x = 0; x < 5; ++x)
            {
                tileMap(x, y) = tileIds[y * 5 + x];
            }
        }

        AABB playerAABB{ {-20, -80}, {20, 0} };
        player = Player{ playerAABB, {ScreenWidth / 2, ScreenHeight / 2} };

        // Setup colliders
        colliders = {
            AABB::fromXYWH(300, 475, 197, 36),
            AABB::fromXYWH(534, 383, 102, 36),
            AABB::fromXYWH(656, 311, 112, 36),
            AABB::fromXYWH(-1e3f, ScreenHeight-1, 1e7f, 1e7f),
        };
    }

    void Game::Shutdown() {}

    // Accelleration due to gravity in pixels/second^2
    static const Tmpl8::vec2 gravity{ 0, 200.0f };

    void Game::Tick(float deltaTime)
    {
        deltaTime /= 1000.0f; // Convert to seconds.
        // Clamp delta time so physics doesn't explode!
        deltaTime = std::min(deltaTime, 1.0f / 60.0f);

        // Update game.
        {
            // Integrate gravity.
            auto v = player.getVelocity();
            v += gravity * deltaTime;
            player.setVelocity(v);
        }

        player.update(deltaTime);

        checkCollisions();

        // Render game.
        screen->Clear(0);

        player.draw(*screen);

        for (auto& collider : colliders)
        {
            screen->Box(collider, 0xFF0000);
        }
    }

    void Game::checkCollisions()
    {
        AABB playerAABB = player.getAABB();
        Tmpl8::vec2 v = player.getVelocity();
        Tmpl8::vec2 p = player.getPosition();

        player.setIsGrounded(false);

        for (auto& collider : colliders)
        {
            // Source: https:://grok.com (March 6, 2025). "What are the basic steps to implementing 2D collision detection and response with AABBs?"
            if (playerAABB.intersect(collider))
            {
                float xOverlap = std::min(playerAABB.max.x, collider.max.x) - std::max(playerAABB.min.x, collider.min.x);
                float yOverlap = std::min(playerAABB.max.y, collider.max.y) - std::max(playerAABB.min.y, collider.min.y);

                Tmpl8::vec2 normal{ 0 };

                if (xOverlap < yOverlap)
                {
                    // The "minimum translation vector" (MTV) is the x-axis.

                    // Player is to the left of the collider.
                    if (playerAABB.min.x < collider.min.x)
                    {
                        normal = { -1, 0 };
                    }
                    else // Player is to the right of the collider.
                    {
                        normal = { 1, 0 };
                    }
                    // Zero the x-velocity.
                    v.x = 0.0f;
                }
                else
                {
                    // The players is above the collider.
                    if (playerAABB.min.y < collider.min.y)
                    {
                        normal = { 0, -1 };
                        player.setIsGrounded(true);
                    }
                    else
                    {
                        normal = { 0, 1 };
                    }
                    v.y = 0.0f;
                }

                p += Tmpl8::vec2{xOverlap, yOverlap} * normal;
            }
        }

        player.setVelocity(v);
        player.setPosition(p);
    }
};