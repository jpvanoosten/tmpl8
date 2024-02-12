#pragma once

#include <memory>
#include <string>

#include "template.h"
#include "surface.h"
#include "AABB.hpp"

class Player
{
public:
    enum class State
    {
        Idle,
        Moving,
        Jumping,
    };

    Player() = default; // Default constructor.
    ~Player() = default;

    // Construct a player using the sprite to visualize the player.
    Player(std::string_view sprite, int numFrames, const Tmpl8::vec2& pos);

    Player& operator=(Player&&) noexcept = default;

    const Tmpl8::vec2& getPosition() const noexcept
    {
        return position;
    }

    void setPosition(const Tmpl8::vec2& pos) noexcept
    {
        position = pos;
    }

    const Tmpl8::vec2& getVelocity() const noexcept
    {
        return velocity;
    }

    void setVelocity(const Tmpl8::vec2& vel) noexcept
    {
        velocity = vel;
    }

    void hitGround()
    {
        isJumping = false;
    }

    void update(float deltaTime);

    // Draw the player to the screen.
    void draw(Tmpl8::Surface* screen);

    AABB getAABB() const noexcept
    {
        return { position, position + size };
    }

    void setAABB(const AABB& aabb) noexcept
    {
        position = aabb.min;
    }

private:
    Tmpl8::vec2 position{0};
    Tmpl8::vec2 velocity{0};
    Tmpl8::vec2 size{ 0 };

    bool isJumping = false;

    std::unique_ptr<Tmpl8::Sprite> sprite;
};
