#include "Ball.hpp"
#include "surface.h"

using namespace Tmpl8;

Ball::Ball(const Tmpl8::vec2& pos, float radius)
    : position{ pos }
    , radius{ radius }
{}

const Tmpl8::vec2& Ball::getPos() const
{
    return position;
}

void Ball::setPos(const Tmpl8::vec2& pos)
{
    position = pos;
}

const Tmpl8::vec2& Ball::getVel() const
{
    return velocity;
}

void Ball::setVelocity(const Tmpl8::vec2& vel)
{
    velocity = vel;
}

float Ball::getRadius() const
{
    return radius;
}

void Ball::setRadius(float _radius)
{
    radius = _radius;
}

bool Ball::checkCollision(const Ball& other) const
{
    Tmpl8::vec2 d = other.position - position; // Displacement.
    const float l = d.sqrLentgh();
    const float r = other.radius + radius; // Sum of the radii.

    return l < (r * r);
}

void Ball::update(float deltaTime)
{
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
