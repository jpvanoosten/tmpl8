#include "Ball.hpp"
#include "surface.h"

#include <cmath>

using namespace Tmpl8;

Ball::Ball(const Tmpl8::vec2& pos, float radius, float mass)
    : position{ pos }
    , radius{ radius }
    , mass{ mass }
{}

const Tmpl8::vec2& Ball::getPosition() const
{
    return position;
}

void Ball::setPosition(const Tmpl8::vec2& pos)
{
    position = pos;
}

const Tmpl8::vec2& Ball::getVelocity() const
{
    return velocity;
}

void Ball::setVelocity(const Tmpl8::vec2& vel)
{
    velocity = vel;
}

const Tmpl8::vec2& Ball::getAcceleration() const
{
    return acceleration;
}

void Ball::setAcceleration(const Tmpl8::vec2& acc)
{
    acceleration = acc;
}

void Ball::addAcceleration(const Tmpl8::vec2& acc)
{
    acceleration += acc;
}

void Ball::addForce(const Tmpl8::vec2& force)
{
    acceleration += force * (1.0f / mass );
}

float Ball::getRadius() const
{
    return radius;
}

void Ball::setRadius(float _radius)
{
    radius = _radius;
}

float Ball::getMass() const
{
    return mass;
}

void Ball::setMass(float _mass)
{
    mass = _mass;
}

std::optional<HitInfo> Ball::checkCollision(const Ball& other) const
{
    Tmpl8::vec2 d = other.position - position; // Displacement.
    const float l = d.sqrLength();
    const float r = other.radius + radius; // Sum of the radii.

    if(l < (r * r))
    {
        HitInfo hit;

        hit.normal = d.normalized();
        hit.depth = r - std::sqrt(l);

        return hit;
    }

    return {};
}

void Ball::update(float deltaTime)
{
    velocity += acceleration * deltaTime;
    position += velocity * deltaTime;
}

void Ball::draw(Tmpl8::Surface* surface)
{
    for (int i = 0; i < 64; i++)
    {
        const float r1 = static_cast<float>(i) * PI / 32;
        const float r2 = static_cast<float>(i + 1) * PI / 32;

        surface->Line(position.x - radius * sinf(r1), position.y - radius * cosf(r1),
            position.x - radius * sinf(r2), position.y - radius * cosf(r2), 0xff0000);
    }

}
