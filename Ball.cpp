#include "Ball.h"

Ball::Ball()
    : circle{{0}, 25.0f}
    , sprite(new Tmpl8::Surface("assets/ball.png"), 1)
{}

Ball::Ball(const Circle& circle, const Tmpl8::vec2& velocity)
    : circle{ circle }
    , velocity{ velocity }
    , sprite(new Tmpl8::Surface("assets/ball.png"), 1)
{}

void Ball::Update(float deltaTime)
{
    circle.center += velocity * deltaTime;
}

void Ball::Draw(Tmpl8::Surface& screen)
{
    const int x = static_cast<int>( circle.center.x - circle.radius );
    const int y = static_cast<int>( circle.center.y - circle.radius );

    sprite.Draw(&screen, x, y);
}

const Circle& Ball::getCircle() const
{
    return circle;
}

void Ball::setPosition(const Tmpl8::vec2& pos)
{
    circle.center = pos;
}

void Ball::setRadius(float radius)
{
    circle.radius = radius;
}

const Tmpl8::vec2& Ball::getVelocity() const
{
    return velocity;
}

void Ball::setVelocity(const Tmpl8::vec2& vel)
{
    velocity = vel;
}
