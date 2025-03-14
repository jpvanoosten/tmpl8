#pragma once

#include "Camera.hpp"
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
    void draw(Tmpl8::Surface& screen, const Camera& camera);

    /// <summary>
    /// Update the player.
    /// </summary>
    /// <param name="deltaTime">The elapsed time (in seconds).</param>
    void update(float deltaTime);

    /// <summary>
    /// A key was released on the keyboard.
    /// </summary>
    /// <param name="key">The key that was released.</param>
    void keyUp(int key);

    /// <summary>
    /// A key was pressed on the keyboard.
    /// </summary>
    /// <param name="key">The key that was pressed.</param>
    void keyDown(int key);

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

    void setVelocity(const Tmpl8::vec2& velocity)
    {
        v = velocity;
    }

    bool isGrounded() const
    {
        return grounded;
    }

    void setIsGrounded(bool _grounded)
    {
        grounded = _grounded;
    }

private:
    static const float moveSpeed; // Player speed in pixels/second
    static const float acceleration; // Directional acceleration.
    static const float deceleration; // Deceleration/drag.
    static const float jumpHeight; // Maximum jump height in pixels.
    static const float jumpTime; // Time (in seconds) to the apex of the jump.
    static const float gravity; // Downward gravitational force.
    static const float jumpForce; // Upward force to apply when jumping.
    static const float maxFallSpeed; // Clamp fall speed to a maximum value.
    static const float coyoteTime; // How long (in seconds) the player can still jump after falling.

    Tmpl8::vec2 p{ 0 }; // Current position of the player.
    Tmpl8::vec2 v{ 0 }; // Velocity of the player.

    AABB aabb; // AABB of the player.
    bool grounded = false; // True if the player is touching the ground.
    float coyoteTimer = 0.0f; // Timer for allowing the player to jump.

    float w = 0.0f, a = 0.0f, s = 0.0f, d = 0.0f; // Directional controls.
    bool space = false; // Jump.
};