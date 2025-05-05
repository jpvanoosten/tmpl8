#include "Player.hpp"
#include "Math.hpp"

#include <cmath> // for std::sqrt

#include <SDL_scancode.h>

const float Player::moveSpeed = 500.0f; // Player speed in pixels/second
const float Player::acceleration = 2000.0f; // Directional acceleration.
const float Player::deceleration = 5000.0f; // Deceleration/drag.
const float Player::jumpHeight = 100.0f; // Maximum jump height (in pixels).
const float Player::jumpTime = 0.25f; // Time (in seconds) to the apex of the jump.
const float Player::maxFallSpeed = 1500.0f; // Clamp fall speed to a maximum value.
const float Player::coyoteTime = 0.1f; // How long (in seconds) the player can still jump after falling.

// Gravity and jump speed are computed to achieve the desired jump parabola.
// Source: https://2dengine.com/?p=platformers#Jumping
// Source: https://jobtalle.com/2d_platformer_physics.html
const float Player::gravity = 2.0f * jumpHeight / ( jumpTime * jumpTime ); // Downward gravitational force.
const float Player::jumpForce = std::sqrt(2.0f * jumpHeight * gravity); // Upward force to apply when jumping.

Player::Player(const AABB& aabb, const Tmpl8::vec2& position)
    : p{ position }
    , aabb{ aabb }
    , circle{ Tmpl8::vec2{0}, std::min(aabb.width()/2.0f, aabb.height()/2.0f) }
{
}

void Player::draw(Tmpl8::Surface& screen, const Camera& camera)
{
    //screen.Box(camera.toScreenSpace(aabb.at(p)), 0x0000ff);
    screen.Circle(camera.toScreenSpace(circle + p), 0x0000ff);
}

void Player::update(float deltaTime)
{
    Tmpl8::vec2 input{ d - a, 0.0f };

    // Apply directional movement.
    if (input.x != 0.0f)
    {
        v.x = moveToward(v.x, input.x * moveSpeed, acceleration * deltaTime);
    }
    else
    {
        v.x = moveToward(v.x, 0.0f, deceleration * deltaTime);
    }

    // Apply gravity.
    v.y += gravity * deltaTime;
    // Clamp fall speed.
    v.y = std::min(v.y, maxFallSpeed);

    // Jumping.
    if (grounded)
    {
        coyoteTimer = coyoteTime;
    }
    else
    {
        coyoteTimer -= deltaTime;
    }

    if (space && coyoteTimer > 0.0f)
    {
        v.y = -jumpForce;
        coyoteTimer = 0.0f;
        grounded = false;
    }

    // Move the player.
    p += v * deltaTime;
}

void Player::keyUp(int key)
{
    switch (key)
    {
    case SDL_SCANCODE_W:
        w = 0.0f;
        break;
    case SDL_SCANCODE_A:
        a = 0.0f;
        break;
    case SDL_SCANCODE_S:
        s = 0.0f;
        break;
    case SDL_SCANCODE_D:
        d = 0.0f;
        break;
    case SDL_SCANCODE_SPACE:
        space = false;
        break;
    }
}

void Player::keyDown(int key)
{
    switch (key)
    {
    case SDL_SCANCODE_W:
        w = 1.0f;
        break;
    case SDL_SCANCODE_A:
        a = 1.0f;
        break;
    case SDL_SCANCODE_S:
        s = 1.0f;
        break;
    case SDL_SCANCODE_D:
        d = 1.0f;
        break;
    case SDL_SCANCODE_SPACE:
        space = true;
        break;
    }
}

