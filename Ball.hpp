#pragma once // Should be at the top of every header file!

#include "template.h"

#include <optional>

namespace Tmpl8
{
    class Surface;
}

struct HitInfo
{
    Tmpl8::vec2 normal;
    float depth;
};

class Ball
{
public:
    Ball() = default; // Default constructor.
    Ball(const Tmpl8::vec2& pos, float radius, float mass = 1.0f ); // Parameratized constructor.

    // Follow the rule of 5 (or rule of 7 now with move constructs).

    const Tmpl8::vec2& getPosition() const;
    void setPosition(const Tmpl8::vec2& pos); // non-const!

    const Tmpl8::vec2& getVelocity() const;
    void setVelocity(const Tmpl8::vec2& vel);

    const Tmpl8::vec2& getAcceleration() const;
    void setAcceleration(const Tmpl8::vec2& acc);

    void addAcceleration(const Tmpl8::vec2& acc);
    void addForce(const Tmpl8::vec2& force);

    float getRadius() const;
    void setRadius(float radius);

    float getMass() const;
    void setMass(float mass);

    std::optional<HitInfo> checkCollision(const Ball& other) const;

    // Update the ball
    // deltaTime: Elapsed time in seconds.
    void update(float deltaTime); 

    // Draw the ball to the screen.
    void draw(Tmpl8::Surface* surface);

private:
    Tmpl8::vec2 position{ 0 }; // Prefer default on declaration.
    Tmpl8::vec2 velocity{ 0 }; // Initial velocity both direction and magnitude (speed).
    Tmpl8::vec2 acceleration{ 0 }; // Acceleration of the ball.
    float radius{ 0.0f };
    float mass{ 1.0f }; // Mass of the ball
};
