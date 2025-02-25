#pragma once

#include "AABB.hpp"

#include "surface.h"

class Player
{
public:
    Player() = default;
    Player(const AABB& aabb, const Tmpl8::vec2& position);

    /// <summary>
    /// Draw the player.
    /// </summary>
    /// <param name="screen"></param>
    void draw(Tmpl8::Surface& screen);

    /// <summary>
    /// Update the player.
    /// </summary>
    /// <param name="deltaTime">The elapsed time (in seconds).</param>
    void update(float deltaTime);

    AABB getAABB() const
    {
        return aabb.at(p);
    }

    void setPosition(const Tmpl8::vec2& position)
    {
        p = position;
    }

    const Tmpl8::vec2& getPosition() const
    {
        return p;
    }

    const Tmpl8::vec2& getVelocity() const
    {
        return v;
    }

    void setVelocity( const Tmpl8::vec2& velocity)
    {
        v = velocity;
    }

private:
    Tmpl8::vec2 p{0}; // Current position of the player.
    Tmpl8::vec2 v{0}; // Velocity of the player.
    AABB aabb;
};