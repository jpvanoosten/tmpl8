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
        const float shrink = 10;
        AABB playerAABB = player.getAABB();
        Tmpl8::vec2 v = player.getVelocity();
        Tmpl8::vec2 p = player.getPosition();

        for (auto& collider : colliders)
        {
            if (playerAABB.intersect(collider))
            {
                if (std::abs(v.x) > std::abs(v.y) )
                {
                    // First check left edge of collider.
                    if (v.x >= 0)
                    {
                        if (playerAABB.intersect(collider.left().shrink(shrink)))
                        {
                            float diff = playerAABB.max.x - collider.min.x + 1;
                            p.x -= diff;
                            v.x = 0.0f;
                        }
                    }
                    if (v.x <= 0)
                    {
                        if (playerAABB.intersect(collider.right().shrink(shrink)))
                        {
                            float diff = collider.max.x - playerAABB.min.x + 1;
                            p.x -= diff;
                            v.x = 0.0f;
                        }
                    }
                    if (v.y >= 0) // Player is moving down.
                    {
                        if (playerAABB.intersect(collider.top().shrink(shrink)))
                        {
                            // Move the player up until it's no longer colliding.
                            float diff = playerAABB.max.y - collider.min.y + 1;
                            p.y -= diff;
                            v.y = 0.0f;
                        }
                    }
                    if (v.y >= 0) // Player is moving up.
                    {
                        if (playerAABB.intersect(collider.bottom().shrink(shrink)))
                        {
                            // Move the player up until it's no longer colliding.
                            float diff = collider.max.y - playerAABB.min.y + 1;
                            p.y -= diff;
                            v.y = 0.0f;
                        }
                    }
                }
                else
                {
                    if (v.y >= 0) // Player is moving down.
                    {
                        if (playerAABB.intersect(collider.top().shrink(10)))
                        {
                            // Move the player up until it's no longer colliding.
                            float diff = playerAABB.max.y - collider.min.y + 1;
                            p.y -= diff;
                            v.y = 0.0f;
                        }
                    }
                    if (v.y >= 0) // Player is moving up.
                    {
                        if (playerAABB.intersect(collider.bottom().shrink(shrink)))
                        {
                            // Move the player up until it's no longer colliding.
                            float diff = collider.max.y - playerAABB.min.y + 1;
                            p.y -= diff;
                            v.y = 0.0f;
                        }
                    }
                    if (v.x >= 0)
                    {
                        if (playerAABB.intersect(collider.left().shrink(shrink)))
                        {
                            float diff = playerAABB.max.x - collider.min.x + 1;
                            p.x -= diff;
                            v.x = 0.0f;
                        }
                    }
                    if (v.x <= 0)
                    {
                        if (playerAABB.intersect(collider.right().shrink(shrink)))
                        {
                            float diff = collider.max.x - playerAABB.min.x + 1;
                            p.x -= diff;
                            v.x = 0.0f;
                        }
                    }
                }
            }
        }

        player.setVelocity(v);
        player.setPosition(p);
    }
};