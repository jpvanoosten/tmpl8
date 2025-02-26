#include "Player.hpp"

#include <SDL_scancode.h>

const float Player::playerSpeed = 100.0f;

Player::Player(const AABB& aabb, const Tmpl8::vec2& position)
    : p{ position }
    , aabb{ aabb }
{
}

void Player::draw(Tmpl8::Surface& screen)
{
    screen.Box(aabb.at(p), 0x0000ff);
}

void Player::update(float deltaTime)
{
    Tmpl8::vec2 p0 = p;
    Tmpl8::vec2 move{ d - a, 0.0f };
    Tmpl8::vec2 vel = move * playerSpeed;

    if (space)
    {
        vel.y -= 20000.0f;
        space = false;
    }

    v += vel * deltaTime;
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

