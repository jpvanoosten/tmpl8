#include "Ball.h"

#include <cmath>

tmpl8::Sprite Ball::ms_Sprite(new tmpl8::Surface("assets/ball.png"), 1);

Ball::Ball(const tmpl8::vec2& pos, const tmpl8::vec2& vel)
    : pos(pos)
    , vel(vel)
{
    // I assume the ball sprite is square...
    radius = ms_Sprite.GetWidth() / 2.0f;
}

Ball::~Ball()
{}



void Ball::SetPos(const tmpl8::vec2& pos)
{
    this->pos = pos;
}

const tmpl8::vec2& Ball::GetPos() const
{
    return pos;
}

tmpl8::vec2& Ball::GetPos()
{
    return pos;
}

void Ball::SetVelocity(const tmpl8::vec2& vel)
{
    this->vel = vel;
}

const tmpl8::vec2& Ball::GetVelocity() const
{
    return vel;
}

tmpl8::vec2& Ball::GetVelocity()
{
    return vel;
}

void Ball::SetMass(float mass)
{
    this->mass = mass;
}

float Ball::GetMass() const
{
    return mass;
}

float Ball::GetWidth() const
{
    return static_cast<float>(ms_Sprite.GetWidth());
}

float Ball::GetHeight() const
{
    return static_cast<float>(ms_Sprite.GetHeight());
}

float Ball::GetTop() const
{
    return pos.y - radius;
}

void Ball::SetTop(float top)
{
    pos.y = top + radius;
}

float Ball::GetBottom() const
{
    return pos.y + radius;
}

void Ball::SetBottom(float bottom)
{
    pos.y = bottom - radius;
}

float Ball::GetLeft() const
{
    return pos.x - radius;
}

void Ball::SetLeft(float left)
{
    pos.x = left + radius;
}

float Ball::GetRight() const
{
    return pos.x + radius;
}

void Ball::SetRight(float right)
{
    pos.x = right - radius;
}

float Ball::GetRadius() const
{
    return radius;
}

bool Ball::Collides(const Ball& ball)
{
    // First compute the squared distence between each ball.
    float d = (ball.pos - pos).sqrLentgh();
    // Calculate the sum of the radii.
    float r = radius + ball.radius;
    // If the squared distance is less than the square of the radii,
    // the the balls are colliding.
    return d <= (r * r);
}

void Ball::Update(float deltaTime)
{
    pos += vel * deltaTime;
}

void Ball::Draw(tmpl8::Surface* target) const
{
    ms_Sprite.Draw(target, static_cast<int>(roundf(pos.x - radius)), static_cast<int>(roundf(pos.y - radius)));
}

