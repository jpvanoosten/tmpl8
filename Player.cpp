#include "Player.hpp"

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cmath>

using namespace Tmpl8;

Player::Player(std::string_view _sprite, int numFrames, const vec2& pos)
    : position{pos}
{
    sprite = std::make_unique<Sprite>(new Surface(_sprite.data()), numFrames);
    size = vec2{ static_cast<float>(sprite->GetWidth()), static_cast<float>(sprite->GetHeight()) };
}

void Player::update(float deltaTime)
{
    constexpr float horizontalForce = 10000.0f;
    constexpr float jumpImpulse = 800.0f;
    constexpr float gravity = 900.0f; // TODO: Tweak till it feels good.
    constexpr float maxSpeed = 200.0f;
    constexpr float drag = 0.999f; // Based on 60FPS.

    bool space = (GetAsyncKeyState(VK_SPACE) & 0x8000) != 0;
    bool left = (GetAsyncKeyState(VK_LEFT) & 0x8000) != 0;
    bool right = (GetAsyncKeyState(VK_RIGHT) & 0x8000) != 0;

    if (left)
        velocity.x -= horizontalForce * deltaTime;
    if (right)
        velocity.x += horizontalForce * deltaTime;

    if (space && !isJumping)
    {
        velocity.y -= jumpImpulse;
        isJumping = true;
    }

    // Clamp velocity.
    velocity.x = velocity.x < -maxSpeed ? -maxSpeed : velocity.x > maxSpeed ? maxSpeed: velocity.x;

    // Apply gravity.
    velocity.y += gravity * deltaTime;

    // Integrate position.
    position += velocity * deltaTime;

    // Apply drag.
    velocity.x *= powf(1.0f - drag, deltaTime); // not frame-rate independent.
}

void Player::draw(Tmpl8::Surface* screen)
{
    sprite->Draw(screen, static_cast<int>(position.x), static_cast<int>(position.y));
}
