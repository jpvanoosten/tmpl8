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

tmpl8::vec2 Ball::GetPosAt(float deltaTime) const
{
    return pos + vel * deltaTime;
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

bool Ball::Collides(const Ball& ball) const
{
    // First compute the squared distence between each ball.
    float d = (ball.pos - pos).sqrLentgh();
    // Calculate the sum of the radii.
    float r = radius + ball.radius;
    // If the squared distance is less than the square of the radii,
    // the the balls are colliding.
    return d <= (r * r);
}

bool Ball::Collides(const Ball& ball, float& t) const
{
    // Source: Real-time Collision Detection, Section 5.5 (Ericson, C. 2005)
    tmpl8::vec2 s = ball.pos - pos; // Difference in positions (delta)
    tmpl8::vec2 v = ball.vel - vel; // Difference in velocities
    float r = ball.radius + radius; // Sum of radii
    float c = s.dot(s) - r * r;
    if (c < 0.0f) {
        // Balls are initally overlapping.
        t = 0.0f;
        return true;
    }
    float a = v.dot(v);
    if (a < 0.00001f) return false; // Balls are not moving relative to eachother.
    float b = v.dot(s);
    if (b >= 0.0f) return false; // Balls are not moving towards eachother.
    float d = b * b - a * c;
    if (d < 0.0f) return false; // No real roots, balls do not intersect.

    t = (-b - sqrtf(d)) / a;
    return true;
}

void Ball::Update(float deltaTime)
{
    if (vel.sqrLentgh() > 1.0f)
    {
        pos += vel * deltaTime;
    }
}

void Ball::Draw(tmpl8::Surface* target) const
{
    ms_Sprite.Draw(target, static_cast<int>(roundf(pos.x - radius)), static_cast<int>(roundf(pos.y - radius)));
}

