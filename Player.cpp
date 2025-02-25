#include "Player.hpp"

Player::Player(const AABB& aabb, const Tmpl8::vec2& position)
    : p{ position }
    , aabb{ aabb }
{}

void Player::draw(Tmpl8::Surface& screen)
{
    screen.Box(aabb.at(p), 0x0000ff);
}

void Player::update(float deltaTime)
{
    p += v * deltaTime;
}

void Player::keyUp(int key)
{
    switch (key)
    {
        
    }
}

void Player::keyDown(int key)
{
    switch (key)
    {
        
    }
}

