#include "game.h"
#include "surface.h"
#include "template.h"
#include <cstdio> //printf
#include <random> // For better random number generated than what the template provides.

#define WIN32_LEAN_AND_MEAN
#include <windows.h> // For VK codes.

thread_local std::mt19937 gen{ std::default_random_engine() };

namespace tmpl8
{
    inline float RandRange(float min, float max)
    {
        std::uniform_real_distribution<float> dist(min, max);
        return dist(gen);
    }

    inline float Rand(float max)
    {
        return RandRange(0.0f, max);
    }

    // -----------------------------------------------------------
    // Initialize the application
    // -----------------------------------------------------------
    void Game::Init()
    {
        totalTime = 0.0f;
        fps = 0.0f;
        numFrames = 0;

        // Maximum random initial velocity for the ball.
        const float maxVelocity = 500.0f;

        // Balls start with a random position and random velocity.
        for (int i = 0; i < NUM_BALLS; ++i)
        {
            Ball& ball = balls[i];

            bool colliding = false;
            do {
                tmpl8::vec2 pos(Rand(ScreenWidth - ball.GetWidth()), Rand(ScreenHeight - ball.GetHeight()));
                ball.SetPos(pos);

                // Make sure it's not colliding with any other ball.
                colliding = false;
                for (int j = 0; j < i && !colliding; ++j)
                {
                    colliding = ball.Collides(balls[j]);
                }
            } while (colliding);

            tmpl8::vec2 vel(RandRange(-maxVelocity, maxVelocity), RandRange(-maxVelocity, maxVelocity));
            ball.SetVelocity(vel);
        }
    }

    // -----------------------------------------------------------
    // Close down application
    // -----------------------------------------------------------
    void Game::Shutdown()
    {
    }

    void Game::KeyDown(int key)
    {
        switch (key)
        {
        case 0x2c: // space bar.
            pause = !pause;
        }
    }

    void Game::Physics(float deltaTime)
    {
        // Check for ball/ball collision.
        for (int i = 0; i < NUM_BALLS; ++i)
        {
            Ball& bi = balls[i];
            for (int j = 0; j < i; ++j)
            {
                Ball& bj = balls[j];
                float t;
                if (bi.Collides(bj, t) && t < deltaTime) // Check collision.
                {
                    vec2 pi = bi.GetPos();
                    vec2 pj = bj.GetPos();

                    vec2 vi = bi.GetVelocity();
                    vec2 vj = bj.GetVelocity();

                    // Get the normalized vector from bj -> bi:
                    vec2 x = (pi - pj).normalized();

                    // First, compute the part of the velocity of bi that is 
                    // projected to the vector from bi -> bj.
                    vec2 xi = x * x.dot(vi);
                    // Now compute the part of the velocity that is perpendicular to xi.
                    vec2 yi = vi - xi;

                    // Next, compute the part of the velocity of bj that is
                    // projected onto the vector from bi -> bj.
                    x *= -1.0f;
                    vec2 xj = x * x.dot(vj);
                    // Now compute the part of the velocity that is perpendicular to xj.
                    vec2 yj = vj - xj;

                    float mi = bi.GetMass();
                    float mj = bj.GetMass();
                    float mij = mi + mj;

                    // Compute the new velocities:
                    vi = xi * (mi - mj) / mij + xj * (2.0f * mj) / mij + yi;
                    vj = xi * (2.0f * mi) / mij + xj * (mj - mi) / mij + yj;

                    bi.SetVelocity(vi);
                    bj.SetVelocity(vj);
#ifdef _DEBUG
                    {
                        // Draw a debug line for the new velocities.
                        float x1 = bi.GetPos().x;
                        float y1 = bi.GetPos().y;
                        float x2 = x1 + bi.GetVelocity().x;
                        float y2 = y1 + bi.GetVelocity().y;

                        screen->Line(x1, y1, x2, y2, 0xff0000);
                    }
                    {
                        // Draw a debug line for the new velocities.
                        float x1 = bj.GetPos().x;
                        float y1 = bj.GetPos().y;
                        float x2 = x1 + bj.GetVelocity().x;
                        float y2 = y1 + bj.GetVelocity().y;

                        screen->Line(x1, y1, x2, y2, 0x00ff00);
                    }
#endif
                }
            }
        }

        // Update ball positions.
        for (auto& ball : balls)
        {
            ball.Update(deltaTime);
        }
    }


    // -----------------------------------------------------------
    // Main application tick function
    // -----------------------------------------------------------
    void Game::Tick(float deltaTime)
    {
        // The deltaTime is sent in milliseconds, but we
        // want to work with seconds as it makes more sense to us.
        // Convert deltaTime from milliseconds to seconds:
        deltaTime /= 1000.0f;

        // Clamp delta time to 1/30s
        deltaTime = Min(deltaTime, 1.0f / 30.0f);

        // clear the graphics window
        screen->Clear(0);

        // Draw the frame-rate in the top-left corner of the screen.
        totalTime += deltaTime;
        numFrames++;

        if (totalTime > 1.0f)
        {
            fps = numFrames / totalTime;
            totalTime = 0.0f;
            numFrames = 0;
        }
        char buffer[16];
        sprintf_s(buffer, "FPS: %f", fps);
        screen->Print(buffer, 2, 2, 0xffffff);

        if (pause) deltaTime = 0.0f;

        const float damping = 0.9f;

        // Update the balls.
        for (auto& ball : balls)
        {
            // Apply force due to gravity:
            const tmpl8::vec2 gravity(0.0f, 500.0f); // Acceleration due to gravity is about 9.81 m/s^2, but what is that in pixels/s^2?
            ball.GetVelocity() += gravity * deltaTime;

            // Check for collisions with the screen.
            auto vel = ball.GetVelocity();

            bool hitTop = ball.GetTop() < 0.0f;
            bool hitBottom = ball.GetBottom() > ScreenHeight;
            bool hitLeft = ball.GetLeft() < 0.0f;
            bool hitRight = ball.GetRight() > ScreenWidth;

            if (hitTop)
            {
                ball.SetTop(0.0f);
                vel *= vec2(1.0f, -damping);
            }
            if (hitBottom)
            {
                ball.SetBottom(ScreenHeight);
                vel *= vec2(0.995f, -damping);
            }
            if (hitLeft)
            {
                ball.SetLeft(0.0f);
                vel *= vec2(-damping, 1.0f);
            }
            if (hitRight)
            {
                ball.SetRight(ScreenWidth);
                vel *= vec2(-damping, 1.0f);
            }

            ball.SetVelocity(vel);
        }

        // Perform the physics integrtion on the balls.
        Physics(deltaTime);

        // Draw the balls.
        for (auto& ball : balls)
        {
            ball.Draw(screen);
        }
    }

};